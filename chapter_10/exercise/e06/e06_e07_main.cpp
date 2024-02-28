#include "help/help.h"
#include "roman/roman.h"
#include "test/test_roman.h"
#include <exception>
#include <iostream>

/* Chapter 10, exercise 6 and 7: Roman numerals
 * 
 * Exercise 6
 *   Define class Roman_int that holds an integer in Roman numeral notation,
 *   with a member function called as_int() that returns the value as <int>.
 * 
 * Exercise 7
 *   Bring in the Calculator program from chapter 6 and make it work with
 *   values of type <Roman_int> created in the earlier exercise.
 * 
 * Differences from the exercises outline in the book:
 * - Read in test cases from a .txt file.
 * - Merge the exercises into one program, prompt the user to either:
 *   a. Run a series of tests on the Roman_int class.
 *   b. Run the Calculator
 */

int main()
try {
	std::cout << "Roman numerals" << '\n';
	std::cin.get();

	trom::run_tests();

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
