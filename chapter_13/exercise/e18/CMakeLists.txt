message("Processing /exercise/e18...")

set(T_THIS "Chapter_13_exercise_18")

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

    e18.cpp
    poly.h
    
    dynpoly.h
    dynpoly.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
