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



#include "tools.h"


AR_NAMESPACE_BEGIN

arStatus_t	Tools_Init()
{
		CFG_Init();
		return AR_S_YES;
}

arStatus_t	Tools_UnInit()
{
		CFG_UnInit();
		return AR_S_YES;
}



AR_NAMESPACE_END

