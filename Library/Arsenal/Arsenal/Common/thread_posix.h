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
#include "common.h"





AR_NAMESPACE_BEGIN

static arSpinLock_t		__g_atomic_lock;

void			AR_InitThread()
{
		AR_InitSpinLock(&__g_atomic_lock);

}

void			AR_UnInitThread()
{
		AR_UnInitSpinLock(&__g_atomic_lock);

}

int_t			AR_AtomicInc(volatile int_t *dest)
{
		AR_LockSpinLock(&__g_atomic_lock);
		*dest += 1;
		AR_UnLockSpinLock(&__g_atomic_lock);
		return *dest;
}

int_t			AR_AtomicDec(volatile int_t *dest)
{
		AR_LockSpinLock(&__g_atomic_lock);
		*dest -= 1;
		AR_UnLockSpinLock(&__g_atomic_lock);
		return *dest;
}


/****************************************************************************SpinLock***********************************************/



void			AR_YieldThread()
{
	pthread_yield();
}

void			AR_Sleep(size_t millisecond)
{
		long m = (long)millisecond;
		
		struct timeval tv;
		tv.tv_sec = m / 1000;
		tv.tv_usec = (m % 1000) * 1000;
		
		int ret = select(0,NULL,NULL,NULL,&tv);
		if(ret == -1)
		{
				AR_error(AR_ERR_WARNING, L"AR_Sleep failed\r\n");
		}

}

void			AR_InitSpinLock(arSpinLock_t *lock)
{
		AR_ASSERT(lock != NULL);
		pthread_spin_init((pthread_spinlock_t*)lock,0);

}

void			AR_UnInitSpinLock(arSpinLock_t *lock)
{
		AR_ASSERT(lock != NULL);
		pthread_spin_destroy((pthread_spinlock_t*)lock);
}

void			AR_LockSpinLock(arSpinLock_t *lock)
{
		AR_ASSERT(lock != NULL);
		pthread_spin_lock((pthread_spinlock_t*)lock);
}


void			AR_UnLockSpinLock(arSpinLock_t *lock)
{
		AR_ASSERT(lock != NULL);
		/*COMP_EXCH(lock, (LONG)UNLOCK_STATE, (LONG)LOCK_STATE);*/
		pthread_spin_unlock((pthread_spinlock_t*)lock);
}


/**********************************************************************************************************************************end*/

#define RESOLUTION		1000000LL

uint_64_t		AR_GetTime_Microseconds()
{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (uint_64_t)tv.tv_sec * (uint_64_t)RESOLUTION + (uint_64_t)tv.tv_usec;
}


AR_NAMESPACE_END


