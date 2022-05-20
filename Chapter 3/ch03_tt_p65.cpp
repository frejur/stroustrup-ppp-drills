#include "std_lib_facilities.h"

namespace ch03_tt_p65
{
	int main()
	{
		cout << "Please enter your first and last name\n>";
		string first, last;
		cin >> first >> last;
		cout << "Hi there, " << first << " " << last << "! How old are you?\n>";
        float age = 0;
        cin >> age;
		cout << age << " eh? That's " << age * 12 << " months!\n";
		return 0;
	}
}