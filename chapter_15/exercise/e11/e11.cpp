#define _USE_MATH_DEFINES
#include "e11.h"
#include "../../lib/Window.h"
#include "../share/barch_helpers.h"
#include "../share/chart/bar_chart.h"
#include "../share/chart/legend.h"
#include "../share/chart/line_chart.h"
#include <vector>

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
//------------------------------------------------------------------------------

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

inline const Graph_lib::Line_style& graphed_line_style()
{
	static const Graph_lib::Line_style
	    s{Graph_lib::Line_style::Line_style_type::solid, 3};
	return s;
};

inline const Graph_lib::Color& montreal_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::green};
	return c;
};

inline const Graph_lib::Color& boston_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::dark_blue};
	return c;
};

inline const std::string& montreal_temperatures_filename()
{
	static const std::string s{"txt_e11/montreal_avg_temp.txt"};
	return s;
};

inline const std::string& boston_temperatures_filename()
{
	static const std::string s{"txt_e11/boston_avg_temp.txt"};
	return s;
};

inline const std::string& streets_csv_filename()
{
	static const std::string s{"txt_e11/montreal_boston_streets.txt"};
	return s;
};

//------------------------------------------------------------------------------

void ch15_e11::e11()
{
	fl_color(default_color().as_int());

	constexpr int win_w{640 * 2};
	constexpr int win_h{320};
	const std::string win_lb{"Hot! Man-named top-names"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	// Avg. temperature Line graph
	chart::Line_chart lc{{16, 16}, win_w / 2 - 32, win_h - 32};
	lc.set_title("Average monthly temperature");
	lc.set_y_title("Temperature (C)");
	lc.set_x_title("January - December");
	lc.hide_x_values();
	std::vector<Value_pair> avg_temp{
	    merge_files_into_name_value_pairs(montreal_temperatures_filename(),
	                                      boston_temperatures_filename())};
	std::vector<double> temp_montreal;
	std::vector<double> temp_boston;
	for (Value_pair p : avg_temp) {
		temp_montreal.push_back({p.value_a});
		temp_boston.push_back({p.value_b});
	}
	lc.add("Montreal", 1, 1, temp_montreal, montreal_color());
	lc.add("Boston", 1, 1, temp_boston, boston_color());
	lc.set_x_unit(1);
	lc.set_y_unit(5);
	lc.set_x_max_value(13);
	lc.set_y_min_value(-10);
	lc.set_y_max_value(25);
	lc.show_horizontal_grid_lines();
	lc.set_style_by_index(graphed_line_style(), 0);
	lc.set_style_by_index(graphed_line_style(), 1);
	win.attach(lc);

	// Street lengths bar chart
	CSV_parser csv_p{streets_csv_filename()};
	std::vector<Name_value_value_triplet> streets{
	    get_name_value_value_triplets(csv_p,
	                                  "Street_name",
	                                  "Montreal",
	                                  "Boston")};
	chart::Bar_chart bc{{win_w / 2 + 16, 16}, win_w / 2 - 32, win_h - 32};
	bc.set_title("Street lengths");
	bc.set_y_title("Length (m)");
	bc.show_grid_lines();
	bc.set_unit(50);
	bc.set_bars_padding(32);
	for (const Name_value_value_triplet& t : streets) {
		bc.disable_automatic_refresh();
		bc.add(t.name, t.value_a, t.value_b);
		bc.enable_automatic_refresh();
		bc.refresh();
	}

	bc.set_fill_colors({montreal_color(), boston_color()});
	win.attach(bc);

	//	Add legend
	constexpr int lbox_x{win_w / 2};
	constexpr int lbox_y{16};
	chart::Legend_box lbox_col{{lbox_x, lbox_y},
	                           18,
	                           chart::Legend_flow::Horizontal};
	lbox_col.add_color_legend("Montreal", montreal_color());
	lbox_col.add_color_legend("Boston", boston_color());
	int lbox_col_w{lbox_col.width()};
	int lbox_col_half_w{static_cast<int>(std::round(lbox_col_w * 0.5))};
	lbox_col.move(-lbox_col_half_w, 0);
	win.attach(lbox_col);

	Graph_lib::gui_main();
}

//------------------------------------------------------------------------------

int main()
try {
	ch15_e11::e11();
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
