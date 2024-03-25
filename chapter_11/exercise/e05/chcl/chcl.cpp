#include "chcl.h"
#include "../../../lib/help.h"
#include <iomanip>
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------------

bool chcl::verify_char_classes(const std::vector<Char_class>& cc)
{
	// Verify the right order (Same as Type enum class)
	// Verify no clash with reserved names
	int control_idx = 0;
	for (const Char_class& c : cc) {
		if (static_cast<int>(c.type) != control_idx || c.name == name_total()
		    || c.name == name_na()) {
			return false;
		}
		++control_idx;
	}
	return true;
}

const std::vector<chcl::Char_class>& chcl::char_classes(bool skip_names)
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

	static std::vector<Char_class> cc_no_names{strip_class_names(cc)};

	static bool is_valid = verify_char_classes(cc);
	if (!is_valid) {
		throw std::runtime_error("Invalid order in Character class definition");
	}

	return (skip_names) ? cc_no_names : cc;
}

static std::vector<chcl::Char_class> chcl::strip_class_names(
    std::vector<Char_class> cc_v)
{
	for (Char_class& cc : cc_v) {
		cc.name = "";
	}
	return cc_v;
}

int chcl::max_len(const std::vector<Char_class>& cc)
{
	int max = 0;
	for (const Char_class& cc : char_classes()) {
		if (cc.name.size() > max) {
			max = cc.name.size();
		}
	}
	return max;
}
const int& chcl::char_class_name_max_len()
{
	static int max{max_len(char_classes())};
	return max;
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
	if (buf.bad() || !src.good()) {
		return *this; // give up
	}

	chars.start_is_truncated = is_truncated;

	fill_buffer();

	chars.end_is_truncated = is_truncated;
	chars.chars = "";
	chars.classification = {};

	char c = 0;
	int count = 0;
	while (buf.get(c)) {
		bool skip_names = count > 0;
		chars.classification.push_back(char_classes(skip_names));
		chars.chars.push_back(c);

		using CCT = Char_class_type;
		std::vector<CCT> types{char_class_types(c)};
		if (types.size() == 0) {
			++na_count;
		} else {
			for (CCT t : types) {
				incr_ch_class_count(t);
				chars.classification.back().at(static_cast<int>(t)).status = true;
			}
		}
		++count;
	}
	ch_count += count;
	buffer_is_full = false;
	return *this;
}

std::vector<chcl::Char_class_count> chcl::Char_class_stream::get_count()
{
	std::vector<Char_class_count> ccc = cl_count;
	ccc.push_back({na_count, {}}); // Unknown
	ccc.push_back({ch_count, {}}); // Total
	return ccc;
}

void chcl::Char_class_stream::fill_buffer()
{
	if (buffer_is_full) {
		return;
	}

	is_truncated = false;

	buf.clear();
	char c = 0;
	int count_c = 0;
	while (count_c < max_chars_target && src.get(c)) {
		buf << c;
		++count_c;
	}

	if (count_c == 0) {
		src.clear(std::ios_base::failbit);
		return;
	}

	char next_c = 0;
	if (src && !help::isspace(c) && src.get(next_c)) {
		src.putback(next_c);
		if (!help::isspace(next_c)) {
			std::string next_word;
			src >> next_word;
			if (next_word.size() > max_additional_chars) {
				is_truncated = true;
				for (int i = next_word.size() - 1; i >= 0; --i) {
					src.putback(next_word[i]);
				}
			}
			for (int j = 0; j < max_additional_chars; ++j) {
				if (j > next_word.size() - 1) {
					break;
				}
				buf << next_word[j];
			}
		}
	}
	if (src.eof()) {
		src.clear(std::ios_base::goodbit); // EOF triggered during fill is not
		                                   // a failed extraction
	}
	buffer_is_full = true;
}

std::ostream& chcl::operator<<(std::ostream& os, Cl_chars cc)
{
	if (!os || cc.chars.size() == 0) {
		return os;
	}
	std::stringstream format_chars;
	std::stringstream count_chars;

	if (cc.start_is_truncated) {
		format_chars << "(...) ";
		count_chars << "(...) ";
	}

	for (int i = 0; i < cc.chars.size(); ++i) {
		char c = cc.chars[i];
		switch (c) {
		case '\t':
			format_chars << " \\t";
			break;
		case '\n':
			format_chars << " \\n";
			break;
		default:
			format_chars << " " << c << " ";
		}
		count_chars << std::setw(2) << (i + 1) << " ";
	}

	if (cc.end_is_truncated) {
		format_chars << "(...) ";
		count_chars << "(...) ";
	}

	os << format_chars.str() << '\n';
	os << count_chars.str() << '\n';
	return os;
}

//------------------------------------------------------------------------------
// Drawing stuff

void chcl::print_classifications(std::ostream& os, const Cl_chars& chars)
{
	if (!os || chars.chars.size() == 0) {
		return;
	}

	os << str_for_char_header(chars) << '\n'
	   << str_for_top_border(chars) << '\n';

	for (const std::string& s : str_for_all_class_rows(chars)) {
		if (s.size() > 0) {
			os << s << '\n';
		}
	}

	os << str_for_btm_border(chars) << '\n';
}

std::string chcl::str_for_char_header(const Cl_chars& chars)
{
	std::stringstream ss;

	// Characters
	ss << std::setw(char_class_name_max_len() + 1) << "";
	for (int i = 0; i < chars.chars.size(); ++i) {
		char c = chars.chars[i];
		switch (c) {
		case '\t':
			ss << " \\t ";
			break;
		case '\n':
			ss << " \\n ";
			break;
		default:
			ss << "  " << c << " ";
		}
	}
	return ss.str();
}

std::string chcl::str_for_top_border(const Cl_chars& chars)
{
	std::stringstream ss;

	ss << std::setw(char_class_name_max_len() + 2) << draw::ul_corner;

	for (int i = 0; i < chars.chars.size(); ++i) {
		ss << draw::top_border << draw::top_border << draw::top_border;
		if (i < chars.chars.size() - 1) {
			ss << draw::top_inters;
		} else {
			ss << draw::ur_corner;
		}
	}
	return ss.str();
}

std::string chcl::str_for_btm_border(const Cl_chars& chars)
{
	std::stringstream ss;

	ss << std::setw(char_class_name_max_len() + 2) << draw::bl_corner;

	for (int i = 0; i < chars.chars.size(); ++i) {
		ss << draw::btm_border << draw::btm_border << draw::btm_border;
		if (i < chars.chars.size() - 1) {
			ss << draw::btm_inters;
		} else {
			ss << draw::br_corner;
		}
	}
	return ss.str();
}

std::vector<std::string> chcl::str_for_all_class_rows(const Cl_chars& chars)
{
	std::vector<std::string> rows;
	for (int i = 0; i < char_classes().size(); ++i) {
		rows.push_back(str_for_single_class_row(chars.classification, i));
	}
	rows.push_back(str_for_single_class_row(chars.classification, -1, true));
	return rows;
}

std::string chcl::str_for_single_class_row(
    const std::vector<std::vector<Char_class>>& cc_v,
    int cl_idx,
    bool skip_if_empty)
{
	int count_check = 0;
	std::ostringstream ss;
	std::string name = (cl_idx == -1) ? name_na() : cc_v.front()[cl_idx].name;
	ss << std::setw(char_class_name_max_len() + 1) << name << draw::l_border;
	for (int i = 0; i < cc_v.size(); ++i) {
		bool check;
		if (cl_idx == -1) {
			check = true;
			for (const Char_class& cl : cc_v[i]) {
				if (cl.status) {
					check = false;
					break;
				}
			}
		} else {
			check = cc_v[i][cl_idx].status;
		}

		if (check) {
			++count_check;
		}

		ss << " " << (check ? draw::check : ' ') << " ";
		if (i < cc_v.size() - 1) {
			ss << draw::hz_border;
		} else {
			ss << draw::r_border;
		}
	}
	if (skip_if_empty && count_check == 0) {
		return "";
	}
	return ss.str();
}

std::vector<chcl::Char_class_count> chcl::get_cl_chars_count(
    const Cl_chars& chars)
{
	std::vector<chcl::Char_class_count> count = char_class_counts();
	count.push_back({}); // Unknown
	count.push_back({}); // Total

	if (chars.chars.size() == 0) {
		return count;
	}

	using CCT = Char_class_type;
	for (char c : chars.chars) {
		std::vector<CCT> types{char_class_types(c)};
		if (types.size() == 0) {
			++count.at(idx_na()).count;
		} else {
			for (CCT t : types) {
				++count.at(static_cast<int>(t)).count;
			}
		}
	}
	count.at(idx_total()).count = chars.chars.size();
	return count;
}

std::vector<chcl::Char_class_type> chcl::char_class_types(char c)
{
	std::vector<Char_class_type> types;
	for (const Char_class& cc : char_classes()) {
		if (char_is_type(c, cc.type, true)) {
			types.push_back(cc.type);
		}
	}
	return types;
}

bool chcl::char_is_type(char c, Char_class_type t, bool exclude_unknown)
{
	using CCT = Char_class_type;
	if (exclude_unknown && t == CCT::Unknown) {
		return false;
	}
	switch (t) {
	case CCT::Whitespace:
		return help::isspace(c);
	case CCT::Letter:
		return help::isalpha(c);
	case CCT::Digit_dec:
		return help::isdigit(c);
	case CCT::Digit_hex:
		return help::isxdigit(c);
	case CCT::Uppercase:
		return help::isupper(c);
	case CCT::Lowercase:
		return help::islower(c);
	case CCT::Letter_or_digit:
		return help::isalnum(c);
	case CCT::Control_character:
		return help::iscntrl(c);
	case CCT::Punctuation:
		return help::ispunct(c);
	case CCT::Printable:
		return help::isprint(c);
	case CCT::Letter_digit_or_punctuation:
		return help::isgraph(c);
	case CCT::Unknown: {
		// Recursively checks that char is not of any other type
		for (const Char_class& cc : char_classes()) {
			if (char_is_type(c, cc.type, true)) {
				return false;
			}
		}
		return true;
	}
	default:
		break;
	}
	return false;
}

void chcl::print_detailed_summary(std::ostream& os,
                                  const std::vector<Char_class_count>& count)
{
	int max = 0;
	std::vector<Char_class_count> ordered;
	int idx = 0;
	for (const Char_class_count& c : count) {
		if (idx == idx_total()) {
			break;
		}
		max = (max < c.count) ? c.count : max;
		if (c.count > 0) {
			ordered.push_back(c);
		}
		++idx;
	}
	order_count(ordered);

	std::ostringstream longest_num;
	longest_num << max;
	int max_len = longest_num.str().size();
	for (const Char_class_count& c : ordered) {
		std::string name
		    = (c.char_class.type == Char_class_type::Unknown)
		          ? name_na()
		          : char_classes().at(static_cast<int>(c.char_class.type)).name;
		os << std::setw(char_class_name_max_len() + 1) << name << ':'
		   << std::setw(max_len + 1) << c.count << '\n';
	}
}

void chcl::order_count(std::vector<Char_class_count>& ordered)
{
	// The most simple, sucky sort, TODO: replace with something proper
	if (ordered.size() < 2) {
		return;
	}
	for (bool all_in_order = false; !all_in_order;) {
		all_in_order = true; // Assumes count is already sorted
		for (int i = 0; i < ordered.size() - 1; ++i) {
			int j = 0;
			while (ordered[i].count > ordered[i + 1].count) {
				if (j > ordered.size() - i) {
					break;
				}

				// Rotate values
				all_in_order = false;
				Char_class_count temp = ordered[i];
				for (int k = i; k < ordered.size() - 1; ++k) {
					ordered[k] = ordered[k + 1];
				}
				ordered.back() = temp;
				++j;
			}
		}
	}
}

void chcl::print_overview(std::ostream& os,
                          const std::vector<Char_class_count>& count)
{
	int total = count[idx_total()].count;
	if (total == 0) {
		std::cout << "No characters registered" << '\n';
		return;
	}

	std::cout << total << " characters in total." << '\n' << '\n';

	int idx_wspace = static_cast<int>(Char_class_type::Whitespace);
	std::string bar_wspace{str_for_bar_chart(char_classes()[idx_wspace].name,
	                                         count[idx_wspace].count,
	                                         total,
	                                         true)};
	int idx_letters = static_cast<int>(Char_class_type::Letter);
	std::string bar_letters{str_for_bar_chart(char_classes()[idx_letters].name,
	                                          count[idx_letters].count,
	                                          total,
	                                          true)};
	int idx_digits = static_cast<int>(Char_class_type::Digit_dec);
	std::string bar_digits{str_for_bar_chart(char_classes()[idx_digits].name,
	                                         count[idx_digits].count,
	                                         total,
	                                         true)};
	int idx_punct = static_cast<int>(Char_class_type::Punctuation);
	std::string bar_punct{str_for_bar_chart(char_classes()[idx_punct].name,
	                                        count[idx_punct].count,
	                                        total,
	                                        true)};
	int idx_ctrl = static_cast<int>(Char_class_type::Control_character);
	std::string bar_ctrl{str_for_bar_chart(char_classes()[idx_ctrl].name,
	                                       count[idx_ctrl].count,
	                                       total,
	                                       true)};
	int na = count[idx_na()].count;
	std::string bar_na{str_for_bar_chart(name_na(), na, total, true)};
	std::vector<std::string> bars;
	bars.push_back(bar_wspace);
	bars.push_back(bar_letters);
	bars.push_back(bar_digits);
	bars.push_back(bar_punct);
	bars.push_back(bar_ctrl);
	bars.push_back(bar_na);

	for (const std::string& s : bars) {
		if (s.size() > 0) {
			os << s << '\n';
		}
	}
}

std::string chcl::str_for_bar_chart(const std::string& label,
                                    int count,
                                    int total,
                                    bool skip_if_zero)
{
	if (skip_if_zero && (count == 0 || total == 0)) {
		return "";
	}
	double p = (static_cast<double>(count) / total);
	int u = static_cast<int>(p * draw::bar_max);

	std::ostringstream bar;
	bar << std::setw(char_class_name_max_len() + 1) << label << ": ";
	if (u <= 1) {
		bar << draw::bar_r;
	} else if (u <= 2) {
		bar << draw::bar_l << draw::bar_r;
	} else {
		bar << draw::bar_l;
		for (int i = 0; i < u - 2; ++i) {
			bar << draw::bar_m;
		}
		bar << draw::bar_r;
	}
	bar << ' ' << count << " (";
	if (p < 0.01) {
		bar << "< 1%";
	} else {
		bar << std::fixed << std::setprecision(1) << (p * 100) << '%';
	}

	bar << ')';
	return bar.str();
}
