
#if defined(__LIB)

#ifndef __AVLTREE__
#define __AVLTREE__


#include "test.h"



AR_NAMESPACE_BEGIN



struct __avl_node_tag;
typedef struct __avl_node_tag	avlNode_t;

struct __avl_tree_tag;
typedef struct __avl_tree_tag	avlTree_t;


typedef enum 
{
		AVL_LEFT = 0,
		AVL_RIGHT = 1
}avlDir_t;

#define OPPOSITE(_i)	(avlDir_t)(1 - (int_t)(_i))

struct __avl_node_tag
{
		
		int_t			data;
		avlNode_t		*parent;
		avlNode_t		*child[2];
		int_t			bf;
};



struct __avl_tree_tag
{
		avlNode_t		*root;
		avlNode_t		*left_most;
		avlNode_t		*right_most;
		size_t			count;
};


void	avl_init(avlTree_t		*tree);
void	avl_uninit(avlTree_t	*tree);
void	avl_clear(avlTree_t		*tree);

avlNode_t*		avl_get_successor(avlNode_t		*node);
avlNode_t*		avl_get_previous(avlNode_t		*node);
avlNode_t*		avl_insert_equal(avlTree_t	*tree, int_t data);
bool_t			avl_remove(avlTree_t	*tree, int_t key);
void			avl_print_tree(const avlTree_t *tree);
bool_t			avl_verify_tree(const avlTree_t	*tree);






void	avl_test();



AR_NAMESPACE_END



#endif



#endif
