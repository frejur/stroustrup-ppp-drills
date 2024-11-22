#include "e01.h"
#include <fstream>

const std::string& input_file_path()
{
	static std::string p{ "data_e01/values.txt" };
	return p;
}

void print_hello(std::ostream& os)
{
	os << "Sum of whitespace-separated values in a text"
	      "file"
	   << '\n'
	   << "Press <ENTER> to calculate the sum of \"" << input_file_path()
	   << "\"." << '\n';
}

void print_sum(std::ostream& os, double sum, int count)
{
	if (count > 0) {
		os << "   Found " << count << " values, sum = " << double_to_string(sum)
		   << '\n';
	} else {
		os << "Found no values in the provided text file." << '\n';
	}
}

void print_expected(std::ostream& os, double sum, int count)
{
	os << "Expected " << count << " values, sum = " << double_to_string(sum)
	   << '\n';
}

void print_success(std::ostream& os)
{
	os << "Happy days! :)" << '\n';
}

void print_failure(std::ostream& os)
{
	os << "Something went wrong :(" << '\n';
}

void print_goodbye(std::ostream& os)
{
	os << "Press <ENTER> to exit." << '\n';
}

std::vector<double> read_values_from_ifstream(const std::string& file_path)
{
	std::ifstream ifs{ file_path };

	if (!ifs) {
		throw std::runtime_error("Could not open file: \"" + input_file_path()
		                         + "\"\n");
	}

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit); // throw if bad()

	std::vector<double> values;
	for (double val; ifs >> val;) {
		values.push_back(val);
	}

	if (!ifs.eof()) {
		throw std::runtime_error("Invalid syntax, aborting...");
	}

	return values;
}

int scale_factor(int decimal_count)
{
	int f = 1;
	for (int i = 0; i < decimal_count; ++i) {
		f *= 10;
	}
	return f;
}

char digit_to_char(int i)
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

std::string double_to_string(double d, int decimal_count)
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

double sum_of_values(const std::vector<double>& values)
{
	// Perform integer arithmetic as to not lose precision
	int scaled_sum = 0;
	int scale_f = scale_factor(max_decimal_count);

	for (const double& v : values) {
		scaled_sum += v * scale_f;
	}

	return scaled_sum / static_cast<double>(scale_f);
}
