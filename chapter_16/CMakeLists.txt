cmake_minimum_required(VERSION 3.2)

project(chapter_16 VERSION 0.0.0 LANGUAGES CXX)

SET(VERBOSE ON)

SET(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FLTK
find_package(FLTK REQUIRED NO_MODULE)

# Targets
set(T_DRILL_A "Drill A")

SET(SELECTED_TARGET ${T_DRILL_A} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL_A}
)
message("Building target: ${SELECTED_TARGET}")

if (
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_A})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_a)
endif()
