//
//  MouseViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>

@class    MouseViewController;

@protocol MouseViewControllerDelegate<NSObject>

-(void)mouseReturnToMainFrame : (MouseViewController*)controller;

@end



@interface MouseViewController : UIViewController

@property(nonatomic, assign)    id<MouseViewControllerDelegate>         delegate;

-(IBAction)returnToMainFrame : (id)sender;

@end
