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

/******************************************************Print**************************************************************/

AR_NAMESPACE_BEGIN



const wchar_t*	AR_Version()
{
		return L"0.3.00.578";
}




/***********************************************************Init****************************************************************/


static void AR_STDCALL __def_error(int_t level, const wchar_t* msg, void *ctx)
{
		AR_UNUSED(level);
		AR_UNUSED(ctx);

		wprintf(L"%ls", msg);
}


static void AR_STDCALL __def_print(const wchar_t *msg, void *ctx)
{
		AR_UNUSED(msg);
		AR_UNUSED(ctx);

		wprintf(L"%ls", msg);
}



static arInit_t	__g_ctx = {{__def_error, __def_print,  NULL}};

arStatus_t AR_CommonInit(const arInit_t *info)
{
		
		if(info)
		{
				__g_ctx = *info;
		}

		AR_InitThread();
		AR_InitMemory();
		return AR_S_YES;
}

arStatus_t AR_CommonUnInit()
{
		AR_UnInitMemory();
		AR_UnInitThread();
		return AR_S_YES;
}


arIOCtx_t*	AR_global_ioctx()
{
		return &__g_ctx.global_io_ctx;
}


arStatus_t	AR_printf_ctx(arIOCtx_t *ctx, const wchar_t *msg,...)
{
		wchar_t *buf;
		int_t len;
		va_list arg_ptr;
		
		if(ctx && ctx->on_print)
		{
				AR_va_start(arg_ptr, msg);
				len = AR_vscwprintf(msg, arg_ptr);
				AR_va_end(arg_ptr);

				if(len <= 0)
				{
						return AR_E_INVAL;
				}

				buf = AR_NEWARR0(wchar_t, len + 1);

				if(buf == NULL)
				{
						return AR_E_NOMEM;
				}
				
				AR_va_start(arg_ptr, msg);
				AR_vswprintf(buf, len + 1, msg, arg_ptr);
				AR_va_end(arg_ptr);

				ctx->on_print(buf, ctx->ctx);
				
				if(buf)
				{
						AR_DEL(buf);
						buf = NULL;
				}
		}

		return AR_S_YES;
}


arStatus_t	AR_error_ctx(arIOCtx_t *ctx, int_t level, const wchar_t *msg, ...)
{		
		wchar_t buf[1024];
		va_list arg_ptr;
		
		if(ctx && ctx->on_error)
		{
				AR_va_start(arg_ptr, msg);
				
				if(AR_vswprintf(buf, 1024, msg, arg_ptr) <= 0)
				{
						buf[0] = L'\0';
				}
				AR_va_end(arg_ptr);

				ctx->on_error(level, buf, ctx->ctx);
				
		}

		return AR_S_YES;
}




arStatus_t AR_error(int_t level, const wchar_t *msg, ...)
{
		wchar_t buf[1024];
		va_list arg_ptr;
		
		if(__g_ctx.global_io_ctx.on_error != NULL)
		{
				AR_va_start(arg_ptr, msg);
				if(AR_vswprintf(buf, 1024, msg, arg_ptr) <= 0)
				{
						buf[0] = L'\0';
				}
				AR_va_end(arg_ptr);
				
				__g_ctx.global_io_ctx.on_error(level, buf, __g_ctx.global_io_ctx.ctx);
				
				
		}


		if(level < AR_ERR_WARNING)
		{
				AR_abort();
		}

		return AR_S_YES;
}




arStatus_t AR_printf(const wchar_t *msg,...)
{
		wchar_t *buf;
		int_t len;
		va_list arg_ptr;

		if(__g_ctx.global_io_ctx.on_print != NULL)
		{
		
				
				AR_va_start(arg_ptr, msg);
				len = AR_vscwprintf(msg, arg_ptr);
				AR_va_end(arg_ptr);

				if(len <= 0)
				{
						return AR_E_INVAL;
				}

				buf = AR_NEWARR0(wchar_t, len + 1);

				if(buf == NULL)
				{
						return AR_E_NOMEM;
				}

				AR_va_start(arg_ptr, msg);
				len = AR_vswprintf(buf, len + 1, msg, arg_ptr);
				AR_va_end(arg_ptr);
				
				if(len <= 0)
				{
						AR_DEL(buf);
						return AR_E_INVAL;
				}

				__g_ctx.global_io_ctx.on_print(buf, __g_ctx.global_io_ctx.ctx);
				
				AR_DEL(buf);
		}

		return AR_S_YES;
}

void	AR_check(bool_t cond, const wchar_t *fmt, ...)
{
		wchar_t buf[1024];
		int_t len;
		va_list arg_ptr;
		AR_ASSERT(fmt);
		
		if(!cond)
		{
				AR_va_start(arg_ptr, fmt);
				len = AR_vswprintf(buf, 1024, fmt, arg_ptr);
				AR_va_end(arg_ptr);

				if(len < 0)
				{
						AR_error(AR_ERR_FATAL, L"%ls : %ls\r\n", L"Arsenal internal error", AR_FUNC_NAME);
						return;/*±ÜÃâwarning*/
				}
				
				AR_error(AR_ERR_FATAL, buf);

		}
}

/***************************************************ctx**********************************/






AR_NAMESPACE_END

