#include "../../lib/std_lib_facilities.h"
#include "../../lib/excerpts.h"

// Chapter 8, Exercise 13. The boundaries of a vector<string>, alphabetically
//                         and by string length.

// Write a function that takes a vector<string> as an argument and produces
// a vector<int> containing the length of each element.

// Write functions that returns the first and last element:
// A. Lexiographically
// B. In terms of character count

// (Additionally)
// Generate a vector of random words when the user presses <ENTER>
// Use the generated vector of words to try out the aforementioned functions,
// then output the result.

// The way lexiographical order plays out with mixed case is not super intuitive
// so all words are lowercase.

// The book suggest you would use the vector<int> of sizes to calculate the
// shortest / longest word.

// Unless you want to sort and print out the whole list of words, this seems
// unnecessary - Just compare lengths as you step through the unsorted values.

// It is useful if you want to isolate values of a certain length or similar.
// That's why this program, in addition to the main task outlined in the book,
// finishes by grouping all the strings into 'buckets' based on character count.

// Note: It arguably makes more sense to always return both the shortest and
// longest word from the same function call since you might just as well
// calculate both at once rather than iterating over the same values twice.
// The same thing applies for the lexiographical min and max.

// What is the "shortest" / "longest" word?
// When you're looking for the shortest string what you usally want is the word
// that is both the shortest and that comes first lexiographically compared to
// other words of the same length:
//     'abc', 'bcd' and 'cde' are all the same length, but 'abc' comes first.
//     Some would say 'abc' is the "shortest" word.

// The same logic would apply for the longest word, but inverted:
//     'fghijk', 'lmnopq', 'rstuvw' are the same length but 'rstuvw' comes last.
//     Some would say 'rstuvw' is the "longest" word.

// Since this program calculates both the lexiographical and length-wise
// min and max, it makes sense to have a function that calculates and returns
// all four at once. It also makes sense to implement the shortest / longest
// word logic detailed above.

namespace CONST {
const std::string PROMPT{ " > " };
const std::string EXIT{ "exit" };
constexpr int LOWER_OFFS{ 'a' - 'A' };
}

//------------------------------------------------------------------------------
// Custom types

// Used to return two strings from a single function call
class String_min_max {
public:
	std::string min;
	std::string max;
};

// Used to return multiple stats from a single function call
class String_stats {
public:
	String_min_max length;
	String_min_max lexiographical;
};

// User to store groups of string
class String_buckets {
public:
	vector<vector<std::string>> buckets;
};

//------------------------------------------------------------------------------
void update_len_min_max(
	const std::string& s,
	std::string& min_s, double& min_len, std::string& max_s, double& max_len )
{
	if ((s.size() < min_len) ||
	    (s.size() == min_len && s < min_s)
	) {

		min_s = s;
		min_len = s.size();
	}
	if ((s.size() > max_len) ||
	    (s.size() == max_len && s > max_s)) {
		max_s = s;
		max_len = s.size();
	}
}

void update_lex_min_max(
	const std::string& s,std::string& min_s, std::string& max_s)
{
	if (s < min_s) {
		min_s = s;
	}
	if (s > max_s) {
		max_s = s;
	}
}

String_min_max str_len_min_max(const vector<std::string>& v) {
	std::string s_min{ v[0] };
	std::string s_max{ v[0] };
	double len_min{ static_cast<double>(v[0].size()) };
	double len_max{ static_cast<double>(v[0].size()) };
	for (int i = 1; i < v.size(); ++i) {
		update_len_min_max(v[i], s_min, len_min, s_max, len_max);
	}
	return { s_min, s_max };
}

String_min_max str_lex_min_max(const vector<std::string>& v) {
	std::string s_min{ v[0] };
	std::string s_max{ v[0] };
	for (int i = 1; i < v.size(); ++i) {
		update_lex_min_max(v[i], s_min, s_max);
	}
	return { s_min, s_max };
}

String_stats str_len_lex_stats(const vector<std::string>& v) {
	std::string len_s_min{ v[0] };
	std::string len_s_max{ v[0] };
	std::string lex_s_min{ v[0] };
	std::string lex_s_max{ v[0] };
	double len_min{ static_cast<double>(v[0].size()) };
	double len_max{ static_cast<double>(v[0].size()) };
	for (int i = 1; i < v.size(); ++i) {
		update_len_min_max(v[i], len_s_min, len_min, len_s_max, len_max);
		update_lex_min_max(v[i], lex_s_min, lex_s_max);
	}
	return { { len_s_min, len_s_max }, { lex_s_min, lex_s_max } };
}

vector<int> str_len_v(const vector<std::string>& v) {
	vector<int> len{};
	for (const std::string& s : v) {
		len.push_back(s.size());
	}
	return len;
}
//------------------------------------------------------------------------------

vector<int> distinct_vals(const vector<int>& v) {
	if (v.size() == 0) {
		error("Cannot get distinct values of an empty vector");
	}
	vector<int> d{ v[0] };
	if (v.size() == 1) {
		return d;
	}

	for (int i = 1; i < v.size(); ++i) {
		bool is_unique{ true };
		for (int j = 0; j < d.size(); ++j) {
			if (v[i] == d[j]) {
				is_unique = false;
				break;
			}
		}
		if (is_unique) {
			d.push_back(v[i]);
		}
	}
	return d;
}

vector<std::string> filter_by_len(const vector<std::string>& v, int len) {
	if (v.size() < 1) {
		error("Cannot filter values of empty vector");
	}
	if (len < 0) {
		error("Cannot filter by a negative length value");
	}
	vector<std::string> f{};
	for (const std::string& s : v) {
		if (s.size() == len) {
			f.push_back({ s });
		}
	}
	return f;
}

String_buckets split_into_buckets(
	const vector<std::string>& v, const vector<int>& sort_by
) {
	if (v.size() != sort_by.size()) {
		error("Cannot sort by a vector of different size");
	}
	vector<int> distinct{ distinct_vals(sort_by) };
	sort(distinct.begin(), distinct.end());

	vector<vector<std::string>> buckets(distinct.size());

	for (int i = 0; i < distinct.size(); ++i) {
		buckets[i] = filter_by_len(v, distinct[i]);
	}
	return { buckets };
}

//------------------------------------------------------------------------------

std::string append_spaces(const std::string& s, int col_w) {
	if(col_w <= s.size()) {
		return s;
	}
	std::string s2 { s };
	for (int i = s.size(); i < col_w; ++i) {
		s2 += ' ';
	}
	return s2;
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

//------------------------------------------------------------------------------

void print_hello() {
	std::cout
		<< "Min and max words, lexiographically and by length."
		<< '\n' << '\n';
}

void print_exit_cmd() {
	std::cout << "(Type '" << CONST::EXIT << "' to quit)";
}

void print_help_get_random_words() {
	std::cout
		<< "Hit <ENTER> to generate words ";
	print_exit_cmd();
}

void print_help_get_stats() {
	std::cout
		<< "Hit <ENTER> to generate some stats ";
	print_exit_cmd();
}

void print_hint_reset() {
	std::cout
		<< "The end. Would you like to go again?"
		<< '\n' << '\n'
		<< "Hit <ENTER> to continue ";
	print_exit_cmd();
}

void print(
	const std::string& label, const vector<std::string>& v,
	const int num_cols, const int col_w
) {
	std::cout << label << ": " << '\n';
	int col{ 0 };
	for (std::string s : v) {
		if (col == num_cols - 1) {
			std::cout << s << '\n';
		} else{
			std::cout << append_spaces(s, col_w);
		}
		col = (col + 1) % num_cols;
	}
	std::cout << '\n';
}

void print(const String_stats& stats) {
	std::cout
		<< "STATS:" << '\n'
		<< "The shortest word is: " << stats.length.min << '\n'
		<< "The longest word is:  " << stats.length.max << '\n'
		<< "Lexiographical min:   " << stats.lexiographical.min << '\n'
		<< "Lexiographical max:   " << stats.lexiographical.max << '\n'
		<< '\n';
}


void print(const String_buckets& sb) {
	for (vector<std::string> b: sb.buckets) {
		std::cout
			<< append_spaces(std::to_string(b[0].size()) + "-letter words:",
			                 22);
		sort(b.begin(), b.end()); // sort copy
		for (int i = 0; i < b.size(); ++i) {
			std::cout << b[i];
			if (i != b.size() - 1) {
				std:: cout << ", ";
			}
		}
		std::cout << '\n';
	}
	std::cout << '\n';
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
//------------------------------------------------------------------------------

void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

// assumes max > min
int randnum(int min, int max) {;
	return min + randint(max - min);
}

vector<std::string> sub_sequence(
	const vector<std::string>& v, int min, int max, int n
) {
	if (max < min) {
		error("Cannot generate sequence when min is greater than max");
	}
	if (n < 2 || n > max - min) {
		error("Too few / too many number of elements");
	}
	vector<std::string> seq{ v[min] };
	int incr{ static_cast<int>((max - min) / (n-1.0) + 0.5) };
	for (int i = 1; i < n-1; ++i) {
		seq.push_back(v[min + incr * i]);
	}
	seq.push_back(v[max]);
	return seq;
}

void shuffle(vector<std::string> & v, int iterations, int steps) {
	if (v.size() < 3 || iterations < 1) {
		return; // don't bother
	}
	for (int i = 0; i < iterations; ++i) {
		for (int j = 0; j < v.size(); ++j) {
			int randidx{ (j + randnum(1, steps)) % (int)v.size() };
			swap(v.at(j), v.at(randidx));
		}
	}
}

//------------------------------------------------------------------------------
// Convert vector<string> / string / char into lowercase

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

void make_lowercase(std::string& s) {
    for (int i = 0; i< s.size(); ++i) {
        s[i] = to_lower(s[i]);
    }
}

void make_lowercase(vector<std::string>& v) {
	for (std::string& s : v) {
		make_lowercase(s);
	}
}

//------------------------------------------------------------------------------

vector<std::string> get_random_words(
	const std::string& text, bool& should_continue
) {
	if (!should_continue) {
		return {};
	}
	print_hello();
	print_help_get_random_words();
	std::cout << CONST::PROMPT;

	if (entered_exit()) {
		should_continue = false;
		return {};
	}
	clear_buffer();

	vector<std::string> all_words{ words_from_vector(string_to_vector(text)) };
	shuffle(all_words, 10, all_words.size()/4);
	shuffle(all_words, 10, all_words.size()/2);

	int min = randnum(0, all_words.size() * 0.25);
	int max = all_words.size() - randnum(0, all_words.size() * 0.25) - 1;
	vector<std::string> ss { sub_sequence(all_words, min, max, 30) };

	make_lowercase(ss); // avoid lexiographical order confusion (e.g. 'B' < 'a')

	return ss;
}

String_stats get_stats(const vector<std::string>& words, bool& should_continue)
{
	if (!should_continue) {
		return {};
	}
	print_help_get_stats();
	std::cout << CONST::PROMPT;

	if (entered_exit()) {
		should_continue = false;
		return {};
	}
	clear_buffer();

	return str_len_lex_stats(words);
}

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

int main()
try
{

    seed_randint(time(NULL)); // good enough
    const std::string text { SNARK::txt + RADIO::txt + NJALL::txt };

	bool should_continue{ true }; // passed by ref, false will trigger exit
	while (should_continue) {
		vector<std::string> words{ get_random_words(text, should_continue) };
		if (!should_continue) {
			break;
		}

		std::cout << '\n';
		print("WORDS", words, 3, 20);

		String_stats stats{ get_stats(words, should_continue) };
		if (!should_continue) {
			break;
		}

		std::cout << '\n';
		print(stats);

		String_buckets sb{ split_into_buckets(words, str_len_v(words)) };
		print(sb);

		get_continue(should_continue);
		std::cout << '\n';
	}

	std::cout << "Goodbye!" << '\n';
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
