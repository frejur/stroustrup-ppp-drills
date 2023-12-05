#ifndef TEST_BOOK_H
#define TEST_BOOK_H

#include <exception>
#include <iostream>
#include "../lib/book.h"

void print(const Book& b) {
	std::cout
		<< "ISBN: " << b.ISBN() << ", "
		<< "Title: " << b.title() << ", "
		<< "Author: " << b.author() << ", "
		<< "Copyright date: " << b.copyright_date() << ", "
		<< "Is checked-out?: " << ( (b.is_checked_out()) ? "Yes" : "No" )
		<< '\n';
}

void test_book_init() {
	std::cout << "Attempting to create invalid instances of Book..." << '\n';

	int max_step = 8;
	int step = 0;
	while (step < max_step)
	try {
		++step;
		std::cout << "Step " << step << ": ";
		if (step == 1)
			Book b{"TooLoooooooong", "Title", "Author", {}};
		if (step == 2)
			Book b{"TooShort", "Title", "Author", {}};
		if (step == 3)
			Book b{"X00-200-300-X", "Title", "Author", {}};
		if (step == 4)
			Book b{"10--200-300-X", "Title", "Author", {}};
		if (step == 5)
			Book b{"1-2-3-4-5-6-X", "Title", "Author", {}};
		if (step == 6)
			Book b{"1---2-3-5-6-X", "Title", "Author", {}};
		if (step == 7)
			Book b{"100-200-300-A", "Title", "Author", {}};
		if (step == 8)
			Book b{"10000000000-X", "Title", "Author", {}};
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void test_book_checkout_checkin(Book &b) {
	std::cout << "Test check-in / check-out..." << '\n';

	int max_step2 = 4;
	int step2 = 0;
	while (step2 < max_step2)
		try {
			++step2;
			std::cout << "Step " << step2 << ": ";
			if (step2 == 1) {
				std::cout << "Attempting to check in a book that is already"
				             " checked-in" << '\n';
				b.check_in();
			}
			if (step2 == 2) {
				std::cout << "Checking out a book.." << '\n';
				b.check_out();
				print(b);
			}
			if (step2 == 3) {
				std::cout << "Attempting to check out a book that is already"
				             " checked-out" << '\n';
				b.check_out();
			}
			if (step2 == 4) {
				std::cout << "Checking in a book.." << '\n';
				b.check_in();
				print(b);
			}
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
}

void test_book_operators(const Book& a, const Book& b) {
	std::cout << "Testing operators..." << '\n'
	          << "Book A == book A : " << ( a == a ? "TRUE" : "FALSE" ) << '\n'
	          << "Book A != book A : " << ( a != a ? "TRUE" : "FALSE" ) << '\n'
	          << '\n'
	          << "Book A == book B : " << ( a == b ? "TRUE" : "FALSE" ) << '\n'
	          << "Book A != book B : " << ( a != b ? "TRUE" : "FALSE" ) << '\n'
	          << '\n'
	          << "Printing A using '<<': " << '\n' << a << '\n'
	          << "Printing B using '<<': " << '\n' << b;
}

Book test_genre(Genre genre) {
	std::cout << "Creating a book with a non-default genre..." << '\n';
	Book b{"0-11-222222-3", "New book", "New author", {}, genre };
	std::cout << b;
	return b;
	}

void test_book_class() {
	test_book_init();

	std::cout << '\n';

	std::cout << "Creating a valid instance of Book..." << '\n';
	Book a{"100-200-300-x", "A title", "An author", {}};
	print(a);

	std::cout << '\n';

	test_book_checkout_checkin(a);

	std::cout << '\n';

	std::cout << "Creating a valid instance of Book..." << '\n';
	Book b{"3000-20-999-0", "Another title", "Another author", {}};
	print(b);

	std::cout << '\n';

	test_book_operators(a, b);

	std::cout << '\n';

	test_genre(Genre::Children);
}

#endif // TEST_BOOK_H
