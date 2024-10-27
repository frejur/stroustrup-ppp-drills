#include "my_win.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Map_char& m)
{
	return os << "('" << m.label().front() << "', " << m.mapped_position().x
	          << ", " << m.mapped_position().y << ")";
}

void My_window::save_map(const std::string& file_path)
{
	std::ofstream ofs{file_path};

	if (!ofs) {
		throw std::runtime_error("Could not open file: '" + file_path
		                         + "' for output");
	}

	for (int i = 0; i < map_chars.size(); ++i) {
		if (!map_chars[i].is_mapped()) {
			continue;
		}
		ofs << map_chars[i] << '\n';
	}
}
