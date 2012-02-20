#include "test.h"


#include "../Arsenal/Tengu/tengu.h"


#if(0)



#if defined(__LIB)

AR_NAMESPACE_BEGIN




#define DEF_PAT_PATH  L"..\\..\\..\\misc\\test.gmr"

#define DEF_SOUR_PATH  L"..\\..\\..\\misc\\input.txt"




static void parse_code(lex_t *lex, const wchar_t *sources)
{
		lexMatch_t match;
		lexToken_t tok;
		size_t	i;
		wchar_t buf[1024];
		
		AR_ASSERT(lex != NULL && sources != NULL);
		
		Lex_GenerateTransTable(lex);

		Lex_InitMatch(&match, sources);

		{
				
				size_t tok_cnt = 0;
				uint_64_t beg, end;

				beg = AR_GetTime_Microseconds();
				//DWORD beg, end;
				//beg = GetTickCount();


				
				while(Lex_Match(lex, &match, &tok))
				{
						/*
						AR_wcsncpy(buf, tok.str, tok.count);
						buf[tok.count] = L'\0';

						AR_printf(L"%ls : type == %d : count == %d : line = %d\r\n", buf, tok.value, tok.count, tok.line);

						getchar();

						*/
						
						tok_cnt++;
						
						if(tok.value == 0)break;
				}

				if(match.is_ok)
				{
						AR_printf(L"lex parse done for %d token\r\n", tok_cnt);
				}else
				{
						size_t n = AR_wcslen(match.next);
						AR_printf(L"lex parse failed : %ls\r\n", AR_wcsndup(match.next, n > 10 ? 10 : n));
				}

				end = AR_GetTime_Microseconds();

				AR_printf(L"elapsed == %I64d\r\n", end - beg);
		}

		Lex_UnInitMatch(&match);


}




#endif


void AR_STDCALL ray_report_func(const rayReportMsg_t *report, void *context)
{
		printf("%ls\r\n", report->message);
}


static rayReport_t		__def_report = 
{
		ray_report_func,
		NULL
};


void align_test(rayParser_t		*parser)
{
		AR_printf(L"Default alignment == %d\r\n", RAY_GetAlignment(parser));
		
		RAY_PushAlignment(parser, 16);
		AR_printf(L"After push alignment == %d\r\n", RAY_GetAlignment(parser));

		RAY_PopAlignment(parser);
		AR_printf(L"After pop alignment == %d\r\n", RAY_GetAlignment(parser));
}

void ray_test()
{
		
		rayParser_t		*parser;
		uint_64_t beg, end;

		
		beg = AR_GetTime_Milliseconds();

		parser = RAY_CreateParser(&__def_report);

		end = AR_GetTime_Milliseconds();
		
		AR_printf(L"build ray parser elapsed == %I64d\r\n", end - beg);
		
		align_test(parser);
		getchar();
		
		const wchar_t *src = __load_txt(DEF_SOUR_PATH);
		AR_ASSERT(src != NULL);
		
		RAY_Parse(parser, src);
		getchar();
		AR_printf(L"%ls\r\n", L"----------------------------------------------\r\n");
		RAY_Parse(parser, src);
		getchar();

		RAY_DestroyParser(parser);

		AR_DEL(src);
}


AR_NAMESPACE_END


#endif



