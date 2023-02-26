cmake_minimum_required(VERSION 3.21.0)

project(XPM42)
set (SRCS
    src/xpm_decode.c
)
set (LIB_NAME xpm42)

set (CMAKE_C_FLAGS "-Wall -Werror -Wextra")
set (CMAKE_C_FLAGS_DEBUG "-g -fsanitize=address") #cmake -DCMAKE_BUILD_TYPE=DEBUG to add debug flags
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_library(${LIB_NAME} ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


#-------------------- TESTING -------------------------------


if ((PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME AND BUILD_TESTS) OR XPM42_BUILD_TESTS)
	add_subdirectory(test)
	enable_testing()
endif()
