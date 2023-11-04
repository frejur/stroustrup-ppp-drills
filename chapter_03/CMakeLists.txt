cmake_minimum_required(VERSION 3.2)
project(chapter_03
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_TT_P65 "Try this, p. 65")
set(T_TT_P68 "Try this, p. 68")
set(T_TT_P75 "Try this, p. 75")
set(T_TT_P81 "Try this, p. 81")
set(T_DRILL "Drill")
set(T_E02 "Exercise 2")
set(T_E04 "Exercise 4 (and 5)")
set(T_E06 "Exercise 6")
set(T_E07 "Exercise 7")
set(T_E08 "Exercise 8")
set(T_E09 "Exercise 9")


set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TT_P65}
    ${T_TT_P68}
    ${T_TT_P75}
    ${T_TT_P81}
    ${T_DRILL}
    ${T_E02}
    ${T_E04}
    ${T_E06}
    ${T_E07}
    ${T_E08}
    ${T_E09}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P65})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p65)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P68})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p68)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P75})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p75)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P81})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p81)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E02})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e02)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E04})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e04)
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
endif()
