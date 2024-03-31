message("Processing /exercise/e09...")

set(T_THIS "Chapter_11_exercise_09")

add_executable(${T_THIS}
    e09.cpp
)

file(COPY data DESTINATION .)
