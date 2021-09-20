/*
 * Foreign function interface
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "../config.h"
#include "foreign.h"
#include "stdlib.h"


#if HAVE_DLOPEN == 1 && HAVE_FOREIGN == 1

#include <dlfcn.h>

/*
 * Free C library resource
 */
static void dyn_free(void *data)
{
  if (data) dlclose(data);
}

/*
 * Check whether resource is library resource
 */
static int is_lib(value *val)
{
  return (val->value_u.res_val->release == dyn_free);
}

/*
 * Check whether resource is library resource
 */
value *dyn_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(is_lib(argv[0]));
}

/*
 * Indicate that dynamic C calls are supported
 */
value *dyn_supported(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(1);
}

/*
 * Call a C function that returns nothing
 */
static void voidcall(void *f, long *a, double *d)
{
  void (*func)() = f;
  
  (*func)(
    a[ 0], a[ 1], a[ 2], a[ 3], a[ 4], a[ 5], a[ 6], a[ 7], a[ 8], a[ 9],
    a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19],
    a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29],
    a[30], a[31], a[32], a[33], a[34], a[35], a[36], a[37], a[38], a[39],
    d[ 0], d[ 1], d[ 2], d[ 3], d[ 4], d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
    d[10], d[11], d[12], d[13], d[14], d[15], d[16], d[17], d[18], d[19]
  );
}

/*
 * Call a C function that returns an int
 */
static int intcall(void *f, long *a, double *d)
{
  int (*func)() = f;
  int res = 0;
  
  res = (*func)(
    a[ 0], a[ 1], a[ 2], a[ 3], a[ 4], a[ 5], a[ 6], a[ 7], a[ 8], a[ 9],
    a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19],
    a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29],
    a[30], a[31], a[32], a[33], a[34], a[35], a[36], a[37], a[38], a[39],
    d[ 0], d[ 1], d[ 2], d[ 3], d[ 4], d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
    d[10], d[11], d[12], d[13], d[14], d[15], d[16], d[17], d[18], d[19]
  );
  return res;
}

/*
 * Call a C function that returns a double
 */
static double floatcall(void *f, long *a, double *d)
{
  double (*func)() = f;
  double res = 0.0;
  
  res = (*func)(
    a[ 0], a[ 1], a[ 2], a[ 3], a[ 4], a[ 5], a[ 6], a[ 7], a[ 8], a[ 9],
    a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19],
    a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29],
    a[30], a[31], a[32], a[33], a[34], a[35], a[36], a[37], a[38], a[39],
    d[ 0], d[ 1], d[ 2], d[ 3], d[ 4], d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
    d[10], d[11], d[12], d[13], d[14], d[15], d[16], d[17], d[18], d[19]
  );
  return res;
}

/*
 * Call a C function that returns a pointer
 */
static void *ptrcall(void *f, long *a, double *d)
{
  void *(*func)() = f;
  void *res = NULL;
  
  res = (*func)(
    a[ 0], a[ 1], a[ 2], a[ 3], a[ 4], a[ 5], a[ 6], a[ 7], a[ 8], a[ 9],
    a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19],
    a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29],
    a[30], a[31], a[32], a[33], a[34], a[35], a[36], a[37], a[38], a[39],
    d[ 0], d[ 1], d[ 2], d[ 3], d[ 4], d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
    d[10], d[11], d[12], d[13], d[14], d[15], d[16], d[17], d[18], d[19]
  );
  return res;
}

/*
 * Build int vector out of value array
 */
static long *makeargs(unsigned int argc, value **argv, double **dargs)
{
  unsigned int i;
  unsigned int size = 0, pos = 0, dsize = 0, dpos = 0, dcount = 0;
  long *args;
  long *dput;
  char **sput;
  void **pput, *resval;
  
  for (i = 0; i < argc; ++i) {
    switch (argv[i]->type) {
      case VALUE_TYPE_VOID:
      case VALUE_TYPE_BOOL:
      case VALUE_TYPE_INT:
        size += sizeof(int);
        break;
      case VALUE_TYPE_FLOAT:
        size += sizeof(double);
        ++dsize;
        break;
      case VALUE_TYPE_STRING:
        size += sizeof(char *);
        break;
      case VALUE_TYPE_RES:
        size += sizeof(void *);
        break;
      default:
        return NULL;
    }
  }

  if (size > 40 * sizeof(int) || dsize > 20) {
    return NULL;
  }

  if (size < 40 * sizeof(int)) {
    size = 40 * sizeof(int);
  }
  args = oom(calloc(size, 1));
  
  if (dsize < 20) dsize = 20;
  *dargs = oom(calloc(dsize, sizeof(double)));
  
  for (i = 0; i < argc; ++i) {
    switch (argv[i]->type) {
      case VALUE_TYPE_VOID:
        args[pos++] = 0;
        break;
      case VALUE_TYPE_BOOL:
        args[pos++] = BOOL_OF(argv[i]);
        break;
      case VALUE_TYPE_INT:
        args[pos++] = INT_OF(argv[i]);
        break;
      case VALUE_TYPE_FLOAT:
        ++dcount;
        *dargs[dpos++] = FLOAT_OF(argv[i]);
        if (dcount > NOSTACK_FLOATS) {
          /*
           * double needs to be stored as two separate 32-bit
           * stores on 32-bit machines or else SPARC will bus
           * error on mis-alignment
           */
          dput        = (long *) &(FLOAT_OF(argv[i]));
          args[pos++] = *dput;
          if (sizeof(long) < sizeof(double)) {
            args[pos++] = *(dput + 1);
          }
        }
        break;
      case VALUE_TYPE_STRING:
        sput  = (char **) (args + pos);
        *sput = STR_OF(argv[i]);
        pos  += sizeof(char *) / sizeof(long);
        break;
      case VALUE_TYPE_RES:
        if (argv[i]->value_u.res_val->get) {
          resval = argv[i]->value_u.res_val->get(RESDATA_OF(argv[i]));
        } else {
          resval = NULL;
        }
        pput  = (void **) (args + pos);
        *pput = resval;
        pos  += sizeof(void *) / sizeof(long);
        break;
      default:
        sanity(0);
    }
  }

  return args;
}

/*
 * Call C function by name and argument list
 */
static value *ccall(unsigned int argc, value **argv, char type, int mfree)
{
  void *handle = RESDATA_OF(argv[0]);
  char *name = STR_OF(argv[1]);
  long *args;
  double *dargs;
  void *func;
  int ires;
  double fres;
  void *pres;
  value *res;

  if (!is_lib(argv[0]) || !name || !handle) {
    return value_make_void();
  }

  func = dlsym(handle, name);
  if (!func) {
    return value_make_void();
  }

  args = makeargs(argc - 2, argv + 2, &dargs);
  if (!args) {
    return value_make_void();
  }

  switch (type) {
    case 'v':
      voidcall(func, args, dargs);
      res = value_make_void();
      break;
    case 'i':
      ires = intcall(func, args, dargs);
      res = value_make_int(ires);
      break;
    case 'f':
      fres = floatcall(func, args, dargs);
      res = value_make_float(fres);
      break;
    case 'p':
      pres = ptrcall(func, args, dargs);
      res = mem_make_pointer(pres, mfree);
      break;
    default:
      res = value_make_void();
      break;
  }

  free(args);
  free(dargs);
  return res;
}

/*
 * Call C function that returns nothing
 */
value *dyn_call_void(arena_state *s, unsigned int argc, value **argv)
{
  return ccall(argc, argv, 'v', 0);
}

/*
 * Call C function that returns an int (or compatible value)
 */
value *dyn_call_int(arena_state *s, unsigned int argc, value **argv)
{
  return ccall(argc, argv, 'i', 0);
}

/*
 * Call C function that returns a float
 */
value *dyn_call_float(arena_state *s, unsigned int argc, value **argv)
{
  return ccall(argc, argv, 'f', 0);
}

/*
 * Call C function that returns a pointer
 */
value *dyn_call_ptr(arena_state *s, unsigned int argc, value **argv)
{
  value *freeval;
  int free = 0, nargc = argc;
  
  freeval = argv[argc - 1];
  if (freeval->type == VALUE_TYPE_BOOL) {
    free = BOOL_OF(freeval);
    --nargc;
  }

  return ccall(nargc, argv, 'p', free);
}

/*
 * Dynamically load a C library
 */
value *dyn_open(arena_state *s, unsigned int argc, value **argv)
{
  char *name = STR_OF(argv[0]);
  void *handle;
  
  if (!value_str_compat(argv[0])) {
    return value_make_void();
  }

  handle = dlopen(name, RTLD_NOW | RTLD_GLOBAL);
  if (!handle) {
    return value_make_void();
  }

  return value_make_resource(handle, dyn_free);
}

/*
 * Unload a previously loaded C library
 */
value *dyn_close(arena_state *s, unsigned int argc, value **argv)
{
  void *handle = RESDATA_OF(argv[0]);
  
  if (is_lib(argv[0]) && handle) {
    dlclose(handle);
    RESDATA_OF(argv[0]) = NULL;
  }
  return value_make_void();
}

/*
 * Get pointer to C function
 */
value *dyn_fn_pointer(arena_state *s, unsigned int argc, value **argv)
{
  void *handle = RESDATA_OF(argv[0]);
  char *name = STR_OF(argv[1]);
  void *func;
  
  if (!is_lib(argv[0]) || !value_str_compat(argv[1])) {
    return value_make_void();
  }
  
  func = dlsym(handle, name);
  if (!func) {
    return value_make_void();
  }
  return mem_make_pointer(func, 0);
}

#else

/*
 * Indicate that dynamic C calls are not supported
 */
value *dyn_supported(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(0);
}

/*
 * Dummy function
 */
value *dyn_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(0);
}

/*
 * Dummy function
 */
value *dyn_open(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *dyn_close(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *dyn_call_void(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *dyn_call_int(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *dyn_call_float(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *dyn_call_ptr(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

/*
 * Dummy function
 */
value *dyn_fn_pointer(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_void();
}

#endif

/*
 * Convert float to call-stack representation
 */ 
value *dyn_c_float(arena_state *s, unsigned int argc, value **argv)
{
  double dval = FLOAT_OF(argv[0]);
  float fval = dval;
  long *lptr = (void *) &fval;
  
  if (sizeof(float) == sizeof(long)) {
    /* bits in float == bits in long, pass as integer */
    return value_make_int(*lptr);
  } else {
    /* bits in float != bits in long, pass as double */
    return value_make_float(dval);
  }
}
