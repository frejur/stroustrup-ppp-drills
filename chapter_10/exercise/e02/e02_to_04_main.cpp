#include "e02/e02.h"
#include "e03/e03.h"
#include "share/e02_to_04_shared.h"
#include <exception>
#include <iostream>

/* Chapter 10, Exercise 2 to 4: Temperature readings.
 * 
 * Exercise 2: Output at least 50 temperature readings to a textfile.
 *          3: Read values from text file into a vector,
 *             calculate the mean and median temperatures.
 *          4: Modify the read/write programs from the previous exercises to
 *             include temperature units 'f' and 'c' (Fahrenheit / Celcius).
 *             Convert temperatures into Fahrenheit on read.
 *
 * Differences from the exercises described in the book:
 *   - Allow the user to select which exercise to execute.
 *   - Split exercise 4 into 2 'steps'.
 *   - Generate a random number of readings, generate random hour and
 *     temperature values (Including the assigned unit).
 *   - When generating the data, calculate the mean and median and store the
 *     results in a separate text file.
 *   - In that same results file, also store the number of generated values.
 *   - When calculating the mean and median of the temperature readings
 *     extracted from the data file, cross check with the values stored in the
 *     results file.
 */

int main()
try {
	share::print_hello(std::cout);

	share::Selection s{ share::Selection::Invalid_selection };
	while (s != share::Selection::Quit) {
		share::print_options(std::cout);
		std::cout << share::symbol_prompt();
		s = share::get_selection(std::cin);

		switch (s) {
		case share::Selection::Quit:
			break;
		case share::Selection::Generate:
			e02::execute();
			break;
		case share::Selection::Read:
			e03::execute();
			break;
		case share::Selection::Generate_with_units:
			std::cout << "Generating file with units..." << '\n';
			break;
		case share::Selection::Read_with_units:
			std::cout << "Reading from file with units..." << '\n';
			break;
		case share::Selection::Invalid_selection:
		default:
			std::cout << "Invalid selection, please try again." << '\n';
			break;
		}
	}

	share::print_goodbye(std::cout);

	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	share::wait_for_exit();
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	share::wait_for_exit();
	return 2;
}
