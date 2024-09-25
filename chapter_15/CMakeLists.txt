cmake_minimum_required(VERSION 3.2)
project(chapter_15
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FLTK
find_package(FLTK REQUIRED NO_MODULE)
message(STATUS "FLTK_INCLUDE_DIRS = '${FLTK_INCLUDE_DIRS}'")

# Targets
set(T_DRILL "Drill")
#set(T_E01 "Exercise 1")

set(SELECTED_TARGET ${T_DRILL} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS
   ${T_DRILL}
#    ${T_E01}
)
message("Building target: ${SELECTED_TARGET}")

if(
   ${SELECTED_TARGET} STREQUAL ${T_DRILL})
       add_subdirectory(${CMAKE_SOURCE_DIR}/drill)
#elseif(
#    ${SELECTED_TARGET} STREQUAL ${T_E01})
#        add_subdirectory(${CMAKE_SOURCE_DIR}/exercise/e01)
endif()
