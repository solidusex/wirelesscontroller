//
//  NetMessage.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#ifndef WiController_NetMessage_h
#define WiController_NetMessage_h

#include "Arsenal.h"


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
        WI_MOUSEHWHEEL  =       0x000E
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


#define WI_EVENT_NAME           "Event"
#define WI_MOUSE_EVENT_TYPE     "TP"
#define WI_MOUSE_X              "X"
#define WI_MOUSE_Y              "Y"
#define WI_MOUSE_DATA           "D"


arBuffer_t* MouseEvent_To_NetMessage(const mouseEvent_t *me);
arStatus_t  NetMessage_To_MouseEvent(mouseEvent_t *me, const arBuffer_t *input);


arBuffer_t* KeyboardEvent_To_NetMessage(const mouseEvent_t *ke);
arBuffer_t* ShortcutsEvent_To_NetMessage(const mouseEvent_t *se);








#endif




