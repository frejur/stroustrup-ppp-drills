message("Processing /drill...")

set(T_THIS "Chapter_15_drill")

add_executable(${T_THIS}
    drill.cpp
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
    ../lib/Debug_window.h
)

target_link_libraries(${T_THIS} PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(${T_THIS} PUBLIC ${FLTK_INCLUDE_DIRS})
