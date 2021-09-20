/*
 * Test case framework
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../libruntime/runtime.h"

static const char *banner = "check";

static testfunc tests[] = {
  value_test,
  cast_test,
  symtab_test,
  call_test,
  parse_test,
  simple_test,
  math_test,
  eval_test,
  userdef_test,
  complex_test,
  NULL
};

static unsigned int pass = 0;
static unsigned int fail = 0;

void test_banner(const char *msg)
{
  banner = msg;
}

void test_section(const char *msg)
{
  printf("[%s: %s]\n", banner, msg);
}

void test_start(const char *msg)
{
  printf("\t%s ... ", msg);
}

void test_assert(int flag)
{
  if (flag) {
    pass++;
    printf("PASS\n");
  } else {
    fail++;
    printf("FAIL\n");
  }
}

void test_stop(void)
{
  printf("%u tests, %u pass, %u fail\n", pass + fail, pass, fail);
}

int main(void)
{
  int i = 0;
  
  while (tests[i] != NULL) {
    tests[i]();
    i++;
  }

  test_stop();  
  if (fail != 0) {
    return 1;
  }
  return 0;
}
