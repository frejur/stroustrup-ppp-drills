#include "punct_stream.h"
#include "../../../lib/help.h"

pstr::Punct_stream& pstr::Punct_stream::operator>>(std::string& s)
{
	while (!(buf >> s)) {
		if (buf.bad() || !src.good()) {
			return *this; // give up
		}
		buf.clear();

		std::getline(src, ln_str);
		++ln_num;

		/* copy into string, discard trailing whitespace to ensure the last
		 * extracted word triggers eof() */
		std::string ln_copy;
		for (int i = ln_str.size() - 1; i >= 0; --i) {
			if (help::isspace(ln_str[i]) || is_whitespace(ln_str[i])) {
				if (ln_copy.empty()) {
					continue;
				}
				ln_copy = " " + ln_copy;
			} else {
				if (!sens && help::isalpha(ln_str[i])) {
					ln_copy = (char) tolower(ln_str[i]) + ln_copy;
				} else {
					ln_copy = ln_str[i] + ln_copy;
				}
			}
		}

		buf.str(ln_copy);
	}
	return *this;
}

bool pstr::Punct_stream::is_whitespace(char c) const
{
	for (char ws : ws_chars) {
		if (c == ws) {
			return true;
		}
	}
	return false;
}
