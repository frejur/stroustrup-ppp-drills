#include "e06_e07_e10_main.h"
#include "calc/calc.h"
#include "help/help.h"
#include "roman/roman.h"
#include "test/test_calc.h"
#include "test/test_roman.h"
#include <exception>
#include <iostream>

/* Chapter 10, exercise 6, 7 and 10: Roman numerals and calculator fstream
 * =======================================================================
 * 
 * Exercise 6
 * ----------
 * - Define class Roman_int that holds an integer expressed in Roman numeral
 *   notation. Add member function 'as_int()' that returns the value as <int>.
 * 
 * Exercise 7
 * ----------
 * - Bring in the Calculator program from Chapter 6 and 7, and make it work with
 *   values of type <Roman_int> created in the earlier exercise.
 *   
 * Exercise 10
 * -----------
 * - Add functions to the calculator from Chapter 6 and 7 that read and write
 *   to / from disk.
 * - Add two new commands to the calculator: 'from x' and 'to y', that use
 *   this new functionality.
 * - Also use the commands to run a series of calculator tests.
 * - Discuss how these commands can be used for testing.
 *   (See 'ch10_e10_discussion.md')
 * 
 * Differences from the exercises outlined in the book:
 * ----------------------------------------------------
 * - Merge the exercises into one program, prompt the user to select one of
 *   the following options:
 *   a. Run a series of tests on the Roman_int class.
 *      (Read in test cases from a .txt file)
 *   b. Run the Calculator, decimal version.
 *   c. Run the Calculator, Roman numerals version.
 *   d. Run a series of Calculator tests, decimal-point version.
 *   e. Run a series of Calculator tests, Roman numerals version.
 * - Add some constraints to the fstream functionality:
 *   1. Hardcode all file paths.
 *   2. Disable the 'from x' and 'to y' commands while reading from an ifstream.
 *   3. Count the number of characters as they are being read from / written to
 *      the file, abort if the count exceeds a certain limit.
 * - The calculator has been refactored to operate on User Defined Objects
 *   of type <Result> instead of <double>. This way the same codebase can be
 *   used for different versions of the Calculator. In this case, one version
 *   operates on <double>'s, the other on <Roman_int>'s. In theory you could mix
 *   types, but this has not been implemented for this exercise.
 */

int main()
try {
	e6_7_10::print_hello();

	char select = 0;
	bool first_iter = true;
	while (select != e6_7_10::select_quit) {
		if (first_iter) {
			first_iter = false;
		} else {
			std::cout << '\n';
		}

		e6_7_10::print_options();

		std::cout << e6_7_10::symbol_prompt << ' ';

		select = e6_7_10::get_selection();
		switch (select) {
		case e6_7_10::select_test_roman:
			trom::run_tests();
			break;
		case e6_7_10::select_calc_decimal:
			calc::run();
			break;
		case e6_7_10::select_calc_roman:
			calc::run(calc::Calculator_version::Roman);
			break;
		case e6_7_10::select_test_calc_decimal:
			tcal::run_calculator_tests(calc::Calculator_version::Decimal);
			break;
		case e6_7_10::select_test_calc_roman:
			tcal::run_calculator_tests(calc::Calculator_version::Roman);
			break;
		case '\n':
			continue;
		case e6_7_10::select_quit:
			break;
		case e6_7_10::select_unknown:
		default:
			std::cout << "Invalid character" << '\n';
			continue;
		}
	}

	e6_7_10::print_goodbye();
	return 0;
} catch (const trom::Test_case& t) {
	std::cerr << "Error: " << t;
	return 1;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}

char e6_7_10::get_selection()
{
	char select = 0;
	std::cin.get(select);
	if (select != '\n') {
		help::clear_buffer(std::cin);
	}
	return select;
}
