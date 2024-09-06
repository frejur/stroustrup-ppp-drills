message("Processing /exercise/e09...")

set(T_THIS "Chapter_14_exercise_09")

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

    ../share/geo/regularpoly.cpp ../share/geo/regularpoly.h
    ../share/help/helpers.cpp ../share/help/helpers.h
    ../share/anim/anim_shp.cpp ../share/anim/anim_shp.h
    
    e09.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
