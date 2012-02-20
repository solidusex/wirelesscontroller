
// GrammarDesignerDoc.h : interface of the CGrammarDesignerDoc class
//


#pragma once
#include "textfile.h"
#include "BackEndThread.h"



#define MAX_ERROR_COUNT			10

class CGrammarDesignerDoc : public CRichEditDoc 
{
private:

protected: // create from serialization only
	CGrammarDesignerDoc();
	DECLARE_DYNCREATE(CGrammarDesignerDoc)

public:
		/*enum TEXTENCODING { ASCII, UNI16_BE, UNI16_LE, UTF_8 };*/
		typedef CTextFileBase::TEXTENCODING		EncodingType;

// Attributes
private:
		EncodingType	m_encoding;

		ARSpace::psrModeType_t	m_parser_mode;
		uint_t					m_lexer_mode;
private:
		CString			m_src_cache;

private:
		ARSpace::lex_t			*m_lexer;
		ARSpace::psrGrammar_t	*m_grammar;
		const ARSpace::parser_t	*m_parser;

private:
		CBackEndThread			m_thread;

// Operations
public:
		EncodingType	GetEncoding()const
		{
				return m_encoding;
		}

// Overrides
public:
	virtual BOOL OnNewDocument();

// Implementation
public:
	virtual ~CGrammarDesignerDoc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo = NULL) const;
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
		void	OnEndcodingChange(UINT nID);

		bool	BuildParser(const ARSpace::cfgConfig_t *cfg);

		bool	IsParseable()const;

		void	ClearParser();

		void	OnTagBuildCompleted(const ARSpace::cfgConfig_t *cfg);

public:
//		virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//		virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

public:
		
		afx_msg void OnEndcodingChangeUI(CCmdUI *pCmdUI);
		
		afx_msg void OnToolsRebuildtags();

		afx_msg void OnChangeParserMode(UINT nID);
		afx_msg void OnUpdateParserModeLalr(CCmdUI *pCmdUI);
		//afx_msg void OnUpdateParserModeLr(CCmdUI *pCmdUI);
		afx_msg void OnUpdateParserModeSlr(CCmdUI *pCmdUI);
		afx_msg void OnEditGotoDecl();
		afx_msg void OnUpdateEditGotoDecl(CCmdUI *pCmdUI);
		afx_msg void OnParserBuild();
		afx_msg void OnParserShowactiontable();
		afx_msg void OnUpdateParserShowactiontable(CCmdUI *pCmdUI);
		afx_msg void OnParserShowconflict();
		afx_msg void OnUpdateParserShowconflict(CCmdUI *pCmdUI);
		afx_msg void OnParserShowfirstfollow();
		afx_msg void OnUpdateParserShowfirstfollow(CCmdUI *pCmdUI);
		afx_msg void OnParserParse();
		afx_msg void OnUpdateParserParse(CCmdUI *pCmdUI);
		afx_msg void OnShowLeftrecursion();
		afx_msg void OnUpdateShowLeftrecursion(CCmdUI *pCmdUI);

public:
		virtual void Serialize(CArchive& ar);
		virtual BOOL SaveModified();

public:
		
		afx_msg void OnTestTest();
		
		
		afx_msg void OnTestTest2();
		afx_msg void OnGenerateTemplate();
		afx_msg void OnStringsStringconverter();
		afx_msg void OnFlagsReportskip();
		afx_msg void OnUpdateFlagsReportskip(CCmdUI *pCmdUI);
		afx_msg void OnFlagsSingleline();
		afx_msg void OnUpdateFlagsSingleline(CCmdUI *pCmdUI);
		afx_msg void OnFlagsIgnorecase();
		afx_msg void OnUpdateFlagsIgnorecase(CCmdUI *pCmdUI);
		afx_msg void OnShowLeftfactor();
		afx_msg void OnUpdateShowLeftfactor(CCmdUI *pCmdUI);
		afx_msg void OnEditFindallreferences();
		afx_msg void OnUpdateEditFindallreferences(CCmdUI *pCmdUI);
		afx_msg void OnUpdateParserBuild(CCmdUI *pCmdUI);
};


