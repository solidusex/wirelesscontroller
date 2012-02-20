#if(0)
#include "test.h"

#include "../Arsenal/Tengu/tengu.h"
#include "../Arsenal/Tengu/tguparser.h"
#include "../Arsenal/Tengu/tguutility.h"


#if defined(__LIB)

AR_NAMESPACE_BEGIN


void AR_STDCALL tengu_test_report(const tguReportInfo_t *report, void *context)
{
		switch(report->type)
		{
		default:
				AR_ASSERT(false);
				break;
		case TGU_REPORT_MESSAGE_T:
		case TGU_REPORT_WARNING_T:
		case TGU_REPORT_ERROR_T:
				printf("%ls : %d\r\n", report->message, report->line + 1);
				break;
		}
}



static tguReport_t		__g_report = 
{
		tengu_test_report,
		NULL
};


static int_t	AR_STDCALL tgu_print (tguMachine_t *vm)
{
		AR_ASSERT(vm != NULL);
		return 0;
}


#if(OS_TYPE == OS_WINDOWS_CE)
		#define TGU_TEST_PATH	L"\\Program Files\\Test\\tengu_input.txt"
#else
		#define TGU_TEST_PATH	L"..\\..\\..\\misc\\tengu_input.txt"
#endif



void test1()
{
		tguParseResult_t		parse_result;
		tguParser_t				*parser;
		tguSrc_t				*src;
		
		tguParserExtern_t		ext;
		ext.work_dir			= L"D:\\Code\\Solidus\\Compiler\\Arsenal\\misc";
		ext.global_constant		= TGU_CreateSymbTable();
		ext.build_in			= TGU_CreateSymbTable();
		ext.import_modules		= TGU_CreateSymbTable();

		TGU_InstallCFunction(ext.build_in, L"print", tgu_print);

		parser = TGU_CreateParser(&__g_report, &ext); 
		
				
		//code = __load_txt(TGU_TEST_PATH);
		src = TGU_LoadSources(L"..\\..\\..\\misc\\", L"tengu_input.txt");
		
		AR_ASSERT(src != NULL);
		AR_printf(L"%ls\r\n", src->code);

		tguSymb_t		*import_modules_symb = TGU_CreateSymb(TGU_SYMB_BLOCK_T, src->module_name);
		TGU_InsertToSymbTable(ext.import_modules, import_modules_symb);
		
		parse_result = TGU_ParseCode(parser, src->module_name, src->code);
		import_modules_symb->block = parse_result.block;

		if(parse_result.has_error)
		{
				TGU_RemoveFromSymbTable(ext.import_modules, import_modules_symb->name, import_modules_symb->type);
				AR_printf(L"%ls\r\n", L"parse failed\r\n");
		}else
		{
				AR_ASSERT(parse_result.block != NULL);

				AR_printf(L"%ls\r\n", L"parse succeeded\r\n");
		}


		getchar();


		

		
		TGU_DestroyParser(parser);

		TGU_DestroySymbTable(ext.import_modules);
		TGU_DestroySymbTable(ext.build_in);
		TGU_DestroySymbTable(ext.global_constant);

		TGU_ReleaseSources(src);
		src = NULL;
}







void load_source_test()
{
		ARSpace::tguSrc_t		*src;
		
		src = 		TGU_LoadSources(L"..\\..\\..\\misc\\txt_enc_test\\", L"bad_ascii.txt");


		if(src)
		{
				MessageBoxW(NULL, src->code, 0,0);
				TGU_ReleaseSources(src);
		}
}



void	Tengu_Test()
{
		test1();
		//load_source_test();


}

AR_NAMESPACE_END

#endif


#endif
