//
//  DiscoveryViewDelegate.h
//  WiController
//
//  Created by solidus on 3/5/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "stdhdr.h"
#import "ArsenalWrapper.h"
#import "NetMessage.h"

@interface DiscoveryViewDataSource :  NSObject<UITableViewDataSource>
{
        NSMutableArray         *_discovered;

        
        BOOL                    is_started;
        CFSocketRef             sock_handle;
        NSTimer                 *timer;

        BOOL                    wifi_is_enable;
        BOOL                    enable_auto_discovery;
        NSInteger               port;
        struct sockaddr_in      ip_beg;
        struct sockaddr_in      ip_end;
        arBuffer_t              *discovery_request_msg;
        
}

@property(nonatomic, readonly) NSMutableArray         *discovered;
@property(nonatomic, assign)  UITableView             *view;
@property(nonatomic, readonly) CFSocketRef             sock_handle;
-(void)start;
-(void)stop;
-(void)loadConfig;

-(void)loadContext;
-(void)saveContext;

@end
