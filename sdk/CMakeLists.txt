add_library(yate_sdk INTERFACE)

target_include_directories(yate_sdk
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/core/include
)

target_compile_features(yate_sdk INTERFACE cxx_std_20)
