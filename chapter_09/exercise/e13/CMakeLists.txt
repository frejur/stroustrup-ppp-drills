message("Processing /exercise/e13...")

set(T_THIS "Chapter_09_exercise_13")

add_executable(${T_THIS}
	e13.cpp
	rational.h rational.cpp
	test/test.h test/test.cpp
	../../lib/help.h ../../lib/help.cpp
)
