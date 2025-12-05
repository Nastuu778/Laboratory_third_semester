cmake_minimum_required(VERSION 3.14)
project(VectorEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включаем предупреждения
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Исходники
file(GLOB_RECURSE SOURCES src/*.cpp)

# Исполняемый файл
add_executable(vector-editor ${SOURCES})

# Include директории
target_include_directories(vector-editor PRIVATE include)