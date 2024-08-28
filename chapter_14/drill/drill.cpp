#include <system_error>
#include <iostream>
#include "drill.h"

void drill_1_to_3()
{
	// Drill 1
	d_1_3::B1 b1;
	b1.f();
	b1.vf();

	// Drill 2
	d_1_3::D1 d1;
	d1.f();
	d1.vf();

	// Drill 3
	d_1_3::B1& b1_ref{d1};
	b1_ref.f();
	b1_ref.vf();
}

void drill_4()
{
	// Drill 1
	d_4::B1 b1;
	b1.f();
	b1.vf();

	// Drill 2
	d_4::D1 d1;
	d1.f(); /* Outputs "D1::f()". Because it's not an overriden virtual function,
	           the 'f()' function defined in D1 hides the function defined in B1. */
	d1.vf();

	// Drill 3
	d_4::B1& b1_ref{d1};
	b1_ref.f(); // Outputs "B1::f()", though one might expect "D1::f()", see above.
	b1_ref.vf();
}

void drill_5()
{
	/*
	// Drill 1
	d_5::B1 b1;
	b1.f();
	b1.vf();

	// Drill 2
	d_5::D1 d1;
	d1.f();
	d1.vf();

	// Drill 3
	d_5::B1& b1_ref{d1};
	b1_ref.f();
	b1_ref.vf();
	*/

	std::cout << "Does not compile: cannot instantiate abstract class" << '\n';
}

void drill_6()
{
	d_6::D2 d2;
	d2.f();
	d2.vf();
	d2.pvf();
}

void drill_7()
{
	d_7::D21 d21;
	d_7::D22 d22;
	d_7::f(d21);
	d_7::f(d22);
}

int main()
{
	try {
		std::cout << "Drill 1 to 3:" << '\n';
		drill_1_to_3();
		std::cout << '\n';

		std::cout << "Drill 4:" << '\n';
		drill_4();
		std::cout << '\n';

		std::cout << "Drill 5:" << '\n';
		drill_5();
		std::cout << '\n';

		std::cout << "Drill 6:" << '\n';
		drill_6();
		std::cout << '\n';

		std::cout << "Drill 7:" << '\n';
		drill_7();

		std::cout << '\n' << "Press <ENTER> to exit" << '\n';

		std::cin.get();
		return 0;
	} catch (std::exception& e) {
		return 1;
	} catch (...) {
		return 2;
	}
}
