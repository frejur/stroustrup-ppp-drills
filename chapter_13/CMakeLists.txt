cmake_minimum_required(VERSION 3.2)
project(chapter_13
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
set(T_DRILL "Drill")
set(T_E01 "Exercise 1")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6")
set(T_E07 "Exercise 7")
set(T_E09 "Exercise 9")
set(T_E11 "Exercise 11")
set(T_E13 "Exercise 13")
set(T_E14 "Exercise 14")
set(T_E15 "Exercise 15")
set(T_E17 "Exercise 17")
set(T_E18 "Exercise 18")
set(T_E19 "Exercise 19")

set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL}
    ${T_E01}
    ${T_E02}
    ${T_E03}
    ${T_E04}
    ${T_E05}
    ${T_E06}
    ${T_E07}
    ${T_E09}
    ${T_E11}
    ${T_E13}
    ${T_E14}
    ${T_E15}
    ${T_E17}
    ${T_E18}
    ${T_E19}
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
    ${SELECTED_TARGET} STREQUAL ${T_E09})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e09)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E11})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e11)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E13})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e13)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E14})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e14)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E15})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e15)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E17})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e17)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E18})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e18)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E19})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e19)
endif()

