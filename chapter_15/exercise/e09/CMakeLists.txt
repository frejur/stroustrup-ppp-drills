message("Processing /exercise/e09...")

set(T_THIS "Chapter_15_exercise_09")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp

    e09.h e09.cpp
    e09_helpers.cpp
    
    ../share/barch_helpers.h ../share/barcH_helpers.cpp
    ../share/chart/chart.h ../share/chart/chart.cpp
    ../share/chart/canvas.h ../share/chart/canvas.cpp
    ../share/chart/bar_chart.h ../share/chart/bar_chart.cpp
    ../share/chart/bar.cpp
    ../share/chart/elem.h ../share/chart/elem.cpp
    ../share/ch15_helpers.h ../share/ch15_helpers.cpp
    ../share/parse/nval_pair.h ../share/parse/nval_pair.cpp
    ../share/parse/csv_parser.h ../share/parse/csv_parser.cpp
)

configure_file(csv/nba_player_stats_2014_2015.csv nba_player_stats_2014_2015.csv COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
