#include "../../lib/std_lib_facilities.h"

bool is_banned(std::string word) {
	const vector<std::string> banned = { "Broccoli", "Wasabi", "Melania" };
	for (std::string banned_word : banned) {
		if (word == banned_word) {
			return true;
		}
	}
	return false;
}

int main()
{
	std::string inp_string = "";
	while (std::cin >> inp_string) {
	  if ( is_banned(inp_string)) std::cout << "BEEP!\n";
	  else std::cout << "I like " << inp_string << '\n';
	}
	keep_window_open();
	return 0;
}
