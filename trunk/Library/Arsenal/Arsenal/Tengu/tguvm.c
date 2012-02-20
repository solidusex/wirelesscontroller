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

#include "tguvm.h"


AR_NAMESPACE_BEGIN


/************************************************************Buildin****************************************************/



const tguVMObject_t	__g_true_object = {TGU_VM_TYPE_BOOL, {true} };
const tguVMObject_t	__g_false_object = {TGU_VM_TYPE_BOOL, {false} };
const tguVMObject_t	__g_null_object = { TGU_VM_TYPE_NULL, {false }};






void	TGU_InitVM()
{

}

void	TGU_UnInitVM()
{


}



#if(0)

void TGU_FormatVMError(tguMachine_t *vm, const wchar_t *fmt,...)
{
		va_list arg_ptr;

		AR_va_start(arg_ptr, fmt);
		AR_VFormatString(vm->last_error, fmt, arg_ptr);
		AR_va_end(arg_ptr);
}



static void __set_run_env(tguMachine_t *vm,  tguVMFunc_t *func)
{
		AR_ASSERT(vm != NULL && func != NULL);
}

static bool_t	__run_vm(tguMachine_t *vm)
{
		AR_ASSERT(vm != NULL);

		return false;
}








bool_t			TGU_ExecuteVM(tguMachine_t *vm, const wchar_t *main_module)
{
		bool_t is_ok	= true;
		const wchar_t	*module_name;
		const tguVMObject_t	*val;

		tguVMModule_t	*module;
		tguVMFunc_t		*function;

		AR_ASSERT(vm != NULL);
		module_name = main_module == NULL ? TGU_DEFAULT_MODULE_NAME  : main_module;

		val = TGU_GetVMTableByCStr(vm, vm->global_table, module_name);

		if(val->type != TGU_VM_TYPE_MODULE)
		{
				TGU_FormatVMError(vm, L"Invalid Module name : %ls\r\n", module_name);
				is_ok = false;
				goto RET_POINT;
		}else
		{
				module = val->val.module;
		}

		val = TGU_GetVMTableByCStr(vm, module->table, TGU_DEFAULT_FUNCTION_NAME);

		if(val->type != TGU_VM_TYPE_FUNC)
		{
				TGU_FormatVMError(vm, L"Invalid function name : %ls\r\n", TGU_DEFAULT_FUNCTION_NAME);
				is_ok = false;
				goto RET_POINT;
		}

		function = val->val.function;

		__set_run_env(vm, function);

		is_ok = __run_vm(vm);

RET_POINT:
		return is_ok;

}



bool_t			TGU_RegisterCFuncVM(tguMachine_t *vm, const wchar_t *module_name,	 const wchar_t *func_name,  tguCFunction_t func)
{
		bool_t			is_ok = true;

		const tguVMObject_t	*val;
		tguVMObject_t	*obj;
		tguVMModule_t	*module;
		AR_ASSERT(vm != NULL && module_name != NULL && func_name && func != NULL);

		val = TGU_GetVMTableByCStr(vm, vm->global_table, module_name);

		if(val->type != TGU_VM_TYPE_MODULE)
		{
				is_ok = false;
				goto END_POINT;
		}

		module = val->val.module;
		val = TGU_GetVMTableByCStr(vm, TGU_GetVMModuleTable(module), func_name);

		if(val != &__g_null_object)
		{
				is_ok = false;
				goto END_POINT;
		}

		obj = TGU_SetVMTableByCStr(vm, TGU_GetVMModuleTable(module), func_name);

		if(obj->type != TGU_VM_TYPE_NULL)
		{
				TGU_FormatVMError(vm, L"Name %ls existed\r\n", func_name);
				is_ok = false;
				goto END_POINT;
		}

		obj->type =		TGU_VM_TYPE_C_FUNC;
		obj->val.c_function = func;

END_POINT:
		return is_ok;

}



bool_t			TGU_UnRegisterCFuncVM(tguMachine_t *vm, const wchar_t *module_name,	 const wchar_t *func_name)
{
		bool_t					is_ok = true;

		const tguVMObject_t		*val;
		tguVMModule_t			*module;
		AR_ASSERT(vm != NULL && module_name != NULL && func_name);

		val = TGU_GetVMTableByCStr(vm, vm->global_table, module_name);

		if(val->type != TGU_VM_TYPE_MODULE)
		{
				is_ok = false;
				goto END_POINT;
		}

		module = val->val.module;
		val = TGU_GetVMTableByCStr(vm, TGU_GetVMModuleTable(module), func_name);

		if(val->type != TGU_VM_TYPE_C_FUNC)
		{
				TGU_FormatVMError(vm, L"Can't found existed C function : %ls\r\n", func_name);
				is_ok = false;
				goto END_POINT;
		}

		is_ok = TGU_RemoveVMTableByCStr(vm, TGU_GetVMModuleTable(module), func_name);

END_POINT:
		return is_ok;

}



#endif






AR_NAMESPACE_END


