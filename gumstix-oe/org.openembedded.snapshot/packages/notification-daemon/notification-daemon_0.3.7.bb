DESCRIPTION = "A dbus service that listens to desktop notification requests and displays them"
HOMEPAGE = "http://www.galago-project.org/"
SECTION = "x11"
LICENSE = "GPL"
DEPENDS = "gettext dbus gtk+ libsexy gconf libwnck"

SRC_URI = "http://www.galago-project.org/files/releases/source/${PN}/${P}.tar.gz"

EXTRA_OECONF = "--disable-binreloc"

inherit autotools pkgconfig

PACKAGES = "${PN}"
FILES_${PN} = "\
  ${libexecdir}/notification-daemon \
  ${datadir}/dbus-1/services/ \
  ${libdir}/notification-daemon-1.0/engines/libstandard.so \
  ${sysconfdir}/gconf/schemas/notification-daemon.schemas \
"
