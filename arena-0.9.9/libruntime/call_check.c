/*
 * Function call type checking
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h>
#include <stdlib.h>

#include "runtime.h"
 
/*
 * Return character corresponding to type
 *
 * Returns a one-character encoding of the type of the given value.
 */
char call_typechar(const value *val)
{
  switch (val->type) {
    case VALUE_TYPE_VOID:
      return 'v';
    case VALUE_TYPE_BOOL:
      return 'b';
    case VALUE_TYPE_INT:
      return 'i';
    case VALUE_TYPE_FLOAT:
      return 'f';
    case VALUE_TYPE_STRING:
      return 's';
    case VALUE_TYPE_ARRAY:
      return 'a';
    case VALUE_TYPE_STRUCT:
      return 'c';
    case VALUE_TYPE_FN:
      return 'p';
    case VALUE_TYPE_RES:
      return 'r';
  }
  return '?';
}

/*
 * Return type corresponding to character
 */
int call_chartype(char val)
{
  switch(val) {
    case 'b':
      return VALUE_TYPE_BOOL;
    case 'i':
      return VALUE_TYPE_INT;
    case 'f':
      return VALUE_TYPE_FLOAT;
    case 's':
      return VALUE_TYPE_STRING;
    case 'a':
      return VALUE_TYPE_ARRAY;
    case 'c':
      return VALUE_TYPE_STRUCT;
    case 'p':
      return VALUE_TYPE_FN;
    case 'r':
      return VALUE_TYPE_RES;
    default:
      return VALUE_TYPE_VOID;
  }
}

/*
 * Return name corresponding to type
 */
const char *call_typename(value_type type)
{
  const char *name = NULL;

  switch (type) {
    case VALUE_TYPE_VOID:
      name = "void";
      break;
    case VALUE_TYPE_BOOL:
      name = "bool";
      break;
    case VALUE_TYPE_INT:
      name = "int";
      break;
    case VALUE_TYPE_FLOAT:
      name = "float";
      break;
    case VALUE_TYPE_STRING:
      name = "string";
      break;
    case VALUE_TYPE_ARRAY:
      name = "array";
      break;
    case VALUE_TYPE_STRUCT:
      name = "struct";
      break;
    case VALUE_TYPE_FN:
      name = "fn";
      break;
    case VALUE_TYPE_RES:
      name = "resource";
      break;
  }
  return name;
}

/*
 * Type-check function call
 *
 * This function checks the given function signature against the
 * given arguments. It returns 0 if the function may be called with
 * those arguments or -1 on failure.
 */
void call_check(arena_state *s, const char *name, signature *sig,
  unsigned int argc, value **argv)
{
  char *arg;
  unsigned int i = 0;

  sanity(name && sig && (argc == 0 || argv));

  if (argc < sig->args) {
    fatal(s, "function `%s': missing arguments (got %u of %u)", name,
      argc, sig->args);
    return;
  }
  if (sig->args == 0 && !sig->proto) {
    return;
  }
  arg = sig->proto;
  while (*arg) {
    if (*arg == '*') return;
    
    sanity(argv[i]);

    if (*arg != '?' && call_typechar(argv[i]) != tolower(*arg)) {
      if (islower(*arg)) {
        fatal(s, "function `%s': arg %u type mismatch (`%s' instead of `%s')",
          name, i + 1, call_typename(argv[i]->type),
          call_typename(call_chartype(*arg))
        );
        return;
      } else {
        value_cast_inplace(s, &argv[i], call_chartype(tolower(*arg)));
      }
    }

    i++;
    arg++;
  }
}
