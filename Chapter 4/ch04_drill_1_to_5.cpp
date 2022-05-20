#include "std_lib_facilities.h"

namespace ch04_drill_1_to_5
{
	int main()
	{
		const string exit_symbol{ '|' };	// Character the user can input to terminate the program
		string a ="", b="";					// Store the input in two strings
		double num_a, num_b;					// Convert above strings to numbers
		double smaller, larger;				// One number is smaller or equal than the other
		constexpr float min_diff{ 0.01 };	// Minimum difference between numbers to qualify as almost equal

		string txt_smaller = "The smaller value is: ";
		string txt_larger = "The larger value is: ";
		string txt_equal = "The numbers are equal.";
		string txt_almost = "The numbers are ALMOST equal.";

		bool graceful = false;	// Graceful exit flag, triggered by the exit symbol
		bool evaluate = true;	// Only evaluate expression when this flag is true

		while (cin >> a >> b) {
			string end_char;
			end_char += b.back();
			if (a == exit_symbol || b == exit_symbol) {
				graceful = true;
				evaluate = false;
			} else if (end_char == exit_symbol) {
				if (b.size() > 1)  b.resize(b.size() - 1);
				graceful = true;
			}
			if (evaluate) {
				try {
					num_a = stod(a);
					num_b = stod(b);
				}
				catch (...) {
					cout << "Invalid input, ";
					break;
				}
				cout << num_a << '\t' << num_b << '\n';
				if (fabs(num_a - num_b) <= min_diff) {
					if (num_a == num_b) cout << txt_equal << '\n';
					else cout << txt_almost << '\n';
				} else {
					if (num_a > num_b) {
						smaller = num_b;
						larger = num_a;
					}
					else {
						smaller = num_a;
						larger = num_b;
					}
					cout << txt_smaller << smaller << '\t' << txt_larger << larger << '\n';
				}
			}
			if (graceful) {
				cout << "Graceful ";
				break;
			}
		}
		cout << "Goodbye!\n";
		return 0;
	}
}