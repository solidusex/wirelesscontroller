//
//  DiscoveryView.m
//  WiController
//
//  Created by  on 3/5/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "DiscoveryView.h"


@implementation DiscoveryView

- (id)initWithFrame:(CGRect)frame
{
        self = [super initWithFrame:frame];
        if (self) 
        {
                discovery = [[DiscoveryViewDataSource alloc] init];
                discovery.view = self;
                self.dataSource = discovery;
        }
        return self;
}

- (id)initWithCoder:(NSCoder *)decoder
{
        self = [super initWithCoder : decoder];
        if(self)
        {
                discovery = [[DiscoveryViewDataSource alloc] init];
                discovery.view = self;
                self.dataSource = discovery;
                
        }
        return self;
}

-(void)dealloc
{
        [super dealloc];
        
        self.dataSource = nil;
        [discovery release];
        discovery = nil;

}

-(NSString*)dataAtIndex : (NSInteger)index
{
        return [discovery.discovered objectAtIndex : index];
}

@end
