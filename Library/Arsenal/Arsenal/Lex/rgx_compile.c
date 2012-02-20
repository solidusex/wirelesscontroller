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

AR_NAMESPACE_BEGIN


static size_t __count(const rgxNode_t *node)
{
		AR_ASSERT(node != NULL);
		
		switch(node->type)
		{
		case RGX_CSET_T:
		case RGX_FINAL_T:
		case RGX_BEGIN_T:
		case RGX_END_T:
		case RGX_LINE_BEGIN_T:
		case RGX_LINE_END_T:
		case RGX_ANY_CHAR_T:
		{
				return 1;
		}
				break;
		case RGX_CAT_T:
		{
				size_t l = 0,r = 0;
				
				if(node->left != NULL) l = __count(node->left);
				if(node->right != NULL)r = __count(node->right);
				return l + r;
		}
				break;
		case RGX_BRANCH_T:
		{
				size_t l = 0,r = 0,curr = 0;
				if(node->left) l = __count(node->left);
				if(node->right) r = __count(node->right);
				if(l > 0 && r > 0) curr = 2;
				return l + r + curr;
		}
				break;
		case RGX_STAR_T:
		{
				return 2 + __count(node->left) ;
		}
				break;
		case RGX_QUEST_T:
		{
				return 1 + __count(node->left);
				break;
		}
		case RGX_PLUS_T:
		{
				return 1 + __count(node->left);
		}
				break;
		case RGX_FIXCOUNT_T:
		{
				return 2 + __count(node->left);
		}
				break;
		case RGX_LOOKAHEAD_T:
		{
				return 2 + __count(node->left);
		}
				break;
		default:
		{
				AR_CHECK(false, L"Arsenal : regex compile error %hs\r\n", AR_FUNC_NAME);
		}
				break;
		}
		
		return 0;
}


static void __emit_code(rgxProg_t *prog, const rgxNode_t *node)
{

		AR_ASSERT(prog != NULL && node != NULL);
		
		AR_ASSERT(prog->pc != NULL && prog->start != NULL && prog->count > 0);
		switch(node->type)
		{
		case RGX_CSET_T:
		{
				prog->pc->opcode = RGX_CHAR_I;
				prog->pc->range.beg = node->range.beg;
				prog->pc->range.end = node->range.end;
				prog->pc++; /*count = 1*/
		}
				break;
		case RGX_FINAL_T:
		{
				prog->pc->opcode = RGX_MATCH_I;
				prog->pc->final = (int_t)node->final_val;
				prog->pc++;/*count = 1*/
		}
				break;
		case RGX_BEGIN_T:
		{
				prog->pc->opcode = RGX_BEGIN_I;
				prog->pc++;/*count = 1*/
		}
				break;
		case RGX_END_T:
		{
				prog->pc->opcode = RGX_END_I;
				prog->pc++;/*count = 1*/
		}
				break;
		case RGX_LINE_BEGIN_T:
		{
				prog->pc->opcode = RGX_LINE_BEGIN_I;
				prog->pc++;/*count = 1*/
		}
				break;
		case RGX_LINE_END_T:
		{
				prog->pc->opcode = RGX_LINE_END_I;
				prog->pc++;/*count = 1*/
		}
				break;
		case RGX_ANY_CHAR_T:
		{
				prog->pc->opcode = RGX_ANY_CHAR_I;
				prog->pc++;/*count = 1*/
		}
				break;
		case RGX_CAT_T:
		{
				/*AR_ASSERT(node->left != NULL && node->right != NULL);*/
				if(node->left)__emit_code(prog, node->left);
				if(node->right)__emit_code(prog, node->right);
		}
				break;
		case RGX_BRANCH_T:
		{
				if(node->left == NULL || node->right == NULL)
				{
						if(node->left)__emit_code(prog, node->left);
						if(node->right)__emit_code(prog, node->right);
				}else
				{
						rgxIns_t *p1, *p2;
						p1 = prog->pc++;
						p1->opcode = RGX_BRANCH_I;/*count + 1*/
						p1->left = prog->pc;/*第一个分支，当前指令的下一条*/

						__emit_code(prog, node->left);
						/*当前prog->pc为node->left生成指令组的下一条指令*/

						p2 = prog->pc++; /*p2是node->left指令组执行完之后的下一条指令*/
						p2->opcode = RGX_JMP_I;/*count + 1*/
						p1->right = prog->pc;/*第二个分支，node->left生成指令组的下一条*/
						__emit_code(prog, node->right);
						p2->left = prog->pc;/*p2要跳到node->right生成的指令组之后的下一条指令*/

						/*count == 2*/
				}
		}
				break;
		case RGX_STAR_T:
		{
				rgxIns_t *p1; 
				prog->pc->opcode = RGX_BRANCH_I;/*这条指令导致一个分支, count + 1*/
				p1 = prog->pc++; /*p1为当前指令*/
				p1->left = prog->pc;/*一是从下一条开始继续匹配node->left*/
				__emit_code(prog, node->left);
				

				/*跟着star的是一个跳转指令，会直接跳回到当前指令*/
				/*这里prog->pc为node->left生成的指令组的下一条指令*/
				prog->pc->opcode = RGX_JMP_I;/*count + 1*/
				prog->pc->left = p1;/*star,所以回退到开始*/
				
				p1->right = ++prog->pc;/*执行到下一条指令*/

				if(node->non_greedy)
				{
						rgxIns_t *tmp = p1->left;
						p1->left = p1->right;
						p1->right = tmp;
				}

				/*count == 2*/
		}
				break;
		case RGX_QUEST_T:
		{
				rgxIns_t *p1;
				prog->pc->opcode = RGX_BRANCH_I;/*quest导致一个分支, count + 1*/
				p1 = prog->pc++;				/*p1当前branch指令*/
				p1->left = prog->pc;			/*p1分支1为下一条指令*/
				__emit_code(prog,node->left);		
				/*当前pc为node->left生成的指令组的下一条指令*/
				p1->right = prog->pc; /*quest == (0|1)，所以分支2为node->left的下一条指令*/

				if(node->non_greedy)
				{
						rgxIns_t *tmp = p1->left;
						p1->left = p1->right;
						p1->right = tmp;
				}
				/*count == 1*/
		}
				break;
		case RGX_PLUS_T:
		{
				rgxIns_t *p1, *p2;
				p1 = prog->pc;/*p1为当前指令*/
				__emit_code(prog, node->left);

				/*此时pc为node->left指令组的下一条指令*/
				p2 = prog->pc++;/*p2为当前指令*/
				p2->opcode = RGX_BRANCH_I;/*count + 1*/
				p2->left = p1;/*plus，分支1为node->left指令组的第一条指令,循环*/
				
				p2->right = prog->pc;/*分支2，经过node->left后，执行到下一条指令*/

				if(node->non_greedy)
				{
						rgxIns_t *tmp = p2->left;
						p2->left = p2->right;
						p2->right = tmp;
				}
				/*count + 1*/
		}
				break;
		case RGX_FIXCOUNT_T:
		{
				rgxIns_t *p1;
				
				AR_ASSERT(node->left != NULL);

				prog->pc->opcode = RGX_LOOP_BEG_I;/*count + 1*/
				prog->pc->fix_count = node->fix_count;
				p1 = prog->pc;
				
				prog->pc++;
				__emit_code(prog, node->left);

				prog->pc->opcode = RGX_LOOP_END_I;
				prog->pc++;
				p1->left = prog->pc;

				/*count == 2*/
		}
				break;
		case RGX_LOOKAHEAD_T:
		{
				rgxIns_t *p1;
				prog->pc->opcode = RGX_LOOKAHEAD_BEG_I;/*count + 1*/

				if(node->negative_lookahead)
				{
						prog->pc->lookahead.negative= true;
				}

				/*prog->pc->lookahead.has_run = false;*/

				p1 = prog->pc;
				
				prog->pc++;
				__emit_code(prog,node->left);/*node->left*/
				/*此时当前指令pc为node->left指令组的下一条*/
				prog->pc->opcode = RGX_LOOKAHEAD_END_I;/*count + 1*/
				prog->pc++;
				
				p1->left = prog->pc;

				/*count == 2*/
		}
				break;
		default:
		{
				AR_CHECK(false, L"Arsenal : regex compile error %hs\r\n", AR_FUNC_NAME);
		}
				break;
		}
}




void			RGX_InitProg(rgxProg_t *prog)
{
		AR_ASSERT(prog != NULL);
		AR_memset(prog, 0, sizeof(*prog));

}		


void			RGX_UnInitProg(rgxProg_t *prog)
{
		AR_ASSERT(prog != NULL);
		if(prog->start != NULL)AR_DEL(prog->start);
		
		if(prog->curr)RGX_DestroyThreadList(prog->curr);
		if(prog->next)RGX_DestroyThreadList(prog->next);

		AR_memset(prog, 0, sizeof(*prog));
}


arStatus_t			RGX_Compile(rgxProg_t *prog, const rgxNode_t *tree)
{
		AR_ASSERT(prog != NULL && prog->count == 0 && prog->start == NULL && tree != NULL);

		AR_ASSERT(tree->type == RGX_CAT_T && tree->right->type == RGX_FINAL_T);

		prog->count = __count(tree);
		
		AR_ASSERT(prog->count > 0);

		prog->start = AR_NEWARR0(rgxIns_t, prog->count);

		if(prog->start == NULL)
		{
				return AR_E_NOMEM;
		}

		prog->pc = prog->start;

		__emit_code(prog, tree);

		AR_ASSERT(prog->pc == prog->start + prog->count);

/*
		{
				arString_t *str;
				
				str = AR_CreateString();

				RGX_ProgToString(prog, str);

				AR_printf(L"%ls\r\n", AR_GetStringCString(str));

				AR_DestroyString(str);
		}
*/

		return AR_S_YES;

}







arStatus_t			RGX_ProgToString(const rgxProg_t *prog, arString_t *str)
{
		size_t i;
		arStatus_t	status;
		AR_ASSERT(prog != NULL && str);

		status = AR_S_YES;

		for(i = 0; i < prog->count; ++i)
		{
				const rgxIns_t *pc = &prog->start[i];
				switch(pc->opcode)
				{
				case RGX_CHAR_I:
				{
						status = AR_AppendFormatString(str, L"%2d. %ls [", i, RGX_INS_NAME[pc->opcode]);

						if(status != AR_S_YES)
						{
								return status;
						}

						if(pc->range.beg == pc->range.end)
						{
								if(AR_iswgraph(pc->range.beg) && pc->range.beg < (wchar_t)128)
								{
										status = AR_AppendFormatString(str, L"%c", pc->range.beg);

										if(status != AR_S_YES)
										{
												return status;
										}
								}else
								{
										status = AR_AppendFormatString(str, L"\\u%Id", pc->range.beg);

										if(status != AR_S_YES)
										{
												return status;
										}
								}
						}else
						{
								if(AR_iswgraph(pc->range.beg) && pc->range.beg < (wchar_t)128)
								{
										status = AR_AppendFormatString(str, L"%c", pc->range.beg);

										if(status != AR_S_YES)
										{
												return status;
										}
								}else
								{
										status = AR_AppendFormatString(str, L"\\u%Id", pc->range.beg);

										if(status != AR_S_YES)
										{
												return status;
										}
								}

								status = AR_AppendString(str, L"-");

								if(status != AR_S_YES)
								{
										return status;
								}

								if(AR_iswgraph(pc->range.end) && pc->range.end < (wchar_t)128)
								{
										status = AR_AppendFormatString(str, L"%c", pc->range.end);

										if(status != AR_S_YES)
										{
												return status;
										}
								}else
								{
										status = AR_AppendFormatString(str, L"\\u%Id", pc->range.end);

										if(status != AR_S_YES)
										{
												return status;
										}
								}
						}
						status = AR_AppendFormatString(str, L"]\r\n");

						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				}
				
				case RGX_LOOP_BEG_I:
				{
						status = AR_AppendFormatString(str, L"%2d. %ls %Id LoopCount == %Id\r\n", i, RGX_INS_NAME[pc->opcode], (size_t)(pc->left - prog->start), pc->fix_count);

						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				}
				case RGX_LOOKAHEAD_BEG_I:
				{
						if(!pc->lookahead.negative)
						{
								status = AR_AppendFormatString(str, L"%2d. %ls %Id\r\n", i, RGX_INS_NAME[pc->opcode], (size_t)(pc->left - prog->start));
						}else
						{
								status = AR_AppendFormatString(str, L"%2d. Negative %ls %Id\r\n", i, RGX_INS_NAME[pc->opcode], (size_t)(pc->left - prog->start));
						}

						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				}
				case RGX_LOOP_END_I:
				case RGX_LOOKAHEAD_END_I:
				case RGX_BEGIN_I:
				case RGX_END_I:
				case RGX_LINE_BEGIN_I:
				case RGX_LINE_END_I:
				case RGX_ANY_CHAR_I:
				case RGX_MATCH_I:
				{
						status = AR_AppendFormatString(str, L"%2d. %ls\r\n", i, RGX_INS_NAME[pc->opcode]);

						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				}
				case RGX_JMP_I:
				{
						status = AR_AppendFormatString(str, L"%2d. %ls %Id\r\n", i, RGX_INS_NAME[pc->opcode], (size_t)(pc->left - prog->start));

						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				}
				case RGX_BRANCH_I:
				{
						status = AR_AppendFormatString(str, L"%2d. %ls %Id %Id\r\n", i, RGX_INS_NAME[pc->opcode], (size_t)(pc->left - prog->start), (size_t)(pc->right - prog->start));

						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				}
				case RGX_NOP_I:
						status = AR_AppendFormatString(str, L"%2d. %ls\r\n", i,RGX_INS_NAME[RGX_NOP_I]);
						if(status != AR_S_YES)
						{
								return status;
						}

						break;
				default:
				{
						AR_CHECK(false, L"Arsenal : regex compile error %hs\r\n", AR_FUNC_NAME);
						break;
				}
				}
		}

		return status;
}


AR_NAMESPACE_END



