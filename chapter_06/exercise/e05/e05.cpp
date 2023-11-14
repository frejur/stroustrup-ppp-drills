#include "../../lib/std_lib_facilities.h"

// Chapter 6, Exercise 5 and 6. English grammar

// Exercise 5: Define grammar that can describe sentences such as:
//		"The birds fly but the fish swim"

class Grammar {
	public:
		Grammar(
			vector<std::string> conj_v,
//			vector<std::string> art_v,
			vector<std::string> noun_v,
			vector<std::string> verb_v,
			vector<char> punct_v
		) :	conjunctions(conj_v),
//			articles(art_v),
			nouns(noun_v),
			verbs(verb_v),
			punctuation(punct_v)
		{
			if (
				conjunctions.size() * /* articles.size() * */ nouns.size() *
				verbs.size() * punctuation.size() == 0
			) {
				error("Incomplete grammar");
			}
		};
		bool is_conjunction(std::string s) { return is_x(s, conjunctions); };
//		bool is_article(std::string s) { return is_x(s, articles); };
		bool is_noun(std::string s) { return is_x(s, nouns); };
		bool is_verb(std::string s) { return is_x(s, verbs); };
		bool is_punctuation(char c) { return is_x(c, punctuation); };
		std::string conjunctions_string() { return x_string(conjunctions); };
//		std::string articles_string() { returnx_string(articles); };
		std::string nouns_string() { return x_string(nouns); };
		std::string verbs_string() { return x_string(verbs); };
		std::string punctuation_string() { return x_string(punctuation); };
		std::string example_string();
		vector<std::string> extract_words(std::string);
		bool is_sentence(vector<std::string> words);
	private:
		const vector<std::string> conjunctions;
//		const vector<std::string> articles;
		const vector<std::string> nouns;
		const vector<std::string> verbs;
		const vector<char> punctuation;
		bool is_x(std::string x, vector<std::string> v);
		bool is_x(char x, vector<char> v);
		bool is_statement(vector<std::string> words);
		std::string x_string(vector<std::string> v);
		std::string x_string(vector<char> v);
};

bool Grammar::is_x(std::string x, vector<std::string> v) {
	for (std::string s : v) {
		if (x == s) {
			return true;
		}
	}
	return false;
};

bool Grammar::is_x(char c, vector<char> v) {
	for (char x : v) {
		if (x == c) {
			return true;
		}
	}
	return false;
};

std::string Grammar::example_string() {
	return (
		nouns.front() + " " + verbs.front() + " " + conjunctions.front() + " "
		+ nouns.at(1%nouns.size()) + " " + verbs.at(1%nouns.size()) + " "
		+ punctuation.front()
	);
}

vector<std::string> Grammar::extract_words(std::string s) {
	vector<std::string> words{};
	s += ' ';
	std::string word{ "" };
	for (char c : s) {
		if (c == ' ') {
			if (word.size()) {
				words.push_back(word);
				word = "";
			}
			continue;
		}
		if (isalpha(c)) {
			word += c;
			continue;
		}
		error("Not a character or space");
	}
	return words;
};

std::string Grammar::x_string(vector<std::string> v) {
	if (v.size() == 0) {
		return "";
	}
	std::string s;
	s += v.front();
	for (int i = 1; i < v.size(); ++i) {
		s += ", " + v.at(i);
	}
	return s;
}

std::string Grammar::x_string(vector<char> v) {
	vector<std::string> s_v;
	for (char c : v) {
		s_v.push_back(std::string() + "'" + c + "'");
	}
	return x_string(s_v);

}

bool Grammar::is_statement(vector<std::string> words) {
	if (words.size() != 2) {
		error("Expected two words in statement, found " +
			std::to_string(words.size())
		);
	}
	return ( is_noun(words.front()) && is_verb(words.back()));
}

bool Grammar::is_sentence(vector<std::string> words) {
	// validates sentence without the punctuation mark
	if (words.size() < 2  || (words.size() > 3 && (words.size() - 2)%3 != 0)) {
		return false;
	}
	if (words.size() == 2) {
		return (is_statement(words));
	}
	for (int i = 0; i < words.size(); i += 3) {
		if (!is_statement({ words.at(i), words.at(i + 1) }) ||
			((i + 2) != words.size() && !is_conjunction(words.at(i + 2)))
		) {
			return false;
		}
	}
	return true;
}

//	Sentence:
//		Statement Punctuation
//		Statement Conjuntion Statement Punctuation
//  Statement:
//		Article Noun Verb
//	Conjunction:
//		"and"
//		"or"
//		"but"
//	Article:
//		"the"
//		"some"
//	Noun:
//		"birds"
//		"fish"
//	Verb:
//		"fly"
//		"swim"
//	Punctuation:
//		'.', '!'

// Exercise 6: Write a program that checks if a sentence is correct according
// to the grammar above but:
// - Don't bother with the "article" token.
// - The sentence needs to be terminated with a space and a dot ' .'.
// Ergo:
// "Birds fly but fish swim ." == Correct

int main()
try {

	Grammar english{
		{ "and", "or", "but" },
		{ "birds", "fish" },
		{ "fly", "swim" },
		{ '.', '!' }
	};

	std::cout
		<< "English grammar" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n'
		<< "Write a sentence that follows this format:" << '\n'
		<< "> Noun Verb Conjuncture Noun Verb Punctuation" << '\n' << '\n'
		<< "Nouns: " << english.nouns_string() << '\n'
		<< "Verbs: " << english.verbs_string() << '\n'
		<< "Conjunctions: " << english.conjunctions_string() << '\n'
		<< "Punctuation Marks: " << english.punctuation_string() << '\n'
		<< '\n'
		<< "Example:" << '\n'
		<< english.example_string() << '\n'
		<< "(Note the space before the punctuation mark)"
		<< '\n' << '\n';

	vector<std::string> word_v{};
	std::string words{};
	std::string word{};
	while (std::cin >> word) {
		words += ' ' + word;
		if (word.size() == 1 && english.is_punctuation(word.front())) {
			words.pop_back();
			word_v = english.extract_words(words);
			words = "";
			for (std::string w : word_v) {
				std::cout << w << '\t' << '\t';
			}
			std::cout << '\n';
			for (std::string w : word_v) {
				std::string w_type { "UNKNOWN" };
				if (english.is_conjunction(w)) {
					w_type = "CONJ.";
				} else if (english.is_verb(w)) {
					w_type = "VERB";
				} else if (english.is_noun(w)) {
					w_type = "NOUN";
				}
				std::cout << w_type << '\t' << '\t';
			}
			if (english.is_sentence(word_v)) {
				std::cout << "Your grammar is perfect!" << '\n';
			} else {
				std::cout << "You done goofed!" << '\n';
			}
		}
	}

	keep_window_open();

	return 0;
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    keep_window_open();
    return 1;
}
catch (...) {
    std::cerr << "std::exception" << ' ' << '\n';
    keep_window_open();
    return 2;
}
