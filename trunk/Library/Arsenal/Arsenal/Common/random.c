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

void			AR_srand(uint_64_t seed)
{
		srand((unsigned int)seed);
}


uint_64_t AR_rand64()
{
		uint_64_t res = rand();
		res ^= (uint_64_t)rand() << 15;
		res ^= (uint_64_t)rand() << 30;
		res ^= (uint_64_t)rand() << 45;
		res ^= (uint_64_t)rand() << 60;
		return res;

}

uint_32_t AR_rand32()
{
		uint_32_t res = rand();
		res ^= (uint_32_t)rand() << 15;
		res ^= (uint_32_t)rand() << 30;
		return res;
}

float AR_rand_flt()
{
		return (float)AR_rand_dbl();
}

double AR_rand_dbl()
{
		return (double)AR_rand64() / (double)ULLONG_MAX;
}













AR_NAMESPACE_END


