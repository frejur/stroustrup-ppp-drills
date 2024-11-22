message("Processing /exercise/e11...")

set(T_THIS "Chapter_10_exercise_11")

add_executable(${T_THIS}
    e11.cpp
    e11.h
)

# Dynamically copy the data folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${T_THIS}>/data_e11
)
