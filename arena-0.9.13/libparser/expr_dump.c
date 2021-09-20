/*
 * Expression dumping
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/*
 * Determine operator precedence
 */
static int expr_prec(expr *ex, int *assoc)
{
  int res = 0;

  if (ex->type == EXPR_ASSIGN || ex->type == EXPR_ASSIGN_ARRAY) {
    *assoc = 1;
    return 0;
  }
  
  if (ex->type == EXPR_IF) {
    *assoc = 0;
    return 1;
  }

  if (ex->type == EXPR_PREFIX && ex->op == OPTYPE_MINUS) {
    *assoc = -1;
    return 11;
  }
  
  if (ex->type == EXPR_CAST) {
    *assoc = 1;
    return 13;
  }

  if (ex->type != EXPR_PREFIX &&
      ex->type != EXPR_INFIX  &&
      ex->type != EXPR_POSTFIX) {
    *assoc = 0;
    return 255;
  } 

  switch (ex->op) {
    case OPTYPE_BOOL_OR:
      *assoc = 1;
      res = 2;
      break;
    case OPTYPE_BOOL_AND:
      *assoc = 1;
      res = 3;
      break;
    case OPTYPE_NOT:
      *assoc = 1;
      res = 4;
      break;
    case OPTYPE_EQUAL:
    case OPTYPE_NOT_EQUAL:
    case OPTYPE_SEQ:
    case OPTYPE_LEQ:
    case OPTYPE_SMALLER:
    case OPTYPE_LARGER:
      *assoc = 0;
      res = 5;
      break;
    case OPTYPE_AND:
    case OPTYPE_OR:
    case OPTYPE_XOR:
      *assoc = -1;
      res = 6;
      break;
    case OPTYPE_PLUS:
    case OPTYPE_MINUS:
      *assoc = -1;
      res = 7;
      break;
    case OPTYPE_MUL:
    case OPTYPE_DIV:
    case OPTYPE_MOD:
      *assoc = -1;
      res = 8;
      break;
    case OPTYPE_POW:
      *assoc = 1;
      res = 9;
      break;
    case OPTYPE_LSHIFT:
    case OPTYPE_RSHIFT:
      *assoc = -1;
      res = 10;
      break;
    case OPTYPE_NEG:
      *assoc = -1;
      res = 11;
      break;
    case OPTYPE_POSTDEC:
    case OPTYPE_POSTINC:
    case OPTYPE_PREDEC:
    case OPTYPE_PREINC:
      *assoc = -1;
      res = 12;
      break;
  }
  return res;
}

/*
 * Print operator symbol
 */
static void optype_dump(op_type type)
{
  switch (type) {
    case OPTYPE_PLUS:
      printf("+");
      break;
    case OPTYPE_MINUS:
      printf("-");
      break;
    case OPTYPE_MUL:
      printf("*");
      break;
    case OPTYPE_DIV:
      printf("/");
      break;
    case OPTYPE_MOD:
      printf("%%");
      break;
    case OPTYPE_BOOL_AND:
      printf("&&");
      break;
    case OPTYPE_BOOL_OR:
      printf("||");
      break;
    case OPTYPE_AND:
      printf("&");
      break;
    case OPTYPE_OR:
      printf("|");
      break;
    case OPTYPE_XOR:
      printf("^");
      break;
    case OPTYPE_POW:
      printf("**");
      break;
    case OPTYPE_EQUAL:
      printf("==");
      break;
    case OPTYPE_NOT_EQUAL:
      printf("!=");
      break;
    case OPTYPE_SEQ:
      printf("<=");
      break;
    case OPTYPE_LEQ:
      printf(">=");
      break;
    case OPTYPE_SMALLER:
      printf("<");
      break;
    case OPTYPE_LARGER:
      printf(">");
      break;
    case OPTYPE_POSTINC:
    case OPTYPE_PREINC:
      printf("++");
      break;
    case OPTYPE_POSTDEC:
    case OPTYPE_PREDEC:
      printf("--");
      break;
    case OPTYPE_NOT:
      printf("!");
      break;
    case OPTYPE_NEG:
      printf("~");
      break;
    case OPTYPE_LSHIFT:
      printf("<<");
      break;
    case OPTYPE_RSHIFT:
      printf(">>");
      break;
  }
}

/*
 * Print function call arguments
 */
static void expr_dump_args(unsigned int argc, expr **argv)
{
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    expr_dump(argv[i]);
    if (i + 1 < argc) printf(", ");
  }
}

/*
 * Print array indexing expressions
 */
static void expr_dump_index(unsigned int argc, expr **argv)
{
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    if (argv[i]->type != EXPR_FIELD) {
      printf("[");
      expr_dump(argv[i]);
      printf("]");
    } else {
      expr_dump(argv[i]);
    }
  }
}

/*
 * Print optional parenthesis around expression
 */
void parenthesis(expr *outer, expr *inner, int assoc)
{
  int iprec, oprec, iassoc = 0, oassoc = 0;
  
  oprec = expr_prec(outer, &oassoc);
  iprec = expr_prec(inner, &iassoc);

  if (oprec > iprec || (oprec == iprec && assoc != iassoc)) {
    printf("(");
    expr_dump(inner);
    printf(")");
  } else {
    expr_dump(inner);
  }
}

/*
 * Indexing without parenthesis allowed?
 */
static int is_indexable(expr_type type)
{
  return (type == EXPR_CALL   ||
          type == EXPR_NEW    ||
          type == EXPR_STATIC ||
          type == EXPR_METHOD ||
          type == EXPR_INDEX);
}

/*
 * Print expression dump
 */
void expr_dump(expr *ex)
{
  if (!ex) return;
  
  switch (ex->type) {
    case EXPR_NOP:
      break;
    case EXPR_ASSIGN:
      printf("%s = ", ex->name);
      parenthesis(ex, ex->inner, 1);
      break;
    case EXPR_ASSIGN_ARRAY:
      printf(ex->name);
      expr_dump_index(ex->argc, ex->argv);
      printf(" = ");
      parenthesis(ex, ex->inner, 1);
      break;
    case EXPR_CAST:
      printf("(%s) ", ex->name);
      parenthesis(ex, ex->inner, 1);
      break;
    case EXPR_CALL:
      printf("%s(", ex->name);
      expr_dump_args(ex->argc, ex->argv);
      printf(")");
      break;
    case EXPR_NEW:
      printf("new %s(", ex->name);
      expr_dump_args(ex->argc, ex->argv);
      printf(")");
      break;
    case EXPR_STATIC:
      printf("%s::%s(", ex->tname, ex->name);
      expr_dump_args(ex->argc, ex->argv);
      printf(")");
      break;
    case EXPR_METHOD:
      expr_dump(ex->inner);
      printf(".%s(", ex->name);
      expr_dump_args(ex->argc, ex->argv);
      printf(")");
      break;
    case EXPR_REF:
      printf(ex->name);
      break;
    case EXPR_REF_ARRAY:
      printf(ex->name);
      expr_dump_index(ex->argc, ex->argv);
      break;
    case EXPR_INDEX:
      if (!is_indexable(ex->inner->type)) {
        printf("(");
      }
      expr_dump(ex->inner);
      if (!is_indexable(ex->inner->type)) {
        printf(")");
      }
      expr_dump_index(ex->argc, ex->argv);
      break;
    case EXPR_CONST_VOID:
      printf("()");
      break;
    case EXPR_CONST_BOOL:
    case EXPR_CONST_INT:
    case EXPR_CONST_FLOAT:
      printf(ex->name);
      break;
    case EXPR_CONST_STRING:
      printf("\"%s\"", ex->name);
      break;
    case EXPR_INFIX:
      parenthesis(ex, ex->inner, -1);
      printf(" ");
      optype_dump(ex->op);
      printf(" ");
      parenthesis(ex, ex->index, 1);
      break;
    case EXPR_POSTFIX:
      parenthesis(ex, ex->inner, 1);
      optype_dump(ex->op);
      break;
    case EXPR_PREFIX:
      optype_dump(ex->op);
      parenthesis(ex, ex->inner, -1);
      break;
    case EXPR_FIELD:
      printf(".%s", ex->name);
      break;
    case EXPR_STATIC_REF:
      printf("%s::%s", ex->tname, ex->name);
      break;
    case EXPR_LAMBDA:
      stmt_dump_mode(1);
      stmt_dump(ex->lambda);
      stmt_dump_mode(0);
      break;
    case EXPR_IF:
      parenthesis(ex, ex->inner, 2);
      printf(" ? ");
      parenthesis(ex, ex->index, 2);
      printf(" : ");
      parenthesis(ex, ex->elif, 2);
      break;
    case EXPR_PASS_REF:
      printf("&");
      parenthesis(ex, ex->inner, 0);
      break;
    case EXPR_FILE:
      printf("__FILE__");
      break;
    case EXPR_LINE:
      printf("__LINE__");
      break;
  }
}
