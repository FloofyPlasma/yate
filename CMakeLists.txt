cmake_minimum_required(VERSION 3.30)
project(yate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(YATE_ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)

if(YATE_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy requested but not found")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wdeprecated-declarations)
elseif(MSVC)
    add_compile_options(/W4 /w14996)
endif()

include(cmake/YateExtension.cmake)

add_subdirectory(sdk)
add_subdirectory(core)
add_subdirectory(extensions)
add_subdirectory(app)
