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

#include "parser.h"
#include "parser_in.h"

AR_NAMESPACE_BEGIN




/*
void			Parser_InitTermInfoList(psrTermInfoList_t	*lst);
void			Parser_UnInitTermInfoList(psrTermInfoList_t	*lst);
void			Parser_ClearTermInfoList(psrTermInfoList_t	*lst);
psrTermInfo_t*	Parser_FindTermByName(psrTermInfoList_t	*lst, const wchar_t *name);
psrTermInfo_t*	Parser_FindTermByValue(psrTermInfoList_t	*lst, size_t val);
bool_t			Parser_InsertToTermInfoList(psrTermInfoList_t	*lst, const wchar_t *name, size_t val, psrAssocType_t assoc, size_t prec, psrTermFunc_t	leaf_f);
*/


void			Parser_InitTermInfoList(psrTermInfoList_t	*lst)
{
		AR_ASSERT(lst != NULL);
		AR_memset(lst, 0, sizeof(*lst));
		

}


void			Parser_UnInitTermInfoList(psrTermInfoList_t	*lst)
{
		AR_ASSERT(lst != NULL);
		Parser_ClearTermInfoList(lst);
		if(lst->lst)
		{
				AR_DEL(lst->lst);
				lst->lst = NULL;
		}
		AR_memset(lst, 0, sizeof(*lst));
}


void			Parser_ClearTermInfoList(psrTermInfoList_t	*lst)
{
		size_t i;
		AR_ASSERT(lst != NULL);

		for(i = 0; i < lst->count; ++i)
		{
				psrTermInfo_t	*info = &lst->lst[i];

				Parser_DestroySymb(info->term);
		}
		lst->count = 0;
}





psrTermInfo_t*	Parser_FindTermByName(psrTermInfoList_t	*lst, const wchar_t *name)
{
		size_t i;
		AR_ASSERT(lst != NULL && name != NULL);
		for(i = 0; i < lst->count; ++i)
		{
				psrTermInfo_t	*info = &lst->lst[i];
				/*注意，这里的参数name可能是任何非Parser_StringTable分配的内存，
				 *因此，这里必须用AR_wcscmp比较字符串而非类似Parser_CompSymb内部的比较str指针
				*/
				if(AR_wcscmp(info->term->name, name) == 0)
				{
						return info;
				}
		}
		return NULL;
}


psrTermInfo_t*	Parser_FindTermByValue(psrTermInfoList_t	*lst, size_t val)
{
		size_t i;
		AR_ASSERT(lst != NULL);
		for(i = 0; i < lst->count; ++i)
		{
				psrTermInfo_t	*info = &lst->lst[i];
				if(info->val == val)
				{
						return info;
				}
		}
		return NULL;
}




int_t			Parser_IndexOfTermInfoListByName(const psrTermInfoList_t	*lst, const wchar_t *name)
{

		size_t i;
		AR_ASSERT(lst != NULL && name != NULL);
		for(i = 0; i < lst->count; ++i)
		{
				psrTermInfo_t	*info = &lst->lst[i];
				/*注意，这里的参数name可能是任何非Parser_StringTable分配的内存，
				 *因此，这里必须用AR_wcscmp比较字符串而非类似Parser_CompSymb内部的比较str指针
				*/
				if(AR_wcscmp(info->term->name, name) == 0)
				{
						return (int_t)i;
				}
		}

		return -1;
}



int_t			Parser_IndexOfTermInfoListByValue(const psrTermInfoList_t	*lst, size_t val)
{

		size_t i;
		AR_ASSERT(lst != NULL);
		for(i = 0; i < lst->count; ++i)
		{
				psrTermInfo_t	*info = &lst->lst[i];
				if(info->val == val)
				{
						return (int_t)i;
				}
		}
		
		return -1;
}


psrTermInfo_t*	Parser_GetTermByIndex(psrTermInfoList_t	*lst, size_t index)
{
		AR_ASSERT(lst != NULL && index < lst->count);
		return &lst->lst[index];
}

arStatus_t			Parser_InsertToTermInfoList(psrTermInfoList_t	*lst, const wchar_t *name, size_t val, psrAssocType_t assoc, size_t prec, psrTermFunc_t	leaf_f)
{
		
		psrTermInfo_t *info;
		const psrSymb_t *new_symb;
		AR_ASSERT(lst != NULL && name != NULL && AR_wcslen(name) > 0);

		info = NULL;
		new_symb = Parser_CreateSymb(name, PARSER_TERM);
		
		if(new_symb == NULL)
		{
				goto INVALID_POINT;
		}

		if(lst->count == lst->cap)
		{
				size_t new_cap;
				psrTermInfo_t *new_lst;

				new_cap = (lst->cap + 4)*2;
				new_lst = AR_NEWARR(psrTermInfo_t, new_cap);

				if(new_lst == NULL)
				{
						goto INVALID_POINT;
				}

				AR_memcpy(new_lst, lst->lst, lst->count * sizeof(psrTermInfo_t));

				if(lst->lst)
				{
						AR_DEL(lst->lst);
						lst->lst = NULL;
				}

				lst->cap = new_cap;
				lst->lst = new_lst;
		}

		info = &lst->lst[lst->count++];
		info->term = new_symb;
		new_symb = NULL;

		info->assoc = assoc;
		info->prec = prec;
		info->val = val;
		info->leaf_f = leaf_f;
		return AR_S_YES;


INVALID_POINT:
		if(new_symb)
		{
				Parser_DestroySymb(new_symb);
				new_symb = NULL;
		}

		return AR_E_NOMEM;
}

/*******************************************Rule******************************************************************/

/*


*/

arStatus_t		Parser_CreateRule(psrRule_t **prule, const psrSymb_t *head, const psrSymbList_t *body, const wchar_t *prec_tok, psrRuleFunc_t rule_f, size_t auto_ret, const psrTermInfoList_t *term_list, arString_t *err_msg)
{
		psrRule_t *rule;
		size_t i;
		bool_t			inerr;
		const wchar_t*  right_term;
		
		

		AR_ASSERT(prule != NULL);
		AR_ASSERT(head != NULL && body != NULL && term_list != NULL);
		AR_ASSERT(auto_ret <= body->count);

		rule = NULL;
		*prule = NULL;
		
		right_term = NULL; 
		inerr = false;

		if(Parser_FindTermByName((psrTermInfoList_t*)term_list, head->name) != NULL)/*输入的非终结符号已存在于非终结符中，错误*/
		{
				if(err_msg)
				{
						AR_FormatString(err_msg,L"Grammar Error: Duplicate Rule name <%ls>!\r\n", head->name);
				}
				return AR_S_NO;
		}

		if(prec_tok != NULL && Parser_FindTermByName((psrTermInfoList_t*)term_list, prec_tok) == NULL)/*产生式优先级符号不存在于非终结符中，错误*/
		{
				/*AR_error(L"Grammar Error: Invalid prec token in <%ls>!\r\n", head->name);*/
				if(err_msg)
				{
						AR_FormatString(err_msg, L"Grammar Error: Invalid prec \"%ls\" token <%ls>\r\n", prec_tok, head->name);
				}
				return AR_S_NO;
		}
		
		

		for(i = 0; i < body->count; ++i)
		{
				const psrSymb_t	*symb;

				symb = body->lst[i];

				if(body->lst[i]->type == PARSER_TERM)
				{
						if(Parser_FindTermByName((psrTermInfoList_t*)term_list, symb->name) == NULL)/*非终结符不存在于语法非终结符集合中，失败*/
						{
								if(err_msg)
								{
										AR_FormatString(err_msg, L"Grammar Error: Invalid term token \"%ls\"\r\n", symb->name);
								}
								return AR_S_NO;
						}
						
						if(Parser_CompSymb(symb, PARSER_ErrorSymb) == 0)
						{
								if(inerr)/*同一个产生式存在两个error*/
								{
										if(err_msg)
										{
												AR_FormatString(err_msg, L"Grammar Error: Duplicate error definition in <%ls>!\r\n", head->name);
										}
										return AR_S_NO;
								}else
								{
										inerr = true;
								}
						}
						right_term = symb->name;
				}else
				{
						if(Parser_FindTermByName((psrTermInfoList_t*)term_list, symb->name) != NULL)/*非终结符号存在于终结符号表中*/
						{
								if(err_msg)
								{
										AR_FormatString(err_msg, L"Grammar Error: Invalid non-term token \"%ls\"\r\n", symb->name);
								}

								return AR_S_NO;
						}
				}
		}
		
		if(right_term == NULL)/*每个产生式必须存有一个优先级符号，且为终结符*/
		{
				right_term = PARSER_DefPrecSymb->name;
		}
		
/*********************************************************************************************************************/
		
		
		
		
		rule = AR_NEW0(psrRule_t);/*分配点1*/

		if(rule == NULL)
		{
				return AR_E_NOMEM;
		}

		rule->prec_tok = prec_tok != NULL ? Parser_AllocString(prec_tok) : Parser_AllocString(right_term);

		if(rule->prec_tok == NULL)
		{
				AR_DEL(rule);
				rule = NULL;
				return AR_E_NOMEM;
		}

		

		rule->head = Parser_CopyNewSymb(head); 
		
		if(rule->head == NULL)					
		{
				AR_DEL(rule);
				rule = NULL;
				return AR_E_NOMEM;
		}

		rule->rule_f = rule_f;
		rule->auto_ret = auto_ret;

		Parser_InitSymbList(&rule->body);
		


		for(i = 0; i < body->count; ++i)
		{
				const psrSymb_t *tmp_symb = Parser_CopyNewSymb(body->lst[i]);/*分配点4*/

				if(tmp_symb == NULL)	
				{
						Parser_DestroyRule(rule);
						rule = NULL;
						return AR_E_NOMEM;
				}

				if(Parser_InsertToSymbList(&rule->body, tmp_symb) != AR_S_YES)
				{
						Parser_DestroySymb(tmp_symb);
						tmp_symb = NULL;
						Parser_DestroyRule(rule);
						rule = NULL;
						return AR_E_NOMEM;
				}

		}

		*prule = rule;
	
		return AR_S_YES;
}



/*****************************************************************************************************************************************/


arStatus_t Parser_CreateRuleByStr(psrRule_t **prule, const wchar_t *str, const wchar_t *prec, psrRuleFunc_t rule_f, size_t auto_ret, const psrTermInfoList_t *term_list, arString_t *err_msg)
{
		const psrSymb_t *head;
		psrSymbList_t	body;
		psrRule_t		*rule;
		const wchar_t	*p, *beg;
		
		arStatus_t		status;
		size_t i;
		AR_ASSERT(str != NULL && term_list != NULL);


		status = AR_S_YES;
		rule = NULL;
		head = NULL; 
		*prule = NULL;

		Parser_InitSymbList(&body);
		p = AR_wcstrim_space(str);

		beg = p;

		if(!AR_iswalpha(*beg) && *beg != L'_')
		{
				status = AR_S_NO;
				goto END_POINT;
		}
		

		while(*p != L'\0' && (AR_iswalnum(*p) || *p == L'_'))
		{
				p++;
		}

		if(*p == L'\0' || p - beg == 0)
		{
				status = AR_S_NO;
				goto END_POINT;
		}else
		{
				head = Parser_CreateSymbN(beg, p - beg, PARSER_NONTERM);

				if(head == NULL)
				{
						status = AR_E_NOMEM;
						goto END_POINT;
				}

		}

		
		p = AR_wcstrim_space(p);

		if(*p != L':')
		{
				status = AR_S_NO;
				goto END_POINT;
		}

		++p;

		while(*p != L'\0')
		{
				if(AR_iswspace(*p))
				{
						++p;
				}else
				{
						beg = p;
						while(*p != L'\0' && !AR_iswspace(*p))
						{
								++p; 
						}
						
						if(*beg != L'\0')
						{
								wchar_t *name;
								size_t count;

								const psrSymb_t *tmp;
								count = p - beg;

								name = AR_wcsndup(beg, count);

								if(name == NULL)
								{
										status = AR_E_NOMEM;
										goto END_POINT;
								}

								if(Parser_FindTermByName((psrTermInfoList_t*)term_list, name) == NULL)
								{
										tmp = Parser_CreateSymb(name, PARSER_NONTERM);
								}else
								{
										tmp = Parser_CreateSymb(name, PARSER_TERM);
								}

								if(tmp == NULL)
								{
										AR_DEL(name);
										name = NULL;
										status = AR_E_NOMEM;
										goto END_POINT;
								}

								status = Parser_InsertToSymbList(&body, tmp);

								if(status != AR_S_YES)
								{
										Parser_DestroySymb(tmp);
										tmp = NULL;

										AR_DEL(name);
										name = NULL;

										status = AR_E_NOMEM;
										goto END_POINT;
								}

								AR_DEL(name);
						}
				}
		}
		

		status = Parser_CreateRule(&rule, head, &body, prec, rule_f, auto_ret, term_list, err_msg);
	

END_POINT:

		if(head)
		{
				Parser_DestroySymb(head);
				head = NULL;
		}

	
		for(i = 0; i < body.count; ++i)
		{
				Parser_DestroySymb(body.lst[i]);
		}

		Parser_UnInitSymbList(&body);


		if(rule != NULL)
		{
				*prule = rule;
				rule = NULL;
		}
		
		return status;
}




void			Parser_DestroyRule(psrRule_t *rule)
{
		size_t i;
		AR_ASSERT(rule != NULL);

		Parser_DestroySymb(rule->head);
		for(i = 0; i < rule->body.count; ++i)
		{
				Parser_DestroySymb(rule->body.lst[i]);
		}

		Parser_UnInitSymbList(&rule->body);
		/*if(rule->prec_tok) AR_DEL(rule->prec_tok);*/
		if(rule->prec_tok)
		{
				rule->prec_tok = NULL;
		}
		AR_DEL(rule);
}


/*
psrRule_t*		Parser_CopyNewRule(const psrRule_t *rule)
{
		psrRule_t *dest;
		size_t i;
		AR_ASSERT(rule != NULL);
		dest = AR_NEW0(psrRule_t);

		dest->head = Parser_CopyNewSymb(rule->head);
		Parser_InitSymbList(&dest->body);

		for(i = 0; i < rule->body.count; ++i)
		{
				Parser_InsertToSymbList(&dest->body, Parser_CopyNewSymb(rule->body.lst[i]));
		}

		dest->prec_tok = rule->prec_tok;
		dest->rule_f = rule->rule_f;
		return dest;

}

bool_t			Parser_IsEmptyRule(const psrRule_t *rule)
{
		AR_ASSERT(rule != NULL);

		return rule->body.count == 0;
}
*/

/******************************************Grammar************************************************************/

/******************************************************************************************************************/

static arStatus_t __insert_rule(psrGrammar_t *grammar, psrRule_t *rule)
{
		if(grammar->count == grammar->cap)
		{
				size_t new_cap;
				psrRule_t		**new_rules;
				new_cap = (grammar->cap + 4)*2;
				new_rules = AR_NEWARR(psrRule_t*, new_cap);

				if(new_rules == NULL)
				{
						return AR_E_NOMEM;
				}
				AR_memcpy(new_rules, grammar->rules, grammar->count * sizeof(psrRule_t*));

				if(grammar->rules)
				{
						AR_DEL(grammar->rules);
						grammar->rules = NULL;
				}


				grammar->cap = new_cap;
				grammar->rules = new_rules;
		}
		grammar->rules[grammar->count++] = rule;

		return AR_S_YES;
}


static arStatus_t __init_grammar_component_unit(psrGrammar_t *grammar)
{
		arStatus_t status;
		AR_ASSERT(grammar != NULL);

		/*每个grammar都有自己私有的符号，因为spec_id的关系，所以这里都copy一份新的*/

		status = Parser_InsertToTermInfoList(&grammar->term_list, PARSER_EOISymb->name,PARSER_EOI_TOKVAL, PARSER_ASSOC_NONASSOC, 0, NULL);

		if(status != AR_S_YES)
		{
				return status;
		}

		status = Parser_InsertToTermInfoList(&grammar->term_list, PARSER_ErrorSymb->name, PARSER_ERROR_TOKVAL, PARSER_ASSOC_NONASSOC, 0, NULL);

		if(status != AR_S_YES)
		{
				return status;
		}


		status = Parser_InsertToTermInfoList(&grammar->term_list, PARSER_DefPrecSymb->name, PARSER_DEFPREC_TOKVAL, PARSER_ASSOC_NONASSOC, 0, NULL);

		if(status != AR_S_YES)
		{
				return status;
		}

		/************************************************初始化symb list空间****************************************/

		status = Parser_ReserveSymbListCapacity(&grammar->symb_list, AR_PSR_MAX_SYMB_LIST);

		if(status != AR_S_YES)
		{
				return status;
		}

		{
				psrRule_t *start;
				psrSymbList_t	body;

				start = NULL;
				Parser_InitSymbList(&body);

				status = Parser_CreateRule(&start, PARSER_StartSymb, &body, NULL, NULL, 0, &grammar->term_list, grammar->last_err_msg);

				Parser_UnInitSymbList(&body);

				
				if(status != AR_S_YES)
				{
						AR_ASSERT(start == NULL);
						return status;
				}else
				{
						AR_ASSERT(start != NULL);
						status = __insert_rule(grammar, start);

						if(status != AR_S_YES)
						{
								Parser_DestroyRule(start);
								start = NULL;
								return status;
						}
				}

				return status;
		}
}


static void __clear_grammar(psrGrammar_t *grammar)
{
		size_t i;
		AR_ASSERT(grammar != NULL);
		
		for(i = 0; i < grammar->count; ++i)
		{
				Parser_DestroyRule(grammar->rules[i]);
				grammar->rules[i] = NULL;
		}
		
		grammar->count = 0;
		Parser_ClearTermInfoList(&grammar->term_list);
		Parser_ClearSymbList(&grammar->symb_list);
}


/******************************************************************************************************************/

void					Parser_ResetGrammarParseHandler(psrGrammar_t *gmr, const psrHandler_t *handler)
{
		AR_ASSERT(gmr != NULL && handler != NULL);
		gmr->psr_handler = *handler;
}

psrGrammar_t*			Parser_CreateGrammar(const psrHandler_t *handler)
{
		psrGrammar_t* gmr;
		
		AR_ASSERT(handler != NULL && handler->free_f != NULL);
		gmr = AR_NEW0(psrGrammar_t);
	
		if(gmr == NULL)
		{
				return NULL;
		}

		gmr->last_err_msg = AR_CreateString();

		if(gmr->last_err_msg == NULL)
		{
				AR_DEL(gmr);
				gmr = NULL;
				return NULL;
		}

		gmr->psr_handler = *handler;

		Parser_InitTermInfoList(&gmr->term_list);
		
		Parser_InitSymbList(&gmr->symb_list);
		
		


		if(__init_grammar_component_unit(gmr) != AR_S_YES)
		{
				Parser_DestroyGrammar(gmr);
				return NULL;
		}
		
		return gmr;
}




arStatus_t	Parser_ClearGrammar(psrGrammar_t *grammar)
{
		psrGrammar_t	tmp;
		psrGrammar_t	*new_gmr;
		AR_ASSERT(grammar != NULL);

		new_gmr = Parser_CreateGrammar(&grammar->psr_handler);

		if(new_gmr == NULL)
		{
				return AR_E_NOMEM;
		}

		tmp = *grammar;
		*grammar = *new_gmr;
		*new_gmr = tmp;

		Parser_DestroyGrammar(new_gmr);
		new_gmr = NULL;
		return AR_S_YES;

		/*
		__clear_grammar(grammar);
		__init_grammar_component_unit(grammar);
		*/
}


const wchar_t*			Parser_GetGrammarLastError(const psrGrammar_t *grammar)
{
		AR_ASSERT(grammar != NULL);
		return AR_GetStringCString(grammar->last_err_msg);
}

void					Parser_ClearGrammarLastError(psrGrammar_t *grammar)
{
		AR_ASSERT(grammar != NULL);
		AR_ClearString(grammar->last_err_msg);
}


void					Parser_DestroyGrammar(psrGrammar_t *grammar)
{

		AR_ASSERT(grammar != NULL);

		AR_DestroyString(grammar->last_err_msg);
		grammar->last_err_msg = NULL;
		
		__clear_grammar(grammar);
		
		Parser_UnInitTermInfoList(&grammar->term_list);
		Parser_UnInitSymbList(&grammar->symb_list);
		AR_DEL(grammar->rules);
		grammar->rules = NULL;

		AR_DEL(grammar);
}



const psrHandler_t*		Parser_GetGrammarHandler(const psrGrammar_t *grammar)
{
		AR_ASSERT(grammar != NULL);
		return &grammar->psr_handler;
}



const psrSymbList_t* Parser_GetSymbList(const psrGrammar_t *grammar)
{
		psrSymbList_t *lst;
		AR_ASSERT(grammar != NULL);
		
		lst = (psrSymbList_t*)(&grammar->symb_list);
		Parser_ClearSymbList(lst);
		
		{
				size_t i,k;
				/*先插入所有终结符*/
				for(i = 0; i < grammar->term_list.count; ++i)
				{
						if(Parser_InsertToSymbList(lst, grammar->term_list.lst[i].term) != AR_S_YES)
						{
								AR_error(AR_ERR_FATAL, L"parser symbol list overflow\r\n");
						}
				}
				
				/*插入每一条产生式的每一个符号，终结符或非终结符*/
				for(i = 0; i < grammar->count; ++i)
				{
						const psrRule_t	*rule = grammar->rules[i];
						
						if(Parser_FindFromSymbList(lst, rule->head) == -1)
						{
								if(Parser_InsertToSymbList(lst, rule->head) != AR_S_YES)
								{
										AR_error(AR_ERR_FATAL, L"parser symbol list overflow\r\n");
								}
						}
						
						for(k = 0; k < rule->body.count; ++k)
						{
								if(Parser_FindFromSymbList(lst, rule->body.lst[k]) == -1)
								{
										if(Parser_InsertToSymbList(lst, rule->body.lst[k]) != AR_S_YES)
										{
												AR_error(AR_ERR_FATAL, L"parser symbol list overflow\r\n");
										}
								}
						}
				}
		}

		return lst;
}


const psrTermInfoList_t*		Parser_GetTermList(const psrGrammar_t *grammar)
{
		AR_ASSERT(grammar != NULL);
		return &grammar->term_list;
}




arStatus_t				Parser_InsertTerm(psrGrammar_t *grammar, const wchar_t *name, size_t val, psrAssocType_t assoc, size_t prec, psrTermFunc_t	leaf_f)
{
		
		AR_ASSERT(grammar != NULL && name != NULL && AR_wcslen(name) > 0);
		
		

		if(val < PARSER_MIN_TOKENVAL)
		{
				/*AR_error(AR_GRAMMAR, L"Grammar Error : invalid token value %d\r\n", val);*/
				/*AR_error(L"Grammar Error : invalid token value %" AR_PLAT_INT_FMT L"d\r\n", (size_t)val);*/
				AR_FormatString(grammar->last_err_msg, L"Grammar Error : invalid token value %Id\r\n", (size_t)val);
				return AR_S_NO;
		}
		
		if(AR_wcslen(name) == 0)
		{
				AR_FormatString(grammar->last_err_msg, L"Grammar Error : invalid token name '%ls'\r\n", name);
				return AR_S_NO;
		}

		
		if(Parser_FindTermByName(&grammar->term_list, name) != NULL)
		{
				AR_FormatString(grammar->last_err_msg, L"Grammar Error : duplicate name : \"%ls\" definition\r\n", name);
				return AR_S_NO;
		}

		if(Parser_FindTermByValue(&grammar->term_list, val) != NULL)
		{
				/*AR_error(AR_GRAMMAR, L"Grammar Error : duplicate token value : %d definition\r\n", val);*/
				/*AR_error(L"Grammar Error : duplicate token value : %" AR_PLAT_INT_FMT L"d definition\r\n", (size_t)val);*/
				AR_FormatString(grammar->last_err_msg, L"Grammar Error : duplicate token value : %Id definition\r\n", (size_t)val);
				return AR_S_NO;
		}


		if(Parser_GetSymbFromGrammarByName(grammar, name) != NULL)
		{
				AR_FormatString(grammar->last_err_msg, L"Grammar Error : duplicate symbol name : \"%ls\" definition\r\n", name);
				return AR_S_NO;
		}
		
		return Parser_InsertToTermInfoList(&grammar->term_list, name, val, assoc, prec, leaf_f);
}


arStatus_t				Parser_InsertRule(psrGrammar_t *grammar, psrRule_t *rule)
{
		arStatus_t status;
		size_t i;
		AR_ASSERT(grammar != NULL && rule != NULL);
		
		status = AR_S_YES;


		for(i = 0; i < grammar->count; ++i)
		{
				if(grammar->rules[i] == rule)
				{
						return AR_S_NO;
				}
		}

		if(Parser_CompSymb(rule->head, PARSER_StartSymb) == 0)/*rule-head不可为%Start保留符号*/
		{
				/*AR_error(L"Grammar Error : Non-term token %ls was reserved\r\n", rule->head->name);*/
				AR_FormatString(grammar->last_err_msg, L"Grammar Error : Non-term token %ls was reserved\r\n", rule->head->name);
				return AR_S_NO;
		}


		for(i = 0; i < rule->body.count; ++i)
		{
				const psrSymb_t *l = rule->body.lst[i];
				const psrSymb_t *r = Parser_GetSymbFromGrammarByName(grammar, l->name);

				if(r != NULL && Parser_CompSymb(l, r) != 0)
				{
						AR_FormatString(grammar->last_err_msg, L"Grammar Error : duplicate symbol name : \"%ls\" definition\r\n", l->name);
						return AR_S_NO;
				}
		}

		if(grammar->count == 1)
		{
				const psrSymb_t *tmp_symb;
				AR_ASSERT(grammar->rules[0]->body.count == 0);
				/*
				Parser_DestroySymb(grammar->rules[0]->body.lst[0]);
				grammar->rules[0]->body.lst[0] = Parser_CopyNewSymb(rule->head);
				*/
				tmp_symb = Parser_CopyNewSymb(rule->head);

				if(tmp_symb == NULL)
				{
						return AR_E_NOMEM;
				}

				status = Parser_InsertToSymbList(&grammar->rules[0]->body, tmp_symb);

				if(status != AR_S_YES)
				{
						Parser_DestroySymb(tmp_symb);
						tmp_symb = NULL;
						return AR_E_NOMEM;
				}
		}
		return __insert_rule(grammar, rule);
}


arStatus_t					Parser_InsertRuleBySymbList(psrGrammar_t *grammar, const psrSymb_t *head, const psrSymbList_t *body, const wchar_t *prec_tok, psrRuleFunc_t rule_f, size_t auto_ret)
{
		arStatus_t		status;
		psrRule_t		*rule;
		AR_ASSERT(grammar != NULL && head != NULL && body != NULL);

		status = AR_S_YES;
		rule = NULL;

		status = Parser_CreateRule(&rule, head, body, prec_tok, rule_f, auto_ret, &grammar->term_list, grammar->last_err_msg);
		
		if(status != AR_S_YES)
		{
				AR_ASSERT(rule == NULL);
				return status;
		}

		status = Parser_InsertRule(grammar, rule);

		if(status != AR_S_YES)
		{
				Parser_DestroyRule(rule);
				rule = NULL;
		}

		return status;
}


arStatus_t				Parser_InsertRuleByStr(psrGrammar_t *grammar, const wchar_t *str, const wchar_t *prec, psrRuleFunc_t rule_f, size_t auto_ret)
{
		arStatus_t		status;
		psrRule_t		*rule;
		AR_ASSERT(grammar != NULL && str != NULL);

		status = AR_S_YES;
		rule = NULL;
		status = Parser_CreateRuleByStr(&rule, str, prec, rule_f, auto_ret, &grammar->term_list, grammar->last_err_msg);

		if(status != AR_S_YES)
		{
				AR_ASSERT(rule == NULL);
				return status;
		}
		
		status = Parser_InsertRule(grammar, rule);

		if(status != AR_S_YES)
		{
				Parser_DestroyRule(rule);
				rule = NULL;
		}

		return status;
}







int_t					Parser_IndexOfGrammar(const psrGrammar_t *grammar, const psrRule_t *rule)
{
		size_t i;
		for(i = 0; i < grammar->count; ++i)
		{
				if(grammar->rules[i] == rule)
				{
						return (int_t)i;
				}
		}

		return -1;
}



void		Parser_ResetTermSpecID(const psrGrammar_t *grammar)
{
		size_t i,k;
		const psrTermInfoList_t *term_lst;
		AR_ASSERT(grammar != NULL);

		term_lst = Parser_GetTermList(grammar);

		for(i = 0; i < term_lst->count; ++i)
		{
				psrTermInfo_t *term;

				term = &term_lst->lst[i];
				((psrSymb_t*)term->term)->spec_id = i;
		}



		for(i = 0; i < grammar->count; ++i)
		{
				const psrRule_t *rule = grammar->rules[i];
				
				for(k = 0; k < rule->body.count; ++k)
				{
						const psrSymb_t *symb = rule->body.lst[k];

						if(symb->type == PARSER_TERM && !Parser_IsBuildInSymbol(symb))
						{
								((psrSymb_t*)symb)->spec_id = Parser_IndexOfTermInfoListByName(term_lst, symb->name);
								AR_ASSERT(symb->spec_id != -1);
						}
				}
		}

}


int_t							Parser_GetTermSpecID(const psrGrammar_t *grammar, const psrSymb_t *symb)
{
		int_t idx;
		const psrTermInfoList_t *term_lst;
		AR_ASSERT(grammar != NULL && symb != NULL);

		term_lst = Parser_GetTermList(grammar);
		if(Parser_IsBuildInSymbol(symb))
		{
				idx = Parser_IndexOfTermInfoListByName(term_lst, symb->name);
		}else
		{
				idx = (int_t)symb->spec_id;
		}
		AR_ASSERT(idx != -1);
		return idx;

}


const psrSymb_t*		Parser_GetSymbFromGrammarByName(const psrGrammar_t *grammar, const wchar_t *name)
{
		
		size_t i,k;
		AR_ASSERT(grammar != NULL && name != NULL);
		
		
		for(i = 0; i < grammar->term_list.count; ++i)
		{
				const psrSymb_t *term = grammar->term_list.lst[i].term;
				if(AR_wcscmp(term->name, name) == 0)
				{
						return term;
				}
		}

		for(i = 0; i < grammar->count; ++i)
		{
				
				const psrRule_t	*rule = grammar->rules[i];
				const psrSymb_t *symb = rule->head;

				if(AR_wcscmp(symb->name, name) == 0)
				{
						return symb;
				}

				for(k = 0; k < rule->body.count; ++k)
				{
						symb = rule->body.lst[k];
						if(AR_wcscmp(symb->name, name) == 0)
						{
								return symb;
						}
				}
		}
		return NULL;
}





const psrRule_t*		Parser_GetStartRule(const psrGrammar_t *grammar)
{
		AR_ASSERT(grammar != NULL && grammar->count > 0);
		return grammar->rules[0];
}


arStatus_t				Parser_SetStartRule(psrGrammar_t *grammar, const wchar_t *rule_name)
{
		psrRule_t *start = grammar->rules[0];
		const psrSymb_t *lhs;
		size_t i;
		AR_ASSERT(grammar != NULL && grammar->count > 0 && rule_name != NULL);

		if(Parser_GetTermSymbInfoByName(grammar, rule_name) != NULL)
		{
				return AR_S_NO;
		}

		if(AR_wcscmp(PARSER_StartSymb->name, rule_name) == 0)
		{
				return AR_S_NO;
		}

		lhs = NULL;

		for(i = 0; i < grammar->count; ++i)
		{
				AR_ASSERT(rule_name != NULL && grammar->rules[i]->head->name != NULL);

				if(AR_wcscmp(rule_name, grammar->rules[i]->head->name) == 0)
				{
						lhs = Parser_CopyNewSymb(grammar->rules[i]->head);

						if(lhs == NULL)
						{
								return AR_E_NOMEM;
						}

						break;
				}
		}

		if(lhs == NULL)
		{
				return AR_S_NO;
		}


		AR_ASSERT(grammar->count > 1);
		AR_ASSERT(start != NULL && start->body.count > 0);

		Parser_DestroySymb(start->body.lst[0]);
		start->body.lst[0] = lhs;
		lhs = NULL;

		return AR_S_YES;
}




const psrTermInfo_t* Parser_GetRulePrecAssocInfo(const psrGrammar_t *grammar, const psrRule_t *rule)
{
		AR_ASSERT(grammar != NULL && rule != NULL && rule->prec_tok != NULL);
		return Parser_FindTermByName((psrTermInfoList_t*)&grammar->term_list, rule->prec_tok);

}

psrTermInfo_t*	Parser_GetTermSymbInfo(const psrGrammar_t	*grammar, const psrSymb_t *term)
{
		AR_ASSERT(grammar != NULL && term != NULL && term->type == PARSER_TERM);
		return  Parser_FindTermByName((psrTermInfoList_t*)&grammar->term_list, term->name);
		
}

psrTermInfo_t*			Parser_GetTermSymbInfoByName(const psrGrammar_t	*grammar, const wchar_t *name)
{
		AR_ASSERT(grammar != NULL && name != NULL);

		return  Parser_FindTermByName((psrTermInfoList_t*)&grammar->term_list, name);

}

psrTermInfo_t*			Parser_GetTermSymbInfoByValue(const psrGrammar_t	*grammar, size_t val)
{
		AR_ASSERT(grammar != NULL);
		return Parser_FindTermByValue((psrTermInfoList_t*)&grammar->term_list, val);
}



arStatus_t			Parser_CheckIsValidGrammar(const psrGrammar_t *grammar, arIOCtx_t *io_ctx)
{
		size_t i,j,k;
		bool_t result;
		const psrSymbList_t *lst;
		bool_t	*mark_tbl; 
		AR_ASSERT(grammar != NULL);
		
		if(grammar->count < 2)/*Start和输入的第一个产生式一定>=2*/
		{
				if(io_ctx)
				{
						AR_printf_ctx(io_ctx, L"Grammar Error : empty grammar!\r\n");
				}
				return AR_S_NO;
		}

		lst = Parser_GetSymbList(grammar);
		AR_ASSERT(lst != NULL);

		mark_tbl = AR_NEWARR0(bool_t, lst->count * lst->count);/*用mark_tbl记录此错误是否已经报告过了*/

		if(mark_tbl == NULL)
		{
				
				return AR_E_NOMEM;
		}


		result = true;
		for(i = 0; i < grammar->count; ++i)/*每一条产生式*/
		{
				const psrRule_t *rule;
				rule = grammar->rules[i];

				for(j = 0; j < rule->body.count; ++j)/*每一个符号*/
				{
						const psrSymb_t *symb;
						symb = rule->body.lst[j];

						if(symb->type == PARSER_NONTERM)		
						{
								bool_t is_ok;
								is_ok = false;
								for(k = 0; !is_ok && k < grammar->count; ++k)/*检查这里引用的非终结符symb是否存有定义*/
								{
										if(Parser_CompSymb(symb, grammar->rules[k]->head) == 0)
										{
												is_ok = true;
										}
								}

								if(!is_ok)/*如果没定义，则报错*/
								{
										size_t h,s;
										h = (size_t)Parser_FindFromSymbList(lst, rule->head);
										s = (size_t)Parser_FindFromSymbList(lst, symb);

										if(!mark_tbl[AR_TBL_IDX_R(h,s,lst->count)])
										{
												if(io_ctx)
												{
														AR_printf_ctx(io_ctx, L"Grammar Error : The rule <%ls> not exist in this grammar <%ls>\r\n", symb->name, rule->head->name);
												}

												mark_tbl[AR_TBL_IDX_R(h,s,lst->count)] = true;
										}
										result = false;
								}
						}

				}
		}


		AR_DEL(mark_tbl);
		mark_tbl = NULL;


		for(i = 0; i < lst->count; ++i)/*此部分检查非终结符是否被引用过*/
		{
				const psrSymb_t *symb;
				bool_t is_ok;
				symb = lst->lst[i];
				is_ok = false;
				
				if(Parser_IsBuildInSymbol(symb) ||	symb->type == PARSER_TERM)
				{
						continue;
				}

				for(k = 0; !is_ok && k < grammar->count; ++k)
				{
						const psrRule_t *rule;
						rule = grammar->rules[k];

						if(Parser_CompSymb(rule->head, symb) == 0)/*自己引用自己不算*/
						{
								continue;
						}
						
						for(j = 0; j < rule->body.count; ++j)
						{
								if(Parser_CompSymb(rule->body.lst[j], symb) == 0)
								{
										is_ok = true;
										break;
								}
						}
				}

				if(!is_ok)
				{
						if(io_ctx)
						{
								AR_printf_ctx((arIOCtx_t*)io_ctx,L"Grammar Warning : The rule <%ls> is declared but never used\r\n", symb->name);
						}
				}
		}

		return result ? AR_S_YES : AR_S_NO;
}

/************************************************************************************************************************************/



/*
firstset求法为，例如A->X(0)...X(n-1);
设First(Term) = {Term}; First(Epsilon) = {Epsilon}; i = 0;
如果First(X(i))存在{Epsilon}，则 First(A) += (First(X(i) - {Epsilon}); 如果i == n-1，则First(A) += {Epsilon}，本次循环终止；
如果不存在{Epsilon}，则循环终止；

因为每次都会处理至少一个符号，所以能确保循环终止，除非无任何符号加入到First集合中(changed == False);
*/
arStatus_t					Parser_CalcFirstSet(const psrGrammar_t *grammar, psrSymbMap_t *first_set)
{
		size_t i;
		bool_t changed;
		const psrSymbList_t		*lst;
		const psrSymb_t			*key;
		arStatus_t status;
		AR_ASSERT(grammar != NULL && first_set != NULL && grammar->count > 1);
		
		lst = Parser_GetSymbList(grammar);
		AR_ASSERT(lst != NULL);
		


		for(i = 0; i < lst->count; ++i)
		{
				key = lst->lst[i];
				if(key->type == PARSER_NONTERM)
				{
						status = Parser_InsertToSymbMap(first_set, key, NULL);
				}else
				{
						status = Parser_InsertToSymbMap(first_set, key, key);
				}

				if(status == AR_S_YES || status == AR_S_NO)
				{

				}else
				{
						return status;
				}
		}
		
		/*changed = false; */
		
		/*首先计算哪个非终结符可以推导出空串Epsilon*/
		do{
				changed = false;

				for(i = 0; i < grammar->count; ++i)
				{
						psrMapRec_t *rec = NULL;
						size_t k = 0;
						psrRule_t *rule = grammar->rules[i];
						rec= Parser_GetSymbolFromSymbMap(first_set, rule->head);
						
						AR_ASSERT(rec != NULL);

						if(rec->can_empty)
						{
								continue;
						}
						
						for(k = 0; k < rule->body.count; ++k)
						{
								const psrSymb_t *symb = NULL;
								const psrMapRec_t *tmp_rec = NULL;

								symb = rule->body.lst[k];
								if(symb->type == PARSER_TERM)
								{
										break;
								}

								tmp_rec= Parser_GetSymbolFromSymbMap(first_set, symb);
								if(!tmp_rec->can_empty)
								{
										break;
								}
						}

						if(k == rule->body.count)/*如果产生式体中无任何符号或所有符号均可以推导出空串，则此产生式头被认为可推导出空*/
						{
								rec->can_empty = true;
								changed = true;
						}
				}

		}while(changed);


		do{
				const psrSymb_t *s1, *s2;
				changed = false;

				for(i = 0; i < grammar->count; ++i)
				{
						const psrRule_t *rule;
						psrMapRec_t *rec = NULL;
						size_t k;
						rule = grammar->rules[i];

						s1 = rule->head;
						rec= Parser_GetSymbolFromSymbMap(first_set, s1);


						for(k = 0; k < rule->body.count; ++k)
						{
								s2 = rule->body.lst[k];/*产生式体中第k个符号*/
								
								if(s2->type == PARSER_TERM)
								{
										/*当前产生式体中存在终结符，则将其加入后终止循环*/
										status = Parser_InsertToSymbList_Unique(&rec->lst, s2);
										
										if(status == AR_S_YES)
										{
												changed = true;
										}else if(status == AR_S_NO)/*证明s2已经在rec->lst中了*/
										{
										}else	/*错误，内存分配失败等*/
										{
												return status;
										}

										break;
								}else if(Parser_CompSymb(s1, s2) == 0)/*非终结符，且与产生式头相同的符号*/
								{
										if(!rec->can_empty)/*如果当前产生式头不为空，则终止循环*/
										{
												break;
										}
								
								}else	/*非终结符，且与产生式头不同*/
								{
										const psrMapRec_t *rec2 = NULL;
										size_t x;
										rec2 = Parser_GetSymbolFromSymbMap(first_set, s2);
										/*将当前非终结符号的所有first符号加入到当前产生式头的first-set中*/
										
										for(x = 0; x < rec2->lst.count; ++x)
										{
												status = Parser_InsertToSymbList_Unique(&rec->lst, rec2->lst.lst[x]);
												
												if(status == AR_S_YES)/*改变了符号非终结符s1的first集合*/
												{
														changed = true;

												}else if(status == AR_S_NO) /*证明rec2->lst.lst[x]已经在rec->lst中了*/
												{

												}else	/*错误，内存分配失败等*/
												{
														return status;
												}
										}
										/*如果当前符号不可导出空串则终止循环*/
										if(!rec2->can_empty)
										{
												break;
										}
								}

						}
				}
		}while(changed);

		return AR_S_YES;
}



/*
FollowSet的求法为: 例如A->X(0)...X(n-1);
设i = 0->n-1, Follow(NULL)= {Epsilon};
如果X(i)为非终结符,则要对X(j)->X(n)循环检测,设j = i+1 && j < n;
如果First(X(j))不包含{Epsilon},则Follow(X(i)) += First(X(j)，循环结束，否则
j < n-1:Follow(X(i)) += (First(X(j)) - {Epsilon})，循环继续;
j == n-1:Follow(X(i)) += (First(X(j)) - {Epsilon})，循环结束，并将Follow(X(i) += Follow(A);
注意，当i == n-1时，Follow(X(i)) += Follow(A);,因为Follow(NULL)= {Epsilon};
*/


arStatus_t				Parser_CalcFollowSet(const psrGrammar_t *grammar, psrSymbMap_t *follow_set, const psrSymbMap_t *first_set)
{
		size_t i;
		bool_t changed;
		const psrSymbList_t *lst;
		psrMapRec_t *rec1 = NULL, *rec2 = NULL;
		arStatus_t status;
		AR_ASSERT(grammar != NULL && grammar->count > 1 && follow_set != NULL && first_set != NULL);

		status = AR_S_YES;

		changed = true;
		
		lst = Parser_GetSymbList(grammar);
		AR_ASSERT(lst != NULL);

		

		for(i = 0; i < lst->count; i++)/*初始化所有非终结符follow集合，并设置每个非终结符是否可空，从first集合得到*/
		{
				const psrSymb_t *key = lst->lst[i];

				if(key->type == PARSER_NONTERM)
				{
						status = Parser_InsertToSymbMap(follow_set, key, NULL);

						if(status == AR_S_YES || status == AR_S_NO)
						{

						}else/*内存分配失败*/
						{
								return status;
						}

						rec1 = Parser_GetSymbolFromSymbMap(first_set, key);
						rec2 = Parser_GetSymbolFromSymbMap(follow_set, key);
						rec2->can_empty = rec1->can_empty;
				}
		}

		/*$一定在产生式start 中*/
		status = Parser_InsertToSymbMap(follow_set, PARSER_StartSymb, PARSER_EOISymb);
		
		if(status == AR_S_YES || status == AR_S_NO)
		{
				
		}else/*内存分配失败*/
		{
				return status;
		}
		

		do{
				changed = false;
				
				for(i = 0; i < grammar->count; ++i)/*对每一条产生式*/
				{
						const psrRule_t *rule;
						const psrMapRec_t *head_follow;
						size_t k;
						rule = grammar->rules[i];

						head_follow = Parser_GetSymbolFromSymbMap(follow_set,rule->head);/*grammar->head[i]所对应的follow集合*/
						
						for(k = 0; k < rule->body.count; ++k)
						{
								const psrSymb_t *key;
								size_t next_idx;
								key = rule->body.lst[k];
								/*终结符无follow-set*/
								
								if(key->type == PARSER_TERM)
								{
										continue;
								}

								next_idx = k + 1;
								
								for(next_idx = k + 1; next_idx < rule->body.count; ++next_idx)
								{
										const psrSymb_t *next = NULL;
										const psrMapRec_t *first_rec;
										psrMapRec_t *rec_tmp = NULL;
										size_t x;
										
										next = Parser_IndexOfSymbList(&rule->body, next_idx);/*next为key之后的符号*/

										first_rec = Parser_GetSymbolFromSymbMap(first_set, next);/*next的first-set*/

										rec_tmp  = Parser_GetSymbolFromSymbMap(follow_set, key);/*key的follow-set*/

										/*将key之后的符号next的first-set加入到key的follow-set中*/
										for(x = 0; first_rec && x < first_rec->lst.count; ++x)
										{
												const psrSymb_t *f_symb;
												f_symb = first_rec->lst.lst[x];
												AR_ASSERT(f_symb->type == PARSER_TERM);				/*first不可能为非终结符*/

												status = Parser_InsertToSymbList_Unique(&rec_tmp->lst, f_symb);

												if(status == AR_S_YES)
												{
														changed = true;	/*任何一步的改动都需要重新计算follow集合*/
												
												}else if(status == AR_S_NO)
												{

												}else	/*内存分配失败*/
												{
														return status;
												}
										}
										/*如果next不可导出空串，则循环终止*/
										if(!first_rec->can_empty)
										{
												break;
										}
								}
								
								if(next_idx == rule->body.count)/*如果key为当前产生式最后一个符号或key之后的所有符号都可导出空串*/
								{
										/*则将产生式头的follow-set加入到符号key的follow-set中*/
										size_t x;
										psrMapRec_t *rec_tmp = Parser_GetSymbolFromSymbMap(follow_set, key);
										
										for(x = 0; x < head_follow->lst.count; ++x)
										{
												status = Parser_InsertToSymbList_Unique(&rec_tmp->lst,head_follow->lst.lst[x]);

												if(status == AR_S_YES)
												{
														changed = true;	/*任何一步的改动都需要重新计算follow集合*/
												}else if(status == AR_S_NO)
												{

												}else	/*AR_E_NOMEM*/
												{
														return status;
												}
										}
								}
						}
				}
		}while(changed);

		return AR_S_YES;
}














/*****************************************************下面为测试用代码*******************************************/





#define __CHECK_RET_VAL(_call_stmt)						\
		do{												\
				arStatus_t status = _call_stmt;			\
				if(status != AR_S_YES)					\
				{										\
						return status;					\
				}										\
		}while(0)


arStatus_t			Parser_PrintGrammar(const psrGrammar_t *grammar, arString_t *str)
{
		size_t i;
		

		__CHECK_RET_VAL(AR_AppendFormatString(str,L"Rule:\r\n"));

		for(i = 0; i < grammar->count; ++i)
		{
				const psrRule_t *rule;
				rule = grammar->rules[i];
				
				__CHECK_RET_VAL(Parser_PrintSymbol(rule->head, str));
				__CHECK_RET_VAL(AR_AppendString(str, L"\t:\t"));
				__CHECK_RET_VAL(Parser_PrintSymbolList(&rule->body, str));
				__CHECK_RET_VAL(AR_AppendString(str, L"\t\t"));
				__CHECK_RET_VAL(Parser_PrintSymbol(rule->head, str));
				
				{
						const psrTermInfo_t *info;
						AR_ASSERT(rule->prec_tok != NULL);
						info = Parser_FindTermByName((psrTermInfoList_t*)&grammar->term_list, rule->prec_tok);
						AR_ASSERT(info != NULL);
						__CHECK_RET_VAL(AR_AppendFormatString(str, L" prec = %qd assoc = %qd prec_tok = %ls", (uint_64_t)info->prec, (uint_64_t)info->assoc, info->term->name));
				}
				
				__CHECK_RET_VAL(AR_AppendString(str, L"\r\n"));
		}
		
		
		__CHECK_RET_VAL(AR_AppendString(str, L"---------------------------------------------------------------------\r\n"));
		__CHECK_RET_VAL(AR_AppendString(str, L"Term Set:\r\n"));
		
		

		for(i = 0; i < grammar->term_list.count; ++i)
		{
				size_t v;
				__CHECK_RET_VAL(Parser_PrintSymbol(grammar->term_list.lst[i].term, str));
				
				v = (size_t)Parser_GetTermSymbInfoByName(grammar,grammar->term_list.lst[i].term->name)->val;

				__CHECK_RET_VAL(AR_AppendFormatString(str, L": %Iu\r\n",  v));
		}
		

		__CHECK_RET_VAL(AR_AppendString(str, L"---------------------------------------------------------------------\r\n"));
		__CHECK_RET_VAL(AR_AppendString(str, L"Symbol List:\r\n"));
		
		
		__CHECK_RET_VAL(Parser_PrintSymbolList(Parser_GetSymbList(grammar), str));
		__CHECK_RET_VAL(AR_AppendString(str, L"\r\n\r\n"));

		return AR_S_YES;
}




AR_NAMESPACE_END












