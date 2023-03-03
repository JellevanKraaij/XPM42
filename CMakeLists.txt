cmake_minimum_required(VERSION 3.18.0)

project(XPM42 VERSION 0.1.0)
set (LIB_NAME xpm42)
set (SRCS
    src/xpm_decode.c
	src/xpm_getline.c
	src/xpm_decode_header.c
	src/xpm_decode_body.c
)

set (CMAKE_C_FLAGS "-Wall -Werror -Wextra")
set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_library(${LIB_NAME} ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#-------------------- TESTING -------------------------------

if ((PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME AND BUILD_TESTS) OR XPM42_BUILD_TESTS)
	target_compile_options(${LIB_NAME} PRIVATE -fsanitize=address)
	add_subdirectory(test)
	enable_testing()
endif()
