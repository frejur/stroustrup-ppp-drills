#ifndef HELP_H
#define HELP_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace help {

inline std::string prepend_char(const std::string& s, char c)
{
	return c + s;
}
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

inline void append_x_ch(std::string& s, int indent_w, char c = ' ')
{
	if (indent_w <= s.size()) {
		return;
	}
	for (int i = s.size(); i <= indent_w; ++i) {
		s.push_back(c);
	}
}

inline void append_spaces(std::string& s, int indent_w)
{
	append_x_ch(s, indent_w);
}

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

inline void keep_window_open(const std::string& action = "exit")
{
	std::cout << "Press <ENTER> to " << action << '\n';
	std::cin.get(); // wait for input
}

void putback_str(std::istream& is, const std::string& s);

// -----------------------------------------------------------------------------

inline char skipto_break_nonws(std::istream& istr)
{
	char ch{' '};
	while (istr && (help::isspace(ch) && ch != '\n')) {
		istr.get(ch);
	}
	return ch;
}

inline std::string feed_into_string_until_newline(std::istream& is,
                                                  bool min_wspace = false)
{
	std::string s;
	bool prev_was_wspace = false;
	char ch = 0;
	for (;;) {
		is.get(ch);
		if (!is || ch == '\n') {
			break;
		}
		if (min_wspace) {
			if (help::isspace(ch)) {
				if (prev_was_wspace) {
					continue;
				}
				ch = ' ';
				prev_was_wspace = true;
			} else {
				prev_was_wspace = false;
			}
		}
		s.push_back(ch);
	}
	return s;
}

} // namespace help

#endif // HELP_H
