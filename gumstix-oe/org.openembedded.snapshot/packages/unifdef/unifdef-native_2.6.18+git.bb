DESCRIPTION = "Kernel header preprocessor"
SECTION = "devel"
LICENSE = "GPL"

SRC_URI =	"http://ares.gizmoforyou-projects.com/code/OE/packages/org.openembedded.snapshot/packages/unifdef/unifdef-native_2.6.18.patch;pnum=0;patch=1 \
			 file://unifdef.c"

inherit native

do_stage() {
	install -m 0755 unifdef ${STAGING_BINDIR}
}

do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} -o unifdef ${WORKDIR}/unifdef.c
}

do_install() {
	:
}

