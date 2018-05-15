set(ENV{ZEPHYR_BASE} /home/geymerson/zephyr)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} zephyr)
set(ENV{ZEPHYR_SDK_INSTALL_DIR} /home/geymerson/zephyr-sdk)

set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(ubit_project)

message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
)

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/main.c"
)

target_sources(app PRIVATE ${SOURCES})
