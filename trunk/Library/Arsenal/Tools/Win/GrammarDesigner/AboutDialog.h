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
#include "HyperLink.h"


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
private:
		CString			m_name;
		CString			m_ver;
		CString			m_arsenal_ver;
		CString			m_copyright;
		CString			m_homepage;
private:
		CHyperLink		m_hplink;
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
		virtual BOOL OnInitDialog();
		afx_msg void OnStnClickedHomepage();
};
