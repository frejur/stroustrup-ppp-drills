#include "library.h"
#include <stdexcept>

Library::Library() {}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Transaction_type& tt) {
	using TT = Transaction_type;
	switch (tt) {
	case TT::Check_in:
		os << "Check-in";
		break;
	case TT::Check_out:
		os << "Check-out";
		break;
	case TT::Purged:
		os << "Purged";
		break;
	default:
		os << "UNKNOWN TYPE";
	}
	return os;
}

//------------------------------------------------------------------------------

void Library::add_book(Book b)
{
	if (book_exists(b.ISBN())) {
		throw std::runtime_error("Cannot add book, an entry with the same "
		                         "ISBN already exists");
	}
	if (b.is_checked_out() == true) {
		throw std::runtime_error("Cannot add a book that is already checked-"
								 "out");
	}
	books.push_back(b);
}

void Library::add_patron(Patron p)
{
	if (card_exists(p.card_number())) {
		throw std::runtime_error("Cannot add user, an entry with the same "
		                         "card number already exists");
	}
	patrons.push_back(p);
}

//------------------------------------------------------------------------------

void Library::check_out(const std::string& isbn, const std::string& card_number,
                        const Date& date)
{
	Book& b{ book_by_isbn(isbn) }; // note: modifying in place
	Patron p{ patron_by_card_number(card_number) };
	if (b.is_checked_out()) {
		throw std::runtime_error("Cannot check out a book that has already "
		                         "been checked out");
	}
	if (p.has_unpaid_fees()) {
		throw std::runtime_error("Cannot allow a patron with unpaid fees to "
		                         "check out a book");
	}
	const Transaction& t{ latest_tx_by_isbn(isbn) };
	if (t.type != Transaction_type::Check_in &&
	    t.type != Transaction_type::Empty) {
		throw std::runtime_error("Corrupt data, the latest transaction for the "
		                         "given ISBN is not a Check-in."   "\n"
		                         "Check in this book with "
		                         "'force_check_in=true' to check it in as "
								 "admin first");
	}
	b.check_out();
	transactions.push_back(
		{ new_tx_id(), isbn, card_number, p.user_name(), date,
		  Transaction_type::Check_out }
	);
}

void Library::check_in(const std::string& isbn, const Date& date,
                       const bool force_check_in)
{
	Book& b{ book_by_isbn(isbn) };

	if (force_check_in) {
		if (!b.is_checked_out()) {
			b.check_out();
		}
		b.check_in();
		transactions.push_back(
			{ new_tx_id(), isbn, "", "", date, Transaction_type::Check_in }
		);
		return;
	}

	if (!b.is_checked_out()) {
		throw std::runtime_error("Cannot check in a book that has not "
		                         "been checked out");
	}
	const Transaction& t{ latest_tx_by_isbn(isbn) };
	if (t.type != Transaction_type::Check_out) {
		throw std::runtime_error("Corrupt data, the latest transaction for the "
		                         "given ISBN is not a Check-out."   "\n"
		                         "Run this command with 'force_check_in=true' "
								 "to check in as admin");
	}
	Patron p{ patron_by_card_number(t.card_number) };
	if (p.has_unpaid_fees()) {
		std::cout << "REMINDER: This patron has unpaid fees.";
	}
	b.check_in();
	transactions.push_back(
		{ new_tx_id(), isbn, t.card_number, p.user_name(), date,
		  Transaction_type::Check_in }
		);
}
//------------------------------------------------------------------------------

std::vector<std::string> Library::blacklist() const
{
	std::vector<std::string> list;
	for (const Patron& p : patrons) {
		if (p.has_unpaid_fees()) {
			list.push_back(p.user_name());
		}
	}
	return list;
}
//------------------------------------------------------------------------------

void Library::purge_transaction(int tx_id)
{
	Transaction& t{ tx_by_id(tx_id) };
	if (t.type == Transaction_type::Purged) {
		throw std::runtime_error("Cannot purge a transaction that is already "
		                          "marked as Purged");
	}
	t.type = Transaction_type::Purged;
}
//------------------------------------------------------------------------------

void Library::add_patron_fee(const std::string& card_number, double amount)
{
	Patron& p{ patron_by_card_number(card_number) };
	p.add_fee(amount);
}

void Library::add_patron_fee(const std::string& card_number, double amount,
                             Date date_registered)
{
	Patron& p{ patron_by_card_number(card_number) };
	p.add_fee(amount, date_registered);
}

void Library::mark_patron_fee_as_paid(const std::string& card_number,
                                      int fee_id)
{
	Patron& p{ patron_by_card_number(card_number) };
	p.mark_fee_as_paid(fee_id);
}

void Library::mark_patron_fee_as_paid(const std::string& card_number,
									  int fee_id,
									  const std::string& comment)
{
	Patron& p{ patron_by_card_number(card_number) };
	p.mark_fee_as_paid(fee_id, comment);
}

void Library::update_patron_fee_comment(const std::string& card_number,
										int fee_id,
										const std::string& comment)
{
	Patron& p{ patron_by_card_number(card_number) };
	p.update_fee_comment(fee_id, comment);
}

const std::vector<Fee>& Library::patron_fees(
	const std::string& card_number)
{
	Patron const& p = patron_by_card_number(card_number);
	return p.all_fees();
}

//------------------------------------------------------------------------------

bool Library::book_exists(const std::string& isbn) const {
	for (const Book& b : books) {
		if (b.ISBN() == isbn) {
			return true;
		}
	}
	return false;
}

Book& Library::book_by_isbn(const std::string& isbn)
{
	for (Book& b : books) {
		if (b.ISBN() == isbn) {
			return b;
		}
	}
	throw std::runtime_error("Could not find a book with that ISBN");
}
//------------------------------------------------------------------------------

bool Library::card_exists(const std::string& card_number) const
{
	for (const Patron& p : patrons) {
		if (p.card_number() == card_number) {
			return true;
		}
	}
	return false;
}

Patron& Library::patron_by_card_number(
	const std::string& card_number)
{
	for (int i = 0; i < patrons.size() ; ++i) {
		if (patrons[i].card_number() == card_number) {
			return patrons[i];
		}
	}
	throw std::runtime_error("Could not find a user with that card number");
}

bool Library::card_is_blacklisted(const std::string& card_number) const
{
	for (const Patron& p : patrons) {
		if (p.card_number() == card_number && p.has_unpaid_fees()) {
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------

// Returns a Transcation with Transaction_type::Empty if no match was found
Transaction Library::latest_tx_by_isbn(const std::string& isbn) const
{
	for (int i = transactions.size() - 1; i >= 0; --i) {
		if (transactions[i].type == Transaction_type::Purged) {
			continue; // Skip purged transactions
		}
		if (transactions[i].isbn == isbn) {
			return transactions[i];
		}
	}
	return { 0, "", "", "", {}, Transaction_type::Empty };
}

//------------------------------------------------------------------------------

Transaction& Library::tx_by_id(int tx_id)
{
	for (Transaction& tx: transactions) {
		if (tx.id == tx_id) {
			return tx;
		}
	}
	throw std::runtime_error("Could not find a transaction with that ID");
}

int Library::new_tx_id() const
{
	return transactions.size();

}
