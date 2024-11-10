message("Processing /exercise/e09...")

set (T_THIS "Chapter_16_exercise_09")

add_executable(${T_THIS}
    e09.cpp
    my_win.h my_win.cpp 
    in_out_ctrl.h in_out_ctrl.cpp
    calc.h calc.cpp calc_btn.cpp
    cb_id.h cb_id.cpp
    cb_mgr.h cb_mgr.cpp
    mask_offs.cpp
    setup_btn.cpp
    setup_edit.cpp
    
    # Expression parser
    expr_parser/calc/calc.cpp expr_parser/calc/calc.h
    expr_parser/help/help.cpp expr_parser/help/help.h
    
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

configure_file(img/calc_icons.png calc_icons.png COPYONLY)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
