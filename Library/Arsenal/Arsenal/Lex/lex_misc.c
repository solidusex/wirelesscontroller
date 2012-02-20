
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


#include "rgx.h"

AR_NAMESPACE_BEGIN


bool_t Lex_IsLineTerminator(wchar_t c)
{
		switch(c)
		{
		case AR_LEX_LF:
		case AR_LEX_VT:
		case AR_LEX_FF:
		case AR_LEX_CR:
		case AR_LEX_NEL:
		case AR_LEX_LS:
		case AR_LEX_PS:
				return true;
		default:
				return false;
		}
}


AR_NAMESPACE_END

