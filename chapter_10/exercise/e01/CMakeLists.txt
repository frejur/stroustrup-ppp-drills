message("Processing /exercise/e01...")

set(T_THIS "Chapter_10_exercise_01")

add_executable(${T_THIS}
    e01_main.cpp
	e01.h
	e01.cpp
)

file(COPY data DESTINATION .)
