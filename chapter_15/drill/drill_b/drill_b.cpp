#include "drill_b.h"
#include <sstream>

// Chapter 15, drill B: Class definitions
//
// 1. Define 'struct Person' with members 'std::string name' and 'int age'.
// 2. Create an instance of Person: named "Goofy", aged 63. Output to console.
// 3. Define stream extraction and insertion operators for 'Person'.
// 4. Use the operators to read in a 'Person' from the console, output the result.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 5. Make members private, add getter functions.
// 6. Update extraction and insertion operators
// 7. Validate the age (range: 0 - 150) and name (Banned chars: ";:";[]*&^%$#@!")
//    parameters in the constructor, throw an exception if invalid.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 8. Read in multiple 'Person's from the console and store them in a vector,
//    output the registered entries and test for erroneous input.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 9. Change the representation of 'Person' to include a 'first_name' and a
//    'second_name' instead of just a 'name'. Throw an exception if any of the
//    name parameters are empty (or if they contain any banned chars). Update
//    the extraction and insertion operators and test.
//------------------------------------------------------------------------------

int main()
try {
	std::string selection;
	do {
		drill::hello();
		std::getline(std::cin, selection);
		if (selection.size() == 1) {
			switch (selection.front()) {
			case 'q':
				std::cout << "Quitting... ";
				break;
			case 'a':
				step_1_to_4::run();
				break;
			case 'b':
				step_5_to_7::run();
				break;
			case 'c':
				step_8::run();
				break;
			case 'd':
				step_9::run();
				break;
			default:
				std::cout << "Invalid char: " << '\n';
				break;
			}
		}
	} while (selection != "q");
	std::cout << "Bye!" << '\n';
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
} catch (...) {
	std::cerr << "Unknown error" << '\n';
}
