message("Processing /exercise/e17...")

set(T_THIS "Chapter_13_exercise_17")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp
    ../../lib/Simple_window.cpp
    ../../lib/Simple_window.h
    ../../lib/Debug_window.h
    ../share/geo/isoscelestriangle.h
    ../share/geo/isoscelestriangle.cpp
    ../share/geo/righttriangle.h
    ../share/geo/regularpoly.h
    ../share/geo/regularpoly.cpp
    ../share/geo/regularhexagon.h
    ../share/geo/regularhexagon.cpp
    ../share/help/coordinate_system.h
    ../share/help/inters.h
    ../share/tiler/dyntile.h
    ../share/tiler/dyntile.cpp
    ../share/tiler/tiler.h
    ../share/tiler/tiler.cpp

    e17.cpp
    hexagontiler.h
    hexagontiler.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
