#ifndef HELP_H
#define HELP_H
#include <iostream>
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

inline bool isxdigit(char c)
{
	return (isvalidch(c) && ::isxdigit(c));
}

inline bool isalnum(char c)
{
	return (isvalidch(c) && ::isalnum(c));
}

inline bool islower(char c)
{
	return (isvalidch(c) && ::islower(c));
}

inline bool isupper(char c)
{
	return (isvalidch(c) && ::isupper(c));
}

inline bool iscntrl(char c)
{
	return (isvalidch(c) && ::iscntrl(c));
}

inline bool ispunct(char c)
{
	return (isvalidch(c) && ::ispunct(c));
}

inline bool isprint(char c)
{
	return (isvalidch(c) && ::isprint(c));
}

inline bool isgraph(char c)
{
	return (isvalidch(c) && ::isgraph(c));
}

inline std::string tolower(std::string s)
{
	for (char& c : s) {
		if (help::isalpha(c)) {
			c = ::tolower(c);
		}
	}
	return s;
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
