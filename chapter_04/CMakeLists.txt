cmake_minimum_required(VERSION 3.2)
project(chapter_04
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
set(TARGETS "Try this, p. 105"  "Try this, p. 109"  "Try this, p. 111")
set(DIRS    "tt/p105"           "tt/p109"           "tt/p111")

apd(TARGETS "Try this, p. 113"  "Try this, p. 116"  "Try this, p. 125")
apd(DIRS    "tt/p113"           "tt/p116"           "tt/p125")

apd(TARGETS "Drill 1 to 5"       "Drill 6 to 11"       "Exercise 2")
apd(DIRS    "drill/drill_1_to_5" "drill/drill_6_to_11" "exercise/e02")

apd(TARGETS "Exercise 3"     "Exercise 4"     "Exercise 5")
apd(DIRS    "exercise/e03"   "exercise/e04"   "exercise/e05")

apd(TARGETS "Exercise 6"     "Exercise 7"     "Exercise 8")
apd(DIRS    "exercise/e06"   "exercise/e07"   "exercise/e08")

apd(TARGETS "Exercise 9"     "Exercise 10"    "Exercise 11")
apd(DIRS    "exercise/e09"   "exercise/e10"   "exercise/e11")

apd(TARGETS "Exercise 12"    "Exercise 13 (And 14)" "Exercise 15")
apd(DIRS    "exercise/e12"   "exercise/e13"         "exercise/e15")

apd(TARGETS "Exercise 16"    "Exercise 17"    "Exercise 18")
apd(DIRS    "exercise/e16"   "exercise/e17"   "exercise/e18")

apd(TARGETS "Exercise 19 to 21")
apd(DIRS    "exercise/e19")

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
