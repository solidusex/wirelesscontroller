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


class CPrintNode
{
private:
		
public:
		CString					m_name;
		size_t					m_line;
		size_t					m_col;
		size_t					m_cnt;
		bool					m_is_term;
		CList<CPrintNode*>		m_nodes;
public:
		CPrintNode(const CString &name, size_t line = 0, size_t col = 0, size_t cnt = 0, bool is_term = false);
		virtual ~CPrintNode(void);
public:
		void	Insert(CPrintNode *node);
		void Clear();
};



ARSpace::psrRetVal_t	 AR_STDCALL build_leaf(const ARSpace::psrToken_t *tok, void *ctx);
ARSpace::psrRetVal_t	 AR_STDCALL build_rule(ARSpace::psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);





 