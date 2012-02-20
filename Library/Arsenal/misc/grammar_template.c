
static const wchar_t *__g_lex_name[] = {
L"delim = [ \\r\\n\\t]",
L"comment = /\\*([^\\*]|\\*+[^\\*/])*\\*+/",
L"comment_line = //[^\\n]*\\n",
L"digit = [0-9]",
L"number = {digit}+",
L"letter = [A-Z_a-z]",
L"int_type_suffix = ((u|U)?(l|L))|((u|U)(l|L)?)",
L"octal_escape = (\\\\[0-3][0-7][0-7])|(\\\\[0-7][0-7])|(\\\\[0-7])",
L"hex_digit = [0-9a-fA-F]",
L"hex_literal = 0(x|X){hex_digit}+{int_type_suffix}?",
L"dec_literal = (0|[1-9][0-9]*){int_type_suffix}?",
L"oct_literal = 0[0-7]+{int_type_suffix}?",
L"exponet = (e|E)(\\+|\\-)?[0-9]+",
L"float_type_suffix = (f|F|d|D)",
L"float_literal = ([0-9]*\\.[0-9]*{exponet}?{float_type_suffix}?)",
L"skip_lexem = {delim}|{comment}|{comment_line}",
L"escape_seq = (\\\\(b|t|n|f|r|\\x22|\\x27|\\\\))|{octal_escape}",
L"string_literal = (\\x22({escape_seq}|[^\\x22\\\\])*\\x22)",
L"char_literal = \\x27({escape_seq}|[^\\x27\\\\])\\x27",
L"keyword_lhd = [A-Z_a-z0-9]"
};

#define __NAME_COUNT__ ((size_t)20)

static struct {const wchar_t *name; size_t tokval; size_t lex_prec; const wchar_t *regex; bool_t skip; }__g_term_pattern[] =  {
{NULL, 256,1, L"{delim}+|{comment}+|{comment_line}+", true},
{L"TYPE_ID", TOK_TYPE_ID, 0, L"^$", false},
{L"DONE_ID", TOK_DONE_ID, 0, L"^$", false},
{L"CHAR_CONSTANT", TOK_CHAR_CONSTANT, 0, L"{char_literal}", false},
{L"STRING_LITERAL", TOK_STRING_LITERAL, 0, L"{string_literal}", false},
{L"FLOAT_CONSTANT", TOK_FLOAT_CONSTANT, 2, L"{float_literal}(?!{keyword_lhd})", false},
{L"HEX_CONSTANT", TOK_HEX_CONSTANT, 2, L"{hex_literal}(?!{keyword_lhd})", false},
{L"OCT_CONSTANT", TOK_OCT_CONSTANT, 1, L"{oct_literal}(?!{keyword_lhd})", false},
{L"DEC_CONSTANT", TOK_DEC_CONSTANT, 1, L"{dec_literal}(?!{keyword_lhd})", false},
{L"IDENTIFIER", TOK_IDENTIFIER, 0, L"{letter}({letter}|{digit})*", false},
{L"switch", TOK_SWITCH, 1, L"\"switch\"(?!{keyword_lhd})", false},
{L"for", TOK_FOR, 1, L"\"for\"(?!{keyword_lhd})", false},
{L"goto", TOK_GOTO, 1, L"\"goto\"(?!{keyword_lhd})", false},
{L"return", TOK_RETURN, 1, L"\"return\"(?!{keyword_lhd})", false},
{L"do", TOK_DO, 1, L"\"do\"(?!{keyword_lhd})", false},
{L"while", TOK_WHILE, 1, L"\"while\"(?!{keyword_lhd})", false},
{L"if", TOK_IF, 1, L"\"if\"(?!{keyword_lhd})", false},
{L"else", TOK_ELSE, 1, L"\"else\"(?!{keyword_lhd})", false},
{L"continue", TOK_CONTINUE, 1, L"\"continue\"(?!{keyword_lhd})", false},
{L"default", TOK_DEFAULT, 1, L"\"default\"(?!{keyword_lhd})", false},
{L"case", TOK_CASE, 1, L"\"case\"(?!{keyword_lhd})", false},
{L"break", TOK_BREAK, 1, L"\"break\"(?!{keyword_lhd})", false},
{L"sizeof", TOK_SIZEOF, 1, L"\"sizeof\"(?!{keyword_lhd})", false},
{L"const", TOK_CONST, 1, L"\"const\"(?!{keyword_lhd})", false},
{L"volatile", TOK_VOLATILE, 1, L"\"volatile\"(?!{keyword_lhd})", false},
{L"struct", TOK_STRUCT, 1, L"\"struct\"(?!{keyword_lhd})", false},
{L"union", TOK_UNION, 1, L"\"union\"(?!{keyword_lhd})", false},
{L"typedef", TOK_TYPEDEF, 1, L"\"typedef\"(?!{keyword_lhd})", false},
{L"static", TOK_STATIC, 1, L"\"static\"(?!{keyword_lhd})", false},
{L"void", TOK_VOID, 1, L"\"void\"(?!{keyword_lhd})", false},
{L"byte", TOK_BYTE, 1, L"\"byte\"(?!{keyword_lhd})", false},
{L"char", TOK_CHAR, 1, L"\"char\"(?!{keyword_lhd})", false},
{L"short", TOK_SHORT, 1, L"\"short\"(?!{keyword_lhd})", false},
{L"int", TOK_INT, 1, L"\"int\"(?!{keyword_lhd})", false},
{L"long", TOK_LONG, 1, L"\"long\"(?!{keyword_lhd})", false},
{L"signed", TOK_SIGNED, 1, L"\"signed\"(?!{keyword_lhd})", false},
{L"unsigned", TOK_UNSIGNED, 1, L"\"unsigned\"(?!{keyword_lhd})", false},
{L"float", TOK_FLOAT, 1, L"\"float\"(?!{keyword_lhd})", false},
{L"double", TOK_DOUBLE, 1, L"\"double\"(?!{keyword_lhd})", false},
{L"import", TOK_IMPORT, 1, L"\"import\"(?!{keyword_lhd})", false},
{L"export", TOK_EXPORT, 1, L"\"export\"(?!{keyword_lhd})", false},
{L"attribute", TOK_ATTRIBUTE, 1, L"\"attribute\"", false},
{L">>=", TOK_RIGHT_ASSIGN, 2, L"\">>=\"", false},
{L"<<=", TOK_LEFT_ASSIGN, 2, L"\"<<=\"", false},
{L"+=", TOK_ADD_ASSIGN, 1, L"\"+=\"", false},
{L"-=", TOK_SUB_ASSIGN, 1, L"\"-=\"", false},
{L"*=", TOK_MUL_ASSIGN, 1, L"\"*=\"", false},
{L"/=", TOK_DIV_ASSIGN, 1, L"\"/=\"", false},
{L"%=", TOK_MOD_ASSIGN, 1, L"\"%=\"", false},
{L"&=", TOK_AND_ASSIGN, 1, L"\"&=\"", false},
{L"^=", TOK_XOR_ASSIGN, 1, L"\"^=\"", false},
{L"|=", TOK_OR_ASSIGN, 1, L"\"|=\"", false},
{L">>", TOK_RIGHT_OP, 1, L"\">>\"", false},
{L"<<", TOK_LEFT_OP, 1, L"\"<<\"", false},
{L"++", TOK_INC_OP, 1, L"\"++\"", false},
{L"--", TOK_DEC_OP, 1, L"\"--\"", false},
{L"->", TOK_PTR_OP, 1, L"\"->\"", false},
{L"&&", TOK_AND_OP, 1, L"\"&&\"", false},
{L"||", TOK_OR_OP, 1, L"\"||\"", false},
{L"<=", TOK_LE_OP, 1, L"\"<=\"", false},
{L">=", TOK_GE_OP, 1, L"\">=\"", false},
{L"==", TOK_EQ_OP, 1, L"\"==\"", false},
{L"!=", TOK_NE_OP, 1, L"\"!=\"", false},
{L"<", TOK_LESS_OP, 0, L"\"<\"", false},
{L">", TOK_GREATER_OP, 0, L"\">\"", false},
{L";", TOK_SEMICOLON, 0, L"\";\"", false},
{L"{", TOK_L_BRACES, 0, L"\"{\"", false},
{L"}", TOK_R_BRACES, 0, L"\"}\"", false},
{L",", TOK_COMMA, 0, L"\",\"", false},
{L":", TOK_COLON, 0, L"\":\"", false},
{L"=", TOK_ASSIGN, 0, L"\"=\"", false},
{L"(", TOK_L_PAREN, 0, L"\"(\"", false},
{L")", TOK_R_PAREN, 0, L"\")\"", false},
{L"[", TOK_L_SQUARE, 0, L"\"[\"", false},
{L"]", TOK_R_SQUARE, 0, L"\"]\"", false},
{L".", TOK_DOT, 0, L"\".\"", false},
{L"&", TOK_AND, 0, L"\"&\"", false},
{L"!", TOK_NOT, 0, L"\"!\"", false},
{L"~", TOK_TILDE, 0, L"\"~\"", false},
{L"+", TOK_ADD, 0, L"\"+\"", false},
{L"-", TOK_SUB, 0, L"\"-\"", false},
{L"*", TOK_MUL, 0, L"\"*\"", false},
{L"/", TOK_DIV, 0, L"\"/\"", false},
{L"%", TOK_MOD, 0, L"\"%\"", false},
{L"^", TOK_XOR, 0, L"\"^\"", false},
{L"|", TOK_OR, 0, L"\"|\"", false},
{L"?", TOK_QUEST, 0, L"\"?\"", false},
{L"EOI", 0, 2, L"$", false}
};

#define __TERM_COUNT__ ((size_t)88)

static struct {const wchar_t *name; size_t tokval; size_t prec_level; psrAssocType_t	assoc;}__g_prec_pattern[] =  {
{L"||", TOK_OR_OP,1, PSR_ASSOC_LEFT},
{L"&&", TOK_AND_OP,2, PSR_ASSOC_LEFT},
{L"|", TOK_OR,3, PSR_ASSOC_LEFT},
{L"^", TOK_XOR,4, PSR_ASSOC_LEFT},
{L"&", TOK_AND,5, PSR_ASSOC_LEFT},
{L"==", TOK_EQ_OP,6, PSR_ASSOC_LEFT},
{L"!=", TOK_NE_OP,6, PSR_ASSOC_LEFT},
{L"<", TOK_LESS_OP,7, PSR_ASSOC_LEFT},
{L"<=", TOK_LE_OP,7, PSR_ASSOC_LEFT},
{L">", TOK_GREATER_OP,7, PSR_ASSOC_LEFT},
{L">=", TOK_GE_OP,7, PSR_ASSOC_LEFT},
{L"<<", TOK_LEFT_OP,8, PSR_ASSOC_LEFT},
{L">>", TOK_RIGHT_OP,8, PSR_ASSOC_LEFT},
{L"+", TOK_ADD,9, PSR_ASSOC_LEFT},
{L"-", TOK_SUB,9, PSR_ASSOC_LEFT},
{L"*", TOK_MUL,10, PSR_ASSOC_LEFT},
{L"/", TOK_DIV,10, PSR_ASSOC_LEFT},
{L"%", TOK_MOD,10, PSR_ASSOC_LEFT},
{L"IF_STMT_PREC", 343,11, PSR_ASSOC_NONASSOC},
{L"IF_STMT_ELSE_STMT_PREC", 344,12, PSR_ASSOC_NONASSOC}
};

#define __PREC_COUNT__ ((size_t)12)

/*translation_unit	:	external_declaration */
/*translation_unit	:	translation_unit external_declaration */
static psrNode_t* AR_STDCALL handle_translation_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*external_declaration	:	function_definition */
/*external_declaration	:	declaration */
/*external_declaration	:	access_unit */
/*external_declaration	:	attribute_unit */
static psrNode_t* AR_STDCALL handle_external_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*access_unit	:	import_or_export STRING_LITERAL ; */
/*access_unit	:	import_or_export error ; */
static psrNode_t* AR_STDCALL handle_access_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*import_or_export	:	import */
/*import_or_export	:	export */
static psrNode_t* AR_STDCALL handle_import_or_export(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*attribute_unit	:	attribute STRING_LITERAL ; */
/*attribute_unit	:	attribute error ; */
static psrNode_t* AR_STDCALL handle_attribute_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*function_declaration	:	declaration_specifiers declarator */
static psrNode_t* AR_STDCALL handle_function_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*function_definition	:	function_declaration compound_statement */
static psrNode_t* AR_STDCALL handle_function_definition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_qualifier	:	const */
/*type_qualifier	:	volatile */
static psrNode_t* AR_STDCALL handle_type_qualifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_qualifier_list	:	type_qualifier_list type_qualifier */
/*type_qualifier_list	:	type_qualifier */
static psrNode_t* AR_STDCALL handle_type_qualifier_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_specifier	:	void */
/*type_specifier	:	byte */
/*type_specifier	:	char */
/*type_specifier	:	short */
/*type_specifier	:	int */
/*type_specifier	:	long */
/*type_specifier	:	float */
/*type_specifier	:	double */
/*type_specifier	:	signed */
/*type_specifier	:	unsigned */
/*type_specifier	:	struct_or_union_specifier */
/*type_specifier	:	TYPE_ID */
static psrNode_t* AR_STDCALL handle_type_specifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*struct_or_union_specifier	:	struct_or_union IDENTIFIER { struct_declaration_list } */
/*struct_or_union_specifier	:	struct_or_union { struct_declaration_list } */
/*struct_or_union_specifier	:	struct_or_union IDENTIFIER */
static psrNode_t* AR_STDCALL handle_struct_or_union_specifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*struct_or_union	:	struct */
/*struct_or_union	:	union */
static psrNode_t* AR_STDCALL handle_struct_or_union(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*struct_declaration_list	:	struct_declaration */
/*struct_declaration_list	:	struct_declaration_list struct_declaration */
static psrNode_t* AR_STDCALL handle_struct_declaration_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*struct_declaration	:	specifier_qualifier_list struct_declarator_list ; */
static psrNode_t* AR_STDCALL handle_struct_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*struct_declarator_list	:	declarator */
/*struct_declarator_list	:	struct_declarator_list , declarator */
static psrNode_t* AR_STDCALL handle_struct_declarator_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*declaration	:	declaration_specifiers init_declarator_list ; */
/*declaration	:	declaration_specifiers ; */
/*declaration	:	error */
static psrNode_t* AR_STDCALL handle_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*storage_class_specifier	:	typedef */
/*storage_class_specifier	:	static */
static psrNode_t* AR_STDCALL handle_storage_class_specifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*declaration_specifiers	:	storage_class_specifier */
/*declaration_specifiers	:	storage_class_specifier declaration_specifiers */
/*declaration_specifiers	:	type_specifier */
/*declaration_specifiers	:	type_specifier declaration_specifiers */
/*declaration_specifiers	:	type_qualifier */
/*declaration_specifiers	:	type_qualifier declaration_specifiers */
static psrNode_t* AR_STDCALL handle_declaration_specifiers(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*declaration_list	:	declaration */
/*declaration_list	:	declaration_list declaration */
static psrNode_t* AR_STDCALL handle_declaration_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*init_declarator_list	:	init_declarator */
/*init_declarator_list	:	init_declarator_list , init_declarator */
static psrNode_t* AR_STDCALL handle_init_declarator_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*init_declarator	:	declarator */
/*init_declarator	:	declarator = initializer */
static psrNode_t* AR_STDCALL handle_init_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*initializer	:	assignment_expression */
/*initializer	:	{ initializer_list } */
static psrNode_t* AR_STDCALL handle_initializer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*initializer_list	:	initializer */
/*initializer_list	:	initializer_list , initializer */
static psrNode_t* AR_STDCALL handle_initializer_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*declarator	:	direct_declarator */
/*declarator	:	pointer direct_declarator */
static psrNode_t* AR_STDCALL handle_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*direct_declarator	:	IDENTIFIER */
/*direct_declarator	:	IDENTIFIER [ constant_expression ] */
/*direct_declarator	:	IDENTIFIER [ ] */
/*direct_declarator	:	IDENTIFIER ( parameter_list ) */
/*direct_declarator	:	IDENTIFIER ( ) */
static psrNode_t* AR_STDCALL handle_direct_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*abstract_declarator	:	pointer */
/*abstract_declarator	:	direct_abstract_declarator */
/*abstract_declarator	:	pointer direct_abstract_declarator */
static psrNode_t* AR_STDCALL handle_abstract_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*direct_abstract_declarator	:	[ ] */
/*direct_abstract_declarator	:	[ constant_expression ] */
static psrNode_t* AR_STDCALL handle_direct_abstract_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*pointer	:	* */
/*pointer	:	* type_qualifier_list */
/*pointer	:	* type_qualifier_list pointer */
/*pointer	:	* pointer */
static psrNode_t* AR_STDCALL handle_pointer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*parameter_list	:	parameter_declaration */
/*parameter_list	:	parameter_list , parameter_declaration */
static psrNode_t* AR_STDCALL handle_parameter_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*parameter_declaration	:	declaration_specifiers declarator */
/*parameter_declaration	:	declaration_specifiers abstract_declarator */
/*parameter_declaration	:	declaration_specifiers */
static psrNode_t* AR_STDCALL handle_parameter_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_name	:	specifier_qualifier_list */
/*type_name	:	specifier_qualifier_list abstract_declarator */
static psrNode_t* AR_STDCALL handle_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*specifier_qualifier_list	:	type_qualifier */
/*specifier_qualifier_list	:	type_specifier */
/*specifier_qualifier_list	:	type_qualifier specifier_qualifier_list */
/*specifier_qualifier_list	:	type_specifier specifier_qualifier_list */
static psrNode_t* AR_STDCALL handle_specifier_qualifier_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*statement	:	labeled_statement */
/*statement	:	compound_statement */
/*statement	:	expression_statement */
/*statement	:	selection_statement */
/*statement	:	iteration_statement */
/*statement	:	jump_statement */
/*postfix_expression	:	primary_expression */
/*argument_expression_list	:	assignment_expression */
/*unary_expression	:	postfix_expression */
/*cast_expression	:	unary_expression */
/*binary_expression	:	cast_expression */
/*constant_expression	:	binary_expression */
/*assignment_expression	:	constant_expression */
static psrNode_t* AR_STDCALL semantic_auto_return_0(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*labeled_statement	:	case constant_expression : statement */
/*labeled_statement	:	default : statement */
/*labeled_statement	:	IDENTIFIER : statement */
static psrNode_t* AR_STDCALL handle_labeled_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement	:	start_block compound_statement_body */
static psrNode_t* AR_STDCALL handle_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*start_block	:	{ */
static psrNode_t* AR_STDCALL handle_start_block(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement_body	:	compound_statement_declarations } */
/*compound_statement_body	:	compound_statement_declarations statement_list } */
static psrNode_t* AR_STDCALL handle_compound_statement_body(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement_declarations	:	declaration_list */
/*compound_statement_declarations	:	 */
static psrNode_t* AR_STDCALL handle_compound_statement_declarations(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*statement_list	:	statement */
/*statement_list	:	statement_list statement */
static psrNode_t* AR_STDCALL handle_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*expression_statement	:	; */
/*expression_statement	:	expression ; */
static psrNode_t* AR_STDCALL handle_expression_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*selection_statement	:	if ( expression ) statement */
/*selection_statement	:	if ( expression ) statement else statement */
/*selection_statement	:	switch ( expression ) statement */
static psrNode_t* AR_STDCALL handle_selection_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*iteration_statement	:	while ( expression ) statement */
/*iteration_statement	:	do statement while ( expression ) ; */
/*iteration_statement	:	for ( expression_statement expression_statement ) statement */
/*iteration_statement	:	for ( expression_statement expression_statement expression ) statement */
static psrNode_t* AR_STDCALL handle_iteration_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*jump_statement	:	goto IDENTIFIER ; */
/*jump_statement	:	continue ; */
/*jump_statement	:	break ; */
/*jump_statement	:	return ; */
/*jump_statement	:	return expression ; */
static psrNode_t* AR_STDCALL handle_jump_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*expression	:	assignment_expression */
/*expression	:	expression , assignment_expression */
static psrNode_t* AR_STDCALL handle_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*primary_expression	:	( expression ) */
static psrNode_t* AR_STDCALL semantic_auto_return_1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*primary_expression	:	IDENTIFIER */
/*primary_expression	:	HEX_CONSTANT */
/*primary_expression	:	DEC_CONSTANT */
/*primary_expression	:	OCT_CONSTANT */
/*primary_expression	:	FLOAT_CONSTANT */
/*primary_expression	:	CHAR_CONSTANT */
/*primary_expression	:	string_list */
static psrNode_t* AR_STDCALL handle_primary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*string_list	:	string_list STRING_LITERAL */
/*string_list	:	STRING_LITERAL */
static psrNode_t* AR_STDCALL handle_string_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*postfix_expression	:	postfix_expression [ expression ] */
/*postfix_expression	:	postfix_expression ( ) */
/*postfix_expression	:	postfix_expression ( argument_expression_list ) */
/*postfix_expression	:	postfix_expression . IDENTIFIER */
/*postfix_expression	:	postfix_expression -> IDENTIFIER */
/*postfix_expression	:	postfix_expression ++ */
/*postfix_expression	:	postfix_expression -- */
static psrNode_t* AR_STDCALL handle_postfix_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*argument_expression_list	:	argument_expression_list , assignment_expression */
static psrNode_t* AR_STDCALL handle_argument_expression_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*unary_expression	:	++ unary_expression */
/*unary_expression	:	-- unary_expression */
/*unary_expression	:	& cast_expression */
/*unary_expression	:	* cast_expression */
/*unary_expression	:	+ cast_expression */
/*unary_expression	:	- cast_expression */
/*unary_expression	:	~ cast_expression */
/*unary_expression	:	! cast_expression */
/*unary_expression	:	sizeof unary_expression */
/*unary_expression	:	sizeof ( type_name ) */
static psrNode_t* AR_STDCALL handle_unary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cast_expression	:	( type_name ) cast_expression */
static psrNode_t* AR_STDCALL handle_cast_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*binary_expression	:	binary_expression + binary_expression */
/*binary_expression	:	binary_expression - binary_expression */
/*binary_expression	:	binary_expression * binary_expression */
/*binary_expression	:	binary_expression / binary_expression */
/*binary_expression	:	binary_expression % binary_expression */
/*binary_expression	:	binary_expression << binary_expression */
/*binary_expression	:	binary_expression >> binary_expression */
/*binary_expression	:	binary_expression < binary_expression */
/*binary_expression	:	binary_expression <= binary_expression */
/*binary_expression	:	binary_expression > binary_expression */
/*binary_expression	:	binary_expression >= binary_expression */
/*binary_expression	:	binary_expression == binary_expression */
/*binary_expression	:	binary_expression != binary_expression */
/*binary_expression	:	binary_expression & binary_expression */
/*binary_expression	:	binary_expression ^ binary_expression */
/*binary_expression	:	binary_expression | binary_expression */
/*binary_expression	:	binary_expression && binary_expression */
/*binary_expression	:	binary_expression || binary_expression */
static psrNode_t* AR_STDCALL handle_binary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*constant_expression	:	binary_expression ? expression : constant_expression */
static psrNode_t* AR_STDCALL handle_constant_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*assignment_expression	:	unary_expression assignment_operator assignment_expression */
static psrNode_t* AR_STDCALL handle_assignment_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*assignment_operator	:	= */
/*assignment_operator	:	*= */
/*assignment_operator	:	/= */
/*assignment_operator	:	%= */
/*assignment_operator	:	+= */
/*assignment_operator	:	-= */
/*assignment_operator	:	<<= */
/*assignment_operator	:	>>= */
/*assignment_operator	:	&= */
/*assignment_operator	:	^= */
/*assignment_operator	:	|= */
static psrNode_t* AR_STDCALL handle_assignment_operator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);




static struct { const wchar_t	*rule; const wchar_t	*prec_token; psrRuleFunc_t	handler; size_t	auto_ret; } __g_rule_pattern[] = {
{L"translation_unit  :  external_declaration ", NULL, handle_translation_unit, 0},
{L"translation_unit  :  translation_unit external_declaration ", NULL, handle_translation_unit, 0},
{L"external_declaration  :  function_definition ", NULL, handle_external_declaration, 0},
{L"external_declaration  :  declaration ", NULL, handle_external_declaration, 0},
{L"external_declaration  :  access_unit ", NULL, handle_external_declaration, 0},
{L"external_declaration  :  attribute_unit ", NULL, handle_external_declaration, 0},
{L"access_unit  :  import_or_export STRING_LITERAL ; ", NULL, handle_access_unit, 0},
{L"access_unit  :  import_or_export error ; ", NULL, handle_access_unit, 0},
{L"import_or_export  :  import ", NULL, handle_import_or_export, 0},
{L"import_or_export  :  export ", NULL, handle_import_or_export, 0},
{L"attribute_unit  :  attribute STRING_LITERAL ; ", NULL, handle_attribute_unit, 0},
{L"attribute_unit  :  attribute error ; ", NULL, handle_attribute_unit, 0},
{L"function_declaration  :  declaration_specifiers declarator ", NULL, handle_function_declaration, 0},
{L"function_definition  :  function_declaration compound_statement ", NULL, handle_function_definition, 0},
{L"type_qualifier  :  const ", NULL, handle_type_qualifier, 0},
{L"type_qualifier  :  volatile ", NULL, handle_type_qualifier, 0},
{L"type_qualifier_list  :  type_qualifier_list type_qualifier ", NULL, handle_type_qualifier_list, 0},
{L"type_qualifier_list  :  type_qualifier ", NULL, handle_type_qualifier_list, 0},
{L"type_specifier  :  void ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  byte ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  char ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  short ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  int ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  long ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  float ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  double ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  signed ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  unsigned ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  struct_or_union_specifier ", NULL, handle_type_specifier, 0},
{L"type_specifier  :  TYPE_ID ", NULL, handle_type_specifier, 0},
{L"struct_or_union_specifier  :  struct_or_union IDENTIFIER { struct_declaration_list } ", NULL, handle_struct_or_union_specifier, 0},
{L"struct_or_union_specifier  :  struct_or_union { struct_declaration_list } ", NULL, handle_struct_or_union_specifier, 0},
{L"struct_or_union_specifier  :  struct_or_union IDENTIFIER ", NULL, handle_struct_or_union_specifier, 0},
{L"struct_or_union  :  struct ", NULL, handle_struct_or_union, 0},
{L"struct_or_union  :  union ", NULL, handle_struct_or_union, 0},
{L"struct_declaration_list  :  struct_declaration ", NULL, handle_struct_declaration_list, 0},
{L"struct_declaration_list  :  struct_declaration_list struct_declaration ", NULL, handle_struct_declaration_list, 0},
{L"struct_declaration  :  specifier_qualifier_list struct_declarator_list ; ", NULL, handle_struct_declaration, 0},
{L"struct_declarator_list  :  declarator ", NULL, handle_struct_declarator_list, 0},
{L"struct_declarator_list  :  struct_declarator_list , declarator ", NULL, handle_struct_declarator_list, 0},
{L"declaration  :  declaration_specifiers init_declarator_list ; ", NULL, handle_declaration, 0},
{L"declaration  :  declaration_specifiers ; ", NULL, handle_declaration, 0},
{L"declaration  :  error ", NULL, handle_declaration, 0},
{L"storage_class_specifier  :  typedef ", NULL, handle_storage_class_specifier, 0},
{L"storage_class_specifier  :  static ", NULL, handle_storage_class_specifier, 0},
{L"declaration_specifiers  :  storage_class_specifier ", NULL, handle_declaration_specifiers, 0},
{L"declaration_specifiers  :  storage_class_specifier declaration_specifiers ", NULL, handle_declaration_specifiers, 0},
{L"declaration_specifiers  :  type_specifier ", NULL, handle_declaration_specifiers, 0},
{L"declaration_specifiers  :  type_specifier declaration_specifiers ", NULL, handle_declaration_specifiers, 0},
{L"declaration_specifiers  :  type_qualifier ", NULL, handle_declaration_specifiers, 0},
{L"declaration_specifiers  :  type_qualifier declaration_specifiers ", NULL, handle_declaration_specifiers, 0},
{L"declaration_list  :  declaration ", NULL, handle_declaration_list, 0},
{L"declaration_list  :  declaration_list declaration ", NULL, handle_declaration_list, 0},
{L"init_declarator_list  :  init_declarator ", NULL, handle_init_declarator_list, 0},
{L"init_declarator_list  :  init_declarator_list , init_declarator ", NULL, handle_init_declarator_list, 0},
{L"init_declarator  :  declarator ", NULL, handle_init_declarator, 0},
{L"init_declarator  :  declarator = initializer ", NULL, handle_init_declarator, 0},
{L"initializer  :  assignment_expression ", NULL, handle_initializer, 0},
{L"initializer  :  { initializer_list } ", NULL, handle_initializer, 0},
{L"initializer_list  :  initializer ", NULL, handle_initializer_list, 0},
{L"initializer_list  :  initializer_list , initializer ", NULL, handle_initializer_list, 0},
{L"declarator  :  direct_declarator ", NULL, handle_declarator, 0},
{L"declarator  :  pointer direct_declarator ", NULL, handle_declarator, 0},
{L"direct_declarator  :  IDENTIFIER ", NULL, handle_direct_declarator, 0},
{L"direct_declarator  :  IDENTIFIER [ constant_expression ] ", NULL, handle_direct_declarator, 0},
{L"direct_declarator  :  IDENTIFIER [ ] ", NULL, handle_direct_declarator, 0},
{L"direct_declarator  :  IDENTIFIER ( parameter_list ) ", NULL, handle_direct_declarator, 0},
{L"direct_declarator  :  IDENTIFIER ( ) ", NULL, handle_direct_declarator, 0},
{L"abstract_declarator  :  pointer ", NULL, handle_abstract_declarator, 0},
{L"abstract_declarator  :  direct_abstract_declarator ", NULL, handle_abstract_declarator, 0},
{L"abstract_declarator  :  pointer direct_abstract_declarator ", NULL, handle_abstract_declarator, 0},
{L"direct_abstract_declarator  :  [ ] ", NULL, handle_direct_abstract_declarator, 0},
{L"direct_abstract_declarator  :  [ constant_expression ] ", NULL, handle_direct_abstract_declarator, 0},
{L"pointer  :  * ", NULL, handle_pointer, 0},
{L"pointer  :  * type_qualifier_list ", NULL, handle_pointer, 0},
{L"pointer  :  * type_qualifier_list pointer ", NULL, handle_pointer, 0},
{L"pointer  :  * pointer ", NULL, handle_pointer, 0},
{L"parameter_list  :  parameter_declaration ", NULL, handle_parameter_list, 0},
{L"parameter_list  :  parameter_list , parameter_declaration ", NULL, handle_parameter_list, 0},
{L"parameter_declaration  :  declaration_specifiers declarator ", NULL, handle_parameter_declaration, 0},
{L"parameter_declaration  :  declaration_specifiers abstract_declarator ", NULL, handle_parameter_declaration, 0},
{L"parameter_declaration  :  declaration_specifiers ", NULL, handle_parameter_declaration, 0},
{L"type_name  :  specifier_qualifier_list ", NULL, handle_type_name, 0},
{L"type_name  :  specifier_qualifier_list abstract_declarator ", NULL, handle_type_name, 0},
{L"specifier_qualifier_list  :  type_qualifier ", NULL, handle_specifier_qualifier_list, 0},
{L"specifier_qualifier_list  :  type_specifier ", NULL, handle_specifier_qualifier_list, 0},
{L"specifier_qualifier_list  :  type_qualifier specifier_qualifier_list ", NULL, handle_specifier_qualifier_list, 0},
{L"specifier_qualifier_list  :  type_specifier specifier_qualifier_list ", NULL, handle_specifier_qualifier_list, 0},
{L"statement  :  labeled_statement ", NULL, semantic_auto_return_0, 0},
{L"statement  :  compound_statement ", NULL, semantic_auto_return_0, 0},
{L"statement  :  expression_statement ", NULL, semantic_auto_return_0, 0},
{L"statement  :  selection_statement ", NULL, semantic_auto_return_0, 0},
{L"statement  :  iteration_statement ", NULL, semantic_auto_return_0, 0},
{L"statement  :  jump_statement ", NULL, semantic_auto_return_0, 0},
{L"labeled_statement  :  case constant_expression : statement ", NULL, handle_labeled_statement, 0},
{L"labeled_statement  :  default : statement ", NULL, handle_labeled_statement, 0},
{L"labeled_statement  :  IDENTIFIER : statement ", NULL, handle_labeled_statement, 0},
{L"compound_statement  :  start_block compound_statement_body ", NULL, handle_compound_statement, 0},
{L"start_block  :  { ", NULL, handle_start_block, 0},
{L"compound_statement_body  :  compound_statement_declarations } ", NULL, handle_compound_statement_body, 0},
{L"compound_statement_body  :  compound_statement_declarations statement_list } ", NULL, handle_compound_statement_body, 0},
{L"compound_statement_declarations  :  declaration_list ", NULL, handle_compound_statement_declarations, 0},
{L"compound_statement_declarations  :   ", NULL, handle_compound_statement_declarations, 0},
{L"statement_list  :  statement ", NULL, handle_statement_list, 0},
{L"statement_list  :  statement_list statement ", NULL, handle_statement_list, 0},
{L"expression_statement  :  ; ", NULL, handle_expression_statement, 0},
{L"expression_statement  :  expression ; ", NULL, handle_expression_statement, 0},
{L"selection_statement  :  if ( expression ) statement ", L"IF_STMT_PREC", handle_selection_statement, 0},
{L"selection_statement  :  if ( expression ) statement else statement ", L"IF_STMT_ELSE_STMT_PREC", handle_selection_statement, 0},
{L"selection_statement  :  switch ( expression ) statement ", NULL, handle_selection_statement, 0},
{L"iteration_statement  :  while ( expression ) statement ", NULL, handle_iteration_statement, 0},
{L"iteration_statement  :  do statement while ( expression ) ; ", NULL, handle_iteration_statement, 0},
{L"iteration_statement  :  for ( expression_statement expression_statement ) statement ", NULL, handle_iteration_statement, 0},
{L"iteration_statement  :  for ( expression_statement expression_statement expression ) statement ", NULL, handle_iteration_statement, 0},
{L"jump_statement  :  goto IDENTIFIER ; ", NULL, handle_jump_statement, 0},
{L"jump_statement  :  continue ; ", NULL, handle_jump_statement, 0},
{L"jump_statement  :  break ; ", NULL, handle_jump_statement, 0},
{L"jump_statement  :  return ; ", NULL, handle_jump_statement, 0},
{L"jump_statement  :  return expression ; ", NULL, handle_jump_statement, 0},
{L"expression  :  assignment_expression ", NULL, handle_expression, 0},
{L"expression  :  expression , assignment_expression ", NULL, handle_expression, 0},
{L"primary_expression  :  ( expression ) ", NULL, semantic_auto_return_1, 0},
{L"primary_expression  :  IDENTIFIER ", NULL, handle_primary_expression, 0},
{L"primary_expression  :  HEX_CONSTANT ", NULL, handle_primary_expression, 0},
{L"primary_expression  :  DEC_CONSTANT ", NULL, handle_primary_expression, 0},
{L"primary_expression  :  OCT_CONSTANT ", NULL, handle_primary_expression, 0},
{L"primary_expression  :  FLOAT_CONSTANT ", NULL, handle_primary_expression, 0},
{L"primary_expression  :  CHAR_CONSTANT ", NULL, handle_primary_expression, 0},
{L"primary_expression  :  string_list ", NULL, handle_primary_expression, 0},
{L"string_list  :  string_list STRING_LITERAL ", NULL, handle_string_list, 0},
{L"string_list  :  STRING_LITERAL ", NULL, handle_string_list, 0},
{L"postfix_expression  :  primary_expression ", NULL, semantic_auto_return_0, 0},
{L"postfix_expression  :  postfix_expression [ expression ] ", NULL, handle_postfix_expression, 0},
{L"postfix_expression  :  postfix_expression ( ) ", NULL, handle_postfix_expression, 0},
{L"postfix_expression  :  postfix_expression ( argument_expression_list ) ", NULL, handle_postfix_expression, 0},
{L"postfix_expression  :  postfix_expression . IDENTIFIER ", NULL, handle_postfix_expression, 0},
{L"postfix_expression  :  postfix_expression -> IDENTIFIER ", NULL, handle_postfix_expression, 0},
{L"postfix_expression  :  postfix_expression ++ ", NULL, handle_postfix_expression, 0},
{L"postfix_expression  :  postfix_expression -- ", NULL, handle_postfix_expression, 0},
{L"argument_expression_list  :  assignment_expression ", NULL, semantic_auto_return_0, 0},
{L"argument_expression_list  :  argument_expression_list , assignment_expression ", NULL, handle_argument_expression_list, 0},
{L"unary_expression  :  postfix_expression ", NULL, semantic_auto_return_0, 0},
{L"unary_expression  :  ++ unary_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  -- unary_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  & cast_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  * cast_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  + cast_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  - cast_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  ~ cast_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  ! cast_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  sizeof unary_expression ", NULL, handle_unary_expression, 0},
{L"unary_expression  :  sizeof ( type_name ) ", NULL, handle_unary_expression, 0},
{L"cast_expression  :  unary_expression ", NULL, semantic_auto_return_0, 0},
{L"cast_expression  :  ( type_name ) cast_expression ", NULL, handle_cast_expression, 0},
{L"binary_expression  :  cast_expression ", NULL, semantic_auto_return_0, 0},
{L"binary_expression  :  binary_expression + binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression - binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression * binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression / binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression % binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression << binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression >> binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression < binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression <= binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression > binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression >= binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression == binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression != binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression & binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression ^ binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression | binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression && binary_expression ", NULL, handle_binary_expression, 0},
{L"binary_expression  :  binary_expression || binary_expression ", NULL, handle_binary_expression, 0},
{L"constant_expression  :  binary_expression ", NULL, semantic_auto_return_0, 0},
{L"constant_expression  :  binary_expression ? expression : constant_expression ", NULL, handle_constant_expression, 0},
{L"assignment_expression  :  constant_expression ", NULL, semantic_auto_return_0, 0},
{L"assignment_expression  :  unary_expression assignment_operator assignment_expression ", NULL, handle_assignment_expression, 0},
{L"assignment_operator  :  = ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  *= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  /= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  %= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  += ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  -= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  <<= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  >>= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  &= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  ^= ", NULL, handle_assignment_operator, 0},
{L"assignment_operator  :  |= ", NULL, handle_assignment_operator, 0}
};

#define __RULE_COUNT__ ((size_t)188)
#define START_RULE L"translation_unit"

static lex_t*	__build_lex(const arIOCtx_t *io)								
{																				
		lex_t	*lex;															
		size_t i;																
		lex = LEX_Create(io);													
		for(i = 0; i < __NAME_COUNT__; ++i)										
		{																		
				if(!LEX_Insert(lex, __g_lex_name[i]))							
				{																
						LEX_Destroy(lex);										
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
				if(!LEX_InsertRule(lex, __g_term_pattern[i].regex, &act))		
				{																
						LEX_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		return lex;																
}

static psrGrammar_t*	__build_grammar(const psrCtx_t	*psr_ctx, const arIOCtx_t *io)											
{																																
		psrGrammar_t	*grammar;																								
		size_t i;																												
		AR_ASSERT(psr_ctx != NULL);																								
		grammar = PSR_CreateGrammar(psr_ctx, io);																				
		for(i = 0; i < __TERM_COUNT__; ++i)																						
		{																														
				if(__g_term_pattern[i].skip || __g_term_pattern[i].tokval == 0)continue;										
				if(!PSR_InsertTerm(grammar, __g_term_pattern[i].name, __g_term_pattern[i].tokval, PSR_ASSOC_NONASSOC,0, NULL))	
				{																												
						PSR_DestroyGrammar(grammar);																			
						grammar = NULL;																							
						AR_ASSERT(false);																						
						return NULL;																							
				}																												
		}																														
		for(i = 0; i < __PREC_COUNT__; ++i)																						
		{																														
				psrTermInfo_t	*info;																							
				info = PSR_GetTermSymbInfoByName(grammar, __g_prec_pattern[i].name);											
				if(info == NULL)																								
				{																												
						if(!PSR_InsertTerm(grammar, __g_prec_pattern[i].name, __g_prec_pattern[i].tokval, __g_prec_pattern[i].assoc, __g_prec_pattern[i].prec_level, NULL))
						{																																					
								PSR_DestroyGrammar(grammar);																												
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
				if(!PSR_InsertRuleByStr(grammar, __g_rule_pattern[i].rule, __g_rule_pattern[i].prec_token, __g_rule_pattern[i].handler, __g_rule_pattern[i].auto_ret))		
				{																																							
						PSR_DestroyGrammar(grammar);																														
						grammar = NULL;																																		
						AR_ASSERT(false);																																	
						return NULL;																																		
				}																																							
		}																																									
		if(!PSR_SetFirstRule(grammar,START_RULE) || !PSR_CheckIsValidGrammar(grammar))																						
		{																																									
				PSR_DestroyGrammar(grammar);																																
				grammar = NULL;																																				
				AR_ASSERT(false);																																			
				return NULL;																																				
		}																																									
		return grammar;																																						
}




/*translation_unit	:	external_declaration */
/*translation_unit	:	translation_unit external_declaration */
static psrNode_t* AR_STDCALL handle_translation_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*external_declaration	:	function_definition */
/*external_declaration	:	declaration */
/*external_declaration	:	access_unit */
/*external_declaration	:	attribute_unit */
static psrNode_t* AR_STDCALL handle_external_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*access_unit	:	import_or_export STRING_LITERAL ; */
/*access_unit	:	import_or_export error ; */
static psrNode_t* AR_STDCALL handle_access_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*import_or_export	:	import */
/*import_or_export	:	export */
static psrNode_t* AR_STDCALL handle_import_or_export(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*attribute_unit	:	attribute STRING_LITERAL ; */
/*attribute_unit	:	attribute error ; */
static psrNode_t* AR_STDCALL handle_attribute_unit(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*function_declaration	:	declaration_specifiers declarator */
static psrNode_t* AR_STDCALL handle_function_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*function_definition	:	function_declaration compound_statement */
static psrNode_t* AR_STDCALL handle_function_definition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*type_qualifier	:	const */
/*type_qualifier	:	volatile */
static psrNode_t* AR_STDCALL handle_type_qualifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*type_qualifier_list	:	type_qualifier_list type_qualifier */
/*type_qualifier_list	:	type_qualifier */
static psrNode_t* AR_STDCALL handle_type_qualifier_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*type_specifier	:	void */
/*type_specifier	:	byte */
/*type_specifier	:	char */
/*type_specifier	:	short */
/*type_specifier	:	int */
/*type_specifier	:	long */
/*type_specifier	:	float */
/*type_specifier	:	double */
/*type_specifier	:	signed */
/*type_specifier	:	unsigned */
/*type_specifier	:	struct_or_union_specifier */
/*type_specifier	:	TYPE_ID */
static psrNode_t* AR_STDCALL handle_type_specifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*struct_or_union_specifier	:	struct_or_union IDENTIFIER { struct_declaration_list } */
/*struct_or_union_specifier	:	struct_or_union { struct_declaration_list } */
/*struct_or_union_specifier	:	struct_or_union IDENTIFIER */
static psrNode_t* AR_STDCALL handle_struct_or_union_specifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*struct_or_union	:	struct */
/*struct_or_union	:	union */
static psrNode_t* AR_STDCALL handle_struct_or_union(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*struct_declaration_list	:	struct_declaration */
/*struct_declaration_list	:	struct_declaration_list struct_declaration */
static psrNode_t* AR_STDCALL handle_struct_declaration_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*struct_declaration	:	specifier_qualifier_list struct_declarator_list ; */
static psrNode_t* AR_STDCALL handle_struct_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*struct_declarator_list	:	declarator */
/*struct_declarator_list	:	struct_declarator_list , declarator */
static psrNode_t* AR_STDCALL handle_struct_declarator_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*declaration	:	declaration_specifiers init_declarator_list ; */
/*declaration	:	declaration_specifiers ; */
/*declaration	:	error */
static psrNode_t* AR_STDCALL handle_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*storage_class_specifier	:	typedef */
/*storage_class_specifier	:	static */
static psrNode_t* AR_STDCALL handle_storage_class_specifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*declaration_specifiers	:	storage_class_specifier */
/*declaration_specifiers	:	storage_class_specifier declaration_specifiers */
/*declaration_specifiers	:	type_specifier */
/*declaration_specifiers	:	type_specifier declaration_specifiers */
/*declaration_specifiers	:	type_qualifier */
/*declaration_specifiers	:	type_qualifier declaration_specifiers */
static psrNode_t* AR_STDCALL handle_declaration_specifiers(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*declaration_list	:	declaration */
/*declaration_list	:	declaration_list declaration */
static psrNode_t* AR_STDCALL handle_declaration_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*init_declarator_list	:	init_declarator */
/*init_declarator_list	:	init_declarator_list , init_declarator */
static psrNode_t* AR_STDCALL handle_init_declarator_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*init_declarator	:	declarator */
/*init_declarator	:	declarator = initializer */
static psrNode_t* AR_STDCALL handle_init_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*initializer	:	assignment_expression */
/*initializer	:	{ initializer_list } */
static psrNode_t* AR_STDCALL handle_initializer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*initializer_list	:	initializer */
/*initializer_list	:	initializer_list , initializer */
static psrNode_t* AR_STDCALL handle_initializer_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*declarator	:	direct_declarator */
/*declarator	:	pointer direct_declarator */
static psrNode_t* AR_STDCALL handle_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*direct_declarator	:	IDENTIFIER */
/*direct_declarator	:	IDENTIFIER [ constant_expression ] */
/*direct_declarator	:	IDENTIFIER [ ] */
/*direct_declarator	:	IDENTIFIER ( parameter_list ) */
/*direct_declarator	:	IDENTIFIER ( ) */
static psrNode_t* AR_STDCALL handle_direct_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*abstract_declarator	:	pointer */
/*abstract_declarator	:	direct_abstract_declarator */
/*abstract_declarator	:	pointer direct_abstract_declarator */
static psrNode_t* AR_STDCALL handle_abstract_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*direct_abstract_declarator	:	[ ] */
/*direct_abstract_declarator	:	[ constant_expression ] */
static psrNode_t* AR_STDCALL handle_direct_abstract_declarator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*pointer	:	* */
/*pointer	:	* type_qualifier_list */
/*pointer	:	* type_qualifier_list pointer */
/*pointer	:	* pointer */
static psrNode_t* AR_STDCALL handle_pointer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*parameter_list	:	parameter_declaration */
/*parameter_list	:	parameter_list , parameter_declaration */
static psrNode_t* AR_STDCALL handle_parameter_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*parameter_declaration	:	declaration_specifiers declarator */
/*parameter_declaration	:	declaration_specifiers abstract_declarator */
/*parameter_declaration	:	declaration_specifiers */
static psrNode_t* AR_STDCALL handle_parameter_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*type_name	:	specifier_qualifier_list */
/*type_name	:	specifier_qualifier_list abstract_declarator */
static psrNode_t* AR_STDCALL handle_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*specifier_qualifier_list	:	type_qualifier */
/*specifier_qualifier_list	:	type_specifier */
/*specifier_qualifier_list	:	type_qualifier specifier_qualifier_list */
/*specifier_qualifier_list	:	type_specifier specifier_qualifier_list */
static psrNode_t* AR_STDCALL handle_specifier_qualifier_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*statement	:	labeled_statement */
/*statement	:	compound_statement */
/*statement	:	expression_statement */
/*statement	:	selection_statement */
/*statement	:	iteration_statement */
/*statement	:	jump_statement */
/*postfix_expression	:	primary_expression */
/*argument_expression_list	:	assignment_expression */
/*unary_expression	:	postfix_expression */
/*cast_expression	:	unary_expression */
/*binary_expression	:	cast_expression */
/*constant_expression	:	binary_expression */
/*assignment_expression	:	constant_expression */
static psrNode_t* AR_STDCALL semantic_auto_return_0(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*labeled_statement	:	case constant_expression : statement */
/*labeled_statement	:	default : statement */
/*labeled_statement	:	IDENTIFIER : statement */
static psrNode_t* AR_STDCALL handle_labeled_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*compound_statement	:	start_block compound_statement_body */
static psrNode_t* AR_STDCALL handle_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*start_block	:	{ */
static psrNode_t* AR_STDCALL handle_start_block(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*compound_statement_body	:	compound_statement_declarations } */
/*compound_statement_body	:	compound_statement_declarations statement_list } */
static psrNode_t* AR_STDCALL handle_compound_statement_body(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*compound_statement_declarations	:	declaration_list */
/*compound_statement_declarations	:	 */
static psrNode_t* AR_STDCALL handle_compound_statement_declarations(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*statement_list	:	statement */
/*statement_list	:	statement_list statement */
static psrNode_t* AR_STDCALL handle_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*expression_statement	:	; */
/*expression_statement	:	expression ; */
static psrNode_t* AR_STDCALL handle_expression_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*selection_statement	:	if ( expression ) statement */
/*selection_statement	:	if ( expression ) statement else statement */
/*selection_statement	:	switch ( expression ) statement */
static psrNode_t* AR_STDCALL handle_selection_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*iteration_statement	:	while ( expression ) statement */
/*iteration_statement	:	do statement while ( expression ) ; */
/*iteration_statement	:	for ( expression_statement expression_statement ) statement */
/*iteration_statement	:	for ( expression_statement expression_statement expression ) statement */
static psrNode_t* AR_STDCALL handle_iteration_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*jump_statement	:	goto IDENTIFIER ; */
/*jump_statement	:	continue ; */
/*jump_statement	:	break ; */
/*jump_statement	:	return ; */
/*jump_statement	:	return expression ; */
static psrNode_t* AR_STDCALL handle_jump_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*expression	:	assignment_expression */
/*expression	:	expression , assignment_expression */
static psrNode_t* AR_STDCALL handle_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*primary_expression	:	( expression ) */
static psrNode_t* AR_STDCALL semantic_auto_return_1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*primary_expression	:	IDENTIFIER */
/*primary_expression	:	HEX_CONSTANT */
/*primary_expression	:	DEC_CONSTANT */
/*primary_expression	:	OCT_CONSTANT */
/*primary_expression	:	FLOAT_CONSTANT */
/*primary_expression	:	CHAR_CONSTANT */
/*primary_expression	:	string_list */
static psrNode_t* AR_STDCALL handle_primary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*string_list	:	string_list STRING_LITERAL */
/*string_list	:	STRING_LITERAL */
static psrNode_t* AR_STDCALL handle_string_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*postfix_expression	:	postfix_expression [ expression ] */
/*postfix_expression	:	postfix_expression ( ) */
/*postfix_expression	:	postfix_expression ( argument_expression_list ) */
/*postfix_expression	:	postfix_expression . IDENTIFIER */
/*postfix_expression	:	postfix_expression -> IDENTIFIER */
/*postfix_expression	:	postfix_expression ++ */
/*postfix_expression	:	postfix_expression -- */
static psrNode_t* AR_STDCALL handle_postfix_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*argument_expression_list	:	argument_expression_list , assignment_expression */
static psrNode_t* AR_STDCALL handle_argument_expression_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*unary_expression	:	++ unary_expression */
/*unary_expression	:	-- unary_expression */
/*unary_expression	:	& cast_expression */
/*unary_expression	:	* cast_expression */
/*unary_expression	:	+ cast_expression */
/*unary_expression	:	- cast_expression */
/*unary_expression	:	~ cast_expression */
/*unary_expression	:	! cast_expression */
/*unary_expression	:	sizeof unary_expression */
/*unary_expression	:	sizeof ( type_name ) */
static psrNode_t* AR_STDCALL handle_unary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*cast_expression	:	( type_name ) cast_expression */
static psrNode_t* AR_STDCALL handle_cast_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*binary_expression	:	binary_expression + binary_expression */
/*binary_expression	:	binary_expression - binary_expression */
/*binary_expression	:	binary_expression * binary_expression */
/*binary_expression	:	binary_expression / binary_expression */
/*binary_expression	:	binary_expression % binary_expression */
/*binary_expression	:	binary_expression << binary_expression */
/*binary_expression	:	binary_expression >> binary_expression */
/*binary_expression	:	binary_expression < binary_expression */
/*binary_expression	:	binary_expression <= binary_expression */
/*binary_expression	:	binary_expression > binary_expression */
/*binary_expression	:	binary_expression >= binary_expression */
/*binary_expression	:	binary_expression == binary_expression */
/*binary_expression	:	binary_expression != binary_expression */
/*binary_expression	:	binary_expression & binary_expression */
/*binary_expression	:	binary_expression ^ binary_expression */
/*binary_expression	:	binary_expression | binary_expression */
/*binary_expression	:	binary_expression && binary_expression */
/*binary_expression	:	binary_expression || binary_expression */
static psrNode_t* AR_STDCALL handle_binary_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*constant_expression	:	binary_expression ? expression : constant_expression */
static psrNode_t* AR_STDCALL handle_constant_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*assignment_expression	:	unary_expression assignment_operator assignment_expression */
static psrNode_t* AR_STDCALL handle_assignment_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


/*assignment_operator	:	= */
/*assignment_operator	:	*= */
/*assignment_operator	:	/= */
/*assignment_operator	:	%= */
/*assignment_operator	:	+= */
/*assignment_operator	:	-= */
/*assignment_operator	:	<<= */
/*assignment_operator	:	>>= */
/*assignment_operator	:	&= */
/*assignment_operator	:	^= */
/*assignment_operator	:	|= */
static psrNode_t* AR_STDCALL handle_assignment_operator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}


