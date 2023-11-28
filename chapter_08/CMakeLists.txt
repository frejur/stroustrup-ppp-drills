cmake_minimum_required(VERSION 3.2)
project(chapter_08
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_DRILL_1 "Drill 1")
set(T_DRILL_2 "Drill 2")
set(T_DRILL_3 "Drill 3")
set(T_E01 "Exercise 1")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3 and 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6")
set(T_E07 "Exercise 7 and 8")
set(T_E09 "Exercise 9")
set(T_E10 "Exercise 10")

set(SELECTED_TARGET ${T_DRILL_1} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL_1}
    ${T_DRILL_2}
    ${T_DRILL_3}
    ${T_E01}
    ${T_E02}
    ${T_E03}
    ${T_E05}
    ${T_E06}
    ${T_E07}
    ${T_E09}
    ${T_E10}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_1})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_1)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_2})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_2)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_3})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_3)
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
    ${SELECTED_TARGET} STREQUAL ${T_E10})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e10)
endif()
