#include "../share/chart/scatter_plot.h"
#include "../share/parse/csv_parser.h"
#include "e10.h"
#include <fstream>

namespace {
const std::string& true_string()
{
	static const std::string s{"True"};
	return s;
}
const std::string& false_string()
{
	static const std::string s{"False"};
	return s;
}
} // namespace

inline bool ch15_e10::str_to_bool(const std::string& s)
{
	int b = -1;
	if (s == true_string()) {
		b = 1;
	} else if (s == false_string()) {
		b = 0;
	} else {
		throw std::runtime_error("Invalid value: \"" + s
		                         + "\", expected \"True\" or \"False\"");
	}
	return b;
}

std::string ch15_e10::region_from_generation(int gen)
{
	if (gen < 1 || gen > pokemon_regions().size()) {
		throw std::runtime_error("Invalid generation value");
	}
	return pokemon_regions()[gen - 1];
}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const ch15_e10::Pokemon_stats& stats)
{
	os << "(\"" << stats.name << "\", " << stats.combined_attack << ", "
	   << stats.combined_defence << ", \"" << stats.region << "\", "
	   << (stats.is_legendary ? true_string() : false_string()) << ')' << '\n';
	return os;
}

//------------------------------------------------------------------------------

std::istream& extr_bool_str(std::istream& is, bool& extr_bool)
{
	std::string s;
	char c{};
	bool get_first = true;
	while (is) {
		if (get_first) {
			is >> c;
			get_first = false;
		} else {
			is.get(c);
		}
		s += c;
		if (s == true_string()) {
			extr_bool = true;
			break;
		} else if (s == false_string()) {
			extr_bool = false;
			break;
		} else if (s.size() >= true_string().size()
		           && s.size() >= false_string().size()) {
			is.clear(std::ios_base::badbit);
		}
	}
	return is;
}

std::istream& operator>>(std::istream& is, ch15_e10::Pokemon_stats& stats)
{
	char l_par{}, r_par{};               // parentheses
	char l_quo{}, r_quo{};               // quotes
	char cm_0{}, cm_1{}, cm_2{}, cm_3{}; // commas
	int val_x{}, val_y{};
	bool is_leg{};

	is >> l_par >> l_quo;
	if (l_par != '(' || l_quo != '"') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	bool found_r_quo = false;
	std::string label;
	while (is) {
		is.get(r_quo);
		if (r_quo == '"') {
			found_r_quo = true;
			break;
		}
		label += r_quo;
	}

	if (!found_r_quo) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	l_quo = ' ';
	r_quo = ' ';
	is >> cm_0 >> val_x >> cm_1 >> val_y >> cm_2 >> l_quo;

	if (!is || cm_0 != ',' || cm_1 != ',' || cm_2 != ',' || l_quo != '"') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	found_r_quo = false;
	std::string region;
	while (is) {
		is.get(r_quo);
		if (r_quo == '"') {
			found_r_quo = true;
			break;
		}
		region += r_quo;
	}

	if (!found_r_quo) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	is >> cm_3;
	if (!is) {
		return is;
	}

	extr_bool_str(is, is_leg);
	if (!is) {
		return is;
	}

	is >> r_par;
	if (r_par != ')') {
		return is;
	}

	stats = {label, val_x, val_y, region, is_leg};
	return is;
}

//------------------------------------------------------------------------------

ch15_e10::Pokemon_stats::Pokemon_stats(const std::string& n,
                                       int comb_a,
                                       int comb_d,
                                       const std::string reg,
                                       bool is_leg)
    : is_legendary(is_leg)
    , combined_attack(comb_a)
    , combined_defence(comb_d)
    , name(n)
    , region(reg)
{}

//------------------------------------------------------------------------------

std::vector<ch15_e10::Pokemon_stats> ch15_e10::get_pokemon_stats(
    CSV_parser& p, const Pokemon_column_names& col_names)
{
	std::vector<Pokemon_stats> stats;
	p.perform_action_on({col_names.name,
	                     col_names.attack,
	                     col_names.sp_attack,
	                     col_names.defence,
	                     col_names.sp_defence,
	                     col_names.generation,
	                     col_names.legendary},
	                    [&stats, &col_names](CSV_value_vector values) {
		                    pokemon_stats(values, stats, col_names);
	                    });
	return stats;
}

void ch15_e10::pokemon_stats(CSV_value_vector values,
                             std::vector<Pokemon_stats>& stats_v,
                             const Pokemon_column_names& col_names)
{
	Pokemon_stats s{values.as_string(col_names.name),
	                values.as_int(col_names.attack)
	                    + values.as_int(col_names.sp_attack),
	                values.as_int(col_names.defence)
	                    + values.as_int(col_names.sp_defence),
	                region_from_generation(values.as_int(col_names.generation)),
	                str_to_bool(values.as_string(col_names.legendary))};
	stats_v.push_back(s);
}

void ch15_e10::save_pokemon_stats_to_file(
    const std::vector<Pokemon_stats>& stats_v, const std::string& filename)
{
	std::ofstream ofs{filename};
	if (!ofs) {
		throw std::runtime_error("Could not open file " + filename
		                         + " for writing");
	}
	for (const Pokemon_stats& s : stats_v) {
		ofs << s;
	}
}

//------------------------------------------------------------------------------

void ch15_e10::add_pokemon_plot_points_from_file(chart::Scatter_plot& plot,
                                                 const std::string& filename)
{
	std::ifstream ifs{filename};
	if (!ifs) {
		throw std::runtime_error("Could not open file: '" + filename + "'");
	}

	plot.disable_automatic_refresh();

	Pokemon_stats s{};
	while (ifs >> s) {
		plot.add([s](const chart::Scatter_plot& p) {
			return new Pokemon_plot_point(p,
			                              s.name,
			                              s.combined_attack,
			                              s.combined_defence,
			                              s.region,
			                              s.is_legendary);
		});
	}

	plot.enable_automatic_refresh();
	plot.refresh();
}
