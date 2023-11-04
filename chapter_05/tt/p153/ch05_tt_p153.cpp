#include "../../lib/std_lib_facilities.h"

// To see what an uncaught exception error looks like,
// run a small program that uses error() without
// catching any exceptions.

// calculate area of a rectangle;
int area(int length, int width)
{
	if (length <= 0 || width <= 0)
		throw std::runtime_error("Invalid arguments");
	return length * width;
}

int main()
{
	int x, y, a;
	char c;

	std::cout << "Enter two integer values followed by either 'c' "
		<< "to catch errors, or 'e' to throw errors "
		<< "without catching."
		<< "\n>";

	while (std::cin >> x >> y >> c) {
		switch (c)
		{
		case 'c':
			try { a = area(x, y); }
			catch (std::runtime_error) { } // will throw an error
									  // but 'a' won't be assigned the return value
									  // it will be an uninitialized variable which
									  // can cause major headache
			break;
		case 'e':
			a = area(x, y); // will still throw an error: Unhandled exception at 0x7674A842
							// and 'a' will be assigned the (undesired) return value
			break;
		default:
			continue;
			break;
		}

		std::cout << a << '\n';
	}

	keep_window_open();

	return 0;
}
