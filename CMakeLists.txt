cmake_minimum_required(VERSION 3.30)
project(yate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(YATE_ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(YATE_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (CLANG_TIDY_EXE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    elseif(CLANG_TIDY_EXE)
        message(WARNING "clang-tidy found, but compiler is not Clang; disabling")
    else()
        message(WARNING "clang-tidy requested but not found")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wdeprecated-declarations)
elseif(MSVC)
    add_compile_options(/W4 /w14996)
endif()

include(cmake/CPM.cmake)
include(cmake/YateExtension.cmake)

set(CPM_USE_LOCAL_PACKAGES ON)

CPMAddPackage(
    NAME SDL3
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-3.4.10
    VERSION 3.4.10
)

CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY bkaradzic/bgfx.cmake
    GIT_TAG v1.146.9306-550
    OPTIONS
        "BGFX_BUILD_TOOLS OFF"
        "BGFX_BUILD_EXAMPLES OFF"
        "BGFX_INSTALL OFF"
)

add_subdirectory(sdk)
add_subdirectory(core)
add_subdirectory(extensions)
add_subdirectory(app)
