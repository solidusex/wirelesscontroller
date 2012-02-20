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
#ifndef __PARSER_IN__H__
#define __PARSER_IN__H__

#include "parser.h"

AR_NAMESPACE_BEGIN



/*typedef struct __parser_symbol_tag psrSymb_t;*/

/*����Ϊ�ս��*/
extern const psrSymb_t	*PARSER_EOISymb;   /*��ʾ�����β����*/
extern const psrSymb_t	*PARSER_ErrorSymb;/*����Ĵ��������ʽ����ս����*/
extern const psrSymb_t	*PARSER_DefPrecSymb;/*�������ս���Ĳ���ʽ��δָ��prec_tok�Ĳ���ʽ����ص��ս��*/

/*���¶�Ϊ���ս��*/
extern const psrSymb_t	*PARSER_StartSymb;/*��һ�����ţ���ת��Ϊ %Start -> gmr->head[0]*/


#define			PARSER_MAX_TERM_SYMB_SPEC_ID	2

bool_t			Parser_IsBuildInSymbol(const psrSymb_t	*symb);


/*����parser������صķ��Ŷ������º������䣬�˹���Ϊ���ŶԱ��ṩ��O(1)������(ֻ��Ա�ָ��)*/

#define PARSER_STRTBL_BUCKET		(1536)


const wchar_t*	Parser_AllocString(const wchar_t *str);
const wchar_t*	Parser_AllocStringN(const wchar_t *str, size_t n);

/*
const wchar_t*  Parser_AllocStringInt(int_64_t num, size_t radix);
const wchar_t*  Parser_AllocStringUInt(uint_64_t num, size_t radix);
*/




AR_NAMESPACE_END

#endif

