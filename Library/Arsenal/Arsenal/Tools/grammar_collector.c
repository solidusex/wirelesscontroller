
/*
 * The Arsenal Library
 * Copyright (c) 2009 by Solidus
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express
 * or implied warranty.
 *
 */

#include "grammar_config.h"



AR_NAMESPACE_BEGIN



typedef enum
{
		CFG_STR_NAME,
		CFG_STR_TOKEN,
		CFG_STR_TOKEN_VALUE,
		CFG_STR_PREC
}cfgStrType_t;

typedef struct __config_parser_data_tag
{
		bool_t					has_error;
		cfgReport_t				*report;
		arStringTable_t			*name;
		arStringTable_t			*token;
		arStringTable_t			*token_val;
		arStringTable_t			*prec;

		arStringTable_t			*normal_str_pool;
}cfgParserData_t;




static void	ParserData_UnInit(cfgParserData_t	*psr_data)
{
		AR_ASSERT(psr_data != NULL);

		if(psr_data->name != NULL)
		{
				AR_DestroyStrTable(psr_data->name);
				psr_data->name = NULL;
		}

		if(psr_data->token != NULL)
		{
				AR_DestroyStrTable(psr_data->token);
				psr_data->token = NULL;
		}

		if(psr_data->token_val != NULL)
		{
				AR_DestroyStrTable(psr_data->token_val);
				psr_data->token_val = NULL;
		}

		if(psr_data->prec != NULL)
		{
				AR_DestroyStrTable(psr_data->prec);
				psr_data->prec = NULL;
		}

		if(psr_data->normal_str_pool != NULL)
		{
				AR_DestroyStrTable(psr_data->normal_str_pool);
				psr_data->normal_str_pool = NULL;
		}

		psr_data->has_error = false;
		AR_memset(psr_data, 0, sizeof(*psr_data));
}



static	arStatus_t	ParserData_Init(cfgParserData_t		*psr_data, cfgReport_t	*report)
{
		AR_ASSERT(psr_data != NULL && report != NULL);

		AR_memset(psr_data, 0, sizeof(*psr_data));

		psr_data->has_error = false;
		psr_data->report = report;
		psr_data->name = AR_CreateStrTable(0);
		psr_data->token = AR_CreateStrTable(0);
		psr_data->token_val = AR_CreateStrTable(0);
		psr_data->prec  = AR_CreateStrTable(0);
		psr_data->normal_str_pool = AR_CreateStrTable(0);

		if(psr_data->name == NULL || psr_data->token == NULL || psr_data->token_val == NULL || psr_data->prec == NULL || psr_data->normal_str_pool == NULL)
		{
				ParserData_UnInit(psr_data);
				return AR_E_NOMEM;
		}else
		{
				return AR_S_YES;
		}

}




static AR_INLINE		arStringTable_t*		__get_parser_data_tbl(cfgParserData_t	*psr_data, cfgStrType_t t)
{
		switch(t)
		{
		case CFG_STR_NAME:
				return psr_data->name;
		case CFG_STR_TOKEN:
				return psr_data->token;
		case CFG_STR_TOKEN_VALUE:
				return psr_data->token_val;
		case CFG_STR_PREC:
				return psr_data->prec;
		default:
				AR_ASSERT(false);
				return NULL;

		}
}


static arStatus_t	ParserData_InsertString(cfgParserData_t	*psr_data, const wchar_t *str, cfgStrType_t t)
{
		arStringTable_t	*tbl;
		AR_ASSERT(psr_data != NULL && str != NULL);
		tbl = __get_parser_data_tbl(psr_data, t);
		
		return AR_GetString(tbl, str) != NULL ? AR_S_YES : AR_E_NOMEM;
}


static arStatus_t	ParserData_HasString(cfgParserData_t	*psr_data, const wchar_t *str, cfgStrType_t t)
{
		arStringTable_t	*tbl;
		AR_ASSERT(psr_data != NULL && str != NULL);
		tbl = __get_parser_data_tbl(psr_data, t);
		return AR_HasString(tbl, str);
}


static arStatus_t	ParserData_CheckAndInsertName(cfgParserData_t *psr_data, const wchar_t *name, size_t line, cfgStrType_t t)
{

		AR_ASSERT(psr_data != NULL && name != NULL);

		if(ParserData_HasString(psr_data, name, t) == AR_S_YES)
		{
				cfgReportInfo_t	msg;
				wchar_t	buf[1024];

				msg.warning.line = line;
				switch(t)
				{
				case CFG_STR_NAME:
						AR_swprintf(buf, 1024, L"Duplicate name definition %ls\r\n", name);
						break;
				case CFG_STR_TOKEN:
						AR_swprintf(buf, 1024, L"Duplicate token definition %ls\r\n", name);
						break;
				case CFG_STR_TOKEN_VALUE:
						AR_swprintf(buf, 1024, L"Duplicate token value definition %ls\r\n", name);
						break;
				case CFG_STR_PREC:
						AR_swprintf(buf, 1024, L"Duplicate prec definition %ls\r\n", name);
						break;
				default:
						AR_ASSERT(false);
				}
				
				msg.warning.msg = buf;
				msg.type = CFG_REPORT_WARNING_SYNTAX_T;
				psr_data->report->report_func(&msg, psr_data->report->report_ctx);
				return AR_S_YES;
		}else
		{
				return ParserData_InsertString(psr_data, name, t);
		}

}


static const wchar_t* ParserData_AllocString(cfgParserData_t *psr_data, const wchar_t *str)
{
		AR_ASSERT(psr_data != NULL && str != NULL);
		return AR_GetString(psr_data->normal_str_pool, str);
}


static const wchar_t* ParserData_AllocStringN(cfgParserData_t *psr_data, const wchar_t *str, size_t n)
{

		AR_ASSERT(psr_data != NULL && str != NULL);
		return AR_GetStringN(psr_data->normal_str_pool, str, n);
}



/*********************************************************************************************************************************************/




typedef enum
{
		CFG_EMPTY_T,
		CFG_LEXEME_T,
		CFG_NAME_T,
		CFG_TOKEN_T,
		CFG_PREC_T,
		CFG_PREDEF_T,
		CFG_START_T,
		CFG_RULE_T,
		CFG_NODE_LIST_T,
		CFG_CONFIG_T,
		CFG_ERROR_T
}cfgNodeType_t;


struct __cfg_node_tag
{
		union{
				cfgConfig_t		config;
				cfgLexeme_t		lexeme;
				cfgName_t		name;
				cfgNodeList_t	lst;
				cfgPrec_t		prec;
				cfgToken_t		token;
				cfgRule_t		rule;
				cfgStart_t		start;
				cfgPreDef_t		predef;
		};
		
		cfgNodeType_t	type;
		cfgNode_t		*next;
};


static const wchar_t *__cfg_lex_name[] =
{
		L"	delim		= 	[\\x{000B}\\x{0020}\\x{00A0}\\x{2028}\\x{2029} \\f\\v\\t\\r\\n]+",
		L"	letter		= 	[A-Z_a-z]",
		L"	digit		=	[0-9]",
		L"	number		=	0|[1-9]{digit}*",
		L"	name		=	{letter}({letter}|{digit})*",
		L"	lexeme		=	{name}|(\\\"([^\\\"\\n\\r])+\\\")|('([^'\\n\\r])+')",
		L"	comment		= 	/\\*([^\\*]|\\*+[^\\*/])*\\*+/",
		L"	comment_line	= //[^\\n\\r]*(\\n|$|\\r)",
		L"  skip_lexem		= {delim}",
		L"	comment_lexem	= {comment}|{comment_line}",
		L"  key_lookahead   = {skip_lexem}+|\"{\""
};




typedef struct  __cfg_lex_pattern_tag
{
		size_t			val;
		const wchar_t	*regex;
		bool_t			is_skip;
		size_t			prec;
}cfgLexPattern_t;


static const cfgLexPattern_t	__cfg_pattern[] =
{
		{CFG_LEXVAL_EOI,	L"$", false,2},
		{CFG_LEXVAL_DELIM, L"{skip_lexem}+", true, 1},
		
		{CFG_LEXVAL_COMMENT, L"{comment_lexem}", false, 1},

		{CFG_LEXVAL_ASSOC,	L"\"%\"(\"left\"|\"right\"|\"nonassoc\")(?={key_lookahead})", false,1},

		{CFG_LEXVAL_CODE,	L"\"%code\"(?={key_lookahead})", false,0},
		{CFG_LEXVAL_VALUE,	L"\"%value\"(?={key_lookahead})", false,0},
		
		{CFG_LEXVAL_SKIP,	L"\"%skip\"(?={key_lookahead})", false,0},
		{CFG_LEXVAL_START,	L"\"%start\"(?={key_lookahead})", false,0},
		{CFG_LEXVAL_NAME,	L"\"%name\"(?={key_lookahead})", false,0},
		{CFG_LEXVAL_TOKEN,	L"\"%token\"(?={key_lookahead})", false,0},
		{CFG_LEXVAL_PREC,	L"\"%prec\"(?={key_lookahead})", false,0},

		{CFG_LEXVAL_ACTION, L"\"%action\"(?={skip_lexem}+)", false, 0},
		{CFG_LEXVAL_ACTION_INS, L"\\{:[^\\u0]*?:\\}", false, 0},

		{CFG_LEXVAL_LEXEME,	L"{lexeme}", false,0},
		{CFG_LEXVAL_NUMBER,	L"{number}", false,0},

		{CFG_LEXVAL_DOT,		L"\".\"",	false,1},
		{CFG_LEXVAL_COMMA,		L"\",\"",	false,1},

		{CFG_LEXVAL_COLON,		L"\":\"",	false,1},
		{CFG_LEXVAL_SEMI,		L"\";\"",	false,1},

		{CFG_LEXVAL_OR,		L"\"|\"",	false,1}
};













typedef struct	__cfg_term_info_tag
{
		cfgLexValue_t	val;
		const wchar_t	*name;
}cfgTermInfo_t;


static const cfgTermInfo_t	__cfg_term[] =
{
		{CFG_LEXVAL_CODE, L"%code"},
		{CFG_LEXVAL_VALUE, L"%value"},
		{CFG_LEXVAL_SKIP, L"%skip"},
		{CFG_LEXVAL_START, L"%start"},
		{CFG_LEXVAL_NAME, L"%name"},
		{CFG_LEXVAL_TOKEN, L"%token"},
		{CFG_LEXVAL_PREC, L"%prec"},
		{CFG_LEXVAL_ACTION, L"%action"},
		{CFG_LEXVAL_ACTION_INS, L"action_ins"},
		{CFG_LEXVAL_ASSOC, L"assoc"},
		{CFG_LEXVAL_LEXEME, L"lexeme"},
		{CFG_LEXVAL_NUMBER, L"number"},

		{CFG_LEXVAL_DOT, L"."},
		{CFG_LEXVAL_COMMA, L","},
		{CFG_LEXVAL_COLON, L":"},
		{CFG_LEXVAL_SEMI, L";"},
		{CFG_LEXVAL_OR,   L"|"},
		{CFG_LEXVAL_FAKE_EOI, L"#"}
};



static void CFG_InitPrec(cfgPrec_t *prec)
{
		AR_ASSERT(prec != NULL);
		AR_memset(prec, 0, sizeof(*prec));
}


static void CFG_UnInitPrec(cfgPrec_t *prec)
{
		
		AR_ASSERT(prec != NULL);

		if(prec->prec_tok_set)
		{
				AR_DEL(prec->prec_tok_set);
		}

		if(prec->prec_tok_val)
		{
				AR_DEL(prec->prec_tok_val);
		}

		AR_memset(prec, 0, sizeof(*prec));
}

static arStatus_t CFG_InsertTokenToPrec(cfgPrec_t *prec, const wchar_t *prec_tok, size_t prec_tok_val, cfgParserData_t *psr_data)
{
		AR_ASSERT(prec != NULL && prec_tok != NULL &&  psr_data != NULL);

		if(prec->count == prec->cap)
		{
				size_t new_cap;
				const wchar_t	**new_tok_set;
				size_t	*new_tok_val;
				new_cap = (prec->cap + 4)*2;
				
				new_tok_set = AR_NEWARR(const wchar_t*, new_cap);
				new_tok_val = AR_NEWARR(size_t, new_cap);

				if(new_tok_set == NULL || new_tok_val == NULL)
				{
						if(new_tok_set)
						{
								AR_DEL(new_tok_set);
								new_tok_set = NULL;
						}

						if(new_tok_val)
						{
								AR_DEL(new_tok_val);
								new_tok_val = NULL;
						}

						return AR_E_NOMEM;
				}

				if(prec->count > 0)
				{
						AR_memcpy((wchar_t**)new_tok_set, prec->prec_tok_set, prec->count * sizeof(wchar_t*));
						AR_memcpy(new_tok_val, prec->prec_tok_val, prec->count * sizeof(size_t));
				}

				if(prec->prec_tok_set)
				{
						AR_DEL(prec->prec_tok_set);
						prec->prec_tok_set = NULL;
				}

				if(prec->prec_tok_val)
				{
						AR_DEL(prec->prec_tok_val);
						prec->prec_tok_val = NULL;
				}


				prec->cap = new_cap;
				prec->prec_tok_set = new_tok_set;
				prec->prec_tok_val = new_tok_val;
		}

		prec->prec_tok_set[prec->count] = ParserData_AllocString(psr_data, prec_tok);
		prec->prec_tok_val[prec->count] = prec_tok_val;

		if(prec->prec_tok_set[prec->count] == NULL)
		{
				return AR_E_NOMEM;
		}else
		{
				prec->count++;
				return AR_S_YES;
		}
}




static arStatus_t CFG_CopyPrec(cfgPrec_t *dest, const cfgPrec_t *sour, cfgParserData_t *psr_data)
{
		size_t i;
		AR_ASSERT(dest != NULL && sour != NULL && psr_data != NULL);
		CFG_UnInitPrec(dest);

		dest->assoc = sour->assoc;
		dest->prec_level = sour->prec_level;
		dest->line = sour->line;
		for(i = 0; i < sour->count; ++i)
		{
				arStatus_t tmp_status;
				tmp_status = CFG_InsertTokenToPrec(dest, sour->prec_tok_set[i], sour->prec_tok_val[i], psr_data);

				if(tmp_status != AR_S_YES)
				{
						return tmp_status;
				}
		}

		return AR_S_YES;
}


/*******************************************************************/
static void CFG_InitNodeList(cfgNodeList_t *lst)
{
		AR_ASSERT(lst != NULL);
		AR_memset(lst, 0, sizeof(*lst));
}


static void CFG_UnInitNodeList(cfgNodeList_t *lst)
{
		if(lst && lst->lst)
		{
				AR_DEL(lst->lst);
				AR_memset(lst, 0, sizeof(*lst));
		}
}


static arStatus_t CFG_InsertToNodeList(cfgNodeList_t *lst, cfgNode_t *node)
{
		AR_ASSERT(lst != NULL && node != NULL);


		if(lst->count == lst->cap)
		{
				size_t new_cap;
				cfgNode_t **new_lst;

				new_cap = (lst->cap + 4)*2;
				new_lst = AR_NEWARR(cfgNode_t*, new_cap);

				if(new_lst == NULL)
				{
						return AR_E_NOMEM;
				}

				if(lst->count > 0)
				{
						AR_memcpy(new_lst, lst->lst, lst->count * sizeof(cfgNode_t*));
				}

				if(lst->lst)
				{
						AR_DEL(lst->lst);
						lst->lst = NULL;
				}

				lst->cap = new_cap;
				lst->lst = new_lst;
				
				/*lst->lst = (cfgNode_t**)AR_realloc(lst->lst, sizeof(cfgNode_t*) * lst->cap);*/
		}
		lst->lst[lst->count++] = node;
		return AR_S_YES;
}




static void CFG_UnInitConfig(cfgConfig_t *cfg)
{
		size_t i;
		AR_ASSERT(cfg != NULL);

		if(cfg->name)
		{
				AR_DEL(cfg->name);
				cfg->name = NULL;
		}


		if(cfg->tok)
		{
				AR_DEL(cfg->tok);
		}


		for(i = 0; i < cfg->prec_cnt; ++i)
		{
				CFG_UnInitPrec(&cfg->prec[i]);
		}

		if(cfg->prec)
		{
				AR_DEL(cfg->prec);
				cfg->prec = NULL;
		}

		

		if(cfg->rule)
		{
				AR_DEL(cfg->rule);
		}


		if(cfg->pre_def)
		{
				AR_DEL(cfg->pre_def);
		}

}




static arStatus_t CFG_InitConfig(cfgConfig_t *cfg, cfgNodeList_t *name, cfgNodeList_t *token, cfgNodeList_t *prec, cfgNodeList_t *rule, cfgStart_t *start_rule, cfgNodeList_t *pre_def, cfgParserData_t *psr_data)
{
		size_t i;
		arStatus_t		status;
		size_t tmp_tok_val = PARSER_MIN_TOKENVAL + 1;

		AR_ASSERT(cfg != NULL);
		AR_ASSERT(psr_data != NULL);
		
		status = AR_S_YES;
		AR_memset(cfg, 0, sizeof(*cfg));

		if(name)
		{
				/*cfg->name_cnt = name->count;*/
				if(name->count > 0)
				{
						cfg->name = AR_NEWARR0(cfgName_t, name->count);

						if(cfg->name == NULL)
						{
								status = AR_E_NOMEM;
								goto INVALID_POINT;
						}

				}else
				{
						cfg->name = NULL;
				}
				
				for(i = 0; i < name->count; ++i)
				{
						if(name->lst[i]->type == CFG_ERROR_T)
						{
								cfg->has_error = true;
						}else
						{
								cfg->name[cfg->name_cnt].line = name->lst[i]->name.line;
								cfg->name[cfg->name_cnt].name = ParserData_AllocString(psr_data,name->lst[i]->name.name);
								cfg->name[cfg->name_cnt].regex = ParserData_AllocString(psr_data,name->lst[i]->name.regex);

								if(cfg->name[cfg->name_cnt].name == NULL || cfg->name[cfg->name_cnt].regex == NULL)
								{
										status = AR_E_NOMEM;
										goto INVALID_POINT;
								}

								cfg->name_cnt++;
						}
				}
		}


		if(token)
		{
				size_t k;


				/*cfg->tok_cnt = token->count + 1;*/

				/*cfg->tok = cfg->tok_cnt > 0 ? AR_NEWARR0(cfgToken_t, cfg->tok_cnt + 1) : NULL;*/

				cfg->tok = AR_NEWARR0(cfgToken_t, token->count + 1);

				if(cfg->tok == NULL)
				{
						status = AR_E_NOMEM;
						goto INVALID_POINT;
				}


				for(i = 0; i < token->count; ++i)
				{
						if(token->lst[i]->type == CFG_ERROR_T)
						{
								cfg->has_error = true;
						}else
						{
								cfg->tok[cfg->tok_cnt] = token->lst[i]->token;

								if(token->lst[i]->token.name != NULL)/*不是每个token都有名字*/
								{
										cfg->tok[cfg->tok_cnt].name = ParserData_AllocString(psr_data,token->lst[i]->token.name);

										if(cfg->tok[cfg->tok_cnt].name == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}
								}else
								{
										cfg->tok[cfg->tok_cnt].name = NULL;
								}

								cfg->tok[cfg->tok_cnt].regex = ParserData_AllocString(psr_data,token->lst[i]->token.regex);

								if(cfg->tok[cfg->tok_cnt].regex == NULL)
								{
										status = AR_E_NOMEM;
										goto INVALID_POINT;
								}

								cfg->tok[cfg->tok_cnt].action_line = token->lst[i]->token.action_line;

								if(token->lst[i]->token.action_name)
								{
										cfg->tok[cfg->tok_cnt].action_name = ParserData_AllocString(psr_data,token->lst[i]->token.action_name);

										if(cfg->tok[cfg->tok_cnt].action_name == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}

								}else
								{
										cfg->tok[cfg->tok_cnt].action_name = NULL;
								}

								if(token->lst[i]->token.action_ins != NULL)
								{
										cfg->tok[cfg->tok_cnt].action_ins = ParserData_AllocString(psr_data, token->lst[i]->token.action_ins);

										if(cfg->tok[cfg->tok_cnt].action_ins == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}
								}else
								{
										cfg->tok[cfg->tok_cnt].action_ins = NULL;
								}
								

								if(token->lst[i]->token.code_name != NULL)
								{
										cfg->tok[cfg->tok_cnt].code_name = ParserData_AllocString(psr_data, token->lst[i]->token.code_name);
										cfg->tok[cfg->tok_cnt].is_assigned_code_name = true;

										if(cfg->tok[cfg->tok_cnt].code_name == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}
								}else
								{
										cfg->tok[cfg->tok_cnt].code_name = NULL;
								}

								cfg->tok_cnt++;
						}
				}

				for(i = 0; i < cfg->tok_cnt ; ++i)
				{
						if(cfg->tok[i].tokval == 0)
						{
RE_CHECK_POINT:
								for(k = 0; k < cfg->tok_cnt; ++k)
								{
										if(cfg->tok[k].tokval == tmp_tok_val)
										{
												tmp_tok_val++;
												k = 0;
												goto RE_CHECK_POINT;
										}
								}
								cfg->tok[i].tokval = tmp_tok_val++;
						}
				}


				/*CFG_LEXVAL_EOI*/
				cfg->tok[cfg->tok_cnt ].is_skip = false;
				cfg->tok[cfg->tok_cnt ].lex_prec = 2;
				cfg->tok[cfg->tok_cnt ].line = 0;
				cfg->tok[cfg->tok_cnt ].tokval = 0;
				cfg->tok[cfg->tok_cnt ].name = ParserData_AllocString(psr_data, L"CFG_LEXVAL_EOI");
				cfg->tok[cfg->tok_cnt ].regex = ParserData_AllocString(psr_data, L"$");

				if(cfg->tok[cfg->tok_cnt ].name == NULL || cfg->tok[cfg->tok_cnt ].regex == NULL)
				{
						status = AR_E_NOMEM;
						goto INVALID_POINT;
				}

				cfg->tok_cnt++;


				for(i = 0; i < cfg->tok_cnt ; ++i)
				{
						if(cfg->tok[i].code_name == NULL)
						{
								wchar_t buf[128];
								AR_swprintf(buf, 128, L"%Id", cfg->tok[i].tokval);
								cfg->tok[i].code_name = ParserData_AllocString(psr_data, buf);
						}
				}


		}




		if(prec)
		{
				/*cfg->prec_cnt = prec->count;*/

				if(prec->count > 0)
				{
						cfg->prec = AR_NEWARR0(cfgPrec_t, prec->count);
						if(cfg->prec == NULL)
						{
								status = AR_E_NOMEM;
								goto INVALID_POINT;
						}
				}else
				{
						cfg->prec = NULL;
				}

				for(i = 0; i < prec->count; ++i)
				{

						if(prec->lst[i]->type == CFG_ERROR_T)
						{
								cfg->has_error = true;

						}else
						{
								arStatus_t tmp_status;
								size_t k;
								cfgPrec_t *dest = &cfg->prec[cfg->prec_cnt];
								CFG_InitPrec(dest);

								tmp_status = CFG_CopyPrec(dest, &prec->lst[i]->prec, psr_data);

								if(tmp_status != AR_S_YES)
								{
										status = tmp_status;
										goto INVALID_POINT;
								}

								
								for(k = 0; k < dest->count; ++k)
								{
										size_t x;
										for(x = 0; x < cfg->tok_cnt; ++x)
										{
												if(cfg->tok[x].is_skip)
												{
														continue;
												}

												AR_ASSERT(cfg->tok[x].name != NULL);
												if(AR_wcscmp(dest->prec_tok_set[k], cfg->tok[x].name) == 0)
												{
														dest->prec_tok_val[k] = cfg->tok[x].tokval;
														break;
												}
										}

										if(dest->prec_tok_val[k] == 0)
										{
												dest->prec_tok_val[k] = tmp_tok_val++;
										}

								}

								dest->prec_level = i + 1;
								cfg->prec_cnt++;
						}
				}
		}


		if(rule)
		{
				/*cfg->rule_cnt = rule->count;*/

				if(rule->count > 0)
				{
						cfg->rule = AR_NEWARR0(cfgRule_t, rule->count);

						if(cfg->rule == NULL)
						{
								status = AR_E_NOMEM;
								goto INVALID_POINT;
						}
				}else
				{
						cfg->rule = NULL;
				}

				for(i = 0; i < rule->count; ++i)
				{
						if(rule->lst[i]->type == CFG_ERROR_T)
						{
								cfg->has_error = true;
						}else
						{
								cfg->rule[cfg->rule_cnt].line = rule->lst[i]->rule.line;

								cfg->rule[cfg->rule_cnt].lhs = ParserData_AllocString(psr_data, rule->lst[i]->rule.lhs);
								cfg->rule[cfg->rule_cnt].rhs = ParserData_AllocString(psr_data, rule->lst[i]->rule.rhs);

								if(cfg->rule[cfg->rule_cnt].lhs == NULL || cfg->rule[cfg->rule_cnt].rhs == NULL)
								{
										status = AR_E_NOMEM;
										goto INVALID_POINT;
								}

								if(rule->lst[i]->rule.prec_tok)
								{
										cfg->rule[cfg->rule_cnt].prec_tok = ParserData_AllocString(psr_data,rule->lst[i]->rule.prec_tok);

										if(cfg->rule[cfg->rule_cnt].prec_tok == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}
								}
										
								cfg->rule[cfg->rule_cnt].action_line = rule->lst[i]->rule.action_line;

								if(rule->lst[i]->rule.action_name)
								{
										cfg->rule[cfg->rule_cnt].action_name = ParserData_AllocString(psr_data, rule->lst[i]->rule.action_name);

										if(cfg->rule[cfg->rule_cnt].action_name == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}
								}

								if(rule->lst[i]->rule.action_ins)
								{
										cfg->rule[cfg->rule_cnt].action_ins = ParserData_AllocString(psr_data, rule->lst[i]->rule.action_ins);

										if(cfg->rule[cfg->rule_cnt].action_ins == NULL)
										{
												status = AR_E_NOMEM;
												goto INVALID_POINT;
										}

								}

								cfg->rule_cnt++;
						}
				}

		}


		if(start_rule != NULL)
		{
				cfg->start.line = start_rule->line;
				cfg->start.start_rule = ParserData_AllocString(psr_data, start_rule->start_rule);

				if(cfg->start.start_rule == NULL)
				{
						status = AR_E_NOMEM;
						goto INVALID_POINT;
				}

		}else
		{
				cfg->start.start_rule = NULL;
				cfg->start.line = 0;
		}


		if(pre_def)
		{
				if(pre_def->count > 0)
				{
						cfg->pre_def = AR_NEWARR0(cfgPreDef_t, pre_def->count);
						if(cfg->pre_def == NULL)
						{
								status = AR_E_NOMEM;
								goto INVALID_POINT;
						}
				}else
				{
						cfg->pre_def = NULL;
				}
				
				cfg->predef_cnt = pre_def->count;

				for(i = 0; i < pre_def->count; ++i)
				{
						AR_ASSERT(pre_def->lst[i]->type == CFG_PREDEF_T);
						cfg->pre_def[i].name = ParserData_AllocString(psr_data, pre_def->lst[i]->predef.name);
						cfg->pre_def[i].code = ParserData_AllocString(psr_data, pre_def->lst[i]->predef.code);

						cfg->pre_def[i].line = pre_def->lst[i]->predef.line;
						cfg->pre_def[i].flags = pre_def->lst[i]->predef.flags;

						if(cfg->pre_def[i].name == NULL || cfg->pre_def[i].code == NULL)
						{
								status = AR_E_NOMEM;
								goto INVALID_POINT;
						}
				}
		}

		return AR_S_YES;

INVALID_POINT:
		CFG_UnInitConfig(cfg);
		return status;
}










/********************************************************Parser Node****************************************************/













static cfgNode_t*		__get_cfg_node()
{
		return AR_NEW(cfgNode_t);
}

static void		__put_cfg_node(cfgNode_t *node)
{
		if(node)
		{
				AR_DEL(node);
		}

}






static cfgNode_t* CFG_CreateNode(cfgNodeType_t type)
{
		cfgNode_t		*node;

		node = __get_cfg_node();
		if(node == NULL)
		{
				return NULL;
		}
		AR_memset(node, 0, sizeof(*node));

		node->type = type;
		node->next = NULL;

		if(node->type == CFG_NODE_LIST_T)
		{
				CFG_InitNodeList(&node->lst);
		}else if(node->type == CFG_PREC_T)
		{
				CFG_InitPrec(&node->prec);
		}
		return node;
}


static void CFG_DestroyNode(cfgNode_t *node)
{
		if(node)
		{

				switch(node->type)
				{
				case CFG_EMPTY_T:
				{
						break;
				}
				case CFG_LEXEME_T:
				{
						break;
				}
				case CFG_NAME_T:
				{
						break;
				}
				case CFG_TOKEN_T:
				{
						break;
				}
				case CFG_PREC_T:
				{
						CFG_UnInitPrec(&node->prec);
						break;
				}
				case CFG_START_T:
				{
						break;
				}
				case CFG_RULE_T:
				{

						break;
				}
				case CFG_NODE_LIST_T:
				{
						size_t i;
						for(i = 0; i < node->lst.count; ++i)
						{
								CFG_DestroyNode(node->lst.lst[i]);
						}
						CFG_UnInitNodeList(&node->lst);
						break;
				}
				case CFG_CONFIG_T:
				{
						CFG_UnInitConfig(&node->config);
						break;
				}
				case CFG_ERROR_T:
				{
						break;
				}
				case CFG_PREDEF_T:
				{
						break;
				}
				default:
				{
						AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
				}
				}
				
				__put_cfg_node(node);

		}
}






/**************************************************************************************************************************************************/
static psrRetVal_t AR_STDCALL __build_leaf(const psrToken_t *tok,  void *ctx)
{
		psrRetVal_t ret = {AR_S_YES, NULL};
		cfgParserData_t	*parser_ctx;
		cfgNode_t *node;
		AR_ASSERT(tok->str_cnt > 0 && ctx != NULL);
		
		parser_ctx = (cfgParserData_t*)ctx;

		node = CFG_CreateNode(CFG_LEXEME_T);

		if(node == NULL)
		{
				ret.status = AR_E_NOMEM;
				goto INVALID_POINT;
		}



		node->lexeme.lex_val = (cfgLexValue_t)tok->term_val;

		if(tok->term_val == CFG_LEXVAL_LEXEME && (tok->str[0] == L'"' || tok->str[0] == L'\''))
		{
				wchar_t *tmp, *p;
				AR_ASSERT(tok->str[tok->str_cnt-1] == L'"' || tok->str[tok->str_cnt-1] == L'\'');

				tmp = AR_NEWARR0(wchar_t, tok->str_cnt + 1);
				if(tmp == NULL)
				{
						ret.status = AR_E_NOMEM;
						goto INVALID_POINT;
				}

				AR_wcsncpy(tmp,tok->str + 1, tok->str_cnt-2);
				tmp[tok->str_cnt-2] = L'\0';

				
				p = (wchar_t*)AR_wcstrim_space(tmp);
				p = AR_wcstrim_right_space(p);
				
				node->lexeme.lexeme = ParserData_AllocString(parser_ctx, p);

				if(node->lexeme.lexeme == NULL)
				{
						AR_DEL(tmp);
						tmp = NULL;
						ret.status = AR_E_NOMEM;
						goto INVALID_POINT;
				}

				if(AR_wcslen(node->lexeme.lexeme) == 0)
				{
						cfgReportInfo_t info;
						wchar_t buf[128];
						
						AR_swprintf(buf, 128, L"Empty lexeme : line = %Id", tok->line);

						info.type = CFG_REPORT_ERROR_LEX_T;
						info.lex_error.msg = buf;
						info.lex_error.tok = tok;
						parser_ctx->report->report_func(&info, parser_ctx->report->report_ctx);
						parser_ctx->has_error = true;
				}
				
				if(tmp)
				{
						AR_DEL(tmp);
						tmp = NULL;
				}

		}else if(tok->term_val == CFG_LEXVAL_ACTION_INS)
		{
				wchar_t *buf;
				
				AR_ASSERT(tok->str_cnt >= 4);

				buf = AR_NEWARR(wchar_t, tok->str_cnt + 1);
				if(buf == NULL)
				{
						ret.status = AR_E_NOMEM;
						goto INVALID_POINT;
				}
				
				AR_wcsncpy(buf, tok->str, tok->str_cnt);
				buf[tok->str_cnt] = L'\0';

				
				AR_ASSERT(buf[0] == L'{' && buf[1] == L':');
				AR_ASSERT(buf[tok->str_cnt-1] == L'}' && buf[tok->str_cnt-2] == L':');

				buf[1] = L' ';
				buf[tok->str_cnt-2] = L' ';
				
				node->lexeme.lexeme = ParserData_AllocString(parser_ctx, buf);

				if(node->lexeme.lexeme == NULL)
				{
						ret.status = AR_E_NOMEM;
						AR_DEL(buf);
						buf = NULL;
						goto INVALID_POINT;
				}

				if(buf)
				{
						AR_DEL(buf);
						buf = NULL;
				}

		}else if(tok->str_cnt > 0)
		{
				node->lexeme.lexeme = ParserData_AllocStringN(parser_ctx, tok->str, tok->str_cnt);

				if(node->lexeme.lexeme == NULL)
				{
						ret.status = AR_E_NOMEM;
						goto INVALID_POINT;
				}
		}

		
		node->lexeme.line = tok->line;

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)node;

		return ret;


INVALID_POINT:
		if(node == NULL)
		{
				CFG_DestroyNode(node);
		}
		ret.node = NULL;
		return ret;
}



#define AR_PRINT_FUNCTION()	AR_LOG(L"enter function : %hs\r\n", AR_FUNC_NAME)

/*
{ L"action_decl			:		%action lexeme action_ins",				__handle_action_decl,0},
{ L"action_decl			:		%action lexeme",						__handle_action_decl},
{ L"action_decl			:				",										NULL},
*/
static psrRetVal_t		AR_STDCALL __handle_action_decl(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;		
		psrRetVal_t		ret = {AR_S_YES, NULL};

		AR_ASSERT(count == 2 || count == 3);
		AR_ASSERT(ns[0]->type == CFG_LEXEME_T && ns[1]->type == CFG_LEXEME_T);

		AR_UNUSED(name);
		AR_UNUSED(ctx);
		
		AR_PRINT_FUNCTION();

		res = CFG_CreateNode(CFG_NODE_LIST_T);

		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}
		
		ret.status = CFG_InsertToNodeList(&res->lst, ns[1]);

		if(ret.status != AR_S_YES)
		{
				CFG_DestroyNode(res);
				res = NULL;
				return ret;
		}

		ns[1] = NULL;
		
		if(count == 3)
		{
				AR_ASSERT(ns[2] && ns[2]->type == CFG_LEXEME_T);

				ret.status = CFG_InsertToNodeList(&res->lst, ns[2]);

				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						return ret;
				}
				ns[2] = NULL;
		}
		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;
}



/*
{ L"term_list			:		term_list term",								NULL},
{ L"term_list			:		term",											NULL},
*/

static psrRetVal_t		AR_STDCALL __handle_term_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t		ret = {AR_S_YES, NULL};
		AR_ASSERT((count == 1 || count == 2) && nodes != NULL);
		AR_UNUSED(name);
		AR_UNUSED(ctx);
		AR_PRINT_FUNCTION();

		if(count == 1)
		{
				res = CFG_CreateNode(CFG_NODE_LIST_T);

				if(res == NULL)
				{
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}

				AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T);

				ret.status = CFG_InsertToNodeList(&res->lst, ns[0]);
				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.node = NULL;
						return ret;
				}
				ns[0] = NULL;
		}else
		{
				AR_ASSERT(ns[0] && ns[0]->type == CFG_NODE_LIST_T && ns[1] && ns[1]->type == CFG_LEXEME_T);

				res = ns[0];

				ret.status = CFG_InsertToNodeList(&res->lst, ns[1]);

				if(ret.status != AR_S_YES)
				{
						return ret;
				}

				ns[0] = ns[1] = NULL;
		}

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;
}




/*
{ L"rhs					:		term_list prec_decl action_decl",				__handle_rhs,0},
{ L"rhs					:		. prec_decl action_decl",						__handle_rhs,0},
*/


static psrRetVal_t		AR_STDCALL __handle_rhs(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		size_t i;
		psrRetVal_t		ret = {AR_S_YES, NULL};
		cfgParserData_t	*psr_data;

		AR_ASSERT(count == 3 && nodes != NULL);
		AR_UNUSED(name);
		AR_UNUSED(count);
		
		AR_PRINT_FUNCTION();


		psr_data = (cfgParserData_t*)ctx;
		AR_ASSERT(psr_data != NULL);

		

		res = CFG_CreateNode(CFG_RULE_T);

		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}

		res->rule.lhs = NULL;
		res->rule.line = 0;
		res->rule.prec_tok = NULL;
		res->rule.rhs = NULL;
		res->rule.action_line = 0;
		res->rule.action_name = NULL;
		res->rule.action_ins = NULL;

		/*AR_ASSERT(ns[0] && ns[0]->type == CFG_NODE_LIST_T && ns[0]->lst.count > 0);*/
		AR_ASSERT(ns[0]);
		AR_ASSERT(ns[1] ? ns[1]->type == CFG_LEXEME_T : true);
		AR_ASSERT(ns[2] ? ns[2]->type == CFG_NODE_LIST_T : true);


		if(ns[0]->type == CFG_LEXEME_T && ns[0]->lexeme.lex_val == CFG_LEXVAL_DOT)
		{
				res->rule.rhs = ParserData_AllocString(psr_data, L" ");
				res->rule.line = ns[0]->lexeme.line;

				if(res->rule.rhs == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						return ret;
				}

		}else if(ns[0]->type == CFG_NODE_LIST_T)
		{
				arString_t *right_tmp;

				right_tmp = AR_CreateString();

				if(right_tmp == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}


				for(i = 0; i < ns[0]->lst.count; ++i)
				{
						cfgNode_t *tmp = ns[0]->lst.lst[i];

						AR_ASSERT(tmp->type == CFG_LEXEME_T && tmp->lexeme.lex_val == (size_t)CFG_LEXVAL_LEXEME);

						ret.status = AR_AppendString(right_tmp, tmp->lexeme.lexeme);
						
						if(ret.status != AR_S_YES)
						{
								AR_DestroyString(right_tmp);
								right_tmp = NULL;
								CFG_DestroyNode(res);
								res = NULL;
								ret.status = AR_E_NOMEM;
								ret.node = NULL;
								return ret;
						}

						ret.status = AR_AppendString(right_tmp, L" ");

						if(ret.status != AR_S_YES)
						{
								AR_DestroyString(right_tmp);
								right_tmp = NULL;
								CFG_DestroyNode(res);
								res = NULL;
								ret.status = AR_E_NOMEM;
								ret.node = NULL;
								return ret;
						}
						
						if(i == 0)
						{
								res->rule.line = tmp->lexeme.line;
						}
				}


				res->rule.rhs = ParserData_AllocString(psr_data, AR_GetStringCString(right_tmp));
				AR_DestroyString(right_tmp);
				right_tmp = NULL;

				if(res->rule.rhs == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}

				
		}else
		{
				AR_ASSERT(false);
		}


		if(ns[1] && ns[1]->lexeme.lexeme)
		{
				res->rule.prec_tok = ParserData_AllocString(psr_data, ns[1]->lexeme.lexeme);

				if(res->rule.prec_tok == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}
		}

		if(ns[2])
		{
				AR_ASSERT(ns[2]->lst.count == 1 || ns[2]->lst.count == 2);
				
				res->rule.action_line = ns[2]->lst.lst[0]->lexeme.line;

				if(ns[2]->lst.lst[0]->lexeme.lexeme)
				{
						res->rule.action_name = ParserData_AllocString(psr_data, ns[2]->lst.lst[0]->lexeme.lexeme);
						
						if(res->rule.action_name == NULL)
						{
								CFG_DestroyNode(res);
								res = NULL;
								ret.status = AR_E_NOMEM;
								ret.node = NULL;
								return ret;
						}
				}
				
				if(ns[2]->lst.count == 2 && ns[2]->lst.lst[1]->lexeme.lexeme)
				{
						
						res->rule.action_ins = ParserData_AllocString(psr_data, ns[2]->lst.lst[1]->lexeme.lexeme);

						if(res->rule.action_ins == NULL)
						{
								CFG_DestroyNode(res);
								res = NULL;
								ret.status = AR_E_NOMEM;
								ret.node = NULL;
								return ret;
						}
				}
		}

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;

}




/*
{ L"rhs_list			: 		rhs_list  | rhs ",								NULL},
{ L"rhs_list			: 		rhs ",											NULL},
*/

static psrRetVal_t		AR_STDCALL __handle_rhs_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t		ret;

		AR_ASSERT((count == 1 || count == 3) && nodes != NULL);
		AR_UNUSED(name);
		AR_UNUSED(ctx);
		AR_PRINT_FUNCTION();


		ret.node = NULL;
		ret.status = AR_S_YES;

		if(count == 3)
		{
				AR_ASSERT(ns[0] && ns[0]->type == CFG_NODE_LIST_T && ns[1]->type == CFG_LEXEME_T && ns[1]->lexeme.lex_val == (size_t)CFG_LEXVAL_OR && ns[2] && ns[2]->type == CFG_RULE_T);

				res = ns[0];

				ret.status = CFG_InsertToNodeList(&res->lst, ns[2]);
				
				if(ret.status != AR_S_YES)
				{
						return ret;
				}

				ns[0] = ns[2] = NULL;
		}else
		{
				AR_ASSERT(ns[0]->type == CFG_RULE_T);
				res = CFG_CreateNode(CFG_NODE_LIST_T);
				if(res == NULL)
				{
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}

				ret.status = CFG_InsertToNodeList(&res->lst, ns[0]);

				if(ret.status != AR_S_YES)
				{
						return ret;
				}

				ns[0] = NULL;
		}

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;


}



/*
{ L"rule_def			: 		lexeme : rhs_list ",							__handle_rule_def},
*/

static psrRetVal_t		AR_STDCALL __handle_rule_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		size_t i;
		cfgParserData_t	*psr_data;
		psrRetVal_t  ret = {AR_S_YES, NULL};
		AR_ASSERT(count == 3);

		AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T && ns[1] && ns[1]->type == CFG_LEXEME_T && ns[2] && ns[2]->type == CFG_NODE_LIST_T);
		AR_ASSERT(ns[0]->lexeme.lexeme != NULL);

		AR_UNUSED(name);
		AR_UNUSED(count);
		AR_PRINT_FUNCTION();


		psr_data = (cfgParserData_t*)ctx;

		AR_ASSERT(psr_data != NULL);


		for(i = 0; i < ns[2]->lst.count; ++i)
		{
				cfgNode_t *tmp = ns[2]->lst.lst[i];

				AR_ASSERT(tmp->type == CFG_RULE_T);
				tmp->rule.lhs = ParserData_AllocString(psr_data, ns[0]->lexeme.lexeme);
				tmp->rule.line = ns[0]->lexeme.line;

				if(tmp->rule.lhs == NULL)
				{
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}
		}

		res = ns[2];
		ns[2] = NULL;
		ret.node = (psrNode_t*)res;
		return ret;
}





/*{ L"prec_def			:  		assoc lexeme ",								__handle_prec_def},*/
static psrRetVal_t		AR_STDCALL __handle_prec_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t		ret;
		wchar_t			c;
		size_t			i;
		cfgParserData_t	*psr_data;
		AR_ASSERT(count == 2);


		AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T &&  ns[0]->lexeme.lex_val == CFG_LEXVAL_ASSOC && ns[1] && ns[1]->type == CFG_NODE_LIST_T);
		AR_UNUSED(name);
		AR_UNUSED(count);
		AR_PRINT_FUNCTION();


		psr_data = (cfgParserData_t*)ctx;
		AR_ASSERT(psr_data != NULL);


		ret.status = AR_S_YES;
		ret.node = NULL;

		res = CFG_CreateNode(CFG_PREC_T);

		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}

		res->prec.line = ns[0]->lexeme.line;

		c = ns[0]->lexeme.lexeme[1];

		if(c == L'n')
		{
				res->prec.assoc	= PARSER_ASSOC_NONASSOC;

		}else if(c == L'l')
		{
				res->prec.assoc	= PARSER_ASSOC_LEFT;

		}else if(c == L'r')
		{
				res->prec.assoc	= PARSER_ASSOC_RIGHT;
		}else
		{
				AR_ASSERT(false);
				AR_CHECK(false, L"Arsenal Tools Internal Error In : %hs\r\n", AR_FUNC_NAME);
		}

		for(i = 0; i < ns[1]->lst.count; ++i)
		{
				const cfgNode_t *node = ns[1]->lst.lst[i];
				AR_ASSERT(node->type == CFG_LEXEME_T);

				ret.status = CFG_InsertTokenToPrec(&res->prec, node->lexeme.lexeme, 0, psr_data);

				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.node = NULL;
						return ret;
				}
				
				ret.status = ParserData_CheckAndInsertName(psr_data, node->lexeme.lexeme, node->lexeme.line, CFG_STR_PREC);
				
				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.node = NULL;
						return ret;
				}

		}

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;

}



/*
{ L"token_def			:  		%token %skip token_val_prec : lexeme token_val_prec token_value action_decl",	__handle_token_def,0},
{L"token_def			:  		%token lexeme token_val_prec : lexeme token_val_prec token_value action_decl",	__handle_token_def,0},
*/

static psrRetVal_t		AR_STDCALL __handle_token_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t		ret;
		cfgParserData_t	*psr_data;
		AR_ASSERT(count == 8);

		/*AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T && ns[1] && ns[1]->type == CFG_LEXEME_T && ns[2] && ns[2]->type == CFG_LEXEME_T && ns[4] && ns[4]->type == CFG_LEXEME_T);*/

		AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T
				&& ns[1] && ns[1]->type == CFG_LEXEME_T
				&& ns[3] && ns[3]->type == CFG_LEXEME_T
				&& ns[4] && ns[4]->type == CFG_LEXEME_T
				);

		AR_ASSERT((ns[2] == NULL) || (ns[2]->type == CFG_LEXEME_T));
		AR_ASSERT((ns[5] == NULL) || (ns[5]->type == CFG_LEXEME_T));

		AR_ASSERT((ns[6] == NULL) || (ns[6]->type == CFG_LEXEME_T));
		AR_ASSERT((ns[7] == NULL) || (ns[7]->type == CFG_NODE_LIST_T));

		AR_UNUSED(name);
		AR_UNUSED(count);
		AR_PRINT_FUNCTION();


		psr_data = (cfgParserData_t*)ctx;
		AR_ASSERT(psr_data != NULL);

		ret.status = AR_S_YES;
		ret.node = NULL;

		res = CFG_CreateNode(CFG_TOKEN_T);

		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				ret.node = NULL;
				return ret;
		}

		res->token.line = ns[1]->lexeme.line;

		if(ns[1]->lexeme.lex_val == CFG_LEXVAL_SKIP)
		{
				res->token.is_skip = true;
				res->token.name = NULL;
		}else
		{
				ret.status = ParserData_CheckAndInsertName((cfgParserData_t*)ctx, ns[1]->lexeme.lexeme, ns[1]->lexeme.line, CFG_STR_TOKEN);

				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						return ret;
				}

				res->token.is_skip = false;
				res->token.name = ParserData_AllocString(psr_data, ns[1]->lexeme.lexeme);
				
				if(res->token.name == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						return ret;
				}

				ns[1]->lexeme.lexeme = NULL;
		}

		res->token.regex = ParserData_AllocString(psr_data, ns[4]->lexeme.lexeme);
		if(res->token.regex == NULL)
		{
				CFG_DestroyNode(res);
				res = NULL;
				ret.status = AR_E_NOMEM;
				return ret;
		}

		ns[4]->lexeme.lexeme = NULL;

		res->token.lex_prec = 0;

		if(ns[2])
		{
				AR_wtou(ns[2]->lexeme.lexeme, (uint_t*)&res->token.tokval, 10);
		}else
		{
				res->token.tokval = 0;
		}

		if(ns[5])
		{
				AR_wtou(ns[5]->lexeme.lexeme, (uint_t*)&res->token.lex_prec, 10);
		}

		if(ns[6])
		{
				res->token.code_name = ParserData_AllocString(psr_data, ns[6]->lexeme.lexeme);
				
				if(res->token.code_name == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						return ret;
				}

				ret.status = ParserData_CheckAndInsertName(psr_data, ns[6]->lexeme.lexeme, ns[6]->lexeme.line, CFG_STR_TOKEN_VALUE);
				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						return ret;
				}

		}


		if(ns[7])
		{
				AR_ASSERT(ns[7]->lst.count == 1 || ns[7]->lst.count == 2);
				
				res->token.action_line = ns[7]->lst.lst[0]->lexeme.line;

				if(ns[7]->lst.lst[0]->lexeme.lexeme)
				{
						res->token.action_name = ParserData_AllocString(psr_data, ns[7]->lst.lst[0]->lexeme.lexeme);
						
						if(res->token.action_name == NULL)
						{
								CFG_DestroyNode(res);
								res = NULL;
								ret.status = AR_E_NOMEM;
								return ret;
						}
				}
				
				if(ns[7]->lst.count == 2)
				{
						res->token.action_ins = ParserData_AllocString(psr_data, ns[7]->lst.lst[1]->lexeme.lexeme);
						if(res->token.action_ins == NULL)
						{
								CFG_DestroyNode(res);
								res = NULL;
								ret.status = AR_E_NOMEM;
								return ret;
						}
				}
		}
	

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;

		return ret;

}





/*
{ L"name_def 			:		%name lexeme : lexeme  ",								__handle_name_def},
*/

static psrRetVal_t		AR_STDCALL __handle_name_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgParserData_t			*psr_data;
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t				ret = {AR_S_YES, NULL};
		AR_ASSERT(count == 4);

		AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T
				&& ns[1] && ns[1]->type == CFG_LEXEME_T
				&& ns[2] && ns[2]->type == CFG_LEXEME_T
				&& ns[3] && ns[3]->type == CFG_LEXEME_T
				);

		AR_UNUSED(name);
		AR_UNUSED(count);
		AR_PRINT_FUNCTION();


		res = CFG_CreateNode(CFG_NAME_T);

		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}


		res->name.line = ns[1]->lexeme.line;
		res->name.name = ns[1]->lexeme.lexeme;
		res->name.regex = ns[3]->lexeme.lexeme;

		psr_data = (cfgParserData_t*)ctx;

		ret.status = ParserData_CheckAndInsertName(psr_data, res->name.name, res->name.line, CFG_STR_NAME);

		if(ret.status != AR_S_YES)
		{
				CFG_DestroyNode(res);
				res = NULL;
				ret.status = AR_E_NOMEM;
				ret.node = NULL;
				return ret;
		}
		
		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;
}


/*
{ L"item				:		name_def ;",	__handle_item},
{ L"item				:		token_def ;",	__handle_item},
{ L"item				:		prec_def ;",	__handle_item},
{ L"item				:		rule_def ;",	__handle_item},
{ L"item				:		error ; ",	__handle_item},
{ L"item				:		; ",	__handle_item},
{ L"item				:		pre_code_decl ;",	 __handle_item,0},

*/

static psrRetVal_t		AR_STDCALL __handle_item(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res = NULL;
		psrRetVal_t				ret = {AR_S_YES, NULL};
		AR_ASSERT(count == 1 || count == 2);
		AR_UNUSED(ctx);
		AR_UNUSED(name);
		AR_PRINT_FUNCTION();


		if(count == 2)
		{
				if(ns[0] == NULL)
				{
						res = CFG_CreateNode(CFG_ERROR_T);
						if(res == NULL)
						{
								ret.status = AR_E_NOMEM;
								ret.node = NULL;
								return ret;
						}
				}else
				{
						res = ns[0];
						ns[0] = NULL;
				}

		}else
		{
				res = CFG_CreateNode(CFG_EMPTY_T);
				if(res == NULL)
				{
						ret.status = AR_E_NOMEM;
						ret.node = NULL;
						return ret;
				}
		}

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		AR_ASSERT(res != NULL);
		return ret;
}


/*
{ L"item_list			:		item_list item",	__handle_item_list},
{ L"item_list			:		",	NULL},
*/

static psrRetVal_t		AR_STDCALL __handle_item_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t		ret = {AR_S_YES, NULL};
		AR_ASSERT(count == 2);

		AR_ASSERT((ns[0] == NULL) || (ns[0] && ns[0]->type == CFG_NODE_LIST_T));
		AR_ASSERT(ns[1]);
		AR_UNUSED(ctx);
		AR_UNUSED(name);
		AR_UNUSED(count);
		AR_PRINT_FUNCTION();


		res = ns[0];
		if(res == NULL)
		{
				res = CFG_CreateNode(CFG_NODE_LIST_T);
				if(res == NULL)
				{
						ret.status = AR_E_NOMEM;
						return ret;
				}

		}

		ns[0] = NULL;

		if(ns[1]->type == CFG_NODE_LIST_T)
		{
				size_t i;
				for(i = 0; i < ns[1]->lst.count; ++i)
				{
						ret.status = CFG_InsertToNodeList(&res->lst, ns[1]->lst.lst[i]);

						if(ret.status != AR_S_YES)
						{
								CFG_DestroyNode(res);
								res = NULL;
								ret.node = NULL;
								return ret;
						}

						ns[1]->lst.lst[i] = NULL;
				}

		}else
		{
				ret.status = CFG_InsertToNodeList(&res->lst, ns[1]);
				if(ret.status != AR_S_YES)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.node = NULL;
					return ret;
				}
				ns[1] = NULL;
		}

		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;
}

/*
{ L"start_def			:  		%start lexeme",							__handle_start_def,0},
*/

static psrRetVal_t		AR_STDCALL __handle_start_def(psrNode_t **nodes, size_t count, const wchar_t * name_tmp, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		psrRetVal_t		ret = {AR_S_YES, NULL};

		AR_PRINT_FUNCTION();


		AR_ASSERT(count == 2);

		AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T && ns[0]->lexeme.lex_val == CFG_LEXVAL_START);
		AR_ASSERT(ns[1] && ns[1]->type == CFG_LEXEME_T);
		
		AR_UNUSED(ctx);
		AR_UNUSED(name_tmp);
		AR_UNUSED(count);

		res = CFG_CreateNode(CFG_START_T);
		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				ret.node = NULL;
				return ret;
		}

		res->start.line = ns[1]->lexeme.line;
		res->start.start_rule = ns[1]->lexeme.lexeme;

		ret.status = AR_S_YES;
		ret.node  = (psrNode_t*)res;
		return ret;
}



/*
{ L"pre_code_decl		:		%code pre_code_name action_ins	code_decl_attr",		__handle_pre_def,0},
*/
static psrRetVal_t		AR_STDCALL __handle_pre_def(psrNode_t **nodes, size_t count, const wchar_t * name_tmp, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res;
		size_t			len;
		psrRetVal_t		ret = {AR_S_YES, NULL};
		cfgParserData_t	*psr_data;

		AR_ASSERT(count == 4);

		AR_ASSERT(ns[0] && ns[0]->type == CFG_LEXEME_T && ns[0]->lexeme.lex_val == CFG_LEXVAL_CODE);
		AR_ASSERT(ns[2] && ns[2]->type == CFG_LEXEME_T && ns[2]->lexeme.lex_val == CFG_LEXVAL_ACTION_INS);

		AR_UNUSED(name_tmp);
		AR_UNUSED(count);
		AR_PRINT_FUNCTION();


		psr_data = (cfgParserData_t*)ctx;
		AR_ASSERT(psr_data != NULL);

		res = CFG_CreateNode(CFG_PREDEF_T);
		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				return ret;
		}

		res->predef.line = ns[0]->lexeme.line;
		
		len = AR_wcslen(ns[2]->lexeme.lexeme);
		AR_ASSERT(len >= 2);
		
		if(len >= 2)
		{
				AR_ASSERT(ns[2]->lexeme.lexeme[0] == L'{' && ns[2]->lexeme.lexeme[len-1] == L'}');
				res->predef.code = ParserData_AllocStringN(psr_data, ns[2]->lexeme.lexeme+1, len - 2);

				if(res->predef.code == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						return ret;
				}
		}else
		{
				res->predef.code = L"";
		}

		if(ns[1] == NULL)
		{
				res->predef.name = L"";
		}else
		{
				res->predef.name = ParserData_AllocString(psr_data, ns[1]->lexeme.lexeme);

				if(res->predef.name == NULL)
				{
						CFG_DestroyNode(res);
						res = NULL;
						ret.status = AR_E_NOMEM;
						return ret;
				}
		}

		res->predef.flags = 0;

		if(ns[3] != NULL)
		{
				size_t i;
				AR_ASSERT(ns[3]->type == CFG_NODE_LIST_T);

				for(i = 0; i < ns[3]->lst.count; ++i)
				{
						cfgNode_t *attr = ns[3]->lst.lst[i];

						if(attr != NULL)
						{
								AR_ASSERT(attr->type == CFG_LEXEME_T);

								if(attr->lexeme.lexeme)
								{
										if(AR_wcscmp(attr->lexeme.lexeme, CFG_BOTTOM_CODE_ATTR_NAME) == 0)/*此段代码是否在文本末尾*/
										{
												res->predef.flags |= CFG_CODE_ON_BOTTOM_F;
										}

										/*********************************************************************/
								}
						}
				}
				
		}


		ret.status = AR_S_YES;
		ret.node = (psrNode_t*)res;
		return ret;
}




/*
{ L"program				:		item_list #",			__handle_program, 0},
{ L"program				:		item_list error #",		__handle_program, 0},
*/
static psrRetVal_t		AR_STDCALL __handle_program(psrNode_t **nodes, size_t count, const wchar_t * name_tmp, void *ctx)
{
		cfgNode_t		**ns = (cfgNode_t**)nodes;
		cfgNode_t		*res = NULL;
		size_t	i;
		bool_t			has_err = false;
		cfgNodeList_t	name, token, prec, rule, error, empty, predef;
		cfgStart_t		*start_rule = NULL;
		cfgParserData_t	*parser_ctx;
		psrRetVal_t		ret = {AR_S_YES, NULL};

		AR_ASSERT(count == 2 || count == 3);
		AR_ASSERT((ns[0] == NULL) || (ns[0] && ns[0]->type == CFG_NODE_LIST_T));
		
		AR_PRINT_FUNCTION();


		parser_ctx = (cfgParserData_t*)ctx;

		AR_ASSERT(parser_ctx != NULL);


		AR_UNUSED(name_tmp);

		if(count == 2)
		{
				AR_ASSERT(ns[1]->type == CFG_LEXEME_T && ns[1]->lexeme.lex_val == CFG_LEXVAL_FAKE_EOI);
		}else
		{
				AR_ASSERT(ns[1] == NULL && ns[2]->type == CFG_LEXEME_T && ns[2]->lexeme.lex_val == CFG_LEXVAL_FAKE_EOI);
				has_err = true;
		}


		CFG_InitNodeList(&name);
		CFG_InitNodeList(&token);
		CFG_InitNodeList(&prec);
		CFG_InitNodeList(&rule);
		CFG_InitNodeList(&error);
		CFG_InitNodeList(&empty);
		CFG_InitNodeList(&predef);
		 

		for(i = 0; ns[0] && i < ns[0]->lst.count; ++i)
		{
				cfgNode_t *node = ns[0]->lst.lst[i];
				AR_ASSERT(node);

				switch(node->type)
				{
				case CFG_EMPTY_T:
				{
						ret.status = CFG_InsertToNodeList(&empty, node);

						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}

						break;
				}
				case CFG_NAME_T:
				{
						ret.status = CFG_InsertToNodeList(&name, node);
						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}
						break;
				}
				case CFG_TOKEN_T:
				{
						ret.status = CFG_InsertToNodeList(&token, node);
						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}

						break;
				}
				case CFG_PREC_T:
				{
						ret.status = CFG_InsertToNodeList(&prec, node);
						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}
						break;
				}
				case CFG_START_T:
				{
						start_rule = &node->start;
						break;
				}
				case CFG_RULE_T:
				{
						ret.status = CFG_InsertToNodeList(&rule, node);
						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}

						break;
				}
				case CFG_ERROR_T:
				{
						ret.status = CFG_InsertToNodeList(&error, node);
						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}

						break;
				}
				case CFG_PREDEF_T:
				{
						ret.status = CFG_InsertToNodeList(&predef, node);
						if(ret.status != AR_S_YES)
						{
								goto END_POINT;
						}

						break;
				}
				case CFG_NODE_LIST_T:
				case CFG_CONFIG_T:
				case CFG_LEXEME_T:
				default:
				{
						AR_ASSERT(false);
						AR_CHECK(false, L"Arsenal Tools Internal Error In : %hs\r\n", AR_FUNC_NAME);
				}
				}
		}


		res = CFG_CreateNode(CFG_CONFIG_T);

		if(res == NULL)
		{
				ret.status = AR_E_NOMEM;
				goto END_POINT;
		}

		ret.status = CFG_InitConfig(&res->config, &name, &token, &prec, &rule, start_rule, &predef, parser_ctx);
		
		if(ret.status != AR_S_YES)
		{
				CFG_DestroyNode(res);
				res = NULL;
				goto END_POINT;
		}

		if(parser_ctx->has_error || error.count > 0 || has_err)
		{
				res->config.has_error = true;
		}

END_POINT:
		CFG_UnInitNodeList(&name);
		CFG_UnInitNodeList(&token);
		CFG_UnInitNodeList(&prec);
		CFG_UnInitNodeList(&rule);
		CFG_UnInitNodeList(&error);
		CFG_UnInitNodeList(&empty);
		CFG_UnInitNodeList(&predef);

		ret.node = (psrNode_t*)res;
		return ret;
}



/**************************************************************************************************************************************************/

typedef struct __cfg_rule_tag
{
		const wchar_t *rule;
		psrRuleFunc_t handler;
		size_t			auto_ret;
}cfgRuleDef_t;



static const cfgRuleDef_t	__cfg_rule[] =
{


		{ L"item_list			:		item_list item",	__handle_item_list, 0},
		{ L"item_list			:		",	NULL, 0},
		
		{ L"item				:		pre_code_decl ;",	 __handle_item,0},
		{ L"item				:		start_def ;",	__handle_item, 0},
		{ L"item				:		name_def ;",	__handle_item, 0},
		{ L"item				:		token_def ;",	__handle_item,0},
		{ L"item				:		prec_def ;",	__handle_item,0},
		{ L"item				:		rule_def ;",	__handle_item,0},
		{ L"item				:		error ; ",	__handle_item,0},
		{ L"item				:		; ",	__handle_item,0},

		{ L"name_def 			:		%name lexeme : lexeme ",								__handle_name_def,0},

		{ L"token_def			:  		%token %skip token_val_prec : lexeme token_val_prec token_value action_decl",	__handle_token_def,0},
		{ L"token_def			:  		%token lexeme token_val_prec : lexeme token_val_prec token_value action_decl",	__handle_token_def,0},

		{ L"token_val_prec 		:		, number",												NULL,1},
		{ L"token_val_prec 		:		",														NULL,0},

		{ L"token_value			:  		%value lexeme",	NULL,1},
		{ L"token_value			:  		",	NULL,0},


		{ L"prec_def			:  		assoc term_list ",								__handle_prec_def,0},


		{ L"rule_def			: 		lexeme : rhs_list ",							__handle_rule_def,0},


		{ L"rhs_list			: 		rhs_list  | rhs ",								__handle_rhs_list,0},
		{ L"rhs_list			: 		rhs ",											__handle_rhs_list,0},
		{ L"rhs					:		term_list prec_decl action_decl",				__handle_rhs,0},
		{ L"rhs					:		. prec_decl action_decl",						__handle_rhs,0},

		{ L"term_list			:		term_list lexeme",								__handle_term_list,0},
		{ L"term_list			:		lexeme",										__handle_term_list,0},




		{ L"prec_decl			:		%prec lexeme",									NULL,1},

		{ L"prec_decl			:		",												NULL,0},
		
		{ L"action_decl			:		%action lexeme action_ins",				__handle_action_decl,0},
		{ L"action_decl			:		%action lexeme",						__handle_action_decl,0},
		{ L"action_decl			:		",										NULL,0},

		{ L"start_def			:  		%start lexeme",							__handle_start_def,0},

		
		{ L"pre_code_decl		:		%code pre_code_name action_ins	code_decl_attr",		__handle_pre_def,0},
		{ L"pre_code_name		:		lexeme",								NULL,0},
		{ L"pre_code_name		:		",										NULL,0},

		{ L"code_decl_attr		:		term_list",								NULL,0},
		{ L"code_decl_attr		:		",										NULL,0},

		
		{ L"program				:		item_list #",			__handle_program, 0},
		{ L"program				:		item_list error #",		__handle_program, 0}

};




static lex_t* __build_lex()
{
		lex_t *lex;
		size_t	i;
		arStatus_t status;
		lex = Lex_Create();

		if(lex == NULL)
		{
				return NULL;
		}

		

		for(i = 0; i < AR_NELEMS(__cfg_lex_name); ++i)
		{
			
				status = Lex_Insert(lex, __cfg_lex_name[i]);
				if(status == AR_S_YES)
				{
				}else if(status == AR_S_NO)
				{
						AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
				}else
				{
						goto INVALID_POINT;
				}
		}

		for(i = 0; i < AR_NELEMS(__cfg_pattern); ++i)
		{
				lexAction_t action;
				action.is_skip = __cfg_pattern[i].is_skip;
				action.priority = __cfg_pattern[i].prec;
				action.value = (size_t)__cfg_pattern[i].val;

				
				status = Lex_InsertRule(lex, __cfg_pattern[i].regex, &action);

				if(status == AR_S_YES)
				{
				}else if(status == AR_S_NO)
				{
						AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
				}else
				{
						goto INVALID_POINT;
				}
		}

		status = Lex_GenerateTransTable(lex);
		if(status == AR_S_YES)
		{
		}else if(status == AR_S_NO)
		{
				AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
		}else
		{
				goto INVALID_POINT;
		}

		return lex;

INVALID_POINT:
		if(lex)
		{
				Lex_Destroy(lex);
				lex = NULL;
		}
		return NULL;
}


static psrGrammar_t*	__build_grammar(psrHandler_t *handler)
{
		psrGrammar_t	*gmr;
		size_t i;
		arStatus_t		status;
		AR_ASSERT(handler != NULL);

		status  = AR_S_YES;
		gmr = Parser_CreateGrammar(handler);

		if(gmr == NULL)
		{
				return NULL;
		}

		for(i = 0; i < AR_NELEMS(__cfg_term); ++i)
		{
				status = Parser_InsertTerm(gmr, __cfg_term[i].name, (size_t)__cfg_term[i].val, PARSER_ASSOC_NONASSOC, 0, __build_leaf);
				if(status == AR_S_YES)
				{
						
				}else if(status == AR_S_NO)
				{
						AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
				}else
				{
						goto INVALID_POINT;
				}
		}

		for(i = 0; i < AR_NELEMS(__cfg_rule); ++i)
		{
				status = Parser_InsertRuleByStr(gmr, __cfg_rule[i].rule, NULL, __cfg_rule[i].handler, __cfg_rule[i].auto_ret);

				if(status == AR_S_YES)
				{
						
				}else if(status == AR_S_NO)
				{
						AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
				}else
				{
						goto INVALID_POINT;
				}

		}

		status = Parser_SetStartRule(gmr, L"program");
		if(status == AR_S_YES)
		{

		}else if(status == AR_S_NO)
		{
				AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
		}else
		{
				goto INVALID_POINT;
		}

		status = Parser_CheckIsValidGrammar(gmr, NULL);
		if(status == AR_S_YES)
		{

		}else if(status == AR_S_NO)
		{
				AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
		}else
		{
				goto INVALID_POINT;
		}


		return gmr;


INVALID_POINT:
		if(gmr)
		{
				Parser_DestroyGrammar(gmr);
				gmr = NULL;
		}

		return NULL;
}




static const parser_t*		__build_parser(const psrGrammar_t *gmr)
{
		const parser_t *parser;
		AR_ASSERT(gmr && Parser_CheckIsValidGrammar(gmr, NULL) == AR_S_YES);

		parser = Parser_CreateParser(gmr, PARSER_SLR);
		AR_ASSERT(parser && Parser_CountParserConflict(parser) == 0);
		return parser;
}




/**************************************************************************************************************************************************/





static void	AR_STDCALL cfg_on_error(int_t level, const wchar_t *msg, void *ctx)
{
		cfgReport_t				*report = NULL;
		cfgReportInfo_t			info;
		AR_ASSERT(msg != NULL && ctx != NULL);

		report = ((cfgParserData_t*)ctx)->report;
		
		AR_memset(&info, 0, sizeof(info));

		info.type = CFG_REPORT_ERROR_T;
		info.error.err_level = level;
		info.error.err_msg = msg;
		report->report_func(&info, report->report_ctx);
}


void	AR_STDCALL cfg_on_print(const wchar_t *msg, void *ctx)
{
		cfgReport_t				*report = NULL;
		cfgReportInfo_t			info;
		AR_ASSERT(msg != NULL && ctx != NULL);

		report = ((cfgParserData_t*)ctx)->report;

		AR_memset(&info, 0, sizeof(info));

		info.type = CFG_REPORT_MESSAGE_T;
		info.std_msg.message = msg;
		report->report_func(&info, report->report_ctx);
}




static void	AR_STDCALL cfg_free(psrNode_t *node, void *ctx)
{
		AR_UNUSED(ctx);
		CFG_DestroyNode((cfgNode_t*)node);
}




static arStatus_t		AR_STDCALL cfg_error(const psrToken_t *tok, const size_t expected[], size_t count, void *ctx)
{
		cfgReport_t				*report = NULL;
		cfgReportInfo_t			info;

		arString_t		*str;
		wchar_t			*buf;
		size_t			i;

/*
		if(tok->term_val == CFG_LEXVAL_FAKE_EOI)
		{
				return;
		}
*/

		AR_ASSERT(tok != NULL && ctx != NULL && expected != NULL && count > 0);

		report = ((cfgParserData_t*)ctx)->report;
		AR_memset(&info, 0, sizeof(info));

		buf = NULL;
		str = NULL;

		/******************************************************************************************/
		if(tok->str_cnt == 0 || tok->term_val == CFG_LEXVAL_FAKE_EOI)
		{
				buf = AR_NEWARR(wchar_t, 128);
				if(buf)
				{
						AR_wcscpy(buf, L"%CFG_LEXVAL_EOI");
				}
		}else
		{
				buf = AR_NEWARR(wchar_t, tok->str_cnt + 1);
				if(buf)
				{
						AR_wcsncpy(buf, tok->str, tok->str_cnt);
						buf[tok->str_cnt] = L'\0';
				}
		}
		
		if(buf == NULL)
		{
				goto INVALID_POINT;
		}


		str = AR_CreateString();

		if(str == NULL)
		{
				goto INVALID_POINT;
		}

		if(AR_AppendFormatString(str, L"Invalid Token \"%ls\" in (%Id : %Id)\r\n\r\n", buf, tok->line, tok->col) != AR_S_YES)
		{
				goto INVALID_POINT;
		}

		AR_DEL(buf);
		buf = NULL;


		if(AR_AppendFormatString(str, L"Expected Term :\r\n") != AR_S_YES)
		{
				goto INVALID_POINT;
		}

		for(i = 0; i < count; ++i)
		{
				const wchar_t *term = NULL;
				size_t x;
				for(x = 0; x < sizeof(__cfg_term) / sizeof(__cfg_term[0]); ++x)
				{
						if((size_t)(__cfg_term[x].val) == expected[i])
						{
								term = __cfg_term[x].name;
						}
				}

				AR_ASSERT(term != NULL);

				if(AR_AppendFormatString(str, L"\"%ls\" ", term) != AR_S_YES)
				{
						goto INVALID_POINT;
				}
		}
		if(AR_AppendFormatString(str, L"\r\n\r\n") != AR_S_YES)
		{
				goto INVALID_POINT;
		}
		/******************************************************************************************/
		info.syntax_error.msg = AR_GetStringCString(str);
		info.syntax_error.tok = tok;
		info.type = CFG_REPORT_ERROR_SYNTAX_T;
		report->report_func(&info, report->report_ctx);
		AR_DestroyString(str);

		return AR_S_YES;

INVALID_POINT:
		if(buf)
		{
				AR_DEL(buf);
				buf = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

		return AR_E_NOMEM;
}



static void AR_STDCALL __default_report_func(const cfgReportInfo_t *report, void *context)
{
		AR_UNUSED(report);
		AR_UNUSED(context);
}


static cfgReport_t		__g_def_report = 
{
		__default_report_func,
		NULL
};


#if(0)
static arIOCtx_t	__def_io_ctx = 
{		
		cfg_on_error,
		cfg_on_print,
		NULL
};

static psrHandler_t		__def_handler_ctx = 
{
		cfg_error,
		cfg_free,
};
#endif


static arSpinLock_t				__g_lock;
static lex_t					*__g_lex;
static psrGrammar_t				*__g_grammar = NULL;
static const parser_t			*__g_parser = NULL;


static void __init_parser_tag()
{
		psrHandler_t	psr_handler;
		AR_InitSpinLock(&__g_lock);
		
		psr_handler.error_f = cfg_error;
		psr_handler.free_f = cfg_free;

#if(0)
		__g_lex		= __build_lex();
		__g_grammar = __build_grammar(&psr_handler);
		__g_parser	= __build_parser(__g_grammar);

		if(__g_lex == NULL || __g_grammar == NULL || __g_parser == NULL)
		{
				AR_error(AR_ERR_FATAL, L"grammar config : failed to initialize\r\n");
		}

#endif
		__g_lex		= NULL;
		__g_grammar = NULL;
		__g_parser	= NULL;
}


static void __uninit_parser_tag()
{
		if(__g_parser)
		{
				Parser_DestroyParser(__g_parser);
				__g_parser = NULL;
		}

		if(__g_grammar)
		{
				Parser_DestroyGrammar(__g_grammar);
				__g_grammar = NULL;
		}

		if(__g_lex)
		{
				Lex_Destroy(__g_lex);
				__g_lex = NULL;
		}
		AR_UnInitSpinLock(&__g_lock);
		
}

static lexMatch_t*		__create_lex_match()
{
		lexMatch_t		*match;

		AR_LockSpinLock(&__g_lock);

		if(__g_lex == NULL)
		{
				__g_lex = __build_lex();
				if(__g_lex == NULL)
				{
						AR_error(AR_ERR_FATAL, L"grammar config : failed to initialize lexer\r\n");
				}
		}


		match = Lex_CreateMatch(__g_lex);
		AR_UnLockSpinLock(&__g_lock);

		return match;
}

static void				__destroy_lex_match(lexMatch_t *match)
{
		AR_ASSERT(match != NULL);
		Lex_DestroyMatch(match);
}

static psrContext_t*	__create_parser_context(void *ctx)
{
		psrContext_t	*parser_context = NULL;
		AR_LockSpinLock(&__g_lock);


		if(__g_grammar == NULL)
		{
				psrHandler_t	psr_handler;
				psr_handler.error_f = cfg_error;
				psr_handler.free_f = cfg_free;

				__g_grammar = __build_grammar(&psr_handler);

				if(__g_grammar == NULL)
				{
						AR_error(AR_ERR_FATAL, L"grammar config : failed to initialize grammar\r\n");
				}

		}

		if(__g_parser == NULL)
		{
				__g_parser = __build_parser(__g_grammar);
				if(__g_parser == NULL)
				{
						AR_error(AR_ERR_FATAL, L"grammar config : failed to initialize parser\r\n");
				}
		}

		parser_context = Parser_CreateContext(__g_parser, ctx);
		AR_UnLockSpinLock(&__g_lock);
		return parser_context;
}

static void				__destroy_parser_context(psrContext_t *parser_context)
{
		AR_ASSERT(parser_context != NULL);
		Parser_DestroyContext(parser_context);
}





const cfgConfig_t*	CFG_CollectGrammarConfig(const wchar_t *gmr_txt, cfgReport_t *report)
{

		arStatus_t is_ok, has_error;
		
		psrContext_t	*parser_context;
		cfgParserData_t	psr_data;
		lexMatch_t		*match;

		lexToken_t		tok;
		psrToken_t		term;
		
		cfgNode_t		*result = NULL;

		arIOCtx_t		io_ctx ;
		

		AR_ASSERT(gmr_txt != NULL);
		result = NULL;

		if(report == NULL)report = &__g_def_report;

		io_ctx.on_error = cfg_on_error;
		io_ctx.on_print = cfg_on_print;
		io_ctx.ctx		= (void*)report;


		match = NULL;
		parser_context = NULL;

		if(ParserData_Init(&psr_data, report) != AR_S_YES)
		{
				goto END_POINT;
		}


		
		
		match		   = __create_lex_match();
		if(match == NULL)
		{
				goto END_POINT;
		}

		
		
		parser_context = __create_parser_context((void*)&psr_data);

		if(parser_context == NULL)
		{
				goto END_POINT;
		}
		
		Lex_ResetInput(match, gmr_txt);

		is_ok = AR_S_YES;
		has_error = AR_S_YES;


		while(is_ok == AR_S_YES)
		{
				is_ok = Lex_Match(match, &tok);

				if(is_ok == AR_S_YES)
				{
						
						if(tok.value == CFG_LEXVAL_COMMENT)
						{
								continue;
						}

						PARSER_TOTERMTOK(&tok, &term);

						/*
						构造一个简单空语句，以便不会在 abc CFG_LEXVAL_EOI这种情况下，无法分析出子树
						*/
						if(term.term_val == CFG_LEXVAL_EOI)
						{
								arStatus_t psr_ret;
								psrToken_t end;
								end.col = term.col;
								end.line = term.line;
								end.str = L"#";
								end.str_cnt = 1;
								end.term_val = CFG_LEXVAL_FAKE_EOI;

								psr_ret = Parser_AddToken(parser_context, &end);
								
								if(psr_ret == AR_S_YES)
								{
										
								}else if(psr_ret == AR_S_NO)
								{
										AR_CHECK(false, L"Arsenal internal error : %hs\r\n", AR_FUNC_NAME);
								}else/*存储分配失败等*/
								{
										goto END_POINT;
								}
						}

						is_ok = Parser_AddToken(parser_context, &term);

						if(tok.value == CFG_LEXVAL_EOI)
						{
								break;
						}

						
				}else if(is_ok == AR_S_NO)
				{
						cfgReportInfo_t	info;
						psrToken_t		tmp_tok;
						
						size_t n;
						size_t	line, col;

						arString_t		*str;
						wchar_t			*tok = NULL;

						str = NULL;
						tok = NULL;

						AR_memset(&info, 0, sizeof(info));
						n = AR_wcslen(Lex_GetNextInput(match));

						if(n > 5)
						{
								n = 5;
						}

						tok = AR_NEWARR(wchar_t, n + 1);
						if(tok)
						{
								AR_wcsncpy(tok, Lex_GetNextInput(match), n);
								tok[n] = L'\0';
						}
						str = AR_CreateString();

						if(tok == NULL || str == NULL)
						{
								goto INNER_INV_POINT;
						}
						
						Lex_MatchGetCoordinate(match, NULL, &line, &col);

						if(AR_AppendFormatString(str, L"Invalid Token %ls...(%Id : %Id)\r\n", tok, line, col) != AR_S_YES)
						{
								goto INNER_INV_POINT;
						}

						if(tok)
						{
								AR_DEL(tok);
								tok = NULL;
						}

						info.type = CFG_REPORT_ERROR_LEX_T;
						info.lex_error.msg = AR_GetStringCString(str);

						tmp_tok.term_val = 0;
						tmp_tok.str_cnt = 0;
						tmp_tok.str =  Lex_GetNextInput(match);

						Lex_MatchGetCoordinate(match, NULL, &line, &col);
						tmp_tok.line = line;
						tmp_tok.col = col;

						info.lex_error.tok = &tmp_tok;
						
						report->report_func(&info, report->report_ctx);
						
						AR_DestroyString(str);
						str = NULL;

						AR_ASSERT(*Lex_GetNextInput(match) != L'\0');

						
						if(Lex_TrySkipTo(match, L";") != AR_S_YES)/*r尝试跳到';'如果未成功，则跳到头一个非空白符*/
						{
								Lex_Skip(match);
						}

						Lex_ClearError(match);
						has_error = AR_S_YES;
						is_ok = AR_S_YES;
						continue;

INNER_INV_POINT:
						if(tok)
						{
								AR_DEL(tok);
								tok = NULL;
						}
						if(str)
						{
								AR_DestroyString(str);
								str = NULL;
						}

						goto END_POINT;
				}else /*各种错误，例如AR_E_NOMEM*/
				{
						goto END_POINT;
				}

				
		}		

		if(is_ok == AR_S_YES)
		{
				result = (cfgNode_t*)Parser_GetResult(parser_context);
				AR_ASSERT(result->type == CFG_CONFIG_T);

				if(result && !result->config.has_error)
				{
						result->config.has_error = has_error == AR_S_YES ? false : true;
				}
		}

END_POINT:

		if(result != NULL)
		{
				result->config.remain_data = (void*)psr_data.normal_str_pool;
				psr_data.normal_str_pool = NULL;
		}

		if(parser_context)
		{
				__destroy_parser_context(parser_context);
				parser_context = NULL;
		}

		if(match)
		{
				__destroy_lex_match(match);
				match = NULL;
		}

		ParserData_UnInit(&psr_data);
		
		return (cfgConfig_t*)result;

}

void			CFG_DestroyGrammarConfig(const cfgConfig_t *cfg)
{
		if(cfg->remain_data != NULL)
		{
				AR_DestroyStrTable((arStringTable_t*)cfg->remain_data);
				((cfgConfig_t*)cfg)->remain_data = NULL;
		}

		CFG_DestroyNode((cfgNode_t*)cfg);

}


/***************************************************************************/

cfgLexicalSet_t*		__create_lexical_set()
{
		return AR_NEW0(cfgLexicalSet_t);
}

void					__destroy_lexical_set(cfgLexicalSet_t *lx_set)
{
		AR_ASSERT(lx_set != NULL);

		if(lx_set->token_set)
		{
				AR_DEL(lx_set->token_set);
				lx_set->token_set = NULL;
		}

		if(lx_set)
		{
				AR_DEL(lx_set);
		}
}

static arStatus_t __insert_to_lexical_set(cfgLexicalSet_t *lx_set, const lexToken_t *tok)
{
		AR_ASSERT(lx_set != NULL && tok != NULL);

		if(lx_set->cnt == lx_set->cap)
		{
				size_t new_cap;
				lexToken_t	*new_token_set;

				new_cap = (lx_set->cap + 4)*2;
				new_token_set = AR_NEWARR(lexToken_t, new_cap);

				if(new_token_set == NULL)
				{
						return AR_E_NOMEM;
				}

				if(lx_set->cnt > 0)
				{
						AR_memcpy(new_token_set, lx_set->token_set, lx_set->cnt * sizeof(lexToken_t));
				}

				if(lx_set->token_set)
				{
						AR_DEL(lx_set->token_set);
						lx_set->token_set = NULL;
				}

				lx_set->cap = new_cap;
				lx_set->token_set = new_token_set;
		}

		lx_set->token_set[lx_set->cnt] = *tok;
		lx_set->cnt++;
		return AR_S_YES;
}



const cfgLexicalSet_t*		CFG_CollectLexicalSet(const wchar_t *gmr_txt)
{
		lexMatch_t		*match;
		cfgLexicalSet_t	*lx_set;
		arStatus_t		is_ok;
		lexToken_t		tok;

		AR_ASSERT(gmr_txt != NULL);

		is_ok = AR_S_YES;
		match = NULL;
		lx_set = NULL;


		match = __create_lex_match();
		lx_set = __create_lexical_set();

		if(match == NULL || lx_set == NULL)
		{
				goto END_POINT;
		}

		Lex_ResetInput(match, gmr_txt);

		


		while(is_ok == AR_S_YES)
		{
				is_ok = Lex_Match(match, &tok);

				if(is_ok == AR_S_YES)
				{
						is_ok = __insert_to_lexical_set(lx_set, &tok);

						if(is_ok != AR_S_YES)
						{
								goto END_POINT;
						}

						if(tok.value == CFG_LEXVAL_EOI)
						{
								break;
						}

				}else if(is_ok == AR_S_NO)
				{
						lx_set->has_error = true;
						AR_ASSERT(*Lex_GetNextInput(match) != L'\0');
						Lex_Skip(match);
						Lex_ClearError(match);
						is_ok = AR_S_YES;
						continue;
				}else /*有错误发生,比如存储分配失败*/
				{
						goto END_POINT;
				}
		}		

END_POINT:
		if(match)
		{
				__destroy_lex_match(match);
				match = NULL;
		}

		if(lx_set)
		{
				if(is_ok != AR_S_YES || lx_set->cnt == 0)
				{
						__destroy_lexical_set(lx_set);
						lx_set = NULL;
				}
		}

		return lx_set;
}

void						CFG_DestroyLexicalSet(const cfgLexicalSet_t *lexical_set)
{
		if(lexical_set)
		{
				__destroy_lexical_set((cfgLexicalSet_t*)lexical_set);
				lexical_set = NULL;
		}
}


void			CFG_Init()
{
		__init_parser_tag();
}

void			CFG_UnInit()
{
		__uninit_parser_tag();
}



AR_NAMESPACE_END
