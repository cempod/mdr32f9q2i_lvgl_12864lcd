cmake_minimum_required(VERSION 3.22)

set(SCRS
    ${CMAKE_CURRENT_LIST_DIR}/lcd_controller.c
)

add_library(lcd_controller_module INTERFACE)
target_sources(lcd_controller_module INTERFACE ${SCRS})

