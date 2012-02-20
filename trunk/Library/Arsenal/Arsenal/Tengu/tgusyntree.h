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


#ifndef __TGU_SYNTAX_TREE_H__
#define __TGU_SYNTAX_TREE_H__


#include "tengu.h"

AR_NAMESPACE_BEGIN



/***************************************************词法信息****************************************************************/

enum{
TOK_DELIM_ID = 257,
TOK_NAME = 258,
TOK_STRING = 259,
TOK_FLOAT_NUMBER = 260,
TOK_INT_NUMBER = 261,
TOK_FOR = 262,
TOK_DO = 263,
TOK_WHILE = 264,
TOK_IF = 265,
TOK_ELSE = 266,
TOK_CONTINUE = 267,
TOK_BREAK = 268,
TOK_RETURN = 269,
TOK_NULL = 270,
TOK_TRUE = 271,
TOK_FALSE = 272,
TOK_VAR = 273,
TOK_IN = 274,
TOK_IMPORT = 275,
TOK_ELLIPSIS = 276,
TOK_INC = 277,
TOK_DEC = 278,
TOK_ANDAND = 279,
TOK_OROR = 280,
TOK_LE = 281,
TOK_GE = 282,
TOK_EQ = 283,
TOK_NE = 284,
TOK_LESS = 285,
TOK_GREATER = 286,
TOK_L_BRACES = 287,
TOK_R_BRACES = 288,
TOK_L_PAREN = 289,
TOK_R_PAREN = 290,
TOK_L_SQUARE = 291,
TOK_R_SQUARE = 292,
TOK_SEMICOLON = 293,
TOK_COMMA = 294,
TOK_ASSIGN = 295,
TOK_ADD = 296,
TOK_SUB = 297,
TOK_MUL = 298,
TOK_DIV = 299,
TOK_MOD = 300,
TOK_NOT = 301,
TOK_COLON = 302,
TOK_QUEST = 303,
TOK_DOT = 304,
};


const wchar_t* TGU_TokenValToString(size_t tok_val);



typedef	struct __tengu_lexinfo_tag
{
		const wchar_t	*module_name;
		size_t			linenum;
		size_t			col;
}tguLexInfo_t;

typedef struct __tengu_token_tag
{
		const	wchar_t	*token;
		size_t			term_val;
		tguLexInfo_t	lex_info;
}tguToken_t;


/***************************************************前向声明****************************************************************/



struct __tengu_symb_tag;
typedef struct __tengu_symb_tag tguSymb_t;


struct __tengu_block_tag;
typedef struct __tengu_block_tag		tguBlock_t;


struct __tengu_expression_tag;
typedef struct __tengu_expression_tag	tguExpr_t;



struct __tengu_statement_tag;
typedef struct __tengu_statement_tag	tguStmt_t;









/*********************************************表达式**************************************************************/



typedef enum
{
		TGU_OP_ASSIGN, 

		TGU_OP_LOGICAL_OR,		
		TGU_OP_LOGICAL_AND, 
		TGU_OP_LOGICAL_NOT,
		
		TGU_OP_IS_EQUAL, 
		TGU_OP_NOT_EQUAL,
		TGU_OP_LESS, 
		TGU_OP_GREATER, 
		TGU_OP_LESS_OR_EQUAL, 
		TGU_OP_GREATER_OR_EQUAL,
		
		TGU_OP_PLUS, 
		TGU_OP_MINUS, 
		TGU_OP_MUL, 
		TGU_OP_DIV, 
		TGU_OP_MOD,

		TGU_OP_UNARY_PLUS, 
		TGU_OP_UNARY_MINUS,

		TGU_OP_PREINC, 
		TGU_OP_PREDEC, 
		TGU_OP_POSTINC, 
		TGU_OP_POSTDEC,
		
		TGU_OP_NONE		= 0xFFFFFFFF,
}tguExprOP_t;



typedef struct __tengu_index_expression_tag
{
		tguExpr_t		*expr;
		tguExpr_t		*index_expr;
}tguIndexExpr_t;


typedef struct __tengu_binary_expression_tag
{
		tguExprOP_t		op;
		tguExpr_t		*left;
		tguExpr_t		*right;
}tguBinaryExpr_t;


typedef struct __tengu_unary_expression_tag	
{
		tguExprOP_t		op;
		tguExpr_t		*expr;
}tguUnaryExpr_t;

typedef struct __tengu_condition_expression_tag	
{
		tguExpr_t		*cond;
		tguExpr_t		*if_true;
		tguExpr_t		*if_false;
}tguCondExpr_t;



typedef struct __tengu_function_call_expression_tag
{
		tguExpr_t		*func_call;
		tguExpr_t		*arg_list;
}tguFuncCallExpr_t;

typedef struct __tengu_assignment_expression_tag
{
		tguExpr_t		*addr;
		tguExpr_t		*value;
}tguAssignExpr_t;






/*******************************************************************************************/
typedef struct __tengu_table_field_tag
{
		tguExpr_t		*name;
		tguExpr_t		*value;
		struct __tengu_table_field_tag	*next;
}tguTableField_t;


tguTableField_t*		TGU_CreateTableField(tguExpr_t		*name, tguExpr_t		*value);
void					TGU_DestroyTableField(tguTableField_t *field);




typedef enum
{
		TGU_AGGREGATE_TABLE_T,
		TGU_AGGREGATE_LIST_T
}tguAggregateType_t;

typedef struct __tengu_aggregate_constructor_expression_tag
{
		tguAggregateType_t		type;
		
		union{
				tguTableField_t	*tbl_field_list;
				tguExpr_t		*list;
		};
}tguAggreExpr_t;








typedef enum 
{
		TGU_ET_AGGRE_INIT,
		TGU_ET_ASSIGN,
		TGU_ET_INDEX,
		TGU_ET_FUNC_CALL,
		TGU_ET_BINARY,
		TGU_ET_UNARY,
		TGU_ET_CONDITIONAL,
		TGU_ET_SYMBOL,
		TGU_ET_UNDEF_NAME
}tguExprType_t;


struct __tengu_expression_tag 
{
		tguExprType_t			expr_type;
		bool_t					is_lvalue;
		bool_t					is_constant;
		
		tguLexInfo_t			lex_info;
		tguExpr_t				*next;
		union{
				tguAggreExpr_t			aggre_init;		/*TGU_ET_TABLE_INIT*/
				tguAssignExpr_t			assign_expr;	/*TGU_ET_ASSIGN*/
				tguIndexExpr_t			index_expr;		/*TGU_ET_INDEX*/
				tguCondExpr_t			cond_expr;		/*TGU_ET_CONDITIONAL*/
				tguUnaryExpr_t			unary_expr;		/*TGU_ET_UNARY*/
				tguBinaryExpr_t			binary_expr;	/*TGU_ET_BINARY*/
				tguFuncCallExpr_t		func_call_expr;	/*TGU_ET_FUNC_CALL*/
				
				tguSymb_t				*symb;			/*TGU_ET_SYMBOL*/
				const	wchar_t			*name;			/*TGU_ET_UNDEF_NAME*/
				
		};
};

tguExpr_t*		TGU_CreateExpr(tguExprType_t type);
void			TGU_DestroyExpr(tguExpr_t *expr);


/*********************************************语句**************************************************************/

typedef enum 
{
		TGU_STT_EMPTY,
		TGU_STT_CONTINUE,
		TGU_STT_BREAK,
		
		TGU_STT_EXPR,
		TGU_STT_COMPOUND,
		TGU_STT_IF,
		TGU_STT_WHILE,
		TGU_STT_DO,
		TGU_STT_FOR,
		TGU_STT_RETURN,

		TGU_STT_DECL,
		TGU_STT_IMPORT,
}tguStmtType_t;



typedef struct __tengu_compound_statement_tag
{
		tguBlock_t		*block;
}tguCompoundStmt_t;


typedef struct __tengu_if_statement_tag		
{
		tguExpr_t		*expr;
		tguStmt_t		*true_part;
		tguStmt_t		*false_part;
}tguIFStmt_t;

typedef struct __tengu_while_statement_tag	
{
		tguExpr_t		*expr;
		tguStmt_t		*loop_part;
}tguWhileStmt_t;


typedef struct __tengu_for_statement_tag
{
		tguExpr_t		*init_expr;
		tguExpr_t		*cond_expr;
		tguExpr_t		*step_expr;
		tguStmt_t		*loop_part;
}tguForStmt_t;


typedef struct __tengu_return_statement_tag
{
		tguExpr_t		*expr;
}tguRetrunStmt_t;


typedef struct __tengu_declaration_statement_tag
{
		tguSymb_t		*id;
		tguExpr_t		*init_expr;
}tguDeclStmt_t;

typedef struct __tengu_import_statement_tag
{
		const wchar_t	*module_name;
}tguImportStmt_t;


struct __tengu_statement_tag
{
		tguStmtType_t			stmt_type;				/*TGU_STT_EMPTY, TGU_STT_CONTINUE,	TGU_STT_BREAK 这三种类型的语句无附加参数*/
		tguLexInfo_t			lex_info;
		
		union{
				tguExpr_t				*expr;			/*TGU_STT_EXPR*/
				tguCompoundStmt_t		compound_stmt;	/*TGU_STT_COMPOUND*/
				tguIFStmt_t				if_stmt;		/*TGU_STT_IF*/
				tguWhileStmt_t			while_stmt;		/*TGU_STT_WHILE, TGU_STT_DO*/
				tguForStmt_t			for_stmt;		/*TGU_STT_FOR*/
				tguRetrunStmt_t			return_stmt;	/*TGU_STT_RETURN*/
				tguDeclStmt_t			decl_stmt;		/*TGU_STT_DECL*/
				tguImportStmt_t			import_stmt;	/*TGU_STT_IMPORT*/
		};
};



tguStmt_t*	TGU_CreateStmt(tguStmtType_t			stmt_type);
void		TGU_DestroyStmt(tguStmt_t *stmt);






/*********************************************函数**************************************************************/

typedef struct __tengu_params_tag
{		
		const wchar_t		**names;
		tguLexInfo_t		*lex_info;
		size_t					count;
		size_t					cap;
		bool_t					is_variadic;
}tguParams_t;

tguParams_t*	TGU_CreateParams();
void			TGU_DestroyParams(tguParams_t *params);
void			TGU_InsertToParams(tguParams_t *params, const tguToken_t	*tok);
void			TGU_ClearParams(tguParams_t *params);




typedef struct __tengu_function_tag
{
		const wchar_t	*name;
		size_t			param_cnt;
		bool_t			is_variadic_param;
		tguBlock_t		*block;
}tguFunc_t;


tguFunc_t*		TGU_CreateFunction(const wchar_t *name, const tguBlock_t *parent_block);
void			TGU_DestroyFunction(tguFunc_t *func);














/************************************************符号管理************************************************************************/


typedef enum 
{
		TGU_SYMB_NULL_T,
		TGU_SYMB_INT_T,
		TGU_SYMB_FLOAT_T,
		TGU_SYMB_BOOL_T,
		TGU_SYMB_STRING_T,

		TGU_SYMB_VAR_T,
		TGU_SYMB_FUNC_T,
		TGU_SYMB_CFUNC_T,
		TGU_SYMB_BLOCK_T
}tguSymbType_t;


typedef union
{
		int_64_t		int_num;
		double			float_num;
		bool_t			boolean;
		const wchar_t	*string;
}tguConstant_t;



struct __tengu_symb_tag
{
		tguSymbType_t	type;
		const wchar_t	*name;
		tguLexInfo_t	lex_info;
		
		tguSymb_t		*next;

		union{
				tguConstant_t			constant;
				tguFunc_t				*function;
				tguBlock_t				*block;
				tguCFunction_t			c_func;
		};
};


tguSymb_t*		TGU_CreateSymb(tguSymbType_t t, const wchar_t *name);
void			TGU_DestroySymb(tguSymb_t *symb);







#define	TENGU_SYMB_BUCKET_SIZE	128

typedef struct __tengu_symbol_table_tag
{
		tguSymb_t		*tbl[TENGU_SYMB_BUCKET_SIZE];
		size_t			item_cnt;
}tguSymbTbl_t;


tguSymbTbl_t*	TGU_CreateSymbTable();
void			TGU_DestroySymbTable(tguSymbTbl_t *tbl);



bool_t			TGU_InsertToSymbTable(tguSymbTbl_t *tbl, tguSymb_t *symb);
bool_t			TGU_RemoveFromSymbTable(tguSymbTbl_t *tbl, const wchar_t *name, tguSymbType_t expected_type);


tguSymb_t*		TGU_FindSymb(tguSymbTbl_t *tbl, const wchar_t *name, tguSymbType_t expected_type);


tguSymb_t*		TGU_InstallInt(tguSymbTbl_t *tbl, int_64_t num);
tguSymb_t*		TGU_InstallNull(tguSymbTbl_t *tbl);
tguSymb_t*		TGU_InstallBoolean(tguSymbTbl_t *tbl, bool_t boolean);
tguSymb_t*		TGU_InstallFloat(tguSymbTbl_t *tbl, double float_num);
tguSymb_t*		TGU_InstallString(tguSymbTbl_t *tbl, const wchar_t *str);

tguSymb_t*		TGU_InstallFunction(tguSymbTbl_t *tbl,	const wchar_t *name,		tguFunc_t			*func);
tguSymb_t*		TGU_InstallCFunction(tguSymbTbl_t *tbl, const wchar_t *name,		tguCFunction_t		c_func);
tguSymb_t*		TGU_InstallBlock(tguSymbTbl_t	*tbl,	const wchar_t *name,		tguBlock_t			*block);



/*
typedef struct __tengu_symbol_table_iterator_tag
{
		tguSymbTbl_t	*tbl;
		size_t			idx;
		tguSymb_t		*curr;
}tguSymbTblIter_t;

void	TGU_InitSymbTableIterator(tguSymbTblIter_t *iter, tguSymbTbl_t *tbl);
void	TGU_UnInitSymbTableIterator(tguSymbTblIter_t *iter);
*/



/******************************块*******************************************************/

/*
		A:
		{
				B:
				{

				};

				C:
				{

				};
				则Block A ->sub_blocks ==		
				
				B->next == B;
				C->next == NULL;

				B->parent == C->parent = A;



		}
*/



struct __tengu_block_tag
{
		tguLexInfo_t	begin;
		tguLexInfo_t	end;

		tguSymbTbl_t	*symb_table;

		tguSymb_t		**decls;
		size_t			decl_cnt;
		size_t			decl_cap;

		tguStmt_t		**stmts;
		size_t			stmt_cnt;
		size_t			stmt_cap;
		
		tguBlock_t		*next;/*同一级的下一个块*/
		tguBlock_t		*parent;
		
		tguBlock_t		*sub_blocks; 
};



tguBlock_t*		TGU_CreateBlock(const tguBlock_t	*parent);
/*
TGU_DestroyBlock会将block从block->parent中的sub_blocks中剔除，之后销毁此block及其所有变量声明
*/

void			TGU_DestroyBlock(tguBlock_t	*block);


void			TGU_InsertSubBlockToBlock(tguBlock_t	*block, tguBlock_t	*sub);
bool_t			TGU_RemoveSubBlockFromBlock(tguBlock_t	*block, tguBlock_t	*sub);


void			TGU_InsertStmtToBlock(tguBlock_t	*block, tguStmt_t	*stmt);
void			TGU_InsertSymbToBlock(tguBlock_t	*block, tguSymb_t	*symb);


tguSymb_t*		TGU_FindSymbFromBlock(tguBlock_t	*block, const wchar_t *name, tguSymbType_t t, bool_t current_block);
#define			TGU_GetBlockSymbolTable(_b)		((_b)->symb_table)








AR_NAMESPACE_END

#endif
