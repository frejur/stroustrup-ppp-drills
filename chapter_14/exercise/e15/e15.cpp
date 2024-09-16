#include <iostream>
#include <stdexcept>
#include <vector>

// Exercise 15
// Define class 'Iterator', containing pure virtual function 'double* next()'.
// From the above, derive 'Vector_iterator' and 'List_iterator':
// - Initialize with a reference to either a vector<double> or list<double>.
// - next() initially returns a pointer to the 1st element of the vector / list.
// - next() then returns a pointer to the next element of the vector / list.
// - next() return 0 if there is no (next) element.
//
// Test both subclasses using function print(Iterator&) to print the elements
// of a vector<double> and a vector<list>.
//------------------------------------------------------------------------------

void e15()
{
	std::cout << "Hello, world!" << '\n';
}

int main() {
	try {
		e15();
		std::cout << '\n' << "Press <ENTER> to exit" << '\n';
		std::cin.get();

		return 0;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
