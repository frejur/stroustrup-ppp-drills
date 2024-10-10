#ifndef E07_H
#define E07_H
#include <iostream>
#include <vector>

// Forward declare
class CSV_value_vector;
class CSV_parser;
//------------------------------------------------------------------------------

namespace ch15_e07 {

void e07();

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

} // namespace ch15_e07

std::ostream& operator<<(std::ostream& os, const ch15_e07::Distr_height h);

#endif // E07_H
