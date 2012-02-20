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

// FindOutputWnd.cpp : implementation file
//


#include "stdafx.h"
#include "GrammarDesigner.h"
#include "FindOutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static int GetSelectIndex(CListBox &box, CPoint pt)
{

		for(int i = 0; i < box.GetCount(); ++i)
		{
				CRect rect;
				box.GetItemRect(i, &rect);

				if(rect.PtInRect(pt))
				{
						return i;
				}
		}				
		
		return -1;
}



IMPLEMENT_DYNAMIC(CFindOutputList, CListBox)


CFindOutputList::CFindOutputList()
{
		m_font.CreatePointFont(90, TEXT("Consolas"));
}

CFindOutputList::~CFindOutputList()
{

}





BEGIN_MESSAGE_MAP(CFindOutputList, CListBox)
		ON_COMMAND(ID_EDIT_COPY, &CFindOutputList::OnEditCopy)
		ON_COMMAND(ID_EDIT_CLEAR, &CFindOutputList::OnEditClear)
		ON_COMMAND(ID_FIND_OUTPUTWND_FONT, &CFindOutputList::OnFindOutputwndFont)
		ON_WM_CONTEXTMENU()
		ON_WM_DESTROY()
		ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CFindOutputList::OnUpdateEditCopy)
		ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, &CFindOutputList::OnUpdateEditClear)
		ON_WM_LBUTTONDOWN()
		ON_WM_RBUTTONDOWN()
		ON_WM_LBUTTONDBLCLK()
		ON_WM_CREATE()
END_MESSAGE_MAP()


int CFindOutputList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CListBox::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		this->SetFont(&m_font);

		return 0;
}


void CFindOutputList::OnEditCopy()
{
		// TODO: Add your command handler code here
		int i = this->GetCurSel();

		if(i == -1)return;
		
		CString src;
		this->GetText(i, src);

		if (OpenClipboard())
		{
				EmptyClipboard();                        
				HGLOBAL hClip =GlobalAlloc(GMEM_MOVEABLE,(src.GetLength() + 1) * sizeof(TCHAR));  
				TCHAR *buf = (TCHAR*)GlobalLock(hClip); 
				lstrcpy(buf, src.GetString());
				GlobalUnlock(hClip);     
				SetClipboardData(CF_UNICODETEXT,hClip); 
				CloseClipboard();            
		}
}


void CFindOutputList::OnEditClear()
{
		// TODO: Add your command handler code here
		Clear();
		
}

void CFindOutputList::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(this->GetCurSel() >= 0);
}


void CFindOutputList::OnUpdateEditClear(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(this->GetCurSel() >= 0);
}


void CFindOutputList::OnFindOutputwndFont()
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


void CFindOutputList::OnContextMenu(CWnd* pWnd, CPoint point)
{
		// TODO: Add your message handler code here
		CMenu menu;
	menu.LoadMenu(IDR_FIND_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);
	
	((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pSumMenu->GetSafeHmenu(),point.x, point.y, this, TRUE);

	SetFocus();
}

void CFindOutputList::OnLButtonDown(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default
		int i = GetSelectIndex(*this, point);
		
		if(i == -1)
		{
				this->SetCurSel(-1);
		}else
		{
				this->SetCurSel(i);
		}

		CListBox::OnLButtonDown(nFlags, point);
}

void CFindOutputList::OnRButtonDown(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default
		
		int i = GetSelectIndex(*this, point);

		if(i != -1) this->SetCurSel(i);

		CListBox::OnRButtonDown(nFlags, point);
}



BOOL CFindOutputList::PreCreateWindow(CREATESTRUCT& cs)
{
		// TODO: Add your specialized code here and/or call the base class
		const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
		cs.style = dwStyle;
		return CListBox::PreCreateWindow(cs);
}


void CFindOutputList::OnDestroy()
{
		Clear();
		CListBox::OnDestroy();

}

void	CFindOutputList::Clear()
{
		for(int i = 0; i < this->GetCount(); ++i)
		{
				Param *ptr = (Param*)this->GetItemData(i);
				
				if(ptr != NULL)
				{
						delete ptr;
				}
		}
		this->ResetContent();
}


void	CFindOutputList::Append(const CString &msg, const Param &param)
{
		int idx = this->AddString(msg);
		Param *ptr = new Param;
		*ptr = param;
		this->SetItemDataPtr(idx, (void*)ptr);
}

void CFindOutputList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default
		CListBox::OnLButtonDblClk(nFlags, point);

		int idx = this->GetCurSel();

		if(idx != -1)
		{
				Param *ptr = (Param*)this->GetItemData(idx);

				if(ptr->target != NULL)
				{
						/*CView *pview = ((CFrameWnd*)::AfxGetMainWnd())->GetActiveView();

						if(pview)
						{
								pview->SendMessage(ID_EDIT_LOCATE_POS, ptr->line);
						}
						*/

						ptr->target->SendMessage(ID_EDIT_LOCATE_POS, ptr->line);
				}
		}
}



/****************************************************************************************************************/
// CFindOutputWnd

IMPLEMENT_DYNAMIC(CFindOutputWnd, CDockablePane)

CFindOutputWnd::CFindOutputWnd()
{

}

CFindOutputWnd::~CFindOutputWnd()
{
}


BEGIN_MESSAGE_MAP(CFindOutputWnd, CDockablePane)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_DESTROY()
END_MESSAGE_MAP()



// CFindOutputWnd message handlers

int CFindOutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CDockablePane::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here

		CRect rectDummy;
		rectDummy.SetRectEmpty();

		// Create tabs window:
		const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

		if (!this->m_output.Create(dwStyle, rectDummy, this, 1))
		{
				TRACE0("Failed to create output list window\n");
				return -1;      // fail to create
		}

	return 0;

		return 0;
}

void CFindOutputWnd::OnSize(UINT nType, int cx, int cy)
{
		CDockablePane::OnSize(nType, cx, cy);
		
		// TODO: Add your message handler code here
		this->m_output.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFindOutputWnd::OnDestroy()
{
		CDockablePane::OnDestroy();

		// TODO: Add your message handler code here
}


void CFindOutputWnd::Clear()
{
		m_output.Clear();
}



void	CFindOutputWnd::Append(const CString &msg, size_t line, size_t col,size_t length, CWnd *target)
{
		CFindOutputList::Param param(line, col, length, target);
		m_output.Append(msg, param);
}
