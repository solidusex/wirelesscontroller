//
//  KeyboardViewController.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "KeyboardViewController.h"

@implementation KeyboardViewController

@synthesize delegate;
@synthesize standardInputText;





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



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
        self.standardInputText.delegate = self;
        
        [self.standardInputText becomeFirstResponder];
        [super viewDidLoad];
}


- (void)viewDidUnload
{
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
        
        self.standardInputText.delegate = nil;
        
        [self setStandardInputText:nil];
        
        [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
        return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}


-(IBAction)returnToMainFrame : (id)sender
{
        [self backgroundTap : self];
        [self.delegate keyboardReturnToMainFrame : self];
}


-(IBAction) backgroundTap : (id)sender
{
        //[self.standardInputText resignFirstResponder];
}

- (void)dealloc {
        [standardInputText release];
        [super dealloc];
}


- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
        
        return YES;
}

@end
