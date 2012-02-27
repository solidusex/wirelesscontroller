//
//  ViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "MouseViewController.h"
#import "KeyboardViewController.h"
#import "ShortcutsViewController.h"



@interface ViewController : UIViewController<MouseViewControllerDelegate, KeyboardViewControllerDelegate, ShortcutsViewControllerDelegate, UITextFieldDelegate>

@property (retain, nonatomic) IBOutlet UITextField *ipText;

@property (retain, nonatomic) IBOutlet UITextField *pwdText;

-(IBAction) backgroundTap : (id)sender;




@end
