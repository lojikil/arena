/*
 * Top-level interpreter API
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file doc/LICENSE for license
 */
#ifndef ARENA_API_H
#define ARENA_API_H

#include <stdarg.h>

typedef void *arena_ctx;

arena_ctx arena_new_ctx(int argc, char **argv);
void arena_inhibit_ctx(arena_ctx ctx, const char *name);
void arena_free_ctx(arena_ctx ctx);

typedef void *arena_script;

arena_script arena_new_script(char *name);
void arena_dump_script(arena_script script);
void arena_free_script(arena_script script);

int arena_execute_script(arena_ctx ctx, arena_script script);

typedef void *arena_result;

arena_result arena_execute_function(arena_ctx ctx, const char *name, ...);
int arena_int_result(arena_result result);
double arena_double_result(arena_result result);
char *arena_string_result(arena_result result);
void arena_free_result(arena_result result);

#endif
