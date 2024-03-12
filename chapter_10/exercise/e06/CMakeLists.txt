message("Processing /exercise/e06...")

set(T_THIS "Chapter_10_exercise_06_07_and_10")

add_executable(${T_THIS}
    e06_e07_e10_main.h e06_e07_e10_main.cpp
    roman/roman.h roman/roman.cpp
    help/help.h help/help.cpp
    calc/calc.h calc/calc.cpp calc/filepaths.cpp
    test/test_roman.h test/test_roman.cpp
    test/test_calc.h test/test_calc.cpp
)

file(COPY data DESTINATION .)
