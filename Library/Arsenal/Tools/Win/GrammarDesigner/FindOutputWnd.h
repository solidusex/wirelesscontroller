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




class CFindOutputList : public CListBox
{
private:
		DECLARE_DYNAMIC(CFindOutputList)
// Construction
public:
	CFindOutputList();

// Implementation
public:
	virtual ~CFindOutputList();
private:
		CFont			m_font;
public:

		struct Param
		{
				size_t	line;
				size_t	col;
				size_t	length;
				CWnd	*target;
				Param(size_t l = 0, size_t c = 0, size_t len = 0, CWnd	*tar = NULL) : line(l), col(c), length(len), target(tar)
				{

				}
		};
public:
		void	Append(const CString &msg, const Param &param);
		void	Clear();
public:
		DECLARE_MESSAGE_MAP()
		afx_msg void OnEditCopy();
		afx_msg void OnEditClear();
		afx_msg void OnFindOutputwndFont();
		afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
protected:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
		afx_msg void OnDestroy();
		afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
		afx_msg void OnUpdateEditClear(CCmdUI *pCmdUI);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};








// CFindOutputWnd

class CFindOutputWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CFindOutputWnd)
private:
		CFindOutputList	m_output;
public:
		void Clear();

		void	Append(const CString &msg, size_t line = 0, size_t col = 0, size_t length = 0, CWnd *target = NULL);
public:
	CFindOutputWnd();
	virtual ~CFindOutputWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnDestroy();
};


