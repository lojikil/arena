/*
 * Constant expressions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"

/*
 * Evaluate void constant
 */
value *eval_const_void(void)
{
  return value_make_void();
}

/*
 * Evaluate bool constant
 */
value *eval_const_bool(expr *ex)
{
  sanity(ex);

  return value_make_bool(strcmp(ex->name, "true") == 0);
}

/*
 * Evaluate int constant
 */
value *eval_const_int(expr *ex)
{
  sanity(ex);

  return value_make_int(strtol(ex->name, NULL, 0));
}

/*
 * Evaluate float constant
 */
value *eval_const_float(expr *ex)
{
  sanity(ex);

  return value_make_float(strtod(ex->name, NULL));
}

/*
 * Character code escape
 */
static int charcode(char *orig, char **pos, int base, unsigned int maxlen)
{
  long int res, len;
  char tmp = 0;
  char *endptr = orig;

  if (strlen(orig) > maxlen) {
    tmp = orig[maxlen];
    orig[maxlen] = 0;
  }
  
  res = strtol(orig, &endptr, base);
  if (endptr != orig) {
    *(*pos) = res & 0xFF;
    (*pos) += 1;
    len = (endptr - orig) - 1;
  } else {
    len = 0;
  }
  
  if (tmp != 0) {
    orig[maxlen] = tmp;
  }
  return len;
}

/*
 * Unescape special characters
 */
static char *unescape(arena_state *s, const char *orig, int *retlen)
{
  char *raw, *pos;
  int i, len, is_esc = 0, count = 0;
  
  len = strlen(orig);
  
  raw = oom(malloc(len + 1));
  pos = raw;
  
  for (i = 0; i < len + 1; i++) {
    if (is_esc) {
      switch (orig[i]) {
        case 0:
          *retlen = 0;
          free(raw);
          fatal(s, "non-terminated string escape sequence");
          return NULL;
          break;
        case '0':
          i += charcode((char *) &orig[i], &pos, 8, 4);
          break;
        case 'b':
          *pos++ = '\b';
          break;
        case 'd':
          i += charcode((char *) &orig[i+1], &pos, 10, 3) + 1;
          break;
        case 'e':
          *pos++ = 27;
          break;
        case 'f':
          *pos++ = '\f';
          break;
        case 'n':
          *pos++ = '\n';
          break;
        case 'o':
          i += charcode((char *) &orig[i+1], &pos, 8, 3) + 1;
          break;
        case 'r':
          *pos++ = '\r';
          break;
        case 't':
          *pos++ = '\t';
          break;
        case 'x':
          i += charcode((char *) &orig[i+1], &pos, 16, 2) + 1;
          break;
        default:
          if (isdigit(orig[i])) {
            i += charcode((char *) &orig[i], &pos, 8, 3);
          } else {
            *pos++ = orig[i];
          }
      }
      is_esc = 0;
      count++;
    } else {
      switch (orig[i]) {
        case 0:
          *pos = 0;
          i = len + 1;
          break;
        case '\\':
          is_esc = 1;
          break;
        default:
          *pos++ = orig[i];
          count++;
      }
    }
  }
  *retlen = count;
  return raw;
}

/*
 * Evaluate string constant
 */
value *eval_const_string(arena_state *s, expr *ex)
{
  char *raw;
  value *val;
  int len;
  
  sanity(ex && ex->name);
  
  raw = unescape(s, ex->name, &len);
  val = value_make_memstring(raw, len);
  free(raw);
  return val;
}
