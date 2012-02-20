//
//  main.m
//  Test
//
//  Created by liu peng on 8/18/11.
//  Copyright 2011 none. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Arsenal.h"







static void AR_STDCALL tiny_error(int_t level, const wchar_t* msg, void *ctx)
{
		
        wprintf(L"%ls\r\n", msg);
		
		
	
}

static void AR_STDCALL tiny_printf(const wchar_t *msg, void *ctx)
{
		
        wprintf(L"%ls\r\n", msg);
		
		
		
}




void  Test_Arsenal()
{
		
		setlocale(LC_ALL, "");
		
        arInit_t ai = {{tiny_error, tiny_printf, NULL}};
		
        Arsenal_Init(&ai);
		
		
		Arsenal_UnInit();
		
}



int main(int argc, char *argv[]) {
    

		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		
		Test_Arsenal();
		
		int retVal = UIApplicationMain(argc, argv, nil, nil);
		[pool release];
		return retVal;
}
