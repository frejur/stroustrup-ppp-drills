#ifndef E10_H
#define E10_H
#include "../share/chart/scatter_plot.h"
#include <iostream>
#include <vector>

// Forward declare
class CSV_value_vector;
class CSV_parser;
//------------------------------------------------------------------------------

namespace ch15_e10 {

void e10();

struct Pokemon_column_names
{
	const std::string name;
	const std::string attack;
	const std::string defence;
	const std::string sp_attack;
	const std::string sp_defence;
	const std::string generation;
	const std::string legendary;
};

std::string region_from_generation(int gen);

struct Pokemon_stats
{
	Pokemon_stats(){};
	Pokemon_stats(const std::string& n,
	              int comb_a,
	              int comb_d,
	              const std::string reg,
	              bool is_leg);
	bool is_legendary{};
	int combined_attack{};  // Attack + Special Attack
	int combined_defence{}; // Defence  Special Defence
	std::string name;
	std::string region; // (Generation)
};

std::vector<Pokemon_stats> get_pokemon_stats(
    CSV_parser& p, const Pokemon_column_names& col_names);

void pokemon_stats(CSV_value_vector values,
                   std::vector<Pokemon_stats>& stats_v,
                   const Pokemon_column_names& col_names);

void save_pokemon_stats_to_file(const std::vector<Pokemon_stats>& stats_v,
                                const std::string& filename);

inline bool str_to_bool(const std::string& s);

class Pokemon_plot_point : public chart::Plot_point
{
public:
	Pokemon_plot_point(const chart::Scatter_plot& parent_chart,
	                   const std::string& name,
	                   int attack,
	                   int defence,
	                   const std::string& region,
	                   bool is_legendary)
	    : chart::Plot_point::Plot_point(parent_chart, name, attack, defence)
	    , is_leg(is_legendary)
	    , reg(region){};
	bool is_legendary() const { return is_leg; };

private:
	bool is_leg;
	std::string reg;
};

void add_pokemon_plot_points_from_file(chart::Scatter_plot& plot,
                                       const std::string& filename);

} // namespace ch15_e10

std::ostream& operator<<(std::ostream& os, const ch15_e10::Pokemon_stats& stats);
std::istream& operator>>(std::istream& is, ch15_e10::Pokemon_stats& stats);

#endif // E10_H
