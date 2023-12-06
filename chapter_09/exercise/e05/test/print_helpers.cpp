#include "print_helpers.h"
#include <iostream>

namespace PRINT{ //-------------------------------------------------------------


void print(const Book& b) {
	std::cout
		<< "ISBN: " << b.ISBN() << ", "
		<< "Title: " << b.title() << ", "
		<< "Author: " << b.author() << ", "
		<< "Copyright date: " << b.copyright_date() << ", "
		<< "Genre: " << b.genre() << ", "
		<< "Is checked-out?: " << ( (b.is_checked_out()) ? "Yes" : "No" )
		<< '\n';
}

void print(const Patron& p) {
	std::cout
		<< "User name: " << p.user_name() << ", "
		<< "Card number: " << p.card_number() << ", "
		<< "Has unpaid fees: " << (p.has_unpaid_fees() ? "Yes" : "No") << ", "
		<< "Debt: " << p.debt()
		<< '\n';
}

void print(const std::vector<Fee>& fees) {
	for (const Fee& f : fees) {
		std::cout << "ID: " << f.id << ", "
		          << "Amount: " << f.amount << ", "
		          << "Registered: " << f.registered << ", "
		          << "Comment: " << f.comment << ", "
		          << "Status: " << (f.is_paid ? "Paid" : "NOT paid" )
		          << '\n';
	}
}

void print(const std::vector<Book>& books)
{
	for (const Book& b : books) {
		print(b);
	}
}

void print(const std::vector<Patron>& patrons)
{
	for (const Patron& p : patrons) {
		print(p);
	}
}

void print(const std::vector<Transaction>& transactions)
{
	for (const Transaction& tx : transactions) {
		std::cout
			<< "ID: " << tx.id << ", "
			<< "ISBN: " << tx.isbn << ", "
			<< "Card: " << tx.card_number << ", "
			<< "User: " << tx.user_name << ", "
			<< "Date: " << tx.date << ", "
			<< "Type: " << tx.type << '\n';
	}
}

void print(const std::vector<std::string>& v)
{
	for (const std::string& s : v) {
		std::cout << s << '\n';
	}
}

} // PRINT ---------------------------------------------------------------------
