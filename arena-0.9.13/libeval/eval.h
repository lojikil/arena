/*
 * Evaluation library
 *
 * This library provides functions needed to evaluate statements
 * and expressions in accordance with the defined semantics of
 * the language.
 *
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
#ifndef LIBEXEC_H
#define LIBEXEC_H

#include "../libmisc/misc.h"
#include "../libruntime/runtime.h"
#include "../libparser/parser.h"

/*
 * Helper functions
 */
void eval_free_floats(arena_state *s);
void eval_call_args(arena_state *s, unsigned int argc, expr **args,
  value ***argv);
void free_call_args(arena_state *s, unsigned int argc, value ***argv);
void update_call_args(arena_state *s, signature *sig, unsigned int argc,
  expr **args);

/*
 * Simple expressions
 */
value *eval_const_void(void);
value *eval_const_bool(expr *ex);
value *eval_const_int(expr *ex);
value *eval_const_float(expr *ex);
value *eval_const_string(arena_state *s, expr *ex);
value *eval_cast(arena_state *s, expr *ex);
value *eval_assign(arena_state *s, expr *ex);
value *eval_assign_array(arena_state *s, expr *ex);
value *eval_ref(arena_state *s, expr *ex);
value *eval_ref_array(arena_state *s, expr *ex);
value *eval_ref_index(arena_state *s, expr *ex);
value *eval_call(arena_state *s, expr *ex);
value *eval_new(arena_state *s, expr *ex);
value *eval_static(arena_state *s, expr *ex);
value *eval_method(arena_state *s, expr *ex);
value *eval_static_ref(arena_state *s, expr *ex);
value *eval_prefix(arena_state *s, expr *ex);
value *eval_postfix(arena_state *s, expr *ex);
value *eval_infix(arena_state *s, expr *ex);
value *eval_lambda(arena_state *s, expr *ex);

void eval_assign_array_direct(arena_state *s, const char *name,
  int argc, expr **index, value *val);

/*
 * Math evaluation
 */
value *eval_math_plus(value *a, value *b);
value *eval_math_minus(value *a, value *b);
value *eval_math_mul(value *a, value *b);
value *eval_math_div(arena_state *s, value *a, value *b);
value *eval_math_mod(arena_state *s, value *a, value *b);
value *eval_math_pow(value *a, value *b);

/*
 * Boolean math evaluation
 */
value *eval_bool_and(arena_state *s, expr *a, expr *b);
value *eval_bool_or(arena_state *s, expr *a, expr *b);
value *eval_expr_if(arena_state *s, expr *ex);

/*
 * Bitwise math evaluation
 */
value *eval_bit_and(value *a, value *b);
value *eval_bit_or(value *a, value *b);
value *eval_bit_xor(value *a, value *b);
value *eval_bit_lshift(value *a, value *b);
value *eval_bit_rshift(value *a, value *b);

/*
 * Order evaluation
 */
value *eval_order_equal(value *a, value *b);
value *eval_order_not_equal(value *a, value *b);
value *eval_order_seq(value *a, value *b);
value *eval_order_leq(value *a, value *b);
value *eval_order_smaller(value *a, value *b);
value *eval_order_larger(value *a, value *b);

/*
 * Top-level expression evaluation
 */
value *eval_expr(arena_state *s, expr *ex);

/*
 * Statement evaluation
 */
void eval_stmt(arena_state *s, stmt *st, int cookie);
void eval_stmt_switch(arena_state *s, stmt *st, int cookie);
void eval_stmt_list(arena_state *s, stmt_list *list, int cookie);

#endif
