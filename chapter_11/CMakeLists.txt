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

set(SELECTED_TARGET "Test" CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
    ${T_TEST}
    ${T_TT01}
    ${T_TT02}
    ${T_TT03}
    ${T_TT04}
)
message("Building target: ${SELECTED_TARGET}")

IF(${SELECTED_TARGET} MATCHES ${T_TEST})
    add_executable(chapter_11
        util.h
        util.cpp
        main.cpp
    )
ENDIF()

IF(${SELECTED_TARGET} MATCHES ${T_TT01})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt01)
ENDIF()

IF(${SELECTED_TARGET} MATCHES ${T_TT02})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt02)
ENDIF()

IF(${SELECTED_TARGET} MATCHES ${T_TT03})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt03)
ENDIF()

IF(${SELECTED_TARGET} MATCHES ${T_TT04})
    add_subdirectory(${CMAKE_SOURCE_DIR}/tt/tt04)
ENDIF()
