message("Processing /exercise/e17...")

set(T_THIS "Chapter_14_exercise_17")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/Simple_window.cpp
    ../../lib/Simple_window.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp
    ../../lib/Debug_window.h
    ../share/help/helpers.h ../share/help/helpers.cpp
    ../share/geo/box.h ../share/geo/box.cpp
    ../share/geo/box_helpers.h ../share/geo/box_helpers.cpp

    e17.cpp
    shp_distr.h shp_distr.cpp
    nodes.h nodes.cpp
    e17_helpers.h e17_helpers.cpp
    distr_ctrl.h distr_ctrl.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
