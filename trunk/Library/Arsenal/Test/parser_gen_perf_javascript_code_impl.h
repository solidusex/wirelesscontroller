
#if(0)
static const wchar_t *__g_lex_name[] = {
L"delim = [ \\r\\n\\t]",
L"comment = /\\*([^\\*]|\\*+[^\\*/])*\\*+/",
L"comment_line = //[^\\n]*\\n",
L"digit = [0-9]",
L"number = {digit}+",
L"letter = [A-Z_a-z]",
L"hex_digit = [0-9a-fA-F]",
L"hex_literal = 0(x|X){hex_digit}+",
L"dec_literal = (0|[1-9][0-9]*)",
L"skip_lexem = {delim}|{comment}|{comment_line}",
L"escape_seq = (\\\\(\\x22|\\x27))",
L"string_dq = (\\x22({escape_seq}|[^\\x22])*\\x22)",
L"string_sq = \\x27({escape_seq}|[^\\x27])*\\x27",
L"string_literal = {string_sq}|{string_dq}",
L"keyword_lhd = [A-Z_a-z0-9]"
};

#define __NAME_COUNT__ ((size_t)15)



enum{
TOK_DELIM_ID = 257,
TOK_NUMBER = 258,
TOK_STRING_LITERAL = 259,
TOK_IDENTIFIER = 260,
TOK_SWITCH = 261,
TOK_FOR = 262,
TOK_RETURN = 263,
TOK_DO = 264,
TOK_WHILE = 265,
TOK_IF = 266,
TOK_ELSE = 267,
TOK_TRUE = 268,
TOK_FALSE = 269,
TOK_THIS = 270,
TOK_NULL = 271,
TOK_CONST = 272,
TOK_IN = 273,
TOK_NEW = 274,
TOK_DELETE = 275,
TOK_TYPEOF = 276,
TOK_FUNCTION = 277,
TOK_VAR = 278,
TOK_WITH = 279,
TOK_INSTANCEOF = 280,
TOK_DEBUGGER = 281,
TOK_TRY = 282,
TOK_CATCH = 283,
TOK_FINALLY = 284,
TOK_THROW = 285,
TOK_CONTINUE = 286,
TOK_DEFAULT = 287,
TOK_CASE = 288,
TOK_BREAK = 289,
TOK_VOID = 290,
TOK_RIGHT_ASSIGN = 291,
TOK_LEFT_ASSIGN = 292,
TOK_UNSIGNED_RIGHT_ASSIGN = 293,
TOK_UNSIGNED_RIGHT = 294,
TOK_STRICT_EQ_OP = 295,
TOK_STRICT_NE_OP = 296,
TOK_ADD_ASSIGN = 297,
TOK_SUB_ASSIGN = 298,
TOK_MUL_ASSIGN = 299,
TOK_DIV_ASSIGN = 300,
TOK_MOD_ASSIGN = 301,
TOK_AND_ASSIGN = 302,
TOK_XOR_ASSIGN = 303,
TOK_OR_ASSIGN = 304,
TOK_RIGHT_OP = 305,
TOK_LEFT_OP = 306,
TOK_INC_OP = 307,
TOK_DEC_OP = 308,
TOK_AND_OP = 309,
TOK_OR_OP = 310,
TOK_LE_OP = 311,
TOK_GE_OP = 312,
TOK_EQ_OP = 313,
TOK_NE_OP = 314,
TOK_LESS_OP = 315,
TOK_GREATER_OP = 316,
TOK_SEMICOLON = 317,
TOK_L_BRACES = 318,
TOK_R_BRACES = 319,
TOK_COMMA = 320,
TOK_COLON = 321,
TOK_ASSIGN = 322,
TOK_L_PAREN = 323,
TOK_R_PAREN = 324,
TOK_L_SQUARE = 325,
TOK_R_SQUARE = 326,
TOK_DOT = 327,
TOK_AND = 328,
TOK_NOT = 329,
TOK_TILDE = 330,
TOK_ADD = 331,
TOK_SUB = 332,
TOK_MUL = 333,
TOK_DIV = 334,
TOK_MOD = 335,
TOK_XOR = 336,
TOK_OR = 337,
TOK_QUEST = 338,
};




static struct {const wchar_t *name;
size_t tokval;
size_t lex_prec;
const wchar_t *regex;
bool_t skip;
psrTermFunc_t leaf;
}__g_term_pattern[] =  {
{NULL, TOK_DELIM_ID,1, L"{delim}+|{comment}+|{comment_line}+", true, NULL},
{L"NUMBER", TOK_NUMBER, 2, L"({hex_literal}|{dec_literal})(?!{keyword_lhd})", false, NULL},
{L"STRING_LITERAL", TOK_STRING_LITERAL, 0, L"{string_literal}", false, NULL},
{L"IDENTIFIER", TOK_IDENTIFIER, 0, L"{letter}({letter}|{digit})*", false, NULL},
{L"switch", TOK_SWITCH, 1, L"\"switch\"(?!{keyword_lhd})", false, NULL},
{L"for", TOK_FOR, 1, L"\"for\"(?!{keyword_lhd})", false, NULL},
{L"return", TOK_RETURN, 1, L"\"return\"(?!{keyword_lhd})", false, NULL},
{L"do", TOK_DO, 1, L"\"do\"(?!{keyword_lhd})", false, NULL},
{L"while", TOK_WHILE, 1, L"\"while\"(?!{keyword_lhd})", false, NULL},
{L"if", TOK_IF, 1, L"\"if\"(?!{keyword_lhd})", false, NULL},
{L"else", TOK_ELSE, 1, L"\"else\"(?!{keyword_lhd})", false, NULL},
{L"true", TOK_TRUE, 1, L"\"true\"(?!{keyword_lhd})", false, NULL},
{L"false", TOK_FALSE, 1, L"\"false\"(?!{keyword_lhd})", false, NULL},
{L"this", TOK_THIS, 1, L"\"this\"(?!{keyword_lhd})", false, NULL},
{L"null", TOK_NULL, 1, L"\"null\"(?!{keyword_lhd})", false, NULL},
{L"const", TOK_CONST, 1, L"\"const\"(?!{keyword_lhd})", false, NULL},
{L"in", TOK_IN, 1, L"\"in\"(?!{keyword_lhd})", false, NULL},
{L"new", TOK_NEW, 1, L"\"new\"(?!{keyword_lhd})", false, NULL},
{L"delete", TOK_DELETE, 1, L"\"delete\"(?!{keyword_lhd})", false, NULL},
{L"typeof", TOK_TYPEOF, 1, L"\"typeof\"(?!{keyword_lhd})", false, NULL},
{L"function", TOK_FUNCTION, 1, L"\"function\"(?!{keyword_lhd})", false, NULL},
{L"var", TOK_VAR, 1, L"\"var\"(?!{keyword_lhd})", false, NULL},
{L"with", TOK_WITH, 1, L"\"with\"(?!{keyword_lhd})", false, NULL},
{L"instanceof", TOK_INSTANCEOF, 1, L"\"instanceof\"(?!{keyword_lhd})", false, NULL},
{L"debugger", TOK_DEBUGGER, 1, L"\"debugger\"(?!{keyword_lhd})", false, NULL},
{L"try", TOK_TRY, 1, L"\"try\"(?!{keyword_lhd})", false, NULL},
{L"catch", TOK_CATCH, 1, L"\"catch\"(?!{keyword_lhd})", false, NULL},
{L"finally", TOK_FINALLY, 1, L"\"finally\"(?!{keyword_lhd})", false, NULL},
{L"throw", TOK_THROW, 1, L"\"throw\"(?!{keyword_lhd})", false, NULL},
{L"continue", TOK_CONTINUE, 1, L"\"continue\"(?!{keyword_lhd})", false, NULL},
{L"default", TOK_DEFAULT, 1, L"\"default\"(?!{keyword_lhd})", false, NULL},
{L"case", TOK_CASE, 1, L"\"case\"(?!{keyword_lhd})", false, NULL},
{L"break", TOK_BREAK, 1, L"\"break\"(?!{keyword_lhd})", false, NULL},
{L"void", TOK_VOID, 1, L"\"void\"(?!{keyword_lhd})", false, NULL},
{L">>=", TOK_RIGHT_ASSIGN, 2, L"\">>=\"", false, NULL},
{L"<<=", TOK_LEFT_ASSIGN, 2, L"\"<<=\"", false, NULL},
{L">>>=", TOK_UNSIGNED_RIGHT_ASSIGN, 3, L"\">>>=\"", false, NULL},
{L">>>", TOK_UNSIGNED_RIGHT, 2, L"\">>>\"", false, NULL},
{L"===", TOK_STRICT_EQ_OP, 2, L"\"===\"", false, NULL},
{L"!==", TOK_STRICT_NE_OP, 2, L"\"!==\"", false, NULL},
{L"+=", TOK_ADD_ASSIGN, 1, L"\"+=\"", false, NULL},
{L"-=", TOK_SUB_ASSIGN, 1, L"\"-=\"", false, NULL},
{L"*=", TOK_MUL_ASSIGN, 1, L"\"*=\"", false, NULL},
{L"/=", TOK_DIV_ASSIGN, 1, L"\"/=\"", false, NULL},
{L"%=", TOK_MOD_ASSIGN, 1, L"\"%=\"", false, NULL},
{L"&=", TOK_AND_ASSIGN, 1, L"\"&=\"", false, NULL},
{L"^=", TOK_XOR_ASSIGN, 1, L"\"^=\"", false, NULL},
{L"|=", TOK_OR_ASSIGN, 1, L"\"|=\"", false, NULL},
{L">>", TOK_RIGHT_OP, 1, L"\">>\"", false, NULL},
{L"<<", TOK_LEFT_OP, 1, L"\"<<\"", false, NULL},
{L"++", TOK_INC_OP, 1, L"\"++\"", false, NULL},
{L"--", TOK_DEC_OP, 1, L"\"--\"", false, NULL},
{L"&&", TOK_AND_OP, 1, L"\"&&\"", false, NULL},
{L"||", TOK_OR_OP, 1, L"\"||\"", false, NULL},
{L"<=", TOK_LE_OP, 1, L"\"<=\"", false, NULL},
{L">=", TOK_GE_OP, 1, L"\">=\"", false, NULL},
{L"==", TOK_EQ_OP, 1, L"\"==\"", false, NULL},
{L"!=", TOK_NE_OP, 1, L"\"!=\"", false, NULL},
{L"<", TOK_LESS_OP, 0, L"\"<\"", false, NULL},
{L">", TOK_GREATER_OP, 0, L"\">\"", false, NULL},
{L";", TOK_SEMICOLON, 0, L"\";\"", false, NULL},
{L"{", TOK_L_BRACES, 0, L"\"{\"", false, NULL},
{L"}", TOK_R_BRACES, 0, L"\"}\"", false, NULL},
{L",", TOK_COMMA, 0, L"\",\"", false, NULL},
{L":", TOK_COLON, 0, L"\":\"", false, NULL},
{L"=", TOK_ASSIGN, 0, L"\"=\"", false, NULL},
{L"(", TOK_L_PAREN, 0, L"\"(\"", false, NULL},
{L")", TOK_R_PAREN, 0, L"\")\"", false, NULL},
{L"[", TOK_L_SQUARE, 0, L"\"[\"", false, NULL},
{L"]", TOK_R_SQUARE, 0, L"\"]\"", false, NULL},
{L".", TOK_DOT, 0, L"\".\"", false, NULL},
{L"&", TOK_AND, 0, L"\"&\"", false, NULL},
{L"!", TOK_NOT, 0, L"\"!\"", false, NULL},
{L"~", TOK_TILDE, 0, L"\"~\"", false, NULL},
{L"+", TOK_ADD, 0, L"\"+\"", false, NULL},
{L"-", TOK_SUB, 0, L"\"-\"", false, NULL},
{L"*", TOK_MUL, 0, L"\"*\"", false, NULL},
{L"/", TOK_DIV, 0, L"\"/\"", false, NULL},
{L"%", TOK_MOD, 0, L"\"%\"", false, NULL},
{L"^", TOK_XOR, 0, L"\"^\"", false, NULL},
{L"|", TOK_OR, 0, L"\"|\"", false, NULL},
{L"?", TOK_QUEST, 0, L"\"?\"", false, NULL},
{L"CFG_LEXVAL_EOI", 0, 2, L"$", false, NULL}
};

#define __TERM_COUNT__ ((size_t)83)

static struct {const wchar_t *name; size_t tokval; size_t prec_level; psrAssocType_t	assoc;}__g_prec_pattern[] =  {
{L"IF_WITHOUT_ELSE", 339,1, PARSER_ASSOC_NONASSOC},
{L"else", TOK_ELSE,2, PARSER_ASSOC_NONASSOC}
};

#define __PREC_COUNT__ ((size_t)2)

/*Literal	:	null */
/*Literal	:	true */
/*Literal	:	false */
/*Literal	:	NUMBER */
/*Literal	:	STRING_LITERAL */
static psrNode_t* AR_STDCALL handle_Literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Property	:	IDENTIFIER : AssignmentExpr */
/*Property	:	STRING_LITERAL : AssignmentExpr */
/*Property	:	NUMBER : AssignmentExpr */
/*Property	:	IDENTIFIER IDENTIFIER ( ) { FunctionBody } */
/*Property	:	IDENTIFIER IDENTIFIER ( FormalParameterList ) { FunctionBody } */
static psrNode_t* AR_STDCALL handle_Property(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PropertyList	:	Property */
/*PropertyList	:	PropertyList , Property */
static psrNode_t* AR_STDCALL handle_PropertyList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PrimaryExpr	:	PrimaryExprNoBrace */
/*PrimaryExpr	:	{ } */
/*PrimaryExpr	:	{ PropertyList } */
/*PrimaryExpr	:	{ PropertyList , } */
static psrNode_t* AR_STDCALL handle_PrimaryExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PrimaryExprNoBrace	:	this */
/*PrimaryExprNoBrace	:	Literal */
/*PrimaryExprNoBrace	:	ArrayLiteral */
/*PrimaryExprNoBrace	:	IDENTIFIER */
/*PrimaryExprNoBrace	:	( Expr ) */
static psrNode_t* AR_STDCALL handle_PrimaryExprNoBrace(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ArrayLiteral	:	[ ElisionOpt ] */
/*ArrayLiteral	:	[ ElementList ] */
/*ArrayLiteral	:	[ ElementList , ElisionOpt ] */
static psrNode_t* AR_STDCALL handle_ArrayLiteral(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ElementList	:	ElisionOpt AssignmentExpr */
/*ElementList	:	ElementList , ElisionOpt AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ElementList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ElisionOpt	:	 */
/*ElisionOpt	:	Elision */
static psrNode_t* AR_STDCALL handle_ElisionOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Elision	:	, */
/*Elision	:	Elision , */
static psrNode_t* AR_STDCALL handle_Elision(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MemberExpr	:	PrimaryExpr */
/*MemberExpr	:	FunctionExpr */
/*MemberExpr	:	MemberExpr [ Expr ] */
/*MemberExpr	:	MemberExpr . IDENTIFIER */
/*MemberExpr	:	new MemberExpr Arguments */
static psrNode_t* AR_STDCALL handle_MemberExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MemberExprNoBF	:	PrimaryExprNoBrace */
/*MemberExprNoBF	:	MemberExprNoBF [ Expr ] */
/*MemberExprNoBF	:	MemberExprNoBF . IDENTIFIER */
/*MemberExprNoBF	:	new MemberExpr Arguments */
static psrNode_t* AR_STDCALL handle_MemberExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*NewExpr	:	MemberExpr */
/*NewExpr	:	new NewExpr */
static psrNode_t* AR_STDCALL handle_NewExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*NewExprNoBF	:	MemberExprNoBF */
/*NewExprNoBF	:	new NewExpr */
static psrNode_t* AR_STDCALL handle_NewExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CallExpr	:	MemberExpr Arguments */
/*CallExpr	:	CallExpr Arguments */
/*CallExpr	:	CallExpr [ Expr ] */
/*CallExpr	:	CallExpr . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CallExprNoBF	:	MemberExprNoBF Arguments */
/*CallExprNoBF	:	CallExprNoBF Arguments */
/*CallExprNoBF	:	CallExprNoBF [ Expr ] */
/*CallExprNoBF	:	CallExprNoBF . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Arguments	:	( ) */
/*Arguments	:	( ArgumentList ) */
static psrNode_t* AR_STDCALL handle_Arguments(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ArgumentList	:	AssignmentExpr */
/*ArgumentList	:	ArgumentList , AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ArgumentList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LeftHandSideExpr	:	NewExpr */
/*LeftHandSideExpr	:	CallExpr */
static psrNode_t* AR_STDCALL handle_LeftHandSideExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LeftHandSideExprNoBF	:	NewExprNoBF */
/*LeftHandSideExprNoBF	:	CallExprNoBF */
static psrNode_t* AR_STDCALL handle_LeftHandSideExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PostfixExpr	:	LeftHandSideExpr */
/*PostfixExpr	:	LeftHandSideExpr ++ */
/*PostfixExpr	:	LeftHandSideExpr -- */
static psrNode_t* AR_STDCALL handle_PostfixExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PostfixExprNoBF	:	LeftHandSideExprNoBF */
/*PostfixExprNoBF	:	LeftHandSideExprNoBF ++ */
/*PostfixExprNoBF	:	LeftHandSideExprNoBF -- */
static psrNode_t* AR_STDCALL handle_PostfixExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*UnaryExprCommon	:	delete UnaryExpr */
/*UnaryExprCommon	:	void UnaryExpr */
/*UnaryExprCommon	:	typeof UnaryExpr */
/*UnaryExprCommon	:	++ UnaryExpr */
/*UnaryExprCommon	:	-- UnaryExpr */
/*UnaryExprCommon	:	+ UnaryExpr */
/*UnaryExprCommon	:	- UnaryExpr */
/*UnaryExprCommon	:	~ UnaryExpr */
/*UnaryExprCommon	:	! UnaryExpr */
static psrNode_t* AR_STDCALL handle_UnaryExprCommon(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*UnaryExpr	:	PostfixExpr */
/*UnaryExpr	:	UnaryExprCommon */
static psrNode_t* AR_STDCALL handle_UnaryExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*UnaryExprNoBF	:	PostfixExprNoBF */
/*UnaryExprNoBF	:	UnaryExprCommon */
static psrNode_t* AR_STDCALL handle_UnaryExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MultiplicativeExpr	:	UnaryExpr */
/*MultiplicativeExpr	:	MultiplicativeExpr * UnaryExpr */
/*MultiplicativeExpr	:	MultiplicativeExpr / UnaryExpr */
/*MultiplicativeExpr	:	MultiplicativeExpr % UnaryExpr */
static psrNode_t* AR_STDCALL handle_MultiplicativeExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MultiplicativeExprNoBF	:	UnaryExprNoBF */
/*MultiplicativeExprNoBF	:	MultiplicativeExprNoBF * UnaryExpr */
/*MultiplicativeExprNoBF	:	MultiplicativeExprNoBF / UnaryExpr */
/*MultiplicativeExprNoBF	:	MultiplicativeExprNoBF % UnaryExpr */
static psrNode_t* AR_STDCALL handle_MultiplicativeExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AdditiveExpr	:	MultiplicativeExpr */
/*AdditiveExpr	:	AdditiveExpr + MultiplicativeExpr */
/*AdditiveExpr	:	AdditiveExpr - MultiplicativeExpr */
static psrNode_t* AR_STDCALL handle_AdditiveExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AdditiveExprNoBF	:	MultiplicativeExprNoBF */
/*AdditiveExprNoBF	:	AdditiveExprNoBF + MultiplicativeExpr */
/*AdditiveExprNoBF	:	AdditiveExprNoBF - MultiplicativeExpr */
static psrNode_t* AR_STDCALL handle_AdditiveExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ShiftExpr	:	AdditiveExpr */
/*ShiftExpr	:	ShiftExpr << AdditiveExpr */
/*ShiftExpr	:	ShiftExpr >> AdditiveExpr */
/*ShiftExpr	:	ShiftExpr >>> AdditiveExpr */
static psrNode_t* AR_STDCALL handle_ShiftExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ShiftExprNoBF	:	AdditiveExprNoBF */
/*ShiftExprNoBF	:	ShiftExprNoBF << AdditiveExpr */
/*ShiftExprNoBF	:	ShiftExprNoBF >> AdditiveExpr */
/*ShiftExprNoBF	:	ShiftExprNoBF >>> AdditiveExpr */
static psrNode_t* AR_STDCALL handle_ShiftExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*RelationalExpr	:	ShiftExpr */
/*RelationalExpr	:	RelationalExpr < ShiftExpr */
/*RelationalExpr	:	RelationalExpr > ShiftExpr */
/*RelationalExpr	:	RelationalExpr <= ShiftExpr */
/*RelationalExpr	:	RelationalExpr >= ShiftExpr */
/*RelationalExpr	:	RelationalExpr instanceof ShiftExpr */
/*RelationalExpr	:	RelationalExpr in ShiftExpr */
static psrNode_t* AR_STDCALL handle_RelationalExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*RelationalExprNoIn	:	ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn < ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn > ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn <= ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn >= ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn instanceof ShiftExpr */
static psrNode_t* AR_STDCALL handle_RelationalExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*RelationalExprNoBF	:	ShiftExprNoBF */
/*RelationalExprNoBF	:	RelationalExprNoBF < ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF > ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF <= ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF >= ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF instanceof ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF in ShiftExpr */
static psrNode_t* AR_STDCALL handle_RelationalExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EqualityExpr	:	RelationalExpr */
/*EqualityExpr	:	EqualityExpr == RelationalExpr */
/*EqualityExpr	:	EqualityExpr != RelationalExpr */
/*EqualityExpr	:	EqualityExpr === RelationalExpr */
/*EqualityExpr	:	EqualityExpr !== RelationalExpr */
static psrNode_t* AR_STDCALL handle_EqualityExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EqualityExprNoIn	:	RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn == RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn != RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn === RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn !== RelationalExprNoIn */
static psrNode_t* AR_STDCALL handle_EqualityExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EqualityExprNoBF	:	RelationalExprNoBF */
/*EqualityExprNoBF	:	EqualityExprNoBF == RelationalExpr */
/*EqualityExprNoBF	:	EqualityExprNoBF != RelationalExpr */
/*EqualityExprNoBF	:	EqualityExprNoBF === RelationalExpr */
/*EqualityExprNoBF	:	EqualityExprNoBF !== RelationalExpr */
static psrNode_t* AR_STDCALL handle_EqualityExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseANDExpr	:	EqualityExpr */
/*BitwiseANDExpr	:	BitwiseANDExpr & EqualityExpr */
static psrNode_t* AR_STDCALL handle_BitwiseANDExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseANDExprNoIn	:	EqualityExprNoIn */
/*BitwiseANDExprNoIn	:	BitwiseANDExprNoIn & EqualityExprNoIn */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseANDExprNoBF	:	EqualityExprNoBF */
/*BitwiseANDExprNoBF	:	BitwiseANDExprNoBF & EqualityExpr */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseXORExpr	:	BitwiseANDExpr */
/*BitwiseXORExpr	:	BitwiseXORExpr ^ BitwiseANDExpr */
static psrNode_t* AR_STDCALL handle_BitwiseXORExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseXORExprNoIn	:	BitwiseANDExprNoIn */
/*BitwiseXORExprNoIn	:	BitwiseXORExprNoIn ^ BitwiseANDExprNoIn */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseXORExprNoBF	:	BitwiseANDExprNoBF */
/*BitwiseXORExprNoBF	:	BitwiseXORExprNoBF ^ BitwiseANDExpr */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseORExpr	:	BitwiseXORExpr */
/*BitwiseORExpr	:	BitwiseORExpr | BitwiseXORExpr */
static psrNode_t* AR_STDCALL handle_BitwiseORExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseORExprNoIn	:	BitwiseXORExprNoIn */
/*BitwiseORExprNoIn	:	BitwiseORExprNoIn | BitwiseXORExprNoIn */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseORExprNoBF	:	BitwiseXORExprNoBF */
/*BitwiseORExprNoBF	:	BitwiseORExprNoBF | BitwiseXORExpr */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalANDExpr	:	BitwiseORExpr */
/*LogicalANDExpr	:	LogicalANDExpr && BitwiseORExpr */
static psrNode_t* AR_STDCALL handle_LogicalANDExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalANDExprNoIn	:	BitwiseORExprNoIn */
/*LogicalANDExprNoIn	:	LogicalANDExprNoIn && BitwiseORExprNoIn */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalANDExprNoBF	:	BitwiseORExprNoBF */
/*LogicalANDExprNoBF	:	LogicalANDExprNoBF && BitwiseORExpr */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalORExpr	:	LogicalANDExpr */
/*LogicalORExpr	:	LogicalORExpr || LogicalANDExpr */
static psrNode_t* AR_STDCALL handle_LogicalORExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalORExprNoIn	:	LogicalANDExprNoIn */
/*LogicalORExprNoIn	:	LogicalORExprNoIn || LogicalANDExprNoIn */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalORExprNoBF	:	LogicalANDExprNoBF */
/*LogicalORExprNoBF	:	LogicalORExprNoBF || LogicalANDExpr */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConditionalExpr	:	LogicalORExpr */
/*ConditionalExpr	:	LogicalORExpr ? AssignmentExpr : AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ConditionalExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConditionalExprNoIn	:	LogicalORExprNoIn */
/*ConditionalExprNoIn	:	LogicalORExprNoIn ? AssignmentExprNoIn : AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConditionalExprNoBF	:	LogicalORExprNoBF */
/*ConditionalExprNoBF	:	LogicalORExprNoBF ? AssignmentExpr : AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentExpr	:	ConditionalExpr */
/*AssignmentExpr	:	LeftHandSideExpr AssignmentOperator AssignmentExpr */
static psrNode_t* AR_STDCALL handle_AssignmentExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentExprNoIn	:	ConditionalExprNoIn */
/*AssignmentExprNoIn	:	LeftHandSideExpr AssignmentOperator AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentExprNoBF	:	ConditionalExprNoBF */
/*AssignmentExprNoBF	:	LeftHandSideExprNoBF AssignmentOperator AssignmentExpr */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentOperator	:	= */
/*AssignmentOperator	:	+= */
/*AssignmentOperator	:	-= */
/*AssignmentOperator	:	*= */
/*AssignmentOperator	:	/= */
/*AssignmentOperator	:	<<= */
/*AssignmentOperator	:	>>= */
/*AssignmentOperator	:	>>>= */
/*AssignmentOperator	:	&= */
/*AssignmentOperator	:	^= */
/*AssignmentOperator	:	|= */
/*AssignmentOperator	:	%= */
static psrNode_t* AR_STDCALL handle_AssignmentOperator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Expr	:	AssignmentExpr */
/*Expr	:	Expr , AssignmentExpr */
static psrNode_t* AR_STDCALL handle_Expr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprNoIn	:	AssignmentExprNoIn */
/*ExprNoIn	:	ExprNoIn , AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_ExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprNoBF	:	AssignmentExprNoBF */
/*ExprNoBF	:	ExprNoBF , AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Statement	:	Block */
/*Statement	:	VariableStatement */
/*Statement	:	ConstStatement */
/*Statement	:	FunctionDeclaration */
/*Statement	:	EmptyStatement */
/*Statement	:	ExprStatement */
/*Statement	:	IfStatement */
/*Statement	:	IterationStatement */
/*Statement	:	ContinueStatement */
/*Statement	:	BreakStatement */
/*Statement	:	ReturnStatement */
/*Statement	:	WithStatement */
/*Statement	:	SwitchStatement */
/*Statement	:	LabelledStatement */
/*Statement	:	ThrowStatement */
/*Statement	:	TryStatement */
/*Statement	:	DebuggerStatement */
static psrNode_t* AR_STDCALL handle_Statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Block	:	{ } */
/*Block	:	{ SourceElements } */
static psrNode_t* AR_STDCALL handle_Block(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*VariableStatement	:	var VariableDeclarationList ; */
/*VariableStatement	:	var VariableDeclarationList error */
static psrNode_t* AR_STDCALL handle_VariableStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*VariableDeclarationList	:	IDENTIFIER */
/*VariableDeclarationList	:	IDENTIFIER Initializer */
/*VariableDeclarationList	:	VariableDeclarationList , IDENTIFIER */
/*VariableDeclarationList	:	VariableDeclarationList , IDENTIFIER Initializer */
static psrNode_t* AR_STDCALL handle_VariableDeclarationList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*VariableDeclarationListNoIn	:	IDENTIFIER */
/*VariableDeclarationListNoIn	:	IDENTIFIER InitializerNoIn */
/*VariableDeclarationListNoIn	:	VariableDeclarationListNoIn , IDENTIFIER */
/*VariableDeclarationListNoIn	:	VariableDeclarationListNoIn , IDENTIFIER InitializerNoIn */
static psrNode_t* AR_STDCALL handle_VariableDeclarationListNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConstStatement	:	const ConstDeclarationList ; */
/*ConstStatement	:	const ConstDeclarationList error */
static psrNode_t* AR_STDCALL handle_ConstStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConstDeclarationList	:	ConstDeclaration */
/*ConstDeclarationList	:	ConstDeclarationList , ConstDeclaration */
static psrNode_t* AR_STDCALL handle_ConstDeclarationList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConstDeclaration	:	IDENTIFIER */
/*ConstDeclaration	:	IDENTIFIER Initializer */
static psrNode_t* AR_STDCALL handle_ConstDeclaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Initializer	:	= AssignmentExpr */
static psrNode_t* AR_STDCALL handle_Initializer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*InitializerNoIn	:	= AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_InitializerNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EmptyStatement	:	; */
static psrNode_t* AR_STDCALL handle_EmptyStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprStatement	:	ExprNoBF ; */
/*ExprStatement	:	ExprNoBF error */
static psrNode_t* AR_STDCALL handle_ExprStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*IfStatement	:	if ( Expr ) Statement */
/*IfStatement	:	if ( Expr ) Statement else Statement */
static psrNode_t* AR_STDCALL handle_IfStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*IterationStatement	:	do Statement while ( Expr ) ; */
/*IterationStatement	:	do Statement while ( Expr ) error */
/*IterationStatement	:	while ( Expr ) Statement */
/*IterationStatement	:	for ( ExprNoInOpt ; ExprOpt ; ExprOpt ) Statement */
/*IterationStatement	:	for ( var VariableDeclarationListNoIn ; ExprOpt ; ExprOpt ) Statement */
/*IterationStatement	:	for ( LeftHandSideExpr in Expr ) Statement */
/*IterationStatement	:	for ( var IDENTIFIER in Expr ) Statement */
/*IterationStatement	:	for ( var IDENTIFIER InitializerNoIn in Expr ) Statement */
static psrNode_t* AR_STDCALL handle_IterationStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprOpt	:	 */
/*ExprOpt	:	Expr */
static psrNode_t* AR_STDCALL handle_ExprOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprNoInOpt	:	 */
/*ExprNoInOpt	:	ExprNoIn */
static psrNode_t* AR_STDCALL handle_ExprNoInOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ContinueStatement	:	continue ; */
/*ContinueStatement	:	continue error */
/*ContinueStatement	:	continue IDENTIFIER ; */
/*ContinueStatement	:	continue IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_ContinueStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BreakStatement	:	break ; */
/*BreakStatement	:	break error */
/*BreakStatement	:	break IDENTIFIER ; */
/*BreakStatement	:	break IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_BreakStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ReturnStatement	:	return ; */
/*ReturnStatement	:	return error */
/*ReturnStatement	:	return Expr ; */
/*ReturnStatement	:	return Expr error */
static psrNode_t* AR_STDCALL handle_ReturnStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*WithStatement	:	with ( Expr ) Statement */
static psrNode_t* AR_STDCALL handle_WithStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*SwitchStatement	:	switch ( Expr ) CaseBlock */
static psrNode_t* AR_STDCALL handle_SwitchStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseBlock	:	{ CaseClausesOpt } */
/*CaseBlock	:	{ CaseClausesOpt DefaultClause CaseClausesOpt } */
static psrNode_t* AR_STDCALL handle_CaseBlock(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseClausesOpt	:	 */
/*CaseClausesOpt	:	CaseClauses */
static psrNode_t* AR_STDCALL handle_CaseClausesOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseClauses	:	CaseClause */
/*CaseClauses	:	CaseClauses CaseClause */
static psrNode_t* AR_STDCALL handle_CaseClauses(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseClause	:	case Expr : */
/*CaseClause	:	case Expr : SourceElements */
static psrNode_t* AR_STDCALL handle_CaseClause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*DefaultClause	:	default : */
/*DefaultClause	:	default : SourceElements */
static psrNode_t* AR_STDCALL handle_DefaultClause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LabelledStatement	:	IDENTIFIER : Statement */
static psrNode_t* AR_STDCALL handle_LabelledStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ThrowStatement	:	throw Expr ; */
/*ThrowStatement	:	throw Expr error */
static psrNode_t* AR_STDCALL handle_ThrowStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*TryStatement	:	try Block finally Block */
/*TryStatement	:	try Block catch ( IDENTIFIER ) Block */
/*TryStatement	:	try Block catch ( IDENTIFIER ) Block finally Block */
static psrNode_t* AR_STDCALL handle_TryStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*DebuggerStatement	:	debugger ; */
/*DebuggerStatement	:	debugger error */
static psrNode_t* AR_STDCALL handle_DebuggerStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FunctionDeclaration	:	function IDENTIFIER ( ) { FunctionBody } */
/*FunctionDeclaration	:	function IDENTIFIER ( FormalParameterList ) { FunctionBody } */
static psrNode_t* AR_STDCALL handle_FunctionDeclaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FunctionExpr	:	function ( ) { FunctionBody } */
/*FunctionExpr	:	function ( FormalParameterList ) { FunctionBody } */
/*FunctionExpr	:	function IDENTIFIER ( ) { FunctionBody } */
/*FunctionExpr	:	function IDENTIFIER ( FormalParameterList ) { FunctionBody } */
static psrNode_t* AR_STDCALL handle_FunctionExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FormalParameterList	:	IDENTIFIER */
/*FormalParameterList	:	FormalParameterList , IDENTIFIER */
static psrNode_t* AR_STDCALL handle_FormalParameterList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FunctionBody	:	 */
/*FunctionBody	:	SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_FunctionBody(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Program	:	 */
/*Program	:	SourceElements */
static psrNode_t* AR_STDCALL handle_Program(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*SourceElements	:	Statement */
/*SourceElements	:	SourceElements Statement */
static psrNode_t* AR_STDCALL handle_SourceElements(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Literal_NoNode	:	null */
/*Literal_NoNode	:	true */
/*Literal_NoNode	:	false */
/*Literal_NoNode	:	NUMBER */
/*Literal_NoNode	:	STRING_LITERAL */
static psrNode_t* AR_STDCALL handle_Literal_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Property_NoNode	:	IDENTIFIER : AssignmentExpr_NoNode */
/*Property_NoNode	:	STRING_LITERAL : AssignmentExpr_NoNode */
/*Property_NoNode	:	NUMBER : AssignmentExpr_NoNode */
/*Property_NoNode	:	IDENTIFIER IDENTIFIER ( ) { FunctionBody_NoNode } */
/*Property_NoNode	:	IDENTIFIER IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
static psrNode_t* AR_STDCALL handle_Property_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PropertyList_NoNode	:	Property_NoNode */
/*PropertyList_NoNode	:	PropertyList_NoNode , Property_NoNode */
static psrNode_t* AR_STDCALL handle_PropertyList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PrimaryExpr_NoNode	:	PrimaryExprNoBrace_NoNode */
/*PrimaryExpr_NoNode	:	{ } */
/*PrimaryExpr_NoNode	:	{ PropertyList_NoNode } */
/*PrimaryExpr_NoNode	:	{ PropertyList_NoNode , } */
static psrNode_t* AR_STDCALL handle_PrimaryExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PrimaryExprNoBrace_NoNode	:	this */
/*PrimaryExprNoBrace_NoNode	:	Literal_NoNode */
/*PrimaryExprNoBrace_NoNode	:	ArrayLiteral_NoNode */
/*PrimaryExprNoBrace_NoNode	:	IDENTIFIER */
/*PrimaryExprNoBrace_NoNode	:	( Expr_NoNode ) */
static psrNode_t* AR_STDCALL handle_PrimaryExprNoBrace_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ArrayLiteral_NoNode	:	[ ElisionOpt_NoNode ] */
/*ArrayLiteral_NoNode	:	[ ElementList_NoNode ] */
/*ArrayLiteral_NoNode	:	[ ElementList_NoNode , ElisionOpt_NoNode ] */
static psrNode_t* AR_STDCALL handle_ArrayLiteral_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ElementList_NoNode	:	ElisionOpt_NoNode AssignmentExpr_NoNode */
/*ElementList_NoNode	:	ElementList_NoNode , ElisionOpt_NoNode AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ElementList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ElisionOpt_NoNode	:	 */
/*ElisionOpt_NoNode	:	Elision_NoNode */
static psrNode_t* AR_STDCALL handle_ElisionOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Elision_NoNode	:	, */
/*Elision_NoNode	:	Elision_NoNode , */
static psrNode_t* AR_STDCALL handle_Elision_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MemberExpr_NoNode	:	PrimaryExpr_NoNode */
/*MemberExpr_NoNode	:	FunctionExpr_NoNode */
/*MemberExpr_NoNode	:	MemberExpr_NoNode [ Expr_NoNode ] */
/*MemberExpr_NoNode	:	MemberExpr_NoNode . IDENTIFIER */
/*MemberExpr_NoNode	:	new MemberExpr_NoNode Arguments_NoNode */
static psrNode_t* AR_STDCALL handle_MemberExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MemberExprNoBF_NoNode	:	PrimaryExprNoBrace_NoNode */
/*MemberExprNoBF_NoNode	:	MemberExprNoBF_NoNode [ Expr_NoNode ] */
/*MemberExprNoBF_NoNode	:	MemberExprNoBF_NoNode . IDENTIFIER */
/*MemberExprNoBF_NoNode	:	new MemberExpr_NoNode Arguments_NoNode */
static psrNode_t* AR_STDCALL handle_MemberExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*NewExpr_NoNode	:	MemberExpr_NoNode */
/*NewExpr_NoNode	:	new NewExpr_NoNode */
static psrNode_t* AR_STDCALL handle_NewExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*NewExprNoBF_NoNode	:	MemberExprNoBF_NoNode */
/*NewExprNoBF_NoNode	:	new NewExpr_NoNode */
static psrNode_t* AR_STDCALL handle_NewExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CallExpr_NoNode	:	MemberExpr_NoNode Arguments_NoNode */
/*CallExpr_NoNode	:	CallExpr_NoNode Arguments_NoNode */
/*CallExpr_NoNode	:	CallExpr_NoNode [ Expr_NoNode ] */
/*CallExpr_NoNode	:	CallExpr_NoNode . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CallExprNoBF_NoNode	:	MemberExprNoBF_NoNode Arguments_NoNode */
/*CallExprNoBF_NoNode	:	CallExprNoBF_NoNode Arguments_NoNode */
/*CallExprNoBF_NoNode	:	CallExprNoBF_NoNode [ Expr_NoNode ] */
/*CallExprNoBF_NoNode	:	CallExprNoBF_NoNode . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Arguments_NoNode	:	( ) */
/*Arguments_NoNode	:	( ArgumentList_NoNode ) */
static psrNode_t* AR_STDCALL handle_Arguments_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ArgumentList_NoNode	:	AssignmentExpr_NoNode */
/*ArgumentList_NoNode	:	ArgumentList_NoNode , AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ArgumentList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LeftHandSideExpr_NoNode	:	NewExpr_NoNode */
/*LeftHandSideExpr_NoNode	:	CallExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LeftHandSideExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LeftHandSideExprNoBF_NoNode	:	NewExprNoBF_NoNode */
/*LeftHandSideExprNoBF_NoNode	:	CallExprNoBF_NoNode */
static psrNode_t* AR_STDCALL handle_LeftHandSideExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PostfixExpr_NoNode	:	LeftHandSideExpr_NoNode */
/*PostfixExpr_NoNode	:	LeftHandSideExpr_NoNode ++ */
/*PostfixExpr_NoNode	:	LeftHandSideExpr_NoNode -- */
static psrNode_t* AR_STDCALL handle_PostfixExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*PostfixExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode */
/*PostfixExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode ++ */
/*PostfixExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode -- */
static psrNode_t* AR_STDCALL handle_PostfixExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*UnaryExprCommon_NoNode	:	delete UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	void UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	typeof UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	++ UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	-- UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	+ UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	- UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	~ UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	! UnaryExpr_NoNode */
static psrNode_t* AR_STDCALL handle_UnaryExprCommon_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*UnaryExpr_NoNode	:	PostfixExpr_NoNode */
/*UnaryExpr_NoNode	:	UnaryExprCommon_NoNode */
static psrNode_t* AR_STDCALL handle_UnaryExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*UnaryExprNoBF_NoNode	:	PostfixExprNoBF_NoNode */
/*UnaryExprNoBF_NoNode	:	UnaryExprCommon_NoNode */
static psrNode_t* AR_STDCALL handle_UnaryExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MultiplicativeExpr_NoNode	:	UnaryExpr_NoNode */
/*MultiplicativeExpr_NoNode	:	MultiplicativeExpr_NoNode * UnaryExpr_NoNode */
/*MultiplicativeExpr_NoNode	:	MultiplicativeExpr_NoNode / UnaryExpr_NoNode */
/*MultiplicativeExpr_NoNode	:	MultiplicativeExpr_NoNode % UnaryExpr_NoNode */
static psrNode_t* AR_STDCALL handle_MultiplicativeExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*MultiplicativeExprNoBF_NoNode	:	UnaryExprNoBF_NoNode */
/*MultiplicativeExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode * UnaryExpr_NoNode */
/*MultiplicativeExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode / UnaryExpr_NoNode */
/*MultiplicativeExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode % UnaryExpr_NoNode */
static psrNode_t* AR_STDCALL handle_MultiplicativeExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AdditiveExpr_NoNode	:	MultiplicativeExpr_NoNode */
/*AdditiveExpr_NoNode	:	AdditiveExpr_NoNode + MultiplicativeExpr_NoNode */
/*AdditiveExpr_NoNode	:	AdditiveExpr_NoNode - MultiplicativeExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AdditiveExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AdditiveExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode */
/*AdditiveExprNoBF_NoNode	:	AdditiveExprNoBF_NoNode + MultiplicativeExpr_NoNode */
/*AdditiveExprNoBF_NoNode	:	AdditiveExprNoBF_NoNode - MultiplicativeExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AdditiveExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ShiftExpr_NoNode	:	AdditiveExpr_NoNode */
/*ShiftExpr_NoNode	:	ShiftExpr_NoNode << AdditiveExpr_NoNode */
/*ShiftExpr_NoNode	:	ShiftExpr_NoNode >> AdditiveExpr_NoNode */
/*ShiftExpr_NoNode	:	ShiftExpr_NoNode >>> AdditiveExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ShiftExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ShiftExprNoBF_NoNode	:	AdditiveExprNoBF_NoNode */
/*ShiftExprNoBF_NoNode	:	ShiftExprNoBF_NoNode << AdditiveExpr_NoNode */
/*ShiftExprNoBF_NoNode	:	ShiftExprNoBF_NoNode >> AdditiveExpr_NoNode */
/*ShiftExprNoBF_NoNode	:	ShiftExprNoBF_NoNode >>> AdditiveExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ShiftExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*RelationalExpr_NoNode	:	ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode < ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode > ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode <= ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode >= ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode instanceof ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode in ShiftExpr_NoNode */
static psrNode_t* AR_STDCALL handle_RelationalExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*RelationalExprNoIn_NoNode	:	ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode < ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode > ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode <= ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode >= ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode instanceof ShiftExpr_NoNode */
static psrNode_t* AR_STDCALL handle_RelationalExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*RelationalExprNoBF_NoNode	:	ShiftExprNoBF_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode < ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode > ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode <= ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode >= ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode instanceof ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode in ShiftExpr_NoNode */
static psrNode_t* AR_STDCALL handle_RelationalExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EqualityExpr_NoNode	:	RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode == RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode != RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode === RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode !== RelationalExpr_NoNode */
static psrNode_t* AR_STDCALL handle_EqualityExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EqualityExprNoIn_NoNode	:	RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode == RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode != RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode === RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode !== RelationalExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_EqualityExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EqualityExprNoBF_NoNode	:	RelationalExprNoBF_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode == RelationalExpr_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode != RelationalExpr_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode === RelationalExpr_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode !== RelationalExpr_NoNode */
static psrNode_t* AR_STDCALL handle_EqualityExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseANDExpr_NoNode	:	EqualityExpr_NoNode */
/*BitwiseANDExpr_NoNode	:	BitwiseANDExpr_NoNode & EqualityExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseANDExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseANDExprNoIn_NoNode	:	EqualityExprNoIn_NoNode */
/*BitwiseANDExprNoIn_NoNode	:	BitwiseANDExprNoIn_NoNode & EqualityExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseANDExprNoBF_NoNode	:	EqualityExprNoBF_NoNode */
/*BitwiseANDExprNoBF_NoNode	:	BitwiseANDExprNoBF_NoNode & EqualityExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseXORExpr_NoNode	:	BitwiseANDExpr_NoNode */
/*BitwiseXORExpr_NoNode	:	BitwiseXORExpr_NoNode ^ BitwiseANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseXORExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseXORExprNoIn_NoNode	:	BitwiseANDExprNoIn_NoNode */
/*BitwiseXORExprNoIn_NoNode	:	BitwiseXORExprNoIn_NoNode ^ BitwiseANDExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseXORExprNoBF_NoNode	:	BitwiseANDExprNoBF_NoNode */
/*BitwiseXORExprNoBF_NoNode	:	BitwiseXORExprNoBF_NoNode ^ BitwiseANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseORExpr_NoNode	:	BitwiseXORExpr_NoNode */
/*BitwiseORExpr_NoNode	:	BitwiseORExpr_NoNode | BitwiseXORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseORExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseORExprNoIn_NoNode	:	BitwiseXORExprNoIn_NoNode */
/*BitwiseORExprNoIn_NoNode	:	BitwiseORExprNoIn_NoNode | BitwiseXORExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BitwiseORExprNoBF_NoNode	:	BitwiseXORExprNoBF_NoNode */
/*BitwiseORExprNoBF_NoNode	:	BitwiseORExprNoBF_NoNode | BitwiseXORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalANDExpr_NoNode	:	BitwiseORExpr_NoNode */
/*LogicalANDExpr_NoNode	:	LogicalANDExpr_NoNode && BitwiseORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalANDExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalANDExprNoIn_NoNode	:	BitwiseORExprNoIn_NoNode */
/*LogicalANDExprNoIn_NoNode	:	LogicalANDExprNoIn_NoNode && BitwiseORExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalANDExprNoBF_NoNode	:	BitwiseORExprNoBF_NoNode */
/*LogicalANDExprNoBF_NoNode	:	LogicalANDExprNoBF_NoNode && BitwiseORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalORExpr_NoNode	:	LogicalANDExpr_NoNode */
/*LogicalORExpr_NoNode	:	LogicalORExpr_NoNode || LogicalANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalORExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalORExprNoIn_NoNode	:	LogicalANDExprNoIn_NoNode */
/*LogicalORExprNoIn_NoNode	:	LogicalORExprNoIn_NoNode || LogicalANDExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LogicalORExprNoBF_NoNode	:	LogicalANDExprNoBF_NoNode */
/*LogicalORExprNoBF_NoNode	:	LogicalORExprNoBF_NoNode || LogicalANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConditionalExpr_NoNode	:	LogicalORExpr_NoNode */
/*ConditionalExpr_NoNode	:	LogicalORExpr_NoNode ? AssignmentExpr_NoNode : AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ConditionalExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConditionalExprNoIn_NoNode	:	LogicalORExprNoIn_NoNode */
/*ConditionalExprNoIn_NoNode	:	LogicalORExprNoIn_NoNode ? AssignmentExprNoIn_NoNode : AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConditionalExprNoBF_NoNode	:	LogicalORExprNoBF_NoNode */
/*ConditionalExprNoBF_NoNode	:	LogicalORExprNoBF_NoNode ? AssignmentExpr_NoNode : AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentExpr_NoNode	:	ConditionalExpr_NoNode */
/*AssignmentExpr_NoNode	:	LeftHandSideExpr_NoNode AssignmentOperator_NoNode AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AssignmentExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentExprNoIn_NoNode	:	ConditionalExprNoIn_NoNode */
/*AssignmentExprNoIn_NoNode	:	LeftHandSideExpr_NoNode AssignmentOperator_NoNode AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentExprNoBF_NoNode	:	ConditionalExprNoBF_NoNode */
/*AssignmentExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode AssignmentOperator_NoNode AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*AssignmentOperator_NoNode	:	= */
/*AssignmentOperator_NoNode	:	+= */
/*AssignmentOperator_NoNode	:	-= */
/*AssignmentOperator_NoNode	:	*= */
/*AssignmentOperator_NoNode	:	/= */
/*AssignmentOperator_NoNode	:	<<= */
/*AssignmentOperator_NoNode	:	>>= */
/*AssignmentOperator_NoNode	:	>>>= */
/*AssignmentOperator_NoNode	:	&= */
/*AssignmentOperator_NoNode	:	^= */
/*AssignmentOperator_NoNode	:	|= */
/*AssignmentOperator_NoNode	:	%= */
static psrNode_t* AR_STDCALL handle_AssignmentOperator_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Expr_NoNode	:	AssignmentExpr_NoNode */
/*Expr_NoNode	:	Expr_NoNode , AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_Expr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprNoIn_NoNode	:	AssignmentExprNoIn_NoNode */
/*ExprNoIn_NoNode	:	ExprNoIn_NoNode , AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_ExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprNoBF_NoNode	:	AssignmentExprNoBF_NoNode */
/*ExprNoBF_NoNode	:	ExprNoBF_NoNode , AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Statement_NoNode	:	Block_NoNode */
/*Statement_NoNode	:	VariableStatement_NoNode */
/*Statement_NoNode	:	ConstStatement_NoNode */
/*Statement_NoNode	:	FunctionDeclaration_NoNode */
/*Statement_NoNode	:	EmptyStatement_NoNode */
/*Statement_NoNode	:	ExprStatement_NoNode */
/*Statement_NoNode	:	IfStatement_NoNode */
/*Statement_NoNode	:	IterationStatement_NoNode */
/*Statement_NoNode	:	ContinueStatement_NoNode */
/*Statement_NoNode	:	BreakStatement_NoNode */
/*Statement_NoNode	:	ReturnStatement_NoNode */
/*Statement_NoNode	:	WithStatement_NoNode */
/*Statement_NoNode	:	SwitchStatement_NoNode */
/*Statement_NoNode	:	LabelledStatement_NoNode */
/*Statement_NoNode	:	ThrowStatement_NoNode */
/*Statement_NoNode	:	TryStatement_NoNode */
/*Statement_NoNode	:	DebuggerStatement_NoNode */
static psrNode_t* AR_STDCALL handle_Statement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Block_NoNode	:	{ } */
/*Block_NoNode	:	{ SourceElements_NoNode } */
static psrNode_t* AR_STDCALL handle_Block_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*VariableStatement_NoNode	:	var VariableDeclarationList_NoNode ; */
/*VariableStatement_NoNode	:	var VariableDeclarationList_NoNode error */
static psrNode_t* AR_STDCALL handle_VariableStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*VariableDeclarationList_NoNode	:	IDENTIFIER */
/*VariableDeclarationList_NoNode	:	IDENTIFIER Initializer_NoNode */
/*VariableDeclarationList_NoNode	:	VariableDeclarationList_NoNode , IDENTIFIER */
/*VariableDeclarationList_NoNode	:	VariableDeclarationList_NoNode , IDENTIFIER Initializer_NoNode */
static psrNode_t* AR_STDCALL handle_VariableDeclarationList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*VariableDeclarationListNoIn_NoNode	:	IDENTIFIER */
/*VariableDeclarationListNoIn_NoNode	:	IDENTIFIER InitializerNoIn_NoNode */
/*VariableDeclarationListNoIn_NoNode	:	VariableDeclarationListNoIn_NoNode , IDENTIFIER */
/*VariableDeclarationListNoIn_NoNode	:	VariableDeclarationListNoIn_NoNode , IDENTIFIER InitializerNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_VariableDeclarationListNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConstStatement_NoNode	:	const ConstDeclarationList_NoNode ; */
/*ConstStatement_NoNode	:	const ConstDeclarationList_NoNode error */
static psrNode_t* AR_STDCALL handle_ConstStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConstDeclarationList_NoNode	:	ConstDeclaration_NoNode */
/*ConstDeclarationList_NoNode	:	ConstDeclarationList_NoNode , ConstDeclaration_NoNode */
static psrNode_t* AR_STDCALL handle_ConstDeclarationList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ConstDeclaration_NoNode	:	IDENTIFIER */
/*ConstDeclaration_NoNode	:	IDENTIFIER Initializer_NoNode */
static psrNode_t* AR_STDCALL handle_ConstDeclaration_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*Initializer_NoNode	:	= AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_Initializer_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*InitializerNoIn_NoNode	:	= AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_InitializerNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*EmptyStatement_NoNode	:	; */
static psrNode_t* AR_STDCALL handle_EmptyStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprStatement_NoNode	:	ExprNoBF_NoNode ; */
/*ExprStatement_NoNode	:	ExprNoBF_NoNode error */
static psrNode_t* AR_STDCALL handle_ExprStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*IfStatement_NoNode	:	if ( Expr_NoNode ) Statement_NoNode */
/*IfStatement_NoNode	:	if ( Expr_NoNode ) Statement_NoNode else Statement_NoNode */
static psrNode_t* AR_STDCALL handle_IfStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*IterationStatement_NoNode	:	do Statement_NoNode while ( Expr_NoNode ) ; */
/*IterationStatement_NoNode	:	do Statement_NoNode while ( Expr_NoNode ) error */
/*IterationStatement_NoNode	:	while ( Expr_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( ExprNoInOpt_NoNode ; ExprOpt_NoNode ; ExprOpt_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( var VariableDeclarationListNoIn_NoNode ; ExprOpt_NoNode ; ExprOpt_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( LeftHandSideExpr_NoNode in Expr_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( var IDENTIFIER in Expr_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( var IDENTIFIER InitializerNoIn_NoNode in Expr_NoNode ) Statement_NoNode */
static psrNode_t* AR_STDCALL handle_IterationStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprOpt_NoNode	:	 */
/*ExprOpt_NoNode	:	Expr_NoNode */
static psrNode_t* AR_STDCALL handle_ExprOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ExprNoInOpt_NoNode	:	 */
/*ExprNoInOpt_NoNode	:	ExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_ExprNoInOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ContinueStatement_NoNode	:	continue ; */
/*ContinueStatement_NoNode	:	continue error */
/*ContinueStatement_NoNode	:	continue IDENTIFIER ; */
/*ContinueStatement_NoNode	:	continue IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_ContinueStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*BreakStatement_NoNode	:	break ; */
/*BreakStatement_NoNode	:	break error */
/*BreakStatement_NoNode	:	break IDENTIFIER ; */
/*BreakStatement_NoNode	:	break IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_BreakStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ReturnStatement_NoNode	:	return ; */
/*ReturnStatement_NoNode	:	return error */
/*ReturnStatement_NoNode	:	return Expr_NoNode ; */
/*ReturnStatement_NoNode	:	return Expr_NoNode error */
static psrNode_t* AR_STDCALL handle_ReturnStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*WithStatement_NoNode	:	with ( Expr_NoNode ) Statement_NoNode */
static psrNode_t* AR_STDCALL handle_WithStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*SwitchStatement_NoNode	:	switch ( Expr_NoNode ) CaseBlock_NoNode */
static psrNode_t* AR_STDCALL handle_SwitchStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseBlock_NoNode	:	{ CaseClausesOpt_NoNode } */
/*CaseBlock_NoNode	:	{ CaseClausesOpt_NoNode DefaultClause_NoNode CaseClausesOpt_NoNode } */
static psrNode_t* AR_STDCALL handle_CaseBlock_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseClausesOpt_NoNode	:	 */
/*CaseClausesOpt_NoNode	:	CaseClauses_NoNode */
static psrNode_t* AR_STDCALL handle_CaseClausesOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseClauses_NoNode	:	CaseClause_NoNode */
/*CaseClauses_NoNode	:	CaseClauses_NoNode CaseClause_NoNode */
static psrNode_t* AR_STDCALL handle_CaseClauses_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*CaseClause_NoNode	:	case Expr_NoNode : */
/*CaseClause_NoNode	:	case Expr_NoNode : SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_CaseClause_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*DefaultClause_NoNode	:	default : */
/*DefaultClause_NoNode	:	default : SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_DefaultClause_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*LabelledStatement_NoNode	:	IDENTIFIER : Statement_NoNode */
static psrNode_t* AR_STDCALL handle_LabelledStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ThrowStatement_NoNode	:	throw Expr_NoNode ; */
/*ThrowStatement_NoNode	:	throw Expr_NoNode error */
static psrNode_t* AR_STDCALL handle_ThrowStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*TryStatement_NoNode	:	try Block_NoNode finally Block_NoNode */
/*TryStatement_NoNode	:	try Block_NoNode catch ( IDENTIFIER ) Block_NoNode */
/*TryStatement_NoNode	:	try Block_NoNode catch ( IDENTIFIER ) Block_NoNode finally Block_NoNode */
static psrNode_t* AR_STDCALL handle_TryStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*DebuggerStatement_NoNode	:	debugger ; */
/*DebuggerStatement_NoNode	:	debugger error */
static psrNode_t* AR_STDCALL handle_DebuggerStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FunctionDeclaration_NoNode	:	function IDENTIFIER ( ) { FunctionBody_NoNode } */
/*FunctionDeclaration_NoNode	:	function IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
static psrNode_t* AR_STDCALL handle_FunctionDeclaration_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FunctionExpr_NoNode	:	function ( ) { FunctionBody_NoNode } */
/*FunctionExpr_NoNode	:	function ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
/*FunctionExpr_NoNode	:	function IDENTIFIER ( ) { FunctionBody_NoNode } */
/*FunctionExpr_NoNode	:	function IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
static psrNode_t* AR_STDCALL handle_FunctionExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FormalParameterList_NoNode	:	IDENTIFIER */
/*FormalParameterList_NoNode	:	FormalParameterList_NoNode , IDENTIFIER */
static psrNode_t* AR_STDCALL handle_FormalParameterList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*FunctionBody_NoNode	:	 */
/*FunctionBody_NoNode	:	SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_FunctionBody_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*SourceElements_NoNode	:	Statement_NoNode */
/*SourceElements_NoNode	:	SourceElements_NoNode Statement_NoNode */
static psrNode_t* AR_STDCALL handle_SourceElements_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);




static struct { const wchar_t	*rule; const wchar_t	*prec_token; psrRuleFunc_t	handler; size_t	auto_ret; } __g_rule_pattern[] = {
{L"Literal  :  null ", NULL, handle_Literal, 0},
{L"Literal  :  true ", NULL, handle_Literal, 0},
{L"Literal  :  false ", NULL, handle_Literal, 0},
{L"Literal  :  NUMBER ", NULL, handle_Literal, 0},
{L"Literal  :  STRING_LITERAL ", NULL, handle_Literal, 0},
{L"Property  :  IDENTIFIER : AssignmentExpr ", NULL, handle_Property, 0},
{L"Property  :  STRING_LITERAL : AssignmentExpr ", NULL, handle_Property, 0},
{L"Property  :  NUMBER : AssignmentExpr ", NULL, handle_Property, 0},
{L"Property  :  IDENTIFIER IDENTIFIER ( ) { FunctionBody } ", NULL, handle_Property, 0},
{L"Property  :  IDENTIFIER IDENTIFIER ( FormalParameterList ) { FunctionBody } ", NULL, handle_Property, 0},
{L"PropertyList  :  Property ", NULL, handle_PropertyList, 0},
{L"PropertyList  :  PropertyList , Property ", NULL, handle_PropertyList, 0},
{L"PrimaryExpr  :  PrimaryExprNoBrace ", NULL, handle_PrimaryExpr, 0},
{L"PrimaryExpr  :  { } ", NULL, handle_PrimaryExpr, 0},
{L"PrimaryExpr  :  { PropertyList } ", NULL, handle_PrimaryExpr, 0},
{L"PrimaryExpr  :  { PropertyList , } ", NULL, handle_PrimaryExpr, 0},
{L"PrimaryExprNoBrace  :  this ", NULL, handle_PrimaryExprNoBrace, 0},
{L"PrimaryExprNoBrace  :  Literal ", NULL, handle_PrimaryExprNoBrace, 0},
{L"PrimaryExprNoBrace  :  ArrayLiteral ", NULL, handle_PrimaryExprNoBrace, 0},
{L"PrimaryExprNoBrace  :  IDENTIFIER ", NULL, handle_PrimaryExprNoBrace, 0},
{L"PrimaryExprNoBrace  :  ( Expr ) ", NULL, handle_PrimaryExprNoBrace, 0},
{L"ArrayLiteral  :  [ ElisionOpt ] ", NULL, handle_ArrayLiteral, 0},
{L"ArrayLiteral  :  [ ElementList ] ", NULL, handle_ArrayLiteral, 0},
{L"ArrayLiteral  :  [ ElementList , ElisionOpt ] ", NULL, handle_ArrayLiteral, 0},
{L"ElementList  :  ElisionOpt AssignmentExpr ", NULL, handle_ElementList, 0},
{L"ElementList  :  ElementList , ElisionOpt AssignmentExpr ", NULL, handle_ElementList, 0},
{L"ElisionOpt  :   ", NULL, handle_ElisionOpt, 0},
{L"ElisionOpt  :  Elision ", NULL, handle_ElisionOpt, 0},
{L"Elision  :  , ", NULL, handle_Elision, 0},
{L"Elision  :  Elision , ", NULL, handle_Elision, 0},
{L"MemberExpr  :  PrimaryExpr ", NULL, handle_MemberExpr, 0},
{L"MemberExpr  :  FunctionExpr ", NULL, handle_MemberExpr, 0},
{L"MemberExpr  :  MemberExpr [ Expr ] ", NULL, handle_MemberExpr, 0},
{L"MemberExpr  :  MemberExpr . IDENTIFIER ", NULL, handle_MemberExpr, 0},
{L"MemberExpr  :  new MemberExpr Arguments ", NULL, handle_MemberExpr, 0},
{L"MemberExprNoBF  :  PrimaryExprNoBrace ", NULL, handle_MemberExprNoBF, 0},
{L"MemberExprNoBF  :  MemberExprNoBF [ Expr ] ", NULL, handle_MemberExprNoBF, 0},
{L"MemberExprNoBF  :  MemberExprNoBF . IDENTIFIER ", NULL, handle_MemberExprNoBF, 0},
{L"MemberExprNoBF  :  new MemberExpr Arguments ", NULL, handle_MemberExprNoBF, 0},
{L"NewExpr  :  MemberExpr ", NULL, handle_NewExpr, 0},
{L"NewExpr  :  new NewExpr ", NULL, handle_NewExpr, 0},
{L"NewExprNoBF  :  MemberExprNoBF ", NULL, handle_NewExprNoBF, 0},
{L"NewExprNoBF  :  new NewExpr ", NULL, handle_NewExprNoBF, 0},
{L"CallExpr  :  MemberExpr Arguments ", NULL, handle_CallExpr, 0},
{L"CallExpr  :  CallExpr Arguments ", NULL, handle_CallExpr, 0},
{L"CallExpr  :  CallExpr [ Expr ] ", NULL, handle_CallExpr, 0},
{L"CallExpr  :  CallExpr . IDENTIFIER ", NULL, handle_CallExpr, 0},
{L"CallExprNoBF  :  MemberExprNoBF Arguments ", NULL, handle_CallExprNoBF, 0},
{L"CallExprNoBF  :  CallExprNoBF Arguments ", NULL, handle_CallExprNoBF, 0},
{L"CallExprNoBF  :  CallExprNoBF [ Expr ] ", NULL, handle_CallExprNoBF, 0},
{L"CallExprNoBF  :  CallExprNoBF . IDENTIFIER ", NULL, handle_CallExprNoBF, 0},
{L"Arguments  :  ( ) ", NULL, handle_Arguments, 0},
{L"Arguments  :  ( ArgumentList ) ", NULL, handle_Arguments, 0},
{L"ArgumentList  :  AssignmentExpr ", NULL, handle_ArgumentList, 0},
{L"ArgumentList  :  ArgumentList , AssignmentExpr ", NULL, handle_ArgumentList, 0},
{L"LeftHandSideExpr  :  NewExpr ", NULL, handle_LeftHandSideExpr, 0},
{L"LeftHandSideExpr  :  CallExpr ", NULL, handle_LeftHandSideExpr, 0},
{L"LeftHandSideExprNoBF  :  NewExprNoBF ", NULL, handle_LeftHandSideExprNoBF, 0},
{L"LeftHandSideExprNoBF  :  CallExprNoBF ", NULL, handle_LeftHandSideExprNoBF, 0},
{L"PostfixExpr  :  LeftHandSideExpr ", NULL, handle_PostfixExpr, 0},
{L"PostfixExpr  :  LeftHandSideExpr ++ ", NULL, handle_PostfixExpr, 0},
{L"PostfixExpr  :  LeftHandSideExpr -- ", NULL, handle_PostfixExpr, 0},
{L"PostfixExprNoBF  :  LeftHandSideExprNoBF ", NULL, handle_PostfixExprNoBF, 0},
{L"PostfixExprNoBF  :  LeftHandSideExprNoBF ++ ", NULL, handle_PostfixExprNoBF, 0},
{L"PostfixExprNoBF  :  LeftHandSideExprNoBF -- ", NULL, handle_PostfixExprNoBF, 0},
{L"UnaryExprCommon  :  delete UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  void UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  typeof UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  ++ UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  -- UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  + UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  - UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  ~ UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExprCommon  :  ! UnaryExpr ", NULL, handle_UnaryExprCommon, 0},
{L"UnaryExpr  :  PostfixExpr ", NULL, handle_UnaryExpr, 0},
{L"UnaryExpr  :  UnaryExprCommon ", NULL, handle_UnaryExpr, 0},
{L"UnaryExprNoBF  :  PostfixExprNoBF ", NULL, handle_UnaryExprNoBF, 0},
{L"UnaryExprNoBF  :  UnaryExprCommon ", NULL, handle_UnaryExprNoBF, 0},
{L"MultiplicativeExpr  :  UnaryExpr ", NULL, handle_MultiplicativeExpr, 0},
{L"MultiplicativeExpr  :  MultiplicativeExpr * UnaryExpr ", NULL, handle_MultiplicativeExpr, 0},
{L"MultiplicativeExpr  :  MultiplicativeExpr / UnaryExpr ", NULL, handle_MultiplicativeExpr, 0},
{L"MultiplicativeExpr  :  MultiplicativeExpr % UnaryExpr ", NULL, handle_MultiplicativeExpr, 0},
{L"MultiplicativeExprNoBF  :  UnaryExprNoBF ", NULL, handle_MultiplicativeExprNoBF, 0},
{L"MultiplicativeExprNoBF  :  MultiplicativeExprNoBF * UnaryExpr ", NULL, handle_MultiplicativeExprNoBF, 0},
{L"MultiplicativeExprNoBF  :  MultiplicativeExprNoBF / UnaryExpr ", NULL, handle_MultiplicativeExprNoBF, 0},
{L"MultiplicativeExprNoBF  :  MultiplicativeExprNoBF % UnaryExpr ", NULL, handle_MultiplicativeExprNoBF, 0},
{L"AdditiveExpr  :  MultiplicativeExpr ", NULL, handle_AdditiveExpr, 0},
{L"AdditiveExpr  :  AdditiveExpr + MultiplicativeExpr ", NULL, handle_AdditiveExpr, 0},
{L"AdditiveExpr  :  AdditiveExpr - MultiplicativeExpr ", NULL, handle_AdditiveExpr, 0},
{L"AdditiveExprNoBF  :  MultiplicativeExprNoBF ", NULL, handle_AdditiveExprNoBF, 0},
{L"AdditiveExprNoBF  :  AdditiveExprNoBF + MultiplicativeExpr ", NULL, handle_AdditiveExprNoBF, 0},
{L"AdditiveExprNoBF  :  AdditiveExprNoBF - MultiplicativeExpr ", NULL, handle_AdditiveExprNoBF, 0},
{L"ShiftExpr  :  AdditiveExpr ", NULL, handle_ShiftExpr, 0},
{L"ShiftExpr  :  ShiftExpr << AdditiveExpr ", NULL, handle_ShiftExpr, 0},
{L"ShiftExpr  :  ShiftExpr >> AdditiveExpr ", NULL, handle_ShiftExpr, 0},
{L"ShiftExpr  :  ShiftExpr >>> AdditiveExpr ", NULL, handle_ShiftExpr, 0},
{L"ShiftExprNoBF  :  AdditiveExprNoBF ", NULL, handle_ShiftExprNoBF, 0},
{L"ShiftExprNoBF  :  ShiftExprNoBF << AdditiveExpr ", NULL, handle_ShiftExprNoBF, 0},
{L"ShiftExprNoBF  :  ShiftExprNoBF >> AdditiveExpr ", NULL, handle_ShiftExprNoBF, 0},
{L"ShiftExprNoBF  :  ShiftExprNoBF >>> AdditiveExpr ", NULL, handle_ShiftExprNoBF, 0},
{L"RelationalExpr  :  ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExpr  :  RelationalExpr < ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExpr  :  RelationalExpr > ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExpr  :  RelationalExpr <= ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExpr  :  RelationalExpr >= ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExpr  :  RelationalExpr instanceof ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExpr  :  RelationalExpr in ShiftExpr ", NULL, handle_RelationalExpr, 0},
{L"RelationalExprNoIn  :  ShiftExpr ", NULL, handle_RelationalExprNoIn, 0},
{L"RelationalExprNoIn  :  RelationalExprNoIn < ShiftExpr ", NULL, handle_RelationalExprNoIn, 0},
{L"RelationalExprNoIn  :  RelationalExprNoIn > ShiftExpr ", NULL, handle_RelationalExprNoIn, 0},
{L"RelationalExprNoIn  :  RelationalExprNoIn <= ShiftExpr ", NULL, handle_RelationalExprNoIn, 0},
{L"RelationalExprNoIn  :  RelationalExprNoIn >= ShiftExpr ", NULL, handle_RelationalExprNoIn, 0},
{L"RelationalExprNoIn  :  RelationalExprNoIn instanceof ShiftExpr ", NULL, handle_RelationalExprNoIn, 0},
{L"RelationalExprNoBF  :  ShiftExprNoBF ", NULL, handle_RelationalExprNoBF, 0},
{L"RelationalExprNoBF  :  RelationalExprNoBF < ShiftExpr ", NULL, handle_RelationalExprNoBF, 0},
{L"RelationalExprNoBF  :  RelationalExprNoBF > ShiftExpr ", NULL, handle_RelationalExprNoBF, 0},
{L"RelationalExprNoBF  :  RelationalExprNoBF <= ShiftExpr ", NULL, handle_RelationalExprNoBF, 0},
{L"RelationalExprNoBF  :  RelationalExprNoBF >= ShiftExpr ", NULL, handle_RelationalExprNoBF, 0},
{L"RelationalExprNoBF  :  RelationalExprNoBF instanceof ShiftExpr ", NULL, handle_RelationalExprNoBF, 0},
{L"RelationalExprNoBF  :  RelationalExprNoBF in ShiftExpr ", NULL, handle_RelationalExprNoBF, 0},
{L"EqualityExpr  :  RelationalExpr ", NULL, handle_EqualityExpr, 0},
{L"EqualityExpr  :  EqualityExpr == RelationalExpr ", NULL, handle_EqualityExpr, 0},
{L"EqualityExpr  :  EqualityExpr != RelationalExpr ", NULL, handle_EqualityExpr, 0},
{L"EqualityExpr  :  EqualityExpr === RelationalExpr ", NULL, handle_EqualityExpr, 0},
{L"EqualityExpr  :  EqualityExpr !== RelationalExpr ", NULL, handle_EqualityExpr, 0},
{L"EqualityExprNoIn  :  RelationalExprNoIn ", NULL, handle_EqualityExprNoIn, 0},
{L"EqualityExprNoIn  :  EqualityExprNoIn == RelationalExprNoIn ", NULL, handle_EqualityExprNoIn, 0},
{L"EqualityExprNoIn  :  EqualityExprNoIn != RelationalExprNoIn ", NULL, handle_EqualityExprNoIn, 0},
{L"EqualityExprNoIn  :  EqualityExprNoIn === RelationalExprNoIn ", NULL, handle_EqualityExprNoIn, 0},
{L"EqualityExprNoIn  :  EqualityExprNoIn !== RelationalExprNoIn ", NULL, handle_EqualityExprNoIn, 0},
{L"EqualityExprNoBF  :  RelationalExprNoBF ", NULL, handle_EqualityExprNoBF, 0},
{L"EqualityExprNoBF  :  EqualityExprNoBF == RelationalExpr ", NULL, handle_EqualityExprNoBF, 0},
{L"EqualityExprNoBF  :  EqualityExprNoBF != RelationalExpr ", NULL, handle_EqualityExprNoBF, 0},
{L"EqualityExprNoBF  :  EqualityExprNoBF === RelationalExpr ", NULL, handle_EqualityExprNoBF, 0},
{L"EqualityExprNoBF  :  EqualityExprNoBF !== RelationalExpr ", NULL, handle_EqualityExprNoBF, 0},
{L"BitwiseANDExpr  :  EqualityExpr ", NULL, handle_BitwiseANDExpr, 0},
{L"BitwiseANDExpr  :  BitwiseANDExpr & EqualityExpr ", NULL, handle_BitwiseANDExpr, 0},
{L"BitwiseANDExprNoIn  :  EqualityExprNoIn ", NULL, handle_BitwiseANDExprNoIn, 0},
{L"BitwiseANDExprNoIn  :  BitwiseANDExprNoIn & EqualityExprNoIn ", NULL, handle_BitwiseANDExprNoIn, 0},
{L"BitwiseANDExprNoBF  :  EqualityExprNoBF ", NULL, handle_BitwiseANDExprNoBF, 0},
{L"BitwiseANDExprNoBF  :  BitwiseANDExprNoBF & EqualityExpr ", NULL, handle_BitwiseANDExprNoBF, 0},
{L"BitwiseXORExpr  :  BitwiseANDExpr ", NULL, handle_BitwiseXORExpr, 0},
{L"BitwiseXORExpr  :  BitwiseXORExpr ^ BitwiseANDExpr ", NULL, handle_BitwiseXORExpr, 0},
{L"BitwiseXORExprNoIn  :  BitwiseANDExprNoIn ", NULL, handle_BitwiseXORExprNoIn, 0},
{L"BitwiseXORExprNoIn  :  BitwiseXORExprNoIn ^ BitwiseANDExprNoIn ", NULL, handle_BitwiseXORExprNoIn, 0},
{L"BitwiseXORExprNoBF  :  BitwiseANDExprNoBF ", NULL, handle_BitwiseXORExprNoBF, 0},
{L"BitwiseXORExprNoBF  :  BitwiseXORExprNoBF ^ BitwiseANDExpr ", NULL, handle_BitwiseXORExprNoBF, 0},
{L"BitwiseORExpr  :  BitwiseXORExpr ", NULL, handle_BitwiseORExpr, 0},
{L"BitwiseORExpr  :  BitwiseORExpr | BitwiseXORExpr ", NULL, handle_BitwiseORExpr, 0},
{L"BitwiseORExprNoIn  :  BitwiseXORExprNoIn ", NULL, handle_BitwiseORExprNoIn, 0},
{L"BitwiseORExprNoIn  :  BitwiseORExprNoIn | BitwiseXORExprNoIn ", NULL, handle_BitwiseORExprNoIn, 0},
{L"BitwiseORExprNoBF  :  BitwiseXORExprNoBF ", NULL, handle_BitwiseORExprNoBF, 0},
{L"BitwiseORExprNoBF  :  BitwiseORExprNoBF | BitwiseXORExpr ", NULL, handle_BitwiseORExprNoBF, 0},
{L"LogicalANDExpr  :  BitwiseORExpr ", NULL, handle_LogicalANDExpr, 0},
{L"LogicalANDExpr  :  LogicalANDExpr && BitwiseORExpr ", NULL, handle_LogicalANDExpr, 0},
{L"LogicalANDExprNoIn  :  BitwiseORExprNoIn ", NULL, handle_LogicalANDExprNoIn, 0},
{L"LogicalANDExprNoIn  :  LogicalANDExprNoIn && BitwiseORExprNoIn ", NULL, handle_LogicalANDExprNoIn, 0},
{L"LogicalANDExprNoBF  :  BitwiseORExprNoBF ", NULL, handle_LogicalANDExprNoBF, 0},
{L"LogicalANDExprNoBF  :  LogicalANDExprNoBF && BitwiseORExpr ", NULL, handle_LogicalANDExprNoBF, 0},
{L"LogicalORExpr  :  LogicalANDExpr ", NULL, handle_LogicalORExpr, 0},
{L"LogicalORExpr  :  LogicalORExpr || LogicalANDExpr ", NULL, handle_LogicalORExpr, 0},
{L"LogicalORExprNoIn  :  LogicalANDExprNoIn ", NULL, handle_LogicalORExprNoIn, 0},
{L"LogicalORExprNoIn  :  LogicalORExprNoIn || LogicalANDExprNoIn ", NULL, handle_LogicalORExprNoIn, 0},
{L"LogicalORExprNoBF  :  LogicalANDExprNoBF ", NULL, handle_LogicalORExprNoBF, 0},
{L"LogicalORExprNoBF  :  LogicalORExprNoBF || LogicalANDExpr ", NULL, handle_LogicalORExprNoBF, 0},
{L"ConditionalExpr  :  LogicalORExpr ", NULL, handle_ConditionalExpr, 0},
{L"ConditionalExpr  :  LogicalORExpr ? AssignmentExpr : AssignmentExpr ", NULL, handle_ConditionalExpr, 0},
{L"ConditionalExprNoIn  :  LogicalORExprNoIn ", NULL, handle_ConditionalExprNoIn, 0},
{L"ConditionalExprNoIn  :  LogicalORExprNoIn ? AssignmentExprNoIn : AssignmentExprNoIn ", NULL, handle_ConditionalExprNoIn, 0},
{L"ConditionalExprNoBF  :  LogicalORExprNoBF ", NULL, handle_ConditionalExprNoBF, 0},
{L"ConditionalExprNoBF  :  LogicalORExprNoBF ? AssignmentExpr : AssignmentExpr ", NULL, handle_ConditionalExprNoBF, 0},
{L"AssignmentExpr  :  ConditionalExpr ", NULL, handle_AssignmentExpr, 0},
{L"AssignmentExpr  :  LeftHandSideExpr AssignmentOperator AssignmentExpr ", NULL, handle_AssignmentExpr, 0},
{L"AssignmentExprNoIn  :  ConditionalExprNoIn ", NULL, handle_AssignmentExprNoIn, 0},
{L"AssignmentExprNoIn  :  LeftHandSideExpr AssignmentOperator AssignmentExprNoIn ", NULL, handle_AssignmentExprNoIn, 0},
{L"AssignmentExprNoBF  :  ConditionalExprNoBF ", NULL, handle_AssignmentExprNoBF, 0},
{L"AssignmentExprNoBF  :  LeftHandSideExprNoBF AssignmentOperator AssignmentExpr ", NULL, handle_AssignmentExprNoBF, 0},
{L"AssignmentOperator  :  = ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  += ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  -= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  *= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  /= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  <<= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  >>= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  >>>= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  &= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  ^= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  |= ", NULL, handle_AssignmentOperator, 0},
{L"AssignmentOperator  :  %= ", NULL, handle_AssignmentOperator, 0},
{L"Expr  :  AssignmentExpr ", NULL, handle_Expr, 0},
{L"Expr  :  Expr , AssignmentExpr ", NULL, handle_Expr, 0},
{L"ExprNoIn  :  AssignmentExprNoIn ", NULL, handle_ExprNoIn, 0},
{L"ExprNoIn  :  ExprNoIn , AssignmentExprNoIn ", NULL, handle_ExprNoIn, 0},
{L"ExprNoBF  :  AssignmentExprNoBF ", NULL, handle_ExprNoBF, 0},
{L"ExprNoBF  :  ExprNoBF , AssignmentExpr ", NULL, handle_ExprNoBF, 0},
{L"Statement  :  Block ", NULL, handle_Statement, 0},
{L"Statement  :  VariableStatement ", NULL, handle_Statement, 0},
{L"Statement  :  ConstStatement ", NULL, handle_Statement, 0},
{L"Statement  :  FunctionDeclaration ", NULL, handle_Statement, 0},
{L"Statement  :  EmptyStatement ", NULL, handle_Statement, 0},
{L"Statement  :  ExprStatement ", NULL, handle_Statement, 0},
{L"Statement  :  IfStatement ", NULL, handle_Statement, 0},
{L"Statement  :  IterationStatement ", NULL, handle_Statement, 0},
{L"Statement  :  ContinueStatement ", NULL, handle_Statement, 0},
{L"Statement  :  BreakStatement ", NULL, handle_Statement, 0},
{L"Statement  :  ReturnStatement ", NULL, handle_Statement, 0},
{L"Statement  :  WithStatement ", NULL, handle_Statement, 0},
{L"Statement  :  SwitchStatement ", NULL, handle_Statement, 0},
{L"Statement  :  LabelledStatement ", NULL, handle_Statement, 0},
{L"Statement  :  ThrowStatement ", NULL, handle_Statement, 0},
{L"Statement  :  TryStatement ", NULL, handle_Statement, 0},
{L"Statement  :  DebuggerStatement ", NULL, handle_Statement, 0},
{L"Block  :  { } ", NULL, handle_Block, 0},
{L"Block  :  { SourceElements } ", NULL, handle_Block, 0},
{L"VariableStatement  :  var VariableDeclarationList ; ", NULL, handle_VariableStatement, 0},
{L"VariableStatement  :  var VariableDeclarationList error ", NULL, handle_VariableStatement, 0},
{L"VariableDeclarationList  :  IDENTIFIER ", NULL, handle_VariableDeclarationList, 0},
{L"VariableDeclarationList  :  IDENTIFIER Initializer ", NULL, handle_VariableDeclarationList, 0},
{L"VariableDeclarationList  :  VariableDeclarationList , IDENTIFIER ", NULL, handle_VariableDeclarationList, 0},
{L"VariableDeclarationList  :  VariableDeclarationList , IDENTIFIER Initializer ", NULL, handle_VariableDeclarationList, 0},
{L"VariableDeclarationListNoIn  :  IDENTIFIER ", NULL, handle_VariableDeclarationListNoIn, 0},
{L"VariableDeclarationListNoIn  :  IDENTIFIER InitializerNoIn ", NULL, handle_VariableDeclarationListNoIn, 0},
{L"VariableDeclarationListNoIn  :  VariableDeclarationListNoIn , IDENTIFIER ", NULL, handle_VariableDeclarationListNoIn, 0},
{L"VariableDeclarationListNoIn  :  VariableDeclarationListNoIn , IDENTIFIER InitializerNoIn ", NULL, handle_VariableDeclarationListNoIn, 0},
{L"ConstStatement  :  const ConstDeclarationList ; ", NULL, handle_ConstStatement, 0},
{L"ConstStatement  :  const ConstDeclarationList error ", NULL, handle_ConstStatement, 0},
{L"ConstDeclarationList  :  ConstDeclaration ", NULL, handle_ConstDeclarationList, 0},
{L"ConstDeclarationList  :  ConstDeclarationList , ConstDeclaration ", NULL, handle_ConstDeclarationList, 0},
{L"ConstDeclaration  :  IDENTIFIER ", NULL, handle_ConstDeclaration, 0},
{L"ConstDeclaration  :  IDENTIFIER Initializer ", NULL, handle_ConstDeclaration, 0},
{L"Initializer  :  = AssignmentExpr ", NULL, handle_Initializer, 0},
{L"InitializerNoIn  :  = AssignmentExprNoIn ", NULL, handle_InitializerNoIn, 0},
{L"EmptyStatement  :  ; ", NULL, handle_EmptyStatement, 0},
{L"ExprStatement  :  ExprNoBF ; ", NULL, handle_ExprStatement, 0},
{L"ExprStatement  :  ExprNoBF error ", NULL, handle_ExprStatement, 0},
{L"IfStatement  :  if ( Expr ) Statement ", L"IF_WITHOUT_ELSE", handle_IfStatement, 0},
{L"IfStatement  :  if ( Expr ) Statement else Statement ", NULL, handle_IfStatement, 0},
{L"IterationStatement  :  do Statement while ( Expr ) ; ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  do Statement while ( Expr ) error ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  while ( Expr ) Statement ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  for ( ExprNoInOpt ; ExprOpt ; ExprOpt ) Statement ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  for ( var VariableDeclarationListNoIn ; ExprOpt ; ExprOpt ) Statement ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  for ( LeftHandSideExpr in Expr ) Statement ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  for ( var IDENTIFIER in Expr ) Statement ", NULL, handle_IterationStatement, 0},
{L"IterationStatement  :  for ( var IDENTIFIER InitializerNoIn in Expr ) Statement ", NULL, handle_IterationStatement, 0},
{L"ExprOpt  :   ", NULL, handle_ExprOpt, 0},
{L"ExprOpt  :  Expr ", NULL, handle_ExprOpt, 0},
{L"ExprNoInOpt  :   ", NULL, handle_ExprNoInOpt, 0},
{L"ExprNoInOpt  :  ExprNoIn ", NULL, handle_ExprNoInOpt, 0},
{L"ContinueStatement  :  continue ; ", NULL, handle_ContinueStatement, 0},
{L"ContinueStatement  :  continue error ", NULL, handle_ContinueStatement, 0},
{L"ContinueStatement  :  continue IDENTIFIER ; ", NULL, handle_ContinueStatement, 0},
{L"ContinueStatement  :  continue IDENTIFIER error ", NULL, handle_ContinueStatement, 0},
{L"BreakStatement  :  break ; ", NULL, handle_BreakStatement, 0},
{L"BreakStatement  :  break error ", NULL, handle_BreakStatement, 0},
{L"BreakStatement  :  break IDENTIFIER ; ", NULL, handle_BreakStatement, 0},
{L"BreakStatement  :  break IDENTIFIER error ", NULL, handle_BreakStatement, 0},
{L"ReturnStatement  :  return ; ", NULL, handle_ReturnStatement, 0},
{L"ReturnStatement  :  return error ", NULL, handle_ReturnStatement, 0},
{L"ReturnStatement  :  return Expr ; ", NULL, handle_ReturnStatement, 0},
{L"ReturnStatement  :  return Expr error ", NULL, handle_ReturnStatement, 0},
{L"WithStatement  :  with ( Expr ) Statement ", NULL, handle_WithStatement, 0},
{L"SwitchStatement  :  switch ( Expr ) CaseBlock ", NULL, handle_SwitchStatement, 0},
{L"CaseBlock  :  { CaseClausesOpt } ", NULL, handle_CaseBlock, 0},
{L"CaseBlock  :  { CaseClausesOpt DefaultClause CaseClausesOpt } ", NULL, handle_CaseBlock, 0},
{L"CaseClausesOpt  :   ", NULL, handle_CaseClausesOpt, 0},
{L"CaseClausesOpt  :  CaseClauses ", NULL, handle_CaseClausesOpt, 0},
{L"CaseClauses  :  CaseClause ", NULL, handle_CaseClauses, 0},
{L"CaseClauses  :  CaseClauses CaseClause ", NULL, handle_CaseClauses, 0},
{L"CaseClause  :  case Expr : ", NULL, handle_CaseClause, 0},
{L"CaseClause  :  case Expr : SourceElements ", NULL, handle_CaseClause, 0},
{L"DefaultClause  :  default : ", NULL, handle_DefaultClause, 0},
{L"DefaultClause  :  default : SourceElements ", NULL, handle_DefaultClause, 0},
{L"LabelledStatement  :  IDENTIFIER : Statement ", NULL, handle_LabelledStatement, 0},
{L"ThrowStatement  :  throw Expr ; ", NULL, handle_ThrowStatement, 0},
{L"ThrowStatement  :  throw Expr error ", NULL, handle_ThrowStatement, 0},
{L"TryStatement  :  try Block finally Block ", NULL, handle_TryStatement, 0},
{L"TryStatement  :  try Block catch ( IDENTIFIER ) Block ", NULL, handle_TryStatement, 0},
{L"TryStatement  :  try Block catch ( IDENTIFIER ) Block finally Block ", NULL, handle_TryStatement, 0},
{L"DebuggerStatement  :  debugger ; ", NULL, handle_DebuggerStatement, 0},
{L"DebuggerStatement  :  debugger error ", NULL, handle_DebuggerStatement, 0},
{L"FunctionDeclaration  :  function IDENTIFIER ( ) { FunctionBody } ", NULL, handle_FunctionDeclaration, 0},
{L"FunctionDeclaration  :  function IDENTIFIER ( FormalParameterList ) { FunctionBody } ", NULL, handle_FunctionDeclaration, 0},
{L"FunctionExpr  :  function ( ) { FunctionBody } ", NULL, handle_FunctionExpr, 0},
{L"FunctionExpr  :  function ( FormalParameterList ) { FunctionBody } ", NULL, handle_FunctionExpr, 0},
{L"FunctionExpr  :  function IDENTIFIER ( ) { FunctionBody } ", NULL, handle_FunctionExpr, 0},
{L"FunctionExpr  :  function IDENTIFIER ( FormalParameterList ) { FunctionBody } ", NULL, handle_FunctionExpr, 0},
{L"FormalParameterList  :  IDENTIFIER ", NULL, handle_FormalParameterList, 0},
{L"FormalParameterList  :  FormalParameterList , IDENTIFIER ", NULL, handle_FormalParameterList, 0},
{L"FunctionBody  :   ", NULL, handle_FunctionBody, 0},
{L"FunctionBody  :  SourceElements_NoNode ", NULL, handle_FunctionBody, 0},
{L"Program  :   ", NULL, handle_Program, 0},
{L"Program  :  SourceElements ", NULL, handle_Program, 0},
{L"SourceElements  :  Statement ", NULL, handle_SourceElements, 0},
{L"SourceElements  :  SourceElements Statement ", NULL, handle_SourceElements, 0},
{L"Literal_NoNode  :  null ", NULL, handle_Literal_NoNode, 0},
{L"Literal_NoNode  :  true ", NULL, handle_Literal_NoNode, 0},
{L"Literal_NoNode  :  false ", NULL, handle_Literal_NoNode, 0},
{L"Literal_NoNode  :  NUMBER ", NULL, handle_Literal_NoNode, 0},
{L"Literal_NoNode  :  STRING_LITERAL ", NULL, handle_Literal_NoNode, 0},
{L"Property_NoNode  :  IDENTIFIER : AssignmentExpr_NoNode ", NULL, handle_Property_NoNode, 0},
{L"Property_NoNode  :  STRING_LITERAL : AssignmentExpr_NoNode ", NULL, handle_Property_NoNode, 0},
{L"Property_NoNode  :  NUMBER : AssignmentExpr_NoNode ", NULL, handle_Property_NoNode, 0},
{L"Property_NoNode  :  IDENTIFIER IDENTIFIER ( ) { FunctionBody_NoNode } ", NULL, handle_Property_NoNode, 0},
{L"Property_NoNode  :  IDENTIFIER IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } ", NULL, handle_Property_NoNode, 0},
{L"PropertyList_NoNode  :  Property_NoNode ", NULL, handle_PropertyList_NoNode, 0},
{L"PropertyList_NoNode  :  PropertyList_NoNode , Property_NoNode ", NULL, handle_PropertyList_NoNode, 0},
{L"PrimaryExpr_NoNode  :  PrimaryExprNoBrace_NoNode ", NULL, handle_PrimaryExpr_NoNode, 0},
{L"PrimaryExpr_NoNode  :  { } ", NULL, handle_PrimaryExpr_NoNode, 0},
{L"PrimaryExpr_NoNode  :  { PropertyList_NoNode } ", NULL, handle_PrimaryExpr_NoNode, 0},
{L"PrimaryExpr_NoNode  :  { PropertyList_NoNode , } ", NULL, handle_PrimaryExpr_NoNode, 0},
{L"PrimaryExprNoBrace_NoNode  :  this ", NULL, handle_PrimaryExprNoBrace_NoNode, 0},
{L"PrimaryExprNoBrace_NoNode  :  Literal_NoNode ", NULL, handle_PrimaryExprNoBrace_NoNode, 0},
{L"PrimaryExprNoBrace_NoNode  :  ArrayLiteral_NoNode ", NULL, handle_PrimaryExprNoBrace_NoNode, 0},
{L"PrimaryExprNoBrace_NoNode  :  IDENTIFIER ", NULL, handle_PrimaryExprNoBrace_NoNode, 0},
{L"PrimaryExprNoBrace_NoNode  :  ( Expr_NoNode ) ", NULL, handle_PrimaryExprNoBrace_NoNode, 0},
{L"ArrayLiteral_NoNode  :  [ ElisionOpt_NoNode ] ", NULL, handle_ArrayLiteral_NoNode, 0},
{L"ArrayLiteral_NoNode  :  [ ElementList_NoNode ] ", NULL, handle_ArrayLiteral_NoNode, 0},
{L"ArrayLiteral_NoNode  :  [ ElementList_NoNode , ElisionOpt_NoNode ] ", NULL, handle_ArrayLiteral_NoNode, 0},
{L"ElementList_NoNode  :  ElisionOpt_NoNode AssignmentExpr_NoNode ", NULL, handle_ElementList_NoNode, 0},
{L"ElementList_NoNode  :  ElementList_NoNode , ElisionOpt_NoNode AssignmentExpr_NoNode ", NULL, handle_ElementList_NoNode, 0},
{L"ElisionOpt_NoNode  :   ", NULL, handle_ElisionOpt_NoNode, 0},
{L"ElisionOpt_NoNode  :  Elision_NoNode ", NULL, handle_ElisionOpt_NoNode, 0},
{L"Elision_NoNode  :  , ", NULL, handle_Elision_NoNode, 0},
{L"Elision_NoNode  :  Elision_NoNode , ", NULL, handle_Elision_NoNode, 0},
{L"MemberExpr_NoNode  :  PrimaryExpr_NoNode ", NULL, handle_MemberExpr_NoNode, 0},
{L"MemberExpr_NoNode  :  FunctionExpr_NoNode ", NULL, handle_MemberExpr_NoNode, 0},
{L"MemberExpr_NoNode  :  MemberExpr_NoNode [ Expr_NoNode ] ", NULL, handle_MemberExpr_NoNode, 0},
{L"MemberExpr_NoNode  :  MemberExpr_NoNode . IDENTIFIER ", NULL, handle_MemberExpr_NoNode, 0},
{L"MemberExpr_NoNode  :  new MemberExpr_NoNode Arguments_NoNode ", NULL, handle_MemberExpr_NoNode, 0},
{L"MemberExprNoBF_NoNode  :  PrimaryExprNoBrace_NoNode ", NULL, handle_MemberExprNoBF_NoNode, 0},
{L"MemberExprNoBF_NoNode  :  MemberExprNoBF_NoNode [ Expr_NoNode ] ", NULL, handle_MemberExprNoBF_NoNode, 0},
{L"MemberExprNoBF_NoNode  :  MemberExprNoBF_NoNode . IDENTIFIER ", NULL, handle_MemberExprNoBF_NoNode, 0},
{L"MemberExprNoBF_NoNode  :  new MemberExpr_NoNode Arguments_NoNode ", NULL, handle_MemberExprNoBF_NoNode, 0},
{L"NewExpr_NoNode  :  MemberExpr_NoNode ", NULL, handle_NewExpr_NoNode, 0},
{L"NewExpr_NoNode  :  new NewExpr_NoNode ", NULL, handle_NewExpr_NoNode, 0},
{L"NewExprNoBF_NoNode  :  MemberExprNoBF_NoNode ", NULL, handle_NewExprNoBF_NoNode, 0},
{L"NewExprNoBF_NoNode  :  new NewExpr_NoNode ", NULL, handle_NewExprNoBF_NoNode, 0},
{L"CallExpr_NoNode  :  MemberExpr_NoNode Arguments_NoNode ", NULL, handle_CallExpr_NoNode, 0},
{L"CallExpr_NoNode  :  CallExpr_NoNode Arguments_NoNode ", NULL, handle_CallExpr_NoNode, 0},
{L"CallExpr_NoNode  :  CallExpr_NoNode [ Expr_NoNode ] ", NULL, handle_CallExpr_NoNode, 0},
{L"CallExpr_NoNode  :  CallExpr_NoNode . IDENTIFIER ", NULL, handle_CallExpr_NoNode, 0},
{L"CallExprNoBF_NoNode  :  MemberExprNoBF_NoNode Arguments_NoNode ", NULL, handle_CallExprNoBF_NoNode, 0},
{L"CallExprNoBF_NoNode  :  CallExprNoBF_NoNode Arguments_NoNode ", NULL, handle_CallExprNoBF_NoNode, 0},
{L"CallExprNoBF_NoNode  :  CallExprNoBF_NoNode [ Expr_NoNode ] ", NULL, handle_CallExprNoBF_NoNode, 0},
{L"CallExprNoBF_NoNode  :  CallExprNoBF_NoNode . IDENTIFIER ", NULL, handle_CallExprNoBF_NoNode, 0},
{L"Arguments_NoNode  :  ( ) ", NULL, handle_Arguments_NoNode, 0},
{L"Arguments_NoNode  :  ( ArgumentList_NoNode ) ", NULL, handle_Arguments_NoNode, 0},
{L"ArgumentList_NoNode  :  AssignmentExpr_NoNode ", NULL, handle_ArgumentList_NoNode, 0},
{L"ArgumentList_NoNode  :  ArgumentList_NoNode , AssignmentExpr_NoNode ", NULL, handle_ArgumentList_NoNode, 0},
{L"LeftHandSideExpr_NoNode  :  NewExpr_NoNode ", NULL, handle_LeftHandSideExpr_NoNode, 0},
{L"LeftHandSideExpr_NoNode  :  CallExpr_NoNode ", NULL, handle_LeftHandSideExpr_NoNode, 0},
{L"LeftHandSideExprNoBF_NoNode  :  NewExprNoBF_NoNode ", NULL, handle_LeftHandSideExprNoBF_NoNode, 0},
{L"LeftHandSideExprNoBF_NoNode  :  CallExprNoBF_NoNode ", NULL, handle_LeftHandSideExprNoBF_NoNode, 0},
{L"PostfixExpr_NoNode  :  LeftHandSideExpr_NoNode ", NULL, handle_PostfixExpr_NoNode, 0},
{L"PostfixExpr_NoNode  :  LeftHandSideExpr_NoNode ++ ", NULL, handle_PostfixExpr_NoNode, 0},
{L"PostfixExpr_NoNode  :  LeftHandSideExpr_NoNode -- ", NULL, handle_PostfixExpr_NoNode, 0},
{L"PostfixExprNoBF_NoNode  :  LeftHandSideExprNoBF_NoNode ", NULL, handle_PostfixExprNoBF_NoNode, 0},
{L"PostfixExprNoBF_NoNode  :  LeftHandSideExprNoBF_NoNode ++ ", NULL, handle_PostfixExprNoBF_NoNode, 0},
{L"PostfixExprNoBF_NoNode  :  LeftHandSideExprNoBF_NoNode -- ", NULL, handle_PostfixExprNoBF_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  delete UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  void UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  typeof UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  ++ UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  -- UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  + UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  - UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  ~ UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExprCommon_NoNode  :  ! UnaryExpr_NoNode ", NULL, handle_UnaryExprCommon_NoNode, 0},
{L"UnaryExpr_NoNode  :  PostfixExpr_NoNode ", NULL, handle_UnaryExpr_NoNode, 0},
{L"UnaryExpr_NoNode  :  UnaryExprCommon_NoNode ", NULL, handle_UnaryExpr_NoNode, 0},
{L"UnaryExprNoBF_NoNode  :  PostfixExprNoBF_NoNode ", NULL, handle_UnaryExprNoBF_NoNode, 0},
{L"UnaryExprNoBF_NoNode  :  UnaryExprCommon_NoNode ", NULL, handle_UnaryExprNoBF_NoNode, 0},
{L"MultiplicativeExpr_NoNode  :  UnaryExpr_NoNode ", NULL, handle_MultiplicativeExpr_NoNode, 0},
{L"MultiplicativeExpr_NoNode  :  MultiplicativeExpr_NoNode * UnaryExpr_NoNode ", NULL, handle_MultiplicativeExpr_NoNode, 0},
{L"MultiplicativeExpr_NoNode  :  MultiplicativeExpr_NoNode / UnaryExpr_NoNode ", NULL, handle_MultiplicativeExpr_NoNode, 0},
{L"MultiplicativeExpr_NoNode  :  MultiplicativeExpr_NoNode % UnaryExpr_NoNode ", NULL, handle_MultiplicativeExpr_NoNode, 0},
{L"MultiplicativeExprNoBF_NoNode  :  UnaryExprNoBF_NoNode ", NULL, handle_MultiplicativeExprNoBF_NoNode, 0},
{L"MultiplicativeExprNoBF_NoNode  :  MultiplicativeExprNoBF_NoNode * UnaryExpr_NoNode ", NULL, handle_MultiplicativeExprNoBF_NoNode, 0},
{L"MultiplicativeExprNoBF_NoNode  :  MultiplicativeExprNoBF_NoNode / UnaryExpr_NoNode ", NULL, handle_MultiplicativeExprNoBF_NoNode, 0},
{L"MultiplicativeExprNoBF_NoNode  :  MultiplicativeExprNoBF_NoNode % UnaryExpr_NoNode ", NULL, handle_MultiplicativeExprNoBF_NoNode, 0},
{L"AdditiveExpr_NoNode  :  MultiplicativeExpr_NoNode ", NULL, handle_AdditiveExpr_NoNode, 0},
{L"AdditiveExpr_NoNode  :  AdditiveExpr_NoNode + MultiplicativeExpr_NoNode ", NULL, handle_AdditiveExpr_NoNode, 0},
{L"AdditiveExpr_NoNode  :  AdditiveExpr_NoNode - MultiplicativeExpr_NoNode ", NULL, handle_AdditiveExpr_NoNode, 0},
{L"AdditiveExprNoBF_NoNode  :  MultiplicativeExprNoBF_NoNode ", NULL, handle_AdditiveExprNoBF_NoNode, 0},
{L"AdditiveExprNoBF_NoNode  :  AdditiveExprNoBF_NoNode + MultiplicativeExpr_NoNode ", NULL, handle_AdditiveExprNoBF_NoNode, 0},
{L"AdditiveExprNoBF_NoNode  :  AdditiveExprNoBF_NoNode - MultiplicativeExpr_NoNode ", NULL, handle_AdditiveExprNoBF_NoNode, 0},
{L"ShiftExpr_NoNode  :  AdditiveExpr_NoNode ", NULL, handle_ShiftExpr_NoNode, 0},
{L"ShiftExpr_NoNode  :  ShiftExpr_NoNode << AdditiveExpr_NoNode ", NULL, handle_ShiftExpr_NoNode, 0},
{L"ShiftExpr_NoNode  :  ShiftExpr_NoNode >> AdditiveExpr_NoNode ", NULL, handle_ShiftExpr_NoNode, 0},
{L"ShiftExpr_NoNode  :  ShiftExpr_NoNode >>> AdditiveExpr_NoNode ", NULL, handle_ShiftExpr_NoNode, 0},
{L"ShiftExprNoBF_NoNode  :  AdditiveExprNoBF_NoNode ", NULL, handle_ShiftExprNoBF_NoNode, 0},
{L"ShiftExprNoBF_NoNode  :  ShiftExprNoBF_NoNode << AdditiveExpr_NoNode ", NULL, handle_ShiftExprNoBF_NoNode, 0},
{L"ShiftExprNoBF_NoNode  :  ShiftExprNoBF_NoNode >> AdditiveExpr_NoNode ", NULL, handle_ShiftExprNoBF_NoNode, 0},
{L"ShiftExprNoBF_NoNode  :  ShiftExprNoBF_NoNode >>> AdditiveExpr_NoNode ", NULL, handle_ShiftExprNoBF_NoNode, 0},
{L"RelationalExpr_NoNode  :  ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExpr_NoNode  :  RelationalExpr_NoNode < ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExpr_NoNode  :  RelationalExpr_NoNode > ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExpr_NoNode  :  RelationalExpr_NoNode <= ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExpr_NoNode  :  RelationalExpr_NoNode >= ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExpr_NoNode  :  RelationalExpr_NoNode instanceof ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExpr_NoNode  :  RelationalExpr_NoNode in ShiftExpr_NoNode ", NULL, handle_RelationalExpr_NoNode, 0},
{L"RelationalExprNoIn_NoNode  :  ShiftExpr_NoNode ", NULL, handle_RelationalExprNoIn_NoNode, 0},
{L"RelationalExprNoIn_NoNode  :  RelationalExprNoIn_NoNode < ShiftExpr_NoNode ", NULL, handle_RelationalExprNoIn_NoNode, 0},
{L"RelationalExprNoIn_NoNode  :  RelationalExprNoIn_NoNode > ShiftExpr_NoNode ", NULL, handle_RelationalExprNoIn_NoNode, 0},
{L"RelationalExprNoIn_NoNode  :  RelationalExprNoIn_NoNode <= ShiftExpr_NoNode ", NULL, handle_RelationalExprNoIn_NoNode, 0},
{L"RelationalExprNoIn_NoNode  :  RelationalExprNoIn_NoNode >= ShiftExpr_NoNode ", NULL, handle_RelationalExprNoIn_NoNode, 0},
{L"RelationalExprNoIn_NoNode  :  RelationalExprNoIn_NoNode instanceof ShiftExpr_NoNode ", NULL, handle_RelationalExprNoIn_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  ShiftExprNoBF_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  RelationalExprNoBF_NoNode < ShiftExpr_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  RelationalExprNoBF_NoNode > ShiftExpr_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  RelationalExprNoBF_NoNode <= ShiftExpr_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  RelationalExprNoBF_NoNode >= ShiftExpr_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  RelationalExprNoBF_NoNode instanceof ShiftExpr_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"RelationalExprNoBF_NoNode  :  RelationalExprNoBF_NoNode in ShiftExpr_NoNode ", NULL, handle_RelationalExprNoBF_NoNode, 0},
{L"EqualityExpr_NoNode  :  RelationalExpr_NoNode ", NULL, handle_EqualityExpr_NoNode, 0},
{L"EqualityExpr_NoNode  :  EqualityExpr_NoNode == RelationalExpr_NoNode ", NULL, handle_EqualityExpr_NoNode, 0},
{L"EqualityExpr_NoNode  :  EqualityExpr_NoNode != RelationalExpr_NoNode ", NULL, handle_EqualityExpr_NoNode, 0},
{L"EqualityExpr_NoNode  :  EqualityExpr_NoNode === RelationalExpr_NoNode ", NULL, handle_EqualityExpr_NoNode, 0},
{L"EqualityExpr_NoNode  :  EqualityExpr_NoNode !== RelationalExpr_NoNode ", NULL, handle_EqualityExpr_NoNode, 0},
{L"EqualityExprNoIn_NoNode  :  RelationalExprNoIn_NoNode ", NULL, handle_EqualityExprNoIn_NoNode, 0},
{L"EqualityExprNoIn_NoNode  :  EqualityExprNoIn_NoNode == RelationalExprNoIn_NoNode ", NULL, handle_EqualityExprNoIn_NoNode, 0},
{L"EqualityExprNoIn_NoNode  :  EqualityExprNoIn_NoNode != RelationalExprNoIn_NoNode ", NULL, handle_EqualityExprNoIn_NoNode, 0},
{L"EqualityExprNoIn_NoNode  :  EqualityExprNoIn_NoNode === RelationalExprNoIn_NoNode ", NULL, handle_EqualityExprNoIn_NoNode, 0},
{L"EqualityExprNoIn_NoNode  :  EqualityExprNoIn_NoNode !== RelationalExprNoIn_NoNode ", NULL, handle_EqualityExprNoIn_NoNode, 0},
{L"EqualityExprNoBF_NoNode  :  RelationalExprNoBF_NoNode ", NULL, handle_EqualityExprNoBF_NoNode, 0},
{L"EqualityExprNoBF_NoNode  :  EqualityExprNoBF_NoNode == RelationalExpr_NoNode ", NULL, handle_EqualityExprNoBF_NoNode, 0},
{L"EqualityExprNoBF_NoNode  :  EqualityExprNoBF_NoNode != RelationalExpr_NoNode ", NULL, handle_EqualityExprNoBF_NoNode, 0},
{L"EqualityExprNoBF_NoNode  :  EqualityExprNoBF_NoNode === RelationalExpr_NoNode ", NULL, handle_EqualityExprNoBF_NoNode, 0},
{L"EqualityExprNoBF_NoNode  :  EqualityExprNoBF_NoNode !== RelationalExpr_NoNode ", NULL, handle_EqualityExprNoBF_NoNode, 0},
{L"BitwiseANDExpr_NoNode  :  EqualityExpr_NoNode ", NULL, handle_BitwiseANDExpr_NoNode, 0},
{L"BitwiseANDExpr_NoNode  :  BitwiseANDExpr_NoNode & EqualityExpr_NoNode ", NULL, handle_BitwiseANDExpr_NoNode, 0},
{L"BitwiseANDExprNoIn_NoNode  :  EqualityExprNoIn_NoNode ", NULL, handle_BitwiseANDExprNoIn_NoNode, 0},
{L"BitwiseANDExprNoIn_NoNode  :  BitwiseANDExprNoIn_NoNode & EqualityExprNoIn_NoNode ", NULL, handle_BitwiseANDExprNoIn_NoNode, 0},
{L"BitwiseANDExprNoBF_NoNode  :  EqualityExprNoBF_NoNode ", NULL, handle_BitwiseANDExprNoBF_NoNode, 0},
{L"BitwiseANDExprNoBF_NoNode  :  BitwiseANDExprNoBF_NoNode & EqualityExpr_NoNode ", NULL, handle_BitwiseANDExprNoBF_NoNode, 0},
{L"BitwiseXORExpr_NoNode  :  BitwiseANDExpr_NoNode ", NULL, handle_BitwiseXORExpr_NoNode, 0},
{L"BitwiseXORExpr_NoNode  :  BitwiseXORExpr_NoNode ^ BitwiseANDExpr_NoNode ", NULL, handle_BitwiseXORExpr_NoNode, 0},
{L"BitwiseXORExprNoIn_NoNode  :  BitwiseANDExprNoIn_NoNode ", NULL, handle_BitwiseXORExprNoIn_NoNode, 0},
{L"BitwiseXORExprNoIn_NoNode  :  BitwiseXORExprNoIn_NoNode ^ BitwiseANDExprNoIn_NoNode ", NULL, handle_BitwiseXORExprNoIn_NoNode, 0},
{L"BitwiseXORExprNoBF_NoNode  :  BitwiseANDExprNoBF_NoNode ", NULL, handle_BitwiseXORExprNoBF_NoNode, 0},
{L"BitwiseXORExprNoBF_NoNode  :  BitwiseXORExprNoBF_NoNode ^ BitwiseANDExpr_NoNode ", NULL, handle_BitwiseXORExprNoBF_NoNode, 0},
{L"BitwiseORExpr_NoNode  :  BitwiseXORExpr_NoNode ", NULL, handle_BitwiseORExpr_NoNode, 0},
{L"BitwiseORExpr_NoNode  :  BitwiseORExpr_NoNode | BitwiseXORExpr_NoNode ", NULL, handle_BitwiseORExpr_NoNode, 0},
{L"BitwiseORExprNoIn_NoNode  :  BitwiseXORExprNoIn_NoNode ", NULL, handle_BitwiseORExprNoIn_NoNode, 0},
{L"BitwiseORExprNoIn_NoNode  :  BitwiseORExprNoIn_NoNode | BitwiseXORExprNoIn_NoNode ", NULL, handle_BitwiseORExprNoIn_NoNode, 0},
{L"BitwiseORExprNoBF_NoNode  :  BitwiseXORExprNoBF_NoNode ", NULL, handle_BitwiseORExprNoBF_NoNode, 0},
{L"BitwiseORExprNoBF_NoNode  :  BitwiseORExprNoBF_NoNode | BitwiseXORExpr_NoNode ", NULL, handle_BitwiseORExprNoBF_NoNode, 0},
{L"LogicalANDExpr_NoNode  :  BitwiseORExpr_NoNode ", NULL, handle_LogicalANDExpr_NoNode, 0},
{L"LogicalANDExpr_NoNode  :  LogicalANDExpr_NoNode && BitwiseORExpr_NoNode ", NULL, handle_LogicalANDExpr_NoNode, 0},
{L"LogicalANDExprNoIn_NoNode  :  BitwiseORExprNoIn_NoNode ", NULL, handle_LogicalANDExprNoIn_NoNode, 0},
{L"LogicalANDExprNoIn_NoNode  :  LogicalANDExprNoIn_NoNode && BitwiseORExprNoIn_NoNode ", NULL, handle_LogicalANDExprNoIn_NoNode, 0},
{L"LogicalANDExprNoBF_NoNode  :  BitwiseORExprNoBF_NoNode ", NULL, handle_LogicalANDExprNoBF_NoNode, 0},
{L"LogicalANDExprNoBF_NoNode  :  LogicalANDExprNoBF_NoNode && BitwiseORExpr_NoNode ", NULL, handle_LogicalANDExprNoBF_NoNode, 0},
{L"LogicalORExpr_NoNode  :  LogicalANDExpr_NoNode ", NULL, handle_LogicalORExpr_NoNode, 0},
{L"LogicalORExpr_NoNode  :  LogicalORExpr_NoNode || LogicalANDExpr_NoNode ", NULL, handle_LogicalORExpr_NoNode, 0},
{L"LogicalORExprNoIn_NoNode  :  LogicalANDExprNoIn_NoNode ", NULL, handle_LogicalORExprNoIn_NoNode, 0},
{L"LogicalORExprNoIn_NoNode  :  LogicalORExprNoIn_NoNode || LogicalANDExprNoIn_NoNode ", NULL, handle_LogicalORExprNoIn_NoNode, 0},
{L"LogicalORExprNoBF_NoNode  :  LogicalANDExprNoBF_NoNode ", NULL, handle_LogicalORExprNoBF_NoNode, 0},
{L"LogicalORExprNoBF_NoNode  :  LogicalORExprNoBF_NoNode || LogicalANDExpr_NoNode ", NULL, handle_LogicalORExprNoBF_NoNode, 0},
{L"ConditionalExpr_NoNode  :  LogicalORExpr_NoNode ", NULL, handle_ConditionalExpr_NoNode, 0},
{L"ConditionalExpr_NoNode  :  LogicalORExpr_NoNode ? AssignmentExpr_NoNode : AssignmentExpr_NoNode ", NULL, handle_ConditionalExpr_NoNode, 0},
{L"ConditionalExprNoIn_NoNode  :  LogicalORExprNoIn_NoNode ", NULL, handle_ConditionalExprNoIn_NoNode, 0},
{L"ConditionalExprNoIn_NoNode  :  LogicalORExprNoIn_NoNode ? AssignmentExprNoIn_NoNode : AssignmentExprNoIn_NoNode ", NULL, handle_ConditionalExprNoIn_NoNode, 0},
{L"ConditionalExprNoBF_NoNode  :  LogicalORExprNoBF_NoNode ", NULL, handle_ConditionalExprNoBF_NoNode, 0},
{L"ConditionalExprNoBF_NoNode  :  LogicalORExprNoBF_NoNode ? AssignmentExpr_NoNode : AssignmentExpr_NoNode ", NULL, handle_ConditionalExprNoBF_NoNode, 0},
{L"AssignmentExpr_NoNode  :  ConditionalExpr_NoNode ", NULL, handle_AssignmentExpr_NoNode, 0},
{L"AssignmentExpr_NoNode  :  LeftHandSideExpr_NoNode AssignmentOperator_NoNode AssignmentExpr_NoNode ", NULL, handle_AssignmentExpr_NoNode, 0},
{L"AssignmentExprNoIn_NoNode  :  ConditionalExprNoIn_NoNode ", NULL, handle_AssignmentExprNoIn_NoNode, 0},
{L"AssignmentExprNoIn_NoNode  :  LeftHandSideExpr_NoNode AssignmentOperator_NoNode AssignmentExprNoIn_NoNode ", NULL, handle_AssignmentExprNoIn_NoNode, 0},
{L"AssignmentExprNoBF_NoNode  :  ConditionalExprNoBF_NoNode ", NULL, handle_AssignmentExprNoBF_NoNode, 0},
{L"AssignmentExprNoBF_NoNode  :  LeftHandSideExprNoBF_NoNode AssignmentOperator_NoNode AssignmentExpr_NoNode ", NULL, handle_AssignmentExprNoBF_NoNode, 0},
{L"AssignmentOperator_NoNode  :  = ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  += ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  -= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  *= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  /= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  <<= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  >>= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  >>>= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  &= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  ^= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  |= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"AssignmentOperator_NoNode  :  %= ", NULL, handle_AssignmentOperator_NoNode, 0},
{L"Expr_NoNode  :  AssignmentExpr_NoNode ", NULL, handle_Expr_NoNode, 0},
{L"Expr_NoNode  :  Expr_NoNode , AssignmentExpr_NoNode ", NULL, handle_Expr_NoNode, 0},
{L"ExprNoIn_NoNode  :  AssignmentExprNoIn_NoNode ", NULL, handle_ExprNoIn_NoNode, 0},
{L"ExprNoIn_NoNode  :  ExprNoIn_NoNode , AssignmentExprNoIn_NoNode ", NULL, handle_ExprNoIn_NoNode, 0},
{L"ExprNoBF_NoNode  :  AssignmentExprNoBF_NoNode ", NULL, handle_ExprNoBF_NoNode, 0},
{L"ExprNoBF_NoNode  :  ExprNoBF_NoNode , AssignmentExpr_NoNode ", NULL, handle_ExprNoBF_NoNode, 0},
{L"Statement_NoNode  :  Block_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  VariableStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  ConstStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  FunctionDeclaration_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  EmptyStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  ExprStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  IfStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  IterationStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  ContinueStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  BreakStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  ReturnStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  WithStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  SwitchStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  LabelledStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  ThrowStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  TryStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Statement_NoNode  :  DebuggerStatement_NoNode ", NULL, handle_Statement_NoNode, 0},
{L"Block_NoNode  :  { } ", NULL, handle_Block_NoNode, 0},
{L"Block_NoNode  :  { SourceElements_NoNode } ", NULL, handle_Block_NoNode, 0},
{L"VariableStatement_NoNode  :  var VariableDeclarationList_NoNode ; ", NULL, handle_VariableStatement_NoNode, 0},
{L"VariableStatement_NoNode  :  var VariableDeclarationList_NoNode error ", NULL, handle_VariableStatement_NoNode, 0},
{L"VariableDeclarationList_NoNode  :  IDENTIFIER ", NULL, handle_VariableDeclarationList_NoNode, 0},
{L"VariableDeclarationList_NoNode  :  IDENTIFIER Initializer_NoNode ", NULL, handle_VariableDeclarationList_NoNode, 0},
{L"VariableDeclarationList_NoNode  :  VariableDeclarationList_NoNode , IDENTIFIER ", NULL, handle_VariableDeclarationList_NoNode, 0},
{L"VariableDeclarationList_NoNode  :  VariableDeclarationList_NoNode , IDENTIFIER Initializer_NoNode ", NULL, handle_VariableDeclarationList_NoNode, 0},
{L"VariableDeclarationListNoIn_NoNode  :  IDENTIFIER ", NULL, handle_VariableDeclarationListNoIn_NoNode, 0},
{L"VariableDeclarationListNoIn_NoNode  :  IDENTIFIER InitializerNoIn_NoNode ", NULL, handle_VariableDeclarationListNoIn_NoNode, 0},
{L"VariableDeclarationListNoIn_NoNode  :  VariableDeclarationListNoIn_NoNode , IDENTIFIER ", NULL, handle_VariableDeclarationListNoIn_NoNode, 0},
{L"VariableDeclarationListNoIn_NoNode  :  VariableDeclarationListNoIn_NoNode , IDENTIFIER InitializerNoIn_NoNode ", NULL, handle_VariableDeclarationListNoIn_NoNode, 0},
{L"ConstStatement_NoNode  :  const ConstDeclarationList_NoNode ; ", NULL, handle_ConstStatement_NoNode, 0},
{L"ConstStatement_NoNode  :  const ConstDeclarationList_NoNode error ", NULL, handle_ConstStatement_NoNode, 0},
{L"ConstDeclarationList_NoNode  :  ConstDeclaration_NoNode ", NULL, handle_ConstDeclarationList_NoNode, 0},
{L"ConstDeclarationList_NoNode  :  ConstDeclarationList_NoNode , ConstDeclaration_NoNode ", NULL, handle_ConstDeclarationList_NoNode, 0},
{L"ConstDeclaration_NoNode  :  IDENTIFIER ", NULL, handle_ConstDeclaration_NoNode, 0},
{L"ConstDeclaration_NoNode  :  IDENTIFIER Initializer_NoNode ", NULL, handle_ConstDeclaration_NoNode, 0},
{L"Initializer_NoNode  :  = AssignmentExpr_NoNode ", NULL, handle_Initializer_NoNode, 0},
{L"InitializerNoIn_NoNode  :  = AssignmentExprNoIn_NoNode ", NULL, handle_InitializerNoIn_NoNode, 0},
{L"EmptyStatement_NoNode  :  ; ", NULL, handle_EmptyStatement_NoNode, 0},
{L"ExprStatement_NoNode  :  ExprNoBF_NoNode ; ", NULL, handle_ExprStatement_NoNode, 0},
{L"ExprStatement_NoNode  :  ExprNoBF_NoNode error ", NULL, handle_ExprStatement_NoNode, 0},
{L"IfStatement_NoNode  :  if ( Expr_NoNode ) Statement_NoNode ", L"IF_WITHOUT_ELSE", handle_IfStatement_NoNode, 0},
{L"IfStatement_NoNode  :  if ( Expr_NoNode ) Statement_NoNode else Statement_NoNode ", NULL, handle_IfStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  do Statement_NoNode while ( Expr_NoNode ) ; ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  do Statement_NoNode while ( Expr_NoNode ) error ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  while ( Expr_NoNode ) Statement_NoNode ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  for ( ExprNoInOpt_NoNode ; ExprOpt_NoNode ; ExprOpt_NoNode ) Statement_NoNode ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  for ( var VariableDeclarationListNoIn_NoNode ; ExprOpt_NoNode ; ExprOpt_NoNode ) Statement_NoNode ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  for ( LeftHandSideExpr_NoNode in Expr_NoNode ) Statement_NoNode ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  for ( var IDENTIFIER in Expr_NoNode ) Statement_NoNode ", NULL, handle_IterationStatement_NoNode, 0},
{L"IterationStatement_NoNode  :  for ( var IDENTIFIER InitializerNoIn_NoNode in Expr_NoNode ) Statement_NoNode ", NULL, handle_IterationStatement_NoNode, 0},
{L"ExprOpt_NoNode  :   ", NULL, handle_ExprOpt_NoNode, 0},
{L"ExprOpt_NoNode  :  Expr_NoNode ", NULL, handle_ExprOpt_NoNode, 0},
{L"ExprNoInOpt_NoNode  :   ", NULL, handle_ExprNoInOpt_NoNode, 0},
{L"ExprNoInOpt_NoNode  :  ExprNoIn_NoNode ", NULL, handle_ExprNoInOpt_NoNode, 0},
{L"ContinueStatement_NoNode  :  continue ; ", NULL, handle_ContinueStatement_NoNode, 0},
{L"ContinueStatement_NoNode  :  continue error ", NULL, handle_ContinueStatement_NoNode, 0},
{L"ContinueStatement_NoNode  :  continue IDENTIFIER ; ", NULL, handle_ContinueStatement_NoNode, 0},
{L"ContinueStatement_NoNode  :  continue IDENTIFIER error ", NULL, handle_ContinueStatement_NoNode, 0},
{L"BreakStatement_NoNode  :  break ; ", NULL, handle_BreakStatement_NoNode, 0},
{L"BreakStatement_NoNode  :  break error ", NULL, handle_BreakStatement_NoNode, 0},
{L"BreakStatement_NoNode  :  break IDENTIFIER ; ", NULL, handle_BreakStatement_NoNode, 0},
{L"BreakStatement_NoNode  :  break IDENTIFIER error ", NULL, handle_BreakStatement_NoNode, 0},
{L"ReturnStatement_NoNode  :  return ; ", NULL, handle_ReturnStatement_NoNode, 0},
{L"ReturnStatement_NoNode  :  return error ", NULL, handle_ReturnStatement_NoNode, 0},
{L"ReturnStatement_NoNode  :  return Expr_NoNode ; ", NULL, handle_ReturnStatement_NoNode, 0},
{L"ReturnStatement_NoNode  :  return Expr_NoNode error ", NULL, handle_ReturnStatement_NoNode, 0},
{L"WithStatement_NoNode  :  with ( Expr_NoNode ) Statement_NoNode ", NULL, handle_WithStatement_NoNode, 0},
{L"SwitchStatement_NoNode  :  switch ( Expr_NoNode ) CaseBlock_NoNode ", NULL, handle_SwitchStatement_NoNode, 0},
{L"CaseBlock_NoNode  :  { CaseClausesOpt_NoNode } ", NULL, handle_CaseBlock_NoNode, 0},
{L"CaseBlock_NoNode  :  { CaseClausesOpt_NoNode DefaultClause_NoNode CaseClausesOpt_NoNode } ", NULL, handle_CaseBlock_NoNode, 0},
{L"CaseClausesOpt_NoNode  :   ", NULL, handle_CaseClausesOpt_NoNode, 0},
{L"CaseClausesOpt_NoNode  :  CaseClauses_NoNode ", NULL, handle_CaseClausesOpt_NoNode, 0},
{L"CaseClauses_NoNode  :  CaseClause_NoNode ", NULL, handle_CaseClauses_NoNode, 0},
{L"CaseClauses_NoNode  :  CaseClauses_NoNode CaseClause_NoNode ", NULL, handle_CaseClauses_NoNode, 0},
{L"CaseClause_NoNode  :  case Expr_NoNode : ", NULL, handle_CaseClause_NoNode, 0},
{L"CaseClause_NoNode  :  case Expr_NoNode : SourceElements_NoNode ", NULL, handle_CaseClause_NoNode, 0},
{L"DefaultClause_NoNode  :  default : ", NULL, handle_DefaultClause_NoNode, 0},
{L"DefaultClause_NoNode  :  default : SourceElements_NoNode ", NULL, handle_DefaultClause_NoNode, 0},
{L"LabelledStatement_NoNode  :  IDENTIFIER : Statement_NoNode ", NULL, handle_LabelledStatement_NoNode, 0},
{L"ThrowStatement_NoNode  :  throw Expr_NoNode ; ", NULL, handle_ThrowStatement_NoNode, 0},
{L"ThrowStatement_NoNode  :  throw Expr_NoNode error ", NULL, handle_ThrowStatement_NoNode, 0},
{L"TryStatement_NoNode  :  try Block_NoNode finally Block_NoNode ", NULL, handle_TryStatement_NoNode, 0},
{L"TryStatement_NoNode  :  try Block_NoNode catch ( IDENTIFIER ) Block_NoNode ", NULL, handle_TryStatement_NoNode, 0},
{L"TryStatement_NoNode  :  try Block_NoNode catch ( IDENTIFIER ) Block_NoNode finally Block_NoNode ", NULL, handle_TryStatement_NoNode, 0},
{L"DebuggerStatement_NoNode  :  debugger ; ", NULL, handle_DebuggerStatement_NoNode, 0},
{L"DebuggerStatement_NoNode  :  debugger error ", NULL, handle_DebuggerStatement_NoNode, 0},
{L"FunctionDeclaration_NoNode  :  function IDENTIFIER ( ) { FunctionBody_NoNode } ", NULL, handle_FunctionDeclaration_NoNode, 0},
{L"FunctionDeclaration_NoNode  :  function IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } ", NULL, handle_FunctionDeclaration_NoNode, 0},
{L"FunctionExpr_NoNode  :  function ( ) { FunctionBody_NoNode } ", NULL, handle_FunctionExpr_NoNode, 0},
{L"FunctionExpr_NoNode  :  function ( FormalParameterList_NoNode ) { FunctionBody_NoNode } ", NULL, handle_FunctionExpr_NoNode, 0},
{L"FunctionExpr_NoNode  :  function IDENTIFIER ( ) { FunctionBody_NoNode } ", NULL, handle_FunctionExpr_NoNode, 0},
{L"FunctionExpr_NoNode  :  function IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } ", NULL, handle_FunctionExpr_NoNode, 0},
{L"FormalParameterList_NoNode  :  IDENTIFIER ", NULL, handle_FormalParameterList_NoNode, 0},
{L"FormalParameterList_NoNode  :  FormalParameterList_NoNode , IDENTIFIER ", NULL, handle_FormalParameterList_NoNode, 0},
{L"FunctionBody_NoNode  :   ", NULL, handle_FunctionBody_NoNode, 0},
{L"FunctionBody_NoNode  :  SourceElements_NoNode ", NULL, handle_FunctionBody_NoNode, 0},
{L"SourceElements_NoNode  :  Statement_NoNode ", NULL, handle_SourceElements_NoNode, 0},
{L"SourceElements_NoNode  :  SourceElements_NoNode Statement_NoNode ", NULL, handle_SourceElements_NoNode, 0}
};

#define __RULE_COUNT__ ((size_t)588)
#define START_RULE L"Program"

static lex_t*	__javascript_build_lex()													
{																				
		lex_t	*lex;															
		size_t i;																
		lex = Lex_Create();														
		for(i = 0; i < __NAME_COUNT__; ++i)										
		{																		
				if(!Lex_Insert(lex, __g_lex_name[i]))							
				{																
						Lex_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		for(i = 0; i < __TERM_COUNT__; ++i)										
		{																		
				lexAction_t		act;											
				act.is_skip		=		__g_term_pattern[i].skip;				
				act.priority	=		__g_term_pattern[i].lex_prec;			
				act.value		=		__g_term_pattern[i].tokval;				
				if(!Lex_InsertRule(lex, __g_term_pattern[i].regex, &act))		
				{																
						Lex_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		return lex;																
}

static psrGrammar_t*	__javascript_build_grammar(const psrHandler_t	*handler)															
{																																
		psrGrammar_t	*grammar;																								
		size_t i;																												
		AR_ASSERT(handler != NULL);																								
		grammar = Parser_CreateGrammar(handler);																				
		for(i = 0; i < __TERM_COUNT__; ++i)																						
		{																														
				if(__g_term_pattern[i].skip || __g_term_pattern[i].tokval == 0)continue;										
				if(!Parser_InsertTerm(grammar, __g_term_pattern[i].name, __g_term_pattern[i].tokval, PARSER_ASSOC_NONASSOC,0, __g_term_pattern[i].leaf))	
				{																												
						Parser_DestroyGrammar(grammar);																			
						grammar = NULL;																							
						AR_ASSERT(false);																						
						return NULL;																							
				}																												
		}																														
		for(i = 0; i < __PREC_COUNT__; ++i)																						
		{																														
				psrTermInfo_t	*info;																							
				info = Parser_GetTermSymbInfoByName(grammar, __g_prec_pattern[i].name);											
				if(info == NULL)																								
				{																												
						if(!Parser_InsertTerm(grammar, __g_prec_pattern[i].name, __g_prec_pattern[i].tokval, __g_prec_pattern[i].assoc, __g_prec_pattern[i].prec_level, NULL))
						{																																					
								Parser_DestroyGrammar(grammar);																												
								grammar = NULL;																																
								AR_ASSERT(false);																															
								return NULL;																																
						}																																					
				}else																																						
				{																																							
						info->assoc = __g_prec_pattern[i].assoc;																											
						info->prec = __g_prec_pattern[i].prec_level;																										
				}																																							
		}																																									
		for(i = 0; i < __RULE_COUNT__; ++i)																													
		{																																									
				if(!Parser_InsertRuleByStr(grammar, __g_rule_pattern[i].rule, __g_rule_pattern[i].prec_token, __g_rule_pattern[i].handler, __g_rule_pattern[i].auto_ret))		
				{																																							
						Parser_DestroyGrammar(grammar);																														
						grammar = NULL;																																		
						AR_ASSERT(false);																																	
						return NULL;																																		
				}																																							
		}																																									
		if(!Parser_SetStartRule(grammar,START_RULE) || !Parser_CheckIsValidGrammar(grammar, NULL))																			
		{																																									
				Parser_DestroyGrammar(grammar);																																
				grammar = NULL;																																				
				AR_ASSERT(false);																																			
				return NULL;																																				
		}																																									
		return grammar;																																						
}




/*Literal	:	null */
/*Literal	:	true */
/*Literal	:	false */
/*Literal	:	NUMBER */
/*Literal	:	STRING_LITERAL */
static psrNode_t* AR_STDCALL handle_Literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Property	:	IDENTIFIER : AssignmentExpr */
/*Property	:	STRING_LITERAL : AssignmentExpr */
/*Property	:	NUMBER : AssignmentExpr */
/*Property	:	IDENTIFIER IDENTIFIER ( ) { FunctionBody } */
/*Property	:	IDENTIFIER IDENTIFIER ( FormalParameterList ) { FunctionBody } */
static psrNode_t* AR_STDCALL handle_Property(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PropertyList	:	Property */
/*PropertyList	:	PropertyList , Property */
static psrNode_t* AR_STDCALL handle_PropertyList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PrimaryExpr	:	PrimaryExprNoBrace */
/*PrimaryExpr	:	{ } */
/*PrimaryExpr	:	{ PropertyList } */
/*PrimaryExpr	:	{ PropertyList , } */
static psrNode_t* AR_STDCALL handle_PrimaryExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PrimaryExprNoBrace	:	this */
/*PrimaryExprNoBrace	:	Literal */
/*PrimaryExprNoBrace	:	ArrayLiteral */
/*PrimaryExprNoBrace	:	IDENTIFIER */
/*PrimaryExprNoBrace	:	( Expr ) */
static psrNode_t* AR_STDCALL handle_PrimaryExprNoBrace(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ArrayLiteral	:	[ ElisionOpt ] */
/*ArrayLiteral	:	[ ElementList ] */
/*ArrayLiteral	:	[ ElementList , ElisionOpt ] */
static psrNode_t* AR_STDCALL handle_ArrayLiteral(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ElementList	:	ElisionOpt AssignmentExpr */
/*ElementList	:	ElementList , ElisionOpt AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ElementList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ElisionOpt	:	 */
/*ElisionOpt	:	Elision */
static psrNode_t* AR_STDCALL handle_ElisionOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Elision	:	, */
/*Elision	:	Elision , */
static psrNode_t* AR_STDCALL handle_Elision(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MemberExpr	:	PrimaryExpr */
/*MemberExpr	:	FunctionExpr */
/*MemberExpr	:	MemberExpr [ Expr ] */
/*MemberExpr	:	MemberExpr . IDENTIFIER */
/*MemberExpr	:	new MemberExpr Arguments */
static psrNode_t* AR_STDCALL handle_MemberExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MemberExprNoBF	:	PrimaryExprNoBrace */
/*MemberExprNoBF	:	MemberExprNoBF [ Expr ] */
/*MemberExprNoBF	:	MemberExprNoBF . IDENTIFIER */
/*MemberExprNoBF	:	new MemberExpr Arguments */
static psrNode_t* AR_STDCALL handle_MemberExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*NewExpr	:	MemberExpr */
/*NewExpr	:	new NewExpr */
static psrNode_t* AR_STDCALL handle_NewExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*NewExprNoBF	:	MemberExprNoBF */
/*NewExprNoBF	:	new NewExpr */
static psrNode_t* AR_STDCALL handle_NewExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CallExpr	:	MemberExpr Arguments */
/*CallExpr	:	CallExpr Arguments */
/*CallExpr	:	CallExpr [ Expr ] */
/*CallExpr	:	CallExpr . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CallExprNoBF	:	MemberExprNoBF Arguments */
/*CallExprNoBF	:	CallExprNoBF Arguments */
/*CallExprNoBF	:	CallExprNoBF [ Expr ] */
/*CallExprNoBF	:	CallExprNoBF . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Arguments	:	( ) */
/*Arguments	:	( ArgumentList ) */
static psrNode_t* AR_STDCALL handle_Arguments(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ArgumentList	:	AssignmentExpr */
/*ArgumentList	:	ArgumentList , AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ArgumentList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LeftHandSideExpr	:	NewExpr */
/*LeftHandSideExpr	:	CallExpr */
static psrNode_t* AR_STDCALL handle_LeftHandSideExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LeftHandSideExprNoBF	:	NewExprNoBF */
/*LeftHandSideExprNoBF	:	CallExprNoBF */
static psrNode_t* AR_STDCALL handle_LeftHandSideExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PostfixExpr	:	LeftHandSideExpr */
/*PostfixExpr	:	LeftHandSideExpr ++ */
/*PostfixExpr	:	LeftHandSideExpr -- */
static psrNode_t* AR_STDCALL handle_PostfixExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PostfixExprNoBF	:	LeftHandSideExprNoBF */
/*PostfixExprNoBF	:	LeftHandSideExprNoBF ++ */
/*PostfixExprNoBF	:	LeftHandSideExprNoBF -- */
static psrNode_t* AR_STDCALL handle_PostfixExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*UnaryExprCommon	:	delete UnaryExpr */
/*UnaryExprCommon	:	void UnaryExpr */
/*UnaryExprCommon	:	typeof UnaryExpr */
/*UnaryExprCommon	:	++ UnaryExpr */
/*UnaryExprCommon	:	-- UnaryExpr */
/*UnaryExprCommon	:	+ UnaryExpr */
/*UnaryExprCommon	:	- UnaryExpr */
/*UnaryExprCommon	:	~ UnaryExpr */
/*UnaryExprCommon	:	! UnaryExpr */
static psrNode_t* AR_STDCALL handle_UnaryExprCommon(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*UnaryExpr	:	PostfixExpr */
/*UnaryExpr	:	UnaryExprCommon */
static psrNode_t* AR_STDCALL handle_UnaryExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*UnaryExprNoBF	:	PostfixExprNoBF */
/*UnaryExprNoBF	:	UnaryExprCommon */
static psrNode_t* AR_STDCALL handle_UnaryExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MultiplicativeExpr	:	UnaryExpr */
/*MultiplicativeExpr	:	MultiplicativeExpr * UnaryExpr */
/*MultiplicativeExpr	:	MultiplicativeExpr / UnaryExpr */
/*MultiplicativeExpr	:	MultiplicativeExpr % UnaryExpr */
static psrNode_t* AR_STDCALL handle_MultiplicativeExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MultiplicativeExprNoBF	:	UnaryExprNoBF */
/*MultiplicativeExprNoBF	:	MultiplicativeExprNoBF * UnaryExpr */
/*MultiplicativeExprNoBF	:	MultiplicativeExprNoBF / UnaryExpr */
/*MultiplicativeExprNoBF	:	MultiplicativeExprNoBF % UnaryExpr */
static psrNode_t* AR_STDCALL handle_MultiplicativeExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AdditiveExpr	:	MultiplicativeExpr */
/*AdditiveExpr	:	AdditiveExpr + MultiplicativeExpr */
/*AdditiveExpr	:	AdditiveExpr - MultiplicativeExpr */
static psrNode_t* AR_STDCALL handle_AdditiveExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AdditiveExprNoBF	:	MultiplicativeExprNoBF */
/*AdditiveExprNoBF	:	AdditiveExprNoBF + MultiplicativeExpr */
/*AdditiveExprNoBF	:	AdditiveExprNoBF - MultiplicativeExpr */
static psrNode_t* AR_STDCALL handle_AdditiveExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ShiftExpr	:	AdditiveExpr */
/*ShiftExpr	:	ShiftExpr << AdditiveExpr */
/*ShiftExpr	:	ShiftExpr >> AdditiveExpr */
/*ShiftExpr	:	ShiftExpr >>> AdditiveExpr */
static psrNode_t* AR_STDCALL handle_ShiftExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ShiftExprNoBF	:	AdditiveExprNoBF */
/*ShiftExprNoBF	:	ShiftExprNoBF << AdditiveExpr */
/*ShiftExprNoBF	:	ShiftExprNoBF >> AdditiveExpr */
/*ShiftExprNoBF	:	ShiftExprNoBF >>> AdditiveExpr */
static psrNode_t* AR_STDCALL handle_ShiftExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*RelationalExpr	:	ShiftExpr */
/*RelationalExpr	:	RelationalExpr < ShiftExpr */
/*RelationalExpr	:	RelationalExpr > ShiftExpr */
/*RelationalExpr	:	RelationalExpr <= ShiftExpr */
/*RelationalExpr	:	RelationalExpr >= ShiftExpr */
/*RelationalExpr	:	RelationalExpr instanceof ShiftExpr */
/*RelationalExpr	:	RelationalExpr in ShiftExpr */
static psrNode_t* AR_STDCALL handle_RelationalExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*RelationalExprNoIn	:	ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn < ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn > ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn <= ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn >= ShiftExpr */
/*RelationalExprNoIn	:	RelationalExprNoIn instanceof ShiftExpr */
static psrNode_t* AR_STDCALL handle_RelationalExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*RelationalExprNoBF	:	ShiftExprNoBF */
/*RelationalExprNoBF	:	RelationalExprNoBF < ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF > ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF <= ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF >= ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF instanceof ShiftExpr */
/*RelationalExprNoBF	:	RelationalExprNoBF in ShiftExpr */
static psrNode_t* AR_STDCALL handle_RelationalExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EqualityExpr	:	RelationalExpr */
/*EqualityExpr	:	EqualityExpr == RelationalExpr */
/*EqualityExpr	:	EqualityExpr != RelationalExpr */
/*EqualityExpr	:	EqualityExpr === RelationalExpr */
/*EqualityExpr	:	EqualityExpr !== RelationalExpr */
static psrNode_t* AR_STDCALL handle_EqualityExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EqualityExprNoIn	:	RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn == RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn != RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn === RelationalExprNoIn */
/*EqualityExprNoIn	:	EqualityExprNoIn !== RelationalExprNoIn */
static psrNode_t* AR_STDCALL handle_EqualityExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EqualityExprNoBF	:	RelationalExprNoBF */
/*EqualityExprNoBF	:	EqualityExprNoBF == RelationalExpr */
/*EqualityExprNoBF	:	EqualityExprNoBF != RelationalExpr */
/*EqualityExprNoBF	:	EqualityExprNoBF === RelationalExpr */
/*EqualityExprNoBF	:	EqualityExprNoBF !== RelationalExpr */
static psrNode_t* AR_STDCALL handle_EqualityExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseANDExpr	:	EqualityExpr */
/*BitwiseANDExpr	:	BitwiseANDExpr & EqualityExpr */
static psrNode_t* AR_STDCALL handle_BitwiseANDExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseANDExprNoIn	:	EqualityExprNoIn */
/*BitwiseANDExprNoIn	:	BitwiseANDExprNoIn & EqualityExprNoIn */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseANDExprNoBF	:	EqualityExprNoBF */
/*BitwiseANDExprNoBF	:	BitwiseANDExprNoBF & EqualityExpr */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseXORExpr	:	BitwiseANDExpr */
/*BitwiseXORExpr	:	BitwiseXORExpr ^ BitwiseANDExpr */
static psrNode_t* AR_STDCALL handle_BitwiseXORExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseXORExprNoIn	:	BitwiseANDExprNoIn */
/*BitwiseXORExprNoIn	:	BitwiseXORExprNoIn ^ BitwiseANDExprNoIn */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseXORExprNoBF	:	BitwiseANDExprNoBF */
/*BitwiseXORExprNoBF	:	BitwiseXORExprNoBF ^ BitwiseANDExpr */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseORExpr	:	BitwiseXORExpr */
/*BitwiseORExpr	:	BitwiseORExpr | BitwiseXORExpr */
static psrNode_t* AR_STDCALL handle_BitwiseORExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseORExprNoIn	:	BitwiseXORExprNoIn */
/*BitwiseORExprNoIn	:	BitwiseORExprNoIn | BitwiseXORExprNoIn */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseORExprNoBF	:	BitwiseXORExprNoBF */
/*BitwiseORExprNoBF	:	BitwiseORExprNoBF | BitwiseXORExpr */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalANDExpr	:	BitwiseORExpr */
/*LogicalANDExpr	:	LogicalANDExpr && BitwiseORExpr */
static psrNode_t* AR_STDCALL handle_LogicalANDExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalANDExprNoIn	:	BitwiseORExprNoIn */
/*LogicalANDExprNoIn	:	LogicalANDExprNoIn && BitwiseORExprNoIn */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalANDExprNoBF	:	BitwiseORExprNoBF */
/*LogicalANDExprNoBF	:	LogicalANDExprNoBF && BitwiseORExpr */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalORExpr	:	LogicalANDExpr */
/*LogicalORExpr	:	LogicalORExpr || LogicalANDExpr */
static psrNode_t* AR_STDCALL handle_LogicalORExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalORExprNoIn	:	LogicalANDExprNoIn */
/*LogicalORExprNoIn	:	LogicalORExprNoIn || LogicalANDExprNoIn */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalORExprNoBF	:	LogicalANDExprNoBF */
/*LogicalORExprNoBF	:	LogicalORExprNoBF || LogicalANDExpr */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConditionalExpr	:	LogicalORExpr */
/*ConditionalExpr	:	LogicalORExpr ? AssignmentExpr : AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ConditionalExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConditionalExprNoIn	:	LogicalORExprNoIn */
/*ConditionalExprNoIn	:	LogicalORExprNoIn ? AssignmentExprNoIn : AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConditionalExprNoBF	:	LogicalORExprNoBF */
/*ConditionalExprNoBF	:	LogicalORExprNoBF ? AssignmentExpr : AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentExpr	:	ConditionalExpr */
/*AssignmentExpr	:	LeftHandSideExpr AssignmentOperator AssignmentExpr */
static psrNode_t* AR_STDCALL handle_AssignmentExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentExprNoIn	:	ConditionalExprNoIn */
/*AssignmentExprNoIn	:	LeftHandSideExpr AssignmentOperator AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentExprNoBF	:	ConditionalExprNoBF */
/*AssignmentExprNoBF	:	LeftHandSideExprNoBF AssignmentOperator AssignmentExpr */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentOperator	:	= */
/*AssignmentOperator	:	+= */
/*AssignmentOperator	:	-= */
/*AssignmentOperator	:	*= */
/*AssignmentOperator	:	/= */
/*AssignmentOperator	:	<<= */
/*AssignmentOperator	:	>>= */
/*AssignmentOperator	:	>>>= */
/*AssignmentOperator	:	&= */
/*AssignmentOperator	:	^= */
/*AssignmentOperator	:	|= */
/*AssignmentOperator	:	%= */
static psrNode_t* AR_STDCALL handle_AssignmentOperator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Expr	:	AssignmentExpr */
/*Expr	:	Expr , AssignmentExpr */
static psrNode_t* AR_STDCALL handle_Expr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprNoIn	:	AssignmentExprNoIn */
/*ExprNoIn	:	ExprNoIn , AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_ExprNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprNoBF	:	AssignmentExprNoBF */
/*ExprNoBF	:	ExprNoBF , AssignmentExpr */
static psrNode_t* AR_STDCALL handle_ExprNoBF(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Statement	:	Block */
/*Statement	:	VariableStatement */
/*Statement	:	ConstStatement */
/*Statement	:	FunctionDeclaration */
/*Statement	:	EmptyStatement */
/*Statement	:	ExprStatement */
/*Statement	:	IfStatement */
/*Statement	:	IterationStatement */
/*Statement	:	ContinueStatement */
/*Statement	:	BreakStatement */
/*Statement	:	ReturnStatement */
/*Statement	:	WithStatement */
/*Statement	:	SwitchStatement */
/*Statement	:	LabelledStatement */
/*Statement	:	ThrowStatement */
/*Statement	:	TryStatement */
/*Statement	:	DebuggerStatement */
static psrNode_t* AR_STDCALL handle_Statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Block	:	{ } */
/*Block	:	{ SourceElements } */
static psrNode_t* AR_STDCALL handle_Block(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*VariableStatement	:	var VariableDeclarationList ; */
/*VariableStatement	:	var VariableDeclarationList error */
static psrNode_t* AR_STDCALL handle_VariableStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*VariableDeclarationList	:	IDENTIFIER */
/*VariableDeclarationList	:	IDENTIFIER Initializer */
/*VariableDeclarationList	:	VariableDeclarationList , IDENTIFIER */
/*VariableDeclarationList	:	VariableDeclarationList , IDENTIFIER Initializer */
static psrNode_t* AR_STDCALL handle_VariableDeclarationList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*VariableDeclarationListNoIn	:	IDENTIFIER */
/*VariableDeclarationListNoIn	:	IDENTIFIER InitializerNoIn */
/*VariableDeclarationListNoIn	:	VariableDeclarationListNoIn , IDENTIFIER */
/*VariableDeclarationListNoIn	:	VariableDeclarationListNoIn , IDENTIFIER InitializerNoIn */
static psrNode_t* AR_STDCALL handle_VariableDeclarationListNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConstStatement	:	const ConstDeclarationList ; */
/*ConstStatement	:	const ConstDeclarationList error */
static psrNode_t* AR_STDCALL handle_ConstStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConstDeclarationList	:	ConstDeclaration */
/*ConstDeclarationList	:	ConstDeclarationList , ConstDeclaration */
static psrNode_t* AR_STDCALL handle_ConstDeclarationList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConstDeclaration	:	IDENTIFIER */
/*ConstDeclaration	:	IDENTIFIER Initializer */
static psrNode_t* AR_STDCALL handle_ConstDeclaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Initializer	:	= AssignmentExpr */
static psrNode_t* AR_STDCALL handle_Initializer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*InitializerNoIn	:	= AssignmentExprNoIn */
static psrNode_t* AR_STDCALL handle_InitializerNoIn(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EmptyStatement	:	; */
static psrNode_t* AR_STDCALL handle_EmptyStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprStatement	:	ExprNoBF ; */
/*ExprStatement	:	ExprNoBF error */
static psrNode_t* AR_STDCALL handle_ExprStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*IfStatement	:	if ( Expr ) Statement */
/*IfStatement	:	if ( Expr ) Statement else Statement */
static psrNode_t* AR_STDCALL handle_IfStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*IterationStatement	:	do Statement while ( Expr ) ; */
/*IterationStatement	:	do Statement while ( Expr ) error */
/*IterationStatement	:	while ( Expr ) Statement */
/*IterationStatement	:	for ( ExprNoInOpt ; ExprOpt ; ExprOpt ) Statement */
/*IterationStatement	:	for ( var VariableDeclarationListNoIn ; ExprOpt ; ExprOpt ) Statement */
/*IterationStatement	:	for ( LeftHandSideExpr in Expr ) Statement */
/*IterationStatement	:	for ( var IDENTIFIER in Expr ) Statement */
/*IterationStatement	:	for ( var IDENTIFIER InitializerNoIn in Expr ) Statement */
static psrNode_t* AR_STDCALL handle_IterationStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprOpt	:	 */
/*ExprOpt	:	Expr */
static psrNode_t* AR_STDCALL handle_ExprOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprNoInOpt	:	 */
/*ExprNoInOpt	:	ExprNoIn */
static psrNode_t* AR_STDCALL handle_ExprNoInOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ContinueStatement	:	continue ; */
/*ContinueStatement	:	continue error */
/*ContinueStatement	:	continue IDENTIFIER ; */
/*ContinueStatement	:	continue IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_ContinueStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BreakStatement	:	break ; */
/*BreakStatement	:	break error */
/*BreakStatement	:	break IDENTIFIER ; */
/*BreakStatement	:	break IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_BreakStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ReturnStatement	:	return ; */
/*ReturnStatement	:	return error */
/*ReturnStatement	:	return Expr ; */
/*ReturnStatement	:	return Expr error */
static psrNode_t* AR_STDCALL handle_ReturnStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*WithStatement	:	with ( Expr ) Statement */
static psrNode_t* AR_STDCALL handle_WithStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*SwitchStatement	:	switch ( Expr ) CaseBlock */
static psrNode_t* AR_STDCALL handle_SwitchStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseBlock	:	{ CaseClausesOpt } */
/*CaseBlock	:	{ CaseClausesOpt DefaultClause CaseClausesOpt } */
static psrNode_t* AR_STDCALL handle_CaseBlock(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseClausesOpt	:	 */
/*CaseClausesOpt	:	CaseClauses */
static psrNode_t* AR_STDCALL handle_CaseClausesOpt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseClauses	:	CaseClause */
/*CaseClauses	:	CaseClauses CaseClause */
static psrNode_t* AR_STDCALL handle_CaseClauses(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseClause	:	case Expr : */
/*CaseClause	:	case Expr : SourceElements */
static psrNode_t* AR_STDCALL handle_CaseClause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*DefaultClause	:	default : */
/*DefaultClause	:	default : SourceElements */
static psrNode_t* AR_STDCALL handle_DefaultClause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LabelledStatement	:	IDENTIFIER : Statement */
static psrNode_t* AR_STDCALL handle_LabelledStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ThrowStatement	:	throw Expr ; */
/*ThrowStatement	:	throw Expr error */
static psrNode_t* AR_STDCALL handle_ThrowStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*TryStatement	:	try Block finally Block */
/*TryStatement	:	try Block catch ( IDENTIFIER ) Block */
/*TryStatement	:	try Block catch ( IDENTIFIER ) Block finally Block */
static psrNode_t* AR_STDCALL handle_TryStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*DebuggerStatement	:	debugger ; */
/*DebuggerStatement	:	debugger error */
static psrNode_t* AR_STDCALL handle_DebuggerStatement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FunctionDeclaration	:	function IDENTIFIER ( ) { FunctionBody } */
/*FunctionDeclaration	:	function IDENTIFIER ( FormalParameterList ) { FunctionBody } */
static psrNode_t* AR_STDCALL handle_FunctionDeclaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FunctionExpr	:	function ( ) { FunctionBody } */
/*FunctionExpr	:	function ( FormalParameterList ) { FunctionBody } */
/*FunctionExpr	:	function IDENTIFIER ( ) { FunctionBody } */
/*FunctionExpr	:	function IDENTIFIER ( FormalParameterList ) { FunctionBody } */
static psrNode_t* AR_STDCALL handle_FunctionExpr(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FormalParameterList	:	IDENTIFIER */
/*FormalParameterList	:	FormalParameterList , IDENTIFIER */
static psrNode_t* AR_STDCALL handle_FormalParameterList(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FunctionBody	:	 */
/*FunctionBody	:	SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_FunctionBody(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Program	:	 */
/*Program	:	SourceElements */
static psrNode_t* AR_STDCALL handle_Program(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*SourceElements	:	Statement */
/*SourceElements	:	SourceElements Statement */
static psrNode_t* AR_STDCALL handle_SourceElements(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Literal_NoNode	:	null */
/*Literal_NoNode	:	true */
/*Literal_NoNode	:	false */
/*Literal_NoNode	:	NUMBER */
/*Literal_NoNode	:	STRING_LITERAL */
static psrNode_t* AR_STDCALL handle_Literal_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Property_NoNode	:	IDENTIFIER : AssignmentExpr_NoNode */
/*Property_NoNode	:	STRING_LITERAL : AssignmentExpr_NoNode */
/*Property_NoNode	:	NUMBER : AssignmentExpr_NoNode */
/*Property_NoNode	:	IDENTIFIER IDENTIFIER ( ) { FunctionBody_NoNode } */
/*Property_NoNode	:	IDENTIFIER IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
static psrNode_t* AR_STDCALL handle_Property_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PropertyList_NoNode	:	Property_NoNode */
/*PropertyList_NoNode	:	PropertyList_NoNode , Property_NoNode */
static psrNode_t* AR_STDCALL handle_PropertyList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PrimaryExpr_NoNode	:	PrimaryExprNoBrace_NoNode */
/*PrimaryExpr_NoNode	:	{ } */
/*PrimaryExpr_NoNode	:	{ PropertyList_NoNode } */
/*PrimaryExpr_NoNode	:	{ PropertyList_NoNode , } */
static psrNode_t* AR_STDCALL handle_PrimaryExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PrimaryExprNoBrace_NoNode	:	this */
/*PrimaryExprNoBrace_NoNode	:	Literal_NoNode */
/*PrimaryExprNoBrace_NoNode	:	ArrayLiteral_NoNode */
/*PrimaryExprNoBrace_NoNode	:	IDENTIFIER */
/*PrimaryExprNoBrace_NoNode	:	( Expr_NoNode ) */
static psrNode_t* AR_STDCALL handle_PrimaryExprNoBrace_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ArrayLiteral_NoNode	:	[ ElisionOpt_NoNode ] */
/*ArrayLiteral_NoNode	:	[ ElementList_NoNode ] */
/*ArrayLiteral_NoNode	:	[ ElementList_NoNode , ElisionOpt_NoNode ] */
static psrNode_t* AR_STDCALL handle_ArrayLiteral_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ElementList_NoNode	:	ElisionOpt_NoNode AssignmentExpr_NoNode */
/*ElementList_NoNode	:	ElementList_NoNode , ElisionOpt_NoNode AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ElementList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ElisionOpt_NoNode	:	 */
/*ElisionOpt_NoNode	:	Elision_NoNode */
static psrNode_t* AR_STDCALL handle_ElisionOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Elision_NoNode	:	, */
/*Elision_NoNode	:	Elision_NoNode , */
static psrNode_t* AR_STDCALL handle_Elision_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MemberExpr_NoNode	:	PrimaryExpr_NoNode */
/*MemberExpr_NoNode	:	FunctionExpr_NoNode */
/*MemberExpr_NoNode	:	MemberExpr_NoNode [ Expr_NoNode ] */
/*MemberExpr_NoNode	:	MemberExpr_NoNode . IDENTIFIER */
/*MemberExpr_NoNode	:	new MemberExpr_NoNode Arguments_NoNode */
static psrNode_t* AR_STDCALL handle_MemberExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MemberExprNoBF_NoNode	:	PrimaryExprNoBrace_NoNode */
/*MemberExprNoBF_NoNode	:	MemberExprNoBF_NoNode [ Expr_NoNode ] */
/*MemberExprNoBF_NoNode	:	MemberExprNoBF_NoNode . IDENTIFIER */
/*MemberExprNoBF_NoNode	:	new MemberExpr_NoNode Arguments_NoNode */
static psrNode_t* AR_STDCALL handle_MemberExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*NewExpr_NoNode	:	MemberExpr_NoNode */
/*NewExpr_NoNode	:	new NewExpr_NoNode */
static psrNode_t* AR_STDCALL handle_NewExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*NewExprNoBF_NoNode	:	MemberExprNoBF_NoNode */
/*NewExprNoBF_NoNode	:	new NewExpr_NoNode */
static psrNode_t* AR_STDCALL handle_NewExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CallExpr_NoNode	:	MemberExpr_NoNode Arguments_NoNode */
/*CallExpr_NoNode	:	CallExpr_NoNode Arguments_NoNode */
/*CallExpr_NoNode	:	CallExpr_NoNode [ Expr_NoNode ] */
/*CallExpr_NoNode	:	CallExpr_NoNode . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CallExprNoBF_NoNode	:	MemberExprNoBF_NoNode Arguments_NoNode */
/*CallExprNoBF_NoNode	:	CallExprNoBF_NoNode Arguments_NoNode */
/*CallExprNoBF_NoNode	:	CallExprNoBF_NoNode [ Expr_NoNode ] */
/*CallExprNoBF_NoNode	:	CallExprNoBF_NoNode . IDENTIFIER */
static psrNode_t* AR_STDCALL handle_CallExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Arguments_NoNode	:	( ) */
/*Arguments_NoNode	:	( ArgumentList_NoNode ) */
static psrNode_t* AR_STDCALL handle_Arguments_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ArgumentList_NoNode	:	AssignmentExpr_NoNode */
/*ArgumentList_NoNode	:	ArgumentList_NoNode , AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ArgumentList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LeftHandSideExpr_NoNode	:	NewExpr_NoNode */
/*LeftHandSideExpr_NoNode	:	CallExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LeftHandSideExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LeftHandSideExprNoBF_NoNode	:	NewExprNoBF_NoNode */
/*LeftHandSideExprNoBF_NoNode	:	CallExprNoBF_NoNode */
static psrNode_t* AR_STDCALL handle_LeftHandSideExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PostfixExpr_NoNode	:	LeftHandSideExpr_NoNode */
/*PostfixExpr_NoNode	:	LeftHandSideExpr_NoNode ++ */
/*PostfixExpr_NoNode	:	LeftHandSideExpr_NoNode -- */
static psrNode_t* AR_STDCALL handle_PostfixExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*PostfixExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode */
/*PostfixExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode ++ */
/*PostfixExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode -- */
static psrNode_t* AR_STDCALL handle_PostfixExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*UnaryExprCommon_NoNode	:	delete UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	void UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	typeof UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	++ UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	-- UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	+ UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	- UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	~ UnaryExpr_NoNode */
/*UnaryExprCommon_NoNode	:	! UnaryExpr_NoNode */
static psrNode_t* AR_STDCALL handle_UnaryExprCommon_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*UnaryExpr_NoNode	:	PostfixExpr_NoNode */
/*UnaryExpr_NoNode	:	UnaryExprCommon_NoNode */
static psrNode_t* AR_STDCALL handle_UnaryExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*UnaryExprNoBF_NoNode	:	PostfixExprNoBF_NoNode */
/*UnaryExprNoBF_NoNode	:	UnaryExprCommon_NoNode */
static psrNode_t* AR_STDCALL handle_UnaryExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MultiplicativeExpr_NoNode	:	UnaryExpr_NoNode */
/*MultiplicativeExpr_NoNode	:	MultiplicativeExpr_NoNode * UnaryExpr_NoNode */
/*MultiplicativeExpr_NoNode	:	MultiplicativeExpr_NoNode / UnaryExpr_NoNode */
/*MultiplicativeExpr_NoNode	:	MultiplicativeExpr_NoNode % UnaryExpr_NoNode */
static psrNode_t* AR_STDCALL handle_MultiplicativeExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*MultiplicativeExprNoBF_NoNode	:	UnaryExprNoBF_NoNode */
/*MultiplicativeExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode * UnaryExpr_NoNode */
/*MultiplicativeExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode / UnaryExpr_NoNode */
/*MultiplicativeExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode % UnaryExpr_NoNode */
static psrNode_t* AR_STDCALL handle_MultiplicativeExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AdditiveExpr_NoNode	:	MultiplicativeExpr_NoNode */
/*AdditiveExpr_NoNode	:	AdditiveExpr_NoNode + MultiplicativeExpr_NoNode */
/*AdditiveExpr_NoNode	:	AdditiveExpr_NoNode - MultiplicativeExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AdditiveExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AdditiveExprNoBF_NoNode	:	MultiplicativeExprNoBF_NoNode */
/*AdditiveExprNoBF_NoNode	:	AdditiveExprNoBF_NoNode + MultiplicativeExpr_NoNode */
/*AdditiveExprNoBF_NoNode	:	AdditiveExprNoBF_NoNode - MultiplicativeExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AdditiveExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ShiftExpr_NoNode	:	AdditiveExpr_NoNode */
/*ShiftExpr_NoNode	:	ShiftExpr_NoNode << AdditiveExpr_NoNode */
/*ShiftExpr_NoNode	:	ShiftExpr_NoNode >> AdditiveExpr_NoNode */
/*ShiftExpr_NoNode	:	ShiftExpr_NoNode >>> AdditiveExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ShiftExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ShiftExprNoBF_NoNode	:	AdditiveExprNoBF_NoNode */
/*ShiftExprNoBF_NoNode	:	ShiftExprNoBF_NoNode << AdditiveExpr_NoNode */
/*ShiftExprNoBF_NoNode	:	ShiftExprNoBF_NoNode >> AdditiveExpr_NoNode */
/*ShiftExprNoBF_NoNode	:	ShiftExprNoBF_NoNode >>> AdditiveExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ShiftExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*RelationalExpr_NoNode	:	ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode < ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode > ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode <= ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode >= ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode instanceof ShiftExpr_NoNode */
/*RelationalExpr_NoNode	:	RelationalExpr_NoNode in ShiftExpr_NoNode */
static psrNode_t* AR_STDCALL handle_RelationalExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*RelationalExprNoIn_NoNode	:	ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode < ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode > ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode <= ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode >= ShiftExpr_NoNode */
/*RelationalExprNoIn_NoNode	:	RelationalExprNoIn_NoNode instanceof ShiftExpr_NoNode */
static psrNode_t* AR_STDCALL handle_RelationalExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*RelationalExprNoBF_NoNode	:	ShiftExprNoBF_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode < ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode > ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode <= ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode >= ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode instanceof ShiftExpr_NoNode */
/*RelationalExprNoBF_NoNode	:	RelationalExprNoBF_NoNode in ShiftExpr_NoNode */
static psrNode_t* AR_STDCALL handle_RelationalExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EqualityExpr_NoNode	:	RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode == RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode != RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode === RelationalExpr_NoNode */
/*EqualityExpr_NoNode	:	EqualityExpr_NoNode !== RelationalExpr_NoNode */
static psrNode_t* AR_STDCALL handle_EqualityExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EqualityExprNoIn_NoNode	:	RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode == RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode != RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode === RelationalExprNoIn_NoNode */
/*EqualityExprNoIn_NoNode	:	EqualityExprNoIn_NoNode !== RelationalExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_EqualityExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EqualityExprNoBF_NoNode	:	RelationalExprNoBF_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode == RelationalExpr_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode != RelationalExpr_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode === RelationalExpr_NoNode */
/*EqualityExprNoBF_NoNode	:	EqualityExprNoBF_NoNode !== RelationalExpr_NoNode */
static psrNode_t* AR_STDCALL handle_EqualityExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseANDExpr_NoNode	:	EqualityExpr_NoNode */
/*BitwiseANDExpr_NoNode	:	BitwiseANDExpr_NoNode & EqualityExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseANDExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseANDExprNoIn_NoNode	:	EqualityExprNoIn_NoNode */
/*BitwiseANDExprNoIn_NoNode	:	BitwiseANDExprNoIn_NoNode & EqualityExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseANDExprNoBF_NoNode	:	EqualityExprNoBF_NoNode */
/*BitwiseANDExprNoBF_NoNode	:	BitwiseANDExprNoBF_NoNode & EqualityExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseANDExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseXORExpr_NoNode	:	BitwiseANDExpr_NoNode */
/*BitwiseXORExpr_NoNode	:	BitwiseXORExpr_NoNode ^ BitwiseANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseXORExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseXORExprNoIn_NoNode	:	BitwiseANDExprNoIn_NoNode */
/*BitwiseXORExprNoIn_NoNode	:	BitwiseXORExprNoIn_NoNode ^ BitwiseANDExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseXORExprNoBF_NoNode	:	BitwiseANDExprNoBF_NoNode */
/*BitwiseXORExprNoBF_NoNode	:	BitwiseXORExprNoBF_NoNode ^ BitwiseANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseXORExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseORExpr_NoNode	:	BitwiseXORExpr_NoNode */
/*BitwiseORExpr_NoNode	:	BitwiseORExpr_NoNode | BitwiseXORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseORExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseORExprNoIn_NoNode	:	BitwiseXORExprNoIn_NoNode */
/*BitwiseORExprNoIn_NoNode	:	BitwiseORExprNoIn_NoNode | BitwiseXORExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BitwiseORExprNoBF_NoNode	:	BitwiseXORExprNoBF_NoNode */
/*BitwiseORExprNoBF_NoNode	:	BitwiseORExprNoBF_NoNode | BitwiseXORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_BitwiseORExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalANDExpr_NoNode	:	BitwiseORExpr_NoNode */
/*LogicalANDExpr_NoNode	:	LogicalANDExpr_NoNode && BitwiseORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalANDExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalANDExprNoIn_NoNode	:	BitwiseORExprNoIn_NoNode */
/*LogicalANDExprNoIn_NoNode	:	LogicalANDExprNoIn_NoNode && BitwiseORExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalANDExprNoBF_NoNode	:	BitwiseORExprNoBF_NoNode */
/*LogicalANDExprNoBF_NoNode	:	LogicalANDExprNoBF_NoNode && BitwiseORExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalANDExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalORExpr_NoNode	:	LogicalANDExpr_NoNode */
/*LogicalORExpr_NoNode	:	LogicalORExpr_NoNode || LogicalANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalORExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalORExprNoIn_NoNode	:	LogicalANDExprNoIn_NoNode */
/*LogicalORExprNoIn_NoNode	:	LogicalORExprNoIn_NoNode || LogicalANDExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LogicalORExprNoBF_NoNode	:	LogicalANDExprNoBF_NoNode */
/*LogicalORExprNoBF_NoNode	:	LogicalORExprNoBF_NoNode || LogicalANDExpr_NoNode */
static psrNode_t* AR_STDCALL handle_LogicalORExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConditionalExpr_NoNode	:	LogicalORExpr_NoNode */
/*ConditionalExpr_NoNode	:	LogicalORExpr_NoNode ? AssignmentExpr_NoNode : AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ConditionalExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConditionalExprNoIn_NoNode	:	LogicalORExprNoIn_NoNode */
/*ConditionalExprNoIn_NoNode	:	LogicalORExprNoIn_NoNode ? AssignmentExprNoIn_NoNode : AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConditionalExprNoBF_NoNode	:	LogicalORExprNoBF_NoNode */
/*ConditionalExprNoBF_NoNode	:	LogicalORExprNoBF_NoNode ? AssignmentExpr_NoNode : AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ConditionalExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentExpr_NoNode	:	ConditionalExpr_NoNode */
/*AssignmentExpr_NoNode	:	LeftHandSideExpr_NoNode AssignmentOperator_NoNode AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AssignmentExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentExprNoIn_NoNode	:	ConditionalExprNoIn_NoNode */
/*AssignmentExprNoIn_NoNode	:	LeftHandSideExpr_NoNode AssignmentOperator_NoNode AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentExprNoBF_NoNode	:	ConditionalExprNoBF_NoNode */
/*AssignmentExprNoBF_NoNode	:	LeftHandSideExprNoBF_NoNode AssignmentOperator_NoNode AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_AssignmentExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*AssignmentOperator_NoNode	:	= */
/*AssignmentOperator_NoNode	:	+= */
/*AssignmentOperator_NoNode	:	-= */
/*AssignmentOperator_NoNode	:	*= */
/*AssignmentOperator_NoNode	:	/= */
/*AssignmentOperator_NoNode	:	<<= */
/*AssignmentOperator_NoNode	:	>>= */
/*AssignmentOperator_NoNode	:	>>>= */
/*AssignmentOperator_NoNode	:	&= */
/*AssignmentOperator_NoNode	:	^= */
/*AssignmentOperator_NoNode	:	|= */
/*AssignmentOperator_NoNode	:	%= */
static psrNode_t* AR_STDCALL handle_AssignmentOperator_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Expr_NoNode	:	AssignmentExpr_NoNode */
/*Expr_NoNode	:	Expr_NoNode , AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_Expr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprNoIn_NoNode	:	AssignmentExprNoIn_NoNode */
/*ExprNoIn_NoNode	:	ExprNoIn_NoNode , AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_ExprNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprNoBF_NoNode	:	AssignmentExprNoBF_NoNode */
/*ExprNoBF_NoNode	:	ExprNoBF_NoNode , AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_ExprNoBF_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Statement_NoNode	:	Block_NoNode */
/*Statement_NoNode	:	VariableStatement_NoNode */
/*Statement_NoNode	:	ConstStatement_NoNode */
/*Statement_NoNode	:	FunctionDeclaration_NoNode */
/*Statement_NoNode	:	EmptyStatement_NoNode */
/*Statement_NoNode	:	ExprStatement_NoNode */
/*Statement_NoNode	:	IfStatement_NoNode */
/*Statement_NoNode	:	IterationStatement_NoNode */
/*Statement_NoNode	:	ContinueStatement_NoNode */
/*Statement_NoNode	:	BreakStatement_NoNode */
/*Statement_NoNode	:	ReturnStatement_NoNode */
/*Statement_NoNode	:	WithStatement_NoNode */
/*Statement_NoNode	:	SwitchStatement_NoNode */
/*Statement_NoNode	:	LabelledStatement_NoNode */
/*Statement_NoNode	:	ThrowStatement_NoNode */
/*Statement_NoNode	:	TryStatement_NoNode */
/*Statement_NoNode	:	DebuggerStatement_NoNode */
static psrNode_t* AR_STDCALL handle_Statement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Block_NoNode	:	{ } */
/*Block_NoNode	:	{ SourceElements_NoNode } */
static psrNode_t* AR_STDCALL handle_Block_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*VariableStatement_NoNode	:	var VariableDeclarationList_NoNode ; */
/*VariableStatement_NoNode	:	var VariableDeclarationList_NoNode error */
static psrNode_t* AR_STDCALL handle_VariableStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*VariableDeclarationList_NoNode	:	IDENTIFIER */
/*VariableDeclarationList_NoNode	:	IDENTIFIER Initializer_NoNode */
/*VariableDeclarationList_NoNode	:	VariableDeclarationList_NoNode , IDENTIFIER */
/*VariableDeclarationList_NoNode	:	VariableDeclarationList_NoNode , IDENTIFIER Initializer_NoNode */
static psrNode_t* AR_STDCALL handle_VariableDeclarationList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*VariableDeclarationListNoIn_NoNode	:	IDENTIFIER */
/*VariableDeclarationListNoIn_NoNode	:	IDENTIFIER InitializerNoIn_NoNode */
/*VariableDeclarationListNoIn_NoNode	:	VariableDeclarationListNoIn_NoNode , IDENTIFIER */
/*VariableDeclarationListNoIn_NoNode	:	VariableDeclarationListNoIn_NoNode , IDENTIFIER InitializerNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_VariableDeclarationListNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConstStatement_NoNode	:	const ConstDeclarationList_NoNode ; */
/*ConstStatement_NoNode	:	const ConstDeclarationList_NoNode error */
static psrNode_t* AR_STDCALL handle_ConstStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConstDeclarationList_NoNode	:	ConstDeclaration_NoNode */
/*ConstDeclarationList_NoNode	:	ConstDeclarationList_NoNode , ConstDeclaration_NoNode */
static psrNode_t* AR_STDCALL handle_ConstDeclarationList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ConstDeclaration_NoNode	:	IDENTIFIER */
/*ConstDeclaration_NoNode	:	IDENTIFIER Initializer_NoNode */
static psrNode_t* AR_STDCALL handle_ConstDeclaration_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*Initializer_NoNode	:	= AssignmentExpr_NoNode */
static psrNode_t* AR_STDCALL handle_Initializer_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*InitializerNoIn_NoNode	:	= AssignmentExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_InitializerNoIn_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*EmptyStatement_NoNode	:	; */
static psrNode_t* AR_STDCALL handle_EmptyStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprStatement_NoNode	:	ExprNoBF_NoNode ; */
/*ExprStatement_NoNode	:	ExprNoBF_NoNode error */
static psrNode_t* AR_STDCALL handle_ExprStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*IfStatement_NoNode	:	if ( Expr_NoNode ) Statement_NoNode */
/*IfStatement_NoNode	:	if ( Expr_NoNode ) Statement_NoNode else Statement_NoNode */
static psrNode_t* AR_STDCALL handle_IfStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*IterationStatement_NoNode	:	do Statement_NoNode while ( Expr_NoNode ) ; */
/*IterationStatement_NoNode	:	do Statement_NoNode while ( Expr_NoNode ) error */
/*IterationStatement_NoNode	:	while ( Expr_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( ExprNoInOpt_NoNode ; ExprOpt_NoNode ; ExprOpt_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( var VariableDeclarationListNoIn_NoNode ; ExprOpt_NoNode ; ExprOpt_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( LeftHandSideExpr_NoNode in Expr_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( var IDENTIFIER in Expr_NoNode ) Statement_NoNode */
/*IterationStatement_NoNode	:	for ( var IDENTIFIER InitializerNoIn_NoNode in Expr_NoNode ) Statement_NoNode */
static psrNode_t* AR_STDCALL handle_IterationStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprOpt_NoNode	:	 */
/*ExprOpt_NoNode	:	Expr_NoNode */
static psrNode_t* AR_STDCALL handle_ExprOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ExprNoInOpt_NoNode	:	 */
/*ExprNoInOpt_NoNode	:	ExprNoIn_NoNode */
static psrNode_t* AR_STDCALL handle_ExprNoInOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ContinueStatement_NoNode	:	continue ; */
/*ContinueStatement_NoNode	:	continue error */
/*ContinueStatement_NoNode	:	continue IDENTIFIER ; */
/*ContinueStatement_NoNode	:	continue IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_ContinueStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*BreakStatement_NoNode	:	break ; */
/*BreakStatement_NoNode	:	break error */
/*BreakStatement_NoNode	:	break IDENTIFIER ; */
/*BreakStatement_NoNode	:	break IDENTIFIER error */
static psrNode_t* AR_STDCALL handle_BreakStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ReturnStatement_NoNode	:	return ; */
/*ReturnStatement_NoNode	:	return error */
/*ReturnStatement_NoNode	:	return Expr_NoNode ; */
/*ReturnStatement_NoNode	:	return Expr_NoNode error */
static psrNode_t* AR_STDCALL handle_ReturnStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*WithStatement_NoNode	:	with ( Expr_NoNode ) Statement_NoNode */
static psrNode_t* AR_STDCALL handle_WithStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*SwitchStatement_NoNode	:	switch ( Expr_NoNode ) CaseBlock_NoNode */
static psrNode_t* AR_STDCALL handle_SwitchStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseBlock_NoNode	:	{ CaseClausesOpt_NoNode } */
/*CaseBlock_NoNode	:	{ CaseClausesOpt_NoNode DefaultClause_NoNode CaseClausesOpt_NoNode } */
static psrNode_t* AR_STDCALL handle_CaseBlock_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseClausesOpt_NoNode	:	 */
/*CaseClausesOpt_NoNode	:	CaseClauses_NoNode */
static psrNode_t* AR_STDCALL handle_CaseClausesOpt_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseClauses_NoNode	:	CaseClause_NoNode */
/*CaseClauses_NoNode	:	CaseClauses_NoNode CaseClause_NoNode */
static psrNode_t* AR_STDCALL handle_CaseClauses_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*CaseClause_NoNode	:	case Expr_NoNode : */
/*CaseClause_NoNode	:	case Expr_NoNode : SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_CaseClause_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*DefaultClause_NoNode	:	default : */
/*DefaultClause_NoNode	:	default : SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_DefaultClause_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*LabelledStatement_NoNode	:	IDENTIFIER : Statement_NoNode */
static psrNode_t* AR_STDCALL handle_LabelledStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ThrowStatement_NoNode	:	throw Expr_NoNode ; */
/*ThrowStatement_NoNode	:	throw Expr_NoNode error */
static psrNode_t* AR_STDCALL handle_ThrowStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*TryStatement_NoNode	:	try Block_NoNode finally Block_NoNode */
/*TryStatement_NoNode	:	try Block_NoNode catch ( IDENTIFIER ) Block_NoNode */
/*TryStatement_NoNode	:	try Block_NoNode catch ( IDENTIFIER ) Block_NoNode finally Block_NoNode */
static psrNode_t* AR_STDCALL handle_TryStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*DebuggerStatement_NoNode	:	debugger ; */
/*DebuggerStatement_NoNode	:	debugger error */
static psrNode_t* AR_STDCALL handle_DebuggerStatement_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FunctionDeclaration_NoNode	:	function IDENTIFIER ( ) { FunctionBody_NoNode } */
/*FunctionDeclaration_NoNode	:	function IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
static psrNode_t* AR_STDCALL handle_FunctionDeclaration_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FunctionExpr_NoNode	:	function ( ) { FunctionBody_NoNode } */
/*FunctionExpr_NoNode	:	function ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
/*FunctionExpr_NoNode	:	function IDENTIFIER ( ) { FunctionBody_NoNode } */
/*FunctionExpr_NoNode	:	function IDENTIFIER ( FormalParameterList_NoNode ) { FunctionBody_NoNode } */
static psrNode_t* AR_STDCALL handle_FunctionExpr_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FormalParameterList_NoNode	:	IDENTIFIER */
/*FormalParameterList_NoNode	:	FormalParameterList_NoNode , IDENTIFIER */
static psrNode_t* AR_STDCALL handle_FormalParameterList_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*FunctionBody_NoNode	:	 */
/*FunctionBody_NoNode	:	SourceElements_NoNode */
static psrNode_t* AR_STDCALL handle_FunctionBody_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*SourceElements_NoNode	:	Statement_NoNode */
/*SourceElements_NoNode	:	SourceElements_NoNode Statement_NoNode */
static psrNode_t* AR_STDCALL handle_SourceElements_NoNode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




#endif
