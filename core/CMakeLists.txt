add_library(yate_core STATIC
    src/editor.cpp
)

target_include_directories(yate_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(yate_core PRIVATE yate_sdk)
