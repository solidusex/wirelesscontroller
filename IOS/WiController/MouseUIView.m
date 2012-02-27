//
//  MouseUIView.m
//  WiController
//
//  Created by  on 2/28/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "MouseUIView.h"

@implementation MouseUIView

@synthesize points = points;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) 
    {
        }
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder
{
        self = [super initWithCoder : decoder];
        if(self)
        {
                points = [NSMutableArray array];
                [points retain];

        }
        return self;
}

-(void)dealloc
{
        [super dealloc];
        [points release];
        points = nil;
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
 

-(void)drawRect : (CGRect)rect
{
        if(points == nil || [points count] < 2)
        {
                return;
        }
        
        
        [[UIColor blackColor] set];
        
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSetLineWidth(context, 4.0f);
        
        for(int i = 0; i < (points.count -1); i++)
        {
                
                CGPoint pt1 = [ [points objectAtIndex : i] CGPointValue];
                CGPoint pt2 = [ [points objectAtIndex : i + 1] CGPointValue];
                
                CGContextMoveToPoint(context, pt1.x, pt1.y);
                CGContextAddLineToPoint(context, pt2.x, pt2.y);
                
                CGContextStrokePath(context);
                
        }
        
}



@end
