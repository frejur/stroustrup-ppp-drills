message("Processing /exercise/e11...")

set(T_THIS "Chapter_10_exercise_11")

add_executable(${T_THIS}
    e11.cpp
    e11.h
)

file(COPY data DESTINATION .)
