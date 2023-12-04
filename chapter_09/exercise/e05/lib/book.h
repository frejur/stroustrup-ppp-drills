#ifndef BOOK_H
#define BOOK_H

#include "../date/date.h"
#include <string>
#include <iostream>

enum class Genre;

class Book
{
public:
	Book(std::string isbn, std::string title, std::string author, Date date);
	Book(std::string isbn, std::string title, std::string author, Date date,
	     Genre genre);
	std::string ISBN() const { return isbn; };
	std::string title() const { return ttl; };
	std::string author() const { return auth; };
	Genre genre() const { return g; };
	Date copyright_date() const { return cr_date; };
	bool is_checked_out() const { return is_chkd_out; };
	void check_out();
	void check_in();

	friend bool operator==(const Book& a, const Book& b);
	friend bool operator!=(const Book& a, const Book& b) { return !(a == b); };
	friend std::ostream& operator<<(std::ostream& os, const Book& b);
private:
	std::string isbn;
	std::string ttl;
	std::string auth;
	Date cr_date;
	bool is_chkd_out{ false };
	Genre g;
};
//------------------------------------------------------------------------------

std::string validate_title(const std::string& title);
std::string validate_author(const std::string& author);
std::string validate_ISBN(std::string& isbn);
//------------------------------------------------------------------------------

enum class Genre {
	Misc=0, Fiction, Non_Fiction, Periodical, Biography, Children
};

std::ostream& operator<<(std::ostream& os, const Genre& g);

#endif // BOOK_H
