cmake_minimum_required(VERSION 3.0)
project(app_project)
add_executable(string main.c mystrlen.c mystrcmp.c mystrrev.c mystrcpy.c mystr.h)
install(TARGETS string DESTINATION bin)
