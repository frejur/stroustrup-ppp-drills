#include "e04.h"
#include "../../lib/help.h"

/* Chapter 11, Exercise 4: A program that reads integers entered in decimal,
 *                         hexadecimal and octal syntax - and prints
 *                         them as decimal numbers in properly spaced columns
 *
 * Additions to the exercise described in the book:
 * 1. Prompt the user to choose between:
 *   A. Manual input.
 *   B. Read numbers from text file.
 */

//------------------------------------------------------------------------------

e04::Input_type e04::input_type(const std::string& s, int v)
{
	std::stringstream ss;
	ss << std::showbase;

	ss << std::dec << v;
	if (ss.str() == s) {
		return Input_type::Decimal;
	}

	ss.str("");
	ss << std::hex << v;
	if (ss.str() == s) {
		return Input_type::Hexadecimal;
	}

	ss.str("");
	ss << std::oct << v;
	if (ss.str() == s) {
		return Input_type::Octal;
	}

	return Input_type::Unknown;
}

//------------------------------------------------------------------------------

int main()
try {
	std::cout << "Ingest numbers written in dexicmal, hexadecimal or "
	             "octal syntax."
	          << '\n'
	          << "10 (dec) = 0xA (hex) = 012 (oct)" << '\n';

	std::cout << "Press <ENTER> to exit" << '\n';
	help::wait_for_enter();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	help::wait_for_enter();
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	help::wait_for_enter();
}
