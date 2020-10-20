/*
 * Foreign function interface
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../../doc/LICENSE for license
 */

#ifdef __i386
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __sparc
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef _ARCH_PPC
#ifndef _ARCH_PPC64
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif
#endif

#ifdef __arm
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __m68k
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __m68000
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __mc68000
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __s390
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __x86_64
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif

#ifdef __alpha
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 6
#endif

#ifdef __ia64
#undef HAVE_FOREIGN
#undef NOSTACK_FLOATS
#define HAVE_FOREIGN 1
#define NOSTACK_FLOATS 0
#endif
