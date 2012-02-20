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

/******************************************************Misc**************************************************************/

AR_NAMESPACE_BEGIN


bool_t	AR_is_equal_flt(float x, float y, float epsilon)
{
		if(x == y || AR_abs_flt(x - y) < epsilon)
		{
				return true;
		}else
		{
				return false;
		}
}

bool_t	AR_is_equal_dbl(double x, double y, double epsilon)
{
		if(x == y || AR_abs_dbl(x - y) < epsilon)
		{
				return true;
		}else
		{
				return false;
		}
}




double AR_logbase_dbl(double a, double base)
{
		return log(a) / log(base);
}





int_32_t		AR_abs_32(int_32_t x)
{
		int_32_t y = x >> 31;
		return ( ( x ^ y ) - y );
}


int_64_t		AR_abs_64(int_64_t x)
{
		int_64_t y = x >> 63;
		return ( ( x ^ y ) - y );
}



double			AR_abs_dbl(double x)
{
		return (double)fabs(x);
}


double AR_floor_dbl(double f)
{
		return (double)floor(f);
}

double AR_ceil_dbl(double f)
{
		return (double)ceil(f);
}

double			AR_sqrt_dbl(double f)
{
		return (double)sqrt(f);
}


double AR_pow_dbl(double x, double y)
{
		return (double)pow(x,y);
}

double AR_exp(double f)
{
		return (double)exp(f);
}


double AR_sin_dbl(double f)
{
		return (double)sin(f);
}


double AR_cos_dbl(double f)
{
		return (double)cos(f);
}


double AR_tan_dbl(double f)
{
		return (double)tan(f);
}

double AR_asin_dbl(double f)
{
		return (double)asin(f);
}

double AR_acos_dbl(double f)
{
		return (double)acos(f);
}

double AR_atan_dbl(double f)
{
		return (double)atan(f);
}

double AR_atan2_dbl(double y, double x)
{
		return (double)atan2(y,x);
}



float AR_logbase_flt(float a, float base)
{
		return logf(a) / logf(base);
}


float			AR_abs_flt(float x)
{
		return (float)fabsf(x);
}

float			AR_ceil_flt(float f)
{
		return ceilf(f);
}

float			AR_floor_flt(float f)
{
		return floorf(f);
}

float			AR_sqrt_flt(float f)
{
		return sqrtf(f);
}

float			AR_exp_flt(float f)
{
		return expf(f);
}

float			AR_pow_flt(float x, float y)
{
		return powf(x,y);
}


float			AR_sin_flt(float f)
{
		return sinf(f);
}

float			AR_cos_flt(float f)
{
		return cosf(f);
}

float			AR_tan_flt(float f)
{
		return tanf(f);
}

float			AR_asin_flt(float f)
{
		return asinf(f);
}

float			AR_acos_flt(float f)
{
		return acosf(f);
}

float			AR_atan_flt(float f)
{
		return atanf(f);
}

float			AR_atan2_flt(float y, float x)
{
		return atan2f(y,x);
}




AR_NAMESPACE_END






