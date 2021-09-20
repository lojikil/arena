AC_INIT(arena.c)
AC_CONFIG_HEADER(config.h)
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_GCC_FLAGS
AC_HEADER_STDC
AC_SEARCH_LIBS(dlopen, dl)
AC_CHECK_FUNCS(dlopen)
AC_SEARCH_LIBS(pcre_compile, pcre)
AC_CHECK_FUNCS(pcre_compile)
AC_ENABLE_PCRE
AC_OUTPUT(Makefile libmisc/Makefile libruntime/Makefile libparser/Makefile libeval/Makefile libstdlib/Makefile tests/Makefile doc/arena.1 doc/manual/transform)
