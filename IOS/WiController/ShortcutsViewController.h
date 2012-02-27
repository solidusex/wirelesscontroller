//
//  ShortcutsViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>



@class    ShortcutsViewController;


@protocol ShortcutsViewControllerDelegate<NSObject>

-(void)shortcutsReturnToMainFrame : (ShortcutsViewController*)controller;

@end




@interface ShortcutsViewController : UIViewController


@property(nonatomic, assign)    id<ShortcutsViewControllerDelegate>         delegate;


-(IBAction)returnToMainFrame : (id)sender;


@end
