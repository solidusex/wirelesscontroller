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


#ifndef __PARSER_LR_ACTION__
#define __PARSER_LR_ACTION__

#include "parser.h"
#include "parser_in.h"


AR_NAMESPACE_BEGIN

/************************************************语法分析表*********************************************************************/

typedef enum
{
		PARSER_SHIFT = 0,
		PARSER_REDUCE,
		PARSER_ACCEPT,
		PARSER_ERROR
}psrActionType_t;

typedef struct __action_record_tag
{
		size_t							type			:	2		;
		size_t							rule_num		:	13		;	
		size_t							prec			:	9		;	
		size_t							delim			:	8  		;	

		size_t							shift_to		:	24		;
		size_t							reduce_count 	:	8 		;		/*规约时用到，产生式如果为%Epsilon，则count为0*/
		
		struct __action_record_tag		*next;
}psrAction_t;





extern const psrAction_t	*	const PARSER_ErrorAction;



struct __parser_action_tag
{
		psrSymbList_t	term_set;
		psrSymbList_t	nonterm_set;

		int_t			*goto_tbl;
		size_t			goto_row;
		size_t			goto_col;

		size_t			row;
		size_t			col;
		psrAction_t		**actions;
		psrSymbList_t	*expected_set;
};




const psrAction_t*			Parser_GetAction(const psrActionTable_t *tbl, size_t state, const psrSymb_t *symb);
int_t						Parser_GetState(const psrActionTable_t *tbl, size_t state, const psrSymb_t *symb);
const psrSymbList_t*		Parser_GetExpectedSymb(const psrActionTable_t *tbl, size_t state);


const psrActionTable_t*		Parser_CreateActionTable_SLR(const psrGrammar_t *grammar);
const psrActionTable_t*		Parser_CreateActionTable_LALR(const psrGrammar_t *grammar);

void						Parser_DestroyActionTable(const psrActionTable_t *tbl);




AR_NAMESPACE_END




#endif

