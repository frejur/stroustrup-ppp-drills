#include "../../lib/std_lib_facilities.h"

// Exercise 8. The partial sum of integers.

// 1.	Ask user for the number of integers to sum up.
// 2.	Record integers entered by user.
// 		Finish on any non-numerical character.
// 3.	Print sum.

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

int sum_i(vector<int> v, int n) {
	if (n > v.size()) {
		error(
			"Not enough numbers recorded to calculate a sum of "
			+ std::to_string(n) + " values");
	}
	int sum{ 0 };
	for (int i = 0; i < n; ++i) {
		sum += v.at(i);

	}
	return sum;
}

std::string join_w_plus(vector<int> v, int n) {
	// Assumes 0 < n <= (size of v)
	std::string s{ "" };
	for (int i = 0; ; ++i) {
		s += std::to_string(v.at(i));
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
		<< "Calculate the sum of a given number of integers" << '\n' << '\n';

	std::cout
		<< "For how many integers do you want calculate the sum?" << '\n';
	int sum_count{ get_sum_count() };

	std::cout
		<< "Please enter some integers (Enter '|' to stop)" << '\n';
	vector<int> int_v{};
	int n{};
	while (std::cin >> n) {
		int_v.push_back(n);
	}

	int sum{ sum_i(int_v, sum_count) };
	std::cout
		<< "The sum of the " << sum_count << " first integers:" << '\n'
		<< join_w_plus(int_v, sum_count) << " = " << sum << '\n';

	keep_window_open();
	return 0;
}
catch (std::exception e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
