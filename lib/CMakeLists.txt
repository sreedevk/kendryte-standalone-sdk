#project(maix_drivers)

# create driver library

ADD_SUBDIRECTORY(nncase)
# ADD_SUBDIRECTORY(freertos)

FILE(GLOB_RECURSE LIB_SRC
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.S"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.S"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.S"
        "${CMAKE_CURRENT_LIST_DIR}/tm1638/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/tm1638/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/u8g2/csrc/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/u8g2/csrc/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/u8g2-kendryte-sdk-hal/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/u8g2-kendryte-sdk-hal/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/ili9341/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/ili9341/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/mems-mic/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/mems-mic/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/lcd1602/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/lcd1602/*.c"
        )

FILE(GLOB_RECURSE ASSEMBLY_FILES
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/bsp/*.S"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/*.S"
        "${CMAKE_CURRENT_LIST_DIR}/utils/*.S"
        )

include_directories(${CMAKE_CURRENT_LIST_DIR}/drivers/include ${CMAKE_CURRENT_LIST_DIR}/bsp/include)

SET_PROPERTY(SOURCE ${ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp -D __riscv64")

ADD_LIBRARY(kendryte ${LIB_SRC})
TARGET_LINK_LIBRARIES(kendryte PUBLIC nncase)
SET_TARGET_PROPERTIES(kendryte PROPERTIES LINKER_LANGUAGE C)
