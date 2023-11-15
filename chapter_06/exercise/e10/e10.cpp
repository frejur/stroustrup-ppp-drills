#include "../../lib/std_lib_facilities.h"

// Chapter 6, Exercise 10. Permutations and Combinations.

//	Prompt the user for integers a and b.
//	Prompt for 'p' or 'c':
//		'p'	Calculate permutations P(a, b)
//		'c' Calculate combinations C(a, b)

// Additions:
//		Added graceful exit keyword

// ===== Pseudo code ===========================================================

// Note that some minor changes were made to the actual code but at that point
// it doesn't make sense to go back and update the corresponding pseudo code...

// Main Loop -------------------------------------------------------------------
// Print greeting and intro.
// Print question: Ask user for two integers 'a' and 'b'.
// Declare instance of class <Result> 'result'.
// Keep feeding integer values into variable a and b while cin is good.
// In the while loop, after two integers have been registered:
//		Print question: Permutations or combinations, ask for 'p' or 'c'.
//		Keep feeding chars into <char> type of 'result' while cin is good.
//		If pc == 'p' or 'c':
//			Proceed to calculate permutations or combinations using
//			corresponding functions, store result in 'result' declared earlier.
//			Break out of integer while loop
//		Else:
//			Reprint question from before.
//			(Loop starts over)
// If cin is in a bad state:
//		Throw input error
// Else:
//		Print result
//------------------------------------------------------------------------------

// Class 'Result' --------------------------------------------------------------
// Store <int> value, and <char> type = 'c' or 'p' (combinations or permut.)
//------------------------------------------------------------------------------

// Permutations function -------------------------------------------------------
// Given integers a and b, returns the number of permutations <int> p.
//
// Formula:        a!
//          p = _________
//              (a - b)!
//
// Throw error is a or b < 1
// Throw error if b > a
// Run factorial function with a and store in <double> a_fact
// Run factorial function with b and store in <double> a_min_b_fact
// Check for integer overflow with 'narrow_cast'.
// Calculate and return p
//------------------------------------------------------------------------------

// Combinations function -------------------------------------------------------
// Given integers a and b, returns the number of combinations <int> c.
//
// Formula:     Permutations(a, b)
//          c = __________________
//                     b!
//
// Because this function depends on the Permutations function we rely on the
// error checking of the latter to ensure a and b are legal. We then also assume
// there is no integer overflow.
//
// Run permutation function with a and b, store result in <int> ab_perm
// Run factorial function with b and store in <double> b_fact
// Calculate and return c
//------------------------------------------------------------------------------

// Factorial function ----------------------------------------------------------
// Lifted from Exercise 3
//------------------------------------------------------------------------------

class Result {
public:
	int value{};
	char type{' '};
};

double calc_factorial(double n) {
	if (n < 0) {
		error("Cannot calculate factorial for n < 0");
	}
	if (n == 0) {
		return 1;
	}
	int n_int{};
	try {
		n_int = narrow_cast<int>(n);
	} catch (...) {
		error("Factorials of floating-point values not supported");
	}
	double f{ (double)n_int };
	for (int i = n_int - 1; i > 0; --i) {
		f *= i;
	}
	return f;
}

int calc_permutations(int a, int b) {
	if (a < 1 || b < 1) {
		error("Parameters a and be must be greater than zero.");
	}
	if (b > a) {
		error("Parameter b cannot be greater than parameter a");
	}

	double a_fact{ calc_factorial((double)a) };
	double a_min_b_fact{ calc_factorial((double)a - b) };
	int p{};
	try {
		p = (int)narrow_cast<int>(a_fact / a_min_b_fact);
	} catch (...) {
		error("Integer overflow when calculating permutations");
	}
	return p;
}

int calc_combinations(int a, int b) {
	// Assumes calc_permutations() validates a and b
	int ab_perm{ calc_permutations(a, b) };
	int b_fact{ (int)calc_factorial(b) };

	return ab_perm / b_fact;
}

void output_result(Result result) {
	std::cout << "= " << result.value << " ";
	if (result.type == 'p') {
		std::cout << "permutation";
	} else {
		std::cout << "combination";
	}
	if (result.value > 1) {
		std::cout << "s";
	}
	std::cout << '\n' << '\n';
}

bool should_exit(std::string exit_key_word) {
	std::string s{};
	std::cin >> s;
	if (s == exit_key_word) {
		return true;
	}
	for (char c : s) {
		std::cin.putback(c);
	}
	return false;
}

int main()
try {
	static const std::string QUIT { "QUIT" }; // Graceful exit keyword
	std::cout
		<< "Permutations and Combinations" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n'
		<< "This program calculates the # of permutations/combinations" << '\n'
		<< "for variables 'a' and 'b', where:"<< '\n'
		<< '\n'
		<< " a = the size of the full set" << '\n'
		<< "    'The total number of items in the sample'" << '\n'
		<< '\n'
		<< " b = the size of the subset" << '\n'
		<< "     'The number of items to be selected from the sample'"
		<< '\n' << '\n'
		<< "Enter '" << QUIT << "' to terminate the program."
		<< '\n' << '\n';

	static const std::string TXT_ASK_A_B {
		"Enter two integer values, one for 'a' the other for 'b'."
	};
	static const std::string TXT_ASK_P_C { "Please enter 'p' or 'c'." };

	Result result{};
	int a{}, b{};
	std::cout << TXT_ASK_A_B << '\n';
	bool gracefully_exiting { false };
	while (
		!gracefully_exiting
		&& !(gracefully_exiting = should_exit(QUIT))
		&& std::cin >> a >> b
	) {
		std::cout << '\n'
			<< "Would you like to calculate the number of permutations" << '\n'
			<< "or combinations?" << ' ';
		std::cout << TXT_ASK_P_C << '\n';
		while (
			!gracefully_exiting
			&& !(gracefully_exiting = should_exit(QUIT))
			&& std::cin >> result.type
		) {
			if (result.type != 'p' && result.type != 'c') {
				std::cout << TXT_ASK_P_C << '\n';
				continue;
			}
			if (result.type == 'p') {
				result.value = calc_permutations(a, b);
			}
			if (result.type == 'c') {
				result.value = calc_combinations(a, b);
			}
			output_result(result);
			break;
		}
		if (!gracefully_exiting) {
			std::cout << TXT_ASK_A_B << '\n';
		}
	}
	if (!std::cin) {
		// assumes cin >> char never fails
		error("Expected integer values for 'a' and 'b'");
	}
	std::cout << '\n' << "Good bye!" << '\n';

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
