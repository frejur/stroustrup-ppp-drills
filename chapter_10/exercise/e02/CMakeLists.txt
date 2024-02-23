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

file(COPY data DESTINATION .)
