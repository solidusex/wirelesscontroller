//
//  ArsenalWrapper.h
//  WiController
//
//  Created by solidus on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <CFNetwork/CFNetwork.h>
#import <arpa/inet.h>
#import <fcntl.h>
#import <ifaddrs.h>
#import <netdb.h>
#import <net/if.h>
#import <sys/socket.h>
#import <sys/types.h>
#import <arpa/inet.h>		// for IPPROTO_TCP
#include <netinet/tcp.h>	// for TCP_NODELAY

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

-(BOOL) addIPV4Address : (struct sockaddr_in*)addr;
-(NSInteger)compareIPV4Address : (const struct sockaddr_in*)l with : (const struct sockaddr_in*)r;


-(const wchar_t*) stringConvertToWideString : (NSString*)str;

@end
