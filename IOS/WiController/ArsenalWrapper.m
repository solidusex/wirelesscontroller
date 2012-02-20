//
//  ArsenalWrapper.m
//  WiController
//
//  Created by peng liu on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import "ArsenalWrapper.h"
#import "NSString_Convert.h"







static void AR_STDCALL __g_on_error(int_t level, const wchar_t* msg, void *ctx)
{
        AR_ASSERT(ctx != NULL);
        AR_ASSERT(msg != NULL);

        ArsenalWrapper  *ar = (ArsenalWrapper*)ctx;
        
        
        [ar onError : level
                Msg : [NSString stringWithWideString : msg]
         ];
}

static void AR_STDCALL __g_on_print(const wchar_t *msg, void *ctx)
{
        AR_ASSERT(ctx != NULL);
        AR_ASSERT(msg != NULL);
        
        ArsenalWrapper  *ar = (ArsenalWrapper*)ctx;
        
        
        [ar onPrint : [NSString stringWithWideString : msg]  ];
		
}





static ArsenalWrapper   *__g_arsenal = NULL;
@implementation ArsenalWrapper

+(void)instance
{
        if(__g_arsenal == nil)
        {
                __g_arsenal = [[ArsenalWrapper alloc] init];
        
                if(__g_arsenal == nil)
                {
                        abort();
                }
        
                arInit_t ai = {{__g_on_error, __g_on_print, (void*)__g_arsenal}};
		
                if(Arsenal_Init(&ai) != AR_S_YES)
                {
                        [__g_arsenal dealloc];
                        abort();
                }
        }
        
}


+(void)unInstance
{
        if(__g_arsenal != nil)
        {
                Arsenal_UnInit();
                [__g_arsenal release];
        }
}






-(id)init
{
        if((self = [super init]) != nil)
        {
                
        }
        
        return self;
}

-(void)dealloc
{
        
        [super dealloc];
}



-(void)onPrint : (NSString*) msg
{
        NSLog(@"%@", msg);
}

-(void)onError : (int)level  Msg : (NSString*)msg
{
        NSLog(@"error level = %d, error msg = '%@'", level, msg);
}

@end



#if(0)

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



@implementation WideCharWrapper 

+(id)WideCharWithString : (const wchar_t*)s
{
		assert(s != NULL);
		WideCharWrapper *wrapper = [[WideCharWrapper alloc] init];
		[wrapper setString : s];
		[wrapper autorelease];
		return wrapper;
		
}

-(id)init
{
		self = [super init];
		if(self)
		{
				string = healper_wcsndup(L"", 0);
		}
		return self;
}

-(void)dealloc
{
		if(string)
		{
				free(string);
				string = NULL;
		}
		
		[super dealloc];
}


-(void)setString : (const wchar_t*)s
{
		if(string)
		{
				free(string);
				string = NULL;
		}
		
		if(s== NULL)
		{
				string = healper_wcsndup(L"", 0);
		}else
		{
				string = healper_wcsndup(s, wcslen(s));
		}
        
}

-(const wchar_t*)string
{
		return string;
}


@end






wchar_t* healper_wcsndup(const wchar_t *sour, size_t len)
{
		wchar_t *result;
		size_t i;
		AR_ASSERT(sour != NULL);
		
		result = (wchar_t*)malloc(sizeof(wchar_t) * (len + 1));
		for(i = 0; i < len; ++i)result[i] = sour[i];
		result[len] = L'\0';
		return result;
}




@implementation ARUtility

-(id)init
{
		self = [super init];
		
		if(self)
		{
				
		}
		
		return self;
}

/*
 size_t					AR_wcs_to_str(arCodePage_t cp, const wchar_t *input, size_t n, char *out, size_t out_len);
 
 */
+(NSString*)convertUTF32ToNSString		:		(const wchar_t*)input
{
		char *utf8 = NULL;
		assert(input != NULL);
		size_t n = wcslen(input), need_n = 0;
		if(n == 0)
		{
				return @"";
		}
		
		need_n = AR_wcs_to_str(AR_CP_UTF8, input, n, NULL, 0);
		
		if(need_n == 0)
		{
				@throw [ARStringConvertException exceptionWithReason : @"can't convert wchar* to utf8 string"];
		}
		
		utf8 = (char*)malloc(sizeof(char) * (need_n + 1));
		need_n = AR_wcs_to_str(AR_CP_UTF8, input, n, utf8, need_n);
		
		if(need_n == 0)
		{
				@throw [ARStringConvertException exceptionWithReason : @"can't convert wchar* to utf8 string"];
		}
		utf8[need_n] = 0;
		NSString *ret = [NSString stringWithUTF8String : utf8];
		
		if(utf8)
		{
				free(utf8);
				utf8 = NULL;
		}
		
		return ret;
		
}

+(NSString*)convertUTF32ToNSString		:		(const wchar_t*)input Length : (size_t)len
{
		if(len == 0)
		{
				return @"";
		}
		
		assert(input != NULL);
		
		wchar_t *wcs = healper_wcsndup(input, len);
		if(wcs == NULL)
		{
				return NULL;
		}
		
		NSString *ret = [ARUtility convertUTF32ToNSString : wcs];
		free(wcs);
		wcs = NULL;
		return ret;
		
}


+(WideCharWrapper*) convertNSStringToUTF32		:		(NSString*)input
{
		
		const char *utf8 = [input cStringUsingEncoding:NSUTF8StringEncoding];
		
		size_t len;
		
		len = AR_str_to_wcs(AR_CP_UTF8, utf8, strlen(utf8), NULL, 0);
		
		if(len == 0)
		{
				@throw [ARStringConvertException exceptionWithReason : @"can't convert utf8* to wchar_t* string"];
		}
		
		
		wchar_t *ret = (wchar_t*)malloc(sizeof(wchar_t) * (len + 1));
		
		len = AR_str_to_wcs(AR_CP_UTF8, utf8, strlen(utf8), ret, len);
		
		if(len == 0)
		{
				free(ret);
				ret = NULL;
				@throw [ARStringConvertException exceptionWithReason : @"can't convert utf8* to wchar_t* string"];
		}else
		{
				ret[len] = 0;
		}
		
		WideCharWrapper *wrapper = [WideCharWrapper WideCharWithString : ret];
		free(ret);
        
		return wrapper;
		
}

@end


#endif
