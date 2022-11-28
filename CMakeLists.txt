cmake_minimum_required(VERSION 3.12)

include(./pico_sdk_import.cmake)

project(temperature C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})




pico_sdk_init()

add_executable(temperature temperature.c)

target_link_libraries(temperature pico_stdlib hardware_adc)

pico_enable_stdio_usb(temperature 1)
pico_enable_stdio_uart(temperature 0)

pico_add_extra_outputs(temperature)
