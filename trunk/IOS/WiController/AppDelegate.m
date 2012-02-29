//
//  AppDelegate.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "ArsenalWrapper.h"
#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window = _window;

- (void)dealloc
{
        [_window release];
        [super dealloc];
}



-(void)alertLocalWifiReachability
{
        if(isAlerted)
        {
                if([localWifiReachability currentReachabilityStatus] == ReachableViaWiFi)
                {
                        [wifiAlertView dismissWithClickedButtonIndex : 0 
                                                            animated : YES
                         ];
                        
                        [wifiAlertView release];
                        wifiAlertView = nil;
                        isAlerted = NO;

                }
        }else
        {   
                if([localWifiReachability currentReachabilityStatus] != ReachableViaWiFi)
                {
                        wifiAlertView  = [[UIAlertView alloc] initWithTitle : @"Warning"
                                                                     message: @"Wifi disabled" 
                                                                    delegate: nil 
                                                           cancelButtonTitle: nil 
                                                           otherButtonTitles: nil
                                          ];
                        
                        [wifiAlertView show];
                        isAlerted = YES;
                }
        }
}



- (void) reachabilityChanged: (NSNotification* )note
{
        Reachability* curReach = [note object];
        NSParameterAssert([curReach isKindOfClass: [Reachability class]]);
        
        if(curReach == localWifiReachability)
        {
                [self alertLocalWifiReachability];
        }
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
        
    // Override point for customization after application launch.
        [ArsenalWrapper instance];
        
        isAlerted = NO;
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(reachabilityChanged:) name: kReachabilityChangedNotification object: nil];
        
        localWifiReachability = [Reachability reachabilityForLocalWiFi];
        [localWifiReachability retain];
        [localWifiReachability startNotifier];
        
        [self alertLocalWifiReachability];
        
        return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
        /*
         Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
         Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
         */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
        /*
         Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
         If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
         */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
        /*
         Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
         */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
        /*
         Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
         */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
        /*
         Called when the application is about to terminate.
         Save data if appropriate.
         See also applicationDidEnterBackground:.
         */
        [localWifiReachability stopNotifier];
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [localWifiReachability release];
        [ArsenalWrapper unInstance];

}

@end
