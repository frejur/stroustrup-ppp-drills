message("Processing /exercise/e05...")

set(T_THIS "Chapter_09_exercise_05_to_09")

add_executable(${T_THIS}
	e05.cpp
	date/date.h
	date/date.cpp
	readme.md
	lib/book.h lib/book.cpp
	test/test_book.h
	lib/lib_helpers.h lib/lib_helpers.cpp
	lib/genre.cpp
	lib/patron.h lib/patron.cpp
	test/test_patron.h
	lib/library.h lib/library.cpp
	test/test_library.h
	test/print_helpers.h test/print_helpers.cpp
	sample/sample_books.h
	sample/sample_patrons.h

)
