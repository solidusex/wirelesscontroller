
#if defined(__LIB)

#include <vector>

#include "test.h"
#include "../Arsenal/Lex/lex.h"
#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Parser/lr_action.h"




AR_NAMESPACE_BEGIN



#include "gen_code_impl.h"

#if(0)

/*******************************************decl****************************************/

struct __parser_node_tag;
typedef struct __parser_node_tag		parserNode_t;


/********************************************************************************************/

typedef enum
{
		TOKEN_T,
}parserNodeType_t;

struct __parser_node_tag
{
		parserNodeType_t		type;

};

static parserNode_t*			TGU_CreateParserNode(parserNodeType_t	type)		;
static void				TGU_DestroyParserNode(parserNode_t	*node)	;

/**************************************************************************************************/










/**********************************************************************************************************************************/




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


void gen_code_test()
{
		uint_64_t sum = 0;
		std::vector<lex_t*>				vl;
		std::vector<psrGrammar_t*>		vg;
		std::vector<const parser_t*>			vp;
		for(int i = 0; i < 10; ++i)
		{
				getchar();
				psrGrammar_t	*gmr;
				uint_64_t		beg, end;
				beg = AR_GetTime_Milliseconds();
				lex_t *lex = __build_lex();
				gmr = __build_grammar(&__g_handler);

				const parser_t		*parser = Parser_CreateParser(gmr, PARSER_LALR);
				end = AR_GetTime_Milliseconds();
				sum += (end - beg);
				AR_printf(L"%ls : tickcount == %qd\r\n", L"parser build successful", end - beg);
				//getchar();

				vl.push_back(lex);
				vg.push_back(gmr);
				vp.push_back(parser);
				/*
				Parser_DestroyParser(parser);
				Lex_Destroy(lex);
				Parser_DestroyGrammar(gmr);
				*/


				AR_printf(L"%ls\r\n", L"after parser release\r\n");
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
}

#endif

AR_NAMESPACE_END


#endif
