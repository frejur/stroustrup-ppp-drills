// Chapter 9, Exercise 5 to 9: A Library of classes

// These exercises describe a set of classes and operators used to manage a
// virtual library.

#include <exception>
#include <iostream>
#include "test/test_book.h"
#include "test/test_patron.h"
#include "test/test_library.h"

int main()
try {
	std::cout
		<< "A Library of classes" << '\n'
	    << "This program runs a series of tests on the Library class" << '\n'
	    << "and its sub-objects (Check out the readme.md for more details)"
	    << '\n';

	std::cout << "Enter any character to proceed" << '\n';

	std::cin.get();

	test_book_class();
	test_patron_class();
	test_library_class();

	std::cout
		<< "All tests ran without causing the program to end pre-maturely!"
		<< '\n';

	std::cout << "Enter any character to exit" << '\n';
	std::cin.get();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Unexpected error: " << e.what();
	std::cout << "Enter any character to exit" << '\n';
	std::cin.get();
	return 1;
}
catch (...) {
	std::cerr << "Unexpected unknown error";
	std::cout << "Enter any character to exit" << '\n';
	std::cin.get();
	return 2;
}
