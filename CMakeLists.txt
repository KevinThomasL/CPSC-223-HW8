
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create unit test executable
add_executable(hw8test hw8_test.cpp)
target_link_libraries(hw8test ${GTEST_LIBRARIES} pthread)

# create performance executable
add_executable(hw8perf hw8_perf.cpp)
