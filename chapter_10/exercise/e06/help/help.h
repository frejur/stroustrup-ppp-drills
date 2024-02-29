#ifndef HELP_H
#define HELP_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace help {

char digit_to_char(int i);
inline int char_to_digit(char c)
{
	if ('0' > c || c > '9') {
		return '0';
	}
	return c - '0';
}
std::string double_to_string(double d, int decimal_count = 2);
inline std::string int_to_string(int i)
{
	return double_to_string(i, 0);
}
int string_to_int(const std::string& s);

void clear_buffer(std::istream& is);
void wait_for_enter();

std::string extract_ch_from_end(std::string& s, int num_ch, bool copy = false);
inline std::string copy_ch_from_end(std::string& s, int num_ch)
{
	return extract_ch_from_end(s, num_ch, true);
};

inline constexpr int scale_factor(int decimal_count)
{
	if (decimal_count < 1) {
		return 1;
	}
	int f = 1;
	for (int i = 0; i < decimal_count; ++i) {
		f *= 10;
	}
	return f;
}

inline constexpr int exp_f_from_int(int i)
{
	// Returns the factor of exponent, 1e0 = 1, 1e1 = 10, etc.
	i = (i > 0) ? i : -i;
	int exp = 1;
	while (i > 10) {
		i /= 10;
		exp *= 10;
	}
	return exp;
}

// from stdlibfacilities.h -----------------------------------------------------

inline void error(const std::string& s)
{
	throw std::runtime_error(s);
}

inline void error(const std::string& s, const std::string& s2)
{
	error(s + s2);
}

inline void error(const std::string& s, int i)
{
	std::ostringstream os;
	os << s << ": " << i;
	error(os.str());
}

template<class R, class A>
R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a)
		error(std::string("info loss"));
	return r;
}

inline void keep_window_open()
{
	std::cin.clear();
	std::cout << "Please enter a character to exit\n";
	char ch;
	std::cin >> ch;
	return;
}

} // namespace help

#endif // HELP_H
