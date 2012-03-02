
// WinSrvDlg.h : header file
//
#pragma once


class CServerService;

// CWinSrvDlg dialog
class CWinSrvDlg : public CDialogEx
{
private:
		CServerService	*m_srv;
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

protected:
		void	LoadConfig();
		BOOL	InitServerService(const CString &ip_addr, USHORT port);
		void	UninitServerService();
		BOOL	ResetServerService();
};
