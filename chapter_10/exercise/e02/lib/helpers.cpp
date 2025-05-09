#include "helpers.h"

int help::scale_factor(int decimal_count)
{
	int f = 1;
	for (int i = 0; i < decimal_count; ++i) {
		f *= 10;
	}
	return f;
}

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
	int scale_f{ scale_factor(decimal_count) };
	int trunc_val = static_cast<int>(scale_f * d);
	int sign = (d > 0 ? 1 : -1);
	trunc_val *= sign;

	int count = 0;
	while (trunc_val > 0) {
		if (count == 2) {
			s = '.' + s;
		}
		int rightmost_digit = (trunc_val * 0.1 - trunc_val / 10) * 10;
		s = digit_to_char(rightmost_digit) + s;
		trunc_val /= 10;
		++count;
	}
	if (count == 2) {
		s = '0' + s;
	}

	if (sign == -1) {
		s = '-' + s;
	}

	return s;
}

char help::chtoupper(char c)
{
	if (c < 'a' || c > 'z') {
		return c;
	}
	return static_cast<char>(c - ('a' - 'A'));
}

void help::clear_buffer(std::istream& is)
{
	for (char temp{}; is.get(temp) && temp != '\n';) { /* Repeat until newline */
	}
}
// Temperature conversion ------------------------------------------------------

const std::string help::abs_zero_error_msg()
{
	static std::string msg{"Invalid argument, value is below absolute zero"};
	return msg;
}

double help::ctof(double c)
{
	if (c < abs_zero_celsius) {
		throw std::runtime_error("ctof() \"" + abs_zero_error_msg() + '"');
	}
	return 9 / 5.0 * c + 32;
}

double help::ftoc(double f)
{
	if (f < abs_zero_fahrenheit) {
		throw std::runtime_error("ftoc() \"" + abs_zero_error_msg() + '"');
	}
	return (f - 32) * 5.0 / 9;
}
