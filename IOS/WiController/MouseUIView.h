//
//  MouseUIView.h
//  WiController
//
//  Created by  on 2/28/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MouseUIView : UIView
{
        NSMutableArray  *_points;
}

@property(nonatomic, readwrite) NSMutableArray  *points;

@end
