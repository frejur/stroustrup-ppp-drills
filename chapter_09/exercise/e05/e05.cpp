// Chapter 9, Exercise 5 to 9: A Library of classes

// These exercises describe a set of classes and operators used to manage a
// virtual library.

#include <exception>
#include <iostream>
#include "test/test_book.h"
#include "test/test_patron.h"

int main()
try {
	// test_book_class();
	test_patron_class();

	std::cin.get();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error";
	return 2;
}
