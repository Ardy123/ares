DESCRIPTION = "Navit is a car navigation system with routing engine."
LICENSE = "GPL"
SECTION = "x11/applications"
DEPENDS = "glib-2.0 gtk+"
#RRECOMMENDS = "gpsd speechd flite"
RRECOMMENDS = "gpsd"

inherit autotools

EXTRA_OECONF = "--disable-binding-python --disable-gui-sdl --disable-samplemap --enable-avoid-float --enable-avoid-unaligned"

PACKAGES = "${PN}-dbg ${PN}-dev ${PN} ${PN}-doc ${PN}-locale"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug"
FILES_${PN}-dev += "${libdir}/${PN}/*/*.so ${libdir}/${PN}/*/*.la"

SRC_URI_append = " \
                  file://navit.xml \
                  file://navit.desktop \
                  file://navit.launcher \
	  	 "

do_install_append() {
        install -d ${D}${datadir}/navit/
        install -m 0644 ${WORKDIR}/navit.xml ${D}${datadir}/navit/

        install -d ${D}${datadir}/applications/
        install -m 0644 ${WORKDIR}/navit.desktop ${D}${datadir}/applications/

        mv ${D}${bindir}/navit ${D}${bindir}/navit.real
        install -m 0755 ${WORKDIR}/navit.launcher ${D}${bindir}/navit
}
