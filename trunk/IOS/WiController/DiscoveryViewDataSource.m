//
//  DiscoveryViewDelegate.m
//  WiController
//
//  Created by  on 3/5/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "Reachability.h"
#import "AppDelegate.h"
#import "DiscoveryViewDataSource.h"

@implementation DiscoveryViewDataSource

@synthesize discovered = _discovered;
@synthesize view;
@synthesize sock_handle;

-(void)reset
{
        [_discovered removeAllObjects];
        [self.view reloadData];
        
        if(timer)
        {
                [timer invalidate];
        }
        
        //[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes
}

         
-(void)loadContext
{
        [self start];
}


-(void)saveContext
{
       [self stop];
}



-(void)loadConfig
{

        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        
        
        port = [defaults integerForKey : PREFS_PORT];
        
        if(port <= 0 || port >= 65535)
        {
                port = 28412;
        }
        
        enable_auto_discovery = [defaults boolForKey : PREFS_AUTODISCOVERY];
        
        NSString *ip_start = [defaults stringForKey : PREFS_IPSTART];
        NSString *ip_stop = [defaults stringForKey : PREFS_IPSTOP];
        
        memset(&ip_beg, 0, sizeof(ip_beg));
        memset(&ip_end, 0, sizeof(ip_end));
        
        if(ip_start != nil && ip_stop != nil)
        {
                const char *start_str = [ip_start UTF8String];
                const char *stop_str = [ip_stop UTF8String];
                WI_LOG(@"start == %s", start_str);
                WI_LOG(@"stop == %s", stop_str);
                ip_beg.sin_addr.s_addr = inet_addr(start_str);
                ip_end.sin_addr.s_addr = inet_addr(stop_str);
        }

}

- (void) reachabilityChanged: (NSNotification* )note
{
        Reachability* curReach = [note object];
        NSParameterAssert([curReach isKindOfClass: [Reachability class]]);
        
        if([curReach currentReachabilityStatus] == ReachableViaWiFi)
        {
                wifi_is_enable = YES;
                [self loadContext];
                
        }else
        {
                wifi_is_enable = NO;
                [self saveContext];
        }
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


-(void)handle_read : (const void*)data
{
        WI_LOG(@"%@", @"handle_read");
        
        
}

-(void)handle_write 
{
        WI_LOG(@"%@", @"handle_write");
        
        if(!CFSocketIsValid(self.sock_handle))
        {
                [self stop];
        }

        ArsenalWrapper *ar = [ArsenalWrapper sharedArsenalWrapper];


        if([ar compareIPV4Address : &ip_beg 
                             with : &ip_end
            ] < 0)
        {
                /*
                __uint8_t	sin_len;
                sa_family_t	sin_family;
                in_port_t	sin_port;
                struct	in_addr sin_addr;
                char		sin_zero[8];
                 */
                struct sockaddr_in addr;
                
                memset(&addr, 0, sizeof(addr));
                addr.sin_len = sizeof(addr);
                addr.sin_family = AF_INET;
                addr.sin_port = htons(port);
                addr.sin_addr = ip_beg.sin_addr;
                
/*                
#if defined(DEBUG)
                const char *s = inet_ntoa(addr.sin_addr);
                WI_LOG(@"ip == %s", s);
#endif
*/
                
                CFSocketNativeHandle sock_native = CFSocketGetNative(self.sock_handle);
                
                ssize_t sn = sendto(sock_native, AR_GetBufferData(discovery_request_msg),  AR_GetBufferAvailable(discovery_request_msg), 0, (const struct sockaddr*)&addr, sizeof(addr));

                if(sn < 0)
                {
                        WI_LOG(@"discovery sendto '%s' error == (%d, %s)\r\n",  inet_ntoa(addr.sin_addr), errno, strerror(errno));
                        
                        if(errno == EACCES || errno == EMSGSIZE || errno == EHOSTUNREACH || errno == ENETUNREACH)
                        {
                                
                        }else
                        {
                                [self stop];
                        }
                }else if(sn == 0)
                {
                        WI_LOG(@"discovery sendto '%s' error == %s\r\n",  inet_ntoa(addr.sin_addr), strerror(errno));
                        [self stop];
                        
                }else
                {
                        WI_LOG(@"Discovery sendto %d bytes\r\n", (int)sn);
                }
                
                struct	in_addr bak = ip_beg.sin_addr ;
                
                if(![ar addIPV4Address : &ip_beg])
                {
                        ip_beg.sin_addr = bak;
                }
        }

}


static void __sock_callback(CFSocketRef s, CFSocketCallBackType type, CFDataRef address, const void *data, void *info)
{
        
        DiscoveryViewDataSource *ds = (DiscoveryViewDataSource*)info;
        
        if(ds.sock_handle != s)
        {
                assert(false);
                return;
        }
        
        switch(type)
        {
        case kCFSocketWriteCallBack:
               [ds handle_write];
               break;
        case  kCFSocketDataCallBack:
              [ds handle_read : data];
               break;
        default:
               assert(false);
               break;
        }
}


-(void)start
{
        if(!wifi_is_enable)
        {
                return;
        }
                
        if(is_started)
        {
                return;
        }
        
        if(!enable_auto_discovery)
        {
                return;    
        }
        
        
        int err = 0;
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock <= 0) 
        {
                err = errno;
                assert(err != 0);       
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
                self->sock_handle = CFSocketCreateWithNative(NULL, sock, kCFSocketWriteCallBack|kCFSocketDataCallBack, __sock_callback, &context);
                assert( CFSocketGetSocketFlags(self->sock_handle) & kCFSocketCloseOnInvalidate );
                sock = -1;
                
                CFRunLoopSourceRef    rls = CFSocketCreateRunLoopSource(NULL, self->sock_handle, 0);
                assert(rls != NULL);
                CFRunLoopAddSource(CFRunLoopGetCurrent(), rls, kCFRunLoopDefaultMode);
                CFRelease(rls);
        }
        
        timer = [NSTimer scheduledTimerWithTimeInterval : 0.2
                                                  target: self
                                                selector:@selector(on_timer:)
                                                userInfo:nil
                                                 repeats:YES
                 ];
        [timer retain];
 
        is_started = YES;
}


-(void)stop
{
        if(!is_started)
        {
                return;
        }
        
        [timer invalidate];
        [timer release];
        timer = nil;
        
        if(sock_handle != NULL)
        {
                CFSocketInvalidate(sock_handle);
                CFRelease(sock_handle);
                sock_handle = NULL;
        }
        
        is_started = NO;
}

- (void)on_timer:(NSTimer*)theTimer
{
        WI_LOG(@"on_timer");
        
        ArsenalWrapper *ar = [ArsenalWrapper sharedArsenalWrapper];
        
        if([ar compareIPV4Address : &ip_beg 
                             with : &ip_end
            ] <= 0
           )
        {

#if defined(DEBUG)
             const char *s = inet_ntoa(ip_beg.sin_addr);
             WI_LOG(@"ip == %s", s);
#endif
                
                CFSocketEnableCallBacks(sock_handle, kCFSocketWriteCallBack|kCFSocketDataCallBack);
        }else
        {
                
                CFSocketEnableCallBacks(sock_handle, kCFSocketDataCallBack);
        }
}


- (void)defaultsChanged:(NSNotification *)notif
{
        [self loadConfig];
        [self stop];
        [self start];
}


        

-(id)init
{
        self = [super init];
        if(self)
        {
                discoveryRequestEvent_t dre;
                memset(&dre, 0, sizeof(dre));
                discovery_request_msg = DiscoveryRequestEvent_To_NetMessage(&dre);
                                                    
                _discovered = [[NSMutableArray alloc]init];

                [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onEnterBackground:) name:UIApplicationDidEnterBackgroundNotification object:nil];
                [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onEnterForeground:) name:UIApplicationWillEnterForegroundNotification object:nil];
                
                [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(reachabilityChanged:) name: kReachabilityChangedNotification object: nil];
                
                
                [[NSNotificationCenter defaultCenter] addObserver:self
                                                         selector:@selector(defaultsChanged:)
                                                             name:NSUserDefaultsDidChangeNotification
                                                           object:nil];
                
                is_started = NO;
                enable_auto_discovery = NO;
                wifi_is_enable = YES;
                [self loadConfig];
                
                [self start];
                
        }
        return self;
}


-(void)dealloc
{
        [super dealloc];
        [self stop];
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidEnterBackgroundNotification object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillEnterForegroundNotification object:nil];
        
        [_discovered release];
        _discovered = nil;
        
        AR_DestroyBuffer(discovery_request_msg);
        discovery_request_msg = NULL;
        
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
        return [_discovered count];
}


-(UITableViewCell*)tableView : (UITableView*)tableView cellForRowAtIndexPath : (NSIndexPath*)indexPath
{
        static NSString *DiscoveredComputerCellReusableIdentifier = @"DiscoveredComputerCellReusableIdentifier";
        
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier : DiscoveredComputerCellReusableIdentifier];
        
        if(cell == nil)
        {
                cell = [[[UITableViewCell alloc] initWithStyle : UITableViewCellStyleDefault
                                               reuseIdentifier : DiscoveredComputerCellReusableIdentifier
                         ]autorelease];
        }
        
        NSUInteger row = [indexPath row];
        cell.textLabel.text = [self.discovered objectAtIndex : row];
        return cell;
}




@end
