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
#include "parser.h"
#include "parser_in.h"



AR_NAMESPACE_BEGIN


		


#define __CHECK_RET_VAL(_call_stmt)						\
		do{												\
				arStatus_t status = _call_stmt;			\
				if(status != AR_S_YES)					\
				{										\
						return status;					\
				}										\
		}while(0)

static arStatus_t Parser_PrintActionTable(const psrActionTable_t *tbl, const psrGrammar_t *grammar, size_t width, arString_t *str)
{
		/*这里必须用int，因为printf一族函数的对于%*d这类width的定义就是int*/
		int __WIDTH__;
		size_t i,j;
		wchar_t buf[1024];

		__WIDTH__ = (int)width;
		
		__CHECK_RET_VAL(AR_AppendString(str,L"TermSet:\r\n"));

		for(i = 0; i < tbl->term_set.count; ++i)
		{
				__CHECK_RET_VAL(Parser_PrintSymbol(tbl->term_set.lst[i],str));
				__CHECK_RET_VAL(AR_AppendString(str,L"  "));
		}

		__CHECK_RET_VAL(AR_AppendString(str,L"\r\n"));
		__CHECK_RET_VAL(AR_AppendString(str, L"-----------------------------------------\r\n"));
		__CHECK_RET_VAL(AR_AppendString(str,L"NonTermSet:\r\n"));

		for(i = 0; i < tbl->nonterm_set.count; ++i)
		{
				__CHECK_RET_VAL(Parser_PrintSymbol(tbl->nonterm_set.lst[i],str));
				__CHECK_RET_VAL(AR_AppendString(str,L"  "));
		}

		__CHECK_RET_VAL(AR_AppendString(str,L"\r\n"));
		__CHECK_RET_VAL(AR_AppendString(str,L"-----------------------------------------\r\n"));

		
		__CHECK_RET_VAL(AR_AppendString(str,L"Goto Table:\r\n"));
		
		__CHECK_RET_VAL(AR_AppendFormatString(str, L"%*ls", __WIDTH__,L"NULL"));

		for(i = 0; i < tbl->nonterm_set.count; ++i)
		{
				AR_swprintf(buf, 1024, L"<%ls>", tbl->nonterm_set.lst[i]->name);
				__CHECK_RET_VAL(AR_AppendFormatString(str, L"%*ls",__WIDTH__, buf));
		}


		__CHECK_RET_VAL(AR_AppendString(str,L"\r\n"));
		__CHECK_RET_VAL(AR_AppendString(str,L"\r\n"));

		for(i = 0; i < tbl->goto_row; i++)
		{
				AR_swprintf(buf, 1024, L"I[%Id]", (size_t)i);

				__CHECK_RET_VAL(AR_AppendFormatString(str, L"%*ls:", __WIDTH__,buf));

				for(j = 0; j < tbl->goto_col; ++j)
				{
						__CHECK_RET_VAL(AR_AppendFormatString(str, L"%*Id", __WIDTH__, tbl->goto_tbl[AR_TBL_IDX_R(i,j,tbl->goto_col)]));
				}

				__CHECK_RET_VAL(AR_AppendString(str,L"\r\n"));
		}

		__CHECK_RET_VAL(AR_AppendString(str,L"-----------------------------------------\r\n"));

		__CHECK_RET_VAL(AR_AppendString(str,L"Action Table:\r\n"));
		
		__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*ls", __WIDTH__,L"NULL"));

		for(i = 0; i < tbl->term_set.count; ++i)
		{
				__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*ls",__WIDTH__, tbl->term_set.lst[i]->name));
		}
		
		__CHECK_RET_VAL(AR_AppendFormatString(str,L"\r\n"));
		__CHECK_RET_VAL(AR_AppendFormatString(str,L"\r\n"));


		for(i = 0; i < tbl->row; ++i)
		{
				AR_swprintf(buf, 1024, L"I[%Id]", i);

				__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*ls:", __WIDTH__,buf));

				for(j = 0; j < tbl->col; ++j)
				{
						const psrAction_t *pact;
						const psrRule_t	 *rule;
						pact = tbl->actions[AR_TBL_IDX_R(i,j, tbl->col)];
						rule = Parser_GetRuleFromGrammar(grammar, pact->rule_num);

						switch(pact->type)
						{
						case PARSER_ACCEPT:
								__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*ls", __WIDTH__,L"accept"));
								break;
						case PARSER_SHIFT:
						{
								__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*Id", __WIDTH__, (size_t)pact->shift_to));
						}
								break;
						case PARSER_REDUCE:
						{
								AR_swprintf(buf, 1024, L"[<%ls>:%Id]",rule->head->name, (size_t)pact->reduce_count);
								__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*ls", __WIDTH__,buf));
								
						}
								break;
						default:
								__CHECK_RET_VAL(AR_AppendFormatString(str,L"%*ls", __WIDTH__,L"error"));
								break;
						}
				}
				__CHECK_RET_VAL(AR_AppendFormatString(str,L"\r\n"));
		}
		__CHECK_RET_VAL(AR_AppendFormatString(str,L"-----------------------------------------\r\n"));

		return AR_S_YES;
}



static arStatus_t Parser_ReportConflict(const psrActionTable_t *tbl, const psrGrammar_t *grammar, arString_t *str)
{
		size_t i,j;
		const psrAction_t *action;
		const psrRule_t	 *rule;

		__CHECK_RET_VAL(AR_AppendFormatString(str,L"%ls\r\n", L"Conflict:"));

		for(i = 0; i < tbl->row; ++i)
		{
				for(j = 0; j < tbl->col; ++j)
				{
						action = tbl->actions[AR_TBL_IDX_R(i,j,tbl->col)];
						rule = Parser_GetRuleFromGrammar(grammar, action->rule_num);
						AR_ASSERT(action != NULL);
						if(action->next == NULL)
						{
								continue;
						}


						__CHECK_RET_VAL(AR_AppendFormatString(str,L"state[%Id] : %ls\r\n",(size_t)i, tbl->term_set.lst[j]->name));
						
						while(action != NULL)
						{
								
								lalrConfig_t	tmp;

								__CHECK_RET_VAL(Parser_InitConfig(&tmp, action->rule_num, action->delim, grammar));
								
								switch(action->type)
								{
								case PARSER_REDUCE:
										if(AR_AppendFormatString(str,L"Reduce: ") != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												return AR_E_NOMEM;
										}
										if(Parser_PrintConfig(&tmp, grammar, str) != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												return AR_E_NOMEM;
										}
										break;
								case PARSER_SHIFT:
										if(AR_AppendFormatString(str,L"Shift: ") != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												return AR_E_NOMEM;
										}

										if(Parser_PrintConfig(&tmp, grammar,str) != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												return AR_E_NOMEM;
										}
										break;
								case PARSER_ACCEPT:
										if(AR_AppendFormatString(str,L"Accept ") != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												return AR_E_NOMEM;
										}
										break;
								default:
										AR_ASSERT(false);
								}
								
								Parser_UnInitConfig(&tmp);

								__CHECK_RET_VAL(AR_AppendFormatString(str,L"\r\n"));
								action = action->next;
								
						}

						__CHECK_RET_VAL(AR_AppendFormatString(str,L"\r\n"));
						__CHECK_RET_VAL(AR_AppendFormatString(str,L"-----------------------------------------------\r\n"));
				}
		}

		return AR_S_YES;
}



static arStatus_t __insert_to_conflict_set(psrConflictView_t *view, psrConflictItem_t *item)
{
		AR_ASSERT(view != NULL && item != NULL);

		if(view->count == view->cap)
		{
				size_t					new_cap;
				psrConflictItem_t		**new_conflict;

				new_cap = (view->cap + 4)*2;
				new_conflict = AR_NEWARR(psrConflictItem_t*, new_cap);

				if(new_conflict == NULL)
				{
						return AR_E_NOMEM;
				}

				if(view->count > 0)
				{
						AR_memcpy(new_conflict, view->conflict, view->count * sizeof(psrConflictItem_t*));
				}

				if(view->conflict)
				{
						
						AR_DEL(view->conflict);
						view->conflict = NULL;
				}

				view->conflict = new_conflict;
				view->cap = new_cap;
		}

		view->conflict[view->count++] = item;

		return AR_S_YES;
}


static void							Parser_DestroyConflictView(const psrConflictView_t *view);

static void __destroy_psrConflictItem_t(psrConflictItem_t *item)
{
		size_t i;

		if(item)
		{
				if(item->name)
				{
						AR_DEL(item->name);
						item->name = NULL;
				}

				if(item->lookahead)
				{
						AR_DEL(item->lookahead);
						item->lookahead = NULL;
				}

				for(i = 0; i < item->count; ++i)
				{
						if(item->items[i])
						{
								AR_DEL(item->items[i]);
						}
				}

				if(item->items)
				{
						AR_DEL(item->items);
						item->items = NULL;
				}

				AR_DEL(item);
		}
}


static const	psrConflictView_t*		Parser_CreateConflictView(const psrActionTable_t *tbl, const psrGrammar_t *grammar)
{
		psrConflictView_t		*view;
		arString_t				*str = NULL;
		size_t i,k;
		AR_ASSERT(tbl != NULL && grammar != NULL);

		str = NULL;
		view = NULL;
	
		str = AR_CreateString();

		if(str == NULL)
		{
				goto INVALID_POINT;
		}

		view = AR_NEW0(psrConflictView_t);
		
		if(view == NULL)
		{
				goto INVALID_POINT;
		}
		
		
		for(i = 0; i < tbl->row; ++i)
		{
				size_t					l = 0;
				psrConflictItem_t		*item = NULL;

				for(k = 0; k < tbl->col; ++k)
				{
						
						size_t cnt;
						const psrAction_t		*act = tbl->actions[AR_TBL_IDX_R(i,k,tbl->col)];
						/*
						const psrRule_t			*rule = Parser_GetRuleFromGrammar(grammar, act->rule_num);
						*/
						
						if(act->next == NULL)
						{
								continue;
						}
						
						AR_ClearString(str);
						item = AR_NEW0(psrConflictItem_t);
						
						if(item == NULL)
						{
								goto INVALID_POINT;
						}
						

						/*
						AR_AppendFormatString(str,L"state[%" AR_PLAT_INT_FMT L"d] : %ls",(size_t)i, tbl->term_set.lst[k]->name);
						*/

						if(AR_AppendFormatString(str,L"state[%Id]",(size_t)i) != AR_S_YES)
						{
								__destroy_psrConflictItem_t(item);
								goto INVALID_POINT;
						}

						item->name = AR_wcsdup(AR_GetStringCString(str));

						if(item->name == NULL)
						{
								__destroy_psrConflictItem_t(item);
								goto INVALID_POINT;
						}

						AR_ClearString(str);

						item->lookahead = AR_wcsdup(tbl->term_set.lst[k]->name);

						if(item->lookahead == NULL)
						{
								__destroy_psrConflictItem_t(item);
								goto INVALID_POINT;
						}

						cnt = 0;
						while(act != NULL)
						{
								cnt++;
								act = act->next;
						}


						item->items = AR_NEWARR0(wchar_t*, cnt);
						if(item->items == NULL)
						{
								__destroy_psrConflictItem_t(item);
								goto INVALID_POINT;
						}
						
						
						for(l = 0, act = tbl->actions[AR_TBL_IDX_R(i,k,tbl->col)]; l < cnt; ++l, act = act->next)
						{
								lalrConfig_t	tmp;
								
								AR_ASSERT(act != NULL);
								
								if(Parser_InitConfig(&tmp, act->rule_num, act->delim, grammar) != AR_S_YES)
								{
										__destroy_psrConflictItem_t(item);
										goto INVALID_POINT;
								}
								

								AR_ClearString(str);

								switch(act->type)
								{
								case PARSER_REDUCE:
										if(AR_AppendFormatString(str,L"Reduce: ") != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												__destroy_psrConflictItem_t(item);
												goto INVALID_POINT;
										}

										if(Parser_PrintConfig(&tmp,grammar,str) != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												__destroy_psrConflictItem_t(item);
												goto INVALID_POINT;
										}

										break;
								case PARSER_SHIFT:
										if(AR_AppendFormatString(str,L"Shift: ") != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												__destroy_psrConflictItem_t(item);
												goto INVALID_POINT;
										}

										if(Parser_PrintConfig(&tmp, grammar,str) != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												__destroy_psrConflictItem_t(item);
												goto INVALID_POINT;
										}

										break;
								case PARSER_ACCEPT:
										if(	AR_AppendFormatString(str,L"Accept ") != AR_S_YES)
										{
												Parser_UnInitConfig(&tmp);
												__destroy_psrConflictItem_t(item);
												goto INVALID_POINT;
										}
										break;
								default:
										AR_ASSERT(false);
								}
								
								Parser_UnInitConfig(&tmp);
								
								item->items[l] = AR_wcsdup(AR_GetStringCString(str));

								if(item->items[l] == NULL)
								{
										__destroy_psrConflictItem_t(item);
										goto INVALID_POINT;
								}
								item->count++;

						}
						
						if(__insert_to_conflict_set(view, item) != AR_S_YES)
						{
								__destroy_psrConflictItem_t(item);
								goto INVALID_POINT;
						}
				}
		}

		AR_DestroyString(str);
		return view;

INVALID_POINT:
		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

		if(view)
		{
				Parser_DestroyConflictView(view);
				view = NULL;
		}

		return NULL;

}


static void							Parser_DestroyConflictView(const psrConflictView_t *view)
{
		
		psrConflictView_t		*v = (psrConflictView_t*)view;

		if(v != NULL)
		{
				size_t i;
				for(i = 0; i < view->count; ++i)
				{
						psrConflictItem_t		*item = view->conflict[i];
						
						if(item != NULL)
						{
								__destroy_psrConflictItem_t(item);
								item = NULL;
						}
				}

				if(v->conflict)
				{
						AR_DEL(v->conflict);
						v->conflict = NULL;
				}

				if(v)
				{
						AR_DEL(v);
						v = NULL;
				}
		}

}







static void Parser_DestroyActionView(const psrActionView_t *action_view);


static const psrActionView_t*	Parser_CreateActionView(const psrActionTable_t *tbl, const psrGrammar_t *grammar)
{
		psrActionView_t		*view;
		size_t r, c, k;
		wchar_t *msg;
		AR_ASSERT(tbl != NULL && grammar != NULL);

		view = AR_NEW0(psrActionView_t);
		
		if(view == NULL)
		{
				goto INVALID_POINT;
		}
		

		view->item_cnt = tbl->term_set.count + tbl->nonterm_set.count;

		view->item = AR_NEWARR0(wchar_t*, view->item_cnt);

		if(view->item == NULL)
		{
				goto INVALID_POINT;
		}
		
		c = 0;
		for(k = 0; k < tbl->term_set.count; ++k)
		{
				view->item[c] = AR_vtow(L"%ls", tbl->term_set.lst[k]->name);

				if(view->item[c] == NULL)
				{
						goto INVALID_POINT;
				}
				c++;
		}

		for(k = 0; k < tbl->nonterm_set.count; ++k)
		{
				view->item[c] = AR_vtow(L"<%ls>", tbl->nonterm_set.lst[k]->name);

				if(view->item[c] == NULL)
				{
						goto INVALID_POINT;
				}

				c++;
		}

		AR_ASSERT(c == view->item_cnt);
		

		view->row = tbl->row;
		view->col = tbl->col + tbl->goto_col;

		AR_ASSERT(view->col == view->item_cnt);

		view->action_tbl = AR_NEWARR0(wchar_t*, view->row * view->col);

		if(view->action_tbl == NULL)
		{
				goto INVALID_POINT;
		}
		
		/*construct action view*/

		for(r = 0; r < tbl->row; ++r)
		{
				c = 0;
				msg = NULL;
				for(k = 0; k < tbl->col; ++k)
				{
						
						const psrAction_t *action = tbl->actions[AR_TBL_IDX_R(r, k, tbl->col)];
						const psrRule_t	 *rule = Parser_GetRuleFromGrammar(grammar, action->rule_num);
						

						switch(action->type)
						{
						case PARSER_ACCEPT:
								msg = AR_wcsdup(L"accept");
								break;
						case PARSER_SHIFT:
								{
										msg = AR_vtow(L"%Id", (size_t)action->shift_to);
								}
								break;
						case PARSER_REDUCE:
								{
										msg = AR_vtow(L"[<%ls>:%Id]", rule->head->name, (size_t)action->reduce_count);
								}
								break;
						default:
								msg = AR_vtow(L"error");
								break;
						}

						if(msg == NULL)
						{
								goto INVALID_POINT;
						}
						
						view->action_tbl[AR_TBL_IDX_R(r, c, view->col)] = msg;
						c++;
						msg = NULL;
				}

				for(k = 0; k < tbl->goto_col; ++k)
				{
						int_t state =  tbl->goto_tbl[AR_TBL_IDX_R(r, k, tbl->goto_col)];
						msg = AR_vtow(L"%Id", state);

						if(msg == NULL)
						{
								goto INVALID_POINT;
						}

						view->action_tbl[AR_TBL_IDX_R(r, c, view->col)] = msg;
						c++;
						msg = NULL;
				}
				AR_ASSERT(c == view->col);
		}

		AR_ASSERT(r == view->row);
		return view;

INVALID_POINT:
		if(view)
		{
				Parser_DestroyActionView(view);
				view = NULL;
		}

		return NULL;
}


static void Parser_DestroyActionView(const psrActionView_t *action_view)
{
		size_t i;
		psrActionView_t *view;
		AR_ASSERT(action_view != NULL);

		view = (psrActionView_t*)action_view;

		for(i = 0; i < view->item_cnt; ++i)
		{
				if(view->item[i])
				{
						AR_DEL(view->item[i]);
						view->item[i] = NULL;
				}
		}

		for(i = 0; i < view->row * view->col; ++i)
		{
				if(view->action_tbl[i])
				{
						AR_DEL(view->action_tbl[i]);
						view->action_tbl[i] = NULL;
				}
		}
		
		if(view->action_tbl)
		{
				AR_DEL(view->action_tbl);
				view->action_tbl = NULL;
		}

		if(view->item)
		{
				AR_DEL(view->item);
				view->item = NULL;
		}
		AR_DEL(view);
}





static size_t Parser_CountConflict(const psrActionTable_t *tbl)
{
		
		size_t i, j, count;
		const psrAction_t *action;

		AR_ASSERT(tbl != NULL);
		count = 0;
		for(i = 0; i < tbl->row; ++i)
		{
				for(j = 0; j < tbl->col; ++j)
				{
						action = tbl->actions[AR_TBL_IDX_R(i,j,tbl->col)];
						AR_ASSERT(action != NULL);
						if(action->next != NULL)
						{
								count++;
						}
				}
		}
		return  count;
}


/**********************************************************************/


/************************Report*********************************/


size_t	Parser_CountParserConflict(const parser_t *parser)
{
		AR_ASSERT(parser != NULL);
		AR_ASSERT(parser->tbl != NULL && parser->grammar != NULL);

		return Parser_CountConflict(parser->tbl);
}

arStatus_t	Parser_PrintParserConflict(const parser_t *parser, arString_t *out)
{
		AR_ASSERT(parser != NULL && out != NULL);
		AR_ASSERT(parser->tbl != NULL && parser->grammar != NULL);
		
		return Parser_ReportConflict(parser->tbl, parser->grammar, out);
}

arStatus_t	Parser_PrintParserActionTable(const parser_t *parser, arString_t *out, size_t width)
{
		AR_ASSERT(parser != NULL && out != NULL);
		AR_ASSERT(parser->tbl != NULL && parser->grammar != NULL);

		return Parser_PrintActionTable(parser->tbl, parser->grammar, width, out);
}



const psrActionView_t* Parser_CreateParserActionView(const parser_t *parser)
{
		AR_ASSERT(parser != NULL);
		return Parser_CreateActionView(parser->tbl, parser->grammar);

}

void					Parser_DestroyParserActionView(const psrActionView_t *view)
{
		AR_ASSERT(view != NULL);
		Parser_DestroyActionView(view);

}



const	psrConflictView_t*		Parser_CreateParserConflictView(const parser_t *parser)
{
		AR_ASSERT(parser != NULL);

		return Parser_CreateConflictView(parser->tbl, parser->grammar);
}


void							Parser_DestroyParserConflictView(const psrConflictView_t *view)
{
		AR_ASSERT(view != NULL);

		Parser_DestroyConflictView(view);
}





/*
typedef struct __sym_tbl_view_tag
{
		wchar_t	**name;
		wchar_t	**name_set;
		size_t	count;
		size_t	cap;
}psrSymbolMapView_t;

typedef struct __first_follow_view_tag
{
		psrSymbolMapView_t		first_set;
		psrSymbolMapView_t		follow_set;
}psrStatusView_t;
*/

arStatus_t __insert_to_symtbl_view(psrSymbolMapView_t *map_view, const wchar_t *name, const wchar_t *set)
{
		AR_ASSERT(map_view != NULL && name != NULL && set != NULL);

		if(map_view->count == map_view->cap)
		{
				size_t new_cap;
				wchar_t **new_name;
				wchar_t **new_name_set;

				new_cap = (map_view->cap + 4) * 2;

				new_name = AR_NEWARR0(wchar_t*, new_cap);
				new_name_set = AR_NEWARR0(wchar_t*, new_cap);

				if(new_name == NULL || new_name_set == NULL)
				{
						if(new_name)
						{
								AR_DEL(new_name);
								new_name = NULL;
						}

						if(new_name_set)
						{
								AR_DEL(new_name_set);
								new_name_set = NULL;
						}

						return AR_E_NOMEM;
				}

				if(map_view->count > 0)
				{
						AR_memcpy(new_name, map_view->name, map_view->count * sizeof(wchar_t*));
						AR_memcpy(new_name_set, map_view->name_set, map_view->count * sizeof(wchar_t*));

				}

				AR_DEL(map_view->name);
				map_view->name = NULL;
				AR_DEL(map_view->name_set);
				map_view->name_set = NULL;

				map_view->cap = new_cap;
				map_view->name = new_name;
				map_view->name_set = new_name_set;
		}

		map_view->name[map_view->count]		= AR_wcsdup(name);
		map_view->name_set[map_view->count] = AR_wcsdup(set);
		map_view->count++;
		return AR_S_YES;
}




static arStatus_t __detect_left_recursion(const psrGrammar_t *grammar, const psrSymb_t *head, psrSymbList_t *lst, psrSymbolMapView_t *output)
{
		size_t i;
		arStatus_t is_recu = AR_S_NO;
		AR_ASSERT(grammar != NULL && head != NULL && lst != NULL);

		/*AR_ASSERT(lst->count > 0);*/

		AR_ASSERT(Parser_FindFromSymbList(lst, head) == -1);
		
		if(Parser_InsertToSymbList(lst, head) != AR_S_YES)
		{
				return AR_E_NOMEM;
		}
		
		
		
		for(i = 0; i < grammar->count; ++i)
		{
				const psrRule_t *rule;
				rule = grammar->rules[i];
				
				if(Parser_CompSymb(rule->head, head) == 0)
				{
						const psrSymb_t *symb;

						size_t x = 0;

						
						if(x < rule->body.count && rule->body.lst[x]->type == PARSER_NONTERM)
						{
								symb = rule->body.lst[x];

								if(Parser_CompSymb(lst->lst[0], symb) == 0)
								{
										is_recu = AR_S_YES;
										if(output)
										{
												size_t cnt;
												
												arString_t *str = AR_CreateString();

												for(cnt = 0; cnt < lst->count; ++cnt)
												{
														if(AR_AppendFormatString(str, L"<%ls> -> ", lst->lst[cnt]->name) != AR_S_YES)
														{
																return AR_E_NOMEM;
														}
												}

												if(AR_AppendFormatString(str, L"<%ls> ", lst->lst[0]->name) != AR_S_YES)
												{
														return AR_E_NOMEM;
												}
												
												if(__insert_to_symtbl_view(output, L"Path:", AR_GetStringCString(str)) != AR_S_YES)
												{
														return AR_E_NOMEM;
												}

												AR_DestroyString(str);
												str = NULL;
										}

								}else if(Parser_FindFromSymbList(lst, symb) != -1)
								{
										continue;
								}else
								{
										arStatus_t tmp;
										tmp = __detect_left_recursion(grammar, symb, lst,output);

										if(tmp == AR_E_NOMEM)
										{
												return AR_E_NOMEM;
										}
								}
						}
				}
		}
		
		Parser_RemoveFromSymbListByIndex(lst, lst->count-1);
		return is_recu;
		
}



arStatus_t					__report_left_recursion(const psrGrammar_t *grammar, psrSymbolMapView_t *output)
{
		size_t i;
		psrSymbList_t	lst;
		const psrSymbList_t		*symblist;
		arStatus_t			ret = AR_S_NO;
		AR_ASSERT(grammar != NULL);
		
		Parser_InitSymbList(&lst);

		symblist = Parser_GetSymbList(grammar);
		
		for(i = 0; i < symblist->count; ++i)
		{
				const psrSymb_t *symb;
				
				symb = symblist->lst[i];

				Parser_ClearSymbList(&lst);
				
				if(symb->type == PARSER_NONTERM)
				{
						arStatus_t tmp = __detect_left_recursion(grammar, symb, &lst,output);
						if(tmp == AR_S_YES)
						{
								ret = AR_S_YES;
						}else if(tmp == AR_S_NO)
						{
						}else
						{
								ret = tmp;
								goto END_POINT;
						}
				}
		}

END_POINT:
		Parser_UnInitSymbList(&lst);
		return ret;
}





/************************************************************************************************************/




static size_t __calc_leftfactor(const psrRule_t *l, const psrRule_t *r)
{
		size_t cnt = 0;
		AR_ASSERT(l != NULL && r != NULL);

		while(cnt < l->body.count && cnt < r->body.count && Parser_CompSymb(l->body.lst[cnt], r->body.lst[cnt]) == 0)
		{
				cnt++;
		}
		return cnt;
}



static arStatus_t	__report_rule_left_factor(const psrSymb_t *lhs, const psrRule_t **rules, size_t n, psrSymbolMapView_t *output)
{
		size_t i,k;
		size_t	*bk;
		size_t			max,cnt;
		arStatus_t		has_left_factor;
		arString_t		*tmp;
		AR_ASSERT(lhs != NULL && rules != NULL);

		if(n < 2)
		{
				return AR_S_NO;
		}

		has_left_factor = AR_S_NO;

		tmp = AR_CreateString();
		bk = AR_NEWARR0(size_t, n);

		if(tmp == NULL || bk == NULL)
		{
				has_left_factor = AR_E_NOMEM;
				goto RETURN_POINT;
		}

RECHECK_POINT:
		
		max = 0;
		cnt = 0;

		for(i = 0; i < n; ++i)
		{
				if(rules[i] == NULL)
				{
						continue;
				}

				AR_ASSERT(Parser_CompSymb(lhs, rules[i]->head) == 0);

				for(k = 0; k < n; ++k)
				{
						if(rules[k] == NULL)continue;

						if(k != i)
						{
								size_t x = __calc_leftfactor(rules[i], rules[k]);
								
								if(x > max)
								{
										max = x;
										AR_memset(bk, 0, sizeof(size_t)*n);
										cnt = 0;
										bk[cnt++] = i;
										bk[cnt++] = k;
								}else if(x > 0 && x == max && __calc_leftfactor(rules[bk[0]], rules[i]) == x)
								{
										size_t j;
										bool_t need_i = true, need_k = true;
										for(j = 0; j < n; ++j)
										{
												if(bk[j] == i)need_i = false;
												if(bk[j] == k)need_k = false;
										}
										
										if(need_i)bk[cnt++] = i;
										if(need_k)bk[cnt++] = k;
								}else
								{
								}
						}
				}
		}

		if(cnt == 0)
		{
				goto RETURN_POINT;
		}else
		{
				has_left_factor = AR_S_YES;
		}
		
		
		for(i = 0; i < cnt ; ++i)
		{
				if(output)
				{
						AR_ClearString(tmp);

						if(AR_AppendString(tmp, lhs->name) != AR_S_YES)
						{
								has_left_factor = AR_E_NOMEM;
								goto RETURN_POINT;
						}

						if(AR_AppendString(tmp, L"\t:\t") != AR_S_YES)
						{
								has_left_factor = AR_E_NOMEM;
								goto RETURN_POINT;
						}

						if(Parser_PrintSymbolList(&rules[bk[i]]->body, tmp) != AR_S_YES)
						{
								has_left_factor = AR_E_NOMEM;
								goto RETURN_POINT;
						}

						if(AR_AppendFormatString(tmp, L"\t:\t%Id", max) != AR_S_YES)
						{
								has_left_factor = AR_E_NOMEM;
								goto RETURN_POINT;
						}

						if(__insert_to_symtbl_view(output, lhs->name, AR_GetStringCString(tmp)) != AR_S_YES)
						{
								has_left_factor = AR_E_NOMEM;
								goto RETURN_POINT;
						}
				}
				rules[bk[i]] = NULL;
		}
		
		if(cnt > 0)
		{
				if(output)
				{
						if(__insert_to_symtbl_view(output, lhs->name, L"") != AR_S_YES)
						{
								has_left_factor = AR_E_NOMEM;
								goto RETURN_POINT;
						}
				}
				goto RECHECK_POINT;
		}


RETURN_POINT:
		if(bk)
		{
				AR_DEL(bk);
				bk = NULL;
		}

		if(tmp)
		{
				AR_DestroyString(tmp);
				tmp = NULL;
		}

		return has_left_factor;
}


static arStatus_t					__report_left_factor(const psrGrammar_t *grammar, psrSymbolMapView_t *output)
{
		const psrRule_t	**rules;
		arStatus_t has_left_factor;
		size_t	cnt;
		size_t	i,k;
		const psrSymbList_t *symblist;
		AR_ASSERT(grammar != NULL);
		
		cnt = 0;
		has_left_factor = AR_S_NO;
		symblist = Parser_GetSymbList(grammar);
		rules = AR_NEWARR0(const psrRule_t*, symblist->count);

		if(rules == NULL)
		{
				has_left_factor = AR_E_NOMEM;
				goto END_POINT;
		}
		
		for(i = 0; i < symblist->count; ++i)
		{
				arStatus_t tmp;
				const psrSymb_t *lhs = symblist->lst[i];
				if(lhs->type == PARSER_TERM)
				{
						continue;
				}
				
				AR_memset((void*)rules, 0, sizeof(const psrRule_t*) * symblist->count);
				
				cnt = 0;
				
				for(k = 0; k < grammar->count; ++k)
				{
						if(Parser_CompSymb(lhs, grammar->rules[k]->head) == 0)
						{
								rules[cnt++] = grammar->rules[k];
						}
				}
				
				tmp = __report_rule_left_factor(lhs, rules, cnt,output);

				if(tmp == AR_S_YES)
				{
						has_left_factor = AR_S_YES;
				}else if(tmp == AR_S_NO)
				{

				}else
				{
						has_left_factor = tmp;
						goto END_POINT;
				}
		}

END_POINT:
		if(rules)
		{
				AR_DEL(rules);
				rules = NULL;
		}
		return has_left_factor;
}


/**************************************************************************************************************/



const psrStatusView_t*		Parser_CreateParserStatusView(const parser_t *parser)
{
		psrSymbMap_t	first, follow;
		arString_t		*str;
		const psrSymbList_t		*symb_list;
		psrStatusView_t	*ret;
		size_t i;
		bool_t is_ok;
		AR_ASSERT(parser != NULL && parser->grammar != NULL);

		
		is_ok = true;
		str = NULL;
		ret = NULL;
		
		symb_list = Parser_GetSymbList(parser->grammar);



		Parser_InitSymbMap(&first);
		Parser_InitSymbMap(&follow);

		if(Parser_CalcFirstSet(parser->grammar, &first) != AR_S_YES || Parser_CalcFollowSet(parser->grammar, &follow, &first) != AR_S_YES)
		{
				is_ok = false;
				goto END_POINT;
		}


		str = AR_CreateString();

		if(str == NULL)
		{
				is_ok = false;
				goto END_POINT;
		}


		ret = AR_NEW0(psrStatusView_t);

		if(ret == NULL)
		{
				is_ok = false;
				goto END_POINT;
		}



		for(i = 0; i < symb_list->count; ++i)
		{
				const psrMapRec_t		*rec;
				const psrSymb_t	*symb = symb_list->lst[i];
				
				rec = Parser_GetSymbolFromSymbMap(&first, symb);
				
				AR_ClearString(str);
				if(rec)
				{
						
						if(Parser_PrintSymbolList(&rec->lst, str) != AR_S_YES)
						{
								is_ok = false;
								goto END_POINT;
						}
						
				}


				if(__insert_to_symtbl_view(&ret->first_set, rec->key->name, AR_GetStringCString(str)) != AR_S_YES)
				{
						is_ok = false;
						goto END_POINT;
				}
						
		}


		for(i = 0; i < symb_list->count; ++i)
		{
				const psrMapRec_t		*rec;
				const psrSymb_t	*symb = symb_list->lst[i];
				
				if(symb->type == PARSER_NONTERM)
				{
						rec = Parser_GetSymbolFromSymbMap(&follow, symb);
						
						AR_ClearString(str);

						if(rec)
						{
								if(Parser_PrintSymbolList(&rec->lst, str) != AR_S_YES)
								{
										is_ok = false;
										goto END_POINT;
								}
								
						}

						if(__insert_to_symtbl_view(&ret->follow_set, rec->key->name, AR_GetStringCString(str)) != AR_S_YES)
						{
								is_ok = false;
								goto END_POINT;
						}
				}
		}

		if(__report_left_recursion(parser->grammar, &ret->left_recursion) == AR_E_NOMEM)
		{
				is_ok = false;
				goto END_POINT;
		}

		if(__report_left_factor(parser->grammar, &ret->left_factor) == AR_E_NOMEM)
		{
				is_ok = false;
				goto END_POINT;
		}

		

END_POINT:
		Parser_UnInitSymbMap(&first);
		Parser_UnInitSymbMap(&follow);
		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

		if(ret != NULL && !is_ok) /*有错误发生，需要清理*/
		{
				Parser_DestroyParserStatusView(ret);
				ret = NULL;
		}

		return ret;
}


void							Parser_DestroyParserStatusView(const psrStatusView_t *status_view)
{
		size_t i;

		if(status_view != NULL)
		{
				psrStatusView_t *view = (psrStatusView_t*)status_view;

				
				for(i = 0; i < view->first_set.count; ++i)
				{
						if(view->first_set.name[i])
						{
								AR_DEL(view->first_set.name[i]);
								view->first_set.name[i] = NULL;
						}

						if(view->first_set.name_set[i])
						{
								AR_DEL(view->first_set.name_set[i]);
								view->first_set.name_set[i] = NULL;
						}
				}

				if(view->first_set.name)
				{
						AR_DEL(view->first_set.name);
						view->first_set.name = NULL;
				}

				if(view->first_set.name_set)
				{
						AR_DEL(view->first_set.name_set);
						view->first_set.name_set = NULL;
				}



				for(i = 0; i < view->follow_set.count; ++i)
				{
						if(view->follow_set.name[i])
						{
								AR_DEL(view->follow_set.name[i]);
								view->follow_set.name[i] = NULL;
						}

						if(view->follow_set.name_set[i])
						{
								AR_DEL(view->follow_set.name_set[i]);
								view->follow_set.name_set[i] = NULL;
						}
				}
				
				if(view->follow_set.name)
				{
						AR_DEL(view->follow_set.name);
						view->follow_set.name = NULL;
				}
				
				if(view->follow_set.name_set)
				{
						AR_DEL(view->follow_set.name_set);
						view->follow_set.name_set = NULL;
				}




				for(i = 0; i < view->left_recursion.count; ++i)
				{
						if(view->left_recursion.name[i])
						{
								AR_DEL(view->left_recursion.name[i]);
								view->left_recursion.name[i] = NULL;
						}

						if(view->left_recursion.name_set[i])
						{
								AR_DEL(view->left_recursion.name_set[i]);
								view->left_recursion.name_set[i] = NULL;
						}
				}

				if(view->left_recursion.name)
				{
						AR_DEL(view->left_recursion.name);
						view->left_recursion.name = NULL;
				}

				if(view->left_recursion.name_set)
				{
						AR_DEL(view->left_recursion.name_set);
						view->left_recursion.name_set = NULL;
				}


				for(i = 0; i < view->left_factor.count; ++i)
				{
						if(view->left_factor.name[i])
						{
								AR_DEL(view->left_factor.name[i]);
								view->left_factor.name[i] = NULL;
						}

						if(view->left_factor.name_set[i])
						{
								AR_DEL(view->left_factor.name_set[i]);
								view->left_factor.name_set[i] = NULL;
						}
				}

				if(view->left_factor.name)
				{
						AR_DEL(view->left_factor.name);
						view->left_factor.name = NULL;
				}

				if(view->left_factor.name_set)
				{
						AR_DEL(view->left_factor.name_set);
						view->left_factor.name_set = NULL;
				}

				AR_DEL(view);
				
		}
}






AR_NAMESPACE_END