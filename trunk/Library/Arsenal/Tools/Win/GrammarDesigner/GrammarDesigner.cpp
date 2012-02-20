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


// GrammarDesigner.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"



#include "afxwinappex.h"

#include "DocManagerEx.h"


#include "GrammarDesigner.h"
#include "MainFrm.h"

#include "GrammarDesignerDoc.h"
#include "GrammarDesignerView.h"
#include "AboutDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CGrammarDesignerApp

BEGIN_MESSAGE_MAP(CGrammarDesignerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGrammarDesignerApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)


END_MESSAGE_MAP()


// CGrammarDesignerApp construction

CGrammarDesignerApp::CGrammarDesignerApp()
{
		
	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CGrammarDesignerApp object

CGrammarDesignerApp theApp;


// CGrammarDesignerApp initialization
/*
typedef struct __ar_init_tag
{
		arIOCtx_t		global_io_ctx;
}arInit_t;
*/

static void	AR_STDCALL	__dummy_error_func(int_t level, const wchar_t *msg, void *ctx)
{

}

static void	AR_STDCALL	__dummy_print_func(const wchar_t *msg, void *ctx)
{

}

static const ARSpace::arInit_t	__dummy_context = 
{
		{
		__dummy_error_func,
		__dummy_print_func,
		NULL
		}
};

BOOL CGrammarDesignerApp::InitInstance()
{

		ARSpace::Arsenal_Init(&__dummy_context);
	

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(REGENTRY_NAME);


	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGrammarDesignerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGrammarDesignerView));
	if (!pDocTemplate)
		return FALSE;

	ASSERT(m_pDocManager == NULL);
	m_pDocManager = new CDocManagerEx();
		
	AddDocTemplate(pDocTemplate);


	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	

	test_func();

	return TRUE;
}



int CGrammarDesignerApp::ExitInstance()
{
		// TODO: Add your specialized code here and/or call the base class
		
		
		int stat = CWinAppEx::ExitInstance();
		ARSpace::Arsenal_UnInit();
		return stat;
}


// App command to run the dialog
void CGrammarDesignerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CGrammarDesignerApp customization load/save methods

void CGrammarDesignerApp::PreLoadState()
{

	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGrammarDesignerApp::LoadCustomState()
{
}

void CGrammarDesignerApp::SaveCustomState()
{
}

// CGrammarDesignerApp message handlers




/*
BOOL CGrammarDesignerApp::OnThreadMessage(MSG* pMsg)
{
		switch(pMsg->wParam)
		{
		case ID_BUILD_CFG_COMPLETED:
		{
				CGrammarDesignerDoc *pdoc = (CGrammarDesignerDoc*)((CMainFrame*)::AfxGetMainWnd())->GetActiveDocument();
				pdoc->OnTagBuildCompleted((ARSpace::cfgConfig_t*) pMsg->lParam);
				return TRUE;
				break;
		}
		default:
				VERIFY(FALSE);
				return FALSE;
		}

}
*/
BOOL CGrammarDesignerApp::PreTranslateMessage(MSG* pMsg)
{
		// TODO: Add your specialized code here and/or call the base class
/*
		if(pMsg->message == ID_THREAD_MESSAGE)
		{
				return OnThreadMessage(pMsg);
		}
*/		

		return CWinAppEx::PreTranslateMessage(pMsg);
}
