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

/*以下为终结符*/
extern const psrSymb_t	*PARSER_EOISymb;   /*表示输入结尾符号*/
extern const psrSymb_t	*PARSER_ErrorSymb;/*特殊的错误处理产生式标记终结符，*/
extern const psrSymb_t	*PARSER_DefPrecSymb;/*所有无终结符的产生式且未指定prec_tok的产生式所相关的终结符*/

/*以下都为非终结符*/
extern const psrSymb_t	*PARSER_StartSymb;/*第一个符号，被转换为 %Start -> gmr->head[0]*/


#define			PARSER_MAX_TERM_SYMB_SPEC_ID	2

bool_t			Parser_IsBuildInSymbol(const psrSymb_t	*symb);


/*所有parser配置相关的符号都由以下函数分配，此功能为符号对比提供了O(1)的性能(只需对比指针)*/

#define PARSER_STRTBL_BUCKET		(1536)


const wchar_t*	Parser_AllocString(const wchar_t *str);
const wchar_t*	Parser_AllocStringN(const wchar_t *str, size_t n);

/*
const wchar_t*  Parser_AllocStringInt(int_64_t num, size_t radix);
const wchar_t*  Parser_AllocStringUInt(uint_64_t num, size_t radix);
*/




AR_NAMESPACE_END

#endif

