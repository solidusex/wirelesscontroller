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


class CDocManagerEx :	public CDocManager
{

		DECLARE_DYNAMIC(CDocManagerEx)
public:
		CDocManagerEx(void);
		~CDocManagerEx(void);
public:
		
		virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
};

