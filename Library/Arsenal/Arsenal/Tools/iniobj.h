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

#ifndef __ARSENAL_INIOBJ_H__
#define __ARSENAL_INIOBJ_H__

#include "../Common/common.h"

AR_NAMESPACE_BEGIN

struct __ini_object_tag;
typedef struct __ini_object_tag iniObject_t;

#define			INI_EMPTY_SECTION_NAME	L"[[__empty_header__]]"


iniObject_t*	Ini_CreateObject();
void			Ini_DestroyObject(iniObject_t *obj);
void			Ini_ClearObject(iniObject_t *obj);

arStatus_t		Ini_LoadObjectFromString(iniObject_t *obj, const wchar_t *ini_data);
arStatus_t		Ini_SaveObjectToString(const iniObject_t *obj, arString_t *out);


arStatus_t		Ini_SectionIsExisted(const iniObject_t *obj, const wchar_t *sect);
arStatus_t		Ini_InsertSection(iniObject_t *obj, const wchar_t *sect, const wchar_t *comment);
arStatus_t		Ini_RemoveSection(iniObject_t *obj, const wchar_t *sect);

const wchar_t*	Ini_GetString(const iniObject_t *obj, const wchar_t *sect, const wchar_t *key);
arStatus_t		Ini_SetString(iniObject_t *obj, const wchar_t *sect, const wchar_t *key, const wchar_t *val, const wchar_t *comment);

arStatus_t		Ini_RemoveKey(iniObject_t *obj, const wchar_t *sect, const wchar_t *key);
arStatus_t		Ini_SetComment(iniObject_t *obj, const wchar_t *sect, const wchar_t *key, const wchar_t *comment);
const wchar_t*	Ini_GetComment(const iniObject_t *obj, const wchar_t *sect, const wchar_t *key);





int_64_t		Ini_GetInt(const iniObject_t *obj, const wchar_t *sect, const wchar_t *key, int_64_t default_data);
uint_64_t		Ini_GetUInt(const iniObject_t *obj, const wchar_t *sect, const wchar_t *key, uint_64_t default_data);
double			Ini_GetFloat(const iniObject_t *obj, const wchar_t *sect, const wchar_t *key, double default_data);



arStatus_t			Ini_SetInt(iniObject_t *obj, const wchar_t *sect, const wchar_t *key, int_64_t val, const wchar_t *comment);
arStatus_t			Ini_SetUInt(iniObject_t *obj, const wchar_t *sect, const wchar_t *key, uint_64_t val, const wchar_t *comment);
arStatus_t			Ini_SetFloat(iniObject_t *obj, const wchar_t *sect, const wchar_t *key, double val, const wchar_t *comment);



AR_NAMESPACE_END


#endif

