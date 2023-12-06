#ifndef TEST_LIBRARY_H
#define TEST_LIBRARY_H

#include <exception>
#include <iostream>
#include "../lib/library.h"
#include "print_helpers.h"
#include "../sample/sample_books.h"
#include "../sample/sample_patrons.h"

void test_add_books(Library& lib) {
	Book b{ "123-456-789-X", "Test Title", "Test Author", {} };
	std::cout << "Adding a book to the library, "
	             "then attempting to add it again" << '\n';
	lib.add_book(b);
	try {
		lib.add_book(b);
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	std::cout << '\n'
	          << "Attempting to add a book that is checked-out from the "
	             "start..." << '\n';
	Book chkd_in_book { "555-555-555-5", "Checked-out", "Some Author", {} };
	chkd_in_book.check_out();
	try {
		lib.add_book(chkd_in_book);
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}


void test_add_patrons(Library& lib) {
	std::string card_num { "100000" };
	Patron p{ "Test User", card_num };
	std::cout << "Adding a patron to the library, "
	             "then attempting to add him/her again "
	             "using the same card number" << '\n';
	lib.add_patron(p);
	try {
		Patron p2{ "Another Test User", card_num };
		lib.add_patron(p);
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}


void test_check_out_existing(Library& lib,
                             const std::string& existing_isbn,
                             const std::string& non_existing_isbn,
                             const std::string& existing_card,
                             const std::string& non_existing_card
) {
	std::cout << "Attempting to check out books..." << '\n';

	try {
		lib.check_out(non_existing_isbn, existing_card, {});
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	try {
		lib.check_out(existing_isbn, non_existing_card, {});
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void test_check_in_existing(Library& lib,
                            const std::string& existing_isbn,
                            const std::string& non_existing_isbn
) {
	std::cout << "Attempting to check in books..." << '\n';

	try {
		lib.check_in(non_existing_isbn, {});
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	try {
		lib.check_in(existing_isbn, {});
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

inline void check_out_book(Library& lib, const Book& book, const Patron& patron)
{
	try {
		lib.check_out(book.ISBN(),
					  patron.card_number(), {});
	}
	catch (std::exception& e) {
		std::cout << patron.user_name() << " attempts to check out "
			<< '\'' << book.title() << "'..." << '\n';
		std::cerr << "Error: " << e.what() << '\n';
		return;
	}
	std::cout << patron.user_name() << " successfully checked out '"
			  << book.title() << "'..." << '\n';
}

inline void check_in_book(Library& lib, const Book& book,
                          bool force_check_in=false
) {
	try {
		lib.check_in(book.ISBN(), {}, force_check_in);
	}
	catch (std::exception& e) {
		std::cout << "Attempting to "
		          << (force_check_in ? "forcefully " : "" )
		          << "check in '" << book.title() << "'..."
		          << '\n';
		std::cerr << "Error: " << e.what() << '\n';
		return;
	}
	std::cout << '\'' << book.title() << '\''
	          << " was "
              << (force_check_in ? "FORCEFULLY and " : "")
              << "successfully checked back in" << '\n';
}

inline void purge_book_transaction(Library& lib, int tx_id) {
	try {
		lib.purge_transaction(tx_id);
	} catch (std::exception& e) {
		std::cout << "Attempting to purge a transaction with the ID: " << tx_id
	              << '\n';
		std::cerr << "Error: " << e.what() << '\n';
		return;
	}
	std::cout << "Successfully purged a transaction with the ID: " << tx_id
	          << '\n';
}

inline void test_purge_transactions(Library& lib) {
	int num_tx{ static_cast<int>(lib.all_transactions().size()) };
	purge_book_transaction(lib, num_tx);
	purge_book_transaction(lib, num_tx-1);
	purge_book_transaction(lib, num_tx-1);
}


void test_transactions(Library& lib,
					   const std::vector<Book>& books,
					   const std::vector<Patron>& patrons)
{
	check_out_book(lib, books.front(), patrons.front());
	check_out_book(lib, books.front(), patrons.front());
	check_in_book(lib, books.front());
	std::cout << "Transactions:" << '\n';
	PRINT::print(lib.all_transactions());

	std::cout << '\n';

	check_out_book(lib, books[1], patrons[1]);
	check_out_book(lib, books[2], patrons[2]);
	std::cout << "Transactions:" << '\n';
	PRINT::print(lib.all_transactions());

	std::cout << '\n';

	test_purge_transactions(lib);

	std::cout << "Transactions:" << '\n';
	PRINT::print(lib.all_transactions());

	std::cout << '\n';

	check_in_book(lib, books[2]);
	check_in_book(lib, books[2], true);

	// Check out a book that is marked as checked-in, but where the latest
	// transaction for the book is not Empty or a Check-in

	std::cout << '\n';

	purge_book_transaction(lib, 1);

	std::cout << "Transactions:" << '\n';
	PRINT::print(lib.all_transactions());

	std::cout << '\n'
	          << "Books" << '\n';

	PRINT::print(lib.all_books());

	std::cout << '\n';

	check_out_book(lib, books[0], patrons[3]);
	check_in_book(lib, books[0]);
	check_in_book(lib, books[0], true);
	check_out_book(lib, books[0], patrons[3]);

	std::cout << '\n'
	          << "Transactions:" << '\n';
	PRINT::print(lib.all_transactions());
}

void test_fees(Library& lib, const Book& b, const Patron& p) {

	std::cout << "Adding fee to patron: " << p.user_name() << "...\n";
	lib.add_patron_fee(p.card_number(), 50);

	PRINT::print(lib.patron_fees(p.card_number()));
	check_out_book(lib, b, p);

	std::cout << '\n'
	          << "Marking patron " << p.user_name() << "'s fee as paid...\n";
	lib.mark_patron_fee_as_paid(p.card_number(), 0);
	check_out_book(lib, b, p);

	std::cout << "Adding another fee to patron: " << p.user_name() << "...\n";
	lib.add_patron_fee(p.card_number(), 100);
	check_in_book(lib, b);
	PRINT::print(lib.patron_fees(p.card_number()));
}

void test_blacklist(Library& lib, const Patron& p1, const Patron& p2) {
	std::cout << "Adding fees to patrons: " << p1.user_name()
	          << " and " << p2.user_name() << '\n';

	lib.add_patron_fee(p1.card_number(), 10);
	lib.add_patron_fee(p1.card_number(), 20);
	lib.add_patron_fee(p1.card_number(), 30);
	lib.add_patron_fee(p2.card_number(), 40);
	lib.add_patron_fee(p2.card_number(), 50);
	lib.add_patron_fee(p2.card_number(), 60);

	std::cout << "Patrons:" << '\n';
	PRINT::print(lib.all_patrons());

	std::cout << '\n'
	          << "Blacklist:" << '\n';
	PRINT::print(lib.blacklist());
}

void test_library_class()
{
	std::cout << "Creating a valid instance of Library..." << '\n';
	Library lib{};

	std::cout << '\n';

	test_add_books(lib);

	std::cout << '\n'
	          << "Also adding the sample books..." << '\n';
	lib.add_book(SAMPLE_BOOKS::pride());
	lib.add_book(SAMPLE_BOOKS::c_lang());
	lib.add_book(SAMPLE_BOOKS::picasso());
	lib.add_book(SAMPLE_BOOKS::horton());
	PRINT::print(lib.all_books());

	std::cout << '\n';

	test_add_patrons(lib);

	std::cout << '\n'
	          << "Also adding the sample patrons..." << '\n';
	lib.add_patron(SAMPLE_PATRONS::seymour());
	lib.add_patron(SAMPLE_PATRONS::mike());
	lib.add_patron(SAMPLE_PATRONS::amanda());
	lib.add_patron(SAMPLE_PATRONS::yuri());
	PRINT::print(lib.all_patrons());

	std::cout << '\n';
	test_check_out_existing(lib,
	                        SAMPLE_BOOKS::pride().ISBN(), "000-000-000-0",
	                        SAMPLE_PATRONS::seymour().card_number(), "333333");

	std::cout << '\n';
	test_check_in_existing(lib,
	                       SAMPLE_BOOKS::pride().ISBN(), "000-000-000-0");

	std::cout << '\n';

	test_transactions(lib,
	                  { SAMPLE_BOOKS::pride(),
	                    SAMPLE_BOOKS::c_lang(),
	                    SAMPLE_BOOKS::picasso() },
	                  { SAMPLE_PATRONS::seymour(),
	                    SAMPLE_PATRONS::yuri(),
	                    SAMPLE_PATRONS::amanda(),
	                    SAMPLE_PATRONS::mike() });

	std::cout << '\n';

	test_fees(lib, SAMPLE_BOOKS::horton(), SAMPLE_PATRONS::yuri());

	std::cout << '\n';

	test_blacklist(lib, SAMPLE_PATRONS::seymour(), SAMPLE_PATRONS::amanda());
}

#endif // TEST_LIBRARY_H
