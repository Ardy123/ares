DESCRIPTION = "Linux Kernel"
SECTION = "kernel"
LICENSE = "GPL"

inherit kernel

# Not every device needs mkimage to generate a kernel image, but lets make OE a bit more
# friendly and increase the "Just Works(TM) factor. Building uboot takes only a minute.
DEPENDS += " u-boot-mkimage-openmoko-native "


RPSRC = "http://www.rpsys.net/openzaurus/patches/archive"

# Specify the commandline for your device

#boot from mmc
CMDLINE_at91sam9263ek = "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p1 rootfstype=ext2 rootdelay=5"
#boot from nfs
#CMDLINE_at91sam9263ek = "mem=64M console=ttyS0,115200 root=301 root=/dev/nfs nfsroot=172.20.3.1:/data/at91 ip=172.20.0.5:::255.255.0.0"

do_configure_prepend() {
        echo "" > ${S}/.config

        #
        # logo support, if you supply logo_linux_clut224.ppm in SRC_URI, then it's going to be used
        #
        if [ -e ${WORKDIR}/logo_linux_clut224.ppm ]; then
                install -m 0644 ${WORKDIR}/logo_linux_clut224.ppm drivers/video/logo/logo_linux_clut224.ppm
                echo "CONFIG_LOGO=y"                    >> ${S}/.config
                echo "CONFIG_LOGO_LINUX_CLUT224=y"      >> ${S}/.config
        fi

        #
        # oabi / eabi support
        #
        if [ "${TARGET_OS}" = "linux-gnueabi" -o  "${TARGET_OS}" = "linux-uclibcgnueabi" ]; then
                echo "CONFIG_AEABI=y"                   >> ${S}/.config
                echo "CONFIG_OABI_COMPAT=y"             >> ${S}/.config
        else
                echo "# CONFIG_AEABI is not set"        >> ${S}/.config
                echo "# CONFIG_OABI_COMPAT is not set"  >> ${S}/.config
        fi

        echo "CONFIG_CMDLINE=\"${CMDLINE}\"" >> ${S}/.config

        sed -e '/CONFIG_AEABI/d' \
            -e '/CONFIG_OABI_COMPAT=/d' \
            -e '/CONFIG_CMDLINE=/d' \
            -e '/CONFIG_LOGO=/d' \
            -e '/CONFIG_LOGO_LINUX_CLUT224=/d' \
            < '${WORKDIR}/defconfig' >>'${S}/.config'

        #
        # root-over-nfs-over-usb-eth support. Limited, but should cover some cases.
        # Enable this by setting a proper CMDLINE_NFSROOT_USB.
        #
        if [ ! -z "${CMDLINE_NFSROOT_USB}" ]; then
                oenote "Configuring the kernel for root-over-nfs-over-usb-eth with CMDLINE ${CMDLINE_NFSROOT_USB}"
                sed -e '/CONFIG_INET/d' \
                    -e '/CONFIG_IP_PNP=/d' \
                    -e '/CONFIG_USB_GADGET=/d' \
                    -e '/CONFIG_USB_GADGET_SELECTED=/d' \
                    -e '/CONFIG_USB_ETH=/d' \
                    -e '/CONFIG_NFS_FS=/d' \
                    -e '/CONFIG_ROOT_NFS=/d' \
                    -e '/CONFIG_CMDLINE=/d' \
                    -i ${S}/.config
                echo "CONFIG_INET=y"                     >> ${S}/.config
				echo "CONFIG_IP_PNP=y"                   >> ${S}/.config
                echo "CONFIG_USB_GADGET=y"               >> ${S}/.config
                echo "CONFIG_USB_GADGET_SELECTED=y"      >> ${S}/.config
                echo "CONFIG_USB_ETH=y"                  >> ${S}/.config
                echo "CONFIG_NFS_FS=y"                   >> ${S}/.config
                echo "CONFIG_ROOT_NFS=y"                 >> ${S}/.config
                echo "CONFIG_CMDLINE=\"${CMDLINE_NFSROOT_USB}\"" >> ${S}/.config
        fi
        yes '' | oe_runmake oldconfig
}

# Support checking the kernel size since some kernels need to reside in partitions
# with a fixed length or there is a limit in transferring the kernel to memory
do_sizecheck() {
        if [ ! -z "${KERNEL_IMAGE_MAXSIZE}" ]; then
            size=`ls -l arch/${ARCH}/boot/${KERNEL_IMAGETYPE} | awk '{ print $5}'`
            if [ $size -ge ${KERNEL_IMAGE_MAXSIZE} ]; then
                    rm arch/${ARCH}/boot/${KERNEL_IMAGETYPE}
                    die  "This kernel (size=$size) is too big for your device. Please reduce the size of the kernel by making more of it modular."
            fi
        fi
}

do_install_prepend() {
        if test -e arch/${ARCH}/boot/Image ; then
             ln -f arch/${ARCH}/boot/Image arch/${ARCH}/boot/uImage
        fi

        if test -e arch/${ARCH}/boot/images/uImage ; then
             ln -f arch/${ARCH}/boot/images/uImage arch/${ARCH}/boot/uImage
        fi

        if test -e arch/${ARCH}/kernel/vmlinux.lds ; then
             ln -f arch/${ARCH}/kernel/vmlinux.lds arch/${ARCH}/boot/vmlinux
        fi
}

UBOOT_ENTRYPOINT ?= "20008000"

KERNEL_IMAGE_BASE_NAME = "${KERNEL_IMAGETYPE}-${PV}-${PR}-${MACHINE}-${DATETIME}"
KERNEL_IMAGE_SYMLINK_NAME = "${KERNEL_IMAGETYPE}-${MACHINE}"

do_deploy() {
        install -d ${DEPLOY_DIR_IMAGE}
        install -m 0644 arch/${ARCH}/boot/${KERNEL_IMAGETYPE} ${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGE_BASE_NAME}.bin
        tar -cvzf ${DEPLOY_DIR_IMAGE}/modules-${KERNEL_RELEASE}-${PR}-${MACHINE}.tgz -C ${D} lib
        
        if test "x${KERNEL_IMAGETYPE}" = "xuImage" ; then 
            if test -e arch/${ARCH}/boot/compressed/vmlinux ; then
                ${OBJCOPY} -O binary -R .note -R .comment -S arch/${ARCH}/boot/compressed/vmlinux linux.bin
                uboot-mkimage -A ${ARCH} -O linux -T kernel -C none -a ${UBOOT_ENTRYPOINT} -e ${UBOOT_ENTRYPOINT} -n "${DISTRO_NAME}/${PV}/${MACHINE}" -d linux.bin ${DEPLOY_DIR_IMAGE}/uImage-${PV}-${PR}-${MACHINE}-${DATETIME}.bin
                rm -f linux.bin
            else
                ${OBJCOPY} -O binary -R .note -R .comment -S vmlinux linux.bin
                rm -f linux.bin.gz
                gzip -9 linux.bin
                uboot-mkimage -A ${ARCH} -O linux -T kernel -C gzip -a ${UBOOT_ENTRYPOINT} -e ${UBOOT_ENTRYPOINT} -n "${DISTRO_NAME}/${PV}/${MACHINE}" -d linux.bin.gz ${DEPLOY_DIR_IMAGE}/uImage-${PV}-${PR}-${MACHINE}-${DATETIME}.bin
                rm -f linux.bin.gz
            fi
        fi

		cd ${DEPLOY_DIR_IMAGE}
		rm -f ${KERNEL_IMAGE_SYMLINK_NAME}.bin
		ln -sf ${KERNEL_IMAGE_BASE_NAME}.bin ${KERNEL_IMAGE_SYMLINK_NAME}.bin
}

do_deploy[dirs] = "${S}"

addtask sizecheck before do_install after do_compile
addtask deploy before do_package after do_install

