#include "name_age_pairs.h"
#include "helpers.h"
#include <algorithm>

using std::string;
using std::vector;

void Name_age_pairs::read_names()
{
	os << "Enter the names of some people, finish with ';'" << '\n';

	std::string s;
	while (is >> s)
	try {
		if (s == ";" && names.size() > 0) {
			break;
		}

		// scan until ';', clear buffer and add back ';' if found
		string s2{ "" };
		for (char c : s) {
			if (c == ';') {
				clear_buffer(is);
				is.putback('\n');
				is.putback(';');
				is.putback(' ');
				break;
			}
			s2 += c;
		}
		if (s2.size() > 0) {
			names.push_back(s2);
		}
	}
	catch (std::exception& e) {
		es << "Error: " << e.what() << '\n';
	}
	catch (...) {
		throw std::runtime_error("Unknown error");
	}
	clear_buffer(is);
}

void Name_age_pairs::read_ages()
{
	if (names.size() == 0) {
		throw std::runtime_error("Cannot add ages for an empty list of names");
	}
	if (names.size()==1) {
		os << "How old is " << names.front() << '?' << '\n';
	} else {
		os
			<< "How old are they? Let's start with " << names.front() << '\n';
	}

	int age{};
	char c{};
	while (is >> c)
	try {
		if (!isdigit(c)) {
			throw std::runtime_error("Bad input");
		} else {
			is.putback(c);
			is >> age;
		}

		if (age <= 0) {
			throw std::runtime_error("Age cannot be below a value of 1");
		}

		ages.push_back(age);

		if (ages.size() < names.size()) {
			os << "So " << names.at(ages.size() - 1) << " is " << age
			   << ", what about " << names.at(ages.size()) << '?'
			   << '\n';
		} else {
			break;
		}
	}
	catch (std::exception e) {
		es << "Error: " << e.what() << '\n';
		clear_buffer(is);
	}
	catch (...) {
		throw std::runtime_error("Unknown error");
	}

	os << "All ages were registered." << '\n';
	clear_buffer(is);
}

void Name_age_pairs::print(const string& label) const
{
	if (names.size() != ages.size()) {
		throw std::runtime_error("The number of names does not match the"
								 " number of age values");
	}
	if (names.size() == 0) {
		throw std::runtime_error("Cannot print an empty name-age list");
	}
	os << label << ':' << '\n';
	if (names.size() == 0) {
		os << "Empty" << '\n';
		return;
	}
	for (int i = 0; i < names.size(); ++i) {
		os << ages.at(i) << '\t' << '\t' << names.at(i) << '\n';
	}
	os << '\n';
}

void Name_age_pairs::sort()
{
	vector<string> unsorted{ names };
	std::sort(names.begin(), names.end());
	int i{ 0 };
	while (true) {
		// skip to first non-checked or return
		while (unsorted.at(i) == names.at(i)) {
			if (i == ages.size() - 1) {
				return;
			}
			++i;
		}
		int match{ find_element(names.at(i), unsorted, names) };
		if (match == -1) {
			throw std::runtime_error("Could not find element of unsorted"
			                         " in sorted");
		}

		if (unsorted.at(match) != names.at(match)) {
			if (unsorted.at(i) != names.at(i)) {
				swap(ages.at(i), ages.at(match));
				swap(unsorted.at(i), unsorted.at(match));
				i = match;
				continue;
			}
		}

		i = 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Name_age_pairs& na) {
	if (na.names.size() != na.ages.size()) {
		throw std::runtime_error("The number of names does not match the"
								 " number of age values");
	}
	if (na.names.size() == 0) {
		throw std::runtime_error("Cannot print an empty name-age list");
	}
	for (int i = 0; i < na.names.size(); ++i) {
		os << na.ages.at(i) << '\t' << '\t' << na.names.at(i) << '\n';
	}
	return os;
}

bool operator==(const Name_age_pairs& a, const Name_age_pairs& b) {
	if ((a.names.size() != b.names.size()) ||
	    (a.ages.size() != b.ages.size())
	) {
		return false;
	}
	for (int i = 0; i < a.names.size(); ++i) {
		if (a.names[i] != b.names[i]) {
			return false;
		}
		if ((i < a.ages.size()) &&
		    (a.ages[i] != b.ages[i])
		) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Name_age_pairs& a, const Name_age_pairs& b) {
	return !(a==b);
}

