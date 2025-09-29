cmake_minimum_required(VERSION 3.14)
project(ip_filter_tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(ip_filter_tests test.cpp)
target_link_libraries(ip_filter_tests PRIVATE ip_filter_lib gtest gtest_main)

# Включение тестирования
enable_testing()
add_test(NAME ip_filter_tests COMMAND ip_filter_tests)