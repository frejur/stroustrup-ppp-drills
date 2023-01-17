cmake_minimum_required(VERSION 3.2)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
project(gui_test
    VERSION 0.0.1
    LANGUAGES C CXX
)

add_compile_options(-std=gnu++17)
add_compile_options(-static)


add_executable(gui_test.exe
    WIN32
    Graph.h
    Graph.cpp
    # Window.h
    # Window.cpp
    # GUI.h
    # GUI.cpp
    Simple_window.h
    Simple_window.cpp
    test.cpp
)

target_link_options(gui_test.exe PUBLIC "-mwindows")
target_link_options(gui_test.exe PUBLIC "-Lc:/ucrt64/lib")
target_link_options(gui_test.exe PUBLIC "-lfltk")
target_link_options(gui_test.exe PUBLIC "-lole32")
target_link_options(gui_test.exe PUBLIC "-luuid")
target_link_options(gui_test.exe PUBLIC "-lcomctl32")
target_link_options(gui_test.exe PUBLIC "-lws2_32")
target_link_options(gui_test.exe PUBLIC "-pipe")
target_link_options(gui_test.exe PUBLIC "-Wl,-subsystem,windows")
