#include "../share/parse/csv_parser.h"
#include "e10.h"
#include <fstream>

inline bool ch15_e10::str_to_bool(const std::string& s)
{
	int b = -1;
	if (s == "True") {
		b = 1;
	} else if (s == "False") {
		b = 0;
	} else {
		throw std::runtime_error("Invalid value: \"" + s
		                         + "\", expected \"True\" or \"False\"");
	}
	return b;
}

std::string ch15_e10::region_from_generation(int gen)
{
	std::string r;
	switch (gen) {
	case 1:
		r = "Kanto";
		break;
	case 2:
		r = "Johto";
		break;
	case 3:
		r = "Hoenn";
		break;
	case 4:
		r = "Sinnoh";
		break;
	case 5:
		r = "Unova";
		break;
	case 6:
		r = "Kalos";
		break;
	default:
		break;
	}
	if (r.empty()) {
		throw std::runtime_error("Invalid generation value");
	}
	return r;
}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const ch15_e10::Pokemon_stats& stats)
{
	os << "(\"" << stats.name << "\", " << stats.combined_attack << ", "
	   << stats.combined_defence << ", \"" << stats.region << "\", "
	   << (stats.is_legendary ? "True" : "False") << ')' << '\n';
	return os;
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
