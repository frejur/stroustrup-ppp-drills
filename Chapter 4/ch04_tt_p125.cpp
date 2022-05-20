#include "std_lib_facilities.h"

namespace ch04_tt_p125
{
	bool is_banned(string word) {
		const vector<string> banned = { "Broccoli", "Wasabi", "Melania" };
		for (string banned_word : banned) {
			if (word == banned_word) {
				return true;
			}
		}
		return false;
	}

	int main()
	{
		string inp_string = "";
		while (cin >> inp_string) {
		  if ( is_banned(inp_string)) cout << "BEEP!\n";
		  else cout << "I like " << inp_string << '\n';
		}
		return 0;
	}
}