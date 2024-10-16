CXXFLAGS       = -std=c++20 -O2
INCS           = -I../include
INSTALLPREFIX  = /usr/local
LDFLAGS        = -std=c++20
LIBTOOL        = libtool
OBJFILES       = dwm_gmk_dirfiles.lo \
                 dwm_gmk_relpath.lo \
                 dwm_gmk_setup.lo \
                 dwm_gmk_thisdir.lo
shlib_version  = 0:0:0

libdwm_gmk.la: ${OBJFILES}
	${LIBTOOL} --mode=link --tag=CXX ${CXX} -o $@ $^ \
	 -rpath ${INSTALLPREFIX}/lib -version-info ${shlib_version}

%.lo: %.cc ../include/dwm_gmk.h
	${LIBTOOL} --mode=compile --tag=CXX ${CXX} ${CXXFLAGS} ${INCS} -c $< -o $@

clean::
	${LIBTOOL} --mode=clean rm -f libdwm_gmk.la ${OBJFILES}
