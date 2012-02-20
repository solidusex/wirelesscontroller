
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


#include "lalr.h"

AR_NAMESPACE_BEGIN




/****************************************lalrConfigList_t aux*****************************************/


static AR_INLINE void __init_config_list_freelist()
{
		
}


static AR_INLINE void __uninit_config_list_freelist()
{

		
}


static AR_INLINE lalrConfigList_t*		__create_config_list()
{
		lalrConfigList_t *res;
		res = AR_NEW(lalrConfigList_t);
		return res;
}

static AR_INLINE void	__destroy_config_list(lalrConfigList_t *lst)
{
		AR_ASSERT(lst);
		AR_DEL(lst);
}




/****************************************lalrConfig aux*****************************************/


static AR_INLINE void __init_config_freelist()
{
		
}

static AR_INLINE void __uninit_config_freelist()
{
		
}


static AR_INLINE lalrConfig_t*	__create_config()
{
		lalrConfig_t *res;
		res = AR_NEW(lalrConfig_t);


		return res;
}

static AR_INLINE void	__destroy_config(lalrConfig_t *config)
{
		AR_ASSERT(config);
		AR_DEL(config);


}




/****************************************lalrConfigNode_t aux*****************************************/



static AR_INLINE void __init_node_freelist()
{
		
}


static AR_INLINE void __uninit_node_freelist()
{
		
}



static AR_INLINE lalrConfigNode_t*		__create_node()
{
		lalrConfigNode_t *res;
		res = AR_NEW(lalrConfigNode_t);

		return res;
}

static AR_INLINE void					__destroy_node(lalrConfigNode_t *node)
{
		AR_ASSERT(node);
		AR_DEL(node);
}









AR_NAMESPACE_END


