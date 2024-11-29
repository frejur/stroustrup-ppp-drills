message("Processing /exercise/e16...")

set(T_THIS "Chapter_14_exercise_16")

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
    ../../lib/Debug_window.h

    ../share/anim/anim_shp.cpp ../share/anim/anim_shp.h
    ../share/grp/grp_shp.cpp ../share/grp/grp_shp.h
    ../share/geo/pac.cpp ../share/geo/pac.h
    ../share/geo/box.cpp ../share/geo/box.h
    ../share/help/helpers.cpp ../share/help/helpers.h

    e16.cpp
    controller.h controller.cpp
    ctrl_obj.h ctrl_obj.cpp
    maze.h maze.cpp
    maze_anim.h maze_anim.cpp
)

# Dynamically copy the txt folder into the same
# directory as the executable
add_custom_command(TARGET ${T_THIS} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/txt
        $<TARGET_FILE_DIR:${T_THIS}>/txt_e16
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
