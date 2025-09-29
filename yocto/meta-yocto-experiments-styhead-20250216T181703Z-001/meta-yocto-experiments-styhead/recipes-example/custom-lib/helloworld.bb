#
# This file is the sampleapp recipe.
#
SUMMARY = "Simple sampleapp application"
SECTION = "sample apps"
LICENSE = "CLOSED"
SRC_URI = "file://helloworld.c"
S = "${WORKDIR}/sources"
UNPACKDIR = "${S}"
DEPENDS = "libsample"
do_compile() {
 ${CC} ${CFLAGS} ${LDFLAGS} -o hello helloworld.c -lsample
}
do_install() {
install -d ${D}${bindir}
install -m 0755 hello ${D}${bindir}
}
FILES_${PN} += "helloworld"

