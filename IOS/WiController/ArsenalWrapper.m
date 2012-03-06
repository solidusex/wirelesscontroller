//
//  ArsenalWrapper.m
//  WiController
//
//  Created by solidus on 2/20/12.
//  Copyright (c) 2012 none. All rights reserved.
//



#import "ArsenalWrapper.h"
#import "NSString_Convert.h"



typedef struct __in_addr_equal 
{
        union {
                struct 
                { unsigned char s_b1,s_b2,s_b3,s_b4; 
                }S_un_b;
                __uint32_t S_addr;
        } S_un;

#define s_net   S_un.S_un_b.s_b1    // network
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_lh    S_un.S_un_b.s_b3    // logical host
#define s_impno S_un.S_un_b.s_b4    // imp #

} __IN_ADDR;




struct __sockaddr_in_equal
{
        __uint8_t	sin_len;
        sa_family_t	sin_family;
        in_port_t	sin_port;
        __IN_ADDR   sin_addr;
        char		sin_zero[8];
};


#define _IP1(_addr)		((_addr)->sin_addr.s_net)
#define _IP2(_addr)		((_addr)->sin_addr.s_host)

#define _IP3(_addr)		((_addr)->sin_addr.s_lh)
#define _IP4(_addr)		((_addr)->sin_addr.s_impno)



int_t	AR_ipv4cmp(const struct sockaddr_in	*l, const struct sockaddr_in	*r)
{
        int_t cmp = 0;
        struct __sockaddr_in_equal l_tmp,r_tmp;
        AR_ASSERT(l != NULL && r != NULL);
        
        memcpy(&l_tmp, l, sizeof(*l));
        memcpy(&r_tmp, r, sizeof(*r));
        
		cmp = _IP1(&l_tmp) - _IP1(&r_tmp);
		if(cmp != 0)return cmp;
        
		cmp = _IP2(&l_tmp) - _IP2(&r_tmp);
		if(cmp != 0)return cmp;
        
		cmp = _IP3(&l_tmp) - _IP3(&r_tmp);
		if(cmp != 0)return cmp;
        
		cmp = _IP4(&l_tmp) - _IP4(&r_tmp);
		if(cmp != 0)return cmp;
        
		return 0;
        
}



bool_t	AR_ipv4add(struct sockaddr_in	*addr)
{
        struct __sockaddr_in_equal addr_tmp;
		AR_ASSERT(addr != NULL);
        
        memcpy(&addr_tmp, addr, sizeof(*addr));

        
		if(_IP4(&addr_tmp) < 255)
		{
				_IP4(&addr_tmp)++;
                memcpy(addr, &addr_tmp, sizeof(addr_tmp));
				return true;
		}else
		{
				_IP4(&addr_tmp) = 0;
		}
        
        
		if(_IP3(&addr_tmp) < 255)
		{
				_IP3(&addr_tmp)++;
                memcpy(addr, &addr_tmp, sizeof(addr_tmp));
				return true;
		}else
		{
				_IP3(&addr_tmp) = 0;
		}
        
        
		if(_IP2(&addr_tmp) < 255)
		{
				_IP2(&addr_tmp)++;
                memcpy(addr, &addr_tmp, sizeof(addr_tmp));
				return true;
		}else
		{
				_IP2(&addr_tmp) = 0;
		}
        
        
		if(_IP1(&addr_tmp) < 255)
		{
				_IP1(&addr_tmp)++;
                memcpy(addr, &addr_tmp, sizeof(addr_tmp));
				return true;
		}else
		{
				_IP1(&addr_tmp) = 0;
		}
        
        memcpy(addr, &addr_tmp, sizeof(addr_tmp));
		return false;
}


#undef _IP1
#undef _IP2
#undef _IP3
#undef _IP4





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

+(ArsenalWrapper*)sharedArsenalWrapper
{
        return __g_arsenal;
}




-(id)init
{
        if((self = [super init]) != nil)
        {
                tmp = NULL;
        }
        
        return self;
}

-(void)dealloc
{
        [super dealloc];
        
        if(tmp != NULL)
        {
                AR_DEL(tmp);
                tmp = NULL;
        }
        
}



-(void)onPrint : (NSString*) msg
{
        NSLog(@"%@", msg);
}

-(void)onError : (int)level  Msg : (NSString*)msg
{
        NSLog(@"error level = %d, error msg = '%@'", level, msg);
}


-(const wchar_t*) strConvertToWideString : (const char*)str
{
        if(str != NULL)
        {
                tmp = AR_str_convto_wcs(AR_CP_UTF8, str, strlen(str));
        }
        
        if(tmp == NULL)
        {
                tmp = AR_wcsdup(L"");
        }
        
        return tmp;
}

-(const wchar_t*) stringConvertToWideString : (NSString*)str
{
        AR_ASSERT(str != nil);
        
        if(tmp != NULL)
        {
                AR_DEL(tmp);
                tmp = NULL;
        }
        
        const char *utf8 = [str UTF8String];
        
        if(utf8 != NULL)
        {
                tmp = AR_str_convto_wcs(AR_CP_UTF8, utf8, strlen(utf8));
        }
        
        if(tmp == NULL)
        {
                tmp = AR_wcsdup(L"");
        }
        
        return tmp;
}




-(BOOL) addIPV4Address : (struct sockaddr_in*)addr
{
        return AR_ipv4add(addr) ? YES : NO;
}

-(NSInteger)compareIPV4Address : (const struct sockaddr_in*)l with : (const struct sockaddr_in*)r
{
        return AR_ipv4cmp(l, r);
}

@end


