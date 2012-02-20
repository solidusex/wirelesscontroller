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


#if defined(OS_FAMILY_WINDOWS)
		#include "thread_win.h"

#elif defined(OS_FAMILY_UNIX)

	#if (OS_TYPE == OS_MAC_OS_X || OS_TYPE == OS_IOS)
			#include "thread_apple.h"
	#else
			#include "thread_posix.h"
	#endif

#else

		#error "Target OS system not supported"

#endif

AR_NAMESPACE_BEGIN

uint_64_t		AR_GetTime_Milliseconds()
{
		return AR_GetTime_Microseconds() / AR_BIGNUM_U64(1000);
}









AR_NAMESPACE_END
