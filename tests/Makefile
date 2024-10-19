# load ../lib/.libs/dwm_gmk.so(dwm_gmk_setup)
load /usr/local/lib/dwm_gmk.so(dwm_gmk_setup)
$(call dwm_gmk_init)

include $(dwm_thisdir )/../Makefile.vars

tests:: test_relpath test_dirfiles test_uniqsort test_subdirs test_rgxmatch \
        test_rgxsearch test_rgxreplace test_rgxsubst test_bison1 test_bison2 \
	test_bison3

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
	@[ "$(dwm_rgxsubst (^.+)\.y$$,$$1.cc $$1.hh,Parser1.y)" \
	  = "Parser1.cc Parser1.hh" ] || exit
	@echo rgxsubst tests passed

bison_rule1 = $(dwm_bison parser.y,-t,-d,-o myparser.cc,-g parser.graph)

test_bison1::
	@[ $(words $(bison_rule1)) -eq 18 ] || exit
	@[ "$(word 1,$(bison_rule1))" = "BISONTARGETS" ] || exit
	@[ "$(word 2,$(bison_rule1))" = "+=" ] || exit
	@[ "$(word 3,$(bison_rule1))" = "parser.graph" ] || exit
	@[ "$(word 4,$(bison_rule1))" = "myparser.cc" ] || exit
	@[ "$(word 5,$(bison_rule1))" = "myparser.hh" ] || exit
	@[ "$(word 6,$(bison_rule1))" = "parser.graph" ] || exit
	@[ "$(word 7,$(bison_rule1))" = "myparser.cc" ] || exit
	@[ "$(word 8,$(bison_rule1))" = "myparser.hh" ] || exit
	@[ "$(word 9,$(bison_rule1))" = "&:" ] || exit
	@[ "$(word 10,$(bison_rule1))" = "parser.y" ] || exit
	@[ "$(word 11,$(bison_rule1))" = "bison" ] || exit
	@[ "$(word 12,$(bison_rule1))" = "-d" ] || exit
	@[ "$(word 13,$(bison_rule1))" = "-t" ] || exit
	@[ "$(word 14,$(bison_rule1))" = "-g" ] || exit
	@[ "$(word 15,$(bison_rule1))" = "parser.graph" ] || exit
	@[ "$(word 16,$(bison_rule1))" = "-o" ] || exit
	@[ "$(word 17,$(bison_rule1))" = "myparser.cc" ] || exit
	@[ "$(word 18,$(bison_rule1))" = "$$<" ] || exit
	@echo bison1 tests passed

bison_rule2 = $(dwm_bison parser.y,-d)

test_bison2::
	@[ $(words $(bison_rule2)) -eq 13 ] || exit
	@[ "$(word 1,$(bison_rule2))" = "BISONTARGETS" ] || exit
	@[ "$(word 2,$(bison_rule2))" = "+=" ] || exit
	@[ "$(word 3,$(bison_rule2))" = "parser.cc" ] || exit
	@[ "$(word 4,$(bison_rule2))" = "parser.hh" ] || exit
	@[ "$(word 5,$(bison_rule2))" = "parser.cc" ] || exit
	@[ "$(word 6,$(bison_rule2))" = "parser.hh" ] || exit
	@[ "$(word 7,$(bison_rule2))" = "&:" ] || exit
	@[ "$(word 8,$(bison_rule2))" = "parser.y" ] || exit
	@[ "$(word 9,$(bison_rule2))" = "bison" ] || exit
	@[ "$(word 10,$(bison_rule2))" = "-d" ] || exit
	@[ "$(word 11,$(bison_rule2))" = "-o" ] || exit
	@[ "$(word 12,$(bison_rule2))" = "parser.cc" ] || exit
	@[ "$(word 13,$(bison_rule2))" = "$$<" ] || exit

bison_rule3 = $(dwm_bison parser.y,-d,-o parser.c)

test_bison3::
	@[ $(words $(bison_rule3)) -eq 13 ] || exit
	@[ "$(word 1,$(bison_rule3))" = "BISONTARGETS" ] || exit
	@[ "$(word 2,$(bison_rule3))" = "+=" ] || exit
	@[ "$(word 3,$(bison_rule3))" = "parser.c" ] || exit
	@[ "$(word 4,$(bison_rule3))" = "parser.h" ] || exit
	@[ "$(word 5,$(bison_rule3))" = "parser.c" ] || exit
	@[ "$(word 6,$(bison_rule3))" = "parser.h" ] || exit
	@[ "$(word 7,$(bison_rule3))" = "&:" ] || exit
	@[ "$(word 8,$(bison_rule3))" = "parser.y" ] || exit
	@[ "$(word 9,$(bison_rule3))" = "bison" ] || exit
	@[ "$(word 10,$(bison_rule3))" = "-d" ] || exit
	@[ "$(word 11,$(bison_rule3))" = "-o" ] || exit
	@[ "$(word 12,$(bison_rule3))" = "parser.c" ] || exit
	@[ "$(word 13,$(bison_rule3))" = "$$<" ] || exit
