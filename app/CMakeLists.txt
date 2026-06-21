get_property(YATE_EXTENSIONS GLOBAL PROPERTY YATE_EXTENSIONS)

add_executable(yate src/main.cpp)

target_include_directories(yate PRIVATE ${CMAKE_SOURCE_DIR}/extensions)

target_link_libraries(yate
    PRIVATE
        ${YATE_EXTENSIONS}
        yate_core
        yate_sdk
)
