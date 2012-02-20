/*
 * Copyright (c) 2011 by Solidus
 * This file is part of Arsenal library tools source code.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express 
 * or implied warranty.
 *
 */


#import "ARException.h"


wchar_t* healper_wcsndup(const wchar_t *sour, size_t len);


@interface WideCharWrapper : NSObject 
{
		wchar_t *string;
}

+(id)WideCharWithString : (const wchar_t*)s;

-(id)init;
-(void)dealloc;

-(void)setString : (const wchar_t*)s;
-(const wchar_t*)string;

@end



@interface ARUtility : NSObject 
{
		
}
+(NSString*)convertUTF32ToNSString		:		(const wchar_t*)input;
+(NSString*)convertUTF32ToNSString		:		(const wchar_t*)input Length : (size_t)len;

+(WideCharWrapper*) convertNSStringToUTF32		:		(NSString*)input;

@end
