#include "test.h"
#include "../Arsenal/Lex/lex.h"



#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Parser/lr_action.h"

#if(0)

#if defined(__LIB)

AR_NAMESPACE_BEGIN



typedef enum
{
		EOI = 0,
		CLP = 354,
		RP = 355,
		ADD = 356,
		MINUS = 357,
		MUL = 358,
		DIV = 359,
		MOD = 360,
		NUMBER = 361
}TokenType_t;

typedef struct __token_tag
{
		TokenType_t		type;
		const wchar_t	*str;
}Token_t;


typedef struct __node_tag
{
		Token_t			op;
		struct __node_tag	*chd[2];
}Node_t;



static Node_t* CreateNode(const Token_t *op, Node_t *l, Node_t *r)
{
		Node_t *node;

		node =AR_NEW0(Node_t);
		node->op = *op;
		node->chd[0] = l;
		node->chd[1] = r;
		return node;
}

static  psrNode_t*		AR_STDCALL create_leaf(const psrToken_t *tok,void *ctx)
{
		Token_t	op;
		op.type = (TokenType_t)tok->term_val;
		op.str = AR_wcsndup(tok->str, tok->str_cnt);
		return (psrNode_t*)CreateNode(&op, NULL, NULL);
}



/*
E : E + E
E : E - E
E : E * E
E : E / E
E : E % E
*/

static  psrNode_t*		AR_STDCALL create_node(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		Node_t *op_node;
		
		op_node = (Node_t*)nodes[1];
		switch(op_node->op.type)
		{
		case ADD:
		case MINUS:
		case MUL:
		case DIV:
		case MOD:
				return (psrNode_t*)CreateNode(&op_node->op, (Node_t*)nodes[0], (Node_t*)nodes[2]);
		default:
				AR_ASSERT(false);
				return NULL;
				break;
		}
}

/*
E : number
E : ( E )
*/

static  psrNode_t*		AR_STDCALL create_node1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		AR_ASSERT(count == 1 || count == 3);
		if(count == 1)
		{
				return nodes[0];
		}else
		{
				return nodes[1];
		}
}

/*
		E : - E
*/


static  psrNode_t*		AR_STDCALL create_node2(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		AR_ASSERT(count == 2);
		return (psrNode_t*)CreateNode(&((Node_t*)nodes[0])->op, NULL, (Node_t*)nodes[1]);
}


static  void			AR_STDCALL free_node(psrNode_t *node, void *ctx)
{
		printf("on_free\r\n");

}

/*
static  void			AR_STDCALL on_error(const psrToken_t *tok, const wchar_t *expected[], size_t count, void *ctx)

{
		printf("on_error\r\n");

}
*/

/*
{L"(", 354, 0, PARSER_ASSOC_NONASSOC},
		{L")", 355, 0, PARSER_ASSOC_NONASSOC},
		{L"+", 356, 0, PARSER_ASSOC_NONASSOC},
		{L"-", 357, 0, PARSER_ASSOC_NONASSOC},
		{L"*", 358, 0, PARSER_ASSOC_NONASSOC},
		{L"/", 359, 0, PARSER_ASSOC_NONASSOC},
		{L"%", 360, 0, PARSER_ASSOC_NONASSOC},
		{L"number", 361, 0, PARSER_ASSOC_NONASSOC},
		{L"UMINUS", 0xFFFF, 0, PARSER_ASSOC_NONASSOC}
*/

static lex_t* __build_lex()
{
		lex_t *lex;

		lex = Lex_Create(NULL);

		Lex_Insert(lex, L"delim 			= 	[ \\r\\n\\t]");
		Lex_Insert(lex, L"digit 			= 	[0-9]");
		Lex_Insert(lex, L"number 			= 	{digit}+");
		Lex_Insert(lex, L"EOI 			= 	$");

		Lex_Insert(lex, L"0				{EOI}");
		Lex_Insert(lex, L"%skip 1		{delim}");
		Lex_Insert(lex, L"354,1			\"(\"");
		Lex_Insert(lex, L"355,1			\")\"");
		Lex_Insert(lex, L"356,1			\"+\"");
		Lex_Insert(lex, L"357,1			\"-\"");
		Lex_Insert(lex, L"358,1			\"*\"");
		Lex_Insert(lex, L"359,1			\"/\"");
		Lex_Insert(lex, L"360,1			\"%\"");
		Lex_Insert(lex, L"361,1		¡¡¡¡{¡¡ number}");
		
		
		if(Lex_GenerateTransTable(lex))
		{
				return lex;
		}else
		{
				AR_ASSERT(0);
				return NULL;
		}
		
}




static psrGrammar_t *__g_gmr = NULL;
static  const parser_t* __build_parser()
{
		psrGrammar_t	*gmr;
		psrHandler_t ctx = {NULL, free_node,};

		gmr = Parser_CreateGrammar(&ctx, NULL);

		Parser_InsertTerm(gmr, L"(", CLP, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L")", RP, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L"+", ADD, PARSER_ASSOC_LEFT, 1, create_leaf);
		Parser_InsertTerm(gmr, L"-", MINUS, PARSER_ASSOC_LEFT, 1, create_leaf);
		Parser_InsertTerm(gmr, L"*", MUL, PARSER_ASSOC_LEFT, 2, create_leaf);
		Parser_InsertTerm(gmr, L"/", DIV, PARSER_ASSOC_LEFT, 2, create_leaf);
		Parser_InsertTerm(gmr, L"%", MOD, PARSER_ASSOC_LEFT, 2, create_leaf);
		Parser_InsertTerm(gmr, L"number", NUMBER, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L"UMINUS", 0xFFFF, PARSER_ASSOC_RIGHT, 3, create_leaf);
		
		Parser_InsertRuleByStr(gmr, L"E : E + E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E - E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E * E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E / E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E % E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : ( E )", NULL, create_node1, 0);
		Parser_InsertRuleByStr(gmr, L"E : - E", L"UMINUS", create_node2, 0);
		Parser_InsertRuleByStr(gmr, L"E : number", NULL, create_node1, 0);

		//Parser_InsertRuleByStr(gmr, L"E : X number", NULL, create_node1, 0);
		//Parser_InsertRuleByStr(gmr, L"E : Y number", NULL, create_node1, 0);
		
/*
		Parser_InsertRuleByStr(gmr, L"X : ", NULL, NULL, 0);
		Parser_InsertRuleByStr(gmr, L"Y : ", NULL, NULL, 0);
*/
		{
				arString_t		*str;

				str = AR_CreateString();
				Parser_PrintGrammar(gmr, str);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));
				AR_DestroyString(str);

				__g_gmr = gmr;
				getchar();
		}

		
		{
				const parser_t *psr;
				
				
				psr =  Parser_CreateParser(gmr, PARSER_SLR);
				
				//AR_printf(L"Conflict == %d\r\n", Parser_CountParserConflict(psr));
				/*Parser_DestroyGrammar(gmr);*/
				arString_t *str = AR_CreateString();

				if(Parser_ReportLeftFactor(gmr, str))
				{
						AR_StrPrint(str);
				}
				
				AR_DestroyString(str);
				getchar();
				return psr;
		}

}

int post_order(Node_t *node)
{
		int l,r,v;
		if(node == NULL)return 0;
		l = post_order(node->chd[0]);
		r = post_order(node->chd[1]);
		
		AR_printf(L"%ls : %d", node->op.str, node->op.type);
		switch(node->op.type)
		{
		case ADD:
				return l + r;
		case MINUS:
				return l - r;
		case MUL:
				return l * r;
		case DIV:
				return l / r;
		case MOD:
				return l % r;
		case NUMBER:
		{
				AR_wtoi32(node->op.str, &v, 10);
				return v;
		}
		default:
				AR_ASSERT(node != NULL);
				return 0;
		}
}





void calc_test()
{
		const parser_t *psr;
		psrContext_t	*pc1, *pc2;
		lex_t	*lex;
		lexMatch_t		match;
		lexToken_t		tok;
		size_t i,k;
		bool_t is_ok;
		arString_t		*str;
		/*
		const psrActionView_t *view;
		const psrConflictView_t	*conflict;
		const psrStatusView_t *first_follow;
		*/

		lex = __build_lex();
		AR_ASSERT(lex);
		psr = __build_parser();
		
		pc1 = Parser_CreateContext(psr, NULL);
		pc2 = Parser_CreateContext(psr, NULL);

		/*
		str = AR_CreateString();

		Parser_ActionTableToString(psr->tbl, str);


		AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		*/

		/*
		first_follow = Parser_CreateParserStatusView(psr);
		

		AR_printf(L"------------------first------------------\r\n");
		for(i = 0; i < first_follow->first_set.count; ++i)
		{
				AR_printf(L"%ls : %ls\r\n", first_follow->first_set.name[i],first_follow->first_set.name_set[i]);
		}

		AR_printf(L"------------------follow------------------\r\n");
		
		for(i = 0; i < first_follow->follow_set.count; ++i)
		{
				AR_printf(L"%ls : %ls\r\n", first_follow->follow_set.name[i],first_follow->follow_set.name_set[i]);
		}
		*/
#if(0)
		view = Parser_CreateParserActionView(psr);

		conflict = Parser_CreateParserConflictView(psr);
		
		AR_printf(L"-----------------------------------------\r\n");

		for(i = 0; i < view->item_cnt; ++i)
		{
				AR_printf(L"%*ls", 20, view->item[i]);
		}

		AR_printf(L"-----------------------------------------\r\n");

		for(i = 0; i < view->row; ++i)
		{
				for(k = 0; k < view->col; ++k)
				{
						AR_printf(L"%*ls", 20, view->action_tbl[AR_TBL_IDX_R(i,k,view->col)]);
				}

				AR_printf(L"\r\n");
		}

		AR_printf(L"-----------------------------------------\r\n");


		for(i = 0; i < conflict->count; ++i)
		{
				const psrConflictItem_t *item = conflict->conflict[i];
				
				AR_printf(L"%ls:\r\n", item->name);
				for(k = 0; k < item->count; ++k)
				{
						AR_printf(L"%ls \r\n", item->items[k]);
				}

				AR_printf(L"\r\n");
		}

#endif


		AR_printf(L"-----------------------------------------\r\n");

		getchar();

		Lex_InitMatch(&match, L"10 + (5 + 4) / 3");
#if(1)
		is_ok = true;
		while(is_ok)
		{
				psrToken_t term;
				is_ok = Lex_Match(lex, &match, &tok);
				if(!is_ok)
				{
						continue;
				}

				
				AR_printf(L"token == %ls : val = %d\r\n", AR_wcsndup(tok.str, tok.count), tok.value);
				PARSER_TOTERMTOK(&tok, &term);
				is_ok = Parser_AddToken(pc1, &term);
				is_ok = Parser_AddToken(pc2, &term);

				if(!is_ok)continue;
				
				if(tok.value == 0)
				{
						break;
				}
		}
		
		AR_ASSERT(is_ok);
		getchar();

		{
				Node_t *res;
				int v;
				res = (Node_t*)Parser_GetResult(pc1);
				v = post_order(res);
				printf("\r\n");
				printf("num == %d\r\n", v);

		}

		{
				Node_t *res;
				int v;
				res = (Node_t*)Parser_GetResult(pc2);
				v = post_order(res);
				printf("\r\n");
				printf("num == %d\r\n", v);

		}

#endif
		Parser_DestroyContext(pc1);
		Parser_DestroyContext(pc2);
		Parser_DestroyParser(psr);
		Parser_DestroyGrammar(__g_gmr);
		Lex_Destroy(lex);
		Lex_UnInitMatch(&match);


}




void calc_test3()
{
		psrGrammar_t	*gmr, *gmr2;
		psrHandler_t ctx = {NULL, free_node};

		gmr = Parser_CreateGrammar(&ctx, NULL);
		

		Parser_InsertTerm(gmr, L"(", CLP, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L")", RP, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L"+", ADD, PARSER_ASSOC_LEFT, 1, create_leaf);
		Parser_InsertTerm(gmr, L"-", MINUS, PARSER_ASSOC_LEFT, 1, create_leaf);
		Parser_InsertTerm(gmr, L"*", MUL, PARSER_ASSOC_LEFT, 2, create_leaf);
		Parser_InsertTerm(gmr, L"/", DIV, PARSER_ASSOC_LEFT, 2, create_leaf);
		Parser_InsertTerm(gmr, L"%", MOD, PARSER_ASSOC_LEFT, 2, create_leaf);
		Parser_InsertTerm(gmr, L"number", NUMBER, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L"UMINUS", 0xFFFF, PARSER_ASSOC_RIGHT, 3, create_leaf);
		
		Parser_InsertRuleByStr(gmr, L"E : E + E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E - E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E * E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E / E", NULL, create_node, 0);
		Parser_InsertRuleByStr(gmr, L"E : E % E", NULL, create_node, 0);

		Parser_InsertRuleByStr(gmr, L"E : number", NULL, create_node1, 0);
		Parser_InsertRuleByStr(gmr, L"E : ( E )", NULL, create_node1, 0);
		Parser_InsertRuleByStr(gmr, L"E : - E", L"UMINUS", create_node2, 0);
		
		{
				arString_t		*str;

				str = AR_CreateString();
				Parser_PrintGrammar(gmr, str);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		}

		Parser_DestroyGrammar(gmr);

		/*
		gmr2 = Parser_CopyNewGrammar(gmr);

		Parser_DestroyGrammar(gmr);
		Parser_DestroyGrammar(gmr2);
		*/

}








AR_NAMESPACE_END

#endif

#endif



