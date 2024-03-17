message("Processing /exercise/e08...")

set(T_THIS "Chapter_10_exercise_08")

add_executable(${T_THIS}
    e08.cpp
    e08.h
)

file(COPY data DESTINATION .)
