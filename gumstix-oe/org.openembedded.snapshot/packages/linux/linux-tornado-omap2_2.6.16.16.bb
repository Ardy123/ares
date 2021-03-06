DESCRIPTION = "Linux kernel for HTC Tornado/Typhoon/Hurricane phones."
SECTION = "kernel"
LICENSE = "GPL"

SRC_URI = "${KERNELORG_MIRROR}/pub/linux/kernel/v2.6/linux-2.6.16.tar.bz2 \
	   http://www.muru.com/linux/omap/patches/old/patch-2.6.16-omap2.bz2;patch=1 \
           file://linux-2.6.16.16.patch;patch=1 \
           file://tornado-20070320.patch;patch=1 \
           file://defconfig"

S = "${WORKDIR}/linux-2.6.16"

inherit kernel

COMPATIBLE_MACHINE = "htctornado"

do_configure() {

        rm -f ${S}/.config

        if [ ! -e ${WORKDIR}/defconfig ]; then
                die "No default configuration for ${MACHINE} available."
        fi


        if [ "${TARGET_OS}" == "linux-gnueabi" -o  "${TARGET_OS}" == "linux-uclibcgnueabi" ]; then
                echo "CONFIG_AEABI=y"                   >> ${S}/.config
                echo "CONFIG_OABI_COMPAT=y"             >> ${S}/.config
        else
                echo "# CONFIG_AEABI is not set"        >> ${S}/.config
                echo "# CONFIG_OABI_COMPAT is not set"  >> ${S}/.config
        fi

        sed     -e '/CONFIG_AEABI/d' \
                -e '/CONFIG_OABI_COMPAT=/d' \
                '${WORKDIR}/defconfig' >>'${S}/.config'

        yes '' | oe_runmake oldconfig

}

do_deploy() {
	install -d ${DEPLOY_DIR_IMAGE}
	install -m 0644 arch/${ARCH}/boot/${KERNEL_IMAGETYPE} ${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE}-${PV}-${MACHINE}-${DATETIME}
}   

do_deploy[dirs] = "${S}"

addtask deploy before do_populate_staging after do_compile
