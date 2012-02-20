
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


const wchar_t *RGX_INS_NAME[] = 
{
		L"nop",
		L"char",
		L"match_begin",
		L"match_end",
		L"match_line_begin",
		L"match_line_end",
		L"match_any_char",
		L"loop_begin",
		L"loop_end",
		L"lookahead_begin",
		L"lookahead_end",
		L"jmp",
		L"branch",
		L"match"
};



void					RGX_InitNameSet(rgxNameSet_t	*set)
{
		AR_ASSERT(set != NULL);
		AR_memset(set, 0, sizeof(*set));
}



void			RGX_ClearNameSet(rgxNameSet_t *set)
{
		size_t i;

		AR_ASSERT(set != NULL);

		for(i = 0; i < set->count; ++i)
		{
				AR_ASSERT(set->name[i].node);
				RGX_DestroyNode(set->name[i].node);
		}

		set->count = 0;

}

void					RGX_UnInitNameSet(rgxNameSet_t	*set)
{
		RGX_ClearNameSet(set);
		if(set->name)AR_DEL(set->name);

		AR_memset(set,0,sizeof(*set));
}

arStatus_t				RGX_InsertToNameSet(rgxNameSet_t	*set, const wchar_t	*name, rgxNode_t *node)
{

		AR_ASSERT(set != NULL && name != NULL && node != NULL);
		
		if(RGX_FindFromNameSet(set, name) != NULL)
		{
				return AR_S_NO;
		}

		if(set->count == set->cap)
		{
				size_t new_cap;
				rgxName_t *new_rgx;

				new_cap = (set->cap + 4)*2;
				new_rgx = AR_NEWARR(rgxName_t, new_cap);

				if(new_rgx == NULL)
				{
						return AR_E_NOMEM;
				}

				if(set->count > 0)
				{
						AR_memcpy(new_rgx, set->name, set->count * sizeof(rgxName_t));
				}
				
				if(set->name)
				{
						AR_DEL(set->name);
						set->name = NULL;
				}

				set->cap = new_cap;
				set->name = new_rgx;
				/*
				set->name = (rgxName_t*)AR_realloc(set->name, sizeof(rgxName_t) * set->cap);
				*/
		}

		AR_wcscpy(set->name[set->count].name, name);
		set->name[set->count].node = node;
		set->count++;
		return AR_S_YES;
}


arStatus_t				RGX_RemoveFromNameSet(rgxNameSet_t	*set, const wchar_t	*name)
{
		size_t i;
		AR_ASSERT(set != NULL && name != NULL);

		for(i = 0; i < set->count; ++i)
		{
				if(AR_wcscmp(set->name[i].name, name) == 0)
				{
						RGX_DestroyNode(set->name[i].node);
						break;
				}
		}

		if(i == set->count)
		{
				return AR_S_NO;
		}

		while(i < set->count - 1)
		{
				set->name[i] = set->name[i + 1];
				i++;
		}
		set->count--;

		return AR_S_YES;
}




const rgxNode_t*		RGX_FindFromNameSet(const rgxNameSet_t	*set, const wchar_t *name)
{
		size_t i;
		AR_ASSERT(set != NULL && name != NULL);

		for(i = 0; i < set->count; ++i)
		{
				if(AR_wcscmp(set->name[i].name, name) == 0)
				{
						AR_ASSERT(set->name[i].node != NULL);
						return set->name[i].node;
				}
		}

		return NULL;
}





/*Char Set*/




void RGX_InitCharSet(rgxCharSet_t *cset)
{
		AR_ASSERT(cset != NULL);
		AR_memset(cset, 0, sizeof(*cset));
}

void RGX_UnInitCharSet(rgxCharSet_t *cset)
{
		AR_ASSERT(cset != NULL);

		while(cset->range)
		{
				rgxCharRange_t		*tmp = cset->range;
				cset->range = cset->range->next;
				AR_DEL(tmp);
		}
}

arStatus_t RGX_CopyCharSet(rgxCharSet_t *dest, const rgxCharSet_t *sour)
{
		rgxCharRange_t *curr;
		AR_ASSERT(dest != NULL && sour != NULL);

		RGX_UnInitCharSet(dest);
		RGX_InitCharSet(dest);
		dest->is_neg = sour->is_neg;

		for(curr = sour->range; curr; curr = curr->next)
		{
				arStatus_t status;

				status = RGX_InsertRangeToCharSet(dest, curr);

				if(status != AR_S_YES)
				{
						return status;
				}
		}

		return AR_S_YES;
}



static rgxCharRange_t* __new_range(wchar_t beg, wchar_t end, rgxCharRange_t *next)
{
		rgxCharRange_t *res;
		AR_ASSERT(beg <= end);
		res = AR_NEW0(rgxCharRange_t);
		
		if(res != NULL)
		{
				res->beg = beg; res->end = end; res->next = next;
		}
	
		return res;
}



arStatus_t RGX_InsertRangeToCharSet(rgxCharSet_t *cset, const rgxCharRange_t *new_range)
{
		rgxCharRange_t		*curr, *prev;
		rgxCharRange_t		range;
		AR_ASSERT(cset != NULL && new_range != NULL && new_range->beg <= new_range->end);

		prev = NULL; curr = cset->range;
		range	= *new_range;

		while(curr != NULL)
		{
				if(curr->beg < range.beg)
				{
						if(curr->end < range.beg)
						{
								/*
							[ curr ]
										[ range ]
								*/


						}else if(curr->end < range.end)
						{
								/*
							[ curr ]
								[ range ]
								*/

								rgxCharRange_t		*tmp = __new_range(curr->beg, range.beg - 1, curr);

								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}

								if(prev == NULL)
								{
										cset->range = tmp;
										prev = tmp;
								}else
								{
										prev->next = tmp;
								}

								curr->beg = range.beg; range.beg = curr->end + 1;

						}else if(curr->end == range.end)
						{
								/*
							[     curr      ]
									 [ range]

								*/

								rgxCharRange_t		*tmp = __new_range(curr->beg, range.beg - 1, curr);

								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}


								if(prev == NULL)
								{
										cset->range = tmp;
										prev = tmp;
								}else
								{
										prev->next = tmp;
								}

								curr->beg = range.beg;
								return AR_S_YES;
						}else if(curr->end > range.end)
						{

								/*
								[  curr      ]
								  [ range ]
								*/
								rgxCharRange_t		*tmp1, *tmp2;
								tmp1 = __new_range(curr->beg, range.beg - 1, NULL);
								tmp2 = __new_range(range.beg, range.end, curr);

								if(tmp1 == NULL || tmp2 == NULL)
								{
										if(tmp1)
										{
												AR_DEL(tmp1);
												tmp1 = NULL;
										}

										if(tmp2)
										{
												AR_DEL(tmp2);
												tmp2 = NULL;
										}

										return AR_E_NOMEM;
								}

								if(prev == NULL)
								{
										cset->range = tmp1;
										prev = tmp1;
								}else
								{
										prev->next = tmp1;
								}

								
								tmp1->next = tmp2;
								curr->beg = range.end + 1;
								return AR_S_YES;
						}

				}else if(curr->beg == range.beg)
				{
						if(curr->end < range.end)
						{
								/*
								[curr]
								[ range ]
								*/
								range.beg = curr->end + 1;

						}else if(curr->end == range.end)
						{
								/*
								[curr ]
								[range]
								*/

								return AR_S_YES;
						}else if(curr->end > range.end)
						{
								/*
								[curr         ]
								[  range  ]

								*/

								rgxCharRange_t		*tmp;
								tmp = __new_range(range.beg, range.end, curr);

								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}

								if(prev == NULL)
								{
										cset->range = tmp;
										prev = tmp;
								}else
								{
										prev->next = tmp;
								}
								curr->beg = range.end + 1;
								return AR_S_YES;
						}

				}else /*if(curr->beg > range->beg)*/
				{
						if(curr->end < range.end)
						{
								/*
								  [curr]
								[ range  ]
								*/

								rgxCharRange_t		*tmp;
								tmp = __new_range(range.beg, curr->beg - 1, curr);

								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}


								if(prev == NULL)
								{
										cset->range = tmp;
										prev = tmp;
								}else
								{
										prev->next = tmp;
								}

								range.beg = curr->end + 1;

						}else if(curr->end == range.end)
						{
								/*
								    [curr]
								[ range  ]
								*/

								rgxCharRange_t		*tmp;
								tmp = __new_range(range.beg, curr->beg - 1, curr);

								if(tmp == NULL)
								{
										return AR_E_NOMEM;
								}

								if(prev == NULL)
								{
										cset->range = tmp;
										prev = tmp;
								}else
								{
										prev->next = tmp;
								}
								return AR_S_YES;
						}else/*curr->end > range->end*/
						{
								if(curr->beg <=range.end)
								{

										/*
									     	[curr]
										[range]
										*/

										rgxCharRange_t		*tmp1,*tmp2;

										tmp1 = __new_range(range.beg, curr->beg - 1, NULL);
										tmp2 = __new_range(curr->beg, range.end, curr);

										if(tmp1 == NULL || tmp2 == NULL)
										{
												if(tmp1)
												{
														AR_DEL(tmp1);
														tmp1 = NULL;
												}

												if(tmp2)
												{
														AR_DEL(tmp2);
														tmp2 = NULL;
												}

												return AR_E_NOMEM;
										}

										if(prev == NULL)
										{
												cset->range = tmp1;
												prev = tmp1;
										}else
										{
												prev->next = tmp1;
										}

										
										tmp1->next = tmp2;
										curr->beg = range.end + 1;
										return AR_S_YES;
								}else
								{
										/*
										       [curr]
									   [range]
										*/

										rgxCharRange_t		*tmp;
										tmp = __new_range(range.beg, range.end, curr);

										if(tmp == NULL)
										{
												return AR_E_NOMEM;
										}

										if(prev == NULL)
										{
												cset->range = tmp;
												prev = tmp;
										}else
										{
												prev->next = tmp;
										}
										return AR_S_YES;
								}
						}
				}

				prev = curr;
				curr = curr->next;
		}

		if(cset->range == NULL)
		{
				cset->range = __new_range(range.beg, range.end, NULL);
		}else
		{
				prev->next = __new_range(range.beg, range.end, NULL);
		}

		return AR_S_YES;

}

arStatus_t RGX_ReverseNegativeCharSet(rgxCharSet_t *cset)
{
		arStatus_t status;
		rgxCharRange_t			*curr, *prev, old;
		rgxCharSet_t			new_set;
		
		AR_ASSERT(cset != NULL);

		status = AR_S_YES;

		if(!cset->is_neg)
		{
				return AR_S_YES;
		}


		cset->is_neg = false;

		RGX_InitCharSet(&new_set);

		old.beg =  L'\0'; 
		old.end = AR_WCHARMAX;

		prev = NULL;

		for(curr = cset->range; curr != NULL; curr = curr->next)
		{
				if(curr->beg > old.beg)
				{
						old.end = curr->beg - 1;
						
						status = RGX_InsertRangeToCharSet(&new_set, &old);

						if(status != AR_S_YES)
						{
								goto END_POINT;
						}
				}

				old.beg = curr->end < AR_WCHARMAX ? curr->end + 1 : curr->end;
				old.end = AR_WCHARMAX;
				prev = curr;
		}

		if(old.beg < AR_WCHARMAX)
		{
				status = RGX_InsertRangeToCharSet(&new_set, &old);

				if(status != AR_S_YES)
				{
						goto END_POINT;
				}
		}

		curr = cset->range;
		cset->range = new_set.range;
		new_set.range = curr;

END_POINT:
		RGX_UnInitCharSet(&new_set);
		return status;
}

/*CharSet end*/

/***********************************************************/


rgxThread_t		RGX_BuildThread(rgxIns_t *pc, const wchar_t *sp, size_t x, size_t y, uint_32_t act)
{
		rgxThread_t tmp;
		AR_ASSERT(pc != NULL && sp != NULL);
		tmp.pc = pc;
		tmp.sp = sp;
		tmp.line = x;
		tmp.col = y;
		tmp.act = act;
		return tmp;
}

/*
void RGX_InitThreadList(rgxThreadList_t *lst)
{
		AR_ASSERT(lst != NULL);
		AR_memset(lst, 0, sizeof(*lst));
}

void RGX_UnInitThreadList(rgxThreadList_t *lst)
{
		AR_ASSERT(lst != NULL);
		if(lst->lst)
		{
				AR_DEL(lst->lst);
		}
		AR_memset(lst, 0, sizeof(*lst));
}
*/


/**********************************************************Global************************************************************/

static rgxThreadList_t	*__g_free_list = NULL;
static arSpinLock_t		__g_spin_lock;
static size_t			__g_max_thread_count = 0;

#if defined(AR_DEBUG)
		#define RGX_THREAD_LIST_INIT_COUNT		0
		#define RGX_THREAD_LIST_POOL_NUM		0
#else
		#define RGX_THREAD_LIST_INIT_COUNT		( 64 )
		#define RGX_THREAD_LIST_POOL_NUM		( 256 )
#endif


void	RGX_InitMisc()
{
		size_t i;
		rgxThreadList_t	**tmp;
		
		AR_InitSpinLock(&__g_spin_lock);
		__g_free_list = NULL;

/*************************************************/
		__g_max_thread_count = 0;
/*************************************************/

		if(RGX_THREAD_LIST_POOL_NUM == 0)return;

		tmp = AR_NEWARR0(rgxThreadList_t*, RGX_THREAD_LIST_POOL_NUM);

		if(tmp == NULL)
		{
				AR_error(AR_ERR_FATAL, L"initialize regex pool failed\r\n");
				return;
		}


		for(i = 0; i < RGX_THREAD_LIST_POOL_NUM; ++i)
		{
				tmp[i] = RGX_CreateThreadList();

				if(tmp[i] == NULL)
				{
						AR_error(AR_ERR_FATAL, L"initialize regex pool failed\r\n");
						return;
				}
		}

		for(i = 0; i < RGX_THREAD_LIST_POOL_NUM; ++i)
		{
				RGX_DestroyThreadList(tmp[i]);
		}

		AR_DEL(tmp);
}


void	RGX_UnInitMisc()
{
		size_t count = 0;
		
		while(__g_free_list != NULL)
		{
				rgxThreadList_t *lst = __g_free_list;
				__g_free_list = __g_free_list->next;
				
				AR_DEL(lst->lst);
				AR_DEL(lst);

				count++;
		}

		{
				wchar_t buf[1024];
				AR_swprintf(buf, 1024, L"Total consume rgxThreadList_t == %Iu", count);
				AR_LOG(L"%ls\r\n", buf);

				AR_swprintf(buf, 1024, L"Max consume rgxThread_t == %Iu",  __g_max_thread_count);
				AR_LOG(L"%ls\r\n", buf);
		}

	
		AR_UnInitSpinLock(&__g_spin_lock);
}

/*****************************************************************************************************************************/

static rgxThreadList_t* __create_new_thread_list()
{
		rgxThreadList_t	*res = NULL;
		res = AR_NEW(rgxThreadList_t);

		if(res == NULL)
		{
				return res;
		}

		res->lst = AR_NEWARR(rgxThread_t, AR_RGX_MAX_THREAD_CNT);

		if(res->lst == NULL)
		{
				AR_DEL(res);
				res = NULL;
				return NULL;
		}
		
		res->count = 0;
		res->next = NULL;
		
		return res;
}



rgxThreadList_t*	RGX_CreateThreadList()
{

		rgxThreadList_t	*res = NULL;


		if(__g_free_list == NULL)
		{
				res = __create_new_thread_list();
		}else
		{
				AR_LockSpinLock(&__g_spin_lock);

				if(__g_free_list == NULL)
				{
						res = __create_new_thread_list();
				}else
				{
						res = __g_free_list;
						__g_free_list = __g_free_list->next;
						res->next = NULL;
				}

				AR_UnLockSpinLock(&__g_spin_lock);
		}

		if(res)
		{
				RGX_ClearThreadList(res);
		}

		return res;

}

void				RGX_DestroyThreadList(rgxThreadList_t *lst)
{
		AR_ASSERT(lst != NULL);
		AR_ASSERT(lst->next == NULL);
		AR_LockSpinLock(&__g_spin_lock);
		lst->next = __g_free_list;
		__g_free_list = lst;
		AR_UnLockSpinLock(&__g_spin_lock);
}







void RGX_InsertToThreadList(rgxThreadList_t *lst, rgxThread_t thd)
{
		AR_ASSERT(lst != NULL);
		AR_ASSERT(thd.pc != NULL && thd.sp != NULL);

		if(lst->count >= AR_RGX_MAX_THREAD_CNT)
		{
				AR_error(AR_ERR_FATAL, L"regex thread list overflow\r\n");
		}else
		{
				lst->lst[lst->count++] = thd;

		}

		if(lst->count > __g_max_thread_count)
		{
				__g_max_thread_count = lst->count;
		}

}


void RGX_SwapThreadList(rgxThreadList_t *l, rgxThreadList_t *r)
{
		rgxThreadList_t tmp;
		AR_ASSERT(l != NULL && r != NULL);
		tmp = *l;
		*l = *r;
		*r = tmp;
}


void RGX_ClearThreadList(rgxThreadList_t *l)
{
		AR_ASSERT(l != NULL);
		l->count = 0;
}


AR_NAMESPACE_END

