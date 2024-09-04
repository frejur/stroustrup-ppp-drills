message("Processing /exercise/e02...")

set(T_THIS "Chapter_14_exercise_02")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    e02.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
