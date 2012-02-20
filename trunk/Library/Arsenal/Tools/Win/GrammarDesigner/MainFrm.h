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


// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "OutputWnd.h"
#include "FindOutputWnd.h"
#include "ActionView.h"
#include "TagView.h"
#include "InputPane.h"
#include "SyntaxPane.h"



class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	
	CFont			  m_status_font;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	
/**/	
	COutputWnd			m_wndOutput;
	CFindOutputWnd		m_wndFindOutput;		
	CActionView			m_wndActView;
	CTagView			m_wndTag;

	CInputPane			m_inputPane;
	CSyntaxPane			m_syntaxPane;	

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusBarPanes(CCmdUI* pCmdUI);

	
	

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
		
public:

		CMFCStatusBar& GetStatusBar(void);
		CMFCMenuBar& GetMenuBar(void);
		CMFCToolBar& GetToolBar(void);
		CTagView&	GetTagView();
		COutputWnd&		GetOutputView();
		CActionView&	GetActionView();
		CInputPane&		GetInputPane();
		CSyntaxPane&	GetSyntaxPnae();
		CFindOutputWnd&	GetFindOutputView();
		void			ClearShow();
		
public:
		afx_msg void OnSize(UINT nType, int cx, int cy);

public:
		afx_msg void OnTestTest();
		afx_msg void OnShowOutput();
		afx_msg void OnShowSyntaxtree();
		afx_msg void OnShowActionview();
		afx_msg void OnShowTagview();
		afx_msg void OnShowInput();
		afx_msg void OnShowFindresults();
		afx_msg void OnClose();
		afx_msg void OnAppExit();

protected:
		WINDOWPLACEMENT			m_OldWndPlacement;//用来保存原窗口位置 
		BOOL					m_bFullScreen;//全屏显示标志 
		CRect					m_FullScreenRect;//表示全屏显示时的窗口位置

protected:
		HACCEL					m_acctbl;

		

public:
		afx_msg void OnViewFullscreen();
		afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		
};


