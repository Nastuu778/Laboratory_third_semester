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

# Поиск GTest с разными вариантами
find_package(GTest QUIET)

if(GTEST_FOUND)
    message(STATUS "GTest found, building tests")
    add_executable(ip_filter_test 
        test.cpp 
        ip_filter.cpp
    )
    target_link_libraries(ip_filter_test GTest::GTest GTest::Main)
    
    include(GoogleTest)
    gtest_discover_tests(ip_filter_test)
else()
    message(WARNING "GTest not found, tests will not be built")
    
    # Альтернативный поиск в стандартных путях Windows
    find_path(GTEST_INCLUDE_DIR gtest/gtest.h
        PATHS "C:/gtest/include"
    )
    find_library(GTEST_LIBRARY
        NAMES gtest
        PATHS "C:/gtest/lib"
    )
    
    if(GTEST_INCLUDE_DIR AND GTEST_LIBRARY)
        message(STATUS "GTest found via manual search")
        add_executable(ip_filter_test 
            test.cpp 
            ip_filter.cpp
        )
        target_include_directories(ip_filter_test PRIVATE ${GTEST_INCLUDE_DIR})
        target_link_libraries(ip_filter_test ${GTEST_LIBRARY})
    else()
        message(STATUS "GTest not available - skipping tests")
    endif()
endif()