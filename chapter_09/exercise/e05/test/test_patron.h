#ifndef TEST_PATRON_H
#define TEST_PATRON_H

#include <exception>
#include <iostream>
#include "../lib/patron.h"
#include "print_helpers.h"

void test_patron_init() {
	std::cout << "Attempting to create invalid instance of Patron..." << '\n';

	int max_step = 9;
	int step = 0;
	while (step < max_step)
	try {
		++step;
		std::cout << "Step " << step << ": ";
		if (step == 1)
			Patron p{ "", "123456" };
		if (step == 2)
			Patron p{ " A", "123456" };
		if (step == 3)
			Patron p{ "A-", "123456" };
		if (step == 4)
			Patron p{ "A-B--C", "123456" };
		if (step == 5)
			Patron p{ "A-B  C", "123456" };
		if (step == 6)
			Patron p{ "A-bcd*fgh", "123456" };
		if (step == 7)
			Patron p{ "Valid Name-Test", "12345" };
		if (step == 8)
			Patron p{ "Valid Name-Test", "a23456" };
		if (step == 9)
			Patron p{ "Valid Name-Test", "023456" };
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void test_patron_fees(Patron& p) {
	std::cout << "Attempting to add a fee with a zero value amount..." << '\n';
	try {
		p.add_fee(0, {});
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << "Adding a fee with the default date value..." << '\n';
	p.add_fee(50);

	Date today{ 2023, Month::dec, 5 };
	std::cout << '\n' << "Setting today's date to: " << today << '\n' << '\n';
	std::cout << "Adding a fee with today's date..." << '\n';
	p.add_fee(25, today);

	PRINT::print(p.all_fees());
	PRINT::print(p);

	std::cout << '\n';

	std::cout << "Attempting to access a non-existant fee..." << '\n';
	try {
		Fee f{ p.single_fee(5) };
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << '\n';

	std::cout << "Marking the first fee as paid..." << '\n';
	p.mark_fee_as_paid(0);
	PRINT::print(p.all_fees());
	PRINT::print(p);

	std::cout << '\n';

	std::cout << "Attempting to mark first fee as paid AGAIN..." << '\n';
	try {
		p.mark_fee_as_paid(0);
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << '\n';

	std::cout << "Marking the second fee as paid, with a note..." << '\n';
	p.mark_fee_as_paid(1, "Here's a note");
	PRINT::print(p.all_fees());
	PRINT::print(p);

	std::cout << '\n';

	std::cout << "Updating the comment of the first fee..." << '\n';
	p.update_fee_comment(0, "Here's another note");
	PRINT::print(p.all_fees());
}

void test_patron_class() {
	test_patron_init();

	std::cout << '\n';

	std::cout << "Creating a valid instance of Patron..." << '\n';
	Patron p{ "Valid Name-Test", "100001" };

	PRINT::print(p);

	std::cout << '\n';

	test_patron_fees(p);
}

#endif // TEST_PATRON_H
