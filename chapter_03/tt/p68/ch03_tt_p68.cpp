#include "../../lib/std_lib_facilities.h"

int main()
{
	std::cout << "Please enter two positive integer values: ";
	int n1, n2;
	std::cin >> n1 >> n2;
	std::cout << "n1 = " << n1 << '\n'
		<< "n1 + 1 = " << n1 + 1 << '\n'
		<< "n1 * 2 = " << n1 + n1 << '\n'
		<< "n1 * 3 = " << n1 + n1 + n1 << '\n'
		<< "n1 squared = " << n1 * n1 << '\n'
		<< "n1 / 2 = " << n1 / 2 << '\n'
		<< "square root of n = " << sqrt(float(n1)) << '\n'
		<< "n2 = " << n2 << '\n'
		<< n1 << " / " << n2 << " * " << n2 << " + " << n1 << " % " << n2 << " = "
		<< n1 / n2 * n2 + n1 % n2 << '\n';
	keep_window_open();
	return 0;
}
