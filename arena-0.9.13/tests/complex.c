/*
 * Parsing and running of programs
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "test.h"

/*
 * Call interpreter binary on a file
 */
static void runscript(const char *name, const char *dir, int want_success)
{
  char buf[512];
  char cmd[512];
  int res;
  
  sprintf(buf, "run (%s)", name);
  sprintf(cmd, "../arena data/%s/%s 2>/dev/null", dir, name);
  
  test_start(buf);
  fflush(stdout);
  res = system(cmd);
  if (want_success) {
    test_assert(res == 0);
  } else {
    test_assert(res != 0);
  }
}

void complex_test(void)
{
  test_banner("interpreter");

  test_section("program semantics");
  runscript("assign", "semantic", 1);
  runscript("out_of_bounds", "semantic", 1);
  runscript("cast", "semantic", 1);
  runscript("prefix", "semantic", 1);
  runscript("infix", "semantic", 1);
  runscript("postfix", "semantic", 1);
  runscript("control", "semantic", 1);
  runscript("uncaught", "semantic", 0);
  runscript("undefined", "semantic", 0);
  runscript("missing", "semantic", 0);
  runscript("mismatch", "semantic", 0);
  runscript("return_mismatch", "semantic", 0);
  runscript("varargs", "semantic", 1);
  runscript("namespace", "semantic", 1);
  runscript("force", "semantic", 1);
  runscript("index", "semantic", 1);
  runscript("isolation", "semantic", 1);
  runscript("template", "semantic", 1);
  runscript("undef_tmpl", "semantic", 0);
  runscript("undef_method", "semantic", 0);
  runscript("undef_parent", "semantic", 0);
  runscript("undef_static_tmpl", "semantic", 0);
  runscript("undef_static_method", "semantic", 0);
  runscript("function", "semantic", 1);
  runscript("function_cast", "semantic", 0);
  runscript("function_retcast", "semantic", 0);
  runscript("lambda", "semantic", 1);
  runscript("reference", "semantic", 1);
  runscript("source", "semantic", 1);
  runscript("order", "semantic", 1);

  test_section("standard library");
  runscript("runtime", "library", 1);
  runscript("assert", "library", 0);
  runscript("print", "library", 1);
  runscript("random", "library", 1);
  runscript("exit", "library", 0);
  runscript("string", "library", 1);
  runscript("math", "library", 1);
  runscript("file", "library", 1);
  runscript("array", "library", 1);
  runscript("struct", "library", 1);
  runscript("time", "library", 1);
  runscript("dict", "library", 1);
  runscript("function", "library", 1);
  runscript("list", "library", 1);
  runscript("memory", "library", 1);
  runscript("foreign", "library", 1);
  runscript("pcre", "library", 1);
  
  test_section("example programs");
  runscript("bubble", "complex", 1);
  runscript("hanoi", "complex", 1);
}
