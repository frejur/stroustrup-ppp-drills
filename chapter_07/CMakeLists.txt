cmake_minimum_required(VERSION 3.2)
project(chapter_07
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_TT "Try This")
set(T_DRILL_1_5 "Drill 1 to 5")
set(T_DRILL_6_11 "Drill 6 to 11")
set(T_E01 "Exercise 1")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6 and 7")
set(T_E09 "Exercise 9")
set(T_E10 "Exercise 10")
set(T_E11_A "Exercise 11, revisit Chapter 4")
set(T_E11_B "Exercise 11, revisit Chapter 5")

set(SELECTED_TARGET ${T_TT} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TT}
    ${T_DRILL_1_5}
    ${T_DRILL_6_11}
    ${T_E01}
    ${T_E02}
    ${T_E03}
    ${T_E04}
    ${T_E05}
    ${T_E06}
    ${T_E09}
    ${T_E10}
    ${T_E11_A}
    ${T_E11_B}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_TT})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_1_5})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_1_5)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_6_11})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_6_11)
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
    ${SELECTED_TARGET} STREQUAL ${T_E09})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e09)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E10})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e10)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E11_A})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e11/e11_a)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E11_B})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e11/e11_b)
endif()
