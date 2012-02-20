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

#include "rgx.h"
#include "lex.h"

AR_NAMESPACE_BEGIN

arStatus_t	Lex_Init()
{
		RGX_InitNode();
		RGX_InitMisc();
		return AR_S_YES;
}

arStatus_t	Lex_UnInit()
{
		RGX_UnInitNode();
		RGX_UnInitMisc();
		return AR_S_YES;
}

/*
typedef struct __lex_rule_set
{
		lexAction_t					*action;
		struct __rgx_node_tag		**nodes;
		size_t						count;
		size_t						cap;
}lexRuleSet_t;
*/

static void		__init_rule_set(lexRuleSet_t *set)
{
		AR_ASSERT(set != NULL);
		AR_memset(set, 0, sizeof(*set));
}

static void		__clear_rule_set(lexRuleSet_t *set)
{
		size_t i;
		AR_ASSERT(set != NULL);

		for(i = 0; i < set->count; ++i)
		{
				RGX_DestroyNode(set->nodes[i]);
				set->nodes[i] = NULL;
		}
		
		set->count = 0;

}

static void		__uninit_rule_set(lexRuleSet_t *set)
{
		size_t i;
		AR_ASSERT(set != NULL);
		for(i = 0; i < set->count; ++i)
		{
				RGX_DestroyNode(set->nodes[i]);
				set->nodes[i] = NULL;
		}

		AR_DEL(set->nodes);
		AR_DEL(set->action);
		AR_memset(set, 0, sizeof(*set));
}

static arStatus_t		__insert_to_rule_set(lexRuleSet_t *set, rgxNode_t *node, const lexAction_t *action)
{
		AR_ASSERT(set != NULL && node != NULL && action != NULL);

		if(set->count == set->cap)
		{
				size_t new_cap;
				lexAction_t *new_acts;
				rgxNode_t **new_nodes;

				new_cap = (set->cap + 1)*2;
				new_acts = AR_NEWARR(lexAction_t, new_cap);
				new_nodes = AR_NEWARR(rgxNode_t*, new_cap);

				if(new_acts == NULL || new_nodes == NULL)
				{
						if(new_acts)
						{
								AR_DEL(new_acts);
								new_acts = NULL;
						}

						if(new_nodes)
						{
								AR_DEL(new_nodes);
								new_nodes = NULL;
						}

						return AR_E_NOMEM;
				}
				AR_memcpy(new_acts, set->action, set->count * sizeof(lexAction_t));
				AR_memcpy(new_nodes, set->nodes, set->count * sizeof(rgxNode_t*));
				
				AR_DEL(set->action);
				set->action = NULL;
				AR_DEL(set->nodes);
				set->nodes = NULL;
				
				set->cap = new_cap;
				set->action = new_acts;
				set->nodes = new_nodes;
		}
		
		set->action[set->count] = *action;
		set->nodes[set->count] = node;
		set->count++;
		return AR_S_YES;
}


static arStatus_t		__remove_from_rule_set(lexRuleSet_t *set, size_t value)
{
		size_t i;
		AR_ASSERT(set != NULL);

		for(i = 0; i < set->count; ++i)
		{
				if(set->action[i].value == value)
				{
						set->action[i] = set->action[set->count-1];
						set->nodes[i] = set->nodes[set->count-1];
						set->count--;
						return AR_S_YES;
				}
		}
		return AR_S_NO;
}


/**********************************lex**************************************************/

arStatus_t	Lex_InsertName(lex_t *lex, const wchar_t *name, const wchar_t *expr)
{
		rgxResult_t res;
		AR_ASSERT(name != NULL && AR_wcslen(name) > 0 && expr != NULL && AR_wcslen(expr) > 0);

		if(AR_wcslen(name) == 0)
		{
				AR_FormatString(lex->last_err_msg, L"Lex Rule Error : empty name '%ls'\r\n", expr);
				return AR_S_NO;
		}

		if(AR_wcslen(expr) == 0)
		{
				AR_FormatString(lex->last_err_msg, L"Lex Rule Error : empty expr '%ls'\r\n", name);
				return AR_S_NO;
		}


		if(RGX_FindFromNameSet(lex->name_tbl, name) != NULL)
		{
				/*AR_error( L"Lex Rule Error : Duplicate name defination %ls: %ls\r\n", name, expr);*/
				AR_FormatString(lex->last_err_msg, L"Lex Name Error : Duplicate name defination %ls: %ls\r\n", name, expr);
				return AR_S_NO;
		}

		res = RGX_ParseExpr(expr, lex->name_tbl);

		if(res.err.status != AR_S_YES)
		{
				AR_ASSERT(res.node == NULL);

				if(res.err.status == AR_S_NO)
				{
						AR_FormatString(lex->last_err_msg, L"Lex Name Error : %ls: %ls\r\n", name, res.err.pos);
				}

				return res.err.status;
		}


		AR_ASSERT(res.node != NULL);

		res.err.status = RGX_InsertToNameSet(lex->name_tbl, name, res.node);

		if(res.err.status != AR_S_YES)
		{
				RGX_DestroyNode(res.node);
				res.node = NULL;
		}

		return res.err.status;
}


arStatus_t	Lex_RemoveByName(lex_t *lex, const wchar_t *name)
{
		AR_ASSERT(lex != NULL && name != NULL);

		return RGX_RemoveFromNameSet(lex->name_tbl, name);
}





arStatus_t	Lex_RemoveByValue(lex_t *lex, size_t value)
{
		AR_ASSERT(lex != NULL);
		
		return __remove_from_rule_set(&lex->rule_set, value);
}





arStatus_t	Lex_InsertRule(lex_t *lex, const wchar_t *rule, const lexAction_t *action)
{
		rgxResult_t res;
		rgxNode_t	*cat, *final;
		
		AR_ASSERT(lex != NULL && rule != NULL && action != NULL);
		AR_ASSERT(AR_wcslen(rule) > 0);

		if(AR_wcslen(rule) == 0)
		{
				AR_FormatString(lex->last_err_msg, L"Lex Rule Error : empty rule %Id\r\n", action->value);
				return AR_S_NO;
		}

		res = RGX_ParseExpr(rule, lex->name_tbl);

		if(res.err.status != AR_S_YES)
		{
				AR_ASSERT(res.node == NULL);
				/*AR_error(AR_LEX, L"Lex Rule Error : %d : %ls\n", action->type, res.err.pos);*/
				/*AR_error(L"Lex Rule Error : %" AR_PLAT_INT_FMT L"d : %ls\n", (size_t)action->type, (size_t)res.err.pos);*/

				if(res.err.status == AR_S_NO)
				{
						AR_FormatString(lex->last_err_msg, L"Lex Rule Error : %Id : %ls\n", (size_t)action->value, res.err.pos == NULL ? L"" : res.err.pos);
				}

				return res.err.status;
		}

		AR_ASSERT(res.node != NULL);

		cat = RGX_CreateNode(RGX_CAT_T);
		final = RGX_CreateNode(RGX_FINAL_T);

		if(cat == NULL || final == NULL)
		{
				if(cat)
				{
						RGX_DestroyNode(cat);
						final = NULL;
				}

				if(final)
				{
						RGX_DestroyNode(final);
						final = NULL;
				}

				if(res.node)
				{
						RGX_DestroyNode(res.node);
						res.node = NULL;
				}

				return AR_E_NOMEM;
		}

		final->final_val = (int_t)action->value;

		cat->left = res.node;
		cat->right = final;

		
		res.err.status = __insert_to_rule_set(&lex->rule_set, cat, action);
		
		if(res.err.status != AR_S_YES)
		{
				RGX_DestroyNode(cat);
				cat = NULL;
		}

		return res.err.status;
}



arStatus_t	Lex_Insert(lex_t *lex, const wchar_t *input)
{
		const wchar_t *p;

		AR_ASSERT(lex != NULL && input != NULL);
		p = AR_wcstrim_space(input);

		if(AR_iswdigit(*p) || *p == L'%')/*action*/
		{
				lexAction_t		act;
				bool_t			is_skip;

				is_skip = false;
				if(*p == L'%')
				{
						if(AR_wcsstr(p, L"%skip") == NULL)
						{
								return AR_S_NO;
						}

						p = AR_wcstrim_space(p + AR_wcslen(L"%skip"));

						is_skip = true;
				}

				act.priority = act.value = 0;
				p = AR_wtou(p, (uint_t*)&act.value, 10);
				if(p == NULL)return AR_S_NO;

				p = AR_wcstrim_space(p);

				if(*p == L',')
				{
						p = AR_wtou(++p, (uint_t*)&act.priority, 10);
						if(p == NULL)return AR_S_NO;
				}

				p = AR_wcstrim_space(p);

				act.is_skip = is_skip;
				return Lex_InsertRule(lex, p, &act);

		}else if(AR_iswalpha(*p) || *p == L'_')
		{
				wchar_t name[AR_RGX_MAXNAME + 1];
				size_t i;
				i = 0;
				while(AR_iswalnum(*p) || *p == L'_')
				{
						name[i++] = *p++;
				}
				name[i] = L'\0';
				p = AR_wcstrim_space(p);

				if(*p != L'=')return AR_S_NO;
				p = AR_wcstrim_space(++p);
				return Lex_InsertName(lex, name, p);

		}else
		{
				/*AR_error(L"Lex Rule Error : Invalid Input %ls\r\n", p);*/
				
				AR_FormatString(lex->last_err_msg, L"Lex Rule Error : Invalid Input %ls\r\n", p);
				return AR_S_NO;
		}


}



arStatus_t	Lex_GenerateTransTable(lex_t *lex)
{
		AR_ASSERT(lex != NULL);
		
		/*
		Lex_SortProgSet(lex->prog_set);
		*/
		return (bool_t)(lex->rule_set.count > 0) ? AR_S_YES : AR_S_NO;
}





lex_t*	Lex_Create()
{
		lex_t *res;

		res = AR_NEW0(lex_t);
		if(res == NULL)
		{
				return NULL;
		}

		res->name_tbl = AR_NEW(rgxNameSet_t);

		if(res->name_tbl == NULL)
		{
				AR_DEL(res);
				res = NULL;
				return NULL;
		}

		res->last_err_msg = AR_CreateString();

		if(res->last_err_msg == NULL)
		{
				AR_DEL(res->name_tbl);
				AR_DEL(res);
				return NULL;
		}


		RGX_InitNameSet(res->name_tbl);
		__init_rule_set(&res->rule_set);
		
		return res;
}



void	Lex_Clear(lex_t *lex)
{
		AR_ASSERT(lex != NULL);
		RGX_ClearNameSet(lex->name_tbl);
		__clear_rule_set(&lex->rule_set);
		AR_DestroyString(lex->last_err_msg);
}





void	Lex_Destroy(lex_t *lex)
{
		AR_ASSERT(lex != NULL);
		
		Lex_Clear(lex);
		RGX_UnInitNameSet(lex->name_tbl);
		__uninit_rule_set(&lex->rule_set);
		AR_DEL(lex->name_tbl);
		AR_DEL(lex);
}


const wchar_t*	Lex_GetLastError(const lex_t *lex)
{
		AR_ASSERT(lex != NULL);
		return AR_GetStringCString(lex->last_err_msg);
}

void			Lex_ClearLastError(lex_t *lex)
{
		AR_ASSERT(lex != NULL);
		AR_ClearString(lex->last_err_msg);
}


AR_NAMESPACE_END
