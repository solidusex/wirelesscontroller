
#include "test.h"
#include <vector>
#include "../Arsenal/Lex/lex.h"
#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Parser/lr_action.h"


AR_NAMESPACE_BEGIN

#if(0)

#pragma warning(disable : 4100)
#include "parser_gen_perf_javascript_code_impl.h"
#include "parser_gen_perf_sql_code_impl.h"

static void		AR_STDCALL handle_free_node(psrNode_t *node, void *ctx)
{
		AR_ASSERT(node != NULL);
}

static bool_t		AR_STDCALL handle_on_error(const psrToken_t *tok, const size_t expected[], size_t count, void *ctx)
{
		AR_ASSERT(ctx != NULL && tok != NULL);
		
		AR_ASSERT(false);

		return true;
}

static const psrHandler_t		__g_handler = 
{
		handle_on_error,
		handle_free_node
};


static void javascript_grammar_test()
{		

		AR_printf(L"begin javascript_grammar_test\r\n");
		uint_64_t sum = 0;
		std::vector<lex_t*>				vl;
		std::vector<psrGrammar_t*>		vg;
		std::vector<const parser_t*>	vp;

		for(int i = 0; i < 10; ++i)
		{
				psrGrammar_t	*gmr;
				uint_64_t		beg, end;
				beg = AR_GetTime_Milliseconds();
				lex_t *lex = __javascript_build_lex();
				gmr = __javascript_build_grammar(&__g_handler);

				const parser_t		*parser = Parser_CreateParser(gmr, PARSER_LALR);
				end = AR_GetTime_Milliseconds();
				sum += (end - beg);
				AR_printf(L"%ls : tickcount == %qd\r\n", L"parser build successful", end - beg);

				vl.push_back(lex);
				vg.push_back(gmr);
				vp.push_back(parser);
				
				AR_printf(L"-------------------------------\r\n");
				
		}
		
		AR_printf(L"average time == %qd\r\n", sum / 10);
		AR_printf(L"-------------------------------\r\n");


		for(int i = 0; i < vl.size(); ++i)
		{

				Parser_DestroyParser(vp[i]);
				Parser_DestroyGrammar(vg[i]);
				Lex_Destroy(vl[i]);
		}
		
		AR_printf(L"end javascript_grammar_test\r\n");
}




static void sql_grammar_test()
{		

		AR_printf(L"begin sql_grammar_test\r\n");
		uint_64_t sum = 0;
		std::vector<lex_t*>				vl;
		std::vector<psrGrammar_t*>		vg;
		std::vector<const parser_t*>	vp;

		for(int i = 0; i < 10; ++i)
		{
				psrGrammar_t	*gmr;
				uint_64_t		beg, end;
				beg = AR_GetTime_Milliseconds();
				lex_t *lex = __sql_build_lex();
				gmr = __sql_build_grammar(&__g_handler);

				const parser_t		*parser = Parser_CreateParser(gmr, PARSER_LALR);
				end = AR_GetTime_Milliseconds();
				sum += (end - beg);
				AR_printf(L"%ls : tickcount == %qd\r\n", L"parser build successful", end - beg);

				vl.push_back(lex);
				vg.push_back(gmr);
				vp.push_back(parser);
				
				AR_printf(L"-------------------------------\r\n");
				
		}
		
		AR_printf(L"average time == %qd\r\n", sum / 10);
		AR_printf(L"-------------------------------\r\n");


		for(int i = 0; i < vl.size(); ++i)
		{

				Parser_DestroyParser(vp[i]);
				Parser_DestroyGrammar(vg[i]);
				Lex_Destroy(vl[i]);
		}
		
		AR_printf(L"end sql_grammar_test\r\n");
}


void parser_gen_perf_test()
{
		
		javascript_grammar_test();
		sql_grammar_test();
}


#endif

AR_NAMESPACE_END