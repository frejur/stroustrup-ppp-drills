cmake_minimum_required(VERSION 3.2)

project(chapter_16 VERSION 0.0.0 LANGUAGES CXX)

SET(VERBOSE ON)

SET(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FLTK
find_package(FLTK REQUIRED NO_MODULE)

# Targets
set(T_DRILL_A "Drill A")
set(T_DRILL_B "Drill B")
set(T_DRILL_C "Drill C")

set(T_E01 "Exercise 1")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6")
set(T_E07 "Exercise 7")

SET(SELECTED_TARGET ${T_DRILL_A} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL_A}
    ${T_DRILL_B}
    ${T_DRILL_C}
    ${T_E01}
    ${T_E02}
    ${T_E03}
    ${T_E04}
    ${T_E05}
    ${T_E06}
    ${T_E07}
)
message("Building target: ${SELECTED_TARGET}")

if (
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_A})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_a)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_B})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_b)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_C})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_c)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E01})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e01/)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E02})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e02/)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E03})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e03/)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E04})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e04/)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E05})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e05/)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E06})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e06/)
elseif (
    ${SELECTED_TARGET} STREQUAL ${T_E07})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e07/)
endif()
