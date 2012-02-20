#if(0)
#include "test.h"

#include "../Arsenal/Parser/grammar.h"
#include "../Arsenal/Parser/parser.h"
#include "../Arsenal/Tools/tools.h"



#include <locale.h>

#if defined(__LIB)

AR_NAMESPACE_BEGIN

#define LOAD_TXT_MAX_BUF		(1024*50)

static const wchar_t* __load_txt(const wchar_t *path)
{
		FILE *pf;
		byte_t	*buf;
		size_t rn;
		const wchar_t *ret;
		
		AR_ASSERT(path != NULL);
		
		pf = _wfopen(path, L"r");

		if(pf == NULL)return NULL;

		buf = AR_NEWARR(byte_t, LOAD_TXT_MAX_BUF);
		rn = fread((void*)buf, 1, LOAD_TXT_MAX_BUF, pf);
		fclose(pf);
		if(rn < 3){AR_DEL(buf); return NULL;}
		buf[rn] = 0;

		if(buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)
		{
				ret = AR_utf8_convto_wcs((const char*)(buf + 3));

		}else if(buf[0] == 0xFF && buf[1] == 0xFE)
		{
				if(rn < 4){AR_DEL(buf); return NULL;}

				ret = (wchar_t*)AR_NEWARR0(wchar_t, rn / 2 + 1);
				AR_wcsncpy((wchar_t*)ret, (wchar_t*)(buf + 2), rn /2 );
		}else
		{
				ret = NULL;
		}
		AR_DEL(buf);
		return ret;
}

static void misc_test()
{
		wchar_t buf[1024];

		while( _getws(buf))
		{
				if(wcscmp(buf, L"quit") == 0)break;

				const wchar_t *txt = __load_txt(buf);
				if(txt != NULL)
				{
						AR_printf(L"%ls\r\n", txt);
						DWORD beg = GetTickCount();
						ARSpace::cfgConfig_t *cfg = CFG_CollectGrammarConfig(txt, NULL);
						DWORD end = GetTickCount();
						AR_printf(L"elapsed == %d\r\n", end - beg);
						AR_DEL(txt);
						if(cfg)CFG_DestroyGrammarConfig(cfg);
				}else
				{
						AR_printf(L"Path == %ls : error\r\n", buf);
				}
		}

}


void perf_test()
{
		misc_test();
}



AR_NAMESPACE_END



#endif

#endif

