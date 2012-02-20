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

#include "StdAfx.h"

#include "InputPane.h"
#include "MainFrm.h"
#include "GrammarDesignerDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/***********************CInputPane*******************************/


CInputPane::CInputPane(void)
{

}

CInputPane::~CInputPane(void)
{

}



int   CInputPane::GetInputLength()
{
		return m_input.GetWindowTextLength();
}

CString	CInputPane::GetInput()const
{
		CString txt;

		m_input.GetWindowText(txt);

		return txt;
}

void CInputPane::Highlight(long start, long end, COLORREF color)
{
		CHARFORMAT cf;
        ZeroMemory(&cf, sizeof(CHARFORMAT));
		this->m_input.GetDefaultCharFormat(cf);

		cf.dwMask  |= CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = color;
		long x,y;

		this->m_input.GetSel(x,y);

		this->m_input.SetSel(start, end);
        this->m_input.SetSelectionCharFormat(cf);
		this->m_input.SetSel(x,y);
		
}




BEGIN_MESSAGE_MAP(CInputPane, CDockablePane)
		ON_WM_CREATE()
		ON_WM_SIZE()

		ON_MESSAGE(ID_EDIT_LOCATE_POS, &CInputPane::OnLocatePos)
		ON_MESSAGE(ID_INPUT_LOCATE_TOKEN, &CInputPane::OnLocateToken)
END_MESSAGE_MAP()

int CInputPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CDockablePane::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here

		CRect rectDummy;

		rectDummy.SetRectEmpty();

		const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL
								| ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE |ES_WANTRETURN  ;

		if (!m_input.Create(dwStyle, rectDummy, this, 1))
		{
				TRACE0("Failed to create input window\n");
				return -1;      // fail to create
		}

		return 0;
}

void CInputPane::OnSize(UINT nType, int cx, int cy)
{
		CDockablePane::OnSize(nType, cx, cy);

		// TODO: Add your message handler code here
		m_input.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


LRESULT CInputPane::OnLocatePos(WPARAM wp, LPARAM lp)
{
		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		
		main_frm->ShowPane(this, TRUE, TRUE, TRUE);

		

		int index = m_input.LineIndex((int)wp);
		
		if(index != -1)
		{
				CPoint pt = m_input.PosFromChar(index);
				m_input.SetCaretPos(pt);
				int cnt = m_input.LineLength(index);
				if(cnt > 0)
				{
						m_input.SetSel(index, index + cnt);
				}
		}
		
		m_input.SetFocus();
		//m_input.Invalidate();
	
		return 0;
}


LRESULT CInputPane::OnLocateToken(WPARAM wp, LPARAM lp)
{

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();

		main_frm->ShowPane(this, TRUE, TRUE, TRUE);

		const CPrintNode *node = (const CPrintNode*)wp;		
		
		ASSERT(node != NULL);

		CString buf;
		m_input.GetWindowText(buf);
		int index = m_input.LineIndex((int)node->m_line);
		
		if(index != -1)
		{
				CPoint pt = m_input.PosFromChar(index + (int)node->m_col);
				m_input.SetCaretPos(pt);
				//int cnt = m_input.LineLength(index);


				if(node->m_cnt)
				{
						const wchar_t *p = node->m_name.GetString();
						int cnt = (int)node->m_cnt;
						while(*p)
						{
								if(*p == TEXT('\n'))cnt--;
								++p;
						}
						//m_input.SetSel(index + (int)node->m_col, index + (int)node->m_col + (int)node->m_cnt);
						m_input.SetSel(index + (int)node->m_col, index + (int)node->m_col + cnt);
				}
		}
		
		m_input.SetFocus();
		//m_input.Invalidate();
	
		return 0;
}




/*****************************************CInputEdit***********************************************************/

IMPLEMENT_DYNAMIC(CInputEdit, CRichEditCtrl)

CInputEdit::CInputEdit()
{
		VERIFY(m_font.CreatePointFont(120, TEXT("Consolas")));

		m_acctbl = ::LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_INPUT_VIEW));
		VERIFY(m_acctbl);
}

CInputEdit::~CInputEdit()
{

}

void	CInputEdit::ResetFont()
{
		this->SetFont(&m_font);
}

BOOL CInputEdit::PreTranslateMessage(MSG* pMsg)
{
		// TODO: Add your specialized code here and/or call the base class

		if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) 
		{ 
				if(::TranslateAccelerator(this->GetSafeHwnd(), m_acctbl, pMsg))
				{
					return true;
				}
		}

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
		case WM_SYSKEYDOWN:
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
				case VK_TAB:
				{

						long nPos, nEnd;
						
						this->GetSel(nPos, nEnd);
						SetSel(nPos, nEnd);
						ReplaceSel(TEXT("\t"), TRUE);
						return TRUE;
				}
				}
		}
		}
		return CRichEditCtrl::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CInputEdit, CRichEditCtrl)
		ON_WM_CONTEXTMENU()
		ON_COMMAND(ID_EDIT_CUT, &CInputEdit::OnEditCut)
		ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CInputEdit::OnUpdateEditCut)
		ON_COMMAND(ID_EDIT_COPY, &CInputEdit::OnEditCopy)
		ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CInputEdit::OnUpdateEditCopy)
		ON_COMMAND(ID_EDIT_PASTE, &CInputEdit::OnEditPaste)
		ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CInputEdit::OnUpdateEditPaste)
		ON_COMMAND(ID_EDIT_SELECT_ALL, &CInputEdit::OnEditSelectAll)
		ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CInputEdit::OnUpdateEditSelectAll)
		ON_COMMAND(ID_EDIT_CLEAR, &CInputEdit::OnEditClear)
		ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, &CInputEdit::OnUpdateEditClear)
		ON_WM_CREATE()
		ON_COMMAND(ID_INPUT_FONT, &CInputEdit::OnInputFont)
		ON_COMMAND(ID_INPUT_EDIT_OPEN, &CInputEdit::OnPopupOpen)
		ON_COMMAND(ID_INPUT_EDIT_SAVE, &CInputEdit::OnPopupSave)
		
		ON_CONTROL_REFLECT(EN_CHANGE, &CInputEdit::OnEnChange)
		ON_WM_DROPFILES()
		ON_COMMAND(ID_POPUP_PARSE, &CInputEdit::OnPopupParse)
		ON_UPDATE_COMMAND_UI(ID_POPUP_PARSE, &CInputEdit::OnUpdatePopupParse)

		ON_COMMAND(ID_EDIT_UNDO, &CInputEdit::OnEditUndo)
END_MESSAGE_MAP()

void CInputEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
		// TODO: Add your message handler code here
		CMenu menu;
	menu.LoadMenu(IDR_INPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);
	
	((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pSumMenu->GetSafeHmenu(),point.x, point.y, this, TRUE);

	SetFocus();

	
}


void CInputEdit::OnEditCut()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Cut();
}

void CInputEdit::OnUpdateEditCut(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		long start = -1, end = -1;
		this->GetSel(start, end);
		
		pCmdUI->Enable(start != end);
		
}

void CInputEdit::OnEditCopy()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Copy();
}


void CInputEdit::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		
		long start = -1, end = -1;
		this->GetSel(start, end);

		pCmdUI->Enable(start != end);
}

void CInputEdit::OnEditPaste()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Paste();
}

void CInputEdit::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(true);
}

void CInputEdit::OnEditSelectAll()
{
		// TODO: Add your command handler code here
		this->SetSel(0, -1);
}

void CInputEdit::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		
		pCmdUI->Enable(this->GetWindowTextLength() > 0);
}

void CInputEdit::OnEditClear()
{
		// TODO: Add your command handler code here
		CRichEditCtrl::Clear();
		
		this->SetWindowText(TEXT(""));
}

void CInputEdit::OnUpdateEditClear(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(this->GetWindowTextLength() > 0);

}

int CInputEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		this->DragAcceptFiles(TRUE);
		if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		this->SetFont(&m_font);
		return 0;
}

void CInputEdit::OnInputFont()
{
		// TODO: Add your command handler code here
		LOGFONT lft;
		m_font.GetLogFont(&lft);
		CFontDialog		dlg(&lft);
		
		if(dlg.DoModal() == IDOK)
		{
				LOGFONT lf; 
				dlg.GetCurrentFont(&lf);
				m_font.Detach();
				VERIFY(m_font.CreateFontIndirect(&lf));
				this->SetFont(&m_font);
		}

}

void CInputEdit::OnPopupOpen()
{
		// TODO: Add your command handler code here

static TCHAR BASED_CODE szFilter[] = TEXT("Input Files (*.txt)|*.txt|All Files (*.*)|*.*||");




		CFileDialog		file(TRUE, TEXT("txt"), NULL, 4|2, szFilter);
		
		if(file.DoModal() != IDOK)
		{
				return;
		}

		CTextFileRead fr(file.GetPathName());

		CString txt;
		
		if(!fr.Read(txt))
		{
				this->MessageBox(TEXT("Open Failed"));
				return;
		}
		
		this->SetWindowText(txt);
	

}

void CInputEdit::OnPopupSave()
{
		// TODO: Add your command handler code here

static const TCHAR BASED_CODE szFilter[] = TEXT("Input Files (*.txt)|*.txt|All Files (*.*)|*.*||");
		CFileDialog		file(FALSE, TEXT("txt"), NULL, 4|2, szFilter);

		
		if(file.DoModal() != IDOK)
		{
				return;
		}
		 
		CMainFrame *main_frm = ( CMainFrame*)::AfxGetMainWnd();
		CGrammarDesignerDoc *pdoc = (CGrammarDesignerDoc*)main_frm->GetActiveDocument();
		ASSERT(pdoc != NULL);

		CTextFileWrite fw(file.GetPathName(), pdoc->GetEncoding());

		CString txt ;
		this->GetWindowText(txt);

		fw.Write(txt);
}

void CInputEdit::OnEnChange()
{
		// TODO:  If this is a RICHEDIT control, the control will not
		// send this notification unless you override the CRichEditCtrl::OnInitDialog()
		// function and call CRichEditCtrl().SetEventMask()
		// with the ENM_CHANGE flag ORed into the mask.

		// TODO:  Add your control notification handler code here
}


void CInputEdit::OnDropFiles(HDROP hDropInfo)
{
		// TODO: Add your message handler code here and/or call default
		CString fname;
		// TODO: Add your message handler code here and/or call default
		UINT DropCount=DragQueryFile(hDropInfo, (UINT)-1,NULL,0);//取得被拖动文件的数目
		for(UINT i=0;i< DropCount;i++)
		{ 
				//取得第i个拖动文件名所占字节数      
				UINT len=DragQueryFile(hDropInfo,i,NULL,0);
				wchar_t *name = new wchar_t[len + 1];
				len = DragQueryFile(hDropInfo,i,name, len + 1);
				name[len] = 0;
				fname = name;
				delete []name;
				break;
		} 
		DragFinish(hDropInfo);  //拖放结束后,释放内存
		
		if(!fname.IsEmpty())
		{
				CTextFileRead	fr(fname);

				CString txt;
				
				if(fr.Read(txt))
				{
						this->SetWindowText(txt);
				}else
				{
						CString msg;
						msg.Format(TEXT("Failed to open %ls"), fname.GetString());
						this->MessageBox(msg);
				}
		}
		//CRichEditCtrl::OnDropFiles(hDropInfo);
}

void CInputEdit::OnPopupParse()
{
		// TODO: Add your command handler code here
		
		::AfxGetMainWnd()->SendMessage(WM_COMMAND, (WPARAM)ID_PARSER_PARSE);
}

void CInputEdit::OnUpdatePopupParse(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here

		 CMainFrame *main_frm = ( CMainFrame*)::AfxGetMainWnd();
		
		 pCmdUI->Enable(((CGrammarDesignerDoc*)main_frm->GetActiveDocument())->IsParseable());
		 
}

void CInputEdit::OnEditUndo()
{
		// TODO: Add your command handler code here
		
		this->Undo();
}
