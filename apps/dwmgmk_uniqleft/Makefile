include ../../Makefile.vars

INCS       := -I../../include
LTINSTALL  := ${LIBTOOL} --mode=install ../../install-sh

dwmgmk_uniqleft: dwmgmk_uniqleft.o
	${LIBTOOL} --mode=link --tag=CXX ${CXX} ${LDFLAGS} -o $@ $^

dwmgmk_uniqleft.o: dwmgmk_uniqleft.cc
	${CXX} ${CXXFLAGS} ${INCS} -c $< -o $@

tarprep: ${TARDIR}/bin/dwmgmk_uniqleft

${TARDIR}/bin/dwmgmk_uniqleft: dwmgmk_uniqleft
	${LTINSTALL} -c $< $@

clean::
	@rm -f dwmgmk_uniqleft dwmgmk_uniqleft.o

distclean:: clean
	@rm -f ${TARDIR}/bin/dwmgmk_uniqleft
