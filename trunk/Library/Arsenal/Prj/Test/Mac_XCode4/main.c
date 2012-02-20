//
//  main.c
//  Test
//
//  Created by peng liu on 2/13/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#include "Arsenal.h"

#include <stdio.h>




int main (int argc, const char * argv[])
{

        // insert code here...
        printf("Hello, World!\n");
        
        Arsenal_Init(NULL);
        getchar();
        
        Arsenal_UnInit(NULL);
        return 0;
}

