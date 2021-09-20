/*
 * System environment functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "stdlib.h"

/*
 * Terminate program
 *
 * Terminates the program and returns its int argument as
 * the program's exit status.
 */
value *sys_exit(arena_state *s, unsigned int argc, value **argv)
{
  int status = argv[0]->value_u.int_val;

  s->exit_flag  = 1;
  s->exit_value = status;
  return value_make_void();
}

/*
 * Get environment value
 *
 * Tries to get the value of the given environment variable. Returns
 * the value as a string on success, or void on failure.
 */
value *sys_getenv(arena_state *s, unsigned int argc, value **argv)
{
  const char *name = argv[0]->value_u.string_val.value;
  char *env;
  
  if (!value_str_compat(argv[0]) || !(env = getenv(name))) {
    return value_make_void();
  }
  return value_make_string(env);
}

/*
 * Execute system command
 *
 * Hands off the command given as the first argument to the system's
 * command interpreter. Returns the exit code of the command on
 * success, or void on failure.
 */
value *sys_system(arena_state *s, unsigned int argc, value **argv)
{
  const char *cmd = argv[0]->value_u.string_val.value;
  int res;
  
  if (!value_str_compat(argv[0])) {
    return value_make_void();
  }
  res = system(cmd);
  if (res == -1) {
    return value_make_void();
  }
  return value_make_int(res);
}
