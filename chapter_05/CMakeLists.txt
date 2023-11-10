cmake_minimum_required(VERSION 3.2)
project(chapter_05
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_TT_P138_139 "Try this, p. 138-139")
set(T_TT_P146 "Try this, p. 146")
set(T_TT_P153 "Try this, p. 153")
set(T_TT_P155_156 "Try this, p. 155-156")
set(T_TT_P157 "Try this, p. 157")
set(T_TT_P166 "Try this, p. 166")
set(T_DRILL "Drill")
set(T_E02 "Exercise 2")
set(T_E03 "Exercise 3")
set(T_E04 "Exercise 4")

set(SELECTED_TARGET ${T_TT_P138_139} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TT_P138_139}
    ${T_TT_P146}
    ${T_TT_P153}
    ${T_TT_P155_156}
    ${T_TT_P157}
    ${T_TT_P166}
    ${T_DRILL}
    ${T_E02}
    ${T_E03}
    ${T_E04}
)
message("Building target: ${SELECTED_TARGET}")

if(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P138_139})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p138_p139)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P146})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p146)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P153})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p153)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P155_156})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p155_p156)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P157})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p157)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_TT_P166})
        add_subdirectory(${CMAKE_SOURCE_DIR}/tt/p166)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_DRILL})
        add_subdirectory(${CMAKE_SOURCE_DIR}/drill)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E02})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e02)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E03})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e03)
elseif(
    ${SELECTED_TARGET} STREQUAL ${T_E04})
        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e04)
endif()
