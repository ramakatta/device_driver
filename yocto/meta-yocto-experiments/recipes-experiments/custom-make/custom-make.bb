DESCRIPTION = "Example Hello world application with Makefile and Yocto build."
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/:"

SRC_URI = "file://custom-make.c \
	file://Makefile"

S = "${WORKDIR}"

CFLAGS:append = "-Wall -O -g"
EXTRA_OEMAKE = "'CC=${CC}' 'CFLAGS=${CFLAGS}'"
#EXTRA_OEMAKE:append  = "'LDFLAGS=${LDFLAGS}'"
EXTRA_OEMAKE:append  = "'DESTDIR=${D}'"

do_compile() {
	oe_runmake WORKDIR=${WORKDIR}
}

do_install() {
# create the /usr/bin folder in the rootfs with default permissions
install -d ${D}${bindir}

# install the application into the /usr/bin folder with default permissions
install  -d  ${D}${bindir}
install  -m 0755 {$WORKDIR}/hello_m  ${D}${bindir}

}
