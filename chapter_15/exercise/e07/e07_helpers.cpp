#include "../share/csv_parser.h"
#include "e07.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const ch15_e07::Distr_height h)
{
	os << "(\"" << h.height << "\", " << h.count << ')' << '\n';
	return os;
}

void ch15_e07::distr_height(CSV_value_vector values,
                            std::vector<Distr_height>& heights,
                            const std::string& height_column_name)
{
	double h{values.as_double(height_column_name)};
	if (h > 0) {
		int rounded_h{static_cast<int>(std::round(h * 2 / 10) * 10 / 2)};
		int match = -1;
		for (int i = 0; i < heights.size(); ++i) {
			if (rounded_h == heights[i].height) {
				match = i;
				break;
			}
		}
		if (match > -1) {
			++heights[match].count;
		} else {
			heights.push_back({rounded_h, 1});
		}
	}
}

std::vector<ch15_e07::Distr_height> ch15_e07::get_distr_heights(
    CSV_parser& p, const std::string& column_name)
{
	std::vector<Distr_height> distr_h;
	p.perform_action_on({column_name},
	                    [&distr_h, &column_name](CSV_value_vector values) {
		                    distr_height(values, distr_h, column_name);
	                    });
	return distr_h;
}

void ch15_e07::save_distr_heights_to_file(
    const std::vector<Distr_height>& heights, const std::string& filename)
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
