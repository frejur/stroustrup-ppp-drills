#include "../../lib/std_lib_facilities.h"

int main()
{
	const std::string exit_symbol{ '|' };	// Character the user can input to terminate the program
	std::string a ="", b="";					// Store the input in two std::strings
	double num_a, num_b;					// Convert above std::strings to numbers
	double smaller, larger;				// One number is smaller or equal than the other
	constexpr float min_diff{ 0.01 };	// Minimum difference between numbers to qualify as almost equal

	std::string txt_smaller = "The smaller value is: ";
	std::string txt_larger = "The larger value is: ";
	std::string txt_equal = "The numbers are equal.";
	std::string txt_almost = "The numbers are ALMOST equal.";

	bool graceful = false;	// Graceful exit flag, triggered by the exit symbol
	bool evaluate = true;	// Only evaluate expression when this flag is true

	std::cout << "Please enter two numbers to compare them. Enter '|' to exit"
		<< '\n';

	while (std::cin >> a >> b) {
		std::string end_char;
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
				std::cout << "Invalid input, ";
				break;
			}
			std::cout << num_a << '\t' << num_b << '\n';
			if (fabs(num_a - num_b) <= min_diff) {
				if (num_a == num_b) std::cout << txt_equal << '\n';
				else std::cout << txt_almost << '\n';
			} else {
				if (num_a > num_b) {
					smaller = num_b;
					larger = num_a;
				}
				else {
					smaller = num_a;
					larger = num_b;
				}
				std::cout << txt_smaller << smaller << '\t' <<
					txt_larger << larger << '\n';
			}
		}
		if (graceful) {
			std::cout << "Graceful ";
			break;
		}
	}
	std::cout << "Goodbye!\n";

	keep_window_open();

	return 0;
}
