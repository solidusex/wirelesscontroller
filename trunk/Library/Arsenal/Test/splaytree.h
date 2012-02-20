
#if defined(__LIB)

#ifndef __SPLAYTREE__
#define __SPLAYTREE__


#include "test.h"


AR_NAMESPACE_BEGIN



struct __splay_node_tag;
typedef struct __splay_node_tag			splayNode_t;

struct __splay_tree_tag;
typedef struct __splay_tree_tag			splayTree_t;


struct __splay_node_tag
{
		
		int_t			data;
		splayNode_t		*parent;
		splayNode_t		*left;
		splayNode_t		*right;
};



struct __splay_tree_tag
{
		splayNode_t		*root;
		splayNode_t		*left_most;
		splayNode_t		*right_most;
		size_t			count;
};





AR_NAMESPACE_END

#endif


#endif

