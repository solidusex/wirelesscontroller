//
//  ArsenalWrapper.h
//  WiController
//
//  Created by solidus on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//


#include "Arsenal.h"
#include "stdhdr.h"


@interface ArsenalWrapper : NSObject
{
        wchar_t         *tmp;
}


+(void)instance;
+(void)unInstance;
+(ArsenalWrapper*)sharedArsenalWrapper;

-(id)init;
-(void)dealloc;
-(void)onPrint : (NSString*) msg;
-(void)onError : (int)level  Msg : (NSString*)msg;

-(const wchar_t*) stringConvertToWideString : (NSString*)str;

@end
