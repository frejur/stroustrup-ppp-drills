#include "my_win.h"

namespace {

} // namespace

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Graph_lib::Window::Window(xy, w, h, title)
    , bg({0, 0}, "ouija.png")
{
	attach(bg);
}
