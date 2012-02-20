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

#ifndef AR_HEADER_H
#define AR_HEADER_H


#include "./Common/common.h"
#include "./Lex/lex.h"
#include "./Parser/parser.h"
#include "./Tools/tools.h"
#include "./Tengu/tengu.h"



AR_NAMESPACE_BEGIN


arStatus_t	Arsenal_Init(const arInit_t *ctx);
arStatus_t	Arsenal_UnInit();




AR_NAMESPACE_END


#endif

