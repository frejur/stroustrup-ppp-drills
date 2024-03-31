#include "dict.h"
#include "../../../lib/help.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

int dict::Dictionary::bucket_idx(int b_len) const
{
	for (int i = 0; i < buck.size(); ++i) {
		if (buck[i].length != 0 && buck[i].length == b_len) {
			return i;
		}
	}
	return -1;
}

dict::Index_pair dict::Dictionary::word_idx(const std::string& word) const
{
	int b_idx = bucket_idx(word.size());
	if (b_idx == -1) {
		return {-1, -1};
	}
	for (int i = 0; i < buck[b_idx].words.size(); ++i) {
		if (buck[b_idx].words[i].word == word) {
			return {b_idx, i};
		}
	}
	return {b_idx, -1};
}

bool dict::Dictionary::is_banned(const std::string& word) const
{
	for (const std::string& b : banned) {
		if (word == b) {
			return true;
		}
	}
	return false;
}

void dict::Dictionary::insert_word(const std::string& word, int b_idx)
{
	if (b_idx < 0 || b_idx > buck.size() - 1 || buck[b_idx].words.size() == 0) {
		throw std::runtime_error("Cannot 'insert' word into empty bucket");
	}
	int w_idx = 0;
	for (const Word_count& wc : buck[b_idx].words) {
		if (help::tolower(word) < wc.word) {
			break;
		}
		++w_idx;
	}
	if (w_idx == buck[b_idx].words.size()) {
		// Add to end
		buck[b_idx].words.push_back({1, word});
		return;
	}

	// Insert
	buck[b_idx].words.push_back({});
	for (int i = buck[b_idx].words.size() - 1; i > w_idx; --i) {
		buck[b_idx].words[i] = buck[b_idx].words[i - 1];
	}
	buck[b_idx].words[w_idx] = {1, word};
}

void dict::Dictionary::add_word(const std::string& word)
{
	if (word.size() == 0 || is_banned(word)) {
		return;
	}

	Index_pair idx = word_idx(word);

	bool new_w = false;
	if (idx.bucket == -1) {
		idx.bucket = buck.size();
		buck.push_back(word);
		new_w = true;
	} else if (idx.word == -1) {
		insert_word(word, idx.bucket);
		new_w = true;
	} else {
		++buck[idx.bucket].words[idx.word].count;
		if ((buck[idx.bucket].words[idx.word].count > freq.count)
		    || (buck[idx.bucket].words[idx.word].count == freq.count
		        && help::tolower(word) < freq.word)) {
			freq = buck[idx.bucket].words[idx.word];
		}
	}

	if (new_w) {
		++count_u;
		if (count_w > 0) {
			if (word.size() > longest) {
				longest = word.size();
			}
			if (word.size() < shortest) {
				shortest = word.size();
			}
			if (freq.count == 1) {
				if (help::tolower(word) < freq.word)
					freq.word = word;
			}
		} else {
			longest = word.size();
			shortest = word.size();
			freq = {1, word};
		}
	}

	++count_w;
}

std::string dict::Dictionary::shortest_word() const
{
	int b_idx = bucket_idx(shortest);
	bool first = true;
	std::string shortest_w;
	for (const Word_count& wc : buck[b_idx].words) {
		if (first) {
			first = false;
			shortest_w = wc.word;
			continue;
		}
		if (help::tolower(wc.word) < shortest_w) {
			shortest_w = wc.word;
		}
	}
	return shortest_w;
}

std::string dict::Dictionary::longest_word() const
{
	int b_idx = bucket_idx(longest);
	bool first = true;
	std::string longest_w;
	for (const Word_count& wc : buck[b_idx].words) {
		if (first) {
			first = false;
			longest_w = wc.word;
			continue;
		}
		if (help::tolower(wc.word) > longest_w) {
			longest_w = wc.word;
		}
	}
	return longest_w;
}

//------------------------------------------------------------------------------

dict::Word_bucket_sum dict::sum_of_bucket(const Word_bucket& b)
{
	Word_bucket_sum sum{b.length, 0};

	for (const Word_count& c : b.words) {
		sum.count += c.count;
	}
	return sum;
}

std::vector<dict::Word_bucket_sum> dict::sorted_bucket_sums(
    const Dictionary& dict)
{
	std::vector<Word_bucket_sum> sum_v;

	for (const Word_bucket& b : dict.buckets()) {
		Word_bucket_sum sum{sum_of_bucket(b)};

		int idx = 0;
		for (; idx < sum_v.size(); ++idx) {
			if (sum.count > sum_v[idx].count) {
				break;
			}
			if (sum.count == sum_v[idx].count) {
				if (sum.length > sum_v[idx].length) {
					++idx;
				}
				break;
			}
		}

		if (idx == sum_v.size()) {
			// Add to end
			sum_v.push_back(sum);
			continue;
		}

		// Insert
		sum_v.push_back({});
		for (int i = sum_v.size() - 1; i > idx; --i) {
			sum_v[i] = sum_v[i - 1];
		}
		sum_v[idx] = sum;
	}

	return sum_v;
}

//------------------------------------------------------------------------------

std::string dict::str_for_bar_chart(const std::string& label,
                                    int count,
                                    int total,
                                    int label_w,
                                    bool skip_if_zero)
{
	if (skip_if_zero && (count == 0 || total == 0)) {
		return "";
	}
	double p = (static_cast<double>(count) / total);
	int u = static_cast<int>(p * draw::bar_max);

	std::ostringstream bar;
	bar << std::setw(label_w) << label << ": ";
	if (u <= 1) {
		bar << draw::bar_r;
	} else if (u <= 2) {
		bar << draw::bar_l << draw::bar_r;
	} else {
		bar << draw::bar_l;
		for (int i = 0; i < u - 2; ++i) {
			bar << draw::bar_m;
		}
		bar << draw::bar_r;
	}
	bar << ' ' << count << " (";
	if (p < 0.01) {
		bar << "< 1%";
	} else {
		bar << std::fixed << std::setprecision(1) << (p * 100) << '%';
	}

	bar << ')';
	return bar.str();
}

void dict::print_stats(const Dictionary& dict)
{
	std::string shortest{dict.shortest_word()};
	std::string longest{dict.longest_word()};

	std::cout << '\n'
	          << std::setw(24)
	          << "Total number of words: " << dict.count_words() << '\n'
	          << std::setw(24) << "Unique words: " << dict.count_unique()
	          << '\n'
	          << std::setw(24) << "Shortest word: " << dict.shortest_word()
	          << '\n'
	          << std::setw(24) << "Longest word: " << dict.longest_word()
	          << '\n'
	          << '\n';

	std::vector<Word_bucket_sum> sum_v{sorted_bucket_sums(dict)};
	for (const Word_bucket_sum& s : sum_v) {
		std::stringstream label;
		label << s.length << " letter" << (s.length > 1 ? "s" : "");
		std::cout << str_for_bar_chart(label.str(), s.count, dict.count_words())
		          << '\n';
	}
}

void dict::print_words(const Dictionary& dict, const int max_w, const int pad)
{
	for (int i = dict.shortest_word().size(); i <= dict.longest_word().size();
	     ++i) {
		// TODO: Proper sorting
		for (const Word_bucket& b : dict.buckets()) {
			if (b.length == i) {
				print_bucket(b, max_w, pad);
				break;
			}
		}
	}
}

void dict::print_bucket(const Word_bucket& bucket, int max_w, int pad)
{
	if (bucket.length < 1 || bucket.words.size() == 0) {
		return;
	}
	if (max_w < 10) {
		max_w = 10;
	}
	if (max_w > 120) {
		max_w = 120;
	}

	int w_p_ln = max_w / (bucket.length + pad);
	if (w_p_ln == 0) {
		w_p_ln = 1;
	}

	std::cout << bucket.length << "-letter words:" << '\n' << '\n';
	std::stringstream wstr;
	int w_num = 1;
	for (const Word_count& c : bucket.words) {
		wstr.str("");
		if (w_num % w_p_ln == 0) {
			wstr << c.word << " (" << c.count << ")";
			std::cout << wstr.str() << '\n';
		} else {
			wstr << c.word << " (" << c.count << ")";
			int len = wstr.str().size();
			wstr << std::setw((pad + bucket.length) - len) << "";
			std::cout << wstr.str();
			if (w_num == bucket.words.size()) {
				std::cout << '\n';
			}
		}
		++w_num;
	}
	std::cout << '\n';
}
