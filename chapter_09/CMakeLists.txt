cmake_minimum_required(VERSION 3.2)
project(chapter_09
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
set(T_DRILL_4 "Drill 4")
set(T_DRILL_5 "Drill 5")
set(T_DRILL_X "Drill Extra")
set(T_E02 "Exercise 2 and 3")

set(SELECTED_TARGET ${T_DRILL_1} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL_1}
    ${T_DRILL_2}
    ${T_DRILL_3}
    ${T_DRILL_4}
    ${T_DRILL_5}
    ${T_DRILL_X}
    ${T_E02}
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
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_4})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_4)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_5})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_5)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_X})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_x)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E02})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e02)
endif()
