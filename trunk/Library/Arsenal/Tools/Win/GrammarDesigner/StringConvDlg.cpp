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

// StringConvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrammarDesigner.h"
#include "StringConvDlg.h"


CStringEdit::CStringEdit() : CRichEditCtrl ()
{
		VERIFY(m_font.CreatePointFont(120, TEXT("Consolas")));
		m_acctbl = ::LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_INPUT_VIEW));
		VERIFY(m_acctbl);
}


CStringEdit::~CStringEdit()
{

}


BOOL CStringEdit::PreTranslateMessage(MSG* pMsg)
{
		// TODO: Add your specialized code here and/or call the base class
		if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) 
		{ 
				if(::TranslateAccelerator(this->GetSafeHwnd(), m_acctbl, pMsg))
				{
					return true;
				}
		}		

		/*
		switch(pMsg->message)
		{
		case WM_RBUTTONDOWN:
		{
				this->SetFocus();
				CPoint point;
				GetCursorPos(&point);
				this->OnContextMenu(this, point);
				return TRUE;
		}
		case WM_KEYDOWN:
		{
				switch(pMsg->wParam)
				{
				case VK_APPS:
				{
						this->SetFocus();
						CPoint pt = this->GetCaretPos();
						this->ClientToScreen(&pt);
						this->OnContextMenu(this, pt);
						return TRUE;
				}
				}
		}
		}
		*/
		return CRichEditCtrl::PreTranslateMessage(pMsg);
}



void CStringEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
		// TODO: Add your message handler code here
		//::AfxMessageBox(_T("aaaaaaaaaaa"));
		
	CMenu menu;
	menu.LoadMenu(IDR_MENU_STRCONV);

	CMenu* pSumMenu = menu.GetSubMenu(0);
		
	pSumMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
	
	//((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pSumMenu->GetSafeHmenu(),point.x, point.y, this, TRUE);

	this->SetFocus();
}




BEGIN_MESSAGE_MAP(CStringEdit, CRichEditCtrl)
		ON_COMMAND(ID_EDIT_SELECT_ALL, &CStringEdit::OnEditSelectAll)
		ON_WM_CREATE()
		ON_COMMAND(ID_EDIT_COPY, &CStringEdit::OnEditCopy)
		ON_COMMAND(ID_EDIT_CUT, &CStringEdit::OnEditCut)
		ON_COMMAND(ID_EDIT_PASTE, &CStringEdit::OnEditPaste)
		ON_COMMAND(ID_EDIT_CLEAR, &CStringEdit::OnEditClear)
		ON_COMMAND(ID_EDIT_UNDO, &CStringEdit::OnEditUndo)
		ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



int CStringEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		this->SetFont(&m_font);
		return 0;
}

void CStringEdit::OnEditCopy()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Copy();
}

void CStringEdit::OnEditCut()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Cut();
}

void CStringEdit::OnEditPaste()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Paste();
}

void CStringEdit::OnEditClear()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Clear();
}

void CStringEdit::OnEditSelectAll()
{
		// TODO: Add your command handler code here
		this->SetSel(0,-1);
}



void CStringEdit::OnEditUndo()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Undo();
}

////////////////////////////////////////////////////////////////////////////////////////////////

// CStringConvDlg dialog

IMPLEMENT_DYNAMIC(CStringConvDlg, CDialog)

CStringConvDlg::CStringConvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStringConvDlg::IDD, pParent)
{
		VERIFY(m_font.CreatePointFont(120, TEXT("Consolas")));
}

CStringConvDlg::~CStringConvDlg()
{
}

void CStringConvDlg::DoDataExchange(CDataExchange* pDX)
{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_EDIT_STRING, m_input_string);
		DDX_Control(pDX, IDC_EDIT_CODE, m_input_code);
}


BEGIN_MESSAGE_MAP(CStringConvDlg, CDialog)
		ON_BN_CLICKED(IDC_BUTTON_TO_CODE, &CStringConvDlg::OnBnClickedButtonToCode)
		ON_BN_CLICKED(IDC_BUTTON_TO_STRING, &CStringConvDlg::OnBnClickedButtonToString)
END_MESSAGE_MAP()


// CStringConvDlg message handlers

void CStringConvDlg::OnBnClickedButtonToCode()
{
		// TODO: Add your control notification handler code here

		CString input;
		this->GetDlgItemText(IDC_EDIT_STRING,input);

		if(input.IsEmpty())
		{
				this->MessageBox(TEXT("Invalid string input!"));
				return;
		}
		
		int_t len = ARSpace::AR_str_to_escstr_buf(NULL, 0, input.GetString());

		AR_ASSERT(len > 0);

		wchar_t *code = new wchar_t[len + 1];
		
		
		len = ARSpace::AR_str_to_escstr_buf(code, len, input.GetString());
		AR_ASSERT(len == len);

		this->SetDlgItemText(IDC_EDIT_CODE, code);

		delete []code;

}

void CStringConvDlg::OnBnClickedButtonToString()
{
		// TODO: Add your control notification handler code here


		CString input;
		this->GetDlgItemText(IDC_EDIT_CODE,input);

		if(input.IsEmpty())
		{
				this->MessageBox(TEXT("Invalid code input!"));
				return;
		}
		
		ARSpace::arEscStrErr_t	err;
		int_t len;
		
		len = ARSpace::AR_escstr_to_str_buf(NULL, 0, input.GetString(), &err);
		
		CString info;
		
		if(err.type == AR_ESCSTR_ERR_VALUE)
		{
				info.Format(L"Invalid value %I64d : too big for wide character\r\n", err.value);
		}else if(err.type == AR_ESCSTR_ERR_CHAR)
		{
				wchar_t c = *err.pos;
				if(iswprint(c))
				{
						info.Format(L"Invalid char %c : unrecognized character escape sequence\r\n", c);
				}else
				{
						info.Format(L"Invalid char \\x%x : unrecognized character escape sequence\r\n", c);
				}
		}else if(err.type == AR_ESCSTR_ERR_BUFFER)
		{
				AR_ASSERT(false);
				return;
		}


		if(!info.IsEmpty())
		{
				this->SetDlgItemText(IDC_EDIT_STRING, info);
				return;
		}
		
		wchar_t *str = new wchar_t[len];
		len = ARSpace::AR_escstr_to_str_buf(str, len, input.GetString(), &err);

		ASSERT(len == len && err.type == AR_ESCSTR_ERR_OK);

		this->SetDlgItemText(IDC_EDIT_STRING, str);

		delete []str;
}

BOOL CStringConvDlg::PreTranslateMessage(MSG* pMsg)
{
		// TODO: Add your specialized code here and/or call the base class
/*
		if (pMsg->message == WM_KEYDOWN && 	(pMsg->wParam == VK_ESCAPE || pMsg->wParam==VK_RETURN))
		{
				return TRUE;
		}    
*/
		return CDialog::PreTranslateMessage(pMsg);
}

BOOL CStringConvDlg::OnInitDialog()
{
		CDialog::OnInitDialog();

		// TODO:  Add extra initialization here

		CRichEditCtrl *pedit = (CRichEditCtrl*)this->GetDlgItem(IDC_EDIT_STRING);
		pedit->SetFont(&m_font);
		pedit->LimitText(0xffffffff);
		
		
		pedit = (CRichEditCtrl*)this->GetDlgItem(IDC_EDIT_CODE);
		pedit->SetFont(&m_font);
		pedit->LimitText(0xffffffff);
		
		

		return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX Property Pages should return FALSE
}

