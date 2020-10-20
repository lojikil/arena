/*
 * Test parser
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include "../libparser/parser.h"

int main(int argc, char **argv)
{
  arena_state *s = state_alloc();

  stmt_list *res;

  if (argc < 2) {
    return 1;
  }
  res = parse_file(s, argv[1]); 
  if (!res) {
    return 1;
  } else {
    return 0;
  }
}
