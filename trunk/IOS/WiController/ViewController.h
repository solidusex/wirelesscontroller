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


#include "stdhdr.h"
#include "Reachability.h"
#import "MouseViewController.h"
#import "KeyboardViewController.h"
#import "ShortcutsViewController.h"


#import "NSString_Convert.h"
#import "DiscoveryView.h"


#define CONFIG_FILE     @"config.plist"
#define LAST_IP         @"LAST_IP"
#define LAST_PWD        @"LAST_PWD"

@interface ViewController : UIViewController<UITableViewDelegate, MouseViewControllerDelegate, KeyboardViewControllerDelegate, ShortcutsViewControllerDelegate, UITextFieldDelegate>
{
        BOOL            localNetResourcesIsSeted;

        CFSocketRef     sock_handle;
        CFDataRef       host_addr;
        
        NSMutableArray  *outlist;
        NSString        *current_pwd;
        
        
        Reachability    *localWifiReachability;
        UIAlertView     *wifiAlertView;
        BOOL            isAlerted;
        
        BOOL            is_saved_context;
        NSMutableArray  *backup_outlist;
}
@property (retain, nonatomic) IBOutlet DiscoveryView *discoveryView;

@property (retain, nonatomic) IBOutlet UITextField *ipText;

@property (retain, nonatomic) IBOutlet UITextField *pwdText;

@property (readonly, nonatomic) CFSocketRef sock_handle;


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

-(void)     saveContext;
-(void)     loadContext;

-(void)     loadConfig;
-(void)     saveConfig;

-(unsigned short)       getDestinationPort;




@end
