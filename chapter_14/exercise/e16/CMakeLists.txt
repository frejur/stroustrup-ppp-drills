message("Processing /exercise/e16...")

set(T_THIS "Chapter_14_exercise_16")

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

    ../share/anim/anim_shp.cpp ../share/anim/anim_shp.h
    ../share/grp/grp_shp.cpp ../share/grp/grp_shp.h
    ../share/geo/pac.cpp ../share/geo/pac.h
    ../share/geo/box.cpp ../share/geo/box.h
    ../share/help/helpers.cpp ../share/help/helpers.h

    e16.cpp
    controller.h controller.cpp
    ctrl_obj.h ctrl_obj.cpp
    maze.h maze.cpp
    maze_anim.h maze_anim.cpp
)

configure_file(txt/lvl_01.txt lvl_01.txt COPYONLY)
configure_file(txt/lvl_02.txt lvl_02.txt COPYONLY)
configure_file(txt/lvl_03.txt lvl_03.txt COPYONLY)
configure_file(txt/lvl_04.txt lvl_04.txt COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
