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


#include "common.h"
#include "heap.h"

AR_NAMESPACE_BEGIN



static arSpinLock_t		__g_lock;
static arHeap_t			*__g_heap = NULL;

void	AR_InitMemory()
{
		AR_InitSpinLock(&__g_lock);
		__g_heap = AR_CreateHeap();
		if(__g_heap == NULL)
		{
				AR_error(AR_ERR_FATAL, L"AR_InitMemory failure\r\n");
		}
}


void	AR_UnInitMemory()
{
		arHeapUsage_t	usage;


		usage = AR_GetHeapMemUsage(__g_heap);


#if(0)
		{
				wchar_t buf[1024];
				AR_swprintf(buf, 1024, L"Peak memroy used : %" AR_INT_FMT64 L"uKB" L"\r\n", usage.peak_mem_used / 1024);
				MessageBox(NULL, buf, 0,0);
		}
#endif
		AR_LOG(L"Peak memroy used : %quKB" L"\r\n", usage.peak_mem_used/1024);


		AR_DestroyHeap(__g_heap);
		__g_heap = NULL;
		AR_UnInitSpinLock(&__g_lock);
}


#if !defined(AR_USE_CRT_ALLOCFUNC)

static AR_INLINE void*	malloc_mem(size_t bytes)
{
		void *ret;
		AR_ASSERT(bytes > 0);
		if(bytes == 0)
		{
				return NULL;
		}

		AR_LockSpinLock(&__g_lock);
		ret = AR_AllocFromHeap(__g_heap, bytes);
		AR_UnLockSpinLock(&__g_lock);
		return ret;
}

static AR_INLINE void	free_mem(void *ptr)
{
		AR_ASSERT(ptr != NULL);
		AR_LockSpinLock(&__g_lock);
		AR_FreeToHeap(__g_heap, ptr);
		
		AR_UnLockSpinLock(&__g_lock);
}

static AR_INLINE void*	calloc_mem(size_t num, size_t size)
{
		void *ret = malloc_mem(num *size);
		if(!ret)
		{
				return NULL;
		}

		AR_memset(ret, 0, num *size);
		return ret;
}

static AR_INLINE void*	realloc_mem(void *ptr, size_t size)
{
		void *ret;
		AR_LockSpinLock(&__g_lock);
		ret = AR_ReallocFromHeap(__g_heap, ptr, size);
		
		AR_UnLockSpinLock(&__g_lock);
		if(!ret)
		{
				return NULL;
		}
		return ret;
}



/*****************************************************Memory*******************************/


void*	AR_malloc(size_t nbytes)
{
		void *ptr;
		size_t i;
		AR_ASSERT(nbytes > 0);
		
		i = 0;
		ptr = NULL;
		
		while(i < AR_MEM_MAX_ALLOC_RETRY_COUNT && (ptr = malloc_mem(nbytes)) == NULL)
		{
				AR_YieldThread();
				++i;
		}

		/*
		if(!ptr)
		{
				AR_error(AR_ERR_FATAL, L"malloc failure for %Iu\r\n", nbytes);
		}
		*/
		
		return ptr;
}

void*	AR_calloc(size_t num, size_t size)
{
		size_t i;
		void *ptr;
		AR_ASSERT(num > 0 && size > 0);
		
		ptr = NULL;
		i = 0; 

		while(i < AR_MEM_MAX_ALLOC_RETRY_COUNT && (ptr = calloc_mem(num,size)) == NULL)
		{
				AR_YieldThread();
				++i;
		}

		/*
		if(!ptr)
		{
				AR_error(AR_ERR_FATAL, L"calloc failure for %Iu\r\n", num * size);
		}
		*/

		return ptr;
}		

#if(0)
void*	AR_realloc(void *block, size_t nbytes)
{
		void *ptr;
		size_t i;
		AR_ASSERT(nbytes > 0);
		
		i = 0;
		ptr = NULL;

		while(i < AR_MEM_MAX_ALLOC_RETRY_COUNT && (ptr = realloc_mem(block, nbytes)) == NULL)
		{
				AR_YieldThread();
				++i;
		}

		/*
		if(!ptr)
		{
				AR_error(AR_ERR_FATAL, L"realloc failure for %Iu\r\n", nbytes);
		}
		*/
		
		return ptr;
}
#endif


void	AR_free(void *ptr)
{
		if(ptr)
		{
				free_mem(ptr);
		}
}



#endif


void	AR_memswap(void *a, void *b, size_t n)
{
		int_t cnt;
		
		AR_ASSERT(a != NULL && b != NULL);

		if(a == b)
		{
				return;
		}


		if((size_t)a % sizeof(uint_t) != 0 || (size_t)b % sizeof(uint_t) != 0)
		{
				cnt = (int_t)n;

				while(cnt-- > 0)
				{
						byte_t t = *(byte_t*)a;
						*(byte_t*)a = *(byte_t*)b;
						*(byte_t*)b = t;
						a = (byte_t*)a + 1;
						b = (byte_t*)b + 1;
				}
		}else
		{
				cnt = (int_t)(n / sizeof(int_t));

				while(cnt-- > 0)
				{
						uint_t t = *(uint_t*)a;
						*(uint_t*)a = *(uint_t*)b;
						*(uint_t*)b = t;
						a = (uint_t*)a + 1;
						b = (uint_t*)b + 1;
				}

				cnt = (int_t)(n %  sizeof(int_t));

				while(cnt-- > 0)
				{
						byte_t t = *(byte_t*)a;
						*(byte_t*)a = *(byte_t*)b;
						*(byte_t*)b = t;
						a = (byte_t*)a + 1;
						b = (byte_t*)b + 1;
				}
		}

}




AR_NAMESPACE_END
