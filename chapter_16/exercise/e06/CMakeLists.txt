message("Processing /exercise/e06...")

set (T_THIS "Chapter_16_exercise_6")


add_executable(${T_THIS}
    e06.cpp
    my_win.h my_win.cpp
    clock_face.h clock_face.cpp

    # Shared
    ../share/win/anim_win.h ../share/win/anim_win.cpp
    ../share/geo/arrow.h ../share/geo/arrow.cpp
    ../share/ch16_helpers.h ../share/ch16_helpers.cpp
    ../share/outlined_text.h
    
    # Graph_lib
    ../../lib/Graph.h ../../lib/Graph.cpp
    ../../lib/GUI.h ../../lib/GUI.cpp
    ../../lib/Window.h ../../lib/Window.cpp
    ../../lib/Point.h
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_forms fltk_images)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
