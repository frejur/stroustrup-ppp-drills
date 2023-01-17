cmake_minimum_required(VERSION 3.2)
project(gui_test_proj
    VERSION 0.0.1
    LANGUAGES C CXX
)
set(VERBOSE ON)

find_package(FLTK REQUIRED NO_MODULE)


message(STATUS "FLTK_INCLUDE_DIRS = '${FLTK_INCLUDE_DIRS}'")

add_executable(gui_test
    WIN32
    Graph.h
    Graph.cpp
    Window.h
    Window.cpp
    GUI.h
    GUI.cpp
    Simple_window.h
    Simple_window.cpp
    test.cpp
)

target_link_libraries(gui_test PUBLIC fltk fltk_images fltk_forms fltk_gl)
target_include_directories(gui_test PUBLIC ${FLTK_INCLUDE_DIRS})
