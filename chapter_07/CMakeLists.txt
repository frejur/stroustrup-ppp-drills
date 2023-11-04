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

set(SELECTED_TARGET ${T_TT} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TT}
    ${T_DRILL_1_5}
    ${T_DRILL_6_11}
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
endif()
