#include <exception>
#include <iostream>
#include "money/money.h"
#include "test/test.h"
#include "test/test_interactive.h"

/* Chapter 9, Exercise 14 - 16. Money class.
 *
 * Design and implement a Money class (Merged exercises 14 to 16)
 *
 * The monetary amount should be:
 *   Represented as the number of centesimal monetary units.
 *   Stored in a variable of type <long>.
 *
 * The result of any calculation is accurate to the last centesimal unit,
 * through the use of rounding ( x < 0.5 = 0, x >= 0.5 = 1).
 *
 * Input and output should be represented as the 'cents' divided by 100
 * followed by the currency:
 *   <Floating-point-literal><CURRENCY>
 *   e.g. '123.45USD' or '67.89EUR'
 *
 * The currency (Class enum) is supplied on intialization.
 * Implement the ostream '<<' and istream '>>' operators accordingly.
 *
 * Only allow initialization by floating-point value if the given number can
 * be exactly represented as a number of centesimal units.
 *
 * Implement a conversion table for the included Currencies.
 *
 * When implementing the arithmetic operators, and comparison operators:
 *   Money * Money is not allowed.
 *   Convert the operands to the same currency before calculating.
 */

using namespace Money_lib;

enum class Selection { Quit=0, Run_tests, Expression_parser };

Selection get_selection(std::istream& is) {
	Selection s{ Selection::Quit };
	char temp{};

	try {
		is.get(temp);
		if (temp == 'a') {
			s = Selection::Run_tests;
		} else if (temp == 'b') {
			s = Selection::Expression_parser;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		throw std::runtime_error("Unknown error");
	}

	if (temp != '\n') {
		clear_buffer(is);
	}
	return s;
}

int main()
try {
	std::cout
		<< "Money class" << '\n' << '\n'
		<< "Enter 'a' to run a series of tests." << '\n'
		<< "Enter 'b' to run a very basic expression parser." << '\n'
		<< "(Any other input will exit the program)" << '\n';

	std::cout << "> ";
	Selection s{ get_selection(std::cin) };
	if (s == Selection::Run_tests) {
		test_all();
	} else if (s == Selection::Expression_parser) {
		test_interactive();
	}

	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 1;
}
catch (...) {
	std::cerr << "Error: Unknown error" << '\n';
	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 2;
}
