load ../lib/.libs/dwm_gmk.so(dwm_gmk_setup)
myfile := $(abspath $(lastword $(MAKEFILE_LIST)))
myfile_s := $(myfile)
$(dwm_include ../Makefile.vars)
myfile := $(myfile_s)

$(dwm_myns puppy)

origfile = $(myfile)
$(dwm_my foo2 = $(origfile))
$(dwm_my foo3 := $(origfile))

$(dwm_my append1 := antelope)
$(dwm_my append1 += $(dwm_my foo3))
$(dwm_my append2 = antelope)
$(dwm_my append2 += $(dwm_my foo2))

origfile = kitten

tests:: test_my test_relpath test_files test_sort test_subdirs test_rgxmatch \
        test_rgxsearch test_rgxreplace test_rgxsubst test_bison1 test_bison2 \
        test_bison3 test_flex1 test_flex2 test_reverse test_pop test_rotate \
        test_alias test_uniqleft test_uniqright test_include test_vrgx \
	test_ifcwd

test_ifcwd::
	@[ "$(dwm_ifcwd yes,no)" = "yes" ] || exit
	@[ "$(dwm_ifcwd no,yes)" = "no" ] || exit
	@echo ifcwd tests passed

test_vrgx::
	@[ $(words $(dwm_vrgx MAKE.+)) -ge 8 ] || exit
	@[ $(words $(dwm_vrgx .+\.cc)) -ge 2 ] || exit
	@echo vrgx tests passed

test_include::
	@[ "$(firstword $(dwm_incstack))" = "$(myfile)" ] || exit
	@[ $(words $(dwm_incstack)) -eq 1 ] || exit
	@echo include tests passed

test_alias::
	$(dwm_aliasfn rotl,dwm_rotl)
	@[ "$(rotl a b c d e,2)" = "c d e a b" ] || exit
	$(dwm_aliasfn rotr,dwm_rotr)
	@[ "$(rotr a b c d e,2)" = "d e a b c" ] || exit
	$(dwm_aliasfn ps,patsubst)
	@[ "$(ps %.cc,%.hh,foo.cc bar.cc foobar.cc)" = "foo.hh bar.hh foobar.hh" ] || exit
	@echo alias tests passed

test_rotate::
	@[ "$(dwm_rotl a b c d e,2)" = "c d e a b" ] || exit
	@[ "$(dwm_rotr a b c d e,2)" = "d e a b c" ] || exit
	@[ "$(dwm_rotl a b c d e,7)" = "c d e a b" ] || exit
	@[ "$(dwm_rotr a b c d e,7)" = "d e a b c" ] || exit
	@[ "$(dwm_rotl a b c d e,5)" = "a b c d e" ] || exit
	@[ "$(dwm_rotr a b c d e,5)" = "a b c d e" ] || exit
	@[ "$(dwm_rotl a b c d e,0)" = "a b c d e" ] || exit
	@[ "$(dwm_rotr a b c d e,0)" = "a b c d e" ] || exit
	@[ "$(dwm_rotl a b c d e)" = "b c d e a" ] || exit
	@[ "$(dwm_rotr a b c d e)" = "e a b c d" ] || exit
	@echo rotate tests passed

test_reverse::
	@[ "$(dwm_reverse a b c d e)" = "e d c b a" ] || exit
	@echo reverse tests passed

test_pop::
	@[ "$(dwm_popf a b c d e)" = "b c d e" ] || exit
	@[ "$(dwm_popb a b c d e)" = "a b c d" ] || exit
	@echo pop tests passed

test_my::
	@[ "$(dwm_my foo2)" = "kitten" ] || exit
	@[ "$(dwm_my foo3)" = "$(myfile)" ] || exit
	@[ $(words $(dwm_myvn puppy)) -eq 4 ] || exit
	@[ "$(dwm_myvn puppy)" = "append1 append2 foo2 foo3" ] || exit
	@[ $(words $(dwm_myvn )) -eq 4 ] || exit
	@[ "$(dwm_myvn )" = "puppy.append1 puppy.append2 puppy.foo2 puppy.foo3" ] || exit
	@[ $(words $(dwm_funcs)) -eq 33 ] || exit
	@[ "$(dwm_my append1)" = "antelope $(myfile)" ] || exit
	@[ "$(dwm_my append2)" = "antelope kitten" ] || exit
	@echo my tests passed

test_relpath::
	@[ $(dwm_relpath $(dwm_thisdir )/../src,$(dwm_thisdir )) = ../tests ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )/../src) = ../src ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(TOP)) = .. ] || exit
	@[ $(dwm_relpath $(TOP),$(dwm_thisdir )) = tests ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(dwm_thisdir )) = . ] || exit
	@[ $(dwm_relpath $(dwm_thisdir ),$(TOP)/src) = ../src ] || exit
	@[ "/$(dwm_relpath /,$(dwm_curpath ))" = $(shell pwd) ] || exit
	@echo relpath tests passed

test_files::
	@[ "$(dwm_files $(dwm_thisdir ),Makefile)" = "Makefile" ] || exit
	@[ $(dwm_files $(dwm_thisdir )/../src,dwm_gmk_files\.cc) = dwm_gmk_files.cc ] || exit
	@[ -n "$(dwm_files $(dwm_thisdir )/../src,.+\.cc)" ] || exit
	@[ -z "$(dwm_files .,Make\.ile)" ] || exit
	@[ "$(dwm_files $(dwm_thisdir ),Make.ile)" = Makefile ] || exit
	@[ $(words $(dwm_files $(dwm_thisdir )/../src,.+\.cc)) -ge 7 ] || exit
	@echo files tests passed

test_sort::
	@[ "$(dwm_sort a b a b a b c a b c d)" = "a a a a b b b b c c d" ] || exit
	@[ "$(dwm_sort d c b a c b a b a b a)" = "a a a a b b b b c c d" ] || exit
	@echo sort tests passed

test_subdirs::
	@[ "$(dwm_subdirs )" = "" ] || exit
	@[ $(words $(dwm_subdirs $(dwm_thisdir )/..)) -ge 5 ] || exit
	@[ $(words $(dwm_subdirs $(dwm_thisdir )/..,tests)) -eq 1 ] || exit
	@[ "$(dwm_subdirs $(dwm_thisdir )/..,tests)" = tests ] || exit
	@[ "$(dwm_subdirs $(dwm_thisdir )/..,src)" = src ] || exit
	@echo subdirs tests passed

test_rgxmatch::
	@[ "$(dwm_rgxmatch ^d.+,dwm)" = "dwm" ] || exit
	@[ "$(dwm_rgxmatch ^d(.+),dwm)" = "dwm wm" ] || exit
	@[ "$(dwm_rgxmatch .wm$$,dwm)" = "dwm" ] || exit
	@echo rgxmatch tests passed

test_rgxsearch::
	@[ "$(dwm_rgxsearch d,dwm)" = "d" ] || exit
	@[ "$(dwm_rgxsearch ^d,dwm)" = "d" ] || exit
	@[ "$(dwm_rgxsearch w,dwm)" = "w" ] || exit
	@[ "$(dwm_rgxsearch m,dwm)" = "m" ] || exit
	@[ "$(dwm_rgxsearch m$$,dwm)" = "m" ] || exit
	@[ "$(dwm_rgxsearch t.+,dwm)" = "" ] || exit
	@[ "$(dwm_rgxsearch (d).+,dwm)" = "dwm d" ] || exit
	@echo rgxsearch tests passed

# $(info strawberry $(dwm_rgxsearch r,strawberry))

test_rgxreplace::
	@[ "$(dwm_rgxreplace a|e|i|o|u,[$$&],Quick brown fox)" = "Q[u][i]ck br[o]wn f[o]x" ] || exit
	@[ "$(dwm_rgxreplace \ brown, [$$`],Quick brown fox)" = "Quick [Quick] fox" ] || exit
	@[ "$(dwm_rgxreplace brown ,[$$'] ,Quick brown fox)" = "Quick [fox] fox" ] || exit
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
	@[ $(words $(bison_rule1)) -eq 23 ] || exit
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
	@[ "$(word 16,$(bison_rule1))" = "bison" ] || exit
	@[ "$(word 17,$(bison_rule1))" = "-d" ] || exit
	@[ "$(word 18,$(bison_rule1))" = "-t" ] || exit
	@[ "$(word 19,$(bison_rule1))" = "-g" ] || exit
	@[ "$(word 20,$(bison_rule1))" = "parser.graph" ] || exit
	@[ "$(word 21,$(bison_rule1))" = "-o" ] || exit
	@[ "$(word 22,$(bison_rule1))" = "myparser.cc" ] || exit
	@[ "$(word 23,$(bison_rule1))" = "$$<" ] || exit
	@echo bison1 tests passed

bison_rule2 = $(dwm_bison parser.y,-d)

test_bison2::
	@[ $(words $(bison_rule2)) -eq 18 ] || exit
	@[ "$(word 1,$(bison_rule2))" = "BISONTARGETS" ] || exit
	@[ "$(word 2,$(bison_rule2))" = "+=" ] || exit
	@[ "$(word 3,$(bison_rule2))" = "parser.cc" ] || exit
	@[ "$(word 4,$(bison_rule2))" = "parser.hh" ] || exit
	@[ "$(word 5,$(bison_rule2))" = "parser.cc" ] || exit
	@[ "$(word 6,$(bison_rule2))" = "parser.hh" ] || exit
	@[ "$(word 7,$(bison_rule2))" = "&:" ] || exit
	@[ "$(word 8,$(bison_rule2))" = "parser.y" ] || exit
	@[ "$(word 14,$(bison_rule2))" = "bison" ] || exit
	@[ "$(word 15,$(bison_rule2))" = "-d" ] || exit
	@[ "$(word 16,$(bison_rule2))" = "-o" ] || exit
	@[ "$(word 17,$(bison_rule2))" = "parser.cc" ] || exit
	@[ "$(word 18,$(bison_rule2))" = "$$<" ] || exit
	@echo bison2 tests passed

bison_rule3 = $(dwm_bison parser.y,-d,-o parser.c)

test_bison3::
	@[ $(words $(bison_rule3)) -eq 18 ] || exit
	@[ "$(word 1,$(bison_rule3))" = "BISONTARGETS" ] || exit
	@[ "$(word 2,$(bison_rule3))" = "+=" ] || exit
	@[ "$(word 3,$(bison_rule3))" = "parser.c" ] || exit
	@[ "$(word 4,$(bison_rule3))" = "parser.h" ] || exit
	@[ "$(word 5,$(bison_rule3))" = "parser.c" ] || exit
	@[ "$(word 6,$(bison_rule3))" = "parser.h" ] || exit
	@[ "$(word 7,$(bison_rule3))" = "&:" ] || exit
	@[ "$(word 8,$(bison_rule3))" = "parser.y" ] || exit
	@[ "$(word 14,$(bison_rule3))" = "bison" ] || exit
	@[ "$(word 15,$(bison_rule3))" = "-d" ] || exit
	@[ "$(word 16,$(bison_rule3))" = "-o" ] || exit
	@[ "$(word 17,$(bison_rule3))" = "parser.c" ] || exit
	@[ "$(word 18,$(bison_rule3))" = "$$<" ] || exit
	@echo bison3 tests passed

flex_rule1 = $(dwm_flex lexer.lex,-o lexer.cc)

test_flex1::
	@[ $(words $(flex_rule1)) -eq 14 ] || exit
	@[ "$(word 1,$(flex_rule1))" = "FLEXTARGETS" ] || exit
	@[ "$(word 2,$(flex_rule1))" = "+=" ] || exit
	@[ "$(word 3,$(flex_rule1))" = "lexer.cc" ] || exit
	@[ "$(word 4,$(flex_rule1))" = "lexer.cc:" ] || exit
	@[ "$(word 5,$(flex_rule1))" = "lexer.lex" ] || exit
	@[ "$(word 11,$(flex_rule1))" = "flex" ] || exit
	@[ "$(word 12,$(flex_rule1))" = "-o" ] || exit
	@[ "$(word 13,$(flex_rule1))" = "lexer.cc" ] || exit
	@[ "$(word 14,$(flex_rule1))" = "$$<" ] || exit
	@echo flex1 tests passed

flex_rule2 = $(dwm_flex lexer.lex,-o lexer.cc,-d,--tables-file=lexertables)

test_flex2::
	@[ $(words $(flex_rule2)) -eq 18 ] || exit
	@[ "$(word 1,$(flex_rule2))" = "FLEXTARGETS" ] || exit
	@[ "$(word 2,$(flex_rule2))" = "+=" ] || exit
	@[ "$(word 3,$(flex_rule2))" = "lexer.cc" ] || exit
	@[ "$(word 4,$(flex_rule2))" = "lexertables" ] || exit
	@[ "$(word 5,$(flex_rule2))" = "lexer.cc" ] || exit
	@[ "$(word 6,$(flex_rule2))" = "lexertables:" ] || exit
	@[ "$(word 7,$(flex_rule2))" = "lexer.lex" ] || exit
	@[ "$(word 13,$(flex_rule2))" = "flex" ] || exit
	@[ "$(word 14,$(flex_rule2))" = "-d" ] || exit
	@[ "$(word 15,$(flex_rule2))" = "-o" ] || exit
	@[ "$(word 16,$(flex_rule2))" = "lexer.cc" ] || exit
	@[ "$(word 17,$(flex_rule2))" = "--tables-file=lexertables" ] || exit
	@[ "$(word 18,$(flex_rule2))" = "$$<" ] || exit
	@echo flex2 tests passed

test_uniqleft::
	@[ "$(dwm_uniqleft a b d d b a)" = "a b d" ] || exit
	@echo uniqleft tests passed

test_uniqright::
	@[ "$(dwm_uniqright a b d d b a)" = "d b a" ] || exit
	@echo uniqright tests passed

# $(info Makefile thisdir $(dwm_thisdir ))

# $(info top $(dwm_top ))
# $(info thisdir $(dwm_thisdir ))
# $(info $(from_top ))
