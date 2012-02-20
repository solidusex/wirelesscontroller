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


// GrammarDesignerDoc.cpp : implementation of the CGrammarDesignerDoc class
//

#include "stdafx.h"
#include <memory>

#include "PrintNode.h"
#include "MainFrm.h"

#include "GrammarDesigner.h"
#include "GrammarDesignerDoc.h"
#include "GrammarDesignerView.h"

#include "StringConvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ARSpace;

// CGrammarDesignerDoc

IMPLEMENT_DYNCREATE(CGrammarDesignerDoc, CRichEditDoc);


BEGIN_MESSAGE_MAP(CGrammarDesignerDoc, CRichEditDoc)

		ON_COMMAND_RANGE(ID_ENDCODING_ASCII, ID_ENDCODING_UTF8, &CGrammarDesignerDoc::OnEndcodingChange)
		ON_UPDATE_COMMAND_UI_RANGE(ID_ENDCODING_ASCII, ID_ENDCODING_UTF8, &CGrammarDesignerDoc::OnEndcodingChangeUI)

		ON_COMMAND(ID_TOOLS_REBUILDTAGS, &CGrammarDesignerDoc::OnToolsRebuildtags)

		ON_COMMAND_RANGE(ID_PARSER_MODE_SLR, ID_PARSER_MODE_LALR, &CGrammarDesignerDoc::OnChangeParserMode)
		ON_UPDATE_COMMAND_UI(ID_PARSER_MODE_LALR, &CGrammarDesignerDoc::OnUpdateParserModeLalr)
		ON_UPDATE_COMMAND_UI(ID_PARSER_MODE_SLR, &CGrammarDesignerDoc::OnUpdateParserModeSlr)
		ON_COMMAND(ID_EDIT_GOTO_DECL, &CGrammarDesignerDoc::OnEditGotoDecl)
		ON_UPDATE_COMMAND_UI(ID_EDIT_GOTO_DECL, &CGrammarDesignerDoc::OnUpdateEditGotoDecl)
		ON_COMMAND(ID_PARSER_BUILD, &CGrammarDesignerDoc::OnParserBuild)
		ON_COMMAND(ID_PARSER_SHOWACTIONTABLE, &CGrammarDesignerDoc::OnParserShowactiontable)
		ON_UPDATE_COMMAND_UI(ID_PARSER_SHOWACTIONTABLE, &CGrammarDesignerDoc::OnUpdateParserShowactiontable)
		ON_COMMAND(ID_PARSER_SHOWCONFLICT, &CGrammarDesignerDoc::OnParserShowconflict)
		ON_UPDATE_COMMAND_UI(ID_PARSER_SHOWCONFLICT, &CGrammarDesignerDoc::OnUpdateParserShowconflict)
		ON_COMMAND(ID_PARSER_SHOWFIRSTFOLLOW, &CGrammarDesignerDoc::OnParserShowfirstfollow)
		ON_UPDATE_COMMAND_UI(ID_PARSER_SHOWFIRSTFOLLOW, &CGrammarDesignerDoc::OnUpdateParserShowfirstfollow)
		ON_COMMAND(ID_PARSER_PARSE, &CGrammarDesignerDoc::OnParserParse)
		ON_UPDATE_COMMAND_UI(ID_PARSER_PARSE, &CGrammarDesignerDoc::OnUpdateParserParse)
		ON_COMMAND(ID_SHOW_LEFTRECURSION, &CGrammarDesignerDoc::OnShowLeftrecursion)
		ON_UPDATE_COMMAND_UI(ID_SHOW_LEFTRECURSION, &CGrammarDesignerDoc::OnUpdateShowLeftrecursion)


		

		ON_COMMAND(ID_TEST_TEST, &CGrammarDesignerDoc::OnTestTest)
		ON_COMMAND(ID_TEST_TEST2, &CGrammarDesignerDoc::OnTestTest2)
		ON_COMMAND(ID_GENERATE_TEMPLATE, &CGrammarDesignerDoc::OnGenerateTemplate)
		ON_COMMAND(ID_STRINGS_STRINGCONVERTER, &CGrammarDesignerDoc::OnStringsStringconverter)
		ON_COMMAND(ID_FLAGS_REPORTSKIP, &CGrammarDesignerDoc::OnFlagsReportskip)
		ON_UPDATE_COMMAND_UI(ID_FLAGS_REPORTSKIP, &CGrammarDesignerDoc::OnUpdateFlagsReportskip)
		ON_COMMAND(ID_FLAGS_SINGLELINE, &CGrammarDesignerDoc::OnFlagsSingleline)
		ON_UPDATE_COMMAND_UI(ID_FLAGS_SINGLELINE, &CGrammarDesignerDoc::OnUpdateFlagsSingleline)
		ON_COMMAND(ID_FLAGS_IGNORECASE, &CGrammarDesignerDoc::OnFlagsIgnorecase)
		ON_UPDATE_COMMAND_UI(ID_FLAGS_IGNORECASE, &CGrammarDesignerDoc::OnUpdateFlagsIgnorecase)
		ON_COMMAND(ID_SHOW_LEFTFACTOR, &CGrammarDesignerDoc::OnShowLeftfactor)
		ON_UPDATE_COMMAND_UI(ID_SHOW_LEFTFACTOR, &CGrammarDesignerDoc::OnUpdateShowLeftfactor)
		ON_COMMAND(ID_EDIT_FINDALLREFERENCES, &CGrammarDesignerDoc::OnEditFindallreferences)
		ON_UPDATE_COMMAND_UI(ID_EDIT_FINDALLREFERENCES, &CGrammarDesignerDoc::OnUpdateEditFindallreferences)
		ON_UPDATE_COMMAND_UI(ID_PARSER_BUILD, &CGrammarDesignerDoc::OnUpdateParserBuild)
END_MESSAGE_MAP()


// CGrammarDesignerDoc construction/destruction
CRichEditCntrItem* CGrammarDesignerDoc::CreateClientItem(REOBJECT* preo ) const
{
		return CRichEditDoc::CreateClientItem(preo);

}
CGrammarDesignerDoc::CGrammarDesignerDoc()
{
	// TODO: add one-time construction code here
		m_encoding		=		CTextFileBase::ASCII;
		m_parser_mode	=		ARSpace::PARSER_LALR;
		m_lexer_mode	=		0;
		m_lexer			=		NULL;
		m_parser		=		NULL;
		m_grammar		=		NULL;
		VERIFY(m_thread.CreateThread());
}

CGrammarDesignerDoc::~CGrammarDesignerDoc()
{
		m_thread.EndThread();
		ClearParser();
}




BOOL CGrammarDesignerDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	reinterpret_cast<CRichEditView*>(m_viewList.GetHead())->SetWindowText(NULL);
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	this->SetTitle(TEXT("Untitled-Grammar"));

	return TRUE;
}




void CGrammarDesignerDoc::Serialize(CArchive& ar)
{
		
			

		if (ar.IsStoring())
		{	// storing code
				

				CRichEditView *view = (CRichEditView*)m_viewList.GetHead();

				CTextFileWrite fw(ar.GetFile(), m_encoding);

				CString buf;
				view->GetWindowText(buf);

				fw.Write(buf);

				
		}
		else
		{	// loading code
				
				CTextFileRead fr(ar.GetFile());

				CString txt;
				
				this->ClearParser();
				if(!fr.Read(txt))
				{
						throw new CFileException(CFileException::genericException);
				}else
				{
						m_encoding = fr.GetEncoding();

						CRichEditView *view = (CRichEditView*)m_viewList.GetHead();

						ASSERT(view != NULL);
						//this->UpdateAllViews(view, NULL, this);
						view->GetRichEditCtrl().SetWindowText(txt);
						
						((CGrammarDesignerView*)view)->ClearLineRecord();

						this->OnToolsRebuildtags();
				}

		}
}





// CGrammarDesignerDoc diagnostics

#ifdef _DEBUG
void CGrammarDesignerDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CGrammarDesignerDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CGrammarDesignerDoc commands



void CGrammarDesignerDoc::OnEndcodingChange(UINT nID)
{
		// TODO: Add your command handler code here

		switch(nID)
		{
		case ID_ENDCODING_ASCII:
				m_encoding = CTextFileBase::ASCII;
				break;
		case ID_ENDCODING_UNICODEBE:
				m_encoding = CTextFileBase::UNI16_BE;
				break;
		case ID_ENDCODING_UNICODELE:
				m_encoding = CTextFileBase::UNI16_LE;
				break;
		case ID_ENDCODING_UTF8:
				m_encoding = CTextFileBase::UTF_8;
				break;
		default:
				ASSERT(false);
		}

}

void CGrammarDesignerDoc::OnEndcodingChangeUI(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here

		switch(pCmdUI->m_nID)
		{
		case ID_ENDCODING_ASCII:
				pCmdUI->SetCheck(m_encoding == CTextFileBase::ASCII);
				break;
		case ID_ENDCODING_UNICODEBE:
				pCmdUI->SetCheck(m_encoding == CTextFileBase::UNI16_BE);
				break;
		case ID_ENDCODING_UNICODELE:
				pCmdUI->SetCheck(m_encoding == CTextFileBase::UNI16_LE);
				break;
		case ID_ENDCODING_UTF8:
				pCmdUI->SetCheck(m_encoding == CTextFileBase::UTF_8);
				break;
		default:
				ASSERT(false);
		}

}



void CGrammarDesignerDoc::OnChangeParserMode(UINT nID)
{
		switch(nID)
		{
		case ID_PARSER_MODE_SLR:
				m_parser_mode = ARSpace::PARSER_SLR;
				break;
		case ID_PARSER_MODE_LALR:
				m_parser_mode = ARSpace::PARSER_LALR;
				break;
		default:
				VERIFY(false);
		}
}



void CGrammarDesignerDoc::OnUpdateParserModeLalr(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(m_parser_mode == ARSpace::PARSER_LALR);
}


void CGrammarDesignerDoc::OnUpdateParserModeSlr(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(m_parser_mode == ARSpace::PARSER_SLR);
}



void CGrammarDesignerDoc::OnFlagsReportskip()
{
		// TODO: Add your command handler code here
/*		if(m_lexer_mode & ARSpace::LEX_REPORT_SKIP)
		{
				m_lexer_mode &= ~ARSpace::LEX_REPORT_SKIP;
		}else
		{
				m_lexer_mode |= ARSpace::LEX_REPORT_SKIP;
		}
*/

}


void CGrammarDesignerDoc::OnUpdateFlagsReportskip(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
/*		if(m_lexer_mode & ARSpace::LEX_REPORT_SKIP)
		{
				pCmdUI->SetCheck(1);
		}
*/
}


void CGrammarDesignerDoc::OnFlagsSingleline()
{
		// TODO: Add your command handler code here

		if(m_lexer_mode & ARSpace::LEX_SINGLE_LINE)
		{
				m_lexer_mode &= ~ARSpace::LEX_SINGLE_LINE;
		}else
		{
				m_lexer_mode |= ARSpace::LEX_SINGLE_LINE;
		}

}

void CGrammarDesignerDoc::OnUpdateFlagsSingleline(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		if(m_lexer_mode & ARSpace::LEX_SINGLE_LINE)
		{
				pCmdUI->SetCheck(1);
		}
}


void CGrammarDesignerDoc::OnFlagsIgnorecase()
{
		// TODO: Add your command handler code here
		if(m_lexer_mode & ARSpace::LEX_IGNORE_CASE)
		{
				m_lexer_mode &= ~ARSpace::LEX_IGNORE_CASE;
		}else
		{
				m_lexer_mode |= ARSpace::LEX_IGNORE_CASE;
		}

}

void CGrammarDesignerDoc::OnUpdateFlagsIgnorecase(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		if(m_lexer_mode & ARSpace::LEX_IGNORE_CASE)
		{
				pCmdUI->SetCheck(1);
		}
}



void CGrammarDesignerDoc::OnEditGotoDecl()
{
		// TODO: Add your command handler code here
		
		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());


		CString sel = view->GetRichEditCtrl().GetSelText();

		sel.TrimLeft();
		sel.TrimRight();

		if(!sel.IsEmpty())
		{
		
				CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();

				CTagView &tag = main_frm->GetTagView();

				const CSrcInfo *info = tag.LookupByName(sel);

				if(info)
				{
						view->OnLocatePos(info->m_line, NULL);
				}else
				{
						CString str;
						str.Format(TEXT("The symbol \"%ls\" is not declared"), sel.GetString());
						view->MessageBox(str);
				}
		}
	
}

void CGrammarDesignerDoc::OnUpdateEditGotoDecl(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here

		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());

		CString sel = view->GetRichEditCtrl().GetSelText();
		sel.TrimLeft();
		sel.TrimRight();
		pCmdUI->Enable(!sel.IsEmpty());
}







void CGrammarDesignerDoc::OnEditFindallreferences()
{
		// TODO: Add your command handler code here
		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());


		CString sel = view->GetRichEditCtrl().GetSelText();

		sel.TrimLeft();
		sel.TrimRight();

		if(!sel.IsEmpty())
		{
		
				CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();

				CFindOutputWnd &find_output = main_frm->GetFindOutputView();
				find_output.Clear();


				/*********************************************************CFG_CollectLexicalSet***************************/

				int find_cnt = 0;
				CString src;
				view->GetWindowText(src);

				
				const ARSpace::cfgLexicalSet_t *lx_set = ARSpace::CFG_CollectLexicalSet(src.GetString());

				if(lx_set != NULL)
				{
						
						for(size_t i = 0; i < lx_set->cnt; ++i)
						{
								const ARSpace::lexToken_t *tok = &lx_set->token_set[i];

								if(tok->count != (size_t)sel.GetLength())
								{
										continue;
								}
								AR_ASSERT(tok->str != NULL);

								if(wcsncmp(tok->str, sel.GetString(), tok->count) == 0)
								{

										int line_idx = view->GetRichEditCtrl().LineIndex((int)tok->line);
										if(line_idx == -1)
										{
												continue;
										}

										int line_len = view->GetRichEditCtrl().LineLength(line_idx);
										if(line_len == -1)
										{
												continue;
										}
										
										CString buf;
										view->GetRichEditCtrl().GetLine((int)tok->line, buf.GetBufferSetLength(line_len + 1), line_len);

										buf.SetAt(line_len, _T('\0')); // null terminate
										buf.ReleaseBuffer(line_len + 1);

										CString msg;
										msg.Format(TEXT("(Line : %d, Col : %d) : %s"), tok->line, tok->col, buf);
										find_output.Append(msg, tok->line, tok->col, tok->count, view);
										find_cnt++;
								}
						}

						ARSpace::CFG_DestroyLexicalSet(lx_set);
						lx_set = NULL;
				}

		

				if(find_cnt <= 1)/*如果只找到一个词法值,则此词法值为当前词法值，启动全局搜索*/
				{

						find_output.Clear();
						const int line_cnt = view->GetRichEditCtrl().GetLineCount();

						for(int i = 0; i < line_cnt; ++i)
						{
								int line_idx = view->GetRichEditCtrl().LineIndex(i);
								int line_len = view->GetRichEditCtrl().LineLength((int)line_idx);

								if(line_len < sel.GetLength())
								{
										continue;
								}

								CString buf;
								view->GetRichEditCtrl().GetLine(i, buf.GetBufferSetLength(line_len + 1), line_len);

								buf.SetAt(line_len, _T('\0')); // null terminate
								buf.ReleaseBuffer(line_len + 1);



								CString tmp = buf;

								tmp.TrimLeft();
								tmp.TrimRight();

								if(tmp.GetLength() == 0)
								{
										continue;

								}

								int start = 0;
								while(buf.GetLength() - start > sel.GetLength())
								{
										start = buf.Find(sel, start);

										if(start == -1)
										{
												break;
										}else
										{
												CString msg;
												msg.Format(TEXT("(Line : %d, Col : %d) : %s"), i, start, buf);

												find_output.Append(msg, i, start, sel.GetLength(), view);
												find_cnt++;
												start += sel.GetLength();
										}
								}


						}
				}

				if(find_cnt == 0)
				{
						find_output.Append(TEXT("Not found!"), 0,0,0, NULL);
				}		

				main_frm->ShowPane(&find_output, TRUE, TRUE, TRUE);
		}

}



void CGrammarDesignerDoc::OnUpdateEditFindallreferences(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here

		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());

		CString sel = view->GetRichEditCtrl().GetSelText();
		sel.TrimLeft();
		sel.TrimRight();
		pCmdUI->Enable(!sel.IsEmpty());

}



static void	AR_STDCALL	__report_io_error_func(int_t level, const wchar_t *msg, void *ctx)
{
		COutputWnd		*output;
		AR_ASSERT(ctx != NULL);
		output = (COutputWnd*)ctx;
		output->Append(msg, COutputList::MSG_MESSAGE, 0, NULL);
}

static void	AR_STDCALL	__report_io_print_func(const wchar_t *msg, void *ctx)
{
		COutputWnd		*output;
		AR_ASSERT(ctx != NULL);
		output = (COutputWnd*)ctx;
		output->Append(msg, COutputList::MSG_MESSAGE, 0, NULL);
} 


struct OutputContext
{
		COutputWnd					*m_output;
		CInputPane					*m_target;
		const ARSpace::parser_t		*m_parser;
		size_t						error_count;

		OutputContext()	:		m_output(NULL)
						,		m_target(NULL)
						,		m_parser(NULL)
						,		error_count(0)
		{

		}
};

static void	AR_STDCALL	__free_node(ARSpace::psrNode_t *node, void *ctx)
{
		CPrintNode		*print_node = (CPrintNode*)node;
		AR_ASSERT(print_node != NULL);
		delete print_node;
}


static arStatus_t	AR_STDCALL	__on_parse_error(const ARSpace::psrToken_t *tok, const size_t expected[], size_t count, void *ctx)
{

		OutputContext	*context;
		AR_ASSERT(ctx != NULL);
		context = (OutputContext*)ctx;

		AR_ASSERT(context->m_parser != NULL);
		
		CString msg;

		CString token;
		if(tok->term_val != 0)
		{
				//AR_ASSERT(tok->str_cnt > 0);
				token.Append(tok->str, (int)tok->str_cnt);
		}else
		{
				token.Append(TEXT("%EOI"));
		}

		if(count > 0)
		{
				msg.Format(TEXT("Invalid Token \"%ls\", expected\t:\t"), token.GetString());

				for(size_t i = 0; i < count; ++i)
				{
						const ARSpace::psrGrammar_t *grammar = ARSpace::Parser_GetGrammar(context->m_parser);
						const ARSpace::psrTermInfo_t	*term_info = ARSpace::Parser_GetTermSymbInfoByValue(grammar, expected[i]);
						msg.AppendFormat(TEXT("\"%ls\" \t"), term_info->term->name);
				}
		}else
		{
				msg.Format(TEXT("Invalid Token \"%ls\""), token.GetString());
		}
		msg.Append(TEXT("."));
		
		context->m_output->Append(msg, COutputList::MSG_ERROR, tok->line, context->m_target);

		context->error_count++;

		return AR_S_YES;

}


static const ARSpace::psrHandler_t		__def_handler = 
{
		__on_parse_error,
		__free_node
};





bool CGrammarDesignerDoc::BuildParser(const ARSpace::cfgConfig_t		*cfg)
{
		
		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		COutputWnd		&output = main_frm->GetOutputView();

		bool has_error = false;
		
		ClearParser();

		
		ARSpace::lex_t			*lexer = ARSpace::Lex_Create();
		
		ARSpace::psrGrammar_t	*grammar = ARSpace::Parser_CreateGrammar(&__def_handler);

		
		
		CWnd	*tar	= main_frm->GetActiveView();


		for(size_t i = 0; i < cfg->name_cnt; ++i)
		{
				const ARSpace::cfgName_t		*name = &cfg->name[i];

				arStatus_t		status = ARSpace::Lex_InsertName(lexer, name->name, name->regex);

				if(status == AR_S_YES)
				{
				}else if(status == AR_S_NO)
				{
						CString msg;
						msg.Format(TEXT("Name Error : \"%ls : %ls\""), name->name, name->regex);
						output.Append(msg, COutputList::MSG_ERROR, name->line, tar);
						has_error = true;
				}else
				{
						
				}
		}

		for(size_t i = 0; i < cfg->tok_cnt; ++i)
		{
				const ARSpace::cfgToken_t		*tok = &cfg->tok[i];

				ARSpace::lexAction_t	action;
				action.is_skip = tok->is_skip;
				action.priority = tok->lex_prec;
				action.value = tok->tokval;

				arStatus_t		status = ARSpace::Lex_InsertRule(lexer, tok->regex, &action);

				if(status == AR_S_YES)
				{

				}else if(status == AR_S_NO)
				{
						CString msg;
						msg.Format(TEXT("Token Error :  \"%ls : %ls\""), tok->name, tok->regex);
						output.Append(msg, COutputList::MSG_ERROR, tok->line, tar);
						has_error = true;
						//continue;
				}else
				{
						abort();
				}

				if(tok->is_skip || tok->tokval == 0)
				{
						continue;
				}

				status = ARSpace::Parser_InsertTerm(grammar, tok->name, tok->tokval, ARSpace::PARSER_ASSOC_NONASSOC, 0, build_leaf);

				if(status == AR_S_YES)
				{
				}else if(status == AR_S_NO)
				{
						CString msg;

						msg.Format(TEXT("Term Error : \"%ls : %ls\""), tok->name, tok->regex);
						output.Append(msg, COutputList::MSG_ERROR, tok->line, tar);
						has_error = true;
				}else
				{
						abort();
				}
		}

		for(size_t i = 0; i < cfg->prec_cnt; ++i)
		{
				const ARSpace::cfgPrec_t		*prec = &cfg->prec[i];
				
				for(size_t k = 0; k < prec->count; ++k)
				{
						ARSpace::psrTermInfo_t *info = ARSpace::Parser_GetTermSymbInfoByName(grammar,prec->prec_tok_set[k]);

						if(info == NULL)
						{
								arStatus_t		status = ARSpace::Parser_InsertTerm(grammar, prec->prec_tok_set[k], prec->prec_tok_val[k], prec->assoc, prec->prec_level, NULL);

								if(status == AR_S_YES)
								{
								}else if(status == AR_S_NO)
								{
										CString msg;
										msg.Format(TEXT("Prec Error : \"%ls\"!"), prec->prec_tok_set[k]);
										output.Append(msg, COutputList::MSG_ERROR, prec->line, tar);
										has_error = true;
								}else
								{
										abort();
								}
						}else
						{
								info->assoc = prec->assoc;
								info->prec = prec->prec_level;
						}
				}

		}


		for(size_t i = 0; i < cfg->rule_cnt; ++i)
		{
				const ARSpace::cfgRule_t		*rule = &cfg->rule[i];
				CString str;
				str.Format(TEXT("%ls : %ls"), rule->lhs, rule->rhs);
				arStatus_t status = ARSpace::Parser_InsertRuleByStr(grammar, str.GetString(), rule->prec_tok,  build_rule, 0);

				if(status == AR_S_YES)
				{
				}else if(status == AR_S_NO)
				{
						CString msg;
						msg.Format(TEXT("Rule Error : \"%ls\"!"), str.GetString());
						output.Append(msg, COutputList::MSG_ERROR, rule->line, tar);
						has_error = true;
				}else
				{
						abort();
				}
		}

		
		
		if(cfg->start.start_rule != NULL)
		{
				bool has_start_rule = true;
				
				for(size_t i = 0; i < cfg->rule_cnt; ++i)
				{
						if(AR_wcscmp(cfg->start.start_rule, cfg->rule[i].lhs) == 0)
						{
								has_start_rule = false;
								break;
						}
				}

				ARSpace::arStatus_t		status = ARSpace::Parser_SetStartRule(grammar, cfg->start.start_rule);

				if(has_start_rule || status == ARSpace::AR_S_NO)
				{
						has_error = true;
						CString msg;
						msg.Format(TEXT("Start Rule Error : \"%ls\"!"), cfg->start.start_rule);
						output.Append(msg, COutputList::MSG_ERROR, cfg->start.line, tar);
				}
		}


		/*********************************************检查并报告语法错误*******************************************************/
		{
		
				ARSpace::arIOCtx_t	io_context = 
				{
						__report_io_error_func,
						__report_io_print_func,
						(void*)&output
				
				};
		
				ARSpace::arStatus_t status = ARSpace::Parser_CheckIsValidGrammar(grammar, &io_context);
				if(status != ARSpace::AR_S_YES)
				{
						has_error = true;
				}
		}
		/******************************************************************************************************/

		if(has_error)
		{
				ARSpace::Lex_Destroy(lexer);
				ARSpace::Parser_DestroyGrammar(grammar);
				return false;
		}else
		{
				DWORD beg, end;

				m_lexer = lexer;
				ARSpace::Lex_GenerateTransTable(m_lexer);
				m_grammar	= grammar;
				beg = GetTickCount();
				
				m_parser = ARSpace::Parser_CreateParser(m_grammar, m_parser_mode);
				
				end = GetTickCount();
				
				CString str;

				str.Format(TEXT("Build Parser Tick count %d"), end - beg);

				output.Append(str, COutputList::MSG_MESSAGE, 0, tar);

				size_t conflict = ARSpace::Parser_CountParserConflict(m_parser);

				if(conflict > 0)
				{
						str.Format(TEXT("The grammar has %d conflicts !"), (uint_32_t)conflict);
						output.Append(str, COutputList::MSG_MESSAGE, 0, tar);
				}
				
				return true;
		}

}


static void AR_STDCALL report_build_func(const ARSpace::cfgReportInfo_t *report, void *context)
{
		COutputWnd *output;
		//COutputList::Param		param;
		CString str;

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		ASSERT(context != NULL);
		
		CWnd *tar = main_frm->GetActiveView();
		output = (COutputWnd*)context;

		switch(report->type)
		{
		case ARSpace::CFG_REPORT_MESSAGE_T:
				output->Append(report->std_msg.message, COutputList::MSG_MESSAGE, 0, tar);
				break;
		case ARSpace::CFG_REPORT_ERROR_T:
				str.Format(TEXT("%ls : %d"), report->error.err_msg, report->error.err_level);
				output->Append(str, COutputList::MSG_ERROR, 0, tar); 
				break;
		case ARSpace::CFG_REPORT_ERROR_LEX_T:
				str.Format(TEXT("Lex error : %ls"), report->lex_error.msg);
				output->Append(str, COutputList::MSG_ERROR, report->lex_error.tok->line, tar);
				break;
		case ARSpace::CFG_REPORT_ERROR_SYNTAX_T:
				str.Format(TEXT("Syntax error : %ls"), report->syntax_error.msg);
				output->Append(str, COutputList::MSG_ERROR, report->syntax_error.tok->line, tar);
				break;
		case	ARSpace::CFG_REPORT_WARNING_SYNTAX_T:
				str.Format(TEXT("Syntax warning : %ls"), report->warning.msg);
				output->Append(str, COutputList::MSG_ERROR, report->warning.line, tar);
				break;
		default:
				AR_ASSERT(false);
		}
}




void	CGrammarDesignerDoc::ClearParser()
{
		
		ASSERT((m_lexer == NULL && m_parser == NULL) || (m_lexer != NULL && m_parser != NULL));
		
		if(m_lexer != NULL && m_parser != NULL)
		{
				ARSpace::Lex_Destroy(m_lexer);
				ARSpace::Parser_DestroyParser(m_parser);
				ARSpace::Parser_DestroyGrammar(m_grammar);
				m_lexer = NULL;
				m_parser = NULL;
				m_grammar = NULL;
		}
}


void CGrammarDesignerDoc::OnUpdateParserBuild(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());
		CString str;
		view->GetRichEditCtrl().GetWindowText(str);

		pCmdUI->Enable(!str.IsEmpty());

}



void CGrammarDesignerDoc::OnParserBuild()
{
		// TODO: Add your command handler code here

		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());
		
		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		COutputWnd		&output = main_frm->GetOutputView();

		main_frm->ClearShow();
		ClearParser();
		
		if(!this->SaveModified())
		{
				return;
		}
		/*
		if(this->IsModified())
		{
				return;
		}
		*/

		CString str;
		view->GetRichEditCtrl().GetWindowText(str);
#if(0)
		if(!str.IsEmpty() && str.GetAt(str.GetLength()) != TEXT('\\'))
		{
				str.Append(TEXT("\r\n"));
		}
#endif
		
		
		
		main_frm->ClearShow();

		ARSpace::cfgReport_t	report = {report_build_func, (void*)&output};
		const ARSpace::cfgConfig_t *cfg = ARSpace::CFG_CollectGrammarConfig(str.GetString(), &report);
		
		if(cfg == NULL || cfg->has_error)
		{
				goto FAILED_POINT;		
		}

		if(!BuildParser(cfg))
		{
				goto FAILED_POINT;	
		}

		if(cfg)ARSpace::CFG_DestroyGrammarConfig(cfg);
		

		output.Append(TEXT("Build Parser successful!"),COutputList::MSG_MESSAGE, 0, NULL);
		main_frm->ShowPane(&output, TRUE, TRUE, TRUE);
		return;

FAILED_POINT:
		this->ClearParser();
		if(cfg)ARSpace::CFG_DestroyGrammarConfig(cfg);
		output.Append(TEXT("Build Parser failed!"), COutputList::MSG_MESSAGE, 0, NULL);
		main_frm->ShowPane(&output, TRUE, TRUE, TRUE);
		return;
}



void CGrammarDesignerDoc::OnParserShowactiontable()
{
		// TODO: Add your command handler code here

		ASSERT(m_parser != NULL);

		const ARSpace::psrActionView_t		*view = ARSpace::Parser_CreateParserActionView(m_parser);

		ASSERT(view != NULL);

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CActionView	&action = main_frm->GetActionView();

		action.DrawActionView(view);
		
		ARSpace::Parser_DestroyParserActionView(view);

		main_frm->ShowPane(&action, TRUE, TRUE, TRUE);

}


void CGrammarDesignerDoc::OnUpdateParserShowactiontable(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here

		pCmdUI->Enable(m_parser != NULL);
}


void CGrammarDesignerDoc::OnParserShowconflict()
{
		// TODO: Add your command handler code here
		ASSERT(m_parser != NULL);

		const ARSpace::psrConflictView_t		*view = ARSpace::Parser_CreateParserConflictView(m_parser);
		
		if(view == NULL)
		{
				return;
		}

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CActionView	&action = main_frm->GetActionView();

		action.DrawConflictView(view);
		
		ARSpace::Parser_DestroyParserConflictView(view);

		main_frm->ShowPane(&action, TRUE, TRUE, TRUE);
}


void CGrammarDesignerDoc::OnUpdateParserShowconflict(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_parser != NULL);
}

void CGrammarDesignerDoc::OnParserShowfirstfollow()
{
		// TODO: Add your command handler code here

		ASSERT(m_parser != NULL);

		const ARSpace::psrStatusView_t		*view = ARSpace::Parser_CreateParserStatusView(m_parser);

		ASSERT(view != NULL);

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CActionView	&action = main_frm->GetActionView();
		
		action.DrawFirstFollowView(view);

		ARSpace::Parser_DestroyParserStatusView(view);
		main_frm->ShowPane(&action, TRUE, TRUE, TRUE);
}


void CGrammarDesignerDoc::OnUpdateParserShowfirstfollow(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_parser != NULL);
}


void CGrammarDesignerDoc::OnShowLeftrecursion()
{
		// TODO: Add your command handler code here

		ASSERT(m_parser != NULL);

		const ARSpace::psrStatusView_t		*view = ARSpace::Parser_CreateParserStatusView(m_parser);
		

		ASSERT(view != NULL);

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CActionView	&action = main_frm->GetActionView();
		
		action.DrawLeftRecursionView(view);

		ARSpace::Parser_DestroyParserStatusView(view);
		main_frm->ShowPane(&action, TRUE, TRUE, TRUE);


}





void CGrammarDesignerDoc::OnShowLeftfactor()
{
		// TODO: Add your command handler code here

		ASSERT(m_parser != NULL);

		const ARSpace::psrStatusView_t		*view = ARSpace::Parser_CreateParserStatusView(m_parser);
		

		ASSERT(view != NULL);

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CActionView	&action = main_frm->GetActionView();
		action.DrawLeftFactorView(view);
		ARSpace::Parser_DestroyParserStatusView(view);
		main_frm->ShowPane(&action, TRUE, TRUE, TRUE);

}

void CGrammarDesignerDoc::OnUpdateShowLeftfactor(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_parser != NULL);
}



void CGrammarDesignerDoc::OnUpdateShowLeftrecursion(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_parser != NULL);
}








void CGrammarDesignerDoc::OnParserParse()
{
		// TODO: Add your command handler code here

		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CInputPane		&input = main_frm->GetInputPane();
		COutputWnd		&output = main_frm->GetOutputView();
		
		OutputContext	output_context;
		output_context.m_output = &output;
		output_context.m_target = &input;
		

		if(this->IsModified())
		{
				OnParserBuild();
		}
		
		main_frm->ClearShow();


		ASSERT((m_lexer == NULL && m_parser == NULL) || (m_lexer != NULL && m_parser != NULL));
		
		if(m_parser == NULL)
		{
				BOOL is_modify = this->IsModified();
				this->SetModifiedFlag(FALSE);
				this->OnParserBuild();

				this->SetModifiedFlag(is_modify);
		}

		if(m_parser == NULL )
		{
				return;
		}

		output_context.m_parser = m_parser;
		ASSERT(m_lexer != NULL && m_parser != NULL);

		ARSpace::psrContext_t	*parser_context = ARSpace::Parser_CreateContext(m_parser, (void*)&output_context);
		


		CString str = input.GetInput();
		
		ARSpace::arStatus_t is_ok = ARSpace::AR_S_YES;


		ARSpace::lexMatch_t *match;
		match = ARSpace::Lex_CreateMatch(this->m_lexer);
		/*
		ARSpace::Lex_InitMatch(&match, this->m_lexer, &io_context);
		*/
		ARSpace::Lex_ResetInput(match, str.GetString());
		
		ARSpace::Lex_MatchClearFlags(match);
		ARSpace::Lex_MatchFlags(match, m_lexer_mode, true);
		
		ARSpace::lexToken_t		token;

		memset(&token, 0, sizeof(token));
		
		DWORD beg = 0, end = 0;

		beg = ::GetTickCount();

		while(is_ok == ARSpace::AR_S_YES)
		{
				
				//if(!m_lexer->GetToken(token))
				is_ok = ARSpace::Lex_Match(match, &token);
				if(is_ok == AR_S_YES)
				{
						ARSpace::psrToken_t		psr_tok;

						PARSER_TOTERMTOK(&token, &psr_tok);
						is_ok = ARSpace::Parser_AddToken(parser_context, &psr_tok);
						
						if(token.value == 0)
						{
								break;
						}

				}else if(is_ok == AR_S_NO)
				{
						size_t len = wcslen(ARSpace::Lex_GetNextInput(match));
						if(len > 10) len = 10;

						CString lex_err;
						CString msg;
						msg.Append(ARSpace::Lex_GetNextInput(match),  (int)len);
					
						lex_err.Format(TEXT("Lexer Error : %ls"), msg.GetString());
						
						size_t line;
						ARSpace::Lex_MatchGetCoordinate(match, NULL, &line, NULL);
						output.Append(lex_err, COutputList::MSG_ERROR, line, &input);

						ARSpace::Lex_Skip(match);
						ARSpace::Lex_ClearError(match);

						output_context.error_count++;
				}else
				{
						abort();
				}

				if(output_context.error_count >= MAX_ERROR_COUNT)
				{
						CString msg;
						msg.Format(TEXT("error count exceeds %d; stopping parse\r\n"), MAX_ERROR_COUNT);
						
						ARSpace::cfgReportInfo_t	info;
						info.type = ARSpace::CFG_REPORT_MESSAGE_T;
						info.std_msg.message = (const TCHAR*)msg;
						report_build_func(&info, (void*)output_context.m_output);
						is_ok = ARSpace::AR_S_NO;
				}
		}

		end = ::GetTickCount();

		{
		CString str;
		str.Format(TEXT("Parse code Tick count %I64d"), (uint_64_t)(end - beg));
		output.Append(str.GetString());
		}

		if(is_ok == ARSpace::AR_S_YES)
		{
				CPrintNode *node = (CPrintNode*)ARSpace::Parser_GetResult(parser_context);
				
				ASSERT(node != NULL);

				output.Append(TEXT("Parse code successful !"));
				
				
				CSyntaxPane &tree = main_frm->GetSyntaxPnae();

				tree.DrawTree(node);
				
				
				main_frm->ShowPane(&tree, TRUE, TRUE, TRUE);
		}else
		{
				output.Append(TEXT("Parse code failed!"));
		}

		main_frm->ShowPane(&output, TRUE, TRUE, TRUE);

		ARSpace::Lex_DestroyMatch(match);
		ARSpace::Parser_DestroyContext(parser_context);
}




bool	CGrammarDesignerDoc::IsParseable()const
{
		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		CInputPane &input = main_frm->GetInputPane();

		int len = input.GetInputLength();

		//return (len > 0 && m_parser != NULL);

		return (len > 0 && main_frm->GetActiveView()->GetWindowTextLength() > 0);
}

void CGrammarDesignerDoc::OnUpdateParserParse(CCmdUI *pCmdUI)
{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(IsParseable());

}



BOOL CGrammarDesignerDoc::SaveModified()
{
		// TODO: Add your specialized code here and/or call the base class

		return CRichEditDoc::SaveModified();
}



static void AR_STDCALL report_tag_func(const ARSpace::cfgReportInfo_t *report, void *context)
{
		switch(report->type)
		{
		case ARSpace::CFG_REPORT_MESSAGE_T:
				//AR_printf(L"%ls\r\n", report->message);
				break;
		case ARSpace::CFG_REPORT_ERROR_T:
				//::AfxMessageBox(report->message);
				//AR_printf(L"%ls : %d\r\n", report->message, report->err_level);
				break;
		case ARSpace::CFG_REPORT_ERROR_LEX_T:
				//::AfxMessageBox(report->message);
				//AR_printf(L"lex error %ls\r\n", report->message);
				break;
		case ARSpace::CFG_REPORT_ERROR_SYNTAX_T:
				//::AfxMessageBox(report->message);
				//AR_printf(L"syntax error %ls\r\n", report->message);
				break;
		case ARSpace::CFG_REPORT_WARNING_SYNTAX_T:
				break;
		default:
				AR_ASSERT(false);
		}
}


class ReBuildTagWorker : public CBackEndThread::CWorkerUnit
{
private:
		CString					m_src;
		CWnd					&m_target;
public:
		ReBuildTagWorker(const CString &source, CWnd &target) : m_src(source), m_target(target)
		{

		}

		virtual ~ReBuildTagWorker()
		{


		}
public:
		virtual void Run()
		{
				ARSpace::cfgReport_t	report = {report_tag_func, NULL};
				const ARSpace::cfgConfig_t *cfg = ARSpace::CFG_CollectGrammarConfig(m_src.GetString(), &report);
				//::AfxGetApp()->PostThreadMessage(ID_THREAD_MESSAGE, ID_BUILD_CFG_COMPLETED, (WPARAM)cfg);
				m_target.PostMessage(ID_BUILD_CFG_COMPLETED, (WPARAM)cfg, NULL);
		}
};


void CGrammarDesignerDoc::OnToolsRebuildtags()
{
		// TODO: Add your command handler code here
		
		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());
		

		ASSERT(view != NULL);
		CString str;

		view->GetWindowText(str);

		if(str != m_src_cache)
		{
				m_src_cache = str;
		}else
		{
				return;
		}

		m_thread.PostWorker(new ReBuildTagWorker(m_src_cache, *this->GetView()));

}

void	CGrammarDesignerDoc::OnTagBuildCompleted(const ARSpace::cfgConfig_t *cfg)
{
		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		
		CTagView &tag = main_frm->GetTagView();

		tag.UpdateTag(cfg);

		if(cfg)ARSpace::CFG_DestroyGrammarConfig(cfg);
		
		
}





void CGrammarDesignerDoc::OnTestTest()
{
		/*
		class TestWorker : public CBackEndThread::CWorkerUnit
		{
		public:
				virtual void Run()
				{
						::AfxMessageBox(TEXT("On TestWorker::Run"));
				}
				
				virtual ~TestWorker()
				{

				}
		};
		// TODO: Add your command handler code here
		m_thread.PostWorker(new TestWorker());
		*/
		//	::AfxMessageBox(TEXT("OnTestTest"));

		//this->GetView()->SendMessage(ID_MSG_TEST, NULL, (LPARAM)(TEXT("abcedefg")));

}


void CGrammarDesignerDoc::OnTestTest2()
{
		// TODO: Add your command handler code here

		
}

void CGrammarDesignerDoc::OnGenerateTemplate()
{
		// TODO: Add your command handler code here
		static TCHAR BASED_CODE szFilter[] = TEXT("C/C++ Files (*.c;*.cpp;*.h;*.hpp)|*.c;*.cpp;*.h;*.hpp|All Files (*.*)|*.*||");
		CFileDialog		file(FALSE, TEXT("c"), NULL, 4|2, szFilter);
		
		
		CGrammarDesignerView *view = (CGrammarDesignerView*)reinterpret_cast<CGrammarDesignerView*>(m_viewList.GetHead());
		
		CMainFrame *main_frm = (CMainFrame*)::AfxGetMainWnd();
		COutputWnd		&output = main_frm->GetOutputView();

		main_frm->ClearShow();
		ClearParser();
		this->SaveModified();
		/*
		if(this->IsModified())
		{
				return;
		}
		*/

		CString str;
		view->GetRichEditCtrl().GetWindowText(str);
		

		main_frm->ClearShow();

		ARSpace::cfgReport_t	report = {report_build_func, (void*)&output};
		const ARSpace::cfgConfig_t *cfg = ARSpace::CFG_CollectGrammarConfig(str.GetString(), &report);
		ARSpace::arString_t *code		= NULL;
		if(cfg == NULL || cfg->has_error)
		{
				main_frm->MessageBox(TEXT("Invalid Grammar"));
				goto END_POINT;

		}
		
		code = ARSpace::AR_CreateString();
		
		if(ARSpace::CFG_ConfigToCode(cfg, code) != AR_S_YES)
		{
				main_frm->MessageBox(TEXT("Failed to generate parser template"));
				goto END_POINT;
		}

		
		
		if(file.DoModal() != IDOK)
		{
				
		}else
		{
				CTextFileWrite fw(file.GetPathName(), m_encoding);
				fw.Write(AR_GetStringCString(code));
				main_frm->MessageBox(TEXT("Generate Template successful"));
		}
		
		
		
		

		

END_POINT:
		
		if(cfg)
		{
				CFG_DestroyGrammarConfig(cfg);
				cfg = NULL;
		}

		if(code)
		{
				AR_DestroyString(code);
		}
}

void CGrammarDesignerDoc::OnStringsStringconverter()
{
		// TODO: Add your command handler code here
		CStringConvDlg dlg;
		
		dlg.DoModal();

		
}
