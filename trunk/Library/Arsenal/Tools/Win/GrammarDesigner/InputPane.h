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
#include "afxdockablepane.h"


class CInputEdit : public CRichEditCtrl
{
private:
		DECLARE_DYNAMIC(CInputEdit)

protected:
		CFont	m_font;
		HACCEL	m_acctbl;
public:
		CInputEdit();
		virtual ~CInputEdit();
public:
		void	ResetFont();
public:

		virtual BOOL PreTranslateMessage(MSG* pMsg);
		DECLARE_MESSAGE_MAP()
		afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
		afx_msg void OnEditCut();
		afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
		afx_msg void OnEditCopy();
		afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
		afx_msg void OnEditPaste();
		afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
		afx_msg void OnEditSelectAll();
		afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
		afx_msg void OnEditClear();
		afx_msg void OnUpdateEditClear(CCmdUI *pCmdUI);
		afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnInputFont();
		afx_msg void OnPopupOpen();
		afx_msg void OnPopupSave();
		
		afx_msg void OnEnChange();
		afx_msg void OnDropFiles(HDROP hDropInfo);
		afx_msg void OnPopupParse();
		afx_msg void OnUpdatePopupParse(CCmdUI *pCmdUI);
		afx_msg void OnEditUndo();
};


class CInputPane :	public CDockablePane
{
protected:
		CInputEdit		m_input;
public:
		CInputPane(void);
		~CInputPane(void);
protected:
		void Highlight(long start, long end, COLORREF color);

public:
		DECLARE_MESSAGE_MAP()
public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
public:
		afx_msg LRESULT OnLocatePos(WPARAM wp, LPARAM lp);
		afx_msg	LRESULT OnLocateToken(WPARAM wp, LPARAM lp);
public:

		int   GetInputLength();
		CString	GetInput()const;
};
