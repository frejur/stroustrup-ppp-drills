#include "lib_helpers.h"

// Valid ISBN (Not the official definition of a valid ISBN):
// 1. 4 groups of characters, separated by hyphens ("-").
// 2. A total number of exactly 10 characters.
// 3. The last group may only contain a single digit, or the letter 'X'.
//    (Lowercase 'x' is allowed but converted to uppercase)
// 4. The first three groups may only contain digits.

HLP::ISBN_code HLP::is_valid_ISBN(const std::string& isbn) {
	using CODE = HLP::ISBN_code;
	if (isbn.size() != 13) {
		return CODE::Invalid_string_length;
	}
	if (!isdigit(isbn.front())) {
		return CODE::Expected_digit;
	}
	if (!isdigit(isbn.back()) && isbn.back() != 'X') {
		return CODE::Expected_digit_or_x;
	}
	if (isbn[11] != '-') {
		return CODE::Expected_hyphen;
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
				return CODE::Empty_group;
			}
			if (num_groups == 3) {
				return CODE::Invalid_number_of_groups;
			}
			num_chars_in_group = 0;
			++num_groups;
		} else {
			return CODE::Expected_digit;
		}
	}
	if (num_groups < 3) {
		return CODE::Invalid_number_of_groups;
	}

	return CODE::Success;
}

//------------------------------------------------------------------------------

// Valid user name
// 1. Cannot be empty
// 2. Any number of words separated by:
//    a. single spaces (' ')
//       OR
//    b. single hyphens '-'.
// 3. Words should only consist of letters.
// 4. The name must start and end with a letter.

HLP::User_name_code HLP::is_valid_user_name(const std::string user) {
	using CODE = HLP::User_name_code;
	if (user.size() == 0) {
		return CODE::Empty;
	}
	if (!isalpha(user.front()) || !isalpha(user.back())) {
		return CODE::Expected_letter;
	}

	// First and last character confirmed to be valid
	for (int i = 1; i < user.size() - 1; ++i) {
		if (isalpha(user[i - 1])) {
			if(!isalpha(user[i]) && user[i] != '-' && user[i] != ' ') {
				return CODE::Invalid_character;
			}
		}
		else if (!isalpha(user[i])) {
			if (user[i] == '-') {
				return CODE::Invalid_hyphen;
			}
			else if (user[i] == ' ') {
				return CODE::Invalid_space;
			}
			else {
				return CODE::Invalid_character;
			}
		}
	}

	return CODE::Success;
}


//------------------------------------------------------------------------------

// Valid Card number
// 1. A six digit number
// 2. The first digit must not be '0'

HLP::Card_number_code HLP::is_valid_card_number(const std::string card) {
	using CODE = HLP::Card_number_code;
	if (card.size() != 6) {
		return CODE::Invalid_string_length;
	}
	bool checked_first_c{ false };
	for (char c : card) {
		if (!isdigit(c)) {
			return CODE::Non_digit;
		}
		else if (!checked_first_c && c == '0') {
			return CODE::Invalid_first_digit;
		}
		checked_first_c = true;
	}
	return CODE::Success;
}
