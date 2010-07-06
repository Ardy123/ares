# basic gumstix image

require gumstix-minimal-image.bb

IMAGE_INSTALL += " \
	directfb \
    cron \
    ntp \
    ntpdate \
    boa \
    motd \
    www-content \
    mtd-utils \
    "


