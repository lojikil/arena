/*
 * Raw memory allocation interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdlib.h"

/*
 * Private wrapper structure for allocated memory
 */
typedef struct {
  int   size;
  int 	rw;
  void  *data;
} memblock;

/*
 * Initialize memory block structure
 */
static memblock *mem_init(int size, void *data)
{
  memblock *mem;
  
  mem = oom(malloc(sizeof(memblock)));
  mem->size = size;
  mem->data = data;
  mem->rw   = 1;
  
  return mem;
}

/*
 * Clean up memory block structure
 */
static void mem_cleanup(void *data)
{
  memblock *mem = data;
  
  if (mem) free(mem->data);
  free(mem);
}

/*
 * Clean up memory block structure put not contained pointer
 */
static void mem_halfcleanup(void *data)
{
  free(data);
}

/*
 * Check whether resource is memory resource
 */
static int is_mem(value *val)
{
  return (val->value_u.res_val->release == mem_cleanup ||
          val->value_u.res_val->release == mem_halfcleanup);
}

/*
 * Get memory pointer from memory resource
 */
static void *mem_get(void *data)
{
  memblock *mem = data;
  
  if (!mem) {
    return NULL;
  }
  return mem->data;
}

/*
 * Check whether resource is memory resource
 */
value *mem_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(is_mem(argv[0]));
}

/*
 * Allocate a given number of bytes
 */
value *mem_malloc(arena_state *s, unsigned int argc, value **argv)
{
  int size = INT_OF(argv[0]);
  void *mem;
  value *res;

  mem = malloc(size);
  if (!mem) {
    return value_make_void();
  }
  res = value_make_resource(mem_init(size, mem), mem_cleanup);
  res->value_u.res_val->get = mem_get;
  return res;
}

/*
 * Allocate a given number of zero-filled bytes
 */
value *mem_calloc(arena_state *s, unsigned int argc, value **argv)
{
  int size = INT_OF(argv[0]) * INT_OF(argv[1]);
  void *mem;
  value *res;
  
  mem = calloc(INT_OF(argv[0]), INT_OF(argv[1]));
  if (!mem) {
    return value_make_void();
  }
  res = value_make_resource(mem_init(size, mem), mem_cleanup);
  res->value_u.res_val->get = mem_get;
  return res;
}

/*
 * Reallocate memory with a new size
 */
value *mem_realloc(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  int size = INT_OF(argv[1]);
  void *data;
  
  if (!is_mem(argv[0]) || !mem || size < 0) {
    return value_make_bool(0);
  }
  
  data = realloc(mem->data, size);
  if (!data) {
    return value_make_bool(0);
  }
  
  mem->data = data;
  mem->size = size;
  return value_make_bool(1);
}

/*
 * Free a memory resource
 */
value *mem_free(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  
  if (is_mem(argv[0]) && mem) {
    mem_cleanup(mem);
    RESDATA_OF(argv[0]) = NULL;
  }
  return value_make_void();
}

/*
 * Create resource for C NULL pointer
 */
value *mem_cnull(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_resource(NULL, mem_cleanup);
}

/*
 * Check for resource containing C NULL pointer
 */
value *mem_is_null(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  
  return value_make_bool(is_mem(argv[0]) && (!mem || !mem->data));
}

/*
 * Create resource from string value
 */
value *mem_cstring(arena_state *s, unsigned int argc, value **argv)
{
  char *str = argv[0]->value_u.string_val.value;
  int len;
  char *mem;
  value *res;

  if (str && !value_str_compat(argv[0])) {
    return value_make_void();
  }

  if (!str) {
    str = "";
  }
  
  len = strlen(str) + 1;
  mem = oom(malloc(len));
  strcpy(mem, str);
  
  res = value_make_resource(mem_init(len, mem), mem_cleanup);
  res->value_u.res_val->get = mem_get;
  return res;
}

/*
 * Put character at offset in memory resource
 */
value *mem_put_char(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *put;
  int offset = INT_OF(argv[1]);
  char val = INT_OF(argv[2]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }

  if (mem->size < offset + sizeof(char)) {
    mem->data = oom(realloc(mem->data, offset + sizeof(char)));
    mem->size = offset + sizeof(char);
  }

  put = mem->data;
  put += offset;
  *put = val;

  return value_make_bool(1);
}

/*
 * Put short integer at offset in memory resource
 */
value *mem_put_short(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  short *put;
  int offset = INT_OF(argv[1]);
  short val = INT_OF(argv[2]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }

  if (mem->size < offset + sizeof(short)) {
    mem->data = oom(realloc(mem->data, offset + sizeof(short)));
    mem->size = offset + sizeof(short);
  }

  pos = mem->data;
  pos += offset;
  put = (short *) pos;
  *put = val;

  return value_make_bool(1);
}

/*
 * Put integer at offset in memory resource
 */
value *mem_put_int(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  int *put;
  int offset = INT_OF(argv[1]);
  int val = INT_OF(argv[2]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }

  if (mem->size < offset + sizeof(int)) {
    mem->data = oom(realloc(mem->data, offset + sizeof(int)));
    mem->size = offset + sizeof(int);
  }

  pos = mem->data;
  pos += offset;
  put = (int *) pos;
  *put = val;

  return value_make_bool(1);
}

/*
 * Put float at offset in memory resource
 */
value *mem_put_float(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  float *put;
  int offset = INT_OF(argv[1]);
  float val = FLOAT_OF(argv[2]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }

  if (mem->size < offset + sizeof(float)) {
    mem->data = oom(realloc(mem->data, offset + sizeof(float)));
    mem->size = offset + sizeof(float);
  }

  pos = mem->data;
  pos += offset;
  put = (float *) pos;
  *put = val;

  return value_make_bool(1);
}

/*
 * Put double at offset in memory resource
 */
value *mem_put_double(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  double *put;
  int offset = INT_OF(argv[1]);
  double val = FLOAT_OF(argv[2]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }

  if (mem->size < offset + sizeof(double)) {
    mem->data = oom(realloc(mem->data, offset + sizeof(double)));
    mem->size = offset + sizeof(double);
  }

  pos = mem->data;
  pos += offset;
  put = (double *) pos;
  *put = val;

  return value_make_bool(1);
}

/*
 * Put string at offset into memory resource
 */
value *mem_put_string(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  int offset = INT_OF(argv[1]);
  int len    = STRLEN_OF(argv[2]);
  char *str  = STR_OF(argv[2]);

  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }

  if (mem->size < offset + len) {
    mem->data = oom(realloc(mem->data, offset + len));
    mem->size = offset + len;
  }
  
  pos = mem->data;
  pos += offset;
  memcpy(pos, str, len);
  
  return value_make_bool(1);
}

/*
 * Put pointer to another resource at offset in resource
 */
value *mem_put_pointer(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  memblock *ptr = RESDATA_OF(argv[2]);
  char *pos;
  void **put;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw || !is_mem(argv[2])) {
    return value_make_bool(0);
  }

  if (mem->size < offset + sizeof(void *)) {
    mem->data = oom(realloc(mem->data, offset + sizeof(void *)));
    mem->size = offset + sizeof(void *);
  }
  
  pos = mem->data;
  pos += offset;
  put = (void **) pos;
  if (ptr) {
    *put = ptr->data;
  } else {
    *put = NULL;
  }
  
  return value_make_bool(1);
}

/*
 * Get character from offset in memory resource
 */
value *mem_get_char(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *get;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(char) > mem->size)) {
    return value_make_void();
  }
  
  get = mem->data;
  get += offset;
  
  return value_make_int((int) *get);
}

/*
 * Get short integer from offset in memory resource
 */
value *mem_get_short(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  short *get;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(short) > mem->size)) {
    return value_make_void();
  }
  
  pos = mem->data;
  pos += offset;
  get = (short *) pos;
  
  return value_make_int((int) *get);
}

/*
 * Get integer from offset in memory resource
 */
value *mem_get_int(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  int *get;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(int) > mem->size)) {
    return value_make_void();
  }
  
  pos = mem->data;
  pos += offset;
  get = (int *) pos;
  
  return value_make_int(*get);
}

/*
 * Get float from offset in memory resource
 */
value *mem_get_float(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  float *get;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(float) > mem->size)) {
    return value_make_void();
  }
  
  pos = mem->data;
  pos += offset;
  get = (float *) pos;
  
  return value_make_float((double) *get);
}

/*
 * Get double from offset in memory resource
 */
value *mem_get_double(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *pos;
  double *get;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(double) > mem->size)) {
    return value_make_void();
  }
  
  pos = mem->data;
  pos += offset;
  get = (double *) pos;
  
  return value_make_float(*get);
}

/*
 * Create memory resource from direct pointer
 */
value *mem_make_pointer(void *data, int free)
{
  memblock *mem;
  value *res;
  
  res = value_make_resource(mem_init(0, data), 
    free ? mem_cleanup : mem_halfcleanup);
  mem = RESDATA_OF(res);
  mem->rw = 0;
  
  res->value_u.res_val->get = mem_get;
  
  return res;
}

/*
 * Get memory resource from offset in memory resource
 */
value *mem_get_pointer(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  memblock *resmem;
  char *pos;
  void **get;
  int offset = INT_OF(argv[1]);
  int cleanup = BOOL_OF(argv[2]);
  value *res;

  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(void *) > mem->size)) {
    return value_make_void();
  }
  
  pos = mem->data;
  pos += offset;
  get = (void **) pos;
  
  res = value_make_resource(mem_init(0, *get),
    cleanup ? mem_cleanup : mem_halfcleanup);
  resmem = RESDATA_OF(res);
  resmem->rw = 0;

  res->value_u.res_val->get = mem_get;
  
  return res;
}

/*
 * Get string value from offset in memory resource
 */
value *mem_string(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *get;
  int offset = INT_OF(argv[1]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + sizeof(char) > mem->size)) {
    return value_make_void();
  }
  
  get = mem->data;
  get += offset;
  
  return value_make_string(get);
}

/*
 * Get fixed-length string value from offset in memory resource
 */
value *mem_get_string(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  char *get;
  int offset = INT_OF(argv[1]);
  int len    = INT_OF(argv[2]);
  
  if (!is_mem(argv[0]) || !mem ||
      (mem->size && offset + len > mem->size)) {
    return value_make_void();
  }
  
  get = mem->data;
  get += offset;
  
  return value_make_memstring(get, len);
}

/*
 * Copy bytes from memory resource to memory resource
 *
 * This routine will corrupt memory if source and destination
 * memory resources overlap.
 */
value *mem_cpy(arena_state *s, unsigned int argc, value **argv)
{
  memblock *dst = RESDATA_OF(argv[0]);
  int dst_off   = INT_OF(argv[1]);
  memblock *src = RESDATA_OF(argv[2]);
  int src_off   = INT_OF(argv[3]);
  int count     = INT_OF(argv[4]);
  
  if (!is_mem(argv[0]) || !dst || !is_mem(argv[2]) || !src) {
    return value_make_bool(0);
  }
  if (count == 0) {
    return value_make_bool(1);
  }
  
  if (count > src->size - src_off) {
    count = src->size - src_off;
  }
  if (dst_off + count > dst->size) {
    dst->data = oom(realloc(dst->data, dst_off + count));
    dst->size = dst_off + count;
  }
  
  memcpy(dst->data + dst_off, src->data + src_off, count);
  return value_make_bool(1);
}

/*
 * Copy bytes from memory resource to memory resource
 *
 * This routine will NOT corrupt memory when source and destination
 * memory resources overlap.
 */
value *mem_move(arena_state *s, unsigned int argc, value **argv)
{
  memblock *dst = RESDATA_OF(argv[0]);
  int dst_off   = INT_OF(argv[1]);
  memblock *src = RESDATA_OF(argv[2]);
  int src_off   = INT_OF(argv[3]);
  int count     = INT_OF(argv[4]);
  
  if (!is_mem(argv[0]) || !dst || !is_mem(argv[2]) || !src) {
    return value_make_bool(0);
  }
  if (count == 0) {
    return value_make_bool(1);
  }
  
  if (count > src->size - src_off) {
    count = src->size - src_off;
  }
  if (dst_off + count > dst->size) {
    dst->data = oom(realloc(dst->data, dst_off + count));
    dst->size = dst_off + count;
  }
  
  memmove(dst->data + dst_off, src->data + src_off, count);
  return value_make_bool(1);
}

/*
 * Compare bytes from two memory resources
 */
value *mem_cmp(arena_state *s, unsigned int argc, value **argv)
{
  memblock *one = RESDATA_OF(argv[0]);  
  int one_off   = INT_OF(argv[1]);
  memblock *two = RESDATA_OF(argv[2]);
  int two_off   = INT_OF(argv[3]);
  int count     = INT_OF(argv[4]);
  int res;
  
  if (!is_mem(argv[0]) || !one || !is_mem(argv[2]) || !two ||
      one_off + count > one->size || two_off + count > two->size) {
    return value_make_void();
  }
  
  res = memcmp(one->data + one_off, two->data + two_off, count);
  return value_make_int(res);
}

/*
 * Look for byte in memory resource
 */
value *mem_chr(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  int offset    = INT_OF(argv[1]);
  int search    = INT_OF(argv[2]);
  int count     = INT_OF(argv[3]);
  void *where   = NULL;
  
  if (!is_mem(argv[0]) || !mem || offset + count > mem->size) {
    return value_make_void();
  }

  where = memchr(mem->data + offset, search, count);
  if (!where) {
    return value_make_void();
  }
  return value_make_int(where - mem->data);
}

/*
 * Set bytes in memory resource
 */
value *mem_set(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  int offset    = INT_OF(argv[1]);
  int data      = INT_OF(argv[2]);
  int count     = INT_OF(argv[3]);
  
  if (!is_mem(argv[0]) || !mem) {
    return value_make_bool(0);
  }
  if (offset + count > mem->size) {
    mem->data = oom(realloc(mem->data, offset + count));
    mem->size = offset + count;
  }
  memset(mem->data + offset, data, count);
  return value_make_bool(1);
}

/*
 * Check whether memory resource is writeable
 */
value *mem_is_rw(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  
  if (!is_mem(argv[0]) || !mem || !mem->rw) {
    return value_make_bool(0);
  }
  return value_make_bool(1);
}

/*
 * Return current allocation size of memory resource (0 = unknown)
 */
value *mem_size(arena_state *s, unsigned int argc, value **argv)
{
  memblock *mem = RESDATA_OF(argv[0]);
  
  if (!is_mem(argv[0])) {
    return value_make_void();
  }
  if (!mem) {
    return value_make_int(0);
  }
  return value_make_int(mem->size);
}
