#ifndef LIB_HELPERS_H
#define LIB_HELPERS_H

#include <string>
#include <stdexcept>
#include <vector>

namespace HLP { // -------------------------------------------------------------

enum class ISBN_code
{
	Success = 0,
	Invalid_string_length,
	Expected_digit,
	Expected_hyphen,
	Expected_digit_or_x,
	Empty_group,
	Invalid_number_of_groups
};

// Valid ISBN (Not the official definition of a valid ISBN):
// 1. 4 groups of characters, separated by hyphens ("-").
// 2. A total number of exactly 10 characters.
// 3. The last group may only contain a single digit, or the letter 'X'.
//    (Lowercase 'x' is allowed but converted to uppercase)
// 4. The first three groups may only contain digits.

ISBN_code is_valid_ISBN(const std::string& isbn) {
	if (isbn.size() != 13) {
		return ISBN_code::Invalid_string_length;
	}
	if (!isdigit(isbn.front())) {
		return ISBN_code::Expected_digit;
	}
	if (!isdigit(isbn.back()) && isbn.back() != 'X') {
		return ISBN_code::Expected_digit_or_x;
	}
	if (isbn[11] != '-') {
		return ISBN_code::Expected_hyphen;
	}
	// Length confirmed to be valid

	int num_groups{ 1 }; // Last group confirmed to be valid
	int num_chars_in_group{ 1 };   // First char confirmed to be valid
	for (int i = 1; i < 11; ++i) { // and the two last chars (0, 11 and 12)
		if (isdigit(isbn[i])) {
			++num_chars_in_group;
		}
		else if (isbn[i] == '-') {
			if (num_chars_in_group == 0) {
				return ISBN_code::Empty_group;
			}
			if (num_groups == 3) {
				return ISBN_code::Invalid_number_of_groups;
			}
			num_chars_in_group = 0;
			++num_groups;
		} else {
			return ISBN_code::Expected_digit;
		}
	}
	if (num_groups < 3) {
		return ISBN_code::Invalid_number_of_groups;
	}

	return ISBN_code::Success;
}


} // HLP -----------------------------------------------------------------------

#endif // LIB_HELPERS_H
