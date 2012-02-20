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

const psrSymb_t*		Parser_CreateSymbN(const wchar_t *name, size_t n, psrSymbType_t t)
{
		psrSymb_t *res;
		AR_ASSERT(name != NULL && n > 0);

		res = AR_NEW0(psrSymb_t);

		if(res == NULL)
		{
				return res;
		}

		res->name = Parser_AllocStringN(name, n);

		if(res->name == NULL)
		{
				AR_DEL(res);
				res = NULL;
				return NULL;
		}

		res->type = t;
		res->hash_code = AR_wcshash(res->name);
		res->ref_count = 1;
		
		return res;
}

const psrSymb_t*		Parser_CreateSymb(const wchar_t *name, psrSymbType_t t)
{
		size_t n;
		AR_ASSERT(name != NULL);
		n = AR_wcslen(name);
		AR_ASSERT(n > 0);
		return Parser_CreateSymbN(name, n, t);
}



#if(0)
const psrSymb_t*		Parser_CreateSymb(const wchar_t *name, psrSymbType_t t)
{
		psrSymb_t		*res;
		AR_ASSERT(name != NULL && AR_wcslen(name) > 0);
		res = AR_NEW0(psrSymb_t);

		if(res == NULL)
		{
				return res;
		}

		res->name = Parser_AllocString(name);

		if(res->name == NULL)
		{
				AR_DEL(res);
				res = NULL;
				return NULL;
		}

		res->type = t;
		res->hash_code = AR_wcshash(res->name);
		res->ref_count = 1;
		
		/*
		wprintf(L"%s : (%s : %p) : %d\r\n", name, res->name, res->name, res->hash_code);
		*/
		return res;

}
#endif



#if defined(AR_DEBUG)
static void __trace_symb_refcount(const psrSymb_t *symb)
{
		AR_UNUSED(symb);

		/*
		if(symb == PARSER_StartSymb)
		{

				int x;
				x = 0;
				++x;
		}
		*/
}

#else

#define __trace_symb_refcount(_ptr) do{}while(0)

#endif



const psrSymb_t*		Parser_CopyNewSymb(const psrSymb_t *sour)
{
		AR_ASSERT(sour != NULL && sour->ref_count > 0);

		__trace_symb_refcount(sour);
		/*
		for(;;)
		{
				volatile int_t tmp = sour->ref_count;
				AR_ASSERT(tmp >= 1);
				
				if(AR_CompExchange((uint_t*)&sour->ref_count, tmp+1, tmp) == (uint_t)tmp)
				{
						break;
				}
		}
		*/
		AR_AtomicInc((volatile int_t*)&sour->ref_count);
		return sour;

}

void			Parser_DestroySymb(const psrSymb_t *symb)
{
		
		AR_ASSERT(symb != NULL && symb->ref_count > 0);
		
		__trace_symb_refcount(symb);
		/*
		for(;;)
		{
				volatile int_t tmp = symb->ref_count;
				AR_ASSERT(tmp >= 1);
				
				if(AR_CompExchange((uint_t*)&symb->ref_count, tmp-1, tmp) == (uint_t)tmp)
				{
						if(tmp == 1)
						{
								AR_DEL((psrSymb_t*)symb);
						}
						break;
				}
		}
		*/

		if(AR_AtomicDec((volatile int_t*)&symb->ref_count) == 0)
		{
				AR_DEL((psrSymb_t*)symb);
		}

}



/*
const psrSymb_t*		Parser_CopyNewSymb(const psrSymb_t *sour)
{
		AR_ASSERT(sour != NULL && sour->ref_count > 0);

		((psrSymb_t*)sour)->ref_count++;
		return sour;

}

void			Parser_DestroySymb(const psrSymb_t *symb)
{
		
		AR_ASSERT(symb != NULL && symb->ref_count > 0);
		
		if(--((psrSymb_t*)symb)->ref_count == 0)
		{
				AR_DEL((psrSymb_t*)symb);
		}
}

*/





#if(0)
int_t					Parser_CompSymb(const psrSymb_t *l, const psrSymb_t *r)
{
		int_t cmp;
		AR_ASSERT(l != NULL && r != NULL);
		if(l == r)return 0;
		cmp = AR_CMP(l->type, r->type);
		if(cmp != 0)return cmp;
		cmp = AR_CMP(l->hash_code, r->hash_code);
		if(cmp != 0)return cmp;
		/*为何靠对比指针来断定字符串请参阅parser_in.h*/


		return AR_CMP(l->name, r->name);		
}
#endif



int_t					Parser_CompSymb(const psrSymb_t *l, const psrSymb_t *r)
{
		int_t cmp;
		AR_ASSERT(l != NULL && r != NULL);
		
		if(l == r)return 0;

		cmp = (int_t)l->type - (int_t)r->type;
		if(cmp != 0) return cmp;

		cmp = l->hash_code - r->hash_code;
		if(cmp != 0) return cmp;

		cmp = (int_t)l->name - (int_t)r->name;
		
		return cmp;
}


void	Parser_InitSymbList(psrSymbList_t *symb_lst)
{
		AR_ASSERT(symb_lst != NULL);
		AR_memset(symb_lst, 0, sizeof(*symb_lst));
}

void	Parser_UnInitSymbList(psrSymbList_t *symb_lst)
{
		AR_ASSERT(symb_lst != NULL);
		if(symb_lst->lst != NULL)
		{
				AR_DEL((psrSymb_t**)symb_lst->lst);
		}

		AR_memset(symb_lst, 0, sizeof(*symb_lst));
}


void	Parser_ClearSymbList(psrSymbList_t *symb_lst)
{
		AR_ASSERT(symb_lst != NULL);
		symb_lst->count = 0;
}



arStatus_t				Parser_CopySymbList(psrSymbList_t *dest, const psrSymbList_t *sour)
{
		size_t i;
		arStatus_t status;
		AR_ASSERT(dest != NULL && sour != NULL);

		status = AR_S_YES;

		for(i = 0; i < sour->count; ++i)
		{
				status = Parser_InsertToSymbList(dest, sour->lst[i]);

				if(status != AR_S_YES)
				{
						return status;
				}
		}

		return status;
}


arStatus_t	Parser_InsertToSymbList(psrSymbList_t *symb_lst, const psrSymb_t *symb)
{
		arStatus_t status;
		AR_ASSERT(symb_lst != NULL && symb != NULL);
		
		status = Parser_ReserveSymbListCapacity(symb_lst, symb_lst->count + 1);

		if(status != AR_S_YES)
		{
				return status;
		}

		symb_lst->lst[symb_lst->count++] = symb;

		return status;
}




arStatus_t			Parser_ReserveSymbListCapacity(psrSymbList_t *symb_lst, size_t cap)
{

		AR_ASSERT(symb_lst != NULL);

		if(cap > symb_lst->cap)
		{
				const psrSymb_t **new_lst;
				new_lst = AR_NEWARR(const psrSymb_t*, cap);

				if(new_lst == NULL)
				{
						return AR_E_NOMEM;
				}

				AR_memcpy((psrSymb_t **)new_lst, symb_lst->lst, symb_lst->count * sizeof(const psrSymb_t*));

				AR_DEL(symb_lst->lst);

				symb_lst->cap = cap;
				symb_lst->lst = new_lst;
		}

		return AR_S_YES;
}



arStatus_t			Parser_RemoveFromSymbListByIndex(psrSymbList_t *symb_lst, size_t index)
{
		size_t i;
		AR_ASSERT(symb_lst != NULL && index < symb_lst->count);
		
		if(index >= symb_lst->count)
		{
				return AR_S_NO;
		}

		i = index;
		while(i < symb_lst->count - 1)
		{
				symb_lst->lst[i] = symb_lst->lst[i+1];
				i++;
		}
		
		symb_lst->count--;
		return AR_S_YES;
		
}

const psrSymb_t*	Parser_IndexOfSymbList(const psrSymbList_t *symb_lst, size_t idx)
{
		AR_ASSERT(symb_lst != NULL);
		
		if(idx >= symb_lst->count)
		{
				return NULL;
		}else
		{
				return symb_lst->lst[idx];
		}
}

int_t				Parser_FindFromSymbList(const psrSymbList_t *symb_lst, const psrSymb_t* symb)
{
		int_t i;

		for(i = 0; i < (int_t)symb_lst->count; ++i)
		{
				if(Parser_CompSymb(symb_lst->lst[i], symb) == 0)return i;
		}
		return -1;
}



int_t				Parser_BSearchFromSymbList(const psrSymbList_t *symb_lst, const psrSymb_t* symb)
{
		int_t l,r,m,cmp;
		AR_ASSERT(symb_lst != NULL && symb != NULL);


		l = 0; r = symb_lst->count - 1;
		while( l <= r )
		{
				m = (l + r)/2;
				
				cmp = Parser_CompSymb(symb_lst->lst[m], symb);

				if(cmp < 0)
				{
						l = m + 1;
				}else if(cmp == 0)
				{
						return m;
				}else	/*cmp > 0*/
				{
						r = m - 1;
				}

		}
		return -1;
}

/*
static int __comp_symb(const void *left, const void *right)
{
		const psrSymb_t *l,*r;
		l = *(const psrSymb_t**)left;
		r = *(const psrSymb_t**)right;

		AR_ASSERT(l != NULL && r != NULL);
		return (int)Parser_CompSymb(l,r);
}



*/

static int_t __comp_symb(const void *left, const void *right)
{
		const psrSymb_t *l,*r;
		l = *(const psrSymb_t**)left;
		r = *(const psrSymb_t**)right;

		AR_ASSERT(l != NULL && r != NULL);
		return Parser_CompSymb(l,r);
}

void			Parser_SortSymbList(psrSymbList_t *symb_lst)
{
		AR_ASSERT(symb_lst != NULL);
		
		if(symb_lst->count > 0)
		{
				AR_qsort((void*)symb_lst->lst, symb_lst->count, sizeof(psrSymb_t*), __comp_symb);
		}
}


arStatus_t				Parser_InsertToSymbList_Unique(psrSymbList_t *symb_lst, const psrSymb_t *symb)
{
		AR_ASSERT(symb_lst != NULL && symb != NULL);
		if(Parser_FindFromSymbList(symb_lst, symb) != -1)
		{
				return AR_S_NO;
		}

		return Parser_InsertToSymbList(symb_lst, symb);
}


/********************************************************************************************************/
arStatus_t			Parser_PrintSymbol(const psrSymb_t *symb, arString_t *str)
{
		if(symb->type == PARSER_TERM)
		{
				return AR_AppendFormatString(str, L"%ls ", symb->name);
				
		}else
		{
				return AR_AppendFormatString(str, L"<%ls> ", symb->name);
		}
}


arStatus_t			Parser_PrintSymbolList(const psrSymbList_t *lst, arString_t *str)
{
		size_t i;
		
		for(i = 0; i < lst->count; ++i)
		{
				arStatus_t status;

				status = Parser_PrintSymbol(lst->lst[i], str);

				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendFormatString(str, L" ");

				if(status != AR_S_YES)
				{
						return status;
				}
		}

		return AR_S_YES;
}



/**************************************Symbol Map**********************************************************/

void					Parser_InitSymbMap(psrSymbMap_t *map)
{
		AR_ASSERT(map != NULL);
		AR_memset(map, 0, sizeof(*map));
}

void					Parser_UnInitSymbMap(psrSymbMap_t *map)
{
		size_t i;
		psrMapRec_t *rec, *tmp;
		
		AR_ASSERT(map != NULL);

		for(i = 0; i < MAP_BUCKET_SIZE; ++i)
		{
				rec = map->bucket[i];
				while(rec)
				{
						tmp = rec->next;
						Parser_UnInitSymbList(&rec->lst);
						AR_DEL(rec);
						rec = tmp;
				}
		}
}


arStatus_t					Parser_InsertToSymbMap(psrSymbMap_t *map, const psrSymb_t *key, const psrSymb_t *val)
{
		psrMapRec_t *rec, *tmp;
		AR_ASSERT(map != NULL && key != NULL);
		
		rec = map->bucket[key->hash_code % MAP_BUCKET_SIZE];
		

		if(rec)
		{
				for(tmp = rec; tmp; tmp = tmp->next)
				{
						if(Parser_CompSymb(tmp->key, key) == 0)
						{
								break;
						}
				}

				if(tmp == NULL)
				{
						tmp = AR_NEW0(psrMapRec_t);

						if(tmp != NULL)
						{
								tmp->key = key;
								Parser_InitSymbList(&tmp->lst);
								tmp->next = map->bucket[key->hash_code % MAP_BUCKET_SIZE];
								map->bucket[key->hash_code % MAP_BUCKET_SIZE] = tmp;
								map->item_count++;
						}
				}
				rec = tmp;
		}else
		{
				rec = AR_NEW0(psrMapRec_t);

				if(rec != NULL)
				{
						rec->key = key;
						rec->can_empty = false;
						Parser_InitSymbList(&rec->lst);
						rec->next = map->bucket[key->hash_code % MAP_BUCKET_SIZE];
						map->bucket[key->hash_code % MAP_BUCKET_SIZE] = rec;
						map->item_count++;
				}
		}
		
		if(rec)
		{
				if(val)
				{
						return Parser_InsertToSymbList_Unique(&rec->lst, val);
				}else
				{
						return AR_S_NO;
				}
		}else
		{
				return AR_E_NOMEM;
		}
}


psrMapRec_t*		Parser_GetSymbolFromSymbMap(const psrSymbMap_t *map, const psrSymb_t *key)
{
		const psrMapRec_t *rec;

		rec = map->bucket[key->hash_code % MAP_BUCKET_SIZE];

		while(rec)
		{
				if(Parser_CompSymb(key, rec->key) == 0)break;
				rec = rec->next;
		}
		return (psrMapRec_t*)rec;
}


arStatus_t				Parser_SetSymbEpsilon(psrSymbMap_t *map, const psrSymb_t *key, bool_t is_epsilon)
{
		psrMapRec_t *rec;
		AR_ASSERT(map != NULL && key != NULL);
		rec = Parser_GetSymbolFromSymbMap(map, key);

		if(rec)
		{
				rec->can_empty = is_epsilon;
				return AR_S_YES;
		}else
		{
				return AR_S_NO;
		}
}



#define __CHECK_RET_VAL(_call_stmt)						\
		do{												\
				arStatus_t status = _call_stmt;			\
				if(status != AR_S_YES)					\
				{										\
						return status;					\
				}										\
		}while(0)


arStatus_t		Parser_PrintSymbolMap(const psrSymbMap_t *map, arString_t *str)
{
		size_t i;

		for(i = 0; i < MAP_BUCKET_SIZE; ++i)
		{
				const psrMapRec_t *rec;
				rec = map->bucket[i];
				while(rec)
				{
						if(rec->key->type == PARSER_NONTERM)
						{
								__CHECK_RET_VAL(Parser_PrintSymbol(rec->key, str));

								__CHECK_RET_VAL(AR_AppendString(str, L" : "));
								__CHECK_RET_VAL(Parser_PrintSymbolList(&rec->lst, str));
								__CHECK_RET_VAL(AR_AppendFormatString(str, L"\r\n"));
						}
						rec = rec->next;
				}
		}

		for(i = 0; i < MAP_BUCKET_SIZE; ++i)
		{
				const psrMapRec_t *rec;
				rec = map->bucket[i];
				while(rec)
				{
						if(rec->key->type == PARSER_TERM)
						{
								__CHECK_RET_VAL(Parser_PrintSymbol(rec->key, str));
								__CHECK_RET_VAL(AR_AppendString(str, L" : "));
								__CHECK_RET_VAL(Parser_PrintSymbolList(&rec->lst, str));
								__CHECK_RET_VAL(AR_AppendFormatString(str, L"\r\n"));
						}
						rec = rec->next;
				}
		}

		return AR_S_YES;
}






AR_NAMESPACE_END
