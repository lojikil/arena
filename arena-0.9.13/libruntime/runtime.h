/*
 * Runtime library
 *
 * This library provides basic typed values, hashed symbol tables,
 * type-safe function calls, and error message printing.
 *
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
#ifndef LIBRUNTIME_H
#define LIBRUNTIME_H

#include "../libmisc/misc.h"

#define DEBUG 0

/*
 * --- Basic typed values ---
 */

/*
 * Value types
 */
typedef enum {
  VALUE_TYPE_VOID       = 0,
  VALUE_TYPE_BOOL	= 1,
  VALUE_TYPE_INT	= 2,
  VALUE_TYPE_FLOAT	= 3,
  VALUE_TYPE_STRING	= 4,
  VALUE_TYPE_ARRAY	= 5,
  VALUE_TYPE_STRUCT	= 6,
  VALUE_TYPE_FN		= 7,
  VALUE_TYPE_RES	= 8
} value_type;

/*
 * String value structure
 */
typedef struct {
  int		len;
  char		*value;
} value_string;

typedef struct value VALUE;

/* 
 * Array value structure
 */
typedef struct {
  int		len;
  int		size;
  VALUE		**value;
} value_array;
#define ARRAY_GROWTH	100

/*
 * Resource value structure
 */
typedef struct {
  int		refcount;
  void		*data;
  void		(*release)(void *);
  void		*(*get)(void *);
} value_res;

/*
 * Value union
 */
typedef struct value {
  value_type		type;
  union {
    int			bool_val;
    int			int_val;
    void		*struct_val;
    void		*fn_val;
    double		float_val;
    value_string	string_val;
    value_array		array_val;
    value_res		*res_val;
  } value_u;
} value;

/*
 * Accessor macros
 */
#define TYPE_OF(v) ((v)->type)
#define BOOL_OF(v) ((v)->value_u.bool_val)
#define INT_OF(v) ((v)->value_u.int_val)
#define FLOAT_OF(v) ((v)->value_u.float_val)
#define STRLEN_OF(v) ((v)->value_u.string_val.len)
#define STR_OF(v) ((v)->value_u.string_val.value)
#define ARRLEN_OF(v) ((v)->value_u.array_val.len)
#define ARR_OF(v) ((v)->value_u.array_val.value)
#define RESTYPE_OF(v) ((v)->value_u.res_val->type)
#define RESDATA_OF(v) ((v)->value_u.res_val->data)

/*
 * Memory management
 */
value *value_alloc(value_type type);
void value_free(value *val);

/*
 * Resource type management
 */
int reserve_resource_type(arena_state *s);

/*
 * Constructors
 */
value *value_make_void(void);
value *value_make_bool(int val);
value *value_make_int(int val);
value *value_make_float(double val);
value *value_make_string(const char *str);
value *value_make_memstring(const void *buf, int len);
value *value_make_array(void);
value *value_make_struct(void);
value *value_make_fn(void *sig);
value *value_make_resource(void *data, void (*release)(void *));

/*
 * Value copy
 */
value *value_copy(value *val);

/*
 * Array management
 */
void value_add_to_array(value *arr, value *val);
void value_set_array(value *arr, int pos, value *val);
value *value_get_array(value *arr, int pos);
void value_delete_array(value *arr, int pos);

/*
 * Struct management
 */
void value_set_struct(value *st, const char *pos, value *val);
value *value_get_struct(value *st, const char *pos);
void value_delete_struct(value *st, const char *pos);

/*
 * Casting and compatibility
 */
value *value_cast(arena_state *s, value *val, value_type type);
void value_cast_inplace(arena_state *s, value **val, value_type type);
int value_str_compat(const value *val);

/*
 * Dump printing
 */
void value_dump(const value *val, int depth, int skip_flag);

/*
 * --- function calls ---
 */

/*
 * Function call types
 */
typedef enum {
  FUNCTION_TYPE_BUILTIN = 1,
  FUNCTION_TYPE_USERDEF = 2
} function_type;
 
/*
 * Pointer type for builtin functions
 */
typedef value *(*call_func)(arena_state *s, unsigned int argc, value **argv);

/*
 * Pointer type for user-defined functions
 */
typedef value *(*user_func)(arena_state *s, void *data, void *def,
  unsigned int args, unsigned int argc, value **argv);

/*
 * Function call signature
 */ 
typedef struct {
  function_type	type;
  unsigned int	args;
  char		*name;
  char		*proto;
  char		rettype;
  void		*data;
  void		*def;
  union {
    call_func	builtin_vector;
    user_func	userdef_vector;
  } call_u;
} signature;

/*
 * Type to character conversion and back 
 */
char call_typechar(const value *val);
const char *call_typename(value_type type);
int call_chartype(char val);

/*
 * Memory managment
 */
signature *call_sig_alloc(void);
signature *call_sig_copy(const signature *sig);
void call_sig_free(signature *sig);
signature *call_sig_builtin(const char *name, unsigned int args, const char *p, call_func v);

/*
 * Function calls
 */
void call_check(arena_state *s, const char *n, signature *sig,
  unsigned int, value **);
value *call_function(arena_state *s, signature *sig, unsigned int, value **);
value *call_named_function(arena_state *s, const char *n, unsigned int c,
  value **argv);

/*
 * --- symbol tables ---
 */

/*
 * Symbol table size
 */
#define SYMTAB_DEFAULT_ORDER	11

/*
 * Entry types
 */
typedef enum {
  SYMTAB_ENTRY_VAR	= 1,
  SYMTAB_ENTRY_FUNCTION	= 2,
  SYMTAB_ENTRY_TMPL	= 3
} symtab_entry_type;

/*
 * Template entry
 */
typedef struct {
  char	*parent;  	/* name of parent template */
  void	*def;		/* definition statement list */
} tmpldecl;

/*
 * Symbol table entry
 */
typedef struct {
  char			*symbol;
  symtab_entry_type	type;
  union {
    value		*var;
    signature		*sig;
    tmpldecl		def;
  } entry_u;
} symtab_entry;

/*
 * Symbol table node
 */
typedef struct {
  unsigned int		count;
  symtab_entry		**entries;
} symtab_node;

/*
 * Symbol table
 */
typedef struct symtab {
  unsigned int		order;
  symtab_node		**nodes;
} symtab;

/*
 * Memory management
 */
symtab_entry *symtab_entry_alloc(void);
void symtab_entry_free(symtab_entry *entry);
symtab_node *symtab_node_alloc(void);
void symtab_node_free(symtab_node *node);
symtab *symtab_alloc(unsigned int order);
void symtab_free(symtab *symtab);

/*
 * Symbol table entry manipulation
 */
void symtab_add(symtab *symtab, symtab_entry *entry);
void symtab_add_variable(symtab *symtab, const char *name, value *val);
void symtab_add_function(symtab *symtab, const char *name, const signature *s);
void symtab_add_template(symtab *, const char *n, const char *p, void *def);
symtab_entry *symtab_lookup(symtab *symtab, const char *symbol);
void symtab_delete(symtab *symtab, const char *symbol);
int symtab_num_entries(symtab *sym);

/*
 * Symbol table stack
 */
void symtab_stack_init(arena_state *s);
void symtab_stack_teardown(arena_state *s);
void symtab_stack_enter(arena_state *s);
void symtab_stack_leave(arena_state *s);
symtab *symtab_stack_pop(arena_state *s);
unsigned int symtab_stack_depth(arena_state *s);
void symtab_stack_add(arena_state *s, symtab_entry *entry);
void symtab_stack_add_global(arena_state *s, const char *name, value *val);
void symtab_stack_add_variable(arena_state *s, const char *name, value *val);
void symtab_stack_add_function(arena_state *s, const char *name,
  const signature *sig);
void symtab_stack_add_template(arena_state *s, const char *name,
  const char *parent, void *d);
symtab_entry *symtab_stack_lookup(arena_state *s, const char *symbol);
int symtab_stack_local(arena_state *s, const char *symbol);
void symtab_stack_delete(arena_state *s, const char *symbol);

#endif
