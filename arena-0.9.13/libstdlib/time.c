/*
 * Date and time functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stdlib.h"

/*
 * Get current time
 *
 * Returns the time in seconds since 1970-01-01 00:00:00.
 */
value *time_time(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_int(time(NULL));
}

/*
 * Create date and time structure
 */
static value *mktimestruct(struct tm *when)
{
  value *st, *val;
  
  st = value_make_struct();
  
  val = value_make_int(when->tm_sec);
  value_set_struct(st, "tm_sec", val); value_free(val);
  
  val = value_make_int(when->tm_min);
  value_set_struct(st, "tm_min", val); value_free(val);
  
  val = value_make_int(when->tm_hour);
  value_set_struct(st, "tm_hour", val); value_free(val);
  
  val = value_make_int(when->tm_mday);
  value_set_struct(st, "tm_mday", val); value_free(val);
  
  val = value_make_int(when->tm_mon);
  value_set_struct(st, "tm_mon", val); value_free(val);
  
  val = value_make_int(when->tm_year);
  value_set_struct(st, "tm_year", val); value_free(val);
  
  val = value_make_int(when->tm_wday);
  value_set_struct(st, "tm_wday", val); value_free(val);
  
  val = value_make_int(when->tm_yday);
  value_set_struct(st, "tm_yday", val); value_free(val);

  val = value_make_int(when->tm_isdst);
  value_set_struct(st, "tm_isdst", val); value_free(val);
  
  return st;
}

/*
 * Make UTC time structure
 *
 * Takes an time in seconds since the epoch and creates a
 * structure containing broken-out time values. It assumes UTC
 * as the local timezone.
 */
value *time_gmtime(arena_state *s, unsigned int argc, value **argv)
{
  return mktimestruct(gmtime((time_t *) &argv[0]->value_u.int_val));
}

/*
 * Make local time structure
 *
 * Takes an time in seconds since the epoch and creates a
 * structure containing broken-out time values. It assumes
 * the default local timezone of the system.
 */
value *time_localtime(arena_state *s, unsigned int argc, value **argv)
{
  return mktimestruct(localtime((time_t *) &argv[0]->value_u.int_val));
}

/*
 * Helper function to get an int from a struct
 */
static int getint(symtab *sym, const char *name)
{
  symtab_entry *entry;

  entry = symtab_lookup(sym, name);
  if (!entry || entry->type != SYMTAB_ENTRY_VAR ||
      entry->entry_u.var->type != VALUE_TYPE_INT) {
    return 0;
  } else {
    return entry->entry_u.var->value_u.int_val;
  }
}

/*
 * Make C struct tm from struct value
 */
static struct tm mkstructtm(value *st)
{
  symtab *sym = st->value_u.struct_val;
  struct tm t;

  memset(&t, 0, sizeof(struct tm));

  t.tm_sec   = getint(sym, "tm_sec");
  t.tm_min   = getint(sym, "tm_min");
  t.tm_hour  = getint(sym, "tm_hour");
  t.tm_mday  = getint(sym, "tm_mday");
  t.tm_mon   = getint(sym, "tm_mon");
  t.tm_year  = getint(sym, "tm_year");
  t.tm_wday  = getint(sym, "tm_wday");
  t.tm_yday  = getint(sym, "tm_yday");
  t.tm_isdst = getint(sym, "tm_isdst");

  return t;
}

/*
 * Convert time structure to time int
 */
value *time_mktime(arena_state *s, unsigned int argc, value **argv)
{
  struct tm t = mkstructtm(argv[0]);
  
  return value_make_int(mktime(&t));
}

/*
 * String representation of time structure
 */
value *time_asctime(arena_state *s, unsigned int argc, value **argv)
{
  struct tm t = mkstructtm(argv[0]);
  
  return value_make_string(asctime(&t));
}

/*
 * String representation of time value
 */
value *time_ctime(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_string(ctime((time_t *) &argv[0]->value_u.int_val));
}

/*
 * Format time
 *
 * This function returns a string containing a formatted time
 * value.
 */
value *time_strftime(arena_state *s, unsigned int argc, value **argv)
{
  char *fmt   = argv[0]->value_u.string_val.value;
  struct tm t = mkstructtm(argv[1]);
  char buf[1024];

  if (!fmt) {
    return value_make_string(NULL);
  }
  
  buf[1023] = 0;
  strftime(buf, 1023, fmt, &t);

  return value_make_string(buf);
}
