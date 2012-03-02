//
//  MouseUIView.h
//  WiController
//
//  Created by  on 2/28/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdhdr.h"
#include "Arsenal.h"
#import "NetMessage.h"


@protocol MouseUIViewDelegate<NSObject>
        -(void)onMouseEvent      :  (const mouseEvent_t*)event;
@end


@interface MouseUIView : UIView
{
        BOOL    middleIsPressed;
        BOOL    touchesBegan;
        CGPoint lastLocation;
        NSMutableArray  *points;
        
        UITapGestureRecognizer  *single_click;
        UITapGestureRecognizer  *double_click;
        
}

@property(nonatomic, readwrite) BOOL                            middleIsPressed;
@property(nonatomic, assign) id<MouseUIViewDelegate>         delegate;

@end
