#ifndef LIB_HELPERS_H
#define LIB_HELPERS_H

#include <string>

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

ISBN_code is_valid_ISBN(const std::string& isbn);

//------------------------------------------------------------------------------

enum class User_name_code
{
	Success = 0,
	Empty,
	Invalid_character,
	Expected_letter,
	Invalid_hyphen,
	Invalid_space
};


User_name_code is_valid_user_name(const std::string user);

//------------------------------------------------------------------------------

enum class Card_number_code
{
	Success = 0,
	Invalid_string_length,
	Non_digit,
	Invalid_first_digit
};


Card_number_code is_valid_card_number(const std::string card);

} // HLP -----------------------------------------------------------------------

#endif // LIB_HELPERS_H
