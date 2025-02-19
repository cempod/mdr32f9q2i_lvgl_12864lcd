cmake_minimum_required(VERSION 3.22)

set(SCRS
    ${CMAKE_CURRENT_LIST_DIR}/led_controller.c
)

add_library(led_controller_module INTERFACE)
target_sources(led_controller_module INTERFACE ${SCRS})

