#include "../../lib/help.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/* Chapter 11, exercise 10 and 11. User-defined split
 * 
 *          Two functions:
 *              e10. vector<string>split(const string& s)
 *                  Splits string into words separated by whitespace.
 *              e11. vector<string>split(const string& s, const string& w)
 *              	Same as above, with each individual char in 'w' also
 *                  considered whitespace / delimiter.
 *
 *          Prompts the user to enter characters to consider as whitespace.
 *          (Blank for regular whitespace only)
 *          Then prompts the user to enter some words.
 *          
 *          Prints out the resulting words.
 */
//------------------------------------------------------------------------------

const std::string& quit_word()
{
	const static std::string q{"quit;"};
	return q;
}

const std::string& quit_info()
{
	const static std::string q{"(or '" + quit_word() + "' to exit)"};
	return q;
}

constexpr char prompt = '>';

//------------------------------------------------------------------------------

bool ch_in_str(const char ch, const std::string s)
{
	for (char c : s) {
		if (c == ch) {
			return true;
		}
	}
	return false;
}

std::string strip_dupl_ch_and_ws(const std::string& s)
{
	std::string new_s;
	for (char c : s) {
		if (!help::isspace(c) && !ch_in_str(c, new_s)) {
			new_s.push_back(c);
		}
	}
	return new_s;
}
//------------------------------------------------------------------------------

std::vector<std::string> split(const std::string& s, const std::string& w)
{
	std::vector<std::string> words;

	if (s.size() == 0) {
		return words;
	}

	std::string copy = (w.size() > 0 ? "" : s);
	if (w.size() > 0) {
		for (char c : s) {
			if (ch_in_str(c, w)) {
				c = ' ';
			}
			copy.push_back(c);
		}
		if (copy.size() == 0) {
			return words;
		}
	}

	std::stringstream ss(copy);
	std::string word;
	while (ss >> word) {
		words.push_back(word);
	}

	return words;
}

std::vector<std::string> split(const std::string& s)
{
	return split(s, "");
}

//------------------------------------------------------------------------------

void print_delim(const std::string& s)
{
	if (s.size() == 0) {
		std::cout << "Words will be delimited by whitespace only.";
	} else {
		std::cout << "Words will be delmited by:" << '\n';
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '\'') {
				std::cout << " ' ";
			} else {
				std::cout << '\'' << s[i] << '\'';
			}
			std::cout << (i == s.size() - 1 ? "" : "    ");
		}
	}
	std::cout << '\n' << '\n';
}

void print_words(const std::vector<std::string> words, int max_w)
{
	if (words.size() == 0) {
		std::cout << "Nothing registered, try again" << '\n';
	} else {
		std::cout << "The following words were extracted:" << '\n';
		int count_len = 0;
		for (int i = 0; i < words.size(); ++i) {
			count_len += words[i].size();
			std::string end;
			if (i == words.size() - 1 || count_len >= max_w) {
				end = "\n";
				count_len = 0;
			} else {
				end = " ";
			}
			std::cout << words[i] << end;
		}
		std::cout << '\n' << "Have another go if you want!" << '\n';
	}
	std::cout << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
	std::cout << "Split string into words" << '\n' << '\n';

	std::string del;
	std::string ln;
	for (;;) {
		std::cout << "Enter the characters you would like to use as delimiters."
		          << ' ' << quit_info() << '\n'
		          << prompt << ' ';
		std::getline(std::cin, ln);
		if (ln == quit_word()) {
			break;
		}

		del = strip_dupl_ch_and_ws(ln);
		print_delim(del);

		std::cout << "Enter some words." << ' ' << quit_info() << '\n'
		          << prompt << ' ';
		std::getline(std::cin, ln);
		if (ln == quit_word()) {
			break;
		}

		std::vector<std::string> words = (del.size() ? split(ln, del)
		                                             : split(ln));

		print_words(words, 80);
	}

	std::cout << "Bye!" << '\n';
	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
	return 2;
}
