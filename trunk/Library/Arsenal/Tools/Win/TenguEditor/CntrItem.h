
// CntrItem.h : interface of the CTenguEditorCntrItem class
//

#pragma once

class CTenguEditorDoc;
class CTenguEditorView;


class CTenguEditorCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CTenguEditorCntrItem)

// Constructors
public:
	CTenguEditorCntrItem(REOBJECT* preo = NULL, CTenguEditorDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CTenguEditorDoc* GetDocument()
		{ return reinterpret_cast<CTenguEditorDoc*>(CRichEditCntrItem::GetDocument()); }
	CTenguEditorView* GetActiveView()
		{ return reinterpret_cast<CTenguEditorView*>(CRichEditCntrItem::GetActiveView()); }

// Implementation
public:
	~CTenguEditorCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

