#include "test.h"

void test_all()
{
	std::cout << "Running tests for the Monetary Math class" << '\n'
			  << "-----------------------------------------" << '\n';
	test_mmath();

	std::cout << '\n';
	std::cout << "Running tests for the Conversion Table class" << '\n'
			  << "--------------------------------------------" << '\n';
	test_table();

	std::cout << '\n';
	std::cout << "Running tests for the Money class" << '\n'
			  << "---------------------------------" << '\n';
	test_money();

	std::cout << '\n';
	std::cout << "Running tests for arithmetic operators" << '\n'
			  << "--------------------------------------" << '\n';
	test_op_arithm();

	std::cout << '\n';
	std::cout << "Running tests for comparison operators" << '\n'
			  << "--------------------------------------" << '\n';
	test_op_comp();

	std::cout << '\n'
		<< "All tests passed without terminating the program pre-maturely!"
		<< '\n' << '\n';

	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
}
