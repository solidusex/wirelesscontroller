//
//  KeyboardViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdhdr.h"
#include "Arsenal.h"
#include "NetMessage.h"


@class    KeyboardViewController;


@protocol KeyboardViewControllerDelegate<NSObject>

-(void)keyboardReturnToMainFrame : (KeyboardViewController*)controller;
-(void)onKeyboardEvent : (const keyboardEvent_t*) ke;
@end





@interface KeyboardViewController : UIViewController<UITextFieldDelegate>

@property(nonatomic, assign)    id<KeyboardViewControllerDelegate>      delegate;

@property (retain, nonatomic) IBOutlet UITextField *standardInputText;


-(IBAction)returnToMainFrame : (id)sender;
-(IBAction) backgroundTap : (id)sender;


-(IBAction) functionKeyDown : (id)sender;
-(IBAction) functionKeyUp : (id)sender;


@end



