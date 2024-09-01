#include "../../lib/Graph.h"
#include <iostream>

// Exercise 2 and 3.
// E2: Try to copy a 'Shape'. (Try to copy a concrete class derived from 'Shape')
// E3: Define an abstract class, try to to initialize it.

//------------------------------------------------------------------------------

class Abstract
{
protected:
	Abstract();
};

class Abstract_pure
{
public:
	virtual void hello() = 0;
};

//------------------------------------------------------------------------------

void e02()
{
	std::cout << "Trying to copy a concrete subclass of 'Shape':" << '\n';
	Graph_lib::Line concrete_class_derived_from_shape{{0, 0}, {1, 0}};
	// Graph_lib::Line copy = concrete_class_derived_from_shape;
	std::cout << '\t' << "Compiler error: Call to implicitly-deleted copy "
	          << '\n'
	          << '\t' << "                constructor of 'Graph_lib::Line'"
	          << '\n';
}

void e03()
{
	std::cout << "Trying to initialize abstract classes..."
	          << "\n\n";

	std::cout << "Initializing a class with a protected constructor:" << '\n';
	// Abstract a{};
	std::cout << '\t' << "Compiler error: Calling a protected constructor"
	          << '\n'
	          << '\t' << "                of class 'Abstract'" << '\n';

	std::cout << '\n';

	std::cout << "Initializing a class with a pure virtual function:" << '\n';
	// Abstract_pure ap{};
	std::cout << '\t' << "Compiler error: Variable type 'Abstract_pure'" << '\n'
	          << '\t' << "                is an abstract class, unimplemented"
	          << '\n'
	          << '\t' << "                pure virtual method 'hello' in "
	          << '\n'
	          << '\t' << "                'Abstract_pure'" << '\n';
}

//------------------------------------------------------------------------------

int main() {
	try {
		e02();
		std::cout << "\n\n";
		e03();

		std::cout << '\n' << "Press <ENTER> to exit" << '\n';
		std::cin.get();

		return 0;
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
