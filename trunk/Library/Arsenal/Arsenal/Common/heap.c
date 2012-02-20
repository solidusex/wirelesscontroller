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

#include "heap.h"


AR_NAMESPACE_BEGIN





struct __heap_page_tag;
typedef struct __heap_page_tag	page_t;

struct __heap_page_tag
{
		byte_t				*data;
		size_t				data_size;
		page_t				*next;
		page_t				*prev;

		size_t				largest_free;		/*medium分配时使用*/
		byte_t*				first_free;			/*medium分配时使用*/
};



struct __medium_entery_tag;
typedef struct __medium_entery_tag	mediumEntry_t;

struct __medium_entery_tag
{
		page_t 					*page;
		size_t					size;
		mediumEntry_t			*prev;
		mediumEntry_t			*next;
		mediumEntry_t			*prev_free;
		mediumEntry_t			*next_free;
		size_t					free_block;
};





struct __arsenal_heap_tag
{
		byte_t			*small_first_free[((SMALL_SIZE + 1)	/	AR_HEAP_ALIGN)+1];/*SMALL_SIZE对齐整理后+header会存在超出256的值,因此数组+1*/
		page_t			*small_cur_page;
		size_t			small_cur_page_offset;
		page_t 			*small_first_used_page;
		

		page_t			*medium_first_free_page;
		page_t			*medium_last_free_page;
		page_t			*medium_first_used_page;
		
		page_t			*large_first_used_page;

		size_t			page_allocated;
		size_t			actual_mem_used;
		size_t			peak_mem_used;
};

static AR_INLINE page_t*		AllocatePage(arHeap_t *heap, size_t page_bytes)
{
		page_t *page;
		byte_t	*ptr;
		size_t size;
		
		AR_ASSERT(heap != NULL && page_bytes > 0);
		
		

		size = page_bytes + sizeof(page_t);
		ptr = (byte_t*)malloc(size);


		if(!ptr)
		{
				return NULL;
		}

		
		
		page = (page_t*)ptr;

		page->data = (byte_t*)AR_ALIGN_SIZE((size_t)(ptr + sizeof(page_t)));
		
		page->data_size = size - (size_t)((byte_t*)page->data - (byte_t*)page);

		page->next = NULL;
		page->prev = NULL;
		page->largest_free = 0;
		page->first_free = NULL;

		heap->page_allocated++;
		heap->actual_mem_used += size;

		if(heap->actual_mem_used > heap->peak_mem_used)
		{
				heap->peak_mem_used = heap->actual_mem_used;
		}

		return page;
}


static AR_INLINE void	FreePage(arHeap_t *heap, page_t *page)
{
		AR_ASSERT(heap != NULL && page != NULL);
		
		
		heap->page_allocated--;
		heap->actual_mem_used -= (page->data_size + (size_t)((byte_t*)page->data - (byte_t*)page));

		free(page);
		page = NULL;

		
}

static AR_INLINE void*	SmallAllocate(arHeap_t *heap, size_t bytes)
{
		byte_t *block;
		size_t	byte_left;
		AR_ASSERT(heap != NULL && bytes > 0 && bytes <= SMALL_SIZE);


		/*
		最小块指针必须能存储一个sizeof(void*)大小的值，以形成一个链表
		*/
		if(bytes < sizeof(void*))
		{
				bytes = sizeof(void*);
		}

		/*
		实际需要的字节数为bytes + SMALL_HEADER_SIZE，将其对齐后，减掉SMALL_HEADER_SIZE，则为实际使用的字节数
		*/
		bytes = SMALL_ALIGN(bytes);

		block = heap->small_first_free[bytes/AR_HEAP_ALIGN];

		if(block)
		{
				size_t next = *(size_t*)(block + SMALL_HEADER_SIZE);
				block[1] = HEAP_SMALL_ALLOC;
				heap->small_first_free[bytes/AR_HEAP_ALIGN] = (byte_t*)next;
				
				return (void*)(block + SMALL_HEADER_SIZE);
		}

		AR_ASSERT(heap->small_cur_page_offset <= heap->small_cur_page->data_size);
		
		/*byte_left = PAGE_SIZE - heap->small_cur_page_offset;*/
		byte_left = heap->small_cur_page->data_size - heap->small_cur_page_offset;
		
		if(bytes + SMALL_HEADER_SIZE > byte_left)
		{
				page_t *new_page = AllocatePage(heap, PAGE_SIZE);
				if(!new_page)
				{
						return NULL;
				}

				heap->small_cur_page->next = heap->small_first_used_page;
				heap->small_first_used_page = heap->small_cur_page;
				heap->small_cur_page = new_page;
				heap->small_cur_page_offset = SMALL_ALIGN(0);
		}

		block = heap->small_cur_page->data + heap->small_cur_page_offset;
		block[0] = (byte_t)(bytes/AR_HEAP_ALIGN);
		block[1] = HEAP_SMALL_ALLOC;
		heap->small_cur_page_offset += (bytes + SMALL_HEADER_SIZE);
		return block + SMALL_HEADER_SIZE;
}


static AR_INLINE void SmallFree(arHeap_t *heap, void *ptr)
{
		byte_t *p, *d;
		size_t *dt, idx;
		AR_ASSERT(heap != NULL && ptr != NULL);
		
		p = (byte_t*)ptr;
		p[-1] = HEAP_INVALID_ALLOC;
		idx = (size_t)p[-2];
		
		d = p - SMALL_HEADER_SIZE;
		dt = (size_t*)p;
		
		if(idx > ((SMALL_SIZE + 1) / AR_HEAP_ALIGN))
		{
				AR_error(AR_ERR_FATAL, L"SmallFree: invalid memory block\r\n");
		}
		
		*dt = (size_t)heap->small_first_free[idx];
		 heap->small_first_free[idx] = d;
}


static AR_INLINE void* SmallRealloc(arHeap_t *heap, void *ptr, size_t nbytes)
{
		byte_t *p;
		size_t idx, org_bytes;
		AR_ASSERT(heap != NULL && ptr != NULL);
		
		p = (byte_t*)ptr;
		idx = (size_t)p[-2];
		org_bytes = (idx + 1)* AR_HEAP_ALIGN - SMALL_HEADER_SIZE;

		if(idx > ((SMALL_SIZE + 1) / AR_HEAP_ALIGN))
		{
				AR_error(AR_ERR_FATAL, L"SmallRealloc : invalid memory block\r\n");
		}

		if(org_bytes < AR_ALIGN_SIZE(nbytes))
		{
				void *new_ptr;
				new_ptr = AR_AllocFromHeap(heap, nbytes);
				AR_memcpy(new_ptr, ptr, org_bytes);
				AR_FreeToHeap(heap, ptr);
				return (void*)new_ptr;
		}else
		{
				return ptr;
		}
}


/*************************************************************************************************/

static AR_INLINE void*			MediumAllocDataFromPage(arHeap_t *heap, page_t *page, size_t bytes)
{
		byte_t *ret;
		mediumEntry_t		*best, *nw;
		
		AR_ASSERT(heap != NULL && page != NULL);
		AR_UNUSED(heap);


		best = (mediumEntry_t*)page->first_free;
		nw = NULL;
		ret = NULL;

		AR_ASSERT(best != NULL);
		AR_ASSERT(best->size <= page->largest_free);
		AR_ASSERT(best->size >= bytes);

		if(best->size >= (bytes + MEDIUM_SMALLEST_SIZE))
		{
				nw = (mediumEntry_t*)((byte_t*)best + best->size - bytes);
				
				nw->page		= page;
				nw->prev		= best;
				nw->next		= best->next;
				nw->prev_free	= NULL;
				nw->next_free	= NULL;
				nw->size		= bytes;
				nw->free_block	= 0;
				
				if(best->next)
				{	
						best->next->prev = nw;
				}
				
				best->next	= nw;
				best->size	-= bytes;
				page->largest_free = best->size;

		}else
		{
				if(best->prev_free)
				{
						best->prev_free->next_free = best->next_free;
				}else
				{
						page->first_free = (byte_t*)best->next_free;
				}

				if(best->next_free)
				{
						best->next_free->prev_free = best->prev_free;
				}
				best->prev_free = NULL;
				best->next_free = NULL;
				best->free_block = 0;
				nw = best;
				page->largest_free = 0;
		}

		/*ret = ((byte_t*)(nw)) + MEDIUM_HEADER_SIZE;*/
		
		ret = ((byte_t*)(nw)) + AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE);
		ret[-1] = HEAP_MEDIUM_ALLOC;
		return (void*)ret;
}


static AR_INLINE void*			MediumAllocate(arHeap_t *heap, size_t bytes)
{
		size_t	need_size;
		page_t	*p;
		void	*ret;
		AR_ASSERT(heap != NULL && bytes > 0 && bytes <= MEDIUM_SIZE);
		
		need_size = AR_ALIGN_SIZE(bytes) + AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE);

		for(p = heap->medium_first_free_page; p != NULL; p = p->next)
		{
				if(p->largest_free >= need_size)
				{
						break;
				}
		}


		if(p == NULL)
		{
				mediumEntry_t *e;
				p = AllocatePage(heap, PAGE_SIZE);

				if(!p)
				{
						return NULL;
				}

				p->prev = NULL;
				p->next = heap->medium_first_free_page;
				
				if(p->next)
				{
						p->next->prev = p;
				}else
				{
						AR_ASSERT(heap->medium_last_free_page == NULL);
						heap->medium_last_free_page = p;
				}

				heap->medium_first_free_page = p;

				p->largest_free = p->data_size;
				p->first_free = p->data;

				e = (mediumEntry_t*)p->first_free;
				e->page = p;
				e->size = p->data_size & ~(AR_HEAP_ALIGN - 1);
				
				e->free_block = 1;
				e->next_free = NULL;
				e->prev_free = NULL;
				e->next = NULL;
				e->prev = NULL;
		}
		

		ret = MediumAllocDataFromPage(heap, p, need_size);

		if(p->largest_free < MEDIUM_SMALLEST_SIZE)
		{
				if(p == heap->medium_last_free_page)
				{
						heap->medium_last_free_page = p->prev;
				}

				if(p == heap->medium_first_free_page)
				{
						heap->medium_first_free_page = p->next;
				}

				if(p->prev)
				{
						p->prev->next = p->next;
				}

				if(p->next)
				{
						p->next->prev = p->prev;
				}

				p->prev = NULL;
				p->next = heap->medium_first_used_page;
				if(p->next)
				{
						p->next->prev = p;
				}
				heap->medium_first_used_page = p;
		}else if(p != heap->medium_first_free_page)
		{
				page_t *prev, *next;
				AR_ASSERT(heap->medium_first_free_page != heap->medium_last_free_page);
				AR_ASSERT(heap->medium_first_free_page != NULL);
				AR_ASSERT(heap->medium_last_free_page != NULL);
				AR_ASSERT(heap->medium_first_free_page->prev == NULL);
				AR_ASSERT(heap->medium_last_free_page->next == NULL);
				AR_ASSERT(p->prev != NULL);

				
				prev = p->prev;
				next = p->next;

				if(p->prev)
				{
						p->prev->next = next;
						p->prev = NULL;
				}
				if(p->next)
				{
						p->next->prev = prev;
						p->next = NULL;
				}

				if(p == heap->medium_last_free_page)
				{
						heap->medium_last_free_page = prev;
				}

				p->next = heap->medium_first_free_page;
				heap->medium_first_free_page->prev = p;
				heap->medium_first_free_page = p;


		}

		return ret;
}


static AR_INLINE void	MediumFree(arHeap_t *heap, void *ptr)
{
		mediumEntry_t		*e;
		page_t					*p;
		bool_t					is_in_freelist;
		mediumEntry_t		*prev, *next;
		AR_ASSERT(heap != NULL && ptr != NULL);

		((byte_t*)ptr)[-1] = HEAP_INVALID_ALLOC;
		
		e = (mediumEntry_t*)((byte_t*)ptr - AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE));
		AR_ASSERT(e->size > 0);
		AR_ASSERT(e->free_block == 0);
		
		p = e->page;
		is_in_freelist = p->largest_free >= MEDIUM_SMALLEST_SIZE ;
		
		prev = e->prev;

		if(prev && prev->free_block)	/*如果前面的块可以合并，则将本块合并到前面得块中*/
		{
				prev->size += e->size;
				prev->next = e->next;
				if(prev->next)
				{
						AR_ASSERT(prev->next->prev != NULL);
						prev->next->prev = prev;
				}
				e = prev;
		}else
		{
				/*
				否则，将本块插入到first_free链表中
				*/
				e->prev_free = NULL;
				e->next_free = (mediumEntry_t*)p->first_free;
				if(e->next_free)
				{
						AR_ASSERT(e->next_free->prev_free == NULL);
						e->next_free->prev_free = e;
				}
				
				p->first_free = (byte_t*)e;
				p->largest_free = e->size;
				e->free_block = 1;
		}

		next = e->next;
		
		if(next && next->free_block)/*如果后面的块可以合并，则合并到当前块e*/
		{
				e->size += next->size;
				e->next = next->next;
				
				if (next->next) 
				{
						next->next->prev = e;
				}
				
				if(next->prev_free) 
				{
						next->prev_free->next_free = next->next_free;
				}else
				{
						/*执行后first_free有可能为NULL*/
						AR_ASSERT((byte_t*)next == (byte_t*)p->first_free );
						p->first_free = (byte_t*)next->next_free; 
				}

				if ( next->next_free ) 
				{
						next->next_free->prev_free = next->prev_free;
				}
		}

		if(p->first_free)
		{
				p->largest_free = ((mediumEntry_t*)p->first_free)->size;
		}else
		{
				p->largest_free = 0;
		}


		if(e->size > p->largest_free)
		{
				/*
				执行到此，证明p->first_free不是最大块，则将块e放到p->first_free中
				*/
				AR_ASSERT((byte_t*)e != p->first_free);
				p->largest_free = e->size;

				if(e->prev_free)
				{
						e->prev_free->next_free = e->next_free;
				}

				if(e->next_free)
				{
						e->next_free->prev_free = e->prev_free;
				}

				e->prev_free = NULL;
				e->next_free = (mediumEntry_t*)p->first_free;
				if(e->next_free)
				{
						e->next_free->prev_free = e;
				}

				p->first_free = (byte_t*)e;
		}


		if(!is_in_freelist)
		{
				/*
				执行到此，证明page已经在medium_first_used_page表中，因此，要将其重新连入first_free表中
				*/
				if(p->prev)
				{
						p->prev->next = p->next;
				}

				if(p->next)
				{
						p->next->prev = p->prev;
				}

				if ( p == heap->medium_first_used_page)
				{
						heap->medium_first_used_page = p->next;
				}
				
				p->next = NULL;
				p->prev = heap->medium_last_free_page;

				if(heap->medium_last_free_page)
				{
						heap->medium_last_free_page->next = p;
				}
				heap->medium_last_free_page = p;
				
				if(!heap->medium_first_free_page)
				{
						heap->medium_first_free_page = p;
				}
		}


		if(e->free_block && e->size == p->data_size)
		{
				
				AR_ASSERT(e->size == e->page->largest_free);
				AR_ASSERT(e->prev == NULL && e->next == NULL);
				AR_ASSERT(e->prev_free == NULL && e->next_free == NULL);

				if(p == heap->medium_first_free_page)
				{
						heap->medium_first_free_page = p->next;
				}

				if(p == heap->medium_last_free_page)
				{
						heap->medium_last_free_page = p->prev;
				}

				if(p->prev)
				{
						p->prev->next = p->next;
				}

				if(p->next)
				{
						p->next->prev = p->prev;
				}

				if(heap->medium_first_free_page == NULL && heap->medium_last_free_page != NULL)
				{
						AR_ASSERT(0);
				}

				if(heap->medium_first_free_page != NULL && heap->medium_last_free_page == NULL)
				{
						AR_ASSERT(0);
				}
				
				FreePage(heap, p);
		}
}




static AR_INLINE void* MediumRealloc(arHeap_t *heap, void *ptr, size_t bytes)
{
		mediumEntry_t		*e;
		size_t new_bytes;
		AR_ASSERT(heap != NULL && ptr != NULL);
		/*e = (mediumEntry_t*)((byte_t*)ptr - MEDIUM_HEADER_SIZE);*/
		e = (mediumEntry_t*)((byte_t*)ptr - AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE));
		
		AR_ASSERT(e->size > AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE));
		AR_ASSERT(e->free_block == 0);

		new_bytes = AR_ALIGN_SIZE(bytes) + AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE);

		if(e->size < new_bytes)
		{
				void *new_ptr;
				new_ptr = AR_AllocFromHeap(heap, bytes);
				AR_memcpy(new_ptr, ptr, e->size - AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE));
				AR_FreeToHeap(heap, ptr);
				return (void*)new_ptr;
		}else
		{
				return ptr;
		}
}




static AR_INLINE void*	LargeAllocate(arHeap_t *heap, size_t bytes)
{
		page_t *p;
		size_t *base_ptr;
		byte_t *ret;
		AR_ASSERT(heap != NULL && bytes > MEDIUM_SIZE);

		p = AllocatePage(heap, bytes + AR_ALIGN_SIZE(LARGE_HEADER_SIZE));

		if(!p)
		{
				return NULL;
		}

		ret = (byte_t*)p->data + AR_ALIGN_SIZE(LARGE_HEADER_SIZE);

		base_ptr = (size_t*)(ret - AR_ALIGN_SIZE(LARGE_HEADER_SIZE));
		base_ptr[0] = (size_t)p;
		ret[-1] = HEAP_LARGE_ALLOC;

		p->prev = NULL;
		p->next = heap->large_first_used_page;

		if(p->next)
		{
				p->next->prev = p;
		}

		heap->large_first_used_page = p;

		return (void*)ret;

}

static AR_INLINE void	LargeFree(arHeap_t *heap, void *ptr)
{
		page_t *p;
		AR_ASSERT(heap != NULL && ptr != NULL);
		((byte_t*)ptr)[-1] = HEAP_INVALID_ALLOC;
		p = (page_t*)(*((size_t*)((byte_t*)ptr - AR_ALIGN_SIZE(LARGE_HEADER_SIZE))));
		
		if(p->prev)
		{
				p->prev->next = p->next;
		}

		if(p->next)
		{
				p->next->prev = p->prev;
		}

		if(p == heap->large_first_used_page)
		{
				heap->large_first_used_page = p->next;
		}

		p->next = p->prev = NULL;

		FreePage(heap, p);
}



static AR_INLINE void* LargeRealloc(arHeap_t *heap, void *ptr, size_t nbytes)
{
		page_t *p;

		AR_ASSERT(heap != NULL && ptr != NULL);
		p = (page_t*)(*((size_t*)((byte_t*)ptr - AR_ALIGN_SIZE(LARGE_HEADER_SIZE))));


		AR_ASSERT(p->data_size > AR_ALIGN_SIZE(LARGE_HEADER_SIZE));

		if((p->data_size - AR_ALIGN_SIZE(LARGE_HEADER_SIZE)) < nbytes)
		{
				void *new_ptr;
				new_ptr = AR_AllocFromHeap(heap, nbytes);
				AR_memcpy(new_ptr, ptr, p->data_size - AR_ALIGN_SIZE(LARGE_HEADER_SIZE));
				AR_FreeToHeap(heap, ptr);
				return (void*)new_ptr;
		}else
		{
				return ptr;
		}

}




/**************************************************************************************************************/

/********************************************Heap****************************************************************************/

arHeap_t*		AR_CreateHeap()
{
		arHeap_t		*heap;
		heap = (arHeap_t*)malloc(sizeof(arHeap_t));

		if(heap == NULL)
		{
				return NULL;
		}
		
		heap->page_allocated = 0;
		heap->actual_mem_used = 0;
		heap->peak_mem_used = 0;
		

		
		heap->small_cur_page = AllocatePage(heap, PAGE_SIZE); 

		if(heap->small_cur_page == NULL)
		{
				free(heap);
				return NULL;
		}

		heap->small_cur_page_offset = SMALL_ALIGN(0);
		AR_memset(heap->small_first_free, 0, sizeof(heap->small_first_free));
		heap->small_first_used_page = NULL;
		
		heap->medium_first_free_page = NULL;
		heap->medium_last_free_page = NULL;
		heap->medium_first_used_page = NULL;

		heap->large_first_used_page = NULL;
		
		

		return heap;
}



void			AR_DestroyHeap(arHeap_t *heap)
{
		page_t *page;

		size_t small_count = 0, medium_count = 0, large_count = 0;

		AR_ASSERT(heap != NULL);
		
		if(heap->small_cur_page)
		{
				FreePage(heap, heap->small_cur_page);
				heap->small_cur_page = NULL;
				small_count++;
		}

		page = heap->small_first_used_page;
		while(page)
		{
				page_t *next = page->next;
				FreePage(heap, page);
				page = next;
				small_count++;
		}

		page = heap->medium_first_free_page;
		while(page)
		{
				page_t *next = page->next;
				FreePage(heap, page);
				page = next;
				medium_count++;
		}
		
		page = heap->medium_first_used_page;
		while(page)
		{
				page_t *next = page->next;
				FreePage(heap, page);
				page = next;
				medium_count++;
		}

		page = heap->large_first_used_page;
		while(page)
		{
				page_t *next = page->next;
				FreePage(heap, page);
				page = next;

				large_count++;
		}
		

		AR_ASSERT(heap->page_allocated == 0);
		AR_ASSERT(heap->actual_mem_used == 0);

		free(heap);
}


/*********************************************************************************************************************************************/


void*	AR_AllocFromHeap(arHeap_t *heap, size_t bytes)
{
		AR_ASSERT(heap != NULL && bytes > 0);

		if(!(bytes & ~(size_t)SMALL_SIZE))
		{
				return SmallAllocate(heap, bytes);
		}else if(!(bytes & ~(size_t)MEDIUM_SIZE))
		{
				return MediumAllocate(heap, bytes);
		}else
		{
				return LargeAllocate(heap, bytes);
		}
}

void*			AR_ClearedAllocFromHeap(arHeap_t *heap, size_t num, size_t elem_size)
{
		void *ptr;
		AR_ASSERT(heap != NULL && num > 0 && elem_size > 0);
		ptr = AR_AllocFromHeap(heap, num * elem_size);

		if(ptr)
		{
				AR_memset(ptr, 0, num * elem_size);
		}
		return ptr;
}


void	AR_FreeToHeap(arHeap_t *heap, void *ptr)
{
		byte_t *p;
		AR_ASSERT(heap != NULL && ptr != NULL);

		p = (byte_t*)ptr;

		switch(p[-1])
		{
		default:
				AR_error(AR_ERR_FATAL, L"%s\r\n", L"invalid memory block : AR_FreeToHeap"); 
				break;
		case HEAP_SMALL_ALLOC:
				SmallFree(heap, ptr);
				break;
		case HEAP_MEDIUM_ALLOC:
				MediumFree(heap, ptr);
				break;
		case HEAP_LARGE_ALLOC:
				LargeFree(heap, ptr);
				break;
		}
}


void*	AR_ReallocFromHeap(arHeap_t *heap, void *ptr, size_t bytes)
{
		byte_t *p;
		AR_ASSERT(heap != NULL);
		AR_ASSERT(bytes > 0);
		
		if(ptr == NULL)
		{
				return AR_AllocFromHeap(heap, bytes);
		}

		p = (byte_t*)ptr;

		switch(p[-1])
		{
		default:
				AR_error(AR_ERR_FATAL, L"%s\r\n", L"invalid memory block : AR_ReAllocFromHeap"); 
				return NULL;
				break;
		case HEAP_SMALL_ALLOC:
				return SmallRealloc(heap, ptr, bytes);
				break;
		case HEAP_MEDIUM_ALLOC:
				return MediumRealloc(heap, ptr, bytes);
				break;
		case HEAP_LARGE_ALLOC:
				return LargeRealloc(heap, ptr, bytes);
				break;
		}
}


arHeapUsage_t	AR_GetHeapMemUsage(const arHeap_t *heap)
{
		arHeapUsage_t	ret;
		AR_ASSERT(heap != NULL);
		ret.acutal_mem_used = (uint_64_t)heap->actual_mem_used;
		ret.peak_mem_used = (uint_64_t)heap->peak_mem_used;
		return ret;
}


AR_NAMESPACE_END



