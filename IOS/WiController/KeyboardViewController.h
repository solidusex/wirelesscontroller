//
//  KeyboardViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>



@class    KeyboardViewController;


@protocol KeyboardViewControllerDelegate<NSObject>

-(void)keyboardReturnToMainFrame : (KeyboardViewController*)controller;

@end





@interface KeyboardViewController : UIViewController<UITextFieldDelegate>

@property(nonatomic, assign)    id<KeyboardViewControllerDelegate>      delegate;

@property (retain, nonatomic) IBOutlet UITextField *standardInputText;


-(IBAction)returnToMainFrame : (id)sender;
-(IBAction)closeKeyboard     : (id)sender;

@end



