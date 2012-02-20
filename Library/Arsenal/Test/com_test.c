
#include "test.h"


#include <math.h>
#include <time.h>

#if defined(__LIB)

AR_NAMESPACE_BEGIN



arString_t*		AR_CreateString();
void			AR_DestroyString(arString_t *str);

arStatus_t		AR_ReserveString(arString_t *str, size_t num);
void			AR_ClearString(arString_t *str);
arStatus_t		AR_AppendString(arString_t *str, const wchar_t *sour);

arStatus_t		AR_FormatString(arString_t *str, const wchar_t *fmt, ...);
arStatus_t		AR_AppendFormatString(arString_t *str, const wchar_t *fmt, ...);


const wchar_t*	AR_GetStringCString(const arString_t *str);
size_t			AR_GetStringLength(const arString_t *str);



void str_test()
{
		arString_t *str;
		size_t i;
		str = AR_CreateString();
		
		for(i = 0; i < 100; ++i)
		{
				AR_AppendFormatString(str, L"%ls:%d", L"solidus", 8512);
				//AR_AppendString(str, L"abcd");
		}

		
		printf("len  == %d\r\n", AR_GetStringLength(str));
		getchar();
		AR_printf(L"%ls\r\n", AR_GetStringCString(str));

		AR_DestroyString(str);
		
		getchar();
}

void str_test2()
{
		wchar_t dest[4096] = {0};

		const wchar_t *s1 = L"abcdefg";
		const wchar_t *s2 = L"0123456789";

		AR_printf(L"%ls\r\n", AR_wcscat(dest, s1));
		AR_printf(L"%ls\r\n", AR_wcscat(dest, L""));

		AR_printf(L"%ls\r\n", AR_wcsncat(dest, s2, 20));

		AR_printf(L"%ls\r\n", AR_wcsncat(dest, L"", 20));
}


void com_test2()
{
		const wchar_t *p;
		const wchar_t *str = L"			 -abcdef";
		
		int_32_t num;
		
		p = AR_wtoi32(str, &num, 16);
		AR_printf(L"%ls : %d\n", p, num);

		p = AR_wtoi32_s(str, str + wcslen(str), &num, 16);
		AR_printf(L"ver_s = %ls : %d\n", p, num);
		getchar();
}

void __wtods_test(const wchar_t *str)
{
		double num;
		str = AR_wtod_s(str, str + AR_wcslen(str) + 1, &num);
		AR_printf(L"%ls : %f\r\n", str, num);

}
void com_test3()
{
		{
		const wchar_t *p;
		const wchar_t *str = L"3a.1415926This stopped it";
		
		double num;
		
		p = AR_wtod(str, &num);
		AR_printf(L"%ls : %f\n", p, num);
		
		p = AR_wtod_s(str, str + 5, &num);
		AR_printf(L"%ls : %f\n", p, num);

		getchar();
		}


		{
		const wchar_t *p;
		const wchar_t *str = L"3.14159265This stopped it";
		
		double num;
		
		p = AR_wtod(str, &num);
		AR_printf(L"%ls : %f\n", p, num);
		
		p = AR_wtod_s(str, str + wcslen(str) + 1, &num);
		AR_printf(L"%ls : %f\n", p, num);

		getchar();
		}

		{
		const wchar_t *p;
		const wchar_t *str = L"3.14159265e+1000This stopped it";
		
		double num;
		
		p = AR_wtod(str, &num);
		AR_printf(L"%ls : %f\n", p, num);

		AR_ASSERT(num == HUGE_VAL);
		
		p = AR_wtod_s(str, str + wcslen(str) + 1, &num);
		AR_printf(L"%ls : %f\n", p, num);

		getchar();
		}


		{
		const wchar_t *p;
		//const wchar_t *str = L"-3.14159265e+1000This stopped it";
		const wchar_t *str = L"-.14159265e+1This stopped it";
		
		double num;
		
		p = AR_wtod(str, &num);
		
		AR_printf(L"%ls : %f\n", p, num);
		
		p = AR_wtod_s(str, str + AR_wcslen(str) + 1, &num);
		AR_printf(L"%ls : %f\n", p, num);

		getchar();
		}

		{
				const wchar_t *str 
						= 
						L"		-198.401E+0abc"
						, *str1 = L"-3.e+1abc"
						, *str2 = L"-.0314e+1x"
						, *str3 = L"-.abc"
						, *str4 = L"-"
						, *str5 = L"3.e+"
						, *str6 = L".3e+0"
						, *str7 = L"		-199999999999999999999999999999999999999999999999999990.999999999999999999999999999999999401E+0abc"
						, *str8 = L"-0.0000e-8"
						, *str9 = L"+0.0001e+1"
						;

				__wtods_test(str);
				__wtods_test(str1);
				__wtods_test(str2);
				__wtods_test(str3);
				__wtods_test(str4);
				__wtods_test(str5);
				__wtods_test(str6);
				__wtods_test(str7);
				__wtods_test(str8);
				__wtods_test(str9);
				
				getchar();
		}
}


void com_conv()
{
		char *tmp;
		wchar_t *wtmp;
		const wchar_t *s = L"中文中文中文中文";


		//const wchar_t *s = L"";
		
		tmp = AR_wcs_convto_str(AR_CP_UTF8, s, AR_wcslen(s));

		wtmp = AR_str_convto_wcs(AR_CP_UTF8,tmp, AR_strlen(tmp));
		
		AR_DEL(tmp); AR_DEL(wtmp);
}


void com_conv2()
{
		char buf[1024];
		size_t l;
		l = AR_wcs_to_str(AR_CP_UTF8, L"", 0, buf, 1024);
		buf[l] = 0;
}



AR_INLINE uint_t str_hash_test(const wchar_t *str, size_t n)
{
		uint_t	ret;
		size_t	i;
		
		AR_ASSERT(str != NULL);
		
		ret = 0;
		for(i = 0; i < n; ++i)
		{
				ret ^= (str[i] << (i & 0x0F));
		}
		return ret;
}

AR_INLINE uint_t str_hash_test2(const wchar_t *s)
{
		return str_hash_test(s, AR_wcslen(s));

}


AR_INLINE uint_t str_hash_test3(const wchar_t *str, size_t n)
{
		uint_t	ret;
		size_t	i;

		const size_t a = 1;
		if(n == 0)return 0;

		AR_ASSERT(str != NULL);

		ret = 0;
		for(i = 0; i < n; ++i)
		{
				ret += ((a << (n-i)) * (uint_t)str[i]);
		}
		return ret;
}

AR_INLINE uint_t str_hash_test4(const wchar_t *s)
{
		return str_hash_test3(s, AR_wcslen(s));

}


void com_hash_test()
{
		const wchar_t *str = L"aaaaabcdefabcedef";
		const wchar_t *str1 = L"aaaaabcdfebacdef";
		AR_printf(L"hash1 string == %ls : value == %u\r\n", str, str_hash_test2(str));
		AR_printf(L"hash1 string == %ls : value == %u\r\n", str1, str_hash_test2(str1));

		AR_printf(L"hash2 string == %ls : value == %u\r\n", str, str_hash_test4(str));
		AR_printf(L"hash2 string == %ls : value == %u\r\n", str1, str_hash_test4(str1));

		

}


void __format_v(const wchar_t *fmt, ...)
{
		int_t len;
		va_list	arg_ptr;
		AR_va_start(arg_ptr, fmt);
		len = AR_vscwprintf(fmt, arg_ptr);
		printf("--------------------------\r\n");
		printf("AR_vscwprintf == %d\r\n", len);
		//printf("_vscwprintf == %d\r\n", _vscwprintf(fmt, arg_ptr));
		
		AR_va_end(arg_ptr);
}

void com_vscwprintf_test()
{
		uint_64_t  x = 7332201052963203716;

		__format_v(L"%       .f%*.*f\r\n", 3344.333333333333333333333333, 20,20,3344.333333333333333333333333);

		__format_v(L"%33.54f", 3.14);

		__format_v(L"%d:%u:%qd:%ls:%f\r\n", 33,44,(uint_64_t)198401010, L"aaaaaaaaa",3.1415);

		__format_v(L"abcdefg");
		
		
		
		
		__format_v(L"%qd", x);
		__format_v(L"%I64d", x); //崩溃
		__format_v(L"%I64ld", x); //崩溃

}


void com_vscwprintf_test2()
{
		__format_v(L"%*333.333Id : %Id\r\n", 0,(size_t)1024, (size_t)2048);

		__format_v(L"%*Id : %d : %qd : %qd : %d : %ld\r\n", 3,(size_t)111, (int_32_t)222, (int_64_t)333, (int_64_t)444, (int)555, (int)666);
		__format_v(L"%*Id : %Id\r\n", 5,(size_t)1024, (size_t)2048);

}

/*****************************************************************************************************************/

typedef struct __ac_automaton_tag		arACAutomaton_t;
arACAutomaton_t*	AR_CreateACAutomaton();
void				AR_DestroyACAutomaton(arACAutomaton_t *atm);
bool_t				AR_InsertToACAutomaton(arACAutomaton_t *atm, const wchar_t *str, void *val);
bool_t				AR_RemoveFromACAutomaton(arACAutomaton_t *atm, const wchar_t *str);
bool_t				AR_BuildACAutomaton(arACAutomaton_t *atm);

bool_t				AR_FindFromACAutomaton(arACAutomaton_t *atm, const wchar_t *key, bool_t sub_str);



/*****************************************************************************************************************/




void itow_test()
{
		size_t i;
		wchar_t buf[1024];
		
		for(i = 2; i <= 16; ++i)
		{
				AR_u64tow_buf(buf, 1024, 0x1234567890, i);
				AR_printf(L"%ls\r\n", buf);
		}

		for(i = 2; i <= 16; ++i)
		{
				AR_i64tow_buf(buf, 1024, -0x1234567890, i);
				AR_printf(L"%ls\r\n", buf);
		}
}


void str_test1()
{

		{
				int_64_t		num;
				const wchar_t *s, *p;
				s = L"-11111111111111111111111111111111";
				
				p = AR_wtoi64(s, &num, 10);
				

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %I64d\r\n", num);
//				printf("_wcstoi64 == %I64d\r\n", _wcstoi64(s, (wchar_t**)&next, 10));
				//AR_printf(L"next == %ls\r\n", next);
		}
		

		{
				uint_32_t		num;
				const wchar_t *s = L"11111111111111111111111111111111";

				const wchar_t *p = AR_wtou32(s, &num, 10);
				const wchar_t *next;

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %u\r\n", num);
				printf("strtoul == %u\r\n", wcstoul(s, (wchar_t**)&next, 10));
				AR_printf(L"next == %ls\r\n", next);
		}


		{
				int_32_t		num;
				const wchar_t *s = L"-11111111111111111111111111111111";
				
				const wchar_t *p = AR_wtoi32(s, &num, 10);

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %d\r\n", num);
				printf("wcstol == %d\r\n", wcstol(s, NULL, 10));

		}


		{
				int_32_t		num;
				const wchar_t *s = L"11111111111111111111111111111111";
				
				const wchar_t *p = AR_wtoi32(s, &num, 10);

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %d\r\n", num);
				printf("wcstol == %d\r\n", wcstol(s, NULL, 10));

		}

		{
				int_32_t		num;
				const wchar_t *s = L"0x468321xyz";
				
				const wchar_t *p = AR_wtoi32(s, &num, 0);

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %d\r\n", num);
				printf("wcstol == %d\r\n", wcstol(s, NULL, 10));


		}


		{
				int_32_t		num;
				const wchar_t *s = L"-0x468321xyz";
				
				const wchar_t *p = AR_wtoi32(s, &num, 0);

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %d\r\n", num);
				printf("wcstol == %d\r\n", wcstol(s, NULL, 10));
		}


		{
				int_32_t		num;
				const wchar_t *s = L"0464321xyz";
				
				const wchar_t *p = AR_wtoi32(s, &num, 0);

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %d\r\n", num);
				printf("wcstol == %d\r\n", wcstol(s, NULL, 10));
		}


				{
				int_32_t		num;
				const wchar_t *s = L"0464321xyz";
				
				const wchar_t *p = AR_wtoi32(s, &num, 0);

				AR_printf(L"next == %ls\r\n", p);
				printf("num == %d\r\n", num);
				printf("wcstol == %d\r\n", wcstol(s, NULL, 10));
		}
#if(0)
#endif
}




void str_test3()
{
		int_t len;

		len = AR_scwprintf(L"%ls : %ls : %ls\r\n", L"ABCDEF猪八戒",L"ABCDEF猪八戒",L"ABCDEF猪八戒");

		printf("len == %d\r\n", len);

}

void str_test4()
{
		const wchar_t *p;
		wchar_t buf[] = L"  abcdefgh    ";
		p = AR_wcstrim_right(buf, L" abcdefgh");
		wprintf(L"%ls\r\n", p);

}

void str_test5()
{
		//AR_report();
		AR_printf(L"%lld  :  %ld\r\n", (uint_64_t)345,(uint_64_t)453);

}


static void test_bittest()
{
		uint_32_t x = 0;

		x = (uint_32_t)AR_BIT_MARK(32);

		AR_BIT_SET(x,0);


		AR_BIT_CLR(x,0);
/*
		

		if(AR_BIT_TEST(x, 3)){printf("xxx\r\n");}

		AR_BIT_CLR(x, 48);
*/


}

void bug_test()
{
		char c = 'c';
        AR_scwprintf(L"%hc\r\n", c);
}


int_t __cmp_size_t(const void *l, const void *r)
{
		return AR_CMP(*(size_t*)l, *(size_t*)r);

}

int __cmp_size_t_2(const void *l, const void *r)
{
		return (int)AR_CMP(*(size_t*)l, *(size_t*)r);

}


#define  SORT_TEST_CNT (30*1024 * 1024)

//#define  SORT_TEST_CNT (30)
#if(0)
void sort_test()
{
		size_t *vi = AR_NEWARR(size_t, SORT_TEST_CNT);
		int i;
		DWORD beg,end;
		int_t cnt = 3;
		AR_srand(time(NULL));

		__int64 n = (__int64)SORT_TEST_CNT;
		while(cnt-- > 0)
		{
				for(i = 0; i < SORT_TEST_CNT; ++i)
				{
						vi[i] = AR_rand32() ;//% 40960;
						
						//vi[i] = (size_t)--n;

				}

				printf("-----------beg------------\r\n");
				beg = GetTickCount();
				
				AR_qsort(vi,SORT_TEST_CNT , sizeof(size_t),__cmp_size_t);
				//qsort(vi, SORT_TEST_CNT, sizeof(size_t), __cmp_size_t_2);

				

				//std::sort(vi, vi + SORT_TEST_CNT);

				end = GetTickCount();

				printf("elapsed == %u\r\n", end - beg);
				printf("-----------end------------\r\n");

				

				for(i = 1; i < SORT_TEST_CNT; ++i)
				{
						if(vi[i-1] <= vi[i])
						{

						}else
						{
								system("pause");
								abort();
						}
				}
		}

}
#endif

void search_test()
{
		int i;
		int arr[] = {0,1,2,3,4,5,6,7,8,9};
		
		for(i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
		{
				int_t m = AR_bsearch(&i, arr,sizeof(arr)/sizeof(arr[0]), sizeof(int), __cmp_size_t);
		
				printf("arr[%d] == %d\r\n", m,arr[m]);
		}



}


void str_test6()
{
		wprintf(L"%ls\r\n", L"\\\"=\\\"");

}

void escstr_test0()
{

		//const wchar_t *s = L"\\a\\b\\c\\d\\s";
		wchar_t buf[1024];

		while(true)
		{
				_getws(buf);
				if(AR_wcscmp(buf, L"quit") == 0)break;

				wchar_t *d = AR_str_to_escstr(buf);

				wprintf(L"escape == %ls\r\n", d);
				AR_DEL(d);

		}
}


void escstr_test1()
{
		wchar_t tmp[1024];

		while(true)
		{
				_getws(tmp);
				if(AR_wcscmp(tmp, L"quit") == 0)break;

				arEscStrErr_t	err;
				wchar_t *d = AR_escstr_to_str(tmp, &err);
				
				wchar_t buf[1024];
				if(err.type == AR_ESCSTR_ERR_VALUE)
				{
						AR_swprintf(buf, 1024, L"invalid value %qd\r\n", err.value);
				}else if(err.type == AR_ESCSTR_ERR_CHAR)
				{
						AR_swprintf(buf, 1024, L"invalid input %ls\r\n", err.pos);
				}else
				{
						AR_swprintf(buf, 1024, L"%ls\r\n", d);
				}

				//wprintf(L"string == %ls\r\n", d);
				::MessageBoxW(NULL, buf, 0,0);
				
				AR_DEL(d);

		}

}




void escstr_test_buf0()
{

		//const wchar_t *s = L"\\a\\b\\c\\d\\s";
		wchar_t buf[1024], tmp[1024];

		while(true)
		{
				_getws(buf);
				if(AR_wcscmp(buf, L"quit") == 0)break;

				int_t l = AR_str_to_escstr_buf(tmp, 1024, buf);

				AR_ASSERT(l >= 0);
				
				wprintf(L"escape == %ls\r\n", tmp);
				

		}
}



void escstr_test_buf1()
{
		wchar_t tmp[1024], out[1024];

		while(true)
		{
				_getws(tmp);
				if(AR_wcscmp(tmp, L"quit") == 0)break;

				arEscStrErr_t	err;
				int_t l = AR_escstr_to_str_buf(out, 1024, tmp, &err);
				
				wchar_t buf[1024];
				if(err.type == AR_ESCSTR_ERR_BUFFER)
				{
						AR_ASSERT(false);
						
				}else if(err.type == AR_ESCSTR_ERR_VALUE)
				{
						AR_swprintf(buf, 1024, L"invalid value %qd\r\n", err.value);
				}else if(err.type == AR_ESCSTR_ERR_CHAR)
				{
						AR_swprintf(buf, 1024, L"invalid input %ls\r\n", err.pos);
				}else
				{
						AR_swprintf(buf, 1024, L"%ls\r\n", out);
				}

				//wprintf(L"string == %ls\r\n", d);
				::MessageBoxW(NULL, buf, 0,0);
				
				

		}

}







void buffer_test()
{
		arBuffer_t		*buffer;
		
		buffer = AR_CreateBuffer(0);

		FILE *f = fopen("d:\\temp\\lcc.rar", "rb");
		FILE *tmp = fopen("d:\\temp\\tmp.rar", "wb");
		assert(f != NULL && tmp != NULL);

		byte_t buf[384];
		
		while(!ferror(f) && !feof(f))
		{
				size_t rn = fread(buf, sizeof(byte_t), sizeof(buf), f);
				if(rn == 0)break;
				AR_InsertBuffer(buffer, buf, rn);

				if(AR_GetBufferAvailable(buffer) > 4096)
				{
						fwrite((void*)AR_GetBufferData(buffer), 1, 4096, tmp);
						AR_EraseBuffer(buffer, 4096);
				}
		}

		fclose(f);

		if(AR_GetBufferAvailable(buffer) > 0)
		{
				fwrite((void*)AR_GetBufferData(buffer), 1, AR_GetBufferAvailable(buffer), tmp);
				AR_EraseBuffer(buffer, AR_GetBufferAvailable(buffer));
		}

		fclose(tmp);
		
		AR_DestroyBuffer(buffer);

}




void com_timer_test()
{
		uint_64_t		beg = AR_GetTime_Milliseconds();
		AR_Sleep(1000);
		uint_64_t		end = AR_GetTime_Milliseconds();

		AR_printf(L"elapsed == %qd\r\n", end - beg);

}



void com_str_test_vscwprintf()
{
		int_t l = AR_scwprintf(L"%C : %C : %C : %C\r\n", L'a', L'b', L'c', L'd');
		printf("l == %d\r\n", l);
}

void com_str_test_cmp()
{
		printf("AR_stricmp == %d\r\n", AR_stricmp("abcdef", "abcdefg"));
		printf("AR_strnicmp == %d\r\n", AR_strnicmp("abcdef", "abcdefg", 3));

		printf("AR_wcsicmp == %d\r\n", AR_wcsicmp(L"abcdef", L"abcdefg"));
		printf("AR_wcsnicmp == %d\r\n", AR_wcsnicmp(L"abcdef", L"abcdefg", 3));
}


void str_tbl_test()
{
		arStringTable_t	*tbl =	AR_CreateStrTable(1);

		const wchar_t *a, *b;

		a = AR_GetString(tbl, L"abc");
		b = AR_GetString(tbl, L"abc");


		AR_ASSERT(a == b);


}

#if(0)
void kmp_test()
{
		const wchar_t *s = L"abcdef";
		const wchar_t *p = L"c";
		size_t	n = AR_wcslen(s);
		AR_printf(L"%ls\r\n", AR_wcsstr_kmp(s,p));

		AR_printf(L"%ls\r\n", AR_wcsstr_kmp_s(s,s + n,p));
}
#endif

const wchar_t *AR_wcsstr_ex(const wchar_t *s, const wchar_t *p)
{
		for(s; *s != L'\0'; ++s)
		{
				size_t i;
				for(i = 0; p[i] != L'\0' && s[i] != L'\0' && p[i] == s[i]; ++i);

				if(p[i] == L'\0')return s;
		}

		return NULL;
		
}

#if(0)
void kmp_test2()
{
		const wchar_t *src = NULL;//__load_txt(L"z:\\1.txt");

		//AR_printf(L"%ls\r\n",src);

		for(int a = 0; a < 3; ++a)
		{
				const wchar_t *s = src;
				const wchar_t *p = L"abcdefhigklmnopqrstuvwxyz";
				size_t m = AR_wcslen(p);

				uint_64_t beg = AR_GetTime_Milliseconds();
				size_t cnt = 0;
				while((s = AR_wcsstr_ex(s,p)) != NULL)
				{
						s += m;
						cnt ++;
				}
				uint_64_t end = AR_GetTime_Milliseconds();
				AR_printf(L"elapsed == %qd match == %Id\r\n", end - beg, cnt);
		}
		
		getchar();

		for(int a = 0; a < 3; ++a)
		{
				const wchar_t *s = src;
				const wchar_t *p = L"abcdefhigklmnopqrstuvwxyz";
				size_t m = AR_wcslen(p);
				uint_64_t beg = AR_GetTime_Milliseconds();
				size_t cnt = 0;
				while((s = AR_wcsstr_kmp(s,p)) != NULL)
				{
						s += m;
						cnt ++;
				}
				uint_64_t end = AR_GetTime_Milliseconds();
				AR_printf(L"elapsed == %qd match == %d\r\n", end - beg, cnt);
		}


		AR_DEL(src);
		getchar();
}

#endif

#if(AR_COMPILER == AR_VC_LEGACY || AR_COMPILER == AR_VC)

static void test_align()
{
#pragma pack(push, 16)
		//32 actual align == 4
		//64 actual align == 8

		struct test
		{
				char a;			//offset == 0, 占用1字节
				//char __pad1[3];
				int  b;			//填充前offset == 1,A =4, A - 1 % A == 3,则补充3字节，填充后，offset = 4,
				long c;			//offset ==8 , A == 4,  8 % 4 == 0,						无填充
				short d;		//offset == 12, A == 2 12 % 2 == 0,						无填充
				//char __pad2[2];
				int *p;			//填充前offset == 14, A = 8, 14 % 8 == 6, A-6 == 2，   填充2,填充后，offset == 16, 占8字节
		};
#pragma pack(pop)
		
		printf("a == %d\r\n", AR_OFFSETOF(struct test, a));
		printf("b == %d\r\n", AR_OFFSETOF(struct test, b));
		printf("c == %d\r\n", AR_OFFSETOF(struct test, c));
		printf("d == %d\r\n", AR_OFFSETOF(struct test, d));
		printf("p == %d\r\n", AR_OFFSETOF(struct test, p));


		
		AR_printf(L"sizeof(test) == %d\r\n", sizeof(test));
}



static void test_align2()
{
#pragma pack(push,16)
		struct test
		{
				char	a;		//offset == 0, 占用1字节
				//char __pad[1];
				short	b;		//填充前 offset == 1, A = 2; 1 % A = 1; A-1 = 1; 填充1后，offset == 2;
				int		c;		//offset == 4, A = 4; 4 % 4 == 0
				long	d;		//offset == 8, A = 4; 8 % 4 == 0
				int		*p;		//offset == 12, A = 4; 12 % 4 == 0
		};
#pragma pack(pop)
		
		printf("a == %d\r\n", AR_OFFSETOF(struct test, a));
		printf("b == %d\r\n", AR_OFFSETOF(struct test, b));
		printf("c == %d\r\n", AR_OFFSETOF(struct test, c));
		printf("d == %d\r\n", AR_OFFSETOF(struct test, d));
		printf("p == %d\r\n", AR_OFFSETOF(struct test, p));


		
		AR_printf(L"sizeof(test) == %d\r\n", sizeof(test));
}


static void test_align3()
{

#pragma pack(push,16)
		struct test
		{
				int		a;
				double	b;
				char	c;
		};
#pragma pack(pop)

		
		printf("a == %d\r\n", AR_OFFSETOF(struct test, a));
		printf("b == %d\r\n", AR_OFFSETOF(struct test, b));
		printf("c == %d\r\n", AR_OFFSETOF(struct test, c));


		
		AR_printf(L"sizeof(test) == %d\r\n", sizeof(test));
}



#else

#define test_align
#define test_align2

#endif



/*
t_uint32 ByteOrder::FlipBytes(t_uint32 val)
{
		return (
				((val >> 24) &0x000000FF)|
				((val >> 8) & 0x0000FF00)|
				((val << 8) & 0x00FF0000)|
				((val << 24) & 0xFF000000)
				);
}

t_uint64 ByteOrder::FlipBytes(t_uint64 val)
{
		t_uint32 hi = t_uint32( val >> 32);
		t_uint32 lo = t_uint32(val  & 0xFFFFFFFF);

		t_uint64 fhi = t_uint64(FlipBytes(hi));
		t_uint64 flo = t_uint64(FlipBytes(lo));

		flo <<= 32;
		return (flo | fhi);

}
*/


#if defined(ARCH_LITTLE_ENDIAN)

#define AR_LTON_16(_n)			AR_BYTEFLIP_16((_n))

#define AR_LTON_32(_n)			AR_BYTEFLIP_32((_n))

#define AR_LTON_64(_n)			AR_BYTEFLIP_64((_n))

#else

#define AR_LTON_16(_n)			(_n)

#define AR_LTON_32(_n)			(_n)

#define AR_LTON_64(_n)			(_n)

#endif





void byte_filp_test()
{
		int_16_t		val16 = -0x1234;

		int_32_t		val32 = -0x12345678;
		
		int_64_t		val64 = -0xAA12345678ABCDEF;


		AR_printf(L"%d\r\n", val16);
		AR_printf(L"%d\r\n", val32);
		AR_printf(L"%qd\r\n", val64);

		
		AR_printf(L"%d\r\n", AR_BYTEFLIP_16(val16));
		AR_printf(L"%d\r\n", AR_BYTEFLIP_32(val32));
		AR_printf(L"%qd\r\n", AR_BYTEFLIP_64(val64));

		AR_printf(L"%d\r\n", AR_BYTEFLIP_16(AR_BYTEFLIP_16(val16)));
		AR_printf(L"%d\r\n", AR_BYTEFLIP_32(AR_BYTEFLIP_32(val32)));
		AR_printf(L"%qd\r\n", AR_BYTEFLIP_64(AR_BYTEFLIP_64(val64)));

		printf("------------------------------\r\n");

		uint_16_t		uval16 = 0x1234;

		uint_32_t		uval32 = 0x12345678;
		
		uint_64_t		uval64 = 0xAA12345678ABCDEF;


		AR_printf(L"0x%X\r\n", uval16);
		AR_printf(L"0x%X\r\n", uval32);
		AR_printf(L"0x%qX\r\n", uval64);
		printf("------------------------------\r\n");
		
		AR_printf(L"0x%X\r\n", AR_BYTEFLIP_U16(uval16));
		AR_printf(L"0x%X\r\n", AR_BYTEFLIP_U32(uval32));
		AR_printf(L"0x%qX\r\n", AR_BYTEFLIP_U64(uval64));
		printf("------------------------------\r\n");

		AR_printf(L"0x%X\r\n", AR_BYTEFLIP_U16(AR_BYTEFLIP_U16(uval16)));
		AR_printf(L"0x%X\r\n", AR_BYTEFLIP_U32(AR_BYTEFLIP_U32(uval32)));
		AR_printf(L"0x%qX\r\n", AR_BYTEFLIP_U64(AR_BYTEFLIP_U64(uval64)));
		printf("------------------------------\r\n");


		


		
		//AR_printf(L"0x%X\r\n", AR_BYTEFLIP_32(val32));
		//AR_printf(L"0x%qX\r\n", AR_BYTEFLIP_64(val64));



/*
		AR_printf(L"0x%X\r\n", AR_LTON_16(val16));
		AR_printf(L"0x%X\r\n", AR_LTON_32(val32));
		AR_printf(L"0x%qX\r\n", AR_LTON_64(val64));
*/

}


static void shuffle(int_t *arr, size_t n)
{
		int_t i;
		for(i = (int_t)n - 1; i > 0; --i)
		{
				int_t idx = rand()%i;
				int_t t = arr[i];
				arr[i] = arr[idx];
				arr[idx] = t;
		}
}

void algo_test1()
{
		int_t a[] = {1,2,3,4,5,6}, i = 0;

		shuffle(a, sizeof(a)/sizeof(a[0]));

		for(i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
		{
				AR_printf(L"%d ", a[i]);
		}

		AR_printf(L"\r\n");

}


static int_t cmp_int(const void *l, const void *r)
{
		int a = *(int*)l;
		int b = *(int*)r;
		return AR_CMP(a,b);
}
void bsearch_test()
{
		size_t i;
		AR_printf(L"%ls\r\n", L"bsearch test");
		
		int arr[] = {0,1, 4, 42, 55, 67, 87, 100, 245};
		
		int key = 42;
		AR_ASSERT(AR_bsearch(&key, arr, AR_NELEMS(arr), sizeof(int), cmp_int) == 3);
		key = 43;
		AR_ASSERT(AR_bsearch(&key, arr, AR_NELEMS(arr), sizeof(int), cmp_int) == -1);

		for(i = 0; i < AR_NELEMS(arr); ++i)
		{
				int_t result;
				key = arr[i];
				result = AR_bsearch(&key, arr, AR_NELEMS(arr), sizeof(int), cmp_int);
				AR_printf(L"key == %d : idx == %d\r\n", key, result);
				AR_ASSERT(result == i);
		}
		
		//assertEquals(2, Util.binarySearch(arrayWith42, 42));
		//assertEquals(-1, Util.binarySearch(arrayWith42, 43));
}




void float_test()
{
		
		AR_printf(L"%f\r\n", AR_FLT_MOD(5,0.8));
		AR_printf(L"%f\r\n", AR_FLT_MOD(5,0.8));

		AR_printf(L"%f\r\n", AR_DBL_MOD(5,4));
		AR_printf(L"%f\r\n", AR_DBL_MOD(5,4));

		AR_ASSERT(AR_DBL_EQ(AR_DBL_MOD(5,4), 1));
		AR_ASSERT(AR_DBL_EQ(AR_DBL_MOD(5,3), 2));
		AR_ASSERT(AR_DBL_EQ(AR_DBL_MOD(4,5), 4));


		double x = 0.11111111111111111111111111111;
		double y = 0.1111111111111111111111;

		AR_printf(L"x == y ? %ls\r\n", AR_DBL_LEEQ(x , y) ? L"true" : L"false");

		AR_printf(L"%.30f\r\n", DBL_EPSILON);
		AR_printf(L"%.30f\r\n", exp(3.0f));


}


static void float_test_2()
{
		const wchar_t *s = L"0123";
		
		AR_ASSERT(!AR_wcs_is_float(s, s + AR_wcslen(s)));


		s = L"0.123e";
		
		AR_ASSERT(!AR_wcs_is_float(s, s + AR_wcslen(s)));

		s = L"0.123e20";
		AR_ASSERT(AR_wcs_is_float(s, s + AR_wcslen(s)));

		s = L"0.123e+20";
		AR_ASSERT(AR_wcs_is_float(s, s + AR_wcslen(s)));

		s = L"0.123e-20";
		AR_ASSERT(AR_wcs_is_float(s, s + AR_wcslen(s)));


		s = L"0.123e20";
		double n = 0.0;

		s = AR_wtod_s(s, s + wcslen(s), &n);


		s = L"0.123e+20";
		n = 0.0;

		s = AR_wtod_s(s, s + wcslen(s), &n);


		s = L"0.123e-20";
		n = 0.0;

		s = AR_wtod_s(s, s + wcslen(s), &n);


		s = L"0.123e";
		n = 0.0;

		s = AR_wtod_s(s, s + wcslen(s), &n);

		{
				s = L"0.123e1";
				AR_ASSERT(!AR_wcs_is_int(s, s + wcslen(s)));

				s = L"0.123e";
				AR_ASSERT(AR_wcs_is_int(s, s + wcslen(s)));


				s = L"0x468321xyz";
				AR_ASSERT(AR_wcs_is_int(s, s + wcslen(s)));

				s = L"0464321xyz";
				AR_ASSERT(AR_wcs_is_int(s, s + wcslen(s)));

				s = L"0464321xyz";
				AR_ASSERT(AR_wcs_is_int(s, s + wcslen(s)));

				s = L"11111111111111111111111111111111";
				AR_ASSERT(!AR_wcs_is_int(s, s + wcslen(s)));

				s = L"-11111111111111111111111111111111";
				AR_ASSERT(!AR_wcs_is_int(s, s + wcslen(s)));

				s = L"11111111111111111111111111111111";
				AR_ASSERT(!AR_wcs_is_int(s, s + wcslen(s)));

				s = L"-0x468321xyz";
				AR_ASSERT(AR_wcs_is_int(s, s + wcslen(s)));



		}

		

		int x=33;

		
}



char*			AR_strupr(char *s);
char*			AR_strlwr(char *s);
char*			AR_strnlwr(char *s, size_t count);
char*			AR_strnupr(char *s, size_t count);
wchar_t*			AR_wcsupr(wchar_t *s);
wchar_t*			AR_wcslwr(wchar_t *s);
wchar_t*			AR_wcsnlwr(wchar_t *s, size_t count);
wchar_t*			AR_wcsnupr(wchar_t *s, size_t count);

void str_test7()
{
		{
		char s[] = "abcdefg";
		AR_printf(L"%hs\r\n", AR_strupr(s));
		}


		{
		char s[] = "ABCDEFG";
		AR_printf(L"%hs\r\n", AR_strlwr(s));
		}


		{
		wchar_t s[] = L"abcdefg";
		AR_printf(L"%ls\r\n", AR_wcsupr(s));
		}


		{
		wchar_t s[] = L"ABCDEFG";
		AR_printf(L"%ls\r\n", AR_wcslwr(s));
		}


		{
		char s[] = "abcdefg";
		AR_printf(L"%hs\r\n", AR_strnupr(s, 3));
		}

		{
		char s[] = "ABCDEFG";
		AR_printf(L"%hs\r\n", AR_strnlwr(s, 3));
		}

		{
		wchar_t s[] = L"abcdefg";
		AR_printf(L"%ls\r\n", AR_wcsnupr(s, 3));
		}

		{
		wchar_t s[] = L"ABCDEFG";
		AR_printf(L"%ls\r\n", AR_wcsnlwr(s, 3));
		}

}


void com_str_test_vcprintf()
{
		//const char *s = "abc";
		int_t n;
		n = AR_scwprintf(L"%33s", L"abc");
		n = AR_scwprintf(L"%.10s", L"abc");

}


void com_test_srpintf()
{
		printf("%llu\r\n", 0xffffffffffffffffui64);


}






void escstr_n_test1()
{
		wchar_t tmp[1024];

		while(true)
		{
				_getws(tmp);
				if(AR_wcscmp(tmp, L"quit") == 0)break;

				arEscStrErr_t	err;
				wchar_t *d = AR_escstr_to_str_n(tmp, rand() % 100, &err);
				
				wchar_t buf[1024];
				if(err.type == AR_ESCSTR_ERR_VALUE)
				{
						AR_swprintf(buf, 1024, L"invalid value %qd\r\n", err.value);
				}else if(err.type == AR_ESCSTR_ERR_CHAR)
				{
						AR_swprintf(buf, 1024, L"invalid input %ls\r\n", err.pos);
				}else
				{
						AR_swprintf(buf, 1024, L"%ls\r\n", d);
				}

				//wprintf(L"string == %ls\r\n", d);
				::MessageBoxW(NULL, buf, 0,0);
				
				AR_DEL(d);

		}

}


void escstr_n_test0()
{

		//const wchar_t *s = L"\\a\\b\\c\\d\\s";
		wchar_t buf[1024];

		while(true)
		{
				_getws(buf);
				if(AR_wcscmp(buf, L"quit") == 0)break;

				wchar_t *d = AR_str_to_escstr_n(buf, 10);

				wprintf(L"escape == %ls\r\n", d);
				AR_DEL(d);

		}
}

void align_test()
{
		byte_t *p1 = (byte_t*)AR_malloc(37);
		byte_t *p2 = (byte_t*)AR_malloc(37);

		AR_memset(p1, 0, 37);
		AR_memset(p2, 0xdd, 37);

		AR_memswap(p1,p2, 37);

}



void text_test_load()
{

		arBuffer_t *buf = AR_CreateBuffer(0);
		arString_t *str = AR_CreateString();
		if(AR_LoadBomTextFromBinary(buf, NULL, str) != AR_S_YES)
		{
				AR_ASSERT(false);
		}

		AR_DestroyString(str);
		AR_DestroyBuffer(buf);
		buf = NULL;

}

void text_test_save()
{

#define INPUT_FILE		L"..\\..\\..\\misc\\txt_enc_test\\empty_ascii.txt"
//#define INPUT_FILE		L"D:\\User\\Temp\\Temp\\output2.txt"
#define OUTPUT_FILE		L"D:\\test.txt"
#define OUTPUT_TYPE		AR_TXT_BOM_UTF_8

		arString_t *str = AR_CreateString();
		
		arTxtBom_t bom;

		if(AR_LoadBomTextFile(INPUT_FILE,&bom, str) != AR_S_YES)
		{
				AR_ASSERT(false);
		}


		if(AR_SaveBomTextFile(OUTPUT_FILE, OUTPUT_TYPE, AR_GetStringCString(str)) != AR_S_YES)
		{
				AR_ASSERT(false);
		}


		
		if(AR_LoadBomTextFile(OUTPUT_FILE, &bom, str) != AR_S_YES)
		{
				AR_ASSERT(false);
		}

		AR_ASSERT(bom == OUTPUT_TYPE);


		AR_DestroyString(str);
}


static void str_vfmt_test(arString_t *str, const wchar_t *fmt, ...)
{
		va_list args;

		AR_va_start(args, fmt);
		AR_AppendVFormatString(str, fmt, args);

		
		//printf("%ls\r\n", AR_GetStringCString(str));

		AR_va_end(args);


		
}


void str_test8()
{
		arString_t *str	 = AR_CreateString();

		str_vfmt_test(str, L"%ls:%d:%f\r\n", L"aaa", 33, 3.14159265f);



		AR_DestroyString(str);
		str = NULL;
		
}



void str_test9()
{
		arString_t *str	 = AR_CreateString();

		for(int i = 0; i < 10; ++i)
		{

				str_vfmt_test(str, L"%ls:%d:%f\r\n", L"aaa", 33, 3.14159265f);
				str_vfmt_test(str, L"%ls", L"\r\n");
		}

		printf("%ls\r\n", AR_GetStringCString(str));

		AR_DestroyString(str);
		str = NULL;
		
}

void rand_test()
{
		AR_srand(time(NULL));
		for(size_t i = 0; i <10; ++i)
		{
				AR_printf(L"%f\r\n", AR_rand_dbl());
				AR_Sleep(1500);
		}
}


/*
size_t AR_base64_encode(byte_t  *out, size_t olen, const byte_t *input, size_t ilen);
size_t AR_base64_decode(byte_t  *out, size_t olen, const byte_t *input, size_t ilen);
*/
static void base64_test()
{
		static const wchar_t *src = L"中国字！！~~中国字~~~！！！中文网中文！";

		size_t n = AR_base64_encode(NULL, 0, (byte_t*)src, AR_wcslen(src) * sizeof(wchar_t));

		AR_printf(L"src == %d, n = %d\r\n", AR_wcslen(src), n);

		char *o = new char[n + 1];

		n = AR_base64_encode((byte_t*)o, n + 1, (byte_t*)src, AR_wcslen(src) * sizeof(wchar_t));
		AR_printf(L"n = %d\r\n", n);
		o[n] = 0;

		AR_printf(L"%hs\r\n", o);

		

		n = AR_base64_decode(NULL, 0, (const byte_t*)o, AR_strlen(o));
		AR_printf(L"decode n = %d\r\n", n);
		
		byte_t *buf = new byte_t[n + 2];
		memset(buf, 0, n + 1);
		
		n = AR_base64_decode(buf, n + 2, (const byte_t*)o, AR_strlen(o));
		AR_printf(L"decode n = %d\r\n", n);
		AR_printf(L"%ls\r\n", buf);
		
		AR_ASSERT(AR_wcscmp((const wchar_t*)buf, src) == 0);
}

static void base64_test2()
{
		const char *src = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";


		size_t n = AR_base64_encode(NULL, 0, (byte_t*)src, AR_strlen(src) * sizeof(char));

		AR_printf(L"src == %d, n = %d\r\n", AR_strlen(src), n);

		char *o = new char[n + 1];

		n = AR_base64_encode((byte_t*)o, n + 1, (byte_t*)src, AR_strlen(src) * sizeof(char));
		AR_printf(L"n = %d\r\n", n);
		o[n] = 0;

		AR_printf(L"%hs\r\n", o);

		

		n = AR_base64_decode(NULL, 0, (const byte_t*)o, AR_strlen(o));
		AR_printf(L"decode n = %d\r\n", n);
		
		byte_t *buf = new byte_t[n + 2];
		memset(buf, 0, n + 1);
		
		n = AR_base64_decode(buf, n + 2, (const byte_t*)o, AR_strlen(o));
		AR_printf(L"decode n = %d\r\n", n);
		AR_printf(L"%ls\r\n", buf);
		
		AR_ASSERT(AR_strcmp((const char*)buf, src) == 0);



}

void com_test()
{

		//bsearch_test();
		//algo_test1();
		
		//str_test();
		//str_test1();
		//str_test2();
		//str_test3();
		//str_test4();
		//str_test5();
		//str_test6();
		//str_test7();
		//str_test8();
		//str_test9();

		//com_test3();
		//com_conv();
		//com_conv2();
		//com_hash_test();

		//com_vscwprintf_test();
		//com_vscwprintf_test2();
		//str_test();
		//itow_test();

		//test_bittest();
		//bug_test();

		//sort_test();
		//search_test();

		//escstr_test0();
		//escstr_test1();

		//escstr_test_buf0();

		//escstr_test_buf1();

		//buffer_test();

		//com_timer_test();

		//com_str_test_vscwprintf();

		//com_str_test_cmp();
		//str_tbl_test();

		//kmp_test();
		//kmp_test2();

		//test_align3();

		//byte_filp_test();

		//float_test();
		

		//com_str_test_vcprintf();
		//com_test_srpintf();

		//escstr_n_test1();
		//escstr_n_test0();
		//align_test();
		//text_test_save();
		//text_test_load();

		//rand_test();
		
		//base64_test();
		//base64_test2();

		float_test_2();
		
}



AR_NAMESPACE_END

#endif
