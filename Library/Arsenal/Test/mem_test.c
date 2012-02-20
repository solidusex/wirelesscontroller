#include "test.h"
#include "../Arsenal/Common/heap.h"

#include <vector>
#include <math.h>
#include <time.h>

#if defined(__LIB)

AR_NAMESPACE_BEGIN

//#define USE_C_MALLOC	1

#if defined(USE_C_MALLOC)
		#define ALLOC_MEM(_heap, _bytes)				malloc((_bytes))
		#define FREE_MEM(_heap, _ptr)					free((_ptr))
		#define	REALLOC_MEM(_heap, _ptr, _size)			realloc((_ptr), (_size))
#else
		#define ALLOC_MEM(_heap, _bytes)				AR_AllocFromHeap((_heap), (_bytes))
		#define FREE_MEM(_heap, _ptr)					AR_FreeToHeap((_heap), (_ptr))
		#define	REALLOC_MEM(_heap, _ptr, _size)			AR_ReallocFromHeap((_heap), (_ptr), (_size))
#endif


void alloc_test()
{
		arHeap_t *heap = NULL;

#if !defined(USE_C_MALLOC)
		heap = AR_CreateHeap();
#endif

		std::vector<size_t>		mem_size_set;
		std::vector<void*>		mem_ptr_set;

		//srand(time(NULL));


		for(size_t i = 0; i < 10000; ++i)
		{
				
				size_t n = 0;
				/*
				while(n == 0)
				{
						n = AR_rand64() % 102767;

						if(n < 102767)n = 102767 + AR_rand64() % 32768;
				}
				mem_size_set.push_back(n);
				*/
				
				
				while(n == 0)
				{
						n = AR_rand64() % 32768;
				}
				mem_size_set.push_back(n);

				while(n == 0)
				{
						n = AR_rand64() % 256;
				}
				mem_size_set.push_back(n);
				

		}

		size_t size_cnt = mem_size_set.size();

		for(size_t i = 0; i < size_cnt; ++i)
		{
				size_t n = mem_size_set[i];
				void *p = ALLOC_MEM(heap, n);
				memset(p, 'a', n);
				AR_ASSERT(p != NULL);
				mem_ptr_set.push_back(p);

				if(AR_rand32() % 8 > 0)
				{
						size_t idx = AR_rand32() % mem_ptr_set.size();
						void *ptr  = mem_ptr_set[idx];
						mem_ptr_set.erase(mem_ptr_set.begin() + idx);
						FREE_MEM(heap, ptr);
				}

		}
		
		
		size_t ptr_cnt = mem_ptr_set.size();
		for(size_t i = 0;  i < ptr_cnt; ++i)
		{
				void *ptr = mem_ptr_set[i];
				AR_ASSERT(ptr != NULL);
				FREE_MEM(heap, ptr);
				mem_ptr_set[i] = NULL;
		}

		if(heap)
		{
				AR_DestroyHeap(heap);
		}
}

void measure_alloc_test()
{
		uint_64_t beg, end;
		
		for(size_t i = 0; i < 500; ++i)
		{
				beg = AR_GetTime_Microseconds();
				alloc_test();
				end = AR_GetTime_Microseconds();

				printf("%d : time == %I64d\r\n", i, end - beg);
		}
}




void realloc_test()
{
		arHeap_t *heap = NULL;
#if !defined(USE_C_MALLOC)
		heap = AR_CreateHeap();
#endif

		std::vector<size_t>		mem_size_set;
		std::vector<void*>		mem_ptr_set;
		
#if(OS_TYPE != OS_WINDOWS_CE)		
		srand(time(NULL));
#else
		srand(_time64 (NULL));
#endif
		


		for(size_t i = 0; i < 10000; ++i)
		{
				
				size_t n = 0;
				
				while(n == 0)
				{
						n = AR_rand64() % 102767;

						if(n < 102767)n = 102767 + AR_rand64() % 32768;
				}
				mem_size_set.push_back(n);
				
				/*
				while(n == 0)
				{
						n = AR_rand64() % 32768;
						if(n < 256)
						{
								n += 256;
						}
				}
				mem_size_set.push_back(n);

				while(n == 0)
				{
						n = AR_rand64() % 256;
				}
				mem_size_set.push_back(n);
				*/

		}


		void *ptr = NULL;
		for(size_t i = 0; i < mem_size_set.size(); ++i)
		{
				size_t bytes = mem_size_set[i];
				ptr = REALLOC_MEM(heap, ptr, bytes);
				memset(ptr, 'a', bytes);
		}

		FREE_MEM(heap, ptr);

		if(heap)
		{
				AR_DestroyHeap(heap);
		}
}




void measure_realloc_test()
{
		uint_64_t beg, end;
		
		for(size_t i = 0; i < 500; ++i)
		{
				beg = AR_GetTime_Microseconds();
				realloc_test();
				end = AR_GetTime_Microseconds();

				printf("%d : time == %I64d\r\n", i, end - beg);
		}
}



void mem_test()
{
		//alloc_test();

		
		measure_alloc_test();
		

		//measure_realloc_test();


}


AR_NAMESPACE_END


#endif



