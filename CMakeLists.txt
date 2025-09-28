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

# Поиск GTest - только если доступен
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
    message(STATUS "GTest not found - building without tests")
    # Не создаем цель для тестов
endif()