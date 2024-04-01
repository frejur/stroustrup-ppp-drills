message("Processing /exercise/e15...")

set(T_THIS "Chapter_11_exercise_15_and_16")

add_executable(${T_THIS}
    e15.cpp
    ../../lib/help.h ../../lib/help.cpp
)


file(COPY data DESTINATION .)
