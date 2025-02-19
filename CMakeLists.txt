cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Add you project name
project(firmware C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork -MMD -MP)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
add_compile_options(-lc -lm -lnosys -specs=nosys.specs)
add_compile_options(-Wall)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-O0 -g)
endif ()

set(DEFINES
    -DUSE_K1986VE92xI
    -D__STARTUP_CLEAR_BSS
)

add_definitions(${DEFINES})

# Add Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bsp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/cmsis/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/spl/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/spl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sys
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rtos
)

# Add you source file
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.S"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/cmsis/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/spl/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sys/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/rtos/*.c"
)

# Add linker file
file(GLOB LINKER_SCRIPT "*.ld")
message(STATUS "Found linker script - ${LINKER_SCRIPT}")

# this options for C++
add_link_options(-lnosys -specs=nosys.specs -specs=nano.specs -lc -lm)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

add_subdirectory(${CMAKE_SOURCE_DIR}/src/drivers/gpio)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/drivers/led)

target_link_libraries(${PROJECT_NAME}.elf
    gpio_driver
    led_driver
)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/modules/led_controller)

target_link_libraries(${PROJECT_NAME}.elf
    led_controller_module
)

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src/sys)
target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
# Select the cross-compile PORT
set(FREERTOS_PORT "GCC_ARM_CM3" CACHE STRING "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/freertos-kernel)

target_link_libraries(${PROJECT_NAME}.elf
    freertos_kernel
)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

