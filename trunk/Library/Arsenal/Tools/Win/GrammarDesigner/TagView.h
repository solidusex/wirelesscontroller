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

#pragma once





// CTagTree

class CSrcInfo
{
public:
		HTREEITEM		m_item;
		CString			m_name;
		size_t			m_line;
		bool			m_refreash;
public:
		CSrcInfo() : m_item(NULL), m_name(TEXT("")), m_line(0), m_refreash(false)
		{

		}

		CSrcInfo(const CString &str, size_t line = 0, HTREEITEM item = NULL) : m_name(str), m_line(line), m_item(item), m_refreash(false)
		{

		}

		~CSrcInfo()
		{

		}

		CSrcInfo& operator=(const CSrcInfo &src)
		{
				if(this != &src)
				{
						this->m_item = src.m_item;
						this->m_name = src.m_name;
						this->m_line = src.m_line;
				}

				return *this;
		}

		CSrcInfo(const CSrcInfo &src)
		{
				*this = src;
		}

};



class CTagTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTagTree)
private:
		HTREEITEM		m_name;
		HTREEITEM		m_term;
		HTREEITEM		m_prec;
		HTREEITEM		m_rule;
		HTREEITEM		m_predef;
		HTREEITEM		m_action;
		CFont			m_font;


		typedef	CMap<CString, LPCTSTR, CSrcInfo*, CSrcInfo*>	CMapTable;

		CMapTable		m_name_tbl;
		CMapTable		m_term_tbl;
		CMapTable		m_prec_tbl;
		CMapTable		m_rule_tbl;
		CMapTable		m_predef_tbl;
		CMapTable		m_action_tbl;

protected:
		void	CTagTree::update_table(CMapTable &src, LPCTSTR name, size_t line);
		void	CTagTree::update_tree_node(CMapTable &src, HTREEITEM node);
		void	CTagTree::change_state(CMapTable &src);
public:
	CTagTree();
	virtual ~CTagTree();
public:
		void	update_action_table(const ARSpace::cfgConfig_t *cfg);
		void	UpdateTag(const ARSpace::cfgConfig_t *cfg);
		
		HTREEITEM InsertText(LPCTSTR lpszItem, LPARAM lParam, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
		void	Clear();
		
		const CSrcInfo*	LookupByName(const CString &name);
protected:
	DECLARE_MESSAGE_MAP()
public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnTagviewFont();
		afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
		afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTagviewRebuild();
		afx_msg void OnDestroy();
};





// CTagView




class CTagView : public CDockablePane
{
	DECLARE_DYNAMIC(CTagView)
private:
		CTagTree		m_tree;
		
public:
	CTagView();
	virtual ~CTagView();

protected:
	DECLARE_MESSAGE_MAP()
public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);

public:
		void	UpdateTag(const ARSpace::cfgConfig_t *cfg);
		
		const CSrcInfo*	LookupByName(const CString &name);

};

