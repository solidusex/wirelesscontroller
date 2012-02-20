
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


#ifndef __PARSER_LALR_DFA_H__
#define __PARSER_LALR_DFA_H__

#include "parser.h"


AR_NAMESPACE_BEGIN



void Parser_Init_LALR_Config();
void Parser_UnInit_LALR_Config();






typedef struct __lalr_config_tag lalrConfig_t;


/**************************************************LALR config list***************************************/
typedef struct __lalr_config_node_tag
{
		lalrConfig_t					*config;
		struct __lalr_config_node_tag	*next;
}lalrConfigNode_t;

typedef struct __lalr_config_list_tag
{
		lalrConfigNode_t		*head;
		lalrConfigNode_t		*tail;
		uint_32_t				count;
}lalrConfigList_t;


lalrConfigList_t*		Parser_CreateConfigList();
void					Parser_DestroyConfigList(lalrConfigList_t *lst, bool_t destroy_config);

arStatus_t				Parser_InsertToConfigList(lalrConfigList_t *lst, lalrConfig_t *cfg);

/*对lalrConfig_t本身不做拷贝*/
arStatus_t				Parser_CopyConfigList(lalrConfigList_t *l, const lalrConfigList_t *r);

/*链表的union，所以无存储分配*/
void					Parser_UnionConfigList(lalrConfigList_t *l, lalrConfigList_t *r);


void					Parser_SortConfigList(lalrConfigList_t *l);
int_t					Parser_CompConfigList(const lalrConfigList_t *l, const lalrConfigList_t *r);

lalrConfig_t*			Parser_FindFromConfigList(lalrConfigList_t *lst, size_t rule_num, size_t delim);

/*此函数生成lalrConfig_t，并插入lalrConfigList_t*和*/
lalrConfig_t*			Parser_InsertToConfigListByValue(lalrConfigList_t *lst, size_t rule_num, size_t delim, const psrGrammar_t *grammar);

/******************************************************************************************************/


/**************************************************LALR config***************************************/

typedef struct __lalr_config_follow_set_tag
{
		uint_8_t		*bit_set;
		uint_16_t		bit_cnt;
}lalrBitSet_t;

void	Parser_InitBitSet(lalrBitSet_t *bs, size_t nbits);
void	Parser_UnInitBitSet(lalrBitSet_t *bs);
void	Parser_ClearBitInBitSet(lalrBitSet_t *bs, size_t bit_idx);

arStatus_t	Parser_SetBitInBitSet(lalrBitSet_t *bs, size_t bit_idx);
arStatus_t	Parser_IsSetInBitSet(const lalrBitSet_t *bs, size_t bit_idx);
arStatus_t	Parser_UnionBitSet(lalrBitSet_t *dest, const lalrBitSet_t *src);



struct __lalr_config_tag
{
		bool_t					is_completed;
		uint_8_t				delim;
		uint_16_t				rule_num;
		
		lalrConfigList_t		*forward;
		lalrConfigList_t		*backward;

		lalrBitSet_t			follow_set;
};


arStatus_t		Parser_InitConfig(lalrConfig_t *config, size_t rule_num, size_t delim, const psrGrammar_t *grammar);
void			Parser_UnInitConfig(lalrConfig_t *config);
int_t			Parser_CompConfig(const lalrConfig_t *l, const lalrConfig_t *r);



arStatus_t	Parser_PrintConfig(const lalrConfig_t *config, const psrGrammar_t *gmr, arString_t *str);
arStatus_t	Parser_PrintConfigList(const lalrConfigList_t *lst, const psrGrammar_t *gmr, arString_t *str);





/**************************************************LALR State***************************************/
typedef struct	__lalr_action_tag			lalrAction_t;
typedef struct	__lalr_state_tag			lalrState_t;

typedef enum
{
		LALR_ACT_SHIFT,
		LALR_ACT_REDUCE,
		LALR_ACT_ACCEPT
}lalrActionType_t;


/*
如果act_type == LALR_ACT_SHIFT，则lalrAction_t描述了config通过符号symb到达了状态to,
如果act_type == (LALR_ACT_REDUCE || LALR_ACT_ACCEPT)则描述了config在symb上执行规约操作

*/
struct __lalr_action_tag
{
		lalrActionType_t				act_type;
		const psrSymb_t					*symb;
		lalrState_t						*to;
		const lalrConfig_t				*config; 
};


struct __lalr_state_tag
{
		lalrConfigList_t		*basis;			/*核心项集*/
		lalrConfigList_t		*all_config;	/*closure项集*/

		lalrAction_t			*actions;
		size_t					count;
		size_t					cap;
};


lalrState_t*	Parser_CreateState();
void			Parser_DestroyState(lalrState_t *state);

lalrAction_t*	Parser_InsertAction(lalrState_t *state, lalrState_t *to, const psrSymb_t *symb, const lalrConfig_t *config);


void			Parser_DestroyState_ALL(lalrState_t *state);



/*******************************************************************************************************************************/


typedef struct __lalr_state_set_tag
{
		lalrState_t		**set;
		size_t			count;
		size_t			cap;
}lalrStateSet_t;

void			Parser_InitStateSet(lalrStateSet_t *set);
void			Parser_UnInitStateSet(lalrStateSet_t *set);


lalrState_t*	Parser_FindStateByBasis(lalrStateSet_t *set, lalrConfigList_t *basis);
int_t			Parser_IndexOfStateSet(const lalrStateSet_t *set, const lalrState_t *state);

arStatus_t		Parser_InsertToStateSet(lalrStateSet_t *set, lalrState_t *state);
arStatus_t		Parser_CollectState(lalrStateSet_t *empty_set, lalrState_t *start);



/*
lalrState_t*   Parser_GetTransTo(lalrState_t *state, const psrSymb_t *symb);
*/

/*******************************************************************************************************/

lalrState_t*	Parser_Create_LR0_State(const psrGrammar_t *grammar);
lalrState_t*	Parser_Create_LALR_State(const psrGrammar_t *grammar);


AR_NAMESPACE_END

#endif

