message("Processing /exercise/e06...")

set(T_THIS "Chapter_11_exercise_06_to_08")

add_executable(${T_THIS}
    e06.h e06.cpp
    ../../lib/help.h ../../lib/help.cpp
    dstr/dstr.h dstr/dstr.cpp
    dict/dict.h dict/dict.cpp
)

file(COPY data DESTINATION .)
