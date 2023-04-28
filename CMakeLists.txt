# version requirements
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# initialization
include(${CMAKE_SOURCE_DIR}/src/Dependency/pico-sdk/pico_sdk_init.cmake)

# project definition
project(picolcd)

pico_sdk_init()

add_executable(${PROJECT_NAME} src/main.cpp)

# target configuration
set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++)

# Waveshare Pico_code/c/lib/GUI for graphics
set(PICO_CODE_LIB ${CMAKE_SOURCE_DIR}/src/Dependency/Pico_code/c/lib)
add_subdirectory(${PICO_CODE_LIB}/Config)
add_subdirectory(${PICO_CODE_LIB}/GUI)
include_directories(${PICO_CODE_LIB}/Config)
include_directories(${PICO_CODE_LIB}/Fonts)
include_directories(${PICO_CODE_LIB}/LCD)
include_directories(${PICO_CODE_LIB}/GUI)

# link libraries to project
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    pico_stdlib
    GUI
    Config)

pico_enable_stdio_usb(${PROJECT_NAME} 1) # enable usb output
pico_enable_stdio_uart(${PROJECT_NAME} 0) # disable uart output
pico_add_extra_outputs(${PROJECT_NAME}) # create map/bin/hex/uf2 files in addition to elf