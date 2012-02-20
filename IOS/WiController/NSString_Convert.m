//
//  NSString+Convert.m
//  WiController
//
//  Created by peng liu on 2/21/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "Arsenal.h"
#import "NSString_Convert.h"

@implementation NSString (Convert)


+(id)stringWithBytes:(const void *)bytes length:(NSUInteger)length encoding:(NSStringEncoding)encoding
{
        NSString *ret = [ [NSString alloc] initWithBytes : bytes
                                                  length : length
                                                encoding : encoding
                         ];
        
        
        [ret autorelease];
        return ret;
}


+(id) stringWithWideString : (const wchar_t*)widestring
{
        NSStringEncoding enc;
        size_t len;
        assert(widestring != NULL);
        
        len = wcslen(widestring);
        if(len == 0)
        {
                return @"";
        }
        
#if defined(ARCH_LITTLE_ENDIAN)
        enc = NSUTF32LittleEndianStringEncoding;
#else
        enc = NSUTF32BigEndianStringEncoding;
#endif
        
        
        return [NSString stringWithBytes : (const void*)widestring
                                  length : len *sizeof(wchar_t)
                                encoding : enc
                ];
}


@end
