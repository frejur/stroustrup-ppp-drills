message("Processing /exercise/e04...")

set (T_THIS "Chapter_16_exercise_04")

add_executable(${T_THIS}
    e04.cpp
    my_win.h my_win.cpp 
    my_win_create_shape.cpp
    button_grid.h button_grid.cpp
    
    # Shared
    ../share/shape_button.h ../share/shape_button.cpp
    ../share/shape_button_state.cpp
    ../share/text_box.cpp
    ../share/image_button.h ../share/image_button.cpp
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp
    ../share/geo/arrow.h ../share/geo/arrow.cpp
    ../share/geo/regularpoly.h ../share/geo/regularpoly.cpp
    ../share/help/helpers.h ../share/help/helpers.cpp
    
    # FLTK
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

# Dynamically copy the img folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/img
        $<TARGET_FILE_DIR:${T_THIS}>/img_e04
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
