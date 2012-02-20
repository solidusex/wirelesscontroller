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
#include "afxwin.h"


// CStringConvDlg dialog

class CStringEdit : public CRichEditCtrl  //CEdit
{
private:
		HACCEL	m_acctbl;
		CFont	m_font;
public:
		CStringEdit();
		virtual ~CStringEdit();
		DECLARE_MESSAGE_MAP()
		afx_msg void OnEditSelectAll();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnEditCopy();
		afx_msg void OnEditCut();
		afx_msg void OnEditPaste();
		afx_msg void OnEditClear();
		afx_msg void OnEditUndo();
		afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


class CStringConvDlg : public CDialog
{
	DECLARE_DYNAMIC(CStringConvDlg)

public:
		CFont	m_font;
public:
	CStringConvDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStringConvDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_STR_CODE_CONV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
		afx_msg void OnBnClickedButtonToCode();
		afx_msg void OnBnClickedButtonToString();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual BOOL OnInitDialog();
		afx_msg void OnEnChangeEditString();
public:
		CStringEdit m_input_string;
		CStringEdit m_input_code;
};
