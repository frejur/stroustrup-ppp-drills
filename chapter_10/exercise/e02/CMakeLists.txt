message("Processing /exercise/e02...")

set(T_THIS "Chapter_10_exercise_02_to_04")

add_executable(${T_THIS}
	e02_to_04_main.cpp
	
	e02/e02.h
	e02/e02.cpp
	
	e03/e03.h
	e03/e03.cpp
	
	e04/e04.h
	e04/e04.cpp
	
	lib/helpers.h
	lib/helpers.cpp
	
	share/e02_to_04_shared.h
	share/e02_to_04_shared.cpp
)

# Dynamically copy the data folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${T_THIS}>/data_e02
)
