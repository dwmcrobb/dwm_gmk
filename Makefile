include Makefile.vars

all:: lib/dwm_gmk.la apps

apps::
	${MAKE} -C apps

lib/dwm_gmk.la::
	${MAKE} -C src
	${MAKE} -C tests

tarprep:: lib/dwm_gmk.la
	${MAKE} -C src $@
	${MAKE} -C apps $@
	${MAKE} -C packaging $@

package: ${OSNAME}-pkg

freebsd-pkg: tarprep
	mkfbsdmnfst -r packaging/fbsd_manifest -s staging > staging/+MANIFEST
	pkg create -o . -r staging -m staging

darwin-pkg: tarprep
	pkgbuild --root staging --identifier net.mcplex.dwmgmk --version ${VERSION} dwmgmk-${VERSION}.pkg

linux-pkg: tarprep
	if [ ! -d staging/DEBIAN ]; then mkdir staging/DEBIAN; fi
	mkdebcontrol -r packaging/debcontrol -s staging/usr/local > staging/DEBIAN/control
	dpkg-deb -b --root-owner-group staging
	dpkg-name -o staging.deb

clean::
	${MAKE} -C src $@
	${MAKE} -C apps $@

distclean:: clean
	${MAKE} -C src $@
	${MAKE} -C apps $@
	${MAKE} -C packaging $@
	rm -Rf autom4te.cache staging
	rm -f config.log config.status Makefile.vars
	rm -f dwm_*.deb

