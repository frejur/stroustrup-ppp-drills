message("Processing /exercise/e07...")

set(T_THIS "Chapter_14_exercise_07")

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
    ../share/geo/strpe_rend.h ../share/geo/strpe_rend.cpp
    ../share/geo/strpe_rec.h ../share/geo/strpe_rec.cpp
    ../share/geo/strpe_circ.h ../share/geo/strpe_circ.cpp
    ../share/geo/strpe_pline.h ../share/geo/strpe_pline.cpp
    ../share/help/helpers.h ../share/help/helpers.cpp

	dynpline.h dynpline.cpp
    e07.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
