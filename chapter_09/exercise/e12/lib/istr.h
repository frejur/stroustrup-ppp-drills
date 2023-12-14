#ifndef ISTR_H
#define ISTR_H
#include <string>
#include <iostream>

std::string buffer_until_eol() {
	std::string s{ "" };
	char c{};
	while(std::cin.get(c) && c != '\n') {
		s += c;
	}
	return s + c;
}

void clear_buffer() {
	char c{};
	while(std::cin.get(c) && c != '\n') {}
}
void restore_buffer(const std::string& b) {
	for (int i = b.size() - 1; i >= 0; --i) {
		std::cin.putback(b[i]);
	}
}

int count_input_int_vals() {
	std::string s{ buffer_until_eol() };
	if (s.size() == 1) {
		return 0;
	}
	int count{ 0 };
	for (int i = 0; i < s.size() - 1; ++i){
		if (isdigit(s[i])) {
			if (isspace(s[i+1])) {
				++count;
			}
		} else if (!isspace(s[i])) {
			return 0;
		}
	}
	restore_buffer(s);
	return count;
}


bool entered_exit(const std::string& exit) {
	std::string b{ buffer_until_eol() };
	if (b == exit + '\n') {
		return true;
	}
	restore_buffer(b);
	return false;
}

#endif // ISTR_H
