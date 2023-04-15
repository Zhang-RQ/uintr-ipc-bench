set(CMAKE_SYSTEM_NAME Linux)

set(TOOLCHAIN_PATH /opt/riscv)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/riscv64-unknown-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/riscv64-unknown-linux-gnu-g++)

