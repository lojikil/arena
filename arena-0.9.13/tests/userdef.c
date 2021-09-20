/*
 * User-defined functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../libeval/eval.h"

void userdef_test(void)
{
  arena_state *s = state_alloc();

  stmt fundef, body;
  stmt voiddef, voidbody;
  expr vari, five;
  expr callmyfunc;
  expr callnested;
  stmt runnested;
  stmt deepdef, deepbody;
  expr deepexpr, deepexpr2;
  stmt deep[4200];
  stmt deepblock[4200];
  expr deepinner[4200];
  value *val;
  expr *exprs[] = { &five };
  expr *deepargv[] = { &deepexpr2 };
  char *argnames[] = { "i" };
  int i;

  symtab_stack_init(s);

  test_banner("libeval");
  test_section("user-defined functions");
  
  /*
   * Define and call simple function
   */

  vari.type = EXPR_REF;
  vari.name = "i";
  
  body.type = STMT_RETURN;
  body.expr = &vari;
  
  fundef.type = STMT_FUNC;
  fundef.true_case = &body;
  fundef.name = "froobar";
  fundef.args = 1;
  fundef.proto = "i";
  fundef.rettype = '?';
  fundef.names = argnames;
  
  test_start("eval_stmt (define)");
  eval_stmt(s, &fundef, 0);
  test_assert(1);

  callmyfunc.type = EXPR_CALL;
  callmyfunc.name = "froobar";
  callmyfunc.argc = 1;
  callmyfunc.argv = exprs;

  five.type = EXPR_CONST_INT;
  five.name = "5";
  
  test_start("eval_expr (call)");
  val = eval_expr(s, &callmyfunc);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 5);
  value_free(val);
  
  /*
   * Define and call nested functions
   */
   
   voiddef.type = STMT_FUNC;
   voiddef.true_case = &voidbody;
   voiddef.name = "barfroo";
   voiddef.args = 1;
   voiddef.proto = "i";
   voiddef.rettype = '?';
   voiddef.names = argnames;
   
   voidbody.type = STMT_EXPR;
   voidbody.expr = &callmyfunc;
   
   test_start("eval_stmt (define nested)");
   eval_stmt(s, &voiddef, 0);
   test_assert(1);
   
   callnested.type = EXPR_CALL;
   callnested.name = "barfroo";
   callnested.argc = 1;
   callnested.argv = exprs;
   
   runnested.type = STMT_EXPR;
   runnested.expr = &callnested;
   
   test_start("eval_stmt (call nested)");
   eval_stmt(s, &runnested, 0);
   test_assert(1);
   
   test_start("eval_stmt (10500 calls)");
   for (i = 0; i < 10500; i++) {
     eval_stmt(s, &runnested, 0);
   }  
   test_assert(1);
   
   /*
    * Deeply nested functions
    */

   deepdef.type  = STMT_FUNC;
   deepdef.true_case = &deepbody;
   deepdef.name  = "fun    ";
   deepdef.args  = 1;
   deepdef.proto = "i";
   deepdef.rettype = '?';
   deepdef.names = argnames;
   
   deepbody.type = STMT_RETURN;
   deepbody.expr = &deepexpr;
   
   deepexpr.type = EXPR_CALL;
   deepexpr.name = "fun    ";
   deepexpr.argc = 1;
   deepexpr.argv = deepargv;
   
   deepexpr2.type  = EXPR_PREFIX;
   deepexpr2.op    = OPTYPE_PREINC;
   deepexpr2.inner = &vari;

   test_start("eval_stmt (define deep)");

   /*
    * Define 4200 function that call each other in turn: fun0000
    * calls fun0001 calls fun0001 ... calls fun4199. Function defs
    * for fun0000 to fun4198 are like this:
    *
    *   function fun0000(int i)
    *   {
    *     return fun0001(++i);
    *   }
    *
    * The last function defined thus:
    *
    *   function fun4199(int i)
    *   {
    *     return i;
    *   }
    *
    * Please note this tests leaves the statments and expressions
    * defining all the functions in memory.
    */   
   for (i = 0; i < 4200; i++) {
     deepinner[i] = deepexpr;
     deepinner[i].name = oom(malloc(strlen(deepexpr.name) + 1));
     strcpy(deepinner[i].name, deepexpr.name);
     sprintf((char *) deepinner[i].name + 3, "%04i", i + 1);
   
     if (i < 4199) {
       deepblock[i] = deepbody;
       deepblock[i].expr = &deepinner[i];
     } else {
       deepblock[i] = body;
     }

     deep[i] = deepdef;
     deep[i].name = oom(malloc(strlen(deepdef.name) + 1));
     strcpy(deep[i].name, deepdef.name);
     sprintf(deep[i].name + 3, "%04i", i);
     deep[i].true_case = &deepblock[i];
    
     eval_stmt(s, &deep[i], 0);
   }
   test_assert(1);

   callnested.name = "fun0000";

   test_start("eval_expr (call deep)");
   val = eval_expr(s, &callnested);
   test_assert(val != NULL && val->type == VALUE_TYPE_INT &&
               val->value_u.int_val == 4204);
   value_free(val);
   
   test_start("eval_stmt (call deep)");
   eval_stmt(s, &runnested, 0);
   test_assert(1);
   
   /* some cleanup for using valgrind */
   for (i = 0; i < 4200; i++) {
     free((char *) deepinner[i].name);
     free(deep[i].name);
   }
   
   symtab_stack_teardown(s);
   state_free(s);
}
