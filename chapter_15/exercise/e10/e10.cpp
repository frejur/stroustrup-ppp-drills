#define _USE_MATH_DEFINES
#include "e10.h"
#include "../../lib/Window.h"
#include "../share/ch15_helpers.h"
#include "../share/parse/csv_parser.h"

// Chapter 15, exercise 10: Collect data unsuitable for a Line or Bar Graph and
//                          plot it using a more sensible type of diagram.
//------------------------------------------------------------------------------

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

inline const std::string& csv_filename()
{
	static const std::string s{"pokemon.csv"};
	return s;
};

inline const std::string& plot_points_filename()
{
	static const std::string s{"pokemon_stats.txt"};
	return s;
};

//------------------------------------------------------------------------------

void ch15_e10::e10()
{
	fl_color(default_color().as_int());

	constexpr int win_w{640};
	constexpr int win_h{320};
	const std::string win_lb{"Scatter plot, I choose you!"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	CSV_parser csv_p{csv_filename()};
	Pokemon_column_names col_names{"Name",
	                               "Attack",
	                               "Defense",
	                               "Sp_Atk",
	                               "Sp_Def",
	                               "Generation",
	                               "Legendary"};
	std::vector<Pokemon_stats> stats{get_pokemon_stats(csv_p, col_names)};
	save_pokemon_stats_to_file(stats, plot_points_filename());
	/*

	chart::Bar_chart bc{{16, 16}, win_w - 32, win_h - 32};
	bc.set_title("Distributed height of NBA Players (2014-2015)");
	bc.set_x_title("Height (cm)");
	bc.show_grid_lines();
	ch15_hlp::add_name_value_pairs_from_file(bc, name_value_pairs_filename());
	bc.set_unit(5);
	bc.set_fill_colors({Graph_lib::Color::dark_blue,
	                    Graph_lib::Color::dark_red,
	                    Graph_lib::Color::dark_green});
	bc.sort_by_label(chart::Order::Asc);
	win.attach(bc);
*/

	Graph_lib::gui_main();
}

//------------------------------------------------------------------------------

int main()
try {
	ch15_e10::e10();
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
