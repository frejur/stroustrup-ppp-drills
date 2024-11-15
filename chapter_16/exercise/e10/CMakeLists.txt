message("Processing /exercise/e10...")

set (T_THIS "Chapter_16_exercise_10")

add_executable(${T_THIS}
    e10.cpp
    my_win.h my_win.cpp
    
    valid_in.h valid_in.cpp
    valid_int_mm.h valid_int_mm.cpp
    valid_dbl_mm.h valid_dbl_mm.cpp
    step_in.h step_in.cpp
    step_in_int.h step_in_int.cpp
    step_in_dbl.h step_in_dbl.cpp
    tgl.h tgl.cpp
    
    # Canvas
    ../share/canvas/canvas.cpp ../share/canvas/canvas.h
    
    # Shape_button
    ../share/shape_button.h ../share/shape_button.cpp
    ../share/image_button.h ../share/image_button.cpp
    ../share/shape_button_state.cpp
    ../share/text_box.cpp
    
    # Helpers
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp

    # Graph_lib
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
