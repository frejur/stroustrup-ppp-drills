#ifndef ROMAN_INT_H
#define ROMAN_INT_H
#include "../help/help.h"
#include <iostream>
#include <string>
#include <vector>

namespace romi {

constexpr int not_a_symbol_value = -1;
constexpr int min_int{-4999};
constexpr int max_int{min_int * -1};
inline bool is_within_bounds(int i)
{
	return (min_int <= i && i <= max_int);
}

struct Roman_terms
{
	char min;
	char mid;
};

struct Roman_symbol
{
	std::string symbol;
	int value = not_a_symbol_value;
};

inline const std::vector<Roman_terms>& lookup_terms()
{
	static std::vector<Roman_terms> t{{'I', 'V'}, // 1 - 9
	                                  {'X', 'L'}, // 10 - 90
	                                  {'C', 'D'}, // 100 - 900
	                                  {'M', 0}};  // 1000 - 4000
	return t;
}

inline const std::string& lookup_terms_string()
{
	static std::string s{};
	for (const Roman_terms& t : lookup_terms()) {
		s.push_back(t.min);
		if (t.mid != 0) {
			s.push_back(t.mid);
		}
	}
	return s;
}

inline std::string generate_lookup_terms_string()
{
	std::string s{};
	for (const Roman_terms& t : lookup_terms()) {
		s.push_back(t.min);
		if (t.mid != 0) {
			s.push_back(t.mid);
		}
	}
	return s;
}

const std::vector<Roman_symbol>& lookup_symbols();
std::vector<Roman_symbol> generate_lookup_symbols();
const int symbol_max_len();

inline bool has_only_valid_ch(const std::string& s)
{
	if (s == "N") {
		return true;
	}
	for (char c : s) {
		bool is_valid = false;
		for (char valid : lookup_terms_string()) {
			if (c == valid) {
				is_valid = true;
				break;
			}
		}
		if (!is_valid) {
			return false;
		}
	}
	return true;
}

romi::Roman_symbol extract_roman_symbol(std::string& s);
int exponent_from_roman_ch(char c);
std::string digit_to_roman(const int digit, const int exponent);
int roman_to_int(const std::string& s);
std::string int_to_roman(const int i);

class Roman_int
{
public:
	Roman_int(){};
	Roman_int(int i)
	    : val_int(i)
	    , val_str(int_to_roman(i)){};
	Roman_int(const std::string& s)
	    : val_int(roman_to_int(s))
	    , val_str(s){};
	int as_int() const { return val_int; };
	std::string as_roman() const { return val_str; };
	void change_value(int i)
	{
		val_int = i;
		val_str = int_to_roman(i);
	};
	void change_value(const std::string& s)
	{
		val_str = s;
		val_int = roman_to_int(s);
	}

private:
	int val_int = 0;
	std::string val_str = "N";
};

std::istream& operator>>(std::istream& is, Roman_int& r);
std::ostream& operator<<(std::ostream& os, const Roman_int& r);
bool operator==(const Roman_int& a, const Roman_int& b);
bool operator!=(const Roman_int& a, const Roman_int& b);

} // namespace romi

#endif // ROMAN_INT_H
