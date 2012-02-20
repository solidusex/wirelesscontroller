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


#include "rgx.h"

AR_NAMESPACE_BEGIN


/***************************************************global*****************************/

static rgxNode_t*		__g_node_list = NULL;
static arSpinLock_t		__g_lock;

void RGX_InitNode()
{
		AR_InitSpinLock(&__g_lock);
		__g_node_list = NULL;

}


void RGX_UnInitNode()
{
		while(__g_node_list)
		{
				rgxNode_t *node = __g_node_list;
				__g_node_list = __g_node_list->left;
				AR_DEL(node);
		}
		AR_UnInitSpinLock(&__g_lock);
}


static rgxNode_t* __alloc_node()
{
		rgxNode_t *node;

		if(__g_node_list == NULL)
		{
				node = AR_NEW0(rgxNode_t);
				
		}else
		{
				AR_LockSpinLock(&__g_lock);
				
				if(__g_node_list == NULL)
				{
						node = AR_NEW0(rgxNode_t);
						
				}else
				{
						node = __g_node_list;
						__g_node_list = __g_node_list->left;
						AR_memset(node, 0, sizeof(*node));
				}
				AR_UnLockSpinLock(&__g_lock);
		}
		
		return node;
}


static void		__free_node(rgxNode_t *node)
{
		AR_ASSERT(node != NULL);
		
		AR_LockSpinLock(&__g_lock);

		node->left = __g_node_list;
		__g_node_list = node;
		AR_UnLockSpinLock(&__g_lock);
}


/**************************************************************************************/

rgxNode_t*		RGX_CreateNode(rgxNodeType_t type)
{
		rgxNode_t		*node;

		/*node = AR_NEW0(rgxNode_t);*/
		
		node = __alloc_node();

		if(node == NULL)
		{
				return NULL;
		}

		node->type = type;

		node->ref_count = 1;

		switch(type)
		{
		case RGX_BEGIN_T:
		{
				break;
		}
		case RGX_END_T:
		{
				break;
		}
		case RGX_LINE_BEGIN_T:
		{
				break;
		}
		case RGX_LINE_END_T:
		{
				break;
		}
		case RGX_ANY_CHAR_T:
		{
				break;
		}
		case RGX_CSET_T:
		{
				
				break;
		}
		case RGX_CAT_T:
		{
				break;
		}
		case RGX_BRANCH_T:
		{
				break;
		}
		case RGX_STAR_T:
		{
				break;
		}
		case RGX_QUEST_T:
		{
				break;
		}
		case RGX_PLUS_T:
		{
				break;
		}
		case RGX_LOOKAHEAD_T:
		{
				break;
		}
		case RGX_FINAL_T:
		{
				break;
		}
		case RGX_FIXCOUNT_T:
		{
				break;
		}
		default:
		{
				AR_CHECK(false, L"Arsenal : regex parser error %hs\r\n", AR_FUNC_NAME);
				return NULL;
				break;
		}
		}
		

		return node;

}

rgxNode_t*		RGX_CopyNewNode(const rgxNode_t *node)
{
		rgxNode_t *res;

		AR_ASSERT(node != NULL);

		AR_ASSERT(node->ref_count >= 1);

		res = (rgxNode_t*)node;

		AR_AtomicInc((volatile int_t*)&node->ref_count);

		return res;
}



void			RGX_DestroyNode(rgxNode_t *node)
{
		AR_ASSERT(node != NULL);
		
		AR_ASSERT(node->ref_count >= 1);

		if(AR_AtomicDec((volatile int_t*)&node->ref_count) > 0)
		{
				return;
		}

		
		
		switch(node->type)
		{
		case RGX_FINAL_T:
		case RGX_BEGIN_T:
		case RGX_LINE_BEGIN_T:
		case RGX_LINE_END_T:
		case RGX_END_T:
		case RGX_ANY_CHAR_T:
		{
				break;
		}
		
		case RGX_CSET_T:
		{
				break;
		}
		case RGX_CAT_T:
		case RGX_BRANCH_T:
		{
				if(node->left)
				{
						RGX_DestroyNode(node->left);
						node->left = NULL;
				}

				if(node->right)
				{
						RGX_DestroyNode(node->right);
						node->right = NULL;
				}
				
				break;
		}
		case RGX_STAR_T:
		case RGX_QUEST_T:
		case RGX_PLUS_T:
		case RGX_FIXCOUNT_T:
		case RGX_LOOKAHEAD_T:
		{
				/*AR_ASSERT(node->left != NULL && node->right == NULL);*/
				if(node->left)
				{
						RGX_DestroyNode(node->left);
						node->left = NULL;
				}

				if(node->right)
				{
						RGX_DestroyNode(node->right);
						node->right = NULL;
				}

				break;
		}
		default:
		{
				AR_CHECK(false, L"Arsenal : regex parser error %hs\r\n", AR_FUNC_NAME);
				break;
		}
		}

		__free_node(node);
}



arStatus_t			RGX_InsertToNode(rgxNode_t *root, rgxNode_t *node)
{
		AR_ASSERT(root != NULL && node != NULL);

		AR_ASSERT(root->type == RGX_CAT_T || root->type == RGX_BRANCH_T);

		if(root->left == NULL)
		{
				AR_ASSERT(root->right == NULL);
				root->left = node;
				return AR_S_YES;

		}else if(root->right == NULL)
		{
				root->right = node;
				return AR_S_YES;
		}else
		{
				rgxNode_t *tmp = RGX_CreateNode(root->type);

				if(tmp == NULL)
				{
						return AR_E_NOMEM;
				}

				tmp->left = root->left;
				tmp->right = root->right;
				root->left = tmp;
				root->right = node;

				return AR_S_YES;
		}
}








arStatus_t		RGX_ToString(const rgxNode_t *node, arString_t *str)
{
		
		arStatus_t status;
		AR_ASSERT(node != NULL && str != NULL);
		
		status = AR_S_YES;

		switch(node->type)
		{
		case RGX_CSET_T:
		{
				
				if(node->range.beg == node->range.end)
				{
						if(AR_iswgraph(node->range.beg) && node->range.beg < (wchar_t)128)
						{
								status = AR_AppendFormatString(str, L"%c", node->range.beg);

								if(status != AR_S_YES)
								{
										return status;
								}
						}else
						{
								status = AR_AppendFormatString(str, L"\\u%Id", node->range.beg);

								if(status != AR_S_YES)
								{
										return status;
								}
						}
				}else
				{
						status = AR_AppendString(str, L"[");
						
						if(status != AR_S_YES)
						{
								return status;
						}

						if(AR_iswgraph(node->range.beg) && node->range.beg < (wchar_t)128)
						{
								status = AR_AppendFormatString(str, L"%c", node->range.beg);

								if(status != AR_S_YES)
								{
										return status;
								}
						}else
						{
								status = AR_AppendFormatString(str, L"\\u%Id", node->range.beg);

								if(status != AR_S_YES)
								{
										return status;
								}
						}

						status = AR_AppendString(str, L"-");

						if(status != AR_S_YES)
						{
								return status;
						}

						if(AR_iswgraph(node->range.end) && node->range.end < (wchar_t)128)
						{
								status = AR_AppendFormatString(str, L"%c", node->range.end);

								if(status != AR_S_YES)
								{
										return status;
								}

						}else
						{
								status = AR_AppendFormatString(str, L"\\u%Id", node->range.end);

								if(status != AR_S_YES)
								{
										return status;
								}
						}

						status = AR_AppendString(str, L"]");

						if(status != AR_S_YES)
						{
								return status;
						}
				}
		}
				break;
		case RGX_CAT_T:
		{
				/*AR_AppendString(str, L"(");*/

				if(node->left)
				{
						status = RGX_ToString(node->left,str);

						if(status != AR_S_YES)
						{
								return status;
						}
				}

				if(node->right)
				{
						status = RGX_ToString(node->right,str);
						if(status != AR_S_YES)
						{
								return status;
						}
				}

				/*AR_AppendString(str, L")");*/
		}
				break;

		case RGX_BRANCH_T:
		{
				
				status = AR_AppendString(str, L"(");

				if(status != AR_S_YES)
				{
						return status;
				}

				if(node->left)
				{
						status = RGX_ToString(node->left,str);
						if(status != AR_S_YES)
						{
								return status;
						}
				}

				if(node->right)
				{
						status = AR_AppendString(str, L"|");
						if(status != AR_S_YES)
						{
								return status;
						}

						status = RGX_ToString(node->right,str);
						if(status != AR_S_YES)
						{
								return status;
						}
				}

				status = AR_AppendString(str, L")");
				if(status != AR_S_YES)
				{
						return status;
				}
		}
				break;
		case RGX_STAR_T:
		{
				AR_ASSERT(node->left != NULL && node->right == NULL);

				status = AR_AppendString(str, L"(");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = RGX_ToString(node->left, str);
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L")");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L"*");
				if(status != AR_S_YES)
				{
						return status;
				}

				if(node->non_greedy)
				{
						status = AR_AppendString(str, L"?");
						if(status != AR_S_YES)
						{
								return status;
						}
				}
				
				break;
		}
		case RGX_QUEST_T:
		{
				AR_ASSERT(node->left != NULL && node->right == NULL);

				status = AR_AppendString(str, L"(");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = RGX_ToString(node->left, str);
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L")");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L"?");

				if(node->non_greedy)
				{
						status = AR_AppendString(str, L"?");
						if(status != AR_S_YES)
						{
								return status;
						}

				}

				break;
		}
		case RGX_PLUS_T:
		{
				AR_ASSERT(node->left != NULL && node->right == NULL);

				status = AR_AppendString(str, L"(");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = RGX_ToString(node->left, str);
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L")");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L"+");

				if(status != AR_S_YES)
				{
						return status;
				}
				
				if(node->non_greedy)
				{
						status = AR_AppendString(str, L"?");
						if(status != AR_S_YES)
						{
								return status;
						}

				}
				
				break;
		}
		case RGX_FIXCOUNT_T:
		{
				wchar_t buf[128];
				AR_ASSERT(node->left != NULL && node->right == NULL);

				status = AR_AppendString(str, L"(");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = RGX_ToString(node->left, str);
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L")");
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L"{");
				if(status != AR_S_YES)
				{
						return status;
				}

				AR_u64tow_buf(buf, 128, (uint_64_t)node->fix_count, 10);


				status = AR_AppendString(str, buf);		
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L"}");
				if(status != AR_S_YES)
				{
						return status;
				}

				break;
		}
				break;
		case RGX_LOOKAHEAD_T:
		{
				AR_ASSERT(node->left != NULL && node->right == NULL);
				if(node->negative_lookahead)
				{
						status = AR_AppendString(str, L"(?!");
						if(status != AR_S_YES)
						{
								return status;
						}

				}else
				{
						status = AR_AppendString(str, L"(?=");
						if(status != AR_S_YES)
						{
								return status;
						}

				}
				
				status = RGX_ToString(node->left, str);
				if(status != AR_S_YES)
				{
						return status;
				}

				status = AR_AppendString(str, L")");
				if(status != AR_S_YES)
				{
						return status;
				}
		}
				break;
		case RGX_BEGIN_T:
		{
				status = AR_AppendString(str, L"^");
				if(status != AR_S_YES)
				{
						return status;
				}
		}
				break;
		case RGX_END_T:
		{
				status = AR_AppendString(str, L"$");
				if(status != AR_S_YES)
				{
						return status;
				}
		}
				break;
		case RGX_LINE_BEGIN_T:
		{
				status = AR_AppendString(str, L"\\B");
				if(status != AR_S_YES)
				{
						return status;
				}

		}
				break;
		
		case RGX_LINE_END_T:
		{
				status = AR_AppendString(str, L"\\E");
				if(status != AR_S_YES)
				{
						return status;
				}
		}
				break;
		case RGX_ANY_CHAR_T:
		{
				status = AR_AppendString(str, L".");
				if(status != AR_S_YES)
				{
						return status;
				}
				break;
		}
		case RGX_FINAL_T:
		{
				status = AR_AppendFormatString(str, L"[final : %Id]", node->final_val);
				if(status != AR_S_YES)
				{
						return status;
				}
		}
				break;
		default:
				AR_CHECK(false, L"Arsenal : regex parser error %hs\r\n", AR_FUNC_NAME);
		}

		return status;
}





AR_NAMESPACE_END








