/*
 * Library of helper functions
 *
 * Provides simple helper functions needed by the other libraries.
 *
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
#ifndef MISC_H
#define MISC_H

/*
 * Interpreter state
 */
typedef struct {
  int	exit_flag;		/* script exit in progress */
  int	exit_value;		/* script return status */
  int	return_flag;		/* return in progress */
  int	continue_flag;		/* continue in progress */
  int	try_flag;		/* try in progress */
  int	except_flag;		/* exception in progress */
  void	*except_value;		/* exception value */
  int	loop_flag;		/* loop in progress */
  int	func_flag;		/* user-defined function in progress */
  int	break_flag;		/* break in progress */
  void	*retval;		/* last function return value */
  int 	retval_cookie;		/* cookie of return value */
  int	global_cookie;		/* current cookie */
  int	float_count;		/* number of in-flight arguments */
  void	*float_args;		/* in-flight arguments */
  int	vector_count;		/* number of in-flight argument vectors */
  void	*vectors;		/* in-flight argument vectors */
  char	*new_cons;		/* current constructor name */
  void	*new_sig;		/* current constructor signature */
  void	*global_table;		/* global symbol table */
  int	local_depth;		/* local symbol table depth */
  void	*local_tables;		/* local symbol tables */
  char	*source_file;		/* current source file */
  int	source_line;		/* current line in source file */
  int	source_col;		/* current column in source file */
  int	seed_init;		/* random generator initialization */
} arena_state;

/*
 * State memory management
 */
arena_state *state_alloc(void);
void state_free(arena_state *state);

/*
 * Error printing
 */
void fatal(arena_state *s, const char *msg, ...);
void nonfatal(arena_state *s, const char *msg, ...);
void internal(const char *file, int line);

/*
 * Sanity checking macro
 */
#define sanity(x) do { if (!(x)) internal(__FILE__, __LINE__); } while(0)

/*
 * Memory allocation checking
 */
void *oom(void *ptr);

#endif
