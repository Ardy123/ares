#@TYPE: Distribution
#@NAME: SlugOS
#@DESCRIPTION: SlugOS Linux Distribution for the NSLU2

# WARNING: this file should not be used directly, use one of
# the supported slugos-derived distributions instead.

#----------------------------------------------------------------------------------
# STANDARD SLUGOS DEFINITIONS
#----------------------------------------------------------------------------------
# The following must be set in the top level distro file:
#
#DISTRO_NAME
#DISTRO_TYPE
#ARM_INSTRUCTION_SET "arm" or "thumb"
#TARGET_OS "linux" or "linux-uclibc"

# The following may be overridden to make sub-versions
SLUGOS_VERSION = "4.6"
DISTRO_REVISION ?= ""
DISTRO_VERSION ?= "${SLUGOS_VERSION}${DISTRO_REVISION}-${DISTRO_TYPE}"
# For release (only):
# DISTRO_FEED ?= "${SLUGOS_VERSION}-${DISTRO_TYPE}"
DISTRO_FEED ?= "unstable"

IMAGE_BASENAME = "${@['slugos${SITEINFO_ENDIANESS}', 'ucslugc'][bb.data.getVar('TARGET_OS', d, 1) == 'linux-uclibc']}"

# The following need not be set, the defaults should be adequate
#USE_NLS = "no" or "yes"
USE_NLS ?= "no"

# To make errors easier to identify:
DISTRO_NAME ?= "INVALID-${SITEINFO_ENDIANESS}-${ARM_INSTRUCTION_SET}-${TARGET_OS}"
DISTRO_TYPE ?= "INVALID"

# The following must not be changed.
TARGET_FPU = "soft"

# glib-2.0 builds require USE_NLS to be overridden
USE_NLS_glib-2.0 = "yes"

INHERIT += "package_ipk debian multimachine"

# FULL_OPTIMIZATION
#    Optimization settings.  Os works fine and is significantly better than O2.
FULL_OPTIMIZATION = "-fexpensive-optimizations -fomit-frame-pointer -frename-registers -Os"

#----------------------------------------------------------------------------------
# FEEDS
#  The FEED_URIS lines define where on the internet SlugOS looks for packages
#  when downloading new packages or updating existing packages.  Additional feeds
#  (such as a local feed) can be defined in local.conf
#----------------------------------------------------------------------------------
#
FEED_URIS_append += "cross##http://ipkg.nslu2-linux.org/feeds/${IMAGE_BASENAME}/cross/${DISTRO_FEED}"
FEED_URIS_append += "native##http://ipkg.nslu2-linux.org/feeds/${IMAGE_BASENAME}/native/${DISTRO_FEED}"

#----------------------------------------------------------------------------------
# FIRMWARE CONFIGURATION
#----------------------------------------------------------------------------------
# IMAGE BUILD OPTIONS
# -------------------
# CMDLINE* macros define the kernel command line.  CMDLINE_DEBUG is provided
# to enable/disable debugging in the distro.  Here noirqdebug is used to
# remove the messages about unhandled interrupts - people debugging interrupt
# issues in the kernel need to cancel this (set CMDLINE_DEBUG empty in local.conf)
CMDLINE_DEBUG = "noirqdebug"

# EXTRA PACKAGES
# --------------
# SlugOS builds an image with no extra packages - to add packages to the
# firmware include this file in a new 'distro' configuration file) and set
# the definition below to include the requirements.
# NOTE: as built this system will *not* be able to boot off anything other than
# the flash file system ('turnup' will not work).  You need to add the filesystem
# modules for your chosen root file system (and any others which will be used).
# See openslug.conf for a more full-featured system!
#
# Everything in this list gets added to the flash image, along with any RDEPENDS
# it has itself!
DISTRO_EXTRA_DEPENDS ?= ""
DISTRO_EXTRA_RDEPENDS ?= ""
DISTRO_EXTRA_RRECOMMENDS ?= ""

#----------------------------------------------------------------------------------
# PACKAGE VERSION CONTROL
#----------------------------------------------------------------------------------
# Define how to bootstrap the system - we need cross compilers.  It is also
# necessary to define which gets generated first, glibc or the kernel, and
# this is done by selecting the provider of libc (in this case it needs the
# kernel, so there has to be a non-libc gcc to build the kernel!)
PREFERRED_PROVIDERS += "virtual/${TARGET_PREFIX}gcc-initial:gcc-cross-initial"
PREFERRED_PROVIDERS += "virtual/${TARGET_PREFIX}gcc:gcc-cross"
PREFERRED_PROVIDERS += "virtual/${TARGET_PREFIX}g++:gcc-cross"
PREFERRED_PROVIDERS += "virtual/${TARGET_PREFIX}libc-for-gcc:glibc"
# Select 2.6 versions of the depmod support
PREFERRED_PROVIDERS += "virtual/${TARGET_PREFIX}depmod:module-init-tools-cross"
PREFERRED_PROVIDERS += "virtual/${TARGET_PREFIX}libc-for-gcc:glibc"

# compiler/binary/library versions
PREFERRED_VERSION_binutils ?= "2.16"
PREFERRED_VERSION_binutils-cross ?= "2.16"
PREFERRED_VERSION_gcc-cross-initial ?= "4.1.1"
PREFERRED_VERSION_gcc-cross ?= "4.1.1"
PREFERRED_VERSION_gcc ?= "4.1.1"
PREFERRED_VERSION_glibc ?= "2.3.5+cvs20050627"
#For SVN uclibc:
#SRCDATE_uclibc ?= "20060120"
#PREFERRED_VERSION_uclibc ?= "0.9.28+svn${SRCDATE_uclibc}"

# Select the correct versions of the kernel and modules (these are the
# defaults, override in the conf/distro top-level distro file).
PREFERRED_PROVIDER_virtual/kernel ?= "ixp4xx-kernel"
PREFERRED_VERSION_ixp4xx-kernel ?= "2.6.21.6"

# Select the smallest provider of x11 libraries
PREFERRED_PROVIDER_virtual/libx11 ?= "diet-x11"
SRCDATE_diet-x11 ?= "20060106"

# Ensure consistency across all SlugOS builds for the provider of a
# relational database - use the latest version of the SleepyCat
# Berkeley database
PREFERRED_PROVIDER_virtual/db = "db"
PREFERRED_PROVIDER_virtual/db-native = "db-native"

SRCDATE_ipkg-utils ?= "20060106"
SRCDATE_ipkg-utils-native ?= "20060106"
SRCDATE_ipkg-link ?= "20060106"
SRCDATE_irssi ?= "20050930"

CVS_TARBALL_STASH = "http://sources.nslu2-linux.org/sources/"
INHERIT += "nslu2-mirrors"

PREFERRED_VERSION_nslu2-linksys-firmware ?= "2.3r63"

PREFERRED_VERSION_ipkg ?= "0.99.163"
PREFERRED_VERSION_ipkg-native ?= "0.99.163"

#FIXME: HACK: REMOVE THIS
IGNORE_STRIP_ERRORS = ""

# Due to upstream instability, and another OE project with conflicting
# needs, nail down a specific, known-working version of madwifi-ng.
# Remove this once the madwifi-ng stuff seems to stabilize once again.
#PREFERRED_VERSION_madwifi-ng ?= "r2156-20070225"

PREFERRED_VERSION_linux-libc-headers = "2.6.18"

# we don't ship gtk-directfb by default
PREFERRED_PROVIDER_gtk+                   ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-ani  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-bmpg ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-gif  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-ico  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-jpeg ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-pcx  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-png  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-pnm  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-ras  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-tga  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-wbmp ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-xbm  ?= "gtk+"
PREFERRED_PROVIDER_gdk-pixbuf-loader-xpm  ?= "gtk+"

require conf/distro/include/sane-srcdates.inc
require conf/distro/include/sane-srcrevs.inc
