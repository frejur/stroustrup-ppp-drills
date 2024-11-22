cmake_minimum_required(VERSION 3.2)
project(chapter_10
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ALL "ALL") # When `SELECTED_TARGET` is set to this value, all targets
               # will be built. Do NOT insert this value into the
               # `TARGETS` list below

# Shorthand for appending to TARGETS and DIRS
function(apd list_var)
   foreach(target IN LISTS ARGN)
        list(APPEND ${list_var} "${target}")
    endforeach()
    # Return changes made to local copy to Parent scope
    set(${list_var} ${${list_var}} PARENT_SCOPE)
endfunction()

# Targets and directories
set(test_name "Test program")
set(test_src  "ch10_test.cpp")
set(test_exe  "Chapter_10_test")

set(TARGETS "Drill"             "Drill Extra")
set(DIRS    "drill/drill_1_7"   "drill/drill_x")

apd(TARGETS "Exercise 1"       "Exercise 2 to 4"   "Exercise 5")
apd(DIRS    "exercise/e01"     "exercise/e02"      "exercise/e05")

apd(TARGETS "Exercise 6, 7 and 10" "Exercise 8"    "Exercise 9")
apd(DIRS    "exercise/e06"         "exercise/e08"  "exercise/e09")

apd(TARGETS "Exercise 11")
apd(DIRS    "exercise/e11")

# Ensure TARGETS length == DIRS length
list(LENGTH TARGETS num_targets)
list(LENGTH DIRS num_dirs)
if(NOT num_targets EQUAL num_dirs)
    message(FATAL_ERROR "Number of entries in TARGETS (${num_targets})"
                        "does not match number of entries in "
                        "DIRS (${num_dirs})")
endif()

# Default target
list(GET TARGETS 0 DEFAULT_TARGET)

# Make targets selectable in `ccmake` and similar
set(SELECTED_TARGET ${DEFAULT_TARGET} CACHE STRING "Selected target")
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS ${test_name} ${TARGETS} ${ALL})

# Print targets
message(STATUS "Available values for SELECTED_TARGET:")
foreach(target ${test_name} ${TARGETS} ${ALL})
    message(STATUS " ${target}")
endforeach()
message(STATUS "Currently selected target: ${SELECTED_TARGET}")

# Build 'All targets' if selected
if(${SELECTED_TARGET} STREQUAL ${ALL})
    message(STATUS "Building all targets...")
    foreach(target_dir ${DIRS})
        add_subdirectory(${CMAKE_SOURCE_DIR}/${target_dir})
    endforeach()
    add_executable(${test_exe} ${CMAKE_SOURCE_DIR}/${test_src})

# Build 'Test program' if selected
elseif(${SELECTED_TARGET} STREQUAL ${test_name})
    add_executable(${test_exe} ${CMAKE_SOURCE_DIR}/${test_src})
else()

# Otherwise, build 'Selected target'
    math(EXPR max_idx "${num_targets} - 1")
    foreach(i RANGE ${max_idx})
        list(GET TARGETS ${i} target)
        list(GET DIRS ${i} target_dir)

        if(${SELECTED_TARGET} STREQUAL ${target})
            message(STATUS "Building ${target}...")
            add_subdirectory(${CMAKE_SOURCE_DIR}/${target_dir})
            break()
        endif()
    endforeach()
endif()
