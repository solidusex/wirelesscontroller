#include "test.h"


#include "../Arsenal/Tools/tools.h"





#if defined(__LIB)

AR_NAMESPACE_BEGIN

#if(0)
snObject_t*		__get_int(arBuffer_t	*buffer);
snObject_t*		__get_str(arBuffer_t	*buffer);
snObject_t*		__get_list(arBuffer_t	*buffer);
snObject_t*		__get_dict(arBuffer_t	*buffer);




void sn_test_path()
{
		arBuffer_t		*buffer;
		buffer = AR_CreateBuffer(0);

		FILE *f = fopen("d:\\temp\\1.torrent", "rb");
		assert(f != NULL);

		byte_t buf[4096];
		
		while(!ferror(f) && !feof(f))
		{
				size_t rn = fread(buf, sizeof(byte_t), sizeof(buf), f);
				if(rn == 0)break;
				AR_InsertBuffer(buffer, buf, rn);
		}
		fclose(f);
		
		snObject_t *obj = SN_GetObject(buffer);
		AR_ASSERT(obj != NULL);
		AR_DestroyBuffer(buffer);
		
		int_t l;
		wchar_t wcs[1024];

		snObject_t *announce = SN_FindObjectByWcsPath(obj, L"announce");

		l = SN_GetWcsFromStringObject(announce, wcs, 1024);

		AR_ASSERT(l > 0);

		::MessageBoxW(NULL, wcs, 0, 0);

		snObject_t *announce_list = SN_FindObjectByWcsPath(obj, L"announce-list");

		if(announce_list != NULL)
		{
				for(size_t i = 0; i < SN_GetListObjectCount(announce_list); ++i)
				{
						snObject_t *obj = SN_GetFromListObject(announce_list, i);
						AR_ASSERT(obj != NULL && SN_GetObjectType(obj) == SN_LIST_T);

						for(size_t k = 0; k < SN_GetListObjectCount(obj); ++k)
						{
								const snObject_t *str = SN_GetFromListObject(obj, k);
								AR_ASSERT(str != NULL && SN_GetObjectType(str) == SN_STRING_T);

								l = SN_GetWcsFromStringObject(str, wcs, 1024);

								AR_ASSERT(l > 0);

								::MessageBoxW(NULL, wcs, 0, 0);
						}

				}
		}



		
		SN_DestroyObject(obj);
}

#endif











/************************************/



void sn_test_str()
{
		snObject_t *obj;
		
		int_t	ret;
		byte_t	data[512];
		char	str[512];
		wchar_t wcs[512];

		obj = SN_CreateObject(SN_STRING_T);

		byte_t buf[] = 
		{
				'a',
				'b',
				'c',
				'd'
		};

		SN_SetStringObjectByData(obj, buf, sizeof(buf));

		
		ret = SN_GetDataFromStringObject(obj, NULL, 0);

		AR_printf(L"SN_GetDataFromStringObject : len == %d\r\n", ret);

		ret = SN_GetStrFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetStrFromStringObject : len == %d\r\n", ret);


		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetWcsFromStringObject : len == %d\r\n", ret);




		ret = SN_GetDataFromStringObject(obj, NULL, 0);
		ret = SN_GetDataFromStringObject(obj, data, sizeof(data));
		AR_printf(L"SN_GetDataFromStringObject : len == %d\r\n", ret);

		
		ret = SN_GetStrFromStringObject(obj, NULL, 0);
		ret = SN_GetStrFromStringObject(obj, str, sizeof(str));
		AR_printf(L"SN_GetStrFromStringObject : str == %hs, len == %d\r\n", str, ret);


		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		ret = SN_GetWcsFromStringObject(obj, wcs, sizeof(wcs)/2);
		AR_printf(L"SN_GetWcsFromStringObject : wcs == %s, len == %d\r\n", wcs, ret);
		
		/*
		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetWcsFromStringObject : len == %d\r\n", ret);
		*/


		SN_DestroyObject(obj);
}




void sn_test_str2()
{
		snObject_t *obj;
		
		int_t	ret;
		byte_t	data[512];
		char	str[512];
		wchar_t wcs[512];

		obj = SN_CreateObject(SN_STRING_T);

		byte_t buf[] = 
		{
				'a',
				'b',
				0,
				'c',
				'd'
		};

		SN_SetStringObjectByData(obj, buf, sizeof(buf));

		
		ret = SN_GetDataFromStringObject(obj, NULL, 0);

		AR_printf(L"SN_GetDataFromStringObject : len == %d\r\n", ret);

		ret = SN_GetStrFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetStrFromStringObject : len == %d\r\n", ret);


		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetWcsFromStringObject : len == %d\r\n", ret);




		ret = SN_GetDataFromStringObject(obj, NULL, 0);
		ret = SN_GetDataFromStringObject(obj, data, sizeof(data));
		AR_printf(L"SN_GetDataFromStringObject : len == %d\r\n", ret);

		
		ret = SN_GetStrFromStringObject(obj, NULL, 0);
		ret = SN_GetStrFromStringObject(obj, str, sizeof(str));
		AR_printf(L"SN_GetStrFromStringObject : str == %hs, len == %d\r\n", str, ret);


		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		ret = SN_GetWcsFromStringObject(obj, wcs, sizeof(wcs)/2);
		AR_printf(L"SN_GetWcsFromStringObject : wcs == %s, len == %d\r\n", wcs, ret);

		
		SN_DestroyObject(obj);
}





void sn_test_str3()
{
		snObject_t *obj;
		
		int_t	ret;
		byte_t	data[512];
		char	str[512];
		wchar_t wcs[512];

		obj = SN_CreateObject(SN_STRING_T);

		//byte_t buf[] = "字符集问题太麻烦了，操！！！abcdefg";

		const wchar_t *txt = L"字符集问题太麻烦了，操！！！abcdefg";


		//SN_SetStringObjectByData(obj, buf, sizeof(buf));

		SN_SetStringObjectByWcs(obj, txt);
		
		ret = SN_GetDataFromStringObject(obj, NULL, 0);

		AR_printf(L"SN_GetDataFromStringObject : len == %d\r\n", ret);

		ret = SN_GetStrFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetStrFromStringObject : len == %d\r\n", ret);


		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		AR_printf(L"SN_GetWcsFromStringObject : len == %d\r\n", ret);




		ret = SN_GetDataFromStringObject(obj, NULL, 0);
		ret = SN_GetDataFromStringObject(obj, data, sizeof(data));
		AR_printf(L"SN_GetDataFromStringObject : len == %d\r\n", ret);

		
		ret = SN_GetStrFromStringObject(obj, NULL, 0);
		ret = SN_GetStrFromStringObject(obj, str, sizeof(str));
		AR_printf(L"SN_GetStrFromStringObject : str == %hs, len == %d\r\n", str, ret);


		ret = SN_GetWcsFromStringObject(obj, NULL, 0);
		ret = SN_GetWcsFromStringObject(obj, wcs, sizeof(wcs)/2);
		AR_printf(L"SN_GetWcsFromStringObject : wcs == %ls, len == %d\r\n", wcs, ret);

		
		SN_DestroyObject(obj);
}







void sn_test_torrent()
{
		arBuffer_t		*buffer;
		snRetVal_t		ret;
		FILE *new_f = NULL;
		buffer = AR_CreateBuffer(0);

		FILE *f = fopen("d:\\1.torrent", "rb");
		assert(f != NULL);

		byte_t buf[4096];
		
		while(!ferror(f) && !feof(f))
		{
				size_t rn = fread(buf, sizeof(byte_t), sizeof(buf), f);
				if(rn == 0)break;
				AR_InsertBuffer(buffer, buf, rn);
		}
		fclose(f);
		
		ret = SN_GetObject(buffer);

		if(ret.status != AR_S_YES)
		{
				goto END_POINT;
		}


		SN_PutObject(buffer, ret.obj);
		


		new_f = fopen("d:\\new.torrent", "wb");
		assert(new_f != NULL);

		fwrite(AR_GetBufferData(buffer), sizeof(byte_t), AR_GetBufferAvailable(buffer), new_f);

END_POINT:
		if(new_f)
		{
				fclose(new_f);
		}

		if(buffer)
		{
				AR_DestroyBuffer(buffer);
				buffer = NULL;
		}

		if(ret.obj)
		{
				SN_DestroyObject(ret.obj);
				ret.obj = NULL;
		}

}



void sn_test_find()
{
		arBuffer_t		*buffer;
		buffer = AR_CreateBuffer(0);

		FILE *f = fopen("d:\\1.torrent", "rb");
		assert(f != NULL);

		byte_t buf[4096];
		
		while(!ferror(f) && !feof(f))
		{
				size_t rn = fread(buf, sizeof(byte_t), sizeof(buf), f);
				if(rn == 0)break;
				AR_InsertBuffer(buffer, buf, rn);
		}
		fclose(f);
		
		snObject_t *root = SN_GetObject(buffer).obj;
		AR_ASSERT(root != NULL);
		AR_DestroyBuffer(buffer);
		
		int_t l;
		wchar_t wcs[1024];

		snObject_t *announce = SN_FindObjectByWcsPath(root, L"////announce").obj;
		if(announce == NULL)
		{
				goto END_POINT;
		}

		l = SN_GetWcsFromStringObject(announce, wcs, 1024);

		AR_ASSERT(l > 0);

		::MessageBoxW(NULL, wcs, 0, 0);

		snObject_t *announce_list = SN_FindObjectByWcsPath(root, L"announce-list").obj;

		if(announce_list != NULL)
		{
				for(size_t i = 0; i < SN_GetListObjectCount(announce_list); ++i)
				{
						wchar_t buf[200];
						AR_swprintf(buf, 200, L"/announce-list/%d", i);
						snObject_t *obj = SN_FindObjectByWcsPath(root, buf).obj;
						if(obj == NULL)
						{
								goto END_POINT;
						}

						AR_ASSERT(obj != NULL && SN_GetObjectType(obj) == SN_LIST_T);

						for(size_t k = 0; k < SN_GetListObjectCount(obj); ++k)
						{
								const snObject_t *str = SN_GetFromListObject(obj, k);
								AR_ASSERT(str != NULL && SN_GetObjectType(str) == SN_STRING_T);

								l = SN_GetWcsFromStringObject(str, wcs, 1024);

								AR_ASSERT(l > 0);

								::MessageBoxW(NULL, wcs, 0, 0);
						}

				}
		}



END_POINT:
		if(root)
		{
				SN_DestroyObject(root);
				root = NULL;
		}
}





void sn_test()
{
		//sn_test_torrent();
		//sn_test_path();
		//sn_test_str();
		//sn_test_str2();
		//sn_test_str3();

		sn_test_find();
}



AR_NAMESPACE_END

#endif

