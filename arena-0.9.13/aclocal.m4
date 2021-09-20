dnl set warning flags for gcc
dnl
AC_DEFUN([AC_PROG_GCC_FLAGS],[
  if test "$GCC" = "yes"
  then
    CFLAGS="$CFLAGS -fno-strict-aliasing -Wall"
  fi
])

dnl check whether PCRE support is wanted
dnl
AC_DEFUN([AC_ENABLE_PCRE],[
  AC_ARG_ENABLE(pcre,
    [AS_HELP_STRING([--enable-pcre],[enable PCRE support (no)])],
    [if test "$enableval" = "yes"
    then
      AC_DEFINE([WANT_PCRE])
    fi])
])
