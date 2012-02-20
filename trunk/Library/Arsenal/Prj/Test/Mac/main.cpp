
#include <iostream>
#include <string>
#include "Arsenal.h"
#include "TestBuildParser.h"


using namespace ARSpace;



void AR_Test1()
{
		//wprintf(L"Invalid Token \"%ls\" in (%lld : %lld)\r\n\r\n", L"d", (size_t)1,(size_t)2);
		/*
		wchar_t buf[1024];

		wchar_t *d = AR_wcsndup(L"d", 1);
		
		AR_swprintf(buf, 1024, L"Invalid Token %ls in (%Id : %Id)\r\n\r\n", d, (size_t)1,  (size_t)2);
		
		AR_DEL(d);
		
		wprintf(L"%ls", buf);
		 */
		
		
		{
		arString_t *s = AR_CreateString();

		wchar_t *buf = AR_wcsndup(L"d", 1);
		
		AR_AppendFormatString(s
							  , L"Invalid Token %ls in (%Id : %Id)\r\n\r\n"
							  , buf
							  , (size_t)0
							  , (size_t)0
							  );
		
		AR_printf(L"%ls\r\n", AR_GetStringCString(s));
		
		AR_DEL(buf);
		buf = NULL;
		AR_DestroyString(s);
		s = NULL;
		}
		
		getchar();
					 
}


#define INPUT_FILE		L"/Users/solidussnakeex/Desktop/Tengu2.gmr"
#define OUTPUT_FILE		L"/Users/solidussnakeex/Desktop/output.txt"

#define OUTPUT_TYPE		AR_TXT_BOM_UTF_8

void text_test_save()
{


		arTxtBom_t		bom;
		arString_t *str = AR_CreateString();
		
		
		if(!AR_LoadBomTextFile(INPUT_FILE, &bom, str))
		{
				AR_ASSERT(false);
		}
		
		
		if(!AR_SaveBomTextFile(OUTPUT_FILE, OUTPUT_TYPE, AR_GetStringCString(str)))
		{
				AR_ASSERT(false);
		}
		
		
		if(!AR_LoadBomTextFile(OUTPUT_FILE, &bom, str))
		{
				AR_ASSERT(false);
		}
		
		AR_ASSERT(bom == OUTPUT_TYPE);
		
		wprintf(L"%ls\r\n", AR_GetStringCString(str));
				
		AR_DestroyString(str);
		
		

}



void AR_Test2()
{

		text_test_save();
				
		
		
}






void AR_Test3()
{
		uint_64_t beg,end;
		for(size_t i = 0; i < 10; ++i)
		{
				
				beg = AR_GetTime_Milliseconds();
				AR_Sleep(999);
				end = AR_GetTime_Milliseconds();
				
				AR_printf(L"elapsed == %qu\r\n", end - beg);
				
		}
}


void AR_Test4()
{
		arSpinLock_t lock;
		
		AR_InitSpinLock(&lock);
		
		AR_LockSpinLock(&lock);
		AR_LockSpinLock(&lock);
		
		AR_UnLockSpinLock(&lock);
		
		AR_UnInitSpinLock(&lock);
}


void AR_Test5()
{
		
		int_t l = AR_scwprintf(L"%C%lc%hC%ls", L'c', L'd', 'e', L"aaaaa");
		
		printf("%d\r\n", l);
		
		printf("sizeof(wint_t) == %d\r\n", sizeof(wint_t));
		
		
}






void AR_STDCALL tiny_error(int_t level, const wchar_t* msg, void *ctx)
{
		
        wprintf(L"%ls\r\n", msg);
}

void AR_STDCALL tiny_printf(const wchar_t *msg, void *ctx)
{
		
        wprintf(L"%ls\r\n", msg);
}







int  main()
{
      
		setlocale(LC_ALL, "");
		
		
				
		//printf("%s\r\n", AR_FUNC_NAME);
        arInit_t ai = {{tiny_error, tiny_printf, NULL}};
		
        //printf("%s\r\n", setlocale(LC_ALL, NULL));
		
        Arsenal_Init(&ai);
		
		//AR_Test1();
        //AR_Test2();
		//AR_Test3();
		//AR_Test4();
		//AR_GenerateParsertest();
		AR_Test5();
		
		
		Arsenal_UnInit();
		
		
		printf("done\r\n");
		
		
		//getchar();
		
		return 0;
		
}









