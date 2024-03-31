#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>

namespace dict {

struct Word_count
{
	int count = 0;
	std::string word;
};

struct Word_bucket
// Group words by length
{
	Word_bucket(){};
	Word_bucket(std::string word)
	    : length(word.size())
	    , words({{1, word}}){};
	int length = 0;
	std::vector<Word_count> words;
};

struct Index_pair
{
	int bucket;
	int word;
};

class Dictionary
// Store words in memory, group by length and sort alphabetically,
// count unique and total.
// Words are stored exactly as they are entered, e.g:
// "Abc" != "abc", "Abc" != "Abc "
{
public:
	Dictionary(){};
	Dictionary(std::vector<std::string> ignore_words)
	    : banned(ignore_words){};
	void add_word(const std::string& s);
	const std::vector<Word_bucket>& buckets() const { return buck; };
	std::string shortest_word() const;
	std::string longest_word() const;
	int count_unique() const { return count_u; };
	int count_words() const { return count_w; };

private:
	int count_w = 0;
	int count_u = 0;
	int shortest = 0;
	int longest = 0;
	Word_count freq; // copy of the most frequent word
	std::vector<std::string> banned;
	std::vector<Word_bucket> buck;

	int bucket_idx(int b_len) const;
	Index_pair word_idx(const std::string& word) const;
	bool is_banned(const std::string& word) const;
	void insert_word(const std::string& word, int b_idx);
};

//------------------------------------------------------------------------------

struct Word_bucket_sum
{
	int length;
	int count;
};

Word_bucket_sum sum_of_bucket(const Word_bucket& b);
std::vector<Word_bucket_sum> sorted_bucket_sums(const Dictionary& dict);

//------------------------------------------------------------------------------

namespace draw {
constexpr char bar_l = '[';
constexpr char bar_m = ':';
constexpr char bar_r = ']';
constexpr int bar_max = 65;
} // namespace draw

std::string str_for_bar_chart(const std::string& label_suffix,
                              int count,
                              int total,
                              int label_w = 16,
                              bool skip_if_zero = false);

//------------------------------------------------------------------------------

void print_stats(const Dictionary& dict);
void print_words(const Dictionary& dict, const int max_w, const int pad);
void print_bucket(const Word_bucket& bucket, int max_w, int pad);

} // namespace dict

#endif // DICTIONARY_H
