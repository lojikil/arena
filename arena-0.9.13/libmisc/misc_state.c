/*
 * Interpreter state management
 */

#include <stdlib.h>

#include "misc.h"

/*
 * Allocate new state structure
 */
arena_state *state_alloc(void)
{
  return oom(calloc(1, sizeof(arena_state)));
}

/*
 * Run cleanup functions and free state structure
 */
void state_free(arena_state *state)
{
  free(state);
}
