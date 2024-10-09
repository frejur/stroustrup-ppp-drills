#define _USE_MATH_DEFINES
#include "../../lib/Window.h"
#include "../share/bar_chart.h"
#include "../share/ch15_helpers.h"
#include "../share/csv_parser.h"

// Chapter 15, exercise 7: Bar chart from an external dataset.
//                         Like the prev. exercise, only using another set
//                         of values.

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

inline const std::string& csv_filename()
{
	static const std::string s{"nba_player_stats_2014_2015.csv"};
	return s;
};

inline const std::string& name_value_pairs_filename()
{
	static const std::string s{"nba_distr_h.txt"};
	return s;
};

//------------------------------------------------------------------------------

struct Distr_height
{
	int height;
	int count;
};

std::ostream& operator<<(std::ostream& os, const Distr_height h)
{
	os << "(\"" << h.height << "\", " << h.count << ')' << '\n';
	return os;
}

std::vector<Distr_height> get_distr_heights(CSV_parser& p,
                                            const std::string& column_name)
{
	std::vector<Distr_height> distr_h;
	p.perform_action_on({column_name},
	                    [&distr_h, &column_name](CSV_value_vector a) {
		                    double h{a.as_double(column_name)};
		                    if (h > 0) {
			                    int rounded_h{static_cast<int>(
			                        std::round(h * 2 / 10) * 10 / 2)};
			                    int match = -1;
			                    for (int i = 0; i < distr_h.size(); ++i) {
				                    if (rounded_h == distr_h[i].height) {
					                    match = i;
					                    break;
				                    }
			                    }
			                    if (match > -1) {
				                    ++distr_h[match].count;
			                    } else {
				                    distr_h.push_back({rounded_h, 1});
			                    }
		                    }
	                    });
	return distr_h;
}

void save_distr_heights_to_file(const std::vector<Distr_height>& heights,
                                const std::string& filename)
{
	std::ofstream ofs{filename};
	if (!ofs) {
		throw std::runtime_error("Could not open file " + filename
		                         + " for writing");
	}
	for (const Distr_height& h : heights) {
		ofs << h;
	}
}

//------------------------------------------------------------------------------

void e07()
{
	fl_color(default_color().as_int());

	constexpr int win_w{640};
	constexpr int win_h{320};
	const std::string win_lb{"Stats"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	CSV_parser csv_p{csv_filename()};
	const std::string& height_col_name{"Height"};
	std::vector<Distr_height> distr_h{get_distr_heights(csv_p, height_col_name)};
	save_distr_heights_to_file(distr_h, name_value_pairs_filename());

	barch::Bar_chart bc{{16, 16}, win_w - 32, win_h - 32};
	bc.set_title("Distributed height of NBA Players (2014-2015)");
	bc.set_y_title("Count");
	bc.set_x_title("Height (cm)");
	bc.show_grid_lines();
	ch15_hlp::add_name_value_pairs_from_file(bc, name_value_pairs_filename());
	bc.set_unit(5);
	bc.set_fill_colors({Graph_lib::Color::dark_blue,
	                    Graph_lib::Color::dark_red,
	                    Graph_lib::Color::dark_green});
	bc.sort_by_label(barch::Order::Asc);
	win.attach(bc);

	Graph_lib::gui_main();
}

//------------------------------------------------------------------------------

int main()
try {
	e07();
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
