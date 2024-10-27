
#include "my_win.h"
#include <fstream>

namespace {
struct Map_char_vals
{
	char c;
	int x;
	int y;
};
} // namespace

std::istream& operator>>(std::istream& is, Map_char_vals& m)
{
	char c{};
	int x{}, y{};
	// Parentheses, single quotes, and commas
	char l_par{}, l_q{}, r_q{}, cm_0{}, cm_1{}, r_par{};
	is >> l_par >> l_q;
	if (!is || l_par != '(' || l_q != '\'') {
		is.clear(std::ios_base::badbit);
		return is;
	}
	is >> c;
	if (!is || !My_window::is_valid_ch(c)) {
		is.clear(std::ios_base::badbit);
		return is;
	}
	is >> r_q >> cm_0 >> x >> cm_1 >> y >> r_par;
	if (r_q != '\'' || cm_0 != ',' || cm_1 != ',' || r_par != ')') {
		is.clear(std::ios_base::badbit);
	}
	if (is) {
		m.c = c;
		m.x = x;
		m.y = y;
	}
	return is;
}

void My_window::load_map(const std::string& file_path)
{
	std::ifstream ifs{file_path};

	if (!ifs) {
		throw std::runtime_error("Could not open file: '" + file_path
		                         + "' for input");
	}

	Map_char_vals m;
	while (ifs >> m) {
		map_ch(m.c, {m.x, m.y});
	}
}
