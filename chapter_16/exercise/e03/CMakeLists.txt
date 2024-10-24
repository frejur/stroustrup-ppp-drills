message("Processing /exercise/e03...")

set (T_THIS "Chapter_16_exercise_03")

add_executable(${T_THIS}
    e03.cpp
    my_win.h my_win.cpp 
    ../share/shape_button.h ../share/shape_button.cpp
    ../share/image_button.h ../share/image_button.cpp
    ../share/shape_button_state.cpp
    ../share/text_box.cpp
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

configure_file(img/honeycomb_80_32.jpg honeycomb_80_32.jpg COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
