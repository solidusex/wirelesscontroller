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


#ifndef __ARSENAL_TGUVM_H__
#define __ARSENAL_TGUVM_H__

#include "tengu.h"
#include "tgusyntree.h"



AR_NAMESPACE_BEGIN


void	TGU_InitVM();
void	TGU_UnInitVM();


/*************************************************************************************************************************************/
struct	__insctruction_tag;
typedef struct	__insctruction_tag		tguVMIns_t;



/******************************************************Object***********************************************************************/




typedef int_64_t								tguVMInteger_t;

typedef	double									tguVMFloat_t;

typedef	bool_t									tguVMBoolean_t;


struct __tengu_vm_string_tag;
typedef struct __tengu_vm_string_tag			tguVMString_t;

struct __tengu_vm_binary_tag;
typedef struct __tengu_vm_binary_tag			tguVMBinary_t;

struct __tengu_vm_userdata_tag;
typedef struct __tengu_vm_userdata_tag			tguVMUserData_t;



struct __tengu_vm_list_tag;
typedef struct __tengu_vm_list_tag				tguVMList_t;


struct __tengu_vm_table_tag;
typedef struct __tengu_vm_table_tag				tguVMTable_t;



struct __tengu_vm_function_tag;
typedef	struct __tengu_vm_function_tag			tguVMFunc_t;

struct __tengu_vm_module_tag;
typedef struct __tengu_vm_module_tag			tguVMModule_t;



typedef union __tengu_value_tag
{
		tguVMBoolean_t		boolean;

		tguVMInteger_t		integer_num;
		tguVMFloat_t		float_num;

		/*GC Object*/
		tguVMString_t		*str;
		tguVMUserData_t		*userdata;
		tguVMBinary_t		*binary;

		tguVMList_t			*list;
		tguVMTable_t		*table;
		
		tguVMFunc_t			*function;
		tguVMModule_t		*module;
		
		tguCFunction_t		c_function;
}tguVMValue_t;






enum
{
		TGU_VM_TYPE_NULL,
		TGU_VM_TYPE_BOOL,
		TGU_VM_TYPE_INTEGER,
		TGU_VM_TYPE_FLOAT,

		TGU_VM_TYPE_STRING,
		TGU_VM_TYPE_USERDATA,
		TGU_VM_TYPE_BINARY,

		TGU_VM_TYPE_LIST,
		TGU_VM_TYPE_TABLE,
		
		TGU_VM_TYPE_FUNC,
		TGU_VM_TYPE_MODULE,

		TGU_VM_TYPE_C_FUNC
	
};



typedef struct __tgu_object_tag
{
		uint_8_t		type;
		tguVMValue_t	val;
}tguVMObject_t;



extern const tguVMObject_t	__g_true_object;
extern const tguVMObject_t	__g_false_object;
extern const tguVMObject_t	__g_null_object;



/*****************************************************Object definition***********************************************************************/

typedef enum 
{
		TGU_MEM_UNMARK,
		TGU_MEM_MARKED,
		TGU_MEM_FIXED
}tguMemMark_t;




struct __tengu_vm_string_tag
{
		tguMemMark_t			mark;
		tguVMString_t			*gc_next;
		tguVMString_t			*hash_next;


		wchar_t					*str;
		size_t					n;
		uint_t					hash;
};


tguVMString_t*	TGU_CreateVMString(tguMachine_t *vm, const wchar_t *str);
tguVMString_t*	TGU_CreateVMStringN(tguMachine_t *vm, const wchar_t *str, size_t n);

void			TGU_DestroyVMString(tguMachine_t *vm, tguVMString_t		*str);


struct __tengu_vm_userdata_tag
{
		tguMemMark_t			mark;
		tguVMUserData_t			*next;

		void					*data;
		int_t					tag;
};



tguVMUserData_t*	TGU_CreateVMUserData(tguMachine_t *vm, void *user_data, int_t tag);
void				TGU_DestroyVMUserData(tguMachine_t *vm, tguVMUserData_t *data);



struct __tengu_vm_binary_tag
{
		tguMemMark_t			mark;
		tguVMBinary_t			*next;
		
		arBuffer_t				*buf;
};


tguVMBinary_t*	TGU_CreateVMBinary(tguMachine_t *vm);
void			TGU_DestroyVMBinary(tguMachine_t *vm, tguVMBinary_t *binary);




struct __tengu_vm_list_tag
{
		tguMemMark_t		mark;
		tguVMList_t			*next;


		tguVMObject_t	**lst;
		size_t			cnt;
		size_t			cap;
		
};


tguVMList_t*			TGU_CreateVMList(tguMachine_t *vm, size_t nsize);
void					TGU_DestroyVMList(tguMachine_t *vm, tguVMList_t *lst);

bool_t					TGU_SetVMList(tguMachine_t *vm, tguVMList_t *lst, size_t idx, tguVMObject_t *obj);
const tguVMObject_t*	TGU_GetVMList(tguMachine_t *vm, tguVMList_t *lst, size_t idx);
size_t					TGU_AppendVMList(tguMachine_t *vm, tguVMList_t *lst, tguVMObject_t *obj);
bool_t					TGU_RemoveVMList(tguMachine_t *vm, tguVMList_t *lst, size_t idx);

int_t					TGU_FindVMList(tguVMList_t	 *lst, tguVMObject_t *obj);
size_t					TGU_GetVMListSize(tguVMList_t	 *lst);




typedef struct __tengu_vm_table_node_tag
{
		tguVMObject_t *key;
		tguVMObject_t *val;
		
		struct __tengu_vm_table_node_tag		*next;
}tguVMTableNode_t;


struct __tengu_vm_table_tag
{
		tguMemMark_t	mark;
		tguVMTable_t	*next;

		tguVMTableNode_t		**bucket;
		size_t					bucket_cnt;
		size_t					item_cnt;
};


tguVMTable_t*			TGU_CreateVMTable(tguMachine_t *vm,		size_t estimate_cnt);
void					TGU_DestroyVMTable(tguMachine_t *vm, tguVMTable_t *tbl);

const tguVMObject_t*	TGU_GetVMTable(tguMachine_t *vm,	tguVMTable_t *tbl,			tguVMObject_t *key);
tguVMObject_t*			TGU_SetVMTable(tguMachine_t *vm,	tguVMTable_t *tbl,			tguVMObject_t *key);
bool_t					TGU_RemoveVMTable(tguMachine_t *vm, tguVMTable_t *tbl,			tguVMObject_t *key);




const tguVMObject_t*	TGU_GetVMTableByBool(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMBoolean_t		key);
const tguVMObject_t*	TGU_GetVMTableByInt(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMInteger_t		key);
const tguVMObject_t*	TGU_GetVMTableByFloat(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMFloat_t		key);
const tguVMObject_t*	TGU_GetVMTableByString(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMString_t		*key);
const tguVMObject_t*	TGU_GetVMTableByCStr(tguMachine_t *vm, tguVMTable_t *tbl,		const wchar_t		*key);




tguVMObject_t*			TGU_SetVMTableByBool(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMBoolean_t		key);
tguVMObject_t*			TGU_SetVMTableByInt(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMInteger_t		key);
tguVMObject_t*			TGU_SetVMTableByFloat(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMFloat_t		key);
tguVMObject_t*			TGU_SetVMTableByString(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMString_t		*key);
tguVMObject_t*			TGU_SetVMTableByCStr(tguMachine_t *vm, tguVMTable_t *tbl,		const wchar_t		*key);


bool_t					TGU_RemoveVMTableByBool(tguMachine_t *vm, tguVMTable_t *tbl,	tguVMBoolean_t		key);
bool_t					TGU_RemoveVMTableByInt(tguMachine_t *vm, tguVMTable_t *tbl,		tguVMInteger_t		key);
bool_t					TGU_RemoveVMTableByFloat(tguMachine_t *vm, tguVMTable_t *tbl,	tguVMFloat_t		key);
bool_t					TGU_RemoveVMTableByString(tguMachine_t *vm, tguVMTable_t *tbl,	tguVMString_t		*key);
bool_t					TGU_RemoveVMTableByCStr(tguMachine_t *vm, tguVMTable_t *tbl,	const wchar_t		*key);





typedef struct __local_var_tag
{
		tguVMString_t	*name;
		size_t			line;
}tguVMLocalVar_t;

struct __tengu_vm_function_tag	
{
		tguMemMark_t			mark;
		tguVMFunc_t				*next;

		bool_t					is_veriadic;
		size_t					param_cnt;
		
		tguVMIns_t				*code;
		size_t					code_size;

		tguVMLocalVar_t			*locvar;
		size_t					loc_cnt;
		size_t					loc_cap;
};



tguVMFunc_t*		TGU_CreateVMFunc(tguMachine_t *vm, tguVMString_t *module_name);
void				TGU_DestroyVMFunc(tguMachine_t *vm, tguVMFunc_t *func);






struct  __tengu_vm_module_tag
{
		tguMemMark_t	mark;
		tguVMModule_t	*next;
		
		tguVMTable_t	*table;

		size_t			ref_cnt;
};



tguVMModule_t*			TGU_CreateVMModule(tguMachine_t *vm, tguVMString_t *module_name);
void					TGU_DestroyVMModule(tguMachine_t *vm, tguVMModule_t *module);


#define					TGU_GetVMModuleTable(_m)		((_m)->table)




/***********************************************************************************************************************************/


typedef struct __tengu_vm_gc_pool_tag
{
		tguVMString_t		*str_root;
		tguVMFunc_t			*function_root;
		tguVMBinary_t		*binary_root;
		tguVMUserData_t		*userdata_root;

		tguVMList_t			*list_root;
		tguVMTable_t		*table_root;
		
		tguVMModule_t		*module_root;
}tguVMGCPool_t;


void	TGU_InitVMGCPool(tguMachine_t *vm, tguVMGCPool_t *pool);
void	TGU_UnInitVMGCPool(tguMachine_t *vm, tguVMGCPool_t *pool);



typedef struct __tengu_vm_constant_pool_tag
{
		tguVMInteger_t		*integer_set;
		size_t				int_cnt;
		size_t				int_cap;
		
		tguVMFloat_t		*float_set;
		size_t				float_cnt;
		size_t				float_cap;

		wchar_t				**str_set;
		size_t				str_cnt;
		size_t				str_cap;
}tguVMConstPool_t;



void	TGU_InitVMConstantPool(tguMachine_t *vm, tguVMConstPool_t *pool);
void	TGU_UnInitVMConstantPool(tguMachine_t *vm, tguVMConstPool_t *pool);


/*
以下三个函数在tguVMConstPool_t搜索，如果存在参数，则返回相关索引，否则将参数插入，并返回索引
*/

size_t	TGU_GetIntegerConstant(tguMachine_t *vm,		tguVMConstPool_t *pool,		tguVMInteger_t num);
size_t	TGU_GetFloatConstant(tguMachine_t *vm,			tguVMConstPool_t *pool,		tguVMFloat_t num);
size_t	TGU_GetStringConstant(tguMachine_t *vm,			tguVMConstPool_t *pool,		const wchar_t *str);



/*************************************************************************************************************************************/




/******************************************************OpCode***********************************************************************/



typedef enum 
{
		TGU_VM_OP_PUSH				,			/*根据arg1决定压入什么, arg2意思取决于arg1*/
		TGU_VM_OP_POP				,			/*arg2为调整数量*/

		TGU_VM_OP_GET				,			/*arg1决定类型，arg2取决于arg1*/
		TGU_VM_OP_SET				,			/*同上*/


		TGU_VM_OP_EQ				,
		TGU_VM_OP_LT				,
		TGU_VM_OP_LE				,
		TGU_VM_OP_GT				,
		TGU_VM_OP_GE				,
		TGU_VM_OP_ADD				,
		TGU_VM_OP_SUB				,
		TGU_VM_OP_MUL				,
		TGU_VM_OP_DIV				,
		TGU_VM_OP_MOD				,
		
		TGU_VM_OP_UMINUS			,
		TGU_VM_OP_NOT				,
		
		TGU_VM_OP_JMP				,
		TGU_VM_OP_TEST				,
		TGU_VM_OP_TESTTEST			,

		TGU_VM_OP_CALL				,
		TGU_VM_OP_RETURN			,
		
		TGU_VM_OP_NOP
}tguVMOpCode_t;




struct	__insctruction_tag
{
		uint_8_t		op;
		uint_8_t		arg1;
		int_16_t		arg2;
};



#define TGU_OP_MIN_ARG2			AR_INT16_MIN
#define TGU_OP_MAX_ARG2			AR_INT16_MAX







typedef tguVMObject_t		tguStackID_t;


typedef struct __call_info_tag
{
		tguVMIns_t		*pc;		
		tguStackID_t	*fp;
		tguStackID_t	*sp;
}tguCallInfo_t;

#define	TGU_MAX_CALL			512


typedef struct __tengu_call_stack_tag
{
		tguStackID_t	*start;
		tguStackID_t	*last;
		tguStackID_t	*sp;	/*last used slot*/
		tguVMFunc_t		*func;
}tguCallStack_t;

#define	TGU_STACK_SIZE(_stk)	((size_t) ( (_stk)->top - (_stk)->start + 1) )

#define	TGU_MAX_STACK_SIZE		8192










struct	__tengu_machine_tag
{
/***************************Run************************/
		tguVMIns_t		*pc;
		tguStackID_t	*fp;
		tguStackID_t	*sp;
		tguVMFunc_t		*curr_func;
		
		
		tguCallStack_t	stack;
		tguCallInfo_t	ci[TGU_MAX_CALL];
		size_t			call_cnt;
		


		
		tguVMGCPool_t			gc_pool;
		tguVMConstPool_t		const_pool;

/************************Value***********************/
		tguVMTable_t		*global_table;

		arString_t			*last_error;


};


typedef struct __tengu_vm_init_tag
{
		const tguReportInfo_t *report;
}tguVMInit_t;

tguMachine_t*	TGU_CreateVM(const tguVMInit_t *init);
void			TGU_DestroyVM(tguMachine_t	*vm);
void			TGU_FormatVMError(tguMachine_t *vm, const wchar_t *fmt,...);

void			TGU_CollectGarbageVM(tguMachine_t	*vm);





#define			TGU_DEFAULT_MODULE_NAME			L"@module"
#define			TGU_DEFAULT_FUNCTION_NAME		L"@main"

bool_t			TGU_ExecuteVM(tguMachine_t *vm, const wchar_t *main_module);


tguVMModule_t*	TGU_GetModuleVM(tguMachine_t *vm, const wchar_t *module_name);


bool_t			TGU_RegisterModuleVM(tguMachine_t *vm, const wchar_t *module_name, const wchar_t *sources);
bool_t			TGU_RegisterModuleVMFromFile(tguMachine_t *vm, const wchar_t *module_name, const wchar_t *path);









AR_NAMESPACE_END

#endif
