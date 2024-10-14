#ifndef E09_H
#define E09_H
#include <iostream>
#include <vector>

// Forward declare
class CSV_value_vector;
class CSV_parser;
//------------------------------------------------------------------------------

namespace ch15_e09 {

void e09();

struct Distr_height
{
	int height;
	int count;
};

void distr_height(CSV_value_vector values,
                  std::vector<Distr_height>& heights,
                  const std::string& height_column_name);

std::vector<Distr_height> get_distr_heights(CSV_parser& p,
                                            const std::string& column_name);

void save_distr_heights_to_file(const std::vector<Distr_height>& heights,
                                const std::string& filename);

} // namespace ch15_e09

std::ostream& operator<<(std::ostream& os, const ch15_e09::Distr_height h);

#endif // E09_H
