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


// CActionView



class CActionCtrl : public CListCtrl
{
private:
		DECLARE_DYNAMIC(CActionCtrl)
public:
		CActionCtrl();
		virtual ~CActionCtrl();
protected:
		DECLARE_MESSAGE_MAP()
private:
		CFont			m_font;
public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
		afx_msg void OnActionViewFont();
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnEditCopy();
		afx_msg void OnUpdateOutputwndFont(CCmdUI *pCmdUI);
		afx_msg void OnEditClear();
//		afx_msg void OnViewAction();
};


class CActionView : public CDockablePane
{
	DECLARE_DYNAMIC(CActionView)
		
public:
	CActionView();
	virtual ~CActionView();

protected:
	DECLARE_MESSAGE_MAP()

private:
		CActionCtrl		m_list;
public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);

public:
		void	DrawActionView(const ARSpace::psrActionView_t *view);
		void	DrawConflictView(const ARSpace::psrConflictView_t *view);
		
		
		void	DrawFirstFollowView(const ARSpace::psrStatusView_t *view);

		void	DrawLeftRecursionView(const ARSpace::psrStatusView_t *view);
		void	DrawLeftFactorView(const ARSpace::psrStatusView_t *view);
		
		void	Clear();
};


