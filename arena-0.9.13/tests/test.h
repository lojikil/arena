/*
 * Test case framework and defined tests
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
#ifndef TESTS_TEST_H
#define TESTS_TEST_H

/*
 * type of test functions
 */
typedef void(*testfunc)(void);

/*
 * test framework
 */
void test_banner(const char *msg);
void test_section(const char *msg);
void test_start(const char *msg);
void test_assert(int val);
void test_stop(void);

/*
 * Actual test functions
 */
void value_test(void);
void cast_test(void);
void symtab_test(void);
void call_test(void);
void parse_test(void);
void simple_test(void);
void eval_test(void);
void math_test(void);
void userdef_test(void);
void complex_test(void);

#endif
