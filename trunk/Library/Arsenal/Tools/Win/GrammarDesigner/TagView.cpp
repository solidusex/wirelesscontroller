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

// TagView.cpp : implementation file
//

#include "stdafx.h"
#include "GrammarDesigner.h"
#include "TagView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CTagTree

IMPLEMENT_DYNAMIC(CTagTree, CTreeCtrl)

CTagTree::CTagTree()
{
		m_font.CreatePointFont(90, TEXT("Consolas"));
}

CTagTree::~CTagTree()
{
}

static void __delete_items(CTreeCtrl *tree, HTREEITEM items)
{
		ASSERT(tree != NULL);

		if (tree->ItemHasChildren(items))
		{
				
				HTREEITEM first = tree->GetChildItem(items);

				while (first != NULL)
				{
						HTREEITEM next = tree->GetNextItem(first,TVGN_NEXT);
						tree->DeleteItem(first);
						first = next;
				}
		}
}


void	CTagTree::Clear()
{
		//this->DeleteAllItems();
		change_state(m_name_tbl);
		change_state(m_term_tbl);
		change_state(m_prec_tbl);
		change_state(m_rule_tbl);

		change_state(m_predef_tbl);
		change_state(m_action_tbl);

		update_tree_node(m_name_tbl,	m_name);
		update_tree_node(m_prec_tbl,	m_prec);
		update_tree_node(m_term_tbl,	m_term);
		update_tree_node(m_rule_tbl,	m_rule);

		update_tree_node(m_predef_tbl,	m_predef);

		update_tree_node(m_action_tbl,	m_action);
		
		__delete_items(this, m_name);
		__delete_items(this, m_term);
		__delete_items(this, m_prec);
		__delete_items(this, m_rule);

		__delete_items(this, m_predef);
		__delete_items(this, m_action);
		
		
		m_name_tbl.RemoveAll();
		m_term_tbl.RemoveAll();
		m_prec_tbl.RemoveAll();
		m_rule_tbl.RemoveAll();
		m_predef_tbl.RemoveAll();
		m_action_tbl.RemoveAll();
		
}

HTREEITEM CTagTree::InsertText(LPCTSTR lpszItem, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
		return this->InsertItem(TVIF_TEXT|TVIF_PARAM, lpszItem ,0,0,0,0, lParam, hParent,hInsertAfter);
}


void	CTagTree::change_state(CMapTable &src)
{
		POSITION		pos = src.GetStartPosition();

		CString key;
		CSrcInfo *val = NULL;

		while(pos != NULL)
		{
				src.GetNextAssoc(pos, key, val);
				ASSERT(val != NULL);
				val->m_refreash = false;
		}

}

void	CTagTree::update_table(CMapTable &src, LPCTSTR name, size_t line)
{
		CString			key;
		CSrcInfo		*val;
		
		val = NULL;
		if(src.Lookup(name, val))
		{
				ASSERT(val != NULL);

				val->m_name = name;
				val->m_line = line;
				val->m_refreash = true;
		}else
		{
				val = new CSrcInfo(name, line, NULL);
				val->m_refreash = true;
				src.SetAt(name, val);
		}
}

void CTagTree::update_tree_node(CMapTable &src, HTREEITEM node)
{
		ASSERT(node != NULL);
		
		POSITION		pos = src.GetStartPosition();

		CString key;
		CSrcInfo *val = NULL;
		
		while(pos != NULL)
		{
				src.GetNextAssoc(pos, key, val);
				ASSERT(val != NULL);

				if(val->m_refreash)
				{
						if(val->m_item == NULL)
						{
								val->m_item = this->InsertText(val->m_name, val->m_line, node);
						}else
						{
								this->SetItemData(val->m_item, (WPARAM)val->m_line);
						}
				}else
				{
						ASSERT(val->m_item != NULL);

						this->DeleteItem(val->m_item);
						src.RemoveKey(key);
						delete val;
				}
		}
}

void	CTagTree::update_action_table(const ARSpace::cfgConfig_t *cfg)
{
		
		change_state(m_action_tbl);
/****************************************************************/
		typedef struct __action_record_tag
		{
				size_t	line;
				BOOL	has_definition;
		}ActionRec_t;
		CMap<CString, LPCTSTR, ActionRec_t*, ActionRec_t*>	action_map;

		for(size_t i = 0; i < cfg->tok_cnt; ++i)
		{
				const ARSpace::cfgToken_t *tok = &cfg->tok[i];
		
				CString name;
				size_t  line;
				BOOL	has_definition = FALSE;
				ActionRec_t *val;
				if(tok->action_name != NULL)
				{
						name.SetString(tok->action_name);
						line = tok->action_line;
						has_definition = tok->action_ins == NULL ? FALSE : TRUE;
						
						if(action_map.Lookup(name, val))
						{
								if(has_definition)
								{
										val->line = line;
										val->has_definition = TRUE;
								}else
								{

								}
						}else
						{
								val = new ActionRec_t;
								val->has_definition = has_definition;
								val->line = line;
								action_map.SetAt(name, val);
						}
				}

		}

		for(size_t i = 0; i < cfg->rule_cnt; ++i)
		{
				CString name;
				size_t  line;
				BOOL	has_definition = FALSE;
				ActionRec_t *val;
				if(cfg->rule[i].action_name != NULL)
				{
						name.SetString(cfg->rule[i].action_name);
						line = cfg->rule[i].action_line;
						has_definition = cfg->rule[i].action_ins == NULL ? FALSE : TRUE;

						if(action_map.Lookup(name, val))
						{
								if(has_definition)
								{
										val->line = line;
										val->has_definition = TRUE;
								}else
								{

								}
						}else
						{
								val = new ActionRec_t;
								val->has_definition = has_definition;
								val->line = line;
								action_map.SetAt(name, val);
						}
				}
		}
		
		POSITION		pos = action_map.GetStartPosition();

		CString key;
		ActionRec_t *val = NULL;
		
		size_t cnt = 0;
		while(pos != NULL)
		{
				action_map.GetNextAssoc(pos, key, val);
				ASSERT(val != NULL);
				action_map.RemoveKey(key);
				this->update_table(m_action_tbl, key, val->line);
				delete val;
				cnt++;
		}

		update_tree_node(m_action_tbl, m_action);

		CString str;
		str.Format(TEXT("Actions (%d)"), cnt);
		this->SetItemText(m_action, str);
}

void	CTagTree::UpdateTag(const ARSpace::cfgConfig_t *cfg)
{
		ASSERT(cfg != NULL);
		
		CString str;
		CMapTable		tmp;
		
		change_state(m_name_tbl);
		change_state(m_term_tbl);
		change_state(m_prec_tbl);
		change_state(m_rule_tbl);
		change_state(m_predef_tbl);

		for(size_t i = 0; i < cfg->name_cnt; ++i)
		{
				const ARSpace::cfgName_t *name = &cfg->name[i];
				if(name->name == NULL)
				{
						str.Format(TEXT("Null Token %d"), i);
				}else
				{
						str = name->name;
				}

				update_table(m_name_tbl, str, name->line);
		}

		for(size_t i = 0; i < cfg->tok_cnt; ++i)
		{
				const ARSpace::cfgToken_t *tok = &cfg->tok[i];
				if(tok->tokval == 0)continue;

				if(tok->name == NULL)
				{
						str.Format(TEXT("Null Token %d"), i);
				}else
				{
						str = tok->name;
				}
				update_table(m_term_tbl, str, tok->line);
		}


		for(size_t i = 0; i < cfg->prec_cnt; ++i)
		{
				size_t k;
				const ARSpace::cfgPrec_t *prec = &cfg->prec[i];
				
				CString str;
				for(k = 0; k < prec->count; ++k)
				{
						ASSERT(prec->prec_tok_set[k] != NULL);
						str = prec->prec_tok_set[k];
						//str.Format(TEXT("%ls : %d"), prec->prec_tok_set[k], prec->prec_level);
						update_table(m_prec_tbl, str, prec->line);
				}
				
				
				/*
				if(prec->prec_tok == NULL)
				{
						str.Format(TEXT("Null Token %d"), i);
				}else
				{
						str = prec->prec_tok;
				}
				update_table(m_prec_tbl, str, prec->line);
				*/
		}


		for(size_t i = 0; i < cfg->rule_cnt; ++i)
		{
				const ARSpace::cfgRule_t *rule = &cfg->rule[i];
				
				ASSERT(rule && rule->lhs);
				
				update_table(m_rule_tbl, rule->lhs, rule->line);
		}
		
		size_t	code_i = 0;
		for(size_t i = 0; i < cfg->predef_cnt; ++i)
		{
				const ARSpace::cfgPreDef_t *def = &cfg->pre_def[i];
				CString name;
				if(def->name == NULL || wcslen(def->name) == 0)
				{
						name.Format(L"Code %d", code_i++);
				}else
				{
						name = def->name;
				}
				update_table(m_predef_tbl, name.GetString(), def->line);
		}

		update_action_table(cfg);

		update_tree_node(m_name_tbl, m_name);
		update_tree_node(m_term_tbl, m_term);
		update_tree_node(m_prec_tbl, m_prec);
		update_tree_node(m_rule_tbl, m_rule);
		update_tree_node(m_predef_tbl, m_predef);

		
		
		
		

		str.Format(TEXT("Name (%d)"), cfg->name_cnt);
		this->SetItemText(m_name, str);


		str.Format(TEXT("Term (%d)"), cfg->tok_cnt);
		this->SetItemText(m_term, str);


		str.Format(TEXT("Prec (%d)"), cfg->prec_cnt);
		this->SetItemText(m_prec, str);


		str.Format(TEXT("Rule (%d)"), cfg->rule_cnt);
		this->SetItemText(m_rule, str);


		str.Format(TEXT("PreDef (%d)"), cfg->predef_cnt);
		this->SetItemText(m_predef, str);

		
}




BEGIN_MESSAGE_MAP(CTagTree, CTreeCtrl)
		ON_WM_CREATE()
		ON_WM_LBUTTONDBLCLK()
		ON_WM_LBUTTONDOWN()
		ON_COMMAND(ID_TAGVIEW_FONT, &CTagTree::OnTagviewFont)
		ON_WM_CONTEXTMENU()
		ON_NOTIFY_REFLECT(NM_RCLICK, &CTagTree::OnNMRClick)
		ON_COMMAND(ID_TAGVIEW_REBUILD, &CTagTree::OnTagviewRebuild)
		ON_WM_DESTROY()
END_MESSAGE_MAP()



// CTagTree message handlers

int CTagTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
		if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
				return -1;

		// TODO:  Add your specialized creation code here
		this->SetFont(&m_font);
		
		m_name = this->InsertItem(TEXT("Name"));
		m_term = this->InsertItem(TEXT("Term"));
		m_prec = this->InsertItem(TEXT("Prec"));
		m_rule = this->InsertItem(TEXT("Rule"));
		m_predef = this->InsertItem(TEXT("PreDef"));
		m_action = this->InsertItem(TEXT("Actions"));
		//Clear();
		return 0;
}



void CTagTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default

		HTREEITEM curr = this->GetSelectedItem();

		if(curr != NULL && curr != m_name && curr != m_term && curr != m_prec && curr != m_rule && curr != m_predef && curr != m_action)
		{
				CString txt = this->GetItemText(curr);
				
				CView *pview = ((CFrameWnd*)::AfxGetMainWnd())->GetActiveView();
				
				if(pview)
				{
						pview->SendMessage(ID_EDIT_LOCATE_POS, this->GetItemData(curr));
				}

		}else
		{

		}
		

		CTreeCtrl::OnLButtonDblClk(nFlags, point);
}



void CTagTree::OnLButtonDown(UINT nFlags, CPoint point)
{
		// TODO: Add your message handler code here and/or call default
		CTreeCtrl::OnLButtonDown(nFlags, point);

		HTREEITEM curr = this->HitTest(point);
		
		this->SelectItem(curr);
}


const CSrcInfo*	CTagTree::LookupByName(const CString &name)
{
		CSrcInfo *val = NULL;

		if(m_term_tbl.Lookup(name, val))
		{
				return val;
		}

		if(m_rule_tbl.Lookup(name, val))
		{
				return val;
		}

		if(m_prec_tbl.Lookup(name, val))
		{
				return val;
		}

		if(m_name_tbl.Lookup(name, val))
		{
				return val;
		}


		if(m_action_tbl.Lookup(name, val))
		{
				return val;
		}

		if(m_predef_tbl.Lookup(name, val))
		{
				return val;
		}


		return NULL;

}



void CTagTree::OnTagviewFont()
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




void CTagTree::OnContextMenu(CWnd* pWnd, CPoint point)
{
		// TODO: Add your message handler code here

		CMenu menu;
		menu.LoadMenu(IDR_MENU_TAGVIEW);

		CMenu* pSumMenu = menu.GetSubMenu(0);
	
		((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pSumMenu->GetSafeHmenu(),point.x, point.y, this, TRUE);

		SetFocus();
}



void CTagTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
		// TODO: Add your control notification handler code here
		*pResult = 0;

		CPoint pt;
		GetCursorPos(&pt);
		OnContextMenu(this, pt);
}




void CTagTree::OnTagviewRebuild()
{
		// TODO: Add your command handler code here
		
		
		CView *pview = ((CFrameWnd*)::AfxGetMainWnd())->GetActiveView();

		if(pview)
		{
				pview->SendMessage(WM_COMMAND, (WPARAM)ID_TOOLS_REBUILDTAGS); 
		}
}


void CTagTree::OnDestroy()
{
		this->Clear();
		CTreeCtrl::OnDestroy();
		// TODO: Add your message handler code here
}



//////////////////////////////// CTagView//////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CTagView, CDockablePane)

CTagView::CTagView()
{

}

CTagView::~CTagView()
{
}


BEGIN_MESSAGE_MAP(CTagView, CDockablePane)
		ON_WM_CREATE()
		ON_WM_SIZE()
		
END_MESSAGE_MAP()



// CTagView message handlers



int CTagView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
// TagView.cpp : implementation file
//




void CTagView::OnSize(UINT nType, int cx, int cy)
{
		CDockablePane::OnSize(nType, cx, cy);
		m_tree.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
		// TODO: Add your message handler code here
}


void	CTagView::UpdateTag(const ARSpace::cfgConfig_t *cfg)
{
		//ASSERT(cfg != NULL);
		if(cfg != NULL)
		{
				m_tree.UpdateTag(cfg);
		}else
		{
				m_tree.Clear();
		}

		m_tree.Invalidate();
}



const CSrcInfo*	CTagView::LookupByName(const CString &name)
{
		return m_tree.LookupByName(name);
}
