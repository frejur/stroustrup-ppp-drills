message("Processing /drill/drill_a...")

set (T_THIS "Chapter_16_drill_A")

add_executable(${T_THIS}
    drill.cpp
    ln_win.h ln_win.cpp
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
