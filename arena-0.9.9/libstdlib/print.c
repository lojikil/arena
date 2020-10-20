/*
 * Printing functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdlib.h"

/*
 * Turn \0 bytes into spaces
 */
void pad_zeros(value *str)
{
  int len = str->value_u.string_val.len;
  char *where;
  
  if (len > 0) {
    while ((where = memchr(str->value_u.string_val.value, 0, len)) != NULL) {
      *where = ' ';
    }
  }
}

/*
 * Dump parameter values
 *
 * This function prints out a dump of all its parameters.
 */
value *print_dump(arena_state *s, unsigned int argc, value **argv)
{
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    value_dump(argv[i], 0, 0);
  }
  
  return value_make_void();
}

/*
 * Print values as strings
 *
 * This function casts all its parameters to string and then
 * prints them out with no intervening newlines.
 */
value *print_print(arena_state *s, unsigned int argc, value **argv)
{
  unsigned int i;

  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_STRING);
    if (argv[i]->value_u.string_val.len > 0) {
      pad_zeros(argv[i]);
      printf("%s", argv[i]->value_u.string_val.value);
    }
  }
  
  return value_make_void();
}

/*
 * Turn conversion specifier into type enum
 */
static int spectype(char spec)
{
  if (spec == 'f') {
    return VALUE_TYPE_FLOAT;
  } else if (spec == 's') {
    return VALUE_TYPE_STRING;
  } else {
    return VALUE_TYPE_INT;
  }
}

/*
 * Parse format string
 *
 * This function parses one format specification from a printf format
 * string. It skips over unknown character inside the spec, returns the
 * parsed format spec, and stores the expected type of the argument in
 * the given int pointer.
 */
static char *parse_fmt(char **i, int *min, int *valtype, char *buf)
{
  char *stop, *pos;
  int len;

  *min     = 0;
  *valtype = 0;
  buf[0]   = '%';
  buf[1]   = 0;
  pos      = buf + 1;

  /* escaped percent sign */
  if (**i == '%') {
    *pos++ = '%';
    *pos   = 0;
    (*i)++;
    return buf;
  }

  /* conversion flags */  
  len = strspn(*i, "-+#0 ");
  if (len > 0) {
    strncat(buf, *i, len);
    *i  += len;
    pos += len;
  }

  /* display width */  
  len = strspn(*i, "0123456789");
  if (len > 0) {
    strncat(buf, *i, len);
    *min = atoi(*i);
    *i  += len;
    pos += len;
  }
  
  /* dispay precision */
  if (**i == '.') {
    len = strspn(*i + 1, "0123456789");
    strncat(buf, *i, len + 1);
    *i  += len + 1;
    pos += len + 1;
  }

  /* conversion specifier */  
  stop = strpbrk(*i, "fsdioxX");
  if (stop) {
    *valtype = spectype(*stop);
    *pos++   = *stop;
    *pos     = 0;
    *i       = stop + 1;
  } else {
    *i += strlen(*i);
  }

  return buf;
}

/*
 * Formatted printing
 */
static value *doformat(arena_state *s, unsigned int argc, value **argv,
  int ret)
{
  char *fmt = argv[0]->value_u.string_val.value;
  char *cfmt, *fmtbuf;
  char *buf = NULL;
  int min = 0;
  int len = 0, valtype, vallen = 0, span = 0;
  unsigned int arg = 1;
  value *val, *curr, *voidval;
  
  if (!fmt) {
    return value_make_string(NULL);
  }
  voidval = value_make_void();

  fmtbuf = oom(malloc(512));

  pad_zeros(argv[0]);

  while (*fmt) {
    span = strcspn(fmt, "%");
    if (span > 0) {
      buf = oom(realloc(buf, len + span + 1));
      if (len == 0) {
        buf[0] = 0;
      }
      strncat(buf, fmt, span);
      len += span;
      fmt += span;
      buf[len] = 0;
    } else {
      ++fmt;
      cfmt = parse_fmt(&fmt, &min, &valtype, fmtbuf);
      
      if (valtype > 0) {
        if (arg < argc) {
          curr = argv[arg];
        } else {
          curr = voidval;
        }
        value_cast_inplace(s, &curr, valtype);
        if (arg < argc) {
          argv[arg] = curr;
        } else {
          voidval = curr;
        }
      }

      switch (valtype) {
        case 0:
          vallen = strlen(cfmt);
          if (min > vallen) vallen = min;
          buf = oom(realloc(buf, len + vallen + 1));
          vallen = sprintf(buf + len, cfmt);
          break;
        case VALUE_TYPE_INT:
          vallen = (min > 32) ? min : 32;
          buf = oom(realloc(buf, len + vallen + 1));
          vallen = sprintf(buf + len, cfmt, curr->value_u.int_val);
          ++arg;
          break;
        case VALUE_TYPE_FLOAT:
          vallen = (min > 64) ? min : 64;
          buf = oom(realloc(buf, len + vallen + 1));
          vallen = sprintf(buf + len, cfmt, curr->value_u.float_val);
          ++arg;
          break;
        case VALUE_TYPE_STRING:
          pad_zeros(curr);
          vallen = curr->value_u.string_val.len;
          if (min > vallen) vallen = min;
          buf = oom(realloc(buf, len + vallen + 1));
          if (curr->value_u.string_val.len > 0) {
            vallen = sprintf(buf + len, cfmt, curr->value_u.string_val.value);
          } else {
            vallen = sprintf(buf + len, cfmt, "");
          }
          ++arg;
          break;
      }
      len += vallen;
    }
  }

  free(fmtbuf);
  
  buf[len] = 0;
  
  if (ret) {
    val = value_make_string(buf);
  } else {
    printf("%s", buf);
    val = value_make_void();
  }
  free(buf);
  value_free(voidval);
  return val;
}

/* 
 * Return formatted string
 */
value *print_sprintf(arena_state *s, unsigned int argc, value **argv)
{
  return doformat(s, argc, argv, 1);
}

/*
 * Print formatted string
 */
value *print_printf(arena_state *s, unsigned int argc, value **argv)
{
  return doformat(s, argc, argv, 0);
}
