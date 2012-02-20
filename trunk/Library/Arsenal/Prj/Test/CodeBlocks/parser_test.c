#if(1)
#include <locale.h>
#include "test.h"




AR_NAMESPACE_BEGIN

#if(0)
#define LOAD_TXT_MAX_BUF  (1024*1024 * 5)
static const wchar_t* __load_txt(const char *path)
{
		FILE *pf;
		byte_t	*buf;
		size_t rn;
		const wchar_t *ret;
		buf = AR_NEWARR(byte_t, LOAD_TXT_MAX_BUF);

		AR_ASSERT(path != NULL);


		//pf = fopen("..\\..\\..\\misc\\book1.gmr", "r");

		pf = fopen(path, "rb");

		AR_ASSERT(pf != NULL);
		rn = fread((void*)buf, 1, LOAD_TXT_MAX_BUF, pf);
		fclose(pf);

		AR_ASSERT(rn > 3);
		//printf("read size == %d\r\n", rn);
		buf[rn] = 0;


		if(buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)
		{
		    ret = AR_str_convto_wcs((const char*)(buf + 3));
		}else
		{
		    ret = AR_utf8_convto_wcs((const char*)(buf));
		}

		AR_DEL(buf);
		return ret;
}
#endif
#if(0)
void print_grammar(const psrGrammar_t *gmr)
{
		arString_t  *str;
		AR_ASSERT(gmr);

		str = AR_CreateString();

		Parser_PrintGrammar(gmr, str);

		AR_printf(L"%ls\r\n", AR_GetStrString(str));

		Parser_ReportLeftRecursion(gmr, str);

		AR_printf(L"%ls\r\n", AR_GetStrString(str));


		AR_DestroyString(str);
}

#endif

void print_first_follow(const psrGrammar_t *gmr)
{
		psrSymbMap_t	first, follow;
		arString_t		*str;
		AR_ASSERT(gmr != NULL);

		Parser_InitSymbMap(&first);
		Parser_InitSymbMap(&follow);

		str = AR_CreateString();


		Parser_CalcFirstSet(gmr, &first);
		Parser_CalcFollowSet(gmr, &follow, &first);

		AR_AppendString(str, L"First Set:\r\n");
		Parser_PrintSymbolMap(&first, str);
		AR_AppendString(str, L"----------------------------------------\r\n");

		AR_AppendString(str, L"Follow Set:\r\n");
		Parser_PrintSymbolMap(&follow, str);
		AR_AppendString(str, L"----------------------------------------\r\n");


		Parser_UnInitSymbMap(&first);
		Parser_UnInitSymbMap(&follow);

		AR_printf(L"%ls\r\n", AR_GetStrString(str));
		AR_DestroyString(str);

}



void print_action_table(const parser_t *psr)
{
		arString_t  *str;
		AR_ASSERT(psr);

		str = AR_CreateString();

		Parser_PrintParserActionTable(psr, str, 20);

		AR_printf(L"%ls\r\n", AR_GetStrString(str));


		AR_DestroyString(str);
}

void print_conflict(const parser_t *psr)
{
		arString_t  *str;
		AR_ASSERT(psr);

		str = AR_CreateString();

		Parser_PrintParserConflict(psr, str);

		AR_printf(L"%ls\r\n", AR_GetStrString(str));


		AR_DestroyString(str);
}



#define DEF_PAT_PATH  "../../../misc/C.gmr"

#define DEF_SOUR_PATH  "../../../misc/input.txt"




void parse_code(const cfgConfig_t *cfg, const wchar_t *sources)
{
		lex_t *lex;
		lexMatch_t *match;
		lexToken_t tok;
		size_t	i;
		wchar_t buf[1024];

		AR_ASSERT(cfg != NULL && sources != NULL);


        lex = Lex_Create(NULL);


		for(i = 0; i < cfg->name_cnt; ++i)
		{
				if(!Lex_InsertName(lex, cfg->name[i].name, cfg->name[i].regex))
				{
						AR_ASSERT(false);
						AR_abort();
				}
		}

		for(i = 0; i < cfg->tok_cnt; ++i)
		{
				lexAction_t act;
				act.is_skip = cfg->tok[i].is_skip;
				act.priority = cfg->tok[i].lex_prec;
				act.value = cfg->tok[i].tokval;
				if(!Lex_InsertRule(lex, cfg->tok[i].regex, &act))
				{
						AR_ASSERT(false);
						AR_abort();
				}
		}

		Lex_GenerateTransTable(lex);
        match = Lex_CreateMatch(lex);

		{

				size_t tok_cnt = 0;
				uint_64_t beg, end;

				beg = AR_GetTime_Milliseconds();
				//DWORD beg, end;
				//beg = GetTickCount();



				while(Lex_Match(match, &tok))
				{
						/*
						AR_wcsncpy(buf, tok.str, tok.count);
						buf[tok.count] = L'\0';

						AR_printf(L"%ls : type == %d : count == %d : line = %d\r\n", buf, tok.value, tok.count, tok.line);
						*/
						tok_cnt++;
						if(tok.value == 0)break;
				}

				if(match->is_ok)
				{
						AR_printf(L"lex parse done for %d token\r\n", tok_cnt);
				}else
				{
						size_t n = AR_wcslen(match->next);
						AR_printf(L"lex parse failed : %ls\r\n", AR_wcsndup(match->next, n > 10 ? 10 : n));
				}

				//end = GetTickCount();

				end = AR_GetTime_Milliseconds();

				AR_printf(L"elapsed == %lld\r\n", end - beg);
		}

		Lex_DestroyMatch(match);


		Lex_Destroy(lex);

        AR_printf(L"\r\n\r\n");

}

/*


typedef enum
{
		CFG_REPORT_MESSAGE_T,
		CFG_REPORT_ERROR_T,
		CFG_REPORT_ERROR_LEX_T,
		CFG_REPORT_ERROR_SYNTAX_T,
		CFG_REPORT_WARNING_SYNTAX_T
}cfgReportType_t;


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

static void AR_STDCALL report_func(const cfgReportInfo_t *report, void *context)
{
		switch(report->type)
		{
		case CFG_REPORT_MESSAGE_T:
				AR_printf(L"%ls\r\n", report->std_msg.message);
				break;
		case CFG_REPORT_ERROR_T:
				AR_printf(L"%ls : %d\r\n",  report->error.err_msg, report->error.err_level);
				break;
		case CFG_REPORT_ERROR_LEX_T:
				AR_printf(L"lex error %ls\r\n", report->lex_error.msg);
				break;
		case CFG_REPORT_ERROR_SYNTAX_T:
				AR_printf(L"syntax error %ls\r\n", report->syntax_error.msg);
				break;
		default:
				AR_ASSERT(false);
		}
}

/*
typedef struct __cfg_report_tag
{
		cfgReportFunc_t	report_func;
		void			*report_ctx;
}cfgReport_t;
*/

static cfgReport_t __g_report = { report_func, NULL};

#if(0)
void parser_test()
{

		const wchar_t	*gmr_txt;
		cfgConfig_t		*cfg;

		char buf[1024];

		AR_printf(L"%ls\r\n", L"Please enter pattern path!");
		//__gets_chk(buf,1024);
                getchar();
    //gmr_txt = __load_txt(DEF_PAT_PATH);

		gmr_txt = __load_txt(buf);

		if(gmr_txt == NULL)
		{
				AR_abort();
		}


		cfg = CFG_CollectGrammarConfig(gmr_txt, &__g_report);


		if(cfg)
		{


#if(1)
				size_t i;

				AR_printf(L"----------------------\r\n");
				for(i = 0; i < cfg->name_cnt; ++i)
				{
						AR_printf(L"%ls : %ls : %d\r\n", cfg->name[i].name, cfg->name[i].regex, cfg->name[i].line);
/*
						if(!LEX_InsertName(tmp_lex, cfg->name[i].name, cfg->name[i].regex))
						{
								AR_abort();
						}
*/

				}
				AR_printf(L"----------------------\r\n");
				for(i = 0; i < cfg->tok_cnt; ++i)
				{
						lexAction_t act;
						act.is_skip = cfg->tok[i].is_skip;
						act.priority = cfg->tok[i].lex_prec;
						act.value = i + 256;

						AR_printf(L"%ls : %ls : %d : %d\r\n", cfg->tok[i].name, cfg->tok[i].regex, cfg->tok[i].lex_prec, cfg->tok[i].tokval);
/*
						if(!LEX_InsertRule(tmp_lex, cfg->tok[i].regex, &act))
						{
								AR_abort();
						}
		*/
				}
				AR_printf(L"----------------------\r\n");

				for(i = 0; i < cfg->prec_cnt; ++i)
				{
						size_t k;
						const cfgPrec_t	*prec = &cfg->prec[i];

						for(k = 0; k < prec->count; ++k)
						{
								AR_printf(L"name == %ls : tok_val == %d : prec_level == %d : assoc == %d \r\n", prec->prec_tok_set[k], prec->prec_tok_val[k],prec->prec_level, prec->assoc);
						}
				}

				AR_printf(L"----------------------\r\n");

				for(i = 0; i < cfg->rule_cnt; ++i)
				{
						AR_printf(L"%ls : %ls : %ls : %ls : line %d\r\n"
								, cfg->rule[i].lhs
								, cfg->rule[i].rhs
								, cfg->rule[i].prec_tok ? cfg->rule[i].prec_tok : L" "
								, cfg->rule[i].action_ins ? cfg->rule[i].action_ins : L" "
								,cfg->rule[i].line
								);
				}

				AR_printf(L"----------------------\r\n");

		//		arString_t *str = NULL;
		//		CFG_ConfigToCode(cfg, str);

#endif

				if(!cfg->has_error)
				{
                        char buf[1024];
                        AR_printf(L"%ls\r\n", "Please enter sources path");
                        //gets(buf);
                        //__gets_chk(buf,1024);

						//const wchar_t *input = __load_txt(DEF_SOUR_PATH);
						const wchar_t *input = __load_txt(buf);
						parse_code(cfg, input);

						AR_DEL(input);
				}
		}else
		{
				AR_abort();
		}


		if(cfg)CFG_DestroyGrammarConfig(cfg);

		AR_DEL(gmr_txt);
}
#endif

#if(0)

void parser_perf_test()
{
		size_t i;
		const wchar_t	*gmr_txt, *src_txt;
		cfgConfig_t		*cfg;
		gmr_txt = __load_txt(DEF_PAT_PATH);

		if(gmr_txt == NULL)
		{
				AR_abort();
		}

		AR_printf(L"%ls\r\n", gmr_txt);
		src_txt = __load_txt(DEF_SOUR_PATH);
		getchar();

		for(i = 0; i < 5; ++i)
		{
				//DWORD beg, end;
				//beg = GetTickCount();

				uint_64_t beg ,end;
				beg = AR_GetTime_Milliseconds();

				cfg = CFG_CollectGrammarConfig(gmr_txt, NULL);

				//parse_code(cfg, src_txt);

				if(cfg)CFG_DestroyGrammarConfig(cfg);

				//end = GetTickCount();
				end = AR_GetTime_Milliseconds();

				AR_printf(L"parser elapsed == %d\r\n", end - beg);


				//Sleep(500);

				system("cls");
		}

		AR_DEL(src_txt);
		AR_DEL(gmr_txt);
}
#endif


AR_NAMESPACE_END






#endif
