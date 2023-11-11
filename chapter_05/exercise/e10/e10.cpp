#include "../../lib/std_lib_facilities.h"

// Exercise 10. The partial sum of doubles

// Rewrite Exercise 8 using <double>'s

int get_sum_count() {
	int n;
	if (!(std::cin >> n)) {
		error("Not a number");
	}
	if (n < 1) {
		error("Number needs to be >0");
	}
	return n;
}

double sum_i(vector<double> v, int n) {
	if (n > v.size()) {
		error(
			"Not enough numbers recorded to calculate a sum of "
			+ std::to_string(n) + " values");
	}
	double sum_float{ 0 };
	for (int i = 0; i < n; ++i) {
		sum_float += v.at(i);
	}
	return sum_float;
}

std::string strip_trailing_zeros(std::string s) {
	std::string new_s{ "" };
	bool found_not_zero_or_dot{ false };
	for (int i = s.size() - 1; i >= 0; --i) {
		if (s.at(i) != '0' || s.at(i) == '.') {
			found_not_zero_or_dot = true;
		}
		if (found_not_zero_or_dot) {
			new_s = s.at(i) + new_s;
		}
	}
	if (new_s.back() == '.') {
		new_s = new_s.substr(0, new_s.size() - 1);
	}
	return new_s;
}

std::string join_w_plus(vector<double> v, int n) {
	// Assumes 0 < n <= (size of v)
	std::string s{ "" };
	for (int i = 0; ; ++i) {
		s += strip_trailing_zeros(std::to_string(v.at(i)));
		if (i > (n - 2)) {
			return s;
		}
		s += " + ";
	}
	return s;
}


int main()
try {
	std::cout
		<< "Calculate the sum of a given number of floating point values."
		<< '\n' << '\n'
		<< "A list of the difference between each entered value and " << '\n'
		<< "the prev. recorded value will also be printed upon exiting."
		<< '\n' << '\n';

	std::cout
		<< "For how many values do you want calculate the sum?" << '\n';
	int sum_count{ get_sum_count() };

	std::cout
		<< "Please enter some numbers (Enter '|' to stop)" << '\n';
	vector<double> double_v{};
	vector<double> diff_v{};
	double n{};
	while (std::cin >> n) {
		double_v.push_back(n);
		if (double_v.size() > 1) {
			diff_v.push_back(n - double_v.at(double_v.size() - 2));
		}
	}

	double sum{ sum_i(double_v, sum_count) };
	std::cout
		<< '\n'
		<< "The sum of the " << sum_count << " first values:" << '\n'
		<< join_w_plus(double_v, sum_count) << " = " << sum << '\n' << '\n';

	std::cout
		<< "Difference in values N - 1:" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
	for (int i = 0; i < sum_count - 1; ++i) {
		std::cout
			<< "  " << strip_trailing_zeros(std::to_string(double_v.at(i)))
			<< " --- ( DIFF: "
			<< strip_trailing_zeros(std::to_string(diff_v.at(i)))
			<< " ) ---> "
			<< strip_trailing_zeros(std::to_string(double_v.at(i + 1)))
			<< '\n';
	}

	keep_window_open();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
