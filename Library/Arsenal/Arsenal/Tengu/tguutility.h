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


#ifndef __ARSENAL_TGUUTILITY_H__
#define __ARSENAL_TGUUTILITY_H__

#include "tengu.h"




AR_NAMESPACE_BEGIN


#define TGU_STRTBL_BUCKET		(512)


void	TGU_InitUtility();
void	TGU_UnInitUtility();




/*����parser������صķ��Ŷ������º������䣬�˹���Ϊ���ŶԱ��ṩ��O(1)������(ֻ��Ա�ָ��)*/

const wchar_t*	TGU_AllocString(const wchar_t *str);
const wchar_t*	TGU_AllocStringN(const wchar_t *str, size_t n);
const wchar_t*  TGU_AllocStringInt(int_64_t num, size_t radix);
const wchar_t*  TGU_AllocStringUInt(uint_64_t num, size_t radix);
const wchar_t*  TGU_AllocStringFloat(double num);
bool_t			TGU_HasString(const wchar_t *name);



/******************************************************����Դ���ı��ļ�**************************************/
typedef struct __tengu_sources_tag
{
		const	wchar_t			*path;
		const	wchar_t			*module_name;
		const	wchar_t			*code;
}tguSrc_t;

tguSrc_t*		TGU_LoadSources(const wchar_t *work_dir, const wchar_t *file_name);
void			TGU_ReleaseSources(tguSrc_t		*src);


AR_NAMESPACE_END



#endif
