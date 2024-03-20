#include "e02.h"
#include "../../lib/help.h"
#include <fstream>
#include <iostream>

/* Chapter 11, Exercise 2
 * Write a program that when passed a filename and a word as arguments,
 * searches through the file for the desired word and prints out the contents
 * of each line that contains that word along with the line number.
 */
std::string e02::get_word()
{
	std::string s;
	std::getline(std::cin, s);

	std::istringstream iss{s};
	std::string word;
	iss >> word;

	if (s.size() != word.size()) {
		word = "";
	} else if (word != quit_symbol()) {
		for (char c : word) {
			if (!help::isalpha(c) && c != '-') {
				word = "";
				break;
			}
		}
	}
	return word;
}

int main()
{
	std::cout << "Please enter a word." << '\n'
	          << '\n'
	          << "The file '" << e02::file_path_source()
	          << "' will be read and any occurences"
	             " of the chosen word will be "
	             "highlighted. (Enter '"
	          << e02::quit_symbol() << "' to exit)" << '\n';
	std::string word;
	while (word != e02::quit_symbol())
		try {
			word = e02::get_word();
			if (word.size() == 0) {
				std::cout << "Please enter a word." << '\n';
				continue;
			}
			if (word == e02::quit_symbol()) {
				break;
			}
			std::cout << "Searching... ";
			std::vector<e02::Line_with_words> lines{
			    e02::get_matching_lines(e02::file_path_source(),
			                            help::tolower(word))};
			std::cout << " Done!" << '\n' << '\n';

			if (lines.size() > 0) {
				std::cout << "Found " << lines.size() << " lines containing '"
				          << word << "':" << '\n'
				          << '\n';
				e02::print_lines(lines);
			} else {
				std::cout << "Could not find any mentions of the word: '"
				          << word << "'" << '\n';
			}

			std::cout << '\n'
			          << "Please enter another word to keep searching, or '"
			          << e02::quit_symbol() << "' to exit." << '\n';

		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << '\n';
			std::cin.clear();
		} catch (...) {
			std::cerr << "Unknown error" << '\n';
			std::cin.clear();
		}
	std::cout << "Bye!" << '\n';
}

std::vector<e02::Line_with_words> e02::get_matching_lines(
    const std::string& file_path, const std::string& word)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_path + "'");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	pstr::Punct_stream ps{ifs, false};
	ps.set_whitespace(",.!?'\";");
	std::vector<e02::Line_with_words> matching_lines;
	while (ps) {
		e02::Line_with_words ln{get_line_w_words(ps)};
		if (e02::has_word(word, ln.words)) {
			matching_lines.push_back(ln);
		}
	}
	return matching_lines;
}

e02::Line_with_words e02::get_line_w_words(pstr::Punct_stream& ps)
{
	e02::Line_with_words words;

	std::string w;
	while (ps >> w) {
		words.words.push_back(w);
		if (ps.eol()) {
			break;
		}
	}

	words.line_number = ps.line_number();
	words.line = ps.line_as_string();

	return words;
}

void e02::print_lines(const std::vector<Line_with_words> lines)
{
	for (const e02::Line_with_words& ln : lines) {
		std::cout << "Line # " << ln.line_number << '\t' << ln.line << '\n';
	}
}
