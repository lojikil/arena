/*
 * File operations, based on standard C facilities
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdlib.h"

/*
 * Callback function for freeing file handles
 */
static void file_free(void *data)
{
  if (data) fclose(data);
}

/*
 * Initialize standard filehandles
 */
void file_init(arena_state *s)
{
  value *val;
  
  val = value_make_resource(stdin, file_free);
  symtab_stack_add_variable(s, "stdin", val);
  value_free(val);

  val = value_make_resource(stdout, file_free);
  symtab_stack_add_variable(s, "stdout", val);
  value_free(val);

  val = value_make_resource(stderr, file_free);
  symtab_stack_add_variable(s, "stderr", val);
  value_free(val);
}

/*
 * Get file pointer from file resource
 */
static void *file_get(void *data)
{
  return data;
}

/*
 * Open file with given mode
 *
 * Opens the given filename with the given mode and returns a file
 * handle. Modes are as in C. On error, void is returned.
 */
value *file_open(arena_state *s, unsigned int argc, value **argv)
{
  char *filename = argv[0]->value_u.string_val.value;
  char *filemode = argv[1]->value_u.string_val.value;
  FILE *fp;
  value *res;

  if (!value_str_compat(argv[0]) || !value_str_compat(argv[1])) {
    return value_make_void();
  }
  
  fp = fopen(filename, filemode);
  if (!fp) {
    return value_make_void();
  }
  
  res = value_make_resource(fp, file_free);
  res->value_u.res_val->get = file_get;
  return res;
}

/*
 * Check whether resource is file resource
 */
value *file_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  
  return value_make_bool(type == file_free);
}

/*
 * Set file position
 *
 * This function sets the file position for the given file handle.
 * Positive values are offsets from the start of the file, negative
 * offsets are from the end of the file. Returns true on success,
 * false on failure.
 */
value *file_seek(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  int pos    = argv[1]->value_u.int_val;
  
  if (type != file_free || !fp) {
    return value_make_bool(0);
  }
  
  return value_make_bool(!fseek(fp, pos, pos >= 0 ? SEEK_SET : SEEK_END));
}

/*
 * Get file position
 *
 * Gets the current file position for the given file handle. On
 * error, void is returned.
 */
value *file_tell(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  long pos;
  
  if (type != file_free || !fp) {
    return value_make_void();
  }

  pos = ftell(fp);
  if (pos == -1) {
    return value_make_void();
  }
  return value_make_int(pos);
}

/*
 * Read from file
 *
 * Reads at most n bytes from the given file descriptor. The result
 * is a string of at most n characters. On error, void is returned.
 * On read errors, a short string is returned.
 */
value *file_read(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  int max    = argv[1]->value_u.int_val;
  char *buf;
  int units;
  value *res;
  
  if (type != file_free || !fp) {
    return value_make_void();
  }
  
  buf = oom(calloc(max, 1));
  units = fread(buf, 1, max, fp);
  res = value_make_memstring(buf, units);
  free(buf);

  return res;
}

/*
 * Write string to file
 *
 * This function writes a string to the given file handle. The number
 * of bytes written is returned. On error, void is returned.
 */
value *file_write(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  int len    = argv[1]->value_u.string_val.len;
  const char *data = argv[1]->value_u.string_val.value;
  size_t written;
  
  if (type != file_free || !fp) {
    return value_make_void();
  }
  
  if (!len) {
    return value_make_int(0);
  }
  
  written = fwrite(data, 1, len, fp);
  return value_make_int(written);
}

/*
 * Set buffering
 *
 * Enables or disables I/O buffering for the given file handle.
 * Returns true on success or false on failure.
 */
value *file_setbuf(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  int res    = -1;
  
  if (type == file_free && fp) {
    if (argv[1]->value_u.bool_val) {
      res = setvbuf(fp, NULL, _IOFBF, BUFSIZ);
    } else {
      res = setvbuf(fp, NULL, _IONBF, BUFSIZ);
    }
  }
  return value_make_bool(res == 0);
}

/*
 * Flush file buffer
 *
 * Flushes the I/O buffer for the given file handle. Returns true
 * on success and false on failure.
 */
value *file_flush(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  
  if (type != file_free || !fp) {
    return value_make_bool(0);
  }
  return value_make_bool(fflush(fp) == 0);
}

/*
 * Check end-of-file condition
 *
 * Returns true if the given file handle points to the end of the
 * corresponding file. The result is only meaninful if the file
 * has been read before. On error, EOF is assumed to be reached.
 */
value *file_is_eof(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  
  if (type != file_free || !fp) {
    return value_make_bool(1);
  }
  return value_make_bool(feof(fp));
}

/*
 * Check error condition
 *
 * Returns true if the given file handle had I/O errors during one
 * of the operations executed before. If the status cannot be
 * determined, it is assumed that no errors were encountered.
 */
value *file_is_error(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;

  if (type != file_free || !fp) {
    return value_make_bool(0);
  }
  return value_make_bool(ferror(fp));
}

/*
 * Clear status indicators
 *
 * This function clears the end-of-file and error indicators for
 * the given file handle.
 */
value *file_clearerr(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;

  if (type == file_free && fp) {
    clearerr(fp);
  }
  return value_make_void();
}

/*
 * Close file
 *
 * This function closes the given file handle. It returns true on
 * success and false if an error occurs during closing. In any
 * case, the file handle is closed when the function returns. If
 * the given file handle does not exit, success is reported.
 */
value *file_close(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;

  if (type != file_free || !fp) {
    return value_make_bool(1);
  }

  argv[0]->value_u.res_val->data = NULL;
  return value_make_bool(!fclose(fp));
}

/*
 * Remove file
 *
 * This function tries to remove the given filename from the system.
 * It returns true on success and false on failure.
 */
value *file_remove(arena_state *s, unsigned int argc, value **argv)
{
  const char *name = argv[0]->value_u.string_val.value;
  
  if (!value_str_compat(argv[0])) {
    return value_make_bool(0);
  }
  return value_make_bool(!remove(name));
}

/*
 * Rename file
 *
 * This functions tries to rename the file given as the first
 * argument to the name given as the second argument. It returns
 * true on success and false on failure.
 */
value *file_rename(arena_state *s, unsigned int argc, value **argv) 
{
  const char *src = argv[0]->value_u.string_val.value;
  const char *dst = argv[1]->value_u.string_val.value;
  
  if (!value_str_compat(argv[0]) || !value_str_compat(argv[1])) {
    return value_make_bool(0);
  }
  return value_make_bool(!rename(src, dst));
}

/*
 * Get error number of last function call
 */
value *file_errno(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_int(errno);
}

/*
 * Get error message for error number
 */
value *file_strerror(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_string(strerror(argv[0]->value_u.int_val));
}

/*
 * Get character from file
 */
value *file_getc(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  char buf[2];
  int got;

  if (type != file_free || !fp) {
    return value_make_void();
  }
  got = fgetc(fp);
  if (got == EOF) {
    return value_make_void();
  }
  buf[0] = got;
  buf[1] = 0;
  return value_make_string(buf);
}

/*
 * Get line from file
 */
value *file_gets(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  FILE *fp   = argv[0]->value_u.res_val->data;
  char buf[65536];
  char *res;
  
  if (type != file_free || !fp) {
    return value_make_void();
  }
  res = fgets(buf, 65536, fp);
  if (!res) {
    return value_make_void();
  }
  return value_make_string(buf);
}
