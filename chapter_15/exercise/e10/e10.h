#ifndef E10_H
#define E10_H
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
	Pokemon_stats(const std::string& n,
	              int comb_a,
	              int comb_d,
	              const std::string reg,
	              bool is_leg);
	;
	bool is_legendary;
	int combined_attack;  // Attack + Special Attack
	int combined_defence; // Defence  Special Defence
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

} // namespace ch15_e10

std::ostream& operator<<(std::ostream& os, const ch15_e10::Pokemon_stats& stats);

#endif // E10_H
