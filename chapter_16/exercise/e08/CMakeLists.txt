message("Processing /exercise/e08...")

set (T_THIS "Chapter_16_exercise_08")

add_executable(${T_THIS}
    e08.cpp
    my_win.h my_win.cpp 
    my_win_cb.cpp
    
    # Parse currencies and exchange rates
    parse_xrate.h parse_xrate.cpp
    
    ../share/dropd.h ../share/dropd.cpp
    
    ../share/shape_button.h ../share/shape_button.cpp
    ../share/image_button.h ../share/image_button.cpp
    ../share/shape_button_state.cpp
    ../share/text_box.cpp
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp
    
    ../share/money/exchangerate.cpp
    ../share/money/exchangerate.h
    ../share/money/monetarymath.cpp
    ../share/money/money.cpp
    ../share/money/money.h
    ../share/money/moneyhelpers.cpp
    ../share/money/moneyhelpers.h
    ../share/money/table.cpp
    
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

# Dynamically copy the img and txt folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/img
        $<TARGET_FILE_DIR:${T_THIS}>/img_e08
)
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/txt
        $<TARGET_FILE_DIR:${T_THIS}>/txt_e08
)


target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
