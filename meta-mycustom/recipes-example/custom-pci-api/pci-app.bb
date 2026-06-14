DESCRIPTION = "Example Calculator  application for Yocto build."
SECTION = "examples"
DEPENDS = ""
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
FILESEXTRAPATHS:prepend := "${THISDIR}/src:"

SRC_URI = "file://pci-app.c \
         file://edu.h"

S = "${UNPACKDIR}"

do_compile() {
${CC} ${CFLAGS} ${LDFLAGS} ${S}/pci-app.c -o pci-app
}

do_install() {
# create the /usr/bin folder in the rootfs with default permissions
install -d ${D}${bindir}

# install the application into the /usr/bin folder with default permissions
install ${S}/pci-app ${D}${bindir}

install -d ${D}${includedir}
install -m 0644 edu.h ${D}${includedir}

}
