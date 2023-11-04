cmake_minimum_required(VERSION 3.2)
project(chapter_06
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_DRILL "Drill")

set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill)
endif()
