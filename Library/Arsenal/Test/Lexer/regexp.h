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


#ifndef __LEX_H__
#define __LEX_H__

#include "Common/common.h"


AR_NAMESPACE_BEGIN


struct __rgx_name_tag;
typedef struct __rgx_name_tag			rgxName_t;

struct __rgx_name_set_tag;
typedef struct __rgx_name_set_tag		rgxNameSet_t;

struct __rgx_node_tag;
typedef struct __rgx_node_tag			rgxNode_t;



/************************************************NameSet***************************************************/
#define	AR_RGX_MAXNAME					256



struct __rgx_name_tag
{
		wchar_t			name[AR_RGX_MAXNAME];
		rgxNode_t		*node;
};

struct __rgx_name_set_tag
{
		rgxName_t		*name;
		size_t			count;
		size_t			cap;
};


void					Regex_InitNameSet(rgxNameSet_t	*set);
void					Regex_UnInitNameSet(rgxNameSet_t	*set);
bool_t					Regex_InsertToNameSet(rgxNameSet_t	*set, const wchar_t	*name, rgxNode_t *node);
bool_t					Regex_RemoveFromNameSet(rgxNameSet_t	*set, const wchar_t	*name);
const rgxNode_t*		Regex_FindFromNameSet(const rgxNameSet_t	*set, const wchar_t *name);
void					Regex_ClearNameSet(rgxNameSet_t *set);




/************************************************Regex Node***************************************************/
typedef enum
{
		RGX_BEGIN_T,
		RGX_END_T,
		RGX_LINE_BEGIN_T,
		RGX_LINE_END_T,
		RGX_ANY_CHAR_T,

		RGX_CSET_T,

		RGX_CAT_T,
		RGX_BRANCH_T,

		RGX_STAR_T,
		RGX_QUEST_T,
		RGX_PLUS_T,
		RGX_FIXCOUNT_T,
		RGX_LOOKAHEAD_T,
		RGX_FINAL_T
}rgxNodeType_t;



struct __rgx_node_tag
{
		rgxNodeType_t		type;
		rgxNode_t			*left;
		rgxNode_t			*right;
		
		size_t				ref_count;

		union{
				struct {
						wchar_t	beg;
						wchar_t end;
				}range;
				
				size_t					fix_count;
				bool_t					negative_lookahead;
				bool_t					non_greedy;
				size_t					final_val;
		};
};



rgxNode_t*		RGX_CreateNode(rgxNodeType_t type);

rgxNode_t*		RGX_CopyNewNode(const rgxNode_t *node);

void			RGX_DestroyNode(rgxNode_t *node);

bool_t			RGX_InsertToNode(rgxNode_t *root, rgxNode_t *node);


void			RGX_ToString(const rgxNode_t *node, arString_t *str);



AR_NAMESPACE_END


















#endif


