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




static void __add_thread(rgxThreadList_t *lst,  rgxThread_t thd, rgxProg_t *prog)
{
		AR_ASSERT(lst != NULL);
		
		if(prog->mark == thd.pc->mark)return;
		thd.pc->mark = prog->mark;

		switch(thd.pc->opcode)
		{
		case RGX_JMP_I:
		{
				AR_ASSERT(thd.pc->right == NULL);
				__add_thread(lst, RGX_BuildThread(thd.pc->left, thd.sp, thd.line, thd.col, thd.act), prog);
				break;
		}
		case RGX_BRANCH_I:
		{
				__add_thread(lst, RGX_BuildThread(thd.pc->left, thd.sp, thd.line, thd.col, thd.act), prog);
				__add_thread(lst, RGX_BuildThread(thd.pc->right, thd.sp, thd.line, thd.col, thd.act), prog);
				break;
		}
		case RGX_LOOP_BEG_I:
		case RGX_LOOP_END_I:
		case RGX_LOOKAHEAD_BEG_I:
		case RGX_LOOKAHEAD_END_I:
		case RGX_NOP_I:
		case RGX_CHAR_I:
		case RGX_BEGIN_I:
		case RGX_END_I:
		case RGX_LINE_BEGIN_I:
		case RGX_LINE_END_I:
		case RGX_ANY_CHAR_I:
		case RGX_MATCH_I:
		{
				RGX_InsertToThreadList(lst, thd);
				break;
		}
		default:
		{
				AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
				break;
		}
		}
}




#define IS_LINE_BEGIN(_sp, _input)		((_sp) == (_input) || (Lex_IsLineTerminator((_sp)[-1])))
#define IS_LINE_END(_sp)				(*(_sp) == L'\0' || (Lex_IsLineTerminator(*(_sp))))



static AR_INLINE void __check_is_newline(const wchar_t *sp, uint_32_t *pact, size_t *px, size_t *py)
{
		AR_ASSERT(sp != NULL && pact != NULL && px != NULL && py != NULL);

		if(Lex_IsLineTerminator(*sp))
		{																				
				if(*pact & RGX_ACT_INCLINE)
				{																		
						*py = 0;															
						*px += 1;
						*pact &= ~RGX_ACT_INCLINE;
				}else
				{
						wchar_t next_c = *(sp + 1);
						if(*sp == AR_LEX_CR && next_c == AR_LEX_LF) /*CR followed by LF*/
						{
								*py += 1;
								*pact |= RGX_ACT_INCLINE;
						}else
						{
								*py = 0;
								*px += 1;
						}
				}
		}else																			
		{
				*py += 1;
		}

}


#undef IS_NEW_LINE
#undef LF
#undef VT
#undef FF
#undef CR
#undef NEL
#undef LS
#undef PS


static arStatus_t  __loop(rgxProg_t *prog, const wchar_t **start_pos, size_t *px, size_t *py, uint_32_t *pact, lexMatch_t *match);
static arStatus_t  __lookahead(rgxProg_t *prog, const wchar_t *sp, lexMatch_t *match);



/*处理预搜索部分*/

static void __clear_for_lookahead(rgxProg_t *prog)
{		
		size_t k,l;
		AR_ASSERT(prog && prog->start != NULL);
		prog->mark = 0;

		for(k = 0, l = 1; l > 0; ++k)
		{
				if(prog->start[k].opcode == RGX_LOOKAHEAD_BEG_I)
				{
						l++;
				}else if(prog->start[k].opcode == RGX_LOOKAHEAD_END_I)
				{
						l--;
				}
				prog->start[k].mark = 0;
		}

		prog->mark = 0;
}



static arStatus_t  __lookahead(rgxProg_t *prog, const wchar_t *sp, lexMatch_t *match)
{
		rgxThreadList_t *curr, *next;
		rgxIns_t *pc;
		size_t i;
		const wchar_t *input_beg;
		arStatus_t status;
		AR_ASSERT(prog != NULL && sp != NULL && match != NULL);
		
		status = AR_S_NO;
		curr = RGX_CreateThreadList();
		next = RGX_CreateThreadList();

		if(curr == NULL || next == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}


		input_beg = match->input;
		

		


		prog->mark = 0;
		__clear_for_lookahead(prog);
		prog->mark++;
		__add_thread(curr, RGX_BuildThread(prog->start, sp,0,0, RGX_ACT_NOACTION), prog);

		for(;;)
		{
				if(curr->count == 0)
				{
						break;
				}
				
				prog->mark++;
				for(i = 0; i < curr->count; ++i)
				{
						pc = curr->lst[i].pc;
						sp = curr->lst[i].sp;
						
						switch(pc->opcode)
						{
						case RGX_CHAR_I:
						{
								bool_t is_ok = false;
								if(*sp != L'\0')
								{
										if(match->flags & LEX_IGNORE_CASE)
										{
												wchar_t lower = (wchar_t)AR_tolower(*sp), upper = (wchar_t)AR_towupper(*sp);
												
												if(lower >=  pc->range.beg && lower <= pc->range.end)
												{
														is_ok = true;
												}else if(upper >=  pc->range.beg && upper <= pc->range.end)
												{
														is_ok = true;
												}
										}else
										{
												is_ok = (*sp >= pc->range.beg && *sp <= pc->range.end);
										}
								}

								if(is_ok)
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp + 1, 0, 0, RGX_ACT_NOACTION), prog);
								}

								break;
						}
						case RGX_ANY_CHAR_I:
						{
								bool_t is_ok = false;

								if(*sp != L'\0')
								{
										if(match->flags & LEX_SINGLE_LINE)/*single line 可以匹配包含换行符号在内的所有字符*/
										{
												is_ok = true;
										}else
										{
												is_ok = !Lex_IsLineTerminator(*sp);
										}
								}

								if(is_ok)
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp + 1, 0, 0, RGX_ACT_NOACTION), prog);
								}
								break;
						}
						case RGX_BEGIN_I:
						{
								if(sp == input_beg)
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, 0, 0, RGX_ACT_NOACTION), prog);
								}
								/*--sp;*/
								break;
						}
						case RGX_END_I:
						{
								if(*sp == L'\0')
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, 0, 0, RGX_ACT_NOACTION), prog);
								}
								break;
						}
						case RGX_LINE_BEGIN_I:
						{
								if(IS_LINE_BEGIN(sp, match->input))
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, 0, 0, RGX_ACT_NOACTION), prog);
								}
								/*--sp;*/
								break;
						}
						case RGX_LINE_END_I:
						{
								if(IS_LINE_END(sp))
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, 0, 0, RGX_ACT_NOACTION), prog);
								}
								break;
						}
						case RGX_LOOP_BEG_I:
						{
								size_t loop_cnt;
								size_t i;
								arStatus_t is_ok = AR_S_YES;
								loop_cnt = pc->fix_count;
								
								for(i = 0; i < loop_cnt && is_ok == AR_S_YES; ++i)
								{
										size_t	x = 0,y = 0;
										uint_32_t act = RGX_ACT_NOACTION;
										rgxProg_t loop;
										loop.start = pc + 1;
										loop.pc = loop.start;
										loop.mark = 0;
										
										is_ok = __loop(&loop, &sp, &x, &y, &act,  match);
								}

								if(is_ok == AR_S_YES)/*匹配成功*/
								{
										__add_thread(next, RGX_BuildThread(pc->left, sp, 0, 0, RGX_ACT_NOACTION), prog);
								
								}else if(is_ok == AR_S_NO)/*匹配失败，则继续*/
								{

								}else					/*出现错误*/
								{
										status = is_ok;
										goto END_POINT;
								}
								

								break;
						}
						case RGX_LOOP_END_I:
						{

								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
						}
								break;
						case RGX_LOOKAHEAD_BEG_I:
						{
								arStatus_t is_ok;
								rgxProg_t lhd;
								
								is_ok = AR_S_YES;

								lhd.start = pc + 1;
								lhd.pc = lhd.start;
								lhd.mark = 0;
								
								/*__clear_ins_set(lhd.start);*/

								is_ok = __lookahead(&lhd, sp, match);

								if(is_ok == AR_S_YES)/*匹配搜索*/
								{
										if(pc->lookahead.negative)
										{

										}else
										{
												__add_thread(next, RGX_BuildThread(pc->left, sp, 0,0, RGX_ACT_NOACTION), prog);
										}

								}else if(is_ok == AR_S_NO)		/*匹配失败*/
								{
										if(pc->lookahead.negative)
										{
												__add_thread(next, RGX_BuildThread(pc->left, sp, 0,0, RGX_ACT_NOACTION), prog);
										}else
										{

										}
								}else							/*内部错误*/
								{
										status = is_ok;
										goto END_POINT;
								}
								
								break;
						}
						case RGX_LOOKAHEAD_END_I:
						{
								/*
										不论你前向预搜索什么，只要有一个走通了就OK
										例如a(?=(a|b|c|d))走通了哪个都算OK
								*/
								status = AR_S_YES;
								goto END_POINT;
								break;
						}
						case RGX_NOP_I:
						case RGX_MATCH_I:
						default:
						{
								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
								break;
						}
						}
				}
				RGX_SwapThreadList(curr, next);
				RGX_ClearThreadList(next);
		}

END_POINT:
		if(curr)
		{
				RGX_DestroyThreadList(curr);
				curr = NULL;
		}

		if(next)
		{
				RGX_DestroyThreadList(next);
				next = NULL;
		}
		return status;
}





/*处理定数循环部分*/

static void __clear_for_loop(rgxProg_t *prog)
{		
		size_t k,l;
		AR_ASSERT(prog && prog->start != NULL);
		prog->mark = 0;

		for(k = 0, l = 1; l > 0; ++k)
		{
				if(prog->start[k].opcode == RGX_LOOP_BEG_I)
				{
						l++;
				}else if(prog->start[k].opcode == RGX_LOOP_END_I)
				{
						l--;
				}
				prog->start[k].mark = 0;
		}

		prog->mark = 0;
}




static arStatus_t  __loop(rgxProg_t *prog, const wchar_t **start_pos, size_t *px, size_t *py, uint_32_t *pact, lexMatch_t *match)
{
		arStatus_t status;
		rgxThreadList_t *curr, *next;
		rgxIns_t				*pc;
		
		const wchar_t	*sp, *final_next;
		uint_32_t		act, final_act;
		size_t i,x,y, final_row, final_col;
		
		
		AR_ASSERT(prog != NULL && start_pos != NULL && *start_pos != NULL && px != NULL && py != NULL && pact != NULL && match != NULL);
		
		status = AR_S_NO;

		

		sp = *start_pos;
		x = *px;
		y = *py;
		act = *pact;
		final_row = x; final_col = y; final_next = NULL; final_act = RGX_ACT_NOACTION;


		curr = RGX_CreateThreadList();
		next = RGX_CreateThreadList();

		if(curr == NULL || next == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}


		__clear_for_loop(prog);
		
		
		prog->mark = 0;

		RGX_ClearThreadList(curr);
		RGX_ClearThreadList(next);


		prog->mark++;
		__add_thread(curr, RGX_BuildThread(prog->start, sp, x,y, act), prog);

		
		for(;;)
		{
				if(curr->count == 0)
				{
						break;
				}

				prog->mark++;
				
				for(i = 0; i < curr->count; ++i)
				{
						pc = curr->lst[i].pc;
						sp = curr->lst[i].sp;
						x = curr->lst[i].line;
						y = curr->lst[i].col;
						act = curr->lst[i].act;

						switch(pc->opcode)
						{
						case RGX_CHAR_I:
						{
								bool_t is_ok = false;
								if(*sp != L'\0')
								{
										if(match->flags & LEX_IGNORE_CASE)
										{
												wchar_t lower = (wchar_t)AR_tolower(*sp), upper = (wchar_t)AR_towupper(*sp);
												
												if(lower >=  pc->range.beg && lower <= pc->range.end)
												{
														is_ok = true;
												}else if(upper >=  pc->range.beg && upper <= pc->range.end)
												{
														is_ok = true;
												}
										}else
										{
												is_ok = (*sp >= pc->range.beg && *sp <= pc->range.end);
										}
								}

								if(is_ok)
								{
										__check_is_newline(sp, &act, &x, &y);
										sp++;
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_ANY_CHAR_I:
						{
								bool_t is_ok = false;

								if(*sp != L'\0')
								{
										if(match->flags & LEX_SINGLE_LINE)/*single line 可以匹配包含换行符号在内的所有字符*/
										{
												is_ok = true;
										}else
										{
												is_ok = !Lex_IsLineTerminator(*sp); 
										}
								}

								if(is_ok)
								{
										__check_is_newline(sp, &act, &x, &y);
										sp++;
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}

								break;
						}
						case RGX_BEGIN_I:
						{
								if(sp == match->input)
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_END_I:
						{
								if(*sp == L'\0')
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_LINE_BEGIN_I:
						{
								if(IS_LINE_BEGIN(sp, match->input))
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_LINE_END_I:
						{
								if(IS_LINE_END(sp))
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_LOOP_BEG_I:
						{
								
								size_t loop_cnt;
								size_t i;
								arStatus_t is_ok = AR_S_YES;
								
								loop_cnt = pc->fix_count;


								for(i = 0; i < loop_cnt && is_ok == AR_S_YES; ++i)
								{
										rgxProg_t loop;
										loop.start = pc + 1;
										loop.pc = loop.start;
										loop.mark = 0;
										is_ok = __loop(&loop, &sp, &x, &y, &act, match);
								}


								if(is_ok == AR_S_YES)
								{
										__add_thread(next, RGX_BuildThread(pc->left, sp, x,y, act), prog);
								}else if(is_ok == AR_S_NO)
								{
										
								}else
								{
										status = is_ok;
										goto END_POINT;
								}
								

								break;
						}
						case RGX_LOOP_END_I:
						{
								final_row = x;
								final_col = y;
								final_next = sp;
								final_act = act;
								status = AR_S_YES;
								goto BREAK_POINT;/*这一步决定了优先级为left most*/
						}
								break;
						case RGX_LOOKAHEAD_BEG_I:
						{
								rgxProg_t lhd;
								arStatus_t is_ok;

								is_ok = AR_S_YES;
								lhd.start = pc + 1;
								lhd.pc = lhd.start;
								lhd.mark = 0;

								is_ok = __lookahead(&lhd, sp, match);

								if(is_ok == AR_S_YES)/*匹配成功*/
								{
										if(pc->lookahead.negative)
										{

										}else
										{
												__add_thread(next, RGX_BuildThread(pc->left, sp, x,y, act), prog);
										}

								}else if(is_ok == AR_S_NO)/*匹配失败*/
								{
										if(pc->lookahead.negative)
										{
												__add_thread(next, RGX_BuildThread(pc->left, sp, x,y, act), prog);
										}else
										{

										}
								}else			/*内部错误*/
								{
										status = is_ok;
										goto END_POINT;
								}

								break;
						}
						case RGX_LOOKAHEAD_END_I:
						{
								AR_ASSERT(false);
								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
								break;
						}
						case RGX_MATCH_I:
						case RGX_NOP_I:
						default:
						{
								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
								break;
						}
						}
				}
		BREAK_POINT:
				RGX_SwapThreadList(curr, next);
				RGX_ClearThreadList(next);
		}
		
END_POINT:
		if(curr)
		{
				RGX_DestroyThreadList(curr);
				curr = NULL;
		}

		if(next)
		{
				RGX_DestroyThreadList(next);
				next = NULL;
		}

		if(status == AR_S_YES)
		{
				*py = final_col;
				*px = final_row;
				*pact = final_act;
				AR_ASSERT(final_next != NULL);
				*start_pos = final_next;
		}

		return status;
}




static arStatus_t __thompson(rgxProg_t *prog, lexMatch_t *match, lexToken_t *tok)
{
		arStatus_t status;
		rgxThreadList_t	*curr, *next;
		
		rgxIns_t		*pc;
		const wchar_t	*sp, *final_next;

		size_t i,x,y, final_row, final_col;
		uint_32_t		act, final_act;
		

		AR_ASSERT(prog != NULL && match->next != NULL && match->input != NULL);
		
		status = AR_S_NO;

		AR_memset(tok, 0, sizeof(*tok));

		for(i = 0; i < prog->count; ++i)
		{
				prog->start[i].mark = 0;
		}

		prog->mark = 0;
		
		if(prog->curr == NULL) 
		{
				prog->curr = RGX_CreateThreadList();
		}


		if(prog->next == NULL) 
		{
				prog->next = RGX_CreateThreadList();
		}


		if(prog->next == NULL || prog->curr == NULL)
		{
				if(prog->next)
				{
						RGX_DestroyThreadList(prog->next);
						prog->next = NULL;
				}

				if(prog->curr)
				{
						RGX_DestroyThreadList(prog->curr);
						prog->curr = NULL;
				}

				return AR_E_NOMEM;
		}


		curr = prog->curr;
		next = prog->next;
		
		RGX_ClearThreadList(curr);
		RGX_ClearThreadList(next);

		sp = match->next;
		x = match->line;
		y = match->col;
		act = match->next_action;

		final_row = 0; final_col = 0; final_next = NULL; final_act = RGX_ACT_NOACTION;

		prog->mark++;
		__add_thread(curr, RGX_BuildThread(prog->start, sp, x,y, act), prog);

		for(;;)
		{
				if(curr->count == 0)break;
				prog->mark++;
				
				for(i = 0; i < curr->count; ++i)
				{
						pc = curr->lst[i].pc;
						sp = curr->lst[i].sp;
						x = curr->lst[i].line;
						y = curr->lst[i].col;
						act = curr->lst[i].act;

						switch(pc->opcode)
						{
						case RGX_CHAR_I:
						{
								bool_t is_ok = false;
								if(*sp != L'\0')
								{
										if(match->flags & LEX_IGNORE_CASE)
										{
												wchar_t lower = (wchar_t)AR_tolower(*sp), upper = (wchar_t)AR_towupper(*sp);
												
												if(lower >=  pc->range.beg && lower <= pc->range.end)
												{
														is_ok = true;
												}else if(upper >=  pc->range.beg && upper <= pc->range.end)
												{
														is_ok = true;
												}
										}else
										{
												is_ok = (*sp >= pc->range.beg && *sp <= pc->range.end);
										}
								}

								if(is_ok)
								{
										__check_is_newline(sp, &act, &x, &y);

										sp++;
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_ANY_CHAR_I:
						{
								bool_t is_ok = false;

								if(*sp != L'\0')
								{
										if(match->flags & LEX_SINGLE_LINE)/*single line 可以匹配包含换行符号在内的所有字符*/
										{
												is_ok = true;
										}else
										{
												is_ok = !Lex_IsLineTerminator(*sp); 
										}
								}

								if(is_ok)
								{
										__check_is_newline(sp, &act, &x, &y);
										sp++;
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}

								break;
						}
						case RGX_BEGIN_I:
						{
								if(sp == match->input)
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_END_I:
						{
								if(*sp == L'\0')
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_LINE_BEGIN_I:
						{
								if(IS_LINE_BEGIN(sp, match->input))
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_LINE_END_I:
						{
								if(IS_LINE_END(sp))
								{
										__add_thread(next, RGX_BuildThread(pc + 1, sp, x,y, act), prog);
								}
								break;
						}
						case RGX_LOOP_BEG_I:
						{
								
								size_t loop_cnt;
								size_t i;
								arStatus_t is_ok = AR_S_YES;

								loop_cnt = pc->fix_count;
								

								
								for(i = 0; i < loop_cnt && is_ok == AR_S_YES; ++i)
								{
										rgxProg_t loop;
										loop.start = pc + 1;
										loop.pc = loop.start;
										loop.mark = 0;
										is_ok =  __loop(&loop, &sp, &x, &y, &act, match);
								}

								if(is_ok == AR_S_YES)/*匹配成功*/
								{
										__add_thread(next, RGX_BuildThread(pc->left, sp, x,y, act), prog);
								
								}else if(is_ok == AR_S_NO)/*匹配失败*/
								{
										
								}else	/*错误*/
								{
										status = is_ok;
										goto END_POINT;
								}
								

								break;
						}
						case RGX_LOOP_END_I:
						{
								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
						}
								break;
						case RGX_LOOKAHEAD_BEG_I:
						{
								rgxProg_t lhd;
								arStatus_t is_ok;

								is_ok = AR_S_YES;
								lhd.start = pc + 1;
								lhd.pc = lhd.start;
								lhd.mark = 0;

								is_ok = __lookahead(&lhd, sp, match);
								
								if(is_ok == AR_S_YES)
								{
										if(pc->lookahead.negative)
										{

										}else
										{
												__add_thread(next, RGX_BuildThread(pc->left, sp, x,y, act), prog);
										}

								}else if(is_ok == AR_S_NO)
								{
										if(pc->lookahead.negative)
										{
												__add_thread(next, RGX_BuildThread(pc->left, sp, x,y, act), prog);
										}else
										{

										}
								
								}else	/*错误*/
								{
										status = is_ok;
										goto END_POINT;
								}

								break;
						}
						case RGX_LOOKAHEAD_END_I:
						{
								AR_ASSERT(false);
								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
								break;
						}
						case RGX_MATCH_I:
						{
								tok->str = match->next;
								tok->index = match->next - match->input;
								tok->count = sp - match->next;
								tok->line = match->line;
								tok->col = match->col;
								tok->value = (size_t)pc->final;

								final_row = x;
								final_col = y;
								final_next = sp;
								final_act = act;
								status = AR_S_YES;

								goto BREAK_POINT;/*这一步决定了优先级为left most*/
								break;
						}
						case RGX_NOP_I:
						default:
						{
								AR_CHECK(false, L"Arsenal : regex exec error %hs\r\n", AR_FUNC_NAME);
								break;
						}
						}
				}
		BREAK_POINT:
				RGX_SwapThreadList(curr, next);
				RGX_ClearThreadList(next);
		}

END_POINT:
		if(status == AR_S_YES)
		{
				match->col = final_col;
				match->line = final_row;
				match->next = final_next;
				match->next_action = final_act;
		}
		return status;
}






arStatus_t RGX_Match(rgxProg_t *prog, lexMatch_t *match, lexToken_t *tok)
{

		AR_ASSERT(prog != NULL && match != NULL && tok != NULL);

		AR_ASSERT(match->input != NULL && match->next != NULL);

		if(!match->is_ok)
		{
				return AR_E_LEXNOTREADY;
		}

		return __thompson(prog, match, tok);
}








AR_NAMESPACE_END




