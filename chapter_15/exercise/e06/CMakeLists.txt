message("Processing /exercise/e06...")

set(T_THIS "Chapter_15_exercise_06")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp

    e06.cpp
    
    ../share/bar_chart.h ../share/bar_chart.cpp
    ../share/bar.cpp
    ../share/ch15_helpers.h ../share/ch15_helpers.cpp
    ../share/nval_pair.h ../share/nval_pair.cpp
)

configure_file(txt/heights.txt heights.txt COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
