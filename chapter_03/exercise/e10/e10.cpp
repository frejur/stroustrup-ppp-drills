#include "../../lib/std_lib_facilities.h"
#include <string>

//	Exercise 10.
//	Prompt for an operator (char) followed by two operands (double's).
//	Valid operators: Addition, substraction, multiplication, division.
//	Output the result.

int main()
{
	std::cout <<
		"Please enter an operator (+, -, *, /) and the two numbers you want to"
		<< " apply the operation to."
		<< '\n';

	char op { ' ' };
	double num_01{ 0 };
	double num_02{ 0 };
	while (true) {
		std::cin >> op >> num_01 >> num_02;
		if (std::cin.fail()) {
			break;
		}

		std::string op_str{ "" };
		double result{ 0 };
		if (op == '+') {
			op_str = " + ";
			result = num_01 + num_02;
		} else if (op == '-') {
			op_str = " - ";
			result = num_01 - num_02;
		} else if (op == '*') {
			op_str = " * ";
			result = num_01 * num_02;
		} else if (op == '/') {
			op_str = " / ";
			if (num_02 == 0) {
				result = 0;
			} else {
				result = num_01 / num_02;
			}
		} else {
			std::cout << "Invalid operand: '" << op << "', please try again"
				<< '\n';
			continue;
		}
		std::cout << num_01 << op_str << num_02 << " = " << result << '\n';
	}

	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
