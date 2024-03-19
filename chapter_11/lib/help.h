#ifndef HELP_H
#define HELP_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace help {

inline bool isvalidch(char c)
{
	return (-1 <= c && c <= 255);
}

inline bool isspace(char c)
{
	return (isvalidch(c) && ::isspace(c));
}

inline bool isalpha(char c)
{
	return (isvalidch(c) && ::isalpha(c));
}

inline bool isdigit(char c)
{
	return (isvalidch(c) && ::isdigit(c));
}

inline bool isalnum(char c)
{
	return (isvalidch(c) && ::isalnum(c));
}

inline bool isupper(char c)
{
	return (isvalidch(c) && ::isupper(c));
}

void clear_buffer(std::istream& is);
void wait_for_enter();

// from stdlibfacilities.h -----------------------------------------------------

template<class R, class A>
R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a)
		error(std::string("info loss"));
	return r;
}

inline void keep_window_open(const std::string& action = "exit")
{
	std::cout << "Press <ENTER> to " << action << '\n';
	std::cin.get(); // wait for input
}

void putback_str(std::istream& is, const std::string& s);

} // namespace help

#endif // HELP_H
