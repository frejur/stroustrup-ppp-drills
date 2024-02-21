cmake_minimum_required(VERSION 3.2)
project(chapter_10
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_TEST "Test program")
set(T_DRILL_1_7 "Drill")
set(T_DRILL_X "Drill Extra")
set(T_E01 "Exercise 1")

set(SELECTED_TARGET ${T_TEST} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TEST}
    ${T_DRILL_1_7}
    ${T_DRILL_X}
    ${T_E01}
)
message("Building target: ${SELECTED_TARGET}")

IF(${SELECTED_TARGET} STREQUAL ${T_TEST})
    add_executable(chapter_10
        ch10_test.cpp
    )
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_DRILL_1_7})
    add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_1_7)
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_DRILL_X})
    add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_x)
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_E01})
    add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e01)
ENDIF()
