#include "../../lib/Graph.h"
#include <iostream>

// Exercise 2 - 4.
// E2: Try to copy a 'Shape'. (Try to copy a concrete class derived from 'Shape')
// E3: Define an abstract class, try to to initialize it.
// E4: Derive class 'Immobile_circle' from 'Circle' and disable the move() method.

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

class Immobile_circle : public Graph_lib::Circle
{
public:
	Immobile_circle(Graph_lib::Point pos, int radius)
	    : Graph_lib::Circle(pos, radius){};

private:
	void move(int x, int y) override
	{
		throw std::runtime_error(
		    "The move() functionality has been disabled for this subclass");
	};
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

void e04()
{
	// Basically there are three options:
	// 1. Override and make private (If it's a public function)
	// 2. Override it with an empty definition.
	// 3. Throw an exception.

	// Only the first option provides some kind of compile time check but if the
	// function to be disabled is already private you are out of luck.

	// Option 1 can be combined with either option 2 or 3.
	// (The implementation of Immobile_circle featured here uses 1 and 3 )

	// This is fine
	Graph_lib::Circle c{{0, 0}, 200};
	c.move(50, 50);

	// This is not
	Immobile_circle ic{{0, 0}, 200};
	// ic.move(50, 50);

	std::cout << "Trying to call 'Immobile_circle'.move(int x, int y):" << '\n';
	std::cout << '\t' << "Compiler error: 'move' is a private member of" << '\n'
	          << '\t' << "                'Immobile_circle'" << '\n';
}

//------------------------------------------------------------------------------

int main() {
	try {
		e02();
		std::cout << "\n\n";
		e03();
		std::cout << "\n\n";
		e04();

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
