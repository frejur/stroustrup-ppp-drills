#include <exception>
#include <iostream>
#include "test/test.h"

/* Chapter 9, Exercise 13. Rational number.
 *
 * Design and implement a rational number class.
 *
 * A rational number can be represented as p / q:
 *   p and q must be integers
 *   q must not be 0 (zero)
 *
 * Provide operators:
 *   Addition
 *   Subtraction
 *   Multiplication
 *   Division
 *   Equality
 *
 * Also provide a conversion to type <double>
 */

int main()
try {
	std::cout
		<< "Rational number class" << '\n' << '\n'
		<< "Press <ENTER> to run a series of tests" << '\n';
	std::cin.get();

	test_gcd_multiple();
	std::cout << '\n';
	test_r_opmult_multiple();
	std::cout << '\n';
	test_r_opdiv_multiple();
	std::cout << '\n';
	test_r_opadd_multiple();
	std::cout << '\n';
	test_r_opsub_multiple();
	std::cout << '\n';
	test_to_double_multiple();

	std::cout << '\n'
		<< "All tests passed without terminating the program pre-maturely!"
		<< '\n' << '\n';

	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what();
	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 1;
}
catch (...) {
	std::cerr << "Error: Unknown error";
	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 2;
}
