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

#ifndef __PARSER_H__
#define __PARSER_H__

#include "../Common/common.h"


AR_NAMESPACE_BEGIN




/**********************************必须在所有其它Parser_族函数之前调用，否则行为未定义***************************/
arStatus_t	Parser_Init();

/**********************************必须在所有其它Parser_族函数之后调用，否则行为未定义***************************/
arStatus_t	Parser_UnInit();



/*******************************************辅助模块********************************************/


typedef void			psrNode_t;


typedef struct __parser_token_tag
{
		size_t			term_val;

		const wchar_t	*str;
		
		size_t			index;
		size_t			str_cnt;
		
		size_t			line;
		size_t			col;
}psrToken_t;

#define PARSER_TOTERMTOK(_ltok, _psr_tok)						\
		do{														\
				(_psr_tok)->str = (_ltok)->str;					\
				(_psr_tok)->index = (_ltok)->index;				\
				(_psr_tok)->str_cnt = (_ltok)->count;			\
				(_psr_tok)->term_val = (_ltok)->value;			\
				(_psr_tok)->line = (_ltok)->line;				\
				(_psr_tok)->col = (_ltok)->col;					\
		}while(0)


#define PARSER_TOLEXTOK(_psr_tok,_ltok)							\
		do{														\
				(_ltok)->str = (_psr_tok)->str;					\
				(_ltok)->index = (_psr_tok)->index;				\
				(_ltok)->count = (_psr_tok)->str_cnt;			\
				(_ltok)->value = (_psr_tok)->term_val;			\
				(_ltok)->line = (_psr_tok)->line;				\
				(_ltok)->col = (_psr_tok)->col;					\
		}while(0)


typedef struct __parser_return_value_tag
{
		arStatus_t		status;
		psrNode_t		*node;
}psrRetVal_t;

typedef psrRetVal_t		(AR_STDCALL *psrTermFunc_t)(const psrToken_t *tok,void *ctx);
typedef psrRetVal_t		(AR_STDCALL *psrRuleFunc_t)(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);


typedef void			(AR_STDCALL *psrFreeFunc_t)(psrNode_t *node, void *ctx);



/*
		此函数如果返回AR_S_YES 则parser继续在state stack上搜索是否有匹配的error 符号，否则，则丢弃当前导致错误的符号tok

		可以将此返回值理解为是否希望尝试移入此tok，返回true则通过error token尝试，返回false，则此token被丢弃，可在此回调函数内
		移动词法值到下一个所希望的元素。
*/
typedef arStatus_t		(AR_STDCALL *psrErrorFunc_t)(const psrToken_t *tok, const size_t expected[], size_t count, void *ctx);



typedef struct __parser_handler_tag
{
		psrErrorFunc_t	error_f;
		psrFreeFunc_t	free_f;
}psrHandler_t;







#define PARSER_EOI_TOKVAL				0x0000/*end of input符号的词法值*/
#define Parser_EPSILON_TOKVAL			0x0001
/*#define PARSER_LALR_TOKVAL			0x0002*/
#define PARSER_ERROR_TOKVAL				0x0003
#define PARSER_DEFPREC_TOKVAL			0x0004

#define PARSER_MIN_TOKENVAL				0x0100		/*最小终结符value*/


/*
所有符号如无特殊定义，则结合性都为NO_ASSOC，左结合表示在发生冲突时，优先选择同优先级的规约，而右结合与其相反，例如
expr -> id | expr '-' expr;

在 输入为 expr - expr - expr时，如果无结合性，则为冲突，如声明'-'为左结合，则优先归于前面的expr-expr，右结合反之

*/

typedef enum 
{
		PARSER_ASSOC_NONASSOC,
		PARSER_ASSOC_LEFT,
		PARSER_ASSOC_RIGHT
}psrAssocType_t;/*终结符结合性*/


typedef enum
{
		PARSER_SLR,
		PARSER_LALR
}psrLRItemType_t;

typedef psrLRItemType_t psrModeType_t;

/*******************************************辅助模块结束****************************************************************/

/***************************************************前向声明************************************************/

struct __parser_symbol_tag;
typedef struct __parser_symbol_tag		psrSymb_t;

struct __parser_grammar_tag;
typedef struct __parser_grammar_tag		psrGrammar_t;



struct __parser_action_tag;
typedef struct __parser_action_tag		psrActionTable_t;

struct __term_table_tag;
typedef struct __term_table_tag			psrTermInfoTbl_t;

struct __expected_message_tag;
typedef	struct __expected_message_tag	psrExpectedMsg_t;


struct __parser_stack_tag;
typedef struct __parser_stack_tag		psrStack_t;

struct __parser_node_stack;
typedef struct __parser_node_stack		psrNodeStack_t;


struct __parser_tag;
typedef struct __parser_tag				parser_t;



struct __parser_context_tag;
typedef struct __parser_context_tag			psrContext_t;


/***************************************************前向声明结束************************************************/





/****************************************************************Symbol***********************************************************************/


typedef enum
{
		PARSER_TERM,
		PARSER_NONTERM
}psrSymbType_t;




struct __parser_symbol_tag
{
		psrSymbType_t	type;
		const wchar_t	*name;
		uint_t			hash_code;
		size_t			ref_count;
		
		int_t			spec_id;
};


const psrSymb_t*		Parser_CreateSymb(const wchar_t *name, psrSymbType_t t);
const psrSymb_t*		Parser_CreateSymbN(const wchar_t *name, size_t n, psrSymbType_t t);

const psrSymb_t*		Parser_CopyNewSymb(const psrSymb_t *sour);
void					Parser_DestroySymb(const psrSymb_t *symb);
int_t					Parser_CompSymb(const psrSymb_t *l, const psrSymb_t *r);

/***************************************symbol_list***************************************************/

typedef struct __parser_symbol_list_tag
{
		const psrSymb_t **lst;
		size_t			count	:		16;
		size_t			cap		:		16;	
}psrSymbList_t;

void				Parser_InitSymbList(psrSymbList_t *symb_lst);
void				Parser_UnInitSymbList(psrSymbList_t *symb_lst);
void				Parser_ClearSymbList(psrSymbList_t *symb_lst);
arStatus_t			Parser_ReserveSymbListCapacity(psrSymbList_t *symb_lst, size_t cap);

arStatus_t			Parser_CopySymbList(psrSymbList_t *dest, const psrSymbList_t *sour);

arStatus_t			Parser_InsertToSymbList(psrSymbList_t *symb_lst, const psrSymb_t *symb);

const psrSymb_t*	Parser_IndexOfSymbList(const psrSymbList_t *symb_lst, size_t idx);
int_t				Parser_FindFromSymbList(const psrSymbList_t *symb_lst, const psrSymb_t* symb);

arStatus_t			Parser_RemoveFromSymbListByIndex(psrSymbList_t *symb_lst, size_t index);

int_t				Parser_BSearchFromSymbList(const psrSymbList_t *symb_lst, const psrSymb_t* symb);
void				Parser_SortSymbList(psrSymbList_t *symb_lst);



arStatus_t			Parser_InsertToSymbList_Unique(psrSymbList_t *symb_lst, const psrSymb_t *symb);



/********************************************************************************************************/
arStatus_t			Parser_PrintSymbol(const psrSymb_t *symb,	arString_t *str);
arStatus_t			Parser_PrintSymbolList(const psrSymbList_t *lst, arString_t *str);



/**************************************Symbol Map**********************************************************/



typedef struct __parser_symbmap_record_tag
{
		const psrSymb_t							*key;
		psrSymbList_t							lst;
		bool_t									can_empty;
		struct __parser_symbmap_record_tag		*next;
}psrMapRec_t;


#define MAP_BUCKET_SIZE (63)

typedef struct __parser_symbmap_tag
{
		psrMapRec_t		*bucket[MAP_BUCKET_SIZE];
		size_t			item_count;
}psrSymbMap_t;


void					Parser_InitSymbMap(psrSymbMap_t *map);
void					Parser_UnInitSymbMap(psrSymbMap_t *map);

arStatus_t				Parser_InsertToSymbMap(psrSymbMap_t *map, const psrSymb_t *key, const psrSymb_t *val);
arStatus_t				Parser_SetSymbEpsilon(psrSymbMap_t *map, const psrSymb_t *key, bool_t is_epsilon);

psrMapRec_t*			Parser_GetSymbolFromSymbMap(const psrSymbMap_t *map, const psrSymb_t *key);

arStatus_t				Parser_PrintSymbolMap(const psrSymbMap_t *map, arString_t *str);



/****************************************************************Symbol结束***********************************************************************/






/*******************************************************************Grammar*******************************************************************/


typedef struct __terminal_info_tag
{
		const	psrSymb_t		*term;
		size_t					prec;
		psrAssocType_t			assoc;
		size_t					val;
		psrTermFunc_t			leaf_f;	/*当有合法的token移入时，将调用对应的leaf_f*/
}psrTermInfo_t;



typedef struct __term_info_list_tag
{
		psrTermInfo_t		*lst;
		size_t				count;
		size_t				cap;
}psrTermInfoList_t;


void			Parser_InitTermInfoList(psrTermInfoList_t	*lst);
void			Parser_UnInitTermInfoList(psrTermInfoList_t	*lst);
void			Parser_ClearTermInfoList(psrTermInfoList_t	*lst);

arStatus_t		Parser_InsertToTermInfoList(psrTermInfoList_t	*lst, const wchar_t *name, size_t val, psrAssocType_t assoc, size_t prec, psrTermFunc_t	leaf_f);
psrTermInfo_t*	Parser_FindTermByValue(psrTermInfoList_t	*lst, size_t val);
psrTermInfo_t*	Parser_FindTermByName(psrTermInfoList_t	*lst, const wchar_t *name);

int_t			Parser_IndexOfTermInfoListByValue(const psrTermInfoList_t	*lst, size_t val);
int_t			Parser_IndexOfTermInfoListByName(const psrTermInfoList_t	*lst, const wchar_t *name);
psrTermInfo_t*	Parser_GetTermByIndex(psrTermInfoList_t	*lst, size_t index);




/***********************************************************Rule*********************************************************************/




typedef struct __parser_rule_tag
{
		const psrSymb_t			*head;
		psrSymbList_t			body;
		const	wchar_t			*prec_tok;
		psrRuleFunc_t			rule_f;
		size_t					auto_ret;

}psrRule_t;

arStatus_t		Parser_CreateRule(psrRule_t **prule, const psrSymb_t *head, const psrSymbList_t *body, const wchar_t *prec_tok, psrRuleFunc_t rule_f, size_t auto_ret, const psrTermInfoList_t *term_list, arString_t *err_msg);


/*
函数Parser_CreateRuleByStr所接受的字符格式为head : body_list
head 格式为[a-z_][a-z_0-9]*
符号 : 为分隔符，必须存在，并且被丢弃
body_list中所有符号都被当做文本符号接收，由空格，制表符等AR_iswspace返回非0值的符号分隔
*/
arStatus_t		Parser_CreateRuleByStr(psrRule_t **prule, const wchar_t *str, const wchar_t *prec, psrRuleFunc_t rule_f, size_t auto_ret, const psrTermInfoList_t *term_list, arString_t *err_msg);
void			Parser_DestroyRule(psrRule_t *rule);

/****************************************************************************************************************************************/

#define AR_PSR_MAX_SYMB_LIST	4096


struct __parser_grammar_tag
{
		psrRule_t				**rules;
		size_t					count;
		size_t					cap;
		
		psrTermInfoList_t		term_list;
		psrSymbList_t			symb_list;

		psrHandler_t			psr_handler;

		arString_t				*last_err_msg;

};


psrGrammar_t*			Parser_CreateGrammar(const psrHandler_t *ctx);
void					Parser_DestroyGrammar(psrGrammar_t *grammar);
arStatus_t				Parser_ClearGrammar(psrGrammar_t *grammar);

const wchar_t*			Parser_GetGrammarLastError(const psrGrammar_t *grammar);
void					Parser_ClearGrammarLastError(psrGrammar_t *grammar);

void					Parser_ResetGrammarParseHandler(psrGrammar_t *grammar, const psrHandler_t *io_ctx);
const psrHandler_t*		Parser_GetGrammarHandler(const psrGrammar_t *grammar);



int_t					Parser_IndexOfGrammar(const psrGrammar_t *grammar, const psrRule_t *rule);

#define					Parser_GetRuleFromGrammar(_gmr, _idx) ((_gmr)->rules[(_idx)])



const psrSymbList_t*		Parser_GetSymbList(const psrGrammar_t *grammar);/*每次运算都会重新计算符号，grammar初始化会预留足够多的空间,AR_PSR_MAX_SYMB_LIST个，超出插入失败，程序崩溃*/
const psrTermInfoList_t*	Parser_GetTermList(const psrGrammar_t *grammar);/*返回所有终结符*/

void						Parser_ResetTermSpecID(const psrGrammar_t *grammar);
int_t						Parser_GetTermSpecID(const psrGrammar_t *grammar, const psrSymb_t *symb);


const psrSymb_t*			Parser_GetSymbFromGrammarByName(const psrGrammar_t *grammar, const wchar_t *name);




const psrRule_t*		Parser_GetStartRule(const psrGrammar_t *grammar);
arStatus_t				Parser_SetStartRule(psrGrammar_t *grammar, const wchar_t *rule_name);

const psrTermInfo_t*	Parser_GetRulePrecAssocInfo(const psrGrammar_t *grammar, const psrRule_t *rule);

psrTermInfo_t*			Parser_GetTermSymbInfo(const psrGrammar_t	*grammar, const psrSymb_t *term);
psrTermInfo_t*			Parser_GetTermSymbInfoByName(const psrGrammar_t	*grammar, const wchar_t *name);
psrTermInfo_t*			Parser_GetTermSymbInfoByValue(const psrGrammar_t	*grammar, size_t val);


arStatus_t				Parser_InsertTerm(psrGrammar_t *grammar, const wchar_t *name, size_t val, psrAssocType_t assoc, size_t prec, psrTermFunc_t	leaf_f);
arStatus_t				Parser_InsertRule(psrGrammar_t *grammar, psrRule_t *rule);

arStatus_t				Parser_InsertRuleBySymbList(psrGrammar_t *grammar, const psrSymb_t *head, const psrSymbList_t *body, const wchar_t *prec_tok, psrRuleFunc_t rule_f, size_t auto_ret);

/*
函数Parser_InsertRuleByStr所接受的字符格式为head : body_list
head 格式为[a-z_][a-z_0-9]*
符号 : 为分隔符，必须存在，并且被丢弃
body_list中所有符号都被当做文本符号接收，由空格，制表符等AR_iswspace返回非0值的符号分隔
*/
arStatus_t				Parser_InsertRuleByStr(psrGrammar_t *grammar, const wchar_t *str, const wchar_t *prec, psrRuleFunc_t rule_f, size_t auto_ret);

arStatus_t				Parser_CheckIsValidGrammar(const psrGrammar_t *grammar, arIOCtx_t *io_ctx);



arStatus_t				Parser_CalcFirstSet(const psrGrammar_t *grammar, psrSymbMap_t *first_set);
arStatus_t				Parser_CalcFollowSet(const psrGrammar_t *grammar, psrSymbMap_t *follow_set, const psrSymbMap_t *first_set);


/*******************************************************************Grammar结束*******************************************************************/








/***************************************************************Parser************************************************************************/

struct __parser_tag
{
		psrModeType_t				psr_type;
		const psrGrammar_t			*grammar;
		const psrActionTable_t		*tbl;
		psrTermInfoTbl_t			*term_tbl;
		psrExpectedMsg_t			*msg_set;
		size_t						msg_count;

		size_t						ref_cnt;
};


#define PSR_REPAIR_MAX_VALID_SHIFT	3


#define PSR_MAX_STACK_CNT				4096

struct __parser_node_stack
{
		psrNode_t		*nodes[PSR_MAX_STACK_CNT];
		size_t			count;
};


struct __parser_stack_tag
{
		size_t			 states[PSR_MAX_STACK_CNT];
		size_t			 count;
};


struct __parser_context_tag
{
		const parser_t				*parser;
		bool_t						is_accepted;
		psrStack_t					state_stack;
		psrNodeStack_t				node_stack;
		void						*ctx;

		bool_t						is_repair;
		size_t						repair_valid_shift;
};



const parser_t*			Parser_CreateParser(const psrGrammar_t *grammar, psrModeType_t type);

void					Parser_DestroyParser(const parser_t *parser);

const	psrGrammar_t*	Parser_GetGrammar(const parser_t *parser);





/*****************************************Context*****************************************/

psrContext_t*	Parser_CreateContext(const parser_t *parser, void *ctx);
void			Parser_DestroyContext(psrContext_t	*ctx);


void			Parser_Clear(psrContext_t *parser);


psrNode_t*		Parser_GetResult(psrContext_t *parser);/*在状态为accepted之后才可以调用*/


bool_t			Parser_IsAccepted(const psrContext_t *parser);

bool_t			Parser_IsRecovering(const psrContext_t *parser);
void			Parser_RecoverDone(psrContext_t *parser);


size_t			Parser_GetNodeCount(const psrContext_t *parser);

psrNode_t*		Parser_IndexOfNodeStack(psrContext_t *parser, size_t index);

/*
		由于采用了一个增广的文法，所以当EOI被增加到stack中时，只可能出现错误或者成为接受状态，EOI永远不会被SHIFT到parser中
*/
arStatus_t		Parser_AddToken(psrContext_t *parser_context, const psrToken_t *tok);


/***************************************************************Parser结束************************************************************************/










/**************************************************************************报告*******************************************************************/

arStatus_t		Parser_PrintParserActionTable(const parser_t *parser, arString_t *out, size_t width);
arStatus_t		Parser_PrintParserConflict(const parser_t *parser, arString_t *out);
size_t			Parser_CountParserConflict(const parser_t *parser);


/*action table view*/

typedef struct __parser_action_item_view_tag
{
		wchar_t			**item;
		size_t			item_cnt;

		wchar_t			**action_tbl;
		size_t			row;
		size_t			col;
}psrActionView_t;

const psrActionView_t*	Parser_CreateParserActionView(const parser_t *parser);
void					Parser_DestroyParserActionView(const psrActionView_t *view);

#define	Parser_IndexActionViewItem(_v, _n)			((_v)->item[(_n)])
#define Parser_IndexActionViewAction(_v, _x,_y)	((_v)->action_tbl[AR_TBL_IDX_R((_x), (_y), (_v)->col)])

/*conflict*/
typedef struct __parser_conflict_item_tag
{
		wchar_t			*name;
		wchar_t			*lookahead;
		wchar_t			**items;
		size_t			count;
}psrConflictItem_t;

typedef struct __parser_conflict_view_tag
{
		psrConflictItem_t		**conflict;
		size_t					count;
		size_t					cap;
}psrConflictView_t;


const	psrConflictView_t*		Parser_CreateParserConflictView(const parser_t *parser);
void							Parser_DestroyParserConflictView(const psrConflictView_t *view);


/*first follow view*/
typedef struct __sym_tbl_view_tag
{
		wchar_t			**name;
		wchar_t			**name_set;
		size_t			count;
		size_t			cap;
}psrSymbolMapView_t;




typedef struct __view_info_tag
{
		psrSymbolMapView_t		first_set;
		psrSymbolMapView_t		follow_set;

		psrSymbolMapView_t		left_recursion;
		psrSymbolMapView_t		left_factor;
}psrStatusView_t;

const psrStatusView_t*			Parser_CreateParserStatusView(const parser_t *parser);
void							Parser_DestroyParserStatusView(const psrStatusView_t *view);





/**************************************************************************报告结束*******************************************************************/

AR_NAMESPACE_END




#endif
