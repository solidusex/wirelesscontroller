//
//  ArsenalWrapper.m
//  WiController
//
//  Created by solidus on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "ArsenalWrapper.h"
#import "NSString_Convert.h"







static void AR_STDCALL __g_on_error(int_t level, const wchar_t* msg, void *ctx)
{
        AR_ASSERT(ctx != NULL);
        AR_ASSERT(msg != NULL);

        ArsenalWrapper  *ar = (ArsenalWrapper*)ctx;
        
        
        [ar onError : level
                Msg : [NSString stringWithWideString : msg]
         ];
}

static void AR_STDCALL __g_on_print(const wchar_t *msg, void *ctx)
{
        AR_ASSERT(ctx != NULL);
        AR_ASSERT(msg != NULL);
        
        ArsenalWrapper  *ar = (ArsenalWrapper*)ctx;
        
        
        [ar onPrint : [NSString stringWithWideString : msg]  ];
		
}





static ArsenalWrapper   *__g_arsenal = NULL;
@implementation ArsenalWrapper

+(void)instance
{
        if(__g_arsenal == nil)
        {
                __g_arsenal = [[ArsenalWrapper alloc] init];
        
                if(__g_arsenal == nil)
                {
                        abort();
                }
        
                arInit_t ai = {{__g_on_error, __g_on_print, (void*)__g_arsenal}};
		
                if(Arsenal_Init(&ai) != AR_S_YES)
                {
                        [__g_arsenal dealloc];
                        abort();
                }
        }
        
}


+(void)unInstance
{
        if(__g_arsenal != nil)
        {
                Arsenal_UnInit();
                [__g_arsenal release];
        }
}






-(id)init
{
        if((self = [super init]) != nil)
        {
                
        }
        
        return self;
}

-(void)dealloc
{
        
        [super dealloc];
}



-(void)onPrint : (NSString*) msg
{
        NSLog(@"%@", msg);
}

-(void)onError : (int)level  Msg : (NSString*)msg
{
        NSLog(@"error level = %d, error msg = '%@'", level, msg);
}




@end


