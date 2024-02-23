#include "e02.h"
#include "../share/e02_to_04_shared.h"
#include <vector>

void e02::execute()
{
	std::cout << e02::info() << '\n' << '\n';

	std::cout << "Generating values..." << '\n' << '\n';

	std::vector<share::Reading> readings{
	    share::generate_readings(50, 100, -15, 40)};

	share::Stats stats{share::statsv(readings)};
	share::print_stats(std::cout, stats);

	std::string read_f{share::file_path_readings() + share::file_extension()};

	std::cout << '\n' << "Writing values to '" << read_f << "'..." << '\n';

	share::write_readings_to_disk(read_f, readings);

	std::string results_f{share::file_path_readings()
	                      + share::file_path_results_suffix()
	                      + share::file_extension()};

	std::cout << "Writing results to '" << results_f << "'..." << '\n';

	share::write_stats_to_disk(results_f, stats);

	std::cout << '\n' << "Done!" << '\n' << '\n';
}

const std::string& e02::info()
{
	static std::string p{
	    "This option generates a series of temperature readings and\n"
	    "stores them in a text file.\n"
	    "\n"
	    "Some statistics such as the mean and median temperatures are\n"
	    "also calculated and stored in a separate text file."};
	return p;
}
