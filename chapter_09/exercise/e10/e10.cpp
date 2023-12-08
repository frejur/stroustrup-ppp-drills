// Chapter 9, Exercise 5 to 9: A Library of classes

// These exercises describe a set of classes and operators used to manage a
// virtual library.

#include <exception>
#include <iostream>
#include "test/test_date.h"

int main()
try {
	std::cout
		<< "Date class helpers" << '\n'
	    << "This program runs a series of tests on the Date class "
	       "and its helper functions."
	    << '\n';

	std::cout << "Enter any character to proceed" << '\n';

	std::cin.get();

	test_date();

	std::cout << '\n'
	          << "All tests ran without causing the program to end prematurely!"
	          << '\n';

	std::cout << "Enter any character to exit" << '\n';
	std::cin.get();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Unexpected error: " << e.what() << '\n';
	std::cout << "Enter any character to exit" << '\n';
	std::cin.get();
	return 1;
}
catch (...) {
	std::cerr << "Unexpected unknown error" << '\n';
	std::cout << "Enter any character to exit" << '\n';
	std::cin.get();
	return 2;
}
