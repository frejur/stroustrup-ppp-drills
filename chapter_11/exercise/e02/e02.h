#ifndef E01_H
#define E01_H

#include "../../lib/help.h"
#include "pstr/punct_stream.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace e02 {

//------------------------------------------------------------------------------

inline const std::string& quit_symbol()
{
	static std::string s{";"};
	return s;
}

inline const std::string& file_path_source()
{
	static std::string p{"data_e02/words.txt"};
	return p;
}

//------------------------------------------------------------------------------

std::string get_word();

struct Line_with_words
{
	std::vector<std::string> words;
	std::string line;
	int line_number;
};

Line_with_words get_line_w_words(pstr::Punct_stream& ps);
inline bool has_word(const std::string& word,
                     const std::vector<std::string> words)
{
	for (const std::string& w : words) {
		if (w == word) {
			return true;
		}
	}
	return false;
}
std::vector<Line_with_words> get_matching_lines(const std::string& file_path,
                                                const std::string& word);

void print_lines(const std::vector<Line_with_words> lines);

} // namespace e02

#endif
