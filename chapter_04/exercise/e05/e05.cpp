#include "../../lib/std_lib_facilities.h"

// Exercise 5, Very simple calculator.
// - Prompt for two floating point operands followed by an operator.
// - Operators: <double>
// - Operator: <char> '+', '-', '*', '/'
// Basically: Rewrite Exercise 10 from Chapter 3 using a switch statement.

int main()
{
	std::cout << "Simple Calculator" << '\n'
		<< "Please enter the two numbers you want to use as operands "
		<< "followed by an operator (+, -, *, /)."
		<< '\n';

	char op { ' ' };
	double num_01{ 0 };
	double num_02{ 0 };
	while (true) {
		std::cin >> num_01 >> num_02 >> op;
		if (std::cin.fail()) {
			break;
		}

		std::string op_str{ "" };
		double result{ 0 };
		switch (op) {
		case '+':
			op_str = " + ";
			result = num_01 + num_02;
			break;
		case '-':
			op_str = " - ";
			result = num_01 - num_02;
			break;
		case '*':
			op_str = " * ";
			result = num_01 * num_02;
			break;
		case '/':
			op_str = " / ";
			if (num_02 == 0) {
				result = 0;
			} else {
				result = num_01 / num_02;
			}
			break;
		default:
			std::cout << "Invalid operand: '" << op << "', please try again"
				<< '\n';
			continue;
			break;
		}
		std::cout << num_01 << op_str << num_02 << " = " << result << '\n';
	}

	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
