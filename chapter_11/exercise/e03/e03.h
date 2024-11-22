#ifndef E03_H
#define E03_H

#include "../../lib/help.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace e03 {

//------------------------------------------------------------------------------

inline const std::string& vowels()
{
	static std::string v_upr{"AEIOU"};
	static std::string v{help::tolower(v_upr) + v_upr};
	return v;
}

inline const std::string& file_path_source()
{
	static std::string p{"data_e03/original.txt"};
	return p;
}

//------------------------------------------------------------------------------

inline bool isbanned(char c, const std::string& banned_chars)
{
	for (char v : banned_chars) {
		if (c == v) {
			return true;
		}
	}
	return false;
}

// In the end, not needed for this exercise
std::string disemvowel(const std::string& s)
{
	std::string new_str;
	for (char c : s) {
		if (!isbanned(c, vowels())) {
			new_str.push_back(c);
		}
	}
	return new_str;
}

void file_to_stringstream(const std::string& file_path,
                          std::stringstream& ss,
                          const std::string& banned_chars = "");
void stringstream_to_file(std::stringstream& ss,
                          const std::string& file_path,
                          const std::string& banned_chars = "");

//------------------------------------------------------------------------------
} // namespace e03

#endif
