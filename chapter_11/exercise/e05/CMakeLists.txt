message("Processing /exercise/e05...")

set(T_THIS "Chapter_11_exercise_05")

add_executable(${T_THIS}
    e05.h e05.cpp
    ../../lib/help.h ../../lib/help.cpp
    chcl/chcl.h chcl/chcl.cpp
)

file(COPY data DESTINATION .)
