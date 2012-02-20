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



class COutputList : public CListBox
{
private:
		DECLARE_DYNAMIC(COutputList)
// Construction
public:
	COutputList();

// Implementation
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
//	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
public:
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
		CFont			m_font;
public:
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
		afx_msg void OnOutputwndFont();
protected:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
		enum MsgType{MSG_MESSAGE, MSG_ERROR};

		struct Param
		{
				MsgType	type;
				size_t	line;
				CWnd	*target;

				Param(MsgType t = MSG_MESSAGE, size_t l = 0, CWnd	*tar = NULL) : type(t), line(l), target(tar)
				{

				}
		};
public:
		void	Append(const CString &msg, const Param &param);
		
		void	Clear();
		afx_msg void OnDestroy();
};






class COutputWnd : public CDockablePane
{
// Construction
public:
	COutputWnd();

// Attributes
protected:
	COutputList			m_output;


protected:

// Implementation
public:
	virtual ~COutputWnd();

	

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:

		
	void	Append(const CString &msg, COutputList::MsgType type = COutputList::MSG_MESSAGE, size_t line = 0, CWnd *target = NULL);
	void	Clear();	
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
};



