//
//  NetMessage.c
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#include "NetMessage.h"



arBuffer_t* MouseEvent_To_NetMessage(const mouseEvent_t *me)
{
        arBuffer_t *buf = NULL;
        snObject_t *obj = NULL;
        AR_ASSERT(me != NULL);
        
        obj = SN_CreateObject(SN_DICT_T);
        
        SN_InsertToDictObjectByStrInt(obj, WI_EVENT_NAME, WI_MOUSE_EVENT_T);
        SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_EVENT_TYPE, me->t);

        if(me->t == WI_MOUSEWHEEL || me->t == WI_MOUSEHWHEEL)
        {
                SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_DATA, me->data);
        }else
        {
                SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_X, me->x);
                SN_InsertToDictObjectByStrInt(obj, WI_MOUSE_Y, me->y);
        }
       
        buf = AR_CreateBuffer(128);
        SN_PutObject(buf, obj);
        
        SN_DestroyObject(obj);
        obj = NULL;
        
        return buf;
        
        
        
}


/*
 #define WI_EVENT_NAME           "Event"
 #define WI_MOUSE_EVENT_TYPE     "TP"
 #define WI_MOUSE_X              "X"
 #define WI_MOUSE_Y              "Y"
 #define WI_MOUSE_DATA           "D"
 */

arStatus_t  NetMessage_To_MouseEvent(mouseEvent_t *me, snObject_t *obj)
{
        snObject_t *val = NULL;
        AR_ASSERT(me != NULL && obj != NULL);
        
        AR_memset(me, 0, sizeof(*me));
        val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_EVENT_TYPE);
        
        if(val == NULL)
        {
                return AR_E_INVAL;
        }
        
        me->t = SN_GetIntObject(val);
        
        if(me->t == WI_MOUSEWHEEL  || me->t == WI_MOUSEHWHEEL)
        {
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_DATA);
                if(val == NULL)
                {
                        return AR_E_INVAL;
                }
                
                me->data = SN_GetIntObject(val);
        }else
        {
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_X);
                if(val == NULL)
                {
                        return AR_E_INVAL;
                }
                me->x = SN_GetIntObject(val);
                
                val = SN_FindFromDictObjectByStr(obj, WI_MOUSE_Y);
                if(val == NULL)
                {
                        return AR_E_INVAL;
                }
                
                me->y = SN_GetIntObject(val);
        }
        
        
        return AR_S_YES;
}




