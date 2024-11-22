message("Processing /exercise/e09...")

set(T_THIS "Chapter_11_exercise_09")

add_executable(${T_THIS}
    e09.cpp
)

# Dynamically copy the data folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${T_THIS}>/data_e09
)
