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

std::string help::int_to_ordinal(int i)
{
	std::string o;
	if (i < 1) {
		return o;
	}

	o = int_to_string(i);
	char rmost_ch{o.back()};
	switch (rmost_ch) {
	case '1':
		o += "st";
		break;
	case '2':
		o += "nd";
		break;
	case '3':
		o += "rd";
		break;
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	default:
		o += "th";
		break;
	}
	return o;
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

// More random numbers ---------------------------------------------------------
std::vector<int> help::sequence(int min, int max, int n)
{
	if (max < min) {
		throw std::runtime_error(
		    "Cannot generate sequence when min is greater than max");
	}
	if (n < 2 || n > max - min + 1) {
		throw std::runtime_error("Too few / too many number of elements");
	}
	std::vector<int> seq{min};
	int incr{static_cast<int>((max - min) / (n - 1.0) + 0.5)};
	for (int i = 1; i < n; ++i) {
		seq.push_back(min + incr * i);
	}
	return seq;
}

void help::shuffle(std::vector<int>& v, int iterations)
{
	if (v.size() < 3 || iterations < 1) {
		return; // don't bother
	}
	for (int i = 0; i < iterations; ++i) {
		for (int j = 0; j < v.size(); ++j) {
			int randidx{(j + randint(1, 3)) % (int) v.size()};
			swap(v.at(j), v.at(randidx));
		}
	}
}
