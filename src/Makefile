include ../Makefile.vars

INCS           = -I../include -I/opt/local/include -I/usr/local/include
LTINSTALL     := ${LIBTOOL} --mode=install ../install-sh
LTUNINSTALL   := ${LIBTOOL} --quiet --mode=uninstall rm -f
OBJFILESNP     = dwm_gmk_aliasfn.lo \
                 dwm_gmk_bison.lo \
                 dwm_gmk_cppdeps.lo \
                 dwm_gmk_curpath.lo \
                 dwm_gmk_files.lo \
                 dwm_gmk_flex.lo \
                 dwm_gmk_funcs.lo \
                 dwm_gmk_include.lo \
                 dwm_gmk_my.lo \
                 dwm_gmk_pushpop.lo \
                 dwm_gmk_pwd.lo \
                 dwm_gmk_relpath.lo \
                 dwm_gmk_relpwd.lo \
                 dwm_gmk_reverse.lo \
                 dwm_gmk_rgxmatch.lo \
                 dwm_gmk_rgxreplace.lo \
                 dwm_gmk_rgxsearch.lo \
                 dwm_gmk_rgxsubst.lo \
                 dwm_gmk_rotate.lo \
                 dwm_gmk_setifcwd.lo \
                 dwm_gmk_setup.lo \
                 dwm_gmk_sort.lo \
                 dwm_gmk_subdirs.lo \
                 dwm_gmk_thisdir.lo \
                 dwm_gmk_uniqleft.lo \
                 dwm_gmk_uniqright.lo \
                 DwmGmkMkfileStack.lo \
                 DwmGmkMyVars.lo \
                 DwmGmkUtils.lo
OBJFILES       = $(OBJFILESNP:%.lo=../obj/%.lo)
OBJDEPS        = $(OBJFILESNP:%.lo=deps/%_deps)
shlib_version  = $(shell ../getvers.sh -s)

../lib/dwm_gmk.la: ${OBJFILES}
	@${LIBTOOL} --mode=link --tag=CXX ${CXX} -module -o $@ $^ \
	  -shared -rpath ${INSTALLPREFIX}/lib -version-info ${shlib_version}

#  dependency rule
deps/%_deps: %.cc
	@echo "making dependencies for $<"
	@set -e; \
	${CXX} -MM ${CXXFLAGS} ${INCS} -c $< | \
	 sed 's/\($*\)\.o[ :]*/..\/obj\/\1.o ..\/obj\/\1.lo $(@D)\/$(@F) : /g' > $@ ; [ -s $@ ] || \
	 rm -f $@

#  only include dependency makefiles if target is not 'clean' or 'distclean'
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include ${OBJDEPS}
endif
endif

../obj/%.lo: %.cc deps/%_deps
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

