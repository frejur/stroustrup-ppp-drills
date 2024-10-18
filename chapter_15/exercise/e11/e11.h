#ifndef E11_HELPERS_H
#define E11_HELPERS_H
#include "../share/parse/csv_parser.h"
#include "../share/parse/nval_pair.h"
#include <string>
#include <vector>

namespace ch15_e11 {

void e11();

struct Value_pair
{
	double value_a;
	double value_b;
};

std::vector<Value_pair> merge_files_into_name_value_pairs(
    const std::string& filename_a, const std::string& filename_b);

std::vector<Name_value_value_triplet> get_name_value_value_triplets(
    CSV_parser& p,
    const std::string& name_header,
    const std::string& value_a_header,
    const std::string& value_b_header);

} // namespace ch15_e11

#endif // E11_HELPERS_H
