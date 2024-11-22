cmake_minimum_required(VERSION 3.2)
project(chapter_11
    VERSION 0.0.0
    LANGUAGES CXX
)
set(VERBOSE ON)

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
set(test_src  "${CMAKE_SOURCE_DIR}/main.cpp"
              "${CMAKE_SOURCE_DIR}/util.cpp"
              "${CMAKE_SOURCE_DIR}/util.h")
set(test_exe  "Chapter_11_test")

set(TARGETS "Try This 1"        "Try This 2")
set(DIRS    "tt/tt01"           "tt/tt02")

apd(TARGETS "Try This 3"       "Try This 4"        "Exercise 1")
apd(DIRS    "tt/tt03"          "tt/tt04"           "exercise/e01")

apd(TARGETS "Exercise 2"       "Exercise 3"        "Exercise 4")
apd(DIRS    "exercise/e02"     "exercise/e03"      "exercise/e04")

apd(TARGETS "Exercise 5 and 14" "Exercise 6 to 8"  "Exercise 9")
apd(DIRS    "exercise/e05"      "exercise/e06"     "exercise/e09")

apd(TARGETS "Exercise 10 and 11" "Exercise 12 and 13" "Exercise 15")
apd(DIRS    "exercise/e10"       "exercise/e12"      "exercise/e15")

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
    add_executable(${test_exe} ${test_src})

# Build 'Test program' if selected
elseif(${SELECTED_TARGET} STREQUAL ${test_name})
    add_executable(${test_exe} ${test_src})
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
