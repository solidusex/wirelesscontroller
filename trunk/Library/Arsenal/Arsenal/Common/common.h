/*
 * The Arsenal Library
 * Copyright (c) 2009 by Solidus
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express
 * or implied warranty.
 *
 */
#ifndef AR_COMMON_H
#define AR_COMMON_H


#include "config.h"




AR_NAMESPACE_BEGIN


/*******************************************************************************error code********************************/

#include "status.h"






/*
common.h -- misc founctions used in Arsenal

*/

const wchar_t*	AR_Version();


/*******************************************************************************init********************************/

typedef void	(AR_STDCALL *AR_error_func_t)(int_t level, const wchar_t *msg, void *ctx);
typedef void	(AR_STDCALL *AR_print_func_t)(const wchar_t *msg, void *ctx);






typedef struct __arsenal_io_context_tag
{
		AR_error_func_t	on_error;
		AR_print_func_t	on_print;
		void			*ctx;
}arIOCtx_t;


typedef struct __ar_init_tag
{
		arIOCtx_t		global_io_ctx;
}arInit_t;






arStatus_t AR_CommonInit(const arInit_t *info);
arStatus_t AR_CommonUnInit();

arIOCtx_t*	AR_global_ioctx();

arStatus_t	AR_printf(const wchar_t *msg,...);


/*库内部错误为负数*/
#define AR_ERR_MESSAGE		((int_t)-0x0099)
#define AR_ERR_WARNING		((int_t)-0x0100)
#define AR_ERR_FATAL		((int_t)-0x0101)



arStatus_t	AR_error(int_t level, const wchar_t *msg, ...);



arStatus_t	AR_printf_ctx(arIOCtx_t *ctx, const wchar_t *msg,...);
arStatus_t	AR_error_ctx(arIOCtx_t *ctx, int_t level, const wchar_t *msg, ...);





/***********************************************************************debug************************************************/

/*
 static const wchar_t *AR_BUILD_TIME = AR_WSTR(__DATE__) AR_WSTR(" ") AR_WSTR(__TIME__);
 */



#define AR_report()		AR_printf(L"File (%ls) : Line (%" AR_PLAT_INT_FMT L"d) : Function (%ls)\r\n", AR_WSTR(__FILE__), (size_t)__LINE__, AR_WSTR(AR_FUNC_NAME))

void	AR_check(bool_t cond, const wchar_t *fmt, ...);

#define AR_CHECK		AR_check

#define AR_STATIC_CHECK(_expr)	do {typedef char __static_assert_t[ (bool_t)(_expr) ]; }while(0)






#if defined(AR_DEBUG)

#define AR_DPRINT				AR_printf

#define AR_ASSERT(_cond)		assert((_cond))


#else

#define AR_DPRINT

#define AR_ASSERT(_cond)		/*(_cond)*/

#endif


#define AR_UNUSED(_e)			((void)(_e))



#if !defined(AR_DISABLE_LOG)

		#define AR_LOG					AR_printf

#else
		#define AR_LOG
	
#endif




/***********************************************************一些宏*********************************************************/


#define AR_MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))
#define AR_MIN(_a,_b) ((_a) < (_b) ? (_a) : (_b))


#define AR_CMP(_a,_b) ((_a) < (_b) ? -1 : ((_a) == (_b) ? 0 : 1))
/*行主映射*/
#define AR_TBL_IDX_R(_x, _y, _col_n) ((_x) * (_col_n) + (_y))


#define AR_NELEMS(_arr)	(sizeof((_arr))/sizeof((_arr)[0]))


static AR_INLINE const void* AR_GET_ELEM(const void *base, size_t width, size_t idx)
{
		AR_ASSERT(base != NULL && width > 0);
		return (const void*)((byte_t*)base + (width * idx));
}


#define AR_OFFSETOF(_ty, _filed)		((byte_t*)&((_ty*)0)->_filed) - ((byte_t*)(_ty*)0)

















/**********************************************************内存管理***************************************************************/

/*内存管理部分暂时只使用标准CRT，并不支持重定位标准存储分配函数，对管理可以依赖AR_USE_CRT_ALLOCFUNC宏控制，定义此宏，则使用当前CRT管理内存，否则
使用arHeap_t来管理堆
*/

#define AR_MEM_MAX_ALLOC_RETRY_COUNT	1000000

void	AR_InitMemory();
void	AR_UnInitMemory();




#if !defined(AR_USE_CRT_ALLOCFUNC)

void*	AR_malloc(size_t nbytes);
void*	AR_calloc(size_t num, size_t size);
void	AR_free(void *ptr);


#else


#define	AR_malloc		malloc
#define	AR_calloc		calloc

#define AR_free			free



#endif






#define AR_memset				memset
#define AR_memcpy				memcpy
#define AR_memcmp				memcmp
#define	AR_memmove				memmove
void	AR_memswap(void *a, void *b, size_t n);





#define AR_NEW(_type) ((_type*)AR_malloc(sizeof(_type)))
#define AR_NEW0(_type) ((_type*)AR_calloc(1, sizeof(_type)))
#define AR_NEWARR(_type, _n) ((_type*)AR_malloc(sizeof(_type) * (_n)))
#define AR_NEWARR0(_type, _n) ((_type*)AR_calloc((_n), sizeof(_type)))

/*
#define AR_REALLOC(_type, _ptr, _new_count) ((_type*)AR_realloc((_ptr), sizeof(_type) * (_new_count)))
*/


#define AR_DO_REALLOC(_type, _org_ptr, _new_cap, _copy_cnt, _status)	\
		do{																\
				_type *new_arr;											\
				new_arr = AR_NEWARR(_type, (_new_cap));					\
				if(new_arr == NULL)										\
				{														\
						(_status) = AR_E_NOMEM;							\
				}														\
				if((_copy_cnt) > 0 && (_org_ptr) != NULL)				\
				{														\
						AR_memcpy(new_arr, (_org_ptr), (_copy_cnt) * sizeof(_type));	\
				}																		\
				if((_org_ptr))															\
				{																		\
						AR_DEL((_org_ptr));												\
						(_org_ptr) = NULL;												\
				}																		\
				(_org_ptr) = new_arr;													\
				(_status) = AR_S_YES;													\
		}while(0);																		


#define AR_DEL(_ptr) AR_free((void*)(_ptr))














/***********************************************************字节序操作*********************************************************/




int_16_t		AR_BYTEFLIP_16(int_16_t val);
uint_16_t		AR_BYTEFLIP_U16(uint_16_t val);


int_32_t		AR_BYTEFLIP_32(int_32_t val);
uint_32_t		AR_BYTEFLIP_U32(uint_32_t val);


int_64_t		AR_BYTEFLIP_64(int_64_t val);
uint_64_t		AR_BYTEFLIP_U64(uint_64_t val);



#if defined(ARCH_LITTLE_ENDIAN)

		#define AR_LTON_16(_n)			AR_BYTEFLIP_16((_n))
		#define AR_LTON_32(_n)			AR_BYTEFLIP_32((_n))
		#define AR_LTON_64(_n)			AR_BYTEFLIP_64((_n))
		#define AR_LTON_U16(_n)			AR_BYTEFLIP_U16((_n))
		#define AR_LTON_U32(_n)			AR_BYTEFLIP_U32((_n))
		#define AR_LTON_U64(_n)			AR_BYTEFLIP_U64((_n))

		#define AR_NTOL_16(_n)			AR_BYTEFLIP_16((_n))
		#define AR_NTOL_32(_n)			AR_BYTEFLIP_32((_n))
		#define AR_NTOL_64(_n)			AR_BYTEFLIP_64((_n))
		#define AR_NTOL_U16(_n)			AR_BYTEFLIP_U16((_n))
		#define AR_NTOL_U32(_n)			AR_BYTEFLIP_U32((_n))
		#define AR_NTOL_U64(_n)			AR_BYTEFLIP_U64((_n))

#else

		#define AR_LTON_16(_n)			(_n)
		#define AR_LTON_32(_n)			(_n)
		#define AR_LTON_64(_n)			(_n)
		#define AR_LTON_U16(_n)			(_n)
		#define AR_LTON_U32(_n)			(_n)
		#define AR_LTON_U64(_n)			(_n)

		#define AR_NTOL_16(_n)			(_n)
		#define AR_NTOL_32(_n)			(_n)
		#define AR_NTOL_64(_n)			(_n)
		#define AR_NTOL_U16(_n)			(_n)
		#define AR_NTOL_U32(_n)			(_n)
		#define AR_NTOL_U64(_n)			(_n)


#endif














/**********************************************************algo*************************************************************/

/*#define AR_qsort		qsort*/



void	AR_qsort(void *base, size_t num, size_t width, int_t (*cmp_f)(const void*, const void*));
int_t	AR_bsearch(const void *key, const void *base, size_t num, size_t width, int_t (*cmp_f)(const void*, const void*));




/**********************************************************rand*************************************************************/
void			AR_srand(uint_64_t seed);

uint_32_t		AR_rand32();
uint_64_t		AR_rand64();
float			AR_rand_flt();
double			AR_rand_dbl();

/********************************************************CRT String*****************************************************************/



int_t			AR_stricmp(const char *l, const char *r);
int_t			AR_strnicmp(const char *l, const char *r, size_t n);
int_t			AR_wcsicmp(const wchar_t *l, const wchar_t *r);
int_t			AR_wcsnicmp(const wchar_t *l, const wchar_t *r, size_t n);




#define AR_strlen(_s)			strlen((_s))
#define AR_strcmp(_l, _r)		strcmp((_l), (_r))
#define AR_strncmp(_l, _r,_n)	strncmp((_l), (_r), (_n))
#define AR_strcpy(_d, _s)		strcpy((_d), (_s))
#define AR_strncpy(_d, _s, _n)	strncpy((_d), (_s), (_n))
#define AR_strchr(_s, _c)		strchr((_s),(_c))
#define AR_strstr(_s1, _s2)		strstr((_s1), (_s2))
#define AR_isalpha(_c)			isalpha((_c))
#define AR_isalnum(_c)			isalnum((_c))
#define AR_isdigit(_c)			isdigit((_c))
#define AR_tolower(_c)			tolower((_c))
#define AR_toupper(_c)			toupper((_c))
#define AR_isspace(_c)			isspace((_c))
#define AR_isgraph(_c)			isgraph((_c))
#define AR_isprint(_c)			isprint((_c))

char*			AR_strupr(char *s);
char*			AR_strlwr(char *s);
char*			AR_strnlwr(char *s, size_t count);
char*			AR_strnupr(char *s, size_t count);



#define AR_wcscmp(_l, _r)		wcscmp((_l), (_r))
#define AR_wcsncmp(_l, _r,_n)	wcsncmp((_l), (_r), (_n))
#define AR_wcslen(_s)			wcslen((_s))
#define AR_wcscpy(_d, _s)		wcscpy((_d), (_s))
#define AR_wcsncpy(_d, _s, _n)	wcsncpy((_d), (_s), (_n))
#define AR_wcschr(_s, _c)		wcschr((_s),(_c))
#define AR_wcsstr(_s1, _s2)		wcsstr((_s1), (_s2))
#define AR_iswalpha(_c)			iswalpha((_c))
#define AR_iswalnum(_c)			iswalnum((_c))
#define AR_iswdigit(_c)			iswdigit((_c))
#define AR_towlower(_c)			towlower((_c))
#define AR_towupper(_c)			towupper((_c))
#define AR_iswspace(_c)			iswspace((_c))
#define AR_iswgraph(_c)			iswgraph((_c))
#define AR_iswprint(_c)			iswprint((_c))


wchar_t*			AR_wcsupr(wchar_t *s);
wchar_t*			AR_wcslwr(wchar_t *s);
wchar_t*			AR_wcsnlwr(wchar_t *s, size_t count);
wchar_t*			AR_wcsnupr(wchar_t *s, size_t count);



wchar_t*		AR_wcsdup(const wchar_t *sour);

/*len == 0时返回空串L""*/
wchar_t*		AR_wcsndup(const wchar_t *sour, size_t len);


char*			AR_strdup(const char *sour);

/*len == 0时返回空串L""*/
char*			AR_strndup(const char *sour, size_t len);


const wchar_t*	AR_wcstrim(const wchar_t *in, const wchar_t *trim);
const wchar_t*	AR_wcstrim_space(const wchar_t *in);

wchar_t*		AR_wcscat(wchar_t *dest, const wchar_t *sour);
wchar_t*		AR_wcsncat(wchar_t *dest, const wchar_t *sour, size_t n);

const wchar_t*	AR_wtoi32(const wchar_t *in, int_32_t  *num, size_t base);
const wchar_t*	AR_wtou32(const wchar_t *in, uint_32_t *num, size_t base);
const wchar_t*	AR_wtoi64(const wchar_t *in, int_64_t  *num, size_t base);
const wchar_t*	AR_wtou64(const wchar_t *in, uint_64_t  *num, size_t base);

const wchar_t*	AR_wtod(const wchar_t *in, double *num);

/********************************************************************************************************************************************/
const wchar_t*	AR_wcstrim_s(const wchar_t *in, const wchar_t *end, const wchar_t *trim);
const wchar_t*	AR_wcstrim_space_s(const wchar_t *in, const wchar_t *end);

const wchar_t*	AR_wtoi32_s(const wchar_t *in, const wchar_t *end, int_32_t  *num, size_t base);
const wchar_t*	AR_wtou32_s(const wchar_t *in, const wchar_t *end, uint_32_t *num, size_t base);

const wchar_t*	AR_wtoi64_s(const wchar_t *in, const wchar_t *end, int_64_t  *num, size_t base);
const wchar_t*	AR_wtou64_s(const wchar_t *in, const wchar_t *end, uint_64_t  *num, size_t base);
const wchar_t*	AR_wtod_s(const wchar_t *in, const wchar_t *end, double *num);


/*此函数相当于修改字符串，因此不存在_s版，且trim之后的字符串结尾为\0*/
wchar_t*		AR_wcstrim_right(wchar_t *in, const wchar_t *trim);
wchar_t*		AR_wcstrim_right_space(wchar_t *in);

/*返回的是需要元素数组的长度包含0*/
int_t			AR_i64tow_buf(wchar_t *out, size_t nbuf, int_64_t num, size_t radix);
int_t			AR_u64tow_buf(wchar_t *out, size_t nbuf, uint_64_t num, size_t radix);



const char*		AR_stristr(const char *s, const char *p);
const wchar_t*	AR_wcsistr(const wchar_t *s, const wchar_t *p);


const wchar_t* AR_reverse_wcschr(const wchar_t* str, size_t l, wchar_t c);
const wchar_t* AR_reverse_wcsstr(const wchar_t *str, size_t l,  const wchar_t *match, size_t ml);

const wchar_t* AR_reverse_wcsichr(const wchar_t* str, size_t l, wchar_t c);
const wchar_t* AR_reverse_wcsistr(const wchar_t *str, size_t l,  const wchar_t *match, size_t ml);



#if(AR_ARCH_VER	== ARCH_32)

		#define AR_wtoi			AR_wtoi32
		#define AR_wtou			AR_wtou32

		#define AR_wtou_s		AR_wtou32_s
		#define AR_wtoi_s		AR_wtoi32_s


#elif(AR_ARCH_VER == ARCH_64)

		#define AR_wtoi			AR_wtoi64
		#define AR_wtou			AR_wtou64

		#define AR_wtou_s		AR_wtou64_s
		#define AR_wtoi_s		AR_wtoi64_s

#else
		
		#error "Not Support Platform!"

#endif


/***************************************************************************************************/
bool_t			AR_wcs_is_float(const wchar_t *in, const wchar_t *end);
bool_t			AR_wcs_is_int(const wchar_t *in, const wchar_t *end);




/*返回一个长度，足够容纳fmt + args*/
int_t			AR_vscwprintf(const wchar_t *fmt, va_list args);
int_t			AR_scwprintf(const wchar_t *fmt, ...);
wchar_t*		AR_vtow(const wchar_t *fmt, ...);

int_t			AR_swprintf(wchar_t *dest, size_t count, const wchar_t *fmt, ...);
int_t			AR_vswprintf(wchar_t *dest, size_t count, const wchar_t *fmt, va_list args);

//int_t			AR_vsprintf(char *dest, size_t count, const char *fmt, va_list args);





int_t			AR_wchartodigit(wchar_t ch);



uint_t			AR_wcshash(const wchar_t *str);
uint_t			AR_wcshash_n(const wchar_t *str, size_t n);






/*********************************************************String Convert****************************************************/

/*
在windows下，需要修改__get_codepage_for_winapi，
在支持iconv的平台下，需要修改__get_locale_str_for_iconv


*/

typedef enum
{
		AR_CP_ACP,
		AR_CP_UTF8,
		AR_CP_BIG5,
		AR_CP_GB2312,
		AR_CP_GB18030,
		AR_CP_MAX
}arCodePage_t;

size_t					AR_str_to_wcs(arCodePage_t cp, const char *acp, size_t n, wchar_t *out, size_t out_len);
size_t					AR_wcs_to_str(arCodePage_t cp, const wchar_t *input, size_t n, char *out, size_t out_len);


char*					AR_wcs_convto_str(arCodePage_t cp, const wchar_t *input, size_t in_n);
wchar_t*				AR_str_convto_wcs(arCodePage_t cp, const char *input, size_t in_n);


/*******************************************************BitMark****************************************************************/


/*#define AR_BIT_MARK(_pos)	(((uint_64_t)0x01) << ((uint_64_t)(_pos)))*/

static AR_INLINE uint_64_t AR_BIT_MARK(uint_64_t pos) { return AR_BIGNUM_U64(0x01) << pos; }

#define AR_BIT_TEST(_val, _pos)  ((((_val) & (AR_BIT_MARK((_pos))))))

#define AR_BIT_SET(_val, _pos)   ((_val) |= (AR_BIT_MARK((_pos))))

#define AR_BIT_CLR(_val, _pos)   (((_val)) &=  (~(AR_BIT_MARK((_pos)))))



/* 在第p位上设置n个1 */
#define AR_MASK1(_n,_p)	( (~( (~(uint_64_t)0) << (_n))) << (_p) )

/* 在第p位上设置n个0 */
#define AR_MASK0(_n,_p)	(~AR_MASK1((_n),(_p)))






/***************************************************************Misc**********************************************************/
#define	AR_ESCSTR_ERR_OK				0x00
#define	AR_ESCSTR_ERR_VALUE				0x01
#define	AR_ESCSTR_ERR_CHAR				0x02
#define AR_ESCSTR_ERR_BUFFER			0x03
#define AR_ESCSTR_ERR_MEMORY			0x04

typedef struct __escape_string_error_tag
{
		int_t			type;
		const wchar_t	*pos;
		uint_64_t		value;
}arEscStrErr_t;


wchar_t*		AR_escstr_to_str(const wchar_t *src, arEscStrErr_t *error);
wchar_t*		AR_str_to_escstr(const wchar_t *src);

wchar_t*		AR_escstr_to_str_n(const wchar_t *src, size_t n, arEscStrErr_t *error);
wchar_t*		AR_str_to_escstr_n(const wchar_t *src, size_t n);


int_t 			AR_escstr_to_str_buf(wchar_t *dest, size_t len, const wchar_t *src, arEscStrErr_t *error);
int_t 			AR_str_to_escstr_buf(wchar_t *dest, size_t len, const wchar_t *src);


int_t 			AR_escstr_to_str_buf_n(wchar_t *dest, size_t len, const wchar_t *src, size_t n,arEscStrErr_t *error);
int_t 			AR_str_to_escstr_buf_n(wchar_t *dest, size_t len, const wchar_t *src, size_t n);



/**************************************************************base64*********************************************************/
size_t			AR_base64_encode(byte_t  *out, size_t olen, const byte_t *input, size_t ilen);
size_t			AR_base64_decode(byte_t  *out, size_t olen, const byte_t *input, size_t ilen);












/********************************************************String*****************************************************************/

typedef struct __arsenal_string_tag		arString_t;




arString_t*		AR_CreateString();
void			AR_DestroyString(arString_t *str);

/*预留num个wchar_t的空间*/
arStatus_t		AR_ReserveString(arString_t *str, size_t num);
void			AR_ClearString(arString_t *str);
arStatus_t		AR_AppendString(arString_t *str, const wchar_t *sour);

arStatus_t		AR_FormatString(arString_t *str, const wchar_t *fmt, ...);
arStatus_t		AR_AppendFormatString(arString_t *str, const wchar_t *fmt, ...);

arStatus_t		AR_VFormatString(arString_t *str, const wchar_t *fmt, va_list va_args);
arStatus_t		AR_AppendVFormatString(arString_t *str, const wchar_t *fmt, va_list va_args);


arStatus_t		AR_AppendCharToString(arString_t *str, wchar_t chr);

const wchar_t*	AR_GetStringCString(const arString_t *str);
size_t			AR_GetStringLength(const arString_t *str);




#define			AR_StrPrint(_s) do{ AR_printf(L"%ls\r\n", AR_GetStringCString((_s))); }while(0)
#define			AR_StrPrintCtx(_ctx, _s)do{ AR_printf_ctx((_ctx), L"%ls\r\n", AR_GetStringCString((_s))); }while(0)



/********************************************************StringTable*****************************************************************/




typedef struct __string_table_			arStringTable_t;




#define		MIN_BUCKET_SIZE		(139)


arStringTable_t*		AR_CreateStrTable(size_t count);
void					AR_DestroyStrTable(arStringTable_t* tbl);


const wchar_t*			AR_GetString(arStringTable_t *tbl, const wchar_t *str);
const wchar_t*			AR_GetStringN(arStringTable_t *tbl, const wchar_t *str, size_t n);

arStatus_t				AR_HasString(const arStringTable_t *tbl, const wchar_t *str);
arStatus_t				AR_HasStringN(const arStringTable_t *tbl, const wchar_t *str, size_t n);

const wchar_t*			AR_GetStringUInt(arStringTable_t *tbl, uint_64_t num, size_t radix);
const wchar_t*			AR_GetStringInt(arStringTable_t *tbl, int_64_t num, size_t radix);
const wchar_t*			AR_GetStringFloat(arStringTable_t *tbl, double num, size_t prec);





/**************************************************Buffer**********************************************************************/

struct arsenal_buffer_tag;
typedef struct arsenal_buffer_tag		arBuffer_t;

arBuffer_t*		AR_CreateBuffer(size_t nbytes);
void			AR_DestroyBuffer(arBuffer_t		*buffer);

void			AR_ClearBuffer(arBuffer_t		*buffer);

/*分配nbytes个字节以供使用*/
byte_t*			AR_AllocBuffer(arBuffer_t *buffer, size_t	nbytes);
/*向buffer写入nbytes个字节*/
arStatus_t		AR_InsertBuffer(arBuffer_t *buffer, const byte_t *data, size_t len);

/*从buffer头擦除nbytes个字节*/
size_t			AR_EraseBuffer(arBuffer_t *buffer, size_t nbytes);

/*返回不重新分配内存还可以写的字节数*/
size_t			AR_GetBufferCapacity(const arBuffer_t *buffer);

/*AR_ReserveBuffer调用成功后，AR_GetBufferCapacity(buffer) >= nbytes*/
arStatus_t		AR_ReserveBuffer(arBuffer_t *buffer, size_t nbytes);

/*可读内存块*/
const byte_t*	AR_GetBufferData(const arBuffer_t *buffer);
/*可读内存块长度*/
size_t			AR_GetBufferAvailable(const arBuffer_t *buffer);


size_t			AR_ReadBufferData(arBuffer_t *buffer, byte_t *dest, size_t len);










/***************************************************************Text**********************************************************/


typedef enum
{
		AR_TXT_BOM_ASCII		=		0x01,
		AR_TXT_BOM_UTF16_BE		=		0x02,
		AR_TXT_BOM_UTF16_LE		=		0x04,
		AR_TXT_BOM_UTF_8		=		0x08,
		AR_TXT_BOM_UTF32_LE		=		0x10,
		AR_TXT_BOM_UTF32_BE		=		0x20
}arTxtBom_t;

arStatus_t	AR_LoadBomTextFromBinary(arBuffer_t *input, arTxtBom_t *bom, arString_t *out);

arStatus_t	AR_LoadBomTextFile(const wchar_t *path, arTxtBom_t *bom, arString_t *out);

arStatus_t	AR_SaveBomTextFile(const wchar_t *path, arTxtBom_t bom, const wchar_t *input);

arStatus_t	AR_SaveBomTextToBinary(arBuffer_t *output, arTxtBom_t bom, const wchar_t *input);






/************************************************************************************************************************************************************************/



/**********************************************************Threading*************************************************************/

/*thread模块初始化函数，只能由AR_Init调用*/
void			AR_InitThread();
void			AR_UnInitThread();

/*uint_t		AR_CompExchange(volatile uint_t *dest, uint_t exch, uint_t compval);*/

int_t			AR_AtomicInc(volatile int_t *dest);
int_t			AR_AtomicDec(volatile int_t *dest);


#define			AR_MAXSPIN_COUNT		5000

#if defined(OS_FAMILY_UNIX)
	
	#if(OS_TYPE == OS_IOS || OS_TYPE == OS_MAC_OS_X)
		typedef			volatile int_t				arSpinLock_t;	
#else
		typedef			pthread_spinlock_t	        arSpinLock_t;

	#endif

#elif defined(OS_FAMILY_WINDOWS)

    typedef         volatile int_t					arSpinLock_t;
#else

#endif

void			AR_InitSpinLock(arSpinLock_t *lock);
void			AR_UnInitSpinLock(arSpinLock_t *lock);
void			AR_LockSpinLock(arSpinLock_t *lock);
void			AR_UnLockSpinLock(arSpinLock_t *lock);

void			AR_YieldThread();
void			AR_Sleep(size_t millisecond);

uint_64_t		AR_GetTime_Microseconds();
uint_64_t		AR_GetTime_Milliseconds();




/***************************************************************************************************************************************/

/*******************************************************************Math*************************************************************************************************/


#define AR_FLOAT_PRINT_PRECISION		3



int_32_t		AR_abs_32(int_32_t x);
int_64_t		AR_abs_64(int_64_t x);


bool_t			AR_is_equal_flt(float x, float y, float epsilon);

float			AR_logbase_flt(float a, float base);
float			AR_abs_flt(float x);
float			AR_ceil_flt(float f);
float			AR_floor_flt(float f);
float			AR_sqrt_flt(float f);
float			AR_exp_flt(float f);
float			AR_pow_flt(float x, float y);

float			AR_sin_flt(float f);
float			AR_cos_flt(float f);
float			AR_tan_flt(float f);
float			AR_asin_flt(float f);
float			AR_acos_flt(float f);
float			AR_atan_flt(float f);
float			AR_atan2_flt(float y, float x);


bool_t			AR_is_equal_dbl(double x, double y, double epsilon);

double			AR_logbase_dbl(double a, double base);
double			AR_abs_dbl(double x);
double			AR_ceil_dbl(double f);
double			AR_floor_dbl(double f);
double			AR_sqrt_dbl(double f);
double			AR_exp_dbl(double f);
double			AR_pow_dbl(double x, double y);

double			AR_sin_dbl(double f);
double			AR_cos_dbl(double f);
double			AR_tan_dbl(double f);
double			AR_asin_dbl(double f);
double			AR_acos_dbl(double f);
double			AR_atan_dbl(double f);
double			AR_atan2_dbl(double y, double x);



/*float macro_oper*/

#define AR_FLT_EQ(_x, _y)		AR_is_equal_flt((float)(_x), (float)(_y), FLT_EPSILON)
#define AR_FLT_LE(_x, _y)		(bool_t) ((((float)(_x)) < ((float)(_y))))
#define AR_FLT_GE(_x, _y)		(bool_t) ((((float)(_x)) > ((float)(_y))))
#define AR_FLT_LEEQ(_x, _y)		(bool_t)( AR_FLT_EQ((_x), (_y)) || AR_FLT_LE((_x), (_y)))
#define AR_FLT_GEEQ(_x, _y)		(bool_t)( AR_FLT_EQ((_x), (_y)) || AR_FLT_GE((_x), (_y)))

#define AR_FLT_MOD(_x,_y)		((float)(_x) - AR_floor_flt((float)(_x) / (float)(_y)) * (float)(_y))
#define AR_FLT_POW(_x,_y)		(float)AR_pow_flt((float)(_x), (float)(_y))


#define AR_DBL_EQ(_x, _y)		AR_is_equal_dbl((double)(_x), (double)(_y), DBL_EPSILON)
#define AR_DBL_LE(_x, _y)		(bool_t) ((((double)(_x)) < ((double)(_y))))
#define AR_DBL_GE(_x, _y)		(bool_t) ((((double)(_x)) > ((double)(_y))))
#define AR_DBL_LEEQ(_x, _y)		(bool_t)( AR_DBL_EQ((_x), (_y)) || AR_DBL_LE((_x), (_y)))
#define AR_DBL_GEEQ(_x, _y)		(bool_t)( AR_DBL_EQ((_x), (_y)) || AR_DBL_GE((_x), (_y)))

#define AR_DBL_MOD(_x,_y)		((double)(_x) - AR_floor_dbl((double)(_x) / (double)(_y)) * (double)(_y))
#define AR_DBL_POW(_x,_y)		(double)AR_pow_dbl((double)(_x), (double)(_y))






/***************************************************************Vector**********************************************************/



struct __arsenal_vector_tag;
typedef struct __arsenal_vector_tag arVector_t;


arVector_t*		AR_CreateVector(size_t size);
void			AR_DestroyVector(arVector_t *vec);
arVector_t*		AR_CopyNewVector(const arVector_t *vec);
arStatus_t		AR_CopyVector(arVector_t *dest, const arVector_t *src);

arStatus_t		AR_SetVectorSize(arVector_t *vec, size_t size);
size_t			AR_GetVectorSize(const arVector_t *vec);

arStatus_t		AR_SetVectorData(arVector_t *vec, size_t size, const double *data);
const double*	AR_GetVectorData(const arVector_t *vec);

void			AR_SwapElements(arVector_t *vec, size_t l, size_t r);

double			AR_GetVectorValue(const arVector_t *vec, size_t idx);
void			AR_SetVectorValue(arVector_t *vec, size_t idx, double val);

int_t			AR_CompareVector(const arVector_t *l, const arVector_t *r, double epsilon);


void			AR_ZeroVector(arVector_t *vec);
void			AR_NegateVector(arVector_t *vec);
void			AR_ClampVector(arVector_t *vec, double minval, double maxval);
void			AR_RandomVector(arVector_t *vec);
void			AR_NormalizeVector(arVector_t *vec);


void			AR_CalcVectorLength(const arVector_t *vec, double *ret);
void			AR_CalcVectorLengthSqr(const arVector_t *vec, double *ret);
void			AR_CalcVectorInnerProduct(const arVector_t *vec, const arVector_t *other, double *ret);
arStatus_t		AR_CalcVectorDistanceByVector(const arVector_t *vec, const arVector_t *other, double *ret);




void			AR_AddVectorByVectorSelf(arVector_t *vec, const arVector_t *other);
void			AR_SubVectorByVectorSelf(arVector_t *vec, const arVector_t *other);
void			AR_MulVectorByValSelf(arVector_t *vec, double val);
void			AR_DivVectorByValSelf(arVector_t *vec, double val);



arStatus_t		AR_AddVectorByVector(const arVector_t *vec, const arVector_t *other, arVector_t *dest);
arStatus_t		AR_SubVectorByVector(const arVector_t *vec, const arVector_t *other, arVector_t *dest);
arStatus_t		AR_MulVectorByVal(const arVector_t *vec, double val, arVector_t *dest);
arStatus_t		AR_DivVectorByVal(const arVector_t *vec, double val, arVector_t *dest);




typedef enum
{
		AR_VEC_NORM_1,
		AR_VEC_NORM_2,
		AR_VEC_NORM_MAX,
		AR_VEC_NORM_NEGAMAX
}arVectorNormType_t;


arStatus_t		AR_CalcVectorNormNumber(const arVector_t *vec, arVectorNormType_t t, double *ret);



arStatus_t		AR_VectorToString(const arVector_t *vec, arString_t *str, size_t precision, const wchar_t *sp_str);

/***************************************************************Matrix**********************************************************/

struct __arsenal_matrix_tag;
typedef struct __arsenal_matrix_tag		arMatrix_t;



arMatrix_t*		AR_CreateMatrix(size_t rows, size_t cols);
void			AR_DestroyMatrix(arMatrix_t *mat);

arMatrix_t*		AR_CopyNewMatrix(const arMatrix_t *mat);
arStatus_t		AR_CopyMatrix(arMatrix_t *dest, const arMatrix_t *src);

arStatus_t		AR_SetMatrixSize(arMatrix_t *mat, size_t rows, size_t cols);
arStatus_t		AR_SetMatrixData(arMatrix_t *mat, size_t row, size_t col, const double *data);

int_t			AR_CompareMatrix(const arMatrix_t *l, const arMatrix_t *r, double epsilon);

size_t			AR_GetMatrixNumRows(const arMatrix_t *mat);
size_t			AR_GetMatrixNumColumns(const arMatrix_t *mat);

void			AR_SetMatrixValue(arMatrix_t *mat, size_t row, size_t col, double val);
double			AR_GetMatrixValue(const arMatrix_t *mat, size_t row, size_t col);


void			AR_SetMatrixRowByRawData(arMatrix_t *mat, size_t row,  const double *data);
void			AR_SetMatrixColumnByRawData(arMatrix_t *mat, size_t col, const double *data);


void			AR_SetMatrixRow(arMatrix_t *mat, size_t row,  const arVector_t *vec);
void			AR_SetMatrixColumn(arMatrix_t *mat, size_t col,  const arVector_t *vec);
arStatus_t		AR_GetMatrixRow(const arMatrix_t *mat, size_t row,  arVector_t *out);
arStatus_t		AR_GetMatrixColumn(const arMatrix_t *mat, size_t col,  arVector_t *out);

const double*	AR_GetMatrixRawData(const arMatrix_t *mat);


/****************************************生成标准矩阵类型******************************************/
void			AR_ZeroMatrix(arMatrix_t *mat);
void			AR_IdentityMatrix(arMatrix_t *mat);
arStatus_t		AR_DiagonalMatrix(arMatrix_t *mat, const arVector_t *vec);
void			AR_RandomMatrix(arMatrix_t *mat);
void			AR_NegateMatrix(arMatrix_t *mat);
void			AR_ClampMatrix(arMatrix_t *mat, double min_val, double max_val);
arStatus_t		AR_SwapMatrixRows(arMatrix_t *mat, size_t l, size_t r);
arStatus_t		AR_SwapMatrixColumns(arMatrix_t *mat, size_t l, size_t r);
void			AR_RemoveMatrixRow(arMatrix_t *mat, size_t r);
void			AR_RemoveMatrixColumn(arMatrix_t *mat, size_t c);
void			AR_ClearMatrixUpperTriangle(arMatrix_t *mat);
void			AR_ClearMatrixLowerTriangle(arMatrix_t *mat);

/****************************************判断矩阵类型******************************************/

arStatus_t			AR_IsSquareMatrix(const arMatrix_t *mat);


arStatus_t		AR_IsZeroMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsIdentityMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsDiagonalMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsTriDiagonalMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsSymmetricMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsOrthogonalMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsOrthonormalMatrix(const arMatrix_t *mat, double epsilon);

/*是否正定矩阵*/
arStatus_t		AR_IsPositiveDefiniteMatrix(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsSymmetricPositiveDefinite(const arMatrix_t *mat, double epsilon);

/*是否半正定矩阵*/
arStatus_t		AR_IsPositiveSemiDefinite(const arMatrix_t *mat, double epsilon);
arStatus_t		AR_IsSymmetricPositiveSemiDefinite(const arMatrix_t *mat, double epsilon);


/****************************************基本矩阵计算******************************************/

arStatus_t		AR_MultiplyMatrixByScalar(const arMatrix_t *mat, double value, arMatrix_t *dest);
arStatus_t		AR_MultiplyMatrixByScalarSelf(arMatrix_t *mat, double value);

arStatus_t		AR_MultiplyMatrixByVector(const arMatrix_t *mat, const arVector_t *other, arVector_t *dest);
arStatus_t		AR_MultiplyTransposeMatrixByVector(const arMatrix_t *mat, const arVector_t *other, arVector_t *dest);

arStatus_t		AR_MultiplyMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest);
arStatus_t		AR_MultiplyTransposeMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest);
arStatus_t		AR_MultiplyMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other);
arStatus_t		AR_MultiplyTransposeMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other);

arStatus_t		AR_AddMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest);
arStatus_t		AR_AddMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other);

arStatus_t		AR_SubMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest);
arStatus_t		AR_SubMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other);





arStatus_t		AR_CalcMatrixTrace(const arMatrix_t *mat, double *ret);
arStatus_t		AR_CalcMatrixDeterminant(const arMatrix_t *mat, double *ret);
arStatus_t		AR_CalcMatrixRank(const arMatrix_t *mat, size_t *ret);
arStatus_t		AR_TransposeMatrix(const arMatrix_t *mat, arMatrix_t *dest);
arStatus_t		AR_TransposeMatrixSelf(arMatrix_t *mat);


/*取逆矩阵*/
arStatus_t		AR_InverseMatrixSelf(arMatrix_t *mat);

arStatus_t		AR_InverseLowerTriangularMatrixSelf(arMatrix_t *mat);
arStatus_t		AR_InverseUpperTriangularMatrixSelf(arMatrix_t *mat);

arStatus_t		AR_InverseMatrixByGaussJordanSelf(arMatrix_t *mat);
arStatus_t		AR_InverseSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b);

/*matlab rref(A)*/
void			AR_ReduceMatrixToEchelonFormSelf(arMatrix_t *mat, size_t *index);
arStatus_t		AR_ReduceMatrixToEchelonForm(const arMatrix_t *mat, size_t *index, arMatrix_t *rm);



/****************************************矩阵分解******************************************/

/*三对角矩阵*/
void			AR_TriDiagonalClearMatrixSelf(arMatrix_t *mat);
arStatus_t		AR_TriDiagonalSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b);
arStatus_t		AR_TriDiagonalInverseMatrix(const arMatrix_t *mat, arMatrix_t *inv);


/*LU分解*/

arStatus_t		AR_LUFactorMatrixSelf(arMatrix_t *mat, size_t *index, double *det);
arStatus_t		AR_LUInverseMatrix(const arMatrix_t *mat, const size_t *index, arMatrix_t *inv);
arStatus_t		AR_LUSolveMatrix(const arMatrix_t *mat, const size_t *index, arVector_t *x,const arVector_t *b);
arStatus_t		AR_UnpackMatrixLUFactors(const arMatrix_t *mat, arMatrix_t *L, arMatrix_t *U);
arStatus_t		AR_MultiplyMatrixLUFactors(const arMatrix_t *mat, const size_t *index, arMatrix_t *original_mat);



/*
LDLT分解 A = L*D*L^t,矩阵为对称方阵
*/

arStatus_t		AR_LDLTFactorMatrixSelf(arMatrix_t *mat);
void			AR_LDLTSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b);
arStatus_t		AR_LDLTInverseMatrix(const arMatrix_t *mat, arMatrix_t *inv);
arStatus_t		AR_UnpackMatrixLDLTFactors(const arMatrix_t *mat, arMatrix_t *L, arMatrix_t *D);
arStatus_t		AR_MultiplyMatrixLDLTFactors(const arMatrix_t *mat, arMatrix_t *original_mat);



/*Cholesky分解*/
arStatus_t		AR_CholeskyFactorMatrixSelf(arMatrix_t *mat);
arStatus_t		AR_CholeskySolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b);
arStatus_t		AR_CholeskyInverseMatrix(const arMatrix_t *mat, arMatrix_t *inv);
arStatus_t		AR_MultiplyMatrixCholeskyFactors(const arMatrix_t *mat, arMatrix_t *original_mat);


/*QR分解*/
arStatus_t		AR_QRFactorMatrixSelf(arMatrix_t *mat, arVector_t *c, arVector_t *d);
arStatus_t		AR_QRSloveMatrix(const arMatrix_t *mat, const arVector_t *c, const arVector_t *d, arVector_t *x, const arVector_t *b);
arStatus_t		AR_QRInverseMatrix(const arMatrix_t *mat, const arVector_t *c, const arVector_t *d, arMatrix_t *inv);
arStatus_t		AR_UnpackMatrixQRFactors(const arMatrix_t *mat, const arVector_t *c, const arVector_t *d, arMatrix_t *Q, arMatrix_t *R);
arStatus_t		AR_MultiplyMatrixQRFactors(const arMatrix_t *mat, const arVector_t *c, const arVector_t *d, arMatrix_t *original_matrix);





/*************************************************************其他功能*************************************************************/
arStatus_t		AR_MatrixToString(const arMatrix_t *mat, arString_t *str, size_t precision, const wchar_t *sp_str, const wchar_t *row_sp);


AR_NAMESPACE_END




#endif
