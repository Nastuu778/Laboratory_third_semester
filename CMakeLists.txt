cmake_minimum_required(VERSION 3.15)
project(ContainersDemo VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific settings
if(MSVC)
    # Windows/Visual Studio settings
    add_compile_options(/W4 /permissive-)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(/O2 /DNDEBUG)
        add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    else()
        add_compile_options(/Zi /Od)
    endif()
else()
    # Linux/GCC settings
    add_compile_options(-Wall -Wextra -pedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    else()
        add_compile_options(-g -O0)
    endif()
endif()

# Create executable
add_executable(containers_demo main.cpp task.cpp)

# Set output properties
set_target_properties(containers_demo PROPERTIES
    OUTPUT_NAME "containers_demo"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Include directories
target_include_directories(containers_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Настройка CPack для создания пакетов
set(CPACK_PACKAGE_NAME "ContainersDemo")
set(CPACK_PACKAGE_VENDOR "YourName")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Custom containers implementation - Vector, DoublyLinkedList, SinglyLinkedList")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ContainersDemo")

# Для DEB пакетов
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name <your.email@example.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

# Для Windows
set(CPACK_NSIS_DISPLAY_NAME "Containers Demo")
set(CPACK_NSIS_PACKAGE_NAME "ContainersDemo")

include(CPack)