message("Processing /exercise/e01...")

set(T_THIS "Chapter_11_exercise_01")

add_executable(${T_THIS}
    e01.h e01.cpp
    ../../lib/help.h ../../lib/help.cpp
)

file(COPY data DESTINATION .)
