
// WinSrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinSrv.h"
#include "WinSrvDlg.h"
#include "afxdialogex.h"
#include "NetMessage.h"
#include "ServerService.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWinSrvDlg dialog




CWinSrvDlg::CWinSrvDlg(CWnd* pParent /*=NULL*/)	: CDialogEx(CWinSrvDlg::IDD, pParent),m_srv(NULL)
{
		
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
}

CWinSrvDlg::~CWinSrvDlg()
{
		UninitServerService();
}

void CWinSrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinSrvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()







// CWinSrvDlg message handlers

BOOL CWinSrvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	if(!ResetServerService())
	{
			AfxMessageBox(_T("Failed to create server socket"), MB_OK | MB_ICONSTOP);
			return FALSE;
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinSrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinSrvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinSrvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void	CWinSrvDlg::LoadConfig()
{
		

}



BOOL	CWinSrvDlg::InitServerService(const CString &ip_addr, USHORT port)
{
		this->UninitServerService();

		const wchar_t *addr = NULL;
		if(ip_addr.GetLength() > 0)
		{
				addr = ip_addr.GetString();
		}

		m_srv = new CServerService;

		if(!m_srv->Create(port, SOCK_DGRAM, FD_READ, addr))
		{
				delete m_srv;
				m_srv = NULL;
				return FALSE;
		}else
		{
				return TRUE;
		}
}


void	CWinSrvDlg::UninitServerService()
{
		if(m_srv != NULL)
		{
				m_srv->Close();
				delete m_srv;
				m_srv = NULL;
		}
}



BOOL	CWinSrvDlg::ResetServerService()
{
		if(!this->InitServerService(L"", 28412))
		{
				return FALSE;
		}

		this->m_srv->SetPassword(L"1");
		return TRUE;
}
