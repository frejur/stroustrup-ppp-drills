message("Processing /exercise/e09...")

set(T_THIS "Chapter_10_exercise_09")

add_executable(${T_THIS}
    e09.cpp
    e09.h
)

file(COPY data DESTINATION .)
