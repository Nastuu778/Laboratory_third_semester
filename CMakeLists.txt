cmake_minimum_required(VERSION 3.14)
project(ip_filter VERSION 1.0.0)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем библиотеку из общих исходных файлов
add_library(ip_filter_lib STATIC ip_filter.cpp)
target_include_directories(ip_filter_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Основное приложение
add_executable(ip_filter main.cpp)
target_link_libraries(ip_filter PRIVATE ip_filter_lib)

# Добавляем поддиректорию с тестами
add_subdirectory(gtest_tests)

# Настройка CPack
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VENDOR "Your Name")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IP Filter Application")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-windows")
else()
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-linux")
endif()

include(CPack)

# Установка файлов для пакета
install(TARGETS ip_filter
    RUNTIME DESTINATION bin
)