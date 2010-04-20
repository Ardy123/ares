DESCRIPTION = "Tea - a GTK based text editor tith highlighting and a lot of processing features"
SECTION = "gpe"
LICENSE = "GPL"
DEPENDS = "gtk+ gtksourceview"

inherit autotools

SRC_URI = "${SOURCEFORGE_MIRROR}/tea-editor/${P}.tar.bz2 \
           file://move-endif.patch;patch=1;pnum=0"

EXTRA_OECONF = "--enable-legacy"
