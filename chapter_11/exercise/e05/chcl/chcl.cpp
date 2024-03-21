#include "chcl.h"
#include "../../../lib/help.h"

//------------------------------------------------------------------------------

bool chcl::verify_char_classes_order(const std::vector<Char_class>& cc)
{
	int control_idx = -1;
	for (const Char_class& c : cc) {
		if (static_cast<int>(c.type) != control_idx) {
			return false;
		}
		++control_idx;
	}
	return true;
}

const std::vector<chcl::Char_class>& chcl::char_classes()
{
	using CCT = Char_class_type;
	static std::vector<Char_class> cc{
	    {false, CCT::Whitespace, "Whitespace"},
	    {false, CCT::Letter, "Letter"},
	    {false, CCT::Digit_dec, "Digit(Dec)"},
	    {false, CCT::Digit_hex, "Digit(Hex)"},
	    {false, CCT::Uppercase, "Uppercase"},
	    {false, CCT::Lowercase, "Lowercase"},
	    {false, CCT::Letter_or_digit, "Letter/digit"},
	    {false, CCT::Control_character, "Control ch"},
	    {false, CCT::Punctuation, "Punctuation"},
	    {false, CCT::Printable, "Printable"},
	    {false, CCT::Letter_digit_or_punctuation, "Let/Dig/Punct"},
	};

	static bool is_valid = verify_char_classes_order(cc);
	if (!is_valid) {
		throw std::runtime_error("Invalid order in Character class definition");
	}

	return cc;
}

std::vector<chcl::Char_class_count> chcl::generate_char_class_counts()
{
	static std::vector<Char_class_count> ccc;
	for (const Char_class& cc : char_classes()) {
		ccc.push_back({0, cc});
	}
	return ccc;
}

const std::vector<chcl::Char_class_count>& chcl::char_class_counts()
{
	static std::vector<Char_class_count> ccc{generate_char_class_counts()};
	return ccc;
}

//------------------------------------------------------------------------------

chcl::Char_class_stream& chcl::Char_class_stream::operator>>(Cl_chars& chars)
{
	chars.start_is_truncated = is_truncated;

	fill_buffer();

	chars.end_is_truncated = is_truncated;
	chars.chars = "";
	chars.classification = {};

	char c = 0;
	while (buf.get(c)) {
		using CCT = Char_class_type;
		chars.chars[static_cast<int>(CCT::Whitespace)] = help::isspace(c);
		chars.chars[static_cast<int>(CCT::Letter)] = help::isalpha(c);
		chars.chars[static_cast<int>(CCT::Digit_dec)] = help::isdigit(c);
		chars.chars[static_cast<int>(CCT::Digit_hex)] = help::isxdigit(c);
		chars.chars[static_cast<int>(CCT::Uppercase)] = help::isupper(c);
		chars.chars[static_cast<int>(CCT::Lowercase)] = help::islower(c);
		chars.chars[static_cast<int>(CCT::Letter_or_digit)] = help::isalnum(c);
		chars.chars[static_cast<int>(CCT::Control_character)] = help::iscntrl(c);
		chars.chars[static_cast<int>(CCT::Punctuation)] = help::ispunct(c);
		chars.chars[static_cast<int>(CCT::Printable)] = help::isprint(c);
		chars.chars[static_cast<int>(CCT::Letter_digit_or_punctuation)]
		    = help::isgraph(c);
	}
}

void chcl::Char_class_stream::fill_buffer()
{
	if (buffer_is_full) {
		return;
	}
	char c = 0;
	int count_c = 0;
	while (src.get(c) && count_c < max_chars_target) {
		buf << c;
		++count_c;
	}
	char next_c = 0;
	if (!help::isspace(c) && src.get(next_c)) {
		src.putback(next_c);
		if (!help::isspace(next_c)) {
			std::string next_word;
			src >> next_word;
			if (next_word.size() > max_additional_chars) {
				for (int i = next_word.size() - 1; i >= 0; --i) {
					src.putback(next_word[i]);
				}
			}
			for (int j = 0; j < max_additional_chars; ++j) {
				buf << next_word[j];
			}
		}
	}
	buffer_is_full = true;
}
