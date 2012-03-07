//
//  DiscoveryView.h
//  WiController
//
//  Created by solidus on 3/5/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DiscoveryViewDataSource.h"


@interface DiscoveryView : UITableView
{
        DiscoveryViewDataSource *discovery;
}

-(NSString*)dataAtIndex : (NSInteger)index;
@end
