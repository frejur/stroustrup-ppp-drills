#include "../../lib/std_lib_facilities.h"

// Chapter 6, Exercise 4. Name-value pairs using classes.

// Rework Exercise 19 (, 20, 21) of Chapter 4 using a vector of a user
// defined type 'Name_value>' - a class with members:
// <string> 'name', and <double> 'score'

vector<std::string> extract_words(std::string words_str);
std::string strip_dots(std::string s);
bool is_number(std::string s);

class Name_value {
public:
	Name_value(std::string n, double s) : name(n), score(s) {};
	std::string name;
	double score;
};

//------------------------------------------------------------------------------
int main()
{
	std::cout
		<< "Collect a number of name-value pairs, check for duplicates" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n'
		<< "Please enter a name followed by a number (delimiter = ' ')." << '\n'
		<< '\n'
		<< "The name must start with a letter, and may only contain" << '\n'
		<< "alphanumerics, spaces and hyphens."
		<< '\n' << '\n';

	const std::string TXT_SEARCH_BY_NAME {
		"+ You can search for entries by entering a name surrounded w. quotes."
	};
	const std::string TXT_SEARCH_BY_SCORE {
		"+ You can also search for past entries by entering a score value."
	};

	vector<Name_value> name_score_v{};
	int exit_code{ 0 };

	bool empty_line{ false };
	std::string input_str{};
	while (!empty_line) {
		vector<std::string> words{};
		std::string name_str{ "" };
		std::string score_str{};
		double score{};
		bool score_is_set{ false };
		bool search_by_name{ false };
		bool name_was_found { false };
		bool search_by_score{ false };
		bool score_was_found { false };
		double matching_score{};
		vector<std::string> matching_names{};

		while (words.size() == 0 || !score_is_set) {
			getline(std::cin, input_str);
			if (input_str.size() == 0) {
				empty_line = true;
				break;
			}

			// Check for search
			if ((name_score_v.size() > 0)) {
			 	if ((input_str.size() > 2) &&
					(input_str.front()) == '"' && (input_str.back() == '"'))
				{
					input_str = input_str.substr(1, input_str.size() - 2);
					search_by_name = true;
				} else if (is_number(input_str)) {
					matching_score = stod(input_str);
					search_by_score = true;
					break;
				}
			}

			words = extract_words(input_str);
			if (search_by_name) {
				if (words.size() == 0 || !isalpha(words.at(0).front())) {
					std::cout << "Invalid search term: "
						<< "Invalid name, please try again!" << '\n' << '\n';
					continue;
				}
			} else if (words.size() < 2 || !isalpha(words.at(0).front())) {
				std::cout << "Invalid input: "
					<< "Invalid name, please try again!" << '\n' << '\n';
				continue;
			}

			if (!search_by_name) {
				score_str = words.back();
				if (!is_number(score_str)) {
					std::cout << "Invalid input: "
						<< "The last element is not a number, please try again!"
						<< '\n' << '\n';
					continue;
				}
				words.pop_back();
				score = std::stod(score_str);
				score_is_set = true;
			}

			for (int i = 0; i < words.size(); ++i) {
				name_str += ((i > 0) ? " " : "") + strip_dots(words.at(i));
			}

			if (search_by_name) {
				break;
			}
		}
		if (!empty_line) {
			// Check for duplicates / Search
			for (Name_value nv : name_score_v) {
				if (search_by_score) {
					if (nv.score == matching_score) {
						score_was_found = true;
						matching_names.push_back(nv.name);
					}
					continue;
				}
				if (nv.name == name_str) {
					if(search_by_name) {
						name_was_found = true;
						matching_score = nv.score;
						break;
					}
					std::cout << "An entry with that name already exists, "
						<< "aborting..." << '\n';
					exit_code = 1;
					goto EXIT;
				}
			}

			if (search_by_score) {
				if (score_was_found) {
					if (matching_names.size() == 1) {
						std::cout << "An entry with a score value of "
							<< matching_score << " was found:" << '\n';
					} else {
						std::cout << "The following entries have a score value "
						<< "of " << matching_score << ":" << '\n';
					}
					for (std::string n : matching_names) {
						std::cout
							<< '\t' << matching_score << '\t' << n << '\n';
					}
				} else {
					std::cout << "No entry with a score value of "
						<< matching_score << " was found." << '\n';
				}
			}else if (search_by_name) {
				if (name_was_found) {
					std::cout << "An entry for the name \"" << name_str
						<< "\" was found: " << '\n'
						<< '\t' << name_str << '\t' << matching_score << '\n';
				} else {
					std::cout << "No entry for the name \"" << name_str
						<< "\" was found." << '\n';
				}
			} else {
				name_score_v.push_back({ name_str, score });
				std::cout << "Name and Score recorded..." << '\n';
			}
			std::cout
				<< "Please submit another entry, or press <ENTER>"
				<< "to finish." << '\n'
				<< TXT_SEARCH_BY_NAME << '\n'
				<< TXT_SEARCH_BY_SCORE << '\n'
				<< '\n';
		}
	}

	std::cout << "Recorded values:" << '\n';
	for (Name_value nv : name_score_v) {
		std::cout << '\t' << nv.score << '\t' << nv.name << '\n';
	}

EXIT:
	keep_window_open();

	return exit_code;
}

double extract_score;

vector<std::string> extract_words(std::string words_str) {
	vector<std::string> words{};
	std::string word{};
	words_str += ' '; // ensure last word gets extracted

	for (int i = 0; i < words_str.size(); ++i) {
		char c{ words_str.at(i) };
		if (!isalnum(c) && c != '.' && c != '-') {
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

std::string strip_dots(std::string s) {
	std::string new_s;
	for (char c : s) {
		if (c != '.') {
			new_s += c;
		}
	}
	return new_s;
}

bool is_number(std::string s) {
	int dot_count{ 0 };
	for (int i = 0; i < s.size(); ++i) {
		char c{ s.at(i) };
		if (i == 0 && c == '-') {
			continue;
		}
		if (c == '.' && (++dot_count < 2)) {
			continue;
		}
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}
