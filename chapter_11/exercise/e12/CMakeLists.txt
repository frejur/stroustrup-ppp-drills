message("Processing /exercise/e12...")

set(T_THIS "Chapter_11_exercise_12_and_13")

add_executable(${T_THIS}
    e12.cpp
    ../../lib/help.h ../../lib/help.cpp
)


file(COPY data DESTINATION .)
