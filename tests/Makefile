load ../lib/.libs/dwm_gmk.so(dwm_gmk_setup)
# load /usr/local/lib/dwm_gmk.so(dwm_gmk_setup)
$(call dwm_gmk_init)

include ../Makefile.vars

tests:: test_relpath test_dirfiles test_uniqsort

test_relpath::
	@[ $(dwm_relpath ../src,$(dwm_thisdir )) = ../tests ] || echo "failed" && exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )/../src) = ../src ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_relpwd ..)) = .. ] || exit
	@[ $(dwm_relpath ..,$(dwm_thisdir )) = tests ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )) = . ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),../src) = ../src ] || exit
	@[ "/$(dwm_relpath /,$(dwm_thisdir ))" = $(shell pwd) ] || exit
	@echo relpath tests passed

test_dirfiles::
	@[ $(dwm_dirfiles .,Makefile) = Makefile ] || exit
	@[ $(dwm_dirfiles ../src,dwm_gmk_dirfiles\.cc) = dwm_gmk_dirfiles.cc ] || exit
	@[ -n "$(dwm_dirfiles ../src,.+\.cc)" ] || exit
	@[ -z "$(dwm_dirfiles .,Make\.ile)" ] || exit
	@[ "$(dwm_dirfiles .,Make.ile)" = Makefile ] || exit
	@[ $(words $(dwm_dirfiles ../src,.+\.cc)) -ge 7 ] || exit
	@echo dirfiles tests passed

test_uniqsort::
	@[ "$(dwm_uniqsort a b a b a b c a b c d)" = "a b c d" ] || exit
	@[ "$(dwm_uniqsort d c b a c b a b a b a)" = "a b c d" ] || exit
	@echo uniqsort tests passed

$(info thisdir $(dwm_thisdir ))
$(info dwm_relpwd ..)
$(info dwm_top $(dwm_top ))
$(info dwm_totop $(dwm_totop ))
$(info dwm_totop ../Makefile.vars $(dwm_totop ../Makefile.vars))
$(info dwm_fromtop $(dwm_fromtop ))
$(info dwm_fromtop ../Makefile.vars $(dwm_fromtop ../Makefile.vars))
$(info dwm_curpath $(dwm_curpath ))
$(info dwm_cwd $(dwm_cwd ))
# $(info relpath thisdir ../src: $(dwm_relpath $(dwm_thisdir),../src))
# $(info $(dwm_dirfiles ../src,.+\.cc))
