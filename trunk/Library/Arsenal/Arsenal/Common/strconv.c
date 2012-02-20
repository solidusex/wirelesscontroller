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

#if(0)
static size_t __utf8_to_unicode_char(const byte_t *utf8, size_t len, wchar_t *uch)
{
		size_t v,n,e;
		const byte_t *p;

		AR_ASSERT(utf8 != NULL && len > 0);

		v = (size_t)(*utf8); n = 0; e= 0; p = utf8;

		if(v >= 0xfc)
		{
				n = 6;/*6:<11111100>*/
				if(n > len)return 0;
				e = (p[0] & 0x01) << 30;
				e |= (p[1] & 0x3f) << 24;
				e |= (p[2] & 0x3f) << 18;
				e |= (p[3] & 0x3f) << 12;
				e |= (p[4] & 0x3f) << 6;
				e |= (p[5] & 0x3f);
		}else if(v >= 0xf8)
		{
				n = 5;/*5:<11111000>*/
				if(n > len)return 0;
				 e = (p[0] & 0x03) << 24;
				e |= (p[1] & 0x3f) << 18;
				e |= (p[2] & 0x3f) << 12;
				e |= (p[3] & 0x3f) << 6;
				e |= (p[4] & 0x3f);

		}else if(v >= 0xf0)
		{
				n = 4; /*4:<11110000>*/
				if(n > len)return 0;
				e = (p[0] & 0x07) << 18;
				e |= (p[1] & 0x3f) << 12;
				e |= (p[2] & 0x3f) << 6;
				e |= (p[3] & 0x3f);
		}else if(v >= 0xe0)
		{
				n = 3;/*3:<11100000>*/
				if(n > len)return 0;
				e = (p[0] & 0x0f) << 12;
				e |= (p[1] & 0x3f) << 6;
				e |= (p[2] & 0x3f);

		}else if(v >= 0xc0)
		{
				n = 2;/*3:<11000000>*/
				if(n > len)return 0;
				e = (p[0] & 0x1f) << 6;
				e |= (p[1] & 0x3f);
		}else
		{
				n = 1;
				if(n > len)return 0;
				e = p[0];
		}
		if(uch)*uch = (wchar_t)e;
		return n;
}


static size_t __unicode_to_utf8_char(wchar_t uch, byte_t *utf8)
{
		byte_t buf[10];
		byte_t *e;
		uint_32_t	uc = (uint_32_t)uch;

		e = (utf8 ? utf8 : buf);

		if(uc < 0x80)
		{
				*e++ = (byte_t)uc;
		}else if(uc < 0x800)
		{
				/*<11011111> < 000 0000 0000>*/
				*e++ = (byte_t)((uc >> 6) & 0x1f)|0xc0;
				*e++ = (byte_t)(uc & 0x3f)|0x80;
		}else if(uc < 0x10000)
		{
				/*<11101111> <0000 0000 0000 0000>*/
				*e++ = (byte_t)(((uc >> 12) & 0x0f)|0xe0);
				*e++ = (byte_t)(((uc >> 6) & 0x3f)|0x80);
				*e++ = (byte_t)((uc & 0x3f)|0x80);
		}else if(uc < 0x200000)
		{
				/*<11110111> <0 0000 0000 0000 0000 0000>*/
				*e++ = (byte_t)(((uc >> 18) & 0x07)|0xf0);
				*e++ = (byte_t)(((uc >> 12) & 0x3f)|0x80);
				*e++ = (byte_t)(((uc >> 6) & 0x3f)|0x80);
				*e++ = (byte_t)((uc & 0x3f)|0x80);
		}else if(uc < 0x4000000)
		{
				/*<11111011> <00 0000 0000 0000 0000 0000 0000>*/
				*e++ = (byte_t)(((uc >> 24) & 0x03)|0xf8);
				*e++ = (byte_t)(((uc >> 18) & 0x3f)|0x80);
				*e++ = (byte_t)(((uc >> 12) & 0x3f)|0x80);
				*e++ = (byte_t)(((uc >> 6) & 0x3f)|0x80);
				*e++ = (byte_t)((uc & 0x3f)|0x80);
		}else
		{
				/*<11111101> <0000 0000 0000 0000 0000 0000 0000 0000>*/
				*e++ = (byte_t)(((uc >> 30) & 0x01)|0xfc);
				*e++ = (byte_t)(((uc >> 24) & 0x3f)|0x80);
				*e++ = (byte_t)(((uc >> 18) & 0x3f)|0x80);
				*e++ = (byte_t)(((uc >> 12) & 0x3f)|0x80);
				*e++ = (byte_t)(((uc >> 6) & 0x3f)|0x80);
				*e++ = (byte_t)((uc & 0x3f)|0x80);
		}

		return utf8 ? e - utf8 : e - buf;
}




size_t AR_wcs_to_utf8(const wchar_t *unicode, size_t n, char *out, size_t out_len)
{
		char *p;
		size_t i, need;
		AR_ASSERT(unicode != NULL);

		for(i = 0,need = 0; i < n; ++i)need += __unicode_to_utf8_char(unicode[i], NULL);

		if(out != NULL)
		{
				p = out;
				if(out_len < need)return 0;
				for(i = 0; i < n; ++i)p += __unicode_to_utf8_char(unicode[i], (byte_t*)p);
		}

		return need;
}

size_t AR_utf8_to_wcs(const char *utf8, size_t n, wchar_t *out, size_t out_len)
{
		const char *p;
		size_t need; int_t l;
		AR_ASSERT(utf8 != NULL && n > 0);
		p = utf8; need = 0; l = (int_t)n;

		while(l > 0)
		{
				size_t nc = __utf8_to_unicode_char((const byte_t*)p, (size_t)l, NULL);
				if(nc == 0)return 0;
				need++;
				p += nc;
				l -= nc;
		}

		if(out != NULL)
		{
				if(out_len < need)return 0;

				l = n; p = utf8; need = 0;
				while(l > 0)
				{
						size_t nc = __utf8_to_unicode_char((const byte_t*)p, (size_t)l, &out[need]);
						need++;
						l -= nc;
						p += nc;
				}
		}

		return need;
}



wchar_t* AR_utf8_convto_wcs(const char *utf8)
{
		wchar_t *buf;
		size_t need;
		size_t in_len;

		AR_ASSERT(utf8 != NULL);

		in_len = AR_strlen(utf8);

		if(in_len == 0)
		{
				return AR_wcsdup(L"");
		}

		need = AR_utf8_to_wcs(utf8, in_len, NULL, 0);

		if(need == 0)return NULL;/*输入有问题*/

		buf = AR_NEWARR(wchar_t, need + 1);
		buf[need] = L'\0';
		AR_utf8_to_wcs(utf8, in_len, buf, need);
		return buf;
}

char*  AR_wcs_convto_utf8(const wchar_t *wcs)
{
		char *buf; size_t need; size_t in_len;

		AR_ASSERT(wcs);

		in_len = AR_wcslen(wcs);

		if(in_len == 0)
		{
				return AR_strdup("");
		}

		need = AR_wcs_to_utf8(wcs,in_len, NULL, 0);

		if(need == 0)return NULL;/*输入有问题*/

		buf = AR_NEWARR(char, need + 1); buf[need] = '\0';

		AR_wcs_to_utf8(wcs,in_len, buf, need);
		return buf;
}

#endif





#if defined(OS_FAMILY_WINDOWS)


static UINT __get_codepage_for_winapi(arCodePage_t cp)
{
		switch(cp)
		{
		default: /*CP_ACP*/
				return CP_ACP;
		case AR_CP_UTF8:
				return CP_UTF8;
		case AR_CP_GB2312:
				return 936;
		case AR_CP_GB18030:
				return 54936;
		case AR_CP_BIG5:
				return 950;
		}
}



size_t					AR_str_to_wcs(arCodePage_t cp, const char *acp, size_t n, wchar_t *out, size_t out_len)
{
		int len;
		const UINT win_cp = __get_codepage_for_winapi(cp);
		AR_ASSERT(acp != NULL);

		len = MultiByteToWideChar(win_cp, 0, acp, (int)n, 0, 0);


		if(len == 0 || out_len == 0 || out == NULL)
		{
				if(len == 0)
				{
						
				}

				return len;
		}

		if((int)out_len < len)
		{
				
				return 0;
		}

		if(MultiByteToWideChar(win_cp, 0, acp, (int)n, out, (int)out_len) == 0)
		{
				return 0;
		}else
		{
				return len;
		}
}


size_t					AR_wcs_to_str(arCodePage_t cp, const wchar_t *input, size_t n, char *out, size_t out_len)
{
		int len;
		const UINT win_cp = __get_codepage_for_winapi(cp);
		AR_ASSERT(input != NULL);

		len = WideCharToMultiByte(win_cp, 0, input, (int)n, 0, 0, NULL, NULL);

		if(len == 0 || out == NULL || out_len == 0)
		{
				if(len == 0)
				{
						
				}
				return len;
		}

		if((int)out_len < len)
		{
				return 0;
		}


		if(WideCharToMultiByte(win_cp, 0, input, (int)n, out, (int)out_len, NULL, NULL) == 0)
		{
				return 0;
		}else
		{
				return len;
		}
}


char*					AR_wcs_convto_str(arCodePage_t cp, const wchar_t *input, size_t in_n)
{
		char *ret;
		int n;
		const UINT win_cp = __get_codepage_for_winapi(cp);
		AR_ASSERT(input != NULL);
		n = (int)in_n;

		if(n == 0)
		{
				return AR_strdup("");
		}else
		{
				int len = WideCharToMultiByte(win_cp, 0, input, n, 0, 0, NULL, NULL);
				if(len == 0)
				{
					
						return NULL;
				}

				ret = AR_NEWARR(char, len + 1);

				if(ret == NULL)
				{
					
						return NULL;
				}

				len = WideCharToMultiByte(win_cp, 0, input, n, ret, len, NULL, NULL);
				
				if(len == 0)
				{
					
						AR_DEL(ret);
						ret = NULL;
				}else
				{
						ret[len] = 0;
				}

				return ret;
		}
}

wchar_t*				AR_str_convto_wcs(arCodePage_t cp, const char *input, size_t in_n)
{
		wchar_t *ret;
		const UINT win_cp = __get_codepage_for_winapi(cp);
		AR_ASSERT(input != NULL);
		if(in_n == 0)
		{
				return AR_wcsdup(L"");
		}else
		{
				int len = MultiByteToWideChar(win_cp, 0, input, (int)in_n, 0, 0);
				if(len == 0)
				{
						return NULL;

				}

				ret = AR_NEWARR(wchar_t, len + 1);

				if(ret == NULL)
				{
					
						return NULL;
				}


				len = MultiByteToWideChar(win_cp, 0, input, (int)in_n, ret, len);
				if(len == 0)
				{
					
						AR_DEL(ret);
						ret = NULL;
				}else
				{
						ret[len] = 0;
				}

				return ret;
		}
}




#elif defined(OS_FAMILY_UNIX)





const char *__get_locale_str_for_iconv(arCodePage_t cp)
{
		switch(cp)
		{
		default: 
				return "";
		case AR_CP_UTF8:
				return "UTF-8";
		case AR_CP_GB2312:
				return "GB2312";
		case AR_CP_GB18030:
				return "GB18030";
		case AR_CP_BIG5:
				return "BIG5";
		}
}


#if(OS_TYPE ==  OS_IOS) || (OS_TYPE == OS_MAC_OS_X)


		#if defined(ARCH_LITTLE_ENDIAN)
				#define UNICODE_ENCODING_NAME	"UCS-4LE"
		#else
				#define UNICODE_ENCODING_NAME	"UCS-4"
		#endif

#else
		#define UNICODE_ENCODING_NAME	"wchar_t"
#endif






size_t					AR_str_to_wcs(arCodePage_t cp, const char *acp, size_t n, wchar_t *out, size_t out_len)
{
		size_t len;
		size_t ret;
		wchar_t *wstr;
		AR_ASSERT(acp != NULL);
		wstr = AR_str_convto_wcs(cp, acp, n);
		if(wstr == NULL)
		{
				ret = 0;
				goto CLEAN_POINT;
		}

		len = AR_wcslen(wstr);

		if(len == 0 || out == NULL || out_len == 0)
		{
				ret = len;
				goto CLEAN_POINT;
		}

		if(out_len < len)
		{
				ret = 0;
				goto CLEAN_POINT;
		}

		AR_wcsncpy(out, wstr, len);
		ret = len;

CLEAN_POINT:
		if(wstr)
		{
				AR_DEL(wstr);
				wstr = NULL;
		}
		return ret;
}

size_t					AR_wcs_to_str(arCodePage_t cp, const wchar_t *input, size_t n, char *out, size_t out_len)
{
		size_t len;
		size_t ret;
		char *str;
		AR_ASSERT(input != NULL);
		str = AR_wcs_convto_str(cp, input, n);

		if(str == NULL)
		{
				ret = 0;
				goto CLEAN_POINT;
		}

		len = AR_strlen(str);

		if(len == 0 || out == NULL || out_len == 0)
		{
				ret = len;
				goto CLEAN_POINT;
		}

		if(out_len < len)
		{
				ret = 0;
				goto CLEAN_POINT;
		}

		AR_strncpy(out, str, len);
		ret = len;

CLEAN_POINT:
		if(str)
		{
				AR_DEL(str);
				str = NULL;
		}
		return ret;

}




wchar_t*				AR_str_convto_wcs(arCodePage_t cp, const char *input, size_t in_n)
{

        char   *out    = NULL;
        size_t out_len = 0;

        char   *inbuf  = NULL;
        char   *outbuf = NULL;
        size_t inleft;
        size_t outleft;
        iconv_t cd;
		const char *cp_iconv = __get_locale_str_for_iconv(cp);
		bool_t	is_ok = true;

		AR_ASSERT(input != NULL);

		if(in_n == 0)
        {
				return AR_wcsdup(L"");
        }

        out_len = sizeof(wchar_t) * (in_n + 1);
        out = (char*)AR_NEWARR0(wchar_t , in_n + 1);

		if(out == NULL)
		{
				is_ok = false;
				cd = NULL;
				goto CLEAN_POINT;
		}

		cd = iconv_open(UNICODE_ENCODING_NAME, cp_iconv);
		//cd = iconv_open("wchar_t", cp_iconv);


        if(cd == (iconv_t)-1)
        {
				is_ok = false;
				cd = NULL;
				goto CLEAN_POINT;
        }

        inbuf = (char*)input;
        outbuf = out;
        inleft = in_n;
        outleft = out_len;

        if(iconv(cd, &inbuf, &inleft, &outbuf, &outleft) == (size_t)-1)
        {
				is_ok = false;
				goto CLEAN_POINT;
        }

CLEAN_POINT:
		if(cd)
		{
				iconv_close(cd);
				cd = NULL;
		}

		if(!is_ok)
		{
				if(out)
				{
						AR_DEL(out);
						out = NULL;
				}
		}

        return (wchar_t*)out;
}



char*					AR_wcs_convto_str(arCodePage_t cp, const wchar_t *input, size_t in_n)
{
        char   *in     = NULL;
        size_t in_len;
        size_t len ;
        char   *out    = NULL;
        size_t out_len = 0;

        iconv_t cd  = NULL;
        bool_t is_ok;
		const char *cp_iconv = __get_locale_str_for_iconv(cp);
        AR_ASSERT(input != NULL);

        in = (char*)input;
        len = in_n;

        if(len == 0)
        {
				return  AR_strdup("");
        }

        is_ok = true;
        in_len = len * sizeof(wchar_t);

        out_len = (len + 1) * 6;
		out = AR_NEWARR0(char, out_len);

		if(out == NULL)
		{
				is_ok = false;
				cd = NULL;
				goto CLEAN_POINT;
		}


        cd = iconv_open(cp_iconv,  UNICODE_ENCODING_NAME);

        if(cd == (iconv_t)-1)
        {
				is_ok = false;
				cd = NULL;
				goto CLEAN_POINT;
        }

        {
            char   *inbuf  = in;
            char   *outbuf = out;
            size_t inleft  = in_len;
            size_t outleft = out_len;

            if(iconv(cd, &inbuf, &inleft, &outbuf, &outleft) != 0)
            {
					is_ok = false;
					goto CLEAN_POINT;
            }
        }

CLEAN_POINT:

        if(cd)
        {
            iconv_close(cd);
            cd = NULL;
        }

        if(!is_ok && out)
        {
				AR_DEL(out);
				out = NULL;
        }

        return out;

}






#else

#error Unknow platform

#endif





AR_NAMESPACE_END

