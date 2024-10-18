include ../../Makefile.vars

LTINSTALL   = ${LIBTOOL} --mode=install ../../install-sh

dwmgmk_quiet: dwmgmk_quiet.o
	${CXX} ${LDFLAGS} -o $@ $<

dwmgmk_quiet.o: dwmgmk_quiet.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

tarprep: ${TARDIR}/bin/dwmgmk_quiet

${TARDIR}/bin/dwmgmk_quiet: dwmgmk_quiet
	${LTINSTALL} -c $< $@

clean::
	@rm -f dwmgmk_quiet dwmgmk_quiet.o

distclean:: clean
	@rm -f ${TARDIR}/bin/dwmgmk_quiet
