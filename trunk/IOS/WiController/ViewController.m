//
//  ViewController.m
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "ArsenalWrapper.h"
#import "AppDelegate.h"
#import "ViewController.h"
#import "ViewController_ViewControllerTest.h"



@implementation ViewController

@synthesize discoveryView;
@synthesize ipText;
@synthesize pwdText;

@synthesize sock_handle;


-(void)alertLocalWifiReachability
{
        if(isAlerted)
        {
                if([localWifiReachability currentReachabilityStatus] == ReachableViaWiFi)
                {
                        [wifiAlertView dismissWithClickedButtonIndex : 0 
                                                            animated : YES
                         ];
                        
                        [wifiAlertView release];
                        wifiAlertView = nil;
                        isAlerted = NO;
                        

                        [self loadContext];
                        
                }
        }else
        {   
                if([localWifiReachability currentReachabilityStatus] != ReachableViaWiFi)
                {
                        [self saveContext];
                        
                        wifiAlertView  = [[UIAlertView alloc] initWithTitle : @"Warning"
                                                                     message: @"Wifi disabled" 
                                                                    delegate: nil 
                                                           cancelButtonTitle: nil 
                                                           otherButtonTitles: nil
                                          ];
                        
                        
                        [wifiAlertView show];
                        isAlerted = YES;
                }
        }
}



- (void) reachabilityChanged: (NSNotification* )note
{
        Reachability* curReach = [note object];
        NSParameterAssert([curReach isKindOfClass: [Reachability class]]);
        
        if(curReach == localWifiReachability)
        {
                [self alertLocalWifiReachability];
        }
}






/*************************************************************************************************/


- (BOOL)textViewShouldBeginEditing:(UITextView *)aTextView 
{
        return YES;
}


- (BOOL)textViewShouldEndEditing:(UITextView *)aTextView 
{
        [aTextView resignFirstResponder];
        return YES;
}



- (void)keyboardWillShow:(NSNotification *)notification
{
        
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


- (void)onEnterBackground:(NSNotification *)notification 
{
        NSLog(@"ViewController::onEnterBackground");
        [self saveContext];
}


- (void)onEnterForeground:(NSNotification *)notification 
{
        NSLog(@"ViewController::onEnterForeground");        
        [self loadContext];
}

#pragma mark - View lifecycle


- (void)viewDidLoad
{
        [super viewDidLoad];
        
        
        // Do any additional setup after loading the view, typically from a nib.
        
        isAlerted = NO;
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(reachabilityChanged:) name: kReachabilityChangedNotification object: nil];
        
        localWifiReachability = [Reachability reachabilityForLocalWiFi];
        [localWifiReachability retain];
        [localWifiReachability startNotifier];
        
        [self alertLocalWifiReachability];
        
        
        
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onEnterBackground:) name:UIApplicationDidEnterBackgroundNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onEnterForeground:) name:UIApplicationWillEnterForegroundNotification object:nil];
        
        
        self.ipText.delegate = self;
        self.pwdText.delegate = self;
        
        localNetResourcesIsSeted = NO;
        sock_handle = NULL;
        
        
        outlist = [[NSMutableArray alloc] initWithCapacity : 128];
        
        is_saved_context = NO;
        
        
        [self loadConfig];
        
        self.discoveryView.delegate = self;
        
        [self test];
}

- (void)viewDidUnload
{
        
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidEnterBackgroundNotification object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillEnterForegroundNotification object:nil];
        
        self.ipText.delegate = nil;
        self.pwdText.delegate = nil;
        
        [self setIpText:nil];
        [self setPwdText:nil];
        [self setDiscoveryView:nil];
        [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
        localNetResourcesIsSeted = NO;
        sock_handle = NULL;
        
        [localWifiReachability stopNotifier];
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [localWifiReachability release];
        
        
        
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
        [current_pwd release];
        [discoveryView release];
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
                [self backgroundTap : self];
                [self performSegueWithIdentifier : @"TransmitToMouseView"
                                           sender:self
                 ];
        }

}

-(IBAction) transToKeyboardView : (id)sender
{
        if(localNetResourcesIsSeted)
        {
                [self backgroundTap : self];
                
                [self performSegueWithIdentifier : @"TransmitToKeyboardView"
                                           sender:self
                 ];
        }

}

-(IBAction) transToShortcutsView : (id)sender
{
        if(localNetResourcesIsSeted)
        {
                [self backgroundTap : self];
                
                [self performSegueWithIdentifier : @"TransmitToShortcutsView"
                                           sender:self
                 ];
        }

}


-(unsigned short) getDestinationPort
{
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        
        NSInteger port = [defaults integerForKey : PREFS_PORT];
        
        if(port <= 0 || port >= 65535)
        {
                port = 28412;
        }
        
        return (unsigned short)port;
}


#define IP_PATTERN      L"(({digit}{1,2}|1{digit}{digit}|2[0-4]{digit}|25[0-5])\\.({digit}{1,2}|1{digit}{digit}|2[0-4]{digit}|25[0-5])\\.({digit}{1,2}|1{digit}{digit}|2[0-4]{digit}|25[0-5])\\.({digit}{1,2}|1{digit}{digit}|2[0-4]{digit}|25[0-5]))(?!{digit})"

static BOOL is_valid_ip_address(const wchar_t *ip, wchar_t valid_ip[16])
{
        lex_t *lex = Lex_Create();
        
        
        if(Lex_InsertName(lex, L"delim", L"[ \\r\\t\\n]") != AR_S_YES)
        {
                assert(false);
        }
        
        if(Lex_InsertName(lex, L"digit", L"[0-9]") != AR_S_YES)
        {
                assert(false);
        }
        
        lexAction_t act;
        act.is_skip = true;
        act.priority = 1;
        act.value = 0;
        
        if(Lex_InsertRule(lex, L"{delim}+", &act) != AR_S_YES)
        {
                assert(false);
        }
        
        
        act.is_skip = false;
        act.priority = 0;
        act.value = 1;
        if(Lex_InsertRule(lex, IP_PATTERN, &act) != AR_S_YES)
        {
                assert(false);
        }
        
        lexMatch_t *match = Lex_CreateMatch(lex);
        Lex_ResetInput(match, ip);
        lexToken_t tok;
        BOOL ret = Lex_Match(match, &tok) == AR_S_YES;
        
        if(ret)
        {
                assert(tok.count < 16);
                AR_wcsncpy(valid_ip, tok.str, tok.count);
                valid_ip[tok.count] = 0;
        }
        
        Lex_DestroyMatch(match);
        match = NULL;
        
        Lex_Destroy(lex);
        lex = NULL;
        
        return ret;
}




-(IBAction) setDestinationAddress : (id)sender
{
        if([ipText.text length] > 0)
        {
                wchar_t valid_ip[16];
                const wchar_t *ip_txt = [[ArsenalWrapper sharedArsenalWrapper] stringConvertToWideString : ipText.text];
                
                if(!is_valid_ip_address(ip_txt, valid_ip))
                {
                        NSString *alert = [NSString stringWithFormat : @"invalid ip address : '%@'", ipText.text];
                        
                        [self showAlert : alert
                                 cancel : @"OK"
                         ];
                        return;
                }
                
                ipText.text = [NSString  stringWithWideString : valid_ip];
        }else
        {
                NSString *alert = [NSString stringWithFormat : @"empty ip address"];
                
                [self showAlert : alert
                         cancel : @"OK"
                 ];
                return;
        }
        
        ///////////////////////////////
        [self uninitLocalNetResources];
        
        if([self initLocalNetResources : ipText.text
                               port : [self getDestinationPort]
        ])
        {
                [current_pwd release];
                current_pwd = [pwdText.text copy];
                
                [self saveConfig];
                
                [self transToMouseView : self];
        }
}


static void __on_write_callback(CFSocketRef s, CFSocketCallBackType type, CFDataRef address, const void *data, void *info)
{
        
        ViewController *controller = (ViewController*)info;
        
        if(controller.sock_handle != s)
        {
                assert(false);
                return;
        }
        
        switch(type)
        {
        case kCFSocketWriteCallBack:
             [controller handle_write];
             break;
        default:
               assert(false);
               break;
        }
        
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
                                
//                              printf("%s\r\n", inet_ntoa(ipv4Addr));
                                
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
        
        [self clearOutList];
        
        if(ipText.text == nil || [ipText.text length] == 0)
        {
                NSString *alert = [NSString stringWithFormat : @"invalid ip address"];
                
                [self showAlert : alert
                         cancel : @"OK"
                 ];
                
                return NO;
        }

        host_handle = NULL;
        sock_handle = NULL;
        
        
        CFStreamError       streamError;
        Boolean             resolved;
        NSArray             *resolved_addresses;
        
        
        host_handle = CFHostCreateWithName(kCFAllocatorDefault, (CFStringRef)addr);
        
        
        
        status = CFHostStartInfoResolution(host_handle, kCFHostAddresses, &streamError);
        
        if(!status)
        {
                status = CFHostStartInfoResolution(host_handle, kCFHostAddresses, &streamError);
        }
        
        
        
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
        
        [self clearOutList];
        
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
                while([outlist count] > 0)
                {
                        [outlist removeObjectAtIndex : 0];
                }
        }
}


-(void)onMouseEvent           :  (const mouseEvent_t*)event
{
        arBuffer_t *buf;
//        WI_LOG(@"event == %d : (%g,%g), data = %g", event->t, event->x,event->y, event->data);
        
        const char *pwd = NULL;
        
        if([current_pwd lengthOfBytesUsingEncoding : NSASCIIStringEncoding] > 0)
        {
                pwd = [current_pwd UTF8String];
        }
        
        buf = MouseEvent_To_NetMessage(event, pwd);
        
        if(buf)
        {
                size_t out_len = AR_GetBufferAvailable(buf);
                if(out_len == 0)
                {
                        assert(false);
                        AR_DestroyBuffer(buf);
                        buf = NULL;
                        return;
                }
                        
                
                NSData *data = [NSData dataWithBytes :(const void *)AR_GetBufferData(buf)
                                               length:out_len
                                ];
                        
                [outlist addObject : data];
                
                AR_DestroyBuffer(buf);
                buf = NULL;

                CFSocketEnableCallBacks(sock_handle, kCFSocketWriteCallBack);
        }
        
}


-(void)onKeyboardEvent : (const keyboardEvent_t*) ke
{
        arBuffer_t *buf;
        //        WI_LOG(@"event == %d : (%g,%g), data = %g", event->t, event->x,event->y, event->data);
        
        const char *pwd = NULL;
        
        if([current_pwd lengthOfBytesUsingEncoding : NSASCIIStringEncoding] > 0)
        {
                pwd = [current_pwd UTF8String];
        }
        
        buf = KeyboardEvent_To_NetMessage(ke, pwd);
        
        if(buf)
        {
                size_t out_len = AR_GetBufferAvailable(buf);
                if(out_len == 0)
                {
                        assert(false);
                        AR_DestroyBuffer(buf);
                        buf = NULL;
                        return;
                }
                
                
                NSData *data = [NSData dataWithBytes :(const void *)AR_GetBufferData(buf)
                                               length:out_len
                                ];
                
                [outlist addObject : data];
                
                AR_DestroyBuffer(buf);
                buf = NULL;
                
                CFSocketEnableCallBacks(sock_handle, kCFSocketWriteCallBack);
        }

}                                                                                                                               




-(void) handle_write
{
        
        BOOL is_valid = CFSocketIsValid(sock_handle);
        
        if(!is_valid)
        {
                goto INVALID_POINT;
        }
        
        
        
        
        if([outlist count] == 0)
        {
                return;
        }
        
        BOOL send_ok = YES;
        NSData *data = [outlist objectAtIndex : 0];
                
        if([data length] > 0)
        {
                int sock_native = CFSocketGetNative(sock_handle);
                
                
                ssize_t sn = sendto(sock_native, [data bytes], [data length], 0, NULL, 0);
                
                if(sn <= 0)
                {
                        WI_LOG(@"error code == %s\r\n", strerror(errno));
                        send_ok = NO;
                        goto INVALID_POINT;
                }
                
                WI_LOG(@"Sendto %d bytes\r\n", (int)sn);
        }
        
        [outlist removeObjectAtIndex : 0];
        
        WI_LOG(@"Remain count == %d\r\n", [outlist count]);
        
        CFSocketEnableCallBacks(sock_handle, kCFSocketWriteCallBack);
        

        
        return;
        
INVALID_POINT:
        
        [self showAlert : @"connection lost!"
                 cancel : @"OK"
         ];
        
        [self uninitLocalNetResources];
        [self dismissViewControllerAnimated : YES
                                 completion : nil
         ];
        return;
}




-(void)     saveContext
{
        NSLog(@"ViewController::saveContext!");
        
        if(is_saved_context)
        {
                return;
        }
        
        if(!localNetResourcesIsSeted)
        {
                return;
        }
        
        [self uninitLocalNetResources];
        
        if(backup_outlist != nil)
        {
                [backup_outlist release];
        }
         
        backup_outlist = [[NSMutableArray alloc] initWithArray : outlist];
        is_saved_context = YES;
       
}



-(void)     loadContext
{
        NSLog(@"ViewController::loadContext!");
        if(!is_saved_context)
        {
                return;
        }
        
        if([localWifiReachability currentReachabilityStatus] != ReachableViaWiFi)
        {
                return;
        }
        
        if(![self initLocalNetResources : ipText.text
                                  port : [self getDestinationPort]
            ])
        {
                [self dismissViewControllerAnimated : YES
                                         completion : nil
                 ];
                is_saved_context = NO;
                return;
        }
        
        [current_pwd release];
        current_pwd = [pwdText.text copy];
        
        if(outlist != nil)
        {
                [outlist release];
        }
         
        outlist = backup_outlist;
        backup_outlist = nil;
        
        
        if([outlist count] > 0)
        {
                CFSocketEnableCallBacks(sock_handle, kCFSocketWriteCallBack);
        }

        is_saved_context = NO;
}


-(void)loadConfig
{
        WI_LOG(@"%@", @"loadConfig");
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
        NSString *documentsDirectory = [paths objectAtIndex : 0];
        
        NSString *config_path = [documentsDirectory stringByAppendingPathComponent : CONFIG_FILE];
        
        NSDictionary *dict = [[NSDictionary alloc] initWithContentsOfFile : config_path];
        
        NSString *ip_str = [dict objectForKey : LAST_IP];
        NSString *pwd_str =[dict objectForKey : LAST_PWD]; 
        
        if(ip_str != nil)
        {
                ipText.text = ip_str;
        }
        
        if(pwd_str != nil)
        {
                pwdText.text = pwd_str;
        }
        
        
}


-(void)saveConfig
{
        WI_LOG(@"%@", @"saveConfig");
        
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
        NSString *documentsDirectory = [paths objectAtIndex : 0];
        
        NSString *config_path = [documentsDirectory stringByAppendingPathComponent : CONFIG_FILE];
        
        
        NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithCapacity : 2];
        [dict setObject : ipText.text
                 forKey : LAST_IP
         ];
        
        [dict setObject : [pwdText.text length] == 0 ? @"" : pwdText.text
                 forKey : LAST_PWD
         ];
        
        [ dict writeToFile : config_path
                atomically : YES
         ];
        
}



/**************************************************************/


///////////////////////////////////////////
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
        NSInteger row = [indexPath row];
        
        NSString *ip = [self.discoveryView dataAtIndex : row];
        
        WI_LOG(@"selected ip addr = %@", ip);
        if(ip)
        {
                ipText.text = ip;
        }
        
}





@end
