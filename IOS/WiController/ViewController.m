//
//  ViewController.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//


#import "ViewController.h"

@implementation ViewController
@synthesize ipText;
@synthesize pwdText;





- (BOOL)textViewShouldBeginEditing:(UITextView *)aTextView 
{
        return YES;
}


- (BOOL)textViewShouldEndEditing:(UITextView *)aTextView 
{
        [aTextView resignFirstResponder];
        return YES;
}


- (void)keyboardWillShow:(NSNotification *)notification {
        
        /*
         Reduce the size of the text view so that it's not obscured by the keyboard.
         Animate the resize so that it's in sync with the appearance of the keyboard.
         */
        
        NSDictionary *userInfo = [notification userInfo];
        
        // Get the origin of the keyboard when it's displayed.
        NSValue* aValue = [userInfo objectForKey:UIKeyboardFrameEndUserInfoKey];
        
        // Get the top of the keyboard as the y coordinate of its origin in self's view's coordinate system. The bottom of the text view's frame should align with the top of the keyboard's final position.
        CGRect keyboardRect = [aValue CGRectValue];
        keyboardRect = [self.view convertRect:keyboardRect fromView:nil];
        
        CGFloat keyboardTop = keyboardRect.origin.y;
        CGRect newTextViewFrame = self.view.bounds;
        newTextViewFrame.size.height = keyboardTop - self.view.bounds.origin.y;
        
        // Get the duration of the animation.
        NSValue *animationDurationValue = [userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey];
        NSTimeInterval animationDuration;
        [animationDurationValue getValue:&animationDuration];
        
        // Animate the resize of the text view's frame in sync with the keyboard's appearance.
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:animationDuration];
        
        //textView.frame = newTextViewFrame;
        
        [UIView commitAnimations];
}


- (void)keyboardWillHide:(NSNotification *)notification {
        
        NSDictionary* userInfo = [notification userInfo];
        
        /*
         Restore the size of the text view (fill self's view).
         Animate the resize so that it's in sync with the disappearance of the keyboard.
         */
        NSValue *animationDurationValue = [userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey];
        NSTimeInterval animationDuration;
        [animationDurationValue getValue:&animationDuration];
        
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:animationDuration];
        
        //textView.frame = self.view.bounds;
        
        [UIView commitAnimations];
}






- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
        [super viewDidLoad];
        
        // Do any additional setup after loading the view, typically from a nib.
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
        
        self.ipText.delegate = self;
        self.pwdText.delegate = self;
}

- (void)viewDidUnload
{
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
        
        self.ipText.delegate = nil;
        self.pwdText.delegate = nil;
        
        [self setIpText:nil];
        [self setPwdText:nil];
        [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
        
        

}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
        return (interfaceOrientation == UIInterfaceOrientationPortrait);
}





-(IBAction) backgroundTap : (id)sender
{
        [ipText resignFirstResponder];
        [pwdText resignFirstResponder];
}



- (void)dealloc {
        [ipText release];
        [pwdText release];
        [super dealloc];
}



-(void)mouseReturnToMainFrame : (MouseViewController*)controller
{
        
        [self dismissViewControllerAnimated : YES
                                 completion : nil
         ];

}

-(void)keyboardReturnToMainFrame : (KeyboardViewController*)controller
{
        [self dismissViewControllerAnimated : YES
                                 completion : nil
         ];

}

-(void)shortcutsReturnToMainFrame : (ShortcutsViewController*)controller
{
        [self dismissViewControllerAnimated : YES
                                 completion : nil
         ];

}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
        if ([segue.identifier isEqualToString:@"TransmitToMouseView"])
        {
                MouseViewController *view = segue.destinationViewController;
                view.delegate = self;
        }
        
        if([segue.identifier isEqualToString : @"TransmitToKeyboardView"])
        {
                KeyboardViewController *view = segue.destinationViewController;
                view.delegate = self;
        }
        
        
        if([segue.identifier isEqualToString : @"TransmitToShortcutsView"])
        {
                ShortcutsViewController *view = segue.destinationViewController;
                view.delegate = self;
        }

}



-(void)onMouseEvent           :  (const mouseNetMsg_t*)event
{
        NSLog(@"event == %d : (%g,%g), data = %g", event->t, event->x,event->y, event->data);
        
}



@end
