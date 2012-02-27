//
//  MouseViewController.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "MouseViewController.h"

@implementation MouseViewController

@synthesize     delegate;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
}
*/

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
        
        middleIsPressed = NO;
        touchesBegan = NO;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}




-(IBAction)returnToMainFrame : (id)sender
{
        [self.delegate mouseReturnToMainFrame : self];
}




-(IBAction)middleButtonDown : (id)sender
{
        mouseNetMsg_t msg;
        middleIsPressed = YES;
        
        
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_MBUTTONDOWN;
        [self.delegate onMouseEvent : &msg];

        
}

-(IBAction)middleButtonUpInside : (id)sender
{
        mouseNetMsg_t msg;
        middleIsPressed = NO;
        
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_MBUTTONUP;
        [self.delegate onMouseEvent : &msg];
        
}

-(IBAction)middleButtonUpOutside : (id)sender
{
        mouseNetMsg_t msg;
        middleIsPressed = NO;
        
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_MBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}



-(IBAction)leftButtonDown       :  (id)sender
{
        mouseNetMsg_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_LBUTTONDOWN;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)leftButtonUpInside   :  (id)sender
{
        mouseNetMsg_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_LBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)leftButtonUpOutside  :  (id)sender
{
        mouseNetMsg_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_LBUTTONUP;
        [self.delegate onMouseEvent : &msg]; 
}


-(IBAction)rightButtonDown       :  (id)sender
{
        mouseNetMsg_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_RBUTTONDOWN;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)rightButtonUpInside   :  (id)sender
{
        mouseNetMsg_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_RBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)rightButtonUpOutside  :  (id)sender
{
        mouseNetMsg_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_RBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}


/*************************Touches*******************************/

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
        NSLog(@"touchesBegan");
        
        touchesBegan = YES;

        UITouch *touch = [touches anyObject];
        if(touch != nil)
        {
                CGPoint beg = [touch locationInView : self.view];
                lastLocation = beg;
        }
}



- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
        NSLog(@"touchesEnded");
        touchesBegan = NO;
        
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
        NSLog(@"touchesCancelled");
        touchesBegan = NO;
}


-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
        mouseNetMsg_t msg;
        
        UITouch *touch = [touches anyObject];
        if(touch == nil)
        {
                return;
        }
        
        CGPoint location = [touch locationInView : self.view];
        
        CGFloat  x,y;
        
        x = location.x - lastLocation.x;
        y = location.y - lastLocation.y;
        
        if(middleIsPressed)
        {
                if(y != 0.0)
                {
                        msg.t = WI_MOUSEWHEEL;
                        msg.data = y;
                }if(x != 0.0)
                {
                        msg.t = WI_MOUSEHWHEEL;
                        msg.data = x;
                }else
                {
                        return;
                }
                
                msg.x = msg.y = 0.0;
                
        }else
        {
                msg.t = WI_MOUSEMOVE;
                msg.x = x;
                msg.y = y;
                msg.data = 0.0;
        }
        
        [self.delegate onMouseEvent : &msg];
        
}







@end
