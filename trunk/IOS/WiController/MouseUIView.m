//
//  MouseUIView.m
//  WiController
//
//  Created by  on 2/28/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "MouseUIView.h"

@implementation MouseUIView

@synthesize delegate;


- (void)onSingleClick:(UITapGestureRecognizer *)sender
{
        if(sender.state == UIGestureRecognizerStateEnded)
        {
                WI_LOG(@"On single click");
                
                mouseEvent_t msg;
                memset(&msg, 0, sizeof(msg));
                msg.t = WI_LBUTTONSGLCLK;
                [self.delegate onMouseEvent : &msg];

        }
}

- (void)onDoubleClick:(UITapGestureRecognizer *)sender
{
        if (sender.state == UIGestureRecognizerStateEnded)
        {
               WI_LOG(@"On double click");
               mouseEvent_t msg;
               memset(&msg, 0, sizeof(msg));
               msg.t = WI_LBUTTONDBLCLK;
               [self.delegate onMouseEvent : &msg];

        }
}


- (void)scroll_lock_click:(UITapGestureRecognizer *)sender
{
        if (sender.state == UIGestureRecognizerStateEnded)
        {
                WI_LOG(@"scroll_lock_click");
                
                is_scroll_mode = !is_scroll_mode;
                
        }
}


-(void)perform_rotated:(UIRotationGestureRecognizer *)sender
{
        float degrees = sender.rotation*(180/M_PI);
        WI_LOG(@"rotation degrees == %g", degrees);
        
        if(degrees < -75.0)
        {
                [self.delegate returnToMainFrame : self];
        }
        
}



-(void) return_to_main_gesture : (UISwipeGestureRecognizer*)sender
{
        WI_LOG(@"%@", sender);
        [self.delegate returnToMainFrame : self];
}


-(void)init_gesture_recognizer
{
        single_click = [ [UITapGestureRecognizer alloc] initWithTarget : self
                                                                action : @selector(onSingleClick:)
                        ];
        double_click = [ [UITapGestureRecognizer alloc] initWithTarget : self
                                                                action : @selector(onDoubleClick:)
                        ];
        
        
        single_click.numberOfTapsRequired = 1;
        single_click.numberOfTouchesRequired = 1;
        
        double_click.numberOfTapsRequired = 2;
        double_click.numberOfTouchesRequired = 1;
        
        
        [single_click requireGestureRecognizerToFail:double_click];

        
       // [self addGestureRecognizer : single_click];
       // [self addGestureRecognizer : double_click];
        
        
        
        
        
        return_recognizer =[[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(return_to_main_gesture:)];
        
        return_recognizer.numberOfTouchesRequired = 2;
        return_recognizer.direction = UISwipeGestureRecognizerDirectionLeft;
        [self addGestureRecognizer:return_recognizer];
        

        
        scroll_mode_recognizer = [ [UITapGestureRecognizer alloc] initWithTarget : self
                                                                         action : @selector(scroll_lock_click:)
                                 ];
        
        scroll_mode_recognizer.numberOfTapsRequired = 2;
        scroll_mode_recognizer.numberOfTouchesRequired = 2;
        
        [self addGestureRecognizer:scroll_mode_recognizer];
        
}

-(void)uninit_gesture_recognizer
{
        //[self removeGestureRecognizer : single_click];
        //[self removeGestureRecognizer : double_click];
        
        [self removeGestureRecognizer : return_recognizer];
        [self removeGestureRecognizer : scroll_mode_recognizer];
        
        [scroll_mode_recognizer release];
        scroll_mode_recognizer = nil;
        
        
        [return_recognizer release];
        return_recognizer = nil;
        
        [single_click release];
        single_click = nil;
        
        [double_click release];
        double_click = nil;
}


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) 
    {
            [self init_gesture_recognizer];
            is_scroll_mode = NO;
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder
{
        self = [super initWithCoder : decoder];
        if(self)
        {
                [self init_gesture_recognizer];
                points = [NSMutableArray array];
                [points retain];
                is_scroll_mode = NO;

        }
        return self;
}

-(void)dealloc
{
       
        [super dealloc];
        
        [self uninit_gesture_recognizer];
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




/*************************Touches*******************************/

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
        WI_LOG(@"touchesBegan");
        
        touchesBegan = YES;
        
        [points removeAllObjects];
        
        UITouch *touch = [touches anyObject];
        if(touch != nil)
        {
                CGPoint beg = [touch locationInView : self];
                lastLocation = beg;
        }
        
        [points addObject : [NSValue valueWithCGPoint : lastLocation]];
        
}




- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
        WI_LOG(@"touchesEnded");
        touchesBegan = NO;
        
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
        WI_LOG(@"touchesCancelled");
        touchesBegan = NO;
}







-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
        mouseEvent_t msg;
        
        UITouch *touch = [touches anyObject];
        if(touch == nil)
        {
                return;
        }
        
        CGPoint location = [touch locationInView : self];
        
        CGFloat  x,y;
        
        x = location.x - lastLocation.x;
        y = location.y - lastLocation.y;
        
        
        if(is_scroll_mode)
        {
                if(AR_abs_flt(y) > AR_abs_flt(x))
                {
                        msg.t = WI_MOUSEWHEEL;
                        msg.data = -y * 2;
                        
                }else if(x != 0.0)
                {
                        msg.t = WI_MOUSEHWHEEL;
                        msg.data = -x * 2;
                }else
                {
                        return;
                }
                
                msg.x = msg.y = 0.0;
                
        }else
        {
                msg.t = WI_MOUSEMOVE;
                msg.x = x * [self.delegate getMouseAccelerate];
                msg.y = y * [self.delegate getMouseAccelerate];
                msg.data = 0.0;
        }
        
        lastLocation = location;
        
        
        
        /*如果位移太小了就不要了*/
        if(msg.t == WI_MOUSEWHEEL || msg.t == WI_MOUSEHWHEEL)
        {
                if((int)msg.data == 0)
                {
                        return;
                }
                
        }else if(msg.t == WI_MOUSEMOVE)
        {
                if((int)msg.x == 0 && (int)msg.y == 0)
                {
                        return;
                }
        }else
        {
                return;
        }
        
        [self.delegate onMouseEvent : &msg];
        
                
        if(points)
        {
                [points addObject : [NSValue valueWithCGPoint : lastLocation]];
                [self setNeedsDisplay];
        }
        
}















@end
