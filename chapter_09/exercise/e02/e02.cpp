#include "helpers.h"
#include "name_age_pairs.h"
#include <iostream>

// Chapter 9, Exercise 2 and 3. Name_age_pairs class.

// Create class Name_age_pairs that holds name-value pairs.
// Store the names and values in member variables:
//    vector<string> names, vector<int> ages
// Provide member functions:
//    read_names - Prompt for names
//    read_ages  - Promp for an age for each name
//    print      - Print the name-value pairs
//    sort       - Sort names alphabetically, then rearrange ages accordingly.

// This is more or less the same exercise as described in CH08E02 - E03:
// Prompt for a list of names, store in a vector.
// Prompt for the age of all names, store in a vector.
// Sort the name vector alphabetically, sort the age vector accordingly.
// Print the name-age pairs.

// All of the above is instead done with through the use of the class
// Name_age_pairs and its member functions.

// Exercise 3 adds operator overloads for << (Instead of print(), == (and !=)

int main()
try
{
	std::cout
		<< "Name-age pairs with class" << '\n';

	Name_age_pairs na{};

	na.read_names();

	na.read_ages();

	na.print("Unsorted");
	// std::cout << "Unsorted" << '\n' << na << '\n';

	Name_age_pairs na_sorted{ na };

	std::cout << "Unsorted IS THE SAME AS Unsorted : "
		<< ( (na == na_sorted) ? " True " : "False" ) << '\n';

	std::cout << "Press any key to continue..." << '\n';
	std::cin.get();

	na_sorted.sort();

	// na.print("Sorted by name");
	std::cout << "Sorted by name" << '\n' << na_sorted << '\n';

	std::cout << "Unsorted IS NOT THE SAME AS Sorted : "
		<< ( (na != na_sorted) ? " True " : "False" ) << '\n';

	std::cout << '\n'
	          << "Goodbye!" << '\n';

	keep_window_open();
	return 0;
}
catch (std::exception e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
