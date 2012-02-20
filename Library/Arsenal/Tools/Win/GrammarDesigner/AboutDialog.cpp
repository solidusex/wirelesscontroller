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

#include "stdafx.h"
#include "resource.h"

#include "AboutDialog.h"

#pragma comment(lib, "Version.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static CString __get_version_info()
{
		TCHAR szFullPath[MAX_PATH];
		DWORD dwVerInfoSize = 0;
		DWORD dwVerHnd;
		VS_FIXEDFILEINFO * pFileInfo;

		GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
		dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
		
		if (dwVerInfoSize > 0)
		{
				void *finfo = malloc(dwVerInfoSize);
				unsigned int uInfoSize = 0;

				if(!GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, finfo))
				{
						free(finfo);
						goto FAILED_POINT;
				}

				if(!VerQueryValue(finfo, (LPTSTR)TEXT("\\"), (void**)&pFileInfo, &uInfoSize))
				{
						free(finfo);
						goto FAILED_POINT;
				}

				WORD m_nProdVersion[4];

				// Product version from the FILEVERSION of the version info resource 
				m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
				m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
				m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
				m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 

				CString strVersion ;
				strVersion.Format(TEXT("Version : %d.%d.%d.%d"),m_nProdVersion[0],m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
				free(finfo);
				return strVersion;
		}
		
FAILED_POINT:
		return CString(TEXT("Version : Unknow"));
}

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
		m_name = TEXT("Grammar Designer");
		m_ver = __get_version_info();
		m_arsenal_ver = CString(_T("Arsenal Version : ")) + ARSpace::AR_Version();
		m_copyright = TEXT("Copyright (C) 2009-2010 Solidus");
		m_homepage = TEXT("http://code.google.com/p/arsenalcomp/");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
		CDialog::DoDataExchange(pDX);

		DDX_Text(pDX, IDC_APP_NAME, m_name);
		DDX_Text(pDX, IDC_APP_GMR_DESIGNER_VERSION, m_ver);
		DDX_Text(pDX, IDC_APP_ARSENAL_VERSION, m_arsenal_ver);

		DDX_Text(pDX, IDC_APP_COPYRIGHT, m_copyright);
		DDX_Text(pDX, IDC_APP_HOMEPAGE, m_homepage);

		DDX_Control(pDX, IDC_APP_HOMEPAGE, m_hplink);
		m_hplink.SetLinkUrl(m_homepage);
}



BOOL CAboutDlg::OnInitDialog()
{
		CDialog::OnInitDialog();

		// TODO:  Add extra initialization here
		
		//m_hplink.SetWindowText(m_homepage);
		

		return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
		ON_STN_CLICKED(IDC_APP_HOMEPAGE, &CAboutDlg::OnStnClickedHomepage)
END_MESSAGE_MAP()


void CAboutDlg::OnStnClickedHomepage()
{
		// TODO: Add your control notification handler code here
		
}
