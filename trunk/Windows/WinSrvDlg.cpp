
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
		m_is_hide = FALSE;
		memset(&m_nid, 0, sizeof(m_nid));
		m_is_started = FALSE;
	
}

CWinSrvDlg::~CWinSrvDlg()
{
		
}

void CWinSrvDlg::DoDataExchange(CDataExchange* pDX)
{
		CDialogEx::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_IPADDRESS_SERVER_IP, m_server_ip);
		DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_server_port);
		DDX_Control(pDX, IDC_BUTTON_START, m_button_server_start);
		DDX_Control(pDX, IDC_BUTTON_STOP, m_button_server_stop);
		DDX_Control(pDX, IDC_EDIT_SERVER_PWD, m_server_pwd);

		DDX_Control(pDX, IDC_CHECK_IS_AUTORUN, m_is_autorun);
		DDX_Control(pDX, IDC_CHECK_IS_MANUAL_IP, m_is_manual_ip);

}

BEGIN_MESSAGE_MAP(CWinSrvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDOK, &CWinSrvDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CWinSrvDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_CUS_SHOW_DIALOG, &OnShowDlg)
	ON_BN_CLICKED(IDC_CUS_HIDE_DIALOG, &OnHideDlg)
	ON_BN_CLICKED(IDC_BUTTON_START, &CWinSrvDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CWinSrvDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK_IS_MANUAL_IP, &CWinSrvDlg::OnBnClickedCheckIsManualIp)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_CHECK_IS_AUTORUN, &CWinSrvDlg::OnBnClickedCheckIsAutorun)
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

	if(!init_systray())
	{
			this->MessageBox(TEXT("systray failed to initialize"));
			return FALSE;
	}

	init_config();
	init_dlg_items();


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





#if defined(_UNICODE)
		#define lsplitpath		_wsplitpath
#else
		#define lsplitpath		_splitpath
#endif


CString UTIL_GetModulePath()
{
		CString path;
		static TCHAR buf[MAX_PATH * 2];
		VERIFY(::GetModuleFileName(GetModuleHandle(NULL), buf, MAX_PATH * 2) > 0);
		
		static TCHAR d[5], dir[MAX_PATH];

		lsplitpath(buf, d, dir,NULL,NULL);

		path.Append(d);
		path.Append(dir);
		return path;
}


CString CWinSrvDlg::get_dlg_ip()const
{
		struct in_addr addr;
		m_server_ip.GetAddress(addr.S_un.S_addr);
		
		addr.S_un.S_addr = AR_BYTEFLIP_U32(addr.S_un.S_addr);

		char *ip = inet_ntoa(addr);

		wchar_t wip[128];

		size_t wn = AR_str_to_wcs(AR_CP_ACP, ip, strlen(ip), wip, 128);

		if(wn > 0)
		{
				wip[wn] = 0;
		}else
		{
				wcscpy(wip, L"0.0.0.0");
		}

		return CString(wip);
}




UINT CWinSrvDlg::get_dlg_port()const
{
		CString tmp;
		
		m_server_port.GetWindowText(tmp);
		return _wtoi(tmp);
}




#define WI_SRV_CONFIG			TEXT("server_config.ini")
#define WI_SRV_CONFIG_SEC		TEXT("Server")

#define WI_SRV_CONFIG_IP		TEXT("IP")
#define WI_SRV_CONFIG_PORT		TEXT("Port")
#define WI_SRV_CONFIG_PWD		TEXT("Password")

#define WI_SRV_CONFIG_MISC_SEC			TEXT("Misc")
#define WI_SRV_CONFIG_MISC_AUTORUN		TEXT("Auto Run")
#define WI_SRV_CONFIG_MISC_MANUALIP		TEXT("Manual IP")

void	CWinSrvDlg::init_config()
{
		m_cfg = Ini_CreateObject();

		bool_t is_ok;
		CString path = UTIL_GetModulePath();
		path += WI_SRV_CONFIG;

		arString_t *out = AR_CreateString();

		is_ok = AR_LoadBomTextFile((const wchar_t*)path, NULL, out) == AR_S_YES;

		if(is_ok)
		{
				Ini_ClearObject(m_cfg);
				is_ok = Ini_LoadObjectFromString(m_cfg, AR_GetStringCString(out)) == AR_S_YES;
		}
		
		AR_DestroyString(out);
		out = NULL;
}



void	CWinSrvDlg::uninit_config()
{

		if(m_cfg)
		{
				Ini_DestroyObject(m_cfg);
				m_cfg = NULL;
		}

}




unsigned long inet_addr_wcs(const wchar_t *input)
{
		if(input == NULL)
		{
				return INADDR_NONE;
		}

		size_t l = wcslen(input) * 2+ 1;
		char *tmp = new char[l];

		size_t n = AR_wcs_to_str(AR_CP_ACP, input, wcslen(input), tmp, l - 1);

		tmp[n] = 0;
		
		unsigned long ret = inet_addr(tmp);
		delete tmp;
		tmp = NULL;
		return ret;
}

void	CWinSrvDlg::save_config()
{
		CString ip_str;
		CString port_str;
		CString	pwd_str;

		m_server_ip.GetWindowText(ip_str);
		m_server_port.GetWindowText(port_str);
		m_server_pwd.GetWindowText(pwd_str);

		if(inet_addr_wcs(ip_str) == INADDR_NONE)
		{
				ip_str = TEXT("0.0.0.0");
		}

		Ini_SetString(m_cfg, WI_SRV_CONFIG_SEC, WI_SRV_CONFIG_IP, (const wchar_t*)ip_str, NULL);
		Ini_SetString(m_cfg, WI_SRV_CONFIG_SEC, WI_SRV_CONFIG_PORT, (const wchar_t*)port_str, NULL);
		Ini_SetString(m_cfg, WI_SRV_CONFIG_SEC, WI_SRV_CONFIG_PWD, (const wchar_t*)pwd_str, NULL);
		Ini_SetUInt(m_cfg, WI_SRV_CONFIG_MISC_SEC, WI_SRV_CONFIG_MISC_AUTORUN, m_is_autorun.GetCheck() == BST_CHECKED ? 1 : 0, NULL);
		Ini_SetUInt(m_cfg, WI_SRV_CONFIG_MISC_SEC, WI_SRV_CONFIG_MISC_MANUALIP, m_is_manual_ip.GetCheck() == BST_CHECKED ? 1 : 0, NULL);
		
		arString_t *out = AR_CreateString();

		Ini_SaveObjectToString(m_cfg, out);

		CString path = UTIL_GetModulePath();
		path += WI_SRV_CONFIG;

		AR_SaveBomTextFile((const wchar_t*)path, AR_TXT_BOM_UTF_8, AR_GetStringCString(out));

		if(out)
		{
				AR_DestroyString(out);
				out = NULL;
		}
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






BOOL	CWinSrvDlg::init_systray()
{
		m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
		m_nid.hWnd    = this->m_hWnd;
		m_nid.uID     = IDR_MAINFRAME;
		m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
		m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
		m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		lstrcpy(m_nid.szTip, TEXT("WiController Server"));                // 信息提示条为"MultiMove Server"
		return Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
}


BOOL	CWinSrvDlg::uninit_systray()
{
		return Shell_NotifyIcon(NIM_DELETE, &m_nid);                // 在托盘区添加图标
}


void	CWinSrvDlg::show_dlg()
{
		if(m_is_hide)
		{
				m_is_hide = FALSE;
				this->ShowWindow(SW_SHOWNORMAL);
		}
}


void	CWinSrvDlg::hide_dlg()
{
		if(!m_is_hide)
		{
				m_is_hide = TRUE;
				this->ShowWindow(SW_HIDE);
		}
}

BOOL	CWinSrvDlg::is_hide()const
{
		return m_is_hide;
}



void CWinSrvDlg::OnShowDlg()
{
		this->show_dlg();
}


void CWinSrvDlg::OnHideDlg()
{
		this->hide_dlg();
		
}



LRESULT CWinSrvDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
		if(wParam != IDR_MAINFRAME)
		{
				return 1;
		}

		switch(lParam)
		{
		case WM_RBUTTONUP:                                //右键起来时弹出菜单
		{
				LPPOINT lpoint = new tagPOINT;
				::GetCursorPos(lpoint);                   //得到鼠标位置
				CMenu menu;
				menu.CreatePopupMenu();                   //声明一个弹出式菜单


				
				menu.AppendMenu(MF_STRING, IDC_CUS_SHOW_ABOUT, TEXT("About"));
				menu.AppendMenu(MF_SEPARATOR);

				menu.AppendMenu(MF_STRING, IDC_BUTTON_START, TEXT("Start"));
				menu.AppendMenu(MF_STRING, IDC_BUTTON_STOP, TEXT("Stop"));
				menu.AppendMenu(MF_SEPARATOR);

				if(is_hide())
				{
						menu.AppendMenu(MF_STRING, IDC_CUS_SHOW_DIALOG, TEXT("Show"));
				}else
				{
						menu.AppendMenu(MF_STRING, IDC_CUS_HIDE_DIALOG, TEXT("Hide"));
				}

				menu.AppendMenu(MF_SEPARATOR);
				menu.AppendMenu(MF_STRING, IDC_BUTTON_QUIT, TEXT("Quit"));


				menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);

				
				
				HMENU hmenu = menu.Detach();
				menu.DestroyMenu();
				delete lpoint;
		}
				break;
		case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
		{
				this->show_dlg();
		}
				break;
		}
		return 0;
}


void CWinSrvDlg::OnBnClickedOk()
{
		// TODO: Add your control notification handler code here
		this->hide_dlg();
		//CDialogEx::OnOK();
}





void	CWinSrvDlg::init_dlg_items()
{
		unsigned long addr = 0;

		char ip[128];

		const wchar_t *wip = Ini_GetString(m_cfg, WI_SRV_CONFIG_SEC, WI_SRV_CONFIG_IP);
		if(wip == NULL)
		{
				wip = L"0.0.0.0";
		}

		size_t wn = AR_wcs_to_str(AR_CP_ACP, wip, wcslen(wip), ip, 128);

		if(wn > 0)
		{
				ip[wn] = 0;
		}

		addr = inet_addr(ip);

		m_server_ip.SetAddress(AR_BYTEFLIP_U32((DWORD)addr));


		DWORD port = Ini_GetUInt(m_cfg, WI_SRV_CONFIG_SEC, WI_SRV_CONFIG_PORT, 0);

		CString tmp;
		tmp.Format(TEXT("%d"), port);
		m_server_port.SetWindowText(tmp);

		
		const wchar_t *wpwd = Ini_GetString(m_cfg, WI_SRV_CONFIG_SEC, WI_SRV_CONFIG_PWD);
		if(wpwd == NULL)
		{
				wpwd = L"";
		}
		m_server_pwd.SetWindowText(wip);
		
		UINT is_auto_run = Ini_GetUInt(m_cfg, WI_SRV_CONFIG_MISC_SEC, WI_SRV_CONFIG_MISC_AUTORUN, 0);
		m_is_autorun.SetCheck(is_auto_run != 0 ? BST_CHECKED : BST_UNCHECKED);

		UINT is_manual_ip = Ini_GetUInt(m_cfg, WI_SRV_CONFIG_MISC_SEC, WI_SRV_CONFIG_MISC_MANUALIP, 0);
		m_is_manual_ip.SetCheck(is_manual_ip != 0 ? BST_CHECKED : BST_UNCHECKED);
		m_server_ip.EnableWindow(is_manual_ip);

		m_button_server_start.EnableWindow(TRUE);
		m_button_server_stop.EnableWindow(FALSE);

}
		




void CWinSrvDlg::OnBnClickedButtonStart()
{
		// TODO: Add your control notification handler code here
		if(m_is_started)
		{
				return;
		}

		CString pwd = TEXT(""), ip= TEXT(""), port= TEXT("");
		
		m_server_ip.GetWindowText(ip);
		m_server_pwd.GetWindowText(pwd);
		m_server_port.GetWindowText(port);

		if(m_is_manual_ip.GetCheck() != BST_CHECKED)
		{
				ip = TEXT("");
		}
		
		if(this->InitServerService(ip, _wtoi(port)))
		{
				this->m_srv->SetPassword(pwd);

				m_button_server_start.EnableWindow(FALSE);
				m_button_server_stop.EnableWindow(TRUE);
				m_is_started = TRUE;
		}
}


void CWinSrvDlg::OnBnClickedButtonStop()
{
		// TODO: Add your control notification handler code here
		if(m_is_started)
		{
				this->UninitServerService();
				m_button_server_start.EnableWindow(TRUE);
				m_button_server_stop.EnableWindow(FALSE);
				m_is_started = FALSE;
		}
}


void CWinSrvDlg::OnBnClickedButtonQuit()
{
		// TODO: Add your control notification handler code here

		OnBnClickedButtonStop();
		save_config();
		CDialogEx::OnOK();
}



void CWinSrvDlg::OnBnClickedCheckIsManualIp()
{
		// TODO: Add your control notification handler code here
		m_server_ip.EnableWindow(m_is_manual_ip.GetCheck() == BST_CHECKED);
}


void CWinSrvDlg::OnClose()
{
		// TODO: Add your message handler code here and/or call default

		this->hide_dlg();
		//CDialogEx::OnClose();
}


void CWinSrvDlg::OnNcDestroy()
{
		// TODO: Add your message handler code here
		UninitServerService();
		uninit_config();
		uninit_systray();

		CDialogEx::OnNcDestroy();

}




void CWinSrvDlg::OnBnClickedCheckIsAutorun()
{
#if(0)
		// TODO: Add your control notification handler code here
		HKEY   RegKey;   
		CString   sPath;   
		GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
		sPath.ReleaseBuffer();   
		int   nPos;   

		nPos=sPath.ReverseFind('\\');   
		sPath=sPath.Left(nPos);   

		CString   lpszFile=sPath + L"\\WinSrv.exe";//这里加上你要查找的执行文件名称   
		CFileFind   fFind;   

		BOOL   bSuccess;   
		bSuccess=fFind.FindFile(lpszFile);   

		fFind.Close();   
		if(bSuccess)   
		{   
				RegKey=NULL;   

				RegOpenKey(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&RegKey);   
				
				wchar_t buf[1024];
				_wfullpath(buf, (const wchar_t*)lpszFile, 1024);

				RegSetValueEx(RegKey,TEXT("WiController-Server"),0,REG_SZ,(const  unsigned   char*)(LPCTSTR)buf, wcslen(buf));

				this->UpdateData(FALSE);   
		}

#endif

}
