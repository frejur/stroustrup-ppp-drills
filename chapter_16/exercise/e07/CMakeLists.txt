message("Processing /exercise/e07...")

set (T_THIS "Chapter_16_exercise_7")


add_executable(${T_THIS}
    e07.cpp
    my_win.h my_win.cpp
    prg_bar.h prg_bar.cpp
    pickup.cpp pickup.h

    # Shared
    ../share/win/anim_win.h ../share/win/anim_win.cpp
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp
    ../share/outlined_text.h
    
    # Graph_lib
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
        $<TARGET_FILE_DIR:${T_THIS}>/img_e07
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
