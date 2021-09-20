/*
 * Locale functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "stdlib.h"

/*
 * Get current locale
 */
value *lc_getlocale(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_string(setlocale(LC_ALL, NULL));
}

/*
 * Set current locale
 */
value *lc_setlocale(arena_state *s, unsigned int argc, value **argv)
{
  char *name = argv[0]->value_u.string_val.value;
  char *res = NULL;
  
  if (!name) {
    res = setlocale(LC_ALL, "");
  } else {
    res = setlocale(LC_ALL, name);
  }
  if (!res) {
    return value_make_void();
  }
  return value_make_string(res);
}

/*
 * Add one-character string to struct
 */
static void addchr(value *s, const char *name, char what)
{
  value *elem;
  char buf[2];
  
  buf[0] = what;
  buf[1] = 0;

  elem = value_make_string(buf);
  value_set_struct(s, name, elem);
  value_free(elem);
}

/*
 * Add string to struct
 */
static void addstr(value *s, const char *name, char *what)
{
  value *elem;
  
  elem = value_make_string(what);
  value_set_struct(s, name, elem);
  value_free(elem);
}

/*
 * Get current locale conventions
 */
value *lc_localeconv(arena_state *s, unsigned int argc, value **argv)
{
  struct lconv *lc;
  value *ret;

  lc = localeconv();
  if (!lc) {
    return value_make_void();
  }
  
  ret = value_make_struct();
  
  addstr(ret, "decimal_point", lc->decimal_point);
  addstr(ret, "thousands_sep", lc->thousands_sep);
  addstr(ret, "grouping", lc->grouping);
  addstr(ret, "int_curr_symbol", lc->int_curr_symbol);
  addstr(ret, "currency_symbol", lc->currency_symbol);
  addstr(ret, "mon_decimal_point", lc->mon_decimal_point);
  addstr(ret, "mon_thousands_sep", lc->mon_thousands_sep);
  addstr(ret, "mon_grouping", lc->mon_grouping);
  addstr(ret, "positive_sign", lc->positive_sign);
  addstr(ret, "negative_sign", lc->negative_sign);
  addchr(ret, "int_frac_digits", lc->int_frac_digits);
  addchr(ret, "frac_digits", lc->frac_digits);
  addchr(ret, "p_cs_precedes", lc->p_cs_precedes);
  addchr(ret, "p_sep_by_space", lc->p_sep_by_space);
  addchr(ret, "n_cs_precedes", lc->n_cs_precedes);
  addchr(ret, "n_sep_by_space", lc->n_sep_by_space);
  addchr(ret, "p_sign_posn", lc->p_sign_posn);
  addchr(ret, "n_sign_posn", lc->n_sign_posn);
  
  return ret;
}
