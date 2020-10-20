/*
 * String functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
 
#include "stdlib.h"

/*
 * Length of a string
 *
 * This function returns the length of a string as an int.
 */
value *str_length(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_int(argv[0]->value_u.string_val.len);
}

/*
 * Concatenate strings
 */
value *str_concat(arena_state *s, unsigned int argc, value **argv)
{
  value *result;
  char *buf, *next;
  unsigned int i;
  int catlen = 0, len;

  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_STRING);
    catlen += argv[i]->value_u.string_val.len;
  }
  
  if (catlen == 0) {
    return value_make_string(NULL);
  }
  
  buf = oom(malloc(catlen + 1));
  buf[catlen] = 0;
  
  next = buf;
  for (i = 0; i < argc; i++) {
    len = argv[i]->value_u.string_val.len;
    if (len > 0) {
      memcpy(next, argv[i]->value_u.string_val.value, len);
      next += len;
    }
  }
  
  result = value_make_memstring(buf, catlen);
  free(buf);
  return result;
}

/*
 * Position of first occurence of character in string
 *
 * This function uses the first character of the second argument
 * as the character to search for. It returns void if the character
 * is not found.
 */
value *str_leftmost(arena_state *s, unsigned int argc, value **argv)
{
  char *str = argv[0]->value_u.string_val.value;
  char search;
  char *pos;
  
  if (argv[0]->value_u.string_val.len == 0 ||
      argv[1]->value_u.string_val.len == 0) {
    return value_make_void();
  }
  search = argv[1]->value_u.string_val.value[0];
  
  pos = memchr(str, search, argv[0]->value_u.string_val.len);
  if (!pos) {
    return value_make_void();
  }
  return value_make_int((ptrdiff_t) pos - (ptrdiff_t) str);
}

/*
 * Position of last occurence of character in string
 *
 * This function uses the first character of the second argument
 * as the character to search for. It returns void if the character
 * cannot be found.
 */
value *str_rightmost(arena_state *s, unsigned int argc, value **argv)
{
  char search;
  char *pos, *next;
  
  if (argv[0]->value_u.string_val.len == 0 ||
      argv[1]->value_u.string_val.len == 0) {
    return value_make_void();
  }
  search = argv[1]->value_u.string_val.value[0];
  
  pos = argv[0]->value_u.string_val.value;
  next = pos + argv[0]->value_u.string_val.len - 1;
  while (next >= pos) {
    if (*next == search) {
      return value_make_int((ptrdiff_t) next - (ptrdiff_t) pos);
    }
    --next;
  }
  
  return value_make_void();
}

/*
 * Return position of substring
 *
 * This function returns the position of the second argument inside
 * the first argument. It returns void if the substring is not found
 * and 0 if the substring is an empty string.
 */
value *str_strpos(arena_state *s, unsigned int argc, value **argv)
{
  char *str1 = argv[0]->value_u.string_val.value;
  int len1   = argv[0]->value_u.string_val.len;
  char *str2 = argv[1]->value_u.string_val.value;
  int len2   = argv[1]->value_u.string_val.len;
  char *pos, *end;
  
  if (!str1 || len2 > len1) {
    return value_make_void();
  }
  if (!str2) {
    return value_make_int(0);
  }
  
  pos = str1;
  end = str1 + len1 - len2;
  while (pos <= end) {
    if (memcmp(pos, str2, len2) == 0) {
      return value_make_int((ptrdiff_t) pos - (ptrdiff_t) str1);
    }
    ++pos;
  }
  
  return value_make_void();
}

/*
 * Extract substring
 *
 * If called with two arguments (string, int), this function returns
 * the substring starting at the indicated position. If called with
 * a third int argument, the third argument specifies the maximum
 * length of the returned substring.
 */
value *str_mid(arena_state *s, unsigned int argc, value **argv)
{
  value *result;
  char *str = argv[0]->value_u.string_val.value;
  int max = argv[0]->value_u.string_val.len;
  int startpos = argv[1]->value_u.int_val;
  int count = 0;
  char *start, *buf;

  if (argc > 2) {
    value_cast_inplace(s, &argv[2], VALUE_TYPE_INT);
  }
  if (startpos < 0) {
    startpos = 0;
  }

  if (startpos > max) startpos = max;
  start = str + startpos;

  if (argc > 2) {
    count = argv[2]->value_u.int_val;
  } else {
    count = max - startpos;
  }
  if (count < 0) count = 0;
  if (startpos + count > max) count = max - startpos;
  
  buf = oom(calloc(count + 1, 1));
  memcpy(buf, start, count);

  result = value_make_memstring(buf, count);
  free(buf);
  return result;
}

/*
 * Extract left part of string
 *
 * This function returns a given number of characters from the
 * beginning of a string.
 */
value *str_left(arena_state *s, unsigned int argc, value **argv)
{
  const char *str = argv[0]->value_u.string_val.value;
  int len         = argv[0]->value_u.string_val.len;
  int wanted      = argv[1]->value_u.int_val;
  char *buf;
  value *val;
  
  if (!str || len < 1) {
    return value_make_string(NULL);
  }
  if (wanted > len) {
    wanted = len;
  }
  
  buf = oom(calloc(wanted + 1, 1));
  memcpy(buf, str, wanted);
  val = value_make_memstring(buf, wanted);
  free(buf);
  
  return val;
}

/*
 * Extract right part of string
 *
 * This function returns a given number of characters from the
 * end of a string.
 */
value *str_right(arena_state *s, unsigned int argc, value **argv)
{
  const char *str = argv[0]->value_u.string_val.value;
  int len         = argv[0]->value_u.string_val.len;
  int wanted      = argv[1]->value_u.int_val;
  char *buf;
  value *val;
  
  if (!str || len < 1) {
    return value_make_string(NULL);
  }
  if (wanted > len) {
    wanted = len;
  }

  buf = oom(calloc(wanted + 1, 1));
  memcpy(buf, str + len - wanted, wanted);
  val = value_make_memstring(buf, wanted);
  free(buf);
  
  return val;
}

/*
 * Convert string using conversion function
 */
static value *convert(value *arg, int (*conv)(int))
{
  char *pos;
  int i;
  
  if (arg->value_u.string_val.len > 0) {
    pos = arg->value_u.string_val.value;
    for (i = 0; i < arg->value_u.string_val.len; i++) {
      *pos = conv(*pos);
      ++pos;
    }
  }
  return value_copy(arg);
}

/*
 * Convert string to lower case
 */
value *str_lower(arena_state *s, unsigned int argc, value **argv)
{
  return convert(argv[0], tolower);
}

/*
 * Convert string to upper case
 */
value *str_upper(arena_state *s, unsigned int argc, value **argv)
{
  return convert(argv[0], toupper);
}

/*
 * Check string for specified property
 */
static value *checkstr(value *arg, int (*check)(int))
{
  int ok = 0, i;
  char *pos;

  if (arg->value_u.string_val.len > 0) {
    pos = arg->value_u.string_val.value;
    for (i = 0; i < arg->value_u.string_val.len; i++) {
      if (!check(*pos)) break;
      pos++;
    }
    if (i == arg->value_u.string_val.len) ok = 1;
  }
  return value_make_bool(ok);
}

/*
 * Test string for being alpha-numeric
 */
value *str_is_alnum(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isalnum);
}

/*
 * Test string for being alphabetical
 */
value *str_is_alpha(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isalpha);
}

/*
 * Test string for being control characters only
 */
value *str_is_cntrl(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], iscntrl);
}

/*
 * Test string for being digits only
 */
value *str_is_digit(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isdigit);
}

/*
 * Test string for being non-space only
 */
value *str_is_graph(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isgraph);
}

/*
 * Test string for being lower-case only
 */
value *str_is_lower(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], islower);
}

/*
 * Test string for being printable characters only
 */
value *str_is_print(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isprint);
}

/*
 * Test string for being punctuation only
 */
value *str_is_punct(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], ispunct);
}

/*
 * Test string for being whitespace only
 */
value *str_is_space(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isspace);
}

/*
 * Test string for being upper-case only
 */
value *str_is_upper(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isupper);
}

/*
 * Test string for being hexadecimal digits only
 */
value *str_is_xdigit(arena_state *s, unsigned int argc, value **argv)
{
  return checkstr(argv[0], isxdigit);
}

/*
 * Get numerical character value of first character of string
 *
 * Returns void if handed an empty string.
 */
value *str_ord(arena_state *s, unsigned int argc, value **argv)
{
  if (argv[0]->value_u.string_val.len > 0) {
    return value_make_int(argv[0]->value_u.string_val.value[0]);
  } else {
    return value_make_void();
  }
}

/*
 * Create single-character string from numerical character value
 */
value *str_chr(arena_state *s, unsigned int argc, value **argv)
{
  char buf[2];
  
  buf[0] = (char) argv[0]->value_u.int_val;
  buf[1] = 0;
  return value_make_memstring(buf, 1);
}

/*
 * Number of characters leading first string from set in second string
 */
value *str_span(arena_state *s, unsigned int argc, value **argv)
{
  char *str1 = argv[0]->value_u.string_val.value;
  int   len1 = argv[0]->value_u.string_val.len;
  char *str2 = argv[1]->value_u.string_val.value;
  int   len2 = argv[1]->value_u.string_val.len;
  int i, count = 0;

  if (!str1 || !str2) {
    return value_make_int(0);
  }
  
  for (i = 0; i < len1; i++) {
    if (memchr(str2, str1[i], len2) == NULL) break;
    ++count;
  }
  return value_make_int(count);
}

/*
 * Number of characters leading first string not from set in second string
 */
value *str_cspan(arena_state *s, unsigned int argc, value **argv)
{
  char *str1 = argv[0]->value_u.string_val.value;
  int   len1 = argv[0]->value_u.string_val.len;
  char *str2 = argv[1]->value_u.string_val.value;
  int   len2 = argv[1]->value_u.string_val.len;
  int i, count = 0;

  if (!str1) {
    return value_make_int(0);
  }
  if (!str2) {
    return value_make_int(len1);
  }
  
  for (i = 0; i < len1; i++) {
    if (memchr(str2, str1[i], len2) != NULL) break;
    ++count;
  }
  return value_make_int(count);
}

/*
 * Position of first character from set in second string
 */
value *str_pbrk(arena_state *s, unsigned int argc, value **argv)
{
  char *str1 = argv[0]->value_u.string_val.value;
  int   len1 = argv[0]->value_u.string_val.len;
  char *str2 = argv[1]->value_u.string_val.value;
  int   len2 = argv[1]->value_u.string_val.len;
  int i;
  
  if (!str1 || !str2) {
    return value_make_void();
  }
  
  for (i = 0; i < len1 ; i++) {
    if (memchr(str2, str1[i], len2) != NULL) {
      return value_make_int(i);
    }
  }
  return value_make_void();
}

/*
 * Compare strings based on locale setting
 */
value *str_coll(arena_state *s, unsigned int argc, value **argv)
{
  char *str1 = argv[0]->value_u.string_val.value;
  char *str2 = argv[1]->value_u.string_val.value;
  
  if (!str1 && !str2) {
    return value_make_int(0);
  }
  if (!str1) {
    return value_make_int(-1);
  }
  if (!str2) {
    return value_make_int(1);
  }
  return value_make_int(strcoll(str1, str2));
}

/*
 * Explode string into array of characters
 */
value *str_explode(arena_state *s, unsigned int argc, value **argv)
{
  value *res, *elem;
  char *str   = argv[0]->value_u.string_val.value;
  int   len   = argv[0]->value_u.string_val.len;
  char buf[2] = { 0, 0 };
  int i;
  
  res = value_make_array();

  for (i = 0; i < len; i++) {
    buf[0] = str[i];
    elem = value_make_string(buf);
    value_add_to_array(res, elem);
    value_free(elem);
  }
  return res;
}

/*
 * Implode array into single string
 */
value *str_implode(arena_state *s, unsigned int argc, value **argv)
{
  int max = argv[0]->value_u.array_val.len;
  int i, len, curr = 0;
  char *buf = NULL;
  value *res, *elem;
  
  for (i = 0; i < max; i++) {
    elem = value_get_array(argv[0], i);
    value_cast_inplace(s, &elem, VALUE_TYPE_STRING);
    len = elem->value_u.string_val.len;
    if (len > 0) {
      curr += len;
      if (!buf) {
        buf = oom(malloc(curr + 1));
        buf[0] = 0;
      } else {
        buf = oom(realloc(buf, curr + 1));
      }
      strcat(buf, elem->value_u.string_val.value);
    }
    value_free(elem);
  }
  res = value_make_string(buf);
  free(buf);
  return res;
}

/*
 * Remove leading whitespace from string
 */
value *str_ltrim(arena_state *s, unsigned int argc, value **argv)
{
  char *str = argv[0]->value_u.string_val.value;
  
  if (!str) {
    return value_make_string(NULL);
  }
  
  while (isspace(*str)) ++str;
  return value_make_string(str);
}

/*
 * Remove trailing whitespace from string
 */
value *str_rtrim(arena_state *s, unsigned int argc, value **argv)
{
  char *str = argv[0]->value_u.string_val.value;
  int   len = argv[0]->value_u.string_val.len;
  
  if (!str) {
    return value_make_string(NULL);
  }
  
  while (len > 1 && isspace(*(str + len - 1))) --len;
  return value_make_memstring(str, len);
}

/*
 * Remove leading and trailing whitespace from string
 */
value *str_trim(arena_state *s, unsigned int argc, value **argv)
{
  char *str = argv[0]->value_u.string_val.value;
  int   len = argv[0]->value_u.string_val.len;

  if (!str) {
    return value_make_string(NULL);
  }
  
  while (isspace(*str)) {
    ++str;
    --len;
  }
  while (len > 1 && isspace(*(str + len - 1))) --len;
  return value_make_memstring(str, len);
}
