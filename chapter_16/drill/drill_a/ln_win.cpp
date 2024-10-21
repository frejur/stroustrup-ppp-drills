#include "ln_win.h"
#include <sstream>

using Graph_lib::Address;

Lines_window::Lines_window(Graph_lib::Point xy,
                           int w,
                           int h,
                           const string& title)
    : Graph_lib::Window{xy, w, h, title}
    , next_button{Graph_lib::Point{x_max() - 150, 0},
                  70,
                  20,
                  "Next point",
                  [](Address, Address pw) {
	                  Graph_lib::reference_to<Lines_window>(pw).next();
                  }}
    , quit_button{Graph_lib::Point{x_max() - 70, 0},
                  70,
                  20,
                  "Quit",
                  [](Address, Address pw) {
	                  Graph_lib::reference_to<Lines_window>(pw).quit();
                  }}
    , next_x{Graph_lib::Point{x_max() - 310, 0}, 50, 20, "Next x:"}
    , next_y{Graph_lib::Point{x_max() - 210, 0}, 50, 20, "Next y:"}
    , xy_out{Graph_lib::Point{100, 0}, 100, 20, "Current (x, y):"}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);
}

void Lines_window::quit()
{
	hide(); // FLTK terminology for closing / deleting the window
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();

	lines.add(Graph_lib::Point{x, y});

	// Update current position readout
	std::ostringstream os;
	os << '(' << x << ", " << y << ')';
	xy_out.put(os.str());

	redraw();
}
