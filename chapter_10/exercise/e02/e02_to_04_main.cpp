#include "e02/e02.h"
#include "e03/e03.h"
#include "e04/e04.h"
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
 *   - Allows the user to select which exercise to execute.
 *   - Splits exercise 4 into 2 'steps'.
 *   - Generates a random number of readings, generates random hour and
 *     temperature values (Including the assigned unit).
 *   - When generating the data, calculates the mean and median and stores the
 *     results in a separate text file.
 *   - In that same results file, also stores the number of generated values,
 *     minimum value, maximum value and base unit.
 *   - When calculating statistics for the temperature readings extracted from
 *     the data file also cross checks with the values previously stored in the
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
			e04::execute_step_1();
			break;
		case share::Selection::Read_with_units:
			e04::execute_step_2();
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
