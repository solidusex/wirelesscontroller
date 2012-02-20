#include "test.h"

#include "../Arsenal/Common/common.h"
#include "../Arsenal/Lex/lex.h"
#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Parser/lr_action.h"
#include "../Arsenal/Tools/tools.h"





#if defined(__LIB)

AR_NAMESPACE_BEGIN



/*


typedef struct __cfg_report_info_tag
{
		cfgReportType_t			type;
		
		union{
		
		struct					{
				const	wchar_t			*message;
		
		}								std_msg;
		
		struct			{
				const	wchar_t			*msg;
				const	psrToken_t		*tok;
		
		}								lex_error;
		
		struct			{
				const	wchar_t			*msg;
				const	psrToken_t		*tok;
		
		}								syntax_error;

		struct	{
				int_t					err_level;
				const	wchar_t			*err_msg;
		
		}								error;

		struct	{
				size_t					line;
				const wchar_t			*msg;
		}								warning;
		};
}cfgReportInfo_t;




*/



static void AR_STDCALL gmr_collect_report_func(const cfgReportInfo_t *report, void *context)
{
		AR_ASSERT(report != NULL);

		switch(report->type)
		{
		case ARSpace::CFG_REPORT_MESSAGE_T:
				AR_printf(L"%ls\r\n", report->std_msg.message);
				break;
		case ARSpace::CFG_REPORT_ERROR_T:
				AR_printf(L"%ls : %u\r\n", report->error.err_msg, report->error.err_level);
				break;
		case ARSpace::CFG_REPORT_ERROR_LEX_T:
				AR_printf(L"Lex error : %ls\r\n", report->lex_error.msg);
				break;
		case ARSpace::CFG_REPORT_ERROR_SYNTAX_T:
				AR_printf(L"Syntax error : %ls\r\n", report->syntax_error.msg);
				break;
		case	ARSpace::CFG_REPORT_WARNING_SYNTAX_T:
				AR_printf(L"Syntax warning : %ls\r\n", report->warning.msg);
				break;
		default:
				AR_ASSERT(false);
		}

}


/*

typedef struct __cfg_config_tag
{
		
		cfgName_t		*name;
		size_t			name_cnt;

		cfgToken_t		*tok;
		size_t			tok_cnt;

		cfgPrec_t		*prec;
		size_t			prec_cnt;
		
		cfgRule_t		*rule;
		size_t			rule_cnt;

		cfgPreDef_t		*pre_def;
		size_t			predef_cnt;
		
		cfgStart_t		start;

		bool_t			has_error;

		void			*remain_data;
}cfgConfig_t;

*/

static void print_gmr_cfg(const cfgConfig_t		*cfg)
{
		AR_printf(L"Name:------------------------------------------\r\n\r\n");
		for(size_t i = 0; i < cfg->name_cnt; ++i)
		{
				const cfgName_t *name = &cfg->name[i];
				AR_printf(L"%ls : %ls : %Iu\r\n", name->name, name->regex, name->line);
		}

		AR_printf(L"---------------------------------------------------------\r\n\r\n");


		AR_printf(L"Token:------------------------------------------\r\n\r\n");


		for(size_t i = 0; i < cfg->tok_cnt; ++i)
		{
				const cfgToken_t *token= &cfg->tok[i];
				AR_printf(L"%ls : %ls : %Iu\r\n", token->name, token->regex, token->tokval);
		}

		for(size_t i = 0; i < cfg->rule_cnt; ++i)
		{
				cfgRule_t		*rule = &cfg->rule[i];

				AR_printf(L"%ls : %ls : prec == %ls\r\n", rule->lhs, rule->rhs, rule->prec_tok);
		}

		

}


static void print_gmr_lexset(const cfgLexicalSet_t	*lx_set)
{
		for(size_t i = 0; i < lx_set->cnt; ++i)
		{
				wchar_t *tok = AR_wcsndup(lx_set->token_set[i].str, lx_set->token_set[i].count);

				AR_printf(L"%ls line : %Iu col : %Iu\r\n", tok, lx_set->token_set[i].line, lx_set->token_set[i].col);

				AR_DEL(tok);
				tok = NULL;
		}
}

#define GMR_FILE_PATH	L"D:\\Code\\Solidus\\Compiler\\Arsenal\\Grammar\\Tengu.gmr"
//#define GMR_FILE_PATH	L"D:\\Code\\Solidus\\Compiler\\Arsenal\\Grammar\\SQL.gmr"

static void test_gmr_lexset()
{
		arStatus_t		status;
		arString_t		*str;
		const cfgLexicalSet_t	*lx_set;
		
		status = AR_S_YES;
		lx_set = NULL;

		str = AR_CreateString();
		if(str == NULL)
		{
				goto END_POINT;
		}

		status = AR_LoadBomTextFile(GMR_FILE_PATH, NULL, str);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}


		lx_set = CFG_CollectLexicalSet(AR_GetStringCString(str));

		if(lx_set != NULL)
		{
				print_gmr_lexset(lx_set);
		}


END_POINT:

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

		if(lx_set)
		{
				CFG_DestroyLexicalSet(lx_set);
				lx_set = NULL;
		}
}



static void test_gmr_collect()
{
		arStatus_t				status;
		arString_t				*str;
		const cfgConfig_t		*cfg;
		cfgReport_t				report;
		status = AR_S_YES;

		cfg = NULL;
		str = AR_CreateString();
		if(str == NULL)
		{
				goto END_POINT;
		}

		status = AR_LoadBomTextFile(GMR_FILE_PATH, NULL, str);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}

		report.report_ctx = NULL;
		report.report_func = gmr_collect_report_func;

		cfg = CFG_CollectGrammarConfig(AR_GetStringCString(str), &report);

		if(cfg != NULL)
		{
				print_gmr_cfg(cfg);
		}


END_POINT:

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

		if(cfg)
		{
				CFG_DestroyGrammarConfig(cfg);
				cfg = NULL;
		}
}


void grammar_config_test()
{

		//test_gmr_lexset();
		test_gmr_collect();

}


AR_NAMESPACE_END




#endif

