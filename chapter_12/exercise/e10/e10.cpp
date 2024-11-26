#include "new_win.h"
#include "../../lib/Graph.h"
#include "graph_box.h"
#include "arrow.h"
#include <memory>
#include <vector>
#include <math.h>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Box.H>
/* Exercise 10. Draw the file diagram from 12.8. */


int main()
{
    const int grd { 24 };
    const int num_x { 38 };
    const int num_y { 36 };
    const int margin { 32 };
    const int ww { margin * 2 + num_x * grd };
    const int wh { margin * 2 + num_y * grd };
    New_window win { {100, 100}, ww, wh, "File diagram" };

    // Top row --------------------------------------------
    GraphBox box_pt_h {
        4, 4, 10, 3, grd, margin,
        "html_e10/point_h.html", "Point.h:" };
    win.attach(box_pt_h);

    Point pt_pt_h_btm_c {
        box_pt_h.getBoundsPosition(2.5) };

    Point pt_pt_h_btm_r {
        box_pt_h.getBoundsPosition(2.2)};

    GraphBox box_hdr {
        20, 1, 7, 3, grd, margin,
        "html_e10/fltk_headers.html", "", true };
    win.attach(box_hdr);

    Point pt_hdr_btm_l { box_hdr.getBoundsPosition(2.9) };
    Point pt_hdr_btm_c { box_hdr.getBoundsPosition(2.5) };
    Point pt_hdr_btm_r { box_hdr.getBoundsPosition(2.1) };
    Point pt_hdr_r { box_hdr.getBoundsPosition(1.5) };

    GraphBox box_code {
        31, 4, 6, 3, grd, margin,
        "html_e10/fltk_code.html", "", true };
    win.attach(box_code);

    Arrow arr_code_to_hdr {
        box_code.getBoundsPosition(3.5),
        pt_hdr_r };
    win.attach(arr_code_to_hdr);

    // 2nd row --------------------------------------------
    GraphBox box_graph_h {
        4, 12, 11, 4, grd, margin,
        "html_e10/graph_h.html", "Graph.h:" };
    win.attach(box_graph_h);

    Point pt_graph_h_top_c {
        box_graph_h.getBoundsPosition(0.5) };

    Point pt_graph_h_btm_c {
        box_graph_h.getBoundsPosition(2.5) };

    Arrow arr_graph_h_to_pt_h {
        pt_graph_h_top_c,
        { pt_graph_h_top_c.x, pt_pt_h_btm_c.y } };

    win.attach(arr_graph_h_to_pt_h);

    Arrow arr_graph_h_to_hdr {
        pt_graph_h_top_c, pt_hdr_btm_l };

    win.attach(arr_graph_h_to_hdr);

    GraphBox box_win_h {
        18, 9, 10, 4, grd, margin,
        "html_e10/window_h.html", "Window.h:" };
    win.attach(box_win_h);

    Arrow arr_win_h_to_pt_h {
        box_win_h.getBoundsPosition(0.05),
        pt_pt_h_btm_r };
    win.attach(arr_win_h_to_pt_h);

    Arrow arr_win_h_to_hdr {
        { pt_hdr_btm_c.x,
          box_win_h.getBoundsPosition(0).y },
        pt_hdr_btm_c };
    win.attach(arr_win_h_to_hdr);

    Point pt_win_h_btm_l {
        box_win_h.getBoundsPosition(2.75)
    };

    Point pt_win_h_btm_r {
        box_win_h.getBoundsPosition(2.075)
    };

    // 3rd row --------------------------------------------
    GraphBox box_win_cpp {
        12, 19, 8, 3, grd, margin,
        "html_e10/window_cpp.html", "Window.cpp:" };
    win.attach(box_win_cpp);

    Arrow arr_win_cpp_to_win_h {
        box_win_cpp.getBoundsPosition(0.75),
        pt_win_h_btm_l };
    win.attach(arr_win_cpp_to_win_h);

    GraphBox box_gui_h {
        27, 16, 10, 4, grd, margin,
        "html_e10/gui_h.html", "GUI.h:" };
    win.attach(box_gui_h);

    Point pt_gui_h_top_c {
        box_gui_h.getBoundsPosition(0.65) };
    Point pt_gui_h_btm_l {
        box_gui_h.getBoundsPosition(2.9) };
    Point pt_gui_h_btm_c {
        box_gui_h.getBoundsPosition(2.5) };

    Arrow arr_pt_gui_h_to_win_h {
        pt_gui_h_top_c, pt_win_h_btm_r };
    win.attach(arr_pt_gui_h_to_win_h);

    Arrow arr_pt_gui_h_to_hdr {
        pt_gui_h_top_c, pt_hdr_btm_r };
    win.attach(arr_pt_gui_h_to_hdr);

    // 4th row --------------------------------------------
    GraphBox box_graph_cpp {
        1, 23, 7, 3, grd, margin,
        "html_e10/graph_cpp.html", "Graph.cpp:" };
    win.attach(box_graph_cpp);

    Arrow arr_graph_cpp_to_graph_h {
        box_graph_cpp.getBoundsPosition(0.8),
        { pt_graph_h_btm_c.x - (int)std::round(grd * 0.1),
          pt_graph_h_btm_c.y }
    };
    win.attach(arr_graph_cpp_to_graph_h);

    GraphBox box_s_win_h {
        14, 24, 13, 4, grd, margin,
        "html_e10/simple_window_h.html", "Simple_window.h" };
    win.attach(box_s_win_h);

    Point pt_s_win_h_top_r {
        pt_hdr_btm_c.x,
        box_s_win_h.getBoundsPosition(0).y };

    Point pt_s_win_h_btm_l {
        box_s_win_h.getBoundsPosition(2.8) };

    Arrow arr_s_win_h_to_win_h {
        pt_s_win_h_top_r,
        { pt_s_win_h_top_r.x, pt_win_h_btm_l.y }
    };
    win.attach(arr_s_win_h_to_win_h);

    Arrow arr_s_win_to_gui_h {
        pt_s_win_h_top_r, pt_gui_h_btm_l };
    win.attach(arr_s_win_to_gui_h);

    GraphBox box_gui_cpp {
        29, 23, 6, 3, grd, margin,
        "html_e10/gui_cpp.html", "GUI.cpp" };
    win.attach(box_gui_cpp);

    Arrow arr_gui_cpp_to_gui_h {
        box_gui_cpp.getBoundsPosition(0.75),
        pt_gui_h_btm_c };
    win.attach(arr_gui_cpp_to_gui_h);

    // Bottom row -----------------------------------------

    GraphBox box_ch12_cpp {
        9, 31, 12, 4, grd, margin,
        "html_e10/chapter12_cpp.html", "chapter12.cpp" };
    win.attach(box_ch12_cpp);

    Point pt_ch12_cpp_top_c {
        box_ch12_cpp.getBoundsPosition(0.45) };

    Arrow arr_ch12_cpp_to_graph_h {
        pt_ch12_cpp_top_c,
        { pt_graph_h_btm_c.x + (int)std::round(grd * 0.1),
          pt_graph_h_btm_c.y }
    };
    win.attach(arr_ch12_cpp_to_graph_h);

    Arrow arr_ch12_cpp_to_s_win_h {
        pt_ch12_cpp_top_c, pt_s_win_h_btm_l };
    win.attach(arr_ch12_cpp_to_s_win_h);

    return Fl::run();
}

