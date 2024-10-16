include ../Makefile.vars

INCS           = -I../include -I/opt/local/include
LTINSTALL     := ${LIBTOOL} --mode=install ../install-sh
LTUNINSTALL   := ${LIBTOOL} --quiet --mode=uninstall rm -f
OBJFILESNP     = dwm_gmk_dirfiles.lo \
                 dwm_gmk_init.lo \
                 dwm_gmk_relpath.lo \
                 dwm_gmk_setup.lo \
                 dwm_gmk_thisdir.lo
OBJFILES       = $(OBJFILESNP:%.lo=../obj/%.lo)
shlib_version  = $(shell ../getvers.sh -s)

../lib/libdwm_gmk.la: ${OBJFILES}
	${LIBTOOL} --mode=link --tag=CXX ${CXX} -module -o $@ $^ -shared \
	 -rpath ${INSTALLPREFIX}/lib -version-info ${shlib_version}

../obj/%.lo: %.cc ../include/dwm_gmk.h
	${LIBTOOL} --mode=compile --tag=CXX ${CXX} ${CXXFLAGS} ${INCS} -c $< -o $@

tarprep: ${TARDIR}/lib/libdwm_gmk.la

${TARDIR}/lib/libdwm_gmk.la: ../lib/libdwm_gmk.la
	${LTINSTALL} -c $< ${TARDIR}/lib/libdwm_gmk.la

distclean:: clean clean-tarprep

clean::
	${LIBTOOL} --mode=clean rm -f ../lib/libdwm_gmk.la ${OBJFILES}

clean-tarprep::
	@${LTUNINSTALL} ${TARDIR}/lib/libdwm_gmk.la

