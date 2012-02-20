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



int_16_t		AR_BYTEFLIP_16(int_16_t val)
{
		byte_t t;
		union{
				byte_t b[2]; int_16_t v;
		}v16;
		v16.v = val;
		t = v16.b[0];
		v16.b[0] = v16.b[1];
		v16.b[1] = t;
		return v16.v;
}

uint_16_t		AR_BYTEFLIP_U16(uint_16_t val)
{
		byte_t t;
		union{
				byte_t b[2]; uint_16_t v;
		}v16;
		v16.v = val;
		t = v16.b[0];
		v16.b[0] = v16.b[1];
		v16.b[1] = t;
		return v16.v;
}


int_32_t		AR_BYTEFLIP_32(int_32_t val)
{
		byte_t t;
		union{
				byte_t b[4]; int_32_t v;
		}v32;
		v32.v = val;
		t = v32.b[0];
		v32.b[0] = v32.b[3];
		v32.b[3] = t;

		t = v32.b[1];
		v32.b[1] = v32.b[2];
		v32.b[2] = t;
		return v32.v;
}

uint_32_t		AR_BYTEFLIP_U32(uint_32_t val)
{
		byte_t t;
		union{
				byte_t b[4]; uint_32_t v;
		}v32;
		v32.v = val;
		t = v32.b[0];
		v32.b[0] = v32.b[3];
		v32.b[3] = t;

		t = v32.b[1];
		v32.b[1] = v32.b[2];
		v32.b[2] = t;
		return v32.v;
}


int_64_t		AR_BYTEFLIP_64(int_64_t val)
{
		byte_t t;
		union{
				byte_t b[8]; int_64_t v;
		}v64;
		v64.v = val;
		t = v64.b[0];
		v64.b[0] = v64.b[7];
		v64.b[7] = t;


		t = v64.b[1];
		v64.b[1] = v64.b[6];
		v64.b[6] = t;


		t = v64.b[2];
		v64.b[2] = v64.b[5];
		v64.b[5] = t;


		t = v64.b[3];
		v64.b[3] = v64.b[4];
		v64.b[4] = t;
		
		return v64.v;
}


uint_64_t		AR_BYTEFLIP_U64(uint_64_t val)
{
		byte_t t;
		union{
				byte_t b[8]; uint_64_t v;
		}v64;
		v64.v = val;
		t = v64.b[0];
		v64.b[0] = v64.b[7];
		v64.b[7] = t;


		t = v64.b[1];
		v64.b[1] = v64.b[6];
		v64.b[6] = t;


		t = v64.b[2];
		v64.b[2] = v64.b[5];
		v64.b[5] = t;


		t = v64.b[3];
		v64.b[3] = v64.b[4];
		v64.b[4] = t;
		
		return v64.v;
}



AR_NAMESPACE_END