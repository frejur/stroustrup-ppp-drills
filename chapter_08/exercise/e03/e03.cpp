#include "../../lib/std_lib_facilities.h"

// Chapter 8 Exercise 3 and 4. Fibonacci numbers revisited

// Rewrite the function that generates the sequence of numbers as:
//   fibonacci(x, y, v, n)
//         <int> x : First number in seq. (Needs validation)
//         <int> y : Second number in seq. (Also needs validation)
// <vector<int>> v : Reference to an empty vector. The seq. of numbers.
//         <int> b : The number of elements to put into <vector> v.

// Write out Fibonacci numbers.
// Prompt for the the two first numbers X and Y of the fibonacci seq.
// Prompt for the desired size of the sequence to generate.
// 1 1 2 3 5 8 13 21 34 (Each new number is the sum of the two prev. ones).
// If the user enters 'overflow', keep printing numbers until it causes integer
// overflow.

// Integers are assigned 4 bytes (32 bits) on a typical desktop computer

namespace CONST { //------------------------------------------------------------

constexpr double COMMON_INT_MAX{(double)
								2*2 * 2*2 * 2*2 * 2*2 *
								2*2 * 2*2 * 2*2 * 2*2 *
								2*2 * 2*2 * 2*2 * 2*2 *
								2*2 * 2*2 * 2*2 * 2
								- 1 };

constexpr int FIB_MAX_IDX{ 100 }; // Should be more than enough

} // CONST ---------------------------------------------------------------------

// Fibonnaci functions

bool is_perfect_sq(int n) {
	if (n < 0) {
		return false;
	}
	double sq = sqrt(n);
	return sq == (double)static_cast<int>(sq);
}

bool is_fib(int n) {
	if (n < 1) {
		return false;
	}
	double sq = 5 * (double)n*n;
	return (is_perfect_sq(sq + 4) || is_perfect_sq(sq - 4));
}

// Moves the stack one step forward (before last, last and current).
// Sets the last item in the stack to the next number in the fibonacci seq.
// Sets it to 0 on integer overflow.
void next_fib(vector<int>& stack) {
	if (stack.size() == 0) {
		stack = { 0, 0, 1 }; // first iteration
		return;
	}
	try {
		stack.at(0) = stack.at(1);      // before last
		stack.at(1) = stack.at(2);      // last
		stack.at(2) = narrow_cast<int>( // current
			(double) stack.at(0) + (double) stack.at(2));
	}
	catch (...) {
		stack.at(2) = 0;
	}
}

void fibonacci(int x, int y, vector<int>& v, int n)
{
	if (v.size() > 0) {
		error("Vector must be empty");
	}
	if (n < 2) {
		error("Length of seq. should be greater than 1.");
	}
	if (y < x) {
		error("X is greater than Y but should precede it");
	}
	if (!is_fib(x) || !is_fib(y)) {
		error("X or Y is not a fibonacci number");
	}

	bool x_is_confirmed{ false };
	vector<int> stack{}; // { before last, last, current }
	while (n > 0) {
		next_fib(stack);
		if (!stack.at(2)) {
			break;
		}
		if (x_is_confirmed) {
			v.push_back(stack.at(2));
			--n;
		} else if (stack.at(2) == x) {
			x_is_confirmed = true;
			next_fib(stack);
			if (!stack.at(2)) {
				break;
			}else if (stack.at(2) != y) {
				error("Y does not follow X");
			} else {
				v.push_back(stack.at(1));
				v.push_back(stack.at(2));
				n -= 2;
			}
		}
	}
}

//------------------------------------------------------------------------------
// String helpers

std::string join_w_space(const vector<int>& v) {
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
//------------------------------------------------------------------------------
// Print stuff

void print_hello() {
	std::cout << "Program that writes out Fibonacci numbers." << '\n'
			  << '\n'
			  << "An error will be thrown if a number exceeds the" << '\n'
			  << "<int> type max value. The max value is system dependent" << '\n'
			  << "but usually 32 bits: "
			  << strip_trailing_zeros(std::to_string(CONST::COMMON_INT_MAX))
			  << '\n'
			  << '\n'
			  << "Which means the overflow should occur at index 47." << '\n'
			  << '\n';

	std::cout << "Please enter the 2 first numbers in the sequence."
			  << " (Or type 'overflow' to test overflow)" << '\n'
			  << '\n';
}

void print_fib(const vector<int>& fib_v) {
	std::cout << '\n'
			  << "Fibonnacci numbers " << fib_v.front() << " to "
			  << fib_v.back() << '\n'
			  << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			  << '\n'
			  << join_w_space(fib_v) << '\n';
}

void print_overflow(const vector<int>& fib_v) {
	std::cerr << "Error: The sequence was truncated, most likely due to "
			  << "type overflow." << '\n' << '\n'
			  << "The last number generated was:" << '\n'
			  << fib_v.back() << '\n'
			  << "The number after that would be (Using <double>):" << '\n'
			  << strip_trailing_zeros(std::to_string(
				 (double)fib_v.at(fib_v.size() - 1) +
				 (double)fib_v.at(fib_v.size() - 2)
				 )) << '\n'
			  << "The <int> max lies somewhere in-between those numbers."
			  << '\n';
}

//------------------------------------------------------------------------------
// Input

int user_wants_overflow() {
	std::string s{};
	std::cin >> s;
	if (s != "overflow") {
		for (int i = s.size() - 1; i >= 0; --i) {
			std::cin.putback(s.at(i));
		}
		return false;
	}
	return true;
}

void get_params(int& x, int&y, int& n) {
		std::cin >> x >> y;
		std::cout << "Please enter how many numbers you wish to generate."
				  << '\n';
		std::cin >> n;
}

//------------------------------------------------------------------------------

int main()
try {
	print_hello();

	int x{}, y{}, n{};
	if (user_wants_overflow()) {
		x = 1;
		y = 1;
		n = CONST::FIB_MAX_IDX;
	} else {
		get_params(x, y, n);
	}

	vector<int> fib_v{};
	fibonacci(x, y, fib_v, n);

	if (fib_v.size() < n) {
		print_overflow(fib_v);
	}

	print_fib(fib_v);

	keep_window_open();
	return 0;
}
catch (std::exception &e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
