APPS      := dwmgmk_quiet dwmgmk_uniqleft dwmgmk_uniqright
APPSCLEAN := $(APPS:%=%-clean)
TARPREP   := $(APPS:%=%-tarprep)
DISTCLEAN := $(APPS:%=%-distclean)

all:: ${APPS}

${APPS}::
	${MAKE} -s -C $@

tarprep:: ${TARPREP}
${TARPREP}::
	${MAKE} -C $(patsubst %-tarprep,%,$@) tarprep

clean:: ${APPSCLEAN}
${APPSCLEAN}::
	@${MAKE} -s -C $(patsubst %-clean,%,$@) clean

distclean:: ${DISTCLEAN}
${DISTCLEAN}::
	${MAKE} -s -C $(patsubst %-distclean,%,$@) distclean
