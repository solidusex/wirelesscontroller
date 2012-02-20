/* * Copyright (c) 2011 by Solidus * This file is part of Arsenal library tools source code. * * Permission to use, copy, modify, distribute and sell this software * and its documentation for any purpose is hereby granted without fee, * provided that the above copyright notice appear in all copies and * that both that copyright notice and this permission notice appear * in supporting documentation.It is provided "as is" without express  * or implied warranty. * */#import "ARThread.h"@interface WaitInfo		:		NSObject{		AREvent			*event;		id				data;}@property (readwrite, assign)	id	data;-(id)	init;-(void)	wait;-(BOOL)	waitTimeout : (NSTimeInterval)milliseconds;-(void)set;@end@implementation WaitInfo	@synthesize data;-(id) init{		self = [super init];		if(self)		{				event = [[AREvent alloc] initEvent :NO];				data = nil;		}		return self;}-(void)dealloc{		[event release];		[super dealloc];}-(void)	wait{		[event wait];}-(BOOL)	waitTimeout : (NSTimeInterval)milliseconds{		return [event waitTimeout : milliseconds];}-(void)set{		[event set];}@end/*  @interface ARAsyncQueue : NSObject { NSLock				*lock; NSMutableArray		*waitQueue; NSMutableArray		*dataQueue; } -(id)	init; -(void)	dealloc; -(id)	getData; -(id)	getDataTimeout : (NSTimeInterval) millisecond; -(void)	putData : (id)data; -(BOOL)	hasIdleThread; -(BOOL)	isEmpty; -(void)	clear; */@implementation ARAsyncQueue-(id) init{		self = [super init];				if(self)		{				lock = [[NSLock alloc] init];				waitQueue = [[NSMutableArray alloc]init];				dataQueue = [[NSMutableArray alloc]init];		}		return self;}-(void)dealloc{		assert([waitQueue count] == 0);		[self clear];				[waitQueue release];		[dataQueue release];		[lock release];				[super dealloc];}-(BOOL)	hasIdleThread{		BOOL has_idle = NO;		[lock lock];		has_idle = [waitQueue count] > 0 ? YES : NO;		[lock unlock];		return has_idle;}-(BOOL)	isEmpty{		BOOL is_empty;		[lock lock];		is_empty = [dataQueue count] > 0 ? NO : YES;		[lock unlock];		return is_empty;}-(void)	clear{		while([dataQueue count] > 0)		{				id data = [dataQueue objectAtIndex : 0];				[dataQueue removeObjectAtIndex : 0];				[data release];		}}-(void)	putData : (id)data{		assert(data != nil);				[data retain]; //为本队列增加引用技术，这里不考虑NSMutableArray对引用技术的修改				[lock lock];				if([waitQueue count] > 0)		{				WaitInfo *wait = [waitQueue objectAtIndex : 0];				[waitQueue removeObjectAtIndex : 0];				assert(wait != nil);				wait.data = data;				[wait set];		}else		{				[dataQueue addObject : data];		}				[lock unlock];		}-(id)	getData{		id result = nil;				[lock lock];				if([dataQueue count] > 0)		{				result = [dataQueue objectAtIndex : 0];				[dataQueue removeObjectAtIndex : 0];				assert(result != nil);				[result release]; //push到此队列中时曾经retain过此对象，与NSMutableArray无关				[lock unlock];						}else		{				WaitInfo *wi = [[WaitInfo alloc] init];				[waitQueue addObject : wi];								[lock unlock];								[wi wait];				assert(wi.data != nil);				result = wi.data;				[result release]; //push到此队列中时曾经retain过此对象，与NSMutableArray无关				[wi release];		}		assert(result != nil);		return result;		}-(id)	getDataTimeout : (NSTimeInterval) milliseconds{		id result = nil;				[lock lock];				if([dataQueue count] > 0)		{				result = [dataQueue objectAtIndex : 0];				[dataQueue removeObjectAtIndex : 0];				assert(result != nil);				[result release]; //push到此队列中时曾经retain过此对象，与NSMutableArray无关				[lock unlock];						}else		{				WaitInfo *wi = [[WaitInfo alloc] init];				[waitQueue addObject : wi];								[lock unlock];								if([wi waitTimeout : milliseconds ])				{						result = wi.data;						assert(result != nil);						[result release]; //push到此队列中时曾经retain过此对象，与NSMutableArray无关				}else				{						[lock lock];												NSUInteger idx = [waitQueue indexOfObject : wi];												if(idx == NSNotFound)						{								assert(wi.data != nil);								result = wi.data;								[result release]; 						}else						{								[waitQueue removeObjectAtIndex : idx];								assert(wi.data == nil);						}												[lock unlock];				}								[wi release];		}				return result;	}@end