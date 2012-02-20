#include "test.h"

#if(0)
#include "../Arsenal/Parser/parser_in.h"
#include "../Arsenal/Parser/symbol.h"
#include "../Arsenal/Parser/grammar.h"
#include "../Arsenal/Parser/lr_item.h"
#include "../Arsenal/Parser/lr_dfa.h"
#include "../Arsenal/Parser/lr_action.h"


#if defined(__LIB)


AR_NAMESPACE_BEGIN


#if(0)

void str_tbl_test()
{
		const wchar_t *l, *r;
		const psrSymb_t	*tmp;

		l = Parser_AllocString( L"abcdef");
		r = Parser_AllocString( L"abcdef");
		AR_ASSERT(l == r);


		l = Parser_AllocString( L"abcdef");
		r = Parser_AllocString( L"abcdef2");

		AR_ASSERT(l != r);


		AR_ASSERT(Parser_CompSymb(Parser_EpsilonSymb, Parser_EpsilonSymb) == 0);
		AR_ASSERT(Parser_CompSymb(Parser_EpsilonSymb, PARSER_EOISymb) != 0);
		AR_ASSERT(Parser_CompSymb(Parser_EpsilonSymb, PARSER_StartSymb) != 0);
		AR_ASSERT(Parser_CompSymb(PARSER_StartSymb, PARSER_StartSymb) == 0);

		tmp = Parser_CreateSymb(L"%Start", PARSER_NONTERM);

		AR_ASSERT(Parser_CompSymb(tmp, PARSER_StartSymb) == 0);

		AR_printf(L"%ls\r\n", Parser_AllocStringInt(33, 10));
		AR_printf(L"%ls\r\n", Parser_AllocStringInt(-33, 10));

		AR_printf(L"%ls\r\n", Parser_AllocStringInt(0x01AF, 16));
		AR_printf(L"%ls\r\n", Parser_AllocStringInt(-0x02AF, 16));
/*
		AR_printf(L"%ls\r\n", Parser_AllocStringUInt(33, 10));
		AR_printf(L"%ls\r\n", Parser_AllocStringUInt(88, 10));

		AR_printf(L"%ls\r\n", Parser_AllocStringUInt(33, 8));
		AR_printf(L"%ls\r\n", Parser_AllocStringUInt(88, 8));

		AR_printf(L"%ls\r\n", Parser_AllocStringUInt(33, 16));
		AR_printf(L"%ls\r\n", Parser_AllocStringUInt(88, 16));
		*/
}

psrNode_t*		AR_STDCALL leaf_func(const psrToken_t *tok,void *ctx)
{
		return NULL;

}

psrNode_t*		AR_STDCALL rule_func(psrNode_t **nodes, size_t count, void *ctx)
{
		return NULL;
}







typedef struct __token_tag
{
		const wchar_t *token;
		size_t			val;
		size_t			prec;
		psrAssocType_t	assoc;
}token_test_t;

typedef struct __rule_tag
{
		const wchar_t	*rule;
		const wchar_t	*prec;
}rule_test_t;


/****************************************************************************************/


token_test_t tokens[] = 
{
		{L"(", 354, 0, PARSER_ASSOC_NONASSOC},
		{L")", 355, 0, PARSER_ASSOC_NONASSOC},
		{L"+", 356, 0, PARSER_ASSOC_NONASSOC},
		{L"-", 357, 0, PARSER_ASSOC_NONASSOC},
		{L"*", 358, 0, PARSER_ASSOC_NONASSOC},
		{L"/", 359, 0, PARSER_ASSOC_NONASSOC},
		{L"%", 360, 0, PARSER_ASSOC_NONASSOC},
		{L"number", 361, 0, PARSER_ASSOC_NONASSOC},
		{L";",		362, 0, PARSER_ASSOC_NONASSOC},
		{L"UMINUS", 0xFFFF, 0, PARSER_ASSOC_NONASSOC}
};



rule_test_t rules[] = 
{
		{L"E : E + E", NULL},
		{L"E : E - E", NULL},
		{L"E : E * E", NULL},
		{L"E : E / E", NULL},
		{L"E : number", NULL},
		{L"E : - E", L"UMINUS"},
		{L"E : ( E )", NULL}
};

token_test_t tokens1[] = 
{
		{L"id", 300, 0, PARSER_ASSOC_NONASSOC},
		{L"n",	400, 0, PARSER_ASSOC_NONASSOC},
		{L":=", 500, 0, PARSER_ASSOC_NONASSOC}
};


rule_test_t rules1[] = 
{
		{L"S : id", NULL},
		{L"S : V := E", NULL},
		{L"V : id", NULL},
		{L"E : V", NULL},
		{L"E : n", NULL}
};


token_test_t tokens2[] = 
{
		{L"(", 300, 0, PARSER_ASSOC_NONASSOC},
		{L")",	301, 0, PARSER_ASSOC_NONASSOC},
		{L"++", 303, 0, PARSER_ASSOC_NONASSOC}
};


rule_test_t rules2[] = 
{
		{L"S : ( S ) S", NULL},
		{L"S : ", NULL}
};




token_test_t tokens3[] = 
{
		{L"n", 300, 0, PARSER_ASSOC_NONASSOC},
		{L"id",	301, 0, PARSER_ASSOC_NONASSOC},
		{L"=", 400, 0, PARSER_ASSOC_NONASSOC},
		{L"*", 401, 0, PARSER_ASSOC_NONASSOC}
};


rule_test_t rules3[] = 
{
		{L"S : L = R", NULL},
		{L"S : R", NULL},
		{L"L : * R", NULL},
		{L"L : id", NULL},
		{L"R : L", NULL}
};



/************************************************************************************************************/

void			AR_STDCALL on_free_test(psrNode_t *node, void *ctx)
{
		printf("free\r\n");
}

void		AR_STDCALL 	on_error_test(const psrToken_t *tok, const wchar_t *expected[], size_t count, void *ctx)
{
		AR_printf(L"on error\r\n");

}



static arString_t		*str;

static void printf_str()
{
		AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		AR_ClearString(str);
}

DWORD beg, end;
void grammar_test2()
{
		psrGrammar_t *gmr;
		size_t i;
		gmr = Parser_CreateGrammar(NULL);
		
		Parser_ClearGrammar(gmr);

		str = AR_CreateString();

		
		for(i = 0; i < sizeof(tokens) / sizeof(tokens[0]); ++i)
		{
				AR_ASSERT(Parser_InsertTerm(gmr,tokens[i].token, tokens[i].val, tokens[i].assoc, tokens[i].prec, NULL));
		}
		
		for(i = 0; i < sizeof(rules)/sizeof(rules[0]); ++i)
		{
				AR_ASSERT(Parser_InsertRuleByStr(gmr, rules[i].rule, rules[i].prec, NULL));

				
		}

		Parser_PrintGrammar(gmr, str);
		AR_ASSERT(Parser_CheckIsValidGrammar(gmr));

		printf_str();


		getchar();

		{		
				psrSymbMap_t first_map, follow_map;
				
				Parser_InitSymbMap(&first_map);
				Parser_InitSymbMap(&follow_map);
				
				Parser_CalcFirstSet(gmr, &first_map);
				Parser_PrintSymbolMap(&first_map, str);
				printf_str();
				printf("-----------------------------------\r\n");

				Parser_CalcFollowSet(gmr, &follow_map, &first_map);
				Parser_PrintSymbolMap(&follow_map, str);
				printf_str();
				printf("-----------------------------------\r\n");


				Parser_UnInitSymbMap(&first_map);
				Parser_UnInitSymbMap(&follow_map);
		}

		getchar();


		{
				
				size_t k;
				psrDFA_t		*dfa;
				psrDFASet_t		set;
				Parser_InitDFASet(&set);
				
				beg = GetTickCount();
				//dfa = Parser_Build_LR0_DFA(&gmr);
				//dfa = Parser_Build_LR1_DFA(&gmr);
				dfa = Parser_Build_LALR_DFA(gmr);
				end = GetTickCount();

				printf("elipsed == %d\r\n", end - beg);

				Parser_CollectDFA(&set, dfa);

				for(k = 0; k < set.count; ++k)
				{
						AR_AppendFormatString(str, L"I[%d] : \r\n",k);
						Parser_PrintLRItemTable(&set.set[k]->tbl, gmr, str);
						AR_AppendFormatString(str, L"-----------------------------\r\n");

				}
				getchar();
				printf_str();
				Parser_DestroyDFA_ALL(dfa);
				Parser_UnInitDFASet(&set);

		}
		getchar();
		
		{
				psrActionTable_t *tbl;	
				beg = GetTickCount();

				//tbl = Parser_CreateActionTable_SLR(&gmr);
				
				//tbl = Parser_CreateActionTable_LR1(&gmr);
				tbl = Parser_CreateActionTable_LALR(gmr);
				end = GetTickCount();
				printf("elipsed == %d\r\n", end - beg);
				getchar();

				Parser_PrintActionTable(tbl, gmr,18,str);
				printf_str();
				getchar();

				Parser_ReportConflict(tbl, gmr, str);
				printf_str();
				getchar();
				
				Parser_DestroyActionTable(tbl);
		}
		
		getchar();

		{
				parser_t		*psr;
				psrCtx_t		user = {on_free_test,  NULL};

				psr = Parser_CreateParser(gmr, PARSER_LALR, &user);


				Parser_DestroyParser(psr);
				

		}
		
		
}













psrNode_t*		AR_STDCALL create_leaf(const psrToken_t *tok,void *ctx)
{
		printf("shift\r\n");
		return (psrNode_t*)(uint_t)1;
}

psrNode_t*		AR_STDCALL create_node(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		AR_printf(L"reduce count == %d\r\n", count);
		return (psrNode_t*)(uint_t)2;
}


psrNode_t*		AR_STDCALL reduce_epsilon_node(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		AR_ASSERT(count == 0);
		printf("reduce to S\r\n");
		return NULL;
}

void			AR_STDCALL free_node(psrNode_t *node, void *ctx)
{
		printf("on_free\r\n");

}

void			AR_STDCALL on_error(const psrToken_t *tok, const wchar_t *expected[], size_t count, void *ctx)

{
		printf("on_error\r\n");

}


static void print_str()
{
		AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		AR_ClearString(str);
}


void calc_test1()
{
		
		psrGrammar_t *gmr;
		parser_t	 *psr;
		str = AR_CreateString();
		
		gmr = Parser_CreateGrammar(NULL);
		
		Parser_InsertTerm(gmr, L"(", 300, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		Parser_InsertTerm(gmr, L")", 301, PARSER_ASSOC_NONASSOC, 0, create_leaf);
		

		Parser_InsertRuleByStr(gmr, L"S : ( S ) S", NULL, create_node);
		Parser_InsertRuleByStr(gmr, L"S : ", NULL, reduce_epsilon_node);


		Parser_PrintGrammar(gmr, str);
		print_str();
		
		
		{
				psrCtx_t ctx = { free_node, NULL};
				psr = Parser_CreateParser(gmr, PARSER_LALR, &ctx);
				AR_ASSERT(psr);

				Parser_ReportConflict(psr->tbl, gmr, str);
				print_str();
				getchar();
				
				{
				psrToken_t tok;
				psrNode_t *node;
				const wchar_t *input = L"((()))()()";
				wchar_t buf[1024];
				
				size_t i;
				for(i = 0; i < AR_wcslen(input); ++i)
				{
						wchar_t c = input[i];
						buf[0] = c;
						buf[1] = L'\0';
						tok.type = (c == L'(' ? 300 : 301);
						tok.str = buf;
						tok.line = 0;
						tok.col = i;
						
						if(!Parser_AddToken(psr, &tok))
						{
								printf("error\r\n");
								assert(0);
						}
						
						getchar();
				}
				
				tok.type = 0;
				tok.str = L"";


				if(!Parser_AddToken(psr, &tok))
				{
						printf("error\r\n");
						assert(0);
				}
				
				if(Parser_IsAccepted(psr))
				{
						printf("success\r\n");
				}

				node = Parser_GetResult(psr);

				}
		}

		getchar();
}














#endif










AR_NAMESPACE_END


#endif


#endif
