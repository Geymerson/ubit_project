set(ENV{ZEPHYR_BASE} /home/geymerson/zephyr)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} zephyr)
set(ENV{ZEPHYR_SDK_INSTALL_DIR} /home/geymerson/zephyr-sdk)

set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(ubit_project)

message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")

# Generate version file
include(build.version.cmake NO_POLICY_SCOPE)

FILE(GLOB app_sources src/*.c)

include_directories(
	"${PROJECT_BINARY_DIR}/include/generated"
    "${PROJECT_SOURCE_DIR}/include"
)

# Schedule a new version file generation after every build
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
    -DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
    -DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}
    -P ${PROJECT_SOURCE_DIR}/build.version.cmake
)

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/main.c"
    "${PROJECT_SOURCE_DIR}/src/buttons.c"
	"${PROJECT_SOURCE_DIR}/src/i2c_util.c"
)

target_sources(app PRIVATE ${SOURCES})
