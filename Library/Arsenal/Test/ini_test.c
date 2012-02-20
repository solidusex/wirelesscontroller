#include "test.h"


#include <math.h>
#include <time.h>

#include "Tools/iniobj.h"

#if defined(__LIB)

AR_NAMESPACE_BEGIN


#define _CHECK_AND_JMP(__stmt)	do{  if(__stmt == AR_E_NOMEM){ goto END_POINT; }}while( 0 )

void Ini_Test()
{
		arString_t	*str;
		iniObject_t *obj;
		str = AR_CreateString();
		

		if(AR_LoadBomTextFile(L"D:\\1.ini", NULL, str) != AR_S_YES)
		{
				goto END_POINT;
		}

		obj = Ini_CreateObject();

		if(obj == NULL)
		{
				goto END_POINT;
		}

		if(Ini_LoadObjectFromString(obj, AR_GetStringCString(str)) != AR_S_YES)
		{
				goto END_POINT;
		}
		

		
		printf("Ini_GetInt == %d\r\n", Ini_GetInt(obj,  INI_EMPTY_SECTION_NAME, L"a", 0));
		printf("Ini_GetUInt == %u\r\n", Ini_GetUInt(obj,  INI_EMPTY_SECTION_NAME, L"b", 0));
		printf("Ini_GetFloat == %g\r\n", Ini_GetFloat(obj,  INI_EMPTY_SECTION_NAME, L"c", 0.0f));

		

		_CHECK_AND_JMP(Ini_SetComment(obj, INI_EMPTY_SECTION_NAME, L"optimize3", L";≤‚ ‘Ini_SetComment"));

		_CHECK_AND_JMP(Ini_RemoveKey(obj, INI_EMPTY_SECTION_NAME, L"optimize"));
		_CHECK_AND_JMP(Ini_RemoveKey(obj, INI_EMPTY_SECTION_NAME, L"optimize2"));
		//Ini_RemoveKey(obj, INI_EMPTY_SECTION_NAME, L"optimize3");
		_CHECK_AND_JMP(Ini_RemoveKey(obj, INI_EMPTY_SECTION_NAME, L"optimize4"));

		_CHECK_AND_JMP(Ini_RemoveSection(obj, L"OPTIMIZE"));
		_CHECK_AND_JMP(Ini_RemoveSection(obj, L"OPTIMIZATION1"));
		
		_CHECK_AND_JMP(Ini_InsertSection(obj, L"Test", L";test"));
		_CHECK_AND_JMP(Ini_SetString(obj, L"Test", L"	a		", L"3", L"comment1"));
		_CHECK_AND_JMP(Ini_SetString(obj, L"Test", L"	b		", NULL, L"comment2"));
		
		_CHECK_AND_JMP(Ini_SetInt(obj, L"Test", L"c", -33, NULL));
		_CHECK_AND_JMP(Ini_SetUInt(obj, L"Test", L"d", 44, L"comment4"));
		_CHECK_AND_JMP(Ini_SetFloat(obj, L"Test", L"e", 0.123456789, L"comment5"));


		/*bad section name*/
		_CHECK_AND_JMP(Ini_InsertSection(obj, L"[ ]", L""));
		_CHECK_AND_JMP(Ini_InsertSection(obj, L"   ", L""));

		_CHECK_AND_JMP(Ini_InsertSection(obj, L"		p		", L""));

		_CHECK_AND_JMP(Ini_SaveObjectToString(obj, str));

		::MessageBoxW(NULL, AR_GetStringCString(str), 0,0);

END_POINT:
		if(obj)
		{
				Ini_DestroyObject(obj);
				obj = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}
}


AR_NAMESPACE_END

#endif