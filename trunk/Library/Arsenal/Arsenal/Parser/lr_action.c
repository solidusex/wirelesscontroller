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

#include "lalr.h"
#include "lr_action.h"


AR_NAMESPACE_BEGIN



/******************************************************************************aux*****************************/



const psrAction_t*		Parser_GetAction(const psrActionTable_t *tbl, size_t state, const psrSymb_t *symb)
{
		int_t idx;
		AR_ASSERT(state < tbl->row && symb->type == PARSER_TERM);
		idx = Parser_BSearchFromSymbList(&tbl->term_set,symb);
		AR_ASSERT(idx != -1);
		return tbl->actions[AR_TBL_IDX_R(state,idx, tbl->col)];
}


int_t					Parser_GetState(const psrActionTable_t *tbl, size_t state, const psrSymb_t *symb)
{
		int_t idx;
		AR_ASSERT(state < tbl->goto_row && symb->type == PARSER_NONTERM);
		idx = Parser_BSearchFromSymbList(&tbl->nonterm_set,symb);
		return tbl->goto_tbl[AR_TBL_IDX_R(state,idx, tbl->goto_col)];
}

const psrSymbList_t*	Parser_GetExpectedSymb(const psrActionTable_t *tbl, size_t state)
{
		AR_ASSERT(state < tbl->row);
		return &tbl->expected_set[state];
}


static psrActionTable_t* __create_table(const psrGrammar_t *gmr)
{
		psrActionTable_t *tbl;
		size_t i;
		
		const psrSymbList_t *symb_lst;
		AR_ASSERT(gmr != NULL && gmr->count > 1);

		tbl = AR_NEW0(psrActionTable_t);
		if(tbl == NULL)
		{
				goto INVALID_POINT;
		}


		symb_lst = Parser_GetSymbList(gmr);
		
		Parser_InitSymbList(&tbl->term_set);
		Parser_InitSymbList(&tbl->nonterm_set);

		for(i = 0; i < symb_lst->count; ++i)
		{
				const psrSymb_t *curr;
				curr = symb_lst->lst[i];

				if(curr->type == PARSER_TERM)
				{
						if(Parser_InsertToSymbList(&tbl->term_set, Parser_CopyNewSymb(curr)) != AR_S_YES)
						{
								goto INVALID_POINT;
						}
				}else
				{
						if(Parser_InsertToSymbList(&tbl->nonterm_set, Parser_CopyNewSymb(curr)) != AR_S_YES)
						{
								goto INVALID_POINT;
						}
				}
		}

		Parser_SortSymbList(&tbl->term_set);
		Parser_SortSymbList(&tbl->nonterm_set);
		return tbl;

INVALID_POINT:
		if(tbl != NULL)
		{
				Parser_UnInitSymbList(&tbl->term_set);
				Parser_UnInitSymbList(&tbl->nonterm_set);
				AR_DEL(tbl);
				tbl = NULL;
		}
		return NULL;
}




static arStatus_t __build_goto_table(psrActionTable_t *tbl, const lalrStateSet_t *set)
{
		size_t i,j;
		AR_ASSERT(tbl != NULL && tbl->goto_tbl == NULL && set != NULL && set->count > 0);

		tbl->goto_row = set->count;
		tbl->goto_col = tbl->nonterm_set.count;
		tbl->goto_tbl = AR_NEWARR(int_t, tbl->goto_row * tbl->goto_col);

		if(tbl->goto_tbl == NULL)
		{
				return AR_E_NOMEM;
		}

		AR_memset(tbl->goto_tbl, (int_t)-1, tbl->goto_row * tbl->goto_col * sizeof(int_t));
		

		for(i = 0; i < tbl->goto_row; ++i)
		{
				const lalrState_t *state;
				state = set->set[i];
				
				for(j = 0; j < state->count; ++j)
				{
						if(state->actions[j].symb->type == PARSER_NONTERM && state->actions[j].act_type == PARSER_SHIFT)
						{
								int_t idx;
								idx = Parser_BSearchFromSymbList(&tbl->nonterm_set, state->actions[j].symb);
								AR_ASSERT(idx != -1);
								tbl->goto_tbl[AR_TBL_IDX_R(i, idx, tbl->goto_col)] = Parser_IndexOfStateSet(set, state->actions[j].to);
						}
				}
		}

		return AR_S_YES;
}




static void __destroy_expected_list(psrActionTable_t *tbl)
{
		size_t i;
		AR_ASSERT(tbl != NULL && tbl->row > 0);
		
		if(tbl->expected_set)
		{
				for(i = 0; i < tbl->row; ++i)
				{
						Parser_UnInitSymbList(&tbl->expected_set[i]);
				}

				AR_DEL(tbl->expected_set);
				tbl->expected_set = NULL;
		}
}


/*�˺������ڽ�����Ϻ����*/

static arStatus_t __build_expected_list(psrActionTable_t *tbl)
{
		size_t i,j;
		AR_ASSERT(tbl != NULL && tbl->expected_set == NULL && tbl->row > 0);
		
		tbl->expected_set = AR_NEWARR0(psrSymbList_t, tbl->row);

		if(tbl->expected_set == NULL)
		{
				return AR_E_NOMEM;
		}

		for(i = 0; i < tbl->row; ++i)
		{
				Parser_InitSymbList(&tbl->expected_set[i]);
		}
		
		for(i = 0; i < tbl->row; ++i)
		{
				for(j = 0; j < tbl->term_set.count; ++j)
				{
						const psrAction_t	*act;
						const psrSymb_t *symb = tbl->term_set.lst[j];
						
						if(Parser_CompSymb(symb, PARSER_ErrorSymb) == 0 )
						{
								continue;
						}

						act = Parser_GetAction(tbl, i, symb);
						AR_ASSERT(act != NULL);
						
						if(act->type != PARSER_ERROR)
						{
								if(Parser_InsertToSymbList(&tbl->expected_set[i], symb) != AR_S_YES)
								{
										__destroy_expected_list(tbl);
										return AR_E_NOMEM;
								}
						}
				}
		}

		return AR_S_YES;
}



void					Parser_DestroyActionTable(const psrActionTable_t *table)
{
		size_t i;
		psrActionTable_t *tbl;
		AR_ASSERT(table != NULL);
		tbl = (psrActionTable_t*)table;

		__destroy_expected_list(tbl);

		for(i = 0; i < tbl->term_set.count; ++i)
		{
				Parser_DestroySymb(tbl->term_set.lst[i]);
		}
		
		for(i = 0; i < tbl->nonterm_set.count; ++i)
		{
				Parser_DestroySymb(tbl->nonterm_set.lst[i]);
		}

		Parser_UnInitSymbList(&tbl->nonterm_set);
		Parser_UnInitSymbList(&tbl->term_set);

		if(tbl->goto_tbl)
		{
				AR_DEL(tbl->goto_tbl);
				tbl->goto_tbl = NULL;
		}

		if(tbl->actions)
		{
				for(i = 0; i < tbl->row * tbl->col; ++i)
				{
						psrAction_t *action;

						action = tbl->actions[i];

						while(action != NULL && action->type != PARSER_ERROR)
						{
								psrAction_t *tmp;
								tmp = action->next;
								AR_DEL(action);
								action = tmp;
						}
				}

				AR_DEL(tbl->actions);
				tbl->actions = NULL;
				
		}

		AR_DEL(tbl);

}




static const psrAction_t error_action = 
{
		PARSER_ERROR,	/*type*/
		0,				/*rule_num*/
		0,				/*prec*/
		0,				/*delim*/

		0,				/*shift_to*/
		0,				/*reduce_count*/
		NULL			/*next*/		
};

const psrAction_t	* const PARSER_ErrorAction = &error_action;



/*
���︺����lookahead�Ͳ���ʽ�������ȼ�����������Լ��ͻ���⣬�����������ǣ����ȼ��ߵİ����ȼ��͵��滻����
������ȼ���ͬ����鿴lookahead����������ϣ��ҵ�ǰ�����������ӽ������ǹ�Լ���ô���������Լ��ͻ
���滻������Ϊ��Լ������ǰ�ǹ�Լ�������ӽ�����Ҳ�ǹ�Լ���õ�һ����Լ��Լ��ͻ���������ӽ����Ĳ��ǹ�Լ�
����������ӵģ��������ء�
lookaheadΪ�ҽ��ʱ����֮�෴�����lookahead�޽���ԣ���ͬ�����ǳ�ͻ��������롣
*/

static void __copy_action(psrAction_t *l, const psrAction_t *r)
{
		l->rule_num = r->rule_num;
		l->prec = r->prec;
		l->type = r->type;
		l->delim = r->delim;
		l->reduce_count = r->reduce_count;
		l->shift_to = r->shift_to;
}



static arStatus_t __insert_action_to_action_list(psrAction_t **dest, const psrAction_t *sour, const psrTermInfo_t *lookahead)
{
		psrAction_t *curr, *prev, *tmp;
		AR_ASSERT(dest != NULL && sour != NULL && lookahead != NULL);
		
		curr = *dest;
		prev = NULL;
		if(curr == NULL)
		{
				*dest = AR_NEW0(psrAction_t);

				if(*dest == NULL)
				{
						return AR_E_NOMEM;
				}

				__copy_action(*dest, sour);
				return AR_S_YES;
		}

		/*
				���ܴ���shift�������ﲻ�ǳ�ͻ�����ֱ�ӷ��أ���Ϊ��������ͬһ�����ϵ����뵼�²�ͬ��״̬ת������ǰ���DFA����������
		*/
		if(curr->type == PARSER_SHIFT && sour->type == PARSER_SHIFT)
		{
				return AR_S_YES;
		}

		if(curr->type == PARSER_ACCEPT)
		{
				tmp = AR_NEW0(psrAction_t);
				if(tmp == NULL)
				{
						return AR_E_NOMEM;
				}
				__copy_action(tmp, sour);
				tmp->next = curr->next;
				curr->next = tmp;
				return AR_S_YES;
		}
		
		
		if(sour->prec > curr->prec)
		{
				/*
						�¼�������ȼ�����ԭ��򲻱���Ϊ�ǳ�ͻ����˲��뵽ͷ��㣬curr����Ϊhead���
				*/
				__copy_action(curr, sour);
				return AR_S_YES;
				
		}else if(sour->prec < curr->prec)
		{
				/*
						�¼�������ȼ�����ԭ��򲻱���Ϊ�ǳ�ͻ���Ҳ����κ��޸ģ���������
				*/
				return AR_S_YES;
		}else
		{
				/*
						��ͬ���ȼ�������£�
				*/
				if(lookahead->assoc == PARSER_ASSOC_NONASSOC)
				{

						tmp = AR_NEW0(psrAction_t);
						if(tmp == NULL)
						{
								return AR_E_NOMEM;
						}
						
						__copy_action(tmp, sour);
						
						if(curr->type != PARSER_SHIFT)
						{
								/*�������shift�����µ�action����ǰ��*/
								tmp->next = *dest;
								*dest = tmp;
						}else
						{
								/*�����shift����ѡ��curr��ǰ*/
								tmp->next = curr->next;
								curr->next = tmp;
						}

				}else if(lookahead->assoc == PARSER_ASSOC_LEFT)
				{
						/*���ϣ����ȼ���ͬ������ѡ��Լ*/
						if(curr->type == PARSER_SHIFT && sour->type == PARSER_REDUCE)/*shift-reduce��ͻ��������*/
						{
								__copy_action(curr, sour);
						
						}else if(curr->type == PARSER_REDUCE && sour->type != PARSER_REDUCE)
						{
								/*���ϣ�ֻҪcurrΪ��Լ��sour���ǹ�Լ�򲻱䶯*/
								return AR_S_YES;
						}else/*��ͻ*/
						{
								/*��ط�һ���ǹ�Լ��Լ��ͻ*/
								AR_ASSERT(curr->type == PARSER_REDUCE && sour->type == PARSER_REDUCE);
								tmp = AR_NEW0(psrAction_t);

								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}

								__copy_action(tmp, sour);
								tmp->next = curr->next;
								curr->next = tmp;
						}
				}else if(lookahead->assoc == PARSER_ASSOC_RIGHT)
				{
						/*�ҽ�ϣ����ȼ���ͬ������ѡ����*/
						if(curr->type == PARSER_REDUCE && sour->type == PARSER_SHIFT)
						{
								__copy_action(curr, sour);
						}else if(curr->type == PARSER_SHIFT && sour->type != PARSER_SHIFT)
						{
								/*�ҽ�ϣ�ֻҪcurrΪ���룬sour���������򲻱䶫*/
								return AR_S_YES;
						}else/*��ͻ*/
						{
								/*��ط�һ���ǹ�Լ��Լ��ͻ*/
								AR_ASSERT(curr->type == PARSER_REDUCE && sour->type == PARSER_REDUCE);
								tmp = AR_NEW0(psrAction_t);
								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}

								__copy_action(tmp, sour);
								tmp->next = curr->next;
								curr->next = tmp;
						}
				}

				return AR_S_YES;
		}
}

/*********************************************************************************************************************************/



psrActionTable_t* __create_action_table(const psrGrammar_t *grammar, psrLRItemType_t type)
{
		psrActionTable_t		*tbl;
		lalrState_t				*start;
		lalrStateSet_t			set;
		size_t i;

		

		
		Parser_InitStateSet(&set);/*res_1*/

		if(type == PARSER_SLR)	/*res_2*/
		{
				start = Parser_Create_LR0_State(grammar);		
		}else
		{
				start = Parser_Create_LALR_State(grammar);
		}

		if(start == NULL)		/*res_2ʧ�ܣ�����res_1������*/
		{
				Parser_UnInitStateSet(&set);
				return NULL;
		}


		if(Parser_CollectState(&set, start) != AR_S_YES)/*ʧ�ܣ�����res_2,res_1,����*/
		{
				Parser_DestroyState_ALL(start);	
				Parser_UnInitStateSet(&set);
				return NULL;
		}


		tbl = __create_table(grammar);	/*res_3*/

		if(tbl == NULL)			/*res_3ʧ�ܣ�����res_2,res_1������*/
		{
				Parser_DestroyState_ALL(start);	
				Parser_UnInitStateSet(&set);
				return NULL;
		}

		if(__build_goto_table(tbl, &set) != AR_S_YES)
		{
				Parser_DestroyActionTable(tbl);
				tbl = NULL;
				Parser_DestroyState_ALL(start);	
				Parser_UnInitStateSet(&set);
				return NULL;
		}

		tbl->row = set.count;
		tbl->col = tbl->term_set.count;

		tbl->actions = AR_NEWARR0(psrAction_t*, tbl->row * tbl->col);

		if(tbl->actions == NULL)
		{
				Parser_DestroyActionTable(tbl);
				tbl = NULL;
				Parser_DestroyState_ALL(start);	
				Parser_UnInitStateSet(&set);
				return NULL;
		}


		for(i = 0; i < tbl->row; ++i)
		{
				size_t k;
				lalrState_t *state;
				state = set.set[i];
				
				for(k = 0; k <	state->count; ++k)
				{
						const lalrConfig_t *config;
						const psrSymb_t	  *body;
						const psrRule_t	  *rule;
						size_t			  rule_num;
						psrAction_t		  record;
						const lalrAction_t	  *action;
						
						const psrTermInfo_t		*term_info;
						action = &state->actions[k];

						config = action->config;
						
						/*rule = action->config->rule;
						rule_num = Parser_IndexOfGrammar(grammar, rule);
						*/
						rule_num = action->config->rule_num;
						rule = Parser_GetRuleFromGrammar(grammar, action->config->rule_num);

						body = Parser_IndexOfSymbList(&rule->body, config->delim);

						term_info = Parser_GetRulePrecAssocInfo(grammar, rule);
						
						
						AR_memset(&record, 0, sizeof(record));

						record.rule_num = rule_num;
						record.delim = config->delim;
						record.prec = term_info->prec;
						record.reduce_count = 0;
						record.shift_to = 0;
						record.next = NULL;


						if(action->act_type == LALR_ACT_REDUCE || action->act_type == LALR_ACT_ACCEPT)
						{
								int_t idx;
								AR_ASSERT(body == NULL && action->to == NULL);
								

								record.reduce_count = rule->body.count;
								record.type = action->act_type == LALR_ACT_REDUCE ? PARSER_REDUCE : PARSER_ACCEPT;
								
								idx = Parser_FindFromSymbList(&tbl->term_set, action->symb);
								AR_ASSERT(idx != -1);

								if(__insert_action_to_action_list(&tbl->actions[AR_TBL_IDX_R(i,idx, tbl->col)], &record, Parser_GetTermSymbInfo(grammar,action->symb)) != AR_S_YES)
								{

										Parser_DestroyActionTable(tbl);
										tbl = NULL;
										Parser_DestroyState_ALL(start);	
										Parser_UnInitStateSet(&set);
										return NULL;
								}


						}else if(action->act_type == LALR_ACT_SHIFT && action->symb->type == PARSER_TERM)
						{
								int_t trans_to_idx,idx;
								
								AR_ASSERT(action->config != NULL && action->to != NULL && action->symb != NULL);
								
								AR_ASSERT(Parser_CompSymb(body, action->symb) == 0);

								record.type = PARSER_SHIFT;


								trans_to_idx = Parser_IndexOfStateSet(&set, action->to);
								AR_ASSERT(trans_to_idx != -1);
								record.shift_to = (size_t)trans_to_idx;
								idx = Parser_FindFromSymbList(&tbl->term_set, action->symb);
								
								if(__insert_action_to_action_list(&tbl->actions[AR_TBL_IDX_R(i,idx, tbl->col)], &record, Parser_GetTermSymbInfo(grammar,action->symb)) != AR_S_YES)
								{
										Parser_DestroyActionTable(tbl);
										tbl = NULL;
										Parser_DestroyState_ALL(start);	
										Parser_UnInitStateSet(&set);
										return NULL;
								}
								
						}

				}
		}

		
		Parser_DestroyState_ALL(start);
		Parser_UnInitStateSet(&set);
		start = NULL;

		/************************************************************/
		for(i = 0; i < tbl->row * tbl->col; ++i)
		{
				if(tbl->actions[i] == NULL)
				{
						tbl->actions[i] = (psrAction_t*)PARSER_ErrorAction;
				}
		}

		if(__build_expected_list(tbl) != AR_S_YES)
		{
				Parser_DestroyActionTable(tbl);
				tbl = NULL;
				return NULL;
		}

		return tbl;

}

const psrActionTable_t* Parser_CreateActionTable_SLR(const psrGrammar_t *grammar)
{
		return __create_action_table(grammar, PARSER_SLR);
}


const psrActionTable_t* Parser_CreateActionTable_LALR(const psrGrammar_t *grammar)
{
		return __create_action_table(grammar, PARSER_LALR);
}


/********************************************************************************************************************************************/




AR_NAMESPACE_END

