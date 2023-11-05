#include <iostream>
#include "../../lib/std_lib_facilities.h"

namespace X {
    int var;
    void print() { std::cout << "X: " << var << '\n'; }
}

namespace Y {
    int var;
    void print() { std::cout << "Y: " << var << '\n'; }
}

namespace Z {
    int var;
    void print() { std::cout << "Z: " << var << '\n'; }
}

int main()
{
	X::var = 7;
	std::cout << "Expecting X -> ";
	X::print();            // print X’s var
	using namespace Y;
	var = 9;
	std::cout << "Expecting Y -> ";
	print();               // print Y’s var
	{
		using Z::var;
		using Z::print;
		var = 11;
		std::cout << "Expecting Z -> ";
		print();           // print Z’s var
	}
	std::cout << "Expecting Y -> ";
	print();               // print Y’s var
	std::cout << "Expecting X -> ";
	X::print();            // print X’s var

	keep_window_open();

	return 0;
}
