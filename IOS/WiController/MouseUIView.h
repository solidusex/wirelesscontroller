//
//  MouseUIView.h
//  WiController
//
//  Created by solidus on 2/28/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdhdr.h"
#include "Arsenal.h"
#import "NetMessage.h"


@protocol MouseUIViewDelegate<NSObject>
        -(void)onMouseEvent      :  (const mouseEvent_t*)event;
        -(float)        getMouseAccelerate;
        -(void)returnToMainFrame : (id)sender;
@end


@interface MouseUIView : UIView
{
        BOOL    touchesBegan;
        CGPoint lastLocation;
        NSMutableArray  *points;
        
        UITapGestureRecognizer          *single_click;
        UITapGestureRecognizer          *double_click;
        
        UITapGestureRecognizer          *scroll_mode_recognizer;
        
        //UIRotationGestureRecognizer   *retrun_recognizer;
        UISwipeGestureRecognizer        *return_recognizer;
        BOOL                            is_scroll_mode;
        
}

@property(nonatomic, assign) id<MouseUIViewDelegate>            delegate;


@end
