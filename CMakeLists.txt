# DO NOT MODIFY THIS FILE, IT WILL BE OVERRIDE!!!

# set this will supress some warnings
set(BUILDING_SDK "yes" CACHE INTERNAL "")

# basic config
if (NOT PROJ)
    get_filename_component(PROJ ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
    get_filename_component(PROJ ${PROJ} NAME)
    string(REPLACE " " "_" PROJ ${PROJ})
    message(STATUS "PROJ not set, use ${PROJ} as PROJ. Also, you can set it manually. e.g. -DPROJ=hello_world")
else()
    message("PROJ = ${PROJ}")
endif ()
cmake_minimum_required(VERSION 3.0)
include(./cmake/common.cmake)
project(${PROJ} C CXX ASM)

# config self use headers
include(./cmake/macros.internal.cmake)
header_directories(${SDK_ROOT}/lib)
header_directories(${SDK_ROOT}/third_party)
header_directories(src/${PROJ})
header_directories(src/${PROJ}/include)
header_directories(kendryte-standalone-demo/${PROJ})
# build library first
add_subdirectory(lib)
add_subdirectory(third_party)

# compile project
add_source_files(src/${PROJ}/*.c src/${PROJ}/*.s src/${PROJ}/*.S src/${PROJ}/*.cpp)
add_source_files(${SDK_ROOT}/${PROJ}/*.c ${SDK_ROOT}/${PROJ}/*.s ${SDK_ROOT}/${PROJ}/*.S ${SDK_ROOT}/${PROJ}/*.cpp)
include(./cmake/executable.cmake)

