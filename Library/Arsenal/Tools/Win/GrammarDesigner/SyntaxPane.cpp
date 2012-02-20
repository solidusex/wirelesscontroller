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

// SyntaxPane.cpp : implementation file
//

#include "stdafx.h"

#include "GrammarDesigner.h"

#include "SyntaxPane.h"


#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSyntaxPane

IMPLEMENT_DYNAMIC(CSyntaxPane, CDockablePane)

CSyntaxPane::CSyntaxPane()
{

}

CSyntaxPane::~CSyntaxPane()
{
}


void CSyntaxPane::Clear()
{
		m_tree.Clear();
}


BEGIN_MESSAGE_MAP(CSyntaxPane, CDockablePane)
		ON_WM_CREATE()
		ON_WM_SIZE()
END_MESSAGE_MAP()



// CSyntaxPane message handlers
int CSyntaxPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CDockablePane::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		CRect rectDummy;

		rectDummy.SetRectEmpty();

		const DWORD dwStyle = TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES  | TVS_DISABLEDRAGDROP  | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

		if (!this->m_tree.Create(dwStyle, rectDummy, this, 1))
		{
				TRACE0("Failed to create tagview tree window\n");
				return -1;      // fail to create
		}
		
		

		return 0;
}


void CSyntaxPane::OnSize(UINT nType, int cx, int cy)
{
		CDockablePane::OnSize(nType, cx, cy);

		// TODO: Add your message handler code here
		m_tree.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


void	CSyntaxPane::DrawTree(CPrintNode *node)
{
		m_tree.DrawTree(node);

		//m_tree.ExpandAll();

		m_tree.ExpandLevel(5);
}


/**********************************SyntaxTree*************************************************/
IMPLEMENT_DYNAMIC(CSyntaxTree, CTreeCtrl)

CSyntaxTree::CSyntaxTree()
{
		m_font.CreatePointFont(100, TEXT("Consolas"));
		m_root = NULL;
}

CSyntaxTree::~CSyntaxTree()
{
		
}

void	CSyntaxTree::Clear()
{
		if(m_root != NULL)
		{
				CPrintNode* root = (CPrintNode*)this->GetItemData(m_root);
				this->DeleteAllItems();
				delete root;
				m_root = NULL;
		}
}

BEGIN_MESSAGE_MAP(CSyntaxTree, CTreeCtrl)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_LBUTTONDBLCLK()
ON_WM_CONTEXTMENU()
ON_NOTIFY_REFLECT(NM_RCLICK, &CSyntaxTree::OnNMRClick)
ON_COMMAND(ID_POPUP_FONT32864, &CSyntaxTree::OnPopupFont32864)
ON_COMMAND(ID_POPUP_CLEAR32865, &CSyntaxTree::OnPopupClear32865)
ON_UPDATE_COMMAND_UI(ID_POPUP_CLEAR32865, &CSyntaxTree::OnUpdatePopupClear32865)
ON_COMMAND(ID_SYNTAX_MENU_EXPAND, &CSyntaxTree::OnSyntaxMenuExpand)
ON_UPDATE_COMMAND_UI(ID_SYNTAX_MENU_EXPAND, &CSyntaxTree::OnUpdateSyntaxMenuExpand)
ON_COMMAND(ID_POPUP_COLLAPSE, &CSyntaxTree::OnPopupCollapse)
ON_UPDATE_COMMAND_UI(ID_POPUP_COLLAPSE, &CSyntaxTree::OnUpdatePopupCollapse)
END_MESSAGE_MAP()


int CSyntaxTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		
		this->SetFont(&m_font);
		return 0;
}


HTREEITEM CSyntaxTree::InsertText(LPCTSTR lpszItem, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
		return this->InsertItem(TVIF_TEXT|TVIF_PARAM, lpszItem ,0,0,0,0, lParam, hParent,hInsertAfter);
}


HTREEITEM	CSyntaxTree::insert_node(CPrintNode *node, HTREEITEM parent)
{
		HTREEITEM hdl = InsertText(node->m_name, (LPARAM)node, parent);

		POSITION pos = node->m_nodes.GetHeadPosition();

		while(pos != NULL)
		{
				CPrintNode *chd = node->m_nodes.GetNext(pos);
				insert_node(chd, hdl);
		}

		return hdl;
}

void	CSyntaxTree::DrawTree(CPrintNode *node)
{
		Clear();
		ASSERT(node != NULL);
		m_root = insert_node(node, TVI_ROOT);
}

void CSyntaxTree::OnDestroy()
{
		// TODO: Add your message handler code here
		Clear();

		CTreeCtrl::OnDestroy();
		
}

void CSyntaxTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
		//CTreeCtrl::OnLButtonDblClk(nFlags, point);

		// TODO: Add your message handler code here and/or call default
		HTREEITEM curr = this->GetSelectedItem();

		if(curr != NULL)
		{
				CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
				const CPrintNode *node = (const CPrintNode*)this->GetItemData(curr);
				ASSERT(node != NULL);
				if(node->m_is_term)
				{
						ASSERT(node != NULL);

						CInputPane &input = main_frm->GetInputPane();

						input.SendMessage(ID_INPUT_LOCATE_TOKEN, (WPARAM)node);
				}else
				{
						CTagView		&tag = main_frm->GetTagView();

						const CSrcInfo *info = tag.LookupByName(node->m_name);


						CView *pview = ((CFrameWnd*)::AfxGetMainWnd())->GetActiveView();

						if(info && pview)
						{
								pview->SendMessage(ID_EDIT_LOCATE_POS, (WPARAM)info->m_line);
						}

				}

		}else
		{

		}
}

void CSyntaxTree::OnContextMenu(CWnd* pWnd, CPoint point)
{
		// TODO: Add your message handler code here

		CMenu menu;
		menu.LoadMenu(IDR_SYNTAXTREE_MENU);

		CMenu* pSumMenu = menu.GetSubMenu(0);

		((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pSumMenu->GetSafeHmenu(),point.x, point.y, this, TRUE);

		SetFocus();

}

void CSyntaxTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
		// TODO: Add your control notification handler code here
	

		POINT pos ;
		if(!GetCursorPos(&pos))
				return ;
		this->ScreenToClient(&pos);
		UINT uFlags;
		HTREEITEM hItem = this->HitTest(pos, &uFlags);
		if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
		{
				this->Select(hItem, TVGN_CARET);
		}else
		{
				this->SelectItem(NULL);
		}

		CPoint pt;
		GetCursorPos(&pt);
		OnContextMenu(this, pt);

		*pResult = 0;
		
		
}

void CSyntaxTree::OnPopupFont32864()
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

void CSyntaxTree::OnPopupClear32865()
{
		// TODO: Add your command handler code here

		this->Clear();
}

void CSyntaxTree::OnUpdatePopupClear32865(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_root != NULL);
}


static void __expand_tree(int_t level, CTreeCtrl &tree, HTREEITEM	item)
{
		if(level <= 0 || item == NULL)return;
		
		if(tree.ItemHasChildren(item))
		{
				VERIFY(tree.Expand(item, TVE_EXPAND));
				HTREEITEM chd = tree.GetChildItem(item);

				while(chd != NULL)
				{
						__expand_tree(level - 1, tree, chd);
						chd = tree.GetNextSiblingItem(chd);
				}
		}
}

void CSyntaxTree::ExpandLevel(size_t level)
{
		if(this->GetRootItem() == NULL)return;

		__expand_tree(level, *this, this->GetRootItem());
}


void	CSyntaxTree::ExpandAll(DWORD action )
{
		if(m_root == NULL)return ;
		
		//VERIFY(this->Expand(m_root, TVE_EXPAND));

		HTREEITEM	item = this->GetRootItem();
		CList<HTREEITEM> que;
		
		if(item != NULL)que.AddTail(item);
		
		while(!que.IsEmpty())
		{
				item = que.RemoveHead();

				if(this->ItemHasChildren(item))
				{
						//VERIFY(this->Expand(item, TVE_EXPAND));
						this->Expand(item, action);
						

						HTREEITEM chd = this->GetChildItem(item);

						while(chd != NULL)
						{
								que.AddTail(chd);
								chd = this->GetNextSiblingItem(chd);
						}
				}
		}
} 

void CSyntaxTree::ExpandItem(HTREEITEM	item, DWORD action)
{
		if(item == NULL)return ;

		CList<HTREEITEM> que;
		
		if(item != NULL)que.AddTail(item);
		
		while(!que.IsEmpty())
		{
				item = que.RemoveHead();

				if(this->ItemHasChildren(item))
				{
						//VERIFY(this->Expand(item, TVE_EXPAND));
						this->Expand(item, action);
						

						HTREEITEM chd = this->GetChildItem(item);

						while(chd != NULL)
						{
								que.AddTail(chd);
								chd = this->GetNextSiblingItem(chd);
						}
				}
		}
}


void CSyntaxTree::OnSyntaxMenuExpand()
{
		// TODO: Add your command handler code here
		/*ExpandAll();*/
		
		this->ExpandItem(this->GetSelectedItem(), TVE_EXPAND);
		
}


void CSyntaxTree::OnPopupCollapse()
{
		// TODO: Add your command handler code here
		//ExpandAll(TVE_COLLAPSE);
		
		this->ExpandItem(this->GetSelectedItem(), TVE_COLLAPSE);
}

void CSyntaxTree::OnUpdateSyntaxMenuExpand(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(this->GetSelectedItem() != NULL);
}


void CSyntaxTree::OnUpdatePopupCollapse(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(this->GetSelectedItem() != NULL);
}
