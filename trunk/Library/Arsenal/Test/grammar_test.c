#include "test.h"

#include "../Arsenal/Common/common.h"
#include "../Arsenal/Lex/lex.h"
#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Parser/lr_action.h"






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

static  psrRetVal_t		AR_STDCALL create_leaf(const psrToken_t *tok,void *ctx)
{
		psrRetVal_t ret = {AR_S_YES, NULL};

		Token_t	op;
		op.type = (TokenType_t)tok->term_val;
		op.str = AR_wcsndup(tok->str, tok->str_cnt);
		ret.node =  (psrNode_t*)CreateNode(&op, NULL, NULL);
		return ret;
}



/*
E : E + E
E : E - E
E : E * E
E : E / E
E : E % E
*/

static  psrRetVal_t		AR_STDCALL create_node(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		
		Node_t *op_node;
		psrRetVal_t ret = {AR_S_YES, NULL};
		
		op_node = (Node_t*)nodes[1];
		switch(op_node->op.type)
		{
		case ADD:
		case MINUS:
		case MUL:
		case DIV:
		case MOD:
				ret.node =  (psrNode_t*)CreateNode(&op_node->op, (Node_t*)nodes[0], (Node_t*)nodes[2]);
				return ret;
		default:
				AR_ASSERT(false);
				return ret;
				break;
		}
}

/*
E : number
E : ( E )
*/

static  psrRetVal_t		AR_STDCALL create_node1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		psrRetVal_t ret = {AR_S_YES, NULL};

		AR_ASSERT(count == 1 || count == 3);
		if(count == 1)
		{
				ret.node =  nodes[0];
		}else
		{
				ret.node =  nodes[1];
		}

		return ret;
}

/*
		E : - E
*/


static  psrRetVal_t		AR_STDCALL create_node2(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		psrRetVal_t ret = {AR_S_YES, NULL};
		AR_ASSERT(count == 2);
		ret.node =  (psrNode_t*)CreateNode(&((Node_t*)nodes[0])->op, NULL, (Node_t*)nodes[1]);

		return ret;
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


void			AR_STDCALL free_func(psrNode_t *node, void *ctx)
{
		AR_printf(L"on free_func\r\n");

}

arStatus_t		AR_STDCALL err_func(const psrToken_t *tok, const size_t expected[], size_t count, void *ctx)
{
		AR_printf(L"on err_func\r\n");
		return AR_S_NO;
}



arStatus_t			Parser_PrintGrammar(const psrGrammar_t *grammar, arString_t *str);


#define CHECK_AND_JMP(_stat)	do{ if((_stat) != AR_S_YES) goto INVALID_POINT;}while(0)
static  psrGrammar_t* __build_grammar()
{
		psrGrammar_t	*gmr;
		arStatus_t status;
		psrHandler_t	handler = {err_func, free_func }; 
		

		gmr = Parser_CreateGrammar(&handler);
	
		if(gmr == NULL)
		{
				goto INVALID_POINT;
		}


		status = Parser_InsertTerm(gmr, L"(", CLP, PARSER_ASSOC_NONASSOC, 0, create_leaf);

		CHECK_AND_JMP(status);

		status = Parser_InsertTerm(gmr, L")", RP, PARSER_ASSOC_NONASSOC, 0, create_leaf);

		CHECK_AND_JMP(status);


		status = Parser_InsertTerm(gmr, L"+", ADD, PARSER_ASSOC_LEFT, 1, create_leaf);

		CHECK_AND_JMP(status);
		
		status = Parser_InsertTerm(gmr, L"-", MINUS, PARSER_ASSOC_LEFT, 1, create_leaf);
		
		CHECK_AND_JMP(status);


		status = Parser_InsertTerm(gmr, L"*", MUL, PARSER_ASSOC_LEFT, 2, create_leaf);
		CHECK_AND_JMP(status);


		status = Parser_InsertTerm(gmr, L"/", DIV, PARSER_ASSOC_LEFT, 2, create_leaf);

		CHECK_AND_JMP(status);

		status = Parser_InsertTerm(gmr, L"%", MOD, PARSER_ASSOC_LEFT, 2, create_leaf);

		CHECK_AND_JMP(status);

		status = Parser_InsertTerm(gmr, L"number", NUMBER, PARSER_ASSOC_NONASSOC, 0, create_leaf);

		CHECK_AND_JMP(status);

		status = Parser_InsertTerm(gmr, L"UMINUS", 0xFFFF, PARSER_ASSOC_RIGHT, 3, create_leaf);

		CHECK_AND_JMP(status);

		status = Parser_InsertRuleByStr(gmr, L"E : E + E", NULL, create_node, 0);

		CHECK_AND_JMP(status);

		
		status =  Parser_InsertRuleByStr(gmr, L"E : E - E", NULL, create_node, 0);
		CHECK_AND_JMP(status);

		status = Parser_InsertRuleByStr(gmr, L"E : E * E", NULL, create_node, 0);
		CHECK_AND_JMP(status);

		status = Parser_InsertRuleByStr(gmr, L"E : E / E", NULL, create_node, 0);
		CHECK_AND_JMP(status);

		status = Parser_InsertRuleByStr(gmr, L"E : E % E", NULL, create_node, 0);
		CHECK_AND_JMP(status);

		status = Parser_InsertRuleByStr(gmr, L"E : ( E )", NULL, create_node1, 0);
		CHECK_AND_JMP(status);


		status = Parser_InsertRuleByStr(gmr, L"E : - E", L"UMINUS", create_node2, 0);
		CHECK_AND_JMP(status);


		status = Parser_InsertRuleByStr(gmr, L"E : number", NULL, create_node1, 0);
		CHECK_AND_JMP(status);

		///////////////////////////////////////////////////////////////////////////////
		/*
		status = Parser_InsertRuleByStr(gmr, L"X : Y", NULL, NULL, 0);//error
		CHECK_AND_JMP(status);

		status = Parser_InsertRuleByStr(gmr, L"X : ", NULL, NULL, 0);//wanrning
		CHECK_AND_JMP(status);
		*/
		
		//Parser_InsertRuleByStr(gmr, L"E : X number", NULL, create_node1, 0);
		//Parser_InsertRuleByStr(gmr, L"E : Y number", NULL, create_node1, 0);

		
		/*
		Parser_InsertRuleByStr(gmr, L"E : ", NULL, NULL, 0);
		Parser_InsertRuleByStr(gmr, L"X : ", NULL, NULL, 0);
		Parser_InsertRuleByStr(gmr, L"Y : ", NULL, NULL, 0);
		*/
		
		{
				arString_t *str = AR_CreateString();
				Parser_PrintGrammar(gmr, str);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));
				AR_DestroyString(str);
				str = NULL;
		}

		status = Parser_CheckIsValidGrammar(gmr, AR_global_ioctx());
		CHECK_AND_JMP(status);


		return gmr;

INVALID_POINT:
		if(gmr)
		{
				Parser_DestroyGrammar(gmr);
				gmr = NULL;
		}

		return NULL;
}







 


void parser_test_lalr(const psrGrammar_t *gmr)
{
		arString_t *str;
		psrStatusView_t	*view;
		const parser_t *parser;
		AR_ASSERT(gmr != NULL);

		str = AR_CreateString();

		parser = Parser_CreateParser(gmr, PARSER_LALR);

		if(parser)
		{
				Parser_PrintParserActionTable(parser, str, 20);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));

				AR_ClearString(str);
				Parser_PrintParserConflict(parser, str);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		
		
		
				const psrActionView_t *act_view = Parser_CreateParserActionView(parser);

				if(act_view)
				{
						Parser_DestroyParserActionView(act_view);
						act_view = NULL;
				}



				const psrConflictView_t *conf_view = Parser_CreateParserConflictView(parser);

				if(conf_view)
				{
						Parser_DestroyParserConflictView(conf_view);
						conf_view = NULL;
				}


				const psrStatusView_t			*status_view = Parser_CreateParserStatusView(parser);



				if(status_view)
				{
						Parser_DestroyParserStatusView(status_view);
						status_view = NULL;
				}
		
		}



		if(parser != NULL)
		{
				Parser_DestroyParser(parser);
				parser = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

}






void grammar_test()
{
		
		psrGrammar_t	*gmr;
		psrSymbMap_t	first, follow;
		size_t i,k;
		bool_t is_ok;
		arString_t		*str;

		str = AR_CreateString();

		Parser_InitSymbMap(&first);
		Parser_InitSymbMap(&follow);

		gmr = __build_grammar();

		if(gmr == NULL)
		{
				Parser_UnInitSymbMap(&first);
				Parser_UnInitSymbMap(&follow);
		}else
		{
				arStatus_t status;
				
				status = Parser_CalcFirstSet(gmr, &first);
				CHECK_AND_JMP(status);

				AR_ClearString(str);
				status = Parser_PrintSymbolMap(&first, str);
				CHECK_AND_JMP(status);
				AR_printf(L"First Set:\r\n%ls\r\n", AR_GetStringCString(str));


				status = Parser_CalcFollowSet(gmr, &follow, &first);
				CHECK_AND_JMP(status);

				AR_ClearString(str);
				status = Parser_PrintSymbolMap(&follow, str);
				CHECK_AND_JMP(status);
				AR_printf(L"Follow Set:\r\n%ls\r\n", AR_GetStringCString(str));


				parser_test_lalr(gmr);


INVALID_POINT:
				if(gmr)
				{
						Parser_DestroyGrammar(gmr);
						gmr = NULL;
				}
				Parser_UnInitSymbMap(&first);
				Parser_UnInitSymbMap(&follow);
		}


		if(str)
		{
				AR_DestroyString(str);
		}
}





AR_NAMESPACE_END




#endif

