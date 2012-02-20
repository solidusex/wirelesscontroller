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

#include "lalr.h"
#include "parser_in.h"

AR_NAMESPACE_BEGIN


static arSpinLock_t		__tbl_lock;
static arStringTable_t *__tbl = NULL;

const psrSymb_t	*PARSER_EOISymb = NULL;   /*表示输入结尾符号*/
const psrSymb_t	*PARSER_ErrorSymb= NULL;/*特殊的错误处理产生式标记终结符，*/
const psrSymb_t	*PARSER_DefPrecSymb = NULL;/*提供默认prec和assoc属性的终结符*/

/*以下都为非终结符*/
const psrSymb_t	*PARSER_StartSymb = NULL;



bool_t			Parser_IsBuildInSymbol(const psrSymb_t		*symb)
{
		AR_ASSERT(symb != NULL);

		if(Parser_CompSymb(symb,PARSER_EOISymb) == 0)
		{
				return true;
		}

		if(Parser_CompSymb(symb,PARSER_ErrorSymb) == 0)
		{
				return true;
		}

		if(Parser_CompSymb(symb,PARSER_DefPrecSymb) == 0)
		{
				return true;
		}

		if(Parser_CompSymb(symb,PARSER_StartSymb) == 0)
		{
				return true;
		}

		return false;
}



/******************************************************************************************************************************************/

arStatus_t	Parser_Init()
{
		AR_InitSpinLock(&__tbl_lock);
		__tbl			=			AR_CreateStrTable(PARSER_STRTBL_BUCKET);

		if(__tbl == NULL)
		{
				AR_error(AR_ERR_FATAL, L"parser initialize failed\r\n");
				return AR_S_NO;/*避免warning*/
		}

		PARSER_EOISymb		=		Parser_CreateSymb(L"%EOI", PARSER_TERM);
		PARSER_ErrorSymb	=		Parser_CreateSymb(L"error", PARSER_TERM);
		PARSER_DefPrecSymb	=		Parser_CreateSymb(L"%PREC_ASSOC", PARSER_TERM);
		PARSER_StartSymb	=		Parser_CreateSymb(L"%START", PARSER_NONTERM);


		if(PARSER_EOISymb == NULL || PARSER_ErrorSymb == NULL || PARSER_DefPrecSymb == NULL || PARSER_StartSymb == NULL)
		{
				AR_error(AR_ERR_FATAL, L"parser initialize failed\r\n");
				return AR_S_NO;/*避免warning*/
		}


		Parser_Init_LALR_Config();
		return AR_S_YES;
}


arStatus_t	Parser_UnInit()
{
		Parser_UnInit_LALR_Config();

		AR_ASSERT(PARSER_EOISymb->ref_count == 1);
		AR_ASSERT(PARSER_ErrorSymb->ref_count == 1);
		AR_ASSERT(PARSER_DefPrecSymb->ref_count == 1);
		AR_ASSERT(PARSER_StartSymb->ref_count == 1);

		Parser_DestroySymb((psrSymb_t*)PARSER_EOISymb);
		Parser_DestroySymb((psrSymb_t*)PARSER_ErrorSymb);
		Parser_DestroySymb((psrSymb_t*)PARSER_DefPrecSymb);
		Parser_DestroySymb((psrSymb_t*)PARSER_StartSymb);

		AR_DestroyStrTable(__tbl);
		AR_UnInitSpinLock(&__tbl_lock);
		__tbl = NULL;
		return AR_S_YES;
}



/***********************************************StringTable************************************/





const wchar_t*	Parser_AllocString(const wchar_t *str)
{
		const wchar_t *res;
		AR_LockSpinLock(&__tbl_lock);
		res = AR_GetString(__tbl, str);
		AR_UnLockSpinLock(&__tbl_lock);
		return res;
}

const wchar_t*	Parser_AllocStringN(const wchar_t *str, size_t n)
{
		const wchar_t *res;
		AR_LockSpinLock(&__tbl_lock);
		res = AR_GetStringN(__tbl, str,n);
		AR_UnLockSpinLock(&__tbl_lock);
		return res;
}


/*
const wchar_t*  Parser_AllocStringInt(int_64_t num, size_t radix)
{
		const wchar_t *res;
		AR_LockSpinLock(&__tbl_lock);
		res = AR_GetStringInt(__tbl, num, radix);
		AR_UnLockSpinLock(&__tbl_lock);
		return res;
}

const wchar_t*  Parser_AllocStringUInt(uint_64_t num, size_t radix)
{
		const wchar_t *res;
		AR_LockSpinLock(&__tbl_lock);
		res = AR_GetStringUInt(__tbl, num, radix);
		AR_UnLockSpinLock(&__tbl_lock);
		return res;
}
*/

AR_NAMESPACE_END

