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


#import <UIKit/UIKit.h>
#include "Arsenal.h"

@interface ARException : NSException {
		
}

+(id)exceptionWithReason : (NSString*)reason;
-(id)init;
-(id)initWithReason : (NSString*)reason;
-(NSString*)what;

@end



#define DECL_EXCEPTION(_new_expt, _base)		@interface _new_expt : _base {}							\
												@end													

#define IMPL_EXCEPTION_BEG(_new_expt)			@implementation _new_expt
#define IMPL_EXCEPTION_END(_new_expt)			@end

#define IMPL_EXCEPTION(_new_expt)				IMPL_EXCEPTION_BEG(_new_expt)													\
												/*+(id)exceptionWithReason : (NSString*)reason									\
												{																				\
														_new_expt *expt = [[_new_expt alloc] initWithReason : reason];			\
														[expt autorelease];														\
														return expt;															\
												}																				\
												*/																				\
												IMPL_EXCEPTION_END(_new_expt)


DECL_EXCEPTION(ARRuntimeException,	ARException)		
DECL_EXCEPTION(ARSystemException,ARRuntimeException)	
DECL_EXCEPTION(ARStringConvertException,ARRuntimeException)	





