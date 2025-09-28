cmake_minimum_required(VERSION 3.10)
project(IPFilter)

set(CMAKE_CXX_STANDARD 17)

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Основная программа
add_executable(ip_filter 
    main.cpp 
    ip_filter.cpp
)

# Поиск GTest
find_package(GTest QUIET)

if(GTEST_FOUND)
    message(STATUS "GTest found, building tests")
    add_executable(ip_filter_test 
        test.cpp 
        ip_filter.cpp
    )
    target_link_libraries(ip_filter_test GTest::GTest GTest::Main)
    
    # Добавление тестов
    include(GoogleTest)
    gtest_discover_tests(ip_filter_test)
else()
    message(WARNING "GTest not found, tests will not be built")
endif()

# Установочные цели
install(TARGETS ip_filter DESTINATION bin)