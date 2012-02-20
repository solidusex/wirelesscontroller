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

// BackEndThread.cpp : implementation file
//

#include "stdafx.h"
#include "GrammarDesigner.h"
#include "BackEndThread.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//MSG
#define ID_USERMSG_WORKER_UNIT	(WM_USER + 104)


// CBackEndThread

IMPLEMENT_DYNCREATE(CBackEndThread, CWinThread)

CBackEndThread::CBackEndThread()
{
		
}

CBackEndThread::~CBackEndThread()
{
		Clear();
}

BOOL CBackEndThread::InitInstance()
{
		// TODO:  perform and per-thread initialization here
		m_bAutoDelete = FALSE;

		//::AfxMessageBox(TEXT("On Init Thread"));
		return TRUE;
}




int CBackEndThread::ExitInstance()
{
		// TODO:  perform any per-thread cleanup here
		return CWinThread::ExitInstance();
}


BOOL CBackEndThread::EndThread()
{
		HANDLE hdl = INVALID_HANDLE_VALUE;
		
		if(!::DuplicateHandle(::GetCurrentProcess(), *this, ::GetCurrentProcess(), &hdl, 0, FALSE, DUPLICATE_SAME_ACCESS))
		{
				goto ERROR_RET;
		}
		
		DWORD code = 0;
		if(!::GetExitCodeThread(hdl, &code) || code != STILL_ACTIVE)goto ERROR_RET;

		if(!this->PostThreadMessage(WM_QUIT, NULL, NULL))goto ERROR_RET;
		
		DWORD stat = ::WaitForSingleObject(hdl, INFINITE);
		
		if(stat == WAIT_OBJECT_0)
		{
				::CloseHandle(hdl);
				return TRUE;
		}
		else
		{
				goto ERROR_RET;
		}

ERROR_RET:
		VERIFY(FALSE);
		if(hdl != INVALID_HANDLE_VALUE)
		{
				::CloseHandle(hdl);
				hdl = INVALID_HANDLE_VALUE;
		}
		return FALSE;
}



void	CBackEndThread::PostWorker(CBackEndThread::CWorkerUnit *work)
{
		ASSERT(work != NULL);
		CSingleLock lock(&m_mtx);
		m_work_queue.AddTail(work);
		VERIFY(this->PostThreadMessage(ID_USERMSG_WORKER_UNIT, NULL, NULL));
}

void	CBackEndThread::Clear()
{
		CSingleLock lock(&m_mtx);

		while(!m_work_queue.IsEmpty())
		{
				CWorkerUnit *work = m_work_queue.GetHead();
				m_work_queue.RemoveHead();
				delete work;
		}
}

int CBackEndThread::Run()
{
		// TODO: Add your specialized code here and/or call the base class

		return CWinThread::Run();
}


BEGIN_MESSAGE_MAP(CBackEndThread, CWinThread)
		ON_THREAD_MESSAGE(ID_USERMSG_WORKER_UNIT, &CBackEndThread::OnWorkerUnit)
END_MESSAGE_MAP()


// CBackEndThread message handlers

void	CBackEndThread::OnWorkerUnit(WPARAM wparam, LPARAM lparam)
{
		CWorkerUnit *work = NULL;

		if(!m_work_queue.IsEmpty())
		{
				CSingleLock lock(&m_mtx);
				work = m_work_queue.GetHead();
				m_work_queue.RemoveHead();
		}

		if(work != NULL)
		{
				work->Run();
				delete work;
		}
}

