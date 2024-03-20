#ifndef E04_H
#define E04_H

#include "../../lib/help.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace e04 {

//------------------------------------------------------------------------------

inline const std::string& file_path_input()
{
	static std::string p{"data/input.txt"};
	return p;
}

//------------------------------------------------------------------------------

enum class Input_type { Unknown = -1, Decimal, Hexadecimal, Octal };
inline const std::string& input_type_name(Input_type t)
{
	static std::vector<std::string> names{"Unknown",
	                                      "Decimal",
	                                      "Hexadecimal",
	                                      "Octal"};
	return names.at(static_cast<int>(t) + 1);
}

Input_type input_type(const std::string& s, int v);
std::ostream& operator<<(std::ostream& os, Input_type t);

struct Multi_input
{
	int value;
	Input_type type;
	std::string input;
};

std::ostream& operator<<(std::ostream& os, Multi_input mi);

class Multi_stream
{
public:
	Multi_stream(std::istream& is)
	    : src(is)
	{
		buf.unsetf(std::ios_base::dec);
	};
	Multi_stream& operator>>(Multi_input& mi);
	operator bool()
	{
		return !(src.fail() || src.bad()) && (buf.good() || buf.eof());
	};
	void clear()
	{
		src.clear();
		buf.clear();
	}

private:
	std::istream& src;
	std::stringstream buf;
};

//------------------------------------------------------------------------------
} // namespace e04

#endif
