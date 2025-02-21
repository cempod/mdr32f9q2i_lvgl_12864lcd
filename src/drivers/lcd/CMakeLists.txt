cmake_minimum_required(VERSION 3.22)

set(SCRS
    ${CMAKE_CURRENT_LIST_DIR}/lcd.c
)

add_library(lcd_driver INTERFACE)
target_sources(lcd_driver INTERFACE ${SCRS})

