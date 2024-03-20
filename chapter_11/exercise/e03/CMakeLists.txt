message("Processing /exercise/e03...")

set(T_THIS "Chapter_11_exercise_03")

add_executable(${T_THIS}
    e03.h e03.cpp
    ../../lib/help.h ../../lib/help.cpp
)

file(COPY data DESTINATION .)
