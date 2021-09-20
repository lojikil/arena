/*
 * Error printing
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdarg.h>
#include <stdio.h> 
#include <stdlib.h>
 
#include "misc.h"

/*
 * Write error message
 */
static void errmsg(arena_state *s, int abort, const char *msg, va_list ap)
{
  char *source_file;

  if (!s || !s->source_file) {
    source_file = "arena";
  } else {
    source_file = s->source_file;
  }

  if (s && s->source_col > 0) {
    fprintf(stderr, "%s:%i:%i: ", source_file, s->source_line, s->source_col);
  } else if (s && s->source_line > 0) {
    fprintf(stderr, "%s:%i: ", source_file, s->source_line);
  } else {
    fprintf(stderr, "%s: ", source_file);
  }

  vfprintf(stderr, msg, ap);
  fprintf(stderr, "\n");

  if (abort) {
    if (s) {
      s->exit_flag  = 1;
      s->exit_value = -1;
    } else {
      exit(1);
    }
  }
}

/*
 * Write fatal error message
 *
 * This function prints a fatal error message. Execution of the
 * running program is aborted.
 */
void fatal(arena_state *s, const char *msg, ...)
{
  va_list ap;
  
  va_start(ap, msg);
  errmsg(s, 1, msg, ap);
  va_end(ap);
}

/*
 * Write nonfatal error message
 *
 * This function prints an error message. Execution of the
 * running program continues as normal.
 */
void nonfatal(arena_state *s, const char *msg, ...)
{
  va_list ap;
  
  va_start(ap, msg);
  errmsg(s, 0, msg, ap);
  va_end(ap);
}

/*
 * Report an internal error
 *
 * This function prints an internal error message and is invoked
 * whenever an interpreter core function is passed impossible
 * values.
 */
void internal(const char *file, int line)
{
  fatal(NULL, "internal error at %s:%i", file, line);
}

/*
 * Report out-of-memory conditions
 *
 * This function prints a message about an out-of-memory condition
 * and aborts the running program if the given pointer is NULL.
 */
void *oom(void *ptr)
{
  if (!ptr) {
    fatal(NULL, "out of memory");
  }
  return ptr;
}
