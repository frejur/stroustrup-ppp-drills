// Chapter 9, Exercise 5 to 9: A Library of classes

// These exercises describe a set of classes and operators used to manage a
// virtual library.

#include "../../lib/help.h"
#include "test/test_date.h"
#include <exception>
#include <iostream>

int main()
try {
	std::cout
		<< "Date class helpers" << '\n'
	    << "This program runs a series of tests on the Date class "
	       "and its helper functions."
	    << '\n';

	std::cout << "Enter any character to proceed" << '\n';
	help::wait_for_enter();

	test_date();

	std::cout << '\n'
	          << "All tests ran without causing the program to end prematurely!"
	          << '\n';

	std::cout << "Enter any character to exit" << '\n';
	help::wait_for_enter();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Unexpected error: " << e.what() << '\n';
	std::cout << "Enter any character to exit" << '\n';
	help::wait_for_enter();
	return 1;
}
catch (...) {
	std::cerr << "Unexpected unknown error" << '\n';
	std::cout << "Enter any character to exit" << '\n';
	help::wait_for_enter();
	return 2;
}
