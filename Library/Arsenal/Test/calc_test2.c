

#if defined(__LIB)

#include "../Arsenal/Common/common.h"
#include "../Arsenal/Lex/lex.h"
#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Parser/lr_action.h"


AR_NAMESPACE_BEGIN

#if(0)

static const wchar_t *__g_lex_name[] = {
L"delim = [ \\r\\n\\t]",
L"comment = /\\*([^\\*]|\\*+[^\\*/])*\\*+/",
L"comment_line = //[^\\n]*\\n",
L"digit = [0-9]",
L"number = {digit}+"
};

#define __NAME_COUNT__ ((size_t)5)



enum
{
		OP_EOI = 0,
		OP_NUM = 300,
		OP_ADD,
		OP_MINUS,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_LP,
		OP_RP
};




static struct {const wchar_t *name; size_t tokval; size_t lex_prec; const wchar_t *regex; bool_t skip; }__g_term_pattern[] =  {
{NULL, 257,1, L"{delim}+|{comment}+|{comment_line}+", true},
{L"NUM", OP_NUM, 0, L"{number}", false},
{L"+", OP_ADD, 0, L"\"+\"", false},
{L"-", OP_MINUS, 0, L"\"-\"", false},
{L"*", OP_MUL, 0, L"\"*\"", false},
{L"/", OP_DIV, 0, L"\"/\"", false},
{L"(", OP_LP, 0, L"\"(\"", false},
{L")", OP_RP, 0, L"\")\"", false},
{L"%", OP_MOD, 0, L"\"%\"", false},
{L"EOI", OP_EOI, 2, L"$", false}
};

#define __TERM_COUNT__ ((size_t)10)

static struct {const wchar_t *name; size_t tokval; size_t prec_level; psrAssocType_t	assoc;}__g_prec_pattern[] =  {
{L"+", OP_ADD,1, PARSER_ASSOC_LEFT},
{L"-", OP_MINUS,1, PARSER_ASSOC_LEFT},
{L"*", OP_MUL,2, PARSER_ASSOC_LEFT},
{L"/", OP_DIV,2, PARSER_ASSOC_LEFT},
{L"%", OP_MOD,2, PARSER_ASSOC_LEFT},
{L"UMINUS", 267,3, PARSER_ASSOC_RIGHT}
};

#define __PREC_COUNT__ ((size_t)6)

/*E	:	E + E */
/*E	:	E - E */
/*E	:	E * E */
/*E	:	E / E */
/*E	:	E % E */
/*E	:	( E ) */
/*E	:	- E */
/*E	:	NUM */
static psrNode_t* AR_STDCALL handle_E(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

static psrNode_t* AR_STDCALL __build_leaf(const psrToken_t *tok,  void *ctx);


static struct { const wchar_t	*rule; const wchar_t	*prec_token; psrRuleFunc_t	handler; size_t	auto_ret; } __g_rule_pattern[] = {
{L"E  :  E + E ", NULL, handle_E, 0},
{L"E  :  E - E ", NULL, handle_E, 0},
{L"E  :  E * E ", NULL, handle_E, 0},
{L"E  :  E / E ", NULL, handle_E, 0},
{L"E  :  E % E ", NULL, handle_E, 0},
{L"E  :  ( E ) ", NULL, handle_E, 0},
{L"E  :  - E ", L"UMINUS", handle_E, 0},
{L"E  :  NUM ", NULL, handle_E, 0}
};

#define __RULE_COUNT__ ((size_t)8)
#define START_RULE L"E"

static lex_t*	__build_lex(const arIOCtx_t *io)								
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

static psrGrammar_t*	__build_grammar(const psrHandler_t	*handler, const arIOCtx_t *io)										
{																																
		psrGrammar_t	*grammar;																								
		size_t i;																												
		AR_ASSERT(handler != NULL);																								
		grammar = Parser_CreateGrammar(handler);																				
		for(i = 0; i < __TERM_COUNT__; ++i)																						
		{																														
				if(__g_term_pattern[i].skip || __g_term_pattern[i].tokval == 0)continue;										
				if(!Parser_InsertTerm(grammar, __g_term_pattern[i].name, __g_term_pattern[i].tokval, PARSER_ASSOC_NONASSOC,0, __build_leaf))	
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


#if(0)
		psrRule_t	*new_rule = Parser_CreateRuleByStr(L"E : ", NULL, NULL, 0, &grammar->term_list, &grammar->io_ctx);
		const psrSymb_t *symb = Parser_CreateSymb(L"NUM",  PARSER_NONTERM);
		Parser_InsertToSymbList(&new_rule->body, symb);
		if(!Parser_InsertRule(grammar, new_rule))
		{																												
				Parser_DestroyGrammar(grammar);																			
				grammar = NULL;																							
				AR_ASSERT(false);																						
				return NULL;																							
		}
#endif

		
		if(!Parser_SetStartRule(grammar,START_RULE) || !Parser_CheckIsValidGrammar(grammar,NULL))																						
		{																																									
				Parser_DestroyGrammar(grammar);																																
				grammar = NULL;																																				
				AR_ASSERT(false);																																			
				return NULL;																																				
		}																																									
		return grammar;																																						
}






static psrNode_t* AR_STDCALL __build_leaf(const psrToken_t *tok,  void *ctx)
{
		int v;

		if(tok->term_val == OP_NUM)
		{
				if(AR_wtoi32_s(tok->str, tok->str + tok->str_cnt, &v, 10) == NULL)
				{
						AR_ASSERT(false);
				}
		}else
		{
				v = tok->term_val;
		}

		return (psrNode_t*)v;
}

/*E	:	E + E */
/*E	:	E - E */
/*E	:	E * E */
/*E	:	E / E */
/*E	:	E % E */
/*E	:	( E ) */
/*E	:	- E */
/*E	:	NUM */
static psrNode_t* AR_STDCALL handle_E(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		int	*nv = (int*)nodes;
		int res = 0;

		if(count == 3)
		{
				
				if(nv[0] == OP_LP)
				{
						res = nv[1];
						nv[1] = 0;
				}else
				{
						switch(nv[1])
						{
						case OP_ADD:
								res = nv[0] + nv[2];
								break;
						case OP_MINUS:
								res = nv[0] - nv[2];
								break;
						case OP_MUL:
								res = nv[0] * nv[2];
								break;
						case OP_DIV:
								if(nv[2] == 0)
								{
										AR_printf(L"Div by 0\r\n");
										res = 0;
								}else
								{
										res = nv[0] / nv[2];
								}
								break;
						case OP_MOD:
								if(nv[2] == 0)
								{
										AR_printf(L"Mod by 0\r\n");
										res = 0;
								}else
								{
										res = nv[0] % nv[2];
								}
								break;
						default:
								AR_ASSERT(false);
						}
				}
		}else if(count == 2)
		{
				res = nv[1];
				nv[1] = 0;
				res = -res;
		}else if(count == 1)
		{
				res = nv[0];
				nv[0] = 0;
				
		}else
		{
				AR_ASSERT(false);
		}
		
		return (psrNode_t*)res;
}


static void		AR_STDCALL handle_free_node(psrNode_t *node, void *ctx)
{
		AR_ASSERT(node != NULL);
}


/*
enum
{
		OP_EOI = 0,
		OP_NUM = 300,
		OP_ADD,
		OP_MINUS,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_LP,
		OP_RP
};
*/

static bool_t		AR_STDCALL handle_on_error(const psrToken_t *tok, const size_t expected[], size_t count, void *ctx)
{
		AR_ASSERT(tok != NULL);
		
		wchar_t buf[1024];
		if(tok->term_val != OP_EOI)
		{
				AR_wcsncpy(buf, tok->str, tok->str_cnt);
				buf[tok->str_cnt] = 0;
		}else
		{
				AR_wcscpy(buf, L"OP_EOI");
		}
		AR_printf(L"invalid token == %ls  ", buf);

		AR_printf(L"expected : ");
		for(int i = 0; i < count; ++i)
		{
				const wchar_t *msg  = NULL;
				switch(expected[i])
				{
				case OP_EOI:
						msg = L"OP_EOI";
						break;
				case OP_NUM:
						msg = L"OP_NUM";
						break;
				case OP_ADD:
						msg = L"+";
						break;
				case OP_MINUS:
						msg = L"-";
						break;
				case OP_MUL:
						msg = L"*";
						break;
				case OP_DIV:
						msg = L"/";
						break;
				case OP_MOD:
						msg = L"%";
						break;
				case OP_LP:
						msg = L"(";
						break;
				case OP_RP:
						msg = L")";
						break;
				default:
						AR_ASSERT(false);
				}

				AR_printf(L"%ls  ", msg);
		}

		AR_printf(L"\r\n");

		return true;
	
}

static const psrHandler_t		__g_handler = 
{
		handle_on_error,
		handle_free_node
};



static int calc(const wchar_t *input)
{
		lex_t *lex;
		lexMatch_t *match;
		lexToken_t		tok;
		psrGrammar_t	*grammar;
		const parser_t		*parser;
		psrContext_t *ctx;
		bool_t is_ok;
		lex = __build_lex(NULL);
		grammar = __build_grammar(&__g_handler, NULL);
		parser = Parser_CreateParser(grammar, PARSER_SLR);
		ctx = Parser_CreateContext(parser, NULL);


		match = Lex_CreateMatch(lex);

		Lex_ResetInput(match, input);
		
		is_ok = true;
		while(is_ok)
		{
				is_ok = Lex_Match(match, &tok);

				if(!is_ok)
				{
						AR_printf(L"Invalid Token == %ls\r\n", Lex_GetNextInput(match));
						continue;
				}else
				{
						psrToken_t psr_tok;

						PARSER_TOTERMTOK(&tok, &psr_tok);
						
						is_ok = Parser_AddToken(ctx, &psr_tok);
						
						if(is_ok)
						{
								if(psr_tok.term_val == OP_EOI)break;		

						}else
						{
								continue;
						}
				}
		}
		
		int v = 0;
		if(is_ok)
		{
				v = (int)Parser_GetResult(ctx);
		}

		Lex_DestroyMatch(match);
		Lex_Destroy(lex);
		Parser_DestroyContext(ctx);
		Parser_DestroyParser(parser);
		Parser_DestroyGrammar(grammar);
		
		return v;
}


void calc2_test()
{
		wchar_t buf[1024];
		int x;
		while(true)
		{
				_getws(buf);
				if(AR_wcscmp(buf, L"quit") == 0)break;
				x = calc(buf);
				AR_printf(L"result value == %d\r\n", x);
		}
		
}

#endif

AR_NAMESPACE_END



#endif

