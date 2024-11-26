message("Processing /exercise/e10...")

set(T_THIS "Chapter_12_exercise_10")

add_executable(${T_THIS}
    ../../lib/Graph.h
    ../../lib/Graph.cpp
    ../../lib/GUI.h
    ../../lib/GUI.cpp
    ../../lib/Point.h
    ../../lib/std_lib_facilities.h
    ../../lib/Window.h
    ../../lib/Window.cpp
    ../../lib/Simple_window.cpp
    ../../lib/Simple_window.h
    e10.cpp
    arrow.cpp
    arrow.h
    graph_box.cpp
    graph_box.h
    new_win.cpp
    new_win.h
)

# Dynamically copy the html folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/html
        $<TARGET_FILE_DIR:${T_THIS}>/html_e10
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
