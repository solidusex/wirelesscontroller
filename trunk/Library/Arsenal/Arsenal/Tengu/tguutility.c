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

#include "tguutility.h"



AR_NAMESPACE_BEGIN



/*******************************************tengu string table*****************************************************/


static arSpinLock_t		__g_tbl_lock;
static arStringTable_t *__g_tbl = NULL;


static void		__init_string_table()
{
		AR_ASSERT(__g_tbl == NULL);
		AR_InitSpinLock(&__g_tbl_lock);
		__g_tbl			=		AR_CreateStrTable(TGU_STRTBL_BUCKET);
}

static void __uninit_string_table()
{
		AR_ASSERT(__g_tbl != NULL);
		AR_DestroyStrTable(__g_tbl);
		AR_UnInitSpinLock(&__g_tbl_lock);
		__g_tbl = NULL;

}




const wchar_t*	TGU_AllocString(const wchar_t *str)
{
		const wchar_t *res;

		
		AR_LockSpinLock(&__g_tbl_lock);
		res = AR_GetString(__g_tbl, str);
		AR_UnLockSpinLock(&__g_tbl_lock);
		return res;
}


const wchar_t*	TGU_AllocStringN(const wchar_t *str, size_t n)
{
		const wchar_t *res;

		AR_LockSpinLock(&__g_tbl_lock);
		res = AR_GetStringN(__g_tbl, str,n);
		AR_UnLockSpinLock(&__g_tbl_lock);

		return res;
}


const wchar_t*  TGU_AllocStringInt(int_64_t num, size_t radix)
{
		const wchar_t *res;
		AR_LockSpinLock(&__g_tbl_lock);
		res = AR_GetStringInt(__g_tbl, num, radix);
		AR_UnLockSpinLock(&__g_tbl_lock);
		return res;
}

const wchar_t*  TGU_AllocStringUInt(uint_64_t num, size_t radix)
{
		const wchar_t *res;
		AR_LockSpinLock(&__g_tbl_lock);
		res = AR_GetStringUInt(__g_tbl, num, radix);
		AR_UnLockSpinLock(&__g_tbl_lock);
		return res;
}

const wchar_t*  TGU_AllocStringFloat(double num)
{
		const wchar_t *res;
		AR_LockSpinLock(&__g_tbl_lock);
		res = AR_GetStringFloat(__g_tbl, num, 500);
		AR_UnLockSpinLock(&__g_tbl_lock);
		return res;
}


bool_t			TGU_HasString(const wchar_t *name)
{
		bool_t	res;
		AR_ASSERT(name != NULL);

		AR_LockSpinLock(&__g_tbl_lock);
		res = AR_HasString(__g_tbl, name) == AR_S_YES;
		AR_UnLockSpinLock(&__g_tbl_lock);
		return res;
}










/***************************************************************Sources**************************************************************/



tguSrc_t*		TGU_LoadSources(const wchar_t *work_dir, const wchar_t *file_name)
{
		tguSrc_t		*src;
		wchar_t			path[1024];
		size_t			len_of_name;
		const wchar_t	*end_of_name;
		AR_ASSERT(work_dir != NULL && file_name != NULL);

		if(AR_wcslen(file_name) == 0 || AR_wcslen(work_dir) == 0)
		{
				return NULL;
		}

		AR_wcscpy(path, work_dir);
		
		if(work_dir[AR_wcslen(work_dir)-1] != AR_PATH_SP_CHAR)
		{
				AR_wcscat(path, AR_PATH_SP);
		}
		AR_wcscat(path, file_name);

		src = AR_NEW0(tguSrc_t);
		src->path = AR_wcsdup(path);
		
		end_of_name = AR_wcsstr(file_name, L".");

		if(end_of_name == NULL)
		{
				len_of_name = AR_wcslen(file_name);
		}else
		{
				len_of_name = end_of_name - file_name;
		}

		src->module_name = AR_wcsndup(file_name, len_of_name);


		{
				arString_t *str;

				str = AR_CreateString();
				if(AR_LoadBomTextFile(path, NULL, str) != AR_S_YES)
				{
						src->code = AR_wcsdup(AR_GetStringCString(str));
				}else
				{
						src->code = NULL;
				}
				AR_DestroyString(str);
		}

		if(!src->code)
		{
				TGU_ReleaseSources(src);
				src = NULL;
		}

		return src;
}


void			TGU_ReleaseSources(tguSrc_t		*src)
{
		AR_ASSERT(src != NULL);
		
		if(src->path)
		{
				AR_DEL(src->path);
				src->path = NULL;
		}

		if(src->module_name)
		{
				AR_DEL(src->module_name);
				src->module_name = NULL;
		}

		if(src->code)
		{
				AR_DEL(src->code);
				src->code = NULL;
		}

		AR_DEL(src);
}




/*************************************************************************************************************************************/

void	TGU_InitUtility()
{
		__init_string_table();
}

void	TGU_UnInitUtility()
{
		__uninit_string_table();
}










AR_NAMESPACE_END