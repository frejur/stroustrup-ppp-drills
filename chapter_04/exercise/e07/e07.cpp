#include "../../lib/std_lib_facilities.h"

// Exercise 7, Very simple calculator with spelled-out numbers.
// - Prompt for two operands followed by an operator.
// - Operators: <string> spelled-out numbers ranging from 0 to 9.
// - Operator: <char> '+', '-', '*', '/'
// Basically: Combine Exercise 5 and 6

double number_from_string(std::string s)
{
	vector<std::string> spelled_out {
		"zero", "one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine"
	};
	for (int i = 0; i < spelled_out.size(); ++i) {
		if (spelled_out[i] == s) {
			return (double)i;
		}
	}
	return -1;
}

int main()
{
	std::cout << "Simple Calculator" << '\n'
		<< "Please spell out two one digit numbers followed by an operator "
		<<  "(+, -, *, /) you want to use."
		<< '\n';

	char op { ' ' };
	std::string str_01{ "" };
	std::string str_02{ "" };
	double num_01{ 0 };
	double num_02{ 0 };
	while (std::cin >> str_01 >> str_02 >> op) {
		std::string op_str{ "" };
		double result{ 0 };

		num_01 = number_from_string(str_01);
		if (num_01 < 0) {
			std::cout << "Invalid operand: '" << str_01 << "', "
				<< "please try again!" << '\n';
			continue;
		}
		num_02 = number_from_string(str_02);
		if (num_02 < 0) {
			std::cout << "Invalid operand: '" << str_02 << "', "
				<< "please try again!" << '\n';
			continue;
		}

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
			std::cout << "Invalid operator: '" << op << "', please try again!"
				<< '\n';
			continue;
			break;
		}
		std::cout << num_01 << op_str << num_02 << " = " << result << '\n';
	}

	keep_window_open();

    return 0;
}
