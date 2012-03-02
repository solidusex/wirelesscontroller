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
        WI_MOUSE_EVENT_T,
        WI_KEYBOARD_EVENT_T,
        WI_SHORTCUTS_EVENT_T
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


static AR_INLINE arBuffer_t* KeyboardEvent_To_NetMessage(const mouseEvent_t *ke, const char *pwd)
{
		AR_UNUSED(ke);
		return NULL;
}

static AR_INLINE arBuffer_t* ShortcutsEvent_To_NetMessage(const mouseEvent_t *se, const char *pwd)
{
		AR_UNUSED(se);
		return NULL;
}






static AR_INLINE arStatus_t  NetMessage_To_MouseEvent(mouseEvent_t *me, snObject_t *obj)
{
        snObject_t *val = NULL;
        AR_ASSERT(me != NULL && obj != NULL);
        
        AR_memset(me, 0, sizeof(*me));
        val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_EVENT_TYPE);
        
        if(val == NULL)
        {
                return AR_E_INVAL;
        }
        
        me->t = (wiMouseEventType_t)SN_GetIntObject(val);
        
        if(me->t == WI_MOUSEWHEEL  || me->t == WI_MOUSEHWHEEL)
        {
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_DATA);
                if(val == NULL)
                {
                        return AR_E_INVAL;
                }
                
                me->data = (float)SN_GetIntObject(val);
        }else
        {
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_X);
                if(val == NULL)
                {
                        return AR_E_INVAL;
                }
                me->x = (float)SN_GetIntObject(val);
                
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_Y);
                if(val == NULL)
                {
                        return AR_E_INVAL;
                }
                
                me->y = (float)SN_GetIntObject(val);
        }
        
        
        return AR_S_YES;
}








#endif




