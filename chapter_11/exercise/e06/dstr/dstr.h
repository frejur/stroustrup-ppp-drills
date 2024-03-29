#ifndef DSTR_H
#define DSTR_H
#include "../../../lib/help.h"
#include <istream>
#include <sstream>
#include <vector>

namespace dstr{

//------------------------------------------------------------------------------

enum class Char_type { None, Whitespace, Letter };

struct Contraction
{
	Char_type required_leading;
	Char_type required_trailing;
	std::string search_for;
	std::string replace_with;
};

//------------------------------------------------------------------------------

constexpr int max_chunk{128}; // Currently words longer than this get chopped up

class Dict_stream {
public:
	Dict_stream(std::istream& is)
	    : src(is)
	    , buf_full(false)
	    , quote_mode(false)
	    , count_w(0){};
	operator bool() { return good(); };
	Dict_stream& operator>>(std::string& s);
	void add_contraction(Contraction c)
	{
		if (contr.size() == 0 || c.search_for.size() < contr_min_len) {
			contr_min_len = c.search_for.size();
		}
		contr.push_back(c);
	};
	void clear()
	{
		buf.clear();
		src.clear();
	}
	void reset_quote_mode() { quote_mode = false; };

private:
	void fill_buffer();
	std::istream& src;
	std::stringstream buf;
	bool buf_full;
	bool quote_mode;
	int count_w;
	bool good() { return buf_full || src.good(); };
	bool is_banned(char c);
	std::vector<Contraction> contr;
	int contr_min_len = 0;
};

//------------------------------------------------------------------------------

bool valid_ch_type(const std::string& s,
                   int pos,
                   Char_type t,
                   char leading_ch = ' ');
bool strip_and_find_single_quotes(std::string& s);
std::vector<std::string> extract_words_and_contractions(
    const std::string& s,
    const std::vector<Contraction>& contractions,
    int max_len);
int str_pos_in_str(const std::string& s_for,
                   const std::string& s_in,
                   int start = -1,
                   int end = -1);
void split_repl_str_in_v(std::vector<std::string>& v,
                         const int v_idx,
                         const int str_start,
                         const int str_end,
                         const std::string new_str);
std::string repl_ch(const std::string& s,
                    const std::string& banned_chars,
                    const char replacement = ' ');

} // namespace dstr

#endif // DSTR_H
