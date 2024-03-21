#ifndef CHCL_H
#define CHCL_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace chcl {

constexpr int max_chars_target = 16;    // Ideally each chunk is this big
constexpr int max_additional_chars = 3; // Only this many more before truncating

enum class Char_class_type {
	Unknown = -1,
	Whitespace = 0,
	Letter,
	Digit_dec,
	Digit_hex,
	Uppercase,
	Lowercase,
	Letter_or_digit,
	Control_character,
	Punctuation,
	Printable,
	Letter_digit_or_punctuation,
};

struct Char_class
{
	bool status = false;
	Char_class_type type = Char_class_type::Unknown;
	std::string name;
};

bool verify_char_classes_order(const std::vector<Char_class>& cc);
const std::vector<Char_class>& char_classes();

struct Char_class_count
{
	long count = 0;
	Char_class char_class;
};

std::vector<Char_class_count> generate_char_class_counts();
const std::vector<Char_class_count>& char_class_counts();

struct Cl_chars
{
	std::string chars;
	std::vector<std::vector<Char_class>> classification;
	bool start_is_truncated = false;
	bool end_is_truncated = false;
};

class Char_class_stream
{
public:
	Char_class_stream(std::istream& is)
	    : buffer_is_full(false)
	    , src(is)
	    , count(char_class_counts()){};
	Char_class_stream& operator>>(Cl_chars& chars);

private:
	void fill_buffer();
	bool buffer_is_full;
	std::istream& src;
	std::stringstream buf;
	std::vector<Char_class_count> count;
	bool is_truncated = false;
};

} // namespace chcl

#endif // CHCL_H
