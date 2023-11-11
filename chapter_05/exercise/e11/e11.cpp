#include "../../lib/std_lib_facilities.h"

// Exercise 11. Fibonacci numbers

// Write out the first X numbers of the Fibonacci series.
// Prompt for the number X.
// 1 1 2 3 5 8 13 21 34 (Each new number is the sum of the two prev. ones).
// If the user enters 0, keeps printing numbers until it causes integer overflow.

// Integers are assigned 4 bytes (32 bits) on a typical desktop computer
static constexpr double COMMON_INT_MAX{ (double)
										2*2 * 2*2 * 2*2 * 2*2 *
										2*2 * 2*2 * 2*2 * 2*2 *
										2*2 * 2*2 * 2*2 * 2*2 *
										2*2 * 2*2 * 2*2 * 2
										- 1 };

vector<int> gen_fib_numbers(int n) {
	if (n < 1) {
		error("Invalid argument, n < 1)");
	}
	vector<int> v{ 1 };
	for (int i = 1; i < n; ++i) {
		if (i == 1) {
			v.push_back(1);
			continue;
		}
		try {
			v.push_back(
				narrow_cast<int>(
					(float)v.at(i-1) + (float)v.at(i - 2)
				)
			);
		} catch (...) {
			return v;
		}
	}
	return v;
}

static constexpr int FIB_MAX_IDX{ 100 }; // Should be more than enough

std::string join_w_space(vector<int> v) {
	// Assumes 0 < n <= (size of v)
	std::string s{ "" };
	for (int i = 0; i < v.size(); ++i) {
		s += std::to_string(v.at(i));
		if (i > v.size() - 2) {
			return s;
		}
		if ((i+1) % 12 == 0) {
			s+= '\n';
			continue;
		}
		s += " ";
	}
	return s;
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

int main()
try {
	std::cout
		<< "Program that writes out Fibonacci numbers." << '\n' << '\n'
		<< "An error will be thrown if a number exceeds the" << '\n'
		<< "<int> type max value. The max value is system dependent" << '\n'
		<< "but usually 32 bits: "
		<< strip_trailing_zeros(std::to_string(COMMON_INT_MAX)) << '\n' << '\n'
		<< "Which means the overflow should occur at index 47."
		<< '\n' << '\n';

	std::cout
		<< "How many numbers do you want to generate? "
		<< '\n' << "(Enter 0 to generate numbers until overflow)."
		<< '\n' << '\n';

	int fib_count{};
	if (!(std::cin >> fib_count)) {
		error("Invalid input");
	}
	if (fib_count == 0) {
		fib_count = FIB_MAX_IDX;
	}

	std::cout << '\n';

	vector<int> fib_v{ gen_fib_numbers(fib_count) };
	if (fib_v.size() < fib_count) {
		std::cerr
			<< "Error: The sequence was truncated, most likely due to "
			<< "type overflow" << '\n';
	}


	std::cout
		<< '\n'
		<< "Fibonnacci numbers 1 to " << fib_v.size()
		<< '\n' << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		<< '\n' << join_w_space(fib_v)
		<< '\n';

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
