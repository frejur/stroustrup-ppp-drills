#ifndef E09_H
#define E09_H

#include <string>
#include <vector>

namespace e11 {

// -----------------------------------------------------------------------------

inline const std::string& file_path_numbers()
{
	static std::string s{"data/numbers.txt"};
	return s;
}

// -----------------------------------------------------------------------------

std::vector<int> ints_from_file(const std::string& file_path);

} // namespace e11

namespace help {

inline bool isvalidch(char c)
{
	return (-1 <= c && c <= 255);
}

inline bool isdigit(char c)
{
	return (isvalidch(c) && ::isdigit(c));
}

inline bool isspace(char c)
{
	return (isvalidch(c) && ::isspace(c));
}

} // namespace help

#endif
