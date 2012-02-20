
// TenguEditorView.cpp : implementation of the CTenguEditorView class
//

#include "stdafx.h"
#include "TenguEditor.h"

#include "TenguEditorDoc.h"
#include "CntrItem.h"
#include "TenguEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTenguEditorView

IMPLEMENT_DYNCREATE(CTenguEditorView, CRichEditView)

BEGIN_MESSAGE_MAP(CTenguEditorView, CRichEditView)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTenguEditorView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTenguEditorView construction/destruction

CTenguEditorView::CTenguEditorView()
{
	// TODO: add construction code here

}

CTenguEditorView::~CTenguEditorView()
{
}

BOOL CTenguEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CTenguEditorView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch)
	SetMargins(CRect(720, 720, 720, 720));
}


// CTenguEditorView printing


void CTenguEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTenguEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CTenguEditorView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CRichEditView::OnDestroy();
}


void CTenguEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTenguEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTenguEditorView diagnostics

#ifdef _DEBUG
void CTenguEditorView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CTenguEditorView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CTenguEditorDoc* CTenguEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTenguEditorDoc)));
	return (CTenguEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CTenguEditorView message handlers
