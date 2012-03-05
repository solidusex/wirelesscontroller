//
//  AppDelegate.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Reachability.h"
#include "stdhdr.h"


#define PREFS_PORT              @"port"
#define PREFS_AUTODISCOVERY     @"auto_discovery"
#define PREFS_IPSTART           @"ip_start"
#define PREFS_IPSTOP            @"ip_stop"


@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
        
}

@property (retain, nonatomic) UIWindow *window;



@end
