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



#include "Arsenal.h"



AR_NAMESPACE_BEGIN


static bool_t	__g_is_initialized = false;




arStatus_t	Arsenal_Init(const arInit_t *ctx)
{

        arStatus_t	result;
		uint_64_t		total_beg, total_end;
		/*AR_ASSERT(ctx != NULL);*/
		AR_ASSERT(!__g_is_initialized);
		result = AR_S_YES;
		total_beg = AR_GetTime_Milliseconds();
		
		if(!__g_is_initialized)
		{
				AR_CommonInit(ctx);
				Lex_Init();
				Parser_Init();
				Tools_Init();
				TGU_Init();

				__g_is_initialized = true;
				result = AR_S_YES;
		}else
		{
				result = AR_S_NO;
		}

		total_end = AR_GetTime_Milliseconds();



		if(result == AR_S_YES)
		{
				wchar_t msg[1024];
				AR_swprintf(msg, AR_NELEMS(msg), L"Arsenal initialized consume time == %Id\r\n", total_end - total_beg);
				AR_printf(msg);
		}else
		{
				
		}

		return result;
}





arStatus_t	Arsenal_UnInit()
{
		AR_ASSERT(__g_is_initialized);

		if(__g_is_initialized)
		{
				TGU_UnInit();
				Tools_UnInit();
				Parser_UnInit();
				Lex_UnInit();
				AR_CommonUnInit();
				__g_is_initialized = false;
				return AR_S_YES;
		}else
		{
				return AR_S_NO;
		}
}


/*************************************************************************************************/



AR_NAMESPACE_END
