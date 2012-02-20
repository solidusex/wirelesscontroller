


#if defined(__LIB)


#include "avltree.h"


AR_NAMESPACE_BEGIN

static AR_INLINE avlNode_t*		__create_node(int_t d)
{
		avlNode_t		*node = AR_NEW0(avlNode_t);
		node->data = d;
		return node;
}

static AR_INLINE void			__destroy_node(avlNode_t *node)
{
		AR_ASSERT(node != NULL);
		AR_DEL(node);
}


/*
向左转
			 A                                     B
            / \                                   / \
           /   \                                 /   \
          a     B           ==>                 A     c
               / \                             / \
              /   \                           /   \
             b     c                         a     b

NewBal(A):
 NewBal(A) = ht(b) - ht(a)
 OldBal(A) = ht(B) - ht(a) = ( 1 + max (ht(b), ht(c)) ) - ht(a)
 NewBal(A) - OldBal(A) = ht(b) - ( 1 + max (ht(b), ht(c)) ) + ht(a) - ht(a)
 NewBal(A) - OldBal(A) = ht(b) -  1 - max (ht(b), ht(c)) 
 NewBal(A) - OldBal(A) =  - 1 - max (ht(b), ht(c)) + ht(b)
 NewBal(A) - OldBal(A) =  - 1 - (max (ht(b), ht(c)) - ht(b))
 NewBal(A) = OldBal(A) - 1 - (max (ht(b), ht(c)) - ht(b) )
 NewBal(A) = OldBal(A) - 1 - max (ht(b)- ht(b), ht(c) - ht(b))
 NewBal(A) = OldBal(A) - 1 - max (0, OldBal(B))

NewBal(B):
 NewBal(B) = ht(c) - ht(A) = ht(c) - (1 + max(ht(a), ht(b)) )
 OldBal(B) = ht(c) - ht(b)

NewBal(B) - OldBal(B) = ht(c) - (1 + max(ht(a), ht(b)) ) - ht(c) + ht(b)
					  = ht(b) - (1 + max(ht(a), ht(b)) )
					  = ht(b) - 1 - max(ht(a), ht(b))
					  = - 1 - max(ht(a), ht(b)) + ht(b)
					  = - 1 - (max(ht(a), ht(b)) - ht(b))
					 

NewBal(B) =  OldBal(B) - 1 - (max(ht(a), ht(b)) - ht(b))
		  =  OldBal(B) - 1 - max(ht(a)- ht(b), ht(b)- ht(b)) 
		  =  OldBal(B) - 1 - max(ht(a)- ht(b), 0) 
		  =  OldBal(B) - 1 - max(-NewBal(A), 0) 
		  =  OldBal(B) - 1 + min(NewBal(A), 0) 

向右转
			 A                                     B
            / \                                   / \
           /   \                                 /   \
          B     a           ==>                 c     A
         / \                                         / \
        /   \                                       /   \
       c     b                                     b     a



 NewBal(A):
 NewBal(A) = ht(a) - ht(b)
 OldBal(A) = ht(a) - ht(B) = ht(a) - (1 + max (ht(b), ht(c)) )

 NewBal(A) - OldBal(A)	= ht(a) - ht(b) - ht(a) + (1 + max (ht(b), ht(c)) )
						= - ht(b) + (1 + max (ht(b), ht(c)) )
						= 1 + max (ht(b), ht(c)) - ht(b)
						= 1 + max (ht(b)- ht(b), ht(c)- ht(b)) 
						= 1 + max(0, -OldBal(B))
						= 1 - min(0, OldBal(B))

NewBal(A)	=	OldBal(A) + 1 - min(OldBal(B), 0)


NewBal(B):
		NewBal(B) = 1 + max(ht(a), ht(b)) - ht(c)
		OldBal(B) = ht(b) - ht(c)

		NewBal(B) - OldBal(B) = 1 + max(ht(a), ht(b)) - ht(c) - ht(b) + ht(c)
							  = 1 + max(ht(a), ht(b))  - ht(b)
							  = 1 + (max(ht(a), ht(b))  - ht(b))
							  = 1 + max(ht(a)- ht(b), ht(b)- ht(b))
							  = 1 + max(NewBal(A), 0)
		
		NewBal(B) = OldBal(B) + 1 + max(NewBal(A), 0)



综上所述：
LEFT Rotate:
		NewBal(A) = OldBal(A) - 1 - max (OldBal(B), 0)
		NewBal(B) =  OldBal(B) - 1 + min(NewBal(A), 0) 

RIGHT Rotate:
		NewBal(A) = OldBal(A) + 1 - min(OldBal(B), 0)
		NewBal(B) = OldBal(B) + 1 + max(NewBal(A), 0)
*/

static AR_INLINE void __rotate_node(avlNode_t *node, avlNode_t **proot, avlDir_t dir)
{
		avlNode_t		*tmp;
		AR_ASSERT(node != NULL && proot != NULL && *proot != NULL);
		AR_ASSERT(node->child[OPPOSITE(dir)] != NULL);
		
		tmp = node->child[OPPOSITE(dir)];
		node->child[OPPOSITE(dir)] = tmp->child[dir];
		if(node->child[OPPOSITE(dir)] != NULL)node->child[OPPOSITE(dir)]->parent = node;

		tmp->child[dir] = node;
		tmp->parent = node->parent;

		if(node == *proot)
		{
				*proot = tmp;
		}else if(node == node->parent->child[AVL_LEFT])
		{
				node->parent->child[AVL_LEFT] = tmp;
		}else
		{
				node->parent->child[AVL_RIGHT] = tmp;
		}
		
		node->parent = tmp;


		if(dir == AVL_LEFT)
		{
				/*
				NewBal(A) = OldBal(A) - 1 - max (OldBal(B), 0)
				NewBal(B) =  OldBal(B) - 1 + min(NewBal(A), 0) 
				*/
				node->bf = node->bf - 1 - AR_MAX(tmp->bf, 0);
				tmp->bf = tmp->bf - 1 +  AR_MIN(node->bf, 0);
		}else
		{
				/*
				NewBal(A) = OldBal(A) + 1 - min(OldBal(B), 0)
				NewBal(B) = OldBal(B) + 1 + max(NewBal(A), 0)
				*/
				node->bf = node->bf + 1 - AR_MIN(tmp->bf, 0);
				tmp->bf = tmp->bf + 1 + AR_MAX(node->bf, 0);

		}
}

/*
单旋转：


向左转

(1):B->bf == 0，左转后，整个树高不变,只有删除A->right才可能出现此种情况
			 A                                     B
              \                                   / \
               \                                 /   \
                B           ==>                 A     c
               / \                               \
              /   \                               \
             b     c                               b

			 A = +2 B = 0						A = +1 	B = -1

(2):B->bf == 1, 树高变短
			 A                                     B
              \                                   / \
               \                                 /   \
                B           ==>                 A     c
                 \                               
                  \                              
                   c                             
			A = +2 	B = +1					 A = 0 	B = 0


向右转

(1):B->bf == 0，右转后，整个树高不变,只有删除A->right才可能出现此种情况

			 A                                     B
            /                                     / \
           /                                     /   \
          B                ==>                  c     A
         / \                                         / 
        /   \                                       /   
       c     b                                     b    
	
		A = -2 	B = 0							A = -1 	B = +1
	   

(2):B->bf == 0，左转后，整个树高不变

			 A                                     B
            /                                     / \
           /                                     /   \
          B                ==>                  c     A
         /                                         
        /                                          
       c		                                   

	   A = -2 	B = -1							A = 0 	B = 0

*/


/*
返回true 为树高旋转后未更改，返回false,为树高降低
*/
static AR_INLINE bool_t __rotate_once(avlNode_t *node, avlNode_t **proot, avlDir_t dir)
{
		bool_t	height_changed = true;
		AR_ASSERT(node != NULL && proot != NULL && *proot != NULL);
		
		if(node->child[OPPOSITE(dir)]->bf == 0)height_changed = false;

		__rotate_node(node, proot, dir);
		return height_changed;
}


/*

				 	      
                
               
              
                   
                                               
                 
双旋转：

左旋：

		(1):B->bf == 0，旋转后，树高毕变短,			只有删除A->a的子树后才可能出现此种情况

				 A                                   A									     B
                / \                                 / \                                     / \
               /   \                               /   \                                   /   \
              a     C              ==>            a     B				 ==>			  A     C
                   / \                                 / \                               / \   / \
                  /   \								  /	  \								/   |  |  \
                 B     c					         b1    C                     	   a   b1  b2  c
                / \                                       / \
               /   \								     /   \
              b1   b2									b2    c

		A = +2 	B = 0	C = -1															A = 0 	B = 0	C = 0

		(2):B->bf == -1，旋转后，树高毕变短

				 A                                   A									     B
                / \                                 / \                                     / \
               /   \                               /   \                                   /   \
              a     C              ==>            a     B				 ==>			  A     C
                   / \                                 / \                               / \     \
                  /   \								  /	  \								/   |     \
                 B     c					         b1    C                     	   a   b1      c
                /										    \
               /   								             \
              b1   									          c
		   A = +2 	B = -1	C = -1														A = 0 	B = 0	C = +1


	   (3):B->bf == 1，旋转后，树高毕变短

				 A                                   A									     B
                / \                                 / \                                     / \
               /   \                               /   \                                   /   \
              a     C              ==>            a     B				 ==>			  A     C
                   / \                                   \                               /     / \
                  /   \								   	  \								/      |  \
                 B     c					               C                     	   a       b2  c
                  \                                       / \
                   \								     /   \
                   b2									b2    c
				A = +2	B = +1	C = -1													A = -1	B = 0	C = 0



右旋:

		(1): B->bf == 0，旋转后，树高毕变短,		只有删除A->a的子树后才可能出现此种情况

				 A                                   A									     B
                / \                                 / \                                     / \
               /   \                               /   \                                   /   \
              C     a              ==>            B     a				 ==>			  C     A
             / \								 / \									 / \   / \
			/   \								/	\									/	|  |   \
           c     B							   C	b1									c	b2 b1  a
                / \                           / \
               /   \					     /   \
              b2   b1						c    b2

		A = -2 	B = 0	C = +1															A = 0 	B = 0	C = 0



		(2): B->bf == -1，旋转后，树高毕变短

				 A                                   A									     B
                / \                                 / \                                     / \
               /   \                               /   \                                   /   \
              C     a              ==>            B     a				 ==>			  C     A
             / \								 /  									 / \     \
			/   \								/	 									/	|     \
           c     B							   C	  								   c	b2     a
                /                             / \
               /    					     /   \
              b2    						c    b2
		A = -2 	B = 0	C = +1															A =  1 	B = 0	C = 0

	
	(1): B->bf == 1，旋转后，树高毕变短		

				 A                                   A									     B
                / \                                 / \                                     / \
               /   \                               /   \                                   /   \
              C     a              ==>            B     a				 ==>			  C     A
             / \								 / \									 /     / \
			/   \								/	\									/	  |   \
           c     B							   C	b1								   c	  b1   a
                  \                           /  
                   \					     /    
                   b1						c     
		A = -2 	B = 1	C = +1															A = 0 	B = 0	C = -1
*/

/*
返回true 为树高旋转后未更改，返回false,为树高降低
*/
static AR_INLINE bool_t __rotate_twice(avlNode_t *node, avlNode_t **proot, avlDir_t dir)
{
		AR_ASSERT(node != NULL && proot != NULL && *proot != NULL);
		AR_ASSERT(node->child[OPPOSITE(dir)] != NULL);
		__rotate_once(node->child[OPPOSITE(dir)], proot, OPPOSITE(dir));
		__rotate_once(node, proot, dir);
		return true;
}


/*
返回true 为树高旋转后未更改，返回false,为树高降低
*/
static AR_INLINE bool_t __rebalance_node(avlNode_t *node, avlNode_t **proot)
{
		AR_ASSERT(node != NULL && proot != NULL && *proot != NULL);
		AR_ASSERT(node->bf <-1 || node->bf > 1);
		
		if(node->bf < -1)
		{
				if(node->child[AVL_LEFT]->bf == 1)
				{
						return __rotate_twice(node, proot, AVL_RIGHT);
				}else
				{
						return __rotate_once(node, proot, AVL_RIGHT);
				}
		}else if(node->bf > 1)
		{
				if(node->child[AVL_RIGHT]->bf == -1)
				{
						return __rotate_twice(node, proot, AVL_LEFT);
				}else
				{
						return __rotate_once(node, proot, AVL_LEFT);
				}
		}
		
		return false;
}

typedef enum { AVL_ERASE = -1, AVL_INSERT = 1}cmd_t;


/*node为被增加或删除的节点的父节点， bf == 1则增删节点为node右节点，bf == -1，则增删节点为node左节点*/
static AR_INLINE void __fixup(avlNode_t *node, avlNode_t **proot, int_t bf, cmd_t cmd)
{
		avlNode_t		*p;
		AR_ASSERT(proot != NULL && *proot != NULL && (bf == 1 || bf == -1 || bf == 0));
		
		while(node)
		{
				p = node->parent;

				node->bf += ((int_t)cmd * bf);
				
				if(p == NULL)
				{
						bf = 0;
				}else if(p->child[AVL_LEFT] == node)
				{
						bf = -1;
				}else 
				{
						bf = 1;
				}

				if(cmd == AVL_INSERT)
				{
						if(node->bf == 0)
						{
								/*
										如果插入后，以node为root的子树达到平衡，则树高不变，则不需要
								*/
								return;
						}else if(node->bf < -1 || node->bf > 1)
						{
						
								/*插入之后，当平衡因子< -2 或 > 2 ,则旋转，
								若旋转后树高更改，则当前子树树高不变，不需要继续向上修正bf
						
						
								例如：
								A                                     A								B
								 \                                     \						   / \			
								  \                                     \						  /	  \
						           B           ==>                       B			==>			  A    c 
							      										  \
							       									 	   \
							        							     	    c
								插入b后向左右转后原树高不变，所以不需要继续修正
								*/
								if(__rebalance_node(node, proot))return;
						}else
						{
								/*
								以当前node为root的子树被插入新节点后，不平衡，但并不破坏AVL法则，则继续向上修正平衡因子
								*/
						}

				}else
				{
						if(node->bf < -1 || node->bf > 1)
						{
								/*
								删除后树高不平衡，则旋转,如果旋转后是树高未更改则返回，否则继续向上修正平衡因子
								例如：
								A                                     B
								 \                                   / \
								  \                                 /   \
							       B           ==>                 A     c
							      / \                               \
							     /   \                               \
							    b     c                               b
								这里，树高与删除前相同，因此不需要继续向上修正
								*/
								if(!__rebalance_node(node, proot))return;
						
						}else if(node->bf == 0)
						{
								/*
								以当前node为root的子树被删除某节点后，node->bf平衡，则证明此子树变短，且当前node不符合
								*/
						}else
						{
								/*
								例如：
								   A                                     B
								  / \                                     \
								 /   \                                     \
								a     b           ==>                       c
							      
								这里，树高与删除前相同，未破坏平衡法则,因此不需要继续向上修正平衡因子，直接返回
							    */
								return ;
						}
				}
				node = p;


		}
}



static AR_INLINE avlNode_t*		__get_min(avlNode_t *node)
{
		if(node == NULL)return NULL;
		while(node->child[AVL_LEFT] != NULL)node = node->child[AVL_LEFT];
		return node;
}

static AR_INLINE avlNode_t*		__get_max(avlNode_t *node)
{
		if(node == NULL)return NULL;

		while(node->child[AVL_RIGHT] != NULL)node = node->child[AVL_RIGHT];
		
		return node;
}



avlNode_t*		avl_get_successor(avlNode_t		*node)
{
		
		if(node == NULL)
		{
				return NULL;

		}else if(node->child[AVL_RIGHT])
		{
				return __get_min(node->child[AVL_RIGHT]);
		}else
		{
				avlNode_t		*p = node->parent;
						
				while(p && p->child[AVL_RIGHT] == node){ node = p; p = node->parent;}
				return p;
		}
}


avlNode_t*		avl_get_previous(avlNode_t		*node)
{
		if(node == NULL)
		{
				return NULL;
		}else if(node->child[AVL_LEFT])
		{
				return __get_max(node->child[AVL_LEFT]);
		}else
		{
				avlNode_t		*p = node->parent;
				while(p && p->child[AVL_LEFT] == node){ node = p; p = node->parent;}
				return p;
		}
}


static void __clear_node(avlNode_t	*node)
{
		while(node)
		{
				avlNode_t		*l = node->child[AVL_LEFT];
				__clear_node(node->child[AVL_RIGHT]);
				__destroy_node(node);
				node = l;
		}
		
}


void	avl_clear(avlTree_t		*tree)
{
		__clear_node(tree->root);
		tree->count = 0;
		tree->root = tree->left_most = tree->right_most = NULL;
}


void	avl_init(avlTree_t		*tree)
{
		AR_ASSERT(tree != NULL);
		AR_memset(tree, 0, sizeof(*tree));
}


void	avl_uninit(avlTree_t	*tree)
{
		AR_ASSERT(tree != NULL);
		avl_clear(tree);
		AR_memset(tree, 0, sizeof(*tree));
}




avlNode_t* avl_insert_equal(avlTree_t	*tree, int_t data)
{
		avlNode_t		*p = NULL, *curr = NULL, *new_node = NULL;
		AR_ASSERT(tree != NULL);

		if(tree->count == 0)
		{
				AR_ASSERT(tree->root == NULL && tree->left_most == NULL && tree->right_most == NULL);
				tree->root = tree->left_most = tree->right_most = __create_node(data);
				tree->count++;
				return tree->root;
		}
		
		curr = tree->root;

		while(curr)
		{
				p = curr;

				if(data < curr->data)
				{
						curr = curr->child[AVL_LEFT];
				}else
				{
						curr = curr->child[AVL_RIGHT];
				}
		}

		new_node = __create_node(data);
		if(data < p->data)
		{
				p->child[AVL_LEFT] = new_node;
		}else
		{
				p->child[AVL_RIGHT] = new_node;
		}
		new_node->parent = p;

		if(p == tree->left_most && data < p->data)tree->left_most = new_node;
		if(p == tree->right_most && data >= p->data)tree->right_most = new_node;

		tree->count++;

		__fixup(p, &tree->root, new_node == p->child[AVL_LEFT] ? -1 : 1, AVL_INSERT);

		
		return new_node;
}



static AR_INLINE avlNode_t* __unlink_node(avlNode_t *node, avlNode_t **proot, avlNode_t **pleft_most, avlNode_t **pright_most)
{
		avlNode_t		*rm, *chd, *p;
		int_t			bf;

		AR_ASSERT(node != NULL && proot != NULL && *proot != NULL && pleft_most != NULL && *pleft_most != NULL && pright_most != NULL && *pright_most != NULL);

		rm = node; chd = NULL; p = NULL; bf = 0;
		
		
		if(rm->child[AVL_LEFT] == NULL)
		{
				chd = rm->child[AVL_RIGHT];
		}else
		{
				if(rm->child[AVL_RIGHT] == NULL)
				{
						chd = rm->child[AVL_LEFT];
				}else
				{
						rm = avl_get_successor(rm);
						chd = rm->child[AVL_RIGHT];
				}
		}

		if(rm != node)
		{
				rm->child[AVL_LEFT] = node->child[AVL_LEFT];
				rm->child[AVL_LEFT]->parent = rm;

				if(rm != node->child[AVL_RIGHT])
				{
						p = rm->parent;
						p->child[AVL_LEFT] = chd;
						if(chd != NULL)chd->parent = p;
						rm->child[AVL_RIGHT] = node->child[AVL_RIGHT];
						rm->child[AVL_RIGHT]->parent = rm;
						bf = -1;
				}else
				{
						p = rm;
						bf = 1;
				}

				if(node == *proot)
				{
						*proot = rm;
				}else if(node == node->parent->child[AVL_LEFT])
				{
						node->parent->child[AVL_LEFT] = rm;
				}else
				{
						node->parent->child[AVL_RIGHT] = rm;
				}

				rm->parent = node->parent;
				{
						int_t bf = rm->bf; 
						rm->bf = node->bf; 
						node->bf = bf;
				}
				
		}else
		{
				p = node->parent;
				if(chd != NULL) chd->parent = p;

				if(node == *proot)
				{
						*proot = chd;
				}else if(node == p->child[AVL_LEFT])
				{
						p->child[AVL_LEFT] = chd;
						bf = -1;
				}else
				{
						p->child[AVL_RIGHT] = chd;

						bf = 1;
				}
				
				if(node == *pleft_most)
				{
						if(node->child[AVL_RIGHT] == NULL)
						{
								*pleft_most = p;
						}else
						{
								*pleft_most = __get_min(chd);
						}
				}

				if(node == *pright_most)
				{
						if(node->child[AVL_LEFT] == NULL)
						{
								*pright_most = p;
						}else
						{
								*pright_most = __get_max(node->child[AVL_LEFT]);	
						}
				}
		}

		__fixup(p, proot, bf, AVL_ERASE);

		return node;
}




avlNode_t*		avl_find(avlTree_t		*tree, int_t key)
{
		avlNode_t		*curr = tree->root;
		AR_ASSERT(tree != NULL);
		
		while(curr)
		{
				if(key < curr->data)
				{
						curr = curr->child[AVL_LEFT];
				}else if(key > curr->data)
				{
						curr = curr->child[AVL_RIGHT];
				}else
				{
						break;
				}
		}

		return curr;
}


bool_t	avl_remove(avlTree_t	*tree, int_t key)
{
		avlNode_t		*node;
		bool_t			found = false;
		AR_ASSERT(tree != NULL);
		node = avl_find(tree, key);

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


static void __print_tree(const avlNode_t  *node, size_t level)
{
		size_t i;
		if(node == NULL)return;
		__print_tree(node->child[AVL_RIGHT], level + 1);
		
		for(i = 0; i < level; ++i)AR_printf(L" - ");
		AR_printf(L" %d \r\n", node->data);
		
		__print_tree(node->child[AVL_LEFT], level + 1);
}



void	avl_print_tree(const avlTree_t *tree)
{
		AR_printf(L"-------------------\r\n");
		__print_tree(tree->root, 0);
		AR_printf(L"-------------------\r\n");
}


static int_t __calc_height(const avlNode_t *node)
{
		int_t l, r;
		if(node == NULL)return 0;

		l = __calc_height(node->child[AVL_LEFT]);
		r = __calc_height(node->child[AVL_RIGHT]);
		return 1 + AR_MAX(l,r);
}



bool_t avl_verify_tree(const avlTree_t	*tree)
{
		avlNode_t		*curr;
		AR_ASSERT(tree != NULL);

		curr = __get_min(tree->root);

		while(curr)
		{
				int_t l = __calc_height(curr->child[AVL_LEFT]);
				int_t r = __calc_height(curr->child[AVL_RIGHT]);

				if(curr->bf != (r - l))
				{
						return false;
				}

				
				if(curr->child[AVL_LEFT] != NULL)
				{
						if(curr->child[AVL_LEFT]->data > curr->data)
						{
								return false;
						}
				}
						
				if(curr->child[AVL_RIGHT] != NULL)
				{
						if(curr->data > curr->child[AVL_RIGHT]->data )
						{
								return false;
						}
				}
				
				if(curr->child[AVL_LEFT] && curr->child[AVL_RIGHT])
				{
						if(curr->child[AVL_LEFT]->data > curr->child[AVL_RIGHT]->data)
						{
								return false;
						}
				}
				curr = avl_get_successor(curr);
		}
		
		return true;
}




/***********************************************************test**************************************************************/


void	avl_test_insert()
{
		avlTree_t		tree;
		avlNode_t		*node;
		int_t			i;
		
		avl_init(&tree);

		for(i = 0; i < 10240; ++i)
		{
				avl_insert_equal(&tree, rand()%999999);
				
		}

		
		
		avl_print_tree(&tree);
		

		if(!avl_verify_tree(&tree))
		{
				AR_ASSERT(false);
		}


		node = tree.left_most;
		while(node)
		{
				AR_printf(L"%d\r\n", node->data);
				node = avl_get_successor(node);
		}
		AR_printf(L"\r\n");

		avl_uninit(&tree);
}



#define INSERT_CNT 10
void	avl_test_remove()
{
		avlTree_t		tree;
		int_t			*rec;
		int_t			i;
		
		rec = AR_NEWARR0(int_t, INSERT_CNT);

		avl_init(&tree);

		for(i = 0; i < INSERT_CNT; ++i)
		{
				int_t n = rand()%999999;
				avl_insert_equal(&tree, n);
				rec[i] = n;
		}

		avl_print_tree(&tree);

		if(!avl_verify_tree(&tree))
		{
				AR_ASSERT(false);
		}
		
		for(i = 0; i < INSERT_CNT; ++i)
		{
				if(!avl_remove(&tree, rec[i]))
				{
						AR_ASSERT(false);
				}
				AR_printf(L"key == %d\r\n", rec[i]);
				avl_print_tree(&tree);
				AR_printf(L"\r\n");
				
				if(!avl_verify_tree(&tree))
				{
						AR_ASSERT(false);
				}

				/*
				avlNode_t *node = avl_find(&tree, rec[i]);
				AR_ASSERT(node && node->data == rec[i]);
				AR_printf(L"key == %d Node == %d\r\n", rec[i], node->data);
				*/

				getchar();
				
		}

		avl_uninit(&tree);

		AR_DEL(rec);
}





void	avl_test()
{
		//avl_test_insert();
		avl_test_remove();
}

AR_NAMESPACE_END



#endif
