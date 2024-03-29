#include "dstr.h"
#include <iomanip>
#include <vector>

void dstr::Dict_stream::fill_buffer()
{
	while (!buf_full) {
		if (!src || buf.bad()) {
			return;
		}

		if (buf.fail() || buf.eof()) {
			buf.clear();
		}

		// Extracts a chunk of characters from istream,
		// until the next whitespace or when the max is reached,
		// sets "quote mode" when double quote is found,
		// if not in quote mode: replaces banned characters with spaces,
		//                       converts to lowercase
		char c{};
		std::string chunk_str;
		for (int count = 0; src && count < max_chunk; ++count) {
			if (count == 0) {
				src >> c; // strip leading whitespace
			} else {
				src.get(c);
				if (src.eof()) {
					src.clear(std::ios_base::goodbit);
					break;
				}
				if (help::isspace(c)) {
					break;
				}
			}
			if (c == '"') {
				quote_mode = !quote_mode;
				buf.str(chunk_str + " \"");
				buf_full = true;
				return;
			}
			if (!quote_mode) {
				if (is_banned(c)) {
					c = ' ';
				} else {
					c = tolower(c);
				}
			}
			chunk_str.push_back(c);
		}

		std::stringstream chunk{chunk_str};

		// Chunk now contains word(s)
		std::string word;
		std::vector<std::string> words;
		while (chunk >> word) {
			if (quote_mode) {
				words.push_back(word);
				continue;
			}
			if (strip_and_find_single_quotes(word)) {
				std::vector<std::string> w_and_c{
				    extract_words_and_contractions(word, contr, contr_min_len)};

				for (const std::string& w : w_and_c) {
					words.push_back(w);
				}
			} else {
				words.push_back(word);
			}
		}

		std::string words_str;
		for (int i = 0; i < words.size(); ++i) {
			if (!words[i].size()) {
				continue;
			}
			words_str += ((words_str.size()) ? " " : "") + words[i];
		}

		if (!(buf_full = words_str.size())) {
			continue;
		}

		buf.str(words_str);
	}
}

bool dstr::Dict_stream::is_banned(char c)
{
	return (c != '\'' && !help::isalnum(c));
}

dstr::Dict_stream& dstr::Dict_stream::operator>>(std::string& s)
{
	fill_buffer();
	buf >> s;
	buf_full = !buf.eof();
	return *this;
}

//------------------------------------------------------------------------------
bool dstr::valid_ch_type(const std::string& s,
                         int pos,
                         Char_type t,
                         char leading_ch)
{
	if (s.size() == 0) {
		return false;
	}
	if (t == Char_type::None) {
		return true;
	}
	if (t == Char_type::Whitespace) {
		return ((pos < 0 || pos > s.size() - 1)
		        || (help::isspace(s[pos]) || s[pos] == '\''));
	}
	if (t == Char_type::Letter) {
		if (pos == -1) {
			return help::isalpha(leading_ch);
		}
		return (pos >= 0 && pos <= s.size() - 1 && help::isalpha(s[pos]));
	}
	return false;
}

bool dstr::strip_and_find_single_quotes(std::string& s)
/*  Strips string from leading and trailing single quotes,
 *  returns true if the remaining characters contain single quotes */
{
	if (s.size() == 0) {
		return false;
	}

	int first_non_q = -1;
	int latest_q = -1;
	int last_non_q = -1;
	bool has_mid_q = false;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] != '\'') {
			if (first_non_q == -1) {
				first_non_q = i;
			} else if (!has_mid_q && latest_q > first_non_q) {
				has_mid_q = true;
			}
			last_non_q = i;
		} else {
			latest_q = i;
		}
	}

	if (first_non_q == -1 && last_non_q == -1) {
		s = "";
	} else if (first_non_q > 0 || last_non_q < s.size() - 1) {
		std::string new_s;
		for (int j = first_non_q; j <= last_non_q; ++j) {
			new_s.push_back(s[j]);
		}
		s = new_s;
	}

	return has_mid_q;
}

std::vector<std::string> dstr::extract_words_and_contractions(
    const std::string& str,
    const std::vector<Contraction>& contractions,
    int min_len)
{
	std::vector<std::string> words{str};
	int i = 0; // Sometimes skips ahead
	for (; i < words.size(); ++i) {
		int len = words[i].size();
		if (len < min_len) {
			words[i] = repl_ch(words[i], "'");
			continue;
		}

		// Find the First Occuring Match, if any
		int fom_pos = -1;
		int fom_idx = -1;
		bool found_fom = false;
		for (int c = 0; c < contractions.size(); ++c) {
			if (found_fom) {
				break;
			}
			const Contraction& con = contractions[c];
			int offs = 0;
			while (offs < len - 1) {
				int pos = str_pos_in_str(con.search_for, words[i], offs);
				if (pos == -1) {
					break;
				}

				int pos_ld = pos - 1;
				int pos_tr = pos + con.search_for.size();
				char c_ld = (i > 0) ? words[i - 1].back() : ' ';

				bool lead = valid_ch_type(words[i],
				                          pos_ld,
				                          con.required_leading,
				                          c_ld);
				bool trail = valid_ch_type(words[i],
				                           pos_tr,
				                           con.required_trailing);
				if (!lead || !trail) {
					offs = pos + 1;
					continue;
				}

				if (fom_pos == -1 || pos < fom_pos) {
					fom_pos = pos;
					fom_idx = c;
					if (pos == 0) {
						found_fom = true;
					}
				}
				break;
			}
		}

		if (fom_pos == -1) {
			words[i] = repl_ch(words[i], "'");
			continue;
		}

		// Insert word(s) into vector
		const Contraction& fom = contractions[fom_idx];
		int fom_end = fom_pos + fom.search_for.size() - 1;
		split_repl_str_in_v(words, i, fom_pos, fom_end, fom.replace_with);

		if (fom_pos > 0) {
			words[i] = repl_ch(words[i], "'");
			++i; // skip leading
		}
		if ((fom_end < len - 1) && (len - fom_end - 1) < min_len) {
			int tr_idx = (fom_pos > 0 ? 2 : 1);
			words[tr_idx] = repl_ch(words[tr_idx], "'");
			++i; // skip trailing
		}
	}
	return words;
}

int dstr::str_pos_in_str(const std::string& s_for,
                         const std::string& s_in,
                         int start,
                         int end)
{
	// Note that start < 0 or end < 0 will set those arguments to string bounds
	if (start < 0) {
		start = 0;
	}
	if (end < 0 || end > s_in.size() - 1) {
		end = s_in.size() - 1;
	}
	if (start > s_in.size() - 1 || end < start) {
		return -1;
	}

	for (int i = start; i <= end; ++i) {
		if (s_for.size() > (end - start + 1)) {
			break;
		}
		bool found = true;
		for (int j = 0; j < s_for.size(); ++j) {
			if (s_for[j] != s_in[j + i]) {
				found = false;
				break;
			}
		}
		if (found) {
			return i;
		}
	}
	return -1;
}

void dstr::split_repl_str_in_v(std::vector<std::string>& v,
                               const int v_idx,
                               const int str_start,
                               const int str_end,
                               const std::string new_str)
{
	// No bounds checking or anything
	if (str_start == 0 && str_end == v[v_idx].size() - 1) {
		v[v_idx] = new_str;
		return;
	}

	const int cut_l = (str_start > 0) * str_start;
	const int cut_r = (str_end < v[v_idx].size() - 1)
	                  * (v[v_idx].size() - 1 - str_end);
	const std::string old_str{v[v_idx]};
	bool last_in_v = (v_idx == v.size() - 1);

	// Allocate slots, move any pre-existing values to the right
	for (int i = 0; i < ((cut_l > 0) + (cut_r > 0)); ++i) {
		v.push_back(v.back());
		if (!last_in_v) {
			std::string temp_prev = v[v_idx + i];
			for (int n = v_idx + i + 1; n < v.size() - 1; ++n) {
				std::string temp_next{v[n + 1]};
				v[n] = temp_prev;
				temp_prev = temp_next;
			}
		}
	}

	// Insert replaced value
	v[v_idx + (cut_l ? 1 : 0)] = new_str;

	// Insert cut off characters - Left
	if (cut_l) {
		v[v_idx] = "";
		for (int j = 0; j < cut_l; ++j) {
			v[v_idx].push_back(old_str[j]);
		}
	}

	// Insert cut off characters - Right
	if (cut_r) {
		int offs = (cut_l) ? 2 : 1;
		v[v_idx + offs] = "";
		for (int j = 0; j < cut_r; ++j) {
			v[v_idx + offs].push_back(old_str[str_end + 1 + j]);
		}
	}
}

std::string dstr::repl_ch(const std::string& s,
                          const std::string& banned_chars,
                          const char replacement)
{
	if (banned_chars.size() == 0) {
		return s;
	}
	std::string new_s = s;
	for (char& c : new_s) {
		bool found = false;
		for (const char b : banned_chars) {
			if (c == b) {
				found = true;
				break;
			}
		}
		if (found) {
			c = replacement;
		}
	}
	return new_s;
}
