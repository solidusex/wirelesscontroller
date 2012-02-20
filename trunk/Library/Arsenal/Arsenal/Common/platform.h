/*
 * The Arsenal Library
 * Copyright (c) 2009 by Solidus
 * 
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express 
 * or implied warranty.
 *
 */

#ifndef AR_PLATFORM_H
#define AR_PLATFORM_H




/*
 Platform Identification
*/

#define OS_FREE_BSD      0x0001
#define OS_AIX           0x0002
#define OS_HPUX          0x0003
#define OS_TRU64         0x0004
#define OS_LINUX         0x0005
#define OS_MAC_OS_X      0x0006
#define OS_NET_BSD       0x0007
#define OS_OPEN_BSD      0x0008
#define OS_IRIX          0x0009
#define OS_SOLARIS       0x000a
#define OS_QNX           0x000b
#define OS_VXWORKS       0x000c
#define OS_CYGWIN        0x000d
#define OS_IOS			 0x000e
#define OS_UNKNOWN_UNIX  0x00ff
#define OS_WINDOWS_NT    0x1001
#define OS_WINDOWS_CE    0x1011
#define OS_VMS           0x2001



#if defined(__FreeBSD__)
	#define OS_FAMILY_UNIX								1
	#define OS_FAMILY_BSD								1
	#define OS_TYPE										OS_FREE_BSD
#elif defined(_AIX) || defined(__TOS_AIX__)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_AIX
#elif defined(hpux) || defined(_hpux)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_HPUX
#elif defined(__digital__) || defined(__osf__)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_TRU64
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_LINUX
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
		#define OS_FAMILY_UNIX								1
		#define OS_FAMILY_BSD								1
		#include <TargetConditionals.h>


		#if(TARGET_OS_MAC == 1)
				#define OS_TYPE										OS_MAC_OS_X
		#endif


		#if(TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1)
				#if defined(OS_TYPE)
						#undef OS_TYPE
				#endif

				#define OS_TYPE										OS_IOS
		#endif


#elif defined(__NetBSD__)
	#define OS_FAMILY_UNIX								1
	#define OS_FAMILY_BSD								1
	#define OS_TYPE										OS_NET_BSD
#elif defined(__OpenBSD__)
	#define OS_FAMILY_UNIX								1
	#define OS_FAMILY_BSD								1
	#define OS_TYPE										OS_OPEN_BSD
#elif defined(sgi) || defined(__sgi)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_IRIX
#elif defined(sun) || defined(__sun)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_SOLARIS
#elif defined(__QNX__)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_QNX
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_UNKNOWN_UNIX
#elif defined(_WIN32_WCE)
	#define OS_FAMILY_WINDOWS							1
	#define OS_TYPE										OS_WINDOWS_CE
#elif defined(_WIN32) || defined(_WIN64)
	#define OS_FAMILY_WINDOWS							1
	#define OS_TYPE										OS_WINDOWS_NT
#elif defined(__CYGWIN__)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_CYGWIN
#elif defined(__VMS)
	#define OS_FAMILY_VMS								1
	#define OS_TYPE										OS_VMS
#elif defined(ANDROID)
	#define OS_FAMILY_UNIX								1
	#define OS_TYPE										OS_ANDROID
#endif



/*
 Hardware Architecture and Byte Order
*/
#define ARCH_ALPHA   0x01
#define ARCH_IA32    0x02
#define ARCH_IA64    0x03
#define ARCH_MIPS    0x04
#define ARCH_HPPA    0x05
#define ARCH_PPC     0x06
#define ARCH_POWER   0x07
#define ARCH_SPARC   0x08
#define ARCH_X64	 0x09
#define ARCH_ARM     0x0a


#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
	#define ARCH										ARCH_ALPHA
	#define ARCH_LITTLE_ENDIAN							1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
	#define ARCH										ARCH_IA32
	#define ARCH_LITTLE_ENDIAN							1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define ARCH										ARCH_IA64
	#if defined(hpux) || defined(_hpux)
		#define ARCH_BIG_ENDIAN							1
	#else
		#define ARCH_LITTLE_ENDIAN						1
	#endif
#elif defined(__x86_64__) || defined(_M_X64)
	#define ARCH										ARCH_X64
	#define ARCH_LITTLE_ENDIAN							1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
	#define ARCH										ARCH_MIPS
	#define ARCH_BIG_ENDIAN								1
#elif defined(__hppa) || defined(__hppa__)
	#define ARCH										ARCH_HPPA
	#define ARCH_BIG_ENDIAN								1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || defined(__powerpc__) || defined(__ppc__) || defined(_ARCH_PPC) || defined(_M_PPC)
	#define ARCH										ARCH_PPC
	#define ARCH_BIG_ENDIAN								1
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || defined(_ARCH_PWR4) || defined(__THW_RS6000)
	#define ARCH										ARCH_POWER
	#define ARCH_BIG_ENDIAN								1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
	#define ARCH										ARCH_SPARC
	#define ARCH_BIG_ENDIAN								1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
	#define ARCH										ARCH_ARM
	#if defined(__ARMEB__)
		#define ARCH_BIG_ENDIAN							1
	#else
		#define ARCH_LITTLE_ENDIAN						1
	#endif
#endif












#endif


