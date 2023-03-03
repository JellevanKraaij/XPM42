set(TEST_EXECUTABLE_NAME unit_tests)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

# Download GoogleTest
# --------------------------------------------------
include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
	googletest
	DOWNLOAD_EXTRACT_TIMESTAMP
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

# --------------------------------------------------
add_executable(
	${TEST_EXECUTABLE_NAME}
	tests.cpp
)

target_compile_options(${TEST_EXECUTABLE_NAME} PRIVATE -fsanitize=address)
target_link_options(${TEST_EXECUTABLE_NAME} PRIVATE -fsanitize=address)

target_link_libraries(
	${TEST_EXECUTABLE_NAME}
	GTest::gtest_main
	xpm42
)

# Add tests to CTest
# Set working directory to the the testing folder so that the test can find their test files
# --------------------------------------------------
gtest_discover_tests(${TEST_EXECUTABLE_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} ADD_PREFIX "XPM42.")
enable_testing()
