#include "e04.h"
#include "../../lib/help.h"
#include <iomanip>

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
	return os << help::tolower(input_type_name(t, true));
}

std::ostream& e04::operator<<(std::ostream& os, Multi_input mi)
{
	return os << std::setw(8) << mi.input << ' ' << mi.type << ' '
	          << " converts to " << std::setw(5) << mi.value << " decimal";
}

//------------------------------------------------------------------------------

e04::Command e04::get_command(bool restore_buffer)
{
	std::string cmd_str;
	std::getline(std::cin, cmd_str);
	if (cmd_str.size() == 0) {
		return {"", ""};
	}

	for (const Command& c : commands()) {
		if (cmd_str == c.symbol) {
			return c;
		}
	}
	if (restore_buffer) {
		std::cin.putback('\n');
		for (int i = cmd_str.size() - 1; i >= 0; --i) {
			std::cin.putback(cmd_str[i]);
		}
	}
	return {"", ""};
}

void e04::consume_leftover_endl()
{
	char c = 0;
	if (std::cin.get(c), c != '\n') {
		std::cin.putback(c);
	}
}

void e04::run_manual_input_mode()
{
	Multi_stream ms{std::cin};
	Multi_input mi;

	std::cout << '\n'
	          << "Please enter some numbers in your desired syntax." << '\n'
	          << "E.g. '10' (dec) = '0xA' (hex) = '012' (oct)" << '\n';
	while (true)
		try {
			consume_leftover_endl();
			if (get_command(true) == cmd_quit()) {
				break;
			}

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
	std::cout << '\n' << "Press <ENTER> to return to main loop" << '\n';
	help::wait_for_enter();
}

void e04::print_commands()
{
	std::cout << "Please enter one of the characters below to proceed:" << '\n';
	for (const Command& c : commands()) {
		std::cout << c.symbol << '\t' << c.name << '\n';
	}
}

void e04::load_input_from_file(const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not load '" + file_path + "'");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	Multi_stream ms{ifs};
	Multi_input mi;

	std::cout << '\n';

	while (ms >> mi) {
		std::cout << mi << '\n';
	}

	std::cout << '\n' << "Press <ENTER> to return to the main loop" << '\n';
	help::wait_for_enter();
}

//------------------------------------------------------------------------------

int main()
{
	std::cout << "Ingest numbers written in decimal, hexadecimal or "
	             "octal syntax."
	          << '\n'
	          << '\n';

	e04::Command cmd;
	while (cmd != e04::cmd_quit()) {
		e04::print_commands();
		cmd = e04::get_command();

		if (cmd == e04::cmd_load_from_file()) {
			e04::load_input_from_file(e04::file_path_input());
		} else if (cmd == e04::cmd_manual_input()) {
			e04::run_manual_input_mode();
		}
	}
	std::cout << "Bye!" << '\n';
}
