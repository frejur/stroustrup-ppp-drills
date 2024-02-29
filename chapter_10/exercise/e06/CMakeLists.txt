message("Processing /exercise/e06...")

set(T_THIS "Chapter_10_exercise_06_and_07")

add_executable(${T_THIS}
    e06_e07_main.cpp
    test/test_roman.h
    test/test_roman.cpp
    roman/roman.h roman/roman.cpp
    help/help.h help/help.cpp
    calc/calc.cpp
    calc/calc.h
)

file(COPY test/data DESTINATION .)
