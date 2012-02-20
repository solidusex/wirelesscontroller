#if(0)

#include "test.h"


#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Tools/tools.h"


#include <locale.h>

#if defined(__LIB)

AR_NAMESPACE_BEGIN


void parser_test()
{

		wchar_t path[1024];

		_wgetcwd(path, 1024);

		printf("%ls\r\n", path);

		arTxtBom_t bom;
		arString_t *str = AR_CreateString();

		if(AR_LoadBomTextFile(L"..\\..\\..\\Grammar\\SQL.gmr", &bom, str) != AR_S_YES)
		{
				AR_abort();
		}

		uint_64_t beg, end;
		
		beg = AR_GetTime_Milliseconds();

		const cfgLexicalSet_t *set = CFG_CollectLexicalSet(AR_GetStringCString(str));

		if(set == NULL)
		{
				AR_abort();
		}


		end = AR_GetTime_Milliseconds();

		printf("elapsed microseconds == %I64u\r\n", end - beg);

		size_t cnt = 0;

		for(size_t i = 0; i < set->cnt; ++i)
		{
				if(set->token_set[i].count == 0)
				{
						cnt++;	
				}
		}

		AR_DestroyString(str);
}

AR_NAMESPACE_END

#endif



#endif

