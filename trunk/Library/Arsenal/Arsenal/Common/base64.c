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





void __six_for_uint32_little(byte_t *out, uint_32_t w)
{
		const byte_t *b;
		AR_ASSERT(out != NULL);
		
		b = (const byte_t*)&w;
		
		out[0] = ( b[0] & 0xfc ) >> 2;
		out[1] = ( ( b[0] & 0x3 ) << 4 ) + ( ( b[1] & 0xf0 ) >> 4 );
		out[2] = ( ( b[1] & 0xf ) << 2 ) + ( ( b[2] & 0xc0 ) >> 6 );
		out[3] = b[2] & 0x3f;
}

void __six_for_uint32_big(byte_t *out, uint_32_t w)
{
		size_t i;
		AR_ASSERT(out != NULL);

		for(i = 0; i < 4 ; i++)
		{
				out[i] = w & 0x3f;
				w >>= 6;
		}
}


uint_32_t __uint32_for_six_little(const byte_t *input)
{
		uint_32_t ret;
		byte_t *b;
		AR_ASSERT(input != NULL);
		
		ret = 0;
		b = (byte_t*)&ret;
		b[0] |= input[0] << 2;
		b[0] |= (input[1] & 0x30 ) >> 4;
		b[1] |= (input[1] & 0xf ) << 4;
		b[1] |= (input[2] & 0x3c ) >> 2;
		b[2] |= (input[2] & 0x3 ) << 6;
		b[2] |= input[3];
		return ret;
}

uint_32_t __uint32_for_six_big(const byte_t *input)
{
		uint_32_t ret;
		AR_ASSERT(input != NULL);
		ret = 0;

		ret |= input[0];
		ret |= input[1] << 6;
		ret |= input[2] << 2*6;
		ret |= input[3] << 3*6;
		return ret;
}


#if defined(ARCH_BIG_ENDIAN)
						
#define __six_for_uint32		__six_for_uint32_big
#define __uint32_for_six		__uint32_for_six_big
						
#else

#define __six_for_uint32	__six_for_uint32_little
#define __uint32_for_six	__uint32_for_six_little

#endif




/***********************************************************base64*********************************************************/

static const char ___g_base64_digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static size_t __base64_need_len(const byte_t *input, size_t ilen)
{
		size_t need_n;
		AR_UNUSED(input);
		need_n = 0;
		need_n = ilen / 3 * 4;

		if(ilen % 3)
		{
				need_n += 4;
		}

		return need_n;
}







size_t AR_base64_encode(byte_t  *out, size_t olen, const byte_t *input, size_t ilen)
{
		size_t r, need_n,i,j;
		uint_32_t w;
		AR_ASSERT(input != NULL && ilen > 0);

		need_n = __base64_need_len(input, ilen);
		if(out == NULL)
		{
				return need_n;
		}

		if(olen < need_n)
		{
				return 0;
		}

		
		r = ilen;
		
		w = 0;
		i = 0;
		while(r > 0)
		{
				w |= *input << i*8;
				++input;
				--r;
				++i;
				if(r == 0 || i == 3)
				{
						byte_t tmp[4];
						__six_for_uint32(tmp, w);
						for(j = 0; j * 6 < i * 8; ++j)
						{
								*out++ = ___g_base64_digits[tmp[j]];
						}

						if(r == 0)
						{
								for(j = i; j < 3; ++j)
								{
										*out++ = '=';
								}
						}

						w = 0;
						i = 0;
				}
		}

		return need_n;
}



static const byte_t __g_base64_to_sixtet[] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x3F, 
	0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 
	0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 
	0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



size_t AR_base64_decode(byte_t  *out, size_t olen, const byte_t *input, size_t ilen)
{
		byte_t *o;
		size_t need_n,i,j,k;
		byte_t tmp[4] = {0,0,0,0};
		

		AR_ASSERT(input != NULL && ilen > 0);

		need_n = 3 * ilen / 4;

		if(out == NULL)
		{
				return need_n;
		}

		if(olen < need_n)
		{
				return 0;
		}


		for(i = 0, o = out, need_n = 0, k = 0; i < ilen && input[i] != '\0' && input[i] != '='; ++i)
		{
				if(input[i] == ' ' || input[i] == '\n')
				{
						continue;
				}

				tmp[k++] = __g_base64_to_sixtet[input[i]];
				
				if(input[i+1] == '\0' || input[i+1] == '=' || k == 4)
				{
						
						uint_32_t w = 0;
						w = __uint32_for_six(tmp);
						
						for(j = 0; j * 8 < k * 6; ++j)
						{
								*o++ = w & 0xff;
								w >>= 8;
								++need_n;
						}

						tmp[0] = tmp[1] = tmp[2] = tmp[3] = 0;
						k = 0;
				}
		}

		
		return need_n;
}





AR_NAMESPACE_END

