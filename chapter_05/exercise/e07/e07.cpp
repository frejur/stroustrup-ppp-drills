#include "../../lib/std_lib_facilities.h"

// Exercise 7. Write a program to solve quadratic equations

// Basically, just modify Chapter 4 Exercise 18 to throw an error when the
// equation has a complex solution.

// There once was a negative boy who couldn't decide if he should stay at this
// radical party. He was such a square he missed out on four awesome chicks
// when he just got up and split at 2 AM.

double get_discriminant(double a, double b, double c) {
	return b * b - 4 * a * c;
}

vector<std::string> solve_quadratic(double a, double b, double c) {
	double d{ get_discriminant(a, b, c) };
	vector<std::string> x_v{};
	if (d >=0) {
		x_v.push_back(std::to_string(
			(-b + sqrt(d)) / (2 * a)
		));
		if (d !=0) {
			x_v.push_back(std::to_string(
				(-b - sqrt(d)) / (2 * a)
			));
		}
		return x_v;
	}
	// Complex solution
	error("The equation has no real roots");
//	std::string neg_b_div_2_a{ std::to_string(-b / (2 * a)) };
//	std::string d_sq_div_2_a{ std::to_string(sqrt(d * -1) / (2 * a)) };
//	x_v.push_back(neg_b_div_2_a + " + " + d_sq_div_2_a + "i");
//	x_v.push_back(neg_b_div_2_a + " - " + d_sq_div_2_a + "i");
//	return x_v;
}

void restore_buffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//------------------------------------------------------------------------------
int main()
try {
	std::cout << "Solving a quadratic equation" << '\n'
		<< "ax^2 + bx + c = 0" << '\t' << "Solve for x." << '\n';

	double a{ 0 };
	double b{}, c{};
	bool b_is_set{ false }, c_is_set{ false };
	while (a == 0 || !b_is_set || !c_is_set) {
		std::cout <<
			((a == 0) ? "What is the value of 'a'?"
						: "a = " + std::to_string(a))
			<< '\n';
		while (a == 0 && std::cin >> a) {
			if (a == 0) {
				std::cout << "'a' cannot be zero" << '\n';
				continue;
			}
		}
		if (a == 0) {
			std::cout << "Invalid value for 'a'" << '\n';
			restore_buffer();
		}
		std::cout <<
			((!b_is_set) ? "What is the value of 'b'?"
						: "b = " + std::to_string(b))
			<< '\n';
		while (!b_is_set && std::cin >> b) {
			b_is_set = true;
		}
		if (!b_is_set) {
			std::cout << "Invalid value for 'b'" << '\n';
			restore_buffer();
		}
		std::cout <<
			((!c_is_set) ? "What is the value of 'c'?"
						: "c = " + std::to_string(c))
			<< '\n';
		while (!c_is_set && std::cin >> c) {
			c_is_set = true;
		}
		if (!c_is_set) {
			std::cout << "Invalid value for 'c'" << '\n';
			restore_buffer();
		}
	}

	std::cout << "Let's solve for x in the following equation: " << '\t'
		<< a << " * x ^ 2 + " << b << " * x + " << c << " = 0" << '\n';

	vector<std::string> x_v{ solve_quadratic(a, b, c) };
	std::cout
		<< ((x_v.size() == 1) ? "x" : "x1")	<< " = " << x_v.front() << '\n';
	if (x_v.size() > 1) {
		std::cout << "x2 = " << x_v.back() << '\n';
	}

	keep_window_open();

	return 0;
}
catch (std::exception &e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
