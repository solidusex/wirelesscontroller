
// CntrItem.cpp : implementation of the CTenguEditorCntrItem class
//

#include "stdafx.h"
#include "TenguEditor.h"

#include "TenguEditorDoc.h"
#include "TenguEditorView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTenguEditorCntrItem implementation

IMPLEMENT_SERIAL(CTenguEditorCntrItem, CRichEditCntrItem, 0)

CTenguEditorCntrItem::CTenguEditorCntrItem(REOBJECT* preo, CTenguEditorDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CTenguEditorCntrItem::~CTenguEditorCntrItem()
{
	// TODO: add cleanup code here
}


// CTenguEditorCntrItem diagnostics

#ifdef _DEBUG
void CTenguEditorCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CTenguEditorCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

