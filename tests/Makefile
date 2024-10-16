load ../lib/.libs/libdwm_gmk.so(dwm_gmk_setup)
$(call dwm_gmk_init)

include ../Makefile.vars

tests:: test_relpath test_dirfiles

test_relpath::
	@[ $(dwm_relpath ../src,$(dwm_thisdir )) = ../tests ] || echo "failed" && exit
	@[ $(dwm_relpath $(dwm_thisdir ),../src) = ../src ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),..) = .. ] || exit
	@[ $(dwm_relpath ..,$(dwm_thisdir )) = tests ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )) = . ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),../src) = ../src ] || exit
	@[ /$(dwm_relpath /,$(dwm_thisdir )) = `pwd` ] || exit
	@echo relpath tests passed

test_dirfiles::
	@[ $(dwm_dirfiles .,Makefile) = Makefile ] || exit
	@[ $(dwm_dirfiles ../src,dwm_gmk_dirfiles\.cc) = dwm_gmk_dirfiles.cc ] || exit
	@[ -n "$(dwm_dirfiles ../src,.+\.cc)" ] || exit
	@[ -z "$(dwm_dirfiles .,Make\.ile)" ] || exit
	@[ "$(dwm_dirfiles .,Make.ile)" = Makefile ] || exit
	@[ $(words $(dwm_dirfiles ../src,.+\.cc)) -ge 4 ] || exit
	@echo dirfiles tests passed

# $(info thisdir $(dwm_thisdir ))
# $(info relpath thisdir ../src: $(dwm_relpath $(dwm_thisdir),../src))
# $(info $(dwm_dirfiles ../src,.+\.cc))
