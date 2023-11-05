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
endif()
