#include <iostream>
#include "../../lib/std_lib_facilities.h"

// Pass-by-value
// Copies values of argument variables but those variables remain unchanged
void swap_v(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

// Pass-by-reference
// Operates directly on the variables passed as arguments
void swap_r(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

/*  Pass-by-const-reference
Will not compile. Initialized constant may only be read, not modified

void swap_cr(const int &x, const int &y)
{
	int temp = x;
	x = y;
	y = temp;
} */

int main()
{
	int x = 7;
	int y = 9;

	std::cout << "== Integers x=" << x << ", y=" << y << '\n';

	std::cout << "Pass-by-value\n";
	std::cout << "Pre: x=" << x << " y=" << y << '\n';
	swap_v (x, y); // Valid, nothing happens to argument vars
	std::cout << "Post: x=" << x << " y=" << y << '\n';

	swap_v(7, 9); // Valid, nothing happens

	std::cout << '\n';

	std::cout << "Pass-by-reference\n";
	std::cout << "Pre: x=" << x << " y=" << y << '\n';
	swap_r(x, y);
	std::cout << "Post: x=" << x << " y=" << y << '\n';

	//swap_r(7, 9); // cannot convert from int to int &
					// cannot create a reference to a literal
					// needs to be an lval

	const int cx = 7;
	const int cy = 9;

	std::cout << '\n';
	std::cout << "== Constant integers cx=" << cx << ", cy=" << cy << '\n';

	std::cout << "Pass-by-value\n";
	std::cout << "Pre: cx=" << cx << " cy=" << cy << '\n';
	swap_v (cx, cy); // Valid, nothing happens to argument vars
	std::cout << "Post: cx=" << cx << " cy=" << cy << '\n';

	swap_v(7.7, 9.9); // Valid, nothing happens

	//swap_r(cx, cy); // cannot convert from const int to int&
	//swap_r(7.7, 9.9); // cannot create a reference to a literal

	double dx = 7.7;
	double dy = 9.9;

	std::cout << '\n';
	std::cout << "== Floating point variables dx=" << dx << ", dy=" << dy << '\n';

	std::cout << "Pass-by-value\n";
	std::cout << "Pre: dx=" << dx << " dy=" << dy << '\n';
	swap_v (dx, dy);
	swap_v (7.7, 9.9);
	std::cout << "Post: dx=" << dx << " dy=" << dy << '\n';

	//swap_r(dx, dy); // // cannot convert from double to int&
	//swap_r(7.7, 9.9); // cannot create a reference to a literal

	keep_window_open();

	return 0;
}
