cmake_minimum_required(VERSION 3.2)
project(chapter_11
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
set(T_TEST "Test program")
set(T_TT01 "Try This 1")
set(T_TT02 "Try This 2")
set(T_TT03 "Try This 3")
set(T_TT04 "Try This 4")
set(E01 "Exercise 1")
set(E02 "Exercise 2")
set(E03 "Exercise 3")

set(SELECTED_TARGET "Test program" CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TEST}
    ${T_TT01}
    ${T_TT02}
    ${T_TT03}
    ${T_TT04}
    ${E01}
    ${E02}
    ${E03}
)
message("Building target: ${SELECTED_TARGET}")

IF(${SELECTED_TARGET} STREQUAL ${T_TEST})
    add_executable(chapter_11
        util.h
        util.cpp
        main.cpp
    )
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_TT01})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt01)
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_TT02})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt02)
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_TT03})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt03)
ELSEIF(${SELECTED_TARGET} STREQUAL ${T_TT04})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt04)
ELSEIF(${SELECTED_TARGET} STREQUAL ${E01})
    add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e01)
ELSEIF(${SELECTED_TARGET} STREQUAL ${E02})
    add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e02)
ELSEIF(${SELECTED_TARGET} STREQUAL ${E03})
    add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e03)
ENDIF()
