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


// GrammarDesigner.h : main header file for the GrammarDesigner application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGrammarDesignerApp:
// See GrammarDesigner.cpp for the implementation of this class
//

class CGrammarDesignerApp : public CWinAppEx
{
public:
	CGrammarDesignerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

public:
		
		//BOOL OnThreadMessage(MSG* pMsg);
		virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CGrammarDesignerApp theApp;
