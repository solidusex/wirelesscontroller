//
//  ArsenalWrapper.h
//  WiController
//
//  Created by solidus on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//


#include "Arsenal.h"



@interface ArsenalWrapper : NSObject


+(void)instance;
+(void)unInstance;


-(id)init;
-(void)dealloc;
-(void)onPrint : (NSString*) msg;
-(void)onError : (int)level  Msg : (NSString*)msg;


@end
