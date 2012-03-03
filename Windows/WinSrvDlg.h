
// WinSrvDlg.h : header file
//
#pragma once
#include "afxcmn.h"
#include "afxwin.h"

using namespace ARSpace;
class CServerService;


// CWinSrvDlg dialog
class CWinSrvDlg : public CDialogEx
{
private:
		NOTIFYICONDATA			m_nid;
		BOOL					m_is_hide;
		iniObject_t				*m_cfg;
		CServerService			*m_srv;
		BOOL					m_is_started;
// Construction
public:
	CWinSrvDlg(CWnd* pParent = NULL);	// standard constructor
	~CWinSrvDlg();
// Dialog Data
	enum { IDD = IDD_WINSRV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
protected:
		CString get_dlg_ip()const;
		UINT get_dlg_port()const;

		void	init_config();
		void	uninit_config();
		void	save_config();


		void	init_dlg_items();
protected:
		BOOL	init_systray();
		BOOL	uninit_systray();

		BOOL	is_hide()const;
		void	hide_dlg();
		void	show_dlg();
protected:

		BOOL	InitServerService(const CString &ip_addr, USHORT port);
		void	UninitServerService();
	
public:
		CIPAddressCtrl	m_server_ip;
		CEdit			m_server_port;
		CEdit			m_server_pwd;
		CButton m_button_server_start;
		CButton m_button_server_stop;
		

		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedButtonQuit();
		afx_msg void OnShowDlg();
		afx_msg void OnHideDlg();
		afx_msg void OnBnClickedButtonStart();
		afx_msg void OnBnClickedButtonStop();

		
		CButton m_is_autorun;
		afx_msg void OnBnClickedCheckIsManualIp();
		CButton m_is_manual_ip;
		afx_msg void OnClose();
		afx_msg void OnNcDestroy();
		
		afx_msg void OnBnClickedCheckIsAutorun();
};
