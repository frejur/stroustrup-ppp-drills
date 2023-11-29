#include "../../lib/std_lib_facilities.h"
#include "./txt/excerpts.h"

// Chapter 8, Exercise 12. Print strings of vector until a match is found.

// Write (Improve the one featured in the book) a function:
//     print_until_s(vector v, string s)
// This function should print the entries one-by-one until s == v[i], or until
// the end of the vector if no match was found.

// Also write a function called:
//     print_until_ss(vector v, string s)
// This function should print entries until the second time a match was found.

namespace CONST {
const std::string PROMPT{ "> " };
const std::string EXIT{ "!" };
const std::string PRINT_ALL{ "*" };
constexpr int LOWER_OFFS{ 'a' - 'A' };
}

//------------------------------------------------------------------------------

// Forward declare
std::string to_lower(const std::string& s); // Forward declare helper function
void print_start_of_output(const int n, const std::string& w);
void print_end_of_output();

// Note: unlike the book this until is "inclusive"
void print_until_n_of_s(
	const vector<std::string>& v, const std::string& quit_w, int n
) {
	if (n < 0) {
		error("Negative number of occurences");
	}
	print_start_of_output(n, quit_w);
	int count{ 0 };
	for (const std::string& s : v) {
		std::cout << s;
		if (to_lower(s) == quit_w) {
			if(++count == n) {
				break;
			}
		}
	}
	print_end_of_output();
}
void print_until_s(const vector<std::string>& v, const std::string& quit_w) {
	print_until_n_of_s(v, quit_w, 1);
}

void print_until_ss(const vector<std::string>& v, const std::string& quit_w) {
	print_until_n_of_s(v, quit_w, 2);
}

//------------------------------------------------------------------------------

void print_start_of_output(const int n, const std::string& quit_w) {
	if (n == 0) {
		std::cout << "Printing the whole text..." <<'\n' <<'\n';
	}
	else
	if (n == 1) {
		std::cout
			<< "Printing text until the word '" << quit_w << "'"
			<< " has been found..." << '\n' << '\n';
	} else {
		std::cout
			<< "Printing text until " << n << " occurences of '" << quit_w << "'"
			<< " have been found..." << '\n' << '\n';
	}
}

void print_end_of_output() {
	std::cout
		<< '\n' << '\n'
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
		<< '\n' << '\n';
}

//------------------------------------------------------------------------------
// Custom types

class Excerpt {
public:
	const std::string name;
	const std::string& text; // Text in excerpts.h
};

class Word_count {
public:
	std::string word;
	int count;
};

//------------------------------------------------------------------------------
// Convert string / char into lowercase

char to_lower(const char c) {
    if (!isalpha(c)) {
        return c;
    }
    if ('a' <= c && c <= 'z') {
    	return c;
    }
    char low{ char(c + CONST::LOWER_OFFS) };
    if (!isalpha(low)) {
        return c;
    }
    return low;
}

std::string to_lower(const std::string& s) {
    std::string low{ "" };
    for (char c : s) {
        low += to_lower(c);
    }
    return low;
}
//------------------------------------------------------------------------------

std::string buffer_until_eol() {
	std::string s{ "" };
	char c{};
	while(std::cin.get(c) && c != '\n') {
		s += c;
	}
	return s + c;
}

void clear_buffer() {
	char c{};
	while(std::cin.get(c) && c != '\n') {}
}
void restore_buffer(const std::string& b) {
	for (int i = b.size() - 1; i >= 0; --i) {
		std::cin.putback(b[i]);
	}
}

bool entered_exit() {
	std::string b{ buffer_until_eol() };
	if (b == CONST::EXIT + '\n') {
		return true;
	}
	restore_buffer(b);
	return false;
}

bool entered_print_all() {
	std::string b{ buffer_until_eol() };
	if (b == CONST::PRINT_ALL + '\n') {
		return true;
	}
	restore_buffer(b);
	return false;
}

//------------------------------------------------------------------------------

void print_exit_cmd() {
	std::cout << "(Type '" << CONST::EXIT << "' to quit)";
}

void print_exit_and_print_cmd() {
	std::cout
		<< "(Type '" << CONST::PRINT_ALL << "' to print all,"
		<< " '" << CONST::EXIT << "' to quit)";
}

void print_hint_text_choice(int n) {
	std::cout << "Pick your choice: 1-" << n << ' ';
	print_exit_cmd();
	std::cout << '\n';
}

void print_help_text_choice(const vector<Excerpt>& texts) {
	std::cout
		<< "You have the following texts to choose from:" << '\n';
	for (int i = 0; i < texts.size(); ++i) {
		std::cout << "    " << (i + 1) << ". " << texts[i].name << '\n';
	}
	std::cout << '\n';
	print_hint_text_choice(static_cast<int>(texts.size()));
}

void print(const std::string& label, const vector<Word_count>& w_count, int max)
{
	if (max < 1 || max > w_count.size()) {
		error("Invalid max value");
	}
	std::cout << label << '\n';
	if (w_count.size() == 0) {
		std::cout << "Empty" << '\n';
		return;
	}
	std::cout << "{";
	for (int i = 0; i < max; ++i) {
		std::cout
			<< "    " << w_count.at(i).word
			<< "  (" << w_count.at(i).count << ")";
		if (i == max - 1) {
			std::cout << " }" << '\n';
			break;
		}
		std::cout << ",";
		if ((i + 1) % 2 == 0) {
			std::cout << "\n ";
		}
	}
}

void print_hint_quit_word() {
	std::cout << "Please enter a word from the text." << ' ';
	print_exit_and_print_cmd();
	std::cout << '\n';
}

void print_help_quit_word(const vector<Word_count>& count) {
	std::cout
		<< "Here's a few frequently occuring word from that text:" << '\n';
	print("(No. of occurences in parentheses)", count, 6);
	std::cout << '\n';

	print_hint_quit_word();
}

void print_hint_occurences(const std::string& w, int max) {
	std::cout
		<< "Specify the number of times: 1 to " << max << ' ';
	print_exit_cmd();
	std::cout << '\n';
}
void print_help_occurences(const std::string& w, int max) {
	std::cout
		<< "The text keeps printing until:" << '\n'
		<< '\'' << w << "' is found X number of times."
		<< '\n' << '\n';
	print_hint_occurences(w, max);
}

void print_hint_reset() {
	std::cout
		<< "The end. Would you like to go again?"
		<< '\n' << '\n'
		<< "Hit <ENTER> to continue ";
	print_exit_cmd();
	std::cout << '\n';
}

//------------------------------------------------------------------------------

int get_text_choice(const vector<Excerpt>& texts, bool& should_continue) {
	if (!should_continue) {
		return {};
	}
	print_help_text_choice(texts);
	char c{};
	int choice{ 0 };
	while (std::cin)
	try {
		std::cout << CONST::PROMPT;
		if (entered_exit()) {
			should_continue = false;
			return {};
		}

		std::cin.get(c);
		if (c == '\n') {
			continue;
		}

		if (isdigit(c)) {
			std::cin.putback(c);
			std::cin >> choice;
			if (0 < choice && choice <= texts.size()) {
				clear_buffer();
				return choice - 1;
			}
		}
		error("Invalid input");
	}
	catch (std::exception e) {
		clear_buffer();
		std::cerr << "Error: " << e.what() << '\n';
		print_hint_text_choice(texts.size());
	}
	catch (...) {
		should_continue = false;
		error("Unknown error");
	}

	return {};
}

//------------------------------------------------------------------------------
// Forward declare...
bool contains_quit_w(const vector<Word_count>& v, const std::string& s);

std::string get_quit_word(
	const vector<Word_count>& w_count, bool& should_continue
) {
	if (!should_continue) {
		return {};
	}
	print_help_quit_word(w_count);
	char c{};
	std::string quit_w{ "" };
	while (std::cin)
	try {
		std::cout << CONST::PROMPT;
		if (entered_exit()) {
			should_continue = false;
			return {};
		}

		if (entered_print_all()) {
			return ""; // empty return value signals print all
		}

		std::cin.get(c);
		if (c == '\n') {
			continue;
		}

		if (isalnum(c)) {
			std::cin.putback(c);
			std::cin >> quit_w;
			char c2{};
			std::cin.get(c2);
			if (c2 == '\n' && contains_quit_w(w_count, to_lower(quit_w))) {
				return quit_w;
			} else {
				std::cin.putback(c2);
			}
		}
		error("Invalid input");
	}
	catch (std::exception e) {
		clear_buffer();
		std::cerr << "Error: " << e.what() << '\n';
		print_hint_quit_word();
	}
	catch (...) {
		should_continue = false;
		error("Unknown error");
	}

	return {};
}

//------------------------------------------------------------------------------

int get_occurences(const std::string& s, int max, bool& should_continue) {
	if (!should_continue) {
		return {};
	}
	print_help_occurences(s, max);
	char c{};
	int occ{};
	while (std::cin)
	try {
		std::cout << CONST::PROMPT;
		if (entered_exit()) {
			should_continue = false;
			return {};
		}

		std::cin.get(c);
		if (c == '\n') {
			continue;
		}

		if (isdigit(c)) {
			std::cin.putback(c);
			std::cin >> occ;
			if (0 < occ && occ <= max) {
				clear_buffer();
				return occ;
			}
		}
		error("Invalid input");
	}
	catch (std::exception e) {
		clear_buffer();
		std::cerr << "Error: " << e.what() << '\n';
		print_hint_occurences(s, max);
	}
	catch (...) {
		should_continue = false;
		error("Unknown error");
	}

	return occ;
}

//------------------------------------------------------------------------------

void get_continue(bool& should_continue) {
	if (!should_continue) {
		return;
	}
	print_hint_reset();
	std::cout << CONST::PROMPT;
	if (entered_exit()) {
		should_continue = false;
		return;
	}
	clear_buffer();
}

//------------------------------------------------------------------------------

std::string extract_word(const std::string& s, int start) {
	if (start < 0 || start > s.size()) {
		error("Invalid start position for word extraction");
	}

	std::string w{ "" };
	bool prev_is_letter { false };
	for (int i = start; i < s.size(); ++i) {
		if (s[i] == '-' || s[i] == '\'') {
			if (i == s.size() - 1 || i - start == 0 || !prev_is_letter) {
				break;
			}
			w += s[i];
			prev_is_letter = false;
		}
		else
		if (!isalnum(s[i])) {
			break;
		}
		else {
			w += s[i];
			prev_is_letter = true;
		}
	}
	if (!prev_is_letter) {
		w.pop_back();
	}
	if (w.size() == 0) {
		error("Could not extract word");
	}
	return w;
}

std::string extract_non_word(const std::string& s, int start) {
	if (start < 0 || start > s.size()) {
		error("Invalid start position for word extraction");
	}

	std::string non_w{ "" };
	for (int i = start; i < s.size(); ++i) {
		if (isalnum(s[i])) {
			break;
		}
		non_w += s[i];
	}
	if (non_w.size() == 0) {
		error("Could not extract word");
	}
	return non_w;
}

vector<std::string> string_to_vector(const std::string& s) {
	if (s.size() == 0) {
		error("Cannot extract words from empty string");
	}

	// get word or non-word, alternates on each iteration
	bool get_word { (bool)isalnum(s[0]) };

	vector<std::string> v{};
	int chars{ 0 };
	while (chars < s.size()) {
		if (get_word) {
			v.push_back(extract_word(s, chars));
		} else {
			v.push_back(extract_non_word(s, chars));
		}
		get_word = !get_word;
		chars += v.back().size();
	}

	return v;
}

vector<std::string> words_from_vector(const vector<std::string> v) {
	vector<std::string> words{};
	for (const std::string& s: v) {
		if (isalnum(s.front())) {
			words.push_back(s);
		}
	}
	return words;
}

vector<Word_count> get_word_count(vector<std::string> words) {
	if (words.size() == 0) {
		error("Cannot get word count for empty vector");
	}
	vector<Word_count> w_count{};
	std::sort(words.begin(), words.end());
	std::string prev_w{ "" };
	for (const std::string& w : words) {
		if (w.size() == 0) {
			error("Found an 'empty' word");
		}
		std::string low_w{ to_lower(w) };
		if (low_w != prev_w) {
			w_count.push_back({ low_w, 1 });
			prev_w = low_w;
		} else {
			++w_count.back().count;
		}
	}
	return w_count;
}

bool contains_quit_w(
	const vector<Word_count>& w_count, const std::string& quit_w
) {
	for (const Word_count& w : w_count) {
		if (w.word == quit_w) {
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------

int find_element(const int& e,
                 const vector<int>& unsorted,
                 const vector<int>& sorted) {
	int idx{ -1 }; // no match
	for (int i = 0; i < sorted.size(); ++i) {
		if (unsorted.at(i) != sorted.at(i) && e == unsorted.at(i)) {
			idx = i;
			break;
		}
	}
	return idx;
}

void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void swap(Word_count& a, Word_count& b) {
	Word_count temp{ a };
	a.word = b.word;
	a.count = b.count;
	b.word = temp.word;
	b.count = temp.count;
}

void reverse(vector<int>& v) {
	if (v.size() < 2) {
		return;
	}
	for (int i = 0; i < (v.size() / 2); ++i) {
		swap(v[i], v[v.size() - 1 - i]);
	}
};

void reverse(vector<Word_count>& v) {
	if (v.size() < 2) {
		return;
	}
	for (int i = 0; i < (v.size() / 2); ++i) {
		swap(v[i], v[v.size() - 1 - i]);
	}
};

void sort_by_count(vector<Word_count>& w_count)
{
	vector<int> int_v{};
	for (const Word_count& wc : w_count) {
		int_v.push_back(wc.count);
	}
	vector<int> unsorted{ int_v };
	std::sort(int_v.begin(), int_v.end());
	int i{ 0 };
	bool is_done{ false };
	while (!is_done) {
		// skip to first non-checked or return
		while (unsorted.at(i) == int_v.at(i)) {
			if (i == int_v.size() - 1) {
				is_done = true;
				break; // sucky see below
			}
			++i;
		}
		if (is_done) {
			break; // suck TODO: restructure
		}
		int match{ find_element(int_v.at(i), unsorted, int_v) };
		if (match == -1) {
			error("Could not find element of unsorted in sorted");
		}

		if (unsorted.at(match) != int_v.at(match)) {
			if (unsorted.at(i) != int_v.at(i)) {
				swap(w_count.at(i), w_count.at(match));
				swap(unsorted.at(i), unsorted.at(match));
				i = match;
				continue;
			}
		}

		i = 0;
	}
	reverse(w_count);
}

int count(const vector<Word_count>& w_count, const std::string& s) {
	for (const Word_count& w : w_count) {
		if (s == w.word) {
			return w.count;
		}
	}
	error("Unknown word");
	return -1;
}

//------------------------------------------------------------------------------

int main()
try
{
	std::cout
		<< "Print elements of vector<string> until the given word is found"
		<< '\n';

	const vector<Excerpt> texts{
		{ "Snark Hunt", SNARK::txt },
		{ "Radio Lingo", RADIO::txt },
		{ "Icelandic Saga", NJALL::txt}
	};

	bool should_continue{ true }; // passed by ref, false will trigger exit
	while (should_continue) {
		int txt_idx{ get_text_choice(texts, should_continue) };
		if (!should_continue) {
			break;
		}

		const std::string& txt = texts[txt_idx].text;
		const vector<std::string> txt_v{ string_to_vector(txt) };
		const vector<std::string> words{ words_from_vector(txt_v) };

		vector<Word_count> w_count{ get_word_count(words) };
		sort_by_count(w_count);

		std::string w{ get_quit_word(w_count, should_continue) };
		if (!should_continue) {
			break;
		}

		// Note that if w is empty we skip the next two steps and print
		// the whole text
		int c{ w != ""
		       ? count(w_count, to_lower(w))
		       : 0 };
		int occ{ c > 1
		         ? get_occurences(w, c, should_continue)
		         : c };
		if (!should_continue) {
			break;
		}

		print_until_n_of_s(txt_v, to_lower(w), occ);

		get_continue(should_continue);
	}

	std::cout << "Goodbye!" << '\n';
	keep_window_open();
	return 0;
}
catch (std::exception e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
