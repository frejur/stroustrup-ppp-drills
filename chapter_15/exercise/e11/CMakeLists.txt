message("Processing /exercise/e11...")

set(T_THIS "Chapter_15_exercise_11")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp

    e11.cpp e11.h
    e11_helpers.cpp
    
    ../share/chart/series.cpp
    ../share/chart/legend.h ../share/chart/legend.cpp
    ../share/chart/plot_pt_shp.cpp
    ../share/chart/chart.h ../share/chart/chart.cpp
    ../share/chart/canvas.h ../share/chart/canvas.cpp
    ../share/chart/bar_chart.h ../share/chart/bar_chart.cpp
    ../share/chart/bar.cpp
    ../share/chart/bar_pair.cpp 
    ../share/chart/line_chart.h ../share/chart/line_chart.cpp
    ../share/chart/elem.h ../share/chart/elem.cpp
    ../share/ch15_helpers.h ../share/ch15_helpers.cpp
    ../share/parse/nval_pair.h ../share/parse/nval_pair.cpp
    ../share/parse/csv_parser.h ../share/parse/csv_parser.cpp
)

configure_file(txt/boston_avg_temp.txt boston_avg_temp.txt COPYONLY)
configure_file(txt/montreal_avg_temp.txt montreal_avg_temp.txt COPYONLY)
configure_file(txt/montreal_boston_streets.txt montreal_boston_streets.txt COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
