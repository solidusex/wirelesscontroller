
// WinSrv.h : main header file for the PROJECT_NAME application
//

/*
 * WiController
 * Copyright (c) 2012 by Solidus
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

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinSrvApp:
// See WinSrv.cpp for the implementation of this class
//

class CWinSrvApp : public CWinApp
{
public:
	CWinSrvApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWinSrvApp theApp;