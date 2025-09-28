cmake_minimum_required(VERSION 3.14)
project(ip_filter)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Статическая линковка для MinGW
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
endif()

# Включение FetchContent
include(FetchContent)

# Загрузка и настройка Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Для статической линковки GTest
set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF)

# Скачивание и создание целей googletest
FetchContent_MakeAvailable(googletest)

# Ваши исполняемые файлы
add_executable(ip_filter main.cpp ip_filter.cpp)
add_executable(ip_filter_test test.cpp ip_filter.cpp)

# Линковка с Google Test
target_link_libraries(ip_filter_test PRIVATE gtest_main)

# Включение тестирования
enable_testing()
add_test(NAME ip_filter_test COMMAND ip_filter_test)