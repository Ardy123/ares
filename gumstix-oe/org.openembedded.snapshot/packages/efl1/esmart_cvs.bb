DESCRIPTION = "ESmart is a collection of smart Evas objects"
LICENSE = "MIT"
DEPENDS = "evas ecore edje imlib2 epsilon libtool"
PV = "0.9.0+cvs${SRCDATE}"

inherit efl_library

EXTRA_OECONF = "--with-edje-cc=${STAGING_BINDIR_NATIVE}/edje_cc"

PACKAGES =+ "${PN}-textentry \
             ${PN}-thumb \
             ${PN}-container \
             ${PN}-container-plugins \
             ${PN}-file-dialog \
             ${PN}-draggies \
             ${PN}-trans-x11"

FILES_${PN}-dbg += "${libdir}/.debug/ ${libdir}/esmart/*/.debug/"
FILES_${PN}-textentry = "${libdir}/libesmart_text_entry*.so*"
FILES_${PN}-thumb = "${libdir}/libesmart_thumb*.so*"
FILES_${PN}-container = "${libdir}/libesmart_container*"
DEPENDS_${PN}-container += "${PN}-container-plugins"
FILES_${PN}-container-plugins = "${libdir}/esmart/layout/*.so"
FILES_${PN}-file-dialog = "${libdir}/libesmart_file_dialog*.so*"
FILES_${PN}-draggies = "${libdir}/libesmart_draggies*.so*"
FILES_${PN}-trans-x11 = "${libdir}/libesmart_trans_x11*.so*"
