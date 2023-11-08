#include "../../lib/std_lib_facilities.h"

// Exercise 17. Deduce the min. max. and mode of a sequence of strings.

using std::string;

vector<string> mode_from_sorted(vector<string> sorted_v) {
	int min_freq{};
	int max_freq{};
	int cur_freq{ 0 };
	bool first_freq_already_found{ false };
	vector<string> unique_v;
	vector<int> freq_v;
	vector<string> mode_v;
	for (int i = 0; i < sorted_v.size(); ++i) {
		++cur_freq;
		if (i == (sorted_v.size() - 1) || sorted_v[i] != sorted_v[i + 1]) {
			if (!first_freq_already_found) {
				min_freq = cur_freq;
				max_freq = cur_freq;
				first_freq_already_found = true;
			} else {
				min_freq = std::min(min_freq,  cur_freq);
				max_freq = std::max(max_freq, cur_freq);
			}
			unique_v.push_back(sorted_v[i]);
			freq_v.push_back(cur_freq);
			cur_freq = 0;
		}
	}

	int unique_count{ static_cast<int>(unique_v.size()) };

	if (min_freq == max_freq) {
		return {};
	}
	for (int i = 0; i < unique_count; ++i) {
		if (freq_v[i] == max_freq) {
			mode_v.push_back(unique_v[i]);
		}
	}

	return mode_v;
}

vector<std::string> extract_words(std::string words_str);
//------------------------------------------------------------------------------
int main()
{
	std::cout << "Given a sequence of words, "
		<< "print the minimum, maximum and mode." << '\n'
		<< "Please enter any number of words seperated by spaces." << '\n';

	vector<std::string> words{};
	while (words.size() == 0) {
		std::string input_str{};
		getline(std::cin, input_str);
		words = extract_words(input_str);
		if (words.size() == 0) {
			std::cout << "Invalid input, please try again" << '\n';
		}
	}

	if (words.size() == 1) {
		std::cout << "The word is: " << words.front() << '\n';

		keep_window_open();
		return 0;
	}

	std::cout << "The words are:" << '\t';
	for (std::string word : words) {
		std::cout << word << ", ";
	}
	std::cout << '\n';

	sort(words.begin(), words.end());

	std::cout << "The min. / max. words are: "
		<< words.front() << " / " << words.back() << '\n';

	vector<string> mode_v{ mode_from_sorted(words) };
	int mode_count { static_cast<int>(mode_v.size()) };
	if (mode_count > 0) {
		std::cout << "The mode" << ((mode_count > 1) ? "s are" : " is")
			<< ": " << '\t';
	} else {
		std::cout
			<< "The mode can't be calculated for this seq. of words" << '\n';
	}
	for (int i = 0; i < mode_count; ++i) {
		std::cout << mode_v[i];
		if (i < (mode_count - 1)) {
			std::cout << ", ";
		}
	}
	std::cout << '\n';

	keep_window_open();

	return 0;
}

vector<std::string> extract_words(std::string words_str) {
	vector<std::string> words{};
	std::string word{};
	words_str += ' '; // ensure last word get extracted

	for (int i = 0; i < words_str.size(); ++i) {
		char c{ words_str.at(i) };
		if (!isalnum(c)) {
			if (c != ' ') {
				return {};
			}
			if (word.size() > 0) {
				words.push_back(word);
				word = "";
			}
		} else {
			word += c;
		}
	}
	return words;
}
