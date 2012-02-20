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


/*****************************************************cmp********************************************************************/


char*			AR_strupr(char *s)
{
		char *r = s;
		AR_ASSERT(s != NULL);
		while(*s)
		{
				*s = (char)AR_toupper(*s);
				++s;
		}
		return r;

}

char*			AR_strlwr(char *s)
{
		char *r = s;
		AR_ASSERT(s != NULL);
		while(*s)
		{
				*s = (char)AR_tolower(*s);
				++s;
		}
		return r;
}

char*	AR_strnlwr(char *s, size_t count)
{
		size_t i;
		AR_ASSERT(s != NULL);

		for(i = 0; i < count && s[i] != '\0'; ++i)
		{
				s[i] = (char)AR_tolower(s[i]);
		}

		return s;
}




char*	AR_strnupr(char *s, size_t count)
{
		size_t i;
		AR_ASSERT(s != NULL);

		for(i = 0; i < count && s[i] != '\0'; ++i)
		{
				s[i] = (char)AR_toupper(s[i]);
		}

		return s;
}


wchar_t*			AR_wcsupr(wchar_t *s)
{
		wchar_t *r = s;
		AR_ASSERT(s != NULL);
		while(*s)
		{
				*s = AR_towupper(*s);
				++s;
		}
		return r;
}

wchar_t*			AR_wcslwr(wchar_t *s)
{
		wchar_t *r = s;
		AR_ASSERT(s != NULL);
		while(*s)
		{
				*s = AR_towlower(*s);
				s++;
		}
		return r;
}


wchar_t* AR_wcsnlwr(wchar_t *s, size_t count)
{
		size_t i;
		AR_ASSERT(s != NULL);

		for(i = 0; i < count && s[i] != L'\0'; ++i)
		{
				s[i] = AR_towlower(s[i]);
		}

		return s;
}




wchar_t* AR_wcsnupr(wchar_t *s, size_t count)
{
		size_t i;
		AR_ASSERT(s != NULL);

		for(i = 0; i < count && s[i] != L'\0'; ++i)
		{
				s[i] = AR_towupper(s[i]);
		}

		return s;
}





int_t	AR_stricmp(const char *l, const char *r)
{
		int_t ret;
		AR_ASSERT(l != NULL && r != NULL);

		for(ret = 0; (ret = (AR_tolower(*l) - AR_tolower(*r))) == 0 && *l && *r; ++l, ++r);

		return ret;
}

int_t	AR_strnicmp(const char *l, const char *r, size_t n)
{
		int_t ret;
		size_t i;
		AR_ASSERT(l != NULL && r != NULL);

		for(ret = 0, i = 0; i < n && (ret = (AR_tolower(l[i]) - AR_tolower(r[i]))) == 0 && l[i] && r[i]; ++i);

		return ret;

}

int_t	AR_wcsicmp(const wchar_t *l, const wchar_t *r)
{
		int_t ret;
		AR_ASSERT(l != NULL && r != NULL);

		for(ret = 0; (ret = (AR_towlower(*l) - AR_towlower(*r))) == 0 && *l && *r; ++l, ++r);

		return ret;

}

int_t	AR_wcsnicmp(const wchar_t *l, const wchar_t *r, size_t n)
{
		int_t ret;
		size_t i;
		AR_ASSERT(l != NULL && r != NULL);

		for(ret = 0, i = 0; i < n && (ret = (AR_towlower(l[i]) - AR_towlower(r[i]))) == 0 && l[i] && r[i]; ++i);

		return ret;

}




const char*		AR_stristr(const char *s, const char *p)
{
		size_t i;
		AR_ASSERT(s != NULL && p != NULL);
		while(*s)
		{
				for(i = 0; s[i] && p[i] && AR_tolower(s[i]) == AR_tolower(p[i]); ++i);
				if(p[i] == '\0')return s;
				++s;
		}
		return NULL;

}

const wchar_t*		AR_wcsistr(const wchar_t *s, const wchar_t *p)
{
		size_t i;
		AR_ASSERT(s != NULL && p != NULL);
		while(*s)
		{
				for(i = 0; s[i] && p[i] && AR_towlower(s[i]) == AR_towlower(p[i]); ++i);
				if(p[i] == L'\0')return s;
				++s;
		}
		return NULL;
}






/**********************************************************string*************************************************************/

static int_t __wcs_format_preprocess(const wchar_t *fmt, wchar_t *out)
{
		wchar_t *p;
		int_t	need_l;
		AR_ASSERT(fmt != NULL);

		if(AR_wcslen(fmt) == 0)
		{
				return 1;
		}

		p = out;
		need_l = 0;

		while(*fmt)
		{
				if(*fmt != L'%')
				{
						if(p)
						{
								*p++ = *fmt;
						}
						fmt++;
						need_l++;

						continue;
				}else if(*fmt == L'%' && *(fmt + 1) == L'%')
				{
						if(p)
						{
								*p++ = *fmt;
								*p++ = *fmt;
						}
						need_l += 2;
						fmt += 2;
						continue;
				}else
				{
						if(p)
						{
								*p++ = *fmt;
						}
						need_l++;
						fmt++;
				}

				/*处理%后面的*/


				while(*fmt)
				{
						if(*fmt == L'#')
						{
								if(p)
								{
										*p++ = *fmt;/*0x*/
								}

								need_l++;
								fmt++;
						}else if(*fmt == L'*')
						{
								if(p)
								{
										*p++ = *fmt;
								}

								need_l++;
								fmt++;
						}else if(*fmt == L'-' || *fmt == L'+' || *fmt == L'0' || *fmt == L' ')
						{
								if(p)
								{
										*p++ = *fmt;
								}

								need_l++;
								fmt++;
						}else
						{
								break;
						}
				}

				while(*fmt && AR_iswdigit(*fmt))
				{
						if(p)
						{
								*p++ = *fmt;
						}
						need_l++;
						fmt++;
				}


				if(*fmt == L'.')
				{
						/*width.prec*/
						if(p)
						{
								*p++ = *fmt;
						}
						need_l++;
						fmt++;

						if(*fmt == L'*')
						{
								if(p)
								{
										*p++ = *fmt;
								}
								need_l++;
								fmt++;
						}else
						{
								while(*fmt && AR_iswdigit(*fmt))
								{
										if(p)
										{
												*p++ = *fmt;
										}
										need_l++;
										fmt++;
								}
						}

				}




				switch (*fmt)
				{
				case L'I':
				{
						#if(AR_ARCH_VER == ARCH_64)
						{
								const wchar_t *pfmt64 = AR_FMT64;
								while(*pfmt64 != L'\0')
								{
										if(p)
										{
												*p++ = *pfmt64;
										}
										pfmt64++;
										need_l++;
								}
						}
						#elif(AR_ARCH_VER == AR_ARCH_32)

						#endif

						fmt++;
				}
						break;
				case L'q': /*64bit*/
				{
						const wchar_t *pfmt64 = AR_FMT64;
						while(*pfmt64 != L'\0')
						{
								if(p)
								{
										*p++ = *pfmt64;
								}
								pfmt64++;
								need_l++;
						}

						fmt++;
				}
						break;
						/*强制ANSI*/
				case L'h':
				case L'l':
				case L'F':
				case L'N':
				case L'L':

						if(p)
						{
								*p++ = *fmt;
						}

						need_l++;
						fmt++;
						break;
				}

				switch (*fmt)
				{
				case L'd':
				case L'i':
				case L'u':
				case L'x':
				case L'X':
				case L'o':
				case L'e':
				case L'E':
				case L'g':
				case L'G':
				case L'f':
				case L'p':
				case L'n':
				case L'c':
				case L'C':
				case L's':
				case L'S':
						if(p)
						{
								*p++ = *fmt;
						}

						fmt++;
						need_l++;
						break;
				default:
						AR_ASSERT(false);
						return -1;
						break;
				}
		}

		if(p)
		{
				*p = L'\0';
		}

		need_l++;
		return need_l;
}



#define __MODIFIER_ANSI			0x10000
#define __MODIFIER_UNICODE		0x20000
#define	__MODIFIER_INT64		0x40000

int_t AR_vscwprintf(const wchar_t *fmt, va_list va_args)
{
		int_t res;
		va_list args;
		AR_ASSERT(fmt != NULL && va_args != NULL);
		res = 0;

		AR_va_copy(args, va_args);

		while(*fmt)
		{
				int_t len = 0, width = 0, prec = 0, modifier = 0;
				if(*fmt != L'%' || *(++fmt) == L'%')
				{
						fmt++;
						res++;
						continue;
				}

				/*处理%后面的*/


				while(*fmt)
				{
						if(*fmt == L'#')
						{
								res += 2; /*0x*/
						}else if(*fmt == L'*')
						{
								width = AR_va_arg(args, int);
						}else if(*fmt == L'-' || *fmt == L'+' || *fmt == L'0' || *fmt == L' ')
						{

						}else
						{
								break;
						}
						fmt++;
				}

				if(width == 0)
				{
						while(*fmt && AR_iswdigit(*fmt))
						{
								width *= 10;
								width += AR_wchartodigit(*fmt);
								fmt++;
						}
				}

				if(*fmt == L'.')
				{
						/*width.prec*/
						fmt++;
						if(*fmt == L'*')
						{
								prec = AR_va_arg(args, int_32_t);
								fmt++;
						}else
						{
								prec = 0;
								while(*fmt && AR_iswdigit(*fmt))
								{
										prec *= 10;
										prec += AR_wchartodigit(*fmt);
										fmt++;
								}
						}

				}

				modifier = 0;

				if(*fmt == L'I')
				{
						/*例如%Id*/
						fmt += 1;

						#if(AR_ARCH_VER == ARCH_64)
								modifier |= __MODIFIER_INT64;
						#elif(AR_ARCH_VER == ARCH_32)

						#endif
				}else if(*fmt == L'q')
				{
						/*例如%lld*/
						fmt += 1;
						modifier |= __MODIFIER_INT64;
				}else
				{
						switch (*fmt)
						{
								/*强制ANSI*/
						case L'h':
								modifier |= __MODIFIER_ANSI;
								fmt++;
								break;
						case L'l':
								modifier |= __MODIFIER_UNICODE;
								fmt++;
								break;
								/*无用*/
						case L'F':
						case L'N':
						case L'L':
								fmt++;
								break;
						}
				}

				switch (*fmt | modifier)
				{
				case L'c':
				case L'C':
						len = 2;
#if(AR_COMPILER == AR_GCC3 || AR_COMPILER == AR_GCC4)
						AR_va_arg(args, int);
#else
						AR_va_arg(args, wint_t);
#endif
						break;
				case L'c' | __MODIFIER_ANSI:
				case L'C' | __MODIFIER_ANSI:

						len = 2;

#if(AR_COMPILER == AR_GCC3 || AR_COMPILER == AR_GCC4)
						AR_va_arg(args, int);
#else
						AR_va_arg(args, char);
#endif

						break;
				case L'c' | __MODIFIER_UNICODE:
				case L'C' | __MODIFIER_UNICODE:
						len = 2;
#if(AR_COMPILER == AR_GCC3 || AR_COMPILER == AR_GCC4)
						AR_va_arg(args, int);
#else
						AR_va_arg(args, wchar_t);
#endif
						break;
				case L's':
				{
						const wchar_t *str = AR_va_arg(args, const wchar_t*);
						if(str == NULL)
						{
								len = 6;/*(null)*/
						}else
						{
								len =(int_t)AR_wcslen(str);
								len = AR_MAX(len, 1);
						}
						break;
				}
				case L'S':
				{
						const char *str = AR_va_arg(args, const char*);
						if(str == NULL)
						{
								len = 6;/*(null)*/
						}else
						{
								len = (int_t)AR_strlen(str);
								len = AR_MAX(len,1);
						}
						break;
				}
				case L's' | __MODIFIER_ANSI:
				case L'S' | __MODIFIER_ANSI:
				{
						const char *str = AR_va_arg(args, const char*);
						if(str == NULL)
						{
								len = 6;/*(null)*/
						}else
						{
								len = (int_t)AR_strlen(str);
								len = AR_MAX(len,1);
						}
						break;
				}
				case L's' | __MODIFIER_UNICODE:
				case L'S' | __MODIFIER_UNICODE:
				{
						const wchar_t *str = AR_va_arg(args, const wchar_t*);
						if(str == NULL)
						{
								len = 6;/*(null)*/
						}else
						{
								len = (int_t)AR_wcslen(str);
								len = AR_MAX(len, 1);
						}
						break;

				}
				}

				if(len != 0)
				{
						len = AR_MAX(len, width);
						if(prec != 0)len = AR_MIN(len, prec);
				}else
				{
						switch (*fmt)
						{
						case L'd':
						case L'i':
						case L'u':
						case L'x':
						case L'X':
						case L'o':
						{
								if(modifier & __MODIFIER_INT64)
								{
										AR_va_arg(args, int_64_t);
								}else
								{
										AR_va_arg(args, int_32_t);
								}
								len = 32;
								len = AR_MAX(len, width + prec);
								break;
						}
						case L'e':
						case L'E':
						case L'g':
						case L'G':
						{
								AR_va_arg(args, double);
								len = 128;
								len = AR_MAX(len, width + prec);
								break;
						}
						case L'f':
						{
								int_t cclen;
								wchar_t *buf;
								double f= AR_va_arg(args, double);

								/*
										312 == wcslen(L"-1+(0{309})")
										double 最大精度为.0{309},这里精度默认设置为6
								*/

								cclen = AR_MAX(width, 312 + prec + 6);/*取最大值*/

								buf = AR_NEWARR0(wchar_t, cclen);

								if(buf == NULL)
								{
										return -1;
								}

								/*
								AR_swprintf(buf, cclen, L"%*.*f", width, prec + 6, f);
								*/
								AR_SWPRINTF(buf, cclen, L"%*.*f", width, prec + 6, f);
								len = AR_wcslen(buf);
								AR_DEL(buf);
								break;
						}
						case L'p':
						{
								AR_va_arg(args, void*);
								len = AR_MAX(32, width + prec);
								break;
						}
						case L'n':
						{
								AR_va_arg(args, int*);
								break;
						}
						default:
						{
								AR_ASSERT(false);
								return -1;
						}

						}
				}
				fmt++;
				res += len;
		}
		AR_va_end(args);
		return res;
}
#undef	__MODIFIER_ANSI
#undef	__MODIFIER_UNICODE
#undef	__MODIFIER_INT64



int_t			AR_scwprintf(const wchar_t *fmt, ...)
{
		int_t len = -1;
		va_list	arg_ptr;

		AR_ASSERT(fmt != NULL);

		AR_va_start(arg_ptr, fmt);
		len = AR_vscwprintf(fmt, arg_ptr);
		AR_va_end(arg_ptr);
		return len;
}



wchar_t*		AR_vtow(const wchar_t *fmt, ...)
{
		va_list			args;

		wchar_t			*buf;
		int_t			len;

		AR_ASSERT(fmt != NULL);

		AR_va_start (args, fmt);
		len = AR_vscwprintf(fmt, args);
		AR_va_end (args);
		if(len < 0)
		{
				return NULL;
		}

		buf = AR_NEWARR(wchar_t, len + 1);

		if(buf == NULL)
		{
				return NULL;
		}

		AR_va_start (args, fmt);
		
		if(AR_vswprintf(buf, len + 1, fmt, args) < 0)
		{
				AR_DEL(buf);
				buf = NULL;
		}
		AR_va_end (args);
		return buf;
}



int_t			AR_vswprintf(wchar_t *dest, size_t count, const wchar_t *fmt, va_list args)
{
		int_t res;
		va_list save;

		wchar_t *src_fmt;
		int_t need_l;

		AR_ASSERT(dest != NULL && fmt != NULL && args != NULL);

		res = 0;
		need_l = 0;
		src_fmt = NULL;



		/********************将Arsenal形式的printf格式，转换为目标CRT的格式***************/
		need_l = __wcs_format_preprocess(fmt, NULL);
		if(need_l <= 0)
		{
				res = -1;
				goto END_POINT;
		}

		src_fmt = AR_NEWARR(wchar_t, need_l);

		if(src_fmt == NULL)
		{
				res = -1;
				goto END_POINT;
		}

		__wcs_format_preprocess(fmt, src_fmt);

		AR_va_copy(save, args);
		res = AR_VSWPRINTF(dest, count, src_fmt, save);
		AR_va_end(save);

	   /*****************************************************************************/


END_POINT:


		if(src_fmt)
		{
				AR_DEL(src_fmt);
				src_fmt = NULL;
		}

		if(res <= 0)						/*忽略掉此种错误*/
		{
				dest[0] = L'\0';
				res = 0;
		}

		return res;
}


int_t			AR_swprintf(wchar_t *dest, size_t count, const wchar_t *fmt, ...)
{
		int_t len = -1;
		va_list	arg_ptr;
		AR_ASSERT(fmt != NULL);

		AR_va_start(arg_ptr, fmt);
		len = AR_vswprintf(dest, count, fmt, arg_ptr);
		AR_va_end(arg_ptr);
		
		return len;
}









int_t AR_wchartodigit(wchar_t ch)
{

		#define DIGIT_RANGE_TEST(zero)  \
		if (ch < zero)					\
				return -1;              \
		if (ch < zero + 10)				\
		{								\
				return ch - zero;       \
		}


		DIGIT_RANGE_TEST(0x0030)			/* 0030;DIGIT ZERO*/
		if (ch < 0xFF10)					/* FF10;FULLWIDTH DIGIT ZERO*/
		{
				DIGIT_RANGE_TEST(0x0660)    /* 0660;ARABIC-INDIC DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x06F0)    /* 06F0;EXTENDED ARABIC-INDIC DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0966)    /* 0966;DEVANAGARI DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x09E6)    /* 09E6;BENGALI DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0A66)    /* 0A66;GURMUKHI DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0AE6)    /* 0AE6;GUJARATI DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0B66)    /* 0B66;ORIYA DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0C66)    /* 0C66;TELUGU DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0CE6)    /* 0CE6;KANNADA DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0D66)    /* 0D66;MALAYALAM DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0E50)    /* 0E50;THAI DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0ED0)    /* 0ED0;LAO DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x0F20)    /* 0F20;TIBETAN DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x1040)    /* 1040;MYANMAR DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x17E0)    /* 17E0;KHMER DIGIT ZERO*/
				DIGIT_RANGE_TEST(0x1810)    /* 1810;MONGOLIAN DIGIT ZERO*/

				return -1;
		}

		if (ch < 0xFF10 + 10)/* FF10;FULLWIDTH DIGIT ZERO*/
		{
				return ch - 0xFF10;
		}
		return -1;

		#undef DIGIT_RANGE_TEST
}







const wchar_t* AR_wcstrim_s(const wchar_t *in, const wchar_t *end, const wchar_t *trim)
{
		AR_ASSERT(in != NULL && end != NULL && trim != NULL);

		while(in < end && AR_wcschr(trim, *in) != NULL)in++;
		return in;
}



const wchar_t*	AR_wcstrim_space_s(const wchar_t *in, const wchar_t *end)
{
		AR_ASSERT(in != NULL && end != NULL);
		while(in < end && AR_iswspace(*in))in++;
		return in;
}


/************************************************************************************************************************************/


wchar_t*		AR_wcscat(wchar_t *dest, const wchar_t *sour)
{
		wchar_t *d;
		AR_ASSERT(dest != NULL && sour != NULL);
		d = dest;
		while(*d)d++;

		while(*sour)*d++ = *sour++;
		*d = 0;
		return dest;
}


wchar_t*		AR_wcsncat(wchar_t *dest, const wchar_t *sour, size_t n)
{
		wchar_t *d;
		size_t i;
		AR_ASSERT(dest != NULL && sour != NULL);
		d = dest;
		while(*d)d++;

		for(i = 0; i < n && sour[i]; ++i,++d) *d = sour[i];

		*d = 0;

		return dest;


}


wchar_t*		AR_wcstrim_right(wchar_t *in, const wchar_t *trim)
{
		wchar_t *p = NULL, *plast = NULL;
		AR_ASSERT(in != NULL && trim != NULL);
		p = in;
		while(*p != L'\0')
		{
				if(AR_wcschr(trim, *p) == NULL)
				{
						plast = NULL;
				}else if(plast == NULL)
				{
						plast = p;
				}
				++p;
		}

		if(plast)*plast = L'\0';
		return in;
}

wchar_t*	AR_wcstrim_right_space(wchar_t *in)
{
		wchar_t *p = NULL, *plast = NULL;
		AR_ASSERT(in != NULL);
		p = in;
		while(*p != L'\0')
		{
				/*if(AR_wcschr(trim, *p) == NULL)*/
				if(AR_iswspace(*p) == 0)
				{
						plast = NULL;
				}else if(plast == NULL)
				{
						plast = p;
				}
				++p;
		}

		if(plast)*plast = L'\0';
		return in;
}

const wchar_t* AR_wcstrim(const wchar_t *in, const wchar_t *trim)
{
		AR_ASSERT(in != NULL && trim != NULL);

		while(*in != L'\0' && AR_wcschr(trim, *in) != NULL)in++;
		return in;
}

const wchar_t*	AR_wcstrim_space(const wchar_t *in)
{
		AR_ASSERT(in != NULL);
		while(*in != L'\0' && AR_iswspace(*in))in++;
		return in;
}


const wchar_t* AR_wtoi64(const wchar_t *in,	 int_64_t  *num, size_t base)
{
		return AR_wtoi64_s(in, in + AR_wcslen(in), num, base);
}

const wchar_t* AR_wtou64(const wchar_t *in,	 uint_64_t  *num, size_t base)
{
		return AR_wtou64_s(in, in + AR_wcslen(in), num, base);
}


const wchar_t* AR_wtoi32(const wchar_t *in,  int_32_t *num, size_t base)
{
		return AR_wtoi32_s(in, in + AR_wcslen(in), num, base);
}

const wchar_t* AR_wtou32(const wchar_t *in,  uint_32_t *num, size_t base)
{
		return AR_wtou32_s(in, in + AR_wcslen(in), num, base);
}







uint_t	AR_wcshash(const wchar_t *str)
{
		uint_t	ret;
		size_t	i;
		AR_ASSERT(str != NULL);

		ret = 0;
		for(i = 0; str[i]; ++i)
		{
				ret ^= (str[i] << (i & 0x0F));
		}
		return ret;
}


uint_t		AR_wcshash_n(const wchar_t *str, size_t n)
{
		uint_t	ret;
		size_t	i;
		if(n == 0)return 0;
		AR_ASSERT(str != NULL);

		ret = 0;
		for(i = 0; i < n && str[i]; ++i)
		{
				ret ^= (str[i] << (i & 0x0F));
		}
		return ret;
}


wchar_t* AR_wcsdup(const wchar_t *sour)
{
		AR_ASSERT(sour != NULL);
		return AR_wcsndup(sour, AR_wcslen(sour));
}




wchar_t* AR_wcsndup(const wchar_t *sour, size_t len)
{
		wchar_t *result;
		size_t i;
		AR_ASSERT(sour != NULL);

		result = AR_NEWARR(wchar_t, len + 1);
		
		if(result == NULL)
		{
				return NULL;
		}

		for(i = 0; i < len; ++i)result[i] = sour[i];
		result[len] = L'\0';
		return result;
}


char*			AR_strdup(const char *sour)
{
		AR_ASSERT(sour != NULL);
		return AR_strndup(sour, AR_strlen(sour));
}

char*			AR_strndup(const char *sour, size_t len)
{
		char *result;
		size_t i;
		AR_ASSERT(sour != NULL);

		result = AR_NEWARR(char, len + 1);

		if(result == NULL)
		{
				return NULL;
		}

		for(i = 0; i < len; ++i)result[i] = sour[i];
		result[len] = '\0';
		return result;
}



#define	__BUFFER_LEN	128


int_t			AR_u64tow_buf(wchar_t *out, size_t nbuf, uint_64_t num, size_t radix)
{
		wchar_t buf[__BUFFER_LEN];
		wchar_t *p;
		int_t len;
		static const wchar_t* __tbl = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		AR_ASSERT(radix >= 2 && radix <= 36);

		p = buf + __BUFFER_LEN;
		*--p = 0;
		do{ *--p = __tbl[num % radix];}while((num /= radix) > 0);

		len = (int_t)(buf + __BUFFER_LEN - p);/*返回的是需要元素数组的长度包含0*/

		if(out != NULL)
		{
				if(nbuf < (size_t)len)return -1;
				AR_wcscpy(out, p);
				return len;
		}else
		{
				return len;
		}

}




int_t			AR_i64tow_buf(wchar_t *out, size_t nbuf, int_64_t num, size_t radix)
{
		bool_t is_neg;
		wchar_t buf[__BUFFER_LEN];
		wchar_t *p;
		int_t len;
		/*static const wchar_t* __tbl = L"0123456789ABCDEF";*/
		static const wchar_t* __tbl = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		AR_ASSERT(radix >= 2 && radix <= 36);
		is_neg = false;

		if(num < 0){ is_neg = true; num = -num;}

		p = buf + __BUFFER_LEN;
		*--p = 0;
		do{ *--p = __tbl[num % radix];}while((num /= radix) > 0);
		if(is_neg)*--p = L'-';

		len = (int_t)(buf + __BUFFER_LEN - p);/*返回的是需要元素数组的长度包含0*/

		if(out != NULL)
		{
				if(nbuf < (size_t)len)return -1;
				AR_wcscpy(out, p);
				return len;
		}else
		{
				return len;
		}
}


#undef __BUFFER_LEN




const wchar_t*	AR_wtod(const wchar_t *in, double *num)
{
/*
		wchar_t *stop;
		AR_ASSERT(in != NULL && num != NULL);

		*num = AR_wcstod(in, &stop);

		if(stop == in)
		{
				return NULL;
		}else
		{
				return stop;
		}
*/

		AR_ASSERT(in != NULL && num != NULL);
		return AR_wtod_s(in, in + AR_wcslen(in), num);
}






/*此函数貌似不太完整，对溢出检测也没做到位*/
const wchar_t*	AR_wtod_s(const wchar_t *in, const wchar_t *end, double *out)
{
		const wchar_t *p;
		double num = 0.0f,frac = 0.0f, exp = 1.0f;
		double result = 0.0f;
		bool_t is_neg = false, is_ok = false;

		AR_ASSERT(in != NULL && end != NULL && in <= end && out != NULL);

		/*p = AR_wcstrim(in, L" \t");*/
		p = AR_wcstrim_space_s(in, end);

		if(*p == L'-')
		{
				++p;
				is_neg = true;
		}else if(*p == L'+')
		{
				is_neg = false;
				++p;
		}


		while(p < end && *p >= L'0' && *p <= L'9')
		{
				num *= 10.0f;
				num += (double)(*p - L'0');
				++p;
				is_ok = true;
		}

		if(p < end && *p == L'.')
		{
				++p;
				while(p < end && *p >= L'0' && *p <= L'9')
				{
						exp *= 10.0f;
						frac *= 10.0f;
						frac += (double)(*p - L'0');
						++p;
						is_ok = true;
				}
		}
		result = num + frac / exp;


		if(p < end && (*p == L'e' || *p == L'E'))
		{
				bool_t factor;
				size_t i, e;
				++p;

				if(*p == L'+')
				{
						factor = true;
						++p;
				}else if(*p == L'-')
				{
						factor = false;
						++p;
				}else
				{
						factor = true;
				}
				
				e = 0;
				is_ok = false;
				while(p < end && *p >= L'0' && *p <= L'9')
				{
						e *= 10;
						e += (*p - L'0');
						++p;
						is_ok = true;
				}

				for(i = 0; i < e; ++i)
				{
						if(factor)
						{
								result *= 10.0f;
						}else
						{
								result /= 10.0f;
						}
				}
		}
		if(is_neg)result = -result;
		*out = result;
		return is_ok ? p : NULL;
}




#define __UNSIGNED   0x01
#define __NEG        0x02
#define __OVERFLOW   0x04
#define __READDIGIT  0x08


static const wchar_t* __wtou64_s(const wchar_t *in, const wchar_t *end, uint_64_t  *num, size_t base, uint_32_t flag)
{
		uint_64_t val,digit, maxval;
		const wchar_t *p;

		AR_ASSERT(in != NULL && end != NULL && num != NULL && (base == 0 || (base > 1 && base <= 36)));

		/*p = AR_wcstrim_s(in, end, L" \t");*/
		p = AR_wcstrim_space_s(in,end);

		if(p >= end)return NULL;

		if(*p == L'-')
		{
				flag |= __NEG;
				++p;
		}else if(*p == L'+')
		{
				++p;
		}

		if(flag & __NEG && flag & __UNSIGNED)return NULL;
		if(p >= end)return NULL;
		if(base == 0)
		{
				if(AR_wchartodigit(*p) != 0)
				{
						base = 10;
				}else if(*(p + 1) == L'x' || *(p + 1) == L'X')
				{
						base = 16;
				}else
				{
						base = 8;
				}
		}

		if(base == 16)
		{
				if(AR_wchartodigit(*p) == 0 && (*(p + 1) == L'x' || *(p + 1) == L'X'))
				{
						p += 2;
				}
		}

		if(p >= end)return NULL;

		maxval = AR_UINT64_MAX / base;
		digit = 0;
		val = 0;

		while(p < end)
		{
				int_t tmp;
				if((tmp = AR_wchartodigit(*p)) != -1)
				{
						/*tmp = (*p - L'0');*/
				}else if(*p >= L'A' && *p <= L'Z')
				{
						tmp = ((*p - L'A') + 10);
				}else if(*p >= L'a' && *p <= L'z')
				{
						tmp = ((*p - L'a') + 10);
				}else
				{
						break;
				}

				digit = (uint_64_t)tmp;
				if(digit >= base)break;
				flag |= __READDIGIT;



				if (val < maxval || (val == maxval && digit <= AR_UINT64_MAX % base))
				{
						val = val * base + digit;
				}else
				{
						flag |= __OVERFLOW;
				}
				++p;
		}

		if(!(flag & __READDIGIT))
		{
				val = 0;
				p = NULL;
		}else if((flag & __OVERFLOW) || ((!(flag & __UNSIGNED)) && (((flag & __NEG) && (val > -AR_INT64_MIN)) || (!(flag & __NEG) && (val > AR_INT64_MAX)))))
		{
				p = NULL;
				/*errno = ERANGE;*/
				
				if(flag & __UNSIGNED)
				{
						val = AR_UINT64_MAX;
				} else if (flag & __NEG )
				{
						val = (uint_64_t)(-AR_INT64_MIN);
				}else
				{
						val = AR_INT64_MAX;
				}
		}

		if(flag & __NEG)
		{
				val = (uint_64_t)(-(int_64_t)val);
		}
		*num = val;
		return p;
}



static const wchar_t* __wtou32_s(const wchar_t *in, const wchar_t *end, uint_32_t  *num, size_t base, uint_32_t flag)
{
		uint_32_t val,digit, maxval;
		const wchar_t *p;

		AR_ASSERT(in != NULL && end != NULL && num != NULL && (base == 0 || (base > 1 && base <= 36)));

		/*p = AR_wcstrim_s(in, end, L" \t");*/
		p = AR_wcstrim_space_s(in,end);

		if(p >= end)return NULL;

		if(*p == L'-')
		{
				flag |= __NEG;
				++p;
		}else if(*p == L'+')
		{
				++p;
		}

		if(flag & __NEG && flag & __UNSIGNED)return NULL;
		if(p >= end)return NULL;
		if(base == 0)
		{
				if(AR_wchartodigit(*p) != 0)
				{
						base = 10;
				}else if(*(p + 1) == L'x' || *(p + 1) == L'X')
				{
						base = 16;
				}else
				{
						base = 8;
				}
		}

		if(base == 16)
		{
				if(AR_wchartodigit(*p) == 0 && (*(p + 1) == L'x' || *(p + 1) == L'X'))
				{
						p += 2;
				}
		}

		if(p >= end)return NULL;

		maxval = AR_UINT32_MAX / (uint_32_t)base;
		digit = 0;
		val = 0;

		while(p < end)
		{
				int_t tmp;
				if((tmp = AR_wchartodigit(*p)) != -1)
				{
						/*tmp = (*p - L'0');*/
				}else if(*p >= L'A' && *p <= L'Z')
				{
						tmp = ((*p - L'A') + 10);
				}else if(*p >= L'a' && *p <= L'z')
				{
						tmp = ((*p - L'a') + 10);
				}else
				{
						break;
				}

				digit = (uint_32_t)tmp;
				if(digit >= base)break;
				flag |= __READDIGIT;



				if (val < maxval || (val == maxval && digit <= AR_UINT32_MAX % base))
				{
						val = val * (uint_32_t)base + digit;
				}else
				{
						flag |= __OVERFLOW;
				}
				++p;
		}

		if(!(flag & __READDIGIT))
		{
				val = 0;
				p = NULL;
		}else if((flag & __OVERFLOW) || ((!(flag & __UNSIGNED)) && (((flag & __NEG) && (val > -AR_INT32_MIN)) || (!(flag & __NEG) && (val > AR_INT32_MAX)))))
		{
				p = NULL;
				/*errno = ERANGE;*/
				if ( flag & __UNSIGNED )
				{
						val = AR_UINT32_MAX;
				} else if (flag & __NEG )
				{
						val = (uint_32_t)(-AR_INT32_MIN);
				}else
				{
						val = AR_INT32_MAX;
				}
		}

		if(flag & __NEG)
		{
				val = (uint_32_t)(-(int_32_t)val);
		}
		*num = val;
		return p;
}






const wchar_t* AR_wtoi64_s(const wchar_t *in, const wchar_t *end, int_64_t  *num, size_t base)
{
		uint_32_t flag = 0;
		uint_64_t val;
		const wchar_t *p;
		AR_ASSERT(in != NULL && end != NULL && num != NULL && (base == 0 || (base > 1 && base <= 36)));

		p = __wtou64_s(in, end, &val, base, flag);

		*num = (int_64_t)val;

		return p;
}


const wchar_t* AR_wtou64_s(const wchar_t *in, const wchar_t *end, uint_64_t  *num, size_t base)
{
		uint_32_t flag = __UNSIGNED;
		const wchar_t *p;
		AR_ASSERT(in != NULL && end != NULL && num != NULL && (base == 0 || (base > 1 && base <= 36)));

		p = __wtou64_s(in, end, num, base, flag);

		return p;

}





const wchar_t* AR_wtoi32_s(const wchar_t *in, const wchar_t *end, int_32_t  *num, size_t base)
{
		uint_32_t flag = 0;
		uint_32_t val;
		const wchar_t *p;
		AR_ASSERT(in != NULL && end != NULL && num != NULL && (base == 0 || (base > 1 && base <= 36)));

		p = __wtou32_s(in, end, &val, base, flag);

		*num = (int_32_t)val;

		return p;
}


const wchar_t* AR_wtou32_s(const wchar_t *in, const wchar_t *end, uint_32_t  *num, size_t base)
{
		uint_32_t flag = __UNSIGNED;
		const wchar_t *p;
		AR_ASSERT(in != NULL && end != NULL && num != NULL && (base == 0 || (base > 1 && base <= 36)));

		p = __wtou32_s(in, end, num, base, flag);

		return p;

}



#if(0)
const wchar_t* AR_wcsstr_kmp(const wchar_t *s, const wchar_t *p)
{
		AR_ASSERT(s != NULL && p != NULL);
		return AR_wcsstr_kmp_s(s, s + AR_wcslen(s), p);

}


const wchar_t* AR_wcsstr_kmp_s(const wchar_t *beg, const wchar_t *end, const wchar_t *p)
{

		size_t i,k,m,n;
		size_t *next;
		const wchar_t *ret, *s;
		AR_ASSERT(beg != NULL && p != NULL && end != NULL);
		n = end - beg;
		m = AR_wcslen(p);
		if(n == 0 || m == 0 || m > n)return NULL;

		next = AR_NEWARR0(size_t, m);

		if(!next)
		{
				return NULL;
		}

		next[0] = 0;

		for(i = 1,k = 0; i < m; ++i)
		{
				/*
				如果p[k]处不相等， 则证明有k个前缀相等，则所对应的真后缀为next[k-1];
				因为改变k长度的只有下面k++一行，且只有k > 0时才有读取next数组的操作，
				所以k读取的永远时已经被计算好的
				*/
				while(k > 0 && p[k] != p[i])k = next[k-1];
				if(p[k] == p[i])k++;
				next[i] = k;
		}

		ret = NULL;
		s = beg;

		for(k = 0; k < m && s != end; ++s)
		{
				while(k > 0 && p[k] != *s) k = next[k-1];
				if(p[k] == *s)k++;
		}

		ret = k == m ? s - m : NULL;

		AR_DEL(next);
		return ret;
}

#endif



const wchar_t* AR_reverse_wcschr(const wchar_t* str, size_t l, wchar_t c)
{
		size_t idx;

		AR_ASSERT(str != NULL);

		if(l == 0)
		{
				return str + l;
		}

		idx = l - 1;
		while(str[idx] != c)
		{
				if(idx == 0)
				{
						break;
				}

				idx--;
		}

		return str + idx;
}






const wchar_t* AR_reverse_wcsstr(const wchar_t *str, size_t l,  const wchar_t *match, size_t ml)
{
		size_t delta;
		uint_t	search_hash, match_hash;
		size_t i;
		AR_ASSERT(str != NULL && match != NULL);

		if (ml > l)
		{
				return NULL;
		}

		if(ml == 0)
		{
				return str + l;
		}

		if(ml == 1)
		{
				return AR_reverse_wcschr(str, l, match[0]);
		}


		delta = l - ml;


		search_hash = 0;
		match_hash = 0;

		for(i = 0; i < ml; ++i)
		{
				search_hash += (uint_t)str[delta + i];
				match_hash += (uint_t)match[i];
		}


		while(search_hash != match_hash || AR_wcsncmp(str + delta, match, ml) != 0)
		{
				if(delta == 0)
				{
						return NULL;
				}

				delta--;
				search_hash -= str[delta + ml];
				search_hash += str[delta];
		}

		return str + delta;
}



const wchar_t* AR_reverse_wcsichr(const wchar_t* str, size_t l, wchar_t c)
{
		size_t idx;
		wchar_t low_c;
		AR_ASSERT(str != NULL);

		if(l == 0)
		{
				return str + l;
		}

		low_c = AR_towlower(c);
		idx = l - 1;

		while(AR_towlower(str[idx]) != low_c)
		{
				if(idx == 0)
				{
						break;
				}

				idx--;
		}

		return str + idx;
}


const wchar_t* AR_reverse_wcsistr(const wchar_t *str, size_t l,  const wchar_t *match, size_t ml)
{
		size_t delta;
		uint_t	search_hash, match_hash;
		size_t i;
		AR_ASSERT(str != NULL && match != NULL);

		if (ml > l)
		{
				return NULL;
		}

		if(ml == 0)
		{
				return str + l;
		}

		if(ml == 1)
		{
				return AR_reverse_wcsichr(str, l, match[0]);
		}


		delta = l - ml;


		search_hash = 0;
		match_hash = 0;

		for(i = 0; i < ml; ++i)
		{
				search_hash += (uint_t)AR_towlower(str[delta + i]);
				match_hash += (uint_t)AR_towlower(match[i]);
		}


		while(search_hash != match_hash || AR_wcsnicmp(str + delta, match, ml) != 0)
		{
				if(delta == 0)
				{
						return NULL;
				}

				delta--;
				search_hash -= (uint_t)AR_towlower(str[delta + ml]);
				search_hash += (uint_t)AR_towlower(str[delta]);
		}

		return str + delta;
}




bool_t	AR_wcs_is_float(const wchar_t *in, const wchar_t *end)
{
		const wchar_t *p;
		
		bool_t is_float;

		AR_ASSERT(in != NULL && end != NULL && in <= end);

		is_float = false;

		p = AR_wcstrim_space_s(in, end);

		if(*p == L'-' || *p == L'+')
		{
				++p;
		}


		while(p < end && *p >= L'0' && *p <= L'9')/*可能是个整数*/
		{
				++p;
		}

		if(p < end && *p == L'.')/*也许是浮点，但可能有错误*/
		{
				is_float = true;
				++p;

				while(p < end && *p >= L'0' && *p <= L'9')
				{
						++p;
				}
		}

		if(p < end && (*p == L'e' || *p == L'E'))/*可能是浮点，但是会有错误*/
		{
				++p;

				if(*p == L'+' || *p == L'-')
				{
						++p;
				}
				
				is_float = false;

				while(p < end && *p >= L'0' && *p <= L'9')/*e后必须跟随指数*/
				{
						++p;
						is_float = true;
				}
		}
		return is_float;
}

bool_t	AR_wcs_is_int(const wchar_t *in, const wchar_t *end)
{
		int_64_t un;

		AR_ASSERT(in != NULL && end != NULL && in <= end);

		if(AR_wcs_is_float(in, end))
		{
				return false;
		}

		
		if(AR_wtoi64_s(in, end, &un, 0) != NULL)
		{
				return true;
		}

		if(AR_wtou64_s(in, end, (uint_64_t*)&un, 0) != NULL)
		{
				return true;
		}

		return false;
}




AR_NAMESPACE_END

