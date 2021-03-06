DESCRIPTION = "void11"
HOMEPAGE = "http://www.wlsec.net/void11"
SECTION = "console/network"
LICENSE = "GPL"
FILES_${PN} += "${libdir}/libvoid11.so"

SRC_URI = "http://www.wirelessdefence.org/Contents/Files/void11-0.2.0.tar.bz2;md5sum=1c5b3e3e70916de74c2932c7f3e46d9e \
           http://hostap.epitest.fi/releases/hostapd-0.1.3.tar.gz;md5sum=54563fb51f143c4bf26ddec2516e8f9f \
           file://oezc.patch;patch=1;pnum=1"

S = "${WORKDIR}/void11-0.2.0"

inherit autotools

do_compile () {
    oe_runmake USECONSOLE=1 HOSTAPD_PATH=${WORKDIR}/hostapd-0.1.3
}

do_install () {
    install -d ${D}/${sbindir}
    install -d ${D}/${libdir}
    install -m 0755 lib/libvoid11.so  ${D}/${libdir}
    install -m 0755 console/void11_hopper ${D}/${sbindir}
    install -m 0755 smallsleep/smallsleep ${D}/${sbindir}
    install -m 0755 console/void11_penetration ${D}/${sbindir}
}
