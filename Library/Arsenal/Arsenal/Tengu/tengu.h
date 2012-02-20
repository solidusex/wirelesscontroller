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



#ifndef __ARSENAL_TENGU_H__
#define __ARSENAL_TENGU_H__

#include "../Common/common.h"
#include "../Lex/lex.h"
#include "../Parser/parser.h"




AR_NAMESPACE_BEGIN


/*************************************************************全局资源****************************************************************************/

bool_t	TGU_Init();
bool_t	TGU_UnInit();




/***************************************************************错误报告**************************************************************************/


typedef enum
{
		TGU_REPORT_MESSAGE_T,
		TGU_REPORT_WARNING_T,
		TGU_REPORT_ERROR_T
}tguReportType_t;



typedef struct __tengu_report_info_tag
{
		tguReportType_t			type;
		
		const wchar_t			*message;
		size_t					line;
		lexToken_t				*token;	/*TGU_REPORT_ERROR_LEX_T*/
}tguReportInfo_t;



typedef void (AR_STDCALL *tguReportFunc_t)(const tguReportInfo_t *report, void *context);


typedef struct __tengu_report_tag
{
		tguReportFunc_t	report_func;
		void			*report_ctx;
}tguReport_t;



#define TGU_ReportError(_report, _msg, _line)							\
		do{																\
				tguReportInfo_t	info;									\
				info.type = TGU_REPORT_ERROR_T;							\
				info.line = (_line);									\
				info.message = (_msg);									\
				(_report)->report_func(&info, (_report)->report_ctx);	\
		}while(0)



#define TGU_ReportWarning(_report, _msg, _line)							\
		do{																\
				tguReportInfo_t	info;									\
				info.type = TGU_REPORT_WARNING_T;						\
				info.line = (_line);									\
				info.message = (_msg);									\
				(_report)->report_func(&info, (_report)->report_ctx);	\
		}while(0)








struct	__tengu_machine_tag;
typedef struct	__tengu_machine_tag		tguMachine_t;

typedef int_t	(AR_STDCALL *tguCFunction_t)(tguMachine_t *vm);








AR_NAMESPACE_END

#endif
