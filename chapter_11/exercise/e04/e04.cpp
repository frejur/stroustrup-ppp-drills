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
	if (ss.str() == help::tolower(s)) {
		return Input_type::Hexadecimal;
	}

	ss.str("");
	ss << std::oct << v;
	if (ss.str() == s) {
		return Input_type::Octal;
	}

	return Input_type::Unknown;
}

e04::Multi_stream& e04::Multi_stream::operator>>(Multi_input& mi)
{
	std::string in;
	int v = 0;
	if (src >> in) {
		if (buf.eof()) {
			buf.clear();
		}
		buf.str(in);
		buf >> v;

		if (buf.fail() || !buf.eof()) {
			src.clear(std::ios_base::failbit);
			return *this;
		}

		Input_type t{input_type(in, v)};
		if (t == Input_type::Unknown) {
			src.clear(std::ios_base::failbit);
			return *this;
		}

		mi.type = t;
		mi.value = v;
		mi.input = in;
	}
	return *this;
}

std::ostream& e04::operator<<(std::ostream& os, e04::Input_type t)
{
	return os << input_type_name(t);
}

std::ostream& e04::operator<<(std::ostream& os, Multi_input mi)
{
	return os << '(' << mi.value << ", " << mi.type << ", " << mi.input << ')';
}

//------------------------------------------------------------------------------

int main()
{
	std::cout << "Ingest numbers written in decimal, hexadecimal or "
	             "octal syntax."
	          << '\n'
	          << "10 (dec) = 0xA (hex) = 012 (oct)" << '\n';

	e04::Multi_stream ms{std::cin};
	e04::Multi_input mi;
	while (true)
		try {
			if (!(ms >> mi)) {
				throw std::runtime_error("Bad input");
			}
			std::cout << mi << '\n';
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << '\n';
			ms.clear();
		} catch (...) {
			std::cerr << "Unknown error" << '\n';
			ms.clear();
		}
	std::cout << "Press <ENTER> to exit" << '\n';
	help::wait_for_enter();
}
