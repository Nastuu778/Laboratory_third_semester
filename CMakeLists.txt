cmake_minimum_required(VERSION 3.10)
project(IPFilter)

set(CMAKE_CXX_STANDARD 17)

# Явно указываем выходную директорию
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Основная программа
add_executable(ip_filter 
    main.cpp 
    ip_filter.cpp
)

# Поиск GTest через find_package (vcpkg обеспечивает правильное нахождение)
find_package(GTest REQUIRED)

message(STATUS "GTest found, building tests")

add_executable(ip_filter_test 
    test.cpp 
    ip_filter.cpp
)

target_link_libraries(ip_filter_test GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ip_filter_test)