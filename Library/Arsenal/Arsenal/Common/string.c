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


/********************************************************String*****************************************************************/


struct __arsenal_string_tag
{
		wchar_t			*str;
		size_t			count;
		size_t			cap;
};

arString_t*	AR_CreateString()
{
		arString_t *str;
		str = AR_NEW0(arString_t);

		if(str == NULL)
		{
				return NULL;
		}

		
		if(AR_ReserveString(str, 8) != AR_S_YES)
		{
				AR_DEL(str);
				str = NULL;
		}

		return str;
}


void	AR_DestroyString(arString_t *str)
{
		AR_ASSERT(str != NULL);
		if(str->str)
		{
				AR_DEL(str->str);
		}
		AR_DEL(str);
}



const wchar_t*	AR_GetStringCString(const arString_t *str)
{
		AR_ASSERT(str != NULL && str->str != NULL);
		return str->str;
}

size_t	AR_GetStringLength(const arString_t *str)
{
		AR_ASSERT(str != NULL && str->str != NULL);
		return str->count;
}


#if(0)
arStatus_t			AR_ReserveString(arString_t *str, size_t num)
{
		AR_ASSERT(str != NULL);
		num += 1;

		if(str->cap - str->count < num)
		{
				wchar_t *new_tmp;
				size_t	new_cap;

				new_cap = (str->count + num)*2;
				new_tmp = AR_NEWARR0(wchar_t, new_cap);

				if(new_tmp == NULL)
				{
						return AR_E_NOMEM;
				}

				if(str->str)
				{
						AR_wcscpy(new_tmp, str->str);
						AR_DEL(str->str);
						str->str = NULL;
				}else
				{
						new_tmp[0] = L'\0';
				}

				str->str = new_tmp;
				str->cap = new_cap;

				AR_ASSERT(AR_wcslen(new_tmp) == str->count);
		}

		return AR_S_YES;

}
#endif


arStatus_t			AR_ReserveString(arString_t *str, size_t num)
{
		AR_ASSERT(str != NULL);
		num += 1;

		if(str->cap - str->count < num)
		{
				
				size_t	new_cap;
				arStatus_t status;
				new_cap = (str->count + num)*2;

				AR_DO_REALLOC(wchar_t, str->str, new_cap, str->count, status);

				if(status != AR_S_YES)
				{
						return status;
				}

				str->str[str->count] = L'\0';
				
				str->cap = new_cap;

				AR_ASSERT(AR_wcslen(str->str) == str->count);
		}

		return AR_S_YES;

}


void			AR_ClearString(arString_t *str)
{
		AR_ASSERT(str != NULL);
		str->str[0] = L'\0';
		str->count = 0;
}

arStatus_t	AR_AppendString(arString_t *str, const wchar_t *sour)
{
		size_t len;
		size_t i;
		arStatus_t ret;
		AR_ASSERT(str != NULL && sour != NULL);
		len = AR_wcslen(sour);
		
		ret = AR_S_YES;
		ret = AR_ReserveString(str,len);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		
		for(i = 0; i < len; ++i)
		{
				str->str[str->count++] = sour[i];
		}
		str->str[str->count] = L'\0';
		
		return ret;

}









arStatus_t	AR_FormatString(arString_t *str, const wchar_t *fmt, ...)
{
		arStatus_t ret;
		va_list args;
		AR_ASSERT(str != NULL && fmt != NULL);

		AR_va_start(args, fmt);
		ret = AR_VFormatString(str, fmt, args);
		AR_va_end(args);
		return ret;
}




arStatus_t	AR_AppendFormatString(arString_t *str, const wchar_t *fmt, ...)
{
		arStatus_t ret;
		va_list args;
		AR_ASSERT(str != NULL && fmt != NULL);
		
		AR_va_start(args, fmt);
		ret = AR_AppendVFormatString(str, fmt, args);
		AR_va_end(args);
		return ret;
}



arStatus_t			AR_VFormatString(arString_t *str, const wchar_t *fmt, va_list va_args)
{
		arStatus_t ret;
		int_t len;
		va_list save;
		AR_ASSERT(str != NULL && fmt != NULL && va_args != NULL);
		AR_ClearString(str);
		
		AR_va_copy(save, va_args);
		len = AR_vscwprintf(fmt, save);
		AR_va_end(save);

		if(len < 0)
		{
				return AR_E_INVAL;
		}
		
		ret = AR_ReserveString(str, (size_t)len + 1);
		if(ret != AR_S_YES)
		{
				return ret;
		}
		
		str->str[0] = L'\0';
		
		AR_va_copy(save, va_args);
		len = AR_vswprintf(str->str, str->cap-1, fmt, save) + 1;
		AR_va_end(save);
		
		if(len < 0)
		{
				return AR_E_INVAL;
		}

		
		str->str[len] = L'\0';
		str->count = AR_wcslen(str->str);
		return AR_S_YES;
}


arStatus_t			AR_AppendVFormatString(arString_t *str, const wchar_t *fmt, va_list va_args)
{
		arStatus_t ret;
		int_t len;
		wchar_t *buf;
		va_list save;
		AR_ASSERT(str != NULL && fmt != NULL && va_args != NULL);

		buf = NULL;
		ret = AR_S_YES;
	
		AR_va_copy(save, va_args);
		len = AR_vscwprintf(fmt, save);
		AR_va_end(save);

		if(len < 0)
		{
				ret = AR_E_INVAL;
				goto END_POINT;
		}
		

		buf = AR_NEWARR0(wchar_t, len + 1);

		if(buf == NULL)
		{
				ret = AR_E_NOMEM;
				goto END_POINT;
		}
		
		AR_va_copy(save, va_args);
		len = AR_vswprintf(buf, len + 1, fmt, save);
		AR_va_end(save);

		if(len < 0)
		{
				ret = AR_E_INVAL;
				goto END_POINT;
		}

		buf[len] = L'\0';
		
		ret = AR_AppendString(str, buf);
		if(ret != AR_S_YES)
		{
				goto END_POINT;
		}

END_POINT:
		if(buf)
		{
				AR_DEL(buf);
				buf = NULL;
		}
		
		return ret;
}


arStatus_t			AR_AppendCharToString(arString_t *str, wchar_t chr)
{
		arStatus_t ret;
		AR_ASSERT(str != NULL);

		if(chr == L'\0')
		{
				return AR_S_YES;
		}

		ret = AR_ReserveString(str, 1);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		str->str[str->count++] = chr;
		str->str[str->count] = L'\0';
		return AR_S_YES;
}






AR_NAMESPACE_END
