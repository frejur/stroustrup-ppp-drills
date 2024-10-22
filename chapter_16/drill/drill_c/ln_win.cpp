#include "ln_win.h"
#include <sstream>

using Graph_lib::Address;

Lines_window::Lines_window(Graph_lib::Point xy,
                           int w,
                           int h,
                           const string& title)
    : Graph_lib::Window{xy, w, h, title}
    , clr_menu(Graph_lib::Point{x_max() - 70, 40},
               70,
               20,
               Graph_lib::Menu::vertical,
               "color")
    , sty_menu(Graph_lib::Point{x_max() - 180, 40},
               70,
               20,
               Graph_lib::Menu::vertical,
               "style")
    , next_button{Graph_lib::Point{x_max() - 150, 0},
                  70,
                  20,
                  "Next point",
                  cb_next}
    , quit_button{Graph_lib::Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit}
    , clr_menu_button{Graph_lib::Point{x_max() - 80, 30},
                      80,
                      20,
                      "Color menu",
                      cb_clr_menu}
    , sty_menu_button{Graph_lib::Point{x_max() - 170, 30},
                      80,
                      20,
                      "Style menu",
                      cb_sty_menu}
    , next_x{Graph_lib::Point{x_max() - 310, 0}, 50, 20, "Next x:"}
    , next_y{Graph_lib::Point{x_max() - 210, 0}, 50, 20, "Next y:"}
    , xy_out{Graph_lib::Point{100, 0}, 100, 20, "Current (x, y):"}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("No Point");

	clr_menu.attach(
	    new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "red", cb_red});
	clr_menu.attach(
	    new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "blue", cb_blue});
	clr_menu.attach(
	    new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "black", cb_black});
	attach(clr_menu);

	clr_menu.hide();
	attach(clr_menu_button);

	sty_menu.attach(
	    new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "solid", cb_solid});
	sty_menu.attach(
	    new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "dotted", cb_dotted});
	sty_menu.attach(
	    new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "dashed", cb_dashed});
	attach(sty_menu);
	sty_menu.hide();
	attach(sty_menu_button);

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
