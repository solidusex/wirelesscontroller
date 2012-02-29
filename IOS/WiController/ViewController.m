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
        
        localNetResourcesIsSeted = NO;
        sock_handle = NULL;
        
        outlist = [[NSMutableArray alloc] initWithCapacity : 128];
        
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
        localNetResourcesIsSeted = NO;
        sock_handle = NULL;
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





- (void)dealloc 
{
        [self clearOutList];
        if(outlist != nil)
        {
                [outlist release];
                outlist = nil;
        }
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





-(IBAction) transToMouseView : (id)sender
{
        if(localNetResourcesIsSeted)
        {
                [self performSegueWithIdentifier : @"TransmitToMouseView"
                                           sender:self
                 ];
        }

}

-(IBAction) transToKeyboardView : (id)sender
{
        if(localNetResourcesIsSeted)
        {
                [self performSegueWithIdentifier : @"TransmitToKeyboardView"
                                           sender:self
                 ];
        }

}

-(IBAction) transToShortcutsView : (id)sender
{
        if(localNetResourcesIsSeted)
        {
                [self performSegueWithIdentifier : @"TransmitToShortcutsView"
                                           sender:self
                 ];
        }

}


-(unsigned short) getDestinationPort
{
        return 28412;
}


-(IBAction) setDestinationAddress : (id)sender
{
        [self uninitLocalNetResources];
        
        [self initLocalNetResources : ipText.text
                               port : [self getDestinationPort]
        ];
}


static void __on_write_callback(CFSocketRef s, CFSocketCallBackType type, CFDataRef address, const void *data, void *info)
{
        
        ViewController *controller = (ViewController*)info;
        [controller handle_write];
        
}





-(BOOL)_setupSocketConnectedToAddress:(NSData *)address port:(NSUInteger)port error:(NSError **)errorPtr
{
        sa_family_t             socketFamily;
        int                     err;
        int                     junk;
        int                     sock;
        
        assert((address == nil) || ([address length] <= sizeof(struct sockaddr_storage)) );
        assert(port < 65536);
        assert(self->sock_handle == NULL);

        err = 0;
        sock = socket(AF_INET6, SOCK_DGRAM, 0);
        
        if(sock >= 0) 
        {
                socketFamily = AF_INET6;
        }else
        {
                sock = socket(AF_INET, SOCK_DGRAM, 0);
                if (sock >= 0) 
                {
                        socketFamily = AF_INET;
                }else 
                {
                        err = errno;
                        socketFamily = 0;
                        assert(err != 0);       
                }
        }
        
        if(err == 0)
        {
                struct sockaddr_storage addr;
                struct sockaddr_in *    addr4;
                struct sockaddr_in6 *   addr6;
                
                addr4 = (struct sockaddr_in * ) &addr;
                addr6 = (struct sockaddr_in6 *) &addr;
                memset(&addr, 0, sizeof(addr));
                
                if([address length] > sizeof(addr)) 
                {
                        assert(NO);         // very weird
                        [address getBytes:&addr length:sizeof(addr)];
                }else
                {
                        [address getBytes:&addr length:[address length]];
                }
                
                if(addr.ss_family == AF_INET)
                {
                        if(socketFamily == AF_INET6)
                        {
                                struct	in_addr ipv4Addr;
                                ipv4Addr = addr4->sin_addr;
                                addr6->sin6_len         = sizeof(*addr6);
                                addr6->sin6_family      = AF_INET6;
                                addr6->sin6_port        = htons(port);
                                addr6->sin6_addr.__u6_addr.__u6_addr32[0] = 0;
                                addr6->sin6_addr.__u6_addr.__u6_addr32[1] = 0;
                                addr6->sin6_addr.__u6_addr.__u6_addr16[4] = 0;
                                addr6->sin6_addr.__u6_addr.__u6_addr16[5] = 0xffff;
                                addr6->sin6_addr.__u6_addr.__u6_addr32[3] = ipv4Addr.s_addr;
                        }else
                        {
                                addr4->sin_port = htons(port);
                        }
                        
                }else 
                {
                        assert(addr.ss_family == AF_INET6);
                        addr6->sin6_port        = htons(port);
                }
                
                if((addr.ss_family == AF_INET) && (socketFamily == AF_INET6) ) 
                {
                        addr6->sin6_len         = sizeof(*addr6);
                        addr6->sin6_port        = htons(port);
                        addr6->sin6_addr        = in6addr_any;
                }
                
                
                err = connect(sock, (const struct sockaddr*)&addr, addr.ss_len);
                
                if (err < 0) 
                {
                        err = errno;
                }
        }
        
        

        if(err == 0) 
        {
                int flags;
                flags = fcntl(sock, F_GETFL);
                err = fcntl(sock, F_SETFL, flags | O_NONBLOCK);
                if (err < 0) 
                {
                        err = errno;
                }
        }
        

        
        if(err == 0) 
        {
                const CFSocketContext   context = { 0, self, NULL, NULL, NULL };
                self->sock_handle = CFSocketCreateWithNative(NULL, sock, kCFSocketWriteCallBack, __on_write_callback, &context);
                assert( CFSocketGetSocketFlags(self->sock_handle) & kCFSocketCloseOnInvalidate );
                sock = -1;
                
                CFRunLoopSourceRef    rls = CFSocketCreateRunLoopSource(NULL, self->sock_handle, 0);
                assert(rls != NULL);
                CFRunLoopAddSource(CFRunLoopGetCurrent(), rls, kCFRunLoopDefaultMode);
                CFRelease(rls);
        }
        
        if (sock != -1)
        {
                junk = close(sock);
                assert(junk == 0);
        }
        
        assert((err == 0) == (self->sock_handle != NULL));
        
        if((self->sock_handle == NULL) && (errorPtr != NULL))
        {
                *errorPtr = [NSError errorWithDomain:NSPOSIXErrorDomain code:err userInfo:nil];
        }
        return (err == 0);
}



-(BOOL) setup_socket : (NSArray*)resolvedAddresses  address : (NSString*)addr port : (unsigned short)port
{
        NSError *error;
        for (NSData * address in resolvedAddresses)
        {
                BOOL                    success;
                const struct sockaddr * addrPtr;
                NSUInteger              addrLen;
                
                addrPtr = (const struct sockaddr *) [address bytes];
                addrLen = [address length];
                assert(addrLen >= sizeof(struct sockaddr));
                success = NO;
                
                if((addrPtr->sa_family == AF_INET) || (addrPtr->sa_family == AF_INET6)) 
                {
                        success = [self _setupSocketConnectedToAddress:address 
                                                                  port:port 
                                                                 error:&error
                                   ];

                        if(success)
                        {
                                host_addr = CFSocketCopyPeerAddress(self->sock_handle);
                                assert(host_addr != NULL);
                        }
                }
                
                if (success) 
                {
                        return YES;
                        
                }
        }

        return NO;
        
}



-(BOOL)     initLocalNetResources : (NSString*)addr port : (unsigned short)port
{
        
        BOOL status = YES;
        
        CFHostRef               host_handle = NULL;
        assert(addr != nil);
        
        if(localNetResourcesIsSeted)
        {
                return NO;
        }
        
        
        if(ipText.text == nil || [ipText.text length] == 0)
        {
                NSString *alert = [NSString stringWithFormat : @"invalid ip address '%@'", addr];
                
                [self showAlert : alert
                         cancel : @"OK"
                 ];
                
                return NO;
        }

        host_handle = NULL;
        sock_handle = NULL;
        
        
        CFStreamError       streamError;

        host_handle = CFHostCreateWithName(kCFAllocatorDefault, (CFStringRef)addr);
        
        
        status = CFHostStartInfoResolution(host_handle, kCFHostAddresses, &streamError);
        
        Boolean             resolved;
        NSArray             *resolved_addresses;
        
        if(status)
        {
                resolved_addresses = (NSArray*)CFHostGetAddressing(host_handle, &resolved);
                if(!resolved || resolved_addresses == nil)
                {
                        status = NO;
                }
        }
        
        if(!status)
        {
                NSString *alert = [NSString stringWithFormat : @"Failed to resolve '%@'", addr];
                
                [self showAlert : alert
                         cancel : @"OK"
                 ];
                
                goto END_POINT;
        }
       
        
        status = [self setup_socket : resolved_addresses
                            address : addr
                               port : port
          ];
                
        if(!status)
        {
                NSString *alert = [NSString stringWithFormat : @"Failed to connect '%@'", addr];
                
                [self showAlert : alert
                         cancel : @"OK"
                 ];
                
                goto END_POINT;
        }
        
        localNetResourcesIsSeted = status;
        
END_POINT:        
        if(host_handle != NULL)
        {
                CFRelease(host_handle);
                host_handle = NULL;
        }
        
        if(!status)
        {
                if(sock_handle != NULL)
                {
                        CFSocketInvalidate(sock_handle);
                        CFRelease(sock_handle);
                        sock_handle = NULL;
                }
        }
        
        return status;
}


-(void)     uninitLocalNetResources
{
        if(!localNetResourcesIsSeted)
        {
                return;
        }
        
        if(sock_handle != NULL)
        {
                CFSocketInvalidate(sock_handle);
                CFRelease(sock_handle);
                sock_handle = NULL;
        }
        
        if(host_addr)
        {
                CFRelease(host_addr);
                host_addr = NULL;
        }
        
        localNetResourcesIsSeted = NO;
        
}


-(void)     showAlert : (NSString*)alert cancel : (NSString*)cancel
{
        
             
       UIAlertView             *alert_view = [[UIAlertView alloc] initWithTitle : @"Warning"
                                                     message: alert
                                                    delegate: nil 
                                           cancelButtonTitle: cancel
                                           otherButtonTitles: nil
                              ];
        [alert_view show];
        
        [alert_view release];
        alert_view = nil;
}


-(void)clearOutList
{
        if(outlist != nil)
        {
                for(int i = 0; i < [outlist count]; ++i)
                {
                        NSData *data = [outlist objectAtIndex : i];
                        [data release];
                }
        }
}


-(void)onMouseEvent           :  (const mouseNetMsg_t*)event
{
        NSLog(@"event == %d : (%g,%g), data = %g", event->t, event->x,event->y, event->data);
        
}



-(void) handle_write
{
        if([outlist count] == 0)
        {
                return;
        }
        
        for(int i = 0; i < [outlist count]; ++i)
        {
                NSData *data = [outlist objectAtIndex : i];
                
                
        }
        [outlist removeAllObjects];
        
        
}







@end
