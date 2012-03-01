
// WinSrv.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WinSrv.h"
#include "WinSrvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


///////////////////////////////////////


static void	AR_STDCALL __on_error_func(int_t level, const wchar_t *msg, void *ctx)
{
		using namespace ARSpace;
		AR_UNUSED(level);
		AR_UNUSED(ctx);
		OutputDebugStringW(msg);
}

static void	AR_STDCALL __on_print_func(const wchar_t *msg, void *ctx)
{
		using namespace ARSpace;
		AR_UNUSED(ctx);
		OutputDebugStringW(msg);
}



static BOOL Init_Arsenal()
{
		using namespace ARSpace;
		arInit_t init;
		
		init.global_io_ctx.ctx = NULL;
		init.global_io_ctx.on_error = __on_error_func;
		init.global_io_ctx.on_print = __on_print_func;

		Arsenal_Init(&init);
		

		return TRUE;
}

static BOOL UnInit_Arsenal()
{
		ARSpace::Arsenal_UnInit();
		return TRUE;
}


///////////////////////////////////////




// CWinSrvApp

BEGIN_MESSAGE_MAP(CWinSrvApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWinSrvApp construction

CWinSrvApp::CWinSrvApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CWinSrvApp object

CWinSrvApp theApp;


// CWinSrvApp initialization

BOOL CWinSrvApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	Init_Arsenal();


	CWinSrvDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	UnInit_Arsenal();
	return FALSE;
}

