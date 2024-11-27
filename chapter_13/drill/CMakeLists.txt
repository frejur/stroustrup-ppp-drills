message("Processing /drill...")

set(T_THIS "Chapter_13_drill")

add_executable(${T_THIS}
    ../lib/Graph.h
    ../lib/Graph.cpp
    ../lib/GUI.h
    ../lib/GUI.cpp
    ../lib/Point.h
    ../lib/Simple_window.cpp
    ../lib/Simple_window.h
    ../lib/std_lib_facilities.h
    ../lib/Window.h
    ../lib/Window.cpp
    drill.h
    drill.cpp
)

# Dynamically copy the img folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/img
        $<TARGET_FILE_DIR:${T_THIS}>/img_drill
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
