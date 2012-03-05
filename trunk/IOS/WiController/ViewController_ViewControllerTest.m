//
//  ViewController+ViewControllerTest.m
//  WiController
//
//  Created by  on 3/5/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "ArsenalWrapper.h"
#import "ViewController_ViewControllerTest.h"

@implementation ViewController (ViewControllerTest)


-(void)test_ip
{
        ArsenalWrapper *ar = [ArsenalWrapper sharedArsenalWrapper];
        
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        
        while([ar addIPV4Address : &addr])
        {
                const char *s = inet_ntoa(addr.sin_addr);
                WI_LOG(@"%s\r\n", s);
        }
}



-(void)test
{
        //[self test_ip];
}

@end
