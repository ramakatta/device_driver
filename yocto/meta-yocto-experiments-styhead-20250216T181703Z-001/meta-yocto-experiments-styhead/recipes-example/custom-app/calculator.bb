SUMMARY = "A simple calculator application"                                    
DESCRIPTION = "This is a simple example of a Yocto recipe"                      
LICENSE = "MIT"                                                                 
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
SRC_URI = "file://calculator.c"                                                      
                                                                                
# Define where the source files are located inside WORKDIR                      
SRC_URI[sha256sum] = "auto"                                                     
                                                                                
# Define a dedicated source directory inside WORKDIR (best practice)            
S = "${WORKDIR}/sources"                                                        
UNPACKDIR = "${S}"                                                              
                                                                                
                                                                                
do_compile() {                                                                  
    ${CC} ${CFLAGS} ${LDFLAGS}  ${S}/calculator.c -o ${S}/calculator                      
}                                                                               

                                                                                
do_install() {                                                                  
    install -d ${D}${bindir}                                                    
    install -m 0755 ${S}/calculator ${D}${bindir}/calculator                              
}                                                                               
                                                                                
FILES_${PN} = "${bindir}/calculator"                                            

