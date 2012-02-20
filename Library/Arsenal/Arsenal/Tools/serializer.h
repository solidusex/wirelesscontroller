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

#ifndef __ARSENAL_SERIALIZATION_H__
#define __ARSENAL_SERIALIZATION_H__

#include "../Common/common.h"

AR_NAMESPACE_BEGIN


typedef enum
{
		SN_INT_T,
		SN_STRING_T,
		SN_LIST_T,
		SN_DICT_T
}snType_t;


struct __serialize_object_tag;
typedef	struct __serialize_object_tag	snObject_t;





typedef struct __serializer_return_value_tag
{
		arStatus_t		status;
		snObject_t		*obj;
}snRetVal_t;


snObject_t*		SN_CreateObject(snType_t		type);
void			SN_DestroyObject(snObject_t		*obj);
snType_t		SN_GetObjectType(const snObject_t *obj);


/*******************************Dict***********************************************************/

typedef struct __sn_dict_pair_tag
{
		snObject_t		*key;
		snObject_t		*val;
}snPair_t;


arStatus_t			SN_InsertToDictObject(snObject_t *obj, snObject_t *key, snObject_t *value);
arStatus_t			SN_RemoveFromDictObject(snObject_t *obj, const snObject_t *key);
snObject_t*			SN_FindFromDictObject(snObject_t *obj, const snObject_t *key);
size_t				SN_GetDictObjectCount(const snObject_t *obj);
snPair_t*			SN_GetFromDictObject(snObject_t *obj, size_t idx);


/*******************************List***********************************************************/
arStatus_t		SN_InsertToListObject(snObject_t	*lst, snObject_t *obj);
arStatus_t		SN_RemoveFromListObject(snObject_t	*lst, size_t idx);
int_t			SN_IndexOfListObject(const snObject_t *lst, const snObject_t *obj);
snObject_t*		SN_GetFromListObject(snObject_t *lst, size_t idx);
size_t			SN_GetListObjectCount(const snObject_t *lst);

/*******************************String***********************************************************/
arStatus_t		SN_SetStringObjectByData(snObject_t	*dest, const byte_t *data, size_t len);
arStatus_t		SN_SetStringObjectByStr(snObject_t	*dest, const char *str);
arStatus_t		SN_SetStringObjectByWcs(snObject_t	*dest, const wchar_t *str);

int_t			SN_GetWcsFromStringObject(const snObject_t	*obj, wchar_t *buf, size_t len);
int_t			SN_GetStrFromStringObject(const snObject_t	*obj, char *buf, size_t len);
int_t			SN_GetDataFromStringObject(const snObject_t	*obj, byte_t *buf, size_t len);



arStatus_t			SN_CompStringObjectByStringObject(const snObject_t		*l,		const snObject_t		*r);
arStatus_t			SN_CompStringObjectByData(const snObject_t				*l,		const byte_t *data,		size_t len);
arStatus_t			SN_CompStringObjectByStr(const snObject_t				*l,		const char *str);
arStatus_t			SN_CompStringObjectByWcs(const snObject_t				*l,		const wchar_t *str);


/*******************************Int***********************************************************/

int_64_t		SN_GetIntObject(const snObject_t	*obj);
uint_64_t		SN_GetUIntObject(const snObject_t	*obj);
void			SN_SetUIntObject(snObject_t	*obj,	uint_64_t num);
void			SN_SetIntObject(snObject_t	*obj,	int_64_t num);



/************************************Util****************************************************/

snRetVal_t		SN_GetObject(arBuffer_t	*buffer);
arStatus_t		SN_PutObject(arBuffer_t	*buffer, const snObject_t *obj);


snRetVal_t		SN_FindObjectByWcsPath(snObject_t *obj, const wchar_t *path);
snRetVal_t		SN_FindObjectByStrPath(snObject_t *obj, const char *path);


AR_NAMESPACE_END


#endif

