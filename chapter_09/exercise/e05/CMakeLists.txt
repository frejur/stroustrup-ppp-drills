message("Processing /exercise/e05...")

set(T_THIS "Chapter_09_exercise_05_to_09")

add_executable(${T_THIS}
	e05.cpp
	date/date.h
	date/date.cpp
	readme.md
	lib/book.h lib/book.cpp
	test/test_book.h
)
