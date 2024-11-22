message("Processing /exercise/e05...")

set(T_THIS "Chapter_11_exercise_05")

add_executable(${T_THIS}
    e05.h e05.cpp
    ../../lib/help.h ../../lib/help.cpp
    chcl/chcl.h chcl/chcl.cpp
)

# Dynamically copy the data folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${T_THIS}>/data_e05
)
