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
        -(float)        getMouseAccelerate;
        -(BOOL)         isScrollMode;
@end


@interface MouseUIView : UIView
{
        BOOL    touchesBegan;
        CGPoint lastLocation;
        NSMutableArray  *points;
        
        UITapGestureRecognizer  *single_click;
        UITapGestureRecognizer  *double_click;
        
        
}

@property(nonatomic, assign) id<MouseUIViewDelegate>            delegate;


@end
