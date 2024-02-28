#include "roman.h"
#include "../help/help.h"
#include <stdexcept>

std::string romi::digit_to_roman(const int digit, const int exponent)
{
	std::string r;
	if (1 > digit || digit > 9) {
		throw std::runtime_error("Invalid digit");
	}
	if (0 > exponent || exponent > (lookup_terms().size() - 1)) {
		throw std::runtime_error("Invalid exponent");
	}
	if (exponent == 3 && digit > 4) {
		throw std::runtime_error("Number out of bounds");
	}

	Roman_terms t{lookup_terms()[exponent]};
	switch (digit) {
	case 1:
	case 2:
	case 3:
		for (int i = 0; i < digit; ++i) {
			r += t.min;
		}
		break;
	case 4:
		if (exponent < (lookup_terms().size() - 1)) {
			r = t.min;
			r += t.mid;
		} else {
			for (int j = 0; j < 4; ++j) {
				r += t.min;
			}
		}
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		r = t.mid;
		for (int k = 0; k < (digit - 5); ++k) {
			r += t.min;
		}
		break;
	case 9:
		r = t.min;
		r += lookup_terms()[exponent + 1].min;
		break;
	default:
		break;
	}
	return r;
}

int romi::exponent_from_roman_ch(char c)
{
	for (int e = 0; e < lookup_terms().size(); ++e) {
		if (c == lookup_terms()[e].min || c == lookup_terms()[e].mid) {
			return e;
		}
	}
	return -1;
}

romi::Roman_symbol romi::extract_roman_symbol(std::string& s)
{
	if (s.size() < 1) {
		throw std::runtime_error("Symbol string empty");
	}
	int chunk_sz = (symbol_max_len() > s.size()) ? s.size() : symbol_max_len();
	std::vector<std::string> search_str;
	for (int i = chunk_sz; i > 0; --i) {
		search_str.push_back(help::copy_ch_from_end(s, i));
	}
	for (const std::string& str : search_str) {
		for (const Roman_symbol& rs : lookup_symbols()) {
			if (str == rs.symbol) {
				return {help::extract_ch_from_end(s, str.size()), rs.value};
			}
		}
	}

	return {"", not_a_symbol_value};
}

std::string romi::int_to_roman(const int i)
{
	if (!is_within_bounds(i)) {
		throw std::runtime_error("Out of bounds error");
	}
	if (i == 0) {
		return "N";
	}

	std::string roman;
	int sign = (i >= 0) ? 1 : -1;

	int abs_i = sign * i;

	int rmost_d = -1;
	int exp = 0;
	while (abs_i > 0) {
		rmost_d = abs_i - (abs_i / 10) * 10;
		if (rmost_d != 0) {
			roman = digit_to_roman(rmost_d, exp) + roman;
		}
		++exp;
		abs_i /= 10;
	}
	if (sign == -1) {
		roman = "-" + roman;
	}
	return roman;
}
int romi::roman_to_int(const std::string& s)
{
	int final_val = 0;
	if (s == "N") {
		return final_val;
	}

	int sign = 1;
	std::string parse_s = s;
	if (s.size() > 1 && s.front() == '-') {
		sign = -1;
		parse_s = help::copy_ch_from_end(parse_s, s.size() - 1);
	}

	if (!has_only_valid_ch(parse_s)) {
		throw std::runtime_error("Invalid characters in roman numeral");
	}

	Roman_symbol sym;
	int min_val;
	for (bool first_i = true; parse_s.size();) {
		sym = extract_roman_symbol(parse_s);

		if (first_i && sym.value != not_a_symbol_value) {
			first_i = false;
			min_val = help::exp_f_from_int(sym.value);
		}

		if (sym.value == not_a_symbol_value || min_val > max_int
		    || (min_val > sym.value || sym.value > max_int)) {
			throw std::runtime_error("Invalid roman numeral notation");
		}

		final_val += sym.value;
		min_val *= 10;
	}

	return final_val * sign;
}

const std::vector<romi::Roman_symbol>& romi::lookup_symbols()
{
	static std::vector<Roman_symbol> symbols{generate_lookup_symbols()};
	return symbols;
}

const int romi::symbol_max_len()
{
	static int len = 0;
	for (const Roman_symbol& s : lookup_symbols()) {
		if (s.symbol.size() > len) {
			len = s.symbol.size();
		}
	}
	return len;
}

std::vector<romi::Roman_symbol> romi::generate_lookup_symbols()
{
	std::vector<Roman_symbol> symbols;
	int exp = 1;
	for (const Roman_terms& t : lookup_terms()) {
		int scale = help::scale_factor(exp - 1);
		std::string s_min;
		int num_min = (exp < lookup_terms().size()) ? 3 : 4;
		for (int i = 1; i <= num_min; ++i) {
			s_min += t.min;
			symbols.push_back({s_min, i * scale});
		}

		if (exp == lookup_terms().size()) {
			break;
		}

		std::string s_mid;
		s_mid += t.min;
		s_mid += t.mid;
		symbols.push_back({s_mid, 4 * scale});

		s_mid = "";
		s_mid += t.mid;
		symbols.push_back({s_mid, 5 * scale});

		for (int j = 6; j < 9; ++j) {
			s_mid += t.min;
			symbols.push_back({s_mid, j * scale});
		}

		std::string s_max;
		s_max += t.min;
		s_max += lookup_terms()[exp].min;
		symbols.push_back({s_max, 9 * scale});

		++exp;
	}
	return symbols;
}

std::istream& romi::operator>>(std::istream& is, Roman_int& r)
{
	std::string r_str;
	is >> r_str;
	if (is) {
		r = {r_str};
	}
	return is;
}

std::ostream& romi::operator<<(std::ostream& os, const Roman_int& r)
{
	os << r.as_roman();
	return os;
}

bool romi::operator==(const Roman_int& a, const Roman_int& b)
{
	return (a.as_roman() == b.as_roman()) && (a.as_int() == b.as_int());
}

bool romi::operator!=(const Roman_int& a, const Roman_int& b)
{
	return !(a == b);
}
