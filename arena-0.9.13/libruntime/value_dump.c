/*
 * Dumping of values
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "runtime.h"

/*
 * Print function prototype
 */
static void print_fn(signature *sig)
{
  char *pos;
  
  printf("%s%s fn(", isupper(sig->rettype) ? "forced " : "",
    sig->rettype != '?' ?
      call_typename(call_chartype(tolower(sig->rettype))) : "mixed");
  
  pos = sig->proto;
  while (pos && *pos != 0) {
    printf("%s%s%s", isupper(*pos) ? "forced " : "",
      *pos != '?' ? call_typename(call_chartype(tolower(*pos))) : "mixed",
      *(pos+1) != 0 ? ", " : "");
    ++pos;
  }
  printf(")");
}

/*
 * Print escaped string
 */
static void escape_str(const value *val)
{
  const char *hex = "0123456789abcdef";
  char *str = val->value_u.string_val.value;
  int len   = val->value_u.string_val.len;
  int i;

  printf("\"");  
  if (len > 0) {
    for (i = 0; i < len; i++) {
      if (isprint(str[i])) {
        printf("%c", str[i]);
      } else {
        switch (str[i]) {
          case 0:
            printf("\\0");
            break;
          case '\b':
            printf("\\b");
            break;
          case 27:
            printf("\\e");
            break;
          case '\f':
            printf("\\f");
            break;
          case '\n':
            printf("\\n");
            break;
          case '\r':
            printf("\\r");
            break;
          case '\t':
            printf("\\t");
            break;
          default:
            printf("\\x%c%c", hex[str[i] >> 4], hex[str[i] & 15]);
        }
      }
    }
  }
  printf("\"");
}

/*
 * Print indentation prefix
 *
 * Prints two spaces for each level of depth so that nested
 * arrays are printed with increasing indentation per nesting
 * level.
 */
static void depth_prefix(int depth)
{
  int i;
  for (i = 0; i < depth; i++) {
    printf(" ");
  }
}

/*
 * Print value contents
 *
 * This function prints out a dump of the given value. Arrays
 * are dumped recursively so that all elements and nested arrays
 * are printed out in full.
 */
void value_dump(const value *val, int depth, int skip_flag)
{
  symtab *sym;
  symtab_node *node;
  symtab_entry *entry;
  unsigned int si, sj;
  value **next;
  int i, len;
  
  if (!val) {
    return;
  }

  if (!skip_flag) {
    depth_prefix(depth);
  }
  skip_flag = 0;
  if (!val) {
    printf("void");
  } else {
    switch (val->type) {
      case VALUE_TYPE_VOID:
        printf("void");
        break;
      case VALUE_TYPE_BOOL:
        printf("bool: ");
        if (val->value_u.bool_val) {
          printf("true");
        } else {
          printf("false");
        }
        break;
      case VALUE_TYPE_INT:
        printf("int: %i", val->value_u.int_val);
        break;
      case VALUE_TYPE_FLOAT:
        printf("float: %0.10g", val->value_u.float_val);
        break;
      case VALUE_TYPE_STRING:
        printf("string[%i]: ", val->value_u.string_val.len);
        escape_str(val);
        break;
      case VALUE_TYPE_ARRAY:
        printf("array(%i): {\n", val->value_u.array_val.len);
        depth += 2;
        next = (value **) val->value_u.array_val.value;
        for (i = 0; i < val->value_u.array_val.len; i++) {
          depth_prefix(depth);
          len = printf("[%i] ", i);
          skip_flag = 1;
          depth += len;
          value_dump(*next++, depth, skip_flag);
          depth -= len;
        }
        depth -= 2;
        depth_prefix(depth);
        printf("}");
        break;
      case VALUE_TYPE_STRUCT:
        printf("struct(%i): {\n", symtab_num_entries(val->value_u.struct_val));
        depth += 2;
        sym = val->value_u.struct_val;
        for (si = 0; si < (unsigned int) (1 << sym->order); si++) {
          node = sym->nodes[si];
          if (node) {
            for (sj = 0; sj < node->count; sj++) {
              entry = node->entries[sj];
              if (entry && entry->type == SYMTAB_ENTRY_VAR) {
                depth_prefix(depth);
                len = printf(".%s = ", entry->symbol);
                depth += len;
                skip_flag = 1;
                value_dump(entry->entry_u.var, depth, skip_flag);
                depth -= len;
              }
              if (entry && entry->type == SYMTAB_ENTRY_FUNCTION) {
                depth_prefix(depth);
                printf(".%s = ", entry->symbol);
                print_fn(entry->entry_u.sig);
                printf("\n");
              }
            }
          }
        }
        depth -= 2;
        depth_prefix(depth);
        printf("}");
        break;
      case VALUE_TYPE_FN:
        printf("fn: ");
        print_fn(val->value_u.fn_val);
        break;
      case VALUE_TYPE_RES:
        printf("resource: 0x%08x[#%i]", (int) val->value_u.res_val->data,
          val->value_u.res_val->refcount);
        break;
      default:
        printf("unknown");
    }
  }
  printf("\n");
}
