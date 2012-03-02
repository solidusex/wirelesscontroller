//
//  MouseViewController.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "MouseUIView.h"
#import "MouseViewController.h"

@implementation MouseViewController

@synthesize     delegate;
@synthesize mouseUIView;


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




//Implement viewDidLoad to do additional setup after loading the view, typically from a nib.

- (void)viewDidLoad
{
        [super viewDidLoad];
 
        mouseUIView.delegate = self;
        
}


-(void)viewDidUnload
{
        
        
       
        [self setMouseUIView:nil];
        [super viewDidUnload];
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
        mouseEvent_t msg;
        mouseUIView.middleIsPressed = YES;
        
        
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_MBUTTONDOWN;
        [self.delegate onMouseEvent : &msg];

        
}

-(IBAction)middleButtonUpInside : (id)sender
{
        mouseEvent_t msg;
        mouseUIView.middleIsPressed = NO;
        
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_MBUTTONUP;
        [self.delegate onMouseEvent : &msg];
        
}

-(IBAction)middleButtonUpOutside : (id)sender
{
        mouseEvent_t msg;
        mouseUIView.middleIsPressed = NO;
        
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_MBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}



-(IBAction)leftButtonDown       :  (id)sender
{
        mouseEvent_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_LBUTTONDOWN;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)leftButtonUpInside   :  (id)sender
{
        mouseEvent_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_LBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)leftButtonUpOutside  :  (id)sender
{
        mouseEvent_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_LBUTTONUP;
        [self.delegate onMouseEvent : &msg]; 
}


-(IBAction)rightButtonDown       :  (id)sender
{
        mouseEvent_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_RBUTTONDOWN;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)rightButtonUpInside   :  (id)sender
{
        mouseEvent_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_RBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}

-(IBAction)rightButtonUpOutside  :  (id)sender
{
        mouseEvent_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.t = WI_RBUTTONUP;
        [self.delegate onMouseEvent : &msg];
}



-(void)onMouseEvent           :  (const mouseEvent_t*)event;
{
        assert(event != NULL);
        [self.delegate onMouseEvent : event];
}




- (void)dealloc {
        [mouseUIView release];
        [super dealloc];
}
@end
