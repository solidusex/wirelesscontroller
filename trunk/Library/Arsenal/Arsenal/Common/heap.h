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

#ifndef __ARSENAL_HEAP_H__
#define __ARSENAL_HEAP_H__

#include "common.h"

AR_NAMESPACE_BEGIN


/**********************************************************Heap***************************************************************/

#define AR_HEAP_ALIGN			8
#define AR_ALIGN_SIZE(_bytes)	( ((_bytes) + AR_HEAP_ALIGN - 1 ) & ~(AR_HEAP_ALIGN - 1) )


#define PAGE_SIZE				((size_t)(65536 - sizeof(page_t)))
#define SMALL_SIZE				255
#define MEDIUM_SIZE				32767

#define SMALL_ALIGN(_bytes)		(AR_ALIGN_SIZE( ((_bytes) + SMALL_HEADER_SIZE) ) - SMALL_HEADER_SIZE )

#define SMALL_HEADER_SIZE		((size_t)(sizeof(byte_t) + sizeof(byte_t)))
#define MEDIUM_HEADER_SIZE		((size_t) ( sizeof(mediumEntry_t) + sizeof(byte_t)))
#define MEDIUM_SMALLEST_SIZE	(AR_ALIGN_SIZE( 256 ) + AR_ALIGN_SIZE(MEDIUM_HEADER_SIZE))
#define LARGE_HEADER_SIZE		((size_t)(sizeof(size_t*) + sizeof(byte_t)))


#define HEAP_SMALL_ALLOC		0xaa
#define HEAP_MEDIUM_ALLOC		0xbb
#define HEAP_LARGE_ALLOC		0xcc
#define HEAP_INVALID_ALLOC		0xdd





typedef struct __arsenal_heap_tag		arHeap_t;
arHeap_t*		AR_CreateHeap();
void			AR_DestroyHeap(arHeap_t *heap);
void*			AR_AllocFromHeap(arHeap_t *heap, size_t bytes);
void*			AR_ClearedAllocFromHeap(arHeap_t *heap, size_t num, size_t elem_size);
void*			AR_ReallocFromHeap(arHeap_t *heap, void *ptr, size_t bytes);
void			AR_FreeToHeap(arHeap_t *heap, void *ptr);

typedef struct __arsenal_heap_usage_tag
{
		uint_64_t	acutal_mem_used;
		uint_64_t	peak_mem_used;
}arHeapUsage_t;

arHeapUsage_t	AR_GetHeapMemUsage(const arHeap_t *heap);



#define AR_HEAP_NEW(_heap, _type)						((_type*)AR_AllocFromHeap((_heap), sizeof(_type)))
#define AR_HEAP_NEW0(_heap, _type)						((_type*)AR_ClearedAllocFromHeap((_heap),1, sizeof(_type)))
#define AR_HEAP_NEWARR(_heap, _type, _n)				((_type*)AR_AllocFromHeap((_heap), sizeof(_type) * (_n)))
#define AR_HEAP_NEWARR0(_heap, _type, _n)				((_type*)AR_ClearedAllocFromHeap((_heap),(_n), sizeof(_type)))
#define AR_HEAP_REALLOC(_heap, _type, _ptr, _new_count) ((_type*)AR_ReallocFromHeap((_heap), (_ptr), sizeof(_type) * (_new_count)))
#define AR_HEAP_DEL(_heap, _ptr)						AR_FreeToHeap((_heap),(void*)(_ptr))


AR_NAMESPACE_END


#endif

