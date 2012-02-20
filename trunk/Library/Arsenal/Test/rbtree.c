
#if defined(__LIB)

#include "rbtree.h"


AR_NAMESPACE_BEGIN




static AR_INLINE rbNode_t*		__create_node(int d, rbColor_t color)
{
		rbNode_t		*node = AR_NEW0(rbNode_t);
		node->data = d;
		node->color = color;
		return node;
}

static AR_INLINE void			__destroy_node(rbNode_t *node)
{
		AR_ASSERT(node != NULL);
		AR_DEL(node);
}


static AR_INLINE rbNode_t* __get_min(rbNode_t *node)
{
		
		if(node)while(node->left)node = node->left;
		return node;
}

static AR_INLINE rbNode_t* __get_max(rbNode_t *node)
{
		if(node)while(node->right) node = node->right;
		return node;
}

rbNode_t*		rb_get_successor(rbNode_t *node)
{
		if(node == NULL)
		{
				return node;
		}else if(node->right)
		{
				return __get_min(node->right);
		}else
		{
				rbNode_t *p = node->parent;
				while(p && p->right == node){ node = p; p = p->parent;}
				return p;
		}
}

rbNode_t*		rb_get_previous(rbNode_t  *node)
{
		if(node == NULL)
		{
				return NULL;
		}else if(node->left)
		{
				return __get_max(node->left);
		}else
		{
				rbNode_t *p = node->parent;
				while(p && p->left == node){ node = p; p = p->parent;}
				return p;
		}
}

/*
		A                                      B
          \                                   / \
           \                                 /   \
            B           ==>                 A     c
           / \                               \
          /   \                               \
         a     c							   a
*/

static AR_INLINE void __rotate_to_left(rbNode_t *node, rbNode_t **proot)
{
		rbNode_t *r;
		AR_ASSERT(node != NULL && node->right != NULL && proot != NULL && *proot != NULL);
		r = node->right;
		node->right = r->left;
		if(r->left)r->left->parent = node;
		r->left = node;
		if(node == *proot)
		{
				*proot = r;
		}else if(node == node->parent->left)
		{
				node->parent->left = r;
		}else
		{
				node->parent->right = r;
		}
		r->parent = node->parent;
		node->parent = r;
}

/*
			 A                                     B
            /                                     / \
           /                                     /   \
          B                ==>                  c     A
         / \                                         / 
        /   \                                       /   
       c     b                                     b    
*/

static AR_INLINE void __rotate_to_right(rbNode_t *node, rbNode_t **proot)
{
		rbNode_t *l;
		AR_ASSERT(node != NULL && node->left != NULL && proot != NULL && *proot != NULL);

		l = node->left;
		node->left = l->right;
		if(l->right)l->right->parent = node;
		l->right = node;

		if(node == *proot)
		{
				*proot = l;
		}else if(node == node->parent->left)
		{
				node->parent->left = l;
		}else
		{
				node->parent->right = l;
		}
		l->parent = node->parent;
		node->parent = l;
}



/*************************************rbTree**********************/

void	rb_init(rbTree_t		*tree)
{
		AR_ASSERT(tree != NULL);
		AR_memset(tree, 0, sizeof(*tree));
}

void	rb_uninit(rbTree_t		*tree)
{
		AR_ASSERT(tree != NULL);
		rb_clear(tree);
		AR_memset(tree, 0, sizeof(*tree));
}


static void __clear_node(rbNode_t *node)
{
		while(node)
		{
				rbNode_t *left = node->left;
				__clear_node(node->right);
				__destroy_node(node);
				node = left;
		}
}

void	rb_clear(rbTree_t		*tree)
{
		AR_ASSERT(tree != NULL);
		__clear_node(tree->root);
		tree->right_most = tree->left_most = tree->root = NULL;
		tree->count = 0;
}


static AR_INLINE void	__fix_insert(rbNode_t *node, rbNode_t **proot)
{
		rbNode_t		*p;
		AR_ASSERT(node != NULL && node->color == RB_RED && proot != NULL && *proot != NULL);
		p = node->parent;
		
		while(node != *proot && p->color == RB_RED)
		{
				rbNode_t		*uncle;
				if(p == p->parent->left)/*根节点一定为黑节点，因为p为红节点，则p->parent一定不为NULL*/
				{
						uncle = p->parent->right;

						if(uncle && uncle->color == RB_RED)
						{
								p->color = uncle->color = RB_BLACK;
								p->parent->color = RB_RED;
								node = p->parent;
								p = node->parent;

						}else
						{
								if(node == p->right)
								{
										__rotate_to_left(p, proot);
										node = p;
										p = node->parent;
								}
								
								p->parent->color = RB_RED;
								p->color = RB_BLACK;
								__rotate_to_right(p->parent, proot);

						}
				}else
				{
						uncle = p->parent->left;

						if(uncle && uncle->color == RB_RED)
						{
								p->color = uncle->color = RB_BLACK;
								p->parent->color = RB_RED;
								node = p->parent;
								p = node->parent;
						}else
						{

								if(node == p->left)
								{
										__rotate_to_right(p, proot);
										node = p;
										p = node->parent;
								}

								p->parent->color = RB_RED;
								p->color = RB_BLACK;
								__rotate_to_left(p->parent,proot);
						}
				}
		}

		(*proot)->color = RB_BLACK;
}








rbNode_t*		rb_insert_equal(rbTree_t	*tree, int_t data)
{
		rbNode_t *new_node;
		AR_ASSERT(tree != NULL);

		new_node = __create_node(data, RB_RED);

		if(tree->root == NULL)
		{
				AR_ASSERT(tree->root == NULL && tree->left_most == NULL && tree->right_most == NULL && tree->count == 0);
				tree->left_most = tree->right_most = tree->root = new_node;
				//new_node->color = RB_BLACK;
		}else
		{
				rbNode_t *p = NULL, *curr = tree->root;

				int_t cmp = 0;
				while(curr)
				{
						p = curr;
						cmp = AR_CMP(new_node->data, curr->data);
						
						if(cmp < 0)
						{
								curr = curr->left;
						}else
						{
								curr = curr->right;
						}
				}

				AR_ASSERT(p != NULL);

				if(cmp < 0)
				{
						AR_ASSERT(p->left == NULL);
						p->left = new_node;
						if(p == tree->left_most)tree->left_most = new_node;
				}else
				{
						AR_ASSERT(p->right == NULL);
						p->right = new_node;
						if(p == tree->right_most)tree->right_most = new_node;
				}
				new_node->parent = p;
		}
		tree->count++;

		__fix_insert(new_node, &tree->root);
		return new_node;
}



rbNode_t*		rb_find(rbTree_t		*tree, int_t key)
{
		rbNode_t		*curr = tree->root;
		AR_ASSERT(tree != NULL);
		
		while(curr)
		{
				if(key < curr->data)
				{
						curr = curr->left;
				}else if(key > curr->data)
				{
						curr = curr->right;
				}else
				{
						break;
				}
		}

		return curr;
}



static AR_INLINE void __fix_erase(rbNode_t *node, rbNode_t *parent, rbNode_t **proot)
{
		rbNode_t		*sibling;
		AR_ASSERT(proot != NULL && *proot != NULL);
		
		while((node != *proot) && (node == NULL || node->color == RB_BLACK))
		{
				if(node == parent->left)
				{
						sibling = parent->right;

						if(sibling->color == RB_RED)
						{
								sibling->color = parent->color;
								parent->color = RB_RED;
								__rotate_to_left(parent, proot);
								sibling = parent->right;
						}

						AR_ASSERT(sibling->color == RB_BLACK);

						if((sibling->left == NULL || sibling->left->color == RB_BLACK) && (sibling->right == NULL || sibling->right->color == RB_BLACK))
						{
								sibling->color = RB_RED;
								node = parent;
								parent = node->parent;
						}else
						{
								if(sibling->left != NULL && sibling->left->color == RB_RED)
								{
										sibling->left->color = RB_BLACK;
										sibling->color = RB_RED;
										__rotate_to_right(sibling, proot);
										sibling = parent->right;
								}
								sibling->color = parent->color;
								parent->color = RB_BLACK;
								sibling->right->color = RB_BLACK;
								__rotate_to_left(parent,proot);
								break;
						}
				}else
				{
						sibling = parent->left;

						if(sibling->color == RB_RED)
						{
								sibling->color = parent->color;
								parent->color = RB_RED;
								__rotate_to_right(parent,proot);
								sibling = parent->left;
						}

						AR_ASSERT(sibling->color == RB_BLACK);
						if((sibling->left == NULL || sibling->left->color == RB_BLACK) && (sibling->right == NULL || sibling->right->color == RB_BLACK))
						{
								sibling->color = RB_RED;
								node = parent;
								parent = node->parent;
						}else
						{
								if(sibling->right != NULL && sibling->right->color == RB_RED)
								{
										sibling->right->color = RB_BLACK;
										sibling->color = RB_RED;
										__rotate_to_left(sibling, proot);
										sibling = parent->left;
								}
								sibling->color = parent->color;
								parent->color = RB_BLACK;
								sibling->left->color = RB_BLACK;
								__rotate_to_right(parent, proot);
								break;
						}

				}
		}

		if(node)node->color = RB_BLACK;
		
}

static AR_INLINE rbNode_t* __unlink_node(rbNode_t *node, rbNode_t **proot, rbNode_t **pleft_most, rbNode_t **pright_most)
{
		rbNode_t *chd = NULL, *rm = NULL, *p = NULL;
		AR_ASSERT(node != NULL && proot != NULL && *proot != NULL && pleft_most != NULL && *pleft_most != NULL && pright_most != NULL && *pright_most != NULL);
		
		if(node->left == NULL && node->right == NULL)
		{
				rm = node;
				chd = NULL;
		}else if(node->left == NULL || node->right == NULL)
		{
				rm = node;
				chd = node->left != NULL ? node->left : node->right;
		}else
		{
				rm = rb_get_successor(node);
				chd = rm->right;
		}

		if(node == rm)
		{
				p = node->parent;
				if(chd)chd->parent = p;
				
				if(node == *proot)
				{
						*proot = chd;
				}else if(node == node->parent->left)
				{
						node->parent->left = chd;
				}else
				{
						node->parent->right = chd;
				}

				if(node == *pleft_most)
				{
						AR_ASSERT(node->left == NULL);
						if(node->right == NULL)
						{
								*pleft_most = p;
						}else
						{
								*pleft_most = __get_min(node->right);
						}
				}

				if(node == *pright_most)
				{
						AR_ASSERT(node->right == NULL);
						
						if(node->left == NULL)
						{
								*pright_most = p;
						}else
						{
								*pright_most = __get_max(node->left);
						}
				}
		}else
		{
				node->left->parent = rm;
				rm->left = node->left;
				
				if(rm == node->right)
				{
				/*
						A
				       / \
			          b   c
					  删除A，则
					  c
			         /
					b
				*/
						p = rm;
				}else
				{
/*
					   node
				       / \
			          b   p
					     / 
				        rm  
						  \
						  chd

					    rm
				       / \
			          b   p
					     / 
						chd
*/
						p = rm->parent;
						p->left = chd;
						if(chd)chd->parent = p;
						rm->right = node->right;
						rm->right->parent = rm;

				}
				
				if(node ==*proot)
				{
						*proot = rm;
				}else  if(node == node->parent->left)
				{
						node->parent->left = rm;
				}else
				{
						node->parent->right = rm;
				}
				rm->parent = node->parent;
				AR_ASSERT(node != *pleft_most && node != *pright_most);
				{
						rbColor_t tmp = rm->color;
						rm->color = node->color;
						node->color = tmp;
				}
		}


		if(*proot != NULL && node->color == RB_BLACK)__fix_erase(chd, p, proot);
		return node;
}


//////////////////////////////////////////

bool_t	rb_remove(rbTree_t	*tree, int_t key)
{
		rbNode_t		*node;
		bool_t			found = false;
		AR_ASSERT(tree != NULL);
		node = rb_find(tree, key);

		if(node)
		{
				if(tree->count == 1)
				{
						tree->root = tree->left_most = tree->right_most = NULL;
				}else
				{
						__unlink_node(node, &tree->root, &tree->left_most, &tree->right_most);
				}
		}

		found = node != NULL ? true : false;
		
		if(found)
		{
				__destroy_node(node); 
				tree->count--;
		}
		return found;
}


static void __print_tree(const rbNode_t  *node, size_t level)
{
		size_t i;
		if(node == NULL)return;
		__print_tree(node->right, level + 1);
		
		for(i = 0; i < level; ++i)AR_printf(L" - ");
		AR_printf(L" %d(%c)\r\n", node->data, node->color == RB_RED ? L'r' : L'b');
		
		__print_tree(node->left, level + 1);
}



void	rb_print_tree(const rbTree_t *tree)
{
		AR_printf(L"-------------------\r\n");
		__print_tree(tree->root, 0);
		AR_printf(L"-------------------\r\n");
}



static AR_INLINE size_t __count_black(const rbNode_t *node)
{
		size_t bc = 0;
		
		while(node)
		{
				bc += (node->color == RB_BLACK ? 1 : 0);
				node = node->parent;
		}
		return bc;
}


bool_t rb_verify_tree(const rbTree_t *self)
{
		const rbNode_t		*curr;
		size_t bn;
		AR_ASSERT(self != NULL);


		if(self->count == 0)
		{
				if(self->left_most != NULL || self->right_most != NULL || self->root != NULL)
				{
						return false;
				}
				
				return true;
		}
		
		curr = self->left_most;
		bn = __count_black(curr);
		

		while(curr != NULL)
		{
				const rbNode_t *x, *l, *r;

				x = curr;
				l = curr->left;
				r = curr->right;

				if(x->color == RB_RED)
				{
						if(l != NULL && l->color == RB_RED)
						{
								return false;
						}
						
						if(r != NULL && r->color == RB_RED)
						{
								return false;
						}
				}

				if(l != NULL && x->data < l->data)
				{
						return false;
				}
				
				if(r != NULL && r->data < x->data) 
				{
						return false;
				}
				
			
				if((l == NULL && r == NULL) && __count_black(x) != bn) 
				{
						return false;
				}

				curr = rb_get_successor((rbNode_t*)curr);
		}
		
		if(self->left_most != __get_min(self->root))
		{
				return false;
		}
		
		if(self->right_most != __get_max(self->root))
		{
				return false;
		}

		return true;
}


/********************************************test****************************************/
#define AR_EXCH(_type, _a,_b)	do{_type t = (_a); (_a) = (_b); (_b) = t;}while(0)
static AR_INLINE void shuffle(int_t *arr, size_t n)
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


static void	 rb_test_insert()
{
		rbTree_t		tree;
		rbNode_t		*node;
		int_t			i;
		
		rb_init(&tree);
		
		int_t arr[15];
		for(i = 0; i < 15; ++i)
		{
				arr[i] = rand()%100;
				rb_insert_equal(&tree, arr[i]);
				AR_printf(L"tree.count == %d\r\n", tree.count);
		}
		
		shuffle(arr, 15);
		
		for(int i = 0; i < 15; ++i)
		{
				rb_print_tree(&tree);
				AR_printf(L"Erase key == %d:\r\n", arr[i]);
				AR_printf(L"curr tree.count == %d:\r\n", tree.count);
				AR_ASSERT(rb_remove(&tree, arr[i]));
				rb_verify_tree(&tree);
				getchar();
		}


		AR_ASSERT(rb_verify_tree(&tree));
		AR_ASSERT(tree.count == 0);
/*
		AR_printf(L"ascend:\r\n");
		for(node = tree.left_most; node; node = rb_get_successor(node))
		{
				AR_printf(L"%d\r\n", node->data);
		}
		AR_printf(L"--------------------------\r\n");


		AR_printf(L"descend:\r\n");
		for(node = tree.right_most; node; node = rb_get_previous(node))
		{
				AR_printf(L"%d\r\n", node->data);
		}
		AR_printf(L"--------------------------\r\n");
*/



		rb_uninit(&tree);
}

void	rb_test()
{
		rb_test_insert();

}

AR_NAMESPACE_END


#endif

