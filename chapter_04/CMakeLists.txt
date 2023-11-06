cmake_minimum_required(VERSION 3.2)
project(chapter_04
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_TT_P105 "Try this, p. 105")
set(T_TT_P109 "Try this, p. 109")
set(T_TT_P111 "Try this, p. 111")
set(T_TT_P113 "Try this, p. 113")
set(T_TT_P116 "Try this, p. 116")
set(T_TT_P125 "Try this, p. 125")
set(T_DRILL_1_5 "Drill 1 to 5")
set(T_DRILL_6_11 "Drill 6 to 11")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")
set(T_E05 "Exercise 5")
set(T_E06 "Exercise 6")
set(T_E07 "Exercise 7")
set(T_E08 "Exercise 8")
set(T_E09 "Exercise 9")

set(SELECTED_TARGET ${T_TT_P105} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TT_P105}
    ${T_TT_P109}
    ${T_TT_P111}
    ${T_TT_P113}
    ${T_TT_P116}
    ${T_TT_P125}
    ${T_DRILL_1_5}
    ${T_DRILL_6_11}
    ${T_E02}
    ${T_E03}
    ${T_E04}
    ${T_E05}
    ${T_E06}
    ${T_E07}
    ${T_E08}
    ${T_E09}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P105})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p105)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P109})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p109)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P111})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p111)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P113})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p113)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P116})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p116)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P125})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p125)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_1_5})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_1_to_5)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL_6_11})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill/drill_6_to_11)
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
endif()
