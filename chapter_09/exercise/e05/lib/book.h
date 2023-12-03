#ifndef BOOK_H
#define BOOK_H

#include "../date/date.h"
#include <string>

class Book
{
public:
	Book(std::string isbn, std::string title, std::string author, Date date);
	std::string ISBN() const { return isbn; };
	std::string title() const { return ttl; };
	std::string author() const { return auth; };
	Date copyright_date() const { return cr_date; };
	bool is_checked_out() const { return is_chkd_out; };
	void check_out();
	void check_in();
private:
	std::string isbn;
	std::string ttl;
	std::string auth;
	Date cr_date;
	bool is_chkd_out{ false };
};

#endif // BOOK_H
