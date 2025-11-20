cmake_minimum_required(VERSION 3.10)

# Название проекта
project(CustomAllocatorDemo LANGUAGES CXX)

# Требуем стандарт C++11 (или новее — можно поставить C++17, если используешь structured bindings)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # используем только стандартный C++, без расширений компилятора

# Добавляем исполняемый файл из main.cpp
# .hpp файлы не нужно указывать — они подключаются через #include
add_executable(${PROJECT_NAME} main.cpp)

# (Опционально) Добавим предупреждения для лучшей отладки
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()