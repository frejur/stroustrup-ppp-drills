message("Processing /exercise/e01...")

set (T_THIS "Chapter_16_exercise_01")

add_executable(${T_THIS}
    e01.cpp
    my_win.h my_win.cpp
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
