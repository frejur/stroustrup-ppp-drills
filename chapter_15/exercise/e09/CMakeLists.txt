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
    
    ../share/barch_helpers.h ../share/barch_helpers.cpp
    ../share/chart/chart.h ../share/chart/chart.cpp
    ../share/chart/canvas.h ../share/chart/canvas.cpp
    ../share/chart/bar_chart.h ../share/chart/bar_chart.cpp
    ../share/chart/bar.cpp
    ../share/chart/bar_pair.cpp
    ../share/chart/elem.h ../share/chart/elem.cpp
    ../share/ch15_helpers.h ../share/ch15_helpers.cpp
    ../share/parse/nval_pair.h ../share/parse/nval_pair.cpp
    ../share/parse/csv_parser.h ../share/parse/csv_parser.cpp
)

# Dynamically copy the csv folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/csv
        $<TARGET_FILE_DIR:${T_THIS}>/csv_e09
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
