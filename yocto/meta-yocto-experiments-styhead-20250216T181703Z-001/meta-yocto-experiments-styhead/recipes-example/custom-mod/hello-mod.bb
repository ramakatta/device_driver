SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
inherit module
SRC_URI = "file://Makefile \
file://hello-mod.c \
file://COPYING.MIT \
"
S = "${WORKDIR}/sources"
UNPACKDIR = "${S}"

