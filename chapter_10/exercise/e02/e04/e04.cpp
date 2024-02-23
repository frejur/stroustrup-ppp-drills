#include "e04.h"
#include "../share/e02_to_04_shared.h"
#include <vector>

void e04::execute_step_1()
{
	std::cout << e04::info_step_1() << '\n' << '\n';

	std::cout << "Generating values..." << '\n' << '\n';

	std::vector<share::Reading> readings{
	    share::generate_readings(50, 100, -15, 40, true)};

	share::Stats stats{
	    share::statsv(readings, share::Temperature_unit::Fahrenheit)};
	share::print_stats(std::cout, stats);

	std::string read_f{share::file_path_readings_with_units()
	                   + share::file_extension()};

	std::cout << '\n' << "Writing values to '" << read_f << "'..." << '\n';

	share::write_readings_to_disk(read_f, readings);

	std::string results_f{share::file_path_readings_with_units()
	                      + share::file_path_results_suffix()
	                      + share::file_extension()};

	std::cout << "Writing results to '" << results_f << "'..." << '\n';

	share::write_stats_to_disk(results_f, stats);

	std::cout << '\n' << "Done!" << '\n' << '\n';
}

void e04::execute_step_2()
{
	std::cout << e04::info_step_2() << '\n' << '\n';

	std::string read_f{share::file_path_readings_with_units()
	                   + share::file_extension()};

	std::cout << "Reading values from '" << read_f << "'..." << '\n';

	std::vector<share::Reading> readings{share::load_readings_from_disk(read_f)};

	std::string stats_f{share::file_path_readings_with_units()
	                    + share::file_path_results_suffix()
	                    + share::file_extension()};

	std::cout << "Calculating results..." << '\n';

	share::Stats stats_this{
	    share::statsv(readings, share::Temperature_unit::Fahrenheit)};

	std::cout << "Reading results from '" << stats_f << "'..." << '\n' << '\n';

	share::Stats stats_from_file{share::load_stats_from_disk(stats_f)};
	share::print_stats(std::cout, stats_this, stats_from_file);

	if (stats_this != stats_from_file) {
		throw std::runtime_error("The calculated results do not "
		                         "correspond to the results stored on disk");
	}

	std::cout << '\n' << "Done!" << '\n' << '\n';
}

const std::string& e04::info_step_1()
{
	static std::string p{
	    "This option generates a series of temperature readings and\n"
	    "stores them in a text file. The temperature values are suffixed\n"
	    "with either 'f' or 'c' (Fahrenheit / Celsius).\n"
	    "\n"
	    "Some statistics such as the mean and median temperatures are\n"
	    "also calculated and stored in a separate text file.\n"
	    "\n"
	    "All values are converted to Fahrenheit before any calculations\n"
	    "are performed."};
	return p;
}

const std::string& e04::info_step_2()
{
	static std::string p{
	    "This option loads the Readings stored on disk and calculates\n"
	    "some statistics such as the mean and median temperatures.\n"
	    "\n"
	    "The temperature values are suffixed with either 'f' or 'c'\n"
	    "(Fahrenheit / Celsius), and all values are converted to Fahrenheit\n"
	    "before any calculations are performed."};
	return p;
}
