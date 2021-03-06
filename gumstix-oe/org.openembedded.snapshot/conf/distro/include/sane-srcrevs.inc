# Generated with 
# bitbake -s | grep svnr  | awk '{print "SRCREV_pn-" $1 "=" $2}' | \
# sed -e s:\+:\=:g -e s:svnr::g| awk -F "=" '{print $1 " ?=\" " $3}' | \
# awk -F "-r" '{print $1"\""}'

# This will miss recipes that have skippackage set (e.g. uclibc)

# this is alphabetical!

SRCREV_pn-aircrack-ng ?= "802"
SRCREV_pn-bfin-uclibc ?= "1857"
SRCREV_pn-dfu-util ?= "2866"
SRCREV_pn-dfu-util-native ?= "2866"
SRCREV_pn-eglibc ?= "3531"
SRCREV_pn-eglibc-initial ?= "3531"
SRCREV_pn-eglibc-intermediate ?= "3531"
SRCREV_pn-ezxd ?= "2058"
SRCREV_pn-elf2flt="1786"
SRCREV_pn-fbgrab-viewer-native ?= "1943"
SRCREV_pn-fstests ?= "204"
SRCREV_pn-gconf-dbus ?= "606"
SRCREV_pn-gnuradio ?= "6377"
SRCREV_pn-gypsy ?= "56"
SRCREV_pn-hildon-1 ?= "14173"
SRCREV_pn-kismet ?= "2285"
SRCREV_pn-kismet-newcore ?= "2285"
SRCREV_pn-libfakekey ?= "1455"
SRCREV_pn-libgsmd ?= "3074"
SRCREV_pn-libjana ?= "662"
SRCREV_pn-libmokogsmd2 ?= "2950"
SRCREV_pn-libmokojournal2 ?= "3217"
SRCREV_pn-libmokopanelui2 ?= "3226"
SRCREV_pn-libmokoui2 ?= "3229"
SRCREV_pn-libowl ?= "277"
SRCREV_pn-libxosd ?= "627"
SRCREV_pn-linux-bfin ?= "3745"
SRCREV_pn-linux-hackndev-2.6 ?= "1308"
SRCREV_pn-llvm-gcc4 ?= "374"
SRCREV_pn-llvm-gcc4-cross ?= "374"
SRCREV_pn-maemo-mapper ?= "108"
SRCREV_pn-matchbox-desktop-2 ?= "1649"
SRCREV_pn-matchbox-keyboard ?= "1739"
SRCREV_pn-matchbox-keyboard-inputmethod ?= "1739"
SRCREV_pn-matchbox-panel-2 ?= "1626"
SRCREV_pn-moko-gtk-engine ?= "3207"
SRCREV_pn-mpd-alsa ?= "6952"
SRCREV_pn-neod ?= "2956"
SRCREV_pn-oh-puzzles ?= "22"
SRCREV_pn-osb-browser ?= "125"
SRCREV_pn-osb-jscore ?= "117"
SRCREV_pn-osb-nrcit ?= "125"
SRCREV_pn-osb-nrcore ?= "126"
SRCREV_pn-openmoko-appearance ?= "3239"
SRCREV_pn-openmoko-appmanager ?= "1851"
SRCREV_pn-openmoko-appmanager2 ?= "3271"
SRCREV_pn-openmoko-browser2 ?= "3249"
SRCREV_pn-openmoko-calculator ?= "2404"
SRCREV_pn-openmoko-calculator2 ?= "3235"
SRCREV_pn-openmoko-common ?= "397"
SRCREV_pn-openmoko-common2 ?= "2679"
SRCREV_pn-openmoko-contacts ?= "2298"
SRCREV_pn-openmoko-contacts2 ?= "358"
SRCREV_pn-openmoko-dates ?= "467"
SRCREV_pn-openmoko-dates2 ?= "658"
SRCREV_pn-openmoko-dialer ?= "2811"
SRCREV_pn-openmoko-dialer2 ?= "3282"
SRCREV_pn-openmoko-feedreader2 ?= "3080"
SRCREV_pn-openmoko-finger-demo ?= "1671"
SRCREV_pn-openmoko-firststart2 ?= "3158"
SRCREV_pn-openmoko-footer ?= "2354"
SRCREV_pn-openmoko-icon-theme-standard ?= "2232"
SRCREV_pn-openmoko-icon-theme-standard2 ?= "3225"
SRCREV_pn-openmoko-icon-theme-standard2-qvga ?= "3225"
SRCREV_pn-openmoko-keyboard ?= "1631"
SRCREV_pn-openmoko-libs ?= "2367"
SRCREV_pn-openmoko-mediaplayer2 ?= "3274"
SRCREV_pn-openmoko-messages ?= "2276"
SRCREV_pn-openmoko-panel-battery ?= "3272"
SRCREV_pn-openmoko-panel-bt ?= "2896"
SRCREV_pn-openmoko-panel-clock ?= "2567"
SRCREV_pn-openmoko-panel-demo ?= "1622"
SRCREV_pn-openmoko-panel-demo-simple ?= "1328"
SRCREV_pn-openmoko-panel-gps ?= "2900"
SRCREV_pn-openmoko-panel-gsm ?= "3185"
SRCREV_pn-openmoko-panel-mainmenu ?= "2567"
SRCREV_pn-openmoko-panel-usb ?= "2893"
SRCREV_pn-openmoko-session ?= "152"
SRCREV_pn-openmoko-simplemediaplayer ?= "1688"
SRCREV_pn-openmoko-sound-theme-standard2 ?= "3192"
SRCREV_pn-openmoko-stylus-demo ?= "2324"
SRCREV_pn-openmoko-stylus-demo-simple ?= "1818"
SRCREV_pn-openmoko-taskmanager ?= "1663"
SRCREV_pn-openmoko-tasks ?= "320"
SRCREV_pn-openmoko-tasks2 ?= "346"
SRCREV_pn-openmoko-terminal2 ?= "2972"
SRCREV_pn-openmoko-theme-standard ?= "2370"
SRCREV_pn-openmoko-theme-standard-qvga ?= "2370"
SRCREV_pn-openmoko-theme-standard2 ?= "3210"
SRCREV_pn-openmoko-theme-standard2-qvga ?= "3210"
SRCREV_pn-openmoko-today ?= "3056"
SRCREV_pn-openmoko-today2 ?= "3287"
SRCREV_pn-openmoko-today2-folders ?= "2680"
SRCREV_pn-openmoko-worldclock2 ?= "3241"
SRCREV_pn-openocd ?= "206"
SRCREV_pn-openocd-native ?= "206"
SRCREV_pn-oprofileui ?= "160"
SRCREV_pn-psplash ?= "249"
SRCREV_pn-settings-daemon ?= "1755"
SRCREV_pn-sjf2410-linux-native ?= "933"
SRCREV_pn-sphyrna ?= "45"
SRCREV_pn-webkit-gtk ?= "26915"
SRCREV_pn-webkit-qt ?= "26079"
SRCREV_pn-webkit-qtopia ?= "26079"
SRCREV_pn-xoo ?= "1623"
SRCREV_pn-mplayer ?= "24587"
SRCREV_pn-networkmanager ?= "2887"
SRCREV_pn-networkmanager-applet ?= "200"
SRCREV_pn-libw100 ?= "47"
SRCREV_pn-usbpath ?= "3108"
SRCREV_pn-usbpath-native ?= "3108"

