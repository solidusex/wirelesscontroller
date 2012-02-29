//
//  AppDelegate.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Reachability.h"


@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
        Reachability    *localWifiReachability;
        UIAlertView     *wifiAlertView;
        BOOL            isAlerted;
}

@property (retain, nonatomic) UIWindow *window;



@end
