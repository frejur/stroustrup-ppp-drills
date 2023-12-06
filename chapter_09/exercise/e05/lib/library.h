#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include "patron.h"
#include <vector>
#include <string>

//------------------------------------------------------------------------------

enum class Transaction_type {
	Check_in = 0, Check_out,
	Empty, // Used as a return type to signal: No matching Transaction was found
	Purged // Used to mark a Transaction as purged while keeping the data,
	       // currently, Transactions marked as Purged are simply 'skipped'.
};

struct Transaction {
	int id;
	std::string isbn;
	std::string card_number;
	std::string user_name;
	Date date; // Not really in use at the moment
	Transaction_type type;
};

std::ostream& operator<<(std::ostream& os, const Transaction_type& tt);

//------------------------------------------------------------------------------

class Library
{
public:
	Library();
	void add_book(Book b);
	void add_patron(Patron p);

	void check_out(const std::string& isbn, const std::string& card_number,
	               const Date& date);
	void check_in(const std::string& isbn, const Date& date,
	              const bool force_check_in = false);

	std::vector<std::string> blacklist() const;

	void purge_transaction(int tx_id);

	void add_patron_fee(const std::string& card_number, double amount);
	void add_patron_fee(const std::string& card_number, double amount,
	                    Date date_registered);
	void mark_patron_fee_as_paid(const std::string& card_number, int fee_id);
	void mark_patron_fee_as_paid(const std::string& card_number, int fee_id,
	                             const std::string& comment);
	void update_patron_fee_comment(const std::string& card_number, int fee_id,
	                               const std::string& comment);

	const std::vector<Fee>& patron_fees(const std::string& card_number);

	// used for testing
	const std::vector<Book>& all_books() const { return books; };
	const std::vector<Patron>& all_patrons() const { return patrons; };
	const std::vector<Transaction>& all_transactions() const {
		return transactions;
	};

private:
	std::vector<Book> books;
	std::vector<Patron> patrons;
	std::vector<Transaction> transactions; // Log check-ins / check-outs

	bool book_exists(const std::string& isbn) const;
	Book& book_by_isbn(const std::string& isbn);

	bool card_exists(const std::string& card_number) const;
	Patron& patron_by_card_number(const std::string& card_number);

	bool card_is_blacklisted(const std::string& card_number) const;

	Transaction latest_tx_by_isbn(const std::string& isbn) const;

	Transaction& tx_by_id(int tx_id);
	int new_tx_id() const;
};

#endif // LIBRARY_H
