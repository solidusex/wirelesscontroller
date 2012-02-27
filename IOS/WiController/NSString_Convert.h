//
//  NSString+Convert.h
//  WiController
//
//  Created by solidus on 2/21/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (Convert)


+(id)stringWithBytes:(const void *)bytes length:(NSUInteger)length encoding:(NSStringEncoding)encoding;
+(id) stringWithWideString : (const wchar_t*)widestring;

@end
