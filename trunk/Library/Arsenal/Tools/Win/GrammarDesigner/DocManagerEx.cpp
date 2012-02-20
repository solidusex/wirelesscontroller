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

#include "StdAfx.h"
#include "DocManagerEx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CDocManagerEx, CDocManager)

CDocManagerEx::CDocManagerEx(void)
{
}

CDocManagerEx::~CDocManagerEx(void)
{
}


static void AFXAPI _AfxAppendFilterSuffix(CString& filter, OPENFILENAME& ofn,CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
		ENSURE_VALID(pTemplate);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		CString strFilterExt, strFilterName;
		if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
				!strFilterExt.IsEmpty() &&
				pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
				!strFilterName.IsEmpty())
		{
				if (pstrDefaultExt != NULL)
						pstrDefaultExt->Empty();

				// add to filter
				filter += strFilterName;
				ASSERT(!filter.IsEmpty());  // must have a file type name
				filter += (TCHAR)'\0';  // next string please

				int iStart = 0;
				do
				{
						CString strExtension = strFilterExt.Tokenize( _T( ";" ), iStart );

						if (iStart != -1)
						{
								// a file based document template - add to filter list

								// If you hit the following ASSERT, your document template 
								// string is formatted incorrectly.  The section of your 
								// document template string that specifies the allowable file
								// extensions should be formatted as follows:
								//    .<ext1>;.<ext2>;.<ext3>
								// Extensions may contain wildcards (e.g. '?', '*'), but must
								// begin with a '.' and be separated from one another by a ';'.
								// Example:
								//    .jpg;.jpeg
								ASSERT(strExtension[0] == '.');
								if ((pstrDefaultExt != NULL) && pstrDefaultExt->IsEmpty())
								{
										// set the default extension
										*pstrDefaultExt = strExtension.Mid( 1 );  // skip the '.'
										ofn.lpstrDefExt = const_cast< LPTSTR >((LPCTSTR)(*pstrDefaultExt));
										ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
								}

								filter += (TCHAR)'*';
								filter += strExtension;
								filter += (TCHAR)';';  // Always append a ';'.  The last ';' will get replaced with a '\0' later.
						}
				} while (iStart != -1);

				filter.SetAt( filter.GetLength()-1, '\0' );;  // Replace the last ';' with a '\0'
				ofn.nMaxCustFilter++;
		}
}




BOOL CDocManagerEx::DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
		CFileDialog dlgFile(bOpenFileDialog, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL, 0);

		CString title;
		ENSURE(title.LoadString(nIDSTitle));

		dlgFile.m_ofn.Flags |= lFlags;

		CString strFilter;
		CString strDefault;
		if (pTemplate != NULL)
		{
				ASSERT_VALID(pTemplate);
				_AfxAppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
		}
		else
		{
				// do for all doc template
				POSITION pos = m_templateList.GetHeadPosition();
				BOOL bFirst = TRUE;
				while (pos != NULL)
				{
						pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
						_AfxAppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
								bFirst ? &strDefault : NULL);
						bFirst = FALSE;
				}
		}

		// append the "*.*" all files filter
		CString allFilter;
		VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
		strFilter += allFilter;
		strFilter += (TCHAR)'\0';   // next string please
		strFilter += _T("*.*");
		strFilter += (TCHAR)'\0';   // last string
		dlgFile.m_ofn.nMaxCustFilter++;

		dlgFile.m_ofn.lpstrFilter = strFilter;
		dlgFile.m_ofn.lpstrTitle = title;
		dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

		INT_PTR nResult = dlgFile.DoModal();
		fileName.ReleaseBuffer();
		return nResult == IDOK;
}


