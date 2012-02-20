

#include "test.h"




AR_NAMESPACE_BEGIN

#if defined(__LIB)

extern void parser_test();
extern void com_test();
extern void str_test();
extern void expr_test();
extern void lex_test();
extern void lr_dfa_test();
extern void action_tbl_test();
extern void parser_test();
extern void lex_test2();
extern void lex_test3();
extern void lex_test4();
extern void trans_char_test();

extern void str_tbl_test();

extern void psr_symb_lst_test();

extern void psr_symb_htbl_test();

extern void lr_item_tbl_test();

extern void Parser_Init();
extern void Parser_UnInit();

extern void cache_test();
extern void rule_test();
extern void grammar_test2();
extern void calc_test();
extern void calc_test1();
extern void calc3_test();
extern void db_test();

extern void pcg_test();

extern void pcg_test2();

extern void create_file_test();

extern void trie_tree_test();

extern void parser_test();
extern void parser_test_lex();

extern void rgx_test();

extern void calc_test3();

extern void parser_perf_test();

extern void lalr_test();

extern void grammar_test();
extern void ray_test();
void code_gen_lex_test();
void sn_test();
void perf_test();
void gen_code_test();

extern void calc2_test();

extern void ds_test();

extern void	Tengu_Test();

extern void mem_test();

extern void tokenizer_test();

extern void Ini_Test();

void parser_gen_perf_test();

extern void math_test();

extern void grammar_config_test();
#endif





void AR_Test()
{
#if defined(__LIB)
		//com_test();
		//math_test();
		//trie_tree_test();
		//expr_test();
		//lex_test();
		
		//lr_dfa_test();
		//action_tbl_test();
		//parser_test();
		//str_test();
		//str_tbl_test();
		//rule_test();
		//grammar_test2();
		//psr_symb_lst_test();
		
		//psr_symb_htbl_test();

		//lr_item_tbl_test();
		//cache_test();
		//calc_test1();
		//calc_test();
		
		//calc_test();

		//db_test();

		//pcg_test();

		//pcg_test2();

		//trans_char_test();
		
		//lex_test();
		

		//parser_perf_test();
		
		//rgx_test();
		//calc_test();

		//parser_test();
		
		//grammar_test();
		
		//code_gen_lex_test();
		
		//lalr_test();

		//ray_test();

		//sn_test();

		//gen_code_test();

		//perf_test();

		//ray_test();

		//calc2_test();

		//ds_test();

		//Tengu_Test();

		//mem_test();
		
		//tokenizer_test();

		//Ini_Test();
		
		//parser_gen_perf_test();

		calc3_test();

		//grammar_config_test();

		getchar();
#else
		ARSpace::AR_printf(L"dll version\r\n");
#endif
}

AR_NAMESPACE_END









