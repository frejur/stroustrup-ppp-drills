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
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5 to 9")
set(T_E10 "Exercise 10 and 11")
set(T_E12 "Exercise 12")

set(SELECTED_TARGET ${T_DRILL_1} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_DRILL_1}
    ${T_DRILL_2}
    ${T_DRILL_3}
    ${T_DRILL_4}
    ${T_DRILL_5}
    ${T_DRILL_X}
    ${T_E02}
    ${T_E04}
    ${T_E05}
    ${T_E10}
    ${T_E12}
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
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E04})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e04)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E05})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e05)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E10})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e10)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E12})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e12)
endif()
