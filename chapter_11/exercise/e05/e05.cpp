#include "e05.h"
#include "../../lib/help.h"
#include "chcl/chcl.h"

/* Chapter 11, Exercise 5 and 14: Char classification
 * 
 * Exercise 5
 * A program that outputs the 'classification' of each char of a string.
 * Classification refers to the functions outlined in section 11.6, e.g.
 * isspace(c), isalpha(c), isdigit(c), etc.
 * 
 * Exercise 14
 * A program that, according to the 'classification' described above,
 * sums up the amount of characters of each type contained in a text file.
 * 
 * Additions to the exercises described in the book:
 * - Present the results of both exercises according to the example contained
 *   in 'e05_e10_sketch.txt'
 * - Let the user choose which program / exercise to run.
 */

//------------------------------------------------------------------------------

e05::Command e05::get_command(bool restore_buffer)
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

void e05::consume_leftover_endl()
{
	char c = 0;
	if (std::cin.get(c), c != '\n') {
		std::cin.putback(c);
	}
}

void e05::run_manual_input_mode()
{
	std::cout << "Manual mode" << '\n';

	std::string ln_str;
	std::stringstream ln_ss;
	chcl::Char_class_stream ccstr{ln_ss};
	while (std::cin) {
		std::getline(std::cin, ln_str);
		ln_ss.str(ln_str);

		chcl::Cl_chars chars;
		while (ccstr >> chars) {
			// std::cout << chars << '\n';
			chcl::print_classifications(std::cout, chars);
			std::cout << '\n' << "OVERVIEW:" << '\n' << '\n';
			chcl::print_overview(std::cout, chcl::get_cl_chars_count(chars));
			std::cout << '\n' << "DETAILED SUMMARY:" << '\n' << '\n';
			chcl::print_detailed_summary(std::cout,
			                             chcl::get_cl_chars_count(chars));
		}
		ccstr.clear();
	}

	std::cout << '\n' << "Press <ENTER> to return to main loop" << '\n';
	help::wait_for_enter();
}

void e05::print_commands()
{
	std::cout << "Please enter one of the characters below to proceed:" << '\n';
	for (const Command& c : commands()) {
		std::cout << c.symbol << '\t' << c.name << '\n';
	}
}

void e05::load_input_from_file(const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not load '" + file_path + "'");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::cout << '\n';

	chcl::Char_class_stream ccstr{ifs};
	chcl::Cl_chars chars;
	while (ccstr >> chars) {
		// chcl::print_classifications(std::cout, chars);
		// std::cout << '\n' << "OVERVIEW:" << '\n' << '\n';
	}
	chcl::print_overview(std::cout, ccstr.get_count());
	std::cout << '\n' << "DETAILED SUMMARY:" << '\n' << '\n';
	chcl::print_detailed_summary(std::cout, ccstr.get_count());

	std::cout << '\n' << "Press <ENTER> to return to the main loop" << '\n';
	help::wait_for_enter();
}

//------------------------------------------------------------------------------

int main()
try {
	std::cout << "Char classification" << '\n' << '\n';

	e05::Command cmd;
	while (cmd != e05::cmd_quit()) {
		e05::print_commands();
		cmd = e05::get_command();

		if (cmd == e05::cmd_load_from_file()) {
			e05::load_input_from_file(e05::file_path_text());
		} else if (cmd == e05::cmd_manual_input()) {
			e05::run_manual_input_mode();
		}
	}
	std::cout << "Press <ENTER> to exit" << '\n';
	help::wait_for_enter();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	help::wait_for_enter();
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	help::wait_for_enter();
}
