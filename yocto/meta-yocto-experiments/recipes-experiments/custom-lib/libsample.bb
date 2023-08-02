#
# This file is the libsample recipe.
#
SUMMARY = "Simple libsample application"
SECTION = "libs"
LICENSE = "CLOSED"
SRC_URI = "file://libsample.c \
 file://libsample.h \
 file://Makefile "
S = "${WORKDIR}"
PACKAGE_ARCH = "${MACHINE_ARCH}"
PROVIDES = "sample"TARGET_CC_ARCH += "${LDFLAGS}"
do_install() {
install -d ${D}${libdir}
install -d ${D}${includedir}
oe_libinstall -so libsample ${D}${libdir}
install -d -m 0655 ${D}${includedir}/SAMPLE
install -m 0644 ${S}/*.h ${D}${includedir}/SAMPLE/
}
FILES_${PN} = "${libdir}/*.so.* ${includedir}/*"
FILES_${PN}-dev = "${libdir}/*.so"

