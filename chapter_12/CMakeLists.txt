cmake_minimum_required(VERSION 3.2)
project(chapter_12
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FLTK
find_package(FLTK REQUIRED NO_MODULE)
message(STATUS "FLTK_INCLUDE_DIRS = '${FLTK_INCLUDE_DIRS}'")

# Targets
set(T_TEST "Test")
set(T_DRILL "Drill")
set(T_E01 "Exercise 1")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6")
set(T_E07 "Exercise 7")
set(T_E08 "Exercise 8")
set(T_E09 "Exercise 9")
set(T_E10 "Exercise 10")
set(T_E11 "Exercise 11")
set(T_E12 "Exercise 12")

set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TEST}
    ${T_DRILL}
    ${T_E01}
    ${T_E02}
    ${T_E03}
    ${T_E04}
    ${T_E05}
    ${T_E06}
    ${T_E07}
    ${T_E08}
    ${T_E09}
    ${T_E10}
    ${T_E11}
    ${T_E12}
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
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E07})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e07)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E08})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e08)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E09})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e09)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E10})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e10)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E11})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e11)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E12})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e12)
endif()
