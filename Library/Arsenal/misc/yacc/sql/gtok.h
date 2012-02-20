/*
Genarate tokens for parse tree
DDF Version 1.00
By Leroy G. Cain
Copywrite 1986
*/

/* Tokens */
/* expressions */
#define T_EQ    0201
#define T_NE    0202
#define T_GT    0203
#define T_NGT   0225
#define T_GE    0204
#define T_LT    0205
#define T_NLT   0226
#define T_LE    0206
#define T_AND   0210
#define T_OR    0211
#define T_ADD   0212
#define T_NEG   0101
#define T_SUB   0213
#define T_MUL   0214
#define T_DIV   0215
#define T_MOD   0221

/* Constaints and varibles */
#define T_FCHAR 0047
#define T_PCHAR 0054
#define T_CHAR  0057
#define T_VAR   0050
#define T_INT4  0070
#define T_FLT8  0074

/* Struct tokens */
#define T_ROOT  0264
#define T_ENDCOMMAND    0220
#define T_AGHEAD        0217
#define T_RESDOM        0200
#define T_TLEND 0001
#define T_QLEND 0002
