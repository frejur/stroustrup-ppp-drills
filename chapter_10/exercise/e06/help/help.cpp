#include "help.h"
#include <iostream>
#include <stdexcept>

char help::digit_to_char(int i)
{
	switch (i) {
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 0:
	default:
		return '0';
	}
}

std::string help::double_to_string(double d, int decimal_count)
{
	if (d == 0) {
		return "0";
	}
	std::string s;
	int scale_f{scale_factor(decimal_count)};
	int trunc_val = static_cast<int>(scale_f * d);
	int sign = (d > 0 ? 1 : -1);
	trunc_val *= sign;

	int count = 0;
	while (trunc_val > 0) {
		if (count > 0 && count == decimal_count) {
			s = '.' + s;
		}
		int rightmost_digit = (trunc_val * 0.1 - trunc_val / 10) * 10;
		s = digit_to_char(rightmost_digit) + s;
		trunc_val /= 10;
		++count;
	}
	if (count > 0 && count == decimal_count) {
		s = '0' + s;
	}

	if (sign == -1) {
		s = '-' + s;
	}

	return s;
}

void help::clear_buffer(std::istream& is)
{
	for (char temp{}; is.get(temp) && temp != '\n';) { /* Repeat until newline */
	}
}

void help::wait_for_enter()
{
	if (!std::cin) {
		if (std::cin.bad()) {
			throw std::runtime_error("Input stream in a bad state");
		}
		std::cin.ignore();
	}
	char ch = 0;
	std::cin.get(ch);
	if (ch != '\n') {
		clear_buffer(std::cin);
	}
}

std::string help::extract_ch_from_end(std::string& s, int num_ch, bool copy)
{
	int len = s.size();
	if (num_ch > len) {
		throw std::runtime_error(
		    "Number of characters to extract exceeds length of string");
	}
	std::string remaining;
	std::string extracted;
	for (int i = 0; i < len; ++i) {
		if (i >= len - num_ch) {
			extracted += s[i];
		} else if (!copy) {
			remaining += s[i];
		}
	}
	if (!copy) {
		s = remaining;
	}
	return extracted;
}

int help::string_to_int(const std::string& s)
{
	int num = 0;
	if (s == "0" || s == "-0") {
		return num;
	}

	bool error = false;
	std::string error_msg;
	int sign = (s.front() == '-') ? -1 : 1;
	for (int i = 0; i < s.size(); ++i) {
		if (i == 0 && sign == -1) {
			continue;
		}
		if (!isdigit(s[i])) {
			error = true;
			error_msg = "Invalid character";
			break;
		}
		if (s[i] == 0) {
			if (num == 0) {
				error = true;
				error_msg = "Cannot begin with a zero";
				break;
			}
			continue;
		}

		int scale = scale_factor(s.size() - i - 1);
		num += scale * char_to_digit(s[i]);
	}
	if (error) {
		throw std::runtime_error("Cannot convert string to integer, "
		                         + error_msg);
	}
	return sign * num;
}

void help::putback_str(std::istream& is, const std::string& s)
{
	for (int i = s.size() - 1; i >= 0; --i) {
		is.putback(s[i]);
	}
}
