message("Processing /exercise/e05...")

set (T_THIS "Chapter_16_exercise_5")

add_executable(${T_THIS}
    e05.cpp
    my_win.h my_win.cpp 
    my_win_create.cpp
    my_win_const.h my_win_const.cpp
    my_win_cb.cpp
    my_window_save.cpp my_win_load.cpp
    
    # Shared
    ../share/shape_button.h ../share/shape_button.cpp
    ../share/shape_button_state.cpp
    ../share/text_box.cpp
    ../share/outlined_text.h
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp
    
    # Graph_lib
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

# Dynamically copy the img and txt folders into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/img
        $<TARGET_FILE_DIR:${T_THIS}>/img_e05
)
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/txt
        $<TARGET_FILE_DIR:${T_THIS}>/txt_e05
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
