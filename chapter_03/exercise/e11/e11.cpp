#include "../../lib/std_lib_facilities.h"
#include <string>

//	Exercise 11.
//	Prompt the user for a series of values:
//		1. No. of Pennies (1 cent)
//		2. No. of Nickels (5 cent)
//		3. No. of Quarters
//		4. No. of Half-dollars
//		5. No. of One-dollar coins.
//		Output each value as "You have x <coin type>".
//		When ouputting, only pluralize coin type if x != 1.
//		At the end, output the sum as:
//		"The sum of all your coins is $x.x"

int main()
{
	double usd_penny{ 0.01 };
	double usd_nickel{ 0.05 };
	double usd_quarter{ 0.25 };
	double usd_half{ 0.5 };

	std::cout << "Let's count some coins!" << '\n';

	int pennies { 0 };
	std::cout << "How many pennies do you have?" << '\n';
	std::cin >> pennies;
	std::string str_pennies{ (pennies == 1) ? "penny" : "pennies" };

	int nickels { 0 };
	std::cout << "... and how many nickels do you have?" << '\n';
	std::cin >> nickels;
	std::string str_nickels{ (nickels == 1) ? "nickel" : "nickels" };

	int quarters { 0 };
	std::cout << "... quarters?" << '\n';
	std::cin >> quarters;
	std::string str_quarters{ (quarters == 1) ? "quarter" : "quarters" };

	int half { 0 };
	std::cout << "... any half-dollars?" << '\n';
	std::cin >> half;
	std::string str_half{ (half == 1) ? "half-dollar" : "half-dollars" };

	int dollars { 0 };
	std::cout << "... what about one-dollar coins, got any of those?" << '\n';
	std::cin >> dollars;
	std::string str_dollars{
		(dollars == 1) ? "one-dollar coin" : "one-dollar coins" };

	std::string count_str{ "You have " };
	std::cout
		<< count_str << pennies << ' ' << str_pennies << '\n'
		<< count_str << nickels << ' ' << str_nickels << '\n'
		<< count_str << quarters << ' ' << str_quarters << '\n'
		<< count_str << half << ' ' << str_half << '\n'
		<< count_str << dollars << ' ' << str_dollars << '\n';

	std::cout << "The value of all your coins is $"
		<<	pennies * usd_penny + nickels * usd_nickel +
			quarters * usd_quarter + half  * usd_half + dollars
		<< "." << '\n';

	keep_window_open();

    return 0;
}
