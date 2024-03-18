#include "e09.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

/* Chapter 10, Exercise 8. Join words, preserve order
 * 
 * Write a program that merges the whitespace-separated words of two files into
 * one. The exercise is worded vaguely, but the words are presumed to be
 * 'sorted' when being read, so I'm guessing sorted alphabetically, and should
 * be merged into one file while 'preserving order', which I'm guessing means
 * the words in the final file also end up being sorted alphabetically.
 */

int main()
try {
	std::cout << "Enter any character to join and sort the words contained in '"
	          << e09::file_path_words_01() << "' and '"
	          << e09::file_path_words_02() << "'" << '\n';
	char c = 0;
	while (std::cin.get(c) && c != '\n') {
		/* clear buffer */
	}

	std::vector<std::string> words{e09::words_from_files(
	    {e09::file_path_words_01(), e09::file_path_words_02()})};

	std::sort(words.begin(), words.end());

	e09::words_to_file(words, e09::file_path_final());

	std::cout << '\n'
	          << "The contents of both files were joined and saved into '"
	          << e09::file_path_final() << "'" << '\n';

	std::cout << '\n' << "Press <ENTER> to exit" << '\n';
	std::cin.get();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
} catch (...) {
	std::cerr << "Unknown error" << '\n';
}

void e09::append_words_from_file(std::vector<std::string>& words,
                                 const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not load file: '" + file_path + "'");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::string w;
	while (ifs >> w) {
		words.push_back(w);
	}
}

std::vector<std::string> e09::words_from_files(
    const std::vector<std::string>& file_paths)
{
	std::vector<std::string> words;
	for (const std::string& p : file_paths) {
		append_words_from_file(words, p);
	}
	return words;
}

void e09::words_to_file(const std::vector<std::string>& words,
                        const std::string& file_path)
{
	std::ofstream ofs{file_path};
	if (!ofs) {
		throw std::runtime_error("Could not create ostream for path: '"
		                         + file_path + "'");
	}

	for (const std::string& w : words) {
		ofs << w << '\n';
	}
}
