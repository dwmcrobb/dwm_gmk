# load ../lib/.libs/dwm_gmk.so(dwm_gmk_setup)
load /usr/local/lib/dwm_gmk.so(dwm_gmk_setup)
$(call dwm_gmk_init)

include $(dwm_thisdir )/../Makefile.vars

tests:: test_relpath test_dirfiles test_uniqsort test_subdirs test_rgxmatch \
        test_rgxsearch test_rgxreplace test_rgxsubst

test_relpath::
	@[ $(dwm_relpath $(dwm_thisdir )/../src,$(dwm_thisdir )) = ../tests ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )/../src) = ../src ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_top )) = .. ] || exit
	@[ $(dwm_relpath $(dwm_top ),$(dwm_thisdir )) = tests ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )) = . ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_top )/src) = ../src ] || exit
	@[ "/$(dwm_relpath /,$(dwm_curpath ))" = $(shell pwd) ] || exit
	@echo relpath tests passed

test_dirfiles::
	@[ $(dwm_dirfiles .,Makefile) = Makefile ] || exit
	@[ $(dwm_dirfiles $(dwm_thisdir )/../src,dwm_gmk_dirfiles\.cc) = dwm_gmk_dirfiles.cc ] || exit
	@[ -n "$(dwm_dirfiles $(dwm_thisdir )/../src,.+\.cc)" ] || exit
	@[ -z "$(dwm_dirfiles .,Make\.ile)" ] || exit
	@[ "$(dwm_dirfiles .,Make.ile)" = Makefile ] || exit
	@[ $(words $(dwm_dirfiles $(dwm_thisdir )/../src,.+\.cc)) -ge 7 ] || exit
	@echo dirfiles tests passed

test_uniqsort::
	@[ "$(dwm_uniqsort a b a b a b c a b c d)" = "a b c d" ] || exit
	@[ "$(dwm_uniqsort d c b a c b a b a b a)" = "a b c d" ] || exit
	@echo uniqsort tests passed

test_subdirs::
	@[ "$(dwm_subdirs )" = "" ] || exit
	@[ $(words $(dwm_subdirs $(dwm_thisdir )/..)) -ge 5 ] || exit
	@[ $(words $(dwm_subdirs $(dwm_thisdir )/..,tests)) -eq 1 ] || exit
	@[ "$(dwm_subdirs $(dwm_thisdir )/..,tests)" = tests ] || exit
	@[ "$(dwm_subdirs $(dwm_thisdir )/..,src)" = src ] || exit
	@echo subdirs tests passed

test_rgxmatch::
	@[ "$(dwm_rgxmatch dwm,^d.+)" = "dwm" ] || exit
	@[ "$(dwm_rgxmatch dwm,^d(.+))" = "dwm wm" ] || exit
	@[ "$(dwm_rgxmatch dwm,.wm$$)" = "dwm" ] || exit
	@echo rgxmatch tests passed

test_rgxsearch::
	@[ "$(dwm_rgxsearch dwm,d)" = "d" ] || exit
	@[ "$(dwm_rgxsearch dwm,^d)" = "d" ] || exit
	@[ "$(dwm_rgxsearch dwm,w)" = "w" ] || exit
	@[ "$(dwm_rgxsearch dwm,m)" = "m" ] || exit
	@[ "$(dwm_rgxsearch dwm,m$$)" = "m" ] || exit
	@[ "$(dwm_rgxsearch dwm,t.+)" = "" ] || exit
	@[ "$(dwm_rgxsearch dwm,(d).+)" = "dwm d" ] || exit
	@echo rgxsearch tests passed

test_rgxreplace::
	@[ "$(dwm_rgxreplace Quick brown fox,a|e|i|o|u,[$$&])" = "Q[u][i]ck br[o]wn f[o]x" ] || exit
	@[ "$(dwm_rgxreplace Quick brown fox, brown, [$$`])" = "Quick [Quick] fox" ] || exit
	@[ "$(dwm_rgxreplace Quick brown fox,brown ,[$$'] )" = "Quick [fox] fox" ] || exit
	@echo rgxreplace tests passed

test_rgxsubst::
	@[ "$(dwm_rgxsubst (.+)\.cc$$,$$1.o,foo.cc bar.cc foobar.cc)" \
	  = "foo.o bar.o foobar.o" ] || exit
	@[ "$(dwm_rgxsubst (.+)_(.+)\.cc,$$1_$$2.o,a_b.cc c_d.cc e_f.cc)" \
	  = "a_b.o c_d.o e_f.o" ] || exit
	@[ "$(dwm_rgxsubst ^Test(.+)\.o,Test$$1,Test1.o Test2.o Test3.o)" \
	  = "Test1 Test2 Test3" ] || exit
	@echo rgxsubst tests passed


