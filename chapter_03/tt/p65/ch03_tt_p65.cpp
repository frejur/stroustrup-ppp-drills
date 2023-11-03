#include "../../lib/std_lib_facilities.h"

int main()
{
	std::cout << "Please enter your first and last name\n>";
	std::string first, last;
	std::cin >> first >> last;
	std::cout << "Hi there, " << first << " " << last << "! How old are you?\n>";
	float age = 0;
	std::cin >> age;
	std::cout << age << " eh? That's " << age * 12 << " months!\n";
	keep_window_open();
	return 0;
}
