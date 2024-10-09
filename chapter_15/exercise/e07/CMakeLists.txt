message("Processing /exercise/e07...")

set(T_THIS "Chapter_15_exercise_07")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp

    e07.cpp
    
    ../share/bar_chart.h ../share/bar_chart.cpp
    ../share/bar.cpp
    ../share/ch15_helpers.h ../share/ch15_helpers.cpp
    ../share/nval_pair.h ../share/nval_pair.cpp
    ../share/csv_parser.h ../share/csv_parser.cpp
)

configure_file(csv/nba_player_stats_2014_2015.csv nba_player_stats_2014_2015.csv COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
