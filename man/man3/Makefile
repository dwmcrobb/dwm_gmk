include ../../Makefile.vars

all: dwmgmk.pdf dwmgmk.html

dwmgmk.pdf: dwmgmk.3
	mandoc -T pdf $< > $@

dwmgmk.html: dwmgmk.3
	mandoc -T html -O style=./dwmgmk.css $< > $@

TARTARGETS = ${TARDIR}/man/man3/dwmgmk.3 \
             ${TARDIR}/share/doc/dwmgmk/dwmgmk.pdf \
             ${TARDIR}/share/doc/dwmgmk/dwmgmk.html

tarprep: ${TARTARGETS}

${TARDIR}/man/man3/dwmgmk.3: dwmgmk.3
	${TOP}/install-sh -m 644 $< $@

${TARDIR}/share/doc/dwmgmk/dwmgmk.%: dwmgmk.%
	${TOP}/install-sh -m 644 $< $@

clean::
	rm -f dwmgmk.pdf dwmgmk.html

