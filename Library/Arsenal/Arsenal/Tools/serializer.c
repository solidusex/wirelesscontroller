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

#include "serializer.h"



AR_NAMESPACE_BEGIN

/***************************************Declaration*************************************************/

typedef struct __sn_int_tag
{
		bool_t	is_signed;
		union{
				uint_64_t		u;
				int_64_t		s;
		};
}snInteger_t;


static void	SN_InitInteger(snInteger_t *dest);
static void	SN_UnInitInteger(snInteger_t *dest);


typedef struct __sn_float_tag
{
		double			num;
}snFloat_t;

static void	SN_InitFloat(snFloat_t *dest);
static void	SN_UnInitFloat(snFloat_t *dest);


typedef struct __sn_string_tag
{
		byte_t	*data;
		size_t	len;
}snString_t;

static void	SN_InitString(snString_t	*str);
static void	SN_UnInitString(snString_t	*dest);

static arStatus_t	SN_SetStringByData(snString_t	*dest, const byte_t *data, size_t len);
static arStatus_t	SN_SetStringByStr(snString_t	*dest, const char *str);
static arStatus_t	SN_SetStringByWcs(snString_t	*dest, const wchar_t *str);


static arStatus_t	SN_CompStringByString(const snString_t	*l,  const snString_t	*r);
static arStatus_t	SN_CompStringByData(const snString_t	*l,  const byte_t *data, size_t len);
static arStatus_t	SN_CompStringByStr(const snString_t		*l,	 const char *str);
static arStatus_t	SN_CompStringByWcs(const snString_t		*l,	 const wchar_t *str);



typedef struct __sn_list_tag
{
		snObject_t		**lst;
		size_t			count;
		size_t			cap;
}snList_t;

static void			SN_InitList(snList_t	*lst);
static void			SN_UnInitList(snList_t	*lst);

static arStatus_t		SN_InsertToList(snList_t	*lst, snObject_t *obj);
static arStatus_t		SN_RemoveFromList(snList_t	*lst, size_t idx);
static int_t			SN_IndexOfList(const snList_t *lst, const snObject_t *obj);
static snObject_t*		SN_GetFromList(snList_t *lst, size_t idx);



typedef struct __sn_dict_tag
{
		snPair_t		*pairs;		
		size_t			count;
		size_t			cap;
}snDict_t;

static void				SN_InitDict(snDict_t *dict);
static void				SN_UnInitDict(snDict_t *dict);
static arStatus_t		SN_InsertToDict(snDict_t *dict, snObject_t *key, snObject_t *value);
static arStatus_t		SN_RemoveFromDict(snDict_t *dict, const snObject_t *key);
static snObject_t*		SN_FindFromDict(snDict_t *dict, const snObject_t *key);








struct __serialize_object_tag
{
		snType_t		type;
		union{
				snInteger_t		integer;
				snFloat_t		float_num;
				snString_t		string;
				snList_t		list;
				snDict_t		dict;
		};
};





/*int*/



static void	SN_InitInteger(snInteger_t *dest)
{
		AR_ASSERT(dest != NULL);
		AR_memset(dest, 0, sizeof(*dest));
}

static void	SN_UnInitInteger(snInteger_t *dest)
{
		AR_ASSERT(dest != NULL);
		AR_memset(dest, 0, sizeof(*dest));
}


/*float*/

static void	SN_InitFloat(snFloat_t *dest)
{
		AR_ASSERT(dest != NULL);
		AR_memset(dest, 0, sizeof(*dest));
}

static void	SN_UnInitFloat(snFloat_t *dest)
{
		AR_ASSERT(dest != NULL);
		AR_memset(dest, 0, sizeof(*dest));
}



/*string*/
static void	SN_InitString(snString_t	*str)
{
		AR_ASSERT(str != NULL);
		AR_memset(str, 0, sizeof(*str));
}

static void	SN_UnInitString(snString_t	*str)
{
		if(str->data != NULL)
		{
				AR_DEL(str->data);
		}
		AR_memset(str, 0, sizeof(*str));
}


static arStatus_t	SN_SetStringByData(snString_t	*dest, const byte_t *data, size_t len)
{
		byte_t *tmp_data;
		AR_ASSERT(dest != NULL && data != NULL && len > 0);

		tmp_data = AR_NEWARR(byte_t, len);

		if(tmp_data == NULL)
		{
				return AR_E_NOMEM;
		}

		if(dest->data != NULL)
		{
				AR_DEL(dest->data);
				dest->data = NULL;
		}

		dest->data = tmp_data;
		AR_memcpy(dest->data, data, len);
		dest->len = len;
		return AR_S_YES;
}

static arStatus_t	SN_SetStringByStr(snString_t	*dest, const char *str)
{
		size_t	l;
		AR_ASSERT(dest != NULL && str != NULL);
		l = AR_strlen(str);

		if(l == 0)
		{
				return AR_E_INVAL;
		}
		return SN_SetStringByData(dest, (const byte_t*)str, l);
}

static arStatus_t	SN_SetStringByWcs(snString_t	*dest, const wchar_t *str)
{
		const char *utf8;
		AR_ASSERT(dest != NULL && str != NULL);
		utf8 = AR_wcs_convto_str(AR_CP_UTF8, str, AR_wcslen(str));

		if(utf8 == NULL)
		{
				return AR_E_NOMEM;
		}

		SN_SetStringByStr(dest, utf8);
		AR_DEL(utf8);
		return AR_S_YES;
}



static arStatus_t	SN_CompStringByString(const snString_t	*l,  const snString_t	*r)
{
		AR_ASSERT(l != NULL && r != NULL && l->len > 0 && r->len > 0 && l->data != NULL && r->data != NULL);
		
		if(l->len < r->len)
		{
				return AR_S_LE;
		}else if(l->len > r->len)
		{
				return AR_S_GE;
		}else
		{
				int cmp =  AR_memcmp(l->data, r->data, l->len);

				if(cmp > 0)
				{
						return AR_S_GE;
				}else if(cmp < 0)
				{
						return AR_S_LE;
				}else
				{
						return AR_S_EQ;
				}
		}
}



static arStatus_t	SN_CompStringByData(const snString_t	*l,  const byte_t *data, size_t len)
{
		arStatus_t status;
		snString_t		other;
		
		AR_ASSERT(l != NULL && l->len > 0 && data != NULL && len > 0);

		SN_InitString(&other);

		status = SN_SetStringByData(&other, data, len);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}

		status = SN_CompStringByString(l, &other);

END_POINT:
		SN_UnInitString(&other);
		return status;
}

static arStatus_t	SN_CompStringByStr(const snString_t		*l,	 const char *str)
{
		snString_t		other;
		arStatus_t		status;
		AR_ASSERT(l != NULL && l->len > 0 && str != NULL);

		SN_InitString(&other);

		status = SN_SetStringByStr(&other, str);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}

		status = SN_CompStringByString(l, &other);

END_POINT:
		SN_UnInitString(&other);
		return status;
}

static arStatus_t	SN_CompStringByWcs(const snString_t		*l,	 const wchar_t *str)
{
		snString_t		other;
		arStatus_t		status;
		AR_ASSERT(l != NULL && l->len > 0 && str != NULL);

		SN_InitString(&other);
		
		status = SN_SetStringByWcs(&other, str);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}

		status = SN_CompStringByString(l, &other);

END_POINT:
		SN_UnInitString(&other);
		return status;
}


/*list*/

static void	SN_InitList(snList_t	*lst)
{
		AR_ASSERT(lst != NULL);
		AR_memset(lst, 0, sizeof(*lst));
}

static void	SN_UnInitList(snList_t	*lst)
{
		size_t i;
		AR_ASSERT(lst != NULL);

		for(i = 0; i < lst->count; ++i)
		{
				SN_DestroyObject(lst->lst[i]);
		}

		if(lst->lst)
		{
				AR_DEL(lst->lst);
				lst->lst = NULL;
		}

		AR_memset(lst, 0, sizeof(*lst));
}


static arStatus_t	SN_InsertToList(snList_t	*lst, snObject_t *obj)
{
		AR_ASSERT(lst != NULL && obj != NULL);

		if(lst->count == lst->cap)
		{
				size_t new_cap;
				snObject_t **new_lst;

				new_cap = (lst->cap + 4) * 2;
				new_lst = AR_NEWARR(snObject_t*, new_cap);

				if(new_lst == NULL)
				{
						return AR_E_NOMEM;
				}

				if(lst->count > 0)
				{
						AR_memcpy(new_lst, lst->lst, lst->count * sizeof(snObject_t*));
				}

				if(lst->lst)
				{
						AR_DEL(lst->lst);
						lst->lst = NULL;
				}
				lst->cap = new_cap;
				lst->lst = new_lst;

		}
		
		lst->lst[lst->count++] = obj;
		return AR_S_YES;
}




static arStatus_t	SN_RemoveFromList(snList_t	*lst, size_t idx)
{
		
		AR_ASSERT(lst != NULL);
		if(idx >= lst->count)
		{
				return AR_S_NO;
		}
		SN_DestroyObject(lst->lst[idx]);
		lst->lst[idx] = lst->lst[lst->count-1];
		lst->count--;
		return AR_S_YES;
}


static int_t	SN_IndexOfList(const snList_t *lst, const snObject_t *obj)
{
		int_t i;
		AR_ASSERT(lst != NULL && obj != NULL);

		for(i = 0; i < (int_t)lst->count; ++i)
		{
				if(obj == lst->lst[i])return i;
		}
		return -1;
}


static snObject_t*		SN_GetFromList(snList_t *lst, size_t idx)
{
		AR_ASSERT(lst != NULL);
		if(idx >= lst->count)
		{
				return NULL;
		}

		return lst->lst[idx];
}






/*dict*/
static void	SN_InitDict(snDict_t *dict)
{
		AR_ASSERT(dict != NULL);
		AR_memset(dict, 0, sizeof(*dict));
}

static void	SN_UnInitDict(snDict_t *dict)
{
		size_t i;
		AR_ASSERT(dict != NULL);
		for(i = 0; i < dict->count; ++i)
		{
				SN_DestroyObject(dict->pairs[i].key);
				SN_DestroyObject(dict->pairs[i].val);
		}
		
		if(dict->pairs)AR_DEL(dict->pairs);
		AR_memset(dict, 0, sizeof(*dict));
}


static arStatus_t	SN_InsertToDict(snDict_t *dict, snObject_t *key, snObject_t *value)
{
		size_t i;
		AR_ASSERT(dict != NULL && key != NULL && key->type == SN_STRING_T && value != NULL);

		for(i = 0; i < dict->count; ++i)
		{
				if(SN_CompStringByString(&key->string, &(dict->pairs[i].key->string)) == AR_S_EQ)
				{
						break;
				}
		}

		if(i < dict->count)
		{

				SN_DestroyObject(dict->pairs[i].key);

				if(dict->pairs[i].val)
				{
						SN_DestroyObject(dict->pairs[i].val);
				}
				
				dict->pairs[i].key = key;
				dict->pairs[i].val = value;
				return AR_S_YES;
		}else
		{
				if(dict->count == dict->cap)
				{
						size_t			new_cap;
						snPair_t		*new_pairs;

						new_cap = (dict->cap + 4) * 2;
						new_pairs = AR_NEWARR(snPair_t, new_cap);

						if(new_pairs == NULL)
						{
								return AR_E_NOMEM;
						}

						if(dict->count > 0)
						{
								AR_memcpy(new_pairs, dict->pairs, sizeof(dict->count) * sizeof(snPair_t));
						}

						if(dict->pairs)
						{
								AR_DEL(dict->pairs);
								dict->pairs = NULL;
						}

						dict->cap = new_cap;
						dict->pairs = new_pairs;
				}		

				dict->pairs[dict->count].key = key;
				dict->pairs[dict->count].val = value;
				dict->count++;
				return AR_S_YES;
		}
}

static arStatus_t	SN_RemoveFromDict(snDict_t *dict, const snObject_t *key)
{
		size_t i;
		AR_ASSERT(dict != NULL && key != NULL && key->type == SN_STRING_T);

		for(i = 0; i < dict->count; ++i)
		{
				if(SN_CompStringByString(&key->string, &(dict->pairs[i].key->string)) == AR_S_EQ)
				{
						break;
				}
		}

		if(i == dict->count)
		{
				return AR_S_NO;
		}

		SN_DestroyObject(dict->pairs[i].key);
		SN_DestroyObject(dict->pairs[i].val);

		dict->pairs[i] = dict->pairs[dict->count-1];
		dict->count--;
		return AR_S_YES;
		
}

static snObject_t* SN_FindFromDict(snDict_t *dict, const snObject_t *key)
{
		size_t i;
		AR_ASSERT(dict != NULL && key != NULL && key->type == SN_STRING_T);

		for(i = 0; i < dict->count; ++i)
		{
				if(SN_CompStringByString(&key->string, &(dict->pairs[i].key->string)) == AR_S_EQ)
				{
						return dict->pairs[i].val;
				}
		}
		return NULL;
}







/*********************************************Object**************************************************************/



snObject_t*		SN_CreateObject(snType_t		type)
{
		snObject_t		*obj;
		obj = AR_NEW0(snObject_t);

		if(obj == NULL)
		{
				return NULL;
		}

		obj->type = type;
		switch(type)
		{
		default:
		{
				AR_ASSERT(false);		
				break;
		}
		case SN_INT_T:
		{
				SN_InitInteger(&obj->integer);
				break;
		}
		case SN_FLOAT_T:
		{
				SN_InitFloat(&obj->float_num);
				break;
		}
		case SN_STRING_T:
		{
				SN_InitString(&obj->string);
				break;
		}
		case SN_LIST_T:
		{
				SN_InitList(&obj->list);
				break;
		}
		case SN_DICT_T:
		{
				SN_InitDict(&obj->dict);
				break;
		}
		}
		return obj;
}


void			SN_DestroyObject(snObject_t		*obj)
{
		AR_ASSERT(obj != NULL);

		switch(obj->type)
		{
		default:
		{
				AR_ASSERT(false);		
				break;
		}
		case SN_INT_T:
		{
				SN_UnInitInteger(&obj->integer);
				break;
		}
		case SN_FLOAT_T:
		{
				SN_UnInitFloat(&obj->float_num);
				break;
		}
		case SN_STRING_T:
		{
				SN_UnInitString(&obj->string);
				break;
		}
		case SN_LIST_T:
		{
				SN_UnInitList(&obj->list);
				break;
		}
		case SN_DICT_T:
		{
				SN_UnInitDict(&obj->dict);
				break;
		}
		}

		AR_DEL(obj);
}

snType_t		SN_GetObjectType(const snObject_t *obj)
{
		AR_ASSERT(obj != NULL);
		return obj->type;
}



static snRetVal_t	__get_int(arBuffer_t	*buffer)
{
		size_t	buf_len, idx;
		const byte_t	*pbuf;
		
		uint_64_t		num = 0;
		bool_t			is_neg = false;

		snRetVal_t		ret = {AR_S_YES, NULL};
		AR_ASSERT(buffer != NULL);

		buf_len = AR_GetBufferAvailable(buffer);
		pbuf	= AR_GetBufferData(buffer);
		
		if(pbuf == NULL)
		{
				ret.status = AR_E_INVAL;
				return ret;
		}

		idx = 0;
		if(pbuf[0] == '-')
		{
				is_neg = true;
				idx = 1;
		}
		
		while(idx < buf_len && AR_isdigit(pbuf[idx]))
		{
				num *= 10;
				num += (pbuf[idx] - '0');
				idx++;
		}
		
		if(idx == buf_len)
		{
				ret.status = AR_E_INVAL;
				return ret;
		}

		if(pbuf[idx] != 'e')
		{
				ret.status = AR_E_INVAL;
				return ret;
		}

		ret.obj = SN_CreateObject(SN_INT_T);

		if(ret.obj == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}

		ret.obj->integer.is_signed = is_neg;

		if(is_neg)
		{
				ret.obj->integer.s = 0 - (int_64_t)num;
		}else
		{
				ret.obj->integer.u = num;
		}
		AR_EraseBuffer(buffer, idx + 1);
		return ret;
}





static snRetVal_t		__get_str(arBuffer_t	*buffer);

static snRetVal_t	__get_float(arBuffer_t	*buffer)
{
		size_t			buf_len;
		const byte_t	*pbuf;
		double			num;
		snObject_t		*str_obj;
		snRetVal_t		ret = {AR_S_YES, NULL};
		AR_ASSERT(buffer != NULL);
		
		str_obj = NULL;
		ret = __get_str(buffer);

		if(ret.status != AR_S_YES)
		{
				AR_ASSERT(ret.obj == NULL);
				goto END_POINT;
		}else
		{
				str_obj = ret.obj;
				ret.obj = NULL;
		}

		buf_len = AR_GetBufferAvailable(buffer);
		pbuf	= AR_GetBufferData(buffer);
		
		if(pbuf == NULL || pbuf[0] != 'e')
		{
				ret.status = AR_E_INVAL;
				goto END_POINT;
		}

		
		AR_EraseBuffer(buffer, 1);
		
		{
				wchar_t buf[1024];
				int_t need_n;
				need_n= SN_GetWcsFromStringObject(str_obj, buf, 1024);
				if(need_n <= 0)
				{
						ret.status = AR_E_INVAL;
						goto END_POINT;
				}

				if(AR_wtod(buf, &num) == NULL)
				{
						ret.status = AR_E_INVAL;
						goto END_POINT;
				}
		}

		ret.obj = SN_CreateObject(SN_FLOAT_T);

		if(ret.obj == NULL)
		{
				ret.status = AR_E_NOMEM;
				goto END_POINT;
		}

		ret.obj->float_num.num = num;

END_POINT:
		if(str_obj)
		{
				SN_DestroyObject(str_obj);
				str_obj = NULL;
		}

		return ret;
}



static snRetVal_t		__get_str(arBuffer_t	*buffer)
{
		size_t	buf_len, idx;
		const byte_t	*pbuf;
		
		size_t	l = 0;
		snRetVal_t ret = {AR_S_YES, NULL};
		AR_ASSERT(buffer != NULL);

		buf_len = AR_GetBufferAvailable(buffer);
		pbuf	= AR_GetBufferData(buffer);
		
		if(pbuf == NULL)
		{
				ret.status = AR_E_INVAL;
				return ret;
		}
		
		for(idx = 0; idx < buf_len && AR_isdigit(pbuf[idx]); ++idx)
		{
				l *= 10;
				l += (pbuf[idx] - '0');
		}

		if(idx  == buf_len || pbuf[idx] != ':' || l == 0)
		{
				ret.status = AR_E_INVAL;
				return ret;
		}

		if(buf_len <  idx + 1 + l)
		{
				ret.status = AR_E_INVAL;
				return ret;
		}

		ret.obj = SN_CreateObject(SN_STRING_T);
		if(ret.obj == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}

		idx++;

		ret.status = SN_SetStringByData(&ret.obj->string, pbuf + idx, l);
		
		if(ret.status != AR_S_YES)
		{
				SN_DestroyObject(ret.obj);
				ret.obj = NULL;
				return ret;
		}

		AR_EraseBuffer(buffer, idx + l);
		return ret;
}


static snRetVal_t		__get_list(arBuffer_t	*buffer);
static snRetVal_t		__get_dict(arBuffer_t	*buffer);

static snRetVal_t		__get_obj(arBuffer_t	*buffer)
{
		byte_t b;
		const byte_t *data;
		snRetVal_t ret = {AR_S_YES, NULL};

		AR_ASSERT(buffer != NULL && AR_GetBufferAvailable(buffer) > 0);

		data = AR_GetBufferData(buffer);
		
		if(data == NULL)
		{
				ret.status = AR_E_INVAL;
				return ret;
		}

		b = data[0];
		
		switch(b)
		{
		case 'd':
				AR_EraseBuffer(buffer, 1);
				return __get_dict(buffer);
		case 'i':
				AR_EraseBuffer(buffer, 1);
				return __get_int(buffer);
		case 'f':
				AR_EraseBuffer(buffer, 1);
				return __get_float(buffer);
		case 'l':
				AR_EraseBuffer(buffer, 1);
				return __get_list(buffer);
		default:
		{
				if(AR_isdigit(b) || b == '-')
				{
						return __get_str(buffer);
				}else
				{
						ret.status = AR_E_INVAL;
						return ret;
				}
		}
		}
}



static snRetVal_t		__get_list(arBuffer_t	*buffer)
{
		const byte_t	*pb;
		snRetVal_t ret = {AR_S_YES, NULL};

		AR_ASSERT(buffer != NULL && AR_GetBufferAvailable(buffer) > 0);
		
		ret.obj = SN_CreateObject(SN_LIST_T);

		if(ret.obj == NULL)
		{
				ret.status = AR_E_NOMEM;
				goto FAILED_POINT;
		}
		
		while(true)
		{
				snRetVal_t tmp_ret;
				pb = AR_GetBufferData(buffer);
				if(pb == NULL)
				{
						ret.status = AR_E_INVAL;
						goto FAILED_POINT;
				}

				if(*pb == 'e')
				{
						break;
				}
				
				tmp_ret = __get_obj(buffer);/*资源1*/

				if(tmp_ret.status != AR_S_YES)	/*获取1失败*/
				{
						ret.status = tmp_ret.status;
						goto FAILED_POINT;
				}
				
				AR_ASSERT(tmp_ret.obj != NULL);
				ret.status = SN_InsertToList(&ret.obj->list, tmp_ret.obj);	

				if(ret.status != AR_S_YES)/*资源1插入0失败,清理资源1*/
				{
						SN_DestroyObject(tmp_ret.obj);
						tmp_ret.obj = NULL;
						goto FAILED_POINT;
				}
		}

		AR_EraseBuffer(buffer, 1);
		return ret;

FAILED_POINT:
		if(ret.obj != NULL)
		{
				SN_DestroyObject(ret.obj);/*清理资源0*/
				ret.obj = NULL;
		}

		return ret;
}


static snRetVal_t		__get_dict(arBuffer_t	*buffer)
{
		const byte_t	*pb;
		snRetVal_t ret = {AR_S_YES, NULL};

		AR_ASSERT(buffer != NULL && AR_GetBufferAvailable(buffer) > 0);
		
		ret.obj = SN_CreateObject(SN_DICT_T);

		if(ret.obj == NULL)
		{
				ret.status = AR_E_NOMEM;
				goto FAILED_POINT;
		}
		
		
		while(true)
		{
				snRetVal_t key, val;
				
				pb = AR_GetBufferData(buffer);
				if(pb == NULL)
				{
						ret.status = AR_E_NOMEM;
						goto FAILED_POINT;
				}

				if(*pb == 'e')
				{
						break;
				}

				key = __get_str(buffer);
				if(key.status != AR_S_YES)
				{
						ret.status = key.status;
						AR_ASSERT(key.obj == NULL);
						goto FAILED_POINT;
				}

				val = __get_obj(buffer);
				if(val.status != AR_S_YES)
				{
						ret.status = val.status;
						AR_ASSERT(val.obj == NULL);
						SN_DestroyObject(key.obj);
						key.obj = NULL;
						goto FAILED_POINT;
				}
				
				ret.status = SN_InsertToDict(&ret.obj->dict, key.obj, val.obj);
				if(ret.status != AR_S_YES )
				{
						SN_DestroyObject(key.obj);
						key.obj = NULL;
						SN_DestroyObject(val.obj);
						val.obj = NULL;
						goto FAILED_POINT;
				}
		}
		
		AR_EraseBuffer(buffer, 1);
		
		return ret;
FAILED_POINT:
		if(ret.obj)
		{
				SN_DestroyObject(ret.obj);
				ret.obj = NULL;
		}

		return ret;
}



snRetVal_t		SN_GetObject(arBuffer_t	*buffer)
{
		return __get_obj(buffer);
}





static arStatus_t		__put_int(arBuffer_t	*buffer, const snInteger_t *integer)
{
		char buf[256];
		char *p;
		bool_t	is_neg = false;
		uint_64_t		num;
		
		static const char _tbl[] = "0123456789";

		AR_ASSERT(buf != NULL && integer != NULL);

		if(integer->is_signed)
		{
				if(integer->s < 0)
				{
						is_neg = true;
						num = (uint_64_t)(-integer->s);
				}else
				{
						num = (uint_64_t)integer->s;
				}
		}else
		{
				num= integer->u;
		}
		
		p = buf + sizeof(buf);
		*--p = '\0';
		*--p = 'e';
		do{ *--p = _tbl[num % 10];}while((num /= 10));

		if(is_neg)*--p = '-';
		*--p = 'i';

		return AR_InsertBuffer(buffer, (const byte_t*)p, AR_strlen(p));
}


static arStatus_t __put_string(arBuffer_t	*buffer, const snString_t *string);


static arStatus_t		__put_float(arBuffer_t	*buffer, const snFloat_t *float_num)
{
		arStatus_t status;
		const char b = 'f', e = 'e';
		wchar_t buf[1024];
		
		AR_ASSERT(buffer != NULL && float_num != NULL);

		status = AR_S_YES;
		

		if(AR_swprintf(buf, 1024, L"%.*g", (uint_32_t)30, float_num->num) <= 0)
		{
				status = AR_E_INVAL;
				return status;
		}

		status = AR_InsertBuffer(buffer, (const byte_t*)&b, 1);
		
		if(status != AR_S_YES)
		{
				goto END_POINT;
		}

		{
				snString_t sn_str;
				SN_InitString(&sn_str);

				status = SN_SetStringByWcs(&sn_str, buf);

				if(status != AR_S_YES)
				{
						SN_UnInitString(&sn_str);
						goto END_POINT;
				}

				status = __put_string(buffer, &sn_str);

				SN_UnInitString(&sn_str);

				if(status != AR_S_YES)
				{
						goto END_POINT;
				}
		}
		
		status = AR_InsertBuffer(buffer, (const byte_t*)&e, 1);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}
		
END_POINT:
		return status;
}



static arStatus_t __put_string(arBuffer_t	*buffer, const snString_t *string)
{
		char buf[256];
		char *p;
		size_t	l;
		static const char _tbl[] = "0123456789";
		arStatus_t status;
		AR_ASSERT(buf != NULL && string != NULL && string->len > 0 && string->data != NULL);
		
		l = string->len;
		
		p = buf + sizeof(buf);
		*--p = '\0';
		*--p = ':';

		do{ *--p = _tbl[l % 10];}while((l /= 10));

		status = AR_InsertBuffer(buffer, (const byte_t*)p, AR_strlen(p));
		if(status != AR_S_YES)
		{
				return status;
		}

		status = AR_InsertBuffer(buffer, string->data, string->len);

		if(status != AR_S_YES)
		{
				return status;
		}

		return AR_S_YES;
}


static arStatus_t __put_list(arBuffer_t	*buffer, const snList_t *lst);
static arStatus_t __put_dict(arBuffer_t	*buffer, const snDict_t *dict);

static arStatus_t __put_obj(arBuffer_t	*buffer, const snObject_t *obj)
{
		
		switch(obj->type)
		{
		default:
		{
				AR_ASSERT(false);
				return AR_E_INVAL;
				break;
		}
		case SN_INT_T:
		{
				return __put_int(buffer, &obj->integer);
				break;
		}
		case SN_FLOAT_T:
		{
				return __put_float(buffer, &obj->float_num);
				break;
		}
		case SN_STRING_T:
		{
				return __put_string(buffer, &obj->string);
				break;
		}
		case SN_LIST_T:
		{
				return __put_list(buffer, &obj->list);
				break;
		}
		case SN_DICT_T:
		{
				return __put_dict(buffer, &obj->dict);
				break;
		}
		}

		
}

static arStatus_t __put_list(arBuffer_t	*buffer, const snList_t *lst)
{
		static const char *h = "l";
		static const char *e = "e";
		size_t i;
		arStatus_t		status;
		AR_ASSERT(buffer != NULL && lst != NULL);

		status = AR_InsertBuffer(buffer, (const byte_t*)h, 1);

		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < lst->count; ++i)
		{
				status = __put_obj(buffer, lst->lst[i]);

				if(status != AR_S_YES)
				{
						return status;
				}
		}

		status = AR_InsertBuffer(buffer, (const byte_t*)e, 1);

		if(status != AR_S_YES)
		{
				return status;
		}

		return AR_S_YES;
}

static arStatus_t __put_dict(arBuffer_t	*buffer, const snDict_t *dict)
{
		static const char *h = "d";
		static const char *e = "e";
		size_t i;
		arStatus_t		status;
		AR_ASSERT(buffer != NULL && dict != NULL);
		

		status = AR_InsertBuffer(buffer, (const byte_t*)h, 1);

		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < dict->count; ++i)
		{
				status = __put_string(buffer, &dict->pairs[i].key->string);
				if(status != AR_S_YES)
				{
						return status;
				}
				status = __put_obj(buffer,  dict->pairs[i].val);
				if(status != AR_S_YES)
				{
						return status;
				}
		}
		status = AR_InsertBuffer(buffer, (const byte_t*)e, 1);
		if(status != AR_S_YES)
		{
				return status;
		}

		return AR_S_YES;
}


arStatus_t			SN_PutObject(arBuffer_t	*buffer, const snObject_t *obj)
{
		AR_ASSERT(buffer != NULL && obj != NULL);
		AR_ClearBuffer(buffer);
		return __put_obj(buffer, obj);
}



















/*****************************************************************************************************/


snRetVal_t		SN_FindObjectByWcsPath(snObject_t *obj, const wchar_t *path)
{
		
		snRetVal_t	ret = {AR_S_YES, NULL};
		wchar_t *beg, *p;
		size_t len = 0;
		wchar_t *pbuf = NULL;
		wchar_t	save;
		AR_ASSERT(obj != NULL && path != NULL );

		pbuf = AR_wcsdup(path);

		if(pbuf == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}

		save = L'\0';

		beg = pbuf;
		p = beg;

		

		while(obj != NULL && *p != L'\0')
		{
				while(*p != L'\0' && *p != L'/') ++p;
				len = p - beg;

				/*
						///a///b///c///d...
						a/b/c
						/b/c
				*/
				

				if(len == 0)
				{
						if(*p == L'\0')
						{
								obj = NULL;
								goto END_POINT;
						}

						AR_ASSERT(*p == L'/');
				}else
				{
						save  = *p;
						*p = 0;

						if(obj->type == SN_LIST_T)
						{
								size_t idx;
								AR_wtou(beg, (uint_t*)&idx, 10);
								obj = SN_GetFromList(&obj->list, idx);

						}else if(obj->type == SN_DICT_T)
						{
								snObject_t		*key = SN_CreateObject(SN_STRING_T);

								if(key == NULL)
								{
										ret.status = AR_E_NOMEM;
										goto END_POINT;
								}

								ret.status = SN_SetStringByWcs(&key->string, beg);
								if(ret.status != AR_S_YES)
								{
										SN_DestroyObject(key);
										key = NULL;
										goto END_POINT;
								}

								obj = SN_FindFromDict(&obj->dict, key);

								if(key)
								{
										SN_DestroyObject(key);
								}
						}else
						{
								ret.status = AR_S_NO;
								obj = NULL;
								goto END_POINT;
						}
						*p = save;
				}

				if(*p != L'\0')
				{
						beg = ++p;
				}else
				{
						beg = p;
				}
		}
		ret.obj = obj;
END_POINT:
		if(pbuf != NULL)
		{
				AR_DEL(pbuf);
				pbuf = NULL;
		}
		
		return ret;
}



snRetVal_t		SN_FindObjectByStrPath(snObject_t *obj, const char *path)
{
		snRetVal_t ret = {AR_S_YES, NULL};
		wchar_t *wcs = NULL;
		AR_ASSERT(obj != NULL && path != NULL);

		/*wcs = AR_utf8_convto_wcs(path);*/
		wcs = AR_str_convto_wcs(AR_CP_UTF8, path, AR_strlen(path));

		if(wcs == NULL)
		{
				ret.status = AR_S_NO;
				return ret;
		}

		ret = SN_FindObjectByWcsPath(obj, wcs);

		AR_DEL(wcs);
		return ret;
}



/***************************************************************************************************************************/


arStatus_t			SN_InsertToDictObject(snObject_t *obj, snObject_t *key, snObject_t *value)
{
		AR_ASSERT(obj != NULL && obj->type == SN_DICT_T);
		AR_ASSERT(key != NULL && value != NULL);
		
		if(obj->type != SN_DICT_T)
		{
				return AR_E_INVAL;
		}

		return SN_InsertToDict(&obj->dict, key, value);
}


arStatus_t			SN_RemoveFromDictObject(snObject_t *obj, const snObject_t *key)
{
		AR_ASSERT(obj != NULL && obj->type == SN_DICT_T);
		AR_ASSERT(key != NULL);
		
		if(obj->type != SN_DICT_T)
		{
				return AR_E_INVAL;
		}

		return SN_RemoveFromDict(&obj->dict,key);
}


snObject_t*		SN_FindFromDictObject(snObject_t *obj, const snObject_t *key)
{
		AR_ASSERT(obj != NULL && obj->type == SN_DICT_T);
		AR_ASSERT(key != NULL);
		
		if(obj->type != SN_DICT_T)
		{
				return false;
		}

		return SN_FindFromDict(&obj->dict,key);
}


snObject_t*			SN_FindFromDictObjectByStr(snObject_t *obj, const char *str)
{
		snObject_t *sn_key, *ret_obj;
		AR_ASSERT(obj != NULL && str != NULL && AR_strlen(str) > 0);
        
		sn_key = SN_CreateObject(SN_STRING_T);
		if(sn_key == NULL)
		{
				return NULL;
		}
        
		if(SN_SetStringObjectByStr(sn_key, str) != AR_S_YES)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
				return NULL;
		}
        
		ret_obj = SN_FindFromDictObject(obj, sn_key);
        
		SN_DestroyObject(sn_key);
		sn_key = NULL;
        
		return ret_obj;
}


snObject_t*			SN_FindFromDictObjectByWcs(snObject_t *obj, const wchar_t *str)
{
		snObject_t *sn_key, *ret_obj;
		AR_ASSERT(obj != NULL && str != NULL && AR_wcslen(str) > 0);
        
		sn_key = SN_CreateObject(SN_STRING_T);
		if(sn_key == NULL)
		{
				return NULL;
		}
        
		if(SN_SetStringObjectByWcs(sn_key, str) != AR_S_YES)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
				return NULL;
		}
        
		ret_obj = SN_FindFromDictObject(obj, sn_key);
        
		SN_DestroyObject(sn_key);
		sn_key = NULL;
        
		return ret_obj;
}




snPair_t*		SN_GetFromDictObject(snObject_t *obj, size_t idx)
{
		AR_ASSERT(obj != NULL && obj->type == SN_DICT_T);
		AR_ASSERT(idx < obj->dict.count);
		return &obj->dict.pairs[idx];

}

size_t			SN_GetDictObjectCount(const snObject_t *obj)
{
		AR_ASSERT(obj != NULL && obj->type == SN_DICT_T);
		return obj->dict.count;
}





arStatus_t			SN_InsertToListObject(snObject_t	*lst, snObject_t *obj)
{
		AR_ASSERT(lst != NULL && lst->type == SN_LIST_T);
		AR_ASSERT(obj != NULL);
		if(lst->type != SN_LIST_T)
		{
				return AR_E_INVAL;
		}

		return SN_InsertToList(&lst->list, obj);
}

arStatus_t			SN_RemoveFromListObject(snObject_t	*lst, size_t idx)
{
		AR_ASSERT(lst != NULL && lst->type == SN_LIST_T);
		if(lst->type != SN_LIST_T)
		{
				return AR_E_INVAL;
		}
		
		return SN_RemoveFromList(&lst->list, idx);
}

int_t			SN_IndexOfListObject(const snObject_t *lst, const snObject_t *obj)
{
		AR_ASSERT(lst != NULL && lst->type == SN_LIST_T);
		AR_ASSERT(obj != NULL);
		
		if(lst->type != SN_LIST_T)
		{
				return -1;
		}
		
		return SN_IndexOfList(&lst->list, obj);
}


snObject_t*		SN_GetFromListObject(snObject_t *lst, size_t idx)
{
		AR_ASSERT(lst != NULL && lst->type == SN_LIST_T);
		
		if(lst->type != SN_LIST_T)
		{
				return NULL;
		}
		
		return SN_GetFromList(&lst->list, idx);
}


size_t			SN_GetListObjectCount(const snObject_t *lst)
{
		AR_ASSERT(lst != NULL && lst->type == SN_LIST_T);
		
		if(lst->type != SN_LIST_T)
		{
				return 0;
		}

		return lst->list.count;
}

arStatus_t			SN_SetStringObjectByData(snObject_t	*dest, const byte_t *data, size_t len)
{
		AR_ASSERT(dest != NULL && dest->type == SN_STRING_T);
		AR_ASSERT(data != NULL && len > 0);
		
		if(dest->type != SN_STRING_T)
		{
				return AR_E_INVAL;
		}

		return SN_SetStringByData(&dest->string, data, len);
}

arStatus_t			SN_SetStringObjectByStr(snObject_t	*dest, const char *str)
{
		AR_ASSERT(dest != NULL && dest->type == SN_STRING_T);
		AR_ASSERT(str != NULL);

		if(dest->type != SN_STRING_T)
		{
				return AR_E_INVAL;
		}

		return SN_SetStringByStr(&dest->string, str);
}

arStatus_t			SN_SetStringObjectByWcs(snObject_t	*dest, const wchar_t *str)
{

		AR_ASSERT(dest != NULL && dest->type == SN_STRING_T);
		AR_ASSERT(str != NULL);

		if(dest->type != SN_STRING_T)
		{
				return AR_E_INVAL;
		}

		return SN_SetStringByWcs(&dest->string, str);
}




int_t			SN_GetDataFromStringObject(const snObject_t	*obj, byte_t *buf, size_t len)
{
		AR_ASSERT(obj != NULL && obj->type == SN_STRING_T);
		if(obj->type != SN_STRING_T)
		{
				return -1;
		}

		if(buf != NULL)
		{
				if(len < obj->string.len)
				{
						return -1;
				}

				AR_memcpy(buf, obj->string.data, obj->string.len);
		}
		
		return (int_t)obj->string.len;
}		


int_t			SN_GetStrFromStringObject(const snObject_t	*obj, char *buf, size_t len)
{
		int_t l;
		
		AR_ASSERT(obj != NULL && obj->type == SN_STRING_T);

		if(obj->type != SN_STRING_T)
		{
				return -1;
		}

		l = SN_GetDataFromStringObject(obj, NULL, 0);
		
		if(l < 0)
		{
				return l;
		}
		
		if(buf == NULL)
		{
				return l + 1;
		}else
		{
				if((int_t)len < (l + 1))
				{
						return -1;
				}

				l = SN_GetDataFromStringObject(obj, (byte_t*)buf, l);

				if(l < 0)
				{
						return l;
				}
				buf[l] = 0;
				return l + 1;
		}
}


int_t			SN_GetWcsFromStringObject(const snObject_t	*obj, wchar_t *buf, size_t len)
{
		int_t l;
		char *tmp;
		wchar_t *wtmp;
		AR_ASSERT(obj != NULL && obj->type == SN_STRING_T);

		if(obj->type != SN_STRING_T)
		{
				return -1;
		}

		l = SN_GetStrFromStringObject(obj, NULL, 0);
		if(l < 0)
		{
				return l;
		}

		tmp = AR_NEWARR(char, l);

		if(tmp == NULL)
		{
				return -1;
		}

		l = SN_GetStrFromStringObject(obj, tmp, l);

		if(l < 0)
		{
				AR_DEL(tmp);
				return -1;
		}

/*		wtmp = AR_utf8_convto_wcs(tmp);*/
		wtmp = AR_str_convto_wcs(AR_CP_UTF8, tmp, AR_strlen(tmp));

		if(tmp == NULL)
		{
				AR_DEL(tmp);
				return -1;
		}
		
		if(buf == NULL)
		{
				int_t ret = (int_t)(AR_wcslen(wtmp) + 1);
				AR_DEL(tmp);
				AR_DEL(wtmp);
				return ret;
		}else
		{
				int_t ret = (int_t)(AR_wcslen(wtmp) + 1);

				if((int_t)len < ret)
				{
						AR_DEL(tmp);
						AR_DEL(wtmp);
						return -1;
				}
				AR_wcscpy(buf, wtmp);
				AR_DEL(tmp);
				AR_DEL(wtmp);
				return ret;
		}
}




arStatus_t			SN_CompStringObjectByStringObject(const snObject_t	*l, const snObject_t	*r)
{
		AR_ASSERT(l != NULL && l->type == SN_STRING_T);
		AR_ASSERT(r != NULL && r->type == SN_STRING_T);
		
		if(l->type != SN_STRING_T)
		{
				return AR_S_NEQ;
		}

		if(r->type != SN_STRING_T)
		{
				return AR_S_NEQ;
		}

		return SN_CompStringByString(&l->string, &r->string);
}


arStatus_t			SN_CompStringObjectByData(const snObject_t	*l,			const byte_t *data, size_t len)
{
		AR_ASSERT(l != NULL && l->type == SN_STRING_T);
		AR_ASSERT(data != NULL && len > 0);
		
		if(l->type != SN_STRING_T)
		{
				return AR_S_NEQ;
		}

		return SN_CompStringByData(&l->string, data, len);
}


arStatus_t			SN_CompStringObjectByStr(const snObject_t		*l,		const char *str)
{
		AR_ASSERT(l != NULL && l->type == SN_STRING_T);
		AR_ASSERT(str != NULL);
		
		if(l->type != SN_STRING_T)
		{
				return AR_S_NEQ;
		}
		
		return SN_CompStringByStr(&l->string, str);
}


arStatus_t			SN_CompStringObjectByWcs(const snObject_t		*l,		const wchar_t *str)
{
		AR_ASSERT(l != NULL && l->type == SN_STRING_T);
		AR_ASSERT(str != NULL);
		
		if(l->type != SN_STRING_T)
		{
				return AR_S_NEQ;
		}
		
		return SN_CompStringByWcs(&l->string, str);

}




void			SN_SetIntObject( snObject_t	*obj,	int_64_t num)
{
		AR_ASSERT(obj != NULL && obj->type == SN_INT_T);

		if(obj->type != SN_INT_T)
		{
				return;
		}

		obj->integer.is_signed = true;
		obj->integer.s = num;
}


void			SN_SetUIntObject(snObject_t	*obj,	uint_64_t num)
{
		AR_ASSERT(obj != NULL && obj->type == SN_INT_T);

		if(obj->type != SN_INT_T)
		{
				return;
		}

		obj->integer.is_signed = false;
		obj->integer.u = num;
}



uint_64_t		SN_GetUIntObject(const snObject_t	*obj)
{
		AR_ASSERT(obj != NULL && obj->type == SN_INT_T);

		if(obj->type != SN_INT_T)
		{
				return 0;
		}

		return obj->integer.u;
}


int_64_t		SN_GetIntObject(const snObject_t	*obj)
{
		AR_ASSERT(obj != NULL && obj->type == SN_INT_T);

		if(obj->type != SN_INT_T)
		{
				return 0;
		}

		return obj->integer.s;
}



double		SN_GetFloatObject(const snObject_t	*obj)
{
		AR_ASSERT(obj != NULL && obj->type == SN_FLOAT_T);
		if(obj->type != SN_FLOAT_T)
		{
				return 0.0;
		}

		return obj->float_num.num;
}

void		SN_SetUFloatObject(snObject_t	*obj,	double num)
{
		AR_ASSERT(obj != NULL && obj->type == SN_FLOAT_T);

		if(obj->type != SN_FLOAT_T)
		{
				return;
		}

		obj->float_num.num = num;
}




#define FAILED_GOTO(_cond) do{ if(!(_cond))goto INVALID_POINT; }while(0)



arStatus_t			SN_InsertToDictObjectByStrInt(snObject_t *obj, const char *key, int_64_t val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByStr(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_INT_T);
		FAILED_GOTO(sn_val != NULL);
		SN_SetIntObject(sn_val, val);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}



arStatus_t			SN_InsertToDictObjectByStrUInt(snObject_t *obj, const char *key, uint_64_t val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;
		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByStr(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_INT_T);
		FAILED_GOTO(sn_val != NULL);
		SN_SetUIntObject(sn_val, val);
		
		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}



arStatus_t			SN_InsertToDictObjectByStrStr(snObject_t *obj, const char *key, const char *val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;
		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByStr(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByStr(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;

}





arStatus_t			SN_InsertToDictObjectByStrWcs(snObject_t *obj, const char *key, const wchar_t *val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByStr(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByWcs(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;

}



arStatus_t			SN_InsertToDictObjectByStrData(snObject_t *obj, const char *key, const byte_t *data, size_t len)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL && data != NULL && len > 0);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByStr(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);

		status = SN_SetStringObjectByData(sn_val, data, len);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}



arStatus_t			SN_InsertToDictObjectByWcsInt(snObject_t *obj, const wchar_t *key, int_64_t val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByWcs(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_INT_T);
		FAILED_GOTO(sn_val != NULL);
		SN_SetIntObject(sn_val, val);


		status = SN_InsertToDictObject(obj, sn_key, sn_val);

		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}




arStatus_t			SN_InsertToDictObjectByWcsUInt(snObject_t *obj, const wchar_t *key, uint_64_t val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByWcs(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_INT_T);
		FAILED_GOTO(sn_val != NULL);
		SN_SetUIntObject(sn_val, val);


		status = SN_InsertToDictObject(obj, sn_key, sn_val);

		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}




arStatus_t			SN_InsertToDictObjectByWcsStr(snObject_t *obj, const wchar_t *key, const char *val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByWcs(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByStr(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);

		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;

}




arStatus_t			SN_InsertToDictObjectByWcsWcs(snObject_t *obj, const wchar_t *key, const wchar_t *val)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByWcs(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByWcs(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}



arStatus_t			SN_InsertToDictObjectByWcsData(snObject_t *obj, const wchar_t *key, const byte_t *data, size_t len)
{
		arStatus_t status;
		snObject_t *sn_key, *sn_val;
		AR_ASSERT(obj != NULL && key != NULL && data != NULL && len > 0);

		sn_key = NULL;
		sn_val = NULL;

		status = AR_S_YES;

		sn_key = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_key != NULL);

		status = SN_SetStringObjectByWcs(sn_key, key);
		FAILED_GOTO(status == AR_S_YES);

		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByData(sn_val, data, len);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToDictObject(obj, sn_key, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;
INVALID_POINT:
		if(sn_key)
		{
				SN_DestroyObject(sn_key);
				sn_key = NULL;
		}

		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}






arStatus_t			SN_InsertToListObjectByStr(snObject_t *obj, const char *val)
{
		arStatus_t status;
		snObject_t *sn_val;
		AR_ASSERT(obj != NULL && val != NULL);

		sn_val = NULL;
		status = AR_S_YES;
		
		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByStr(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToListObject(obj, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;

INVALID_POINT:
		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}


arStatus_t			SN_InsertToListObjectByWcs(snObject_t *obj, const wchar_t *val)
{
		arStatus_t status;
		snObject_t *sn_val;
		AR_ASSERT(obj != NULL && val != NULL);

		sn_val = NULL;
		status = AR_S_YES;
		
		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByWcs(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToListObject(obj, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;

INVALID_POINT:
		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}



arStatus_t			SN_InsertToListObjectByInt(snObject_t *obj, const int_64_t val)
{
		arStatus_t status;
		snObject_t *sn_val;
		AR_ASSERT(obj != NULL);

		sn_val = NULL;
		status = AR_S_YES;
		
		sn_val = SN_CreateObject(SN_INT_T);
		FAILED_GOTO(sn_val != NULL);
		SN_SetIntObject(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToListObject(obj, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;

INVALID_POINT:
		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}



arStatus_t			SN_InsertToListObjectByUInt(snObject_t *obj, const uint_64_t val)
{
		arStatus_t status;
		snObject_t *sn_val;
		AR_ASSERT(obj != NULL);

		sn_val = NULL;
		status = AR_S_YES;
		
		sn_val = SN_CreateObject(SN_INT_T);
		FAILED_GOTO(sn_val != NULL);
		SN_SetUIntObject(sn_val, val);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToListObject(obj, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;

INVALID_POINT:
		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;

}



arStatus_t			SN_InsertToListObjectByData(snObject_t *obj, const byte_t *data, size_t len)
{
		arStatus_t status;
		snObject_t *sn_val;
		AR_ASSERT(obj != NULL && data != NULL && len > 0);

		sn_val = NULL;
		status = AR_S_YES;
		
		sn_val = SN_CreateObject(SN_STRING_T);
		FAILED_GOTO(sn_val != NULL);
		status = SN_SetStringObjectByData(sn_val, data, len);
		FAILED_GOTO(status == AR_S_YES);

		status = SN_InsertToListObject(obj, sn_val);
		FAILED_GOTO(status == AR_S_YES);

		return AR_S_YES;

INVALID_POINT:
		if(sn_val)
		{
				SN_DestroyObject(sn_val);
				sn_val = NULL;
		}

		return status;
}





AR_NAMESPACE_END
