
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
�˺��������ɵ�����heap�����ݶ������all_config�У���ˣ����ݴ��߼��£�����Ҫ�����κ���Դ
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
				�� body[delim] == B������ B -> . a b c;װ�뱾��
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
								/*����ÿһ���﷨*/

								if(Parser_CompSymb(symb, inner_rule->head) == 0)
								{
										/*
										�����ǰlhs��symb��ͬ���򽫵�ǰ�﷨���� B -> . a b c�����all_config
										*/
										size_t k;
										lalrConfig_t *new_config;

										new_config = Parser_FindFromConfigList(all_config, inner_rule_num, 0);

										if(new_config == NULL)
										{
												new_config = Parser_InsertToConfigListByValue(all_config, inner_rule_num, 0, grammar);/*��Դ�����0*/

												if(new_config == NULL)
												{
														return AR_E_NOMEM;
												}

										}

										AR_ASSERT(new_config != NULL);

										/*lr0ģʽ�������㴫�����Լ�follow set*/
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

										for(k = delim + 1; k < rule->body.count; ++k)/*���㴫����*/
										{
												const psrSymb_t *sp = rule->body.lst[k];
												AR_ASSERT(sp != NULL);

												if(sp->type == PARSER_TERM)
												{
														/*
														���spΪ�ս���������������new_config��follow_set�У�֮��ѭ����ֹ����Ϊ��
														�����﷨�����в�����sp֮����ս�����뵽new_config��
														*/
														int_t idx = Parser_GetTermSpecID(grammar, sp);
														AR_ASSERT(idx >= 0);

														status = Parser_SetBitInBitSet(&new_config->follow_set, (size_t)idx);/*��Դ�����1��new_config�洢��all_config��*/
														
														if(status  != AR_S_YES)
														{
																return status;
														}

														break;
												}else
												{
														/*
														���spΪ���ս��������first_set���뵽new_config�У�������ս���ɵ����մ���
														��ѭ������������ѭ����ֹ
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

																status = Parser_SetBitInBitSet(&new_config->follow_set, (size_t)idx);/*��Դ�����2,ͬ��1*/

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
										����node->configΪA -> a . B C D;
										��C D���ɵ����մ��� ����A��follow_set���ᴫ����������
										*/
										if(k == rule->body.count)
										{
												status = Parser_InsertToConfigList(node->config->forward, new_config);/*��Դ�����3,node��all_config�еĽڵ�*/

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
�˺����������µ�lalr״̬�����������lalrStateSet_t�����ݹ����__build_goto���������δ����set��state����Ҫ����
��Ϊstate������basis����˴˺������۳ɹ���񣬶���Ҫ����basis��������Դ���߹�����new_state
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
				�˺������Ѿ�������state_set�У���ֱ�ӽ�basis�е�backward�����������Ѵ��ڵ�״̬�ĺ��򴫲�����֮����������õ�basis
				*/
				if(!lr0)
				{
						lalrConfigNode_t *l, *r;
						/*���µĺ��������󴫲��ı�(��goto����) copy���Ѵ��ڵ�״̬�������*/
						for(l = basis->head, r = new_state->basis->head; l != NULL && r != NULL; l = l->next, r = r->next)
						{
								Parser_UnionConfigList(r->config->backward, l->config->backward);
						}
				}
				
				/*�������ú�����*/
				Parser_DestroyConfigList(basis, true);
				
				return new_state;
		}else
		{
				/*
				�����������״̬���У������Ҫ�½�״̬�������ϼ���goto �ݹ����
				*/

				lalrConfigList_t *all_config;

				all_config = Parser_CreateConfigList();/*��Դ�����0*/

				if(all_config == NULL)/*ʧ����ֻ�������basis��֮�󷵻ؿգ���״̬δ����*/
				{
						Parser_DestroyConfigList(basis, true);/*����basis�����ڲ�config*/
						return NULL;
				}

				if(Parser_CopyConfigList(all_config, basis) != AR_S_YES)/*��Դ�����1�����ʧ�ܣ�������all_config��basis*/
				{
						Parser_DestroyConfigList(all_config, false);/*����all_config*/
						all_config = NULL;
						Parser_DestroyConfigList(basis, true);/*����basis�����ڲ���������config*/
						basis = NULL;

						return NULL;
				}


				if(__calc_lr0_closure(all_config, grammar, first_set, lr0) != AR_S_YES)/*��Դ�����2������lr0�հ������ʧ�ܣ�������all_config��basis*/
				{
						Parser_DestroyConfigList(all_config, true);/*��ʱall_config�ض�����basis����config������������lr0�Ǻ�������Ҫ����all_config����������config*/
						all_config = NULL;
						
						Parser_DestroyConfigList(basis, false); 
						basis = NULL;

						return NULL;
				}

				Parser_SortConfigList(all_config);
				
				new_state = Parser_CreateState();/*��Դ�����3*/

				if(new_state == NULL)/*���ʧ�ܣ���״̬����δ����������ֻ��Ҫ����all_config��basis*/
				{
						Parser_DestroyConfigList(all_config, true);/*��ʱall_config�ض�����basis����config������������lr0�Ǻ�������Ҫ����all_config����������config*/
						all_config = NULL;
						
						Parser_DestroyConfigList(basis, false); 
						basis = NULL;

						return NULL;

				}


				new_state->basis = basis;
				new_state->all_config = all_config;

				if(Parser_InsertToStateSet(set, new_state) != AR_S_YES)/*��Դ�����4�����ʧ�ܣ�new_stateδ������״̬����set�У�����������״̬����Դ�Ϳ�����*/
				{
						Parser_DestroyState(new_state);
						new_state = NULL;
						return NULL;
				}

				
				/*build_gotoʧ�ܣ���������new_state����Ϊnew_state�Ѿ������뵽set��*/
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


		/*����״̬(�)start��ÿһ����*/
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

				if(node->config->delim >= rule->body.count)/*��node->configû��goto��*/
				{
						continue;
				}

				/*A -> a. B c ;
				���ʱ delim == 1,��body[delim] == B;��symb== BΪ��һ��ת��
				*/
				symb = rule->body.lst[node->config->delim]; 

				new_state = NULL;



				goto_list = Parser_CreateConfigList();/*��Դ�����0��������list*/

				if(goto_list == NULL)/*ʧ�ܣ��򷵻أ�����������Դ*/
				{
						return AR_E_NOMEM;
				}
				

				/*����Ϊ��״̬(�)start���������ڷ���symb�ϵ�ת��*/
				for(inner_node = start->all_config->head; inner_node != NULL; inner_node = inner_node->next)
				{
						const psrSymb_t			*bsp;
						lalrConfig_t			*new_config;
						const psrRule_t			*inner_rule;
						
						inner_rule = Parser_GetRuleFromGrammar(grammar, inner_node->config->rule_num);

						if(inner_node->config->is_completed)
						{
								continue;/*����������ټ���*/
						}

						AR_ASSERT(inner_node->config->delim <= inner_rule->body.count);

						if(inner_node->config->delim == inner_rule->body.count)/*��������ʽûת����*/
						{
								continue;
						}

						bsp = inner_rule->body.lst[inner_node->config->delim];
						
						if(Parser_CompSymb(symb, bsp) != 0)/*��������ʽ�ڴ�symb����ת��*/
						{
								continue;
						}

						inner_node->config->is_completed = true;

						/*�Ƿ��Ѵ�����goto_list����*/
						new_config = Parser_FindFromConfigList(goto_list, inner_node->config->rule_num, inner_node->config->delim + 1);

						if(new_config == NULL)
						{
								new_config = Parser_InsertToConfigListByValue(goto_list, inner_node->config->rule_num, inner_node->config->delim + 1, grammar);/*��Դ�����1*/

								if(new_config == NULL)/*ʧ�ܣ����������Դ�����0��goto_list��Դ��Ȼ�󷵻ش���*/
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
										
										config0��$��Ҫ���ݵ�config1
										
								*/

								/*
										��¼����inner_node->config ��������symb��ת�Ƶ�new_config,
								���磺s0 -> [A'		: . A, $] ��������Aת�Ƶ�  s1 :    [A'		: A . $ ] 

								*/
								

								if(Parser_InsertToConfigList(new_config->backward, inner_node->config) != AR_S_YES)/*��Դ�����2����Ϊ�����1����Դ��������Դ0�� �������˴�ʧ�ܣ�ֻ��Ҫ��������0*/
								{
										Parser_DestroyConfigList(goto_list, true);
										goto_list = NULL;
										return AR_E_NOMEM;
								}
						}
				}

				/*goto_listһ������__build_state�б����������new_state!=NULL����ض��ѱ����뵽set��*/
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

		
		/*****************************���ó�ʼ������״̬��S' : S $*******************************************/
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
				start = NULL;/*���__build_state�����������ȷ��state������set��*/
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

										}else if(tmp == AR_S_NO)/*�޸��µĴ������򲻶�*/
										{

										}else /*�洢����ʧ�ܣ��򷵻ش���*/
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
						node->config->delim == rule->body.count�����˴���Ϊ��Լ״̬
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

												if(action == NULL)/*�洢����ʧ��*/
												{
														return AR_E_NOMEM;
												}

												if(Parser_CompSymb(rule->head, PARSER_StartSymb) == 0)
												{
															action->act_type = LALR_ACT_ACCEPT;
												}		
										}else if(tmp == AR_S_NO)
										{

										}else /*����,malloc == NULL��*/
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
		if(start == NULL)/*start == NULL����˼��ǰ��ʧ����*/
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
