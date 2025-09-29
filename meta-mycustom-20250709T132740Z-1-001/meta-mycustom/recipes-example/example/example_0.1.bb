DESCRIPTION = "Custom file installer"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://rootfs"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${sysconfdir}
    install -m 0644 ${WORKDIR}/rootfs ${D}${sysconfdir}/rootfs
}

FILES:${PN} += "${sysconfdir}/rootfs"

