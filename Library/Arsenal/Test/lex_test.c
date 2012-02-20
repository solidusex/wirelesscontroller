#include "test.h"
#include "../Arsenal/Lex/lex.h"
#include "../Arsenal/Lex/rgx.h"



#if defined(__LIB)


AR_NAMESPACE_BEGIN


#if(1)

void rgx_compile_test(rgxNode_t *node)
{
		rgxProg_t		prog;
		arString_t		*out;
		AR_ASSERT(node != NULL);
		
		out = AR_CreateString();
		

		RGX_InitProg(&prog);


		if(RGX_Compile(&prog, node) == AR_S_YES)
		{
				RGX_ProgToString(&prog, out);
				AR_printf(L"%ls\r\n", AR_GetStringCString(out));
		}
		

		AR_DestroyString(out);
		RGX_UnInitProg(&prog);
}



void rgx_test_loop()
{
		rgxNameSet_t	set;
		rgxResult_t		result;
		arString_t		*out;

		RGX_InitNameSet(&set);
		out = AR_CreateString();
		
		while(true)
		{
				wchar_t buf[1024];
				_getws(buf);

				if(AR_wcscmp(buf, L"quit") == 0)break;

				result = RGX_ParseExpr(buf, &set);

				if(result.err.status == AR_S_YES)
				{
						rgxNode_t *cat, *final;
						
						final = RGX_CreateNode(RGX_FINAL_T);
						final->final_val = 21;
						cat = RGX_CreateNode(RGX_CAT_T);
						
						RGX_InsertToNode(cat, result.node);
						RGX_InsertToNode(cat, final);
						result.node = NULL;

						AR_ClearString(out);
						RGX_ToString(cat, out);
						AR_printf(L"%ls\r\n", AR_GetStringCString(out));

						rgx_compile_test(cat);

						RGX_DestroyNode(cat);
				}else
				{
						AR_printf(L"error  code == %d, position == %ls\r\n", result.err.status.m_code, result.err.pos);
				}
		}

		

		AR_DestroyString(out);
		RGX_UnInitNameSet(&set);

}










void lex_test_loop()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 0;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"a{3,5}", &act) == AR_S_YES);

		act.value = 1;
		AR_ASSERT(Lex_InsertRule(lex, L"[ \\r\\n\\t]", &act)  == AR_S_YES);
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act)  == AR_S_YES );

		match = Lex_CreateMatch(lex);

		Lex_ResetInput(match, L"aaa\r\naaa\r\naaaaa\r\naa");
		//Lex_ResetInput(match, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaa\r\n");
		

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d\r\n", s, tok.line, tok.col);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}




void lex_test_loop2()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 0;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"a{3,5}?(?=(a){3,5})", &act) == AR_S_YES);

		act.value = 1;
		AR_ASSERT(Lex_InsertRule(lex, L"[ \\r\\n\\t]", &act) == AR_S_YES);
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act) == AR_S_YES);

		match = Lex_CreateMatch(lex);

		Lex_ResetInput(match, L"aaaaaa");
		

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d\r\n", s, tok.line, tok.col);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}





void lex_chinese_char()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 0;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"[a-z_A-Z\\u{	19968   }-\\u{   40869	}]+", &act) == AR_S_YES);
		
		act.value = 1;
		AR_ASSERT(Lex_InsertRule(lex, L"[ \\r\\n\\t]", &act) == AR_S_YES);
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act) == AR_S_YES);

		match = Lex_CreateMatch(lex);

		//Lex_ResetInput(match, L"aaa\r\naaa\r\naaaaa\r\n");
		Lex_ResetInput(match, L"中国字abc真麻烦\r\n");
		

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d\r\n", s, tok.line, tok.col);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}




void lex_line_test()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 0;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"\\B[ \\t]*;[^\\r\\n]*\\E", &act) == AR_S_YES);

		act.value = 201;
		AR_ASSERT(Lex_InsertRule(lex, L"[\\r\\n]", &act)== AR_S_YES);
		

		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act)== AR_S_YES);

		match = Lex_CreateMatch(lex);
		
		//Lex_ResetInput(match, L";中国\r;字abc\n;真麻烦\r\n;太烦了\r\n");
		Lex_ResetInput(match, L";中国\n\r;字abc\r\n");
		

		
		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d action == %Iu\r\n", s, tok.line, tok.col, tok.value);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);
}


void lex_line_test2()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 0;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"(\\r\\n)|\\r|\\n", &act) == AR_S_YES);
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act)  == AR_S_YES );

		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"\r\n\n\r");
		

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d action == %Iu\r\n", s, tok.line, tok.col, tok.value);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}

}




void lex_line_test3()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 1;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"\\r\\n", &act) == AR_S_YES);


		act.priority = 1;
		act.value = 201;
		AR_ASSERT(Lex_InsertRule(lex, L"\\n\\r", &act) == AR_S_YES);


		act.priority = 0;
		act.value = 301;
		AR_ASSERT(Lex_InsertRule(lex, L"\\r", &act) == AR_S_YES);


		act.priority = 0;
		act.value = 302;
		AR_ASSERT(Lex_InsertRule(lex, L"\\n", &act) == AR_S_YES);
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act) == AR_S_YES);

		match = Lex_CreateMatch(lex);
		
		//Lex_ResetInput(match, L"\n\r\r\n");
		Lex_ResetInput(match, L"\n");

		
		printf("\r\n");

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d action == %Iu\r\n", s, tok.line, tok.col, tok.value);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}







void lex_line_test4()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 1;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"[\\r\\n]{1,2}", &act) == AR_S_YES);


		
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act) == AR_S_YES);

		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"\n\r\r\r\n\n");
		

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d action == %Iu\r\n", s, tok.line, tok.col, tok.value);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}




void lex_quote_test7()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 1;
		act.value = 200;

		

		AR_ASSERT(Lex_InsertRule(lex, L"\"abc\"", &act) == AR_S_YES);

		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act) == AR_S_YES);
		
		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"abcabcabcabc");
		

		lexToken_t tok;
		arStatus_t lex_status;
		
		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d action == %Iu\r\n", s, tok.line, tok.col, tok.value);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);
}


void lex_test_skip_line_test()
{
		//const wchar_t *s = L"a\r\nb\n\rc\rd\ne\r\rf";

		const wchar_t *s = L"a\n\rb";

		lexMatch_t match;

		AR_memset(&match, 0, sizeof(match));


		match.next = s;
		match.input = s;

		while(*match.next != L'\0')
		{
				printf("line : %I64d col : %I64d\r\n", match.line, match.col);
				Lex_SkipN(&match, 1);
		}

}





void lex_line_num_test()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 1;
		act.value = 200;


		AR_ASSERT(Lex_InsertName(lex, L"keyword_lhd", L"[A-Z_a-z0-9]") == AR_S_YES);
		AR_ASSERT(Lex_InsertName(lex, L"hex_digit", L"[0-9a-fA-F]") == AR_S_YES);
		AR_ASSERT(Lex_InsertName(lex, L"hex_literal", L"0(x|X){hex_digit}+") == AR_S_YES);
		AR_ASSERT(Lex_InsertName(lex, L"oct_literal", L"0[0-7]+") == AR_S_YES);
		AR_ASSERT(Lex_InsertName(lex, L"dec_literal", L"(0|[1-9][0-9]*)") == AR_S_YES);


		AR_ASSERT(Lex_InsertName(lex, L"hex_constant", L"{hex_literal}(?!{keyword_lhd})") == AR_S_YES);
		AR_ASSERT(Lex_InsertName(lex, L"oct_constant", L"{oct_literal}(?!{keyword_lhd})") == AR_S_YES);
		AR_ASSERT(Lex_InsertName(lex, L"dec_constant", L"{dec_literal}(?!{keyword_lhd})") == AR_S_YES);



		act.priority = 1;
		act.value = 261;
		
		AR_ASSERT( Lex_InsertRule(lex, L"{hex_constant}|{oct_constant}|{dec_constant}", &act) == AR_S_YES  );

		act.priority = 0;
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act) == AR_S_YES);


		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"333");

		
		printf("\r\n");

		lexToken_t tok;
		arStatus_t lex_status;
		
		

		while(true)
		{
				lex_status = Lex_Match(match, &tok);

				if(lex_status == AR_S_YES || lex_status == AR_S_YES)
				{
						if(tok.value == 0)
						{
								break;
						}
						wchar_t *s = AR_wcsndup(tok.str, tok.count);
						AR_printf(L"%ls : row == %d : col == %d action == %Iu\r\n", s, tok.line, tok.col, tok.value);
						AR_DEL(s);
				}else
				{
						break;
				}
		}

		if(lex_status == AR_S_YES || lex_status == AR_S_YES)
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}else
		{
				AR_printf(L"error code = %d, %ls\r\n", AR_GET_STATUS(lex_status), L"failed\r\n");
				
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}
#endif





#if(0)

void lex_line_test7()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 0;
		act.value = 200;
		
		AR_ASSERT(Lex_InsertRule(lex, L".*(\\r\\n|\\n\\r|\\r|\\n)?", &act));
		
		act.priority = 1;
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act));
		
		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"\r\n\r\n\r\n%token\tline\t:\t\".*(\\r\\n|\\n\\r|\\r|\\n)?\"\r\n\t\t;\r\n\r\n\r\n%start\tprogram;\r\n\r\n\r\nprogram\t:\tline_list\r\n\t\t|\t.\r\n\t\t;\r\n\r\n\r\nline_list\t:\tline_list\tline \r\n\t\t|\tline\r\n\t\t;\r\n\r\n\r\n");
		

		lexToken_t tok;
		bool_t is_ok = false;
		
		

		while(Lex_Match(match, &tok))
		{
				wchar_t *s = AR_wcsndup(tok.str, tok.count);
				AR_printf(L"%ls : row == %d : col == %d : count == %d\r\n", s, tok.line, tok.col, tok.count);
				AR_DEL(s);
				
				if(tok.value == 0)
				{
						is_ok = true;
						break;
				}
		}

		if(!is_ok)
		{
				AR_printf(L"%ls\r\n", L"failed\r\n");
		}else
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);
}




void lex_line_test5()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 1;
		act.value = 200;
		AR_ASSERT(Lex_InsertRule(lex, L"[\\r\\n]", &act));

		
		
		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act));

		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"\r\n\f\f\r\n");
		

		lexToken_t tok;
		bool_t is_ok = false;
		
		printf("\r\n");

		while(Lex_Match(match, &tok))
		{
				wchar_t *s = AR_wcsndup(tok.str, tok.count);
				AR_printf(L"%ls : row == %d : col == %d : count == %d\r\n", s, tok.line, tok.col, tok.count);
				AR_DEL(s);
				
				if(tok.value == 0)
				{
						is_ok = true;
						break;
				}
		}

		if(!is_ok)
		{
				AR_printf(L"%ls\r\n", L"failed\r\n");
		}else
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}




void lex_line_test6()
{
		lexMatch_t		*match;
		lex_t			*lex;

		lex = Lex_Create();
		
		lexAction_t act;
		act.is_skip = false;
		act.priority = 1;
		act.value = 200;

		

		AR_ASSERT(Lex_InsertRule(lex, L"\"\\\"\\b\\f\\n\\r\\t\\v\\a\\\\\\\"\\'\\x67\\012\\\"\"", &act));

		act.value = 0;
		AR_ASSERT(Lex_InsertRule(lex, L"$", &act));
		
		match = Lex_CreateMatch(lex);
		
		Lex_ResetInput(match, L"\\\\\\\\");
		

		lexToken_t tok;
		bool_t is_ok = false;
		
		printf("\r\n");

		while(Lex_Match(match, &tok))
		{
				wchar_t *s = AR_wcsndup(tok.str, tok.count);
				AR_printf(L"%ls : row == %d : col == %d : count == %d\r\n", s, tok.line, tok.col, tok.count);
				AR_DEL(s);
				
				if(tok.value == 0)
				{
						is_ok = true;
						break;
				}
		}

		if(!is_ok)
		{
				AR_printf(L"%ls\r\n", L"failed\r\n");
		}else
		{
				AR_printf(L"%ls\r\n", L"success\r\n");
		}


		Lex_DestroyMatch(match);
		Lex_Destroy(lex);

}



#endif

void lex_test()
{
		//rgx_test_loop();
		//lex_test_loop();
		//lex_test_loop2();
		//lex_chinese_char();
		//lex_line_test();
		//lex_line_test2();
		//lex_line_test3();
		//lex_line_test4();

		//lex_line_test5();
		//lex_line_test6();
		//lex_line_test7();
		

		

		//lex_quote_test7();

		//lex_test_skip_line_test();

//		lex_line_num_test();
}

AR_NAMESPACE_END



#endif

