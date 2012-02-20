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


#ifndef __TGU_COMPILER_H__
#define __TGU_COMPILER_H__


#include "tengu.h"
#include "tgusyntree.h"


AR_NAMESPACE_BEGIN



bool_t	TGU_Compile(const tguReport_t	*report, tguBlock_t	 *block, arString_t *out);



AR_NAMESPACE_END

#endif
