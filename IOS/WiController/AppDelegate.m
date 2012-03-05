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





- (void)setupByPreferences
{
        NSString *testValue = [[NSUserDefaults standardUserDefaults] stringForKey:PREFS_PORT];
        
        if (testValue == nil)
        {
                NSString *pathStr = [[NSBundle mainBundle] bundlePath];
                NSString *settingsBundlePath = [pathStr stringByAppendingPathComponent:@"Settings.bundle"];
                NSString *finalPath = [settingsBundlePath stringByAppendingPathComponent:@"Root.plist"];
                
                NSDictionary *settingsDict = [NSDictionary dictionaryWithContentsOfFile:finalPath];
                NSArray *prefSpecifierArray = [settingsDict objectForKey:@"PreferenceSpecifiers"];
                
                
                NSString *port = nil;
                NSString *auto_discovery = nil;
                NSString *ip_start = @"192.168.0.0";
                NSString *ip_stop = @"192.168.255.255";
                
                
                NSDictionary *prefItem;
                for (prefItem in prefSpecifierArray)
                {
                        WI_LOG(@"%@", prefItem);
                        
                        NSString *key = [prefItem objectForKey:@"Key"];
                        NSString *defaultValue = [prefItem objectForKey:@"DefaultValue"];

                        
                        if ([key isEqualToString:PREFS_PORT])
                        {
                                port = defaultValue;
                        }
                        else if ([key isEqualToString:PREFS_AUTODISCOVERY])
                        {
                                auto_discovery = defaultValue;
                        }
                        else if ([key isEqualToString:PREFS_IPSTART])
                        {
                                ip_start = defaultValue;
                        }
                        else if ([key isEqualToString:PREFS_IPSTOP])
                        {
                                ip_stop = defaultValue;
                        }
                }
                

                // since no default values have been set (i.e. no preferences file created), create it here		
                NSDictionary *appDefaults = [NSDictionary dictionaryWithObjectsAndKeys:
                                             port, PREFS_PORT,
                                             auto_discovery, PREFS_AUTODISCOVERY,
                                             ip_start, PREFS_IPSTART,
                                             ip_stop, PREFS_IPSTOP,
                                             nil];
                
                [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaults];
                [[NSUserDefaults standardUserDefaults] synchronize];
               
        }
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
        
    // Override point for customization after application launch.
        [ArsenalWrapper instance];
        
        [self setupByPreferences];
        
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
        
        [ArsenalWrapper unInstance];

}

@end
