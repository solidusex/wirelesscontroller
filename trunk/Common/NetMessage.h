//
//  NetMessage.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#ifndef WiController_NetMessage_h
#define WiController_NetMessage_h

#if defined(__cplusplus)
		using namespace ARSpace;
#endif

typedef enum
{
        WI_MOUSEMOVE    =       0x0000,
        
        WI_LBUTTONDOWN  =       0x0001,
        WI_LBUTTONUP    =       0x0002,
        WI_LBUTTONDBLCLK=       0x0003,
        
        WI_RBUTTONDOWN  =       0x0004,
        WI_RBUTTONUP    =       0x0005,
        WI_RBUTTONDBLCLK=       0x0006,
        
        WI_MBUTTONDOWN  =       0x0007,
        WI_MBUTTONUP    =       0x0008,
        WI_MBUTTONDBLCLK=       0x0009,
        WI_MOUSEWHEEL   =       0x000A,
        WI_MOUSEHWHEEL  =       0x000B,
        
        WI_MBUTTONSGLCLK=       0x0010,
        WI_LBUTTONSGLCLK=       0x0011,
        WI_RBUTTONSGLCLK=       0x0012,
}wiMouseEventType_t;


typedef struct __mouse_net_message_tag
{
        wiMouseEventType_t  t;
        float               x;
        float               y;
        float               data;
}mouseEvent_t;






typedef enum
{
        WI_FUNCTION_KEY_T,
        WI_ASCII_KEY_T,
        WI_TEXT_T
}wiKeyboardEventType_t;

typedef enum
{
        WI_KEY_FUNC_ESC_DONW  =       0x0000,
        WI_KEY_FUNC_ESC_UP    =       0x0001,
        
        WI_KEY_FUNC_CMD_DONW  =       0x0002,
        WI_KEY_FUNC_CMD_UP    =       0x0003,

        WI_KEY_FUNC_CTRL_DONW  =       0x0004,
        WI_KEY_FUNC_CTRL_UP    =       0x0005,
        
        WI_KEY_FUNC_TAB_DONW  =       0x0006,
        WI_KEY_FUNC_TAB_UP    =       0x0007,
        
        WI_KEY_FUNC_SHIFT_DONW  =       0x0008,
        WI_KEY_FUNC_SHIFT_UP    =       0x0009,
        
        WI_KEY_FUNC_DELETE_DONW  =       0x000A,
        WI_KEY_FUNC_DELETE_UP    =       0x000B,
        
        WI_KEY_FUNC_INSERT_DONW  =       0x000C,
        WI_KEY_FUNC_INSERT_UP    =       0x000D,
        
        WI_KEY_FUNC_HOME_DONW  =       0x000E,
        WI_KEY_FUNC_HOME_UP    =       0x000F,
        
        WI_KEY_FUNC_END_DONW  =       0x0010,
        WI_KEY_FUNC_END_UP    =       0x0011,
        
        WI_KEY_FUNC_PAGEDOWN_DONW  =     0x0012,
        WI_KEY_FUNC_PAGEDOWN_UP    =     0x0013,
        
        WI_KEY_FUNC_PAGEUP_DONW  =       0x0014,
        WI_KEY_FUNC_PAGEUP_UP    =       0x0015,
        
        WI_KEY_FUNC_UP_DONW  =       0x0016,
        WI_KEY_FUNC_UP_UP    =       0x0017,
        WI_KEY_FUNC_DOWN_DONW  =       0x0018,
        WI_KEY_FUNC_DOWN_UP    =       0x0019,
        WI_KEY_FUNC_LEFT_DONW  =       0x001A,
        WI_KEY_FUNC_LEFT_UP    =       0x001B,
        WI_KEY_FUNC_RIGHT_DONW  =       0x001C,
        WI_KEY_FUNC_RIGHT_UP    =       0x001D,
        
        WI_KEY_FUNC_BACKSPACE_DONW  =       0x001E,
        WI_KEY_FUNC_BACKSPACE_UP    =       0x001F,
        
        WI_KEY_FUNC_ALT_DONW  =       0x0020,
        WI_KEY_FUNC_ALT_UP    =       0x0021
}wiKeyboardFunctionKey_t;

typedef struct __keyboard_net_message_tag
{
		wiKeyboardEventType_t   type;
        union{
                wiKeyboardFunctionKey_t func_key;
                unsigned int            ascii;
                char                    text[8192];
        };
}keyboardEvent_t;






typedef struct __shortcuts_net_message_tag
{
		int		unused;
}shortcutsEvent_t;


typedef enum 
{
        WI_MOUSE_EVENT_T,
        WI_KEYBOARD_EVENT_T,
        WI_SHORTCUTS_EVENT_T,
		WI_SHORTCUTS_EVENT_MAX_T
}netMsgEventType_t;

#define WI_PASSWORD             "PWD"

#define WI_EVENT_NAME           "EVT"
#define WI_MOUSE_EVENT_TYPE     "TP"
#define WI_MOUSE_X              "X"
#define WI_MOUSE_Y              "Y"
#define WI_MOUSE_DATA           "D"







static AR_INLINE arBuffer_t* MouseEvent_To_NetMessage(const mouseEvent_t *me, const char *pwd)
{
        arBuffer_t *buf = NULL;
        snObject_t *obj = NULL;
        AR_ASSERT(me != NULL);
        
        obj = SN_CreateObject(SN_DICT_T);
        
        if(pwd)
        {
                SN_InsertToDictObjectByStrStr(obj, WI_PASSWORD, pwd);
        }

        SN_InsertToDictObjectByStrInt(obj, WI_EVENT_NAME, WI_MOUSE_EVENT_T);
        SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_EVENT_TYPE, me->t);

        if(me->t == WI_MOUSEWHEEL || me->t == WI_MOUSEHWHEEL)
        {
                SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_DATA, (int_64_t)me->data);
        }else
        {
                SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_X, (int_64_t)me->x);
                SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_Y, (int_64_t)me->y);
        }
       
        buf = AR_CreateBuffer(128);
        SN_PutObject(buf, obj);
        
        SN_DestroyObject(obj);
        obj = NULL;
        
        return buf;
        
        
        
}



#define WI_KEYBOARD_EVENT_TYPE          "KBEVT"
#define WI_KEYBOARD_FUNCKEY_VALUE       "FUNC_VALUE"
#define WI_KEYBOARD_ASCIIKEY_VALUE       "ASCII_VALUE"
#define WI_KEYBOARD_TEXTKEY_VALUE       "TEXT_VALUE"


static AR_INLINE arBuffer_t* KeyboardEvent_To_NetMessage(const keyboardEvent_t *ke, const char *pwd)
{
		
        arBuffer_t *buf = NULL;
        snObject_t *obj = NULL;
        AR_ASSERT(ke != NULL);
        
        obj = SN_CreateObject(SN_DICT_T);
        
        if(pwd)
        {
                SN_InsertToDictObjectByStrStr(obj, WI_PASSWORD, pwd);
        }
        
        SN_InsertToDictObjectByStrInt(obj, WI_EVENT_NAME, WI_KEYBOARD_EVENT_T);
        SN_InsertToDictObjectByStrInt(obj, WI_KEYBOARD_EVENT_TYPE, ke->type);
        
        if(ke->type == WI_FUNCTION_KEY_T)
        {
                SN_InsertToDictObjectByStrInt(obj, WI_KEYBOARD_FUNCKEY_VALUE, (int_64_t)ke->func_key);
        }else if(ke->type == WI_ASCII_KEY_T)
        {
                SN_InsertToDictObjectByStrInt(obj, WI_KEYBOARD_ASCIIKEY_VALUE, (int_64_t)ke->ascii);
        }else if(ke->type == WI_TEXT_T)
        {
                SN_InsertToDictObjectByStrStr(obj, WI_KEYBOARD_TEXTKEY_VALUE, ke->text);
        }
       
        
        buf = AR_CreateBuffer(128);
        SN_PutObject(buf, obj);
        
        SN_DestroyObject(obj);
        obj = NULL;
        
        return buf;
}




static AR_INLINE arBuffer_t* ShortcutsEvent_To_NetMessage(const shortcutsEvent_t *se, const char *pwd)
{
		AR_UNUSED(se);
		AR_UNUSED(pwd);
		return NULL;
}

/*

#define WI_MOUSE_EVENT_TYPE     "TP"
#define WI_MOUSE_X              "X"
#define WI_MOUSE_Y              "Y"
#define WI_MOUSE_DATA           "D"
*/




#define __CHECK_AND_RET(_cond, _evt) do{ if(!(_cond)) {	return _evt;}}while(0)

static AR_INLINE arStatus_t  NetMessage_To_MouseEvent(mouseEvent_t *me, snObject_t *obj)
{
        snObject_t *val = NULL;
        AR_ASSERT(me != NULL && obj != NULL);
        
        AR_memset(me, 0, sizeof(*me));
        val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_EVENT_TYPE);
        
		__CHECK_AND_RET(val != NULL, AR_E_INVAL);
        
        me->t = (wiMouseEventType_t)SN_GetIntObject(val);
        
        if(me->t == WI_MOUSEWHEEL  || me->t == WI_MOUSEHWHEEL)
        {
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_DATA);
				__CHECK_AND_RET(val != NULL, AR_E_INVAL);
                me->data = (float)SN_GetIntObject(val);
        }else
        {
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_X);
				__CHECK_AND_RET(val != NULL, AR_E_INVAL);
				me->x = (float)SN_GetIntObject(val);
                
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_Y);
				__CHECK_AND_RET(val != NULL, AR_E_INVAL);
                me->y = (float)SN_GetIntObject(val);
        }
        return AR_S_YES;
}



static AR_INLINE arStatus_t NetMessage_To_KeyboardEvent(keyboardEvent_t *ke, snObject_t *obj)
{
		snObject_t *val = NULL;
        AR_ASSERT(ke != NULL && obj != NULL);
        
        AR_memset(ke, 0, sizeof(*ke));
        val = SN_FindFromDictObjectByStr(obj, WI_KEYBOARD_EVENT_TYPE);
        
		__CHECK_AND_RET(val != NULL, AR_E_INVAL);
        
        ke->type = (wiKeyboardEventType_t)SN_GetIntObject(val);

		if(ke->type == WI_FUNCTION_KEY_T)
		{
				val = SN_FindFromDictObjectByStr(obj, WI_KEYBOARD_FUNCKEY_VALUE);
				__CHECK_AND_RET(val != NULL, AR_E_INVAL);
				ke->func_key = (wiKeyboardFunctionKey_t)SN_GetUIntObject(val);

		}else if(ke->type == WI_ASCII_KEY_T)
		{
				val = SN_FindFromDictObjectByStr(obj, WI_KEYBOARD_ASCIIKEY_VALUE);
				__CHECK_AND_RET(val != NULL, AR_E_INVAL);
				ke->ascii = (wiKeyboardFunctionKey_t)SN_GetUIntObject(val);
				
		}else if(ke->type == WI_TEXT_T)
		{
				int_t len;
				val = SN_FindFromDictObjectByStr(obj, WI_KEYBOARD_TEXTKEY_VALUE);
				__CHECK_AND_RET(val != NULL, AR_E_INVAL);
				len = SN_GetStrFromStringObject(val, ke->text, sizeof(ke->text) * sizeof(ke->text[0]));
				__CHECK_AND_RET(len > 0, AR_E_INVAL);
		}else
		{
				__CHECK_AND_RET(false, AR_E_INVAL);
		}
		return AR_S_YES;
}





static AR_INLINE arStatus_t NetMessage_To_ShortcutsEvent(shortcutsEvent_t *se, snObject_t *obj)
{
		AR_UNUSED(se);
		AR_UNUSED(obj);
		return AR_E_INVAL;
}


typedef struct
{
		netMsgEventType_t		type;
		union{
				mouseEvent_t			me;
				keyboardEvent_t			ke;
				shortcutsEvent_t		se;
		};
}netEvent_t;

static AR_INLINE arStatus_t  NetMessage_To_Event(netEvent_t *e, arBuffer_t *buf, const char *pwd)
{

		snRetVal_t sn_ret = {AR_E_INVAL, NULL};
		arStatus_t status;
		snObject_t *val = NULL;
		
		AR_ASSERT(e != NULL && buf != NULL);

		sn_ret = SN_GetObject(buf);
		
		if(sn_ret.status != AR_S_YES)
		{
				AR_ASSERT(sn_ret.obj == NULL);
				status = sn_ret.status;
				AR_LOG(L"%ls\r\n", L"bad package");
				goto END_POINT;
		}

		if(pwd && AR_strlen(pwd) > 0)
		{
				int_t str_len;
				char *tmp_str = NULL;

				val = SN_FindFromDictObjectByStr(sn_ret.obj, WI_PASSWORD);

				if(val == NULL)
				{
						status = AR_E_INVAL;
						AR_LOG(L"%ls\r\n", L"bad password");
						goto END_POINT;
				}

				str_len = SN_GetWcsFromStringObject(val, NULL, 0);

				if(str_len <= 0)
				{
						status = AR_E_INVAL;
						AR_LOG(L"%ls\r\n", L"bad password");
						goto END_POINT;
				}


				tmp_str = AR_NEWARR(char, str_len + 1);

				str_len = SN_GetStrFromStringObject(val, tmp_str, str_len);
				AR_ASSERT(str_len > 0);

				if(AR_strcmp(tmp_str, pwd) != 0)
				{
						AR_DEL(tmp_str);
						tmp_str = NULL;


						status = AR_E_INVAL;
						AR_LOG(L"%ls\r\n", L"bad password");
						goto END_POINT;
				}

				AR_DEL(tmp_str);
				tmp_str = NULL;

		}

		e->type = WI_SHORTCUTS_EVENT_MAX_T;
		val = SN_FindFromDictObjectByStr(sn_ret.obj, WI_EVENT_NAME);

		if(val)
		{
				e->type = (netMsgEventType_t)SN_GetUIntObject(val);
		}
		
		switch(e->type)
		{
		case WI_MOUSE_EVENT_T:
		{
				status = NetMessage_To_MouseEvent(&e->me, sn_ret.obj);

				if(status != AR_S_YES)
				{
						AR_LOG(L"%ls\r\n", L"bad mouse package");
						goto END_POINT;
				}
		}
				break;
		case WI_KEYBOARD_EVENT_T:
		{
				status = NetMessage_To_KeyboardEvent(&e->ke, sn_ret.obj);

				if(status != AR_S_YES)
				{
						AR_LOG(L"%ls\r\n", L"bad keyboard package");
						goto END_POINT;
				}
		}
				break;
		case WI_SHORTCUTS_EVENT_T:
		{
				status = NetMessage_To_ShortcutsEvent(&e->se, sn_ret.obj);

				if(status != AR_S_YES)
				{
						AR_LOG(L"%ls\r\n", L"bad shortcuts package");
						goto END_POINT;
				}
		}
				break;
		default:
		{
				status = AR_E_INVAL;
				AR_LOG(L"%ls\r\n", L"bad event type from");
				goto END_POINT;
		}
		}

END_POINT:

		if(sn_ret.obj)
		{
				SN_DestroyObject(sn_ret.obj);
				sn_ret.obj = NULL;
		}

		return status;

}



#undef __CHECK_AND_RET


#endif




