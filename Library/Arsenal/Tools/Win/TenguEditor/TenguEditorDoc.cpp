
// TenguEditorDoc.cpp : implementation of the CTenguEditorDoc class
//

#include "stdafx.h"
#include "TenguEditor.h"

#include "TenguEditorDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTenguEditorDoc

IMPLEMENT_DYNCREATE(CTenguEditorDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CTenguEditorDoc, CRichEditDoc)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CTenguEditorDoc construction/destruction

CTenguEditorDoc::CTenguEditorDoc()
{
	// TODO: add one-time construction code here

}

CTenguEditorDoc::~CTenguEditorDoc()
{
}

BOOL CTenguEditorDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CTenguEditorDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CTenguEditorCntrItem(preo, const_cast<CTenguEditorDoc*>(this));
}




// CTenguEditorDoc serialization

void CTenguEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}


// CTenguEditorDoc diagnostics

#ifdef _DEBUG
void CTenguEditorDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CTenguEditorDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CTenguEditorDoc commands
