#include "help.h"

void help::clear_buffer(std::istream& is)
{
	for (char temp{}; is.get(temp) && temp != '\n';) { /* Repeat until newline */
	}
}

void help::wait_for_enter()
{
	if (!std::cin) {
		if (std::cin.bad()) {
			throw std::runtime_error("Input stream in a bad state");
		}
		std::cin.ignore();
	}
	char ch = 0;
	std::cin.get(ch);
	if (ch != '\n') {
		clear_buffer(std::cin);
	}
}
