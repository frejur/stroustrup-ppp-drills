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

namespace draw {
constexpr char ul_corner = '>';
constexpr char ur_corner = '<';
constexpr char top_border = '-';
constexpr char top_inters = '+';

constexpr char l_border = '|';
constexpr char r_border = '|';
constexpr char hz_border = ':';

constexpr char bl_corner = '\'';
constexpr char br_corner = '\'';
constexpr char btm_border = '-';
constexpr char btm_inters = '-';

constexpr char check = 'X';

constexpr char bar_l = '[';
constexpr char bar_m = ':';
constexpr char bar_r = ']';

constexpr int bar_max = 65;
} // namespace draw

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

inline const std::string& name_total()
{
	static std::string n{"Total"};
	return n;
}

inline const std::string& name_na()
{
	static std::string n{"Other"};
	return n;
}

struct Char_class
{
	bool status = false;
	Char_class_type type = Char_class_type::Unknown;
	std::string name;
};

bool verify_char_classes(const std::vector<Char_class>& cc);
const std::vector<Char_class>& char_classes(bool skip_names = false);

inline const static int idx_na()
{
	static int i = char_classes().size();
	return i;
}

inline const static int idx_total()
{
	static int i = idx_na() + 1;
	return i;
}

std::vector<Char_class> strip_class_names(std::vector<Char_class> cc_v);
int max_len(const std::vector<Char_class>& cc);
const int& char_class_name_max_len();

struct Char_class_count
{
	long count = 0;
	Char_class char_class;
};

std::vector<Char_class_count> generate_char_class_counts();
const std::vector<Char_class_count>& char_class_counts();

struct Cl_chars
{
	Cl_chars()
	    : classification(
	        std::vector<std::vector<Char_class>>(1, char_classes())){};
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
	    , cl_count(char_class_counts()){};
	void extracted(char& c, Char_class& cc);
	Char_class_stream& operator>>(Cl_chars& chars);
	operator bool() { return bool(src); };
	void clear()
	{
		src.clear();
		buf.clear();
	};
	void reset_count()
	{
		for (Char_class_count& ccc : cl_count) {
			ccc.count = 0;
		}
		ch_count = 0;
		na_count = 0;
	}
	std::vector<Char_class_count> get_count();

private:
	void fill_buffer();
	void incr_ch_class_count(Char_class_type t)
	{
		++cl_count.at(static_cast<int>(t)).count;
	}
	bool buffer_is_full;
	std::istream& src;
	std::stringstream buf;
	std::vector<Char_class_count> cl_count;
	int na_count = 0; // Count unknown char classifications
	int ch_count = 0;
	bool is_truncated = false;
};

std::vector<Char_class_type> char_class_types(char c);
bool char_is_type(char c, Char_class_type t, bool exclude_unknown = false);
std::vector<Char_class_count> get_cl_chars_count(const Cl_chars& chars);
void print_classifications(std::ostream& os, const Cl_chars& chars);
void print_detailed_summary(std::ostream& os,
                            const std::vector<Char_class_count>& count);
void print_overview(std::ostream& os,
                    const std::vector<Char_class_count>& count);
std::string str_for_bar_chart(const std::string& label,
                              int count,
                              int total,
                              bool skip_if_zero = false);
std::string str_for_char_header(const Cl_chars& chars);
std::vector<std::string> str_for_all_class_rows(const Cl_chars& chars);
std::string str_for_single_class_row(
    const std::vector<std::vector<Char_class>>& cc_v,
    int cl_idx,
    bool skip_if_empty = false);
std::string str_for_top_border(const Cl_chars& chars);
std::string str_for_btm_border(const Cl_chars& chars);
void order_count(std::vector<Char_class_count>& ordered);

std::ostream& operator<<(std::ostream& os, Cl_chars cc); // For testing

} // namespace chcl

#endif // CHCL_H
