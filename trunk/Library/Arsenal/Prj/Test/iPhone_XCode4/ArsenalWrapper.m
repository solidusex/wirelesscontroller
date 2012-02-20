//
//  ArsenalWrapper.cpp
//  Test
//
//  Created by peng liu on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//


#include "ArsenalWrapper.h"

//using namespace ARSpace;



/************************************************************************************************************************/


static void AR_STDCALL tiny_error(int_t level, const wchar_t* msg, void *ctx)
{
        wprintf(L"%ls\r\n", msg);
}

static void AR_STDCALL tiny_printf(const wchar_t *msg, void *ctx)
{
		
        wprintf(L"%ls\r\n", msg);
		
		
}



void    Initialize_Arsenal()
{
        
        arInit_t ai = {{tiny_error, tiny_printf, NULL}};
		
        if(Arsenal_Init(&ai) != AR_S_YES)
        {
                abort();
        }
        
}

void    UnInitialize_Arsenal()
{
        Arsenal_UnInit();
}