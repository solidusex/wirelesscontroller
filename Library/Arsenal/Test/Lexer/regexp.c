
#if(0)

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



#include "regexp.h"


AR_NAMESPACE_BEGIN

/************************************************************NameSet******************************************/

void					Regex_InitNameSet(rgxNameSet_t	*set)
{
		AR_ASSERT(set != NULL);
		AR_memset(set, 0, sizeof(*set));
}



void			Regex_ClearNameSet(rgxNameSet_t *set)
{
		size_t i;

		AR_ASSERT(set != NULL);

		for(i = 0; i < set->count; ++i)
		{
				AR_ASSERT(set->name[i].node);
				RGX_DestroyNode(set->name[i].node);
		}

		set->count = 0;

}

void					Regex_UnInitNameSet(rgxNameSet_t	*set)
{
		Regex_ClearNameSet(set);
		if(set->name)AR_DEL(set->name);

		AR_memset(set,0,sizeof(*set));
}

bool_t					Regex_InsertToNameSet(rgxNameSet_t	*set, const wchar_t	*name, rgxNode_t *node)
{

		AR_ASSERT(set != NULL && name != NULL && node != NULL);
		if(Regex_FindFromNameSet(set, name) != NULL)return false;

		if(set->count == set->cap)
		{
				set->cap = (set->cap + 4)*2;
				set->name = AR_REALLOC(rgxName_t, set->name, set->cap);
				/*
				set->name = (rgxName_t*)AR_realloc(set->name, sizeof(rgxName_t) * set->cap);
				*/
		}

		AR_wcscpy(set->name[set->count].name, name);
		set->name[set->count].node = node;
		set->count++;
		return true;
}


bool_t					Regex_RemoveFromNameSet(rgxNameSet_t	*set, const wchar_t	*name)
{
		size_t i;
		AR_ASSERT(set != NULL && name != NULL);

		for(i = 0; i < set->count; ++i)
		{
				if(AR_wcscmp(set->name[i].name, name) == 0)
				{
						RGX_DestroyNode(set->name[i].node);
						break;
				}
		}

		if(i == set->count)return false;

		while(i < set->count - 1)
		{
				set->name[i] = set->name[i + 1];
				i++;
		}
		set->count--;

		return true;
}




const rgxNode_t*		Regex_FindFromNameSet(const rgxNameSet_t	*set, const wchar_t *name)
{
		size_t i;
		AR_ASSERT(set != NULL && name != NULL);

		for(i = 0; i < set->count; ++i)
		{
				if(AR_wcscmp(set->name[i].name, name) == 0)
				{
						AR_ASSERT(set->name[i].node != NULL);
						return set->name[i].node;
				}
		}

		return NULL;
}






AR_NAMESPACE_END

#endif