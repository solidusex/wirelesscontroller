
 
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
 


/*
syntax_node
*/
 

	typedef enum
	{
		TGU_NODE_TOKEN_T,
		TGU_NODE_STMT_T,
		TGU_NODE_EXPR_T,
		TGU_NODE_SYMB_T,
		TGU_NODE_PARAMS_T,
		TGU_NODE_FUNC_T
	}tguSynNodeType_t;

	typedef struct __tengu_syntax_node_tag
	{
		tguSynNodeType_t		type;
		
		union{
				tguToken_t			token;
				tguStmt_t			*stmt;
				tguExpr_t			*expr;
				tguParams_t			*params;
				tguSymb_t			*symb;
		};
	}tguSynNode_t;


	static tguSynNode_t*	__create_synnode(tguSynNodeType_t type, void *data)
	{
			tguSynNode_t *node;

			node = AR_NEW0(tguSynNode_t);
			node->type = type;

			switch(node->type)
			{
			case TGU_NODE_TOKEN_T:
				node->token = *(tguToken_t*)data;
				break;
			case TGU_NODE_STMT_T:
				node->stmt = (tguStmt_t*)data;
				break;
			case TGU_NODE_EXPR_T:
				node->expr = (tguExpr_t*)data;
				break;
			case TGU_NODE_SYMB_T:
				node->symb = (tguSymb_t*)data;
				break;
			case TGU_NODE_PARAMS_T:
				node->params = (tguParams_t*)data;
				break;
			}

			return node;
	}


	static void	__destroy_synnode(	tguSynNode_t* node)
	{
		AR_ASSERT(node != NULL);
		switch(node->type)
		{
		case TGU_NODE_TOKEN_T:
			break;
		case TGU_NODE_STMT_T:
			if(node->stmt)
			{
				TGU_DestroyStmt(node->stmt);
				node->stmt = NULL;
			}
			break;
		case TGU_NODE_EXPR_T:
			if(node->expr)
			{
				tguExpr_t	*expr = node->expr;
				while(expr)
				{
					tguExpr_t	*tmp = expr->next;
					TGU_DestroyExpr(node->expr);
					expr = tmp;
				}
				node->expr = NULL;
			}
			break;
		case TGU_NODE_SYMB_T:
			if(node->symb)
			{
				TGU_DestroySymb(node->symb);
				node->symb = NULL;
			}
			break;
		case TGU_NODE_PARAMS_T:
			if(node->params)
			{	
				TGU_DestroyParams(node->params);
				node->params = NULL;
			}
			break;
		}

		AR_DEL(node);
	}
 


/*
syntax_tree_handler
*/
 

	static void		AR_STDCALL on_free_node(psrNode_t *node, void *ctx)
	{
		AR_ASSERT(node != NULL && ctx != NULL);
		__destroy_synnode((tguSynNode_t*)node);
		
	}

	static bool_t		AR_STDCALL on_error(const psrToken_t *tok, const size_t expected[], size_t count, void *ctx)
	{
			tguParser_t	*parser;
			size_t		i;
			arString_t	*str;
			wchar_t		*tok_str;
			AR_ASSERT(tok != NULL && ctx != NULL);

			parser = (tguParser_t*)ctx;
			str = AR_CreateString();

			if(tok->term_val == 0)
			{
					tok_str = AR_wcsdup(L"EOI");
			}else
			{
					tok_str = AR_wcsndup(tok->str, tok->str_cnt);
			}
		
			AR_AppendFormatString(str, L"Invalid token : '%ls', expected ", tok_str);
			
			for(i = 0; i < count; ++i)
			{
					AR_AppendFormatString(str, L"'%ls'", TGU_TokenValToString(expected[i]));
			}
			
			TGU_ReportError(&parser->report, AR_GetStringCString(str), tok->line);
		
			AR_DestroyString(str);
			str = NULL;
			AR_DEL(tok_str);
			tok_str = NULL;
			return true;
	}
	
	static const psrHandler_t	__g_handler = {on_error, on_free_node};
 


/*
token_operation
*/
 
	
	static tguSynNode_t*	on_lex_node(tguParser_t *parser, const wchar_t *str, size_t term_val, size_t line, size_t col)
	{
		tguToken_t token;
		AR_ASSERT(parser != NULL && parser->module_name);
		token.token = str;
		token.term_val = term_val;
		token.lex_info.linenum = line;
		token.lex_info.col = col;
		token.lex_info.module_name = parser->module_name;
		return __create_synnode(TGU_NODE_TOKEN_T, (void*)&token);
	}

 


/*
handle_function
*/
 
	
	static void	start_function(tguParser_t *parser, const wchar_t *func_name, const tguParams_t	*params, const tguLexInfo_t *lex_info)
	{
		size_t	i;
		AR_ASSERT(parser != NULL && func_name != NULL && lex_info != NULL);

		AR_ASSERT(parser->top_block == parser->abs_tree && parser->current_function == NULL);
		AR_ASSERT(!parser->is_on_function_compound);
		
		parser->is_on_function_compound = true;
		if(	TGU_FindSymbFromBlock(parser->abs_tree, func_name, TGU_SYMB_FUNC_T, true) != NULL 
		|| 	TGU_FindSymbFromBlock(parser->abs_tree, func_name, TGU_SYMB_CFUNC_T, true) != NULL
		||	TGU_FindSymb((tguSymbTbl_t*)parser->ext->build_in, func_name, TGU_SYMB_FUNC_T) != NULL
		||	TGU_FindSymb((tguSymbTbl_t*)parser->ext->build_in, func_name, TGU_SYMB_CFUNC_T) != NULL
		)
		{
			wchar_t	msg[1024];
			parser->has_error = true;
			parser->on_redef_function = true;
			AR_swprintf(msg, 1024, L"error : function '%ls' : redefinition",  func_name);
			TGU_ReportError(&parser->report, msg, lex_info->linenum);
		}else
		{
			tguSymb_t	*symb = TGU_CreateSymb(TGU_SYMB_FUNC_T, func_name);
			symb->lex_info = *lex_info;
			symb->function = NULL;
			TGU_InsertSymbToBlock(parser->abs_tree, symb);
		}

		parser->current_function = TGU_CreateFunction(func_name, parser->abs_tree);
		parser->top_block = parser->current_function->block;
		parser->current_function->is_variadic_param = params ? params->is_variadic : false;
		
		
		for(i = 0; params != NULL && i < params->count; ++i)
		{
			tguSymb_t	*symb;
			tguBlock_t	*block = parser->current_function->block;
			const wchar_t	*name = params->names[i];
			const tguLexInfo_t	lex_info = params->lex_info[i];
			AR_ASSERT(name != NULL);

			symb = TGU_FindSymbFromBlock(block, name, TGU_SYMB_VAR_T, true);

			if(symb)
			{
				wchar_t	msg[1024];
				parser->has_error = true;
				AR_swprintf(msg, 1024, L"error : '%ls' : redefinition",  name);
				TGU_ReportError(&parser->report, msg, lex_info.linenum);
			}else
			{
				symb = TGU_CreateSymb(TGU_SYMB_VAR_T, name);
				symb->lex_info = lex_info;
				TGU_InsertSymbToBlock(block, symb);
			}
		}
		
		AR_ASSERT(parser->top_block != NULL);
		
	}
	

	static void	close_function(tguParser_t *parser, tguStmt_t	*stmt)
	{
		tguFunc_t	*func;
		bool_t		is_redef_func = false;
		AR_ASSERT(parser != NULL);
		AR_ASSERT(parser->top_block== parser->abs_tree && parser->current_function != NULL);
		AR_ASSERT(stmt->stmt_type == TGU_STT_COMPOUND && stmt->compound_stmt.block == parser->current_function->block);
		func = parser->current_function;
		parser->current_function = NULL;
		parser->is_on_function_compound = false;
		is_redef_func = parser->on_redef_function;
		parser->on_redef_function = false;
		stmt->compound_stmt.block = NULL;
		TGU_DestroyStmt(stmt);
		if(is_redef_func)
		{
			TGU_DestroyFunction(func);
			func = NULL;
		}else
		{
			tguSymb_t	*symb = NULL;
			symb = TGU_FindSymbFromBlock(parser->abs_tree, func->name, TGU_SYMB_FUNC_T, true);
			AR_ASSERT(symb != NULL && symb->function == NULL);
			symb->function = func;
		}
		
			
	}
 


/*
handle_init_declarator
*/
 
	
	static void	handle_symb_from_expression(tguParser_t 	*parser, const tguToken_t *tok, tguExpr_t *expr)
	{
			tguSymb_t	*symb;
			size_t		t;
			AR_ASSERT(parser != NULL && tok != NULL);
			
			for(t = TGU_SYMB_VAR_T, symb = NULL; t <= TGU_SYMB_BLOCK_T && symb == NULL; ++t)
			{
				symb = TGU_FindSymbFromBlock(parser->top_block, tok->token, (tguSymbType_t)t, true);
			}


			
			if(symb)
			{
				wchar_t	msg[1024];
				parser->has_error = true;
				AR_swprintf(msg, 1024, L"error : '%ls' : redefinition",  tok->token);
				TGU_ReportError(&parser->report, msg, tok->lex_info.linenum);
			}else
			{
				tguStmt_t	*decl_stmt;
				symb = TGU_CreateSymb(TGU_SYMB_VAR_T, tok->token);
				symb->lex_info = tok->lex_info;
				TGU_InsertSymbToBlock(parser->top_block, symb);
				
				decl_stmt = TGU_CreateStmt(TGU_STT_DECL);
				decl_stmt->decl_stmt.id = symb;
				decl_stmt->decl_stmt.init_expr = expr;
				
				TGU_InsertStmtToBlock(parser->top_block, decl_stmt);
				
			}
	}
 

 
	tguStmt_t*		make_compound_stmt(tguParser_t 	*parser, tguBlock_t		*block, const tguLexInfo_t *start, const tguLexInfo_t *end)
	{
			tguStmt_t	*ret;
			AR_ASSERT(parser != NULL);
			ret = TGU_CreateStmt(TGU_STT_COMPOUND);
			ret->lex_info = *start;
			

			if(block)
			{
				block->begin = *start;
				block->end = *end;
			}
			ret->compound_stmt.block = block;
			return ret;

	}
 

 
	static tguStmt_t*	make_empty_statement(tguParser_t *parser, const tguLexInfo_t *lex_info)
	{
			tguStmt_t	*ret;
			AR_ASSERT(parser != NULL && lex_info != NULL);
			ret = TGU_CreateStmt(TGU_STT_EMPTY);
			ret->lex_info = *lex_info;
			return ret;

	}



	static tguStmt_t*	make_expression_statement(tguParser_t *parser, tguExpr_t *expr, const tguLexInfo_t *lex_info)
	{
			tguStmt_t	*ret;
			AR_ASSERT(parser != NULL);
			ret = TGU_CreateStmt(TGU_STT_EXPR);

			if(lex_info)
			{
				ret->lex_info = *lex_info;
			}
			ret->expr = expr;
			return ret;

	}


		

 

 

	static tguStmt_t*	make_if_statement(tguParser_t *parser, tguExpr_t *cond, tguStmt_t *if_true, tguStmt_t *if_false, const tguLexInfo_t *lex_info)
	{
			tguStmt_t	*ret;
			AR_ASSERT(parser != NULL && lex_info != NULL);
			ret = TGU_CreateStmt(TGU_STT_IF);
			ret->lex_info = *lex_info;
			ret->if_stmt.expr = cond;
			ret->if_stmt.true_part = if_true;
			ret->if_stmt.false_part = if_false;
			return ret;

	}

 

 
	static tguStmt_t*	make_while_statement(tguParser_t *parser, tguStmtType_t type, tguExpr_t *cond, tguStmt_t *loop, const tguLexInfo_t *lex_info)
	{
			tguStmt_t	*ret;
			AR_ASSERT(parser != NULL && lex_info != NULL);
			ret = TGU_CreateStmt(type);
			ret->lex_info = *lex_info;
			ret->while_stmt.expr = cond;
			ret->while_stmt.loop_part = loop;
			return ret;

	}
 

 
	static tguStmt_t*	make_jump_statement(tguParser_t *parser, tguStmtType_t type, tguExpr_t *expr, const tguLexInfo_t *lex_info)
	{
		tguStmt_t	*ret;
		wchar_t	msg[512];
		AR_ASSERT(parser != NULL && lex_info != NULL);
		
		ret = TGU_CreateStmt(type);
		ret->lex_info = *lex_info;

		if(type == TGU_STT_RETURN)
		{
			ret->return_stmt.expr = expr;
			
		}else
		{

			if(parser->loop_level == 0)
			{
				const wchar_t *err_msg = NULL;
				if(type == TGU_STT_CONTINUE)
				{
					err_msg = L"error : illegal continue";
				}else if(type == TGU_STT_BREAK)
				{
					err_msg =  L"error : illegal break";
				}
			
				if(err_msg)
				{
					parser->has_error = true;
					AR_swprintf(msg, 512, L"%ls", err_msg);
					TGU_ReportError(&parser->report, msg, ret->lex_info.linenum);
				}
			}
		}


		return ret;
	}
 

 

	static tguExpr_t*		make_assignment_expression(tguParser_t	*parser, 	tguExpr_t *addr, tguExpr_t *value, const tguLexInfo_t *lex_info)
	{
			tguExpr_t	*ret;
			wchar_t	msg[512];
			AR_ASSERT(parser != NULL && lex_info != NULL);
			ret = TGU_CreateExpr(TGU_ET_ASSIGN);

			if(addr)
			{
				if(!addr->is_lvalue)
				{
					parser->has_error = true;
					AR_swprintf(msg, 512, L"%ls", L"error  : left operand must be l-value");
					TGU_ReportError(&parser->report, msg, addr->lex_info.linenum);
				}else
				{
					AR_ASSERT(!addr->is_constant);
				}
			}

			ret->is_lvalue = true;
			ret->is_constant = true;
			ret->lex_info = *lex_info;

			ret->assign_expr.addr = addr;
			ret->assign_expr.value = value;

			return ret;
	}

 

 

	static tguExpr_t*		make_condition_expression(tguParser_t	*parser, 	tguExpr_t *cond, tguExpr_t *if_true, tguExpr_t *if_false, const tguLexInfo_t *lex_info)
	{
			tguExpr_t	*ret;
			AR_ASSERT(parser != NULL && lex_info != NULL);
			ret = TGU_CreateExpr(TGU_ET_CONDITIONAL);

			ret->is_lvalue = true;
			ret->is_constant = false;
			if(if_true)
			{
				if(!if_true->is_lvalue)
				{
					ret->is_lvalue = false;
				}

				if(if_true->is_constant)
				{
					ret->is_constant = true;
				}
			}

			if(if_false)
			{
				if(!if_false->is_lvalue)
				{
					ret->is_lvalue = false;
				}
				
				if(if_false->is_constant)
				{
					ret->is_constant = true;
				}
			}

			ret->lex_info = *lex_info;

			ret->cond_expr.cond = cond;
			ret->cond_expr.if_true  = if_true;
			ret->cond_expr.if_false = if_false;
			return ret;

	}

 

 

	static tguExpr_t*		make_binary_expression(tguParser_t	*parser, 	tguExprOP_t op, tguExpr_t *left, tguExpr_t *right, const tguLexInfo_t *lex_info)
	{
			tguExpr_t	*ret;	
			AR_ASSERT(parser != NULL && lex_info != NULL);
			ret = TGU_CreateExpr(TGU_ET_BINARY);
			ret->is_lvalue = false;
			ret->is_constant = false;
			ret->lex_info = *lex_info;
			ret->binary_expr.op = op;
			ret->binary_expr.left  = left;
			ret->binary_expr.right = right;
			return ret;
	}

 

 

	static tguExpr_t*		make_unary_expression(tguParser_t	*parser, 	tguExprOP_t op, tguExpr_t *expr, bool_t is_lvalue, const tguLexInfo_t *lex_info)
	{
			tguExpr_t	*ret;
			wchar_t 	msg[512];
			const 		wchar_t *op_str;
			AR_ASSERT(parser != NULL && lex_info != NULL);
			
			ret = TGU_CreateExpr(TGU_ET_UNARY);
			ret->is_lvalue = is_lvalue;
			ret->lex_info = *lex_info;
			ret->unary_expr.op = op;
			ret->unary_expr.expr = expr;
			ret->is_constant = expr == NULL ? false : expr->is_constant;
			
			switch(op)
			{
			case TGU_OP_PREINC:
			case TGU_OP_POSTINC:
				op_str = L"++";
				break;
			case TGU_OP_PREDEC:
			case TGU_OP_POSTDEC:
				op_str = L"--";
				break;
			default:
				op_str = NULL;
				break;
			}

			if(op_str != NULL && !ret->is_lvalue)
			{
				parser->has_error = true;
				AR_swprintf(msg, 512, L"error : '%ls' needs l-value", op_str);
				TGU_ReportError(&parser->report, msg, lex_info->linenum);

			}
			
			return ret;
	}



	static tguExpr_t*	make_index_expression(tguParser_t *parser, tguExpr_t *expr, tguExpr_t *index_expr, const tguLexInfo_t *lex_info)
	{
		tguExpr_t	*ret;
		wchar_t msg[512];

		AR_ASSERT(parser != NULL && lex_info != NULL);

		if(expr != NULL)
		{
			if(expr->is_constant)
			{
				parser->has_error = true;
				AR_swprintf(msg, 512, L"%ls", L"error : invalid table action");
				TGU_ReportError(&parser->report, msg, lex_info->linenum);
			}
		}
		
		ret = TGU_CreateExpr(TGU_ET_INDEX);
		ret->index_expr.expr = expr;
		ret->index_expr.index_expr = index_expr;
		ret->is_lvalue = expr == NULL ? true : expr->is_lvalue;
		ret->is_constant = false;
		ret->lex_info = *lex_info;

		return ret;
	}

	
 


/*
handle_constant
*/
 
	static tguExpr_t*		make_constant_expression(tguParser_t	*parser, tguToken_t *token)
	{
			tguSymb_t		*symb;
			tguSymbTbl_t		*symb_tbl;
			tguExpr_t		*expr;
			AR_ASSERT(parser != NULL && token != NULL); 
			
			expr = NULL;
			symb = NULL;
			symb_tbl = parser->ext->global_constant;
			AR_ASSERT(symb_tbl != NULL);

			switch(token->term_val)
			{
			default:
				AR_ASSERT(false);
				break;
			case TOK_NULL:
				symb = TGU_InstallNull(symb_tbl);
				break;
			case TOK_TRUE:
				symb = TGU_InstallBoolean(symb_tbl, true);
				break;
			case TOK_FALSE:
				symb = TGU_InstallBoolean(symb_tbl, false);
				break;
			case TOK_FLOAT_NUMBER:
			{
				double df;
				AR_wtod(token->token, &df);
				symb = TGU_InstallFloat(symb_tbl, df); 
			}
				break;
			case TOK_INT_NUMBER:
			{
				int_64_t	num;
				AR_wtoi64(token->token, &num, 0);/*0表示AR_wtoi64自动识别*/
				symb = TGU_InstallInt(symb_tbl, num); 
			}
				break;
			case TOK_STRING:
				symb = TGU_InstallString(symb_tbl, token->token);
				break;
			}
			
			expr = TGU_CreateExpr(TGU_ET_SYMBOL);
			expr->is_lvalue = false;
			expr->is_constant = true;
			expr->lex_info = token->lex_info;
			expr->symb = symb;
			return expr;
	}

 


/*
handle_identifier
*/
 
	
	static tguExpr_t*		make_identifier_expression(tguParser_t	*parser, tguToken_t *token)
	{
			tguExpr_t	*expr;
			tguSymb_t	*symb;
			size_t		t;
			AR_ASSERT(parser != NULL && token != NULL);
			AR_ASSERT(parser->top_block != NULL);
			
			
			for(t = TGU_SYMB_VAR_T, symb = NULL; t <= TGU_SYMB_BLOCK_T && symb == NULL; ++t)
			{
				symb = TGU_FindSymbFromBlock(parser->top_block, token->token, (tguSymbType_t)t, false);
			}


			if(symb == NULL)
			{
				for(t = TGU_SYMB_VAR_T, symb = NULL; t <= TGU_SYMB_BLOCK_T && symb == NULL; ++t)
				{
						symb = TGU_FindSymb((tguSymbTbl_t*)parser->ext->build_in, token->token, (tguSymbType_t)t);
				}
			}
				
			if(symb == NULL)
			{
				wchar_t msg[512];
				expr = TGU_CreateExpr(TGU_ET_UNDEF_NAME);
				expr->name = token->token;
				parser->has_error = true;
				AR_swprintf(msg, 512, L"error : '%ls' : undeclared identifier", token->token);
				TGU_ReportError(&parser->report, msg, token->lex_info.linenum);
				
			}else
			{
				expr = TGU_CreateExpr(TGU_ET_SYMBOL);
				expr->symb = symb;
			}
			
			if(symb && symb->type == TGU_SYMB_VAR_T)
			{
				expr->is_lvalue = true;
			}else
			{
					expr->is_lvalue  = false;
			}

			expr->is_constant = false;
			expr->lex_info = token->lex_info;
			return expr;
	}




 

 
	static tguExpr_t*		make_call_expression(tguParser_t	*parser, tguExpr_t *call_expr, tguExpr_t *args, const tguLexInfo_t *lex_info)
	{
			tguExpr_t *expr;
			AR_ASSERT(parser != NULL && lex_info != NULL);

			expr = TGU_CreateExpr(TGU_ET_FUNC_CALL);
			expr->is_lvalue = false;
			expr->is_constant = false;
			expr->lex_info = *lex_info;
			
			expr->func_call_expr.func_call = call_expr;
			expr->func_call_expr.arg_list = args;

			return expr;
	}
 

static const wchar_t *__g_lex_name[] = {
L"delim = [\\x{000A}\\x{000B}\\x{000C}\\x{000D}\\x{0085}\\x{2028}\\x{2029}\\x{0020}\\f\\n\\r\\t\\v]",
L"comment = /\\*([^\\*]|\\*+[^\\*/])*\\*+/",
L"comment_line = (//[^\\x{000A}\\x{000B}\\x{000C}\\x{000D}\\x{0085}\\x{2028}\\x{2029}]*(\\x{000A}|\\x{000B}|\\x{000C}|\\x{000D}|\\x{0085}|\\x{2028}|\\x{2029}|$))",
L"skip_lexem = {delim}|{comment_line}|{comment}",
L"digit = [0-9]",
L"number = {digit}+",
L"letter = [A-Z_a-z\\x{0800}-\\x{4E00}\\x{4E00}-\\x{9FA5}\\x{3130}-\\x{318F}\\x{AC00}-\\x{D7AF}]",
L"hex_digit = [0-9a-fA-F]",
L"hex_literal = 0(x|X){hex_digit}+",
L"oct_literal = 0[0-7]+",
L"dec_literal = (0|[1-9][0-9]*)",
L"exponet = (e|E)(\\+|\\-)?[0-9]+",
L"float_literal = (((([0-9]\\.[0-9]*)){exponet}?)|([0-9]+{exponet}))",
L"escape_seq = (\\\\(\\x22|\\x27))",
L"string_dq = (\\x22({escape_seq}|[^\\x22])*\\x22)",
L"string_sq = \\x27({escape_seq}|[^\\x27])*\\x27",
L"keyword_lhd = [A-Z_a-z0-9]",
L"float_constant = {float_literal}(?!{keyword_lhd})",
L"hex_constant = {hex_literal}(?!{keyword_lhd})",
L"oct_constant = {oct_literal}(?!{keyword_lhd})",
L"dec_constant = {dec_literal}(?!{keyword_lhd})"
};

#define __NAME_COUNT__ ((size_t)21)

static psrNode_t* AR_STDCALL default_leaf_handler(const psrToken_t *tok,void *ctx);


static psrNode_t* AR_STDCALL on_string_leaf_handler(const psrToken_t *tok,void *ctx);







static struct {const wchar_t *name;
size_t tokval;
size_t lex_prec;
const wchar_t *regex;
bool_t skip;
psrTermFunc_t leaf;
}__g_term_pattern[] =  {
{NULL, TOK_DELIM_ID,1, L"{skip_lexem}", true, NULL},
{L"NAME", TOK_NAME, 0, L"{letter}({letter}|{digit})*", false, default_leaf_handler},
{L"STRING", TOK_STRING, 0, L"{string_dq}|{string_sq}", false, on_string_leaf_handler},
{L"FLOAT_NUMBER", TOK_FLOAT_NUMBER, 2, L"{float_constant}", false, default_leaf_handler},
{L"INT_NUMBER", TOK_INT_NUMBER, 2, L"{hex_constant}|{oct_constant}|{dec_constant}", false, default_leaf_handler},
{L"for", TOK_FOR, 1, L"\"for\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"do", TOK_DO, 1, L"\"do\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"while", TOK_WHILE, 1, L"\"while\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"if", TOK_IF, 1, L"\"if\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"else", TOK_ELSE, 1, L"\"else\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"continue", TOK_CONTINUE, 1, L"\"continue\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"break", TOK_BREAK, 1, L"\"break\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"return", TOK_RETURN, 1, L"\"return\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"null", TOK_NULL, 1, L"\"null\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"true", TOK_TRUE, 1, L"\"true\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"false", TOK_FALSE, 1, L"\"false\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"var", TOK_VAR, 1, L"\"var\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"in", TOK_IN, 1, L"\"in\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"import", TOK_IMPORT, 2, L"\"import\"(?!{keyword_lhd})", false, default_leaf_handler},
{L"...", TOK_ELLIPSIS, 2, L"\"...\"", false, default_leaf_handler},
{L"++", TOK_INC, 1, L"\"++\"", false, default_leaf_handler},
{L"--", TOK_DEC, 1, L"\"--\"", false, default_leaf_handler},
{L"&&", TOK_ANDAND, 1, L"\"&&\"", false, default_leaf_handler},
{L"||", TOK_OROR, 1, L"\"||\"", false, default_leaf_handler},
{L"<=", TOK_LE, 1, L"\"<=\"", false, default_leaf_handler},
{L">=", TOK_GE, 1, L"\">=\"", false, default_leaf_handler},
{L"==", TOK_EQ, 1, L"\"==\"", false, default_leaf_handler},
{L"!=", TOK_NE, 1, L"\"!=\"", false, default_leaf_handler},
{L"<", TOK_LESS, 0, L"\"<\"", false, default_leaf_handler},
{L">", TOK_GREATER, 0, L"\">\"", false, default_leaf_handler},
{L"{", TOK_L_BRACES, 0, L"\"{\"", false, default_leaf_handler},
{L"}", TOK_R_BRACES, 0, L"\"}\"", false, default_leaf_handler},
{L"(", TOK_L_PAREN, 0, L"\"(\"", false, default_leaf_handler},
{L")", TOK_R_PAREN, 0, L"\")\"", false, default_leaf_handler},
{L"[", TOK_L_SQUARE, 0, L"\"[\"", false, default_leaf_handler},
{L"]", TOK_R_SQUARE, 0, L"\"]\"", false, default_leaf_handler},
{L";", TOK_SEMICOLON, 0, L"\";\"", false, default_leaf_handler},
{L",", TOK_COMMA, 0, L"\",\"", false, default_leaf_handler},
{L"=", TOK_ASSIGN, 0, L"\"=\"", false, default_leaf_handler},
{L"+", TOK_ADD, 0, L"\"+\"", false, default_leaf_handler},
{L"-", TOK_SUB, 0, L"\"-\"", false, default_leaf_handler},
{L"*", TOK_MUL, 0, L"\"*\"", false, default_leaf_handler},
{L"/", TOK_DIV, 0, L"\"/\"", false, default_leaf_handler},
{L"%", TOK_MOD, 0, L"\"%\"", false, default_leaf_handler},
{L"!", TOK_NOT, 0, L"\"!\"", false, default_leaf_handler},
{L":", TOK_COLON, 0, L"\":\"", false, default_leaf_handler},
{L"?", TOK_QUEST, 0, L"\"?\"", false, default_leaf_handler},
{L".", TOK_DOT, 0, L"\".\"", false, default_leaf_handler},
{L"CFG_LEXVAL_EOI", 0, 2, L"$", false, NULL}
};

#define __TERM_COUNT__ ((size_t)49)

static struct {const wchar_t *name; size_t tokval; size_t prec_level; psrAssocType_t	assoc;}__g_prec_pattern[] =  {
{L"?", TOK_QUEST,1, PARSER_ASSOC_RIGHT},
{L":", TOK_COLON,1, PARSER_ASSOC_RIGHT},
{L"||", TOK_OROR,2, PARSER_ASSOC_LEFT},
{L"&&", TOK_ANDAND,3, PARSER_ASSOC_LEFT},
{L"==", TOK_EQ,4, PARSER_ASSOC_LEFT},
{L"!=", TOK_NE,4, PARSER_ASSOC_LEFT},
{L"<", TOK_LESS,4, PARSER_ASSOC_LEFT},
{L"<=", TOK_LE,4, PARSER_ASSOC_LEFT},
{L">", TOK_GREATER,4, PARSER_ASSOC_LEFT},
{L">=", TOK_GE,4, PARSER_ASSOC_LEFT},
{L"+", TOK_ADD,5, PARSER_ASSOC_LEFT},
{L"-", TOK_SUB,5, PARSER_ASSOC_LEFT},
{L"*", TOK_MUL,6, PARSER_ASSOC_LEFT},
{L"/", TOK_DIV,6, PARSER_ASSOC_LEFT},
{L"%", TOK_MOD,6, PARSER_ASSOC_LEFT},
{L"IF_WITHOUT_ELSE", 305,7, PARSER_ASSOC_NONASSOC},
{L"else", TOK_ELSE,8, PARSER_ASSOC_NONASSOC}
};

#define __PREC_COUNT__ ((size_t)17)

/*program	:	translation_unit */
/*program	:	 */
static psrNode_t* AR_STDCALL on_translation_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*translation_unit	:	element */
/*translation_unit	:	translation_unit element */
/*element	:	declaration */
/*element	:	function_defination */
/*declaration	:	var init_declarator_list semi */
/*declaration	:	var error ; */
/*init_declarator_list	:	init_declarator */
/*init_declarator_list	:	init_declarator_list , init_declarator */
/*compound_element_list	:	compound_element_list compound_element */
/*compound_element_list	:	compound_element */
/*compound_element	:	declaration */
/*expression_statement	:	error ; */
static psrNode_t* AR_STDCALL auto_return_null(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*element	:	statement */
static psrNode_t* AR_STDCALL on_global_stmtement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*function_signature	:	var NAME ( params ) */
static psrNode_t* AR_STDCALL on_function_signature(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*function_defination	:	function_signature compound_statement */
static psrNode_t* AR_STDCALL on_function_defination(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*params	:	namelist , ... */
static psrNode_t* AR_STDCALL on_namelist_ellipsis(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*params	:	namelist */
/*list_field_list	:	field */
/*field	:	expression */
/*field	:	aggregate_constructor */
/*statement	:	compound_statement */
/*statement	:	expression_statement */
/*statement	:	selection_statement */
/*statement	:	iteration_statement */
/*statement	:	jump_statement */
/*statement	:	empty_statement */
/*selection_statement	:	if_statement */
/*selection_statement	:	if_else_statement */
/*iteration_statement	:	while_statement */
/*iteration_statement	:	do_while_statement */
/*iteration_statement	:	for_statement */
/*semi	:	; */
/*expression	:	assignment_expression */
/*assignment_expression	:	constant_expression */
/*constant_expression	:	binary_expression */
/*binary_expression	:	unary_expression */
/*unary_expression	:	postfix_expression */
/*postfix_expression	:	call_expression */
/*postfix_expression	:	primary_expression */
/*primary_expression	:	constant */
/*primary_expression	:	import_expression */
/*primary_expression	:	value_expression */
/*expression_list	:	expression */
static psrNode_t* AR_STDCALL auto_return_0(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*params	:	... */
static psrNode_t* AR_STDCALL on_ellipsis(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*namelist	:	namelist , NAME */
static psrNode_t* AR_STDCALL on_name_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*namelist	:	NAME */
static psrNode_t* AR_STDCALL on_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*init_declarator	:	NAME = expression */
/*init_declarator	:	NAME = aggregate_constructor */
/*init_declarator	:	NAME */
static psrNode_t* AR_STDCALL on_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*aggregate_constructor	:	table_constructor */
/*aggregate_constructor	:	list_constructor */
static psrNode_t* AR_STDCALL handle_aggregate_constructor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*list_constructor	:	[ list_field_list ] */
/*list_constructor	:	[ ] */
/*list_constructor	:	[ error ] */
static psrNode_t* AR_STDCALL handle_list_constructor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*list_field_list	:	list_field_list , field */
static psrNode_t* AR_STDCALL on_list_field_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_constructor	:	{ table_field_list } */
/*table_constructor	:	{ } */
/*table_constructor	:	{ error } */
static psrNode_t* AR_STDCALL on_table_constructor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_field_list	:	table_field_list , table_field */
/*table_field_list	:	table_field */
static psrNode_t* AR_STDCALL handle_table_field_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_field	:	expression : field */
static psrNode_t* AR_STDCALL handle_table_field(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement	:	start_block compound_element_list } */
static psrNode_t* AR_STDCALL on_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement	:	start_block } */
static psrNode_t* AR_STDCALL on_empty_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement	:	start_block error } */
static psrNode_t* AR_STDCALL on_compound_error_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*start_block	:	{ */
static psrNode_t* AR_STDCALL on_start_block(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_element	:	statement */
static psrNode_t* AR_STDCALL on_compound_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty_statement	:	; */
static psrNode_t* AR_STDCALL on_empty_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*expression_statement	:	expression semi */
static psrNode_t* AR_STDCALL on_expression_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*if_statement	:	if ( expression ) statement */
/*if_statement	:	if ( error ) statement */
static psrNode_t* AR_STDCALL on_if_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*if_else_statement	:	if ( expression ) statement else statement */
/*if_else_statement	:	if ( error ) statement else statement */
static psrNode_t* AR_STDCALL on_if_else_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*while_statement	:	while enter_loop ( expression ) statement leave_loop */
/*while_statement	:	while enter_loop ( error ) statement leave_loop */
static psrNode_t* AR_STDCALL on_while_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*do_while_statement	:	do enter_loop statement while ( expression ) leave_loop semi */
/*do_while_statement	:	do enter_loop statement while ( error ) leave_loop semi */
static psrNode_t* AR_STDCALL on_do_while_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_statement	:	for ( NAME in expression ) enter_loop statement leave_loop */
static psrNode_t* AR_STDCALL on_for_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_statement	:	for ( error ) enter_loop statement leave_loop */
static psrNode_t* AR_STDCALL on_error_for_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*enter_loop	:	 */
static psrNode_t* AR_STDCALL on_enter_loop(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*leave_loop	:	 */
static psrNode_t* AR_STDCALL on_leave_loop(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*jump_statement	:	continue semi */
static psrNode_t* AR_STDCALL on_continue_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*jump_statement	:	break semi */
static psrNode_t* AR_STDCALL on_break_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*jump_statement	:	return semi */
/*jump_statement	:	return expression semi */
static psrNode_t* AR_STDCALL on_return_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*semi	:	error */
static psrNode_t* AR_STDCALL on_semi_error(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*assignment_expression	:	unary_expression = aggregate_constructor */
/*assignment_expression	:	unary_expression = assignment_expression */
static psrNode_t* AR_STDCALL on_assignment_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*constant_expression	:	binary_expression ? expression : expression */
static psrNode_t* AR_STDCALL on_condition_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*binary_expression	:	binary_expression + binary_expression */
/*binary_expression	:	binary_expression - binary_expression */
/*binary_expression	:	binary_expression * binary_expression */
/*binary_expression	:	binary_expression / binary_expression */
/*binary_expression	:	binary_expression % binary_expression */
/*binary_expression	:	binary_expression < binary_expression */
/*binary_expression	:	binary_expression <= binary_expression */
/*binary_expression	:	binary_expression > binary_expression */
/*binary_expression	:	binary_expression >= binary_expression */
/*binary_expression	:	binary_expression == binary_expression */
/*binary_expression	:	binary_expression != binary_expression */
/*binary_expression	:	binary_expression && binary_expression */
/*binary_expression	:	binary_expression || binary_expression */
static psrNode_t* AR_STDCALL on_binary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*unary_expression	:	+ unary_expression */
/*unary_expression	:	- unary_expression */
/*unary_expression	:	! unary_expression */
/*unary_expression	:	++ unary_expression */
/*unary_expression	:	-- unary_expression */
static psrNode_t* AR_STDCALL on_unary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*postfix_expression	:	postfix_expression ++ */
/*postfix_expression	:	postfix_expression -- */
static psrNode_t* AR_STDCALL on_post_add_minus_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*postfix_expression	:	postfix_expression [ expression ] */
/*postfix_expression	:	postfix_expression [ error ] */
static psrNode_t* AR_STDCALL on_index_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*postfix_expression	:	postfix_expression . NAME */
static psrNode_t* AR_STDCALL on_access_name_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*primary_expression	:	( expression ) */
/*primary_expression	:	( error ) */
static psrNode_t* AR_STDCALL on_lp_rp_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*primary_expression	:	NAME */
static psrNode_t* AR_STDCALL on_identifier_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*constant	:	FLOAT_NUMBER */
/*constant	:	INT_NUMBER */
/*constant	:	STRING */
/*constant	:	true */
/*constant	:	false */
/*constant	:	null */
static psrNode_t* AR_STDCALL on_constant(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*value_expression	:	var aggregate_constructor */
/*value_expression	:	var constant */
static psrNode_t* AR_STDCALL handle_value_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*import_expression	:	import ( STRING ) */
static psrNode_t* AR_STDCALL on_import_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*call_expression	:	postfix_expression ( expression_list ) */
/*call_expression	:	postfix_expression ( error ) */
/*call_expression	:	postfix_expression ( ) */
static psrNode_t* AR_STDCALL on_call_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*expression_list	:	expression_list , expression */
static psrNode_t* AR_STDCALL on_expression_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);




static struct { const wchar_t	*rule; const wchar_t	*prec_token; psrRuleFunc_t	handler; size_t	auto_ret; } __g_rule_pattern[] = {
{L"program  :  translation_unit ", NULL, on_translation_unit, 0},
{L"program  :   ", NULL, on_translation_unit, 0},
{L"translation_unit  :  element ", NULL, auto_return_null, 0},
{L"translation_unit  :  translation_unit element ", NULL, auto_return_null, 0},
{L"element  :  declaration ", NULL, auto_return_null, 0},
{L"element  :  function_defination ", NULL, auto_return_null, 0},
{L"element  :  statement ", NULL, on_global_stmtement, 0},
{L"function_signature  :  var NAME ( params ) ", NULL, on_function_signature, 0},
{L"function_defination  :  function_signature compound_statement ", NULL, on_function_defination, 0},
{L"params  :  namelist , ... ", NULL, on_namelist_ellipsis, 0},
{L"params  :  namelist ", NULL, auto_return_0, 0},
{L"params  :  ... ", NULL, on_ellipsis, 0},
{L"params  :   ", NULL, NULL, 0},
{L"namelist  :  namelist , NAME ", NULL, on_name_list, 0},
{L"namelist  :  NAME ", NULL, on_name, 0},
{L"declaration  :  var init_declarator_list semi ", NULL, auto_return_null, 0},
{L"declaration  :  var error ; ", NULL, auto_return_null, 0},
{L"init_declarator_list  :  init_declarator ", NULL, auto_return_null, 0},
{L"init_declarator_list  :  init_declarator_list , init_declarator ", NULL, auto_return_null, 0},
{L"init_declarator  :  NAME = expression ", NULL, on_declarator, 0},
{L"init_declarator  :  NAME = aggregate_constructor ", NULL, on_declarator, 0},
{L"init_declarator  :  NAME ", NULL, on_declarator, 0},
{L"aggregate_constructor  :  table_constructor ", NULL, handle_aggregate_constructor, 0},
{L"aggregate_constructor  :  list_constructor ", NULL, handle_aggregate_constructor, 0},
{L"list_constructor  :  [ list_field_list ] ", NULL, handle_list_constructor, 0},
{L"list_constructor  :  [ ] ", NULL, handle_list_constructor, 0},
{L"list_constructor  :  [ error ] ", NULL, handle_list_constructor, 0},
{L"list_field_list  :  list_field_list , field ", NULL, on_list_field_list, 0},
{L"list_field_list  :  field ", NULL, auto_return_0, 0},
{L"table_constructor  :  { table_field_list } ", NULL, on_table_constructor, 0},
{L"table_constructor  :  { } ", NULL, on_table_constructor, 0},
{L"table_constructor  :  { error } ", NULL, on_table_constructor, 0},
{L"table_field_list  :  table_field_list , table_field ", NULL, handle_table_field_list, 0},
{L"table_field_list  :  table_field ", NULL, handle_table_field_list, 0},
{L"table_field  :  expression : field ", NULL, handle_table_field, 0},
{L"field  :  expression ", NULL, auto_return_0, 0},
{L"field  :  aggregate_constructor ", NULL, auto_return_0, 0},
{L"statement  :  compound_statement ", NULL, auto_return_0, 0},
{L"statement  :  expression_statement ", NULL, auto_return_0, 0},
{L"statement  :  selection_statement ", NULL, auto_return_0, 0},
{L"statement  :  iteration_statement ", NULL, auto_return_0, 0},
{L"statement  :  jump_statement ", NULL, auto_return_0, 0},
{L"statement  :  empty_statement ", NULL, auto_return_0, 0},
{L"compound_statement  :  start_block compound_element_list } ", NULL, on_compound_statement, 0},
{L"compound_statement  :  start_block } ", NULL, on_empty_compound_statement, 0},
{L"compound_statement  :  start_block error } ", NULL, on_compound_error_statement, 0},
{L"start_block  :  { ", NULL, on_start_block, 0},
{L"compound_element_list  :  compound_element_list compound_element ", NULL, auto_return_null, 0},
{L"compound_element_list  :  compound_element ", NULL, auto_return_null, 0},
{L"compound_element  :  statement ", NULL, on_compound_element, 0},
{L"compound_element  :  declaration ", NULL, auto_return_null, 0},
{L"empty_statement  :  ; ", NULL, on_empty_statement, 0},
{L"expression_statement  :  expression semi ", NULL, on_expression_statement, 0},
{L"expression_statement  :  error ; ", NULL, auto_return_null, 0},
{L"selection_statement  :  if_statement ", NULL, auto_return_0, 0},
{L"selection_statement  :  if_else_statement ", NULL, auto_return_0, 0},
{L"if_statement  :  if ( expression ) statement ", L"IF_WITHOUT_ELSE", on_if_statement, 0},
{L"if_statement  :  if ( error ) statement ", L"IF_WITHOUT_ELSE", on_if_statement, 0},
{L"if_else_statement  :  if ( expression ) statement else statement ", NULL, on_if_else_statement, 0},
{L"if_else_statement  :  if ( error ) statement else statement ", NULL, on_if_else_statement, 0},
{L"iteration_statement  :  while_statement ", NULL, auto_return_0, 0},
{L"iteration_statement  :  do_while_statement ", NULL, auto_return_0, 0},
{L"iteration_statement  :  for_statement ", NULL, auto_return_0, 0},
{L"while_statement  :  while enter_loop ( expression ) statement leave_loop ", NULL, on_while_statement, 0},
{L"while_statement  :  while enter_loop ( error ) statement leave_loop ", NULL, on_while_statement, 0},
{L"do_while_statement  :  do enter_loop statement while ( expression ) leave_loop semi ", NULL, on_do_while_statement, 0},
{L"do_while_statement  :  do enter_loop statement while ( error ) leave_loop semi ", NULL, on_do_while_statement, 0},
{L"for_statement  :  for ( NAME in expression ) enter_loop statement leave_loop ", NULL, on_for_statement, 0},
{L"for_statement  :  for ( error ) enter_loop statement leave_loop ", NULL, on_error_for_statement, 0},
{L"enter_loop  :   ", NULL, on_enter_loop, 0},
{L"leave_loop  :   ", NULL, on_leave_loop, 0},
{L"jump_statement  :  continue semi ", NULL, on_continue_statement, 0},
{L"jump_statement  :  break semi ", NULL, on_break_statement, 0},
{L"jump_statement  :  return semi ", NULL, on_return_statement, 0},
{L"jump_statement  :  return expression semi ", NULL, on_return_statement, 0},
{L"semi  :  ; ", NULL, auto_return_0, 0},
{L"semi  :  error ", NULL, on_semi_error, 0},
{L"expression  :  assignment_expression ", NULL, auto_return_0, 0},
{L"assignment_expression  :  constant_expression ", NULL, auto_return_0, 0},
{L"assignment_expression  :  unary_expression = aggregate_constructor ", NULL, on_assignment_expression, 0},
{L"assignment_expression  :  unary_expression = assignment_expression ", NULL, on_assignment_expression, 0},
{L"constant_expression  :  binary_expression ", NULL, auto_return_0, 0},
{L"constant_expression  :  binary_expression ? expression : expression ", NULL, on_condition_expression, 0},
{L"binary_expression  :  unary_expression ", NULL, auto_return_0, 0},
{L"binary_expression  :  binary_expression + binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression - binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression * binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression / binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression % binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression < binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression <= binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression > binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression >= binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression == binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression != binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression && binary_expression ", NULL, on_binary_expression, 0},
{L"binary_expression  :  binary_expression || binary_expression ", NULL, on_binary_expression, 0},
{L"unary_expression  :  + unary_expression ", NULL, on_unary_expression, 0},
{L"unary_expression  :  - unary_expression ", NULL, on_unary_expression, 0},
{L"unary_expression  :  ! unary_expression ", NULL, on_unary_expression, 0},
{L"unary_expression  :  ++ unary_expression ", NULL, on_unary_expression, 0},
{L"unary_expression  :  -- unary_expression ", NULL, on_unary_expression, 0},
{L"unary_expression  :  postfix_expression ", NULL, auto_return_0, 0},
{L"postfix_expression  :  postfix_expression ++ ", NULL, on_post_add_minus_expression, 0},
{L"postfix_expression  :  postfix_expression -- ", NULL, on_post_add_minus_expression, 0},
{L"postfix_expression  :  postfix_expression [ expression ] ", NULL, on_index_expression, 0},
{L"postfix_expression  :  postfix_expression [ error ] ", NULL, on_index_expression, 0},
{L"postfix_expression  :  postfix_expression . NAME ", NULL, on_access_name_expression, 0},
{L"postfix_expression  :  call_expression ", NULL, auto_return_0, 0},
{L"postfix_expression  :  primary_expression ", NULL, auto_return_0, 0},
{L"primary_expression  :  ( expression ) ", NULL, on_lp_rp_expression, 0},
{L"primary_expression  :  ( error ) ", NULL, on_lp_rp_expression, 0},
{L"primary_expression  :  NAME ", NULL, on_identifier_expression, 0},
{L"primary_expression  :  constant ", NULL, auto_return_0, 0},
{L"primary_expression  :  import_expression ", NULL, auto_return_0, 0},
{L"primary_expression  :  value_expression ", NULL, auto_return_0, 0},
{L"constant  :  FLOAT_NUMBER ", NULL, on_constant, 0},
{L"constant  :  INT_NUMBER ", NULL, on_constant, 0},
{L"constant  :  STRING ", NULL, on_constant, 0},
{L"constant  :  true ", NULL, on_constant, 0},
{L"constant  :  false ", NULL, on_constant, 0},
{L"constant  :  null ", NULL, on_constant, 0},
{L"value_expression  :  var aggregate_constructor ", NULL, handle_value_expression, 0},
{L"value_expression  :  var constant ", NULL, handle_value_expression, 0},
{L"import_expression  :  import ( STRING ) ", NULL, on_import_statement, 0},
{L"call_expression  :  postfix_expression ( expression_list ) ", NULL, on_call_expression, 0},
{L"call_expression  :  postfix_expression ( error ) ", NULL, on_call_expression, 0},
{L"call_expression  :  postfix_expression ( ) ", NULL, on_call_expression, 0},
{L"expression_list  :  expression ", NULL, auto_return_0, 0},
{L"expression_list  :  expression_list , expression ", NULL, on_expression_list, 0}
};

#define __RULE_COUNT__ ((size_t)130)
#define START_RULE L"program"

static lex_t*	__build_lex()													
{																				
		lex_t	*lex;															
		size_t i;																
		lex = Lex_Create();														
		for(i = 0; i < __NAME_COUNT__; ++i)										
		{																		
				if(!Lex_Insert(lex, __g_lex_name[i]))							
				{																
						Lex_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		for(i = 0; i < __TERM_COUNT__; ++i)										
		{																		
				lexAction_t		act;											
				act.is_skip		=		__g_term_pattern[i].skip;				
				act.priority	=		__g_term_pattern[i].lex_prec;			
				act.value		=		__g_term_pattern[i].tokval;				
				if(!Lex_InsertRule(lex, __g_term_pattern[i].regex, &act))		
				{																
						Lex_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		return lex;																
}

static psrGrammar_t*	__build_grammar(const psrHandler_t	*handler)															
{																																
		psrGrammar_t	*grammar;																								
		size_t i;																												
		AR_ASSERT(handler != NULL);																								
		grammar = Parser_CreateGrammar(handler);																				
		for(i = 0; i < __TERM_COUNT__; ++i)																						
		{																														
				if(__g_term_pattern[i].skip || __g_term_pattern[i].tokval == 0)continue;										
				if(!Parser_InsertTerm(grammar, __g_term_pattern[i].name, __g_term_pattern[i].tokval, PARSER_ASSOC_NONASSOC,0, __g_term_pattern[i].leaf))	
				{																												
						Parser_DestroyGrammar(grammar);																			
						grammar = NULL;																							
						AR_ASSERT(false);																						
						return NULL;																							
				}																												
		}																														
		for(i = 0; i < __PREC_COUNT__; ++i)																						
		{																														
				psrTermInfo_t	*info;																							
				info = Parser_GetTermSymbInfoByName(grammar, __g_prec_pattern[i].name);											
				if(info == NULL)																								
				{																												
						if(!Parser_InsertTerm(grammar, __g_prec_pattern[i].name, __g_prec_pattern[i].tokval, __g_prec_pattern[i].assoc, __g_prec_pattern[i].prec_level, NULL))
						{																																					
								Parser_DestroyGrammar(grammar);																												
								grammar = NULL;																																
								AR_ASSERT(false);																															
								return NULL;																																
						}																																					
				}else																																						
				{																																							
						info->assoc = __g_prec_pattern[i].assoc;																											
						info->prec = __g_prec_pattern[i].prec_level;																										
				}																																							
		}																																									
		for(i = 0; i < __RULE_COUNT__; ++i)																													
		{																																									
				if(!Parser_InsertRuleByStr(grammar, __g_rule_pattern[i].rule, __g_rule_pattern[i].prec_token, __g_rule_pattern[i].handler, __g_rule_pattern[i].auto_ret))		
				{																																							
						Parser_DestroyGrammar(grammar);																														
						grammar = NULL;																																		
						AR_ASSERT(false);																																	
						return NULL;																																		
				}																																							
		}																																									
		if(!Parser_SetStartRule(grammar,START_RULE) || !Parser_CheckIsValidGrammar(grammar, NULL))																			
		{																																									
				Parser_DestroyGrammar(grammar);																																
				grammar = NULL;																																				
				AR_ASSERT(false);																																			
				return NULL;																																				
		}																																									
		return grammar;																																						
}



static psrNode_t* AR_STDCALL default_leaf_handler(const psrToken_t *tok,void *ctx)
{
	 { 
					tguParser_t	*parser = (tguParser_t*)ctx;
					const wchar_t	*term_str = NULL;
					AR_ASSERT(parser != NULL && tok != NULL);
					AR_ASSERT(tok->str_cnt > 0);
					term_str = TGU_AllocStringN(tok->str, tok->str_cnt);
					return on_lex_node(parser, term_str, tok->term_val, tok->line, tok->col);
				 }
}


static psrNode_t* AR_STDCALL on_string_leaf_handler(const psrToken_t *tok,void *ctx)
{
	 { 
					arEscStrErr_t	err;
					tguParser_t	*parser = (tguParser_t*)ctx;
					wchar_t	*str = NULL;
					const wchar_t *term_str;
					AR_ASSERT(parser != NULL && tok != NULL);
					AR_ASSERT(tok->str_cnt >= 2);			
					AR_ASSERT(tok->str[0] == L'"' || tok->str[0] == L'\'');
					AR_ASSERT(tok->str[tok->str_cnt-1] == L'"' || tok->str[tok->str_cnt-1] == L'\'');

					str = AR_escstr_to_str_n(tok->str + 1, tok->str_cnt - 2, &err);
					if(str == NULL)
					{
						wchar_t	msg[1024];
						parser->has_error = true;
						AR_swprintf(msg, 1024, L"error : character escape sequence");
						TGU_ReportError(&parser->report, msg, tok->line);
					}
					term_str = TGU_AllocString(str == NULL ? L"" : str);
					
					if(str)
					{
						AR_DEL(str);
						str = NULL;
					}

					return on_lex_node(parser, term_str, tok->term_val, tok->line, tok->col);
				 }
}


/*program	:	translation_unit */
/*program	:	 */
static psrNode_t* AR_STDCALL on_translation_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
					tguParser_t 	*parser = (tguParser_t*)ctx;
					tguBlock_t	*result;
					AR_ASSERT(count == 0 || count == 1);

					AR_UNUSED(parser);
					AR_UNUSED(result);
					return NULL;
				 }
}




/*translation_unit	:	element */
/*translation_unit	:	translation_unit element */
/*element	:	declaration */
/*element	:	function_defination */
/*declaration	:	var init_declarator_list semi */
/*declaration	:	var error ; */
/*init_declarator_list	:	init_declarator */
/*init_declarator_list	:	init_declarator_list , init_declarator */
/*compound_element_list	:	compound_element_list compound_element */
/*compound_element_list	:	compound_element */
/*compound_element	:	declaration */
/*expression_statement	:	error ; */
static psrNode_t* AR_STDCALL auto_return_null(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						return NULL;
					 }
}




/*element	:	statement */
static psrNode_t* AR_STDCALL on_global_stmtement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						AR_ASSERT(ns != NULL && count == 1);
						if(ns[0] == NULL)
						{
							return NULL;
						}
						
						AR_ASSERT(ns[0]->type == TGU_NODE_STMT_T && ns[0]->stmt != NULL);
						
						AR_ASSERT(parser->top_block == parser->abs_tree);
						TGU_InsertStmtToBlock(parser->top_block, ns[0]->stmt);
						ns[0]->stmt = NULL;
						return NULL;

				 }
}




/*function_signature	:	var NAME ( params ) */
static psrNode_t* AR_STDCALL on_function_signature(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t 	*parser = (tguParser_t*)ctx;
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguToken_t		name;
						tguLexInfo_t		lex_info;
						tguParams_t		*params;
						AR_ASSERT(ns[0] != NULL && ns[1] != NULL);

						lex_info = ns[0]->token.lex_info;
						name = ns[1]->token;
						if(ns[3] == NULL)
						{
							params = NULL;
						}else
						{
							params = ns[3]->params;
							AR_ASSERT(params != NULL);
						}
						
						start_function(parser, name.token, params, &lex_info);
						return NULL;
				 }
}




/*function_defination	:	function_signature compound_statement */
static psrNode_t* AR_STDCALL on_function_defination(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t 	*parser = (tguParser_t*)ctx;
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguStmt_t	*stmt;
						if(ns[1] != NULL)
						{
							stmt = ns[1]->stmt;
							ns[1]->stmt = NULL;
						}else
						{
							stmt = NULL;
						}

						close_function(parser, stmt);
						return NULL;
				 }
}




/*params	:	namelist , ... */
static psrNode_t* AR_STDCALL on_namelist_ellipsis(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						AR_ASSERT(nodes != NULL && count == 3);
						ns[0]->params->is_variadic = true;
						ret = ns[0];
						ns[0] = NULL;
						return ret;
				 }
}




/*params	:	namelist */
/*list_field_list	:	field */
/*field	:	expression */
/*field	:	aggregate_constructor */
/*statement	:	compound_statement */
/*statement	:	expression_statement */
/*statement	:	selection_statement */
/*statement	:	iteration_statement */
/*statement	:	jump_statement */
/*statement	:	empty_statement */
/*selection_statement	:	if_statement */
/*selection_statement	:	if_else_statement */
/*iteration_statement	:	while_statement */
/*iteration_statement	:	do_while_statement */
/*iteration_statement	:	for_statement */
/*semi	:	; */
/*expression	:	assignment_expression */
/*assignment_expression	:	constant_expression */
/*constant_expression	:	binary_expression */
/*binary_expression	:	unary_expression */
/*unary_expression	:	postfix_expression */
/*postfix_expression	:	call_expression */
/*postfix_expression	:	primary_expression */
/*primary_expression	:	constant */
/*primary_expression	:	import_expression */
/*primary_expression	:	value_expression */
/*expression_list	:	expression */
static psrNode_t* AR_STDCALL auto_return_0(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						psrNode_t *ret = nodes[0];
						ret  = nodes[0];
						nodes[0] = NULL;
						return ret;
				 }
}




/*params	:	... */
static psrNode_t* AR_STDCALL on_ellipsis(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParams_t	*params;
						tguSynNode_t	*ret;
						AR_ASSERT(nodes != NULL && count == 1);

						params = TGU_CreateParams();
						params->is_variadic = true;
						ret = __create_synnode(TGU_NODE_PARAMS_T, (void*)params);
						return ret;
				 }
}




/*namelist	:	namelist , NAME */
static psrNode_t* AR_STDCALL on_name_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						tguParams_t	*params;
						tguToken_t	tok;
						AR_ASSERT(nodes != NULL && count == 2);
						tok = ns[1]->token;
						params = ns[0]->params;
						TGU_InsertToParams(params, &tok);
						ret = ns[0];
						ns[0] = NULL;
						return ret;
				 }
}




/*namelist	:	NAME */
static psrNode_t* AR_STDCALL on_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						tguParams_t	*params;
						tguToken_t	tok;
						AR_ASSERT(nodes != NULL && count == 1);
						tok = ns[0]->token;
						params = TGU_CreateParams();
						TGU_InsertToParams(params, &tok);
						ret = __create_synnode(TGU_NODE_PARAMS_T, (void*)params);
						return ret;
				 }
}




/*init_declarator	:	NAME = expression */
/*init_declarator	:	NAME = aggregate_constructor */
/*init_declarator	:	NAME */
static psrNode_t* AR_STDCALL on_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t 		*parser = (tguParser_t*)ctx;
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguExpr_t		*expr;
						AR_ASSERT(nodes != NULL && parser != NULL && (count == 1 || count == 3));

						if(count == 1)
						{
							/*声明了一个null类型的变量*/
							handle_symb_from_expression(parser, &ns[0]->token, NULL);
						}else
						{
							if(ns[2] == NULL)
							{
								/*expression 或者 table_constructor出现错误*/
								parser->has_error = true;
								handle_symb_from_expression(parser, &ns[0]->token, NULL);
							}else 
							{
								expr = ns[2]->expr;
								ns[2]->expr = NULL;
								AR_ASSERT(expr != NULL);
								handle_symb_from_expression(parser, &ns[0]->token, expr);
							}
						}

						return NULL;
					 }
}




/*aggregate_constructor	:	table_constructor */
/*aggregate_constructor	:	list_constructor */
static psrNode_t* AR_STDCALL handle_aggregate_constructor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*list_constructor	:	[ list_field_list ] */
/*list_constructor	:	[ ] */
/*list_constructor	:	[ error ] */
static psrNode_t* AR_STDCALL handle_list_constructor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*list_field_list	:	list_field_list , field */
static psrNode_t* AR_STDCALL on_list_field_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						tguExpr_t		*lst;
						AR_ASSERT(ns != NULL && count == 3);
						if(ns[0] == NULL) return ns[2];
						if(ns[2] == NULL) return ns[0];
						AR_ASSERT(ns[0]->expr != NULL  && ns[2]->expr != NULL);

						for(lst = ns[0]->expr; lst->next != NULL; lst = lst->next);
						
						lst->next = ns[2]->expr;
						ns[2]->expr = NULL;
						ret = ns[0];
						ns[0] = NULL;
						return ret;

					 }
}




/*table_constructor	:	{ table_field_list } */
/*table_constructor	:	{ } */
/*table_constructor	:	{ error } */
static psrNode_t* AR_STDCALL on_table_constructor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t 	*parser = (tguParser_t*)ctx;
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						AR_ASSERT(parser != NULL && ns != NULL);
						AR_ASSERT(count == 2 || count == 3);

						AR_UNUSED(parser);
						AR_UNUSED(ns);
						
						ret = NULL;
						return ret;	
						
					 }
}




/*table_field_list	:	table_field_list , table_field */
/*table_field_list	:	table_field */
static psrNode_t* AR_STDCALL handle_table_field_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_field	:	expression : field */
static psrNode_t* AR_STDCALL handle_table_field(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*compound_statement	:	start_block compound_element_list } */
static psrNode_t* AR_STDCALL on_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
					tguParser_t 	*parser = (tguParser_t*)ctx;
					tguSynNode_t	**ns = (tguSynNode_t**)nodes;
					tguSynNode_t	*ret;
					tguBlock_t		*cb = NULL;
					tguStmt_t *stmt;
						
					AR_ASSERT(nodes != NULL && (count == 3));
					cb = TGU_ParserPopBlock(parser);
						
					stmt = make_compound_stmt(parser, cb, &ns[0]->token.lex_info,&ns[2]->token.lex_info);
					ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
					return ret;
				 }
}




/*compound_statement	:	start_block } */
static psrNode_t* AR_STDCALL on_empty_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						tguStmt_t *stmt;		
						tguBlock_t		*cb = NULL;
						tguParser_t	*parser = (tguParser_t*)ctx;
						AR_ASSERT(nodes != NULL && (count == 2));
						cb = TGU_ParserPopBlock(parser);
						cb->begin = ns[0]->token.lex_info;
						cb->end = ns[1]->token.lex_info;
						
						stmt = make_compound_stmt(parser, cb, &ns[0]->token.lex_info,&ns[1]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
						
				 }
}




/*compound_statement	:	start_block error } */
static psrNode_t* AR_STDCALL on_compound_error_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t 	*parser = (tguParser_t*)ctx;
						/*tguSynNode_t	**ns = (tguSynNode_t**)nodes;*/
						tguBlock_t		*cb = NULL;
						AR_ASSERT(nodes != NULL && (count == 2));
						AR_ASSERT(parser != NULL);
						parser->has_error = true;
						cb = TGU_ParserPopBlock(parser);
						TGU_DestroyBlock(cb);
						return NULL;
				 }
}




/*start_block	:	{ */
static psrNode_t* AR_STDCALL on_start_block(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
							tguParser_t 	*parser = (tguParser_t*)ctx;
							tguSynNode_t	**ns = (tguSynNode_t**)nodes;
							tguSynNode_t	*ret;
							AR_ASSERT(ns != NULL && count == 1);
							ret = ns[0]; 
							ns[0] = NULL;
							if(!parser->is_on_function_compound)
							{
								TGU_ParserPushBlock(parser);
							}else
							{
								parser->is_on_function_compound = false;
							}
							return ret;
				 }
}




/*compound_element	:	statement */
static psrNode_t* AR_STDCALL on_compound_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						AR_ASSERT(ns != NULL && count == 1);
						if(ns[0] == NULL)
						{
							return NULL;
						}
						
						AR_ASSERT(ns[0]->type == TGU_NODE_STMT_T && ns[0]->stmt != NULL);
						TGU_InsertStmtToBlock(parser->top_block, ns[0]->stmt);
						ns[0]->stmt = NULL;
						return NULL;
				 }
}




/*empty_statement	:	; */
static psrNode_t* AR_STDCALL on_empty_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguSynNode_t 	*ret;
						tguStmt_t		*stmt;
						AR_ASSERT(ns != NULL && parser != NULL && count == 1);

						stmt = make_empty_statement(parser, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
					 }
}




/*expression_statement	:	expression semi */
static psrNode_t* AR_STDCALL on_expression_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguSynNode_t	*ret;
						tguStmt_t	*stmt;
						tguExpr_t	*expr;
						AR_ASSERT(ns != NULL && count == 2);
						
						if(ns[0] == NULL)
						{
							expr = NULL;
							parser->has_error = true;
						}else
						{
							expr = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}
							
						stmt = make_expression_statement(parser, expr, expr ? &expr->lex_info : NULL);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;

					 }
}




/*if_statement	:	if ( expression ) statement */
/*if_statement	:	if ( error ) statement */
static psrNode_t* AR_STDCALL on_if_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguSynNode_t	*ret;
						tguExpr_t		*expr;
						tguStmt_t		*if_true, *stmt;
						AR_ASSERT(ns != NULL && count == 5);
						
						if(ns[2] == NULL)
						{
							expr = NULL;
							parser->has_error = true;
						}else
						{
							expr = ns[2]->expr;
							ns[2]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}
							
						if(ns[4] == NULL)
						{	
							if_true = NULL;
							parser->has_error = true;
						}else
						{
							if_true = ns[4]->stmt;
							ns[4]->stmt = NULL;
							AR_ASSERT(if_true != NULL);
						}

						stmt = make_if_statement(parser, expr, if_true, NULL, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
				 }
}




/*if_else_statement	:	if ( expression ) statement else statement */
/*if_else_statement	:	if ( error ) statement else statement */
static psrNode_t* AR_STDCALL on_if_else_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguSynNode_t	*ret;
						tguExpr_t		*expr;
						tguStmt_t		*if_true;
						tguStmt_t		*if_false;
						tguStmt_t		*stmt;
						AR_ASSERT(ns != NULL && count == 7);
						if(ns[2] == NULL)
						{
							expr = NULL;
							parser->has_error = true;
						}else
						{
							expr = ns[2]->expr;
							ns[2]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}
							
						if(ns[4] == NULL)
						{	
							if_true = NULL;
							parser->has_error = true;
						}else
						{
							if_true = ns[4]->stmt;
							ns[4]->stmt = NULL;
							AR_ASSERT(if_true != NULL);
						}

						if(ns[6] == NULL)
						{	
							if_false = NULL;
							parser->has_error = true;
						}else
						{
							if_false = ns[6]->stmt;
							ns[6]->stmt = NULL;
							AR_ASSERT(if_false != NULL);
						}


						stmt = make_if_statement(parser, expr, if_true, if_false,  &ns[0]->token.lex_info);	
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
				 }
}




/*while_statement	:	while enter_loop ( expression ) statement leave_loop */
/*while_statement	:	while enter_loop ( error ) statement leave_loop */
static psrNode_t* AR_STDCALL on_while_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguSynNode_t	*ret;
						tguExpr_t		*expr;
						tguStmt_t		*stmt;
						AR_ASSERT(ns != NULL && count == 7);

						if(ns[3] == NULL)
						{
							expr = NULL;
							parser->has_error = true;
						}else
						{
							expr = ns[3]->expr;
							ns[3]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}
							
						if(ns[5] == NULL)
						{	
							stmt = NULL;
							parser->has_error = true;
						}else
						{
							stmt = ns[5]->stmt;
							ns[5]->stmt = NULL;
							AR_ASSERT(stmt != NULL);
						}

						stmt = make_while_statement(parser, TGU_STT_WHILE, expr, stmt, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
					 }
}




/*do_while_statement	:	do enter_loop statement while ( expression ) leave_loop semi */
/*do_while_statement	:	do enter_loop statement while ( error ) leave_loop semi */
static psrNode_t* AR_STDCALL on_do_while_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = 	(tguSynNode_t**)nodes;
						tguParser_t	*parser =	(tguParser_t*)ctx;
						tguSynNode_t	*ret;
						tguExpr_t		*expr;
						tguStmt_t		*stmt;
						AR_ASSERT(ns != NULL && count == 9);
						if(ns[2] == NULL)
						{
							stmt = NULL;
							parser->has_error = true;
						}else
						{
							stmt = ns[2]->stmt;
							ns[2]->stmt = NULL;
							AR_ASSERT(stmt != NULL);
						}
							
						if(ns[5] == NULL)
						{	
							expr = NULL;
							parser->has_error = true;
						}else
						{
							expr = ns[5]->expr;
							ns[5]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}

						stmt = make_while_statement(parser, TGU_STT_DO, expr, stmt, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
					 }
}




/*for_statement	:	for ( NAME in expression ) enter_loop statement leave_loop */
static psrNode_t* AR_STDCALL on_for_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguParser_t		*parser = (tguParser_t*)ctx;
						tguSynNode_t		*ret;
						
						AR_ASSERT(ns != NULL && count == 11);
						
						AR_UNUSED(parser);
						AR_UNUSED(ns);

						ret = NULL;

						return ret;
				 }
}




/*for_statement	:	for ( error ) enter_loop statement leave_loop */
static psrNode_t* AR_STDCALL on_error_for_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguParser_t		*parser = (tguParser_t*)ctx;
						tguSynNode_t		*ret;


						AR_UNUSED(parser);
						AR_UNUSED(ns);

						ret = NULL;



						return ret;
				 }
}




/*enter_loop	:	 */
static psrNode_t* AR_STDCALL on_enter_loop(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t	*parser = NULL;
						AR_ASSERT(ctx != NULL);
						parser = (tguParser_t*)ctx;
						parser->loop_level++;
						return NULL;
					 }
}




/*leave_loop	:	 */
static psrNode_t* AR_STDCALL on_leave_loop(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t	*parser = NULL;
						AR_ASSERT(ctx != NULL);
						parser = (tguParser_t*)ctx;
						AR_ASSERT(parser->loop_level > 0);
						parser->loop_level--;
						return NULL;
					 }
}




/*jump_statement	:	continue semi */
static psrNode_t* AR_STDCALL on_continue_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguStmt_t		*stmt;
						tguParser_t	*parser = (tguParser_t*)ctx;
						stmt = make_jump_statement(parser, TGU_STT_CONTINUE, 	NULL, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;

					 }
}




/*jump_statement	:	break semi */
static psrNode_t* AR_STDCALL on_break_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguStmt_t		*stmt;
						tguParser_t	*parser = (tguParser_t*)ctx;
						ret = AR_NEW(tguSynNode_t);
						ret->type = TGU_NODE_STMT_T;
						stmt = make_jump_statement(parser, TGU_STT_BREAK, 	NULL, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
						
					 }
}




/*jump_statement	:	return semi */
/*jump_statement	:	return expression semi */
static psrNode_t* AR_STDCALL on_return_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguExpr_t		*expr;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguStmt_t		*stmt;
						AR_ASSERT(nodes != NULL && (count == 2 || count == 3));
						
						if(count == 2)
						{
							expr = NULL;
						}else
						{
							if(ns[1] == NULL)
							{
								expr = NULL;
								parser->has_error = true;
							}else
							{
								AR_ASSERT(ns[1]->type == TGU_NODE_EXPR_T);
								expr = ns[1]->expr;
								ns[1]->expr = NULL;
								AR_ASSERT(expr != NULL);
							}
						}

						stmt = make_jump_statement(parser, TGU_STT_RETURN, 	expr, &ns[0]->token.lex_info);
						ret = __create_synnode(TGU_NODE_STMT_T, (void*)stmt);
						return ret;
					 }
}




/*semi	:	error */
static psrNode_t* AR_STDCALL on_semi_error(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguParser_t	*parser = (tguParser_t*)ctx;
						AR_ASSERT(parser != NULL);
						parser->has_error = true;
						return NULL;
					 }
}




/*assignment_expression	:	unary_expression = aggregate_constructor */
/*assignment_expression	:	unary_expression = assignment_expression */
static psrNode_t* AR_STDCALL on_assignment_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguExpr_t		*addr, *value, *expr;
						const tguLexInfo_t *lex_info; 
						AR_ASSERT(ns != NULL && count == 3 && parser != NULL);

						if(ns[0] == NULL)
						{
							parser->has_error = true;
							addr = NULL;	
						}else
						{
							addr = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(addr != NULL);
						}
						

						if(ns[2] == NULL)
						{
							parser->has_error = true;
							value = NULL;	
						}else
						{
							value = ns[2]->expr;
							ns[2]->expr = NULL;
							AR_ASSERT(value != NULL);
						}

						lex_info = addr != NULL ? &addr->lex_info : &ns[1]->token.lex_info;
						AR_ASSERT(lex_info != NULL);
						expr = make_assignment_expression(parser, addr, value, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);

						return ret;

					 }
}




/*constant_expression	:	binary_expression ? expression : expression */
static psrNode_t* AR_STDCALL on_condition_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguExpr_t		*cond, *if_true, *if_false, *expr;
						const tguLexInfo_t *lex_info;
						AR_ASSERT(ns != NULL && count == 3 && parser != NULL);

						if(ns[0] == NULL)
						{
							parser->has_error = true;
							cond= NULL;	
						}else
						{
							cond = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(cond != NULL);
						}

						

						if(ns[2] == NULL)
						{
							parser->has_error = true;
							if_true = NULL;	
						}else
						{
							if_true= ns[2]->expr;
							ns[2]->expr = NULL;
							AR_ASSERT(if_true != NULL);
						}
						
						if(ns[4] == NULL)
						{
							parser->has_error = true;
							if_false = NULL;	
						}else
						{
							if_false= ns[4]->expr;
							ns[4]->expr = NULL;
							AR_ASSERT(if_false != NULL);
						}

						lex_info = cond != NULL ? &cond->lex_info : &ns[1]->token.lex_info;
						AR_ASSERT(lex_info != NULL);
						expr = make_condition_expression(parser, cond, if_true, if_false, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;

					 }
}




/*binary_expression	:	binary_expression + binary_expression */
/*binary_expression	:	binary_expression - binary_expression */
/*binary_expression	:	binary_expression * binary_expression */
/*binary_expression	:	binary_expression / binary_expression */
/*binary_expression	:	binary_expression % binary_expression */
/*binary_expression	:	binary_expression < binary_expression */
/*binary_expression	:	binary_expression <= binary_expression */
/*binary_expression	:	binary_expression > binary_expression */
/*binary_expression	:	binary_expression >= binary_expression */
/*binary_expression	:	binary_expression == binary_expression */
/*binary_expression	:	binary_expression != binary_expression */
/*binary_expression	:	binary_expression && binary_expression */
/*binary_expression	:	binary_expression || binary_expression */
static psrNode_t* AR_STDCALL on_binary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguExpr_t		*left, *right, *expr;

						tguExprOP_t	op;
						const tguLexInfo_t *lex_info;
						tguToken_t	tok;
						AR_ASSERT(ns != NULL && count == 3 && parser != NULL);

						if(ns[0] == NULL)
						{
							parser->has_error = true;
							left = NULL;	
						}else
						{
							left = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(left != NULL);
						}

						AR_ASSERT(ns[1] != NULL);
						tok = ns[1]->token;


						if(ns[2] == NULL)
						{
							parser->has_error = true;
							right = NULL;	
						}else
						{
							right = ns[2]->expr;
							ns[2]->expr = NULL;
							AR_ASSERT(right != NULL);
						}

						switch(tok.term_val)
						{
						case TOK_INC:
							op = TGU_OP_PLUS;
							break;
						case TOK_SUB :
							op = TGU_OP_MINUS;
							break;
						case TOK_MUL:
							op = TGU_OP_MUL;
							break;
						case TOK_DIV:
							op = TGU_OP_DIV;
							break;
						case TOK_MOD:
							op = TGU_OP_MOD;
							break;
						case TOK_LESS:
							op = TGU_OP_LESS;
							break;
						case TOK_LE:
							op = TGU_OP_LESS_OR_EQUAL;
							break;
						case TOK_GREATER:
							op = TGU_OP_GREATER;
							break;
						case TOK_GE:
							op = TGU_OP_GREATER_OR_EQUAL;
							break;
						case TOK_EQ:
							op = TGU_OP_IS_EQUAL;
							break;
						case TOK_NE:
							op = TGU_OP_NOT_EQUAL;
							break;
						case TOK_ANDAND:
							op = TGU_OP_LOGICAL_AND;
							break;
						case TOK_OROR:
							op = TGU_OP_LOGICAL_OR;
							break;
						default:
							op = TGU_OP_NONE;/*op如果在此不赋值会导致一个warning*/
							AR_ASSERT(false);
							break;
						}

						lex_info  = left != NULL ? &left->lex_info : &tok.lex_info;
						AR_ASSERT(lex_info != NULL);
						expr = make_binary_expression(parser, op, left, right, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;
					 }
}




/*unary_expression	:	+ unary_expression */
/*unary_expression	:	- unary_expression */
/*unary_expression	:	! unary_expression */
/*unary_expression	:	++ unary_expression */
/*unary_expression	:	-- unary_expression */
static psrNode_t* AR_STDCALL on_unary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguExpr_t		*expr;

						tguExprOP_t		op;
						tguToken_t		tok;
						const tguLexInfo_t	*lex_info;
						bool_t			is_lvalue;
						AR_ASSERT(ns != NULL && count == 2 && parser != NULL);
			
						if(ns[1] == NULL)
						{
							parser->has_error = true;
							expr = NULL;	
						}else
						{
							expr = ns[1]->expr;
							ns[1]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}

						AR_ASSERT(ns[0] != NULL);
						tok = ns[0]->token;	
						
						switch(tok.term_val)
						{
						case TOK_INC:
							op = TGU_OP_PREINC;
							is_lvalue = true;
							break;
						case TOK_DEC:
							op = TGU_OP_PREDEC;
							is_lvalue = true;
							break;
						case TOK_ADD:
							op = TGU_OP_UNARY_PLUS;
							is_lvalue = false;
							break;
						case TOK_SUB:
							op = TGU_OP_UNARY_MINUS;
							is_lvalue = false;
							break;
						case TOK_NOT:
							op = TGU_OP_LOGICAL_NOT;
							is_lvalue = false;
							break;
						default:
							op = TGU_OP_NONE;
							is_lvalue = false;
							AR_ASSERT(false);
							break;
						}
						lex_info = expr != NULL ? &expr->lex_info : &tok.lex_info;
						expr = make_unary_expression(parser, op, expr, is_lvalue, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;

				 }
}




/*postfix_expression	:	postfix_expression ++ */
/*postfix_expression	:	postfix_expression -- */
static psrNode_t* AR_STDCALL on_post_add_minus_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 		*ret;
						tguParser_t		*parser = (tguParser_t*)ctx;
						tguExpr_t		*expr;
						tguToken_t		tok;
						tguExprOP_t		op;
						const tguLexInfo_t	*lex_info; 

						AR_ASSERT(ns != NULL && count == 2 && parser != NULL);

						if(ns[0] == NULL)
						{
							parser->has_error = true;
							expr = NULL;	
						}else
						{
							expr = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}

						AR_ASSERT(ns[1] != NULL );
						tok = ns[1]->token;	
							
						switch(tok.term_val)	
						{
						case TOK_INC:
							op = TGU_OP_POSTINC;
							break;
						case TOK_DEC:
							op = TGU_OP_POSTDEC;
							break;
						default:
							op = TGU_OP_NONE;
							AR_ASSERT(false);
							break;
						}
						
						lex_info = expr != NULL ? &expr->lex_info : &tok.lex_info;
						expr = make_unary_expression(parser, op, expr, false, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;
				 }
}




/*postfix_expression	:	postfix_expression [ expression ] */
/*postfix_expression	:	postfix_expression [ error ] */
static psrNode_t* AR_STDCALL on_index_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
					
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 	*ret;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguExpr_t		*expr, *index_expr;
						const tguLexInfo_t	*lex_info;
						AR_ASSERT(ns != NULL && count == 4 && parser != NULL);

						if(ns[0] == NULL)
						{
							parser->has_error = true;
							expr = NULL;
						}else
						{
							expr = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}

						if(ns[2] == NULL)
						{
							index_expr = NULL;
							parser->has_error = true;
						}else
						{
							index_expr = ns[2]->expr;
							ns[2]->expr = NULL;
							AR_ASSERT(index_expr != NULL);
						}

						lex_info = expr != NULL ? &expr->lex_info : &ns[1]->token.lex_info;
						expr = make_index_expression(parser, expr, index_expr, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;
				 }
}




/*postfix_expression	:	postfix_expression . NAME */
static psrNode_t* AR_STDCALL on_access_name_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguSynNode_t		*ret;
						tguParser_t		*parser = (tguParser_t*)ctx;
						tguExpr_t		*expr, *index_expr;
						tguToken_t		tmp;
						const tguLexInfo_t	*lex_info;
						AR_ASSERT(ns != NULL && count == 3 && parser != NULL);

						if(ns[0] == NULL)
						{
							parser->has_error = true;
							expr = NULL;
						}else
						{
							expr = ns[0]->expr;
							ns[0]->expr = NULL;
							AR_ASSERT(expr != NULL);
						}

						tmp = ns[2]->token;
						tmp.term_val = TOK_STRING;
						tmp.token = ns[2]->token.token;
						index_expr = make_constant_expression(parser, &tmp);
						AR_ASSERT(index_expr != NULL);
						tmp.token = NULL;

						lex_info = expr != NULL ? &expr->lex_info : &index_expr->lex_info;
						expr = make_index_expression(parser, expr, index_expr, lex_info);
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;
				 }
}




/*primary_expression	:	( expression ) */
/*primary_expression	:	( error ) */
static psrNode_t* AR_STDCALL on_lp_rp_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
					tguParser_t	*parser = (tguParser_t*)ctx;
					psrNode_t 	*ret;
					if(nodes[1] == NULL)
					{
						parser->has_error = true;
						ret = NULL;
					}else
					{
						ret = nodes[1];
						nodes[1] = NULL;
					}
					return ret;
				 }
}




/*primary_expression	:	NAME */
static psrNode_t* AR_STDCALL on_identifier_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 		*ret;
						tguParser_t		*parser = (tguParser_t*)ctx;
						tguExpr_t		*expr;
						AR_ASSERT(parser != NULL && ns != NULL && count == 1);
						expr = make_identifier_expression(parser, &ns[0]->token);
						
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;

				 }
}




/*constant	:	FLOAT_NUMBER */
/*constant	:	INT_NUMBER */
/*constant	:	STRING */
/*constant	:	true */
/*constant	:	false */
/*constant	:	null */
static psrNode_t* AR_STDCALL on_constant(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*value_expression	:	var aggregate_constructor */
/*value_expression	:	var constant */
static psrNode_t* AR_STDCALL handle_value_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*import_expression	:	import ( STRING ) */
static psrNode_t* AR_STDCALL on_import_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
					return NULL;
				 }
}




/*call_expression	:	postfix_expression ( expression_list ) */
/*call_expression	:	postfix_expression ( error ) */
/*call_expression	:	postfix_expression ( ) */
static psrNode_t* AR_STDCALL on_call_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t		**ns = (tguSynNode_t**)nodes;
						tguSynNode_t 		*ret;
						tguParser_t	*parser = (tguParser_t*)ctx;
						tguExpr_t		*expr, *call_expr, *args;
						const tguLexInfo_t	*lex_info;

						/*如果postfix_expression 为空，则表明此call表达式错误*/
						if(ns[0] == NULL)				
						{
							parser->has_error = true;
							call_expr = NULL;
						}else
						{
							call_expr= ns[0]->expr;
							ns[0]->expr = NULL;
						}


						if(count == 4)
						{
							if(ns[2] == NULL)/*对应"(" error ")"*/
							{
								args = NULL;
								parser->has_error = true;
							}else
							{
								args = ns[2]->expr;
								ns[2]->expr = NULL;
								AR_ASSERT(args != NULL);
							}
						}else
						{
						
							AR_ASSERT(count == 3);
							args = NULL;
						}
						
						lex_info = call_expr != NULL ? &call_expr->lex_info : &ns[1]->token.lex_info;
						expr = make_call_expression(parser, call_expr, args, lex_info );
						
						ret = __create_synnode(TGU_NODE_EXPR_T, (void*)expr);
						return ret;
				 }
}




/*expression_list	:	expression_list , expression */
static psrNode_t* AR_STDCALL on_expression_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 { 
						tguSynNode_t	**ns = (tguSynNode_t**)nodes;
						tguSynNode_t	*ret;
						tguExpr_t		*lst;
						AR_ASSERT(ns != NULL && count == 3);
						if(ns[0] == NULL) return ns[2];
						if(ns[2] == NULL) return ns[0];
						AR_ASSERT(ns[0]->expr != NULL  && ns[2]->expr != NULL);

						for(lst = ns[0]->expr; lst->next != NULL; lst = lst->next);
						
						lst->next = ns[2]->expr;
						ns[2]->expr = NULL;
						ret = ns[0];
						ns[0] = NULL;
						return ret;
				 }
}







