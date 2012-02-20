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


#include "tgusyntree.h"
#include "tguutility.h"

AR_NAMESPACE_BEGIN





const wchar_t* TGU_TokenValToString(size_t tok_val)
{
		switch(tok_val)
		{
		default:
				AR_ASSERT(false);
				return L"";
		case TOK_DELIM_ID:
				return L" ";
		case TOK_NAME:
				return L"Identifier";
		case TOK_STRING:
				return L"String";
		case TOK_FLOAT_NUMBER:
				return L"Float Number";
		case TOK_INT_NUMBER:
				return L"Int Number";
		case TOK_FOR:
				return L"for";
		case TOK_DO:
				return L"do";
		case TOK_WHILE:
				return L"while";
		case TOK_IF:
				return L"if";
		case TOK_ELSE:
				return L"else";
		case TOK_CONTINUE:
				return L"continue";
		case TOK_BREAK:
				return L"break";
		case TOK_RETURN:
				return L"return";
		case TOK_NULL:
				return L"null";
		case TOK_TRUE:
				return L"true";
		case TOK_FALSE:
				return L"false";
		case TOK_VAR:
				return L"var";
		case TOK_IMPORT:
				return L"import";
		case TOK_ELLIPSIS:
				return L"...";
		case TOK_INC:
				return L"++";
		case TOK_DEC:
				return L"--";
		case TOK_ANDAND:
				return L"++";
		case TOK_OROR:
				return L"||";
		case TOK_LE:
				return L"<=";
		case TOK_GE:
				return L">=";
		case TOK_EQ:
				return L"==";
		case TOK_NE:
				return L"!=";
		case TOK_LESS:
				return L"<";
		case TOK_GREATER:
				return L">";
		case TOK_L_BRACES:
				return L"{";
		case TOK_R_BRACES:
				return L"}";
		case TOK_L_PAREN:
				return L"(";
		case TOK_R_PAREN:
				return L")";
		case TOK_L_SQUARE:
				return L"[";
		case TOK_R_SQUARE:
				return L"]";
		case TOK_SEMICOLON:
				return L";";
		case TOK_COMMA:
				return L",";
		case TOK_ASSIGN:
				return L"=";
		case TOK_ADD:
				return L"+";
		case TOK_SUB:
				return L"-";
		case TOK_MUL:
				return L"*";
		case TOK_DIV:
				return L"/";
		case TOK_MOD:
				return L"%";
		case TOK_NOT:
				return L"!";
		case TOK_COLON:
				return L":";
		case TOK_QUEST:
				return L"?";
		case TOK_DOT:
				return L".";
		}
}




/****************************************Expr***************************************************************/

tguTableField_t*		TGU_CreateTableField(tguExpr_t		*name, tguExpr_t		*value)
{
		tguTableField_t	*field;
		field = AR_NEW(tguTableField_t);
		field->name = name;
		field->value = value;
		field->next = NULL;
		return field;
}

void					TGU_DestroyTableField(tguTableField_t *field)
{
		tguTableField_t *next;

		while(field)
		{
				next = field->next;

				if(field->name)
				{
						TGU_DestroyExpr(field->name);
						field->name = NULL;
				}

				if(field->value)
				{
						TGU_DestroyExpr(field->value);
						field->value = NULL;
				}
				AR_DEL(field);
				field = next;
		}
}


tguExpr_t*		TGU_CreateExpr(tguExprType_t type)
{
		tguExpr_t		*expr;
		
		expr = AR_NEW0(tguExpr_t);

		expr->expr_type = type;
		return expr;
}


void			TGU_DestroyExpr(tguExpr_t *expr)
{

		AR_ASSERT(expr != NULL);
		while(expr)
		{
				tguExpr_t		*tmp = expr->next;

				switch(expr->expr_type)
				{
				default:
						AR_ASSERT(false);
						break;
				case TGU_ET_AGGRE_INIT:
						{
								if(expr->aggre_init.type == TGU_AGGREGATE_LIST_T)
								{
										tguExpr_t	*lst = expr->aggre_init.list;
										expr->aggre_init.list = NULL;
										TGU_DestroyExpr(lst);
								}else
								{
										tguTableField_t *fields = expr->aggre_init.tbl_field_list;
										expr->aggre_init.tbl_field_list = NULL;
										TGU_DestroyTableField(fields);
								}
						}
						break;
				case TGU_ET_ASSIGN:
						{
								TGU_DestroyExpr(expr->assign_expr.addr);
								TGU_DestroyExpr(expr->assign_expr.value);
								expr->assign_expr.addr = NULL;
								expr->assign_expr.value = NULL;
						}
						break;
				case TGU_ET_INDEX:
						if(expr->index_expr.expr)
						{
								TGU_DestroyExpr(expr->index_expr.expr);
								expr->index_expr.expr = NULL;
						}

						if(expr->index_expr.index_expr)
						{
								TGU_DestroyExpr(expr->index_expr.index_expr);
								expr->index_expr.index_expr = NULL;
						}

						break;
				case TGU_ET_FUNC_CALL:
						if(expr->func_call_expr.arg_list)
						{
								tguExpr_t *arg = expr->func_call_expr.arg_list;

								while(arg)
								{
										tguExpr_t *tmp = arg->next;
										TGU_DestroyExpr(arg);
										arg = tmp;
								}
						}

						if(expr->func_call_expr.func_call)
						{
								TGU_DestroyExpr(expr->func_call_expr.func_call);
								expr->func_call_expr.func_call = NULL;
						}
						break;
				case TGU_ET_BINARY:
						if(expr->binary_expr.left != NULL)
						{
								TGU_DestroyExpr(expr->binary_expr.left);
								expr->binary_expr.left = NULL;
						}

						if(expr->binary_expr.right != NULL)
						{
								TGU_DestroyExpr(expr->binary_expr.right);
								expr->binary_expr.right = NULL;
						}
						break;
				case TGU_ET_UNARY:
						if(expr->unary_expr.expr)
						{
								TGU_DestroyExpr(expr->unary_expr.expr);
								expr->unary_expr.expr = NULL;
						}
						break;
				case TGU_ET_CONDITIONAL:
						if(expr->cond_expr.cond)
						{
								TGU_DestroyExpr(expr->cond_expr.cond);
								expr->cond_expr.cond = NULL;
						}

						if(expr->cond_expr.if_true)
						{
								TGU_DestroyExpr(expr->cond_expr.if_true);
								expr->cond_expr.if_true = NULL;
						}

						if(expr->cond_expr.if_false)
						{
								TGU_DestroyExpr(expr->cond_expr.if_false);
								expr->cond_expr.if_false = NULL;
						}

						break;
				case TGU_ET_SYMBOL:
						if(expr->symb)
						{
								/*TGU_DestroySymb(expr->symb);*/
								expr->symb = NULL;
						}
						break;
				case TGU_ET_UNDEF_NAME:
						expr->name = NULL;
						break;
				}

				AR_DEL(expr);
				
				expr = tmp;
		}
}





/********************************************Stmt********************************************************/

tguStmt_t*	TGU_CreateStmt(tguStmtType_t			stmt_type)
{
		tguStmt_t		*stmt;
		
		stmt = AR_NEW0(tguStmt_t);

		stmt->stmt_type = stmt_type;
		return stmt;
}


void		TGU_DestroyStmt(tguStmt_t *stmt)
{
		AR_ASSERT(stmt != NULL);

		switch(stmt->stmt_type)
		{
		default:
				AR_ASSERT(false);
				break;
		case TGU_STT_EMPTY:
		case TGU_STT_CONTINUE:
		case TGU_STT_BREAK:
				break;
		case TGU_STT_EXPR:
				if(stmt->expr)
				{
						TGU_DestroyExpr(stmt->expr);
						stmt->expr = NULL;
				}
				break;
		case TGU_STT_COMPOUND:
				if(stmt->compound_stmt.block)
				{
						TGU_DestroyBlock(stmt->compound_stmt.block);
						stmt->compound_stmt.block = NULL;
				}
				break;
		case TGU_STT_IF:
				if(stmt->if_stmt.expr)
				{
						TGU_DestroyExpr(stmt->if_stmt.expr);
						stmt->if_stmt.expr = NULL;
				}

				if(stmt->if_stmt.true_part)
				{
						TGU_DestroyStmt(stmt->if_stmt.true_part);
						stmt->if_stmt.true_part = NULL;
				}

				if(stmt->if_stmt.false_part)
				{
						TGU_DestroyStmt(stmt->if_stmt.false_part);
						stmt->if_stmt.false_part = NULL;
				}

				break;
		case TGU_STT_WHILE:
		case TGU_STT_DO:
				if(stmt->while_stmt.expr)
				{
						TGU_DestroyExpr(stmt->while_stmt.expr);
						stmt->while_stmt.expr = NULL;
				}

				if(stmt->while_stmt.loop_part)
				{
						TGU_DestroyStmt(stmt->while_stmt.loop_part);
						stmt->while_stmt.loop_part = NULL;
				}
				break;
		case TGU_STT_FOR:
				if(stmt->for_stmt.init_expr)
				{
						TGU_DestroyExpr(stmt->for_stmt.init_expr);
						stmt->for_stmt.init_expr = NULL;
				}

				if(stmt->for_stmt.cond_expr)
				{
						TGU_DestroyExpr(stmt->for_stmt.cond_expr);
						stmt->for_stmt.cond_expr = NULL;
				}

				if(stmt->for_stmt.step_expr)
				{
						TGU_DestroyExpr(stmt->for_stmt.step_expr);
						stmt->for_stmt.step_expr = NULL;
				}

				if(stmt->for_stmt.loop_part)
				{
						TGU_DestroyStmt(stmt->for_stmt.loop_part);
						stmt->for_stmt.loop_part = NULL;
				}

				break;
		case TGU_STT_RETURN:
				if(stmt->return_stmt.expr)
				{
						TGU_DestroyExpr(stmt->return_stmt.expr);
						stmt->return_stmt.expr = NULL;
				}
				break;
		case TGU_STT_DECL:
				if(stmt->decl_stmt.id)
				{
						stmt->decl_stmt.id = NULL;
				}

				if(stmt->decl_stmt.init_expr)
				{
						TGU_DestroyExpr(stmt->decl_stmt.init_expr);
						stmt->decl_stmt.init_expr = NULL;
				}
		case TGU_STT_IMPORT:
				break;
		}

		AR_DEL(stmt);
}



/*********************************************Function**************************************************************/


tguParams_t*	TGU_CreateParams()
{	
		tguParams_t *ret;
		ret = AR_NEW0(tguParams_t);

		ret->is_variadic = false;
		return ret;
}


void	TGU_ClearParams(tguParams_t *params)
{
		size_t i;
		AR_ASSERT(params != NULL);
		for(i = 0; i < params->count; ++i)
		{
			params->names[i] = NULL;
		}
		params->count = 0;
		params->is_variadic = false;
}


void	TGU_DestroyParams(tguParams_t *params)
{
		AR_ASSERT(params != NULL);
		TGU_ClearParams(params);
		if(params->names)AR_DEL(params->names);
		params->names = NULL;
		if(params->lex_info)AR_DEL(params->lex_info);
		params->lex_info = NULL;
		AR_DEL(params);
}

void	 TGU_InsertToParams(tguParams_t *params, const tguToken_t	*tok)
{
		AR_ASSERT(params != NULL && tok != NULL && tok->token != NULL);

		if(params->count == params->cap)
		{
			params->cap += 2;
			params->names 	= AR_REALLOC(const wchar_t*, (void*)params->names, params->cap);
			params->lex_info	= AR_REALLOC(tguLexInfo_t, (void*)params->lex_info, params->cap);
		}
		params->names[params->count] = TGU_AllocString(tok->token);
		params->lex_info[params->count] = tok->lex_info;
		params->count++;
}




tguFunc_t*		TGU_CreateFunction(const wchar_t *name, const tguBlock_t *parent_block)
{
		tguFunc_t *func;
		AR_ASSERT(name != NULL && parent_block != NULL);
		func = AR_NEW0(tguFunc_t);
		func->name = TGU_AllocString(name);
		func->block = TGU_CreateBlock(parent_block);
		return func;
}


void			TGU_DestroyFunction(tguFunc_t *func)
{

		AR_ASSERT(func != NULL);
		
		TGU_DestroyBlock(func->block);
		func->block = NULL;
		AR_DEL(func);
}











/************************************************符号管理************************************************************************/






/*******************************************SymbolTable***********************************************************/
tguSymb_t*		TGU_CreateSymb(tguSymbType_t t, const wchar_t *name)
{
		tguSymb_t *symb;
		AR_ASSERT(name != NULL);

		symb = AR_NEW0(tguSymb_t);
		
		symb->type = t;
		symb->name = TGU_AllocString(name);
		return symb;
}


void			TGU_DestroySymb(tguSymb_t *symb)
{
		AR_ASSERT(symb != NULL);
		
		switch(symb->type)
		{
		default:
				break;
		case TGU_SYMB_NULL_T:
		case TGU_SYMB_INT_T:
		case TGU_SYMB_FLOAT_T:
		case TGU_SYMB_BOOL_T:
		case TGU_SYMB_STRING_T:
				break;
		case TGU_SYMB_VAR_T:
				break;
		case TGU_SYMB_FUNC_T:
		{
				if(symb->function)
				{
						TGU_DestroyFunction(symb->function);
						symb->function = NULL;
				}
		}
				break;
		case TGU_SYMB_CFUNC_T:
				symb->c_func = NULL;
				break;
		case TGU_SYMB_BLOCK_T:
				if(symb->block)
				{
						TGU_DestroyBlock(symb->block);
						symb->block = NULL;
				}
				break;
		}
		AR_DEL(symb);
}


tguSymbTbl_t*	TGU_CreateSymbTable()
{
		tguSymbTbl_t *tbl;
		tbl = AR_NEW0(tguSymbTbl_t);
		
		return tbl;
}

void			TGU_DestroySymbTable(tguSymbTbl_t *tbl)
{
		size_t i;
		AR_ASSERT(tbl != NULL);

		for(i = 0; i < TENGU_SYMB_BUCKET_SIZE; ++i)
		{
				tguSymb_t		*symb = tbl->tbl[i];

				while(symb)
				{
						tguSymb_t *next = symb->next;
						TGU_DestroySymb(symb);
						symb = next;
				}
		}

		AR_DEL(tbl);
}


#define __hash_name(_name)		(((size_t)(_name)) % TENGU_SYMB_BUCKET_SIZE)

tguSymb_t*		TGU_FindSymb(tguSymbTbl_t *tbl, const wchar_t *name, tguSymbType_t expected_type)
{
		size_t index;
		tguSymb_t *symb;
		AR_ASSERT(tbl != NULL && name != NULL);
		
		/*
		因为所有符号都需要统一分配，因此，此名称一定被TGU_AllocString一族的函数分配
		*/
		
		AR_ASSERT(TGU_HasString(name));

		index = __hash_name(name);
		
		symb = tbl->tbl[index];

		while(symb)
		{
				if(symb->name == name && (symb->type == expected_type))
				{
						return symb;
				}else
				{
						symb = symb->next;
				}
		}

		return symb;
}


bool_t		TGU_InsertToSymbTable(tguSymbTbl_t *tbl, tguSymb_t *symb)
{
		size_t			index;
		AR_ASSERT(tbl != NULL && symb != NULL);
		
		index = __hash_name(symb->name);
		
		symb->next = tbl->tbl[index];
		tbl->tbl[index] = symb;
		tbl->item_cnt += 1;

		return true;
}


bool_t			TGU_RemoveFromSymbTable(tguSymbTbl_t *tbl, const wchar_t *name, tguSymbType_t expected_type)
{
		size_t index;
		tguSymb_t *symb, *prev;
		AR_ASSERT(tbl != NULL && name != NULL);
		index = __hash_name(name);

		symb = tbl->tbl[index];
		
		prev = NULL;
		while(symb)
		{
				if(AR_wcscmp(symb->name, name) == 0 && symb->type == expected_type)
				{
						break;
				}else
				{
						prev = symb;
						symb = symb->next;
				}
		}

		if(symb == NULL)
		{
				return false;
		}

		if(prev == NULL)
		{
				tbl->tbl[index] = symb->next;
				symb->next = NULL;
		}else
		{
				prev->next = symb->next;
				symb->next = NULL;
		}
		TGU_DestroySymb(symb);
		tbl->item_cnt--;
		return true;
}



tguSymb_t*		TGU_InstallInt(tguSymbTbl_t *tbl, int_64_t num)
{
		tguSymb_t		*symb;
		const wchar_t	*name;
		tguConstant_t const_val;
		AR_ASSERT(tbl != NULL);
		const_val.int_num = num;
		
		name = TGU_AllocStringInt(num, 10);
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_INT_T);
		
		if(symb == NULL)
		{
				symb = TGU_CreateSymb(TGU_SYMB_INT_T, name);
				symb->constant.int_num = num;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}


tguSymb_t*		TGU_InstallNull(tguSymbTbl_t *tbl)
{
		tguSymb_t		*symb;
		const wchar_t	*name;
		AR_ASSERT(tbl != NULL);
		
		name = TGU_AllocString(L"null");
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_NULL_T);
		
		if(symb == NULL)
		{
				symb = TGU_CreateSymb(TGU_SYMB_NULL_T, name);
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}



tguSymb_t*		TGU_InstallBoolean(tguSymbTbl_t *tbl, bool_t boolean)
{
		tguSymb_t		*symb;
		const wchar_t	*name;

		AR_ASSERT(tbl != NULL);
		
		name = TGU_AllocString(boolean ? L"true" : L"false");
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_BOOL_T);
		
		if(symb == NULL)
		{
				symb = TGU_CreateSymb(TGU_SYMB_BOOL_T, name);
				symb->constant.boolean = boolean;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}


tguSymb_t*		TGU_InstallFloat(tguSymbTbl_t *tbl, double float_num)
{
		tguSymb_t		*symb;
		const wchar_t	*name;
		
		AR_ASSERT(tbl != NULL);
		name = TGU_AllocStringFloat(float_num);
		
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_FLOAT_T);
		
		if(symb == NULL)
		{
				symb = TGU_CreateSymb(TGU_SYMB_FLOAT_T, name);
				symb->constant.float_num = float_num;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}


tguSymb_t*		TGU_InstallString(tguSymbTbl_t *tbl, const wchar_t *str)
{
		tguSymb_t		*symb;
		const wchar_t	*name;
		
		AR_ASSERT(tbl != NULL && str != NULL);
		name = TGU_AllocString(str);
		
		
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_STRING_T);
		
		if(symb == NULL)
		{
				symb = TGU_CreateSymb(TGU_SYMB_STRING_T, name);
				symb->constant.string = name;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}



tguSymb_t*		TGU_InstallFunction(tguSymbTbl_t *tbl,	const wchar_t *name,		tguFunc_t			*func)
{
		tguSymb_t		*symb;
		
		AR_ASSERT(tbl != NULL && name != NULL);
		AR_ASSERT(func == NULL || AR_wcscmp(name, func->name) == 0);
		
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_FUNC_T);

		if(!symb)
		{
				symb = TGU_CreateSymb(TGU_SYMB_FUNC_T, name);
				symb->function = func;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}


tguSymb_t*		TGU_InstallCFunction(tguSymbTbl_t *tbl, const wchar_t *name,		tguCFunction_t		c_func)
{
		tguSymb_t		*symb;
		
		AR_ASSERT(tbl != NULL && name != NULL);
		
		symb = TGU_FindSymb(tbl, TGU_AllocString(name), TGU_SYMB_CFUNC_T);

		if(!symb)
		{
				symb = TGU_CreateSymb(TGU_SYMB_CFUNC_T, name);
				symb->c_func = c_func;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}


tguSymb_t*		TGU_InstallBlock(tguSymbTbl_t	*tbl,	const wchar_t *name,		tguBlock_t			*block)
{
		tguSymb_t		*symb;
		
		AR_ASSERT(tbl != NULL && name != NULL);
		
		symb = TGU_FindSymb(tbl, name, TGU_SYMB_BLOCK_T);

		if(!symb)
		{
				symb = TGU_CreateSymb(TGU_SYMB_BLOCK_T, name);
				symb->block = block;
				TGU_InsertToSymbTable(tbl, symb);
		}
		return symb;
}

/*********************************************Block******************************************************/


void			TGU_InsertSubBlockToBlock(tguBlock_t	*block, tguBlock_t	*sub)
{
		tguBlock_t		*tmp;
		AR_ASSERT(block != NULL && sub != NULL);
		AR_ASSERT(block != sub);

		/*
		如果sub->next不为空，则证明此block已被插入到其它Block中
		*/
		AR_ASSERT(sub->next == NULL && sub->parent == NULL);

		if(block->sub_blocks == NULL)
		{
				block->sub_blocks = sub;
				sub->next = NULL;
		}else
		{
				for(tmp = block->sub_blocks; tmp->next != NULL; tmp = tmp->next);
				tmp->next = sub;
				sub->next = NULL;
		}
		sub->parent = block;
}

bool_t			TGU_RemoveSubBlockFromBlock(tguBlock_t	*block, tguBlock_t	*sub)
{
		tguBlock_t		*tmp, *prev;
		AR_ASSERT(block != NULL && sub != NULL);
		AR_ASSERT(block != sub);
		
		for(prev = NULL, tmp = block->sub_blocks; tmp != NULL; tmp = tmp->next)
		{
				if(tmp == sub)
				{
						break;
				}else
				{
						prev = tmp;
				}
		}

		if(tmp != sub)
		{
				return false;
		}
		
		if(prev == NULL)
		{
				AR_ASSERT(sub == block->sub_blocks);
				block->sub_blocks = block->sub_blocks->next;
		}else
		{
				prev->next = sub->next;
		}
		
		sub->next = NULL;
		sub->parent = NULL;
		return true;
}




tguBlock_t*		TGU_CreateBlock(const tguBlock_t	*parent)
{
		tguBlock_t		*block;
		
		block = AR_NEW0(tguBlock_t);

		block->begin.col = 0;
		block->begin.linenum = 0;

		block->end.col = 0;
		block->end.linenum = 0;

		block->symb_table = TGU_CreateSymbTable();
		
		block->decls = NULL;
		block->decl_cnt = 0;
		block->decl_cap = 0;

		block->stmts = NULL;
		block->stmt_cnt = 0;
		block->stmt_cap = 0;
		

		block->next = NULL;
		block->parent = NULL;
		block->sub_blocks = NULL;
		
		if(parent)
		{
				TGU_InsertSubBlockToBlock((tguBlock_t*)parent, block);
		}

		return block;
}


void			TGU_DestroyBlock(tguBlock_t	*block)
{
		size_t i;
		tguBlock_t *parent;
		
		AR_ASSERT(block != NULL);
		
		parent = block->parent;
		block->parent = NULL;

		if(parent)
		{
				bool_t		find;
				find = TGU_RemoveSubBlockFromBlock(parent, block);
				AR_ASSERT(find);
		}

		/*
		while(block->sub_blocks)
		{
				AR_ASSERT(block->sub_blocks->parent == block);
				TGU_DestroyBlock(block->sub_blocks);
		}
		*/

		for(i = 0; i < block->stmt_cnt; ++i)
		{
				TGU_DestroyStmt(block->stmts[i]);
		}
		
		if(block->stmts)AR_DEL(block->stmts);

		if(block->decls)
		{
				AR_DEL(block->decls);
		}


		if(block->symb_table != NULL)
		{
				TGU_DestroySymbTable(block->symb_table);
				block->symb_table = NULL;
		}

		AR_DEL(block);

}



void			TGU_InsertStmtToBlock(tguBlock_t	*block, tguStmt_t	*stmt)
{
		AR_ASSERT(block != NULL && stmt != NULL);
		
		if(block->stmt_cnt == block->stmt_cap)
		{
				block->stmt_cap += 4;
				block->stmt_cap *= 2;
				block->stmts = AR_REALLOC(tguStmt_t*, block->stmts, block->stmt_cap);
		}

		block->stmts[block->stmt_cnt] = stmt;
		block->stmt_cnt++;
}



void			TGU_InsertSymbToBlock(tguBlock_t	*block, tguSymb_t	*symb)
{
		AR_ASSERT(block != NULL && symb != NULL);
		
		TGU_InsertToSymbTable(block->symb_table, symb);

		if(block->decl_cnt == block->decl_cap)
		{
				block->decl_cap += 4;
				block->decl_cap *= 2;
				block->decls = AR_REALLOC(tguSymb_t*, block->decls, block->decl_cap);
		}

		block->decls[block->decl_cnt] = symb;
		block->decl_cnt++;
}


tguSymb_t*		TGU_FindSymbFromBlock(tguBlock_t	*block, const wchar_t *name, tguSymbType_t t, bool_t current_block)
{
		tguSymb_t *symb;
		AR_ASSERT(block != NULL && name != NULL);

		symb = NULL;
		do{
				symb = TGU_FindSymb(block->symb_table, name, t);

				block = block->parent;
		}while(!current_block && block != NULL && symb== NULL);

		return symb;
}



AR_NAMESPACE_END






