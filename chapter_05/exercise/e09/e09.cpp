#include "../../lib/std_lib_facilities.h"

// Exercise 9. The partial sum of integers revisited

// Modify exercise 8 to throw an error if an integer overflow occurs during the
// the calculation of the sum.

// Integers are assigned 4 bytes (32 bits) on a typical desktop computer
static constexpr double COMMON_INT_MAX{ (double)
										2*2 * 2*2 * 2*2 * 2*2 *
										2*2 * 2*2 * 2*2 * 2*2 *
										2*2 * 2*2 * 2*2 * 2*2 *
										2*2 * 2*2 * 2*2 * 2
										- 1 };

// If the user enters a value that exceeds this limit on its own the program
// terminates, the same way it would if you entered any non-numeric
// character. It's hard to write any decent error handling for this case,
// at least at this point.

// The sum overflow can be caught by using narrow_cast.

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
	double sum_float{ 0 };
	for (int i = 0; i < n; ++i) {
		sum_float = narrow_cast<int>(sum_float + v.at(i));
	}
	return (int)sum_float;
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
		<< "Calculate the sum of a given number of integers" << '\n' << '\n'
		<< "An error will be thrown if the total sum exceeds the" << '\n'
		<< "type max value. The max value is system dependent" << '\n'
		<< "but usually 32 bits: " << std::to_string(COMMON_INT_MAX) << '\n'
		<< "(Add anything past that and you should trigger the error)"
		<< '\n' << '\n';

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
