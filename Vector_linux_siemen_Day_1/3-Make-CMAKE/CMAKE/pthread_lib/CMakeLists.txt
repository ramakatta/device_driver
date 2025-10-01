cmake_minimum_required(VERSION 2.8)
project(pthread_task)
add_executable(pthread_task main.c)
target_link_libraries(pthread_task pthread.so.0)
install(TARGETS pthread_task DESTINATION ${CMAKE_INSTALL_PREFIX})


