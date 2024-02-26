message("Processing /exercise/e05...")

set(T_THIS "Chapter_10_exercise_05")

add_executable(${T_THIS}
    e05_main.cpp
	e05.h
	e05.cpp
    reading/reading.h reading/reading.cpp
    date/date.h date/date.cpp
    help/helpers.h
    help/helpers.cpp
)

file(COPY data DESTINATION .)
