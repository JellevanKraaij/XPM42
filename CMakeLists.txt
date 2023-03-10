cmake_minimum_required(VERSION 3.18.0)

project(XPM42 VERSION 0.1.0)
set (LIB_NAME xpm42)
set (SRCS
    src/xpm_decode.c
	src/xpm_getline.c
	src/xpm_decode_header.c
	src/xpm_decode_body.c
)

add_library(${LIB_NAME} ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_compile_options(${LIB_NAME} PRIVATE -O3 -Wall -Werror -Wextra -Wshadow)
target_compile_features(${LIB_NAME} PRIVATE c_std_90)


#-------------------- TESTING -------------------------------

if ((PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME AND BUILD_TESTS) OR XPM42_BUILD_TESTS)
	target_compile_options(${LIB_NAME} PUBLIC -fsanitize=address -g3)
	add_subdirectory(test)
	enable_testing()
endif()
