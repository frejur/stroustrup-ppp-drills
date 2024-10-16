#define _USE_MATH_DEFINES
#include "e10.h"
#include "../../lib/Window.h"
#include "../share/chart/scatter_plot.h"
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

static const std::vector<Graph_lib::Color>& pokemon_region_colors()
{
	static const std::vector<Graph_lib::Color> c{Graph_lib::Color::green,
	                                             Graph_lib::Color::dark_blue,
	                                             Graph_lib::Color::yellow,
	                                             Graph_lib::Color::dark_magenta,
	                                             Graph_lib::Color::cyan,
	                                             Graph_lib::Color::white};
	return c;
}

Graph_lib::Color color_by_region(const chart::Plot_point& pt)
{
	const std::string reg{
	    dynamic_cast<const ch15_e10::Pokemon_plot_point&>(pt).region()};
	Graph_lib::Color col = Graph_lib::Color::black;
	int count = 0;
	int match = -1;
	for (const std::string& r : pokemon_regions()) {
		if (r == reg) {
			match = count;
			break;
		}
		++count;
	}
	if (match != -1) {
		col = pokemon_region_colors()[match];
	}
	return col;
}

chart::Point_shape_type shape_type_by_legendary(const chart::Plot_point& pt)
{
	const bool is_leg{
	    dynamic_cast<const ch15_e10::Pokemon_plot_point&>(pt).is_legendary()};
	return (is_leg) ? chart::Point_shape_type::Diamond
	                : chart::Point_shape_type::Circle;
}

//------------------------------------------------------------------------------

void ch15_e10::e10()
{
	fl_color(default_color().as_int());

	constexpr int win_w{1024};
	constexpr int win_h{780};
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

	chart::Scatter_plot sp{{16, 16}, win_w - 32, win_h - 32};
	sp.set_title("Pokemon base stats");
	sp.set_x_title("Attack + Sp. Attack");
	sp.set_y_title("Defence + Sp. Defence");
	sp.show_horizontal_grid_lines();
	sp.show_vertical_grid_lines();
	sp.set_x_unit(100);
	sp.set_y_unit(100);
	sp.set_x_min_value(0);
	sp.set_y_min_value(0);
	sp.set_x_max_value(425);
	sp.set_y_max_value(475);
	sp.set_plot_point_size(12);
	sp.set_color_callback(color_by_region);
	sp.set_shape_type_callback(shape_type_by_legendary);
	add_pokemon_plot_points_from_file(sp, plot_points_filename());
	win.attach(sp);

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
