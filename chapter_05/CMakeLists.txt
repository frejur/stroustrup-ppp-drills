cmake_minimum_required(VERSION 3.2)
project(chapter_05
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

set(TARGETS "Try this, p. 138-139"  "Try this, p. 146"  "Try this, p. 153")
set(DIRS    "tt/p138_p139"          "tt/p146"          "tt/p153")

apd(TARGETS "Try this, p. 155-156"  "Try this, p. 157"  "Try this, p. 166")
apd(DIRS    "tt/p155_p156"          "tt/p157"          "tt/p166")

apd(TARGETS "Drill"                "Exercise 2"        "Exercise 3")
apd(DIRS    "drill"                "exercise/e02"      "exercise/e03")

apd(TARGETS "Exercise 4"           "Exercise 5"        "Exercise 6")
apd(DIRS    "exercise/e04"         "exercise/e05"      "exercise/e06")

apd(TARGETS "Exercise 7"           "Exercise 8"        "Exercise 9")
apd(DIRS    "exercise/e07"         "exercise/e08"      "exercise/e09")

apd(TARGETS "Exercise 10"          "Exercise 11"       "Exercise 12 and 13")
apd(DIRS    "exercise/e10"         "exercise/e11"      "exercise/e12")

apd(TARGETS "Exercise 14")
apd(DIRS    "exercise/e14")

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
set_property(CACHE SELECTED_TARGET PROPERTY STRINGS ${TARGETS} ${ALL})

# Print targets
message(STATUS "Available values for SELECTED_TARGET:")
foreach(target ${TARGETS} ${ALL})
    message(STATUS " ${target}")
endforeach()
message(STATUS "Currently selected target: ${SELECTED_TARGET}")

# Build 'All targets' if selected
if(${SELECTED_TARGET} STREQUAL ${ALL})
    message(STATUS "Building all targets...")
    foreach(target_dir ${DIRS})
        add_subdirectory(${CMAKE_SOURCE_DIR}/${target_dir})
    endforeach()
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

