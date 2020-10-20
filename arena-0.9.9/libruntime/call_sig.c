/*
 * Function call memory
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Allocate function signature
 *
 * This function tries to allocate a new function signature structure
 * filled with zeros.
 */
signature *call_sig_alloc(void)
{
  signature *sig;

  sig = oom(calloc(sizeof(signature), 1));
  sig->rettype = '?';

  return sig;
}

/*
 * Copy signature
 *
 * This function makes a complete copy of the given function signature.
 * The prototype string contained will be a newly allocated copy.
 */
signature *call_sig_copy(const signature *sig)
{
  signature *copy;
  char *proto = NULL;
  
  if (!sig) {
    return NULL;
  }

  if (sig->proto) {
    proto = oom(malloc(strlen(sig->proto) + 1));
    strcpy(proto, sig->proto);
  }
  
  copy = call_sig_alloc();

  memcpy(copy, sig, sizeof(signature));
  copy->proto = proto;
  return copy;
}

/*
 * Free function signature
 *
 * This function frees the given function signature after freeing the
 * contained prototype string.
 */
void call_sig_free(signature *sig)
{
  if (!sig) return;
  if (sig->proto) free(sig->proto);
#if DEBUG == 1
  memset(sig, 0, sizeof(signature));
#endif
  free(sig);
}

/*
 * Create signature for builtin function
 *
 * This function creates a function signature for a builtin function.
 * The number of arguments, function prototype, and pointer to the
 * builtin function need to be given.
 */
signature *call_sig_builtin(unsigned int args, const char *proto,
    call_func vector)
{
  signature *sig;
  int proto_len;
  char *proto_copy;

  sig = call_sig_alloc();
  
  proto_len = strlen(proto);
  proto_copy = oom(malloc(proto_len + 1));
  strcpy(proto_copy, proto);

  sig->type = FUNCTION_TYPE_BUILTIN;
  sig->args = args;
  sig->proto = proto_copy;
  sig->call_u.builtin_vector = vector;
  return sig;
}
