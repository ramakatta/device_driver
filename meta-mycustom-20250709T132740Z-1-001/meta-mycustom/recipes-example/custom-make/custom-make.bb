DESCRIPTION = "Example Hello world application with Makefile and Yocto build."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
FILESEXTRAPATHS:prepend := "${THISDIR}/:"

SRC_URI = "file://custom-make.c \
	file://Makefile"

S = "${WORKDIR}"

CFLAGS:append = "-Wall -O -g"
TARGET_CC_ARCH += "${LDFLAGS}"
EXTRA_OEMAKE = "CC='${CC}' CFLAGS='${CFLAGS}' LDFLAGS='${LDFLAGS}'"


do_compile() {
	oe_runmake WORKDIR=${WORKDIR}
}

do_install() {
        oe_runmake install DESTDIR=${D}
}
