load ../src/.libs/libdwm_gmk.so(dwm_gmk_setup)

tests:: test_relpath test_dirfiles

test_relpath::
	@if [ $(dwm_relpath ../src,.) = ../tests \
              -a $(dwm_relpath .,../src) = ../src \
	      -a $(dwm_relpath .,..) = .. \
	      -a $(dwm_relpath ..,.) = tests \
	      -a $(dwm_relpath .,.) = . ]; then \
	  echo relpath tests passed ; \
	fi

test_dirfiles::
	@if [ $(dwm_dirfiles .,Makefile) = Makefile \
	      -a $(dwm_dirfiles ../src,dwm_gmk_dirfiles\.cc) = dwm_gmk_dirfiles.cc \
	      -a -n "$(dwm_dirfiles ../src,.+\.cc)" \
	      -a -z "$(dwm_dirfiles .,Make\.ile)" \
	      -a "$(dwm_dirfiles .,Make.ile)" = Makefile \
	      -a $(words $(dwm_dirfiles ../src,.+\.cc)) -ge 4 ]; then \
	  echo dirfiles tests passed ; \
	fi

$(info $(call dwm_thisdir))
$(info $(dwm_relpath .,..))
$(info $(dwm_relpath .,../src))
$(info $(dwm_relpath ../src,.))

