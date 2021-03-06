require scummvm.inc
DEPENDS = "virtual/libsdl libmad libvorbis libogg zlib mpeg2dec"

SRC_URI += "file://makefile-nostrip.patch;patch=1"
SRC_URI_append_openmoko = " file://openmoko-scummvm \
                           file://scummvm.desktop"

SRC_URI_OVERRIDES_PACKAGE_ARCH = "1"

EXTRA_OECONF += "--enable-lure \
		 --enable-agi \
		 --enable-cine \
		 "

do_compile() {
	oe_runmake CC="${CC}" CXX="${CXX}" CFLAGS="${CFLAGS}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS} -lmpeg2" \
	           DEFINES="-DUNIX -DSCUMM_NEED_ALIGNMENT -DUSE_MAD -DUSE_VORBIS -DUSE_ZLIB -DUSE_MPEG2"
}


do_install_append() {
	if [ -f ${WORKDIR}/openmoko-scummvm ]; then
		install -d ${D}${bindir}
		install -m 0755 ${WORKDIR}/openmoko-scummvm ${D}${bindir}/openmoko-scummvm
	fi
	if  [ -f ${WORKDIR}/scummvm.desktop ]; then
		install -d ${D}${datadir}/applications
		install -m 0644 ${WORKDIR}/scummvm.desktop ${D}${datadir}/applications
	fi
	install -d ${D}${datadir}/scummvm
	install -m 0644 gui/themes/modern.ini ${D}${datadir}/scummvm/ 
	install -m 0644 gui/themes/modern.zip ${D}${datadir}/scummvm/
}
