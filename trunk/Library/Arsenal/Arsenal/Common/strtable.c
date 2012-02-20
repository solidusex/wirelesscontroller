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
#include "common.h"



AR_NAMESPACE_BEGIN


typedef struct __arsenal_str_rec		arStringRec_t;
struct __arsenal_str_rec
{
		wchar_t					 *str;
		size_t					 len;
		struct __arsenal_str_rec *next;
};


struct __string_table_
{
		arStringRec_t	**bucket;
		size_t			count;
		size_t			item_count;
};


arStringTable_t*		AR_CreateStrTable(size_t count)
{
		arStringTable_t		*res;

		res = AR_NEW0(arStringTable_t);

		if(res == NULL)
		{
				return NULL;
		}

		
		if(count < MIN_BUCKET_SIZE)
		{
				count = MIN_BUCKET_SIZE;
		}

		res->count = count;
		res->item_count = 0;

		res->bucket = AR_NEWARR0(arStringRec_t*, res->count);
		
		if(res->bucket == NULL)
		{
				AR_DEL(res);
				res = NULL;
		}
		return res;
}


void					AR_DestroyStrTable(arStringTable_t* tbl)
{
		size_t i;
		arStringRec_t *curr, *tmp;		
		AR_ASSERT(tbl != NULL);

		for(i = 0; i < tbl->count; ++i)
		{
				curr = tbl->bucket[i];
				while(curr)
				{
						tmp = curr->next;
						AR_DEL(curr->str);
						AR_DEL(curr);
						curr = tmp;
				}
		}

		if(tbl->bucket)AR_DEL(tbl->bucket);
		AR_DEL(tbl);
}



const wchar_t*			AR_GetString(arStringTable_t *tbl, const wchar_t *str)
{
		size_t n;
		AR_ASSERT(tbl != NULL && str != NULL);
		n = AR_wcslen(str);
		return AR_GetStringN(tbl, str, n);
}


arStatus_t				AR_HasString(const arStringTable_t *tbl, const wchar_t *str)
{
		AR_ASSERT(tbl != NULL && str != NULL);
		return AR_HasStringN(tbl, str, AR_wcslen(str));
}



arStatus_t					AR_HasStringN(const arStringTable_t *tbl, const wchar_t *str, size_t n)
{
		const arStringRec_t		*record;
		AR_ASSERT(tbl != NULL && str != NULL);
		record = tbl->bucket[AR_wcshash_n(str, n) % tbl->count];
		
		while(record)
		{
				if(record->len == n && AR_wcsncmp(record->str, str, n) == 0)
				{
						return AR_S_YES;
				}
				record=record->next;
		}
		return AR_S_NO;
}

const wchar_t*			AR_GetStringN(arStringTable_t *tbl, const wchar_t *str, size_t n)
{

		size_t idx;
		arStringRec_t		*record;
		AR_ASSERT(tbl != NULL && str != NULL);

		idx =  AR_wcshash_n(str, n) % tbl->count;
		record = tbl->bucket[idx];
		
		while(record)
		{
				if(n == record->len && AR_wcsncmp(record->str, str, n) == 0)
				{
						return record->str;
				}
				record=record->next;
		}

		

		/***************************´´½¨ÐÂrecord*************************/
		record = AR_NEW0(arStringRec_t);

		if(record == NULL)
		{
				return NULL;
		}
		
		record->str = AR_wcsndup(str, n);

		if(record->str == NULL)
		{
				AR_DEL(record);
				record = NULL;
				return NULL;
		}

		record->len = n;
		record->next = tbl->bucket[idx];

		tbl->bucket[idx] = record;
		tbl->item_count++;
		return record->str;
}



const wchar_t*			AR_GetStringInt(arStringTable_t *tbl, int_64_t num, size_t radix)
{
		wchar_t buf[1024];

		AR_ASSERT(tbl != NULL && radix > 1 && radix <= 16);
		AR_i64tow_buf(buf, 1024, num, radix);
		return AR_GetString(tbl, buf);
}

const wchar_t*			AR_GetStringUInt(arStringTable_t *tbl, uint_64_t num, size_t radix)
{
		wchar_t buf[1024];
		
		AR_ASSERT(tbl != NULL && radix > 1 && radix <= 16);
		
		AR_u64tow_buf(buf, 1024, num, radix);
		
		return AR_GetString(tbl, buf);
}


const wchar_t*			AR_GetStringFloat(arStringTable_t *tbl, double num, size_t prec)
{
		wchar_t buf[1024];
		
		AR_ASSERT(tbl != NULL && prec > 0);
		
		AR_swprintf(buf, 1024, L"%.*g", (uint_32_t)prec, num);
		
		return AR_GetString(tbl, buf);
}


/******************************************************************************************************************/


AR_NAMESPACE_END

