message("Processing /exercise/e10...")

set(T_THIS "Chapter_14_exercise_10")

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
    
    ../share/help/helpers.cpp ../share/help/helpers.h
    ../share/anim/anim_shp.cpp ../share/anim/anim_shp.h
    ../share/grp/grp_shp.cpp ../share/grp/grp_shp.h
    
    ../share/geo/box.cpp ../share/geo/box.h
    ../share/geo/box_helpers.cpp ../share/geo/box_helpers.h
    ../share/geo/pac.h ../share/geo/pac.cpp

    e10.cpp
    e10.h
    e10_anim.cpp e10_anim.h
    e10_pswin.h e10_pswin.cpp
    e10_pnp.h e10_pnp.cpp
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
