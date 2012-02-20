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


// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#include "GrammarDesigner.h"

#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame


const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx);

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)

	ON_UPDATE_COMMAND_UI_RANGE(ID_INDICATOR_LINE, ID_INDICATOR_COL, &CMainFrame::OnUpdateStatusBarPanes)

	
		

	ON_WM_SIZE()
	ON_COMMAND(ID_SHOW_OUTPUT, &CMainFrame::OnShowOutput)
	ON_COMMAND(ID_SHOW_SYNTAXTREE, &CMainFrame::OnShowSyntaxtree)
	ON_COMMAND(ID_SHOW_ACTIONVIEW, &CMainFrame::OnShowActionview)
	ON_COMMAND(ID_SHOW_TAGVIEW, &CMainFrame::OnShowTagview)
	ON_COMMAND(ID_SHOW_INPUT, &CMainFrame::OnShowInput)

	//ON_COMMAND(ID_TEST_TEST, &CMainFrame::OnTestTest)

	
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(ID_VIEW_FULLSCREEN, &CMainFrame::OnViewFullscreen)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_SHOW_FINDRESULTS, &CMainFrame::OnShowFindresults)
END_MESSAGE_MAP()

static UINT indicators[] =
{
		ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_LINE,
		ID_INDICATOR_COL,
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() 
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_AQUA);

	m_bFullScreen	= FALSE;
	memset(&m_OldWndPlacement, 0, sizeof(m_OldWndPlacement));
	memset(&m_FullScreenRect, 0, sizeof(m_FullScreenRect));
	

	m_acctbl = ::LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	VERIFY(m_acctbl);
}

CMainFrame::~CMainFrame()
{
}


/**************************************************************************************/




int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	

	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	
/*
	m_wndMenuBar.SetRecentlyUsedMenus(FALSE);
	
	m_wndMenuBar.SetShowAllCommands(TRUE);
	*/

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_status_font.CreatePointFont(110, TEXT("Consolas"));
	m_wndStatusBar.SetFont(&m_status_font);


	
	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}


	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

#if(0)
	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
#endif

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	HICON ico = AfxGetApp()->LoadIconW(IDR_MAINFRAME);
	SetIcon(ico,true);

/*******************************************************/
	
	
	return 0;
}

void CMainFrame::OnClose()
{
		// TODO: Add your message handler code here and/or call default
		CFrameWndEx::OnClose();
}



void CMainFrame::OnAppExit()
{
		// TODO: Add your command handler code here
		SendMessage(WM_CLOSE);	
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
		BOOL bNameValid;
		// Create output window
		CString strOutputWnd;
		bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
		ASSERT(bNameValid);
		if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
		{
				TRACE0("Failed to create Output window\n");
				return FALSE; // failed to create
		}





		CString strActView;

		bNameValid = strActView.LoadString(IDS_ACTVIEW_WND);

		ASSERT(bNameValid);

		if (!m_wndActView.Create(strActView, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_ACTIONWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP | CBRS_FLOAT_MULTI))
		{
				TRACE0("Failed to create Action window\n");
				return FALSE; // failed to create
		}

		CString strTagView;


		bNameValid = strTagView.LoadString(IDS_TAGVIEW_WND);

		if(!m_wndTag.Create(strTagView, this, CRect(0,0,100,100), TRUE, ID_VIEW_TAGWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
		{
				TRACE0("Failed to create TagView window\n");
				return FALSE; // failed to create
		}

		CString strInputView;
		bNameValid = strInputView.LoadString(IDS_INPUTVIEW_WND);

		if(!m_inputPane.Create(strInputView, this, CRect(0,0,100,100), TRUE, ID_INPUTVIEW_WND ,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP | CBRS_FLOATING))
		{
				TRACE0("Failed to create input  window\n");
				return FALSE; // failed to create
		}



		CString strSyntaxPane;

		bNameValid = strSyntaxPane.LoadString(IDS_SYNTAXPANE_WND);

		if(!m_syntaxPane.Create(strSyntaxPane, this, CRect(0,0,100,100), TRUE, ID_SYNTAXPANE_WND ,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
		{
				TRACE0("Failed to create syntax tree  window\n");
				return FALSE; // failed to create
		}



		CString strFindOutputWnd;
		bNameValid = strFindOutputWnd.LoadString(IDS_FIND_OUTPUT_WND);

		if (!m_wndFindOutput.Create(strFindOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_FIND_OUTPPUT_WND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
		{
				TRACE0("Failed to create FindOutput window\n");
				return FALSE; // failed to create
		}


		SetDockingWindowIcons(theApp.m_bHiColorIcons);



		m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_wndOutput, AFX_IDW_DOCKBAR_BOTTOM);

		m_wndActView.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_wndActView, AFX_IDW_DOCKBAR_TOP);


		m_wndTag.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_wndTag, AFX_IDW_DOCKBAR_LEFT);


		m_inputPane.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_inputPane, AFX_IDW_DOCKBAR_RIGHT);


		m_syntaxPane.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_syntaxPane, AFX_IDW_DOCKBAR_RIGHT);


		m_wndFindOutput.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_wndFindOutput, AFX_IDW_DOCKBAR_BOTTOM);



		
		/***************************************设置某些Pane大小*********************************/
		
		CRect mainfrm_rect;
		this->GetWindowRect(&mainfrm_rect);

		CRect rect;


		m_wndTag.GetWindowRect(rect);
		//rect.right += 150;
		rect.right = (LONG)(mainfrm_rect.right * 0.3);
		m_wndTag.MoveWindow(rect);

		m_syntaxPane.GetWindowRect(rect);
		rect.left = (LONG)(mainfrm_rect.right * 0.65);
		m_syntaxPane.MoveWindow(rect);



		m_wndActView.GetWindowRect(rect);
		rect.bottom = (LONG)(mainfrm_rect.bottom * 0.6);
		m_wndActView.MoveWindow(rect);


		m_wndOutput.GetWindowRect(rect);
		rect.top = (LONG)(mainfrm_rect.bottom * 0.7);
		m_wndOutput.MoveWindow(rect);
		m_wndFindOutput.MoveWindow(rect);





		/***************************************设置某些Pane自动隐藏*********************************/
		m_inputPane.DockToWindow(&m_syntaxPane, CBRS_ALIGN_TOP);
		m_wndFindOutput.DockToWindow(&m_wndOutput, CBRS_ALIGN_RIGHT);

		m_wndActView.SetAutoHideMode(TRUE, CBRS_ALIGN_TOP);
		m_wndOutput.SetAutoHideMode(TRUE, CBRS_ALIGN_BOTTOM);
		m_wndFindOutput.SetAutoHideMode(TRUE, CBRS_ALIGN_BOTTOM);




		



		return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);


	HICON hActViewBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndActView.SetIcon(hActViewBarIcon, FALSE);

	HICON hTagViewBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndTag.SetIcon(hTagViewBarIcon, FALSE);

	HICON hInputViewBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_inputPane.SetIcon(hInputViewBarIcon, FALSE);


	HICON hSyntaxPaneBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_syntaxPane.SetIcon(hSyntaxPaneBarIcon, FALSE);

}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

CMFCStatusBar& CMainFrame::GetStatusBar(void)
{
		return this->m_wndStatusBar;
}

CMFCMenuBar& CMainFrame::GetMenuBar(void)
{
		//TODO: insert return statement here
		return this->m_wndMenuBar;
}

CMFCToolBar& CMainFrame::GetToolBar(void)
{
		//TODO: insert return statement here
		return this->m_wndToolBar;
}


CTagView&	CMainFrame::GetTagView()
{
		return this->m_wndTag;

}

COutputWnd&		CMainFrame::GetOutputView()
{
		return this->m_wndOutput;
}

CFindOutputWnd&	CMainFrame::GetFindOutputView()
{
		return this->m_wndFindOutput;
}

CActionView&	CMainFrame::GetActionView()
{
		return this->m_wndActView;
}


CInputPane&		CMainFrame::GetInputPane()
{
		return this->m_inputPane;
}

CSyntaxPane&	CMainFrame::GetSyntaxPnae()
{
		return m_syntaxPane;
}

void	CMainFrame::ClearShow()
{
		m_wndActView.Clear();
		m_wndOutput.Clear();
		m_syntaxPane.Clear();
}

void CMainFrame::OnUpdateStatusBarPanes(CCmdUI* pCmdUI)
{
		pCmdUI->Enable(TRUE);

		CRichEditView *view = (CRichEditView*)this->GetActiveView();
		
		if(view)
		{


				CPoint   VarCharPoint;                   //指定字符的位置   
				CPoint   CurrPoint;                         //当前光标位置   
				int   LineFirstIndex;                     //当前行首字符位置   
				int   Length;                                     //当前行长度   

				int   CurrentCharIndex = 0;                 //当前编辑光标所在字符序号。   
				int   CurrentLine= 0;                           //当前编辑光标所在的行号   
				int   CurrentRow= 0;                             //当前编辑光标所在的列号   
				int   i;
				CurrPoint   =   view->GetRichEditCtrl().GetCaretPos();                 //获取光标位置   
				LineFirstIndex   =   view->GetRichEditCtrl().LineIndex(-1);       //获取当前行首字符位置   
				Length   =   view->GetRichEditCtrl().LineLength(-1);                     //获取当前行长度.   

				for   (i  =   0;   i   <   Length;   i++)   
				{   
						VarCharPoint   =  view->GetRichEditCtrl(). GetCharPos(   LineFirstIndex   );   
						if   (VarCharPoint.x   >=   CurrPoint.x)   
						{   
								CurrentCharIndex   =   LineFirstIndex;   
								break;   
						}   
						LineFirstIndex++;   
				}   
				
				CurrentRow   =   i;   //列号   
                CurrentLine   =   view->GetRichEditCtrl().LineFromChar(   -1   );   //行号   


				int line = CurrentLine;
				int col = CurrentRow;



				CString str;
				str.Format(TEXT("Ln %d"), line);

				this->GetStatusBar().SetPaneText(this->GetStatusBar().CommandToIndex(ID_INDICATOR_LINE), str);

				str.Format(TEXT("Col %d"), col);
				this->GetStatusBar().SetPaneText(this->GetStatusBar().CommandToIndex(ID_INDICATOR_COL), str);
		}
}



void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
		CFrameWndEx::OnSize(nType, cx, cy);

		// TODO: Add your message handler code here

		if(this->GetStatusBar().GetSafeHwnd() != NULL)
		{
				m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
				float w = (float)cx;
				this->GetStatusBar().SetPaneInfo(1, ID_INDICATOR_LINE, SBPS_NORMAL, (int)(w * 0.08));
				this->GetStatusBar().SetPaneInfo(2, ID_INDICATOR_COL, SBPS_NORMAL, (int)(w * 0.08));
				this->GetStatusBar().SetPaneInfo(3, ID_INDICATOR_CAPS, SBPS_NORMAL, (int)(w * 0.03));
				this->GetStatusBar().SetPaneInfo(4, ID_INDICATOR_NUM, SBPS_NORMAL, (int)(w * 0.03));
				this->GetStatusBar().SetPaneInfo(5, ID_INDICATOR_SCRL, SBPS_NORMAL, (int)(w * 0.03));
		}
}






void CMainFrame::OnShowOutput()
{
		// TODO: Add your command handler code here

		this->ShowPane(&m_wndOutput, TRUE, TRUE, TRUE);
}

void CMainFrame::OnShowSyntaxtree()
{
		// TODO: Add your command handler code here
		this->ShowPane(&m_syntaxPane, TRUE, TRUE, TRUE);
}

void CMainFrame::OnShowActionview()
{
		// TODO: Add your command handler code here
		this->ShowPane(&m_wndActView, TRUE, TRUE, TRUE);
}

void CMainFrame::OnShowTagview()
{
		// TODO: Add your command handler code here
		this->ShowPane(&m_wndTag, TRUE, TRUE, TRUE);
}

void CMainFrame::OnShowInput()
{
		// TODO: Add your command handler code here
		this->ShowPane(&m_inputPane, TRUE, TRUE, TRUE);
}

void CMainFrame::OnShowFindresults()
{
		// TODO: Add your command handler code here
		this->ShowPane(&m_wndFindOutput, TRUE, TRUE, TRUE);
}


void CMainFrame::OnTestTest()
{
		OnShowInput();
		
}


void CMainFrame::OnViewFullscreen()
{
		if(!m_bFullScreen)
		{
				((CWinAppEx*)AfxGetApp())->SaveState(this, TEXT("FullScreen"));

				GetWindowPlacement(&m_OldWndPlacement); 
				CRect WindowRect;
				GetWindowRect(&WindowRect); 
				CRect ClientRect; 
				RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);
				ClientToScreen(&ClientRect); 
				// 获取屏幕的分辨率 

				int nFullWidth=GetSystemMetrics(SM_CXSCREEN); 
				int nFullHeight=GetSystemMetrics(SM_CYSCREEN); 
				//将除控制条外的客户区全屏显示到从(0,0)到(nFullWidth, nFullHeight)区域, 
				//将(0,0)和(nFullWidth, nFullHeight)两个点外扩充原窗口和除控制条之外的 客户区位置间的差值, 就得到全屏显示的窗口位置 

				
				m_FullScreenRect.left = WindowRect.left - ClientRect.left; 
				m_FullScreenRect.top = WindowRect.top - ClientRect.top; 
				m_FullScreenRect.right = WindowRect.right - ClientRect.right + nFullWidth; 
				m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;

				
				m_bFullScreen = TRUE;  //设置全屏显示标志为 TRUE 
				//进入全屏显示状态 

				WINDOWPLACEMENT wndpl;
				wndpl.length=sizeof(WINDOWPLACEMENT); 
				wndpl.flags=0; 
				wndpl.showCmd=SW_SHOWNORMAL; 
				wndpl.rcNormalPosition=m_FullScreenRect; 
				//SetWindowPlacement(&wndpl);
				this->SetWindowPos(&wndTopMost, m_FullScreenRect.left, m_FullScreenRect.top, m_FullScreenRect.Width(), m_FullScreenRect.Height(),SWP_SHOWWINDOW   );

		}else
		{
				//退出全屏显示, 恢复原窗口显示
				m_bFullScreen = FALSE;
				ShowWindow(SW_HIDE); 
				SetWindowPlacement(&m_OldWndPlacement);

				((CWinAppEx*)AfxGetApp())->LoadState(this, TEXT("FullScreen"));
				
		}
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
		// TODO: Add your message handler code here and/or call default

		if(m_bFullScreen)
		{
				lpMMI->ptMaxSize.x=m_FullScreenRect.Width(); 
				lpMMI->ptMaxSize.y=m_FullScreenRect.Height(); 
				lpMMI->ptMaxPosition.x=m_FullScreenRect.Width(); 
				lpMMI->ptMaxPosition.y=m_FullScreenRect.Height(); 
				// 最大的Track尺寸也要改变 
				lpMMI->ptMaxTrackSize.x=m_FullScreenRect.Width(); 
				lpMMI->ptMaxTrackSize.y=m_FullScreenRect.Height(); 
		}

		CFrameWnd::OnGetMinMaxInfo(lpMMI) ; 
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
		// TODO: Add your specialized code here and/or call the base class

		if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) 
		{ 
				if(::TranslateAccelerator(this->GetSafeHwnd(), m_acctbl, pMsg))
				{
						return true;
				}
		}

		return CFrameWndEx::PreTranslateMessage(pMsg);
}

