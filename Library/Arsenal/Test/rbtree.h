#if defined(__LIB)


#ifndef __RBTREE__
#define __RBTREE__


#include "test.h"


AR_NAMESPACE_BEGIN


typedef enum { RB_RED,  RB_BLACK } rbColor_t;

struct __rb_node_tag;
typedef struct __rb_node_tag	rbNode_t;

struct __rb_tree_tag;
typedef struct __rb_tree_tag	rbTree_t;

struct __rb_node_tag
{
		rbColor_t		color;
		rbNode_t		*parent;
		rbNode_t		*left;
		rbNode_t		*right;
		
		int_t			data;
};



struct __rb_tree_tag
{
		rbNode_t		*root;
		rbNode_t		*left_most;
		rbNode_t		*right_most;
		size_t			count;
};

void	rb_init(rbTree_t		*tree);
void	rb_uninit(rbTree_t		*tree);
void	rb_clear(rbTree_t		*tree);

rbNode_t*		rb_get_successor(rbNode_t *node);
rbNode_t*		rb_get_previous(rbNode_t  *node);


rbNode_t*		rb_insert_equal(rbTree_t	*tree, int_t data);
bool_t			rb_remove(rbTree_t	*tree, int_t key);

AR_NAMESPACE_END



















#endif

#endif

