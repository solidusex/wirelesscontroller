//
//  ViewController.h
//  WiController
//
//  Created by solidus on 2/27/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>


#import <CFNetwork/CFNetwork.h>
#import <arpa/inet.h>
#import <fcntl.h>
#import <ifaddrs.h>
#import <netdb.h>
#import <net/if.h>
#import <sys/socket.h>
#import <sys/types.h>
#import <arpa/inet.h>		// for IPPROTO_TCP
#include <netinet/tcp.h>	// for TCP_NODELAY



#import "MouseViewController.h"
#import "KeyboardViewController.h"
#import "ShortcutsViewController.h"




@interface ViewController : UIViewController<MouseViewControllerDelegate, KeyboardViewControllerDelegate, ShortcutsViewControllerDelegate, UITextFieldDelegate>
{
        BOOL            localNetResourcesIsSeted;
        
        CFSocketRef     sock_handle;
        CFDataRef       host_addr;
        
        NSMutableArray  *outlist;
}

@property (retain, nonatomic) IBOutlet UITextField *ipText;

@property (retain, nonatomic) IBOutlet UITextField *pwdText;


-(IBAction) backgroundTap : (id)sender;

-(IBAction) transToMouseView : (id)sender;
-(IBAction) transToKeyboardView : (id)sender;
-(IBAction) transToShortcutsView : (id)sender;
-(IBAction) setDestinationAddress : (id)sender;

-(BOOL)     initLocalNetResources : (NSString*)addr port : (unsigned short)port;
-(void)     uninitLocalNetResources;

-(void)     showAlert : (NSString*)alert cancel : (NSString*)cancel;
-(void)     clearOutList;
-(void)     handle_write;


@end
