#define _USE_MATH_DEFINES
#include "../../lib/Window.h"
#include "../share/barch_helpers.h"
#include "../share/chart/bar_chart.h"

// Chapter 15, exercise 6 to 8: Bar charts

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

//------------------------------------------------------------------------------

void e06()
{
	fl_color(default_color().as_int());

	constexpr int win_w{640};
	constexpr int win_h{320};
	const std::string win_lb{"Wuthering"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	chart::Bar_chart bc{{16, 16}, win_w - 32, win_h - 32};
	bc.set_title("People grouped by their height");
	bc.set_x_title("Height (cm)");
	bc.show_grid_lines();
	barch_hlp::add_name_value_pairs_from_file(bc, "heights.txt");
	bc.set_unit(5);
	bc.set_fill_colors({Graph_lib::Color::blue,
	                    Graph_lib::Color::dark_blue,
	                    Graph_lib::Color::yellow});
	bc.set_max_value(25);
	win.attach(bc);

	Graph_lib::gui_main();
}

//------------------------------------------------------------------------------

int main()
try {
	e06();
	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
	return 2;
}
