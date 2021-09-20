/*
 * Statement dumping
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/*
 * Printing mode (0 = normal, > 0 = inside lambda expression)
 */
static int dump_mode = 0;

/*
 * Current indentation level
 */
static int depth = 0;

/*
 * Print indentation prefix
 */
static void prefix(void)
{
  int i;

  if (dump_mode == 0) {
    for (i = 0; i < depth * 2; i++) {
      putchar(' ');
    }
  }
}

static void newline(void)
{
  if (dump_mode == 0) {
    printf("\n");
  } else {
    printf(" ");
  }
}

/*
 * Print function arguments dump
 */
static void stmt_proto_dump(char *args, char **names)
{
  if (!args) return;
  
  while (*args != 0) {
    if (isupper(*args)) {
      printf("forced ");
    }
    switch (tolower(*args)) {
      case 'v':
        printf("void");
        break;
      case 'b':
        printf("bool");
        break;
      case 'i':
        printf("int");
        break;
      case 'f':
        printf("float");
        break;
      case 's':
        printf("string");
        break;
      case 'a':
        printf("array");
        break;
      case 'p':
        printf("fn");
        break;
      case '?':
        printf("mixed");
        break;
    }
    if (names) {
      printf(" %s", *names);
    }
    ++args;
    if (*args != 0) {
      printf(", ");
    }
  }
}

/*
 * Dump function
 */
static void stmt_dump_func(stmt *st)
{
  char buf[2];

  if (dump_mode == 0) {
    buf[0] = st->rettype;
    buf[1] = 0;
    stmt_proto_dump(buf, NULL);
    printf(" %s(", st->name);
  } else {
    printf("\\ (");
  }
  stmt_proto_dump(st->proto, st->names);
  printf(")"); newline();
  stmt_dump(st->true_case);
}

/*
 * Print statement dump
 */
void stmt_dump(stmt *st)
{
  sanity(st);
  
  prefix();
  switch (st->type) {
    case STMT_NOP:
      printf(";"); newline();
      break;
    case STMT_BLOCK:
      printf("{"); newline();
      ++depth;
      stmt_list_dump((stmt_list *) st->block, 1);
      --depth;
      prefix();
      printf("}"); newline();
      break;
    case STMT_IF:
      printf("if (");
      expr_dump(st->expr);
      printf(")"); newline();
      ++depth;
      stmt_dump(st->true_case);
      --depth;
      break;
    case STMT_IF_ELSE:
      printf("if (");
      expr_dump(st->expr);
      printf(")"); newline();
      ++depth;
      stmt_dump(st->true_case);
      --depth;
      prefix();
      printf("else"); newline();
      ++depth;
      stmt_dump(st->false_case);
      --depth;
      break;
    case STMT_WHILE:
      printf("while (");
      expr_dump(st->expr);
      printf(")"); newline();
      ++depth;
      stmt_dump(st->true_case);
      --depth;
      break;
    case STMT_DO:
      printf("do"); newline();
      ++depth;
      stmt_dump(st->true_case);
      --depth;
      prefix();
      printf("while (");
      expr_dump(st->expr);
      printf(")");
      break;
    case STMT_FOR:
      printf("for (");
      expr_dump(st->init);
      printf("; ");
      expr_dump(st->expr);
      printf("; ");
      expr_dump(st->guard);
      printf(")"); newline();
      ++depth;
      stmt_dump(st->true_case);
      --depth;
      break;
    case STMT_CONTINUE:
      printf("continue;"); newline();
      break;
    case STMT_BREAK:
      printf("break;"); newline();
      break;
    case STMT_RETURN:
      printf("return");
      if (st->expr) {
        printf(" ");
        expr_dump(st->expr);
      }
      printf(";"); newline();
      break;
    case STMT_EXPR:
      expr_dump(st->expr);
      printf(";"); newline();
      break;
    case STMT_FUNC:
      stmt_dump_func(st);
      break;
    case STMT_SWITCH:
      printf("switch (");
      expr_dump(st->expr);
      printf(") {"); newline();
      ++depth;
      stmt_list_dump((stmt_list *) st->block, 1);
      --depth;
      prefix();
      printf("}"); newline();
      break;
    case STMT_CASE:
      printf("case ");
      expr_dump(st->expr);
      printf(":"); newline();
      ++depth;
      stmt_list_dump((stmt_list *) st->block, 1);
      if (!st->thru) {
        prefix();
        printf("break;"); newline();
      }
      --depth;
      break;
    case STMT_DEFAULT:
      printf("default:"); newline();
      ++depth;
      stmt_list_dump((stmt_list *) st->block, 1);
      --depth;
      break;
    case STMT_TRY:
      printf("try"); newline();
      ++depth;
      stmt_dump(st->true_case);
      --depth;
      prefix();
      printf("catch (%s)", st->name); newline();
      ++depth;
      stmt_dump(st->false_case);
      --depth;
      break;
    case STMT_THROW:
      printf("throw ");
      expr_dump(st->expr);
      printf(";"); newline();
      break;
    case STMT_TMPL:
      printf("template %s", st->name);
      if (st->proto) {
        printf(" extends %s", st->proto);
      }
      newline();
      prefix();
      printf("{"); newline();
      ++depth;
      stmt_list_dump((stmt_list *) st->block, 1);
      --depth;
      prefix();
      printf("}"); newline();
  }
}

/*
 * Print statement list dump
 */
void stmt_list_dump(stmt_list *list, int internal)
{
  unsigned int i;

  if (!internal) depth = 0;
  if (!list) return;
  
  for (i = 0; i < list->len; i++) {
    stmt_dump(list->list[i]);
  }
}

/*
 * Set dump mode
 */
void stmt_dump_mode(int mode)
{
  if (mode) {
    ++dump_mode;
  } else {
    --dump_mode;
  }
}
