#include "help.h"

std::string help::extract_ch_from_end(std::string& s, int num_ch, bool copy)
{
	int len = s.size();
	if (num_ch > len) {
		throw std::runtime_error(
		    "Number of characters to extract exceeds length of string");
	}
	std::string remaining;
	std::string extracted;
	for (int i = 0; i < len; ++i) {
		if (i >= len - num_ch) {
			extracted += s[i];
		} else if (!copy) {
			remaining += s[i];
		}
	}
	if (!copy) {
		s = remaining;
	}
	return extracted;
}
