//
//  NetMessage.c
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#include "NetMessage.h"



/*
#define WI_EVENT_NAME           "Event"
#define WI_MOUSE_EVENT_TYPE     "TP"
#define WI_MOUSE_X              "X"
#define WI_MOUSE_Y              "Y"
#define WI_MOUSE_DATA           "D"
*/

arBuffer_t* MouseEvent_To_NetMessage(const mouseEvent_t *me)
{
        arBuffer_t *buf = NULL;
        
        snObject_t *obj = NULL, *key = NULL, *val = NULL;

        obj = SN_CreateObject(SN_DICT_T);
        buf = AR_CreateBuffer(1024);
        
        key = SN_CreateObject(SN_STRING_T);
        val = SN_CreateObject(SN_INT_T);
        
        
        SN_SetStringObjectByStr(key, WI_EVENT_NAME);
        SN_SetIntObject(val, WI_MOUSE_EVENT_T);
        
        
        SN_InsertToDictObject(obj, key, val);
        
        
        SN_DestroyObject(obj);
        obj = NULL;
        return buf;
        
        
        
}


arStatus_t  NetMessage_To_MouseEvent(mouseEvent_t *me, const arBuffer_t *input)
{
        
}

