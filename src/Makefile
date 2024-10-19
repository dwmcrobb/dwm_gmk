include ../Makefile.vars

$(info PWD $(PWD))

INCS           = -I../include -I/opt/local/include -I/usr/local/include
LTINSTALL     := ${LIBTOOL} --mode=install ../install-sh
LTUNINSTALL   := ${LIBTOOL} --quiet --mode=uninstall rm -f
OBJFILESNP     = dwm_gmk_bison.lo \
                 dwm_gmk_curpath.lo \
                 dwm_gmk_dirfiles.lo \
                 dwm_gmk_flex.lo \
                 dwm_gmk_fromtop.lo \
                 dwm_gmk_init.lo \
                 dwm_gmk_pwd.lo \
                 dwm_gmk_relpath.lo \
                 dwm_gmk_relpwd.lo \
                 dwm_gmk_rgxmatch.lo \
                 dwm_gmk_settop.lo \
                 dwm_gmk_subdirs.lo \
                 dwm_gmk_totop.lo \
                 dwm_gmk_setup.lo \
                 dwm_gmk_thisdir.lo \
                 dwm_gmk_uniqsort.lo \
                 DwmGmkUtils.lo
OBJFILES       = $(OBJFILESNP:%.lo=../obj/%.lo)
shlib_version  = $(shell ../getvers.sh -s)

../lib/dwm_gmk.la: ${OBJFILES}
	@${LIBTOOL} --mode=link --tag=CXX ${CXX} -module -o $@ $^ \
	  -shared -rpath ${INSTALLPREFIX}/lib -version-info ${shlib_version}

../obj/%.lo: %.cc ../include/dwm_gmk.h
	@${LIBTOOL} --mode=compile --tag=CXX ${CXX} ${CXXFLAGS} \
	  ${INCS} -c $< -o $@

tarprep: ${TARDIR}/lib/dwm_gmk.la

${TARDIR}/lib/dwm_gmk.la: ../lib/dwm_gmk.la
	${LTINSTALL} -c $< ${TARDIR}/lib/dwm_gmk.la

distclean:: clean clean-tarprep

clean::
	@${LIBTOOL} --quiet --mode=clean rm -f ../lib/dwm_gmk.la ${OBJFILES}

clean-tarprep::
	@${LTUNINSTALL} ${TARDIR}/lib/dwm_gmk.la

