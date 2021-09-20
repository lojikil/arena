/*
 * Parsing of simple constructs
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "test.h"

/*
 * Call tparser binary on a file
 */
static void parse(const char *name)
{
  char buf[512];
  char cmd[512];
  int res;
  
  sprintf(buf, "parse_file (%s)", name);
  sprintf(cmd, "./tparser data/simple/%s", name);
  
  test_start(buf);
  res = system(cmd);
  test_assert(res == 0);
}

void simple_test(void)
{
  test_banner("libparser");

  test_section("parse of simple expressions");
  parse("bool");
  parse("int");
  parse("float");
  parse("string");
  parse("variable");
  parse("source");
  
  test_section("parse of simple nested expressions");
  parse("variable_array");
  parse("assign");
  parse("assign_array");
  parse("assign_nested");
  parse("paren");
  parse("cast");
  parse("call_void");
  parse("call");
  parse("prefix");
  parse("infix");
  parse("postfix");
  parse("new");
  parse("static");
  parse("method");
  parse("conditional");
  parse("refpass");
  parse("lambda");
  parse("reference");

  test_section("parse of simple statements");
  parse("empty");
  parse("nop");
  parse("block");
  parse("if");
  parse("if_else");
  parse("while");
  parse("do");
  parse("for");
  parse("continue");
  parse("break");
  parse("switch");
  parse("return");
  parse("return_value");
  parse("function");
  parse("include");
  parse("template");
}
