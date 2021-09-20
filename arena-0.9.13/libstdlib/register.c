/*
 * Register function
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "stdlib.h"

/*
 * stdlib function definition
 */
typedef struct {
  char		*name;
  call_func	vector;
  unsigned int	args;
  char		*proto;
  char		rettype;
} stdlib_func;

/*
 * stdlib int constant definition
 */
typedef struct {
  char		*name;
  int		value;
} stdlib_int_const;

/*
 * stdlib float constant definition
 */
typedef struct {
  char		*name;
  double	value;
} stdlib_float_const;

/*
 * stdlib int constants to register
 */
static stdlib_int_const ints[] = {
  { "stdin",		1		},
  { "stdout",		2 		},
  { "stderr",		3		},
  { "FLT_DIG",		DBL_DIG		},
  { "FLT_MANT_DIG",	DBL_MANT_DIG	},
  { "FLT_MAX_EXP",	DBL_MAX_EXP	},
  { "FLT_MIN_EXP",	DBL_MIN_EXP	},
  { "FLT_RADIX",	FLT_RADIX	},
  { "INT_MIN",		INT_MIN		},
  { "INT_MAX",		INT_MAX		},
  { "RAND_MAX",		RAND_MAX	},
  { NULL,		0 		}
};

static stdlib_float_const floats[] = {
  { "FLT_EPSILON",	DBL_EPSILON	},
  { "FLT_MAX",		DBL_MAX		},
  { "FLT_MIN",		DBL_MIN		},
  { NULL,		0.0		}
};

/*
 * stdlib functions to register
 */
static stdlib_func std[] = {
  /* runtime system functions */
  { "type_of",		rt_type_of,		1,	"?",	's'	},
  { "tmpl_of",		rt_tmpl_of,		1,	"?",	'?'	},
  { "is_void",		rt_is_void,		1,	"?",	'b'	},
  { "is_bool",		rt_is_bool,		1,	"?",	'b'	},
  { "is_int",		rt_is_int,		1,	"?",	'b'	},
  { "is_float",		rt_is_float,		1,	"?",	'b'	},
  { "is_string",	rt_is_string,		1,	"?",	'b'	},
  { "is_array",		rt_is_array,		1,	"?",	'b'	},
  { "is_struct",	rt_is_struct,		1,	"?",	'b'	},
  { "is_fn",		rt_is_fn,		1,	"?",	'b'	},
  { "is_resource",	rt_is_resource,		1,	"?",	'b'	},
  { "is_a",		rt_is_a,		2,	"?s",	'b'	},
  { "is_function",	rt_is_function,		1,	"s",	'b'	},
  { "is_var",		rt_is_var,		1,	"s",	'b'	},
  { "is_tmpl",		rt_is_tmpl,		1,	"s",	'b'	},
  { "is_local",		rt_is_local,		1,	"s",	'b'	},
  { "is_global",	rt_is_global,		1,	"s",	'b'	},
  { "set",		rt_set,			2,	"s?",	'b'	},
  { "get",		rt_get,			1,	"s",	'?'	},
  { "get_static",	rt_get_static,		2,	"ss",	'?'	},
  { "unset",		rt_unset,		0,	"",	'v'	},
  { "assert",		rt_assert,		0,	"",	'v'	},
  { "global",		rt_global,		0,	"",	'v'	},
  { "cast_to",		rt_cast_to,		2,	"?s",	'?'	},
  { "versions",		rt_versions,		0,	"",	'c'	},

  /* system environment functions */
  { "exit",		sys_exit,		1,	"i",	'v'	},
  { "getenv",		sys_getenv,		1,	"s",	'?'	},
  { "system",		sys_system,		1,	"s",	'?'	},

  /* random number functions */
  { "rand",		rnd_random,		2,	"ii",	'i'	},
  { "srand",		rnd_srandom,		1,	"i",	'v'	},

  /* printing functions */
  { "print",		print_print,		0,	"",	'v'	},
  { "dump",		print_dump,		0,	"",	'v'	},
  { "sprintf",		print_sprintf,		1,	"s",	's'	},
  { "printf",		print_printf,		1,	"s",	'v'	},

  /* array functions */
  { "mkarray",		array_mkarray,		0,	"",	'a'	},
  { "qsort",		array_sort,		1,	"a",	'a'	},
  { "is_sorted",	array_is_sorted,	1,	"a",	'b'	},
  { "array_unset",	array_unset,		2,	"ai",	'a'	},
  { "array_compact",	array_compact,		1,	"a",	'a'	},
  { "array_search",	array_search,		2,	"a?",	'?'	},
  { "array_merge",	array_merge,		0,	"",	'a'	},
  { "array_reverse",	array_reverse,		1,	"a",	'a'	},
  
  /* struct functions */
  { "mkstruct",		struct_mkstruct,	0,	"",	'c'	},
  { "struct_get",	struct_get,		2,	"cs",	'?'	},
  { "struct_set",	struct_set,		3,	"cs?",	'c'	},
  { "struct_unset",	struct_unset,		2,	"cs",	'c'	},
  { "struct_fields",	struct_fields,		1,	"c",	'a'	},
  { "struct_methods",	struct_methods,		1,	"c",	'a'	},
  { "is_field",		struct_is_field,	2,	"cs",	'b'	},
  { "is_method",	struct_is_method,	2,	"cs",	'b'	},
  { "struct_merge",	struct_merge,		0,	"",	'c'	},

  /* string functions */
  { "strlen",		str_length,		1,	"S",	'i'	},
  { "strcat",		str_concat,		0,	"",	's'	},
  { "strchr",		str_leftmost,		2,	"SS",	'?'	},
  { "strrchr",		str_rightmost,		2,	"SS",	'?'	},
  { "strstr",		str_strpos,		2,	"SS",	'?'	},
  { "strspn",		str_span,		2,	"SS",	'i'	},
  { "strcspn",		str_cspan,		2,	"SS",	'i'	},
  { "strpbrk",		str_pbrk,		2,	"SS",	'?'	},
  { "strcoll",		str_coll,		2,	"SS",	'i'	},
  { "tolower",		str_lower,		1,	"S",	's' 	},
  { "toupper",		str_upper,		1,	"S",	's' 	},
  { "isalnum",		str_is_alnum,		1,	"S",	'b'	},  
  { "isalpha",		str_is_alpha,		1,	"S",	'b'	},  
  { "iscntrl",		str_is_cntrl,		1,	"S",	'b'	},  
  { "isdigit",		str_is_digit,		1,	"S",	'b'	},  
  { "isgraph",		str_is_graph,		1,	"S",	'b'	},  
  { "islower",		str_is_lower,		1,	"S",	'b'	},  
  { "isprint",		str_is_print,		1,	"S",	'b'	},  
  { "ispunct",		str_is_punct,		1,	"S",	'b'	},  
  { "isspace",		str_is_space,		1,	"S",	'b'	},  
  { "isupper",		str_is_upper,		1,	"S",	'b'	},  
  { "isxdigit",		str_is_xdigit,		1,	"S",	'b'	},  
  { "substr",		str_mid,		2,	"Si*",	's'	},
  { "left",		str_left,		2,	"Si",	's'	},
  { "right",		str_right,		2,	"Si",	's'	},
  { "ord",		str_ord,		1,	"S",	'?'	},
  { "chr",		str_chr,		1,	"i",	's'	},
  { "explode",		str_explode,		1,	"S",	'a'	},
  { "implode",		str_implode,		1,	"a",	's'	},
  { "ltrim",		str_ltrim,		1,	"S",	's'	},
  { "rtrim",		str_rtrim,		1,	"S",	's'	},
  { "trim",		str_trim,		1,	"S",	's'	},

  /* file I/O functions */
  { "is_file_resource",	file_is_resource,	1,	"r",	'b'	},
  { "fopen",		file_open,		2,	"ss",	'?'	},
  { "fseek",		file_seek,		2,	"ri",	'b'	},
  { "ftell",		file_tell,		1,	"r",	'?'	},
  { "fread",		file_read,		2,	"ri",	'?'	},
  { "fwrite",		file_write,		2,	"rS",	'?'	},
  { "setbuf",		file_setbuf,		2,	"rb",	'b'	},
  { "fflush",		file_flush,		1,	"r",	'b'	},
  { "feof",		file_is_eof,		1,	"r",	'b'	},
  { "ferror",		file_is_error,		1,	"r",	'b'	},
  { "clearerr",		file_clearerr,		1,	"r",	'v'	},
  { "fclose",		file_close,		1,	"r",	'b'	},
  { "remove",		file_remove,		1,	"s",	'b'	},
  { "rename",		file_rename,		1,	"s",	'b'	},
  { "errno",		file_errno,		0,	"",	'i'	},
  { "strerror",		file_strerror,		1,	"i",	's'	},
  { "fgetc",		file_getc,		1,	"r",	'?'	},
  { "fgets",		file_gets,		1,	"r",	'?'	},
  
  /* locale functions */
  { "getlocale",	lc_getlocale,		0,	"",	's'	},
  { "setlocale",	lc_setlocale,		1,	"s",	'?'	},
  { "localeconv",	lc_localeconv,		0,	"",	'?'	},

  /* dictionary functions */    
  { "is_dict_resource",	dict_is_resource,	1,	"r",	'b'	},
  { "dopen",		dict_open,		1,	"i",	'?'	},
  { "dread",		dict_read,		2,	"rS",	'?'	},
  { "dwrite",		dict_write,		3,	"rS?",	'b'	},
  { "dremove",		dict_remove,		2,	"rS",	'b'	},
  { "dexists",		dict_exists,		2,	"rS",	'b'	},
  { "dclose",		dict_close,		1,	"r",	'v'	},

  /* math functions */
  { "exp",		math_exp,		1,	"F",	'f'	},
  { "log",		math_log,		1,	"F",	'f'	},
  { "log10",		math_log10,		1,	"F",	'f'	},
  { "sqrt",		math_sqrt,		1,	"F",	'f'	},
  { "ceil",		math_ceil,		1,	"F",	'f'	},
  { "floor",		math_floor,		1,	"F",	'f'	},
  { "fabs",		math_fabs,		1,	"F",	'f'	},
  { "sin",		math_sin,		1,	"F",	'f'	},
  { "cos",		math_cos,		1,	"F",	'f'	},
  { "tan",		math_tan,		1,	"F",	'f'	},
  { "asin",		math_asin,		1,	"F",	'f'	},
  { "acos",		math_acos,		1,	"F",	'f'	},
  { "atan",		math_atan,		1,	"F",	'f'	},
  { "sinh",		math_sinh,		1,	"F",	'f'	},
  { "cosh",		math_cosh,		1,	"F",	'f'	},
  { "tanh",		math_tanh,		1,	"F",	'f'	},
  { "abs",		math_abs,		1,	"I",	'i'	},

  /* date and time functions */
  { "time",		time_time,		0,	"",	'i'	},
  { "gmtime",		time_gmtime,		1,	"i",	'c'	},
  { "localtime",	time_localtime,		1,	"i",	'c'	},
  { "mktime",		time_mktime,		1,	"c",	'i'	},
  { "asctime",		time_asctime,		1,	"c",	's'	},
  { "ctime",		time_ctime,		1,	"i",	's'	},
  { "strftime",		time_strftime,		2,	"sc",	's'	},

  /* functions on functions */
  { "is_builtin",	fn_is_builtin,		1,	"p",	'b'	},
  { "is_userdef",	fn_is_userdef,		1,	"p",	'b'	},
  { "function_name",	fn_name,		1,	"p",	's'	},
  { "call",		fn_call,		1,	"p",	'?'	},
  { "call_array",	fn_call_array,		2,	"pa",	'?'	},
  { "call_method",	fn_call_method,		2,	"pc",	'?'	},
  { "call_method_array",fn_call_method_array,	3,	"pca",	'?'	},
  { "prototype",	fn_prototype,		1,	"p",	'c'	},
  { "map",		fn_map,			2,	"pa",	'a'	},
  { "filter",		fn_filter,		2,	"pa",	'a'	},
  { "foldl",		fn_foldl,		3,	"p?a",	'?'	},
  { "foldr",		fn_foldr,		3,	"pa?",	'?'	},
  { "take_while",	fn_take_while,		2,	"pa",	'a'	},
  { "drop_while",	fn_drop_while,		2,	"pa",	'a'	},

  /* list functions */
  { "nil",		list_nil,		0,	"",	'a'	},
  { "cons",		list_cons,		2,	"?a",	'a'	},
  { "head",		list_head,		1,	"a",	'?'	},
  { "tail",		list_tail,		1,	"a",	'a'	},
  { "last",		list_last,		1,	"a",	'?'	},
  { "init",		list_init,		1,	"a",	'a'	},
  { "take",		list_take,		2,	"ai",	'a'	},
  { "drop",		list_drop,		2,	"ai",	'a'	},
  { "length",		list_length,		1,	"a",	'i'	},
  { "null",		list_null,		1,	"a",	'b'	},
  { "elem",		list_elem,		2,	"a?",	'b'	},
  { "intersperse",	list_intersperse,	2,	"a?",	'a'	},
  { "replicate",	list_replicate,		2,	"?i",	'a'	},

  /* foreign function interface */
  { "is_dyn_resource",	dyn_is_resource,	1,	"r",	'b'	},
  { "dyn_supported",	dyn_supported,		0,	"",	'b'	},
  { "dyn_open",		dyn_open,		1,	"s",	'?'	},
  { "dyn_close",	dyn_close,		1,	"r",	'v'	},	
  { "dyn_fn_pointer",	dyn_fn_pointer,		1,	"rs",	'?'	},
  { "dyn_call_void",	dyn_call_void,		2,	"rs",	'v'	},
  { "dyn_call_int",	dyn_call_int,		2,	"rs",	'?'	},
  { "dyn_call_float",	dyn_call_float,		2,	"rs",	'?'	},
  { "dyn_call_ptr",	dyn_call_ptr,		2,	"rs",	'?'	},
  { "cfloat",		dyn_c_float,		1,	"F",	'?'	},

  /* memory handling functions */
  { "is_mem_resource",	mem_is_resource,	1,	"r",	'b'	},
  { "malloc",		mem_malloc,		1,	"i",	'?'	},
  { "calloc",		mem_calloc,		2,	"ii",	'?'	},
  { "realloc",		mem_realloc,		2,	"ri",	'b'	},
  { "free",		mem_free,		1,	"r",	'v'	},
  { "cnull",		mem_cnull,		0,	"",	'r'	},
  { "is_null",		mem_is_null,		1,	"r",	'b'	},
  { "cstring",		mem_cstring,		1,	"S",	'?'	},
  { "mputchar",		mem_put_char,		3,	"rii",	'b'	},
  { "mputshort",	mem_put_short,		3,	"rii",	'b'	},
  { "mputint",		mem_put_int,		3,	"rii",	'b'	},
  { "mputfloat",	mem_put_float,		3,	"rif",	'b'	},
  { "mputdouble",	mem_put_double,		3,	"rif",	'b'	},
  { "mputstring",	mem_put_string,		3,	"riS",	'b'	},
  { "mputptr",		mem_put_pointer,	3,	"rir",	'b'	},
  { "mgetchar",		mem_get_char,		2,	"ri",	'?'	},
  { "mgetshort",	mem_get_short,		2,	"ri",	'?'	},
  { "mgetint",		mem_get_int,		2,	"ri",	'?'	},
  { "mgetfloat",	mem_get_float,		2,	"ri",	'?'	},
  { "mgetdouble",	mem_get_double,		2,	"ri",	'?'	},
  { "mgetstring",	mem_get_string,		3,	"rii",	'?'	},
  { "mgetptr",		mem_get_pointer,	3,	"rib",	'?'	},
  { "mstring",		mem_string,		2,	"ri",	'?'	},
  { "is_rw",		mem_is_rw,		1,	"r",	'b'	},
  { "msize",		mem_size,		1,	"r",	'?'	},
  { "memcpy",		mem_cpy,		5,	"ririi",'b'	},
  { "memmove",		mem_move,		5,	"ririi",'b'	},
  { "memcmp",		mem_cmp,		5,	"ririi",'?'	},
  { "memchr",		mem_chr,		4,	"riii",	'?'	},
  { "memset",		mem_set,		4,	"riii",	'b'	},

  /* PCRE regular expression functions */
  { "is_pcre_resource",	preg_is_resource,	1,	"r",	'b'	},
  { "pcre_supported",	preg_supported,		0,	"",	'b'	},
  { "pcre_compile",	preg_compile,		2,	"si",	'?'	},
  { "pcre_match",	preg_match,		2,	"rsi",	'?'	},
  { "pcre_exec",	preg_exec,		2,	"rsi",	'?'	},
  { "pcre_free",	preg_free,		1,	"r",	'v'	},
  
  /* list terminator */
  { NULL,		NULL,			0,	NULL,	0	}
};

/*
 * Register command line arguments
 */
static void register_args(arena_state *s, int argc, char **argv)
{
  value *val, *vector;
  int i;
  
  val = value_make_int(argc);
  symtab_stack_add_variable(s, "argc", val);
  value_free(val);
  
  vector = value_make_array();
  for (i = 0; i < argc; i++) {
    val = value_make_string(argv[i]);
    value_add_to_array(vector, val);
    value_free(val);
  }
  symtab_stack_add_variable(s, "argv", vector);
  value_free(vector);
}

/*
 * Register stdlib functions
 *
 * This function registers the stdlib functions in the current
 * symbol table. Usually this means the global symbol table.
 */
void stdlib_register(arena_state *s, int argc, char **argv)
{
  value *val;
  signature sig;
  unsigned int i;
  
  sig.type = FUNCTION_TYPE_BUILTIN;

  i = 0;
  while (std[i].name) {
    sig.args  = std[i].args;
    sig.name  = std[i].name;
    sig.proto = std[i].proto;
    sig.call_u.builtin_vector = std[i].vector;
    sig.rettype = std[i].rettype;
    symtab_stack_add_function(s, std[i].name, &sig);
    i++;
  }
  
  i = 0;
  while (ints[i].name) {
    val = value_make_int(ints[i].value);
    symtab_stack_add_variable(s, ints[i].name, val);
    value_free(val);
    i++;
  }
  
  i = 0;
  while (floats[i].name) {
    val = value_make_float(floats[i].value);
    symtab_stack_add_variable(s, floats[i].name, val);
    value_free(val);
    i++;
  }

  file_init(s);  
  preg_init(s);
  register_args(s, argc, argv);
}
