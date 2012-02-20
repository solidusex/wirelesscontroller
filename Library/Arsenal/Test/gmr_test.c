#include "../Arsenal/Parser/parser.h"


#if defined(__LIB)


AR_NAMESPACE_BEGIN

#if(0)



static wchar_t *rule_pattern =
L"%token{\r\n"

L"	Lex_DEF : 500, Lex_LINE : 501,\r\n"
L"	TOK_DEF : 601, PREC_DEF : 602, RULE_DEF : 603,\r\n"
L"	LEXEME : 604, NUMBER : 605,  ASSOC_DECL : 606,\r\n"
L"	\".\" : 607, \"=\" : 608,  \"->\" : 609, \":\" : 610, \"|\" : 611, \",\" : 612, \";\" : 613,\r\n"
L"	\"{\" : 614, \"}\" : 615,\r\n"
L"	\"+\" : 616, \"-\" : 617,\r\n"
L"	\"*\" : 618, \"/\" : 619, \"%\" : 620 ;\r\n"
L"}\r\n"

L"%prec {\r\n"
L"%left \"+\", \"-\";\r\n"
L"%left \"*\", \"/\", \"%\";\r\n"
L"%right \"UMINUS\";\r\n"
L"%noassoc \"UMINUS2\";\r\n"
L"}\r\n"

L"%rules{\r\n"

L"	arsenal_rule		-> 	token_rule  prec_rule rules_rule;\r\n"

L"	token_rule 			-> 	TOK_DEF \"{\" token_decl_list \";\" \"}\";\r\n"
L"	token_decl_list 	->	token_decl_list \",\" token_decl | token_decl;\r\n"
L"	token_decl			->	LEXEME \":\" NUMBER;\r\n"

L"	prec_rule			->	PREC_DEF \"{\" prec_decl_list \"}\" | .;\r\n"
L"	prec_decl_list		->	prec_decl_list  prec_decl \";\" |  prec_decl \";\"; \r\n"
L"	prec_decl			->	ASSOC_DECL prec_token_list;\r\n"
L"	prec_token_list		->	prec_token_list  \",\"  LEXEME |  LEXEME;\r\n"
	
L"	rules_rule			->	RULE_DEF  \"{\" rule_decl_list \";\" \"}\";\r\n"
L"	rule_decl_list		->	rule_decl_list  \";\" rule_decl | rule_decl ;\r\n"
L"	rule_decl			->	LEXEME \"->\" rule_list %prec UMINUS2;\r\n"
L"	rule_list			->	rule_list \"|\" rule | rule;\r\n"
L"	rule				->	rule LEXEME | LEXEME | \".\";\r\n"
L"	test				->	rule %prec UMINUS | . %prec UMINUS;\r\n"
L"}\r\n"
;



static const wchar_t *rule_pattern2 = 
L"  %token{\r\n"
L"'(' : 300, ')' : 301, '+' : 302, '-' : 303, '*' : 304, '/' : 305, '%' : 306,"
L"number : 400,"
L"id : 401;"
L"}\r\n"

L"%prec{\r\n"
L"%left	';';"
L"%left '+', '-';"
L"%left '*', '/';"
L"%right UMINUS;"
L"}\r\n"

L"%rules{\r\n"
L"E -> E '+' E | E '-' E | E '*' E | E '/' E | '('E')' | '-' E %prec UMINUS| number ;"
L"}\r\n"
;


const wchar_t *lex_test_pat =
L"%lex{\r\n"
L"	delim		= 	[\\t\\r\\n ]*\r\n"
L"	letter 		= 	[A-Z_a-z]\r\n"
L"	digit		=	[0-9]\r\n"
L"	number		=	0|[1-9]{digit}*\r\n"
L"	name		=	{letter}({letter}|{digit})*\r\n"
L"	lexeme		=	{name}|('[^']+')|(\\\"[^\\\"]+\\\")\r\n"
L"	comment		= 	\\/\\*([^\\*]|\\*+[^\\*\\/])*\\*+\\/\r\n"
L"	comment_line	= 	\\/\\/[^\\n]*\\n\r\n"

L"	0					[\\0]\r\n"
L"%skip	1				{delim}|{comment_line}|{comment}\r\n"

L"	300,1				\"(\"\r\n"
L"	301,1				\")\"\r\n"
L"	302,1				\"+\"\r\n"
L"	303,1				\"-\"\r\n"
L"	304,1				\"*\"\r\n"
L"	305,1				\"/\"\r\n"
L"	306,1				\"%\"\r\n"

L"	400,1				{number}\r\n"
L"	401,1				{name}\r\n"
L"}"
;




const wchar_t *lex_test_pat2 =
L"%lex{\r\n"
L"¡¡¡¡·Ö¸î		= 	[\\t\\r\\n ]*\r\n"
L"	letter 		= 	[A-Z_a-z]\r\n"
L"	digit		=	[0-9]\r\n"
L"	number		=	0|[1-9]{digit}*\r\n"
L"	name		=	{letter}({letter}|{digit})*\r\n"
L"	lexeme		=	{name}|('[^']+')|(\\\"[^\\\"]+\\\")\r\n"
L"	×¢ÊÍ		= 	\\/\\*([^\\*]|\\*+[^\\*\\/])*\\*+\\/\r\n"
L"	comment_line	= 	\\/\\/[^\\n]*\\n\r\n"

L"	0					[\\0]\r\n"
L"%skip	1¡¡¡¡¡¡¡¡¡¡{¡¡¡¡·Ö¸î¡¡¡¡}|{comment_line}|{¡¡¡¡×¢ÊÍ¡¡¡¡}\r\n"

L"	300,1				\"(\"\r\n"
L"	301,1				\")\"\r\n"
L"	302,1				\"+\"\r\n"
L"	303,1				\"-\"\r\n"
L"	304,1				\"*\"\r\n"
L"	305,1				\"/\"\r\n"
L"	306,1				\"%\"\r\n"

L"	400,1				{number}\r\n"
L"	401,1				{name}\r\n"
L"}"
;


static const wchar_t *rule_pattern3 = 
L"  %token{\r\n"
L"'(' : 300, ')' : 301, '+' : 302, '-' : 303, '*' : 304, '/' : 305, '%' : 306,"
L"number : 400,"
L"id : 401;"
L"}\r\n"

L"%prec{\r\n"
L"%left	';';"
L"%left '+', '-';"
L"%left '*', '/';"
L"%right UMINUS;"
L"}\r\n"

L"%rules{\r\n"
L"A -> B | C |A;"
L"B -> number;"
L"C -> number | D;"
L"D -> number | A;"
L"}\r\n"
;


void pcg_test2()
{
		psrGrammar_t *gmr;
		arString_t *str;

		gmr = Parser_CreateGrammar();
		str = AR_CreateString();

		//lex = Lex_Create();
		//AR_ASSERT(Lex_Config(lex, lex_test_pat2));

		if(Parser_ConfigGrammar(gmr, rule_pattern3))
		{
				Parser_PrintGrammar(gmr, str);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));
				AR_ClearString(str);
		}
		AR_printf(L"\r\n");
		AR_ClearString(str);
		//if(Parser_ReportLeftRecursion(gmr,str))
		if(Parser_ReportLeftRecursion(gmr,NULL))
		{
				AR_printf(L"Recursion:\r\n%ls\r\n", AR_GetStringCString(str));
		}
}


void pcg_test()
{
		lex_t *lex;
		parser_t		*psr;
		psrGrammar_t *gmr;
		arString_t *str;
		
		lex = NULL;
		psr = NULL;
		gmr = Parser_CreateGrammar();
		str = AR_CreateString();

		lex = Lex_Create();
		AR_ASSERT(Lex_Config(lex, lex_test_pat2));

		if(Parser_ConfigGrammar(gmr, rule_pattern))
		{
				Parser_PrintGrammar(gmr, str);
				AR_printf(L"%ls\r\n", AR_GetStringCString(str));
				AR_ClearString(str);
		}

		psr = Parser_CreateParser(gmr, Parser_LR1, Parser_GetPrintNodeContext());
		AR_ASSERT(psr != NULL);
#if(0)
		getchar();


		{
				lexToken_t tok; lexMatch_t	match;
				Lex_InitMatch(&match, L"3 + 4 * (78 + 5)");

				while(Lex_Match(lex, &match, &tok))
				{
						if(!Parser_AddToken(psr, &tok))
						{
								AR_ASSERT(false);
						}
						if(tok.type == 0)break;
				}
		}
		
		{
				printNode_t		*root = (printNode_t*)Parser_GetResult(psr);
				AR_printf(L"%ls\r\n", root->name);
		}
#endif

		Parser_DestroyGrammar(gmr);
		AR_DestroyString(str);

}		






#endif

















AR_NAMESPACE_END


#endif
