/*************************************************************************/
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


#ifndef __REGEX_PARSER_H__
#define __REGEX_PARSER_H__

#include "rgx.h"


AR_NAMESPACE_BEGIN


static const wchar_t*	__transform_char(const wchar_t *input, wchar_t *c, rgxError_t *err)
{
		const wchar_t	*p; 
		AR_ASSERT(input != NULL && c != NULL && err != NULL);
		err->pos = NULL;
		
		p = input;
		switch(*p)
		{
				case L'\0':
						err->status = AR_S_NO;
						err->pos = p;
						return NULL;
				case L'{':
				case L'}':
				case L'[':
				case L']':
				case L'(':
				case L')':
				case L'\\':
				case L'?':
				case L'+':
				case L'-':
				case L'*':
				case L'|':
				case L'^':
				case L'$':
				case L'"':
				case L'.':
						*c = *p;
						return ++p;
				case L'a': 
						*c = L'\a';
						return ++p;
				case L'b':
						*c = L'\b';
						return ++p;
				case L'f': 
						*c = L'\f';
						return ++p;
				case L'n': 
						*c = L'\n';
						return ++p;
				case L'r': 
						*c = L'\r';
						return ++p;
				case L't': 
						*c = L'\t';
						return ++p;
				case L'v': 
						*c = L'\v';
						return ++p;
				case L'u':
				{
						const wchar_t *ret; uint_32_t val;
						p += 1;
						
						if(*p != L'{')
						{
								ret = AR_wtou32_s(p,p+4, &val, 10);
								
								if(ret == NULL)
								{
										err->status = AR_S_NO;
										err->pos = p;
										return NULL;
								}else
								{
										*c = (wchar_t)val;
										p = ret;
								}
						}else
						{
								const wchar_t *end;
								p+=1;
								end = p;
								
								while(*end != L'\0' && *end != L'}')
								{
										end++;
								}
								
								ret = AR_wtou32_s(p, end, &val, 10);
								
								if(ret)
								{
										ret = AR_wcstrim_space(ret);
										
										if(*ret != L'}')
										{
												ret = NULL;
										}
								}
								
								if(ret == NULL)
								{
										err->status = AR_S_NO;
										err->pos = p;
										return NULL;
								}else
								{
										*c = (wchar_t)val;
										p = ret;
								}
								
								AR_ASSERT(*p == L'}');
								p++;		
						}
						
						return p;
				}
						break;
				case L'x':
				{
						const wchar_t *ret;  uint_32_t val;
						
						p += 1;
						
						if(*p != L'{')
						{
								ret = AR_wtou32_s(p, p + 2, &val, 16);
								if(ret == NULL)
								{
										err->status = AR_S_NO;
										err->pos = p;
										return NULL;
								}else
								{
										*c = (wchar_t)val;
										p = ret;
								}
						}else
						{
								const wchar_t *end;
								p+=1;
								end = p;
								
								while(*end != L'\0' && *end != L'}')
								{
										end++;
								}
								
								ret = AR_wtou32_s(p, end, &val, 16);
								
								if(ret)
								{
										ret = AR_wcstrim_space(ret);
										if(*ret != L'}')
										{
												ret = NULL;
										}
								}
								
								if(ret == NULL)
								{
										err->status = AR_S_NO;
										err->pos = p;
										return NULL;
								}else
								{
										*c = (wchar_t)val;
										p = ret;
								}
								
								AR_ASSERT(*p == L'}');
								p++;
						}
						return p;
				}
						break;
				default:
						err->status = AR_S_NO;
						err->pos = p;
						return NULL;
		}
}


#define __SET_ERR(_e, _next, _node, _pos, _status) \
do{\
(_e).err.status = (_status); \
(_e).err.pos = (_pos); \
(_e).next = (_next); \
(_e).node = (_node); \
}while(0)

static rgxResult_t	__handle_quote(const wchar_t *input)
{
		const wchar_t *p; 
		rgxNode_t *cat;
		rgxResult_t		g_res;
		AR_ASSERT(input != NULL);
		
		__SET_ERR(g_res, NULL, NULL, NULL, AR_S_YES);
		
		p = input;
		cat = RGX_CreateNode(RGX_CAT_T);
		
		if(cat == NULL)
		{
				__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
				goto INVALID_POINT;
		}
		
		
		while(*p != L'"')
		{
				wchar_t c;
				rgxCharRange_t range;
				rgxNode_t		*tmp = NULL;
				
				if(*p == L'\0')/*����"abc���ֲ�������*/
				{
						__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
						g_res.err.pos = p;
						goto INVALID_POINT;
				}else if(*p == L'\\')/*����\"\b\c\\�ȵȵĴ�*/
				{
						
						if(*(p+1) == L'\0')/*������������\*/
						{
								__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
								goto INVALID_POINT;
						}
						
						++p;
						
						switch(*p)
						{
								case L'b':
										c = L'\b';
										++p;
										break;
								case L'f':
										c = L'\f';
										++p;
										break;
								case L'n':
										c = L'\n';
										++p;
										break;
								case L'r':
										c = L'\r';
										++p;
										break;
								case L't':
										c = L'\t';
										++p;
										break;
								case L'v':
										c = L'\v';
										++p;
										break;
								case L'a':
										c = L'\a';
										++p;
										break;
								case L'\\':
										c = L'\\';
										++p;
										break;
								case L'\"':
										c = L'\"';
										++p;
										break;
								case L'\'':
										c = L'\'';
										++p;
										break;
								case L'x':
								{
										uint_64_t num;
										if(*(p + 1) == L'\0')/*����\x���ֲ�������*/
										{
												__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
												goto INVALID_POINT;
										}else
										{
												const wchar_t *tmp_ptr;
												tmp_ptr = AR_wtou64(p + 1, &num, 16);
												
												if(tmp_ptr == NULL || num > (uint_64_t)AR_WCHARMAX)
												{
														__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
														goto INVALID_POINT;
												}
												p = tmp_ptr;
												c = (wchar_t)num;
										}
										break;
								}
								default:/*�˽���*/
								{
										if(*p >= L'0' && *p <= L'7')
										{
												if(*p == L'0' && *(p + 1) == 0)
												{
														c = 0;
														++p;
												}else
												{
														size_t i;
														wchar_t t = 0;
														
														for(i = 0; i < 3 && p[i] && p[i] >= L'0' && p[i] <= L'7'; ++i)
														{
																t *= 8;
																t += p[i] - L'0';
														}
														
														c = t;
														p += i;
												}
										}else
										{
												__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
												goto INVALID_POINT;
										}
										break;
								}
						}
				}else/*��׼�ַ�*/
				{
						c = *p;
						++p;
				}
				
				range.beg = range.end = c;
				tmp = RGX_CreateNode(RGX_CSET_T);
				if(tmp == NULL)
				{
						__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
						goto INVALID_POINT;
				}
				tmp->range.beg = tmp->range.end = c;
				g_res.err.status = RGX_InsertToNode(cat, tmp);
				if(g_res.err.status != AR_S_YES)
				{
						RGX_DestroyNode(tmp);
						tmp = NULL;
						__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
						goto INVALID_POINT;
				}
		}
		
		AR_ASSERT(*p == L'"');
		
		if(cat->left == NULL && cat->right == NULL)/*������Ϊ""�Ŀ�����*/
		{
				__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
				goto INVALID_POINT;
		}
		__SET_ERR(g_res, ++p, cat, NULL, AR_S_YES);
		cat = NULL;
		
		return g_res;
		
		
INVALID_POINT:
		
		if(cat != NULL)
		{
				RGX_DestroyNode(cat);
				cat = NULL;
		}
		return g_res;
}


static const wchar_t* __get_charset(const wchar_t *input, wchar_t *c, rgxError_t *err)
{
		AR_ASSERT(input != NULL && c != NULL && err != NULL);
		err->pos = NULL;
		err->status = AR_S_YES;
		
		switch(*input)
		{
				case L'\0':
						err->status = AR_S_NO;
						err->pos = input;
						return NULL;
				case L'\a': 
				case L'\f': 
				case L'\n': 
				case L'\r': 
				case L'\t': 
				case L'\v': 
				case L'\b':
						/*				AR_ASSERT(0);*/
						err->status = AR_S_NO;
						err->pos = input;
						return NULL;
				case L'{':
				case L'}':
				case L'[':
				case L']':
				case L'(':
				case L')':
				case L'?':
				case L'+':
				case L'-':
				case L'*':
				case L'|':
				case L'"':
				case L'^':
				case L'$':
				case L'.':
						err->status = AR_S_NO;
						err->pos = input;
						return NULL;
				case L'\\':
						return __transform_char(input + 1, c, err);
				default:
						*c = *input;
						return ++input;
		}
}




static rgxResult_t	__handle_cset_range(const wchar_t *input)
{
		const wchar_t *p; 
		rgxResult_t		g_res; 
		rgxCharSet_t	cset;
		rgxCharRange_t	*range = NULL;
		AR_ASSERT(input != NULL);
		
		
		__SET_ERR(g_res, NULL, NULL, NULL, AR_S_YES);
		
		p = input;
		
		RGX_InitCharSet(&cset);
		
		if(*p == L'^') /*����[^a-z]*/
		{
				cset.is_neg = true; 
				p++;
		}
		
		while(*p != L']')
		{
				rgxCharRange_t	range;	
				rgxError_t err;
				p = __get_charset(p, &range.beg, &err);/*������ȡÿ���ַ�*/
				
				if(p == NULL)/*���󷵻�*/
				{
						__SET_ERR(g_res, NULL, NULL, err.pos, err.status);
						goto INVALID_POINT;
				}else
				{
						if(*p == L'\0')/*�������룬���紮��[abc��*/
						{
								__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
								goto INVALID_POINT;
						}
						
						if(*p == L'-')/*����[a-z]*/
						{
								p = __get_charset(p + 1, &range.end, &err);
								if(p == NULL)/*���󷵻�*/
								{
										__SET_ERR(g_res, NULL, NULL, err.pos, err.status);
										goto INVALID_POINT;
								}
						}else/*����[ab]����[a]�ȵ�*/
						{
								range.end = range.beg;
						}
				}
				g_res.err.status = RGX_InsertRangeToCharSet(&cset, &range);
				
				if(g_res.err.status != AR_S_YES)
				{
						__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
						goto INVALID_POINT;
				}
		}
		
		AR_ASSERT(*p == L']');
		
		if(cset.is_neg)/*����[^a-z]��ʽ*/
		{
				g_res.err.status = RGX_ReverseNegativeCharSet(&cset);
				
				if(g_res.err.status != AR_S_YES)
				{
						__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
						goto INVALID_POINT;
				}
		}
		
		
		AR_ASSERT(cset.range != NULL);
		
		g_res.node = RGX_CreateNode(RGX_BRANCH_T);
		
		//g_res.next = ++p
		
		if(g_res.node == NULL)
		{		
				__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
				goto INVALID_POINT;
		}
		
		for(range = cset.range; range; range = range->next)
		{
				rgxNode_t *tmp = RGX_CreateNode(RGX_CSET_T);
				
				if(tmp == NULL)
				{
						__SET_ERR(g_res, NULL, g_res.node, NULL, AR_E_NOMEM);
						goto INVALID_POINT;
				}
				
				tmp->range.beg = range->beg;
				tmp->range.end = range->end;
				
				g_res.err.status = RGX_InsertToNode(g_res.node, tmp);
				
				if(g_res.err.status != AR_S_YES)
				{
						RGX_DestroyNode(tmp);
						tmp = NULL;
						
						__SET_ERR(g_res, NULL, g_res.node, NULL, g_res.err.status);
						goto INVALID_POINT;
				}
		}
		
		RGX_UnInitCharSet(&cset);
		
		__SET_ERR(g_res, p + 1, g_res.node, NULL, AR_S_YES);
		
		
		return g_res;
		
INVALID_POINT:
		RGX_UnInitCharSet(&cset);
		
		if(g_res.node != NULL) 
		{
				RGX_DestroyNode(g_res.node);
				g_res.node = NULL;
		}
		return g_res;
}

static rgxResult_t	__handle_charset(const wchar_t *input)
{
		const wchar_t *p; 
		rgxResult_t		g_res; 
		rgxCharRange_t range;
		AR_ASSERT(input != NULL);
		p = input;
		
		
		__SET_ERR(g_res, NULL, NULL, NULL, AR_S_YES);
		
		if(*p == L'[')/*����[a-z0-9A-Z]�ȵ�*/
		{
				return __handle_cset_range(p+1);
				
		}else if(*p == L'.')/*any char*/
		{
				g_res.node =  RGX_CreateNode(RGX_ANY_CHAR_T);
				
				if(g_res.node == NULL)
				{
						__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
				}else
				{
						__SET_ERR(g_res, ++p, g_res.node, NULL, AR_S_YES);
				}
				return g_res;
				
		}else if(*p == L'\\')/*����Ϊת���ַ�����\\B or \\E ƥ������β�������Ϊ����β�� �����*/
		{
				if(*(p + 1) == L'B' || *(p + 1) == L'E')
				{
						++p;
						g_res.node =  RGX_CreateNode(*p == L'B' ? RGX_LINE_BEGIN_T : RGX_LINE_END_T);
						
						if(g_res.node == NULL)
						{
								__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
						}else
						{
								__SET_ERR(g_res, ++p, g_res.node, NULL, AR_S_YES);
						}
						return g_res;
				}
		}
		/*����ƥ������ַ�������a or b or c�ȵ�*/
		
		
		
		p = __get_charset(p, &range.beg, &g_res.err);
		
		if(p == NULL)
		{
				__SET_ERR(g_res, NULL, NULL, g_res.err.pos, g_res.err.status);
		}else
		{
				range.end = range.beg;
				g_res.node = RGX_CreateNode(RGX_CSET_T);
				
				if(g_res.node == NULL)
				{
						__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
				}else
				{
						__SET_ERR(g_res, p, g_res.node, NULL, AR_S_YES);
						
						g_res.node->range.beg = range.beg;
						g_res.node->range.end = range.end;
				}
		}
		
		return g_res;
}






static rgxNode_t*       __handle_loopcount(rgxNode_t *expr, size_t min, size_t max, bool_t non_greedy)
{
		bool_t is_infinite;
		
		AR_ASSERT(expr != NULL && min <= max && max > 0);
		
		is_infinite = (max == AR_SIZE_MAX ? true : false);
		
		
		
RECHECK:
		if(min < max)
		{
				if(min == 0)/*����{0,n}����{0,������}��ʽ*/
				{
						if(is_infinite)/*���Ϊ{0-������},���Ϊ '*'ģʽ*/
						{
								min = max; 
								goto RECHECK;
								
						}else	/*{0,n}��ʽ����Ҫ�����޸ĳ�(a?){n}����ʽ*/
						{
								rgxNode_t *new_expr, *max_node;
								
								new_expr = NULL;
								max_node = NULL;
								
								new_expr = RGX_CreateNode(RGX_QUEST_T);
								
								
								if(new_expr == NULL)
								{
										goto INVALID_POINT_1;
								}
								
								new_expr->left = expr;
								expr = NULL;
								new_expr->non_greedy = non_greedy;
								
								
								max_node = RGX_CreateNode(RGX_FIXCOUNT_T);
								
								if(max_node == NULL)
								{
										goto INVALID_POINT_1;
								}
								
								max_node->fix_count = max;
								max_node->left = new_expr;
								new_expr = NULL;
								
								return max_node;
								/***************************************************************************************/
						INVALID_POINT_1:	
								if(new_expr)
								{
										RGX_DestroyNode(new_expr);
										new_expr = NULL;
								}
								
								if(max_node)
								{
										RGX_DestroyNode(max_node);
										max_node = NULL;
								}
								
								if(expr)
								{
										RGX_DestroyNode(expr);
										expr = NULL;
								}
								return NULL;
								/***************************************************************************************/
								
						}
				}else/*����{m,n}��m > 0 && m < n  && n < ������*/
				{
						rgxNode_t *cat, *min_node, *max_node, *new_expr;
						
						cat = NULL;
						min_node = NULL;
						max_node = NULL;
						new_expr = NULL;
						
						min_node = RGX_CreateNode(RGX_FIXCOUNT_T);
						
						if(min_node == NULL)
						{
								goto INVALID_POINT_2;
						}
						
						min_node->fix_count = min;
						min_node->left = RGX_CopyNewNode(expr);
						
						if(min_node->left == NULL)
						{
								goto INVALID_POINT_2;
						}
						
						
						if(is_infinite)
						{
								/*
								 ���������������дΪa{m}a*��ʽ,���non_greedyΪ�棬���дΪa{m}a*
								 */
								max_node = RGX_CreateNode(RGX_STAR_T);
								
								if(max_node == NULL)
								{
										goto INVALID_POINT_2;
								}
								
								max_node->left = RGX_CopyNewNode(expr);
								
								if(max_node->left == NULL)
								{
										goto INVALID_POINT_2;
								}
								
								max_node->non_greedy = non_greedy;
								
						}else
						{
								/*
								 ���������a{3,5}�������дΪa{3}(a??){2}��ʽ,���non_greedyΪ�棬���дΪa{m}a*
								 */
								
								new_expr = RGX_CreateNode(RGX_QUEST_T);
								
								if(new_expr == NULL)
								{
										goto INVALID_POINT_2;
								}
								
								new_expr->left = RGX_CopyNewNode(expr);
								
								if(new_expr->left == NULL)
								{
										goto INVALID_POINT_2;
								}
								
								new_expr->non_greedy = non_greedy;
								
								max_node = RGX_CreateNode(RGX_FIXCOUNT_T);
								
								if(max_node == NULL)
								{
										goto INVALID_POINT_2;
								}
								
								max_node->fix_count = max - min;
								max_node->left = new_expr;
								new_expr = NULL;
						}
						
						
						cat = RGX_CreateNode(RGX_CAT_T);
						if(cat == NULL)
						{
								goto INVALID_POINT_2;
						}
						
						if(RGX_InsertToNode(cat, min_node) != AR_S_YES)
						{
								goto INVALID_POINT_2;
						}
						min_node = NULL;
						
						
						if(RGX_InsertToNode(cat, max_node) != AR_S_YES)
						{
								goto INVALID_POINT_2;
						}
						max_node = NULL;
						
						RGX_DestroyNode(expr);
						expr = NULL;
						
						return cat;
						
				INVALID_POINT_2:
						if(min_node)
						{
								RGX_DestroyNode(min_node);
								min_node = NULL;
						}
						
						if(max_node)
						{
								RGX_DestroyNode(max_node);
								max_node = NULL;
						}
						
						if(new_expr)
						{
								RGX_DestroyNode(new_expr);
								new_expr = NULL;
						}
						
						if(cat)
						{
								RGX_DestroyNode(cat);
								cat = NULL;
						}
						
						if(expr)
						{
								RGX_DestroyNode(expr);
								expr= NULL;
						}
						
						return NULL;
				}
				
				
				
		}else/* if(min == max)*/
		{
				rgxNode_t *loop;
				loop = NULL;
				
				if(is_infinite)	/*���Ϊ{0-������},���Ϊ '*'ģʽ*/
				{
						loop = RGX_CreateNode(RGX_STAR_T);
						if(loop == NULL)
						{
								RGX_DestroyNode(expr);
								expr = NULL;
						}else
						{
								loop->left = expr;
								expr = NULL;
								loop->non_greedy = non_greedy;
						}
						return loop;
				}else /*min == max && max > 0 ����a{3,3}����д��a{3}*/
				{
						loop = RGX_CreateNode(RGX_FIXCOUNT_T);
						
						if(loop == NULL)
						{
								RGX_DestroyNode(expr);
								expr = NULL;
						}else
						{
								loop->left = expr;
								expr = NULL;
								loop->fix_count = min;
						}
						return loop;
				}
		}
}




static rgxResult_t	__handle_expr(const wchar_t *input, wchar_t tc, const rgxNameSet_t *name_set);
static rgxResult_t	__handle_postfix(rgxNode_t *expr, const wchar_t *input)
{
		const wchar_t *p; 
		rgxResult_t		g_res; 
		AR_ASSERT(input != NULL && expr != NULL);
		
		p = input;
		
		__SET_ERR(g_res, NULL, NULL, NULL, AR_S_YES);
		
		
		switch(*p)
		{
				case '*':		/*ƥ��{0-������}��*/
				{
						g_res.node = RGX_CreateNode(RGX_STAR_T);
						if(g_res.node == NULL)
						{
								__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
								goto INVALID_POINT;
						}
						
						g_res.node->left = expr;
						expr = NULL;
						
						++p;
						if(*p == L'?')/*����ƥ�䣬����ƥ��0��*/
						{
								g_res.node->non_greedy = true;
								++p;
						}
						g_res.next = p;
				}
						break;
				case '+':		/*ƥ��{1-������}��*/
				{
						g_res.node = RGX_CreateNode(RGX_PLUS_T);
						
						if(g_res.node == NULL)
						{
								__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
								goto INVALID_POINT;
						}
						
						g_res.node->left = expr;
						expr = NULL;
						++p;
						if(*p == L'?')/*����ƥ�䣬����ƥ��1��*/
						{
								g_res.node->non_greedy = true;
								++p;
						}
						g_res.next = p;
				}
						break;
				case '?':		/*ƥ��{0-1}��*/
				{
						g_res.node = RGX_CreateNode(RGX_QUEST_T);
						
						if(g_res.node == NULL)
						{
								__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
								goto INVALID_POINT;
						}
						
						
						g_res.node->left = expr;
						expr = NULL;
						++p;
						if(*p == L'?')/*����ƥ�䣬����ƥ��0��*/
						{
								g_res.node->non_greedy = true;
								++p;
						}
						g_res.next = p;
				}
						break;
				case '{':		/*ƥ��{m-n}��,���У���Ϊ{m,n}, {m,}, {,n}, {m},Ҳ���������ƣ�����{name},*/
				{
						bool_t non_greedy = false;
						const wchar_t *beg = p + 1;
						uint_t min,max;
						
						/*beg = AR_wcstrim(beg,L" \t");*/
						beg = AR_wcstrim_space(beg);
						
						beg = AR_wtou(beg, &min, 10);
						
						if(beg == NULL) 
						{
								__SET_ERR(g_res, p, expr, NULL, AR_S_YES);
								return g_res;
						}
						
						/*beg = AR_wcstrim(beg,L" \t");*/
						beg = AR_wcstrim_space(beg);
						
						if(*beg == L',')
						{
								beg++;
								/*beg = AR_wcstrim(beg,L" \t");*/
								beg = AR_wcstrim_space(beg);
								
								if(*beg == L'}')		/*��ʱΪ{m,}��ʽ,��˼Ϊ��{m-������}*/
								{
										max = AR_SIZE_MAX;
								}else
								{
										beg = AR_wtou(beg, &max, 10);/*��ȡ��n*/
										
										if(beg == NULL) /*��ʱ ��ʽΪ{m,...�Ƿ��ַ�}����ʧ��*/
										{
												__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
												
												goto INVALID_POINT;
										}
										
										beg = AR_wcstrim_space(beg);
										
										if(*beg != L'}')/*��ʱΪ{m,n �Ƿ��ַ� ��ʽ,��ʧ��*/
										{
												__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
												goto INVALID_POINT;
										}
								}
						}else if(*beg == L'}')/*��ʱΪ{m}��ʽ,��˼Ϊ��ƥ��m��Ԫ��*/
						{
								max = min;
								
						}else			/*��ʱ��ʽΪ{m�Ƿ��ַ�������*/
						{
								
								__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
								goto INVALID_POINT;
						}
						
						/*
						 if(min > max || max == 0){ g_res.err.pos = p; goto INVALID_POINT;}
						 */
						
						if(min > max || max == 0)	/*����{5,3}����{0,0}���ַǷ���ʽ*/
						{
								__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
								goto INVALID_POINT;
						}
						
						++beg;
						
						if(*beg == L'?')		/*����ģʽ������ƥ��min*/
						{
								non_greedy = true;
								++beg;
						}
						
						g_res.next = beg;
						g_res.node = __handle_loopcount(expr, min,max, non_greedy);
						expr = NULL;
						
						if(g_res.node == NULL)
						{
								__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
								goto INVALID_POINT;
						}
				}
						break;
				default:/*û�к�׺����ʽ����ֱ�ӷ�������*/
						__SET_ERR(g_res, input, expr, NULL, AR_S_YES);
						return g_res;
		}
		
		return g_res;
INVALID_POINT:
		
		if(expr)
		{
				RGX_DestroyNode(expr);
				expr = NULL;
		}
		
		if(g_res.node)
		{
				RGX_DestroyNode(g_res.node);
				g_res.node = NULL;
		}
		return g_res;
}




static rgxResult_t __handle_factor(const wchar_t *input, const rgxNameSet_t *name_set)
{
		const wchar_t *p; 
		rgxResult_t		g_res; 
		
		AR_ASSERT(input != NULL);
		p = input;
		
		__SET_ERR(g_res, NULL, NULL, NULL, AR_S_YES);
		
		switch(*p)
		{
				case L'^':		/*�������Ԫ��Ϊ^����$������û�к�׺���������ɺ�ֱ�ӷ���*/
				case L'$':
				{
						g_res.node =  RGX_CreateNode(*p == L'^' ? RGX_BEGIN_T : RGX_END_T);
						
						if(g_res.node == NULL)
						{
								__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
						}else
						{
								g_res.next = ++p;
						}
						return g_res;
						break;
				}
				case L'"':		/*�������Ԫ��Ϊ���ã����к�׺����Ҫ__handle_postfix�������׺������еĻ���*/
				{
						g_res = __handle_quote(p + 1);
						break;
				}
				case L'(':		/*�������Ԫ��Ϊ���飬���к�׺����Ҫ__handle_postfix�������׺������еĻ���*/
				{
						++p;
						
						if(*p == L'?')/*lookahead*/
						{
								++p;
								
								if(*p == L'=' || *p == L'!')
								{
										rgxResult_t		result;
										result = __handle_expr(p + 1, L')', name_set);
										
										if(result.err.status != AR_S_YES)
										{
												AR_ASSERT(result.node == NULL);
												return result;
										}
										
										g_res.err = result.err;
										g_res.next = result.next;
										
										g_res.node = RGX_CreateNode(RGX_LOOKAHEAD_T);
										
										if(g_res.node == NULL)
										{
												RGX_DestroyNode(result.node);
												result.node = NULL;
												
												__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
												
												return g_res;
										}
										
										g_res.node->left = result.node;
										
										if(*p == L'=')
										{
												g_res.node->negative_lookahead = false;
										}else
										{
												g_res.node->negative_lookahead = true;
										}
										
								}else
								{
										__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
										return g_res;
										
								}
						}else	/*�����ӱ��ʽ*/
						{
								g_res = __handle_expr(p, L')', name_set);
						}
				}
						break;
				case L'{':		/*{����������ض�Ϊ�������ã�����{name}�� ����Ϊ����*/
				{
						
						p += 1;
						p = AR_wcstrim_space(p);
						
						if(AR_iswalpha(*p) || *p == L'_')
						{
								const wchar_t *beg;
								size_t i, count;
								
								beg = p; count = 0;
								
								while(AR_iswalnum(*p) || *p == L'_')
								{
										p++;
										count++;
								}
								
								p = AR_wcstrim_space(p);
								
								if(*p != L'}' || count >= AR_RGX_MAXNAME)
								{
										__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
										return g_res;
								}else
								{
										const rgxNode_t *new_node;
										wchar_t name[AR_RGX_MAXNAME];
										
										for(i = 0; i < count; ++i)
										{
												name[i] = beg[i];
										}
										
										name[count] = L'\0';
										new_node = RGX_FindFromNameSet(name_set, name);
										
										if(new_node == NULL)
										{
												__SET_ERR(g_res, NULL, NULL, (p - count - 1), AR_S_NO);
												
												return g_res;
										}else
										{
												g_res.node = RGX_CopyNewNode(new_node);
												
												if(g_res.node == NULL)
												{
														__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
														return g_res;
												}else
												{
														__SET_ERR(g_res, ++p, g_res.node, NULL, AR_S_YES);
												}
										}
								}
								
						}else
						{
								/*
								 AR_ASSERT(0);
								 */
								__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
								return g_res;
						}
				}
						break;
				default:/*����a*/
						g_res = __handle_charset(p);
		}
		
		
		if(g_res.err.status == AR_S_YES)
		{
				AR_ASSERT(g_res.node != NULL);
				AR_ASSERT(g_res.next != NULL);
				/*return __handle_postfix(g_res.node, g_res.next,name_set);*/
				return __handle_postfix(g_res.node, g_res.next);
		}else
		{
				return g_res;
		}
}




static rgxResult_t __handle_expr(const wchar_t *input, wchar_t tc, const rgxNameSet_t *name_set)
{
		
		rgxNode_t		*branch, *cat;
		const wchar_t *p; 
		rgxResult_t g_res; 
		
		AR_ASSERT(input != NULL);
		
		branch = NULL; 
		cat = NULL;
		
		p = input; 
		
		__SET_ERR(g_res, NULL, NULL, NULL, AR_S_YES);
		
		while(*p != L'\0' && *p != tc)
		{
				rgxResult_t tmp = __handle_factor(p, name_set);
				
				if(tmp.err.status != AR_S_YES)
				{
						AR_ASSERT(tmp.node == NULL);
						AR_ASSERT(tmp.next == NULL);
						
						__SET_ERR(g_res, NULL, NULL, tmp.err.pos, tmp.err.status);
						goto INVALID_POINT;
				}
				
				AR_ASSERT(p != NULL);
				AR_ASSERT(tmp.node != NULL);
				
				p = tmp.next;
				
				if(*p == L'|')
				{
						/*
						 ����������ʽ����"a|b"��������'|'ʱ�����branch ��cat��ΪNULL,��ʱ��Ҫ��aֱ�Ӳ���branch�ڵ�
						 ����������ʽ����"ab|c"��������'|'ʱ�����branch ΪNULL����ʱ��Ҫ��aֱ�Ӳ���cat�ڵ㣬�ٽ�cat����branch�ڵ�
						 */
						if(branch == NULL)
						{
								branch = RGX_CreateNode(RGX_BRANCH_T);
								
								if(branch == NULL)
								{
										RGX_DestroyNode(tmp.node);
										tmp.node = NULL;
										
										__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
										goto INVALID_POINT;
								}
						}
						
						if(cat == NULL)
						{
								if((g_res.err.status = RGX_InsertToNode(branch, tmp.node)) != AR_S_YES)
								{
										RGX_DestroyNode(tmp.node);
										tmp.node = NULL;
										
										__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
										goto INVALID_POINT;
								}
						}else
						{
								if((g_res.err.status = RGX_InsertToNode(cat, tmp.node)) != AR_S_YES)
								{
										RGX_DestroyNode(tmp.node);
										tmp.node = NULL;
										
										__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
										goto INVALID_POINT;
								}else
								{
										tmp.node = NULL;
								}
								
								
								if((g_res.err.status = RGX_InsertToNode(branch, cat)) != AR_S_YES)
								{
										__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
										
										goto INVALID_POINT;
								}else
								{
										cat = NULL;
								}
						}
						p++;
				}else
				{
						if(cat == NULL)
						{
								cat =  RGX_CreateNode(RGX_CAT_T);
								
								if(cat == NULL)
								{
										RGX_DestroyNode(tmp.node);
										tmp.node = NULL;
										
										__SET_ERR(g_res, NULL, NULL, NULL, AR_E_NOMEM);
										
										goto INVALID_POINT;
								}
						}
						
						if((g_res.err.status = RGX_InsertToNode(cat, tmp.node)) != AR_S_YES)
						{
								RGX_DestroyNode(tmp.node);
								tmp.node = NULL;
								
								__SET_ERR(g_res, NULL, NULL, NULL, g_res.err.status);
								goto INVALID_POINT;
						}
				}
		}
		
		if(*p != tc)
		{ 
				__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
				goto INVALID_POINT;
		}
		
		if(cat == NULL && branch == NULL) 
		{ 
				__SET_ERR(g_res, NULL, NULL, p, AR_S_NO);
				goto INVALID_POINT;
		}
		
		
		if(cat != NULL && branch != NULL)
		{
				if((g_res.err.status = RGX_InsertToNode(branch, cat)) != AR_S_YES)
				{
						__SET_ERR(g_res, NULL, NULL, p, g_res.err.status);
						goto INVALID_POINT;
				}else
				{
						cat = NULL;
				}
		}
		
		g_res.next = (*p == L'\0' ? p : ++p);
		g_res.node = (branch != NULL ? branch : cat);
		g_res.err.pos = NULL;
		g_res.err.status = AR_S_YES;
		
		return g_res;
		
		
INVALID_POINT:
		if(cat != NULL)
		{
				RGX_DestroyNode(cat);
				cat = NULL;
		}
		
		if(branch != NULL) 
		{
				RGX_DestroyNode(branch);
				branch = NULL;
		}
		
		if(g_res.node != NULL) 
		{
				RGX_DestroyNode(g_res.node);
				g_res.node = NULL;
		}
		
		g_res.node = NULL; 
		g_res.next = NULL;
		return g_res;
}



rgxResult_t	RGX_ParseExpr(const wchar_t *expr, const rgxNameSet_t *name_set)
{
		AR_ASSERT(expr != NULL && name_set != NULL);
		return __handle_expr(expr, L'\0', name_set);
}



#undef __SET_ERR



AR_NAMESPACE_END



#endif
