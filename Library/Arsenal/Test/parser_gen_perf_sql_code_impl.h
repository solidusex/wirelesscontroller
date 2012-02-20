#if(0)
static const wchar_t *__g_sql_lex_name[] = {
NULL
};

#define __SQL_NAME_COUNT__ ((size_t)0)



/*enum{
};*/




static struct {const wchar_t *name;
size_t tokval;
size_t lex_prec;
const wchar_t *regex;
bool_t skip;
psrTermFunc_t leaf;
}__g_sql_term_pattern[] =  {
{L"(", 257, 0, L"\"none\"", false, NULL},
{L")", 258, 0, L"\"none\"", false, NULL},
{L"*", 259, 0, L"\"none\"", false, NULL},
{L"+", 260, 0, L"\"none\"", false, NULL},
{L",", 261, 0, L"\"none\"", false, NULL},
{L"-", 262, 0, L"\"none\"", false, NULL},
{L".", 263, 0, L"\"none\"", false, NULL},
{L"/", 264, 0, L"\"none\"", false, NULL},
{L";", 265, 0, L"\"none\"", false, NULL},
{L"[", 266, 0, L"\"none\"", false, NULL},
{L"]", 267, 0, L"\"none\"", false, NULL},
{L"NAME", 268, 0, L"\"none\"", false, NULL},
{L"STRING", 269, 0, L"\"none\"", false, NULL},
{L"WSTRING", 270, 0, L"\"none\"", false, NULL},
{L"INTNUM", 271, 0, L"\"none\"", false, NULL},
{L"APPROXNUM", 272, 0, L"\"none\"", false, NULL},
{L"NUM_ERROR", 273, 0, L"\"none\"", false, NULL},
{L"AMMSC", 274, 0, L"\"none\"", false, NULL},
{L"PARAMETER_L", 275, 0, L"\"none\"", false, NULL},
{L"NAMED_PARAMETER", 276, 0, L"\"none\"", false, NULL},
{L"BEGIN_EQCALL_X", 277, 0, L"\"none\"", false, NULL},
{L"HTMLSTR", 278, 0, L"\"none\"", false, NULL},
{L"SQL_TSI", 279, 0, L"\"none\"", false, NULL},
{L"TIMESTAMP_FUNC", 280, 0, L"\"none\"", false, NULL},
{L"BINARYNUM", 281, 0, L"\"none\"", false, NULL},
{L"MSSQL_XMLCOL_NAME", 282, 0, L"\"none\"", false, NULL},
{L"MSSQL_XMLCOL_NAME1", 283, 0, L"\"none\"", false, NULL},
{L"MSSQL_XMLCOL_NAMEYZ", 284, 0, L"\"none\"", false, NULL},
{L"MSSQL_XMLCOL_NAMEZ", 285, 0, L"\"none\"", false, NULL},
{L"MSSQL_XMLCOL_INTNUM", 286, 0, L"\"none\"", false, NULL},
{L"TYPE", 287, 0, L"\"none\"", false, NULL},
{L"FINAL_L", 288, 0, L"\"none\"", false, NULL},
{L"METHOD", 289, 0, L"\"none\"", false, NULL},
{L"CHECKED", 290, 0, L"\"none\"", false, NULL},
{L"SYSTEM", 291, 0, L"\"none\"", false, NULL},
{L"GENERATED", 292, 0, L"\"none\"", false, NULL},
{L"SOURCE", 293, 0, L"\"none\"", false, NULL},
{L"RESULT", 294, 0, L"\"none\"", false, NULL},
{L"LOCATOR", 295, 0, L"\"none\"", false, NULL},
{L"INSTANCE_L", 296, 0, L"\"none\"", false, NULL},
{L"CONSTRUCTOR", 297, 0, L"\"none\"", false, NULL},
{L"SELF_L", 298, 0, L"\"none\"", false, NULL},
{L"OVERRIDING", 299, 0, L"\"none\"", false, NULL},
{L"STYLE", 300, 0, L"\"none\"", false, NULL},
{L"SQL_L", 301, 0, L"\"none\"", false, NULL},
{L"GENERAL", 302, 0, L"\"none\"", false, NULL},
{L"DETERMINISTIC", 303, 0, L"\"none\"", false, NULL},
{L"NO", 304, 0, L"\"none\"", false, NULL},
{L"CONTAINS", 305, 0, L"\"none\"", false, NULL},
{L"READS", 306, 0, L"\"none\"", false, NULL},
{L"DATA", 307, 0, L"\"none\"", false, NULL},
{L"MODIFIES", 308, 0, L"\"none\"", false, NULL},
{L"INPUT", 309, 0, L"\"none\"", false, NULL},
{L"CALLED", 310, 0, L"\"none\"", false, NULL},
{L"ADA", 311, 0, L"\"none\"", false, NULL},
{L"C", 312, 0, L"\"none\"", false, NULL},
{L"COBOL", 313, 0, L"\"none\"", false, NULL},
{L"FORTRAN", 314, 0, L"\"none\"", false, NULL},
{L"MUMPS", 315, 0, L"\"none\"", false, NULL},
{L"PASCAL_L", 316, 0, L"\"none\"", false, NULL},
{L"PLI", 317, 0, L"\"none\"", false, NULL},
{L"NAME_L", 318, 0, L"\"none\"", false, NULL},
{L"TEXT_L", 319, 0, L"\"none\"", false, NULL},
{L"JAVA", 320, 0, L"\"none\"", false, NULL},
{L"INOUT_L", 321, 0, L"\"none\"", false, NULL},
{L"REMOTE", 322, 0, L"\"none\"", false, NULL},
{L"KEYSET", 323, 0, L"\"none\"", false, NULL},
{L"VALUE", 324, 0, L"\"none\"", false, NULL},
{L"PARAMETER", 325, 0, L"\"none\"", false, NULL},
{L"VARIABLE", 326, 0, L"\"none\"", false, NULL},
{L"ADMIN_L", 327, 0, L"\"none\"", false, NULL},
{L"ROLE_L", 328, 0, L"\"none\"", false, NULL},
{L"TEMPORARY", 329, 0, L"\"none\"", false, NULL},
{L"CLR", 330, 0, L"\"none\"", false, NULL},
{L"ATTRIBUTE", 331, 0, L"\"none\"", false, NULL},
{L"__SOAP_DOC", 332, 0, L"\"none\"", false, NULL},
{L"__SOAP_DOCW", 333, 0, L"\"none\"", false, NULL},
{L"__SOAP_HEADER", 334, 0, L"\"none\"", false, NULL},
{L"__SOAP_HTTP", 335, 0, L"\"none\"", false, NULL},
{L"__SOAP_NAME", 336, 0, L"\"none\"", false, NULL},
{L"__SOAP_TYPE", 337, 0, L"\"none\"", false, NULL},
{L"__SOAP_XML_TYPE", 338, 0, L"\"none\"", false, NULL},
{L"__SOAP_FAULT", 339, 0, L"\"none\"", false, NULL},
{L"__SOAP_DIME_ENC", 340, 0, L"\"none\"", false, NULL},
{L"__SOAP_ENC_MIME", 341, 0, L"\"none\"", false, NULL},
{L"__SOAP_OPTIONS", 342, 0, L"\"none\"", false, NULL},
{L"FOREACH", 343, 0, L"\"none\"", false, NULL},
{L"ARE", 344, 0, L"\"none\"", false, NULL},
{L"REF", 345, 0, L"\"none\"", false, NULL},
{L"STATIC_L", 346, 0, L"\"none\"", false, NULL},
{L"SPECIFIC", 347, 0, L"\"none\"", false, NULL},
{L"DYNAMIC", 348, 0, L"\"none\"", false, NULL},
{L"COLUMN", 349, 0, L"\"none\"", false, NULL},
{L"START_L", 350, 0, L"\"none\"", false, NULL},
{L"AS", 351, 0, L"\"none\"", false, NULL},
{L"DOUBLE_COLON", 352, 0, L"\"none\"", false, NULL},
{L"COLON", 353, 0, L"\"none\"", false, NULL},
{L"OR", 354, 0, L"\"none\"", false, NULL},
{L"AND", 355, 0, L"\"none\"", false, NULL},
{L"NOT", 356, 0, L"\"none\"", false, NULL},
{L"COMPARISON", 357, 0, L"\"none\"", false, NULL},
{L"EQUALS", 358, 0, L"\"none\"", false, NULL},
{L"STRING_CONCAT_OPERATOR", 359, 0, L"\"none\"", false, NULL},
{L"UMINUS", 360, 0, L"\"none\"", false, NULL},
{L"ALL", 361, 0, L"\"none\"", false, NULL},
{L"ANY", 362, 0, L"\"none\"", false, NULL},
{L"ATTACH", 363, 0, L"\"none\"", false, NULL},
{L"ASC", 364, 0, L"\"none\"", false, NULL},
{L"AUTHORIZATION", 365, 0, L"\"none\"", false, NULL},
{L"BETWEEN", 366, 0, L"\"none\"", false, NULL},
{L"BY", 367, 0, L"\"none\"", false, NULL},
{L"CASCADE", 368, 0, L"\"none\"", false, NULL},
{L"CHARACTER", 369, 0, L"\"none\"", false, NULL},
{L"CHECK", 370, 0, L"\"none\"", false, NULL},
{L"CLOSE", 371, 0, L"\"none\"", false, NULL},
{L"COMMIT", 372, 0, L"\"none\"", false, NULL},
{L"CONSTRAINT", 373, 0, L"\"none\"", false, NULL},
{L"CONTINUE", 374, 0, L"\"none\"", false, NULL},
{L"CREATE", 375, 0, L"\"none\"", false, NULL},
{L"CUBE", 376, 0, L"\"none\"", false, NULL},
{L"CURRENT", 377, 0, L"\"none\"", false, NULL},
{L"CURSOR", 378, 0, L"\"none\"", false, NULL},
{L"DECIMAL", 379, 0, L"\"none\"", false, NULL},
{L"DECLARE", 380, 0, L"\"none\"", false, NULL},
{L"DEFAULT", 381, 0, L"\"none\"", false, NULL},
{L"DELETE_L", 382, 0, L"\"none\"", false, NULL},
{L"DESC", 383, 0, L"\"none\"", false, NULL},
{L"DISTINCT", 384, 0, L"\"none\"", false, NULL},
{L"DOUBLE", 385, 0, L"\"none\"", false, NULL},
{L"DROP", 386, 0, L"\"none\"", false, NULL},
{L"ESCAPE", 387, 0, L"\"none\"", false, NULL},
{L"EXISTS", 388, 0, L"\"none\"", false, NULL},
{L"FETCH", 389, 0, L"\"none\"", false, NULL},
{L"FLOAT", 390, 0, L"\"none\"", false, NULL},
{L"FOR", 391, 0, L"\"none\"", false, NULL},
{L"FOREIGN", 392, 0, L"\"none\"", false, NULL},
{L"FOUND", 393, 0, L"\"none\"", false, NULL},
{L"FROM", 394, 0, L"\"none\"", false, NULL},
{L"GOTO", 395, 0, L"\"none\"", false, NULL},
{L"GO", 396, 0, L"\"none\"", false, NULL},
{L"GRANT", 397, 0, L"\"none\"", false, NULL},
{L"GROUP", 398, 0, L"\"none\"", false, NULL},
{L"GROUPING", 399, 0, L"\"none\"", false, NULL},
{L"HAVING", 400, 0, L"\"none\"", false, NULL},
{L"IN_L", 401, 0, L"\"none\"", false, NULL},
{L"INDEX", 402, 0, L"\"none\"", false, NULL},
{L"INDICATOR", 403, 0, L"\"none\"", false, NULL},
{L"INSERT", 404, 0, L"\"none\"", false, NULL},
{L"INTEGER", 405, 0, L"\"none\"", false, NULL},
{L"INTO", 406, 0, L"\"none\"", false, NULL},
{L"IS", 407, 0, L"\"none\"", false, NULL},
{L"KEY", 408, 0, L"\"none\"", false, NULL},
{L"LANGUAGE", 409, 0, L"\"none\"", false, NULL},
{L"ENCODING", 410, 0, L"\"none\"", false, NULL},
{L"LIKE", 411, 0, L"\"none\"", false, NULL},
{L"NULLX", 412, 0, L"\"none\"", false, NULL},
{L"NUMERIC", 413, 0, L"\"none\"", false, NULL},
{L"OF", 414, 0, L"\"none\"", false, NULL},
{L"ON", 415, 0, L"\"none\"", false, NULL},
{L"OPEN", 416, 0, L"\"none\"", false, NULL},
{L"OPTION", 417, 0, L"\"none\"", false, NULL},
{L"ORDER", 418, 0, L"\"none\"", false, NULL},
{L"PRECISION", 419, 0, L"\"none\"", false, NULL},
{L"PRIMARY", 420, 0, L"\"none\"", false, NULL},
{L"PRIVILEGES", 421, 0, L"\"none\"", false, NULL},
{L"PROCEDURE", 422, 0, L"\"none\"", false, NULL},
{L"PUBLIC", 423, 0, L"\"none\"", false, NULL},
{L"REAL", 424, 0, L"\"none\"", false, NULL},
{L"REFERENCES", 425, 0, L"\"none\"", false, NULL},
{L"RESTRICT", 426, 0, L"\"none\"", false, NULL},
{L"ROLLBACK", 427, 0, L"\"none\"", false, NULL},
{L"ROLLUP", 428, 0, L"\"none\"", false, NULL},
{L"SCHEMA", 429, 0, L"\"none\"", false, NULL},
{L"SELECT", 430, 0, L"\"none\"", false, NULL},
{L"SET", 431, 0, L"\"none\"", false, NULL},
{L"SMALLINT", 432, 0, L"\"none\"", false, NULL},
{L"SOME", 433, 0, L"\"none\"", false, NULL},
{L"SQLCODE", 434, 0, L"\"none\"", false, NULL},
{L"SQLERROR", 435, 0, L"\"none\"", false, NULL},
{L"TABLE", 436, 0, L"\"none\"", false, NULL},
{L"TO", 437, 0, L"\"none\"", false, NULL},
{L"UNION", 438, 0, L"\"none\"", false, NULL},
{L"UNIQUE", 439, 0, L"\"none\"", false, NULL},
{L"UPDATE", 440, 0, L"\"none\"", false, NULL},
{L"USER", 441, 0, L"\"none\"", false, NULL},
{L"VALUES", 442, 0, L"\"none\"", false, NULL},
{L"VIEW", 443, 0, L"\"none\"", false, NULL},
{L"WHENEVER", 444, 0, L"\"none\"", false, NULL},
{L"WHERE", 445, 0, L"\"none\"", false, NULL},
{L"WITH", 446, 0, L"\"none\"", false, NULL},
{L"WORK", 447, 0, L"\"none\"", false, NULL},
{L"ARRAY", 448, 0, L"\"none\"", false, NULL},
{L"CONTIGUOUS", 449, 0, L"\"none\"", false, NULL},
{L"OBJECT_ID", 450, 0, L"\"none\"", false, NULL},
{L"UNDER", 451, 0, L"\"none\"", false, NULL},
{L"CLUSTERED", 452, 0, L"\"none\"", false, NULL},
{L"VARCHAR", 453, 0, L"\"none\"", false, NULL},
{L"VARBINARY", 454, 0, L"\"none\"", false, NULL},
{L"BINARY", 455, 0, L"\"none\"", false, NULL},
{L"LONG", 456, 0, L"\"none\"", false, NULL},
{L"REPLACING", 457, 0, L"\"none\"", false, NULL},
{L"SOFT", 458, 0, L"\"none\"", false, NULL},
{L"HASH", 459, 0, L"\"none\"", false, NULL},
{L"LOOP", 460, 0, L"\"none\"", false, NULL},
{L"SHUTDOWN", 461, 0, L"\"none\"", false, NULL},
{L"CHECKPOINT", 462, 0, L"\"none\"", false, NULL},
{L"BACKUP", 463, 0, L"\"none\"", false, NULL},
{L"REPLICATION", 464, 0, L"\"none\"", false, NULL},
{L"SYNC", 465, 0, L"\"none\"", false, NULL},
{L"ALTER", 466, 0, L"\"none\"", false, NULL},
{L"ADD", 467, 0, L"\"none\"", false, NULL},
{L"RENAME", 468, 0, L"\"none\"", false, NULL},
{L"DISCONNECT", 469, 0, L"\"none\"", false, NULL},
{L"MODIFY", 470, 0, L"\"none\"", false, NULL},
{L"BEFORE", 471, 0, L"\"none\"", false, NULL},
{L"AFTER", 472, 0, L"\"none\"", false, NULL},
{L"INSTEAD", 473, 0, L"\"none\"", false, NULL},
{L"TRIGGER", 474, 0, L"\"none\"", false, NULL},
{L"REFERENCING", 475, 0, L"\"none\"", false, NULL},
{L"OLD", 476, 0, L"\"none\"", false, NULL},
{L"AGGREGATE", 477, 0, L"\"none\"", false, NULL},
{L"FUNCTION", 478, 0, L"\"none\"", false, NULL},
{L"OUT_L", 479, 0, L"\"none\"", false, NULL},
{L"HANDLER", 480, 0, L"\"none\"", false, NULL},
{L"IF", 481, 0, L"\"none\"", false, NULL},
{L"THEN", 482, 0, L"\"none\"", false, NULL},
{L"ELSE", 483, 0, L"\"none\"", false, NULL},
{L"ELSEIF", 484, 0, L"\"none\"", false, NULL},
{L"WHILE", 485, 0, L"\"none\"", false, NULL},
{L"BEGINX", 486, 0, L"\"none\"", false, NULL},
{L"ENDX", 487, 0, L"\"none\"", false, NULL},
{L"RETURN", 488, 0, L"\"none\"", false, NULL},
{L"CALL", 489, 0, L"\"none\"", false, NULL},
{L"RETURNS", 490, 0, L"\"none\"", false, NULL},
{L"DO", 491, 0, L"\"none\"", false, NULL},
{L"EXCLUSIVE", 492, 0, L"\"none\"", false, NULL},
{L"PREFETCH", 493, 0, L"\"none\"", false, NULL},
{L"SQLSTATE", 494, 0, L"\"none\"", false, NULL},
{L"SQLWARNING", 495, 0, L"\"none\"", false, NULL},
{L"SQLEXCEPTION", 496, 0, L"\"none\"", false, NULL},
{L"EXIT", 497, 0, L"\"none\"", false, NULL},
{L"RESIGNAL", 498, 0, L"\"none\"", false, NULL},
{L"REVOKE", 499, 0, L"\"none\"", false, NULL},
{L"PASSWORD", 500, 0, L"\"none\"", false, NULL},
{L"OFF", 501, 0, L"\"none\"", false, NULL},
{L"LOGX", 502, 0, L"\"none\"", false, NULL},
{L"TIMESTAMP", 503, 0, L"\"none\"", false, NULL},
{L"DATE", 504, 0, L"\"none\"", false, NULL},
{L"DATETIME", 505, 0, L"\"none\"", false, NULL},
{L"TIME", 506, 0, L"\"none\"", false, NULL},
{L"EXECUTE", 507, 0, L"\"none\"", false, NULL},
{L"REXECUTE", 508, 0, L"\"none\"", false, NULL},
{L"MODULE", 509, 0, L"\"none\"", false, NULL},
{L"BEGIN_FN_X", 510, 0, L"\"none\"", false, NULL},
{L"BEGIN_CALL_X", 511, 0, L"\"none\"", false, NULL},
{L"BEGIN_OJ_X", 512, 0, L"\"none\"", false, NULL},
{L"BEGIN_U_X", 513, 0, L"\"none\"", false, NULL},
{L"CONVERT", 514, 0, L"\"none\"", false, NULL},
{L"CASE", 515, 0, L"\"none\"", false, NULL},
{L"WHEN", 516, 0, L"\"none\"", false, NULL},
{L"IDENTITY", 517, 0, L"\"none\"", false, NULL},
{L"LEFT", 518, 0, L"\"none\"", false, NULL},
{L"RIGHT", 519, 0, L"\"none\"", false, NULL},
{L"FULL", 520, 0, L"\"none\"", false, NULL},
{L"OUTER", 521, 0, L"\"none\"", false, NULL},
{L"INNER", 522, 0, L"\"none\"", false, NULL},
{L"CROSS", 523, 0, L"\"none\"", false, NULL},
{L"NATURAL", 524, 0, L"\"none\"", false, NULL},
{L"USING", 525, 0, L"\"none\"", false, NULL},
{L"JOIN", 526, 0, L"\"none\"", false, NULL},
{L"USE", 527, 0, L"\"none\"", false, NULL},
{L"COALESCE", 528, 0, L"\"none\"", false, NULL},
{L"CAST", 529, 0, L"\"none\"", false, NULL},
{L"NULLIF", 530, 0, L"\"none\"", false, NULL},
{L"NEW", 531, 0, L"\"none\"", false, NULL},
{L"CORRESPONDING", 532, 0, L"\"none\"", false, NULL},
{L"EXCEPT", 533, 0, L"\"none\"", false, NULL},
{L"INTERSECT", 534, 0, L"\"none\"", false, NULL},
{L"BEST", 535, 0, L"\"none\"", false, NULL},
{L"TOP", 536, 0, L"\"none\"", false, NULL},
{L"PERCENT", 537, 0, L"\"none\"", false, NULL},
{L"TIES", 538, 0, L"\"none\"", false, NULL},
{L"XML", 539, 0, L"\"none\"", false, NULL},
{L"XPATH", 540, 0, L"\"none\"", false, NULL},
{L"PERSISTENT", 541, 0, L"\"none\"", false, NULL},
{L"INTERVAL", 542, 0, L"\"none\"", false, NULL},
{L"INCREMENT_L", 543, 0, L"\"none\"", false, NULL},
{L"DTD", 544, 0, L"\"none\"", false, NULL},
{L"INTERNAL", 545, 0, L"\"none\"", false, NULL},
{L"EXTERNAL", 546, 0, L"\"none\"", false, NULL},
{L"COLLATE", 547, 0, L"\"none\"", false, NULL},
{L"NCHAR", 548, 0, L"\"none\"", false, NULL},
{L"NVARCHAR", 549, 0, L"\"none\"", false, NULL},
{L"INCREMENTAL", 550, 0, L"\"none\"", false, NULL},
{L"NONINCREMENTAL", 551, 0, L"\"none\"", false, NULL},
{L"PURGE", 552, 0, L"\"none\"", false, NULL},
{L"SNAPSHOT", 553, 0, L"\"none\"", false, NULL},
{L"IDENTIFIED", 554, 0, L"\"none\"", false, NULL},
{L"EXTRACT", 555, 0, L"\"none\"", false, NULL},
{L"KWD_TAG", 556, 0, L"\"none\"", false, NULL},
{L"LEXICAL_ERROR", 557, 0, L"\"none\"", false, NULL},
{L"CURRENT_DATE", 558, 0, L"\"none\"", false, NULL},
{L"CURRENT_TIME", 559, 0, L"\"none\"", false, NULL},
{L"CURRENT_TIMESTAMP", 560, 0, L"\"none\"", false, NULL},
{L"PERMISSION_SET", 561, 0, L"\"none\"", false, NULL},
{L"AUTOREGISTER_L", 562, 0, L"\"none\"", false, NULL},
{L"LIBRARY_L", 563, 0, L"\"none\"", false, NULL},
{L"ASSEMBLY_L", 564, 0, L"\"none\"", false, NULL},
{L"SAFE_L", 565, 0, L"\"none\"", false, NULL},
{L"UNRESTRICTED", 566, 0, L"\"none\"", false, NULL},
{L"CFG_LEXVAL_EOI", 0, 2, L"$", false, NULL}
};

#define __SQL_TERM_COUNT__ ((size_t)311)

static struct {const wchar_t *name; size_t tokval; size_t prec_level; psrAssocType_t	assoc;}__g_sql_prec_pattern[] =  {
NULL
};

#define __SQL_PREC_COUNT__ ((size_t)0)

/*sql_list	:	sql_list1 ; */
/*sql_list	:	sql_list1 */
static psrNode_t* AR_STDCALL handle_sql_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*sql_list1	:	sql */
static psrNode_t* AR_STDCALL handle_sql_list1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*sql	:	schema_element_list */
/*sql	:	view_def */
/*sql	:	xml_view */
/*sql	:	create_xml_schema */
/*sql	:	alter_constraint */
/*sql	:	create_library */
/*sql	:	create_assembly */
/*sql	:	drop_library */
/*sql	:	drop_assembly */
/*sql	:	user_aggregate_declaration */
/*sql	:	routine_declaration */
/*sql	:	module_declaration */
/*sql	:	method_declaration */
/*sql	:	trigger_def */
/*sql	:	drop_trigger */
/*sql	:	drop_proc */
/*sql	:	manipulative_statement */
/*sql	:	BEGIN_EQCALL_X q_table_name ENDX */
/*sql	:	BEGIN_EQCALL_X q_table_name ( opt_scalar_exp_commalist ) ENDX */
static psrNode_t* AR_STDCALL handle_sql(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*schema_element_list	:	schema_element */
/*schema_element_list	:	add_column */
/*schema_element_list	:	schema_element_list schema_element */
/*schema_element_list	:	schema_element_list add_column */
static psrNode_t* AR_STDCALL handle_schema_element_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*schema_element	:	base_table_def */
/*schema_element	:	create_index_def */
/*schema_element	:	drop_table */
/*schema_element	:	drop_index */
/*schema_element	:	table_rename */
/*schema_element	:	privilege_def */
/*schema_element	:	privilege_revoke */
/*schema_element	:	create_user_statement */
/*schema_element	:	delete_user_statement */
/*schema_element	:	set_pass */
/*schema_element	:	set_group_stmt */
/*schema_element	:	add_group_stmt */
/*schema_element	:	delete_group_stmt */
/*schema_element	:	user_defined_type */
/*schema_element	:	user_defined_type_drop */
/*schema_element	:	user_defined_type_alter */
static psrNode_t* AR_STDCALL handle_schema_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*identifier	:	NAME */
/*identifier	:	TYPE */
/*identifier	:	FINAL_L */
/*identifier	:	METHOD */
/*identifier	:	CHECKED */
/*identifier	:	SYSTEM */
/*identifier	:	GENERATED */
/*identifier	:	SOURCE */
/*identifier	:	RESULT */
/*identifier	:	LOCATOR */
/*identifier	:	INSTANCE_L */
/*identifier	:	CONSTRUCTOR */
/*identifier	:	SELF_L */
/*identifier	:	OVERRIDING */
/*identifier	:	STYLE */
/*identifier	:	SQL_L */
/*identifier	:	GENERAL */
/*identifier	:	DETERMINISTIC */
/*identifier	:	NO */
/*identifier	:	CONTAINS */
/*identifier	:	READS */
/*identifier	:	DATA */
/*identifier	:	MODIFIES */
/*identifier	:	INPUT */
/*identifier	:	CALLED */
/*identifier	:	ADA */
/*identifier	:	C */
/*identifier	:	COBOL */
/*identifier	:	FORTRAN */
/*identifier	:	MUMPS */
/*identifier	:	PASCAL_L */
/*identifier	:	PLI */
/*identifier	:	NAME_L */
/*identifier	:	TEXT_L */
/*identifier	:	JAVA */
/*identifier	:	INOUT_L */
/*identifier	:	REMOTE */
/*identifier	:	KEYSET */
/*identifier	:	VALUE */
/*identifier	:	PARAMETER */
/*identifier	:	VARIABLE */
/*identifier	:	CLR */
/*identifier	:	TEMPORARY */
/*identifier	:	ADMIN_L */
/*identifier	:	__SOAP_DOC */
/*identifier	:	__SOAP_DOCW */
/*identifier	:	__SOAP_HEADER */
/*identifier	:	__SOAP_HTTP */
/*identifier	:	__SOAP_NAME */
/*identifier	:	__SOAP_TYPE */
/*identifier	:	__SOAP_XML_TYPE */
/*identifier	:	__SOAP_FAULT */
/*identifier	:	__SOAP_DIME_ENC */
/*identifier	:	__SOAP_ENC_MIME */
/*identifier	:	__SOAP_OPTIONS */
/*identifier	:	START_L */
/*identifier	:	ATTRIBUTE */
/*identifier	:	REXECUTE */
/*identifier	:	PERMISSION_SET */
/*identifier	:	AUTOREGISTER_L */
/*identifier	:	LIBRARY_L */
/*identifier	:	ASSEMBLY_L */
/*identifier	:	SAFE_L */
/*identifier	:	UNRESTRICTED */
/*identifier	:	INCREMENT_L */
/*identifier	:	FOREACH */
static psrNode_t* AR_STDCALL handle_identifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*base_table_def	:	CREATE TABLE new_table_name ( base_table_element_commalist ) */
static psrNode_t* AR_STDCALL handle_base_table_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*base_table_element_commalist	:	base_table_element */
/*base_table_element_commalist	:	base_table_element_commalist , base_table_element */
static psrNode_t* AR_STDCALL handle_base_table_element_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*base_table_element	:	column_def */
/*base_table_element	:	table_constraint_def */
static psrNode_t* AR_STDCALL handle_base_table_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_def	:	column column_data_type column_def_opt_list */
static psrNode_t* AR_STDCALL handle_column_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_referential_triggered_action	:	 */
/*opt_referential_triggered_action	:	referential_rule */
/*opt_referential_triggered_action	:	referential_rule referential_rule */
static psrNode_t* AR_STDCALL handle_opt_referential_triggered_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*referential_rule	:	ON UPDATE referential_action */
/*referential_rule	:	delete_referential_rule */
static psrNode_t* AR_STDCALL handle_referential_rule(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*delete_referential_rule	:	ON DELETE_L referential_action */
static psrNode_t* AR_STDCALL handle_delete_referential_rule(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_on_delete_referential_rule	:	 */
/*opt_on_delete_referential_rule	:	delete_referential_rule */
static psrNode_t* AR_STDCALL handle_opt_on_delete_referential_rule(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*referential_action	:	CASCADE */
/*referential_action	:	SET NULLX */
/*referential_action	:	SET DEFAULT */
static psrNode_t* AR_STDCALL handle_referential_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*references	:	REFERENCES q_table_name opt_column_commalist opt_referential_triggered_action */
static psrNode_t* AR_STDCALL handle_references(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_def_opt_list	:	 */
/*column_def_opt_list	:	column_def_opt_list column_def_opt */
static psrNode_t* AR_STDCALL handle_column_def_opt_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*identity_opt	:	START_L WITH signed_literal */
/*identity_opt	:	INCREMENT_L BY INTNUM */
static psrNode_t* AR_STDCALL handle_identity_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*identity_opt_list	:	identity_opt */
/*identity_opt_list	:	identity_opt_list , identity_opt */
static psrNode_t* AR_STDCALL handle_identity_opt_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_def_opt	:	NOT NULLX */
/*column_def_opt	:	NULLX */
/*column_def_opt	:	IDENTITY */
/*column_def_opt	:	IDENTITY ( identity_opt_list ) */
/*column_def_opt	:	PRIMARY KEY */
/*column_def_opt	:	DEFAULT signed_literal */
/*column_def_opt	:	COLLATE q_table_name */
/*column_def_opt	:	references */
/*column_def_opt	:	IDENTIFIED BY column */
/*column_def_opt	:	CHECK ( search_condition ) */
/*column_def_opt	:	WITH SCHEMA column_xml_schema_def */
/*column_def_opt	:	UNIQUE */
static psrNode_t* AR_STDCALL handle_column_def_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_xml_schema_def	:	( STRING , STRING ) */
/*column_xml_schema_def	:	( STRING , STRING , STRING ) */
static psrNode_t* AR_STDCALL handle_column_xml_schema_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_constraint_def	:	UNDER q_table_name */
/*table_constraint_def	:	opt_constraint_name PRIMARY KEY ( index_column_commalist ) opt_index_option_list */
/*table_constraint_def	:	opt_constraint_name FOREIGN KEY ( column_commalist ) references */
/*table_constraint_def	:	opt_constraint_name CHECK ( search_condition ) */
/*table_constraint_def	:	opt_constraint_name UNIQUE ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_table_constraint_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_constraint_name	:	 */
/*opt_constraint_name	:	CONSTRAINT identifier */
static psrNode_t* AR_STDCALL handle_opt_constraint_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_commalist	:	column */
/*column_commalist	:	column_commalist , column */
static psrNode_t* AR_STDCALL handle_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*index_column_commalist	:	column opt_asc_desc */
/*index_column_commalist	:	index_column_commalist , column opt_asc_desc */
static psrNode_t* AR_STDCALL handle_index_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*index_option	:	CLUSTERED */
/*index_option	:	UNIQUE */
/*index_option	:	OBJECT_ID */
static psrNode_t* AR_STDCALL handle_index_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*index_option_list	:	index_option */
/*index_option_list	:	index_option_list index_option */
static psrNode_t* AR_STDCALL handle_index_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_index_option_list	:	 */
/*opt_index_option_list	:	index_option_list */
static psrNode_t* AR_STDCALL handle_opt_index_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_index_def	:	CREATE opt_index_option_list INDEX index ON new_table_name ( index_column_commalist ) */
static psrNode_t* AR_STDCALL handle_create_index_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_index	:	DROP INDEX identifier opt_table */
static psrNode_t* AR_STDCALL handle_drop_index(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_table	:	 */
/*opt_table	:	q_table_name */
static psrNode_t* AR_STDCALL handle_opt_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_table	:	DROP TABLE q_table_name */
/*drop_table	:	DROP VIEW q_table_name */
static psrNode_t* AR_STDCALL handle_drop_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_col_add_column	:	 */
/*opt_col_add_column	:	COLUMN */
static psrNode_t* AR_STDCALL handle_opt_col_add_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*add_col_column_def_list	:	column_def */
/*add_col_column_def_list	:	add_col_column_def_list , column_def */
static psrNode_t* AR_STDCALL handle_add_col_column_def_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*add_col_column_list	:	column */
/*add_col_column_list	:	add_col_column_list , column */
static psrNode_t* AR_STDCALL handle_add_col_column_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*add_column	:	ALTER TABLE q_table_name ADD opt_col_add_column add_col_column_def_list */
/*add_column	:	ALTER TABLE q_table_name DROP opt_col_add_column add_col_column_list */
/*add_column	:	ALTER TABLE q_table_name MODIFY opt_col_add_column column_def */
static psrNode_t* AR_STDCALL handle_add_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_rename	:	ALTER TABLE q_table_name RENAME new_table_name */
static psrNode_t* AR_STDCALL handle_table_rename(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*constraint_op	:	ADD */
/*constraint_op	:	DROP */
/*constraint_op	:	MODIFY */
static psrNode_t* AR_STDCALL handle_constraint_op(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_drop_behavior	:	 */
/*opt_drop_behavior	:	CASCADE */
/*opt_drop_behavior	:	RESTRICT */
static psrNode_t* AR_STDCALL handle_opt_drop_behavior(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_table_constraint_def	:	CONSTRAINT identifier opt_drop_behavior */
/*opt_table_constraint_def	:	table_constraint_def */
static psrNode_t* AR_STDCALL handle_opt_table_constraint_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*alter_constraint	:	ALTER TABLE q_table_name constraint_op opt_table_constraint_def */
static psrNode_t* AR_STDCALL handle_alter_constraint(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_xml_schema	:	CREATE XML SCHEMA STRING */
static psrNode_t* AR_STDCALL handle_create_xml_schema(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*view_query_spec	:	query_exp */
/*view_query_spec	:	query_no_from_spec */
static psrNode_t* AR_STDCALL handle_view_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty_1	:	 */
static psrNode_t* AR_STDCALL handle_empty_1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*view_def	:	CREATE VIEW new_table_name empty_1 opt_column_commalist AS view_query_spec opt_with_check_option */
/*view_def	:	CREATE PROCEDURE VIEW new_table_name AS q_table_name ( column_commalist_or_empty ) ( proc_col_list ) */
static psrNode_t* AR_STDCALL handle_view_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_check_option	:	 */
/*opt_with_check_option	:	WITH CHECK OPTION */
static psrNode_t* AR_STDCALL handle_opt_with_check_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_column_commalist	:	 */
/*opt_column_commalist	:	( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*priv_opt_column_commalist	:	 */
/*priv_opt_column_commalist	:	( column_commalist ) */
static psrNode_t* AR_STDCALL handle_priv_opt_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*privilege_def	:	GRANT ALL PRIVILEGES TO grantee */
/*privilege_def	:	GRANT privileges ON table TO grantee_commalist opt_with_grant_option */
/*privilege_def	:	GRANT EXECUTE ON function_name TO grantee_commalist opt_with_grant_option */
/*privilege_def	:	GRANT REXECUTE ON STRING TO grantee_commalist */
/*privilege_def	:	GRANT UNDER ON q_old_type_name TO grantee_commalist opt_with_grant_option */
/*privilege_def	:	GRANT grantee_commalist TO grantee_commalist opt_with_admin_option */
static psrNode_t* AR_STDCALL handle_privilege_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_admin_option	:	 */
/*opt_with_admin_option	:	WITH ADMIN_L OPTION */
static psrNode_t* AR_STDCALL handle_opt_with_admin_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*privilege_revoke	:	REVOKE privileges ON table FROM grantee_commalist */
/*privilege_revoke	:	REVOKE EXECUTE ON function_name FROM grantee_commalist */
/*privilege_revoke	:	REVOKE UNDER ON q_old_type_name FROM grantee_commalist */
/*privilege_revoke	:	REVOKE REXECUTE ON STRING FROM grantee_commalist */
/*privilege_revoke	:	REVOKE grantee_commalist FROM grantee_commalist */
static psrNode_t* AR_STDCALL handle_privilege_revoke(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_grant_option	:	 */
/*opt_with_grant_option	:	WITH GRANT OPTION */
static psrNode_t* AR_STDCALL handle_opt_with_grant_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*privileges	:	ALL PRIVILEGES */
/*privileges	:	ALL */
/*privileges	:	operation_commalist */
static psrNode_t* AR_STDCALL handle_privileges(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*operation_commalist	:	operation */
/*operation_commalist	:	operation_commalist , operation */
static psrNode_t* AR_STDCALL handle_operation_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*operation	:	SELECT priv_opt_column_commalist */
/*operation	:	INSERT */
/*operation	:	DELETE_L */
/*operation	:	UPDATE priv_opt_column_commalist */
/*operation	:	REFERENCES priv_opt_column_commalist */
static psrNode_t* AR_STDCALL handle_operation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*grantee_commalist	:	grantee */
/*grantee_commalist	:	grantee_commalist , grantee */
static psrNode_t* AR_STDCALL handle_grantee_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*grantee	:	PUBLIC */
/*grantee	:	user */
static psrNode_t* AR_STDCALL handle_grantee(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*set_pass	:	SET PASSWORD identifier identifier */
static psrNode_t* AR_STDCALL handle_set_pass(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_user_statement	:	CREATE USER user */
/*create_user_statement	:	CREATE ROLE_L user */
static psrNode_t* AR_STDCALL handle_create_user_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*delete_user_statement	:	DELETE_L USER user */
/*delete_user_statement	:	DELETE_L USER user CASCADE */
/*delete_user_statement	:	DROP USER user */
/*delete_user_statement	:	DROP USER user CASCADE */
/*delete_user_statement	:	DROP ROLE_L user */
static psrNode_t* AR_STDCALL handle_delete_user_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*set_group_stmt	:	SET USER GROUP user user */
static psrNode_t* AR_STDCALL handle_set_group_stmt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*add_group_stmt	:	ADD USER GROUP user user */
static psrNode_t* AR_STDCALL handle_add_group_stmt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*delete_group_stmt	:	DELETE_L USER GROUP user user */
static psrNode_t* AR_STDCALL handle_delete_group_stmt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_attach_primary_key	:	 */
/*opt_attach_primary_key	:	PRIMARY KEY ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_attach_primary_key(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*attach_table	:	ATTACH TABLE attach_q_table_name opt_attach_primary_key opt_as FROM literal opt_login opt_not_select opt_remote_name */
static psrNode_t* AR_STDCALL handle_attach_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_as	:	 */
/*opt_as	:	AS new_table_name */
static psrNode_t* AR_STDCALL handle_opt_as(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_login	:	 */
/*opt_login	:	USER scalar_exp PASSWORD scalar_exp */
static psrNode_t* AR_STDCALL handle_opt_login(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_not_select	:	 */
/*opt_not_select	:	NOT SELECT */
static psrNode_t* AR_STDCALL handle_opt_not_select(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_remote_name	:	 */
/*opt_remote_name	:	REMOTE AS scalar_exp */
static psrNode_t* AR_STDCALL handle_opt_remote_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cursor_type	:	STATIC_L */
/*cursor_type	:	DYNAMIC */
/*cursor_type	:	KEYSET */
static psrNode_t* AR_STDCALL handle_cursor_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cursor_def	:	DECLARE identifier CURSOR FOR query_exp */
/*cursor_def	:	DECLARE identifier cursor_type CURSOR FOR query_exp */
static psrNode_t* AR_STDCALL handle_cursor_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_order_by_clause	:	 */
/*opt_order_by_clause	:	ORDER BY ordering_spec_commalist */
static psrNode_t* AR_STDCALL handle_opt_order_by_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ordering_spec_commalist	:	ordering_spec */
/*ordering_spec_commalist	:	ordering_spec_commalist , ordering_spec */
static psrNode_t* AR_STDCALL handle_ordering_spec_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*ordering_spec	:	scalar_exp opt_asc_desc */
/*ordering_spec	:	mssql_xml_col opt_asc_desc */
static psrNode_t* AR_STDCALL handle_ordering_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_asc_desc	:	 */
/*opt_asc_desc	:	ASC */
/*opt_asc_desc	:	DESC */
static psrNode_t* AR_STDCALL handle_opt_asc_desc(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_snapshot_log	:	CREATE SNAPSHOT LOGX FOR q_table_name */
static psrNode_t* AR_STDCALL handle_create_snapshot_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_snapshot_log	:	DROP SNAPSHOT LOGX FOR q_table_name */
static psrNode_t* AR_STDCALL handle_drop_snapshot_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*purge_snapshot_log	:	PURGE SNAPSHOT LOGX FOR q_table_name */
static psrNode_t* AR_STDCALL handle_purge_snapshot_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_snapshot_string_literal	:	 */
/*opt_snapshot_string_literal	:	STRING */
static psrNode_t* AR_STDCALL handle_opt_snapshot_string_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_snapshot_where_clause	:	 */
/*opt_snapshot_where_clause	:	WHERE STRING */
static psrNode_t* AR_STDCALL handle_opt_snapshot_where_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_snapshot	:	CREATE SNAPSHOT q_table_name FROM q_table_name opt_snapshot_string_literal opt_snapshot_where_clause */
/*create_snapshot	:	CREATE NONINCREMENTAL SNAPSHOT q_table_name AS STRING */
static psrNode_t* AR_STDCALL handle_create_snapshot(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_delete	:	 */
/*opt_with_delete	:	WITH DELETE_L */
static psrNode_t* AR_STDCALL handle_opt_with_delete(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_snapshot	:	DROP SNAPSHOT q_table_name opt_with_delete */
static psrNode_t* AR_STDCALL handle_drop_snapshot(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_nonincremental	:	 */
/*opt_nonincremental	:	AS NONINCREMENTAL */
static psrNode_t* AR_STDCALL handle_opt_nonincremental(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*refresh_snapshot	:	UPDATE SNAPSHOT q_table_name opt_nonincremental */
static psrNode_t* AR_STDCALL handle_refresh_snapshot(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_freetext_index	:	CREATE TEXT_L opt_xml INDEX ON q_table_name ( column ) opt_with_key opt_deffer_generation opt_with opt_data_modification_action opt_lang opt_enc */
static psrNode_t* AR_STDCALL handle_create_freetext_index(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_data_modification_action	:	 */
/*opt_data_modification_action	:	USING FUNCTION */
static psrNode_t* AR_STDCALL handle_opt_data_modification_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_column	:	 */
/*opt_column	:	( column ) */
static psrNode_t* AR_STDCALL handle_opt_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_freetext_trigger	:	CREATE TEXT_L TRIGGER ON q_table_name opt_column */
static psrNode_t* AR_STDCALL handle_create_freetext_trigger(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_freetext_trigger	:	DROP TEXT_L TRIGGER ON q_table_name opt_column */
static psrNode_t* AR_STDCALL handle_drop_freetext_trigger(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_xml	:	 */
/*opt_xml	:	XML */
static psrNode_t* AR_STDCALL handle_opt_xml(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_key	:	 */
/*opt_with_key	:	WITH KEY column */
static psrNode_t* AR_STDCALL handle_opt_with_key(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with	:	 */
/*opt_with	:	CLUSTERED WITH ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_with(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_lang	:	 */
/*opt_lang	:	LANGUAGE STRING */
static psrNode_t* AR_STDCALL handle_opt_lang(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_enc	:	 */
/*opt_enc	:	ENCODING STRING */
static psrNode_t* AR_STDCALL handle_opt_enc(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_deffer_generation	:	 */
/*opt_deffer_generation	:	NOT INSERT */
static psrNode_t* AR_STDCALL handle_opt_deffer_generation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*manipulative_statement	:	query_exp */
/*manipulative_statement	:	query_no_from_spec */
/*manipulative_statement	:	update_statement_positioned */
/*manipulative_statement	:	update_statement_searched */
/*manipulative_statement	:	insert_statement */
/*manipulative_statement	:	delete_statement_positioned */
/*manipulative_statement	:	delete_statement_searched */
/*manipulative_statement	:	call_statement */
/*manipulative_statement	:	static_method_invocation */
/*manipulative_statement	:	METHOD CALL static_method_invocation */
/*manipulative_statement	:	top_level_method_invocation */
/*manipulative_statement	:	set_statement */
/*manipulative_statement	:	drop_xml_view */
/*manipulative_statement	:	commit_statement */
/*manipulative_statement	:	rollback_statement */
/*manipulative_statement	:	admin_statement */
/*manipulative_statement	:	use_statement */
/*manipulative_statement	:	attach_table */
/*manipulative_statement	:	create_snapshot_log */
/*manipulative_statement	:	drop_snapshot_log */
/*manipulative_statement	:	purge_snapshot_log */
/*manipulative_statement	:	create_snapshot */
/*manipulative_statement	:	drop_snapshot */
/*manipulative_statement	:	refresh_snapshot */
/*manipulative_statement	:	create_freetext_index */
/*manipulative_statement	:	create_freetext_trigger */
/*manipulative_statement	:	drop_freetext_trigger */
static psrNode_t* AR_STDCALL handle_manipulative_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*use_statement	:	USE identifier */
static psrNode_t* AR_STDCALL handle_use_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*close_statement	:	CLOSE cursor */
static psrNode_t* AR_STDCALL handle_close_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*commit_statement	:	COMMIT WORK */
static psrNode_t* AR_STDCALL handle_commit_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*delete_statement_positioned	:	DELETE_L FROM table WHERE CURRENT OF cursor */
static psrNode_t* AR_STDCALL handle_delete_statement_positioned(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*delete_statement_searched	:	DELETE_L FROM table opt_where_clause */
static psrNode_t* AR_STDCALL handle_delete_statement_searched(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*fetch_statement	:	FETCH cursor INTO target_commalist */
/*fetch_statement	:	FETCH cursor NAME INTO target_commalist */
/*fetch_statement	:	FETCH cursor NAME scalar_exp INTO target_commalist */
static psrNode_t* AR_STDCALL handle_fetch_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*insert_mode	:	INTO */
/*insert_mode	:	REPLACING */
/*insert_mode	:	SOFT */
static psrNode_t* AR_STDCALL handle_insert_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*insert_statement	:	INSERT insert_mode table priv_opt_column_commalist values_or_query_spec */
static psrNode_t* AR_STDCALL handle_insert_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*values_or_query_spec	:	VALUES ( insert_atom_commalist ) */
/*values_or_query_spec	:	query_spec */
static psrNode_t* AR_STDCALL handle_values_or_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*insert_atom_commalist	:	insert_atom */
/*insert_atom_commalist	:	insert_atom_commalist , insert_atom */
static psrNode_t* AR_STDCALL handle_insert_atom_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*insert_atom	:	scalar_exp */
static psrNode_t* AR_STDCALL handle_insert_atom(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*sql_option	:	ORDER */
/*sql_option	:	HASH */
/*sql_option	:	LOOP */
/*sql_option	:	INDEX identifier */
/*sql_option	:	INDEX PRIMARY KEY */
/*sql_option	:	INDEX TEXT_L KEY */
/*sql_option	:	NAME INTNUM */
static psrNode_t* AR_STDCALL handle_sql_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*sql_opt_commalist	:	sql_option */
/*sql_opt_commalist	:	sql_opt_commalist , sql_option */
static psrNode_t* AR_STDCALL handle_sql_opt_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_sql_opt	:	 */
/*opt_sql_opt	:	OPTION ( sql_opt_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_sql_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_table_opt	:	 */
/*opt_table_opt	:	TABLE OPTION ( sql_opt_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_table_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cursor_option	:	EXCLUSIVE */
/*cursor_option	:	PREFETCH INTNUM */
static psrNode_t* AR_STDCALL handle_cursor_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cursor_options_commalist	:	cursor_option */
/*cursor_options_commalist	:	cursor_options_commalist , cursor_option */
static psrNode_t* AR_STDCALL handle_cursor_options_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_cursor_options_list	:	 */
/*opt_cursor_options_list	:	( cursor_options_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_cursor_options_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*open_statement	:	OPEN cursor opt_cursor_options_list */
static psrNode_t* AR_STDCALL handle_open_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*rollback_statement	:	ROLLBACK WORK */
static psrNode_t* AR_STDCALL handle_rollback_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*with_opt_cursor_options_list	:	 */
/*with_opt_cursor_options_list	:	WITH opt_cursor_options_list */
static psrNode_t* AR_STDCALL handle_with_opt_cursor_options_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*select_statement	:	SELECT opt_top selection INTO target_commalist table_exp with_opt_cursor_options_list */
static psrNode_t* AR_STDCALL handle_select_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_all_distinct	:	 */
/*opt_all_distinct	:	ALL */
/*opt_all_distinct	:	DISTINCT */
static psrNode_t* AR_STDCALL handle_opt_all_distinct(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_ties	:	 */
/*opt_ties	:	WITH TIES */
static psrNode_t* AR_STDCALL handle_opt_ties(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_top	:	opt_all_distinct */
/*opt_top	:	opt_all_distinct TOP INTNUM opt_ties */
/*opt_top	:	opt_all_distinct TOP ( scalar_exp ) opt_ties */
/*opt_top	:	opt_all_distinct TOP INTNUM , INTNUM opt_ties */
/*opt_top	:	opt_all_distinct TOP ( scalar_exp , scalar_exp ) opt_ties */
static psrNode_t* AR_STDCALL handle_opt_top(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*update_statement_positioned	:	UPDATE table SET assignment_commalist WHERE CURRENT OF cursor */
static psrNode_t* AR_STDCALL handle_update_statement_positioned(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*assignment_commalist	:	 */
/*assignment_commalist	:	assignment */
/*assignment_commalist	:	assignment_commalist , assignment */
static psrNode_t* AR_STDCALL handle_assignment_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*assignment	:	column COMPARISON scalar_exp */
static psrNode_t* AR_STDCALL handle_assignment(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*update_statement_searched	:	UPDATE table SET assignment_commalist opt_where_clause */
static psrNode_t* AR_STDCALL handle_update_statement_searched(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*target_commalist	:	target */
/*target_commalist	:	target_commalist , target */
static psrNode_t* AR_STDCALL handle_target_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*target	:	column_ref */
/*target	:	member_observer */
/*target	:	lvalue_array_ref */
static psrNode_t* AR_STDCALL handle_target(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_where_clause	:	 */
/*opt_where_clause	:	where_clause */
static psrNode_t* AR_STDCALL handle_opt_where_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_best	:	 */
/*opt_best	:	BEST */
static psrNode_t* AR_STDCALL handle_opt_best(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*query_exp	:	query_term */
/*query_exp	:	non_final_union_exp opt_best UNION opt_corresponding query_term */
/*query_exp	:	non_final_union_exp opt_best UNION ALL opt_corresponding query_term */
/*query_exp	:	non_final_union_exp INTERSECT opt_corresponding query_term */
/*query_exp	:	non_final_union_exp INTERSECT ALL opt_corresponding query_term */
/*query_exp	:	non_final_union_exp EXCEPT opt_corresponding query_term */
/*query_exp	:	non_final_union_exp EXCEPT ALL opt_corresponding query_term */
static psrNode_t* AR_STDCALL handle_query_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*non_final_union_exp	:	non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp opt_best UNION opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp opt_best UNION ALL opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp INTERSECT opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp INTERSECT ALL opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp EXCEPT opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp EXCEPT ALL opt_corresponding non_final_query_term */
static psrNode_t* AR_STDCALL handle_non_final_union_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*non_final_query_term	:	non_final_query_spec */
/*non_final_query_term	:	XPATH STRING */
static psrNode_t* AR_STDCALL handle_non_final_query_term(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*query_term	:	query_spec */
/*query_term	:	( query_exp ) opt_order_by_clause */
/*query_term	:	XPATH STRING */
static psrNode_t* AR_STDCALL handle_query_term(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_corresponding	:	 */
/*opt_corresponding	:	CORRESPONDING BY ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_corresponding(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*non_final_query_spec	:	SELECT opt_top selection non_final_table_exp */
static psrNode_t* AR_STDCALL handle_non_final_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*query_spec	:	SELECT opt_top selection table_exp */
static psrNode_t* AR_STDCALL handle_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*query_no_from_spec	:	SELECT opt_top selection */
static psrNode_t* AR_STDCALL handle_query_no_from_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*selection	:	select_scalar_exp_commalist */
static psrNode_t* AR_STDCALL handle_selection(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*non_final_table_exp	:	from_clause opt_where_clause opt_group_by_clause opt_having_clause */
static psrNode_t* AR_STDCALL handle_non_final_table_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_exp	:	from_clause opt_where_clause opt_group_by_clause opt_having_clause opt_order_by_clause opt_lock_mode opt_sql_opt */
static psrNode_t* AR_STDCALL handle_table_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*from_clause	:	FROM table_ref_commalist */
static psrNode_t* AR_STDCALL handle_from_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_ref_commalist	:	table_ref */
/*table_ref_commalist	:	table_ref_commalist , table_ref */
static psrNode_t* AR_STDCALL handle_table_ref_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*proc_col_list	:	column_def */
/*proc_col_list	:	proc_col_list , column_def */
static psrNode_t* AR_STDCALL handle_proc_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_proc_col_list	:	( proc_col_list ) */
static psrNode_t* AR_STDCALL handle_opt_proc_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_commalist_or_empty	:	 */
/*column_commalist_or_empty	:	column_commalist */
static psrNode_t* AR_STDCALL handle_column_commalist_or_empty(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_ref	:	table */
/*table_ref	:	( query_exp ) identifier */
/*table_ref	:	( query_exp ) AS identifier */
/*table_ref	:	joined_table */
/*table_ref	:	q_table_name ( column_commalist_or_empty ) opt_proc_col_list identifier */
static psrNode_t* AR_STDCALL handle_table_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table_ref_nj	:	table */
/*table_ref_nj	:	subquery identifier */
/*table_ref_nj	:	subquery AS identifier */
/*table_ref_nj	:	( joined_table ) */
static psrNode_t* AR_STDCALL handle_table_ref_nj(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*jtype	:	 */
/*jtype	:	LEFT opt_outer */
/*jtype	:	RIGHT opt_outer */
/*jtype	:	FULL opt_outer */
/*jtype	:	INNER */
/*jtype	:	CROSS */
static psrNode_t* AR_STDCALL handle_jtype(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_outer	:	 */
/*opt_outer	:	OUTER */
static psrNode_t* AR_STDCALL handle_opt_outer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*join	:	NATURAL jtype */
/*join	:	jtype */
static psrNode_t* AR_STDCALL handle_join(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*joined_table	:	joined_table_1 */
/*joined_table	:	BEGIN_OJ_X joined_table_1 ENDX */
/*joined_table	:	( joined_table_1 ) */
static psrNode_t* AR_STDCALL handle_joined_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*joined_table_1	:	table_ref join JOIN table_ref_nj join_condition */
static psrNode_t* AR_STDCALL handle_joined_table_1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*join_condition	:	 */
/*join_condition	:	ON search_condition */
/*join_condition	:	USING ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_join_condition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*where_clause	:	WHERE search_condition */
static psrNode_t* AR_STDCALL handle_where_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_group_by_clause	:	 */
/*opt_group_by_clause	:	GROUP BY ordering_spec_commalist */
/*opt_group_by_clause	:	GROUP BY ROLLUP ( ordering_spec_commalist ) */
/*opt_group_by_clause	:	GROUP BY CUBE ( ordering_spec_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_group_by_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_having_clause	:	 */
/*opt_having_clause	:	HAVING search_condition */
static psrNode_t* AR_STDCALL handle_opt_having_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_lock_mode	:	 */
/*opt_lock_mode	:	FOR UPDATE */
/*opt_lock_mode	:	FOR XML NAME */
/*opt_lock_mode	:	FOR XML NAME NAME */
static psrNode_t* AR_STDCALL handle_opt_lock_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*search_condition	:	search_condition OR search_condition */
/*search_condition	:	search_condition AND search_condition */
/*search_condition	:	NOT search_condition */
/*search_condition	:	( search_condition ) */
/*search_condition	:	predicate */
static psrNode_t* AR_STDCALL handle_search_condition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*predicate	:	comparison_predicate */
/*predicate	:	between_predicate */
/*predicate	:	like_predicate */
/*predicate	:	test_for_null */
/*predicate	:	in_predicate */
/*predicate	:	all_or_any_predicate */
/*predicate	:	existence_test */
/*predicate	:	scalar_exp_predicate */
static psrNode_t* AR_STDCALL handle_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*scalar_exp_predicate	:	scalar_exp */
static psrNode_t* AR_STDCALL handle_scalar_exp_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*comparison_predicate	:	scalar_exp COMPARISON scalar_exp */
static psrNode_t* AR_STDCALL handle_comparison_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*between_predicate	:	scalar_exp NOT BETWEEN scalar_exp AND scalar_exp */
/*between_predicate	:	scalar_exp BETWEEN scalar_exp AND scalar_exp */
static psrNode_t* AR_STDCALL handle_between_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*like_predicate	:	scalar_exp NOT LIKE scalar_exp opt_escape */
/*like_predicate	:	scalar_exp LIKE scalar_exp opt_escape */
static psrNode_t* AR_STDCALL handle_like_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_escape	:	 */
/*opt_escape	:	ESCAPE atom */
/*opt_escape	:	BEGINX ESCAPE atom ENDX */
static psrNode_t* AR_STDCALL handle_opt_escape(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*test_for_null	:	scalar_exp IS NOT NULLX */
/*test_for_null	:	scalar_exp IS NULLX */
static psrNode_t* AR_STDCALL handle_test_for_null(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*in_predicate	:	scalar_exp NOT IN_L subquery */
/*in_predicate	:	scalar_exp IN_L subquery */
/*in_predicate	:	scalar_exp NOT IN_L ( scalar_exp_commalist ) */
/*in_predicate	:	scalar_exp IN_L ( scalar_exp_commalist ) */
static psrNode_t* AR_STDCALL handle_in_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*all_or_any_predicate	:	scalar_exp COMPARISON any_all_some subquery */
static psrNode_t* AR_STDCALL handle_all_or_any_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*any_all_some	:	ANY */
/*any_all_some	:	ALL */
/*any_all_some	:	SOME */
static psrNode_t* AR_STDCALL handle_any_all_some(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*existence_test	:	EXISTS subquery */
static psrNode_t* AR_STDCALL handle_existence_test(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*scalar_subquery	:	subquery */
static psrNode_t* AR_STDCALL handle_scalar_subquery(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*subquery	:	( SELECT opt_top selection table_exp ) */
static psrNode_t* AR_STDCALL handle_subquery(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*scalar_exp	:	scalar_exp - scalar_exp */
/*scalar_exp	:	scalar_exp + scalar_exp */
/*scalar_exp	:	scalar_exp * scalar_exp */
/*scalar_exp	:	scalar_exp / scalar_exp */
/*scalar_exp	:	+ scalar_exp */
/*scalar_exp	:	- scalar_exp */
/*scalar_exp	:	assignment_statement */
/*scalar_exp	:	string_concatenation_operator */
/*scalar_exp	:	column_ref */
/*scalar_exp	:	scalar_exp_no_col_ref */
/*scalar_exp	:	obe_literal */
static psrNode_t* AR_STDCALL handle_scalar_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*scalar_exp_no_col_ref	:	atom_no_obe */
/*scalar_exp_no_col_ref	:	aggregate_ref */
/*scalar_exp_no_col_ref	:	scalar_subquery */
/*scalar_exp_no_col_ref	:	( scalar_exp ) */
/*scalar_exp_no_col_ref	:	( scalar_exp , scalar_exp_commalist ) */
/*scalar_exp_no_col_ref	:	function_call */
/*scalar_exp_no_col_ref	:	new_invocation */
/*scalar_exp_no_col_ref	:	cvt_exp */
/*scalar_exp_no_col_ref	:	cast_exp */
/*scalar_exp_no_col_ref	:	simple_case */
/*scalar_exp_no_col_ref	:	searched_case */
/*scalar_exp_no_col_ref	:	coalesce_exp */
/*scalar_exp_no_col_ref	:	nullif_exp */
/*scalar_exp_no_col_ref	:	array_ref */
/*scalar_exp_no_col_ref	:	static_method_invocation */
/*scalar_exp_no_col_ref	:	method_invocation */
/*scalar_exp_no_col_ref	:	member_observer */
static psrNode_t* AR_STDCALL handle_scalar_exp_no_col_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*scalar_exp_no_col_ref_no_mem_obs_chain	:	atom_no_obe */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	aggregate_ref */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	scalar_subquery */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	( scalar_exp ) */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	( scalar_exp , scalar_exp_commalist ) */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	function_call */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	new_invocation */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	cvt_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	cast_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	simple_case */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	searched_case */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	coalesce_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	nullif_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	array_ref */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	static_method_invocation */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	method_invocation */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	member_observer_no_id_chain */
static psrNode_t* AR_STDCALL handle_scalar_exp_no_col_ref_no_mem_obs_chain(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cvt_exp	:	CONVERT ( data_type , scalar_exp ) */
static psrNode_t* AR_STDCALL handle_cvt_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_collate_exp	:	 */
/*opt_collate_exp	:	COLLATE q_table_name */
static psrNode_t* AR_STDCALL handle_opt_collate_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cast_exp	:	CAST ( scalar_exp AS data_type opt_collate_exp ) */
static psrNode_t* AR_STDCALL handle_cast_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*mssql_xml_col	:	MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAMEZ */
/*mssql_xml_col	:	MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAMEYZ */
/*mssql_xml_col	:	MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAME MSSQL_XMLCOL_NAMEZ */
static psrNode_t* AR_STDCALL handle_mssql_xml_col(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*as_expression	:	scalar_exp AS identifier data_type */
/*as_expression	:	scalar_exp AS identifier */
/*as_expression	:	scalar_exp identifier */
/*as_expression	:	scalar_exp AS mssql_xml_col */
static psrNode_t* AR_STDCALL handle_as_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*array_ref	:	scalar_exp_no_col_ref [ scalar_exp ] */
/*array_ref	:	lvalue_array_ref */
static psrNode_t* AR_STDCALL handle_array_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*lvalue_array_ref	:	column_ref [ scalar_exp ] */
static psrNode_t* AR_STDCALL handle_lvalue_array_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_scalar_exp_commalist	:	 */
/*opt_scalar_exp_commalist	:	scalar_exp_commalist */
static psrNode_t* AR_STDCALL handle_opt_scalar_exp_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*function_name	:	identifier */
/*function_name	:	identifier . method_identifier */
/*function_name	:	identifier . identifier . method_identifier */
/*function_name	:	identifier . identifier . identifier . method_identifier */
/*function_name	:	identifier . . method_identifier */
/*function_name	:	identifier . . identifier . method_identifier */
/*function_name	:	LEFT */
/*function_name	:	RIGHT */
/*function_name	:	LOGX */
static psrNode_t* AR_STDCALL handle_function_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*kwd_commalist	:	identifier KWD_TAG scalar_exp */
/*kwd_commalist	:	kwd_commalist , identifier KWD_TAG scalar_exp */
static psrNode_t* AR_STDCALL handle_kwd_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*as_commalist	:	as_expression */
/*as_commalist	:	as_commalist , as_expression */
/*as_commalist	:	as_commalist , scalar_exp */
static psrNode_t* AR_STDCALL handle_as_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_arg_commalist	:	 */
/*opt_arg_commalist	:	kwd_commalist */
/*opt_arg_commalist	:	scalar_exp_commalist */
/*opt_arg_commalist	:	scalar_exp_commalist , kwd_commalist */
/*opt_arg_commalist	:	scalar_exp_commalist , as_commalist */
/*opt_arg_commalist	:	as_commalist */
static psrNode_t* AR_STDCALL handle_opt_arg_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*function_call	:	function_name ( opt_arg_commalist ) */
/*function_call	:	TIMESTAMP_FUNC ( SQL_TSI , scalar_exp , scalar_exp ) */
/*function_call	:	EXTRACT ( NAME FROM scalar_exp ) */
/*function_call	:	BEGIN_FN_X identifier ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X LEFT ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X RIGHT ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X LOGX ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X identifier ( scalar_exp IN_L scalar_exp ) ENDX */
/*function_call	:	BEGIN_CALL_X function_name ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_CALL_X function_name ENDX */
/*function_call	:	BEGIN_FN_X USER ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X CHARACTER ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X TIMESTAMP_FUNC ( SQL_TSI , scalar_exp , scalar_exp ) ENDX */
/*function_call	:	BEGIN_FN_X CONVERT ( scalar_exp , NAME ) ENDX */
/*function_call	:	BEGIN_FN_X EXTRACT ( NAME FROM scalar_exp ) ENDX */
/*function_call	:	CALL ( scalar_exp ) ( opt_arg_commalist ) */
/*function_call	:	CURRENT_DATE */
/*function_call	:	CURRENT_TIME */
/*function_call	:	CURRENT_TIME ( scalar_exp ) */
/*function_call	:	CURRENT_TIMESTAMP */
/*function_call	:	CURRENT_TIMESTAMP ( scalar_exp ) */
/*function_call	:	GROUPING ( column_ref ) */
static psrNode_t* AR_STDCALL handle_function_call(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*obe_literal	:	BEGINX identifier atom ENDX */
/*obe_literal	:	BEGIN_U_X STRING ENDX */
static psrNode_t* AR_STDCALL handle_obe_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*scalar_exp_commalist	:	scalar_exp */
/*scalar_exp_commalist	:	scalar_exp_commalist , scalar_exp */
static psrNode_t* AR_STDCALL handle_scalar_exp_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*select_scalar_exp_commalist	:	scalar_exp */
/*select_scalar_exp_commalist	:	as_expression */
/*select_scalar_exp_commalist	:	select_scalar_exp_commalist , scalar_exp */
/*select_scalar_exp_commalist	:	select_scalar_exp_commalist , as_expression */
static psrNode_t* AR_STDCALL handle_select_scalar_exp_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*atom_no_obe	:	parameter_ref */
/*atom_no_obe	:	literal */
/*atom_no_obe	:	USER */
static psrNode_t* AR_STDCALL handle_atom_no_obe(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*atom	:	atom_no_obe */
/*atom	:	obe_literal */
static psrNode_t* AR_STDCALL handle_atom(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*simple_case	:	CASE scalar_exp simple_when_list ENDX */
static psrNode_t* AR_STDCALL handle_simple_case(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*searched_case	:	CASE searched_when_list ENDX */
static psrNode_t* AR_STDCALL handle_searched_case(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*searched_when_list	:	searched_when */
/*searched_when_list	:	searched_when_list searched_when */
static psrNode_t* AR_STDCALL handle_searched_when_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*simple_when_list	:	simple_when */
/*simple_when_list	:	simple_when_list simple_when */
static psrNode_t* AR_STDCALL handle_simple_when_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*simple_when	:	WHEN scalar_exp THEN scalar_exp */
/*simple_when	:	ELSE scalar_exp */
static psrNode_t* AR_STDCALL handle_simple_when(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*searched_when	:	WHEN search_condition THEN scalar_exp */
/*searched_when	:	ELSE scalar_exp */
static psrNode_t* AR_STDCALL handle_searched_when(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*coalesce_exp	:	COALESCE ( scalar_exp_commalist ) */
static psrNode_t* AR_STDCALL handle_coalesce_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*nullif_exp	:	NULLIF ( scalar_exp , scalar_exp ) */
static psrNode_t* AR_STDCALL handle_nullif_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*parameter_ref	:	parameter */
/*parameter_ref	:	parameter parameter */
/*parameter_ref	:	parameter INDICATOR parameter */
static psrNode_t* AR_STDCALL handle_parameter_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*aggregate_ref	:	AGGREGATE function_name ( opt_arg_commalist ) */
/*aggregate_ref	:	AMMSC ( DISTINCT scalar_exp ) */
/*aggregate_ref	:	AMMSC ( ALL scalar_exp ) */
/*aggregate_ref	:	AMMSC ( scalar_exp ) */
static psrNode_t* AR_STDCALL handle_aggregate_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*literal	:	STRING */
/*literal	:	WSTRING */
/*literal	:	INTNUM */
/*literal	:	APPROXNUM */
/*literal	:	BINARYNUM */
/*literal	:	NULLX */
static psrNode_t* AR_STDCALL handle_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*signed_literal	:	STRING */
/*signed_literal	:	WSTRING */
/*signed_literal	:	INTNUM */
/*signed_literal	:	- INTNUM */
/*signed_literal	:	+ INTNUM */
/*signed_literal	:	APPROXNUM */
/*signed_literal	:	- APPROXNUM */
/*signed_literal	:	+ APPROXNUM */
/*signed_literal	:	BINARYNUM */
/*signed_literal	:	NULLX */
static psrNode_t* AR_STDCALL handle_signed_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*q_table_name	:	identifier */
/*q_table_name	:	identifier . identifier */
/*q_table_name	:	identifier . identifier . identifier */
/*q_table_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_q_table_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*attach_q_table_name	:	identifier */
/*attach_q_table_name	:	identifier . identifier */
/*attach_q_table_name	:	identifier . identifier . identifier */
/*attach_q_table_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_attach_q_table_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*new_proc_or_bif_name	:	identifier */
/*new_proc_or_bif_name	:	identifier . identifier */
/*new_proc_or_bif_name	:	identifier . identifier . identifier */
/*new_proc_or_bif_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_new_proc_or_bif_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*new_table_name	:	identifier */
/*new_table_name	:	identifier . identifier */
/*new_table_name	:	identifier . identifier . identifier */
/*new_table_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_new_table_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*table	:	q_table_name opt_table_opt */
/*table	:	q_table_name AS identifier opt_table_opt */
/*table	:	q_table_name identifier opt_table_opt */
static psrNode_t* AR_STDCALL handle_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_ref	:	identifier */
/*column_ref	:	identifier . identifier */
/*column_ref	:	identifier . identifier . identifier */
/*column_ref	:	identifier . identifier . identifier . identifier */
/*column_ref	:	identifier . . identifier . identifier */
/*column_ref	:	* */
/*column_ref	:	identifier . * */
/*column_ref	:	identifier . identifier . * */
/*column_ref	:	identifier . identifier . identifier . * */
/*column_ref	:	identifier . . identifier . * */
static psrNode_t* AR_STDCALL handle_column_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*base_data_type	:	NUMERIC */
/*base_data_type	:	NUMERIC ( INTNUM ) */
/*base_data_type	:	NUMERIC ( INTNUM , INTNUM ) */
/*base_data_type	:	DECIMAL */
/*base_data_type	:	DECIMAL ( INTNUM ) */
/*base_data_type	:	DECIMAL ( INTNUM , INTNUM ) */
/*base_data_type	:	INTEGER */
/*base_data_type	:	SMALLINT */
/*base_data_type	:	FLOAT */
/*base_data_type	:	FLOAT ( INTNUM ) */
/*base_data_type	:	REAL */
/*base_data_type	:	DOUBLE PRECISION */
/*base_data_type	:	LONG VARCHAR */
/*base_data_type	:	LONG VARBINARY */
/*base_data_type	:	VARBINARY */
/*base_data_type	:	VARBINARY ( INTNUM ) */
/*base_data_type	:	BINARY ( INTNUM ) */
/*base_data_type	:	TIMESTAMP */
/*base_data_type	:	DATETIME */
/*base_data_type	:	TIME */
/*base_data_type	:	DATE */
/*base_data_type	:	NCHAR */
/*base_data_type	:	NCHAR ( INTNUM ) */
/*base_data_type	:	NVARCHAR */
/*base_data_type	:	NVARCHAR ( INTNUM ) */
/*base_data_type	:	LONG NVARCHAR */
/*base_data_type	:	ANY */
/*base_data_type	:	ANY ( INTNUM ) */
static psrNode_t* AR_STDCALL handle_base_data_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*data_type	:	base_data_type */
/*data_type	:	CHARACTER */
/*data_type	:	VARCHAR */
/*data_type	:	VARCHAR ( INTNUM ) */
/*data_type	:	CHARACTER ( INTNUM ) */
static psrNode_t* AR_STDCALL handle_data_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*array_modifier	:	ARRAY */
/*array_modifier	:	ARRAY [ INTNUM ] */
static psrNode_t* AR_STDCALL handle_array_modifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*data_type_ref	:	data_type_ref array_modifier */
/*data_type_ref	:	data_type */
/*data_type_ref	:	q_type_name */
static psrNode_t* AR_STDCALL handle_data_type_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column_data_type	:	base_data_type */
/*column_data_type	:	CHARACTER */
/*column_data_type	:	VARCHAR */
/*column_data_type	:	VARCHAR ( INTNUM ) */
/*column_data_type	:	CHARACTER ( INTNUM ) */
/*column_data_type	:	q_type_name */
/*column_data_type	:	LONG q_type_name */
/*column_data_type	:	LONG XML */
static psrNode_t* AR_STDCALL handle_column_data_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*column	:	identifier */
/*column	:	identifier . identifier . identifier . identifier */
static psrNode_t* AR_STDCALL handle_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*index	:	identifier */
static psrNode_t* AR_STDCALL handle_index(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cursor	:	identifier */
static psrNode_t* AR_STDCALL handle_cursor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*parameter	:	PARAMETER_L */
/*parameter	:	NAMED_PARAMETER */
static psrNode_t* AR_STDCALL handle_parameter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*user	:	identifier */
static psrNode_t* AR_STDCALL handle_user(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_log	:	 */
/*opt_log	:	STRING */
static psrNode_t* AR_STDCALL handle_opt_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*comma_opt_log	:	 */
/*comma_opt_log	:	, STRING */
static psrNode_t* AR_STDCALL handle_comma_opt_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*admin_statement	:	SHUTDOWN opt_log */
/*admin_statement	:	CHECKPOINT opt_log */
/*admin_statement	:	CHECKPOINT STRING STRING */
/*admin_statement	:	BACKUP STRING */
/*admin_statement	:	CHECK */
/*admin_statement	:	SYNC REPLICATION opt_log comma_opt_log */
/*admin_statement	:	DISCONNECT REPLICATION opt_log */
/*admin_statement	:	LOGX ON */
/*admin_statement	:	LOGX OFF */
static psrNode_t* AR_STDCALL handle_admin_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*user_aggregate_declaration	:	CREATE AGGREGATE new_table_name rout_parameter_list opt_return FROM new_proc_or_bif_name , new_proc_or_bif_name , new_proc_or_bif_name user_aggregate_merge_opt */
static psrNode_t* AR_STDCALL handle_user_aggregate_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*user_aggregate_merge_opt	:	 */
/*user_aggregate_merge_opt	:	, new_proc_or_bif_name */
static psrNode_t* AR_STDCALL handle_user_aggregate_merge_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*routine_declaration	:	CREATE routine_head new_table_name rout_parameter_list opt_return rout_alt_type compound_statement */
/*routine_declaration	:	ATTACH routine_head attach_q_table_name rout_parameter_list opt_return rout_alt_type opt_as FROM literal */
/*routine_declaration	:	CREATE routine_head new_table_name rout_parameter_list opt_return rout_alt_type LANGUAGE external_language_name EXTERNAL NAME_L STRING opt_type_option_list */
static psrNode_t* AR_STDCALL handle_routine_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*module_body_part	:	routine_head identifier rout_parameter_list opt_return rout_alt_type compound_statement */
static psrNode_t* AR_STDCALL handle_module_body_part(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*module_body	:	module_body_part ; */
/*module_body	:	module_body module_body_part ; */
static psrNode_t* AR_STDCALL handle_module_body(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*module_declaration	:	CREATE MODULE new_table_name BEGINX module_body ENDX */
static psrNode_t* AR_STDCALL handle_module_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*routine_head	:	FUNCTION */
/*routine_head	:	PROCEDURE */
static psrNode_t* AR_STDCALL handle_routine_head(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_return	:	 */
/*opt_return	:	RETURNS data_type_ref */
static psrNode_t* AR_STDCALL handle_opt_return(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*rout_parameter_list	:	( ) */
/*rout_parameter_list	:	( parameter_commalist ) */
static psrNode_t* AR_STDCALL handle_rout_parameter_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*parameter_commalist	:	rout_parameter */
/*parameter_commalist	:	parameter_commalist , rout_parameter */
static psrNode_t* AR_STDCALL handle_parameter_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*rout_parameter	:	parameter_mode column_ref data_type_ref rout_alt_type */
/*rout_parameter	:	parameter_mode column_ref data_type_ref DEFAULT signed_literal rout_alt_type */
/*rout_parameter	:	parameter_mode column_ref data_type_ref EQUALS signed_literal rout_alt_type */
static psrNode_t* AR_STDCALL handle_rout_parameter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*parameter_mode	:	IN_L */
/*parameter_mode	:	OUT_L */
/*parameter_mode	:	INOUT_L */
static psrNode_t* AR_STDCALL handle_parameter_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_parameter_mode	:	 */
/*opt_parameter_mode	:	parameter_mode */
static psrNode_t* AR_STDCALL handle_opt_parameter_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_soap_enc_mode	:	 */
/*opt_soap_enc_mode	:	__SOAP_DIME_ENC IN_L */
/*opt_soap_enc_mode	:	__SOAP_DIME_ENC OUT_L */
/*opt_soap_enc_mode	:	__SOAP_DIME_ENC INOUT_L */
/*opt_soap_enc_mode	:	__SOAP_ENC_MIME IN_L */
/*opt_soap_enc_mode	:	__SOAP_ENC_MIME OUT_L */
/*opt_soap_enc_mode	:	__SOAP_ENC_MIME INOUT_L */
static psrNode_t* AR_STDCALL handle_opt_soap_enc_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*soap_proc_opt_list	:	soap_proc_opt */
/*soap_proc_opt_list	:	soap_proc_opt_list , soap_proc_opt */
static psrNode_t* AR_STDCALL handle_soap_proc_opt_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*soap_proc_opt	:	NAME EQUALS signed_literal */
static psrNode_t* AR_STDCALL handle_soap_proc_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*soap_kwd	:	__SOAP_TYPE */
/*soap_kwd	:	__SOAP_HEADER */
/*soap_kwd	:	__SOAP_FAULT */
/*soap_kwd	:	__SOAP_DOC */
/*soap_kwd	:	__SOAP_XML_TYPE */
/*soap_kwd	:	__SOAP_DOCW */
/*soap_kwd	:	__SOAP_HTTP */
static psrNode_t* AR_STDCALL handle_soap_kwd(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*rout_alt_type	:	 */
/*rout_alt_type	:	__SOAP_OPTIONS ( soap_kwd EQUALS STRING opt_soap_enc_mode , soap_proc_opt_list ) */
/*rout_alt_type	:	soap_kwd STRING opt_soap_enc_mode */
static psrNode_t* AR_STDCALL handle_rout_alt_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*routine_statement	:	select_statement */
/*routine_statement	:	update_statement_positioned */
/*routine_statement	:	update_statement_searched */
/*routine_statement	:	insert_statement */
/*routine_statement	:	delete_statement_positioned */
/*routine_statement	:	delete_statement_searched */
/*routine_statement	:	close_statement */
/*routine_statement	:	fetch_statement */
/*routine_statement	:	open_statement */
/*routine_statement	:	rollback_statement */
/*routine_statement	:	commit_statement */
/*routine_statement	:	 */
static psrNode_t* AR_STDCALL handle_routine_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty2	:	 */
static psrNode_t* AR_STDCALL handle_empty2(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*compound_statement	:	BEGINX empty2 statement_list ENDX */
static psrNode_t* AR_STDCALL handle_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*statement_list	:	statement_in_cs */
/*statement_list	:	statement_list statement_in_cs */
static psrNode_t* AR_STDCALL handle_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*statement_in_cs	:	local_declaration ; */
/*statement_in_cs	:	compound_statement */
/*statement_in_cs	:	empty3 statement_in_cs_oper */
static psrNode_t* AR_STDCALL handle_statement_in_cs(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty3	:	 */
static psrNode_t* AR_STDCALL handle_empty3(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*statement_in_cs_oper	:	routine_statement ; */
/*statement_in_cs_oper	:	control_statement */
/*statement_in_cs_oper	:	identifier COLON statement_in_cs */
/*statement_in_cs_oper	:	HTMLSTR */
/*statement_in_cs_oper	:	COMPARISON scalar_exp HTMLSTR */
/*statement_in_cs_oper	:	/ scalar_exp HTMLSTR */
static psrNode_t* AR_STDCALL handle_statement_in_cs_oper(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*statement	:	compound_statement */
/*statement	:	empty4 routine_statement ; */
/*statement	:	empty5 control_statement */
static psrNode_t* AR_STDCALL handle_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty4	:	 */
static psrNode_t* AR_STDCALL handle_empty4(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty5	:	 */
static psrNode_t* AR_STDCALL handle_empty5(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*local_declaration	:	cursor_def */
/*local_declaration	:	variable_declaration */
/*local_declaration	:	handler_declaration */
static psrNode_t* AR_STDCALL handle_local_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*variable_declaration	:	DECLARE variable_list data_type_ref */
static psrNode_t* AR_STDCALL handle_variable_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*variable_list	:	identifier */
/*variable_list	:	variable_list , identifier */
static psrNode_t* AR_STDCALL handle_variable_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*condition	:	NOT FOUND */
/*condition	:	SQLSTATE STRING */
/*condition	:	SQLSTATE VALUE STRING */
/*condition	:	SQLEXCEPTION */
/*condition	:	SQLWARNING */
static psrNode_t* AR_STDCALL handle_condition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*handler_statement	:	compound_statement */
/*handler_statement	:	routine_statement */
/*handler_statement	:	call_statement */
/*handler_statement	:	method_invocation */
/*handler_statement	:	static_method_invocation */
/*handler_statement	:	set_statement */
/*handler_statement	:	RESIGNAL */
/*handler_statement	:	RESIGNAL scalar_exp */
/*handler_statement	:	return_statement */
/*handler_statement	:	assignment_statement */
/*handler_statement	:	if_statement */
/*handler_statement	:	goto_statement */
/*handler_statement	:	for_statement */
/*handler_statement	:	while_statement */
static psrNode_t* AR_STDCALL handle_handler_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*handler_declaration	:	WHENEVER condition GOTO identifier */
/*handler_declaration	:	WHENEVER condition GO TO identifier */
/*handler_declaration	:	WHENEVER condition DEFAULT */
/*handler_declaration	:	DECLARE handler_type HANDLER FOR cond_value_list handler_statement */
static psrNode_t* AR_STDCALL handle_handler_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*handler_type	:	CONTINUE */
/*handler_type	:	EXIT */
static psrNode_t* AR_STDCALL handle_handler_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*cond_value_list	:	condition */
/*cond_value_list	:	cond_value_list , condition */
static psrNode_t* AR_STDCALL handle_cond_value_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*control_statement	:	call_statement ; */
/*control_statement	:	method_invocation ; */
/*control_statement	:	static_method_invocation ; */
/*control_statement	:	set_statement ; */
/*control_statement	:	RESIGNAL ; */
/*control_statement	:	RESIGNAL scalar_exp ; */
/*control_statement	:	return_statement ; */
/*control_statement	:	assignment_statement ; */
/*control_statement	:	if_statement */
/*control_statement	:	goto_statement ; */
/*control_statement	:	for_statement */
/*control_statement	:	while_statement */
static psrNode_t* AR_STDCALL handle_control_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*assignment_statement	:	lvalue EQUALS scalar_exp */
/*assignment_statement	:	column_ref [ scalar_exp ] EQUALS scalar_exp */
static psrNode_t* AR_STDCALL handle_assignment_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*lvalue	:	column_ref */
/*lvalue	:	member_observer */
static psrNode_t* AR_STDCALL handle_lvalue(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*if_statement	:	IF ( search_condition ) statement opt_else */
static psrNode_t* AR_STDCALL handle_if_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_else	:	 */
/*opt_else	:	ELSE statement */
static psrNode_t* AR_STDCALL handle_opt_else(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*call_statement	:	CALL function_name ( opt_arg_commalist ) */
/*call_statement	:	function_call */
static psrNode_t* AR_STDCALL handle_call_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*set_statement	:	SET identifier COMPARISON scalar_exp */
/*set_statement	:	SET identifier ON */
/*set_statement	:	SET identifier OFF */
static psrNode_t* AR_STDCALL handle_set_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*goto_statement	:	GOTO identifier */
/*goto_statement	:	GO TO identifier */
static psrNode_t* AR_STDCALL handle_goto_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*return_statement	:	RETURN scalar_exp */
/*return_statement	:	RETURN */
static psrNode_t* AR_STDCALL handle_return_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*while_statement	:	WHILE ( search_condition ) statement */
static psrNode_t* AR_STDCALL handle_while_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_init_statement	:	assignment_statement */
/*for_init_statement	:	variable_declaration */
/*for_init_statement	:	call_statement */
/*for_init_statement	:	static_method_invocation */
static psrNode_t* AR_STDCALL handle_for_init_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_init_statement_list	:	 */
/*for_init_statement_list	:	for_init_statement */
/*for_init_statement_list	:	for_init_statement_list , for_init_statement */
static psrNode_t* AR_STDCALL handle_for_init_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_inc_statement	:	assignment_statement */
/*for_inc_statement	:	call_statement */
/*for_inc_statement	:	static_method_invocation */
static psrNode_t* AR_STDCALL handle_for_inc_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_inc_statement_list	:	 */
/*for_inc_statement_list	:	for_inc_statement */
/*for_inc_statement_list	:	for_inc_statement_list , for_inc_statement */
static psrNode_t* AR_STDCALL handle_for_inc_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_opt_search_cond	:	 */
/*for_opt_search_cond	:	search_condition */
static psrNode_t* AR_STDCALL handle_for_opt_search_cond(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*for_statement	:	FOR query_exp DO statement */
/*for_statement	:	FOR ( for_init_statement_list ; for_opt_search_cond ; for_inc_statement_list ) statement */
/*for_statement	:	FOREACH ( data_type_ref identifier IN_L scalar_exp ) DO statement */
static psrNode_t* AR_STDCALL handle_for_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*trigger_def	:	CREATE TRIGGER identifier action_time event ON q_table_name opt_order opt_old_ref trig_action */
static psrNode_t* AR_STDCALL handle_trigger_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_order	:	 */
/*opt_order	:	ORDER INTNUM */
static psrNode_t* AR_STDCALL handle_opt_order(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*trig_action	:	compound_statement */
static psrNode_t* AR_STDCALL handle_trig_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*action_time	:	BEFORE */
/*action_time	:	AFTER */
/*action_time	:	INSTEAD OF */
static psrNode_t* AR_STDCALL handle_action_time(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*event	:	INSERT */
/*event	:	UPDATE opt_column_commalist */
/*event	:	DELETE_L */
static psrNode_t* AR_STDCALL handle_event(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_old_ref	:	 */
/*opt_old_ref	:	REFERENCING old_commalist */
static psrNode_t* AR_STDCALL handle_opt_old_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*old_commalist	:	old_alias */
/*old_commalist	:	old_commalist , old_alias */
static psrNode_t* AR_STDCALL handle_old_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*old_alias	:	OLD AS identifier */
/*old_alias	:	NEW AS identifier */
static psrNode_t* AR_STDCALL handle_old_alias(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_trigger	:	DROP TRIGGER q_table_name */
static psrNode_t* AR_STDCALL handle_drop_trigger(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_proc	:	DROP AGGREGATE q_table_name */
/*drop_proc	:	DROP routine_head q_table_name */
/*drop_proc	:	DROP MODULE q_table_name */
static psrNode_t* AR_STDCALL handle_drop_proc(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_element	:	 */
/*opt_element	:	AS identifier */
static psrNode_t* AR_STDCALL handle_opt_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xml_col	:	column_ref */
/*xml_col	:	scalar_exp AS identifier */
/*xml_col	:	scalar_exp IN_L identifier */
static psrNode_t* AR_STDCALL handle_xml_col(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xml_col_list	:	xml_col */
/*xml_col_list	:	xml_col_list , xml_col */
static psrNode_t* AR_STDCALL handle_xml_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_xml_col_list	:	( xml_col_list ) */
static psrNode_t* AR_STDCALL handle_opt_xml_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_pk	:	 */
/*opt_pk	:	PRIMARY KEY ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_pk(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_join	:	 */
/*opt_join	:	ON ( search_condition ) */
static psrNode_t* AR_STDCALL handle_opt_join(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_elt	:	 */
/*opt_elt	:	NAME */
static psrNode_t* AR_STDCALL handle_opt_elt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xml_join_elt	:	q_table_name identifier opt_element opt_xml_col_list opt_join opt_pk opt_elt opt_xml_child */
static psrNode_t* AR_STDCALL handle_xml_join_elt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_xml_child	:	 */
/*opt_xml_child	:	BEGINX xml_join_list ENDX */
static psrNode_t* AR_STDCALL handle_opt_xml_child(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*top_xml_child	:	query_spec */
/*top_xml_child	:	BEGINX xml_join_list ENDX */
static psrNode_t* AR_STDCALL handle_top_xml_child(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xml_join_list	:	xml_join_elt */
/*xml_join_list	:	xml_join_list , xml_join_elt */
static psrNode_t* AR_STDCALL handle_xml_join_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_persist	:	 */
/*opt_persist	:	PERSISTENT */
static psrNode_t* AR_STDCALL handle_opt_persist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_interval	:	 */
/*opt_interval	:	INTERVAL INTNUM */
static psrNode_t* AR_STDCALL handle_opt_interval(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_metas	:	 */
/*opt_metas	:	DTD INTERNAL */
/*opt_metas	:	DTD EXTERNAL */
/*opt_metas	:	DTD STRING */
/*opt_metas	:	SCHEMA EXTERNAL */
/*opt_metas	:	SCHEMA STRING */
static psrNode_t* AR_STDCALL handle_opt_metas(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_publish	:	 */
/*opt_publish	:	PUBLIC STRING identifier STRING opt_persist opt_interval opt_metas */
static psrNode_t* AR_STDCALL handle_opt_publish(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xmlview_param_value	:	NAME */
/*xmlview_param_value	:	STRING */
static psrNode_t* AR_STDCALL handle_xmlview_param_value(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xmlview_param	:	NAME COMPARISON xmlview_param_value */
static psrNode_t* AR_STDCALL handle_xmlview_param(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xmlview_params	:	xmlview_param */
/*xmlview_params	:	xmlview_params xmlview_param */
static psrNode_t* AR_STDCALL handle_xmlview_params(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_xmlview_params	:	 */
/*opt_xmlview_params	:	[ xmlview_params ] */
static psrNode_t* AR_STDCALL handle_opt_xmlview_params(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*xml_view	:	CREATE XML VIEW new_table_name AS opt_xmlview_params top_xml_child opt_elt opt_publish */
static psrNode_t* AR_STDCALL handle_xml_view(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_xml_view	:	DROP XML VIEW q_table_name */
static psrNode_t* AR_STDCALL handle_drop_xml_view(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*string_concatenation_operator	:	scalar_exp STRING_CONCAT_OPERATOR scalar_exp */
static psrNode_t* AR_STDCALL handle_string_concatenation_operator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*q_type_name	:	identifier */
/*q_type_name	:	identifier . identifier */
/*q_type_name	:	identifier . identifier . identifier */
/*q_type_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_q_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*q_old_type_name	:	identifier */
/*q_old_type_name	:	identifier . identifier */
/*q_old_type_name	:	identifier . identifier . identifier */
/*q_old_type_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_q_old_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*new_type_name	:	identifier */
/*new_type_name	:	identifier . identifier */
/*new_type_name	:	identifier . identifier . identifier */
/*new_type_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_new_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*empty6	:	 */
static psrNode_t* AR_STDCALL handle_empty6(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*user_defined_type	:	CREATE TYPE new_type_name opt_subtype_clause opt_external_and_language_clause empty6 opt_as_type_representation opt_type_option_list opt_method_specification_list */
static psrNode_t* AR_STDCALL handle_user_defined_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*user_defined_type_drop	:	DROP TYPE q_old_type_name opt_drop_behavior */
static psrNode_t* AR_STDCALL handle_user_defined_type_drop(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_external_and_language_clause	:	 */
/*opt_external_and_language_clause	:	LANGUAGE language_name EXTERNAL NAME_L STRING */
/*opt_external_and_language_clause	:	EXTERNAL NAME_L STRING LANGUAGE language_name */
/*opt_external_and_language_clause	:	LANGUAGE language_name */
static psrNode_t* AR_STDCALL handle_opt_external_and_language_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_subtype_clause	:	 */
/*opt_subtype_clause	:	UNDER q_type_name */
static psrNode_t* AR_STDCALL handle_opt_subtype_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_as_type_representation	:	 */
/*opt_as_type_representation	:	AS type_representation */
static psrNode_t* AR_STDCALL handle_opt_as_type_representation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_representation	:	( type_member_list ) */
static psrNode_t* AR_STDCALL handle_type_representation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_member_list	:	type_member */
/*type_member_list	:	type_member_list , type_member */
static psrNode_t* AR_STDCALL handle_type_member_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_external_clause	:	 */
/*opt_external_clause	:	EXTERNAL NAME_L STRING */
/*opt_external_clause	:	EXTERNAL NAME_L STRING EXTERNAL TYPE STRING */
/*opt_external_clause	:	EXTERNAL TYPE STRING */
static psrNode_t* AR_STDCALL handle_opt_external_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_soap_clause	:	 */
/*opt_soap_clause	:	__SOAP_NAME STRING */
/*opt_soap_clause	:	__SOAP_TYPE STRING */
/*opt_soap_clause	:	__SOAP_TYPE STRING __SOAP_NAME STRING */
/*opt_soap_clause	:	__SOAP_NAME STRING __SOAP_TYPE STRING */
static psrNode_t* AR_STDCALL handle_opt_soap_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_external_type	:	 */
/*opt_external_type	:	EXTERNAL TYPE STRING */
static psrNode_t* AR_STDCALL handle_opt_external_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_member	:	identifier data_type_ref opt_reference_scope_check opt_default_clause opt_collate_exp opt_external_clause opt_soap_clause */
static psrNode_t* AR_STDCALL handle_type_member(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_reference_scope_check	:	 */
/*opt_reference_scope_check	:	REFERENCES ARE CHECKED opt_on_delete_referential_rule */
/*opt_reference_scope_check	:	REFERENCES ARE NOT CHECKED */
static psrNode_t* AR_STDCALL handle_opt_reference_scope_check(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_default_clause	:	 */
/*opt_default_clause	:	DEFAULT signed_literal */
static psrNode_t* AR_STDCALL handle_opt_default_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_type_option_list	:	 */
/*opt_type_option_list	:	type_option_list */
static psrNode_t* AR_STDCALL handle_opt_type_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_option_list	:	type_option */
/*type_option_list	:	type_option_list type_option */
static psrNode_t* AR_STDCALL handle_type_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*type_option	:	FINAL_L */
/*type_option	:	NOT FINAL_L */
/*type_option	:	REF USING data_type_ref */
/*type_option	:	REF FROM ( column_commalist ) */
/*type_option	:	REF IS SYSTEM GENERATED */
/*type_option	:	CAST ( SOURCE AS REF ) WITH identifier */
/*type_option	:	CAST ( REF AS SOURCE ) WITH identifier */
/*type_option	:	SELF_L AS REF */
/*type_option	:	TEMPORARY */
/*type_option	:	UNRESTRICTED */
/*type_option	:	__SOAP_TYPE STRING */
static psrNode_t* AR_STDCALL handle_type_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_method_specification_list	:	 */
/*opt_method_specification_list	:	method_specification_list */
static psrNode_t* AR_STDCALL handle_opt_method_specification_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_specification_list	:	method_specification */
/*method_specification_list	:	method_specification_list , method_specification */
static psrNode_t* AR_STDCALL handle_method_specification_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_type	:	 */
/*method_type	:	STATIC_L */
/*method_type	:	INSTANCE_L */
static psrNode_t* AR_STDCALL handle_method_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*decl_parameter_list	:	( ) */
/*decl_parameter_list	:	( decl_parameter_commalist ) */
static psrNode_t* AR_STDCALL handle_decl_parameter_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*decl_parameter_commalist	:	decl_parameter */
/*decl_parameter_commalist	:	decl_parameter_commalist , decl_parameter */
static psrNode_t* AR_STDCALL handle_decl_parameter_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*decl_parameter	:	opt_parameter_mode column_ref data_type_ref opt_external_type */
static psrNode_t* AR_STDCALL handle_decl_parameter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*partial_method_specification	:	method_type METHOD method_identifier decl_parameter_list RETURNS data_type_ref opt_specific_method_name */
/*partial_method_specification	:	CONSTRUCTOR METHOD method_identifier decl_parameter_list opt_specific_method_name */
static psrNode_t* AR_STDCALL handle_partial_method_specification(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_specification	:	partial_method_specification opt_self_result opt_method_characteristics */
/*method_specification	:	OVERRIDING partial_method_specification */
static psrNode_t* AR_STDCALL handle_method_specification(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_self_result	:	 */
/*opt_self_result	:	SELF_L AS RESULT */
/*opt_self_result	:	SELF_L AS LOCATOR */
/*opt_self_result	:	SELF_L AS RESULT SELF_L AS LOCATOR */
static psrNode_t* AR_STDCALL handle_opt_self_result(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_specific_method_name	:	 */
/*opt_specific_method_name	:	SPECIFIC new_table_name */
static psrNode_t* AR_STDCALL handle_opt_specific_method_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_method_characteristics	:	 */
/*opt_method_characteristics	:	method_characteristics */
static psrNode_t* AR_STDCALL handle_opt_method_characteristics(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_characteristics	:	method_characteristic */
/*method_characteristics	:	method_characteristics method_characteristic */
static psrNode_t* AR_STDCALL handle_method_characteristics(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_characteristic	:	LANGUAGE language_name */
/*method_characteristic	:	PARAMETER STYLE SQL_L */
/*method_characteristic	:	PARAMETER STYLE GENERAL */
/*method_characteristic	:	DETERMINISTIC */
/*method_characteristic	:	NOT DETERMINISTIC */
/*method_characteristic	:	NO SQL_L */
/*method_characteristic	:	CONTAINS SQL_L */
/*method_characteristic	:	READS SQL_L DATA */
/*method_characteristic	:	MODIFIES SQL_L DATA */
/*method_characteristic	:	RETURNS NULLX ON NULLX INPUT */
/*method_characteristic	:	CALLED ON NULLX INPUT */
/*method_characteristic	:	EXTERNAL NAME_L STRING */
/*method_characteristic	:	EXTERNAL VARIABLE NAME_L STRING */
/*method_characteristic	:	EXTERNAL TYPE STRING */
static psrNode_t* AR_STDCALL handle_method_characteristic(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*external_language_name	:	ADA */
/*external_language_name	:	C */
/*external_language_name	:	COBOL */
/*external_language_name	:	FORTRAN */
/*external_language_name	:	MUMPS */
/*external_language_name	:	PASCAL_L */
/*external_language_name	:	PLI */
/*external_language_name	:	JAVA */
/*external_language_name	:	CLR */
static psrNode_t* AR_STDCALL handle_external_language_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*language_name	:	external_language_name */
/*language_name	:	SQL_L */
static psrNode_t* AR_STDCALL handle_language_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_constructor_return	:	 */
/*opt_constructor_return	:	RETURNS new_type_name */
static psrNode_t* AR_STDCALL handle_opt_constructor_return(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_declaration	:	CREATE method_type METHOD method_identifier rout_parameter_list opt_return rout_alt_type FOR q_type_name compound_statement */
/*method_declaration	:	CREATE CONSTRUCTOR METHOD q_table_name rout_parameter_list opt_constructor_return FOR q_type_name compound_statement */
static psrNode_t* AR_STDCALL handle_method_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*static_method_invocation	:	q_type_name DOUBLE_COLON method_identifier ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_static_method_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*identifier_chain	:	identifier . identifier . identifier . method_identifier */
/*identifier_chain	:	identifier . . identifier . method_identifier */
/*identifier_chain	:	identifier . identifier_chain */
static psrNode_t* AR_STDCALL handle_identifier_chain(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*identifier_chain_method	:	identifier . identifier . identifier . identifier . method_identifier */
/*identifier_chain_method	:	identifier . . identifier . identifier . method_identifier */
/*identifier_chain_method	:	identifier . identifier_chain_method */
static psrNode_t* AR_STDCALL handle_identifier_chain_method(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_invocation	:	scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ( opt_arg_commalist ) */
/*method_invocation	:	identifier_chain_method ( opt_arg_commalist ) */
/*method_invocation	:	( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
/*method_invocation	:	( column_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_method_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*top_level_method_invocation	:	METHOD CALL scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ( opt_arg_commalist ) */
/*top_level_method_invocation	:	METHOD CALL identifier_chain_method ( opt_arg_commalist ) */
/*top_level_method_invocation	:	METHOD CALL ( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
/*top_level_method_invocation	:	METHOD CALL ( column_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_top_level_method_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*member_observer	:	member_observer_no_id_chain */
/*member_observer	:	identifier . identifier_chain */
static psrNode_t* AR_STDCALL handle_member_observer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*member_observer_no_id_chain	:	scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier */
/*member_observer_no_id_chain	:	( scalar_exp_no_col_ref AS q_type_name ) . method_identifier */
/*member_observer_no_id_chain	:	( column_ref AS q_type_name ) . method_identifier */
static psrNode_t* AR_STDCALL handle_member_observer_no_id_chain(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*method_identifier	:	identifier */
/*method_identifier	:	EXTRACT */
static psrNode_t* AR_STDCALL handle_method_identifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*new_invocation	:	NEW q_type_name ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_new_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*user_defined_type_alter	:	ALTER TYPE q_type_name alter_type_action */
static psrNode_t* AR_STDCALL handle_user_defined_type_alter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*alter_type_action	:	ADD ATTRIBUTE type_member */
/*alter_type_action	:	DROP ATTRIBUTE identifier opt_drop_behavior */
/*alter_type_action	:	ADD method_specification */
/*alter_type_action	:	DROP partial_method_specification opt_drop_behavior */
static psrNode_t* AR_STDCALL handle_alter_type_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_permission_set	:	 */
/*opt_with_permission_set	:	WITH PERMISSION_SET COMPARISON SAFE_L */
/*opt_with_permission_set	:	WITH PERMISSION_SET COMPARISON UNRESTRICTED */
static psrNode_t* AR_STDCALL handle_opt_with_permission_set(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*opt_with_autoregister	:	 */
/*opt_with_autoregister	:	WITH AUTOREGISTER_L */
static psrNode_t* AR_STDCALL handle_opt_with_autoregister(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_library	:	CREATE LIBRARY_L q_table_name AS scalar_exp opt_with_permission_set opt_with_autoregister */
static psrNode_t* AR_STDCALL handle_create_library(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*create_assembly	:	CREATE ASSEMBLY_L q_table_name FROM scalar_exp opt_with_permission_set opt_with_autoregister */
static psrNode_t* AR_STDCALL handle_create_assembly(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_library	:	DROP LIBRARY_L q_table_name */
static psrNode_t* AR_STDCALL handle_drop_library(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);

/*drop_assembly	:	DROP ASSEMBLY_L q_table_name */
static psrNode_t* AR_STDCALL handle_drop_assembly(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx);




static struct { const wchar_t	*rule; const wchar_t	*prec_token; psrRuleFunc_t	handler; size_t	auto_ret; } __g_sql_rule_pattern[] = {
{L"sql_list  :  sql_list1 ; ", NULL, handle_sql_list, 0},
{L"sql_list  :  sql_list1 ", NULL, handle_sql_list, 0},
{L"sql_list1  :  sql ", NULL, handle_sql_list1, 0},
{L"sql  :  schema_element_list ", NULL, handle_sql, 0},
{L"sql  :  view_def ", NULL, handle_sql, 0},
{L"sql  :  xml_view ", NULL, handle_sql, 0},
{L"sql  :  create_xml_schema ", NULL, handle_sql, 0},
{L"sql  :  alter_constraint ", NULL, handle_sql, 0},
{L"sql  :  create_library ", NULL, handle_sql, 0},
{L"sql  :  create_assembly ", NULL, handle_sql, 0},
{L"sql  :  drop_library ", NULL, handle_sql, 0},
{L"sql  :  drop_assembly ", NULL, handle_sql, 0},
{L"schema_element_list  :  schema_element ", NULL, handle_schema_element_list, 0},
{L"schema_element_list  :  add_column ", NULL, handle_schema_element_list, 0},
{L"schema_element_list  :  schema_element_list schema_element ", NULL, handle_schema_element_list, 0},
{L"schema_element_list  :  schema_element_list add_column ", NULL, handle_schema_element_list, 0},
{L"schema_element  :  base_table_def ", NULL, handle_schema_element, 0},
{L"schema_element  :  create_index_def ", NULL, handle_schema_element, 0},
{L"schema_element  :  drop_table ", NULL, handle_schema_element, 0},
{L"schema_element  :  drop_index ", NULL, handle_schema_element, 0},
{L"schema_element  :  table_rename ", NULL, handle_schema_element, 0},
{L"schema_element  :  privilege_def ", NULL, handle_schema_element, 0},
{L"schema_element  :  privilege_revoke ", NULL, handle_schema_element, 0},
{L"schema_element  :  create_user_statement ", NULL, handle_schema_element, 0},
{L"schema_element  :  delete_user_statement ", NULL, handle_schema_element, 0},
{L"schema_element  :  set_pass ", NULL, handle_schema_element, 0},
{L"schema_element  :  set_group_stmt ", NULL, handle_schema_element, 0},
{L"schema_element  :  add_group_stmt ", NULL, handle_schema_element, 0},
{L"schema_element  :  delete_group_stmt ", NULL, handle_schema_element, 0},
{L"schema_element  :  user_defined_type ", NULL, handle_schema_element, 0},
{L"schema_element  :  user_defined_type_drop ", NULL, handle_schema_element, 0},
{L"schema_element  :  user_defined_type_alter ", NULL, handle_schema_element, 0},
{L"identifier  :  NAME ", NULL, handle_identifier, 0},
{L"identifier  :  TYPE ", NULL, handle_identifier, 0},
{L"identifier  :  FINAL_L ", NULL, handle_identifier, 0},
{L"identifier  :  METHOD ", NULL, handle_identifier, 0},
{L"identifier  :  CHECKED ", NULL, handle_identifier, 0},
{L"identifier  :  SYSTEM ", NULL, handle_identifier, 0},
{L"identifier  :  GENERATED ", NULL, handle_identifier, 0},
{L"identifier  :  SOURCE ", NULL, handle_identifier, 0},
{L"identifier  :  RESULT ", NULL, handle_identifier, 0},
{L"identifier  :  LOCATOR ", NULL, handle_identifier, 0},
{L"identifier  :  INSTANCE_L ", NULL, handle_identifier, 0},
{L"identifier  :  CONSTRUCTOR ", NULL, handle_identifier, 0},
{L"identifier  :  SELF_L ", NULL, handle_identifier, 0},
{L"identifier  :  OVERRIDING ", NULL, handle_identifier, 0},
{L"identifier  :  STYLE ", NULL, handle_identifier, 0},
{L"identifier  :  SQL_L ", NULL, handle_identifier, 0},
{L"identifier  :  GENERAL ", NULL, handle_identifier, 0},
{L"identifier  :  DETERMINISTIC ", NULL, handle_identifier, 0},
{L"identifier  :  NO ", NULL, handle_identifier, 0},
{L"identifier  :  CONTAINS ", NULL, handle_identifier, 0},
{L"identifier  :  READS ", NULL, handle_identifier, 0},
{L"identifier  :  DATA ", NULL, handle_identifier, 0},
{L"identifier  :  MODIFIES ", NULL, handle_identifier, 0},
{L"identifier  :  INPUT ", NULL, handle_identifier, 0},
{L"identifier  :  CALLED ", NULL, handle_identifier, 0},
{L"identifier  :  ADA ", NULL, handle_identifier, 0},
{L"identifier  :  C ", NULL, handle_identifier, 0},
{L"identifier  :  COBOL ", NULL, handle_identifier, 0},
{L"identifier  :  FORTRAN ", NULL, handle_identifier, 0},
{L"identifier  :  MUMPS ", NULL, handle_identifier, 0},
{L"identifier  :  PASCAL_L ", NULL, handle_identifier, 0},
{L"identifier  :  PLI ", NULL, handle_identifier, 0},
{L"identifier  :  NAME_L ", NULL, handle_identifier, 0},
{L"identifier  :  TEXT_L ", NULL, handle_identifier, 0},
{L"identifier  :  JAVA ", NULL, handle_identifier, 0},
{L"identifier  :  INOUT_L ", NULL, handle_identifier, 0},
{L"identifier  :  REMOTE ", NULL, handle_identifier, 0},
{L"identifier  :  KEYSET ", NULL, handle_identifier, 0},
{L"identifier  :  VALUE ", NULL, handle_identifier, 0},
{L"identifier  :  PARAMETER ", NULL, handle_identifier, 0},
{L"identifier  :  VARIABLE ", NULL, handle_identifier, 0},
{L"identifier  :  CLR ", NULL, handle_identifier, 0},
{L"identifier  :  TEMPORARY ", NULL, handle_identifier, 0},
{L"identifier  :  ADMIN_L ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_DOC ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_DOCW ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_HEADER ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_HTTP ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_NAME ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_TYPE ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_XML_TYPE ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_FAULT ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_DIME_ENC ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_ENC_MIME ", NULL, handle_identifier, 0},
{L"identifier  :  __SOAP_OPTIONS ", NULL, handle_identifier, 0},
{L"identifier  :  START_L ", NULL, handle_identifier, 0},
{L"identifier  :  ATTRIBUTE ", NULL, handle_identifier, 0},
{L"identifier  :  REXECUTE ", NULL, handle_identifier, 0},
{L"identifier  :  PERMISSION_SET ", NULL, handle_identifier, 0},
{L"identifier  :  AUTOREGISTER_L ", NULL, handle_identifier, 0},
{L"identifier  :  LIBRARY_L ", NULL, handle_identifier, 0},
{L"identifier  :  ASSEMBLY_L ", NULL, handle_identifier, 0},
{L"identifier  :  SAFE_L ", NULL, handle_identifier, 0},
{L"identifier  :  UNRESTRICTED ", NULL, handle_identifier, 0},
{L"identifier  :  INCREMENT_L ", NULL, handle_identifier, 0},
{L"identifier  :  FOREACH ", NULL, handle_identifier, 0},
{L"base_table_def  :  CREATE TABLE new_table_name ( base_table_element_commalist ) ", NULL, handle_base_table_def, 0},
{L"base_table_element_commalist  :  base_table_element ", NULL, handle_base_table_element_commalist, 0},
{L"base_table_element_commalist  :  base_table_element_commalist , base_table_element ", NULL, handle_base_table_element_commalist, 0},
{L"base_table_element  :  column_def ", NULL, handle_base_table_element, 0},
{L"base_table_element  :  table_constraint_def ", NULL, handle_base_table_element, 0},
{L"column_def  :  column column_data_type column_def_opt_list ", NULL, handle_column_def, 0},
{L"opt_referential_triggered_action  :   ", NULL, handle_opt_referential_triggered_action, 0},
{L"opt_referential_triggered_action  :  referential_rule ", NULL, handle_opt_referential_triggered_action, 0},
{L"opt_referential_triggered_action  :  referential_rule referential_rule ", NULL, handle_opt_referential_triggered_action, 0},
{L"referential_rule  :  ON UPDATE referential_action ", NULL, handle_referential_rule, 0},
{L"referential_rule  :  delete_referential_rule ", NULL, handle_referential_rule, 0},
{L"delete_referential_rule  :  ON DELETE_L referential_action ", NULL, handle_delete_referential_rule, 0},
{L"opt_on_delete_referential_rule  :   ", NULL, handle_opt_on_delete_referential_rule, 0},
{L"opt_on_delete_referential_rule  :  delete_referential_rule ", NULL, handle_opt_on_delete_referential_rule, 0},
{L"referential_action  :  CASCADE ", NULL, handle_referential_action, 0},
{L"referential_action  :  SET NULLX ", NULL, handle_referential_action, 0},
{L"referential_action  :  SET DEFAULT ", NULL, handle_referential_action, 0},
{L"references  :  REFERENCES q_table_name opt_column_commalist opt_referential_triggered_action ", NULL, handle_references, 0},
{L"column_def_opt_list  :   ", NULL, handle_column_def_opt_list, 0},
{L"column_def_opt_list  :  column_def_opt_list column_def_opt ", NULL, handle_column_def_opt_list, 0},
{L"identity_opt  :  START_L WITH signed_literal ", NULL, handle_identity_opt, 0},
{L"identity_opt  :  INCREMENT_L BY INTNUM ", NULL, handle_identity_opt, 0},
{L"identity_opt_list  :  identity_opt ", NULL, handle_identity_opt_list, 0},
{L"identity_opt_list  :  identity_opt_list , identity_opt ", NULL, handle_identity_opt_list, 0},
{L"column_def_opt  :  NOT NULLX ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  NULLX ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  IDENTITY ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  IDENTITY ( identity_opt_list ) ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  PRIMARY KEY ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  DEFAULT signed_literal ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  COLLATE q_table_name ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  references ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  IDENTIFIED BY column ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  CHECK ( search_condition ) ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  WITH SCHEMA column_xml_schema_def ", NULL, handle_column_def_opt, 0},
{L"column_def_opt  :  UNIQUE ", NULL, handle_column_def_opt, 0},
{L"column_xml_schema_def  :  ( STRING , STRING ) ", NULL, handle_column_xml_schema_def, 0},
{L"column_xml_schema_def  :  ( STRING , STRING , STRING ) ", NULL, handle_column_xml_schema_def, 0},
{L"table_constraint_def  :  UNDER q_table_name ", NULL, handle_table_constraint_def, 0},
{L"table_constraint_def  :  opt_constraint_name PRIMARY KEY ( index_column_commalist ) opt_index_option_list ", NULL, handle_table_constraint_def, 0},
{L"table_constraint_def  :  opt_constraint_name FOREIGN KEY ( column_commalist ) references ", NULL, handle_table_constraint_def, 0},
{L"table_constraint_def  :  opt_constraint_name CHECK ( search_condition ) ", NULL, handle_table_constraint_def, 0},
{L"table_constraint_def  :  opt_constraint_name UNIQUE ( column_commalist ) ", NULL, handle_table_constraint_def, 0},
{L"opt_constraint_name  :   ", NULL, handle_opt_constraint_name, 0},
{L"opt_constraint_name  :  CONSTRAINT identifier ", NULL, handle_opt_constraint_name, 0},
{L"column_commalist  :  column ", NULL, handle_column_commalist, 0},
{L"column_commalist  :  column_commalist , column ", NULL, handle_column_commalist, 0},
{L"index_column_commalist  :  column opt_asc_desc ", NULL, handle_index_column_commalist, 0},
{L"index_column_commalist  :  index_column_commalist , column opt_asc_desc ", NULL, handle_index_column_commalist, 0},
{L"index_option  :  CLUSTERED ", NULL, handle_index_option, 0},
{L"index_option  :  UNIQUE ", NULL, handle_index_option, 0},
{L"index_option  :  OBJECT_ID ", NULL, handle_index_option, 0},
{L"index_option_list  :  index_option ", NULL, handle_index_option_list, 0},
{L"index_option_list  :  index_option_list index_option ", NULL, handle_index_option_list, 0},
{L"opt_index_option_list  :   ", NULL, handle_opt_index_option_list, 0},
{L"opt_index_option_list  :  index_option_list ", NULL, handle_opt_index_option_list, 0},
{L"create_index_def  :  CREATE opt_index_option_list INDEX index ON new_table_name ( index_column_commalist ) ", NULL, handle_create_index_def, 0},
{L"drop_index  :  DROP INDEX identifier opt_table ", NULL, handle_drop_index, 0},
{L"opt_table  :   ", NULL, handle_opt_table, 0},
{L"opt_table  :  q_table_name ", NULL, handle_opt_table, 0},
{L"drop_table  :  DROP TABLE q_table_name ", NULL, handle_drop_table, 0},
{L"drop_table  :  DROP VIEW q_table_name ", NULL, handle_drop_table, 0},
{L"opt_col_add_column  :   ", NULL, handle_opt_col_add_column, 0},
{L"opt_col_add_column  :  COLUMN ", NULL, handle_opt_col_add_column, 0},
{L"add_col_column_def_list  :  column_def ", NULL, handle_add_col_column_def_list, 0},
{L"add_col_column_def_list  :  add_col_column_def_list , column_def ", NULL, handle_add_col_column_def_list, 0},
{L"add_col_column_list  :  column ", NULL, handle_add_col_column_list, 0},
{L"add_col_column_list  :  add_col_column_list , column ", NULL, handle_add_col_column_list, 0},
{L"add_column  :  ALTER TABLE q_table_name ADD opt_col_add_column add_col_column_def_list ", NULL, handle_add_column, 0},
{L"add_column  :  ALTER TABLE q_table_name DROP opt_col_add_column add_col_column_list ", NULL, handle_add_column, 0},
{L"add_column  :  ALTER TABLE q_table_name MODIFY opt_col_add_column column_def ", NULL, handle_add_column, 0},
{L"table_rename  :  ALTER TABLE q_table_name RENAME new_table_name ", NULL, handle_table_rename, 0},
{L"constraint_op  :  ADD ", NULL, handle_constraint_op, 0},
{L"constraint_op  :  DROP ", NULL, handle_constraint_op, 0},
{L"constraint_op  :  MODIFY ", NULL, handle_constraint_op, 0},
{L"opt_drop_behavior  :   ", NULL, handle_opt_drop_behavior, 0},
{L"opt_drop_behavior  :  CASCADE ", NULL, handle_opt_drop_behavior, 0},
{L"opt_drop_behavior  :  RESTRICT ", NULL, handle_opt_drop_behavior, 0},
{L"opt_table_constraint_def  :  CONSTRAINT identifier opt_drop_behavior ", NULL, handle_opt_table_constraint_def, 0},
{L"opt_table_constraint_def  :  table_constraint_def ", NULL, handle_opt_table_constraint_def, 0},
{L"alter_constraint  :  ALTER TABLE q_table_name constraint_op opt_table_constraint_def ", NULL, handle_alter_constraint, 0},
{L"create_xml_schema  :  CREATE XML SCHEMA STRING ", NULL, handle_create_xml_schema, 0},
{L"view_query_spec  :  query_exp ", NULL, handle_view_query_spec, 0},
{L"view_query_spec  :  query_no_from_spec ", NULL, handle_view_query_spec, 0},
{L"empty_1  :   ", NULL, handle_empty_1, 0},
{L"view_def  :  CREATE VIEW new_table_name empty_1 opt_column_commalist AS view_query_spec opt_with_check_option ", NULL, handle_view_def, 0},
{L"view_def  :  CREATE PROCEDURE VIEW new_table_name AS q_table_name ( column_commalist_or_empty ) ( proc_col_list ) ", NULL, handle_view_def, 0},
{L"opt_with_check_option  :   ", NULL, handle_opt_with_check_option, 0},
{L"opt_with_check_option  :  WITH CHECK OPTION ", NULL, handle_opt_with_check_option, 0},
{L"opt_column_commalist  :   ", NULL, handle_opt_column_commalist, 0},
{L"opt_column_commalist  :  ( column_commalist ) ", NULL, handle_opt_column_commalist, 0},
{L"priv_opt_column_commalist  :   ", NULL, handle_priv_opt_column_commalist, 0},
{L"priv_opt_column_commalist  :  ( column_commalist ) ", NULL, handle_priv_opt_column_commalist, 0},
{L"privilege_def  :  GRANT ALL PRIVILEGES TO grantee ", NULL, handle_privilege_def, 0},
{L"privilege_def  :  GRANT privileges ON table TO grantee_commalist opt_with_grant_option ", NULL, handle_privilege_def, 0},
{L"privilege_def  :  GRANT EXECUTE ON function_name TO grantee_commalist opt_with_grant_option ", NULL, handle_privilege_def, 0},
{L"privilege_def  :  GRANT REXECUTE ON STRING TO grantee_commalist ", NULL, handle_privilege_def, 0},
{L"privilege_def  :  GRANT UNDER ON q_old_type_name TO grantee_commalist opt_with_grant_option ", NULL, handle_privilege_def, 0},
{L"privilege_def  :  GRANT grantee_commalist TO grantee_commalist opt_with_admin_option ", NULL, handle_privilege_def, 0},
{L"opt_with_admin_option  :   ", NULL, handle_opt_with_admin_option, 0},
{L"opt_with_admin_option  :  WITH ADMIN_L OPTION ", NULL, handle_opt_with_admin_option, 0},
{L"privilege_revoke  :  REVOKE privileges ON table FROM grantee_commalist ", NULL, handle_privilege_revoke, 0},
{L"privilege_revoke  :  REVOKE EXECUTE ON function_name FROM grantee_commalist ", NULL, handle_privilege_revoke, 0},
{L"privilege_revoke  :  REVOKE UNDER ON q_old_type_name FROM grantee_commalist ", NULL, handle_privilege_revoke, 0},
{L"privilege_revoke  :  REVOKE REXECUTE ON STRING FROM grantee_commalist ", NULL, handle_privilege_revoke, 0},
{L"privilege_revoke  :  REVOKE grantee_commalist FROM grantee_commalist ", NULL, handle_privilege_revoke, 0},
{L"opt_with_grant_option  :   ", NULL, handle_opt_with_grant_option, 0},
{L"opt_with_grant_option  :  WITH GRANT OPTION ", NULL, handle_opt_with_grant_option, 0},
{L"privileges  :  ALL PRIVILEGES ", NULL, handle_privileges, 0},
{L"privileges  :  ALL ", NULL, handle_privileges, 0},
{L"privileges  :  operation_commalist ", NULL, handle_privileges, 0},
{L"operation_commalist  :  operation ", NULL, handle_operation_commalist, 0},
{L"operation_commalist  :  operation_commalist , operation ", NULL, handle_operation_commalist, 0},
{L"operation  :  SELECT priv_opt_column_commalist ", NULL, handle_operation, 0},
{L"operation  :  INSERT ", NULL, handle_operation, 0},
{L"operation  :  DELETE_L ", NULL, handle_operation, 0},
{L"operation  :  UPDATE priv_opt_column_commalist ", NULL, handle_operation, 0},
{L"operation  :  REFERENCES priv_opt_column_commalist ", NULL, handle_operation, 0},
{L"grantee_commalist  :  grantee ", NULL, handle_grantee_commalist, 0},
{L"grantee_commalist  :  grantee_commalist , grantee ", NULL, handle_grantee_commalist, 0},
{L"grantee  :  PUBLIC ", NULL, handle_grantee, 0},
{L"grantee  :  user ", NULL, handle_grantee, 0},
{L"set_pass  :  SET PASSWORD identifier identifier ", NULL, handle_set_pass, 0},
{L"create_user_statement  :  CREATE USER user ", NULL, handle_create_user_statement, 0},
{L"create_user_statement  :  CREATE ROLE_L user ", NULL, handle_create_user_statement, 0},
{L"delete_user_statement  :  DELETE_L USER user ", NULL, handle_delete_user_statement, 0},
{L"delete_user_statement  :  DELETE_L USER user CASCADE ", NULL, handle_delete_user_statement, 0},
{L"delete_user_statement  :  DROP USER user ", NULL, handle_delete_user_statement, 0},
{L"delete_user_statement  :  DROP USER user CASCADE ", NULL, handle_delete_user_statement, 0},
{L"delete_user_statement  :  DROP ROLE_L user ", NULL, handle_delete_user_statement, 0},
{L"set_group_stmt  :  SET USER GROUP user user ", NULL, handle_set_group_stmt, 0},
{L"add_group_stmt  :  ADD USER GROUP user user ", NULL, handle_add_group_stmt, 0},
{L"delete_group_stmt  :  DELETE_L USER GROUP user user ", NULL, handle_delete_group_stmt, 0},
{L"opt_attach_primary_key  :   ", NULL, handle_opt_attach_primary_key, 0},
{L"opt_attach_primary_key  :  PRIMARY KEY ( column_commalist ) ", NULL, handle_opt_attach_primary_key, 0},
{L"attach_table  :  ATTACH TABLE attach_q_table_name opt_attach_primary_key opt_as FROM literal opt_login opt_not_select opt_remote_name ", NULL, handle_attach_table, 0},
{L"opt_as  :   ", NULL, handle_opt_as, 0},
{L"opt_as  :  AS new_table_name ", NULL, handle_opt_as, 0},
{L"opt_login  :   ", NULL, handle_opt_login, 0},
{L"opt_login  :  USER scalar_exp PASSWORD scalar_exp ", NULL, handle_opt_login, 0},
{L"opt_not_select  :   ", NULL, handle_opt_not_select, 0},
{L"opt_not_select  :  NOT SELECT ", NULL, handle_opt_not_select, 0},
{L"opt_remote_name  :   ", NULL, handle_opt_remote_name, 0},
{L"opt_remote_name  :  REMOTE AS scalar_exp ", NULL, handle_opt_remote_name, 0},
{L"cursor_type  :  STATIC_L ", NULL, handle_cursor_type, 0},
{L"cursor_type  :  DYNAMIC ", NULL, handle_cursor_type, 0},
{L"cursor_type  :  KEYSET ", NULL, handle_cursor_type, 0},
{L"cursor_def  :  DECLARE identifier CURSOR FOR query_exp ", NULL, handle_cursor_def, 0},
{L"cursor_def  :  DECLARE identifier cursor_type CURSOR FOR query_exp ", NULL, handle_cursor_def, 0},
{L"opt_order_by_clause  :   ", NULL, handle_opt_order_by_clause, 0},
{L"opt_order_by_clause  :  ORDER BY ordering_spec_commalist ", NULL, handle_opt_order_by_clause, 0},
{L"ordering_spec_commalist  :  ordering_spec ", NULL, handle_ordering_spec_commalist, 0},
{L"ordering_spec_commalist  :  ordering_spec_commalist , ordering_spec ", NULL, handle_ordering_spec_commalist, 0},
{L"ordering_spec  :  scalar_exp opt_asc_desc ", NULL, handle_ordering_spec, 0},
{L"ordering_spec  :  mssql_xml_col opt_asc_desc ", NULL, handle_ordering_spec, 0},
{L"opt_asc_desc  :   ", NULL, handle_opt_asc_desc, 0},
{L"opt_asc_desc  :  ASC ", NULL, handle_opt_asc_desc, 0},
{L"opt_asc_desc  :  DESC ", NULL, handle_opt_asc_desc, 0},
{L"create_snapshot_log  :  CREATE SNAPSHOT LOGX FOR q_table_name ", NULL, handle_create_snapshot_log, 0},
{L"drop_snapshot_log  :  DROP SNAPSHOT LOGX FOR q_table_name ", NULL, handle_drop_snapshot_log, 0},
{L"purge_snapshot_log  :  PURGE SNAPSHOT LOGX FOR q_table_name ", NULL, handle_purge_snapshot_log, 0},
{L"opt_snapshot_string_literal  :   ", NULL, handle_opt_snapshot_string_literal, 0},
{L"opt_snapshot_string_literal  :  STRING ", NULL, handle_opt_snapshot_string_literal, 0},
{L"opt_snapshot_where_clause  :   ", NULL, handle_opt_snapshot_where_clause, 0},
{L"opt_snapshot_where_clause  :  WHERE STRING ", NULL, handle_opt_snapshot_where_clause, 0},
{L"create_snapshot  :  CREATE SNAPSHOT q_table_name FROM q_table_name opt_snapshot_string_literal opt_snapshot_where_clause ", NULL, handle_create_snapshot, 0},
{L"create_snapshot  :  CREATE NONINCREMENTAL SNAPSHOT q_table_name AS STRING ", NULL, handle_create_snapshot, 0},
{L"opt_with_delete  :   ", NULL, handle_opt_with_delete, 0},
{L"opt_with_delete  :  WITH DELETE_L ", NULL, handle_opt_with_delete, 0},
{L"drop_snapshot  :  DROP SNAPSHOT q_table_name opt_with_delete ", NULL, handle_drop_snapshot, 0},
{L"opt_nonincremental  :   ", NULL, handle_opt_nonincremental, 0},
{L"opt_nonincremental  :  AS NONINCREMENTAL ", NULL, handle_opt_nonincremental, 0},
{L"refresh_snapshot  :  UPDATE SNAPSHOT q_table_name opt_nonincremental ", NULL, handle_refresh_snapshot, 0},
{L"create_freetext_index  :  CREATE TEXT_L opt_xml INDEX ON q_table_name ( column ) opt_with_key opt_deffer_generation opt_with opt_data_modification_action opt_lang opt_enc ", NULL, handle_create_freetext_index, 0},
{L"opt_data_modification_action  :   ", NULL, handle_opt_data_modification_action, 0},
{L"opt_data_modification_action  :  USING FUNCTION ", NULL, handle_opt_data_modification_action, 0},
{L"opt_column  :   ", NULL, handle_opt_column, 0},
{L"opt_column  :  ( column ) ", NULL, handle_opt_column, 0},
{L"create_freetext_trigger  :  CREATE TEXT_L TRIGGER ON q_table_name opt_column ", NULL, handle_create_freetext_trigger, 0},
{L"drop_freetext_trigger  :  DROP TEXT_L TRIGGER ON q_table_name opt_column ", NULL, handle_drop_freetext_trigger, 0},
{L"opt_xml  :   ", NULL, handle_opt_xml, 0},
{L"opt_xml  :  XML ", NULL, handle_opt_xml, 0},
{L"opt_with_key  :   ", NULL, handle_opt_with_key, 0},
{L"opt_with_key  :  WITH KEY column ", NULL, handle_opt_with_key, 0},
{L"opt_with  :   ", NULL, handle_opt_with, 0},
{L"opt_with  :  CLUSTERED WITH ( column_commalist ) ", NULL, handle_opt_with, 0},
{L"opt_lang  :   ", NULL, handle_opt_lang, 0},
{L"opt_lang  :  LANGUAGE STRING ", NULL, handle_opt_lang, 0},
{L"opt_enc  :   ", NULL, handle_opt_enc, 0},
{L"opt_enc  :  ENCODING STRING ", NULL, handle_opt_enc, 0},
{L"opt_deffer_generation  :   ", NULL, handle_opt_deffer_generation, 0},
{L"opt_deffer_generation  :  NOT INSERT ", NULL, handle_opt_deffer_generation, 0},
{L"manipulative_statement  :  query_exp ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  query_no_from_spec ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  update_statement_positioned ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  update_statement_searched ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  insert_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  delete_statement_positioned ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  delete_statement_searched ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  call_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  static_method_invocation ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  METHOD CALL static_method_invocation ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  top_level_method_invocation ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  set_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  drop_xml_view ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  commit_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  rollback_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  admin_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  use_statement ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  attach_table ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  create_snapshot_log ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  drop_snapshot_log ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  purge_snapshot_log ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  create_snapshot ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  drop_snapshot ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  refresh_snapshot ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  create_freetext_index ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  create_freetext_trigger ", NULL, handle_manipulative_statement, 0},
{L"manipulative_statement  :  drop_freetext_trigger ", NULL, handle_manipulative_statement, 0},
{L"use_statement  :  USE identifier ", NULL, handle_use_statement, 0},
{L"close_statement  :  CLOSE cursor ", NULL, handle_close_statement, 0},
{L"commit_statement  :  COMMIT WORK ", NULL, handle_commit_statement, 0},
{L"delete_statement_positioned  :  DELETE_L FROM table WHERE CURRENT OF cursor ", NULL, handle_delete_statement_positioned, 0},
{L"delete_statement_searched  :  DELETE_L FROM table opt_where_clause ", NULL, handle_delete_statement_searched, 0},
{L"fetch_statement  :  FETCH cursor INTO target_commalist ", NULL, handle_fetch_statement, 0},
{L"fetch_statement  :  FETCH cursor NAME INTO target_commalist ", NULL, handle_fetch_statement, 0},
{L"fetch_statement  :  FETCH cursor NAME scalar_exp INTO target_commalist ", NULL, handle_fetch_statement, 0},
{L"insert_mode  :  INTO ", NULL, handle_insert_mode, 0},
{L"insert_mode  :  REPLACING ", NULL, handle_insert_mode, 0},
{L"insert_mode  :  SOFT ", NULL, handle_insert_mode, 0},
{L"insert_statement  :  INSERT insert_mode table priv_opt_column_commalist values_or_query_spec ", NULL, handle_insert_statement, 0},
{L"values_or_query_spec  :  VALUES ( insert_atom_commalist ) ", NULL, handle_values_or_query_spec, 0},
{L"values_or_query_spec  :  query_spec ", NULL, handle_values_or_query_spec, 0},
{L"insert_atom_commalist  :  insert_atom ", NULL, handle_insert_atom_commalist, 0},
{L"insert_atom_commalist  :  insert_atom_commalist , insert_atom ", NULL, handle_insert_atom_commalist, 0},
{L"insert_atom  :  scalar_exp ", NULL, handle_insert_atom, 0},
{L"sql_option  :  ORDER ", NULL, handle_sql_option, 0},
{L"sql_option  :  HASH ", NULL, handle_sql_option, 0},
{L"sql_option  :  LOOP ", NULL, handle_sql_option, 0},
{L"sql_option  :  INDEX identifier ", NULL, handle_sql_option, 0},
{L"sql_option  :  INDEX PRIMARY KEY ", NULL, handle_sql_option, 0},
{L"sql_option  :  INDEX TEXT_L KEY ", NULL, handle_sql_option, 0},
{L"sql_option  :  NAME INTNUM ", NULL, handle_sql_option, 0},
{L"sql_opt_commalist  :  sql_option ", NULL, handle_sql_opt_commalist, 0},
{L"sql_opt_commalist  :  sql_opt_commalist , sql_option ", NULL, handle_sql_opt_commalist, 0},
{L"opt_sql_opt  :   ", NULL, handle_opt_sql_opt, 0},
{L"opt_sql_opt  :  OPTION ( sql_opt_commalist ) ", NULL, handle_opt_sql_opt, 0},
{L"opt_table_opt  :   ", NULL, handle_opt_table_opt, 0},
{L"opt_table_opt  :  TABLE OPTION ( sql_opt_commalist ) ", NULL, handle_opt_table_opt, 0},
{L"cursor_option  :  EXCLUSIVE ", NULL, handle_cursor_option, 0},
{L"cursor_option  :  PREFETCH INTNUM ", NULL, handle_cursor_option, 0},
{L"cursor_options_commalist  :  cursor_option ", NULL, handle_cursor_options_commalist, 0},
{L"cursor_options_commalist  :  cursor_options_commalist , cursor_option ", NULL, handle_cursor_options_commalist, 0},
{L"opt_cursor_options_list  :   ", NULL, handle_opt_cursor_options_list, 0},
{L"opt_cursor_options_list  :  ( cursor_options_commalist ) ", NULL, handle_opt_cursor_options_list, 0},
{L"open_statement  :  OPEN cursor opt_cursor_options_list ", NULL, handle_open_statement, 0},
{L"rollback_statement  :  ROLLBACK WORK ", NULL, handle_rollback_statement, 0},
{L"with_opt_cursor_options_list  :   ", NULL, handle_with_opt_cursor_options_list, 0},
{L"with_opt_cursor_options_list  :  WITH opt_cursor_options_list ", NULL, handle_with_opt_cursor_options_list, 0},
{L"select_statement  :  SELECT opt_top selection INTO target_commalist table_exp with_opt_cursor_options_list ", NULL, handle_select_statement, 0},
{L"opt_all_distinct  :   ", NULL, handle_opt_all_distinct, 0},
{L"opt_all_distinct  :  ALL ", NULL, handle_opt_all_distinct, 0},
{L"opt_all_distinct  :  DISTINCT ", NULL, handle_opt_all_distinct, 0},
{L"opt_ties  :   ", NULL, handle_opt_ties, 0},
{L"opt_ties  :  WITH TIES ", NULL, handle_opt_ties, 0},
{L"opt_top  :  opt_all_distinct ", NULL, handle_opt_top, 0},
{L"opt_top  :  opt_all_distinct TOP INTNUM opt_ties ", NULL, handle_opt_top, 0},
{L"opt_top  :  opt_all_distinct TOP ( scalar_exp ) opt_ties ", NULL, handle_opt_top, 0},
{L"opt_top  :  opt_all_distinct TOP INTNUM , INTNUM opt_ties ", NULL, handle_opt_top, 0},
{L"opt_top  :  opt_all_distinct TOP ( scalar_exp , scalar_exp ) opt_ties ", NULL, handle_opt_top, 0},
{L"update_statement_positioned  :  UPDATE table SET assignment_commalist WHERE CURRENT OF cursor ", NULL, handle_update_statement_positioned, 0},
{L"assignment_commalist  :   ", NULL, handle_assignment_commalist, 0},
{L"assignment_commalist  :  assignment ", NULL, handle_assignment_commalist, 0},
{L"assignment_commalist  :  assignment_commalist , assignment ", NULL, handle_assignment_commalist, 0},
{L"assignment  :  column COMPARISON scalar_exp ", NULL, handle_assignment, 0},
{L"update_statement_searched  :  UPDATE table SET assignment_commalist opt_where_clause ", NULL, handle_update_statement_searched, 0},
{L"target_commalist  :  target ", NULL, handle_target_commalist, 0},
{L"target_commalist  :  target_commalist , target ", NULL, handle_target_commalist, 0},
{L"target  :  column_ref ", NULL, handle_target, 0},
{L"target  :  member_observer ", NULL, handle_target, 0},
{L"target  :  lvalue_array_ref ", NULL, handle_target, 0},
{L"opt_where_clause  :   ", NULL, handle_opt_where_clause, 0},
{L"opt_where_clause  :  where_clause ", NULL, handle_opt_where_clause, 0},
{L"opt_best  :   ", NULL, handle_opt_best, 0},
{L"opt_best  :  BEST ", NULL, handle_opt_best, 0},
{L"query_exp  :  query_term ", NULL, handle_query_exp, 0},
{L"query_exp  :  non_final_union_exp opt_best UNION opt_corresponding query_term ", NULL, handle_query_exp, 0},
{L"query_exp  :  non_final_union_exp opt_best UNION ALL opt_corresponding query_term ", NULL, handle_query_exp, 0},
{L"query_exp  :  non_final_union_exp INTERSECT opt_corresponding query_term ", NULL, handle_query_exp, 0},
{L"query_exp  :  non_final_union_exp INTERSECT ALL opt_corresponding query_term ", NULL, handle_query_exp, 0},
{L"query_exp  :  non_final_union_exp EXCEPT opt_corresponding query_term ", NULL, handle_query_exp, 0},
{L"query_exp  :  non_final_union_exp EXCEPT ALL opt_corresponding query_term ", NULL, handle_query_exp, 0},
{L"non_final_union_exp  :  non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_union_exp  :  non_final_union_exp opt_best UNION opt_corresponding non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_union_exp  :  non_final_union_exp opt_best UNION ALL opt_corresponding non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_union_exp  :  non_final_union_exp INTERSECT opt_corresponding non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_union_exp  :  non_final_union_exp INTERSECT ALL opt_corresponding non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_union_exp  :  non_final_union_exp EXCEPT opt_corresponding non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_union_exp  :  non_final_union_exp EXCEPT ALL opt_corresponding non_final_query_term ", NULL, handle_non_final_union_exp, 0},
{L"non_final_query_term  :  non_final_query_spec ", NULL, handle_non_final_query_term, 0},
{L"non_final_query_term  :  XPATH STRING ", NULL, handle_non_final_query_term, 0},
{L"query_term  :  query_spec ", NULL, handle_query_term, 0},
{L"query_term  :  ( query_exp ) opt_order_by_clause ", NULL, handle_query_term, 0},
{L"query_term  :  XPATH STRING ", NULL, handle_query_term, 0},
{L"opt_corresponding  :   ", NULL, handle_opt_corresponding, 0},
{L"opt_corresponding  :  CORRESPONDING BY ( column_commalist ) ", NULL, handle_opt_corresponding, 0},
{L"non_final_query_spec  :  SELECT opt_top selection non_final_table_exp ", NULL, handle_non_final_query_spec, 0},
{L"query_spec  :  SELECT opt_top selection table_exp ", NULL, handle_query_spec, 0},
{L"query_no_from_spec  :  SELECT opt_top selection ", NULL, handle_query_no_from_spec, 0},
{L"selection  :  select_scalar_exp_commalist ", NULL, handle_selection, 0},
{L"non_final_table_exp  :  from_clause opt_where_clause opt_group_by_clause opt_having_clause ", NULL, handle_non_final_table_exp, 0},
{L"table_exp  :  from_clause opt_where_clause opt_group_by_clause opt_having_clause opt_order_by_clause opt_lock_mode opt_sql_opt ", NULL, handle_table_exp, 0},
{L"from_clause  :  FROM table_ref_commalist ", NULL, handle_from_clause, 0},
{L"table_ref_commalist  :  table_ref ", NULL, handle_table_ref_commalist, 0},
{L"table_ref_commalist  :  table_ref_commalist , table_ref ", NULL, handle_table_ref_commalist, 0},
{L"proc_col_list  :  column_def ", NULL, handle_proc_col_list, 0},
{L"proc_col_list  :  proc_col_list , column_def ", NULL, handle_proc_col_list, 0},
{L"opt_proc_col_list  :  ( proc_col_list ) ", NULL, handle_opt_proc_col_list, 0},
{L"column_commalist_or_empty  :   ", NULL, handle_column_commalist_or_empty, 0},
{L"column_commalist_or_empty  :  column_commalist ", NULL, handle_column_commalist_or_empty, 0},
{L"table_ref  :  table ", NULL, handle_table_ref, 0},
{L"table_ref  :  ( query_exp ) identifier ", NULL, handle_table_ref, 0},
{L"table_ref  :  ( query_exp ) AS identifier ", NULL, handle_table_ref, 0},
{L"table_ref  :  joined_table ", NULL, handle_table_ref, 0},
{L"table_ref  :  q_table_name ( column_commalist_or_empty ) opt_proc_col_list identifier ", NULL, handle_table_ref, 0},
{L"table_ref_nj  :  table ", NULL, handle_table_ref_nj, 0},
{L"table_ref_nj  :  subquery identifier ", NULL, handle_table_ref_nj, 0},
{L"table_ref_nj  :  subquery AS identifier ", NULL, handle_table_ref_nj, 0},
{L"table_ref_nj  :  ( joined_table ) ", NULL, handle_table_ref_nj, 0},
{L"jtype  :   ", NULL, handle_jtype, 0},
{L"jtype  :  LEFT opt_outer ", NULL, handle_jtype, 0},
{L"jtype  :  RIGHT opt_outer ", NULL, handle_jtype, 0},
{L"jtype  :  FULL opt_outer ", NULL, handle_jtype, 0},
{L"jtype  :  INNER ", NULL, handle_jtype, 0},
{L"jtype  :  CROSS ", NULL, handle_jtype, 0},
{L"opt_outer  :   ", NULL, handle_opt_outer, 0},
{L"opt_outer  :  OUTER ", NULL, handle_opt_outer, 0},
{L"join  :  NATURAL jtype ", NULL, handle_join, 0},
{L"join  :  jtype ", NULL, handle_join, 0},
{L"joined_table  :  joined_table_1 ", NULL, handle_joined_table, 0},
{L"joined_table  :  BEGIN_OJ_X joined_table_1 ENDX ", NULL, handle_joined_table, 0},
{L"joined_table  :  ( joined_table_1 ) ", NULL, handle_joined_table, 0},
{L"joined_table_1  :  table_ref join JOIN table_ref_nj join_condition ", NULL, handle_joined_table_1, 0},
{L"join_condition  :   ", NULL, handle_join_condition, 0},
{L"join_condition  :  ON search_condition ", NULL, handle_join_condition, 0},
{L"join_condition  :  USING ( column_commalist ) ", NULL, handle_join_condition, 0},
{L"where_clause  :  WHERE search_condition ", NULL, handle_where_clause, 0},
{L"opt_group_by_clause  :   ", NULL, handle_opt_group_by_clause, 0},
{L"opt_group_by_clause  :  GROUP BY ordering_spec_commalist ", NULL, handle_opt_group_by_clause, 0},
{L"opt_group_by_clause  :  GROUP BY ROLLUP ( ordering_spec_commalist ) ", NULL, handle_opt_group_by_clause, 0},
{L"opt_group_by_clause  :  GROUP BY CUBE ( ordering_spec_commalist ) ", NULL, handle_opt_group_by_clause, 0},
{L"opt_having_clause  :   ", NULL, handle_opt_having_clause, 0},
{L"opt_having_clause  :  HAVING search_condition ", NULL, handle_opt_having_clause, 0},
{L"opt_lock_mode  :   ", NULL, handle_opt_lock_mode, 0},
{L"opt_lock_mode  :  FOR UPDATE ", NULL, handle_opt_lock_mode, 0},
{L"opt_lock_mode  :  FOR XML NAME ", NULL, handle_opt_lock_mode, 0},
{L"opt_lock_mode  :  FOR XML NAME NAME ", NULL, handle_opt_lock_mode, 0},
{L"search_condition  :  search_condition OR search_condition ", NULL, handle_search_condition, 0},
{L"search_condition  :  search_condition AND search_condition ", NULL, handle_search_condition, 0},
{L"search_condition  :  NOT search_condition ", NULL, handle_search_condition, 0},
{L"search_condition  :  ( search_condition ) ", NULL, handle_search_condition, 0},
{L"search_condition  :  predicate ", NULL, handle_search_condition, 0},
{L"predicate  :  comparison_predicate ", NULL, handle_predicate, 0},
{L"predicate  :  between_predicate ", NULL, handle_predicate, 0},
{L"predicate  :  like_predicate ", NULL, handle_predicate, 0},
{L"predicate  :  test_for_null ", NULL, handle_predicate, 0},
{L"predicate  :  in_predicate ", NULL, handle_predicate, 0},
{L"predicate  :  all_or_any_predicate ", NULL, handle_predicate, 0},
{L"predicate  :  existence_test ", NULL, handle_predicate, 0},
{L"predicate  :  scalar_exp_predicate ", NULL, handle_predicate, 0},
{L"scalar_exp_predicate  :  scalar_exp ", NULL, handle_scalar_exp_predicate, 0},
{L"comparison_predicate  :  scalar_exp COMPARISON scalar_exp ", NULL, handle_comparison_predicate, 0},
{L"between_predicate  :  scalar_exp NOT BETWEEN scalar_exp AND scalar_exp ", NULL, handle_between_predicate, 0},
{L"between_predicate  :  scalar_exp BETWEEN scalar_exp AND scalar_exp ", NULL, handle_between_predicate, 0},
{L"like_predicate  :  scalar_exp NOT LIKE scalar_exp opt_escape ", NULL, handle_like_predicate, 0},
{L"like_predicate  :  scalar_exp LIKE scalar_exp opt_escape ", NULL, handle_like_predicate, 0},
{L"opt_escape  :   ", NULL, handle_opt_escape, 0},
{L"opt_escape  :  ESCAPE atom ", NULL, handle_opt_escape, 0},
{L"opt_escape  :  BEGINX ESCAPE atom ENDX ", NULL, handle_opt_escape, 0},
{L"test_for_null  :  scalar_exp IS NOT NULLX ", NULL, handle_test_for_null, 0},
{L"test_for_null  :  scalar_exp IS NULLX ", NULL, handle_test_for_null, 0},
{L"in_predicate  :  scalar_exp NOT IN_L subquery ", NULL, handle_in_predicate, 0},
{L"in_predicate  :  scalar_exp IN_L subquery ", NULL, handle_in_predicate, 0},
{L"in_predicate  :  scalar_exp NOT IN_L ( scalar_exp_commalist ) ", NULL, handle_in_predicate, 0},
{L"in_predicate  :  scalar_exp IN_L ( scalar_exp_commalist ) ", NULL, handle_in_predicate, 0},
{L"all_or_any_predicate  :  scalar_exp COMPARISON any_all_some subquery ", NULL, handle_all_or_any_predicate, 0},
{L"any_all_some  :  ANY ", NULL, handle_any_all_some, 0},
{L"any_all_some  :  ALL ", NULL, handle_any_all_some, 0},
{L"any_all_some  :  SOME ", NULL, handle_any_all_some, 0},
{L"existence_test  :  EXISTS subquery ", NULL, handle_existence_test, 0},
{L"scalar_subquery  :  subquery ", NULL, handle_scalar_subquery, 0},
{L"subquery  :  ( SELECT opt_top selection table_exp ) ", NULL, handle_subquery, 0},
{L"scalar_exp  :  scalar_exp - scalar_exp ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  scalar_exp + scalar_exp ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  scalar_exp * scalar_exp ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  scalar_exp / scalar_exp ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  + scalar_exp ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  - scalar_exp ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  assignment_statement ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  string_concatenation_operator ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  column_ref ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  scalar_exp_no_col_ref ", NULL, handle_scalar_exp, 0},
{L"scalar_exp  :  obe_literal ", NULL, handle_scalar_exp, 0},
{L"scalar_exp_no_col_ref  :  atom_no_obe ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  aggregate_ref ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  scalar_subquery ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  ( scalar_exp ) ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  ( scalar_exp , scalar_exp_commalist ) ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  function_call ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  new_invocation ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  cvt_exp ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  cast_exp ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  simple_case ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  searched_case ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  coalesce_exp ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  nullif_exp ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  array_ref ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  static_method_invocation ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  method_invocation ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref  :  member_observer ", NULL, handle_scalar_exp_no_col_ref, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  atom_no_obe ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  aggregate_ref ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  scalar_subquery ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  ( scalar_exp ) ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  ( scalar_exp , scalar_exp_commalist ) ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  function_call ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  new_invocation ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  cvt_exp ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  cast_exp ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  simple_case ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  searched_case ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  coalesce_exp ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  nullif_exp ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  array_ref ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  static_method_invocation ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  method_invocation ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"scalar_exp_no_col_ref_no_mem_obs_chain  :  member_observer_no_id_chain ", NULL, handle_scalar_exp_no_col_ref_no_mem_obs_chain, 0},
{L"cvt_exp  :  CONVERT ( data_type , scalar_exp ) ", NULL, handle_cvt_exp, 0},
{L"opt_collate_exp  :   ", NULL, handle_opt_collate_exp, 0},
{L"opt_collate_exp  :  COLLATE q_table_name ", NULL, handle_opt_collate_exp, 0},
{L"cast_exp  :  CAST ( scalar_exp AS data_type opt_collate_exp ) ", NULL, handle_cast_exp, 0},
{L"mssql_xml_col  :  MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAMEZ ", NULL, handle_mssql_xml_col, 0},
{L"mssql_xml_col  :  MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAMEYZ ", NULL, handle_mssql_xml_col, 0},
{L"mssql_xml_col  :  MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAME MSSQL_XMLCOL_NAMEZ ", NULL, handle_mssql_xml_col, 0},
{L"as_expression  :  scalar_exp AS identifier data_type ", NULL, handle_as_expression, 0},
{L"as_expression  :  scalar_exp AS identifier ", NULL, handle_as_expression, 0},
{L"as_expression  :  scalar_exp identifier ", NULL, handle_as_expression, 0},
{L"as_expression  :  scalar_exp AS mssql_xml_col ", NULL, handle_as_expression, 0},
{L"array_ref  :  scalar_exp_no_col_ref [ scalar_exp ] ", NULL, handle_array_ref, 0},
{L"array_ref  :  lvalue_array_ref ", NULL, handle_array_ref, 0},
{L"lvalue_array_ref  :  column_ref [ scalar_exp ] ", NULL, handle_lvalue_array_ref, 0},
{L"opt_scalar_exp_commalist  :   ", NULL, handle_opt_scalar_exp_commalist, 0},
{L"opt_scalar_exp_commalist  :  scalar_exp_commalist ", NULL, handle_opt_scalar_exp_commalist, 0},
{L"function_name  :  identifier ", NULL, handle_function_name, 0},
{L"function_name  :  identifier . method_identifier ", NULL, handle_function_name, 0},
{L"function_name  :  identifier . identifier . method_identifier ", NULL, handle_function_name, 0},
{L"function_name  :  identifier . identifier . identifier . method_identifier ", NULL, handle_function_name, 0},
{L"function_name  :  identifier . . method_identifier ", NULL, handle_function_name, 0},
{L"function_name  :  identifier . . identifier . method_identifier ", NULL, handle_function_name, 0},
{L"function_name  :  LEFT ", NULL, handle_function_name, 0},
{L"function_name  :  RIGHT ", NULL, handle_function_name, 0},
{L"function_name  :  LOGX ", NULL, handle_function_name, 0},
{L"kwd_commalist  :  identifier KWD_TAG scalar_exp ", NULL, handle_kwd_commalist, 0},
{L"kwd_commalist  :  kwd_commalist , identifier KWD_TAG scalar_exp ", NULL, handle_kwd_commalist, 0},
{L"as_commalist  :  as_expression ", NULL, handle_as_commalist, 0},
{L"as_commalist  :  as_commalist , as_expression ", NULL, handle_as_commalist, 0},
{L"as_commalist  :  as_commalist , scalar_exp ", NULL, handle_as_commalist, 0},
{L"opt_arg_commalist  :   ", NULL, handle_opt_arg_commalist, 0},
{L"opt_arg_commalist  :  kwd_commalist ", NULL, handle_opt_arg_commalist, 0},
{L"opt_arg_commalist  :  scalar_exp_commalist ", NULL, handle_opt_arg_commalist, 0},
{L"opt_arg_commalist  :  scalar_exp_commalist , kwd_commalist ", NULL, handle_opt_arg_commalist, 0},
{L"opt_arg_commalist  :  scalar_exp_commalist , as_commalist ", NULL, handle_opt_arg_commalist, 0},
{L"opt_arg_commalist  :  as_commalist ", NULL, handle_opt_arg_commalist, 0},
{L"function_call  :  function_name ( opt_arg_commalist ) ", NULL, handle_function_call, 0},
{L"function_call  :  TIMESTAMP_FUNC ( SQL_TSI , scalar_exp , scalar_exp ) ", NULL, handle_function_call, 0},
{L"function_call  :  EXTRACT ( NAME FROM scalar_exp ) ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X identifier ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X LEFT ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X RIGHT ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X LOGX ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X identifier ( scalar_exp IN_L scalar_exp ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_CALL_X function_name ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_CALL_X function_name ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X USER ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X CHARACTER ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X TIMESTAMP_FUNC ( SQL_TSI , scalar_exp , scalar_exp ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X CONVERT ( scalar_exp , NAME ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  BEGIN_FN_X EXTRACT ( NAME FROM scalar_exp ) ENDX ", NULL, handle_function_call, 0},
{L"function_call  :  CALL ( scalar_exp ) ( opt_arg_commalist ) ", NULL, handle_function_call, 0},
{L"function_call  :  CURRENT_DATE ", NULL, handle_function_call, 0},
{L"function_call  :  CURRENT_TIME ", NULL, handle_function_call, 0},
{L"function_call  :  CURRENT_TIME ( scalar_exp ) ", NULL, handle_function_call, 0},
{L"function_call  :  CURRENT_TIMESTAMP ", NULL, handle_function_call, 0},
{L"function_call  :  CURRENT_TIMESTAMP ( scalar_exp ) ", NULL, handle_function_call, 0},
{L"function_call  :  GROUPING ( column_ref ) ", NULL, handle_function_call, 0},
{L"obe_literal  :  BEGINX identifier atom ENDX ", NULL, handle_obe_literal, 0},
{L"obe_literal  :  BEGIN_U_X STRING ENDX ", NULL, handle_obe_literal, 0},
{L"scalar_exp_commalist  :  scalar_exp ", NULL, handle_scalar_exp_commalist, 0},
{L"scalar_exp_commalist  :  scalar_exp_commalist , scalar_exp ", NULL, handle_scalar_exp_commalist, 0},
{L"select_scalar_exp_commalist  :  scalar_exp ", NULL, handle_select_scalar_exp_commalist, 0},
{L"select_scalar_exp_commalist  :  as_expression ", NULL, handle_select_scalar_exp_commalist, 0},
{L"select_scalar_exp_commalist  :  select_scalar_exp_commalist , scalar_exp ", NULL, handle_select_scalar_exp_commalist, 0},
{L"select_scalar_exp_commalist  :  select_scalar_exp_commalist , as_expression ", NULL, handle_select_scalar_exp_commalist, 0},
{L"atom_no_obe  :  parameter_ref ", NULL, handle_atom_no_obe, 0},
{L"atom_no_obe  :  literal ", NULL, handle_atom_no_obe, 0},
{L"atom_no_obe  :  USER ", NULL, handle_atom_no_obe, 0},
{L"atom  :  atom_no_obe ", NULL, handle_atom, 0},
{L"atom  :  obe_literal ", NULL, handle_atom, 0},
{L"simple_case  :  CASE scalar_exp simple_when_list ENDX ", NULL, handle_simple_case, 0},
{L"searched_case  :  CASE searched_when_list ENDX ", NULL, handle_searched_case, 0},
{L"searched_when_list  :  searched_when ", NULL, handle_searched_when_list, 0},
{L"searched_when_list  :  searched_when_list searched_when ", NULL, handle_searched_when_list, 0},
{L"simple_when_list  :  simple_when ", NULL, handle_simple_when_list, 0},
{L"simple_when_list  :  simple_when_list simple_when ", NULL, handle_simple_when_list, 0},
{L"simple_when  :  WHEN scalar_exp THEN scalar_exp ", NULL, handle_simple_when, 0},
{L"simple_when  :  ELSE scalar_exp ", NULL, handle_simple_when, 0},
{L"searched_when  :  WHEN search_condition THEN scalar_exp ", NULL, handle_searched_when, 0},
{L"searched_when  :  ELSE scalar_exp ", NULL, handle_searched_when, 0},
{L"coalesce_exp  :  COALESCE ( scalar_exp_commalist ) ", NULL, handle_coalesce_exp, 0},
{L"nullif_exp  :  NULLIF ( scalar_exp , scalar_exp ) ", NULL, handle_nullif_exp, 0},
{L"parameter_ref  :  parameter ", NULL, handle_parameter_ref, 0},
{L"parameter_ref  :  parameter parameter ", NULL, handle_parameter_ref, 0},
{L"parameter_ref  :  parameter INDICATOR parameter ", NULL, handle_parameter_ref, 0},
{L"aggregate_ref  :  AGGREGATE function_name ( opt_arg_commalist ) ", NULL, handle_aggregate_ref, 0},
{L"aggregate_ref  :  AMMSC ( DISTINCT scalar_exp ) ", NULL, handle_aggregate_ref, 0},
{L"aggregate_ref  :  AMMSC ( ALL scalar_exp ) ", NULL, handle_aggregate_ref, 0},
{L"aggregate_ref  :  AMMSC ( scalar_exp ) ", NULL, handle_aggregate_ref, 0},
{L"literal  :  STRING ", NULL, handle_literal, 0},
{L"literal  :  WSTRING ", NULL, handle_literal, 0},
{L"literal  :  INTNUM ", NULL, handle_literal, 0},
{L"literal  :  APPROXNUM ", NULL, handle_literal, 0},
{L"literal  :  BINARYNUM ", NULL, handle_literal, 0},
{L"literal  :  NULLX ", NULL, handle_literal, 0},
{L"signed_literal  :  STRING ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  WSTRING ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  INTNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  - INTNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  + INTNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  APPROXNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  - APPROXNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  + APPROXNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  BINARYNUM ", NULL, handle_signed_literal, 0},
{L"signed_literal  :  NULLX ", NULL, handle_signed_literal, 0},
{L"q_table_name  :  identifier ", NULL, handle_q_table_name, 0},
{L"q_table_name  :  identifier . identifier ", NULL, handle_q_table_name, 0},
{L"q_table_name  :  identifier . identifier . identifier ", NULL, handle_q_table_name, 0},
{L"q_table_name  :  identifier . . identifier ", NULL, handle_q_table_name, 0},
{L"attach_q_table_name  :  identifier ", NULL, handle_attach_q_table_name, 0},
{L"attach_q_table_name  :  identifier . identifier ", NULL, handle_attach_q_table_name, 0},
{L"attach_q_table_name  :  identifier . identifier . identifier ", NULL, handle_attach_q_table_name, 0},
{L"attach_q_table_name  :  identifier . . identifier ", NULL, handle_attach_q_table_name, 0},
{L"new_proc_or_bif_name  :  identifier ", NULL, handle_new_proc_or_bif_name, 0},
{L"new_proc_or_bif_name  :  identifier . identifier ", NULL, handle_new_proc_or_bif_name, 0},
{L"new_proc_or_bif_name  :  identifier . identifier . identifier ", NULL, handle_new_proc_or_bif_name, 0},
{L"new_proc_or_bif_name  :  identifier . . identifier ", NULL, handle_new_proc_or_bif_name, 0},
{L"new_table_name  :  identifier ", NULL, handle_new_table_name, 0},
{L"new_table_name  :  identifier . identifier ", NULL, handle_new_table_name, 0},
{L"new_table_name  :  identifier . identifier . identifier ", NULL, handle_new_table_name, 0},
{L"new_table_name  :  identifier . . identifier ", NULL, handle_new_table_name, 0},
{L"table  :  q_table_name opt_table_opt ", NULL, handle_table, 0},
{L"table  :  q_table_name AS identifier opt_table_opt ", NULL, handle_table, 0},
{L"table  :  q_table_name identifier opt_table_opt ", NULL, handle_table, 0},
{L"column_ref  :  identifier ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . identifier ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . identifier . identifier ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . identifier . identifier . identifier ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . . identifier . identifier ", NULL, handle_column_ref, 0},
{L"column_ref  :  * ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . * ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . identifier . * ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . identifier . identifier . * ", NULL, handle_column_ref, 0},
{L"column_ref  :  identifier . . identifier . * ", NULL, handle_column_ref, 0},
{L"base_data_type  :  NUMERIC ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  NUMERIC ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  NUMERIC ( INTNUM , INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  DECIMAL ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  DECIMAL ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  DECIMAL ( INTNUM , INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  INTEGER ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  SMALLINT ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  FLOAT ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  FLOAT ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  REAL ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  DOUBLE PRECISION ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  LONG VARCHAR ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  LONG VARBINARY ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  VARBINARY ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  VARBINARY ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  BINARY ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  TIMESTAMP ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  DATETIME ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  TIME ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  DATE ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  NCHAR ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  NCHAR ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  NVARCHAR ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  NVARCHAR ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  LONG NVARCHAR ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  ANY ", NULL, handle_base_data_type, 0},
{L"base_data_type  :  ANY ( INTNUM ) ", NULL, handle_base_data_type, 0},
{L"data_type  :  base_data_type ", NULL, handle_data_type, 0},
{L"data_type  :  CHARACTER ", NULL, handle_data_type, 0},
{L"data_type  :  VARCHAR ", NULL, handle_data_type, 0},
{L"data_type  :  VARCHAR ( INTNUM ) ", NULL, handle_data_type, 0},
{L"data_type  :  CHARACTER ( INTNUM ) ", NULL, handle_data_type, 0},
{L"array_modifier  :  ARRAY ", NULL, handle_array_modifier, 0},
{L"array_modifier  :  ARRAY [ INTNUM ] ", NULL, handle_array_modifier, 0},
{L"data_type_ref  :  data_type_ref array_modifier ", NULL, handle_data_type_ref, 0},
{L"data_type_ref  :  data_type ", NULL, handle_data_type_ref, 0},
{L"data_type_ref  :  q_type_name ", NULL, handle_data_type_ref, 0},
{L"column_data_type  :  base_data_type ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  CHARACTER ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  VARCHAR ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  VARCHAR ( INTNUM ) ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  CHARACTER ( INTNUM ) ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  q_type_name ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  LONG q_type_name ", NULL, handle_column_data_type, 0},
{L"column_data_type  :  LONG XML ", NULL, handle_column_data_type, 0},
{L"column  :  identifier ", NULL, handle_column, 0},
{L"column  :  identifier . identifier . identifier . identifier ", NULL, handle_column, 0},
{L"index  :  identifier ", NULL, handle_index, 0},
{L"cursor  :  identifier ", NULL, handle_cursor, 0},
{L"parameter  :  PARAMETER_L ", NULL, handle_parameter, 0},
{L"parameter  :  NAMED_PARAMETER ", NULL, handle_parameter, 0},
{L"user  :  identifier ", NULL, handle_user, 0},
{L"opt_log  :   ", NULL, handle_opt_log, 0},
{L"opt_log  :  STRING ", NULL, handle_opt_log, 0},
{L"comma_opt_log  :   ", NULL, handle_comma_opt_log, 0},
{L"comma_opt_log  :  , STRING ", NULL, handle_comma_opt_log, 0},
{L"admin_statement  :  SHUTDOWN opt_log ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  CHECKPOINT opt_log ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  CHECKPOINT STRING STRING ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  BACKUP STRING ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  CHECK ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  SYNC REPLICATION opt_log comma_opt_log ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  DISCONNECT REPLICATION opt_log ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  LOGX ON ", NULL, handle_admin_statement, 0},
{L"admin_statement  :  LOGX OFF ", NULL, handle_admin_statement, 0},
{L"sql  :  user_aggregate_declaration ", NULL, handle_sql, 0},
{L"sql  :  routine_declaration ", NULL, handle_sql, 0},
{L"sql  :  module_declaration ", NULL, handle_sql, 0},
{L"sql  :  method_declaration ", NULL, handle_sql, 0},
{L"sql  :  trigger_def ", NULL, handle_sql, 0},
{L"sql  :  drop_trigger ", NULL, handle_sql, 0},
{L"sql  :  drop_proc ", NULL, handle_sql, 0},
{L"sql  :  manipulative_statement ", NULL, handle_sql, 0},
{L"sql  :  BEGIN_EQCALL_X q_table_name ENDX ", NULL, handle_sql, 0},
{L"sql  :  BEGIN_EQCALL_X q_table_name ( opt_scalar_exp_commalist ) ENDX ", NULL, handle_sql, 0},
{L"user_aggregate_declaration  :  CREATE AGGREGATE new_table_name rout_parameter_list opt_return FROM new_proc_or_bif_name , new_proc_or_bif_name , new_proc_or_bif_name user_aggregate_merge_opt ", NULL, handle_user_aggregate_declaration, 0},
{L"user_aggregate_merge_opt  :   ", NULL, handle_user_aggregate_merge_opt, 0},
{L"user_aggregate_merge_opt  :  , new_proc_or_bif_name ", NULL, handle_user_aggregate_merge_opt, 0},
{L"routine_declaration  :  CREATE routine_head new_table_name rout_parameter_list opt_return rout_alt_type compound_statement ", NULL, handle_routine_declaration, 0},
{L"routine_declaration  :  ATTACH routine_head attach_q_table_name rout_parameter_list opt_return rout_alt_type opt_as FROM literal ", NULL, handle_routine_declaration, 0},
{L"routine_declaration  :  CREATE routine_head new_table_name rout_parameter_list opt_return rout_alt_type LANGUAGE external_language_name EXTERNAL NAME_L STRING opt_type_option_list ", NULL, handle_routine_declaration, 0},
{L"module_body_part  :  routine_head identifier rout_parameter_list opt_return rout_alt_type compound_statement ", NULL, handle_module_body_part, 0},
{L"module_body  :  module_body_part ; ", NULL, handle_module_body, 0},
{L"module_body  :  module_body module_body_part ; ", NULL, handle_module_body, 0},
{L"module_declaration  :  CREATE MODULE new_table_name BEGINX module_body ENDX ", NULL, handle_module_declaration, 0},
{L"routine_head  :  FUNCTION ", NULL, handle_routine_head, 0},
{L"routine_head  :  PROCEDURE ", NULL, handle_routine_head, 0},
{L"opt_return  :   ", NULL, handle_opt_return, 0},
{L"opt_return  :  RETURNS data_type_ref ", NULL, handle_opt_return, 0},
{L"rout_parameter_list  :  ( ) ", NULL, handle_rout_parameter_list, 0},
{L"rout_parameter_list  :  ( parameter_commalist ) ", NULL, handle_rout_parameter_list, 0},
{L"parameter_commalist  :  rout_parameter ", NULL, handle_parameter_commalist, 0},
{L"parameter_commalist  :  parameter_commalist , rout_parameter ", NULL, handle_parameter_commalist, 0},
{L"rout_parameter  :  parameter_mode column_ref data_type_ref rout_alt_type ", NULL, handle_rout_parameter, 0},
{L"rout_parameter  :  parameter_mode column_ref data_type_ref DEFAULT signed_literal rout_alt_type ", NULL, handle_rout_parameter, 0},
{L"rout_parameter  :  parameter_mode column_ref data_type_ref EQUALS signed_literal rout_alt_type ", NULL, handle_rout_parameter, 0},
{L"parameter_mode  :  IN_L ", NULL, handle_parameter_mode, 0},
{L"parameter_mode  :  OUT_L ", NULL, handle_parameter_mode, 0},
{L"parameter_mode  :  INOUT_L ", NULL, handle_parameter_mode, 0},
{L"opt_parameter_mode  :   ", NULL, handle_opt_parameter_mode, 0},
{L"opt_parameter_mode  :  parameter_mode ", NULL, handle_opt_parameter_mode, 0},
{L"opt_soap_enc_mode  :   ", NULL, handle_opt_soap_enc_mode, 0},
{L"opt_soap_enc_mode  :  __SOAP_DIME_ENC IN_L ", NULL, handle_opt_soap_enc_mode, 0},
{L"opt_soap_enc_mode  :  __SOAP_DIME_ENC OUT_L ", NULL, handle_opt_soap_enc_mode, 0},
{L"opt_soap_enc_mode  :  __SOAP_DIME_ENC INOUT_L ", NULL, handle_opt_soap_enc_mode, 0},
{L"opt_soap_enc_mode  :  __SOAP_ENC_MIME IN_L ", NULL, handle_opt_soap_enc_mode, 0},
{L"opt_soap_enc_mode  :  __SOAP_ENC_MIME OUT_L ", NULL, handle_opt_soap_enc_mode, 0},
{L"opt_soap_enc_mode  :  __SOAP_ENC_MIME INOUT_L ", NULL, handle_opt_soap_enc_mode, 0},
{L"soap_proc_opt_list  :  soap_proc_opt ", NULL, handle_soap_proc_opt_list, 0},
{L"soap_proc_opt_list  :  soap_proc_opt_list , soap_proc_opt ", NULL, handle_soap_proc_opt_list, 0},
{L"soap_proc_opt  :  NAME EQUALS signed_literal ", NULL, handle_soap_proc_opt, 0},
{L"soap_kwd  :  __SOAP_TYPE ", NULL, handle_soap_kwd, 0},
{L"soap_kwd  :  __SOAP_HEADER ", NULL, handle_soap_kwd, 0},
{L"soap_kwd  :  __SOAP_FAULT ", NULL, handle_soap_kwd, 0},
{L"soap_kwd  :  __SOAP_DOC ", NULL, handle_soap_kwd, 0},
{L"soap_kwd  :  __SOAP_XML_TYPE ", NULL, handle_soap_kwd, 0},
{L"soap_kwd  :  __SOAP_DOCW ", NULL, handle_soap_kwd, 0},
{L"soap_kwd  :  __SOAP_HTTP ", NULL, handle_soap_kwd, 0},
{L"rout_alt_type  :   ", NULL, handle_rout_alt_type, 0},
{L"rout_alt_type  :  __SOAP_OPTIONS ( soap_kwd EQUALS STRING opt_soap_enc_mode , soap_proc_opt_list ) ", NULL, handle_rout_alt_type, 0},
{L"rout_alt_type  :  soap_kwd STRING opt_soap_enc_mode ", NULL, handle_rout_alt_type, 0},
{L"routine_statement  :  select_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  update_statement_positioned ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  update_statement_searched ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  insert_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  delete_statement_positioned ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  delete_statement_searched ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  close_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  fetch_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  open_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  rollback_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :  commit_statement ", NULL, handle_routine_statement, 0},
{L"routine_statement  :   ", NULL, handle_routine_statement, 0},
{L"empty2  :   ", NULL, handle_empty2, 0},
{L"compound_statement  :  BEGINX empty2 statement_list ENDX ", NULL, handle_compound_statement, 0},
{L"statement_list  :  statement_in_cs ", NULL, handle_statement_list, 0},
{L"statement_list  :  statement_list statement_in_cs ", NULL, handle_statement_list, 0},
{L"statement_in_cs  :  local_declaration ; ", NULL, handle_statement_in_cs, 0},
{L"statement_in_cs  :  compound_statement ", NULL, handle_statement_in_cs, 0},
{L"empty3  :   ", NULL, handle_empty3, 0},
{L"statement_in_cs  :  empty3 statement_in_cs_oper ", NULL, handle_statement_in_cs, 0},
{L"statement_in_cs_oper  :  routine_statement ; ", NULL, handle_statement_in_cs_oper, 0},
{L"statement_in_cs_oper  :  control_statement ", NULL, handle_statement_in_cs_oper, 0},
{L"statement_in_cs_oper  :  identifier COLON statement_in_cs ", NULL, handle_statement_in_cs_oper, 0},
{L"statement_in_cs_oper  :  HTMLSTR ", NULL, handle_statement_in_cs_oper, 0},
{L"statement_in_cs_oper  :  COMPARISON scalar_exp HTMLSTR ", NULL, handle_statement_in_cs_oper, 0},
{L"statement_in_cs_oper  :  / scalar_exp HTMLSTR ", NULL, handle_statement_in_cs_oper, 0},
{L"statement  :  compound_statement ", NULL, handle_statement, 0},
{L"empty4  :   ", NULL, handle_empty4, 0},
{L"statement  :  empty4 routine_statement ; ", NULL, handle_statement, 0},
{L"empty5  :   ", NULL, handle_empty5, 0},
{L"statement  :  empty5 control_statement ", NULL, handle_statement, 0},
{L"local_declaration  :  cursor_def ", NULL, handle_local_declaration, 0},
{L"local_declaration  :  variable_declaration ", NULL, handle_local_declaration, 0},
{L"local_declaration  :  handler_declaration ", NULL, handle_local_declaration, 0},
{L"variable_declaration  :  DECLARE variable_list data_type_ref ", NULL, handle_variable_declaration, 0},
{L"variable_list  :  identifier ", NULL, handle_variable_list, 0},
{L"variable_list  :  variable_list , identifier ", NULL, handle_variable_list, 0},
{L"condition  :  NOT FOUND ", NULL, handle_condition, 0},
{L"condition  :  SQLSTATE STRING ", NULL, handle_condition, 0},
{L"condition  :  SQLSTATE VALUE STRING ", NULL, handle_condition, 0},
{L"condition  :  SQLEXCEPTION ", NULL, handle_condition, 0},
{L"condition  :  SQLWARNING ", NULL, handle_condition, 0},
{L"handler_statement  :  compound_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  routine_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  call_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  method_invocation ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  static_method_invocation ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  set_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  RESIGNAL ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  RESIGNAL scalar_exp ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  return_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  assignment_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  if_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  goto_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  for_statement ", NULL, handle_handler_statement, 0},
{L"handler_statement  :  while_statement ", NULL, handle_handler_statement, 0},
{L"handler_declaration  :  WHENEVER condition GOTO identifier ", NULL, handle_handler_declaration, 0},
{L"handler_declaration  :  WHENEVER condition GO TO identifier ", NULL, handle_handler_declaration, 0},
{L"handler_declaration  :  WHENEVER condition DEFAULT ", NULL, handle_handler_declaration, 0},
{L"handler_declaration  :  DECLARE handler_type HANDLER FOR cond_value_list handler_statement ", NULL, handle_handler_declaration, 0},
{L"handler_type  :  CONTINUE ", NULL, handle_handler_type, 0},
{L"handler_type  :  EXIT ", NULL, handle_handler_type, 0},
{L"cond_value_list  :  condition ", NULL, handle_cond_value_list, 0},
{L"cond_value_list  :  cond_value_list , condition ", NULL, handle_cond_value_list, 0},
{L"control_statement  :  call_statement ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  method_invocation ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  static_method_invocation ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  set_statement ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  RESIGNAL ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  RESIGNAL scalar_exp ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  return_statement ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  assignment_statement ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  if_statement ", NULL, handle_control_statement, 0},
{L"control_statement  :  goto_statement ; ", NULL, handle_control_statement, 0},
{L"control_statement  :  for_statement ", NULL, handle_control_statement, 0},
{L"control_statement  :  while_statement ", NULL, handle_control_statement, 0},
{L"assignment_statement  :  lvalue EQUALS scalar_exp ", NULL, handle_assignment_statement, 0},
{L"assignment_statement  :  column_ref [ scalar_exp ] EQUALS scalar_exp ", NULL, handle_assignment_statement, 0},
{L"lvalue  :  column_ref ", NULL, handle_lvalue, 0},
{L"lvalue  :  member_observer ", NULL, handle_lvalue, 0},
{L"if_statement  :  IF ( search_condition ) statement opt_else ", NULL, handle_if_statement, 0},
{L"opt_else  :   ", NULL, handle_opt_else, 0},
{L"opt_else  :  ELSE statement ", NULL, handle_opt_else, 0},
{L"call_statement  :  CALL function_name ( opt_arg_commalist ) ", NULL, handle_call_statement, 0},
{L"call_statement  :  function_call ", NULL, handle_call_statement, 0},
{L"set_statement  :  SET identifier COMPARISON scalar_exp ", NULL, handle_set_statement, 0},
{L"set_statement  :  SET identifier ON ", NULL, handle_set_statement, 0},
{L"set_statement  :  SET identifier OFF ", NULL, handle_set_statement, 0},
{L"goto_statement  :  GOTO identifier ", NULL, handle_goto_statement, 0},
{L"goto_statement  :  GO TO identifier ", NULL, handle_goto_statement, 0},
{L"return_statement  :  RETURN scalar_exp ", NULL, handle_return_statement, 0},
{L"return_statement  :  RETURN ", NULL, handle_return_statement, 0},
{L"while_statement  :  WHILE ( search_condition ) statement ", NULL, handle_while_statement, 0},
{L"for_init_statement  :  assignment_statement ", NULL, handle_for_init_statement, 0},
{L"for_init_statement  :  variable_declaration ", NULL, handle_for_init_statement, 0},
{L"for_init_statement  :  call_statement ", NULL, handle_for_init_statement, 0},
{L"for_init_statement  :  static_method_invocation ", NULL, handle_for_init_statement, 0},
{L"for_init_statement_list  :   ", NULL, handle_for_init_statement_list, 0},
{L"for_init_statement_list  :  for_init_statement ", NULL, handle_for_init_statement_list, 0},
{L"for_init_statement_list  :  for_init_statement_list , for_init_statement ", NULL, handle_for_init_statement_list, 0},
{L"for_inc_statement  :  assignment_statement ", NULL, handle_for_inc_statement, 0},
{L"for_inc_statement  :  call_statement ", NULL, handle_for_inc_statement, 0},
{L"for_inc_statement  :  static_method_invocation ", NULL, handle_for_inc_statement, 0},
{L"for_inc_statement_list  :   ", NULL, handle_for_inc_statement_list, 0},
{L"for_inc_statement_list  :  for_inc_statement ", NULL, handle_for_inc_statement_list, 0},
{L"for_inc_statement_list  :  for_inc_statement_list , for_inc_statement ", NULL, handle_for_inc_statement_list, 0},
{L"for_opt_search_cond  :   ", NULL, handle_for_opt_search_cond, 0},
{L"for_opt_search_cond  :  search_condition ", NULL, handle_for_opt_search_cond, 0},
{L"for_statement  :  FOR query_exp DO statement ", NULL, handle_for_statement, 0},
{L"for_statement  :  FOR ( for_init_statement_list ; for_opt_search_cond ; for_inc_statement_list ) statement ", NULL, handle_for_statement, 0},
{L"for_statement  :  FOREACH ( data_type_ref identifier IN_L scalar_exp ) DO statement ", NULL, handle_for_statement, 0},
{L"trigger_def  :  CREATE TRIGGER identifier action_time event ON q_table_name opt_order opt_old_ref trig_action ", NULL, handle_trigger_def, 0},
{L"opt_order  :   ", NULL, handle_opt_order, 0},
{L"opt_order  :  ORDER INTNUM ", NULL, handle_opt_order, 0},
{L"trig_action  :  compound_statement ", NULL, handle_trig_action, 0},
{L"action_time  :  BEFORE ", NULL, handle_action_time, 0},
{L"action_time  :  AFTER ", NULL, handle_action_time, 0},
{L"action_time  :  INSTEAD OF ", NULL, handle_action_time, 0},
{L"event  :  INSERT ", NULL, handle_event, 0},
{L"event  :  UPDATE opt_column_commalist ", NULL, handle_event, 0},
{L"event  :  DELETE_L ", NULL, handle_event, 0},
{L"opt_old_ref  :   ", NULL, handle_opt_old_ref, 0},
{L"opt_old_ref  :  REFERENCING old_commalist ", NULL, handle_opt_old_ref, 0},
{L"old_commalist  :  old_alias ", NULL, handle_old_commalist, 0},
{L"old_commalist  :  old_commalist , old_alias ", NULL, handle_old_commalist, 0},
{L"old_alias  :  OLD AS identifier ", NULL, handle_old_alias, 0},
{L"old_alias  :  NEW AS identifier ", NULL, handle_old_alias, 0},
{L"drop_trigger  :  DROP TRIGGER q_table_name ", NULL, handle_drop_trigger, 0},
{L"drop_proc  :  DROP AGGREGATE q_table_name ", NULL, handle_drop_proc, 0},
{L"drop_proc  :  DROP routine_head q_table_name ", NULL, handle_drop_proc, 0},
{L"drop_proc  :  DROP MODULE q_table_name ", NULL, handle_drop_proc, 0},
{L"opt_element  :   ", NULL, handle_opt_element, 0},
{L"opt_element  :  AS identifier ", NULL, handle_opt_element, 0},
{L"xml_col  :  column_ref ", NULL, handle_xml_col, 0},
{L"xml_col  :  scalar_exp AS identifier ", NULL, handle_xml_col, 0},
{L"xml_col  :  scalar_exp IN_L identifier ", NULL, handle_xml_col, 0},
{L"xml_col_list  :  xml_col ", NULL, handle_xml_col_list, 0},
{L"xml_col_list  :  xml_col_list , xml_col ", NULL, handle_xml_col_list, 0},
{L"opt_xml_col_list  :  ( xml_col_list ) ", NULL, handle_opt_xml_col_list, 0},
{L"opt_pk  :   ", NULL, handle_opt_pk, 0},
{L"opt_pk  :  PRIMARY KEY ( column_commalist ) ", NULL, handle_opt_pk, 0},
{L"opt_join  :   ", NULL, handle_opt_join, 0},
{L"opt_join  :  ON ( search_condition ) ", NULL, handle_opt_join, 0},
{L"opt_elt  :   ", NULL, handle_opt_elt, 0},
{L"opt_elt  :  NAME ", NULL, handle_opt_elt, 0},
{L"xml_join_elt  :  q_table_name identifier opt_element opt_xml_col_list opt_join opt_pk opt_elt opt_xml_child ", NULL, handle_xml_join_elt, 0},
{L"opt_xml_child  :   ", NULL, handle_opt_xml_child, 0},
{L"opt_xml_child  :  BEGINX xml_join_list ENDX ", NULL, handle_opt_xml_child, 0},
{L"top_xml_child  :  query_spec ", NULL, handle_top_xml_child, 0},
{L"top_xml_child  :  BEGINX xml_join_list ENDX ", NULL, handle_top_xml_child, 0},
{L"xml_join_list  :  xml_join_elt ", NULL, handle_xml_join_list, 0},
{L"xml_join_list  :  xml_join_list , xml_join_elt ", NULL, handle_xml_join_list, 0},
{L"opt_persist  :   ", NULL, handle_opt_persist, 0},
{L"opt_persist  :  PERSISTENT ", NULL, handle_opt_persist, 0},
{L"opt_interval  :   ", NULL, handle_opt_interval, 0},
{L"opt_interval  :  INTERVAL INTNUM ", NULL, handle_opt_interval, 0},
{L"opt_metas  :   ", NULL, handle_opt_metas, 0},
{L"opt_metas  :  DTD INTERNAL ", NULL, handle_opt_metas, 0},
{L"opt_metas  :  DTD EXTERNAL ", NULL, handle_opt_metas, 0},
{L"opt_metas  :  DTD STRING ", NULL, handle_opt_metas, 0},
{L"opt_metas  :  SCHEMA EXTERNAL ", NULL, handle_opt_metas, 0},
{L"opt_metas  :  SCHEMA STRING ", NULL, handle_opt_metas, 0},
{L"opt_publish  :   ", NULL, handle_opt_publish, 0},
{L"opt_publish  :  PUBLIC STRING identifier STRING opt_persist opt_interval opt_metas ", NULL, handle_opt_publish, 0},
{L"xmlview_param_value  :  NAME ", NULL, handle_xmlview_param_value, 0},
{L"xmlview_param_value  :  STRING ", NULL, handle_xmlview_param_value, 0},
{L"xmlview_param  :  NAME COMPARISON xmlview_param_value ", NULL, handle_xmlview_param, 0},
{L"xmlview_params  :  xmlview_param ", NULL, handle_xmlview_params, 0},
{L"xmlview_params  :  xmlview_params xmlview_param ", NULL, handle_xmlview_params, 0},
{L"opt_xmlview_params  :   ", NULL, handle_opt_xmlview_params, 0},
{L"opt_xmlview_params  :  [ xmlview_params ] ", NULL, handle_opt_xmlview_params, 0},
{L"xml_view  :  CREATE XML VIEW new_table_name AS opt_xmlview_params top_xml_child opt_elt opt_publish ", NULL, handle_xml_view, 0},
{L"drop_xml_view  :  DROP XML VIEW q_table_name ", NULL, handle_drop_xml_view, 0},
{L"string_concatenation_operator  :  scalar_exp STRING_CONCAT_OPERATOR scalar_exp ", NULL, handle_string_concatenation_operator, 0},
{L"q_type_name  :  identifier ", NULL, handle_q_type_name, 0},
{L"q_type_name  :  identifier . identifier ", NULL, handle_q_type_name, 0},
{L"q_type_name  :  identifier . identifier . identifier ", NULL, handle_q_type_name, 0},
{L"q_type_name  :  identifier . . identifier ", NULL, handle_q_type_name, 0},
{L"q_old_type_name  :  identifier ", NULL, handle_q_old_type_name, 0},
{L"q_old_type_name  :  identifier . identifier ", NULL, handle_q_old_type_name, 0},
{L"q_old_type_name  :  identifier . identifier . identifier ", NULL, handle_q_old_type_name, 0},
{L"q_old_type_name  :  identifier . . identifier ", NULL, handle_q_old_type_name, 0},
{L"new_type_name  :  identifier ", NULL, handle_new_type_name, 0},
{L"new_type_name  :  identifier . identifier ", NULL, handle_new_type_name, 0},
{L"new_type_name  :  identifier . identifier . identifier ", NULL, handle_new_type_name, 0},
{L"new_type_name  :  identifier . . identifier ", NULL, handle_new_type_name, 0},
{L"empty6  :   ", NULL, handle_empty6, 0},
{L"user_defined_type  :  CREATE TYPE new_type_name opt_subtype_clause opt_external_and_language_clause empty6 opt_as_type_representation opt_type_option_list opt_method_specification_list ", NULL, handle_user_defined_type, 0},
{L"user_defined_type_drop  :  DROP TYPE q_old_type_name opt_drop_behavior ", NULL, handle_user_defined_type_drop, 0},
{L"opt_external_and_language_clause  :   ", NULL, handle_opt_external_and_language_clause, 0},
{L"opt_external_and_language_clause  :  LANGUAGE language_name EXTERNAL NAME_L STRING ", NULL, handle_opt_external_and_language_clause, 0},
{L"opt_external_and_language_clause  :  EXTERNAL NAME_L STRING LANGUAGE language_name ", NULL, handle_opt_external_and_language_clause, 0},
{L"opt_external_and_language_clause  :  LANGUAGE language_name ", NULL, handle_opt_external_and_language_clause, 0},
{L"opt_subtype_clause  :   ", NULL, handle_opt_subtype_clause, 0},
{L"opt_subtype_clause  :  UNDER q_type_name ", NULL, handle_opt_subtype_clause, 0},
{L"opt_as_type_representation  :   ", NULL, handle_opt_as_type_representation, 0},
{L"opt_as_type_representation  :  AS type_representation ", NULL, handle_opt_as_type_representation, 0},
{L"type_representation  :  ( type_member_list ) ", NULL, handle_type_representation, 0},
{L"type_member_list  :  type_member ", NULL, handle_type_member_list, 0},
{L"type_member_list  :  type_member_list , type_member ", NULL, handle_type_member_list, 0},
{L"opt_external_clause  :   ", NULL, handle_opt_external_clause, 0},
{L"opt_external_clause  :  EXTERNAL NAME_L STRING ", NULL, handle_opt_external_clause, 0},
{L"opt_external_clause  :  EXTERNAL NAME_L STRING EXTERNAL TYPE STRING ", NULL, handle_opt_external_clause, 0},
{L"opt_external_clause  :  EXTERNAL TYPE STRING ", NULL, handle_opt_external_clause, 0},
{L"opt_soap_clause  :   ", NULL, handle_opt_soap_clause, 0},
{L"opt_soap_clause  :  __SOAP_NAME STRING ", NULL, handle_opt_soap_clause, 0},
{L"opt_soap_clause  :  __SOAP_TYPE STRING ", NULL, handle_opt_soap_clause, 0},
{L"opt_soap_clause  :  __SOAP_TYPE STRING __SOAP_NAME STRING ", NULL, handle_opt_soap_clause, 0},
{L"opt_soap_clause  :  __SOAP_NAME STRING __SOAP_TYPE STRING ", NULL, handle_opt_soap_clause, 0},
{L"opt_external_type  :   ", NULL, handle_opt_external_type, 0},
{L"opt_external_type  :  EXTERNAL TYPE STRING ", NULL, handle_opt_external_type, 0},
{L"type_member  :  identifier data_type_ref opt_reference_scope_check opt_default_clause opt_collate_exp opt_external_clause opt_soap_clause ", NULL, handle_type_member, 0},
{L"opt_reference_scope_check  :   ", NULL, handle_opt_reference_scope_check, 0},
{L"opt_reference_scope_check  :  REFERENCES ARE CHECKED opt_on_delete_referential_rule ", NULL, handle_opt_reference_scope_check, 0},
{L"opt_reference_scope_check  :  REFERENCES ARE NOT CHECKED ", NULL, handle_opt_reference_scope_check, 0},
{L"opt_default_clause  :   ", NULL, handle_opt_default_clause, 0},
{L"opt_default_clause  :  DEFAULT signed_literal ", NULL, handle_opt_default_clause, 0},
{L"opt_type_option_list  :   ", NULL, handle_opt_type_option_list, 0},
{L"opt_type_option_list  :  type_option_list ", NULL, handle_opt_type_option_list, 0},
{L"type_option_list  :  type_option ", NULL, handle_type_option_list, 0},
{L"type_option_list  :  type_option_list type_option ", NULL, handle_type_option_list, 0},
{L"type_option  :  FINAL_L ", NULL, handle_type_option, 0},
{L"type_option  :  NOT FINAL_L ", NULL, handle_type_option, 0},
{L"type_option  :  REF USING data_type_ref ", NULL, handle_type_option, 0},
{L"type_option  :  REF FROM ( column_commalist ) ", NULL, handle_type_option, 0},
{L"type_option  :  REF IS SYSTEM GENERATED ", NULL, handle_type_option, 0},
{L"type_option  :  CAST ( SOURCE AS REF ) WITH identifier ", NULL, handle_type_option, 0},
{L"type_option  :  CAST ( REF AS SOURCE ) WITH identifier ", NULL, handle_type_option, 0},
{L"type_option  :  SELF_L AS REF ", NULL, handle_type_option, 0},
{L"type_option  :  TEMPORARY ", NULL, handle_type_option, 0},
{L"type_option  :  UNRESTRICTED ", NULL, handle_type_option, 0},
{L"type_option  :  __SOAP_TYPE STRING ", NULL, handle_type_option, 0},
{L"opt_method_specification_list  :   ", NULL, handle_opt_method_specification_list, 0},
{L"opt_method_specification_list  :  method_specification_list ", NULL, handle_opt_method_specification_list, 0},
{L"method_specification_list  :  method_specification ", NULL, handle_method_specification_list, 0},
{L"method_specification_list  :  method_specification_list , method_specification ", NULL, handle_method_specification_list, 0},
{L"method_type  :   ", NULL, handle_method_type, 0},
{L"method_type  :  STATIC_L ", NULL, handle_method_type, 0},
{L"method_type  :  INSTANCE_L ", NULL, handle_method_type, 0},
{L"decl_parameter_list  :  ( ) ", NULL, handle_decl_parameter_list, 0},
{L"decl_parameter_list  :  ( decl_parameter_commalist ) ", NULL, handle_decl_parameter_list, 0},
{L"decl_parameter_commalist  :  decl_parameter ", NULL, handle_decl_parameter_commalist, 0},
{L"decl_parameter_commalist  :  decl_parameter_commalist , decl_parameter ", NULL, handle_decl_parameter_commalist, 0},
{L"decl_parameter  :  opt_parameter_mode column_ref data_type_ref opt_external_type ", NULL, handle_decl_parameter, 0},
{L"partial_method_specification  :  method_type METHOD method_identifier decl_parameter_list RETURNS data_type_ref opt_specific_method_name ", NULL, handle_partial_method_specification, 0},
{L"partial_method_specification  :  CONSTRUCTOR METHOD method_identifier decl_parameter_list opt_specific_method_name ", NULL, handle_partial_method_specification, 0},
{L"method_specification  :  partial_method_specification opt_self_result opt_method_characteristics ", NULL, handle_method_specification, 0},
{L"method_specification  :  OVERRIDING partial_method_specification ", NULL, handle_method_specification, 0},
{L"opt_self_result  :   ", NULL, handle_opt_self_result, 0},
{L"opt_self_result  :  SELF_L AS RESULT ", NULL, handle_opt_self_result, 0},
{L"opt_self_result  :  SELF_L AS LOCATOR ", NULL, handle_opt_self_result, 0},
{L"opt_self_result  :  SELF_L AS RESULT SELF_L AS LOCATOR ", NULL, handle_opt_self_result, 0},
{L"opt_specific_method_name  :   ", NULL, handle_opt_specific_method_name, 0},
{L"opt_specific_method_name  :  SPECIFIC new_table_name ", NULL, handle_opt_specific_method_name, 0},
{L"opt_method_characteristics  :   ", NULL, handle_opt_method_characteristics, 0},
{L"opt_method_characteristics  :  method_characteristics ", NULL, handle_opt_method_characteristics, 0},
{L"method_characteristics  :  method_characteristic ", NULL, handle_method_characteristics, 0},
{L"method_characteristics  :  method_characteristics method_characteristic ", NULL, handle_method_characteristics, 0},
{L"method_characteristic  :  LANGUAGE language_name ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  PARAMETER STYLE SQL_L ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  PARAMETER STYLE GENERAL ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  DETERMINISTIC ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  NOT DETERMINISTIC ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  NO SQL_L ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  CONTAINS SQL_L ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  READS SQL_L DATA ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  MODIFIES SQL_L DATA ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  RETURNS NULLX ON NULLX INPUT ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  CALLED ON NULLX INPUT ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  EXTERNAL NAME_L STRING ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  EXTERNAL VARIABLE NAME_L STRING ", NULL, handle_method_characteristic, 0},
{L"method_characteristic  :  EXTERNAL TYPE STRING ", NULL, handle_method_characteristic, 0},
{L"external_language_name  :  ADA ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  C ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  COBOL ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  FORTRAN ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  MUMPS ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  PASCAL_L ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  PLI ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  JAVA ", NULL, handle_external_language_name, 0},
{L"external_language_name  :  CLR ", NULL, handle_external_language_name, 0},
{L"language_name  :  external_language_name ", NULL, handle_language_name, 0},
{L"language_name  :  SQL_L ", NULL, handle_language_name, 0},
{L"opt_constructor_return  :   ", NULL, handle_opt_constructor_return, 0},
{L"opt_constructor_return  :  RETURNS new_type_name ", NULL, handle_opt_constructor_return, 0},
{L"method_declaration  :  CREATE method_type METHOD method_identifier rout_parameter_list opt_return rout_alt_type FOR q_type_name compound_statement ", NULL, handle_method_declaration, 0},
{L"method_declaration  :  CREATE CONSTRUCTOR METHOD q_table_name rout_parameter_list opt_constructor_return FOR q_type_name compound_statement ", NULL, handle_method_declaration, 0},
{L"static_method_invocation  :  q_type_name DOUBLE_COLON method_identifier ( opt_arg_commalist ) ", NULL, handle_static_method_invocation, 0},
{L"identifier_chain  :  identifier . identifier . identifier . method_identifier ", NULL, handle_identifier_chain, 0},
{L"identifier_chain  :  identifier . . identifier . method_identifier ", NULL, handle_identifier_chain, 0},
{L"identifier_chain  :  identifier . identifier_chain ", NULL, handle_identifier_chain, 0},
{L"identifier_chain_method  :  identifier . identifier . identifier . identifier . method_identifier ", NULL, handle_identifier_chain_method, 0},
{L"identifier_chain_method  :  identifier . . identifier . identifier . method_identifier ", NULL, handle_identifier_chain_method, 0},
{L"identifier_chain_method  :  identifier . identifier_chain_method ", NULL, handle_identifier_chain_method, 0},
{L"method_invocation  :  scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ( opt_arg_commalist ) ", NULL, handle_method_invocation, 0},
{L"method_invocation  :  identifier_chain_method ( opt_arg_commalist ) ", NULL, handle_method_invocation, 0},
{L"method_invocation  :  ( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) ", NULL, handle_method_invocation, 0},
{L"method_invocation  :  ( column_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) ", NULL, handle_method_invocation, 0},
{L"top_level_method_invocation  :  METHOD CALL scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ( opt_arg_commalist ) ", NULL, handle_top_level_method_invocation, 0},
{L"top_level_method_invocation  :  METHOD CALL identifier_chain_method ( opt_arg_commalist ) ", NULL, handle_top_level_method_invocation, 0},
{L"top_level_method_invocation  :  METHOD CALL ( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) ", NULL, handle_top_level_method_invocation, 0},
{L"top_level_method_invocation  :  METHOD CALL ( column_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) ", NULL, handle_top_level_method_invocation, 0},
{L"member_observer  :  member_observer_no_id_chain ", NULL, handle_member_observer, 0},
{L"member_observer  :  identifier . identifier_chain ", NULL, handle_member_observer, 0},
{L"member_observer_no_id_chain  :  scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ", NULL, handle_member_observer_no_id_chain, 0},
{L"member_observer_no_id_chain  :  ( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ", NULL, handle_member_observer_no_id_chain, 0},
{L"member_observer_no_id_chain  :  ( column_ref AS q_type_name ) . method_identifier ", NULL, handle_member_observer_no_id_chain, 0},
{L"method_identifier  :  identifier ", NULL, handle_method_identifier, 0},
{L"method_identifier  :  EXTRACT ", NULL, handle_method_identifier, 0},
{L"new_invocation  :  NEW q_type_name ( opt_arg_commalist ) ", NULL, handle_new_invocation, 0},
{L"user_defined_type_alter  :  ALTER TYPE q_type_name alter_type_action ", NULL, handle_user_defined_type_alter, 0},
{L"alter_type_action  :  ADD ATTRIBUTE type_member ", NULL, handle_alter_type_action, 0},
{L"alter_type_action  :  DROP ATTRIBUTE identifier opt_drop_behavior ", NULL, handle_alter_type_action, 0},
{L"alter_type_action  :  ADD method_specification ", NULL, handle_alter_type_action, 0},
{L"alter_type_action  :  DROP partial_method_specification opt_drop_behavior ", NULL, handle_alter_type_action, 0},
{L"opt_with_permission_set  :   ", NULL, handle_opt_with_permission_set, 0},
{L"opt_with_permission_set  :  WITH PERMISSION_SET COMPARISON SAFE_L ", NULL, handle_opt_with_permission_set, 0},
{L"opt_with_permission_set  :  WITH PERMISSION_SET COMPARISON UNRESTRICTED ", NULL, handle_opt_with_permission_set, 0},
{L"opt_with_autoregister  :   ", NULL, handle_opt_with_autoregister, 0},
{L"opt_with_autoregister  :  WITH AUTOREGISTER_L ", NULL, handle_opt_with_autoregister, 0},
{L"create_library  :  CREATE LIBRARY_L q_table_name AS scalar_exp opt_with_permission_set opt_with_autoregister ", NULL, handle_create_library, 0},
{L"create_assembly  :  CREATE ASSEMBLY_L q_table_name FROM scalar_exp opt_with_permission_set opt_with_autoregister ", NULL, handle_create_assembly, 0},
{L"drop_library  :  DROP LIBRARY_L q_table_name ", NULL, handle_drop_library, 0},
{L"drop_assembly  :  DROP ASSEMBLY_L q_table_name ", NULL, handle_drop_assembly, 0}
};

#define __SQL_RULE_COUNT__ ((size_t)1116)
#define SQL_START_RULE L"sql_list"

static lex_t*	__sql_build_lex()													
{																				
		lex_t	*lex;															
		size_t i;																
		lex = Lex_Create();														
		for(i = 0; i < __SQL_NAME_COUNT__; ++i)										
		{																		
				if(!Lex_Insert(lex, __g_sql_lex_name[i]))							
				{																
						Lex_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		for(i = 0; i < __SQL_TERM_COUNT__; ++i)										
		{																		
				lexAction_t		act;											
				act.is_skip		=		__g_sql_term_pattern[i].skip;				
				act.priority	=		__g_sql_term_pattern[i].lex_prec;			
				act.value		=		__g_sql_term_pattern[i].tokval;				
				if(!Lex_InsertRule(lex, __g_sql_term_pattern[i].regex, &act))		
				{																
						Lex_Destroy(lex);										
						AR_ASSERT(false);										
						return NULL;											
				}																
		}																		
		return lex;																
}

static psrGrammar_t*	__sql_build_grammar(const psrHandler_t	*handler)															
{																																
		psrGrammar_t	*grammar;																								
		size_t i;																												
		AR_ASSERT(handler != NULL);																								
		grammar = Parser_CreateGrammar(handler);																				
		for(i = 0; i < __SQL_TERM_COUNT__; ++i)																						
		{																														
				if(__g_sql_term_pattern[i].skip || __g_sql_term_pattern[i].tokval == 0)continue;										
				if(!Parser_InsertTerm(grammar, __g_sql_term_pattern[i].name, __g_sql_term_pattern[i].tokval, PARSER_ASSOC_NONASSOC,0, __g_sql_term_pattern[i].leaf))	
				{																												
						Parser_DestroyGrammar(grammar);																			
						grammar = NULL;																							
						AR_ASSERT(false);																						
						return NULL;																							
				}																												
		}																														
		for(i = 0; i < __SQL_PREC_COUNT__; ++i)																						
		{																														
				psrTermInfo_t	*info;																							
				info = Parser_GetTermSymbInfoByName(grammar, __g_sql_prec_pattern[i].name);											
				if(info == NULL)																								
				{																												
						if(!Parser_InsertTerm(grammar, __g_sql_prec_pattern[i].name, __g_sql_prec_pattern[i].tokval, __g_sql_prec_pattern[i].assoc, __g_sql_prec_pattern[i].prec_level, NULL))
						{																																					
								Parser_DestroyGrammar(grammar);																												
								grammar = NULL;																																
								AR_ASSERT(false);																															
								return NULL;																																
						}																																					
				}else																																						
				{																																							
						info->assoc = __g_sql_prec_pattern[i].assoc;																											
						info->prec = __g_sql_prec_pattern[i].prec_level;																										
				}																																							
		}																																									
		for(i = 0; i < __SQL_RULE_COUNT__; ++i)																													
		{																																									
				if(!Parser_InsertRuleByStr(grammar, __g_sql_rule_pattern[i].rule, __g_sql_rule_pattern[i].prec_token, __g_sql_rule_pattern[i].handler, __g_sql_rule_pattern[i].auto_ret))		
				{																																							
						Parser_DestroyGrammar(grammar);																														
						grammar = NULL;																																		
						AR_ASSERT(false);																																	
						return NULL;																																		
				}																																							
		}																																									
		if(!Parser_SetStartRule(grammar,SQL_START_RULE))																			
		{																																									
				Parser_DestroyGrammar(grammar);																																
				grammar = NULL;																																				
				AR_ASSERT(false);																																			
				return NULL;																																				
		}																																									
		return grammar;																																						
}




/*sql_list	:	sql_list1 ; */
/*sql_list	:	sql_list1 */
static psrNode_t* AR_STDCALL handle_sql_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*sql_list1	:	sql */
static psrNode_t* AR_STDCALL handle_sql_list1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*sql	:	schema_element_list */
/*sql	:	view_def */
/*sql	:	xml_view */
/*sql	:	create_xml_schema */
/*sql	:	alter_constraint */
/*sql	:	create_library */
/*sql	:	create_assembly */
/*sql	:	drop_library */
/*sql	:	drop_assembly */
/*sql	:	user_aggregate_declaration */
/*sql	:	routine_declaration */
/*sql	:	module_declaration */
/*sql	:	method_declaration */
/*sql	:	trigger_def */
/*sql	:	drop_trigger */
/*sql	:	drop_proc */
/*sql	:	manipulative_statement */
/*sql	:	BEGIN_EQCALL_X q_table_name ENDX */
/*sql	:	BEGIN_EQCALL_X q_table_name ( opt_scalar_exp_commalist ) ENDX */
static psrNode_t* AR_STDCALL handle_sql(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*schema_element_list	:	schema_element */
/*schema_element_list	:	add_column */
/*schema_element_list	:	schema_element_list schema_element */
/*schema_element_list	:	schema_element_list add_column */
static psrNode_t* AR_STDCALL handle_schema_element_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*schema_element	:	base_table_def */
/*schema_element	:	create_index_def */
/*schema_element	:	drop_table */
/*schema_element	:	drop_index */
/*schema_element	:	table_rename */
/*schema_element	:	privilege_def */
/*schema_element	:	privilege_revoke */
/*schema_element	:	create_user_statement */
/*schema_element	:	delete_user_statement */
/*schema_element	:	set_pass */
/*schema_element	:	set_group_stmt */
/*schema_element	:	add_group_stmt */
/*schema_element	:	delete_group_stmt */
/*schema_element	:	user_defined_type */
/*schema_element	:	user_defined_type_drop */
/*schema_element	:	user_defined_type_alter */
static psrNode_t* AR_STDCALL handle_schema_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*identifier	:	NAME */
/*identifier	:	TYPE */
/*identifier	:	FINAL_L */
/*identifier	:	METHOD */
/*identifier	:	CHECKED */
/*identifier	:	SYSTEM */
/*identifier	:	GENERATED */
/*identifier	:	SOURCE */
/*identifier	:	RESULT */
/*identifier	:	LOCATOR */
/*identifier	:	INSTANCE_L */
/*identifier	:	CONSTRUCTOR */
/*identifier	:	SELF_L */
/*identifier	:	OVERRIDING */
/*identifier	:	STYLE */
/*identifier	:	SQL_L */
/*identifier	:	GENERAL */
/*identifier	:	DETERMINISTIC */
/*identifier	:	NO */
/*identifier	:	CONTAINS */
/*identifier	:	READS */
/*identifier	:	DATA */
/*identifier	:	MODIFIES */
/*identifier	:	INPUT */
/*identifier	:	CALLED */
/*identifier	:	ADA */
/*identifier	:	C */
/*identifier	:	COBOL */
/*identifier	:	FORTRAN */
/*identifier	:	MUMPS */
/*identifier	:	PASCAL_L */
/*identifier	:	PLI */
/*identifier	:	NAME_L */
/*identifier	:	TEXT_L */
/*identifier	:	JAVA */
/*identifier	:	INOUT_L */
/*identifier	:	REMOTE */
/*identifier	:	KEYSET */
/*identifier	:	VALUE */
/*identifier	:	PARAMETER */
/*identifier	:	VARIABLE */
/*identifier	:	CLR */
/*identifier	:	TEMPORARY */
/*identifier	:	ADMIN_L */
/*identifier	:	__SOAP_DOC */
/*identifier	:	__SOAP_DOCW */
/*identifier	:	__SOAP_HEADER */
/*identifier	:	__SOAP_HTTP */
/*identifier	:	__SOAP_NAME */
/*identifier	:	__SOAP_TYPE */
/*identifier	:	__SOAP_XML_TYPE */
/*identifier	:	__SOAP_FAULT */
/*identifier	:	__SOAP_DIME_ENC */
/*identifier	:	__SOAP_ENC_MIME */
/*identifier	:	__SOAP_OPTIONS */
/*identifier	:	START_L */
/*identifier	:	ATTRIBUTE */
/*identifier	:	REXECUTE */
/*identifier	:	PERMISSION_SET */
/*identifier	:	AUTOREGISTER_L */
/*identifier	:	LIBRARY_L */
/*identifier	:	ASSEMBLY_L */
/*identifier	:	SAFE_L */
/*identifier	:	UNRESTRICTED */
/*identifier	:	INCREMENT_L */
/*identifier	:	FOREACH */
static psrNode_t* AR_STDCALL handle_identifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*base_table_def	:	CREATE TABLE new_table_name ( base_table_element_commalist ) */
static psrNode_t* AR_STDCALL handle_base_table_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*base_table_element_commalist	:	base_table_element */
/*base_table_element_commalist	:	base_table_element_commalist , base_table_element */
static psrNode_t* AR_STDCALL handle_base_table_element_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*base_table_element	:	column_def */
/*base_table_element	:	table_constraint_def */
static psrNode_t* AR_STDCALL handle_base_table_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_def	:	column column_data_type column_def_opt_list */
static psrNode_t* AR_STDCALL handle_column_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_referential_triggered_action	:	 */
/*opt_referential_triggered_action	:	referential_rule */
/*opt_referential_triggered_action	:	referential_rule referential_rule */
static psrNode_t* AR_STDCALL handle_opt_referential_triggered_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*referential_rule	:	ON UPDATE referential_action */
/*referential_rule	:	delete_referential_rule */
static psrNode_t* AR_STDCALL handle_referential_rule(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*delete_referential_rule	:	ON DELETE_L referential_action */
static psrNode_t* AR_STDCALL handle_delete_referential_rule(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_on_delete_referential_rule	:	 */
/*opt_on_delete_referential_rule	:	delete_referential_rule */
static psrNode_t* AR_STDCALL handle_opt_on_delete_referential_rule(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*referential_action	:	CASCADE */
/*referential_action	:	SET NULLX */
/*referential_action	:	SET DEFAULT */
static psrNode_t* AR_STDCALL handle_referential_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*references	:	REFERENCES q_table_name opt_column_commalist opt_referential_triggered_action */
static psrNode_t* AR_STDCALL handle_references(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_def_opt_list	:	 */
/*column_def_opt_list	:	column_def_opt_list column_def_opt */
static psrNode_t* AR_STDCALL handle_column_def_opt_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*identity_opt	:	START_L WITH signed_literal */
/*identity_opt	:	INCREMENT_L BY INTNUM */
static psrNode_t* AR_STDCALL handle_identity_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*identity_opt_list	:	identity_opt */
/*identity_opt_list	:	identity_opt_list , identity_opt */
static psrNode_t* AR_STDCALL handle_identity_opt_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_def_opt	:	NOT NULLX */
/*column_def_opt	:	NULLX */
/*column_def_opt	:	IDENTITY */
/*column_def_opt	:	IDENTITY ( identity_opt_list ) */
/*column_def_opt	:	PRIMARY KEY */
/*column_def_opt	:	DEFAULT signed_literal */
/*column_def_opt	:	COLLATE q_table_name */
/*column_def_opt	:	references */
/*column_def_opt	:	IDENTIFIED BY column */
/*column_def_opt	:	CHECK ( search_condition ) */
/*column_def_opt	:	WITH SCHEMA column_xml_schema_def */
/*column_def_opt	:	UNIQUE */
static psrNode_t* AR_STDCALL handle_column_def_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_xml_schema_def	:	( STRING , STRING ) */
/*column_xml_schema_def	:	( STRING , STRING , STRING ) */
static psrNode_t* AR_STDCALL handle_column_xml_schema_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_constraint_def	:	UNDER q_table_name */
/*table_constraint_def	:	opt_constraint_name PRIMARY KEY ( index_column_commalist ) opt_index_option_list */
/*table_constraint_def	:	opt_constraint_name FOREIGN KEY ( column_commalist ) references */
/*table_constraint_def	:	opt_constraint_name CHECK ( search_condition ) */
/*table_constraint_def	:	opt_constraint_name UNIQUE ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_table_constraint_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_constraint_name	:	 */
/*opt_constraint_name	:	CONSTRAINT identifier */
static psrNode_t* AR_STDCALL handle_opt_constraint_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_commalist	:	column */
/*column_commalist	:	column_commalist , column */
static psrNode_t* AR_STDCALL handle_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*index_column_commalist	:	column opt_asc_desc */
/*index_column_commalist	:	index_column_commalist , column opt_asc_desc */
static psrNode_t* AR_STDCALL handle_index_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*index_option	:	CLUSTERED */
/*index_option	:	UNIQUE */
/*index_option	:	OBJECT_ID */
static psrNode_t* AR_STDCALL handle_index_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*index_option_list	:	index_option */
/*index_option_list	:	index_option_list index_option */
static psrNode_t* AR_STDCALL handle_index_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_index_option_list	:	 */
/*opt_index_option_list	:	index_option_list */
static psrNode_t* AR_STDCALL handle_opt_index_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_index_def	:	CREATE opt_index_option_list INDEX index ON new_table_name ( index_column_commalist ) */
static psrNode_t* AR_STDCALL handle_create_index_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_index	:	DROP INDEX identifier opt_table */
static psrNode_t* AR_STDCALL handle_drop_index(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_table	:	 */
/*opt_table	:	q_table_name */
static psrNode_t* AR_STDCALL handle_opt_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_table	:	DROP TABLE q_table_name */
/*drop_table	:	DROP VIEW q_table_name */
static psrNode_t* AR_STDCALL handle_drop_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_col_add_column	:	 */
/*opt_col_add_column	:	COLUMN */
static psrNode_t* AR_STDCALL handle_opt_col_add_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*add_col_column_def_list	:	column_def */
/*add_col_column_def_list	:	add_col_column_def_list , column_def */
static psrNode_t* AR_STDCALL handle_add_col_column_def_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*add_col_column_list	:	column */
/*add_col_column_list	:	add_col_column_list , column */
static psrNode_t* AR_STDCALL handle_add_col_column_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*add_column	:	ALTER TABLE q_table_name ADD opt_col_add_column add_col_column_def_list */
/*add_column	:	ALTER TABLE q_table_name DROP opt_col_add_column add_col_column_list */
/*add_column	:	ALTER TABLE q_table_name MODIFY opt_col_add_column column_def */
static psrNode_t* AR_STDCALL handle_add_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_rename	:	ALTER TABLE q_table_name RENAME new_table_name */
static psrNode_t* AR_STDCALL handle_table_rename(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*constraint_op	:	ADD */
/*constraint_op	:	DROP */
/*constraint_op	:	MODIFY */
static psrNode_t* AR_STDCALL handle_constraint_op(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_drop_behavior	:	 */
/*opt_drop_behavior	:	CASCADE */
/*opt_drop_behavior	:	RESTRICT */
static psrNode_t* AR_STDCALL handle_opt_drop_behavior(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_table_constraint_def	:	CONSTRAINT identifier opt_drop_behavior */
/*opt_table_constraint_def	:	table_constraint_def */
static psrNode_t* AR_STDCALL handle_opt_table_constraint_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*alter_constraint	:	ALTER TABLE q_table_name constraint_op opt_table_constraint_def */
static psrNode_t* AR_STDCALL handle_alter_constraint(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_xml_schema	:	CREATE XML SCHEMA STRING */
static psrNode_t* AR_STDCALL handle_create_xml_schema(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*view_query_spec	:	query_exp */
/*view_query_spec	:	query_no_from_spec */
static psrNode_t* AR_STDCALL handle_view_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*empty_1	:	 */
static psrNode_t* AR_STDCALL handle_empty_1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*view_def	:	CREATE VIEW new_table_name empty_1 opt_column_commalist AS view_query_spec opt_with_check_option */
/*view_def	:	CREATE PROCEDURE VIEW new_table_name AS q_table_name ( column_commalist_or_empty ) ( proc_col_list ) */
static psrNode_t* AR_STDCALL handle_view_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_check_option	:	 */
/*opt_with_check_option	:	WITH CHECK OPTION */
static psrNode_t* AR_STDCALL handle_opt_with_check_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_column_commalist	:	 */
/*opt_column_commalist	:	( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*priv_opt_column_commalist	:	 */
/*priv_opt_column_commalist	:	( column_commalist ) */
static psrNode_t* AR_STDCALL handle_priv_opt_column_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*privilege_def	:	GRANT ALL PRIVILEGES TO grantee */
/*privilege_def	:	GRANT privileges ON table TO grantee_commalist opt_with_grant_option */
/*privilege_def	:	GRANT EXECUTE ON function_name TO grantee_commalist opt_with_grant_option */
/*privilege_def	:	GRANT REXECUTE ON STRING TO grantee_commalist */
/*privilege_def	:	GRANT UNDER ON q_old_type_name TO grantee_commalist opt_with_grant_option */
/*privilege_def	:	GRANT grantee_commalist TO grantee_commalist opt_with_admin_option */
static psrNode_t* AR_STDCALL handle_privilege_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_admin_option	:	 */
/*opt_with_admin_option	:	WITH ADMIN_L OPTION */
static psrNode_t* AR_STDCALL handle_opt_with_admin_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*privilege_revoke	:	REVOKE privileges ON table FROM grantee_commalist */
/*privilege_revoke	:	REVOKE EXECUTE ON function_name FROM grantee_commalist */
/*privilege_revoke	:	REVOKE UNDER ON q_old_type_name FROM grantee_commalist */
/*privilege_revoke	:	REVOKE REXECUTE ON STRING FROM grantee_commalist */
/*privilege_revoke	:	REVOKE grantee_commalist FROM grantee_commalist */
static psrNode_t* AR_STDCALL handle_privilege_revoke(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_grant_option	:	 */
/*opt_with_grant_option	:	WITH GRANT OPTION */
static psrNode_t* AR_STDCALL handle_opt_with_grant_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*privileges	:	ALL PRIVILEGES */
/*privileges	:	ALL */
/*privileges	:	operation_commalist */
static psrNode_t* AR_STDCALL handle_privileges(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*operation_commalist	:	operation */
/*operation_commalist	:	operation_commalist , operation */
static psrNode_t* AR_STDCALL handle_operation_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*operation	:	SELECT priv_opt_column_commalist */
/*operation	:	INSERT */
/*operation	:	DELETE_L */
/*operation	:	UPDATE priv_opt_column_commalist */
/*operation	:	REFERENCES priv_opt_column_commalist */
static psrNode_t* AR_STDCALL handle_operation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*grantee_commalist	:	grantee */
/*grantee_commalist	:	grantee_commalist , grantee */
static psrNode_t* AR_STDCALL handle_grantee_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*grantee	:	PUBLIC */
/*grantee	:	user */
static psrNode_t* AR_STDCALL handle_grantee(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*set_pass	:	SET PASSWORD identifier identifier */
static psrNode_t* AR_STDCALL handle_set_pass(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_user_statement	:	CREATE USER user */
/*create_user_statement	:	CREATE ROLE_L user */
static psrNode_t* AR_STDCALL handle_create_user_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*delete_user_statement	:	DELETE_L USER user */
/*delete_user_statement	:	DELETE_L USER user CASCADE */
/*delete_user_statement	:	DROP USER user */
/*delete_user_statement	:	DROP USER user CASCADE */
/*delete_user_statement	:	DROP ROLE_L user */
static psrNode_t* AR_STDCALL handle_delete_user_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*set_group_stmt	:	SET USER GROUP user user */
static psrNode_t* AR_STDCALL handle_set_group_stmt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*add_group_stmt	:	ADD USER GROUP user user */
static psrNode_t* AR_STDCALL handle_add_group_stmt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*delete_group_stmt	:	DELETE_L USER GROUP user user */
static psrNode_t* AR_STDCALL handle_delete_group_stmt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_attach_primary_key	:	 */
/*opt_attach_primary_key	:	PRIMARY KEY ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_attach_primary_key(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*attach_table	:	ATTACH TABLE attach_q_table_name opt_attach_primary_key opt_as FROM literal opt_login opt_not_select opt_remote_name */
static psrNode_t* AR_STDCALL handle_attach_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_as	:	 */
/*opt_as	:	AS new_table_name */
static psrNode_t* AR_STDCALL handle_opt_as(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_login	:	 */
/*opt_login	:	USER scalar_exp PASSWORD scalar_exp */
static psrNode_t* AR_STDCALL handle_opt_login(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_not_select	:	 */
/*opt_not_select	:	NOT SELECT */
static psrNode_t* AR_STDCALL handle_opt_not_select(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_remote_name	:	 */
/*opt_remote_name	:	REMOTE AS scalar_exp */
static psrNode_t* AR_STDCALL handle_opt_remote_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cursor_type	:	STATIC_L */
/*cursor_type	:	DYNAMIC */
/*cursor_type	:	KEYSET */
static psrNode_t* AR_STDCALL handle_cursor_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cursor_def	:	DECLARE identifier CURSOR FOR query_exp */
/*cursor_def	:	DECLARE identifier cursor_type CURSOR FOR query_exp */
static psrNode_t* AR_STDCALL handle_cursor_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_order_by_clause	:	 */
/*opt_order_by_clause	:	ORDER BY ordering_spec_commalist */
static psrNode_t* AR_STDCALL handle_opt_order_by_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ordering_spec_commalist	:	ordering_spec */
/*ordering_spec_commalist	:	ordering_spec_commalist , ordering_spec */
static psrNode_t* AR_STDCALL handle_ordering_spec_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*ordering_spec	:	scalar_exp opt_asc_desc */
/*ordering_spec	:	mssql_xml_col opt_asc_desc */
static psrNode_t* AR_STDCALL handle_ordering_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_asc_desc	:	 */
/*opt_asc_desc	:	ASC */
/*opt_asc_desc	:	DESC */
static psrNode_t* AR_STDCALL handle_opt_asc_desc(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_snapshot_log	:	CREATE SNAPSHOT LOGX FOR q_table_name */
static psrNode_t* AR_STDCALL handle_create_snapshot_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_snapshot_log	:	DROP SNAPSHOT LOGX FOR q_table_name */
static psrNode_t* AR_STDCALL handle_drop_snapshot_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*purge_snapshot_log	:	PURGE SNAPSHOT LOGX FOR q_table_name */
static psrNode_t* AR_STDCALL handle_purge_snapshot_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_snapshot_string_literal	:	 */
/*opt_snapshot_string_literal	:	STRING */
static psrNode_t* AR_STDCALL handle_opt_snapshot_string_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_snapshot_where_clause	:	 */
/*opt_snapshot_where_clause	:	WHERE STRING */
static psrNode_t* AR_STDCALL handle_opt_snapshot_where_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_snapshot	:	CREATE SNAPSHOT q_table_name FROM q_table_name opt_snapshot_string_literal opt_snapshot_where_clause */
/*create_snapshot	:	CREATE NONINCREMENTAL SNAPSHOT q_table_name AS STRING */
static psrNode_t* AR_STDCALL handle_create_snapshot(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_delete	:	 */
/*opt_with_delete	:	WITH DELETE_L */
static psrNode_t* AR_STDCALL handle_opt_with_delete(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_snapshot	:	DROP SNAPSHOT q_table_name opt_with_delete */
static psrNode_t* AR_STDCALL handle_drop_snapshot(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_nonincremental	:	 */
/*opt_nonincremental	:	AS NONINCREMENTAL */
static psrNode_t* AR_STDCALL handle_opt_nonincremental(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*refresh_snapshot	:	UPDATE SNAPSHOT q_table_name opt_nonincremental */
static psrNode_t* AR_STDCALL handle_refresh_snapshot(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_freetext_index	:	CREATE TEXT_L opt_xml INDEX ON q_table_name ( column ) opt_with_key opt_deffer_generation opt_with opt_data_modification_action opt_lang opt_enc */
static psrNode_t* AR_STDCALL handle_create_freetext_index(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_data_modification_action	:	 */
/*opt_data_modification_action	:	USING FUNCTION */
static psrNode_t* AR_STDCALL handle_opt_data_modification_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_column	:	 */
/*opt_column	:	( column ) */
static psrNode_t* AR_STDCALL handle_opt_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_freetext_trigger	:	CREATE TEXT_L TRIGGER ON q_table_name opt_column */
static psrNode_t* AR_STDCALL handle_create_freetext_trigger(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_freetext_trigger	:	DROP TEXT_L TRIGGER ON q_table_name opt_column */
static psrNode_t* AR_STDCALL handle_drop_freetext_trigger(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_xml	:	 */
/*opt_xml	:	XML */
static psrNode_t* AR_STDCALL handle_opt_xml(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_key	:	 */
/*opt_with_key	:	WITH KEY column */
static psrNode_t* AR_STDCALL handle_opt_with_key(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with	:	 */
/*opt_with	:	CLUSTERED WITH ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_with(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_lang	:	 */
/*opt_lang	:	LANGUAGE STRING */
static psrNode_t* AR_STDCALL handle_opt_lang(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_enc	:	 */
/*opt_enc	:	ENCODING STRING */
static psrNode_t* AR_STDCALL handle_opt_enc(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_deffer_generation	:	 */
/*opt_deffer_generation	:	NOT INSERT */
static psrNode_t* AR_STDCALL handle_opt_deffer_generation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*manipulative_statement	:	query_exp */
/*manipulative_statement	:	query_no_from_spec */
/*manipulative_statement	:	update_statement_positioned */
/*manipulative_statement	:	update_statement_searched */
/*manipulative_statement	:	insert_statement */
/*manipulative_statement	:	delete_statement_positioned */
/*manipulative_statement	:	delete_statement_searched */
/*manipulative_statement	:	call_statement */
/*manipulative_statement	:	static_method_invocation */
/*manipulative_statement	:	METHOD CALL static_method_invocation */
/*manipulative_statement	:	top_level_method_invocation */
/*manipulative_statement	:	set_statement */
/*manipulative_statement	:	drop_xml_view */
/*manipulative_statement	:	commit_statement */
/*manipulative_statement	:	rollback_statement */
/*manipulative_statement	:	admin_statement */
/*manipulative_statement	:	use_statement */
/*manipulative_statement	:	attach_table */
/*manipulative_statement	:	create_snapshot_log */
/*manipulative_statement	:	drop_snapshot_log */
/*manipulative_statement	:	purge_snapshot_log */
/*manipulative_statement	:	create_snapshot */
/*manipulative_statement	:	drop_snapshot */
/*manipulative_statement	:	refresh_snapshot */
/*manipulative_statement	:	create_freetext_index */
/*manipulative_statement	:	create_freetext_trigger */
/*manipulative_statement	:	drop_freetext_trigger */
static psrNode_t* AR_STDCALL handle_manipulative_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*use_statement	:	USE identifier */
static psrNode_t* AR_STDCALL handle_use_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*close_statement	:	CLOSE cursor */
static psrNode_t* AR_STDCALL handle_close_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*commit_statement	:	COMMIT WORK */
static psrNode_t* AR_STDCALL handle_commit_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*delete_statement_positioned	:	DELETE_L FROM table WHERE CURRENT OF cursor */
static psrNode_t* AR_STDCALL handle_delete_statement_positioned(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*delete_statement_searched	:	DELETE_L FROM table opt_where_clause */
static psrNode_t* AR_STDCALL handle_delete_statement_searched(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*fetch_statement	:	FETCH cursor INTO target_commalist */
/*fetch_statement	:	FETCH cursor NAME INTO target_commalist */
/*fetch_statement	:	FETCH cursor NAME scalar_exp INTO target_commalist */
static psrNode_t* AR_STDCALL handle_fetch_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*insert_mode	:	INTO */
/*insert_mode	:	REPLACING */
/*insert_mode	:	SOFT */
static psrNode_t* AR_STDCALL handle_insert_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*insert_statement	:	INSERT insert_mode table priv_opt_column_commalist values_or_query_spec */
static psrNode_t* AR_STDCALL handle_insert_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*values_or_query_spec	:	VALUES ( insert_atom_commalist ) */
/*values_or_query_spec	:	query_spec */
static psrNode_t* AR_STDCALL handle_values_or_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*insert_atom_commalist	:	insert_atom */
/*insert_atom_commalist	:	insert_atom_commalist , insert_atom */
static psrNode_t* AR_STDCALL handle_insert_atom_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*insert_atom	:	scalar_exp */
static psrNode_t* AR_STDCALL handle_insert_atom(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*sql_option	:	ORDER */
/*sql_option	:	HASH */
/*sql_option	:	LOOP */
/*sql_option	:	INDEX identifier */
/*sql_option	:	INDEX PRIMARY KEY */
/*sql_option	:	INDEX TEXT_L KEY */
/*sql_option	:	NAME INTNUM */
static psrNode_t* AR_STDCALL handle_sql_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*sql_opt_commalist	:	sql_option */
/*sql_opt_commalist	:	sql_opt_commalist , sql_option */
static psrNode_t* AR_STDCALL handle_sql_opt_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_sql_opt	:	 */
/*opt_sql_opt	:	OPTION ( sql_opt_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_sql_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_table_opt	:	 */
/*opt_table_opt	:	TABLE OPTION ( sql_opt_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_table_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cursor_option	:	EXCLUSIVE */
/*cursor_option	:	PREFETCH INTNUM */
static psrNode_t* AR_STDCALL handle_cursor_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cursor_options_commalist	:	cursor_option */
/*cursor_options_commalist	:	cursor_options_commalist , cursor_option */
static psrNode_t* AR_STDCALL handle_cursor_options_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_cursor_options_list	:	 */
/*opt_cursor_options_list	:	( cursor_options_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_cursor_options_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*open_statement	:	OPEN cursor opt_cursor_options_list */
static psrNode_t* AR_STDCALL handle_open_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*rollback_statement	:	ROLLBACK WORK */
static psrNode_t* AR_STDCALL handle_rollback_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*with_opt_cursor_options_list	:	 */
/*with_opt_cursor_options_list	:	WITH opt_cursor_options_list */
static psrNode_t* AR_STDCALL handle_with_opt_cursor_options_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*select_statement	:	SELECT opt_top selection INTO target_commalist table_exp with_opt_cursor_options_list */
static psrNode_t* AR_STDCALL handle_select_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_all_distinct	:	 */
/*opt_all_distinct	:	ALL */
/*opt_all_distinct	:	DISTINCT */
static psrNode_t* AR_STDCALL handle_opt_all_distinct(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_ties	:	 */
/*opt_ties	:	WITH TIES */
static psrNode_t* AR_STDCALL handle_opt_ties(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_top	:	opt_all_distinct */
/*opt_top	:	opt_all_distinct TOP INTNUM opt_ties */
/*opt_top	:	opt_all_distinct TOP ( scalar_exp ) opt_ties */
/*opt_top	:	opt_all_distinct TOP INTNUM , INTNUM opt_ties */
/*opt_top	:	opt_all_distinct TOP ( scalar_exp , scalar_exp ) opt_ties */
static psrNode_t* AR_STDCALL handle_opt_top(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*update_statement_positioned	:	UPDATE table SET assignment_commalist WHERE CURRENT OF cursor */
static psrNode_t* AR_STDCALL handle_update_statement_positioned(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*assignment_commalist	:	 */
/*assignment_commalist	:	assignment */
/*assignment_commalist	:	assignment_commalist , assignment */
static psrNode_t* AR_STDCALL handle_assignment_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*assignment	:	column COMPARISON scalar_exp */
static psrNode_t* AR_STDCALL handle_assignment(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*update_statement_searched	:	UPDATE table SET assignment_commalist opt_where_clause */
static psrNode_t* AR_STDCALL handle_update_statement_searched(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*target_commalist	:	target */
/*target_commalist	:	target_commalist , target */
static psrNode_t* AR_STDCALL handle_target_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*target	:	column_ref */
/*target	:	member_observer */
/*target	:	lvalue_array_ref */
static psrNode_t* AR_STDCALL handle_target(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_where_clause	:	 */
/*opt_where_clause	:	where_clause */
static psrNode_t* AR_STDCALL handle_opt_where_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_best	:	 */
/*opt_best	:	BEST */
static psrNode_t* AR_STDCALL handle_opt_best(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*query_exp	:	query_term */
/*query_exp	:	non_final_union_exp opt_best UNION opt_corresponding query_term */
/*query_exp	:	non_final_union_exp opt_best UNION ALL opt_corresponding query_term */
/*query_exp	:	non_final_union_exp INTERSECT opt_corresponding query_term */
/*query_exp	:	non_final_union_exp INTERSECT ALL opt_corresponding query_term */
/*query_exp	:	non_final_union_exp EXCEPT opt_corresponding query_term */
/*query_exp	:	non_final_union_exp EXCEPT ALL opt_corresponding query_term */
static psrNode_t* AR_STDCALL handle_query_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*non_final_union_exp	:	non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp opt_best UNION opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp opt_best UNION ALL opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp INTERSECT opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp INTERSECT ALL opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp EXCEPT opt_corresponding non_final_query_term */
/*non_final_union_exp	:	non_final_union_exp EXCEPT ALL opt_corresponding non_final_query_term */
static psrNode_t* AR_STDCALL handle_non_final_union_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*non_final_query_term	:	non_final_query_spec */
/*non_final_query_term	:	XPATH STRING */
static psrNode_t* AR_STDCALL handle_non_final_query_term(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*query_term	:	query_spec */
/*query_term	:	( query_exp ) opt_order_by_clause */
/*query_term	:	XPATH STRING */
static psrNode_t* AR_STDCALL handle_query_term(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_corresponding	:	 */
/*opt_corresponding	:	CORRESPONDING BY ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_corresponding(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*non_final_query_spec	:	SELECT opt_top selection non_final_table_exp */
static psrNode_t* AR_STDCALL handle_non_final_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*query_spec	:	SELECT opt_top selection table_exp */
static psrNode_t* AR_STDCALL handle_query_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*query_no_from_spec	:	SELECT opt_top selection */
static psrNode_t* AR_STDCALL handle_query_no_from_spec(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*selection	:	select_scalar_exp_commalist */
static psrNode_t* AR_STDCALL handle_selection(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*non_final_table_exp	:	from_clause opt_where_clause opt_group_by_clause opt_having_clause */
static psrNode_t* AR_STDCALL handle_non_final_table_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_exp	:	from_clause opt_where_clause opt_group_by_clause opt_having_clause opt_order_by_clause opt_lock_mode opt_sql_opt */
static psrNode_t* AR_STDCALL handle_table_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*from_clause	:	FROM table_ref_commalist */
static psrNode_t* AR_STDCALL handle_from_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_ref_commalist	:	table_ref */
/*table_ref_commalist	:	table_ref_commalist , table_ref */
static psrNode_t* AR_STDCALL handle_table_ref_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*proc_col_list	:	column_def */
/*proc_col_list	:	proc_col_list , column_def */
static psrNode_t* AR_STDCALL handle_proc_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_proc_col_list	:	( proc_col_list ) */
static psrNode_t* AR_STDCALL handle_opt_proc_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_commalist_or_empty	:	 */
/*column_commalist_or_empty	:	column_commalist */
static psrNode_t* AR_STDCALL handle_column_commalist_or_empty(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_ref	:	table */
/*table_ref	:	( query_exp ) identifier */
/*table_ref	:	( query_exp ) AS identifier */
/*table_ref	:	joined_table */
/*table_ref	:	q_table_name ( column_commalist_or_empty ) opt_proc_col_list identifier */
static psrNode_t* AR_STDCALL handle_table_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table_ref_nj	:	table */
/*table_ref_nj	:	subquery identifier */
/*table_ref_nj	:	subquery AS identifier */
/*table_ref_nj	:	( joined_table ) */
static psrNode_t* AR_STDCALL handle_table_ref_nj(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*jtype	:	 */
/*jtype	:	LEFT opt_outer */
/*jtype	:	RIGHT opt_outer */
/*jtype	:	FULL opt_outer */
/*jtype	:	INNER */
/*jtype	:	CROSS */
static psrNode_t* AR_STDCALL handle_jtype(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_outer	:	 */
/*opt_outer	:	OUTER */
static psrNode_t* AR_STDCALL handle_opt_outer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*join	:	NATURAL jtype */
/*join	:	jtype */
static psrNode_t* AR_STDCALL handle_join(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*joined_table	:	joined_table_1 */
/*joined_table	:	BEGIN_OJ_X joined_table_1 ENDX */
/*joined_table	:	( joined_table_1 ) */
static psrNode_t* AR_STDCALL handle_joined_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*joined_table_1	:	table_ref join JOIN table_ref_nj join_condition */
static psrNode_t* AR_STDCALL handle_joined_table_1(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*join_condition	:	 */
/*join_condition	:	ON search_condition */
/*join_condition	:	USING ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_join_condition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*where_clause	:	WHERE search_condition */
static psrNode_t* AR_STDCALL handle_where_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_group_by_clause	:	 */
/*opt_group_by_clause	:	GROUP BY ordering_spec_commalist */
/*opt_group_by_clause	:	GROUP BY ROLLUP ( ordering_spec_commalist ) */
/*opt_group_by_clause	:	GROUP BY CUBE ( ordering_spec_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_group_by_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_having_clause	:	 */
/*opt_having_clause	:	HAVING search_condition */
static psrNode_t* AR_STDCALL handle_opt_having_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_lock_mode	:	 */
/*opt_lock_mode	:	FOR UPDATE */
/*opt_lock_mode	:	FOR XML NAME */
/*opt_lock_mode	:	FOR XML NAME NAME */
static psrNode_t* AR_STDCALL handle_opt_lock_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*search_condition	:	search_condition OR search_condition */
/*search_condition	:	search_condition AND search_condition */
/*search_condition	:	NOT search_condition */
/*search_condition	:	( search_condition ) */
/*search_condition	:	predicate */
static psrNode_t* AR_STDCALL handle_search_condition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*predicate	:	comparison_predicate */
/*predicate	:	between_predicate */
/*predicate	:	like_predicate */
/*predicate	:	test_for_null */
/*predicate	:	in_predicate */
/*predicate	:	all_or_any_predicate */
/*predicate	:	existence_test */
/*predicate	:	scalar_exp_predicate */
static psrNode_t* AR_STDCALL handle_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*scalar_exp_predicate	:	scalar_exp */
static psrNode_t* AR_STDCALL handle_scalar_exp_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*comparison_predicate	:	scalar_exp COMPARISON scalar_exp */
static psrNode_t* AR_STDCALL handle_comparison_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*between_predicate	:	scalar_exp NOT BETWEEN scalar_exp AND scalar_exp */
/*between_predicate	:	scalar_exp BETWEEN scalar_exp AND scalar_exp */
static psrNode_t* AR_STDCALL handle_between_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*like_predicate	:	scalar_exp NOT LIKE scalar_exp opt_escape */
/*like_predicate	:	scalar_exp LIKE scalar_exp opt_escape */
static psrNode_t* AR_STDCALL handle_like_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_escape	:	 */
/*opt_escape	:	ESCAPE atom */
/*opt_escape	:	BEGINX ESCAPE atom ENDX */
static psrNode_t* AR_STDCALL handle_opt_escape(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*test_for_null	:	scalar_exp IS NOT NULLX */
/*test_for_null	:	scalar_exp IS NULLX */
static psrNode_t* AR_STDCALL handle_test_for_null(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*in_predicate	:	scalar_exp NOT IN_L subquery */
/*in_predicate	:	scalar_exp IN_L subquery */
/*in_predicate	:	scalar_exp NOT IN_L ( scalar_exp_commalist ) */
/*in_predicate	:	scalar_exp IN_L ( scalar_exp_commalist ) */
static psrNode_t* AR_STDCALL handle_in_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*all_or_any_predicate	:	scalar_exp COMPARISON any_all_some subquery */
static psrNode_t* AR_STDCALL handle_all_or_any_predicate(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*any_all_some	:	ANY */
/*any_all_some	:	ALL */
/*any_all_some	:	SOME */
static psrNode_t* AR_STDCALL handle_any_all_some(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*existence_test	:	EXISTS subquery */
static psrNode_t* AR_STDCALL handle_existence_test(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*scalar_subquery	:	subquery */
static psrNode_t* AR_STDCALL handle_scalar_subquery(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*subquery	:	( SELECT opt_top selection table_exp ) */
static psrNode_t* AR_STDCALL handle_subquery(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*scalar_exp	:	scalar_exp - scalar_exp */
/*scalar_exp	:	scalar_exp + scalar_exp */
/*scalar_exp	:	scalar_exp * scalar_exp */
/*scalar_exp	:	scalar_exp / scalar_exp */
/*scalar_exp	:	+ scalar_exp */
/*scalar_exp	:	- scalar_exp */
/*scalar_exp	:	assignment_statement */
/*scalar_exp	:	string_concatenation_operator */
/*scalar_exp	:	column_ref */
/*scalar_exp	:	scalar_exp_no_col_ref */
/*scalar_exp	:	obe_literal */
static psrNode_t* AR_STDCALL handle_scalar_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*scalar_exp_no_col_ref	:	atom_no_obe */
/*scalar_exp_no_col_ref	:	aggregate_ref */
/*scalar_exp_no_col_ref	:	scalar_subquery */
/*scalar_exp_no_col_ref	:	( scalar_exp ) */
/*scalar_exp_no_col_ref	:	( scalar_exp , scalar_exp_commalist ) */
/*scalar_exp_no_col_ref	:	function_call */
/*scalar_exp_no_col_ref	:	new_invocation */
/*scalar_exp_no_col_ref	:	cvt_exp */
/*scalar_exp_no_col_ref	:	cast_exp */
/*scalar_exp_no_col_ref	:	simple_case */
/*scalar_exp_no_col_ref	:	searched_case */
/*scalar_exp_no_col_ref	:	coalesce_exp */
/*scalar_exp_no_col_ref	:	nullif_exp */
/*scalar_exp_no_col_ref	:	array_ref */
/*scalar_exp_no_col_ref	:	static_method_invocation */
/*scalar_exp_no_col_ref	:	method_invocation */
/*scalar_exp_no_col_ref	:	member_observer */
static psrNode_t* AR_STDCALL handle_scalar_exp_no_col_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*scalar_exp_no_col_ref_no_mem_obs_chain	:	atom_no_obe */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	aggregate_ref */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	scalar_subquery */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	( scalar_exp ) */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	( scalar_exp , scalar_exp_commalist ) */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	function_call */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	new_invocation */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	cvt_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	cast_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	simple_case */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	searched_case */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	coalesce_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	nullif_exp */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	array_ref */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	static_method_invocation */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	method_invocation */
/*scalar_exp_no_col_ref_no_mem_obs_chain	:	member_observer_no_id_chain */
static psrNode_t* AR_STDCALL handle_scalar_exp_no_col_ref_no_mem_obs_chain(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cvt_exp	:	CONVERT ( data_type , scalar_exp ) */
static psrNode_t* AR_STDCALL handle_cvt_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_collate_exp	:	 */
/*opt_collate_exp	:	COLLATE q_table_name */
static psrNode_t* AR_STDCALL handle_opt_collate_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cast_exp	:	CAST ( scalar_exp AS data_type opt_collate_exp ) */
static psrNode_t* AR_STDCALL handle_cast_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*mssql_xml_col	:	MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAMEZ */
/*mssql_xml_col	:	MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAMEYZ */
/*mssql_xml_col	:	MSSQL_XMLCOL_NAME1 MSSQL_XMLCOL_INTNUM MSSQL_XMLCOL_NAME MSSQL_XMLCOL_NAMEZ */
static psrNode_t* AR_STDCALL handle_mssql_xml_col(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*as_expression	:	scalar_exp AS identifier data_type */
/*as_expression	:	scalar_exp AS identifier */
/*as_expression	:	scalar_exp identifier */
/*as_expression	:	scalar_exp AS mssql_xml_col */
static psrNode_t* AR_STDCALL handle_as_expression(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*array_ref	:	scalar_exp_no_col_ref [ scalar_exp ] */
/*array_ref	:	lvalue_array_ref */
static psrNode_t* AR_STDCALL handle_array_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*lvalue_array_ref	:	column_ref [ scalar_exp ] */
static psrNode_t* AR_STDCALL handle_lvalue_array_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_scalar_exp_commalist	:	 */
/*opt_scalar_exp_commalist	:	scalar_exp_commalist */
static psrNode_t* AR_STDCALL handle_opt_scalar_exp_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*function_name	:	identifier */
/*function_name	:	identifier . method_identifier */
/*function_name	:	identifier . identifier . method_identifier */
/*function_name	:	identifier . identifier . identifier . method_identifier */
/*function_name	:	identifier . . method_identifier */
/*function_name	:	identifier . . identifier . method_identifier */
/*function_name	:	LEFT */
/*function_name	:	RIGHT */
/*function_name	:	LOGX */
static psrNode_t* AR_STDCALL handle_function_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*kwd_commalist	:	identifier KWD_TAG scalar_exp */
/*kwd_commalist	:	kwd_commalist , identifier KWD_TAG scalar_exp */
static psrNode_t* AR_STDCALL handle_kwd_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*as_commalist	:	as_expression */
/*as_commalist	:	as_commalist , as_expression */
/*as_commalist	:	as_commalist , scalar_exp */
static psrNode_t* AR_STDCALL handle_as_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_arg_commalist	:	 */
/*opt_arg_commalist	:	kwd_commalist */
/*opt_arg_commalist	:	scalar_exp_commalist */
/*opt_arg_commalist	:	scalar_exp_commalist , kwd_commalist */
/*opt_arg_commalist	:	scalar_exp_commalist , as_commalist */
/*opt_arg_commalist	:	as_commalist */
static psrNode_t* AR_STDCALL handle_opt_arg_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*function_call	:	function_name ( opt_arg_commalist ) */
/*function_call	:	TIMESTAMP_FUNC ( SQL_TSI , scalar_exp , scalar_exp ) */
/*function_call	:	EXTRACT ( NAME FROM scalar_exp ) */
/*function_call	:	BEGIN_FN_X identifier ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X LEFT ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X RIGHT ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X LOGX ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X identifier ( scalar_exp IN_L scalar_exp ) ENDX */
/*function_call	:	BEGIN_CALL_X function_name ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_CALL_X function_name ENDX */
/*function_call	:	BEGIN_FN_X USER ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X CHARACTER ( opt_scalar_exp_commalist ) ENDX */
/*function_call	:	BEGIN_FN_X TIMESTAMP_FUNC ( SQL_TSI , scalar_exp , scalar_exp ) ENDX */
/*function_call	:	BEGIN_FN_X CONVERT ( scalar_exp , NAME ) ENDX */
/*function_call	:	BEGIN_FN_X EXTRACT ( NAME FROM scalar_exp ) ENDX */
/*function_call	:	CALL ( scalar_exp ) ( opt_arg_commalist ) */
/*function_call	:	CURRENT_DATE */
/*function_call	:	CURRENT_TIME */
/*function_call	:	CURRENT_TIME ( scalar_exp ) */
/*function_call	:	CURRENT_TIMESTAMP */
/*function_call	:	CURRENT_TIMESTAMP ( scalar_exp ) */
/*function_call	:	GROUPING ( column_ref ) */
static psrNode_t* AR_STDCALL handle_function_call(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*obe_literal	:	BEGINX identifier atom ENDX */
/*obe_literal	:	BEGIN_U_X STRING ENDX */
static psrNode_t* AR_STDCALL handle_obe_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*scalar_exp_commalist	:	scalar_exp */
/*scalar_exp_commalist	:	scalar_exp_commalist , scalar_exp */
static psrNode_t* AR_STDCALL handle_scalar_exp_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*select_scalar_exp_commalist	:	scalar_exp */
/*select_scalar_exp_commalist	:	as_expression */
/*select_scalar_exp_commalist	:	select_scalar_exp_commalist , scalar_exp */
/*select_scalar_exp_commalist	:	select_scalar_exp_commalist , as_expression */
static psrNode_t* AR_STDCALL handle_select_scalar_exp_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*atom_no_obe	:	parameter_ref */
/*atom_no_obe	:	literal */
/*atom_no_obe	:	USER */
static psrNode_t* AR_STDCALL handle_atom_no_obe(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*atom	:	atom_no_obe */
/*atom	:	obe_literal */
static psrNode_t* AR_STDCALL handle_atom(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*simple_case	:	CASE scalar_exp simple_when_list ENDX */
static psrNode_t* AR_STDCALL handle_simple_case(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*searched_case	:	CASE searched_when_list ENDX */
static psrNode_t* AR_STDCALL handle_searched_case(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*searched_when_list	:	searched_when */
/*searched_when_list	:	searched_when_list searched_when */
static psrNode_t* AR_STDCALL handle_searched_when_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*simple_when_list	:	simple_when */
/*simple_when_list	:	simple_when_list simple_when */
static psrNode_t* AR_STDCALL handle_simple_when_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*simple_when	:	WHEN scalar_exp THEN scalar_exp */
/*simple_when	:	ELSE scalar_exp */
static psrNode_t* AR_STDCALL handle_simple_when(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*searched_when	:	WHEN search_condition THEN scalar_exp */
/*searched_when	:	ELSE scalar_exp */
static psrNode_t* AR_STDCALL handle_searched_when(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*coalesce_exp	:	COALESCE ( scalar_exp_commalist ) */
static psrNode_t* AR_STDCALL handle_coalesce_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*nullif_exp	:	NULLIF ( scalar_exp , scalar_exp ) */
static psrNode_t* AR_STDCALL handle_nullif_exp(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*parameter_ref	:	parameter */
/*parameter_ref	:	parameter parameter */
/*parameter_ref	:	parameter INDICATOR parameter */
static psrNode_t* AR_STDCALL handle_parameter_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*aggregate_ref	:	AGGREGATE function_name ( opt_arg_commalist ) */
/*aggregate_ref	:	AMMSC ( DISTINCT scalar_exp ) */
/*aggregate_ref	:	AMMSC ( ALL scalar_exp ) */
/*aggregate_ref	:	AMMSC ( scalar_exp ) */
static psrNode_t* AR_STDCALL handle_aggregate_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*literal	:	STRING */
/*literal	:	WSTRING */
/*literal	:	INTNUM */
/*literal	:	APPROXNUM */
/*literal	:	BINARYNUM */
/*literal	:	NULLX */
static psrNode_t* AR_STDCALL handle_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*signed_literal	:	STRING */
/*signed_literal	:	WSTRING */
/*signed_literal	:	INTNUM */
/*signed_literal	:	- INTNUM */
/*signed_literal	:	+ INTNUM */
/*signed_literal	:	APPROXNUM */
/*signed_literal	:	- APPROXNUM */
/*signed_literal	:	+ APPROXNUM */
/*signed_literal	:	BINARYNUM */
/*signed_literal	:	NULLX */
static psrNode_t* AR_STDCALL handle_signed_literal(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*q_table_name	:	identifier */
/*q_table_name	:	identifier . identifier */
/*q_table_name	:	identifier . identifier . identifier */
/*q_table_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_q_table_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*attach_q_table_name	:	identifier */
/*attach_q_table_name	:	identifier . identifier */
/*attach_q_table_name	:	identifier . identifier . identifier */
/*attach_q_table_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_attach_q_table_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*new_proc_or_bif_name	:	identifier */
/*new_proc_or_bif_name	:	identifier . identifier */
/*new_proc_or_bif_name	:	identifier . identifier . identifier */
/*new_proc_or_bif_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_new_proc_or_bif_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*new_table_name	:	identifier */
/*new_table_name	:	identifier . identifier */
/*new_table_name	:	identifier . identifier . identifier */
/*new_table_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_new_table_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*table	:	q_table_name opt_table_opt */
/*table	:	q_table_name AS identifier opt_table_opt */
/*table	:	q_table_name identifier opt_table_opt */
static psrNode_t* AR_STDCALL handle_table(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_ref	:	identifier */
/*column_ref	:	identifier . identifier */
/*column_ref	:	identifier . identifier . identifier */
/*column_ref	:	identifier . identifier . identifier . identifier */
/*column_ref	:	identifier . . identifier . identifier */
/*column_ref	:	* */
/*column_ref	:	identifier . * */
/*column_ref	:	identifier . identifier . * */
/*column_ref	:	identifier . identifier . identifier . * */
/*column_ref	:	identifier . . identifier . * */
static psrNode_t* AR_STDCALL handle_column_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*base_data_type	:	NUMERIC */
/*base_data_type	:	NUMERIC ( INTNUM ) */
/*base_data_type	:	NUMERIC ( INTNUM , INTNUM ) */
/*base_data_type	:	DECIMAL */
/*base_data_type	:	DECIMAL ( INTNUM ) */
/*base_data_type	:	DECIMAL ( INTNUM , INTNUM ) */
/*base_data_type	:	INTEGER */
/*base_data_type	:	SMALLINT */
/*base_data_type	:	FLOAT */
/*base_data_type	:	FLOAT ( INTNUM ) */
/*base_data_type	:	REAL */
/*base_data_type	:	DOUBLE PRECISION */
/*base_data_type	:	LONG VARCHAR */
/*base_data_type	:	LONG VARBINARY */
/*base_data_type	:	VARBINARY */
/*base_data_type	:	VARBINARY ( INTNUM ) */
/*base_data_type	:	BINARY ( INTNUM ) */
/*base_data_type	:	TIMESTAMP */
/*base_data_type	:	DATETIME */
/*base_data_type	:	TIME */
/*base_data_type	:	DATE */
/*base_data_type	:	NCHAR */
/*base_data_type	:	NCHAR ( INTNUM ) */
/*base_data_type	:	NVARCHAR */
/*base_data_type	:	NVARCHAR ( INTNUM ) */
/*base_data_type	:	LONG NVARCHAR */
/*base_data_type	:	ANY */
/*base_data_type	:	ANY ( INTNUM ) */
static psrNode_t* AR_STDCALL handle_base_data_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*data_type	:	base_data_type */
/*data_type	:	CHARACTER */
/*data_type	:	VARCHAR */
/*data_type	:	VARCHAR ( INTNUM ) */
/*data_type	:	CHARACTER ( INTNUM ) */
static psrNode_t* AR_STDCALL handle_data_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*array_modifier	:	ARRAY */
/*array_modifier	:	ARRAY [ INTNUM ] */
static psrNode_t* AR_STDCALL handle_array_modifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*data_type_ref	:	data_type_ref array_modifier */
/*data_type_ref	:	data_type */
/*data_type_ref	:	q_type_name */
static psrNode_t* AR_STDCALL handle_data_type_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column_data_type	:	base_data_type */
/*column_data_type	:	CHARACTER */
/*column_data_type	:	VARCHAR */
/*column_data_type	:	VARCHAR ( INTNUM ) */
/*column_data_type	:	CHARACTER ( INTNUM ) */
/*column_data_type	:	q_type_name */
/*column_data_type	:	LONG q_type_name */
/*column_data_type	:	LONG XML */
static psrNode_t* AR_STDCALL handle_column_data_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*column	:	identifier */
/*column	:	identifier . identifier . identifier . identifier */
static psrNode_t* AR_STDCALL handle_column(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*index	:	identifier */
static psrNode_t* AR_STDCALL handle_index(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cursor	:	identifier */
static psrNode_t* AR_STDCALL handle_cursor(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*parameter	:	PARAMETER_L */
/*parameter	:	NAMED_PARAMETER */
static psrNode_t* AR_STDCALL handle_parameter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*user	:	identifier */
static psrNode_t* AR_STDCALL handle_user(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_log	:	 */
/*opt_log	:	STRING */
static psrNode_t* AR_STDCALL handle_opt_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*comma_opt_log	:	 */
/*comma_opt_log	:	, STRING */
static psrNode_t* AR_STDCALL handle_comma_opt_log(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*admin_statement	:	SHUTDOWN opt_log */
/*admin_statement	:	CHECKPOINT opt_log */
/*admin_statement	:	CHECKPOINT STRING STRING */
/*admin_statement	:	BACKUP STRING */
/*admin_statement	:	CHECK */
/*admin_statement	:	SYNC REPLICATION opt_log comma_opt_log */
/*admin_statement	:	DISCONNECT REPLICATION opt_log */
/*admin_statement	:	LOGX ON */
/*admin_statement	:	LOGX OFF */
static psrNode_t* AR_STDCALL handle_admin_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*user_aggregate_declaration	:	CREATE AGGREGATE new_table_name rout_parameter_list opt_return FROM new_proc_or_bif_name , new_proc_or_bif_name , new_proc_or_bif_name user_aggregate_merge_opt */
static psrNode_t* AR_STDCALL handle_user_aggregate_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*user_aggregate_merge_opt	:	 */
/*user_aggregate_merge_opt	:	, new_proc_or_bif_name */
static psrNode_t* AR_STDCALL handle_user_aggregate_merge_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*routine_declaration	:	CREATE routine_head new_table_name rout_parameter_list opt_return rout_alt_type compound_statement */
/*routine_declaration	:	ATTACH routine_head attach_q_table_name rout_parameter_list opt_return rout_alt_type opt_as FROM literal */
/*routine_declaration	:	CREATE routine_head new_table_name rout_parameter_list opt_return rout_alt_type LANGUAGE external_language_name EXTERNAL NAME_L STRING opt_type_option_list */
static psrNode_t* AR_STDCALL handle_routine_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*module_body_part	:	routine_head identifier rout_parameter_list opt_return rout_alt_type compound_statement */
static psrNode_t* AR_STDCALL handle_module_body_part(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*module_body	:	module_body_part ; */
/*module_body	:	module_body module_body_part ; */
static psrNode_t* AR_STDCALL handle_module_body(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*module_declaration	:	CREATE MODULE new_table_name BEGINX module_body ENDX */
static psrNode_t* AR_STDCALL handle_module_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*routine_head	:	FUNCTION */
/*routine_head	:	PROCEDURE */
static psrNode_t* AR_STDCALL handle_routine_head(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_return	:	 */
/*opt_return	:	RETURNS data_type_ref */
static psrNode_t* AR_STDCALL handle_opt_return(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*rout_parameter_list	:	( ) */
/*rout_parameter_list	:	( parameter_commalist ) */
static psrNode_t* AR_STDCALL handle_rout_parameter_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*parameter_commalist	:	rout_parameter */
/*parameter_commalist	:	parameter_commalist , rout_parameter */
static psrNode_t* AR_STDCALL handle_parameter_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*rout_parameter	:	parameter_mode column_ref data_type_ref rout_alt_type */
/*rout_parameter	:	parameter_mode column_ref data_type_ref DEFAULT signed_literal rout_alt_type */
/*rout_parameter	:	parameter_mode column_ref data_type_ref EQUALS signed_literal rout_alt_type */
static psrNode_t* AR_STDCALL handle_rout_parameter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*parameter_mode	:	IN_L */
/*parameter_mode	:	OUT_L */
/*parameter_mode	:	INOUT_L */
static psrNode_t* AR_STDCALL handle_parameter_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_parameter_mode	:	 */
/*opt_parameter_mode	:	parameter_mode */
static psrNode_t* AR_STDCALL handle_opt_parameter_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_soap_enc_mode	:	 */
/*opt_soap_enc_mode	:	__SOAP_DIME_ENC IN_L */
/*opt_soap_enc_mode	:	__SOAP_DIME_ENC OUT_L */
/*opt_soap_enc_mode	:	__SOAP_DIME_ENC INOUT_L */
/*opt_soap_enc_mode	:	__SOAP_ENC_MIME IN_L */
/*opt_soap_enc_mode	:	__SOAP_ENC_MIME OUT_L */
/*opt_soap_enc_mode	:	__SOAP_ENC_MIME INOUT_L */
static psrNode_t* AR_STDCALL handle_opt_soap_enc_mode(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*soap_proc_opt_list	:	soap_proc_opt */
/*soap_proc_opt_list	:	soap_proc_opt_list , soap_proc_opt */
static psrNode_t* AR_STDCALL handle_soap_proc_opt_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*soap_proc_opt	:	NAME EQUALS signed_literal */
static psrNode_t* AR_STDCALL handle_soap_proc_opt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*soap_kwd	:	__SOAP_TYPE */
/*soap_kwd	:	__SOAP_HEADER */
/*soap_kwd	:	__SOAP_FAULT */
/*soap_kwd	:	__SOAP_DOC */
/*soap_kwd	:	__SOAP_XML_TYPE */
/*soap_kwd	:	__SOAP_DOCW */
/*soap_kwd	:	__SOAP_HTTP */
static psrNode_t* AR_STDCALL handle_soap_kwd(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*rout_alt_type	:	 */
/*rout_alt_type	:	__SOAP_OPTIONS ( soap_kwd EQUALS STRING opt_soap_enc_mode , soap_proc_opt_list ) */
/*rout_alt_type	:	soap_kwd STRING opt_soap_enc_mode */
static psrNode_t* AR_STDCALL handle_rout_alt_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*routine_statement	:	select_statement */
/*routine_statement	:	update_statement_positioned */
/*routine_statement	:	update_statement_searched */
/*routine_statement	:	insert_statement */
/*routine_statement	:	delete_statement_positioned */
/*routine_statement	:	delete_statement_searched */
/*routine_statement	:	close_statement */
/*routine_statement	:	fetch_statement */
/*routine_statement	:	open_statement */
/*routine_statement	:	rollback_statement */
/*routine_statement	:	commit_statement */
/*routine_statement	:	 */
static psrNode_t* AR_STDCALL handle_routine_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*empty2	:	 */
static psrNode_t* AR_STDCALL handle_empty2(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*compound_statement	:	BEGINX empty2 statement_list ENDX */
static psrNode_t* AR_STDCALL handle_compound_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*statement_list	:	statement_in_cs */
/*statement_list	:	statement_list statement_in_cs */
static psrNode_t* AR_STDCALL handle_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*statement_in_cs	:	local_declaration ; */
/*statement_in_cs	:	compound_statement */
/*statement_in_cs	:	empty3 statement_in_cs_oper */
static psrNode_t* AR_STDCALL handle_statement_in_cs(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*empty3	:	 */
static psrNode_t* AR_STDCALL handle_empty3(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*statement_in_cs_oper	:	routine_statement ; */
/*statement_in_cs_oper	:	control_statement */
/*statement_in_cs_oper	:	identifier COLON statement_in_cs */
/*statement_in_cs_oper	:	HTMLSTR */
/*statement_in_cs_oper	:	COMPARISON scalar_exp HTMLSTR */
/*statement_in_cs_oper	:	/ scalar_exp HTMLSTR */
static psrNode_t* AR_STDCALL handle_statement_in_cs_oper(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*statement	:	compound_statement */
/*statement	:	empty4 routine_statement ; */
/*statement	:	empty5 control_statement */
static psrNode_t* AR_STDCALL handle_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*empty4	:	 */
static psrNode_t* AR_STDCALL handle_empty4(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*empty5	:	 */
static psrNode_t* AR_STDCALL handle_empty5(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*local_declaration	:	cursor_def */
/*local_declaration	:	variable_declaration */
/*local_declaration	:	handler_declaration */
static psrNode_t* AR_STDCALL handle_local_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*variable_declaration	:	DECLARE variable_list data_type_ref */
static psrNode_t* AR_STDCALL handle_variable_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*variable_list	:	identifier */
/*variable_list	:	variable_list , identifier */
static psrNode_t* AR_STDCALL handle_variable_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*condition	:	NOT FOUND */
/*condition	:	SQLSTATE STRING */
/*condition	:	SQLSTATE VALUE STRING */
/*condition	:	SQLEXCEPTION */
/*condition	:	SQLWARNING */
static psrNode_t* AR_STDCALL handle_condition(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*handler_statement	:	compound_statement */
/*handler_statement	:	routine_statement */
/*handler_statement	:	call_statement */
/*handler_statement	:	method_invocation */
/*handler_statement	:	static_method_invocation */
/*handler_statement	:	set_statement */
/*handler_statement	:	RESIGNAL */
/*handler_statement	:	RESIGNAL scalar_exp */
/*handler_statement	:	return_statement */
/*handler_statement	:	assignment_statement */
/*handler_statement	:	if_statement */
/*handler_statement	:	goto_statement */
/*handler_statement	:	for_statement */
/*handler_statement	:	while_statement */
static psrNode_t* AR_STDCALL handle_handler_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*handler_declaration	:	WHENEVER condition GOTO identifier */
/*handler_declaration	:	WHENEVER condition GO TO identifier */
/*handler_declaration	:	WHENEVER condition DEFAULT */
/*handler_declaration	:	DECLARE handler_type HANDLER FOR cond_value_list handler_statement */
static psrNode_t* AR_STDCALL handle_handler_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*handler_type	:	CONTINUE */
/*handler_type	:	EXIT */
static psrNode_t* AR_STDCALL handle_handler_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*cond_value_list	:	condition */
/*cond_value_list	:	cond_value_list , condition */
static psrNode_t* AR_STDCALL handle_cond_value_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*control_statement	:	call_statement ; */
/*control_statement	:	method_invocation ; */
/*control_statement	:	static_method_invocation ; */
/*control_statement	:	set_statement ; */
/*control_statement	:	RESIGNAL ; */
/*control_statement	:	RESIGNAL scalar_exp ; */
/*control_statement	:	return_statement ; */
/*control_statement	:	assignment_statement ; */
/*control_statement	:	if_statement */
/*control_statement	:	goto_statement ; */
/*control_statement	:	for_statement */
/*control_statement	:	while_statement */
static psrNode_t* AR_STDCALL handle_control_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*assignment_statement	:	lvalue EQUALS scalar_exp */
/*assignment_statement	:	column_ref [ scalar_exp ] EQUALS scalar_exp */
static psrNode_t* AR_STDCALL handle_assignment_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*lvalue	:	column_ref */
/*lvalue	:	member_observer */
static psrNode_t* AR_STDCALL handle_lvalue(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*if_statement	:	IF ( search_condition ) statement opt_else */
static psrNode_t* AR_STDCALL handle_if_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_else	:	 */
/*opt_else	:	ELSE statement */
static psrNode_t* AR_STDCALL handle_opt_else(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*call_statement	:	CALL function_name ( opt_arg_commalist ) */
/*call_statement	:	function_call */
static psrNode_t* AR_STDCALL handle_call_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*set_statement	:	SET identifier COMPARISON scalar_exp */
/*set_statement	:	SET identifier ON */
/*set_statement	:	SET identifier OFF */
static psrNode_t* AR_STDCALL handle_set_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*goto_statement	:	GOTO identifier */
/*goto_statement	:	GO TO identifier */
static psrNode_t* AR_STDCALL handle_goto_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*return_statement	:	RETURN scalar_exp */
/*return_statement	:	RETURN */
static psrNode_t* AR_STDCALL handle_return_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*while_statement	:	WHILE ( search_condition ) statement */
static psrNode_t* AR_STDCALL handle_while_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*for_init_statement	:	assignment_statement */
/*for_init_statement	:	variable_declaration */
/*for_init_statement	:	call_statement */
/*for_init_statement	:	static_method_invocation */
static psrNode_t* AR_STDCALL handle_for_init_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*for_init_statement_list	:	 */
/*for_init_statement_list	:	for_init_statement */
/*for_init_statement_list	:	for_init_statement_list , for_init_statement */
static psrNode_t* AR_STDCALL handle_for_init_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*for_inc_statement	:	assignment_statement */
/*for_inc_statement	:	call_statement */
/*for_inc_statement	:	static_method_invocation */
static psrNode_t* AR_STDCALL handle_for_inc_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*for_inc_statement_list	:	 */
/*for_inc_statement_list	:	for_inc_statement */
/*for_inc_statement_list	:	for_inc_statement_list , for_inc_statement */
static psrNode_t* AR_STDCALL handle_for_inc_statement_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*for_opt_search_cond	:	 */
/*for_opt_search_cond	:	search_condition */
static psrNode_t* AR_STDCALL handle_for_opt_search_cond(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*for_statement	:	FOR query_exp DO statement */
/*for_statement	:	FOR ( for_init_statement_list ; for_opt_search_cond ; for_inc_statement_list ) statement */
/*for_statement	:	FOREACH ( data_type_ref identifier IN_L scalar_exp ) DO statement */
static psrNode_t* AR_STDCALL handle_for_statement(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*trigger_def	:	CREATE TRIGGER identifier action_time event ON q_table_name opt_order opt_old_ref trig_action */
static psrNode_t* AR_STDCALL handle_trigger_def(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_order	:	 */
/*opt_order	:	ORDER INTNUM */
static psrNode_t* AR_STDCALL handle_opt_order(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*trig_action	:	compound_statement */
static psrNode_t* AR_STDCALL handle_trig_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*action_time	:	BEFORE */
/*action_time	:	AFTER */
/*action_time	:	INSTEAD OF */
static psrNode_t* AR_STDCALL handle_action_time(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*event	:	INSERT */
/*event	:	UPDATE opt_column_commalist */
/*event	:	DELETE_L */
static psrNode_t* AR_STDCALL handle_event(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_old_ref	:	 */
/*opt_old_ref	:	REFERENCING old_commalist */
static psrNode_t* AR_STDCALL handle_opt_old_ref(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*old_commalist	:	old_alias */
/*old_commalist	:	old_commalist , old_alias */
static psrNode_t* AR_STDCALL handle_old_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*old_alias	:	OLD AS identifier */
/*old_alias	:	NEW AS identifier */
static psrNode_t* AR_STDCALL handle_old_alias(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_trigger	:	DROP TRIGGER q_table_name */
static psrNode_t* AR_STDCALL handle_drop_trigger(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_proc	:	DROP AGGREGATE q_table_name */
/*drop_proc	:	DROP routine_head q_table_name */
/*drop_proc	:	DROP MODULE q_table_name */
static psrNode_t* AR_STDCALL handle_drop_proc(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_element	:	 */
/*opt_element	:	AS identifier */
static psrNode_t* AR_STDCALL handle_opt_element(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xml_col	:	column_ref */
/*xml_col	:	scalar_exp AS identifier */
/*xml_col	:	scalar_exp IN_L identifier */
static psrNode_t* AR_STDCALL handle_xml_col(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xml_col_list	:	xml_col */
/*xml_col_list	:	xml_col_list , xml_col */
static psrNode_t* AR_STDCALL handle_xml_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_xml_col_list	:	( xml_col_list ) */
static psrNode_t* AR_STDCALL handle_opt_xml_col_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_pk	:	 */
/*opt_pk	:	PRIMARY KEY ( column_commalist ) */
static psrNode_t* AR_STDCALL handle_opt_pk(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_join	:	 */
/*opt_join	:	ON ( search_condition ) */
static psrNode_t* AR_STDCALL handle_opt_join(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_elt	:	 */
/*opt_elt	:	NAME */
static psrNode_t* AR_STDCALL handle_opt_elt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xml_join_elt	:	q_table_name identifier opt_element opt_xml_col_list opt_join opt_pk opt_elt opt_xml_child */
static psrNode_t* AR_STDCALL handle_xml_join_elt(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_xml_child	:	 */
/*opt_xml_child	:	BEGINX xml_join_list ENDX */
static psrNode_t* AR_STDCALL handle_opt_xml_child(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*top_xml_child	:	query_spec */
/*top_xml_child	:	BEGINX xml_join_list ENDX */
static psrNode_t* AR_STDCALL handle_top_xml_child(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xml_join_list	:	xml_join_elt */
/*xml_join_list	:	xml_join_list , xml_join_elt */
static psrNode_t* AR_STDCALL handle_xml_join_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_persist	:	 */
/*opt_persist	:	PERSISTENT */
static psrNode_t* AR_STDCALL handle_opt_persist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_interval	:	 */
/*opt_interval	:	INTERVAL INTNUM */
static psrNode_t* AR_STDCALL handle_opt_interval(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_metas	:	 */
/*opt_metas	:	DTD INTERNAL */
/*opt_metas	:	DTD EXTERNAL */
/*opt_metas	:	DTD STRING */
/*opt_metas	:	SCHEMA EXTERNAL */
/*opt_metas	:	SCHEMA STRING */
static psrNode_t* AR_STDCALL handle_opt_metas(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_publish	:	 */
/*opt_publish	:	PUBLIC STRING identifier STRING opt_persist opt_interval opt_metas */
static psrNode_t* AR_STDCALL handle_opt_publish(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xmlview_param_value	:	NAME */
/*xmlview_param_value	:	STRING */
static psrNode_t* AR_STDCALL handle_xmlview_param_value(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xmlview_param	:	NAME COMPARISON xmlview_param_value */
static psrNode_t* AR_STDCALL handle_xmlview_param(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xmlview_params	:	xmlview_param */
/*xmlview_params	:	xmlview_params xmlview_param */
static psrNode_t* AR_STDCALL handle_xmlview_params(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_xmlview_params	:	 */
/*opt_xmlview_params	:	[ xmlview_params ] */
static psrNode_t* AR_STDCALL handle_opt_xmlview_params(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*xml_view	:	CREATE XML VIEW new_table_name AS opt_xmlview_params top_xml_child opt_elt opt_publish */
static psrNode_t* AR_STDCALL handle_xml_view(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_xml_view	:	DROP XML VIEW q_table_name */
static psrNode_t* AR_STDCALL handle_drop_xml_view(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*string_concatenation_operator	:	scalar_exp STRING_CONCAT_OPERATOR scalar_exp */
static psrNode_t* AR_STDCALL handle_string_concatenation_operator(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*q_type_name	:	identifier */
/*q_type_name	:	identifier . identifier */
/*q_type_name	:	identifier . identifier . identifier */
/*q_type_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_q_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*q_old_type_name	:	identifier */
/*q_old_type_name	:	identifier . identifier */
/*q_old_type_name	:	identifier . identifier . identifier */
/*q_old_type_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_q_old_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*new_type_name	:	identifier */
/*new_type_name	:	identifier . identifier */
/*new_type_name	:	identifier . identifier . identifier */
/*new_type_name	:	identifier . . identifier */
static psrNode_t* AR_STDCALL handle_new_type_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*empty6	:	 */
static psrNode_t* AR_STDCALL handle_empty6(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*user_defined_type	:	CREATE TYPE new_type_name opt_subtype_clause opt_external_and_language_clause empty6 opt_as_type_representation opt_type_option_list opt_method_specification_list */
static psrNode_t* AR_STDCALL handle_user_defined_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*user_defined_type_drop	:	DROP TYPE q_old_type_name opt_drop_behavior */
static psrNode_t* AR_STDCALL handle_user_defined_type_drop(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_external_and_language_clause	:	 */
/*opt_external_and_language_clause	:	LANGUAGE language_name EXTERNAL NAME_L STRING */
/*opt_external_and_language_clause	:	EXTERNAL NAME_L STRING LANGUAGE language_name */
/*opt_external_and_language_clause	:	LANGUAGE language_name */
static psrNode_t* AR_STDCALL handle_opt_external_and_language_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_subtype_clause	:	 */
/*opt_subtype_clause	:	UNDER q_type_name */
static psrNode_t* AR_STDCALL handle_opt_subtype_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_as_type_representation	:	 */
/*opt_as_type_representation	:	AS type_representation */
static psrNode_t* AR_STDCALL handle_opt_as_type_representation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*type_representation	:	( type_member_list ) */
static psrNode_t* AR_STDCALL handle_type_representation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*type_member_list	:	type_member */
/*type_member_list	:	type_member_list , type_member */
static psrNode_t* AR_STDCALL handle_type_member_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_external_clause	:	 */
/*opt_external_clause	:	EXTERNAL NAME_L STRING */
/*opt_external_clause	:	EXTERNAL NAME_L STRING EXTERNAL TYPE STRING */
/*opt_external_clause	:	EXTERNAL TYPE STRING */
static psrNode_t* AR_STDCALL handle_opt_external_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_soap_clause	:	 */
/*opt_soap_clause	:	__SOAP_NAME STRING */
/*opt_soap_clause	:	__SOAP_TYPE STRING */
/*opt_soap_clause	:	__SOAP_TYPE STRING __SOAP_NAME STRING */
/*opt_soap_clause	:	__SOAP_NAME STRING __SOAP_TYPE STRING */
static psrNode_t* AR_STDCALL handle_opt_soap_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_external_type	:	 */
/*opt_external_type	:	EXTERNAL TYPE STRING */
static psrNode_t* AR_STDCALL handle_opt_external_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*type_member	:	identifier data_type_ref opt_reference_scope_check opt_default_clause opt_collate_exp opt_external_clause opt_soap_clause */
static psrNode_t* AR_STDCALL handle_type_member(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_reference_scope_check	:	 */
/*opt_reference_scope_check	:	REFERENCES ARE CHECKED opt_on_delete_referential_rule */
/*opt_reference_scope_check	:	REFERENCES ARE NOT CHECKED */
static psrNode_t* AR_STDCALL handle_opt_reference_scope_check(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_default_clause	:	 */
/*opt_default_clause	:	DEFAULT signed_literal */
static psrNode_t* AR_STDCALL handle_opt_default_clause(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_type_option_list	:	 */
/*opt_type_option_list	:	type_option_list */
static psrNode_t* AR_STDCALL handle_opt_type_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*type_option_list	:	type_option */
/*type_option_list	:	type_option_list type_option */
static psrNode_t* AR_STDCALL handle_type_option_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*type_option	:	FINAL_L */
/*type_option	:	NOT FINAL_L */
/*type_option	:	REF USING data_type_ref */
/*type_option	:	REF FROM ( column_commalist ) */
/*type_option	:	REF IS SYSTEM GENERATED */
/*type_option	:	CAST ( SOURCE AS REF ) WITH identifier */
/*type_option	:	CAST ( REF AS SOURCE ) WITH identifier */
/*type_option	:	SELF_L AS REF */
/*type_option	:	TEMPORARY */
/*type_option	:	UNRESTRICTED */
/*type_option	:	__SOAP_TYPE STRING */
static psrNode_t* AR_STDCALL handle_type_option(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_method_specification_list	:	 */
/*opt_method_specification_list	:	method_specification_list */
static psrNode_t* AR_STDCALL handle_opt_method_specification_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_specification_list	:	method_specification */
/*method_specification_list	:	method_specification_list , method_specification */
static psrNode_t* AR_STDCALL handle_method_specification_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_type	:	 */
/*method_type	:	STATIC_L */
/*method_type	:	INSTANCE_L */
static psrNode_t* AR_STDCALL handle_method_type(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*decl_parameter_list	:	( ) */
/*decl_parameter_list	:	( decl_parameter_commalist ) */
static psrNode_t* AR_STDCALL handle_decl_parameter_list(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*decl_parameter_commalist	:	decl_parameter */
/*decl_parameter_commalist	:	decl_parameter_commalist , decl_parameter */
static psrNode_t* AR_STDCALL handle_decl_parameter_commalist(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*decl_parameter	:	opt_parameter_mode column_ref data_type_ref opt_external_type */
static psrNode_t* AR_STDCALL handle_decl_parameter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*partial_method_specification	:	method_type METHOD method_identifier decl_parameter_list RETURNS data_type_ref opt_specific_method_name */
/*partial_method_specification	:	CONSTRUCTOR METHOD method_identifier decl_parameter_list opt_specific_method_name */
static psrNode_t* AR_STDCALL handle_partial_method_specification(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_specification	:	partial_method_specification opt_self_result opt_method_characteristics */
/*method_specification	:	OVERRIDING partial_method_specification */
static psrNode_t* AR_STDCALL handle_method_specification(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_self_result	:	 */
/*opt_self_result	:	SELF_L AS RESULT */
/*opt_self_result	:	SELF_L AS LOCATOR */
/*opt_self_result	:	SELF_L AS RESULT SELF_L AS LOCATOR */
static psrNode_t* AR_STDCALL handle_opt_self_result(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_specific_method_name	:	 */
/*opt_specific_method_name	:	SPECIFIC new_table_name */
static psrNode_t* AR_STDCALL handle_opt_specific_method_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_method_characteristics	:	 */
/*opt_method_characteristics	:	method_characteristics */
static psrNode_t* AR_STDCALL handle_opt_method_characteristics(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_characteristics	:	method_characteristic */
/*method_characteristics	:	method_characteristics method_characteristic */
static psrNode_t* AR_STDCALL handle_method_characteristics(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_characteristic	:	LANGUAGE language_name */
/*method_characteristic	:	PARAMETER STYLE SQL_L */
/*method_characteristic	:	PARAMETER STYLE GENERAL */
/*method_characteristic	:	DETERMINISTIC */
/*method_characteristic	:	NOT DETERMINISTIC */
/*method_characteristic	:	NO SQL_L */
/*method_characteristic	:	CONTAINS SQL_L */
/*method_characteristic	:	READS SQL_L DATA */
/*method_characteristic	:	MODIFIES SQL_L DATA */
/*method_characteristic	:	RETURNS NULLX ON NULLX INPUT */
/*method_characteristic	:	CALLED ON NULLX INPUT */
/*method_characteristic	:	EXTERNAL NAME_L STRING */
/*method_characteristic	:	EXTERNAL VARIABLE NAME_L STRING */
/*method_characteristic	:	EXTERNAL TYPE STRING */
static psrNode_t* AR_STDCALL handle_method_characteristic(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*external_language_name	:	ADA */
/*external_language_name	:	C */
/*external_language_name	:	COBOL */
/*external_language_name	:	FORTRAN */
/*external_language_name	:	MUMPS */
/*external_language_name	:	PASCAL_L */
/*external_language_name	:	PLI */
/*external_language_name	:	JAVA */
/*external_language_name	:	CLR */
static psrNode_t* AR_STDCALL handle_external_language_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*language_name	:	external_language_name */
/*language_name	:	SQL_L */
static psrNode_t* AR_STDCALL handle_language_name(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_constructor_return	:	 */
/*opt_constructor_return	:	RETURNS new_type_name */
static psrNode_t* AR_STDCALL handle_opt_constructor_return(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_declaration	:	CREATE method_type METHOD method_identifier rout_parameter_list opt_return rout_alt_type FOR q_type_name compound_statement */
/*method_declaration	:	CREATE CONSTRUCTOR METHOD q_table_name rout_parameter_list opt_constructor_return FOR q_type_name compound_statement */
static psrNode_t* AR_STDCALL handle_method_declaration(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*static_method_invocation	:	q_type_name DOUBLE_COLON method_identifier ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_static_method_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*identifier_chain	:	identifier . identifier . identifier . method_identifier */
/*identifier_chain	:	identifier . . identifier . method_identifier */
/*identifier_chain	:	identifier . identifier_chain */
static psrNode_t* AR_STDCALL handle_identifier_chain(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*identifier_chain_method	:	identifier . identifier . identifier . identifier . method_identifier */
/*identifier_chain_method	:	identifier . . identifier . identifier . method_identifier */
/*identifier_chain_method	:	identifier . identifier_chain_method */
static psrNode_t* AR_STDCALL handle_identifier_chain_method(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_invocation	:	scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ( opt_arg_commalist ) */
/*method_invocation	:	identifier_chain_method ( opt_arg_commalist ) */
/*method_invocation	:	( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
/*method_invocation	:	( column_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_method_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*top_level_method_invocation	:	METHOD CALL scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier ( opt_arg_commalist ) */
/*top_level_method_invocation	:	METHOD CALL identifier_chain_method ( opt_arg_commalist ) */
/*top_level_method_invocation	:	METHOD CALL ( scalar_exp_no_col_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
/*top_level_method_invocation	:	METHOD CALL ( column_ref AS q_type_name ) . method_identifier ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_top_level_method_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*member_observer	:	member_observer_no_id_chain */
/*member_observer	:	identifier . identifier_chain */
static psrNode_t* AR_STDCALL handle_member_observer(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*member_observer_no_id_chain	:	scalar_exp_no_col_ref_no_mem_obs_chain . method_identifier */
/*member_observer_no_id_chain	:	( scalar_exp_no_col_ref AS q_type_name ) . method_identifier */
/*member_observer_no_id_chain	:	( column_ref AS q_type_name ) . method_identifier */
static psrNode_t* AR_STDCALL handle_member_observer_no_id_chain(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*method_identifier	:	identifier */
/*method_identifier	:	EXTRACT */
static psrNode_t* AR_STDCALL handle_method_identifier(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*new_invocation	:	NEW q_type_name ( opt_arg_commalist ) */
static psrNode_t* AR_STDCALL handle_new_invocation(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*user_defined_type_alter	:	ALTER TYPE q_type_name alter_type_action */
static psrNode_t* AR_STDCALL handle_user_defined_type_alter(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*alter_type_action	:	ADD ATTRIBUTE type_member */
/*alter_type_action	:	DROP ATTRIBUTE identifier opt_drop_behavior */
/*alter_type_action	:	ADD method_specification */
/*alter_type_action	:	DROP partial_method_specification opt_drop_behavior */
static psrNode_t* AR_STDCALL handle_alter_type_action(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_permission_set	:	 */
/*opt_with_permission_set	:	WITH PERMISSION_SET COMPARISON SAFE_L */
/*opt_with_permission_set	:	WITH PERMISSION_SET COMPARISON UNRESTRICTED */
static psrNode_t* AR_STDCALL handle_opt_with_permission_set(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*opt_with_autoregister	:	 */
/*opt_with_autoregister	:	WITH AUTOREGISTER_L */
static psrNode_t* AR_STDCALL handle_opt_with_autoregister(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_library	:	CREATE LIBRARY_L q_table_name AS scalar_exp opt_with_permission_set opt_with_autoregister */
static psrNode_t* AR_STDCALL handle_create_library(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*create_assembly	:	CREATE ASSEMBLY_L q_table_name FROM scalar_exp opt_with_permission_set opt_with_autoregister */
static psrNode_t* AR_STDCALL handle_create_assembly(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_library	:	DROP LIBRARY_L q_table_name */
static psrNode_t* AR_STDCALL handle_drop_library(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}




/*drop_assembly	:	DROP ASSEMBLY_L q_table_name */
static psrNode_t* AR_STDCALL handle_drop_assembly(psrNode_t **nodes, size_t count, const wchar_t *name, void *ctx)
{
	 return NULL;
}





#endif
