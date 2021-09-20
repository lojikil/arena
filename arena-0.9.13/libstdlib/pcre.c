/*
 * PCRE regular expression functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "stdlib.h"

#if WANT_PCRE == 1 && HAVE_PCRE_COMPILE == 1

#include <pcre.h>

/*
 * Internal data for a compiled regular expression
 */
typedef struct {
  pcre			*data;
  unsigned char 	*table;
} pregdata;

/*
 * Data structure for defining PCRE option values
 */
typedef struct {
  const char 		*name;
  int 			value;
} pregopt;

/*
 * Table of supported PCRE option values
 */
static pregopt pregopts[] = {
  { "PRCE_ANCHORED",		PCRE_ANCHORED,		},
  { "PCRE_CASELESS",		PCRE_CASELESS,		},
  { "PCRE_DOLLAR_ENDONLY",	PCRE_DOLLAR_ENDONLY,	},
  { "PCRE_DOTALL",		PCRE_DOTALL,		},
  { "PCRE_EXTENDED",		PCRE_EXTENDED,		},
  { "PCRE_MULTILINE",		PCRE_MULTILINE,		},
  { "PCRE_UNGREEDY",		PCRE_UNGREEDY,		},
  { "PCRE_NOTBOL",		PCRE_NOTBOL,		},
  { "PCRE_NOTEOL",		PCRE_NOTEOL,		},
  { "PCRE_NOTEMPTY",		PCRE_NOTEMPTY,		},
  { NULL,			0			}
};

/*
 * Initialize PCRE support by defining all option values
 */
void preg_init(arena_state *s)
{
  pregopt *next = &pregopts[0];
  value *val;
  
  while (next->name) {
    val = value_make_int(next->value);
    symtab_stack_add_variable(s, next->name, val);
    value_free(val);
    next++;
  }
}

/*
 * Free internal data of a compiled regular expression
 */
static void pregdata_free(void *data)
{
  pregdata *pd = data;

  if (pd) free(pd->data);
  if (pd) free(pd->table);
  free(pd);
}

/*
 * Initialize internal data for a compiled regular expression
 */
static pregdata *pregdata_init(pcre *data, const unsigned char *table)
{
  pregdata *res;
  
  res = oom(malloc(sizeof(pregdata)));
  res->data = data;
  res->table = (unsigned char *) table;
  
  return res;
}

/*
 * Get compiled regexp pointer from resource
 */
static void *pregdata_get(void *data)
{
  pregdata *pd = data;
  
  if (!pd) {
    return NULL;
  }
  return pd->data;
}

/*
 * Check whether a value is a regular expression resource
 */
static int is_preg(value *val)
{
  return (val->value_u.res_val->release == pregdata_free);
}

/*
 * Check whether resourse is PCRE resource
 */
value *preg_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(is_preg(argv[0]));
}

/*
 * Return true to indicate present PCRE support
 */
value *preg_supported(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(1);
}

/*
 * Compile regular expression into PCRE resource
 */
value *preg_compile(arena_state *s, unsigned int argc, value **argv)
{
  char *pat = STR_OF(argv[0]);
  int opts  = INT_OF(argv[1]);
  const unsigned char *table;
  pcre *comp;
  const char *err;
  int erroffset;
  value *res;
  
  if (!value_str_compat(argv[0])) {
    return value_make_void();
  }
  
  table = pcre_maketables();
  if (!table) {
    return value_make_void();
  }
  
  comp = pcre_compile(pat, opts, &err, &erroffset, table);
  if (!comp) {
    nonfatal(s, "pcre error: %s (offset %i)", err, erroffset);
    return value_make_void();
  }

  res = value_make_resource(pregdata_init(comp, table), pregdata_free);
  res->value_u.res_val->get = pregdata_get;
  return res;
}

/*
 * Run compiled regular expression on some string
 *
 * This function tries to match an input string with a previously
 * compiled regular expression. Depending on the matches parameter,
 * either a bool or an array of matching substrings is returned.
 */
static value *preg_run(arena_state *s, unsigned int argc, value **argv,
  int matches)
{
  pregdata *pd = RESDATA_OF(argv[0]);
  int len      = STRLEN_OF(argv[1]);
  char *str    = STR_OF(argv[1]);
  int opts     = INT_OF(argv[2]);
  int i, res, subs = 0;
  int *ovector;
  char *start;
  value *info, *elem;
  
  if (!is_preg(argv[0]) || !value_str_compat(argv[1]) || !pd) {
    return value_make_void();
  }
  
  pcre_fullinfo(pd->data, NULL, PCRE_INFO_CAPTURECOUNT, &subs);
  ++subs;

  ovector = malloc(subs * 3 * sizeof(int));
  if (!ovector) {
    return value_make_void();
  }
  
  res = pcre_exec(pd->data, NULL, str, len, 0, opts, ovector, subs * 3);
  if (res < -1) {
    free(ovector);
    return value_make_void();
  }

  if (!matches) {
    free(ovector);
    return value_make_bool(res > 0);
  }
  
  info = value_make_array();
  for (i = 0; i < res; ++i) {
    if (ovector[2 * i] == -1) {
      elem = value_make_void();
    } else {
      start = str + ovector[2 * i];
      elem = value_make_memstring(start, ovector[2 * i + 1] - ovector[2 * i]);
    }
    value_add_to_array(info, elem);
    value_free(elem);
  }
  
  free(ovector);
  return info;
}

/*
 * Try to match regular expression
 *
 * This function returns true if a precompiled regular expression
 * matches a given string. It returns false otherwise.
 */
value *preg_match(arena_state *s, unsigned int argc, value **argv)
{
  return preg_run(s, argc, argv, 0);
}

/*
 * Return matching substrings
 *
 * This function returns an array of matching substring for the
 * given precompiled regular expression and input string. The
 * result is an empty array if the regexp does not match.
 */
value *preg_exec(arena_state *s, unsigned int argc, value **argv)
{
  return preg_run(s, argc, argv, 1);
}

/* 
 * Free data of a precompiled regular expression
 */
value *preg_free(arena_state *s, unsigned int argc, value **argv)
{
  pregdata *pd = RESDATA_OF(argv[0]);
  
  if (is_preg(argv[0]) && pd) {
    pregdata_free(pd);
    RESDATA_OF(argv[0]) = NULL;
  }
  return value_make_void();
}

#else

/*
 * No initialization if PCRE not supported
 */
void preg_init(arena_state *s)
{
}

/*
 * Return false to indicate PRCE is not supported
 */
value *preg_supported(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(0);
}

/*
 * Dummy function
 */
value *preg_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(0);
}

/*
 * Dummy function
 */
value *preg_compile(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *preg_match(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *preg_exec(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *preg_free(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

#endif
