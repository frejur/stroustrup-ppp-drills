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
set(T_DRILL "Drill")
set(T_E01 "Exercise 1")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6")

set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL}
    ${T_E01}
    ${T_E02}
    ${T_E03}
    ${T_E04}
    ${T_E05}
    ${T_E06}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E01})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e01)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E02})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e02)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E03})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e03)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E04})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e04)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E05})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e05)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E06})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e06)
endif()
