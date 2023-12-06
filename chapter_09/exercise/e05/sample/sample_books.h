#ifndef SAMPLE_BOOKS_H
#define SAMPLE_BOOKS_H

#include "../lib/book.h"

namespace SAMPLE_BOOKS { // ----------------------------------------------------

const Book& pride() {
	static Book b {
		"0-14-143951-3", "Pride and Prejudice",
		"Jane Austen", { 1813, Month::jan, 29 }, Genre::Fiction
	};
	return b;
}

const Book& c_lang() {
	static Book b {
		"0-13-110362-8", "The C Programming Language",
		"Brian Kernighan, Dennis Ritchie", { 1988, Month::mar, 22 },
		Genre::Non_Fiction
	};
	return b;
}

const Book& picasso() {
	static Book b {
		"0-316-88173-2", "Picasso: Portrait of Picasso as a Young Man",
		"Norman Mailer", { 1996, Month::nov, 18 }, Genre::Biography
	};
	return b;
}

const Book& horton() {
	static Book b {
		"0-394-80078-8", "Horton Hears a Who!",
		"Dr. Seuss", { 1954, Month::aug, 12 }, Genre::Children
	};
	return b;
}

} // SAMPLE_BOOKS --------------------------------------------------------------

#endif // SAMPLE_BOOKS_H
