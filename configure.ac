dnl Process this file with autoconf to produce a configure script.


AC_PREREQ(2.61)
AC_INIT([bpwrapper], [0.1.0], [freeplant@gmail.com])
AC_CONFIG_HEADER([config.h])

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.9 foreign])

AC_MINGW32

dnl enable the build of share library by default
AC_DISABLE_SHARED

AC_SUBST(LIBTOOL_DEPS)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
#AM_C_PROTOTYPES
AC_C_CONST
AC_PROG_MAKE_SET
# AC_PROG_RANLIB
LT_INIT

# check platform
AC_MSG_CHECKING(for WIN32)
if test "$MINGW32" = yes; then
  bwin32=true
  AC_MSG_RESULT(compile in mingw32)
else
  AC_MSG_RESULT(no)
fi

AC_MSG_CHECKING(for Mac)
if test "$(uname)" = "Darwin"; then
  bmac=true
  AC_MSG_RESULT(compile in mac)
else
  AC_MSG_RESULT(no)
fi

AC_MSG_CHECKING(for Linux)
if test "$bmac" != "true" -a "$bwin32" != "true"; then
  blinux=true
  AC_MSG_RESULT(compile in linux)
else
  AC_MSG_RESULT(no)
fi

AM_CONDITIONAL([WIN32], [test "$bwin32" = "true"])
AM_CONDITIONAL([MACOS], [test "$bmac" = "true"])
AM_CONDITIONAL([LINUX], [test "$blinux" = "true"])


BREAKPAD_REQUIRED=0.1

PKG_CHECK_MODULES(BREAKPAD, [breakpad >= $BREAKPAD_REQUIRED])
AC_SUBST(BREAKPAD_CFLAGS)
AC_SUBST(BREAKPAD_LIBS)

PKG_CHECK_MODULES(BREAKPADCLIENT, [breakpad-client >= $BREAKPAD_REQUIRED])
AC_SUBST(BREAKPADCLIENT_CFLAGS)
AC_SUBST(BREAKPADCLIENT_LIBS)

AC_CONFIG_FILES([Makefile bpwrapper.pc tests/Makefile])

AC_OUTPUT
