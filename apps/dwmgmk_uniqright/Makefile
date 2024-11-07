include ../../Makefile.vars

INCS       := -I../../include
LTINSTALL  := ${LIBTOOL} --mode=install ../../install-sh

dwmgmk_uniqright: dwmgmk_uniqright.o
	${LIBTOOL} --mode=link --tag=CXX ${CXX} ${LDFLAGS} -o $@ $^

dwmgmk_uniqright.o: dwmgmk_uniqright.cc
	${CXX} ${CXXFLAGS} ${INCS} -c $< -o $@

tarprep: ${TARDIR}/bin/dwmgmk_uniqright

${TARDIR}/bin/dwmgmk_uniqright: dwmgmk_uniqright
	${LTINSTALL} -c $< $@

clean::
	@rm -f dwmgmk_uniqright dwmgmk_uniqright.o

distclean:: clean
	@rm -f ${TARDIR}/bin/dwmgmk_uniqright
