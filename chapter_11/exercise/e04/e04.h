#ifndef E04_H
#define E04_H

#include "../../lib/help.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace e04 {

//------------------------------------------------------------------------------

inline const std::string& file_path_input()
{
	static std::string p{"data/input.txt"};
	return p;
}

//------------------------------------------------------------------------------

enum class Input_type { Unknown = -1, Decimal, Hexadecimal, Octal };

Input_type input_type(const std::string& s, int v);

struct Multi_input
{
	int value;
	Input_type type;
	std::string input;
};

class Multi_stream
{
public:
	Multi_stream(std::istream& is)
	    : src(is){};
	bool operator()
	{
		return !(src.fail() || src.bad()) && (buf.good() || buf.eof());
	};

private:
	std::istream& src;
	std::stringstream buf;
};

//------------------------------------------------------------------------------
} // namespace e04

#endif
