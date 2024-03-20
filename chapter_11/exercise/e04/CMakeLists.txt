message("Processing /exercise/e04...")

set(T_THIS "Chapter_11_exercise_04")

add_executable(${T_THIS}
    e04.h e04.cpp
    ../../lib/help.h ../../lib/help.cpp
)

file(COPY data DESTINATION .)
