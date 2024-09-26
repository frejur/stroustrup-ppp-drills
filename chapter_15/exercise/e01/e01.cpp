#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Chapter 15, Exercise 1: Recursive factorial.
// Compare the results of functions that calculate the factorial:
// - iterative::fac(n)
// - recursive::fac(n)
// Range: 0 <= n <= 20

constexpr int col_sz_n{10};
constexpr int col_sz_val{16};
//------------------------------------------------------------------------------

void wait_for_enter(const std::string action = "proceed")
{
	std::cout << "Press <ENTER> to " << action << '\n';
	std::string dummy;
	std::getline(std::cin, dummy);
}
//------------------------------------------------------------------------------

namespace iterative {
int fac(int n)
{
	int r = 1;
	while (n > 1) {
		r *= n;
		--n;
	}
	return r;
}
} // namespace iterative

namespace recursive {
int fac(int n)
{
	return n > 1 ? n * fac(n - 1) : 1;
}
} // namespace recursive
//------------------------------------------------------------------------------

int main() {
	try {
		std::cout << "Recursive vs. Iterative factorial" << '\n';
		wait_for_enter();
		std::cout << std::left;
		std::cout << std::setw(col_sz_n) << "" << std::setw(col_sz_val)
		          << "Recursive" << std::setw(col_sz_val) << "Iterative"
		          << '\n';
		std::cout << std::setfill('-') << std::setw(col_sz_n + col_sz_val * 2)
		          << "" << '\n'
		          << std::setfill(' ');
		std::ostringstream os;
		for (int n = 0; n <= 20; ++n) {
			os << "n == " << n;
			std::cout << std::setw(col_sz_n) << os.str()
			          << std::setw(col_sz_val) << recursive::fac(n)
			          << std::setw(col_sz_val) << iterative::fac(n) << '\n';
			os.str({});
		}
		wait_for_enter("quit");
		std::cout << "Bye!" << '\n';
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
