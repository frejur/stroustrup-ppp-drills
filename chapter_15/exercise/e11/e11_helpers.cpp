#include "e11.h"
#include <fstream>

std::vector<ch15_e11::Value_pair> ch15_e11::merge_files_into_name_value_pairs(
    const std::string& filename_a, const std::string& filename_b)
{
	std::ifstream ifs_a{filename_a};
	if (!ifs_a) {
		throw std::runtime_error("Could not open file '" + filename_a
		                         + "' for parsing");
	}

	std::ifstream ifs_b{filename_b};
	if (!ifs_b) {
		throw std::runtime_error("Could not open file '" + filename_b
		                         + "' for parsing");
	}

	std::vector<Value_pair> tr_v;
	double val_a, val_b;
	for (;;) {
		ifs_a >> val_a;
		ifs_b >> val_b;
		if (!ifs_a || !ifs_b) {
			break;
		}
		tr_v.push_back({val_a, val_b});
	}

	if (ifs_a || ifs_b) {
		throw std::runtime_error("Values mismatch");
	}

	return tr_v;
}

std::vector<Name_value_value_triplet> ch15_e11::get_name_value_value_triplets(
    CSV_parser& p,
    const std::string& name_header,
    const std::string& value_a_header,
    const std::string& value_b_header)
{
	std::vector<Name_value_value_triplet> tr_v;
	p.perform_action_on({name_header, value_a_header, value_b_header},
	                    [&tr_v, &name_header, &value_a_header, &value_b_header](
	                        CSV_value_vector values) {
		                    tr_v.push_back({values.as_string(name_header),
		                                    values.as_double(value_a_header),
		                                    values.as_double(value_b_header)});
	                    });
	return tr_v;
}
