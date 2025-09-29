DESCRIPTION = "Example Hello world application with Makefile and Yocto build."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://custom-make.c \
           file://Makefile"

# Define the source directory
S = "${WORKDIR}/sources"
UNPACKDIR = "${S}"


# Compiler flags
CFLAGS = "-Wall -Wextra -O2 -pipe"
TARGET_CC_ARCH += "${LDFLAGS}"

# Pass CFLAGS and CC correctly
EXTRA_OEMAKE = "'CC=${CC}' 'CFLAGS=${CFLAGS}'"


# Compile using Makefile
do_compile() {
    oe_runmake
}

# Install compiled binary correctly
do_install() {
    install -d ${D}${bindir}
    oe_runmake install DESTDIR=${D}
}

# Ensure correct packaging
FILES_${PN} = "${bindir}/hello_m"

