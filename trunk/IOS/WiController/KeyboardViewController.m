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



/*
 WI_FUNCTION_KEY_T,
 WI_FUNCTION_ASCII_KEY_T,
 WI_FUNCTION_TEXT_T
 }wiKeyboardEventType_t;
 
 typedef enum
 {
 WI_KEY_FUNC_ESC_UP    =       0x0000,
 
   =       0x0001,
 WI_KEY_FUNC_CMD_UP    =       0x0002,
 
   =       0x0003,
 WI_KEY_FUNC_CTRL_UP    =       0x0004,
 
   =       0x0005,
 WI_KEY_FUNC_TAB_UP    =       0x0006,
 
   =       0x0007,
 WI_KEY_FUNC_SHIFT_UP    =       0x0008,
 
   =       0x0007,
 WI_KEY_FUNC_DELETE_UP    =       0x0008,
 
   =       0x0007,
 WI_KEY_FUNC_INSERT_UP    =       0x0008,
 
   =       0x0009,
 WI_KEY_FUNC_HOME_UP    =       0x000A,
 
   =       0x000B,
 WI_KEY_FUNC_END_UP    =       0x000C,
 
   =     0x000D,
 WI_KEY_FUNC_PAGEDOWN_UP    =     0x000E,
 
   =       0x000F,
 WI_KEY_FUNC_PAGEUP_UP    =       0x0010,
 
   =       0x0011,
 WI_KEY_FUNC_UP_UP    =       0x0012,
   =       0x0013,
 WI_KEY_FUNC_DOWN_UP    =       0x0014,
   =       0x0015,
 WI_KEY_FUNC_LEFT_UP    =       0x0016,
   =       0x0017,
 WI_KEY_FUNC_RIGHT_UP    =       0x0018,
 
   =       0x0019,
 WI_KEY_FUNC_BACKSPACE_UP    =       0x001A,
 
   =       0x001B,
 WI_KEY_FUNC_ALT_UP    =       0x001C,

 */
-(IBAction) functionKeyDown : (id)sender
{
        NSString *key = ((UIButton*)sender).titleLabel.text;
        WI_LOG(@"%@ keydown", ((UIButton*)sender).titleLabel.text);
        
        keyboardEvent_t ke;
        ke.type = WI_FUNCTION_KEY_T;
        
        if([key compare : @"ESC"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_ESC_DONW;
                
        }else if([key compare : @"Home"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_HOME_DONW;
        }else if([key compare : @"Page Up"] == NSOrderedSame)
        {
                ke.func_key =WI_KEY_FUNC_PAGEUP_DONW;

        }else if([key compare : @"Page Down"] == NSOrderedSame)
        {
                ke.func_key =   WI_KEY_FUNC_PAGEDOWN_DONW;

                
        }else if([key compare : @"End"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_END_DONW;
                
        }else if([key compare : @"Delete"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_DELETE_DONW;
                
        }else if([key compare : @"Tab"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_TAB_DONW;
                
        }else if([key compare : @"Shift"] == NSOrderedSame)
        {
                ke.func_key =   WI_KEY_FUNC_SHIFT_DONW;
                
        }else if([key compare : @"Insert"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_INSERT_DONW;
                
        }else if([key compare : @"Backspace"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_BACKSPACE_DONW;
                
        }else if([key compare : @"Cmd"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_CMD_DONW;
                
        }else if([key compare : @"Alt"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_ALT_DONW;
                
        }else if([key compare : @"Ctrl"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_CTRL_DONW;
                
        }else if([key compare : @"Up"] == NSOrderedSame)
        {
                ke.func_key =   WI_KEY_FUNC_UP_DONW;
                
        }else if([key compare : @"Down"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_DOWN_DONW;
        }else if([key compare : @"Left"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_LEFT_DONW;
        }else if([key compare : @"Right"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_RIGHT_DONW;
        }else
        {
                return;
        }
        
        [self.delegate onKeyboardEvent : &ke];
}

-(IBAction) functionKeyUp : (id)sender
{
        NSString *key = ((UIButton*)sender).titleLabel.text;
        
        WI_LOG(@"%@ keyup", ((UIButton*)sender).titleLabel.text);
        
        keyboardEvent_t ke;
        
        ke.type = WI_FUNCTION_KEY_T;
        
        if([key compare : @"ESC"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_ESC_UP;
                
        }else if([key compare : @"Home"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_HOME_UP;
        }else if([key compare : @"Page Up"] == NSOrderedSame)
        {
                ke.func_key =WI_KEY_FUNC_PAGEUP_UP;
                
        }else if([key compare : @"Page Down"] == NSOrderedSame)
        {
                ke.func_key =   WI_KEY_FUNC_PAGEDOWN_UP;
                
                
        }else if([key compare : @"End"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_END_UP;
                
        }else if([key compare : @"Delete"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_DELETE_UP;
                
        }else if([key compare : @"Tab"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_TAB_UP;
                
        }else if([key compare : @"Shift"] == NSOrderedSame)
        {
                ke.func_key =   WI_KEY_FUNC_SHIFT_UP;
                
        }else if([key compare : @"Insert"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_INSERT_UP;
                
        }else if([key compare : @"Backspace"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_BACKSPACE_UP;
                
        }else if([key compare : @"Cmd"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_CMD_UP;
                
        }else if([key compare : @"Alt"] == NSOrderedSame)
        {
                ke.func_key = WI_KEY_FUNC_ALT_UP;
                
        }else if([key compare : @"Ctrl"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_CTRL_UP;
                
        }else if([key compare : @"Up"] == NSOrderedSame)
        {
                ke.func_key =   WI_KEY_FUNC_UP_UP;
                
        }else if([key compare : @"Down"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_DOWN_UP;
        }else if([key compare : @"Left"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_LEFT_UP;
        }else if([key compare : @"Right"] == NSOrderedSame)
        {
                ke.func_key =  WI_KEY_FUNC_RIGHT_UP;
        }else
        {
                return;
        }

        [self.delegate onKeyboardEvent : &ke];
        
}









@end
