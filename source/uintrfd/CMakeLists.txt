###########################################################
## TARGETS
###########################################################

add_executable(uintrfd-uni uintrfd-uni.c uintr.S)
add_executable(uintrfd-bi uintrfd-bi.c uintr.S)

###########################################################
## COMMON
###########################################################

target_link_libraries(uintrfd-uni ipc-bench-common pthread)
target_link_libraries(uintrfd-bi ipc-bench-common pthread)