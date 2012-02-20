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

#pragma once



// CBackEndThread

class CBackEndThread : public CWinThread
{
		DECLARE_DYNCREATE(CBackEndThread)
public:
		class CWorkerUnit
		{
		public:
				virtual void Run() = 0;
				virtual ~CWorkerUnit()
				{

				}
		};

private:
		CCriticalSection		m_mtx;
		CList<CWorkerUnit*>		m_work_queue;
public:
		CBackEndThread();           // protected constructor used by dynamic creation
		virtual ~CBackEndThread();
		
public:
		virtual BOOL InitInstance();
		virtual int ExitInstance();
public:
		//此函数不可在thread_func中调用
		BOOL EndThread();
public:
		void	PostWorker(CWorkerUnit *work);
		void	Clear();
protected:
		DECLARE_MESSAGE_MAP()

protected:
		void	OnWorkerUnit(WPARAM wparam, LPARAM lparam);
public:
		virtual int Run();
};


