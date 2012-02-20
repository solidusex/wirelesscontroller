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

#include "lex.h"
#include "rgx.h"



AR_NAMESPACE_BEGIN




struct __prog_set_tag
{
		rgxProg_t						**prog;
		lexAction_t						*action;
		size_t							count;
		size_t							cap;
};

lexProgSet_t* Lex_CreateProgSet()
{
		lexProgSet_t *res;
		res = AR_NEW0(lexProgSet_t);
		

		return res;
}


void Lex_ClearProgSet(lexProgSet_t *set)
{
		size_t i;
		AR_ASSERT(set != NULL);

		for(i = 0; i < set->count; ++i)
		{
				RGX_UnInitProg(set->prog[i]);
				AR_DEL(set->prog[i]);
		}

		set->count = 0;
}


void		Lex_DestroyProgSet(lexProgSet_t *set)
{

		if(set)
		{
				Lex_ClearProgSet(set);

				if(set->prog)AR_DEL(set->prog);
				if(set->action)AR_DEL(set->action);
				AR_DEL(set);
		}
}

arStatus_t Lex_InserToProgSet(lexProgSet_t *set, rgxProg_t *prog, const lexAction_t *act)
{
		AR_ASSERT(set != NULL && prog != NULL && act != NULL);

		if(set->count == set->cap)
		{
				size_t new_cap;
				rgxProg_t **new_progs;
				lexAction_t *new_acts;

				new_cap = (set->cap + 1)*2;
				new_progs = AR_NEWARR(rgxProg_t*, new_cap);
				new_acts = AR_NEWARR(lexAction_t, new_cap);
				if(new_progs == NULL || new_acts == NULL)
				{
						if(new_progs)
						{
								AR_DEL(new_progs);
								new_progs = NULL;
						}

						if(new_acts == NULL)
						{
								AR_DEL(new_acts);
								new_acts = NULL;
						}
						return AR_E_NOMEM;
				}

				AR_memcpy(new_progs, set->prog, set->count * sizeof(rgxProg_t*));
				AR_memcpy(new_acts, set->action, set->count * sizeof(lexAction_t));

				AR_DEL(set->prog);
				AR_DEL(set->action);

				set->cap = new_cap;
				set->prog = new_progs;
				set->action = new_acts;
		}

		set->prog[set->count] = prog;
		set->action[set->count] = *act;
		set->count++;
		return AR_S_YES;
}


static void __exch_set(lexProgSet_t *set, int_t i,int_t j)
{
		rgxProg_t		*prog;
		lexAction_t		act;
		AR_ASSERT(set != NULL);

		prog = set->prog[i];
		set->prog[i] = set->prog[j];
		set->prog[j] = prog;


		act = set->action[i];
		set->action[i] = set->action[j];
		set->action[j] = act;
}

arStatus_t	Lex_RemoveFromProgSet(lexProgSet_t *set, size_t value)
{
		int_t l,r,cnt;
		bool_t res = false;
		AR_ASSERT(set != NULL);

		l = 0; r = (int_t)set->count - (int_t)1, cnt = (int_t)set->count;

		while(l <= r)
		{
				if(set->action[l].value == value)
				{
						__exch_set(set, l,r);
						r--;
						res = true;
				}
				l++;
		}


		for(l = r + 1; l < (int_t)set->count; ++l)
		{
				rgxProg_t *prog = set->prog[l];
				set->prog[l] = NULL;
				RGX_UnInitProg(prog);
				AR_DEL(prog);
				cnt--;
		}
		AR_ASSERT(cnt >= 0);

		set->count = (size_t)cnt;

		return res ? AR_S_YES : AR_S_NO;
}



void Lex_SortProgSet(lexProgSet_t *set)
{
		int_t i,j;



		for(i = (int_t)set->count - 1; i > 0; --i)
		{
				if(set->action[i].priority > set->action[i-1].priority)
				{
						__exch_set(set, i, i - 1);
				}
		}
		
		for(i = 1; i < (int_t)set->count; ++i)
		{
				for(j = i; j > 0 && set->action[j].priority > set->action[j-1].priority; --j)
				{
						__exch_set(set, j, j - 1);
				}
		}
}

/*********************************lexMatch_t***************************/


#define __ALL_FLAGS		(LEX_IGNORE_CASE|LEX_SINGLE_LINE)

void			Lex_MatchFlags(lexMatch_t *pmatch, uint_t flags, bool_t is_on)
{
		AR_ASSERT(pmatch != NULL);
		flags &= __ALL_FLAGS;
		if(is_on)
		{
				pmatch->flags |= flags;
		}else
		{
				pmatch->flags &= ~flags;
		}
}

void			Lex_MatchClearFlags(lexMatch_t *pmatch)
{
		AR_ASSERT(pmatch != NULL);
		pmatch->flags = 0;
}

#undef __ALL_FLAGS



void Lex_ResetInput(lexMatch_t *pmatch, const wchar_t *input)
{
		AR_ASSERT(pmatch != NULL && input != NULL);
		pmatch->input = input;
		pmatch->next = pmatch->input;
		pmatch->is_ok = true;
		pmatch->col = pmatch->line = 0;
		pmatch->next_action = RGX_ACT_NOACTION;
}


void	Lex_ClearInput(lexMatch_t *pmatch)
{
		Lex_ResetInput(pmatch, L"");
}


void Lex_ResetMatchState(lexMatch_t *pmatch)
{
		AR_ASSERT(pmatch != NULL && pmatch->input != NULL);
		pmatch->is_ok = true;
		pmatch->col = pmatch->line = 0;
		pmatch->next_action = RGX_ACT_NOACTION;
		pmatch->next = pmatch->input;

}








lexMatch_t*		Lex_CreateMatch(const lex_t *lex)
{
		size_t i;
		lexMatch_t		*pmatch;
		AR_ASSERT(lex != NULL);
		
		pmatch = AR_NEW(lexMatch_t);

		if(pmatch == NULL)
		{
				return NULL;
		}

		AR_memset(pmatch, 0, sizeof(*pmatch));


		pmatch->input = L"";
		pmatch->next = pmatch->input;
		pmatch->is_ok = true;
		pmatch->flags = 0;
		
		pmatch->prog_set = Lex_CreateProgSet();

		if(pmatch->prog_set == NULL)
		{
				AR_DEL(pmatch);
				return NULL;
		}

		

		for(i = 0; i < lex->rule_set.count; ++i)
		{
				rgxProg_t *prog;
				prog = AR_NEW(rgxProg_t);

				if(prog == NULL)
				{
						Lex_DestroyMatch(pmatch);
						return NULL;
				}
		

				RGX_InitProg(prog);

				if(RGX_Compile(prog, lex->rule_set.nodes[i]) != AR_S_YES)
				{
						RGX_UnInitProg(prog);
						AR_DEL(prog);
						Lex_DestroyMatch(pmatch);
						return NULL;
				}
				
				if(Lex_InserToProgSet(pmatch->prog_set, prog, &lex->rule_set.action[i]) != AR_S_YES)
				{
						RGX_UnInitProg(prog);
						AR_DEL(prog);
						Lex_DestroyMatch(pmatch);
						return NULL;
				}
		}

		Lex_SortProgSet(pmatch->prog_set);
		
		return pmatch;
}



void Lex_DestroyMatch(lexMatch_t *pmatch)
{
		if(pmatch != NULL)
		{
				/*if(pmatch->input)AR_DEL(pmatch->input);*/
				Lex_DestroyProgSet(pmatch->prog_set);
				/*AR_memset(pmatch, 0, sizeof(*pmatch));*/
				AR_DEL(pmatch);
		}
}



const wchar_t* Lex_GetNextInput(const lexMatch_t *match)
{
		AR_ASSERT(match != NULL);
		return match->next;
}

arStatus_t	Lex_IsError(const lexMatch_t *match)
{
		AR_ASSERT(match != NULL);
		return !match->is_ok ? AR_S_YES : AR_S_NO;
}

void	Lex_ClearError(lexMatch_t *match)
{
		AR_ASSERT(match != NULL);
		match->is_ok = true;
}






void	Lex_Skip(lexMatch_t *pmatch)
{
		AR_ASSERT(pmatch != NULL && pmatch->next != NULL);

		
		while(*pmatch->next && !AR_iswspace(*pmatch->next))
		{
				pmatch->next++;
				pmatch->col++;
		}


		while(*pmatch->next && AR_iswspace(*pmatch->next))
		{
				if(Lex_IsLineTerminator(*pmatch->next))
				{
						wchar_t next_c;
						
						pmatch->line++;
						pmatch->col = 0;
						
						next_c = *(pmatch->next + 1);
						if(*pmatch->next == AR_LEX_CR && next_c == AR_LEX_LF)
						{
								pmatch->next++;
						}

						pmatch->next_action &= ~RGX_ACT_INCLINE;
				}else
				{
						pmatch->col++;
				}
				pmatch->next++;
		}
}




void			Lex_SkipTo(lexMatch_t *pmatch, const wchar_t *tok)
{
		const wchar_t *next;
		AR_ASSERT(pmatch != NULL && pmatch->next != NULL);
		next = AR_wcsstr(pmatch->next, tok);

		if(next == NULL)
		{
				while(*pmatch->next != L'\0')
				{
						if(Lex_IsLineTerminator(*pmatch->next))
						{
								wchar_t next_c;
								pmatch->line++;
								pmatch->col = 0;
								
								next_c = *(pmatch->next + 1);
								if(*pmatch->next == AR_LEX_CR && next_c == AR_LEX_LF)
								{
										pmatch->next++;
								}

								pmatch->next_action &= ~RGX_ACT_INCLINE;
						}else
						{
								pmatch->col++;
						}
						pmatch->next++;
				}
		}else
		{
				while(pmatch->next != next)
				{
						if(Lex_IsLineTerminator(*pmatch->next))
						{
								wchar_t next_c;
								pmatch->line++;
								pmatch->col = 0;
							
								next_c = *(pmatch->next + 1);
								if(*pmatch->next == AR_LEX_CR && next_c == AR_LEX_LF)
								{
										pmatch->next++;
								}

								pmatch->next_action &= ~RGX_ACT_INCLINE;
						}else
						{
								pmatch->col++;
						}

						pmatch->next++;
				}
		}

		
}

arStatus_t		Lex_TrySkipTo(lexMatch_t *pmatch, const wchar_t *tok)
{
		const wchar_t *next;
		AR_ASSERT(pmatch != NULL && pmatch->next != NULL);
		next = AR_wcsstr(pmatch->next, tok);
		
		if(next == NULL)
		{
				return AR_S_NO;
		}else
		{
				Lex_SkipTo(pmatch, tok);
				return AR_S_YES;
		}

}


void			Lex_SkipN(lexMatch_t *pmatch, size_t nchar)
{
		size_t i;
		AR_ASSERT(pmatch != NULL && pmatch->next != NULL);
		
		for(i = 0; *pmatch->next != L'\0' && i < nchar; ++i)
		{
				if(Lex_IsLineTerminator(*pmatch->next))
				{
						wchar_t next_c;
						pmatch->line++;
						pmatch->col = 0;

						next_c = *(pmatch->next + 1);

						if(*pmatch->next == AR_LEX_CR && next_c == AR_LEX_LF)
						{
								pmatch->next++;
						}

						pmatch->next_action &= ~RGX_ACT_INCLINE;
				}else
				{
						pmatch->col++;
				}
				pmatch->next++;
		}
}


/***********************************************************************************************************************************/



void			Lex_PutBack(lexMatch_t *pmatch, const lexToken_t *tok)
{
		AR_ASSERT(pmatch !=  NULL && tok != NULL && tok->str != NULL);

#if defined(AR_DEBUG)
		{
				const wchar_t *beg = pmatch->input, *end = pmatch->input + AR_wcslen(pmatch->input);
				AR_ASSERT(tok->str >= beg && tok->str < end);
		}
#endif
		pmatch->next = tok->str;
		pmatch->line = tok->line;
		pmatch->col = tok->col;
		pmatch->next_action = 0;
}




void			Lex_MatchGetCoordinate(const lexMatch_t *pmatch, size_t *index, size_t *line, size_t *col)
{
		AR_ASSERT(pmatch != NULL);
		if(index)*index = pmatch->next - pmatch->input;
		if(line)*line = pmatch->line;
		if(col) *col = pmatch->col;
}






#define LEX_MAX_EMPTY_MATCH_CNT 1

arStatus_t Lex_Match(lexMatch_t *match, lexToken_t *tok)
{
		arStatus_t status;
		size_t i;
		size_t empty_match_cnt = 0;

		AR_ASSERT(match != NULL && tok != NULL);

		status = AR_S_YES;
REMATCH:
		if(empty_match_cnt > LEX_MAX_EMPTY_MATCH_CNT)
		{
				/*
				AR_printf_ctx(&match->io_ctx, L"%ls\r\n", L"Invalid empty pattern\r\n");
				AR_ASSERT(false);
				*/

				//AR_CHECK(false, L"%ls\r\n", L"Invalid empty pattern\r\n");
				
				return AR_E_LEXMPTYMATCH;
		}


		for(i = 0; i < match->prog_set->count; ++i)
		{
				status = RGX_Match(match->prog_set->prog[i], match, tok);

				if(status == AR_S_YES)
				{
						/*
						{
								arString_t *str = AR_CreateString();
								RGX_ProgToString(lex->prog_set->prog[i],str);
								AR_printf_ctx(&lex->io_ctx, L"Matched : %ls\r\n", AR_GetStringCString(str));
								AR_DestroyString(str);
						}
						*/

						if(match->prog_set->action[i].is_skip)
						{
								if(tok->count == 0)
								{
										empty_match_cnt++;
								}

								goto REMATCH;
						}else
						{
								if(tok->count > 0)
								{
										return AR_S_YES;
								}else
								{
										return AR_S_YES;
								}
						}
				}else if(status == AR_S_NO)
				{
						continue;
				}else
				{
						break;
				}
		}

		AR_ASSERT(status != AR_S_YES);
		match->is_ok = false;
		return status;
}







AR_NAMESPACE_END





