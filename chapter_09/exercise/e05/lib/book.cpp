#include "book.h"
#include <stdexcept>

std::string validate_ISBN(const std::string& isbn) {
	// Must be of format n - n - n - x
	// Where n is an integer 0-9, and x is a single digit or letter
	if (isbn.size() != 7) {
		throw std::runtime_error("Invalid ISBN, invalid string length");
	}
	if (!isdigit(isbn[0]) || !isdigit(isbn[2]) || !isdigit(isbn[4])) {
		throw std::runtime_error("Invalid ISBN, expected digit");
	}
	if (isbn[1] != '-' || isbn[3] != '-' || isbn[5] != '-') {
		throw std::runtime_error("Invalid ISBN, expected hyphen");
	}
	if (!isalnum(isbn.back())) {
		throw std::runtime_error("Invalid ISBN, expected digit or letter");
	}
	return isbn;
}

std::string validate_title(const std::string& title) {
	if (title.length() == 0) {
		throw std::runtime_error("Invalid Title, empty string");
	}
	return title;
}

std::string validate_author(const std::string& author) {
	if (author.length() == 0) {
		throw std::runtime_error("Invalid Author, empty string");
	}
	return author;
}

Book::Book(
	std::string iisbn, std::string title, std::string author, Date date
) : isbn(validate_ISBN(iisbn)), ttl(validate_title(title)),
    auth(validate_author(author)), cr_date(date)
{}

void Book::check_out()
{
	if (is_chkd_out == true) {
		throw std::runtime_error(
			"Cannot check out book that is already checked-out");
	}
	is_chkd_out = true;
}

void Book::check_in()
{
	if (is_chkd_out == false) {
		throw std::runtime_error(
			"Cannot check in book that is already checked-in");
	}
	is_chkd_out = false;
}
