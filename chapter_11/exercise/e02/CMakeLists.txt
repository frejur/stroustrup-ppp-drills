message("Processing /exercise/e02...")

set(T_THIS "Chapter_11_exercise_02")

add_executable(${T_THIS}
    e02.h e02.cpp
    ../../lib/help.h ../../lib/help.cpp
    pstr/punct_stream.h pstr/punct_stream.cpp
)

file(COPY data DESTINATION .)
