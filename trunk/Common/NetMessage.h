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
        WI_MOUSEMOVE    =       0x0200,
        WI_LBUTTONDOWN  =       0x0201,
        WI_LBUTTONUP    =       0x0202,
        WI_LBUTTONDBLCLK=       0x0203,
        WI_RBUTTONDOWN  =       0x0204,
        WI_RBUTTONUP    =       0x0205,
        WI_RBUTTONDBLCLK=       0x0206,
        WI_MBUTTONDOWN  =       0x0207,
        WI_MBUTTONUP    =       0x0208,
        WI_MBUTTONDBLCLK=       0x0209,
        WI_MOUSEWHEEL   =       0x020A,
        WI_MOUSEHWHEEL  =       0x020E
}wiMouseEventType_t;

typedef struct __mouse_net_message_tag
{
        wiMouseEventType_t  t;
        float               x;
        float               y;
        float               data;
}mouseNetMsg_t;











#endif




