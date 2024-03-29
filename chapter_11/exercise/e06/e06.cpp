#include "e06.h"
#include "../../lib/help.h"
#include "dstr/dstr.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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
 * - Merge all exercise into one, allow the user to:
 *     1. Try out the word extraction by entering text.
 *     2. Run some predefined test cases for Ex. 6 and 7.
 *     3. Generate a dictionary from a text file:
 *         a. Group words by length, calculate ratios and print bar charts.
 *         b.. Print the longest and shortest word(s).
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

void e06::print_input_help()
{
	std::cout << "Enter text below to extract lowercase words, type '"
	          << quit_word() << "' to exit." << '\n';
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

void e06::run_manual_input()
{
	std::cout << "Manual input" << '\n' << '\n';

	std::stringstream iss;
	dstr::Dict_stream ds{iss};

	std::cout << "Loading contractions from: '" << e06::file_path_contractions()
	          << "'...";
	add_contractions_from_file(ds, e06::file_path_contractions());
	std::cout << " Done!" << '\n';

	int count = 0;
	while (std::cin) {
		if (!(count % 5)) {
			if (count > 0) {
				std::cout << '\n' << "Nice, keep going!..." << '\n';
			}
			print_input_help();
			if (count > 0) {
				std::cout << '\n';
			}
		}
		std::string ln;
		std::cout << "> ";
		std::getline(std::cin, ln);
		if (ln == quit_word()) {
			break;
		}
		iss.str(ln);
		std::string word;
		while (ds >> word) {
			std::cout << word << ' ';
		}
		std::cout << '\n';
		ds.clear();
		ds.reset_quote_mode();
		++count;
	}

	std::cout << "Press <ENTER to return to the main loop." << '\n';
	help::wait_for_enter();
}
void e06::run_tests(const std::string& test_cases_file_path)
{
	std::cout << "Loading test cases from: '" << test_cases_file_path << "'...";
	std::vector<Test_case> tc{test_cases_from_file(test_cases_file_path)};
	std::cout << " Done!" << '\n';

	std::stringstream iss;
	dstr::Dict_stream ds{iss};
	std::cout << "Loading contractions from: '" << e06::file_path_contractions()
	          << "'...";
	add_contractions_from_file(ds, e06::file_path_contractions());
	std::cout << " Done!" << '\n';

	int count_fail = 0;
	for (int i = 0; i < tc.size(); ++i) {
		iss.str(tc[i].input);
		std::string final;
		std::string word;
		int count_q = 0;
		bool skip_space = false;
		while (ds >> word) {
			if (word == "\"") {
				skip_space = !(count_q % 2);
				final += ((skip_space && final.size()) ? " \"" : "\"");
				++count_q;
				continue;
			}
			final += (final.size() && !skip_space ? " " : "") + word;
			if (skip_space) {
				skip_space = false;
			}
		}
		std::cout << "Test " << std::setw(3) << i << ": ";

		if (tc[i].expected == final) {
			std::cout << "SUCCESS";
		} else {
			std::cout << "FAILURE";
			++count_fail;
		}

		std::cout << '\n';

		std::cout << std::setw(10) << "Input:" << ' ' << tc[i].input << '\n'
		          << std::setw(10) << "Expected:" << ' ' << tc[i].expected
		          << '\n'
		          << std::setw(10) << "Outcome:" << ' ' << final << '\n'
		          << '\n';
		ds.reset_quote_mode();
		ds.clear();
	}

	std::cout << '\n';

	if (count_fail) {
		std::cout << count_fail << " out of " << tc.size() << " tests FAILED!"
		          << '\n';
	} else {
		std::cout << "All tests passed." << '\n';
	}

	std::cout << '\n' << "Press <ENTER to return to the main loop." << '\n';
	help::wait_for_enter();
}

void e06::run_test_dictionary()
{
	std::cout << "Test dict" << '\n';

	std::cout << "Press <ENTER to return to the main loop." << '\n';
	help::wait_for_enter();
}

// -----------------------------------------------------------------------------

void e06::add_contractions_from_file(dstr::Dict_stream& ds,
                                     const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not open file: " + file_path);
	}

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::string ln;
	while (ifs) {
		std::getline(ifs, ln);
		if (ln.size() == 0 || ln.front() == '#') {
			continue;
		}
		std::string s;
		std::stringstream os{ln};
		std::string s_for;
		std::string repl_w;
		bool has_symbol = false;
		while (os >> s) {
			if (!has_symbol) {
				if (s == "->") {
					has_symbol = true;
					continue;
				} else {
					s_for += ((s_for.size() && s.size()) ? " " : "") + s;
				}
			} else {
				repl_w += ((repl_w.size() && s.size()) ? " " : "") + s;
			}
		}

		if (s_for.size() == 0 || repl_w.size() == 0) {
			throw std::runtime_error("Expected a string");
		}
		if (!has_symbol) {
			throw std::runtime_error("Expected '->'");
		}
		dstr::Char_type leading_t = dstr::Char_type::Whitespace;
		dstr::Char_type trailing_t = dstr::Char_type::Whitespace;
		bool strip = false;
		if (s_for.front() == '*') {
			leading_t = dstr::Char_type::Letter;
			strip = true;
		}
		if (s_for.back() == '*') {
			trailing_t = dstr::Char_type::Letter;
			strip = true;
		}
		if (strip) {
			std::string temp = s_for;
			s_for = "";
			for (int i = 0; i < temp.size(); ++i) {
				if (i == 0 && leading_t == dstr::Char_type::Letter) {
					continue;
				}
				if (i == temp.size() - 1
				    && trailing_t == dstr::Char_type::Letter) {
					continue;
				}
				s_for.push_back(temp[i]);
			}
			if (s_for.size() == 0) {
				throw std::runtime_error(
				    "Expected a string after removing wildcard(s)");
			}
		}

		ds.add_contraction({leading_t,
		                    trailing_t,
		                    help::tolower(s_for),
		                    help::tolower(repl_w)});
	}
}

//------------------------------------------------------------------------------

std::vector<e06::Test_case> e06::test_cases_from_file(
    const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not open file: " + file_path);
	}

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::vector<Test_case> tc;

	std::string ln;
	std::string in;
	std::string exp;
	bool found_in = false;
	int count_ln = 0;
	while (ifs) {
		std::getline(ifs, ln);
		++count_ln;
		if (ln.size() == 0) {
			if (found_in) {
				std::stringstream ss;
				ss << "Expected string at line " << count_ln;
				throw std::runtime_error(ss.str());
			}
			continue;
		}
		if (!found_in) {
			in = ln;
			found_in = true;
		} else {
			exp = ln;
			tc.push_back({in, exp});
			found_in = false;
		}
	}
	return tc;
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
		case e06::Command_ID::Manual_input:
			e06::run_manual_input();
			break;
		case e06::Command_ID::Test_punctuation:
			e06::run_tests(e06::file_path_test_punct());
			break;
		case e06::Command_ID::Test_contractions:
			e06::run_tests(e06::file_path_test_contr());
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
