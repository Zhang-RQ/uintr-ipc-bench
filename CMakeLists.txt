###########################################################
## CMAKE SETUP
###########################################################

cmake_minimum_required(VERSION 2.8.7)
project(ipc-bench)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
ENABLE_LANGUAGE(ASM)

add_subdirectory(source)
