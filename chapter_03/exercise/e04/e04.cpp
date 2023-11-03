#include "../../lib/std_lib_facilities.h"

//	Exercise 4 and 5
//	Promt the user for two numbers
//		1. Store them as integers.
//		2. Store them as double's
//	Output:
//		- The smaller number.
//		- The greater.
//		- The sum.
//		- The difference.
//		- The product.
//		- The ratio.
//	Compare the result for int vs double.

int main()
{
	std::cout <<
		"Please enter two numbers."
		<< '\n';

	int val01_int{ 0 };
	int val02_int{ 0 };
	double val01_dec{ 0 };
	double val02_dec{ 0 };

	std::cin >> val01_dec >> val02_dec;
	val01_int = val01_dec;
	val02_int = val02_dec;

	int smaller_int { val01_int };
	int greater_int { val02_int };
	if (smaller_int > greater_int) {
		smaller_int = greater_int;
		greater_int = val01_int;
	}
	double smaller_dec { val01_dec };
	double greater_dec { val02_dec };
	if (smaller_dec > greater_dec) {
		smaller_dec = greater_dec;
		greater_dec = val01_dec;
	}
	std::cout << "Size comparison:" << '\n';
	std::cout << "  INT: " << smaller_int << " is smaller than "
		<< greater_int << '\n';
	std::cout << "  DEC: " << smaller_dec << " is smaller than "
		<< greater_dec << '\n';

	std::cout << "Sum:" << '\n';
	std::cout << "  INT: " << val01_int << " + " << val02_int << " = "
		<< val01_int + val02_int << '\n';
	std::cout << "  DEC: " << val01_dec << " + " << val02_dec << " = "
		<< val01_dec + val02_dec << '\n';

	std::cout << "Difference:" << '\n';
	std::cout << "  INT: " << greater_int << " - " << smaller_int << " = "
		<< greater_int - smaller_int << '\n';
	std::cout << "  DEC: " << greater_dec << " - " << smaller_dec << " = "
		<< greater_dec - smaller_dec << '\n';

	std::cout << "Product:" << '\n';
	std::cout << "  INT: " << val01_int << " * " << val02_int << " = "
		<< val01_int * val02_int << '\n';
	std::cout << "  DEC: " << val01_dec << " * " << val02_dec << " = "
		<< val01_dec * val02_dec << '\n';

	std::cout << "Ratio:" << '\n';
	std::cout << "  INT: " << greater_int << " / " << smaller_int << " = "
		<< ((val01_int == 0 || val02_int == 0) ? 0 : (greater_int / smaller_int))
		<< '\n';
	std::cout << "  DEC: " << greater_dec << " / " << smaller_dec << " = "
		<< ((val01_dec == 0 || val02_dec == 0) ? 0 : (greater_dec / smaller_dec))
		<< '\n';

	keep_window_open();

    return 0;
}
