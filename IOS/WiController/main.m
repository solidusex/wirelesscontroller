//
//  main.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AppDelegate.h"

int main(int argc, char *argv[])
{
        
        NSAutoreleasePool *pool = [NSAutoreleasePool new];
        
        int ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
        
        [pool drain];
        
        return ret;
}
