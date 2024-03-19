#include "help.h"
#include <iostream>
#include <stdexcept>

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
	std::string s;
	std::getline(std::cin, s);
}
