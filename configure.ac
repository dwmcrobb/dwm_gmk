AC_INIT([dwmgmk],[m4_esyscmd_s(./getvers.sh -v)],[dwmcrobb@me.com],[dwmgmk],[http://www.mcplex.net])

AC_PROG_CC
AC_PROG_CXX
AC_CANONICAL_TARGET

# LT_INIT([disable-static])
# AC_PROG_LIBTOOL

dnl  ###  Read some generally useful macros.
builtin(include, ./dwm.m4)  dnl
builtin(include, ax_check_compile_flag.m4) dnl

# OSLIBS=""
LIBTOOL="libtool"

case $host_os in
  freebsd1[[0123]]*)
    CXXFLAGS="-O2"
    LDFLAGS=""
    ;;
  linux*)
    CXXFLAGS="-O2"
    DEBARCH=`dpkg --print-architecture`
    AC_SUBST(DEBARCH)
    ;;
  darwin*)
    CC="clang++"
    CXX="clang++"
    CXXFLAGS="${CXXFLAGS} -stdlib=libc++"
    LDFLAGS="${LDFLAGS} -g -O2 -stdlib=libc++"
    LIBTOOL="glibtool"
    ;;
esac
AC_SUBST(LIBTOOL)
AC_SUBST(LDFLAGS)

echo "host_os ${host_os}"

dnl  Check for C++20
DWM_CHECK_CPLUSPLUS_20

DWM_SET_PKGVARS(dwmgmk,[dwmgmk-0.0.0])
DWM_GET_TAG([dwmgmk])

AC_SUBST(CXXFLAGS)

AC_CONFIG_FILES([Makefile.vars packaging/debcontrol packaging/fbsd_manifest
                 packaging/dwmgmk.pc])
AC_OUTPUT
