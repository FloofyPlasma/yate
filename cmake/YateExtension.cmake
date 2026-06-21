function(yate_extension)
    cmake_parse_arguments(ARG "OPTIONAL" "NAME" "SOURCES;DEPS" ${ARGN})

    if(ARG_OPTIONAL)
        foreach(dep ${ARG_DEPS})
            if(NOT TARGET ${dep} AND NOT ${dep}_FOUND)
                message(STATUS "yate: skipping optional extension '${ARG_NAME}' (${dep} not found)")
                return()
            endif()
        endforeach()
    endif()

    add_library(yate_ext_${ARG_NAME} STATIC ${ARG_SOURCES})

    target_link_libraries(yate_ext_${ARG_NAME}
        PUBLIC yate_sdk
        PRIVATE ${ARG_DEPS}
    )

    target_include_directories(yate_ext_${ARG_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )

    set_property(GLOBAL APPEND PROPERTY YATE_EXTENSIONS yate_ext_${ARG_NAME})
endfunction()
