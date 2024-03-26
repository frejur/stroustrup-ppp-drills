#include "e06.h"
#include "../../lib/help.h"
#include <iostream>
#include <stdexcept>

/* Chapter 11, Exercise 6, 7 and 8.
 * 
 * 6. A program that replaces punctuation with whitespace, but leaves text
 *    wrapped in double quotes unchanged.
 * 7. Also replace contractions such as "Don't" with "Do not".
 * 8. Run the program on a "multi-page text file" to generate a "dictionary",
 *    ergo. a list of words in lexiographical order.
 * 
 * Changes to the exercises outlined in the book:
 * - Merge all exercise into one, allow the user to select which one to "run".
 * - Run some predefined test cases for Ex. 6 and 7.
 * - For the dictionary:
 *   1. Group words by length, calculate ratios and print bar charts.
 *   2. Print the longest and shortest word(s).
 */
//------------------------------------------------------------------------------

void e06::print_hello()
{
	std::cout << "More word extraction" << '\n';
}

void e06::print_options()
{
	std::cout << "Enter one of the characters listed below to continue:"
	          << '\n';
	for (const Command& c : options()) {
		std::cout << c.symbol << '\t' << c.name << '\n';
	}
}

//------------------------------------------------------------------------------

e06::Command_ID e06::get_command(std::istream& is)
{
	std::string in;
	std::getline(std::cin, in);
	Command_ID id = Command_ID::Unknown;
	if (in.size() != 1) {
		return id;
	}

	for (const Command& c : options()) {
		if (in.front() == c.symbol) {
			return c.id;
		}
	}
	return id;
}

//------------------------------------------------------------------------------

void e06::run_test_punctuation()
{
	std::cout << "Test punct" << '\n';

	std::cout << "Press <ENTER to return to the main loop." << '\n';
	help::wait_for_enter();
}

void e06::run_test_contractions()
{
	std::cout << "Test contr" << '\n';

	std::cout << "Press <ENTER to return to the main loop." << '\n';
	help::wait_for_enter();
}

void e06::run_test_dictionary()
{
	std::cout << "Test dict" << '\n';

	std::cout << "Press <ENTER to return to the main loop." << '\n';
	help::wait_for_enter();
}

//------------------------------------------------------------------------------

int main()
try {
	e06::print_hello();

	e06::Command_ID cmd = e06::Command_ID::Unknown;
	while (cmd != e06::Command_ID::Quit) {
		e06::print_options();
		cmd = e06::get_command(std::cin);
		switch (cmd) {
		case e06::Command_ID::Test_punctuation:
			e06::run_test_punctuation();
			break;
		case e06::Command_ID::Test_contractions:
			e06::run_test_contractions();
			break;
		case e06::Command_ID::Generate_dictionary:
			e06::run_test_dictionary();
			break;
		case e06::Command_ID::Quit:
			break;
		case e06::Command_ID::Unknown:
		default:
			std::cout << "Unknown command" << '\n';
			break;
		}
	}
	std::cout << "Bye!" << '\n';
	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cerr << "Press <ENTER> to exit" << '\n';
	help::wait_for_enter();
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cerr << "Press <ENTER> to exit" << '\n';
	help::wait_for_enter();
	return 2;
}
