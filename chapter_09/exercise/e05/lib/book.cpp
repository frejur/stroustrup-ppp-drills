#include "book.h"
#include "lib_helpers.h"
#include <stdexcept>

Book::Book(
	std::string new_isbn, std::string title, std::string author, Date date
) : isbn(validate_ISBN(new_isbn)), ttl(validate_title(title)),
    auth(validate_author(author)), cr_date(date), g(Genre::Misc)
{}

Book::Book(
	std::string new_isbn, std::string title, std::string author, Date date,
	Genre genre
) : isbn(validate_ISBN(new_isbn)), ttl(validate_title(title)),
    auth(validate_author(author)), cr_date(date), g(genre)
{}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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

std::string validate_ISBN(std::string& isbn) {
	HLP::ISBN_code c{ HLP::is_valid_ISBN(isbn) };

	switch (c){
	case HLP::ISBN_code::Success:
		break;
	case HLP::ISBN_code::Invalid_string_length:
		throw std::runtime_error("Invalid ISBN, invalid string length");
	case HLP::ISBN_code::Expected_digit:
		throw std::runtime_error("Invalid ISBN, expected a digit");
	case HLP::ISBN_code::Expected_hyphen:
		throw std::runtime_error("Invalid ISBN, expected a hyphen");
	case HLP::ISBN_code::Expected_digit_or_x:
		if (isbn.back() == 'x') {
			isbn.back() = 'X';
			break;
		}
		throw std::runtime_error("Invalid ISBN, expected a digit or 'X'");
	case HLP::ISBN_code::Empty_group:
		throw std::runtime_error("Invalid ISBN, empty group of digits");
	case HLP::ISBN_code::Invalid_number_of_groups:
		throw std::runtime_error("Invalid ISBN, expected 4 groups of digits");
	}

	return isbn;
}
//------------------------------------------------------------------------------

bool operator==(const Book& a, const Book& b) {
	return (a.ISBN() == b.ISBN());
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
	os << b.title() << '\n' << b.author() << '\n' << b.ISBN() << '\n'
	   << b.genre() << '\n';
	return os;
}
