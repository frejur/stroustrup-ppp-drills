message("Processing /exercise/e01...")

set(T_THIS "Chapter_14_exercise_01")

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
    ../share/geo/arc.h
    ../share/geo/arc.cpp
    ../share/geo/isoscelestriangle.cpp
    ../share/geo/isoscelestriangle.h
    ../share/geo/star.cpp
    ../share/geo/star.h
    ../share/img/image_cutout.cpp
    ../share/img/image_cutout.h
    ../share/help/helpers.h
    ../share/help/helpers.cpp
    
    
    emoticons.h emoticons.cpp
    attire.h attire.cpp
    e01.cpp
    em_templates.h em_templates.cpp
)

configure_file(img/dots.jpg dots.jpg COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
