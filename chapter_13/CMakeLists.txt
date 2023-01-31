cmake_minimum_required(VERSION 3.2)
project(chapter_13
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FLTK
find_package(FLTK REQUIRED NO_MODULE)
message(STATUS "FLTK_INCLUDE_DIRS = '${FLTK_INCLUDE_DIRS}'")

# Targets
set(T_TEST "Test")
set(T_DRILL "Drill")

set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TEST}
    ${T_DRILL}
)
message("Building target: ${SELECTED_TARGET}")

IF(${SELECTED_TARGET} MATCHES ${T_DRILL})
    add_subdirectory(${CMAKE_SOURCE_DIR}/drill)
ENDIF()
