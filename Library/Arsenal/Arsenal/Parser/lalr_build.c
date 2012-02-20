
/*
 * The Arsenal Library
 * Copyright (c) 2009 by Solidus
 * 
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express 
 * or implied warranty.
 *
 */


#include "parser_in.h"
#include "lalr.h"

AR_NAMESPACE_BEGIN


/*
此函数所生成的所有heap上数据都会放入all_config中，因此，在容错逻辑下，不需要清理任何资源
*/
static	arStatus_t	__calc_lr0_closure(lalrConfigList_t *all_config, const psrGrammar_t *grammar, const psrSymbMap_t *first_set, bool_t lr0)
{
		arStatus_t				status;
		lalrConfigNode_t		*node;
		
		AR_ASSERT(all_config != NULL && grammar != NULL && first_set != NULL);
		AR_ASSERT(all_config->count > 0);

		status = AR_S_YES;

		for(node = all_config->head; node != NULL; node = node->next)
		{
				const psrRule_t *rule;
				size_t rule_num;
				size_t delim;
				const psrSymb_t *symb;

				rule_num = node->config->rule_num;
				delim = node->config->delim;
				rule = Parser_GetRuleFromGrammar(grammar, rule_num);

				if(delim >= rule->body.count)
				{
						continue;
				}

				/*
				A -> a . B C;
				则 body[delim] == B则将所有 B -> . a b c;装入本项
				*/
				symb = rule->body.lst[delim];

				if(symb->type == PARSER_NONTERM)
				{
						size_t i;
						
						for(i = 0; i < grammar->count; ++i)
						{
								const psrRule_t *inner_rule;
								size_t			inner_rule_num;

								inner_rule = grammar->rules[i];
								inner_rule_num = i;
								/*检索每一条语法*/

								if(Parser_CompSymb(symb, inner_rule->head) == 0)
								{
										/*
										如果当前lhs与symb相同，则将当前语法例如 B -> . a b c加入项集all_config
										*/
										size_t k;
										lalrConfig_t *new_config;

										new_config = Parser_FindFromConfigList(all_config, inner_rule_num, 0);

										if(new_config == NULL)
										{
												new_config = Parser_InsertToConfigListByValue(all_config, inner_rule_num, 0, grammar);/*资源分配点0*/

												if(new_config == NULL)
												{
														return AR_E_NOMEM;
												}

										}

										AR_ASSERT(new_config != NULL);

										/*lr0模式，不计算传播链以及follow set*/
										if(lr0)
										{
												continue;
										}
										
										/*
												S : A . B C D
												  ;

												body[delim] == B;
												body[k] == C 
										*/

										for(k = delim + 1; k < rule->body.count; ++k)/*计算传播链*/
										{
												const psrSymb_t *sp = rule->body.lst[k];
												AR_ASSERT(sp != NULL);

												if(sp->type == PARSER_TERM)
												{
														/*
														如果sp为终结符，则将其加入新项new_config的follow_set中，之后循环中止，因为在
														本条语法规则中不会有sp之后的终结符加入到new_config中
														*/
														int_t idx = Parser_GetTermSpecID(grammar, sp);
														AR_ASSERT(idx >= 0);

														status = Parser_SetBitInBitSet(&new_config->follow_set, (size_t)idx);/*资源分配点1，new_config存储于all_config中*/
														
														if(status  != AR_S_YES)
														{
																return status;
														}

														break;
												}else
												{
														/*
														如果sp为非终结符，则将其first_set加入到new_config中，如果此终结符可导出空串，
														则循环继续，否则循环中止
														*/
														const psrMapRec_t *rec;
														size_t x;
														rec = Parser_GetSymbolFromSymbMap(first_set, sp);
														
														AR_ASSERT(rec != NULL);

														for(x = 0; x < rec->lst.count; ++x)
														{
																int_t idx;
																AR_ASSERT(rec->lst.lst[x]->type == PARSER_TERM);
																
																idx = Parser_GetTermSpecID(grammar, rec->lst.lst[x]);
																AR_ASSERT(idx >= 0);

																status = Parser_SetBitInBitSet(&new_config->follow_set, (size_t)idx);/*资源分配点2,同点1*/

																if(status != AR_S_YES)
																{
																		return status;
																}
														}

														if(!rec->can_empty)
														{
																break;
														}
												}
										}
												
										/*
										形如node->config为A -> a . B C D;
										若C D均可导出空串， 则则A的follow_set将会传播至新项中
										*/
										if(k == rule->body.count)
										{
												status = Parser_InsertToConfigList(node->config->forward, new_config);/*资源分配点3,node是all_config中的节点*/

												if(status != AR_S_YES)
												{
														return status;
												}
										}
								}
						}
				}

		}

		return status;

}



static	arStatus_t	__build_goto(lalrState_t *start, const psrGrammar_t *grammar, lalrStateSet_t *set, const psrSymbMap_t *first_set, bool_t lr0);


/*
此函数会生成新的lalr状态，并将其插入lalrStateSet_t，并递归调用__build_goto，因此所有未放入set的state都需要清理，
因为state依赖于basis，因此此函数无论成功与否，都需要处理basis，清理资源或者归属给new_state
*/
static	lalrState_t* __build_state(lalrConfigList_t *basis, const psrGrammar_t *grammar, lalrStateSet_t *set, const psrSymbMap_t *first_set, bool_t lr0)
{
		lalrState_t		*new_state;
		AR_ASSERT(basis != NULL && basis->count > 0 && grammar != NULL && set != NULL && first_set != NULL);
		

		Parser_SortConfigList(basis);
		new_state = Parser_FindStateByBasis(set, basis);


		if(new_state)
		{
				/*
				此核心项已经存在于state_set中，则直接将basis中的backward传播链放入已存在的状态的后向传播链，之后清理掉无用的basis
				*/
				if(!lr0)
				{
						lalrConfigNode_t *l, *r;
						/*将新的核心项的向后传播的表(由goto生成) copy到已存在的状态（项集）中*/
						for(l = basis->head, r = new_state->basis->head; l != NULL && r != NULL; l = l->next, r = r->next)
						{
								Parser_UnionConfigList(r->config->backward, l->config->backward);
						}
				}
				
				/*销毁无用核心项*/
				Parser_DestroyConfigList(basis, true);
				
				return new_state;
		}else
		{
				/*
				核心项不存在于状态集中，因此需要新建状态并在其上计算goto 递归调用
				*/

				lalrConfigList_t *all_config;

				all_config = Parser_CreateConfigList();/*资源分配点0*/

				if(all_config == NULL)/*失败则只需清理掉basis，之后返回空，新状态未建立*/
				{
						Parser_DestroyConfigList(basis, true);/*清理basis及其内部config*/
						return NULL;
				}

				if(Parser_CopyConfigList(all_config, basis) != AR_S_YES)/*资源分配点1，如果失败，则清理all_config和basis*/
				{
						Parser_DestroyConfigList(all_config, false);/*清理all_config*/
						all_config = NULL;
						Parser_DestroyConfigList(basis, true);/*清理basis及其内部所包含的config*/
						basis = NULL;

						return NULL;
				}


				if(__calc_lr0_closure(all_config, grammar, first_set, lr0) != AR_S_YES)/*资源分配点2，计算lr0闭包，如果失败，则清理all_config和basis*/
				{
						Parser_DestroyConfigList(all_config, true);/*此时all_config必定包含basis所有config，及其衍生的lr0非核心项，因此要清理all_config及其所包含config*/
						all_config = NULL;
						
						Parser_DestroyConfigList(basis, false); 
						basis = NULL;

						return NULL;
				}

				Parser_SortConfigList(all_config);
				
				new_state = Parser_CreateState();/*资源分配点3*/

				if(new_state == NULL)/*如果失败，则状态创建未完整，还是只需要清理all_config和basis*/
				{
						Parser_DestroyConfigList(all_config, true);/*此时all_config必定包含basis所有config，及其衍生的lr0非核心项，因此要清理all_config及其所包含config*/
						all_config = NULL;
						
						Parser_DestroyConfigList(basis, false); 
						basis = NULL;

						return NULL;

				}


				new_state->basis = basis;
				new_state->all_config = all_config;

				if(Parser_InsertToStateSet(set, new_state) != AR_S_YES)/*资源分配点4，如果失败，new_state未被插入状态集合set中，因此清理掉此状态的资源就可以了*/
				{
						Parser_DestroyState(new_state);
						new_state = NULL;
						return NULL;
				}

				
				/*build_goto失败，不必清理new_state，因为new_state已经被插入到set中*/
				if(__build_goto(new_state, grammar, set, first_set, lr0) != AR_S_YES)
				{
						return NULL;
				}else
				{
						return new_state;
				}
		}
}


static	arStatus_t	__build_goto(lalrState_t *start, const psrGrammar_t *grammar, lalrStateSet_t *set, const psrSymbMap_t *first_set, bool_t lr0)
{
		lalrConfigNode_t		*node;
		AR_ASSERT(start != NULL && grammar != NULL && set != NULL && first_set != NULL);
		AR_ASSERT(start->basis != NULL && start->all_config != NULL);

		for(node = start->all_config->head; node != NULL; node = node->next)
		{
				node->config->is_completed = false;
		}


		/*遍历状态(项集)start的每一个项*/
		for(node = start->all_config->head; node != NULL; node = node->next)
		{
				lalrState_t				*new_state;
				lalrConfigList_t		*goto_list;
				const psrSymb_t			*symb;
				const psrRule_t			*rule;
				lalrConfigNode_t		*inner_node;
				
				rule = Parser_GetRuleFromGrammar(grammar, node->config->rule_num);

				if(node->config->is_completed)
				{
						continue;
				}

				if(node->config->delim >= rule->body.count)/*项node->config没有goto了*/
				{
						continue;
				}

				/*A -> a. B c ;
				则此时 delim == 1,则body[delim] == B;则symb== B为下一个转移
				*/
				symb = rule->body.lst[node->config->delim]; 

				new_state = NULL;



				goto_list = Parser_CreateConfigList();/*资源分配点0，创建新list*/

				if(goto_list == NULL)/*失败，则返回，不用清理资源*/
				{
						return AR_E_NOMEM;
				}
				

				/*以下为求状态(项集)start的所有项在符号symb上的转移*/
				for(inner_node = start->all_config->head; inner_node != NULL; inner_node = inner_node->next)
				{
						const psrSymb_t			*bsp;
						lalrConfig_t			*new_config;
						const psrRule_t			*inner_rule;
						
						inner_rule = Parser_GetRuleFromGrammar(grammar, inner_node->config->rule_num);

						if(inner_node->config->is_completed)
						{
								continue;/*被计算过则不再计算*/
						}

						AR_ASSERT(inner_node->config->delim <= inner_rule->body.count);

						if(inner_node->config->delim == inner_rule->body.count)/*这条产生式没转移了*/
						{
								continue;
						}

						bsp = inner_rule->body.lst[inner_node->config->delim];
						
						if(Parser_CompSymb(symb, bsp) != 0)/*这条产生式在此symb下无转移*/
						{
								continue;
						}

						inner_node->config->is_completed = true;

						/*是否已存在于goto_list中中*/
						new_config = Parser_FindFromConfigList(goto_list, inner_node->config->rule_num, inner_node->config->delim + 1);

						if(new_config == NULL)
						{
								new_config = Parser_InsertToConfigListByValue(goto_list, inner_node->config->rule_num, inner_node->config->delim + 1, grammar);/*资源分配点1*/

								if(new_config == NULL)/*失败，则清理掉资源分配点0的goto_list资源，然后返回错误*/
								{
										Parser_DestroyConfigList(goto_list, true);
										goto_list = NULL;
										return AR_E_NOMEM;
								}

						}
						
						if(!lr0)
						{
								/*
										A  :   ( A ) | a
										   ;

										s0 :	[A'		: . A, $]				config0
												[A		: . ( A ), $]			
												[A		: . a, $]
										
										s1 :    [A'		: A . $ ]				//config 1

										s2 :	[A		:	( . A )		, $]	//config 2
												[A		: . ( A )		, )]
												[A		: . a			, )]

										s3 :	[A		:	a .			, $]	//config 3
										
										config0的$需要传递到config1
										
								*/

								/*
										记录从项inner_node->config 经过符号symb，转移到new_config,
								例如：s0 -> [A'		: . A, $] 经过符号A转移到  s1 :    [A'		: A . $ ] 

								*/
								

								if(Parser_InsertToConfigList(new_config->backward, inner_node->config) != AR_S_YES)/*资源分配点2，因为分配点1的资源归属于资源0， 因此如果此处失败，只需要清理分配点0*/
								{
										Parser_DestroyConfigList(goto_list, true);
										goto_list = NULL;
										return AR_E_NOMEM;
								}
						}
				}

				/*goto_list一定会在__build_state中被清理，且如果new_state!=NULL，则必定已被插入到set中*/
				new_state = __build_state(goto_list, grammar, set, first_set, lr0);

				if(new_state == NULL)
				{
						return AR_E_NOMEM;
				}
				
				if(Parser_InsertAction(start, new_state, symb, node->config) == NULL)
				{
						return AR_E_NOMEM;
				}
		}

		return AR_S_YES;
}




static arStatus_t __build_slr_actions(lalrStateSet_t *set, const psrGrammar_t *grammar, const psrSymbMap_t *follow_set)
{
		size_t i;
		
		
		AR_ASSERT(set != NULL && set->count > 0 && follow_set != NULL);

		
		for(i = 0; i < set->count; ++i)
		{
				lalrConfigNode_t *node;
				lalrState_t *state = set->set[i];

				for(node = state->all_config->head; node != NULL; node = node->next)
				{
						const psrRule_t *rule = Parser_GetRuleFromGrammar(grammar, node->config->rule_num);
						
						if(node->config->delim == rule->body.count)
						{
								size_t x;
								const psrSymbList_t *lst = &(Parser_GetSymbolFromSymbMap(follow_set, rule->head)->lst);

								for(x = 0; x < lst->count; ++x)
								{
										
										lalrAction_t *action = Parser_InsertAction(state, NULL, lst->lst[x], node->config);

										if(action == NULL)
										{
												return AR_E_NOMEM;
										}

										if(Parser_CompSymb(rule->head, PARSER_StartSymb) == 0)
										{
												action->act_type = LALR_ACT_ACCEPT;
										}
								}
						}
				}
		}

		return AR_S_YES;
}





lalrState_t*	Parser_Create_LR0_State(const psrGrammar_t *grammar)
{
		psrSymbMap_t			first_set, follow_set;
		lalrState_t				*start;
		lalrConfigList_t		*basis;
		lalrConfig_t			*first_cfg;
		lalrStateSet_t			set;
		int_t idx;
		AR_ASSERT(grammar != NULL);
		
		
		start = NULL;
		basis = NULL;
		first_cfg = NULL;

		Parser_InitSymbMap(&first_set);
		Parser_InitSymbMap(&follow_set);
		Parser_InitStateSet(&set);


		if(Parser_CalcFirstSet(grammar, &first_set) != AR_S_YES)
		{
				goto END_POINT;
		}

		if(Parser_CalcFollowSet(grammar, &follow_set, &first_set) != AR_S_YES)
		{
				goto END_POINT;
		}

		
		basis = Parser_CreateConfigList();

		if(basis == NULL)
		{
				goto END_POINT;
		}

		first_cfg = Parser_InsertToConfigListByValue(basis, 0, 0, grammar);

		if(first_cfg == NULL)
		{
				Parser_DestroyConfigList(basis, true);
				basis = NULL;
				goto END_POINT;
		}

		
		/*****************************设置初始化核心状态，S' : S $*******************************************/
		idx = Parser_GetTermSpecID(grammar,PARSER_EOISymb);
		AR_ASSERT(idx >= 0);

		if(Parser_SetBitInBitSet(&first_cfg->follow_set, (size_t)idx) != AR_S_YES)
		{
				Parser_DestroyConfigList(basis, true);
				basis = NULL;
				goto END_POINT;
		}
		/************************************************************************/


		start = __build_state(basis, grammar, &set, &first_set, true);
		if(start == NULL)
		{
				goto END_POINT;
		}

		if(__build_slr_actions(&set, grammar, &follow_set) != AR_S_YES)
		{
				start = NULL;/*如果__build_state结束，则可以确定state存在于set中*/
				goto END_POINT;
		}

END_POINT:
		
		if(start == NULL)
		{
				size_t i;
				for(i = 0; i < set.count; ++i)
				{
						Parser_DestroyState(set.set[i]);
						set.set[i] = NULL;
				}
		}

		Parser_UnInitStateSet(&set);


		Parser_UnInitSymbMap(&follow_set);
		Parser_UnInitSymbMap(&first_set);


		return start;
}







static arStatus_t __build_propagation_links(lalrStateSet_t *set)
{
		size_t i;
		bool_t changed;
		
		AR_ASSERT(set != NULL);

		
		
		for(i = 0; i < set->count; ++i)
		{
				lalrConfigNode_t *node;
				lalrState_t *state = set->set[i];

				for(node = state->all_config->head; node != NULL; node = node->next)
				{
						lalrConfigNode_t		*bp;
						lalrConfig_t			*config;
						config = node->config;
						for(bp = node->config->backward->head; bp != NULL; bp = bp->next)
						{
								arStatus_t tmp;
								lalrConfig_t			*other = bp->config;
								tmp = Parser_InsertToConfigList(other->forward, config);

								if(tmp != AR_S_YES)
								{
										return tmp;
								}
						}
				}
		}


		for(i = 0; i < set->count; ++i)
		{
				lalrConfigNode_t *node;
				lalrState_t *state = set->set[i];

				for(node = state->all_config->head; node != NULL; node = node->next)
				{
						node->config->is_completed = false;
				}
		}
		

		do{
				changed = false;

				for(i = 0; i < set->count; ++i)
				{
						lalrConfigNode_t *node;
						lalrState_t *state = set->set[i];

						for(node = state->all_config->head; node != NULL; node = node->next)
						{
								lalrConfigNode_t *fp;
								
								if(node->config->is_completed)continue;

								for(fp = node->config->forward->head; fp != NULL; fp = fp->next)
								{
										arStatus_t tmp;
										lalrConfig_t *next_config = fp->config;
										
										tmp = Parser_UnionBitSet(&next_config->follow_set, &node->config->follow_set);

										if(tmp == AR_S_YES)
										{
												changed = true;
												next_config->is_completed = false;

										}else if(tmp == AR_S_NO)/*无更新的传播，则不动*/
										{

										}else /*存储分配失败，则返回错误*/
										{
												return tmp;
										}
								}

								node->config->is_completed = true;
						}
				}
		}while(changed);

		return AR_S_YES;
}



static arStatus_t __build_actions(lalrStateSet_t *set, const psrGrammar_t *grammar)
{
		
		size_t i;
		const psrTermInfoList_t *term_lst;
		AR_ASSERT(set != NULL && set->count > 0);
		
		

		term_lst = Parser_GetTermList(grammar);

		for(i = 0; i < set->count; ++i)
		{
				lalrConfigNode_t *node;
				lalrState_t *state = set->set[i];

				for(node = state->all_config->head; node != NULL; node = node->next)
				{
						psrRule_t *rule = Parser_GetRuleFromGrammar(grammar, node->config->rule_num);
						/*
						node->config->delim == rule->body.count表明了此项为规约状态
						*/

						if(node->config->delim == rule->body.count)
						{
								size_t x;
								for(x = 0; x < node->config->follow_set.bit_cnt; ++x)
								{
										arStatus_t tmp;
										tmp = Parser_IsSetInBitSet(&node->config->follow_set, x);

										if(tmp == AR_S_YES)
										{
												lalrAction_t *action = Parser_InsertAction(state, NULL, term_lst->lst[x].term, node->config);

												if(action == NULL)/*存储分配失败*/
												{
														return AR_E_NOMEM;
												}

												if(Parser_CompSymb(rule->head, PARSER_StartSymb) == 0)
												{
															action->act_type = LALR_ACT_ACCEPT;
												}		
										}else if(tmp == AR_S_NO)
										{

										}else /*错误,malloc == NULL等*/
										{
												return tmp;
										}
								}
						}
				}
		}

		return AR_S_YES;
}


lalrState_t*	Parser_Create_LALR_State(const psrGrammar_t *grammar)
{

		psrSymbMap_t			first_set;
		lalrState_t				*start;
		lalrConfigList_t		*basis;
		lalrConfig_t			*first_cfg;
		lalrStateSet_t			set;
		int_t idx;
		AR_ASSERT(grammar != NULL);
		
		start = NULL;
		basis = NULL;
		first_cfg = NULL;

		Parser_InitSymbMap(&first_set);
		Parser_InitStateSet(&set);


		if(Parser_CalcFirstSet(grammar, &first_set) != AR_S_YES)
		{
				goto END_POINT;
		}
		

		basis = Parser_CreateConfigList();

		if(basis == NULL)
		{
				goto END_POINT;
		}

		first_cfg = Parser_InsertToConfigListByValue(basis, 0,  0, grammar);

		if(first_cfg == NULL)
		{
				Parser_DestroyConfigList(basis, true);
				basis = NULL;

				goto END_POINT;
		}
		

		idx = Parser_GetTermSpecID(grammar,PARSER_EOISymb);
		AR_ASSERT(idx >= 0);
		
		if(Parser_SetBitInBitSet(&first_cfg->follow_set, (size_t)idx) != AR_S_YES)
		{
				Parser_DestroyConfigList(basis, true);
				basis = NULL;
				goto END_POINT;
		}

		start = __build_state(basis, grammar, &set, &first_set, false);

		if(start == NULL)
		{
				start = NULL;
				goto END_POINT;
		}

		if(__build_propagation_links(&set) != AR_S_YES)
		{
				start = NULL;
				goto END_POINT;
		}

		if(__build_actions(&set, grammar) != AR_S_YES)
		{
				start = NULL;
				goto END_POINT;
		}

END_POINT:
		if(start == NULL)/*start == NULL的意思是前面失败了*/
		{
				size_t i;
				for(i = 0; i < set.count; ++i)
				{
						AR_ASSERT(set.set[i] != NULL);
						Parser_DestroyState(set.set[i]);
						set.set[i] = NULL;
				}
		}
		Parser_UnInitStateSet(&set);
		Parser_UnInitSymbMap(&first_set);
		

		return start;
}


AR_NAMESPACE_END
