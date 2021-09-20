/*
 * Interpreter main program
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

#define VERSION 	"0.9.13"

#define MODE_NORMAL	0x0
#define MODE_CHECK	0x1
#define MODE_DUMP	0x2

/*
 * Interpreter mode
 */
static int mode = MODE_NORMAL;

/*
 * First input file and position in command line
 */
static char *filename = NULL;
static int filearg = 0;

/*
 * Execution context and script data
 */
arena_ctx context = NULL;
arena_script script = NULL;

/*
 * Print usage message
 */
static void usage(char *name)
{
  printf("arena v" VERSION " C-like scripting interpreter\n"
         "(C) 2006, Pascal Schmidt <arena-language@ewetel.net>\n\n"
         "Usage: %s [options] script [script options]\n"
         "Options:\n"
         "\t-h, --help\tdisplay this help message\n"
         "\t-V, --version\tdisplay interpreter version and exit\n"
         "\t-c, --check\tsyntax check only\n"
         "\t-d, --dump\tparse script and dump parse tree\n\n"
         "The script is not executed when -c or -d are in effect.\n"
         "You can use the special option -- to terminate option\n"
         "processing; the next argument will then be used as the\n"
         "name of the script to execute.\n"
         , name);
}

/*
 * Evaluate command line options
 */
static void options(int argc, char **argv)
{
  int i, in_opts = 1;
  char *opt;
  
  for (i = 1; i < argc; i++) {
    opt = argv[i];
    if (in_opts) {
      if (strcmp(opt, "-d") == 0 || strcmp(opt, "--dump") == 0) {
        mode = MODE_DUMP;
        continue;
      } else if (strcmp(opt, "-c") == 0 || strcmp(opt, "--check") == 0) {
        mode = MODE_CHECK;
        continue;
      } else if (strcmp(opt, "-h") == 0 || strcmp(opt, "--help") == 0) {
        usage(argv[0]);
        exit(0);
      } else if (strcmp(opt, "-V") == 0 || strcmp(opt, "--version") == 0) {
        printf("%s\n", VERSION);
        exit(0);
      } else if (strcmp(opt, "--") == 0) {
        in_opts = 0;
        continue;
      } else if (*opt == '-') {
        fprintf(stderr, "arena: unknown option `%s'\n", opt);
        exit(1);
      }
    }
    if (!filename) {
      filename = argv[i];
      filearg  = i;
      break;
    }
  }
}

/*
 * Memory cleanup at interpreter exit
 */
static void teardown(void)
{
  if (context) arena_free_ctx(context);
  if (script) arena_free_script(script);
}

/*
 * Main function
 *
 * This function will attempt to parse the first command line
 * argument as a script and will then execute that script if
 * it was parsed successfully.
 */
int main(int argc, char **argv)
{
  int status = 0;

  setvbuf(stdin,  NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  options(argc, argv);
  atexit(teardown);
  
  if (!filename) {
    fprintf(stderr, "arena: missing script name on command line\n");
    exit(1);
  }

  context = arena_new_ctx(argc - filearg, argv + filearg);
  script  = arena_new_script(filename);
  if (!script) {
    return 1;
  }

  /* execute operation */
  if (mode == MODE_NORMAL) {  
    status = arena_execute_script(context, script);
  } else if (mode == MODE_DUMP) {
    arena_dump_script(script);
  }

  return (status >= 0) ? status : 1;
}
