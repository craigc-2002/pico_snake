cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(PicoSnake
    VERSION 0.1
    DESCRIPTION "Snake clone on Raspberry Pi Pico using my pico alarm clock hardware library"
    LANGUAGES CXX C ASM
)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(lib/alarm_clock_hw_lib) # library for the display

add_executable(snake
    main.cpp
    snake.cpp
)

target_link_libraries(snake
    alarm-clock-hw-lib
    pico_stdlib)

pico_add_extra_outputs(snake)
