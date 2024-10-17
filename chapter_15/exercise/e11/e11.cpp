#define _USE_MATH_DEFINES
#include "../../lib/Window.h"
#include "../share/barch_helpers.h"
#include "../share/chart/bar_chart.h"

// Chapter 15, exercise 11: Graph the average temperatures for each month of the
//                          year for two cities with identical names but
//                          different locations.
// Notes:
// - It seems like the aim of this exercise is to compare two continuous
//   series of data by superimposing them on the same graph / canvas.
// - This program stays true to this core concept, but instead, draws two graphs
//   with a different subject matter:
//   1. A combined Bar chart that plots the length of a number of streets that
//      share the same name, but are located in either:
//          > Montreal, Canada
//          > Boston, USA
//      The streets are:
//          > Acorn Street
//          > King Street
//          > Bishop Street
//          > Queen Street
//          > Oxford Street
//   2. A Line chart that plots the monthly average temperatures of:
//          > Montreal, Canada
//          > Boston, USA
inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

//------------------------------------------------------------------------------

void e11()
{
	fl_color(default_color().as_int());

	constexpr int win_w{640};
	constexpr int win_h{320};
	const std::string win_lb{"Hot! Man-named top-names"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	Graph_lib::gui_main();
}

//------------------------------------------------------------------------------

int main()
try {
	e11();
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
