#ifndef E01_H
#define E01_H

#include <fstream>
#include <stdexcept>
#include <string>

namespace e01 {

//------------------------------------------------------------------------------

inline const std::string& file_path_source()
{
	static std::string p{"data/mixed.txt"};
	return p;
}
inline const std::string& file_path_output()
{
	static std::string p{"data/lowercase.txt"};
	return p;
}

//------------------------------------------------------------------------------

void convert_file_to_lowercase(const std::string& source,
                               const std::string& output);
} // namespace e01

#endif
