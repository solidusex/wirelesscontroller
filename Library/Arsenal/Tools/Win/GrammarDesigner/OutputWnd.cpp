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
#include "GrammarDesigner.h"
#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




IMPLEMENT_DYNAMIC(COutputList, CListBox)
// COutputList1

COutputList::COutputList()
{
		m_font.CreatePointFont(90, TEXT("Consolas"));

}

COutputList::~COutputList()
{
		
}



void	COutputList::Append(const CString &msg, const Param &param)
{
		int idx = this->AddString(msg);
		Param *ptr = new Param;
		*ptr = param;
		this->SetItemDataPtr(idx, (void*)ptr);
}


void	COutputList::Clear()
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

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
//	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &COutputList::OnUpdateEditCopy)
	ON_COMMAND(ID_OUTPUTWND_FONT, &COutputList::OnOutputwndFont)
	ON_WM_DESTROY()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers



void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{

	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);
	
	((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pSumMenu->GetSafeHmenu(),point.x, point.y, this, TRUE);

	SetFocus();

}

void COutputList::OnEditCopy()
{
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

void COutputList::OnEditClear()
{
		Clear();
}


//void COutputList::OnViewOutput()
//{
//	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner()->GetOwner());
//	CMainFrame *pMainFrame =  DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
//	
//	if(pParentBar && pMainFrame)
//	{
//			pMainFrame->SetFocus();
//			pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
//			pMainFrame->RecalcLayout();
//	}
//}


void COutputList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default
		
		CListBox::OnLButtonDblClk(nFlags, point);

		int idx = this->GetCurSel();

		if(idx != -1)
		{
				Param *ptr = (Param*)this->GetItemData(idx);

				if(ptr->type != MSG_MESSAGE && ptr->target != NULL)
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





int COutputList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CListBox::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		this->SetFont(&m_font);

		/*this->AddString(TEXT(__FUNCSIG__));
		Param param;
		this->Append(TEXT(__FUNCSIG__), param);
		*/
		return 0;
}


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



void COutputList::OnRButtonDown(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default

		int i = GetSelectIndex(*this, point);

		if(i != -1) this->SetCurSel(i);

		CListBox::OnRButtonDown(nFlags, point);
}

void COutputList::OnLButtonDown(UINT nFlags, CPoint point)
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



void COutputList::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		
		pCmdUI->Enable(this->GetCurSel() >= 0);

}

void COutputList::OnOutputwndFont()
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

BOOL COutputList::PreCreateWindow(CREATESTRUCT& cs)
{
		// TODO: Add your specialized code here and/or call the base class
		const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
		cs.style = dwStyle;
		return CListBox::PreCreateWindow(cs);
}


void COutputList::OnDestroy()
{
		Clear();
		CListBox::OnDestroy();

		// TODO: Add your message handler code here
}



/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}




BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

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
}


void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	// Tab control should cover the whole client area:
	this->m_output.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}



void	COutputWnd::Append(const CString &msg, COutputList::MsgType type, size_t line, CWnd *target)
{
		//this->Append(msg, COutputList::Param(type, line, target));
		m_output.Append(msg, COutputList::Param(type, line, target));
}

void COutputWnd::Clear()
{
		m_output.Clear();
}
void COutputWnd::OnDestroy()
{
		CDockablePane::OnDestroy();

		// TODO: Add your message handler code here
}
