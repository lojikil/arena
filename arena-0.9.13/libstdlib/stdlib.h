/*
 * Standard library
 *
 * This library provides C implementations of the standard library
 * functions.
 *
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
#ifndef LIBSTD_STD_H
#define LIBSTD_STD_H

#include <sys/types.h>
#include <sys/stat.h>

#include "../libmisc/misc.h"
#include "../libruntime/runtime.h"
#include "../libeval/eval.h"

/*
 * Dictionary functions
 */
value *dict_is_resource(arena_state *s, unsigned int, value **);
value *dict_open(arena_state *s, unsigned int, value **);
value *dict_read(arena_state *s, unsigned int, value **);
value *dict_write(arena_state *s, unsigned int, value **);
value *dict_remove(arena_state *s, unsigned int, value **);
value *dict_exists(arena_state *s, unsigned int, value **);
value *dict_close(arena_state *s, unsigned int, value **);

/*
 * Runtime environment functions
 */
value *rt_type_of(arena_state *s, unsigned int, value **);
value *rt_tmpl_of(arena_state *s, unsigned int, value **);
value *rt_is_void(arena_state *s, unsigned int, value **);
value *rt_is_bool(arena_state *s, unsigned int, value **);
value *rt_is_int(arena_state *s, unsigned int, value **);
value *rt_is_float(arena_state *s, unsigned int, value **);
value *rt_is_string(arena_state *s, unsigned int, value **);
value *rt_is_array(arena_state *s, unsigned int, value **);
value *rt_is_struct(arena_state *s, unsigned int, value **);
value *rt_is_fn(arena_state *s, unsigned int, value **);
value *rt_is_resource(arena_state *s, unsigned int, value **);
value *rt_is_a(arena_state *s, unsigned int, value **);
value *rt_is_local(arena_state *s, unsigned int, value **);
value *rt_is_global(arena_state *s, unsigned int, value **);
value *rt_is_function(arena_state *s, unsigned int, value **);
value *rt_is_var(arena_state *s, unsigned int, value **);
value *rt_is_tmpl(arena_state *s, unsigned int, value **);
value *rt_set(arena_state *s, unsigned int, value **);
value *rt_get(arena_state *s, unsigned int, value **);
value *rt_get_static(arena_state *s, unsigned int, value **);
value *rt_unset(arena_state *s, unsigned int, value **);
value *rt_assert(arena_state *s, unsigned int, value **);
value *rt_global(arena_state *s, unsigned int, value **);
value *rt_cast_to(arena_state *s, unsigned int, value **);
value *rt_versions(arena_state *s, unsigned int, value **);

/*
 * System environment functions
 */
value *sys_exit(arena_state *s, unsigned int, value **);
value *sys_getenv(arena_state *s, unsigned int, value **);
value *sys_system(arena_state *s, unsigned int, value **);

/*
 * Random number functions
 */
value *rnd_random(arena_state *s, unsigned int, value **);
value *rnd_srandom(arena_state *s, unsigned int, value **);

/*
 * Print functions
 */
value *print_print(arena_state *s, unsigned int, value **);
value *print_dump(arena_state *s, unsigned int, value **);
value *print_sprintf(arena_state *s, unsigned int, value **);
value *print_printf(arena_state *s, unsigned int, value **);

/*
 * String functions
 */
value *str_length(arena_state *s, unsigned int, value **);
value *str_concat(arena_state *s, unsigned int, value **);
value *str_leftmost(arena_state *s, unsigned int, value **);
value *str_rightmost(arena_state *s, unsigned int, value **);
value *str_strpos(arena_state *s, unsigned int, value **);
value *str_span(arena_state *s, unsigned int, value **);
value *str_cspan(arena_state *s, unsigned int, value **);
value *str_pbrk(arena_state *s, unsigned int, value **);
value *str_coll(arena_state *s, unsigned int, value **);
value *str_lower(arena_state *s, unsigned int, value **);
value *str_upper(arena_state *s, unsigned int, value **);
value *str_is_alnum(arena_state *s, unsigned int, value **);
value *str_is_alpha(arena_state *s, unsigned int, value **);
value *str_is_cntrl(arena_state *s, unsigned int, value **);
value *str_is_digit(arena_state *s, unsigned int, value **);
value *str_is_graph(arena_state *s, unsigned int, value **);
value *str_is_lower(arena_state *s, unsigned int, value **);
value *str_is_print(arena_state *s, unsigned int, value **);
value *str_is_punct(arena_state *s, unsigned int, value **);
value *str_is_space(arena_state *s, unsigned int, value **);
value *str_is_upper(arena_state *s, unsigned int, value **);
value *str_is_xdigit(arena_state *s, unsigned int, value **);
value *str_mid(arena_state *s, unsigned int, value **);
value *str_left(arena_state *s, unsigned int, value **);
value *str_right(arena_state *s, unsigned int, value **);
value *str_ord(arena_state *s, unsigned int, value **);
value *str_chr(arena_state *s, unsigned int, value **);
value *str_explode(arena_state *s, unsigned int, value **);
value *str_implode(arena_state *s, unsigned int, value **);
value *str_ltrim(arena_state *s, unsigned int, value **);
value *str_rtrim(arena_state *s, unsigned int, value **);
value *str_trim(arena_state *s, unsigned int, value **);

/*
 * Math functions
 */
value *math_exp(arena_state *s, unsigned int, value **);
value *math_log(arena_state *s, unsigned int, value **);
value *math_log10(arena_state *s, unsigned int, value **);
value *math_sqrt(arena_state *s, unsigned int, value **);
value *math_ceil(arena_state *s, unsigned int, value **);
value *math_floor(arena_state *s, unsigned int, value **);
value *math_fabs(arena_state *s, unsigned int, value **);
value *math_sin(arena_state *s, unsigned int, value **);
value *math_cos(arena_state *s, unsigned int, value **);
value *math_tan(arena_state *s, unsigned int, value **);
value *math_asin(arena_state *s, unsigned int, value **);
value *math_acos(arena_state *s, unsigned int, value **);
value *math_atan(arena_state *s, unsigned int, value **);
value *math_sinh(arena_state *s, unsigned int, value **);
value *math_cosh(arena_state *s, unsigned int, value **);
value *math_tanh(arena_state *s, unsigned int, value **);
value *math_abs(arena_state *s, unsigned int, value **);

/*
 * File functions
 */
void file_init(arena_state *s);
value *file_is_resource(arena_state *s, unsigned int, value **);
value *file_open(arena_state *s, unsigned int, value **);
value *file_seek(arena_state *s, unsigned int, value **);
value *file_tell(arena_state *s, unsigned int, value **);
value *file_read(arena_state *s, unsigned int, value **);
value *file_write(arena_state *s, unsigned int, value **);
value *file_setbuf(arena_state *s, unsigned int, value **);
value *file_flush(arena_state *s, unsigned int, value **);
value *file_is_eof(arena_state *s, unsigned int, value **);
value *file_is_error(arena_state *s, unsigned int, value **);
value *file_clearerr(arena_state *s, unsigned int, value **);
value *file_close(arena_state *s, unsigned int, value **);
value *file_remove(arena_state *s, unsigned int, value **);
value *file_rename(arena_state *s, unsigned int, value **);
value *file_errno(arena_state *s, unsigned int, value **);
value *file_strerror(arena_state *s, unsigned int, value **);
value *file_getc(arena_state *s, unsigned int, value **);
value *file_gets(arena_state *s, unsigned int, value **);

/*
 * Array functions
 */
value *array_mkarray(arena_state *s, unsigned int, value **);
value *array_sort(arena_state *s, unsigned int, value **);
value *array_is_sorted(arena_state *s, unsigned int, value **);
value *array_unset(arena_state *s, unsigned int, value **);
value *array_compact(arena_state *s, unsigned int, value **);
value *array_search(arena_state *s, unsigned int, value **);
value *array_merge(arena_state *s, unsigned int, value **);
value *array_reverse(arena_state *s, unsigned int, value **);

/*
 * Struct functions
 */
value *struct_mkstruct(arena_state *s, unsigned int, value **);
value *struct_get(arena_state *s, unsigned int, value **);
value *struct_set(arena_state *s, unsigned int, value **);
value *struct_unset(arena_state *s, unsigned int, value **);
value *struct_fields(arena_state *s, unsigned int, value **);
value *struct_methods(arena_state *s, unsigned int, value **);
value *struct_is_field(arena_state *s, unsigned int, value **);
value *struct_is_method(arena_state *s, unsigned int, value **);
value *struct_merge(arena_state *s, unsigned int, value **);

/*
 * Date and time functions
 */
value *time_time(arena_state *s, unsigned int, value **);
value *time_gmtime(arena_state *s, unsigned int, value **);
value *time_localtime(arena_state *s, unsigned int, value **);
value *time_mktime(arena_state *s, unsigned int, value **);
value *time_asctime(arena_state *s, unsigned int, value **);
value *time_ctime(arena_state *s, unsigned int, value **);
value *time_strftime(arena_state *s, unsigned int, value **);

/*
 * Functions on functions
 */
value *fn_is_builtin(arena_state *s, unsigned int, value **);
value *fn_is_userdef(arena_state *s, unsigned int, value **);
value *fn_name(arena_state *s, unsigned int, value **);
value *fn_call(arena_state *s, unsigned int, value **);
value *fn_call_array(arena_state *s, unsigned int, value **);
value *fn_call_method(arena_state *s, unsigned int, value **);
value *fn_call_method_array(arena_state *s, unsigned int, value **);
value *fn_prototype(arena_state *s, unsigned int, value **);
value *fn_map(arena_state *s, unsigned int, value **);
value *fn_filter(arena_state *s, unsigned int, value **);
value *fn_foldl(arena_state *s, unsigned int, value **);
value *fn_foldr(arena_state *s, unsigned int, value **);
value *fn_take_while(arena_state *s, unsigned int, value **);
value *fn_drop_while(arena_state *s, unsigned int, value **);

/*
 * Locale functions
 */
value *lc_getlocale(arena_state *s, unsigned int, value **);
value *lc_setlocale(arena_state *s, unsigned int, value **);
value *lc_localeconv(arena_state *s, unsigned int, value **);

/*
 * List functions
 */
value *list_nil(arena_state *s, unsigned int, value **);
value *list_cons(arena_state *s, unsigned int, value **);
value *list_head(arena_state *s, unsigned int, value **);
value *list_tail(arena_state *s, unsigned int, value **);
value *list_last(arena_state *s, unsigned int, value **);
value *list_init(arena_state *s, unsigned int, value **);
value *list_take(arena_state *s, unsigned int, value **);
value *list_drop(arena_state *s, unsigned int, value **);
value *list_length(arena_state *s, unsigned int, value **);
value *list_null(arena_state *s, unsigned int, value **);
value *list_elem(arena_state *s, unsigned int, value **);
value *list_intersperse(arena_state *s, unsigned int, value **);
value *list_replicate(arena_state *s, unsigned int, value **);

/*
 * Memory handling functions
 */
value *mem_make_pointer(void *, int);
value *mem_is_resource(arena_state *s, unsigned int, value **);
value *mem_malloc(arena_state *s, unsigned int, value **);
value *mem_calloc(arena_state *s, unsigned int, value **);
value *mem_realloc(arena_state *s, unsigned int, value **);
value *mem_free(arena_state *s, unsigned int, value **);
value *mem_cnull(arena_state *s, unsigned int, value **);
value *mem_is_null(arena_state *s, unsigned int, value **);
value *mem_cstring(arena_state *s, unsigned int, value **);
value *mem_put_char(arena_state *s, unsigned int, value **);
value *mem_put_short(arena_state *s, unsigned int, value **);
value *mem_put_int(arena_state *s, unsigned int, value **);
value *mem_put_float(arena_state *s, unsigned int, value **);
value *mem_put_double(arena_state *s, unsigned int, value **);
value *mem_put_string(arena_state *s, unsigned int, value **);
value *mem_put_pointer(arena_state *s, unsigned int, value **);
value *mem_get_char(arena_state *s, unsigned int, value **);
value *mem_get_short(arena_state *s, unsigned int, value **);
value *mem_get_int(arena_state *s, unsigned int, value **);
value *mem_get_float(arena_state *s, unsigned int, value **);
value *mem_get_double(arena_state *s, unsigned int, value **);
value *mem_get_string(arena_state *s, unsigned int, value **);
value *mem_get_pointer(arena_state *s, unsigned int, value **);
value *mem_string(arena_state *s, unsigned int, value **);
value *mem_is_rw(arena_state *s, unsigned int, value **);
value *mem_size(arena_state *s, unsigned int, value **);
value *mem_cpy(arena_state *s, unsigned int, value **);
value *mem_move(arena_state *s, unsigned int, value **);
value *mem_cmp(arena_state *s, unsigned int, value **);
value *mem_chr(arena_state *s, unsigned int, value **);
value *mem_set(arena_state *s, unsigned int, value **);

/*
 * Foreign function interface
 */
value *dyn_is_resource(arena_state *s, unsigned int, value **);
value *dyn_supported(arena_state *s, unsigned int, value **);
value *dyn_open(arena_state *s, unsigned int, value **);
value *dyn_close(arena_state *s, unsigned int, value **);
value *dyn_fn_pointer(arena_state *s, unsigned int, value **);
value *dyn_call_void(arena_state *s, unsigned int, value **);
value *dyn_call_int(arena_state *s, unsigned int, value **);
value *dyn_call_float(arena_state *s, unsigned int, value **);
value *dyn_call_ptr(arena_state *s, unsigned int, value **);
value *dyn_c_float(arena_state *s, unsigned int, value **);

/*
 * PCRE functions
 */
void preg_init(arena_state *s);
value *preg_is_resource(arena_state *s, unsigned int, value **);
value *preg_supported(arena_state *s, unsigned int, value **);
value *preg_compile(arena_state *s, unsigned int, value **);
value *preg_match(arena_state *s, unsigned int, value **);
value *preg_exec(arena_state *s, unsigned int, value **);
value *preg_free(arena_state *s, unsigned int, value **);

/*
 * Register functions
 */
void stdlib_register(arena_state *s, int argc, char **argv);

#endif
