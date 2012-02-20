
// TenguEditorView.h : interface of the CTenguEditorView class
//


#pragma once

class CTenguEditorCntrItem;

class CTenguEditorView : public CRichEditView
{
protected: // create from serialization only
	CTenguEditorView();
	DECLARE_DYNCREATE(CTenguEditorView)

// Attributes
public:
	CTenguEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTenguEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TenguEditorView.cpp
inline CTenguEditorDoc* CTenguEditorView::GetDocument() const
   { return reinterpret_cast<CTenguEditorDoc*>(m_pDocument); }
#endif

