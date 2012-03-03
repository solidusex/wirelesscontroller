//
//  MouseViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MouseUIView.h>

#include "stdhdr.h"
#include "Arsenal.h"
#import "NetMessage.h"

@class    MouseViewController;

@protocol MouseViewControllerDelegate<NSObject>

-(void)mouseReturnToMainFrame : (MouseViewController*)controller;
-(void)onMouseEvent           :  (const mouseEvent_t*)event;

@end



@interface MouseViewController : UIViewController<MouseUIViewDelegate>
{
        
        double  mouse_accelerate;
        BOOL    is_scroll_mode;

}

@property(nonatomic, assign)    id<MouseViewControllerDelegate>         delegate;
@property (retain, nonatomic) IBOutlet MouseUIView *mouseUIView;

-(IBAction)returnToMainFrame : (id)sender;

-(IBAction)middleButtonDown : (id)sender;
-(IBAction)middleButtonUpInside : (id)sender;
-(IBAction)middleButtonUpOutside : (id)sender;


-(IBAction)leftButtonDown       :  (id)sender;
-(IBAction)leftButtonUpInside   :  (id)sender;
-(IBAction)leftButtonUpOutside  :  (id)sender;


-(IBAction)rightButtonDown       :  (id)sender;
-(IBAction)rightButtonUpInside   :  (id)sender;
-(IBAction)rightButtonUpOutside  :  (id)sender;



-(IBAction)  mouseAccelerateChanged : (id)sender;


-(float)  getMouseAccelerate;
-(BOOL)   isScrollMode;
@end
