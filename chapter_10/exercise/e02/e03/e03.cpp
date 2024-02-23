#include "e03.h"
#include "../share/e02_to_04_shared.h"
#include <iostream>
#include <string>

void e03::execute()
{
	std::cout << e03::info() << '\n' << '\n';

	std::string read_f{share::file_path_readings() + share::file_extension()};

	std::cout << "Reading values from '" << read_f << "'..." << '\n';

	std::vector<share::Reading> readings{share::load_readings_from_disk(read_f)};

	std::string stats_f{share::file_path_readings()
	                    + share::file_path_results_suffix()
	                    + share::file_extension()};

	std::cout << "Calculating results..." << '\n';

	share::Stats stats_this{share::statsv(readings)};

	std::cout << "Reading results from '" << stats_f << "'..." << '\n' << '\n';

	share::Stats stats_from_file{share::load_stats_from_disk(stats_f)};
	share::print_stats(std::cout, stats_this, stats_from_file);

	if (stats_this != stats_from_file) {
		throw std::runtime_error("The calculated results do not "
		                         "correspond to the results stored on disk");
	}

	std::cout << '\n' << "Done!" << '\n' << '\n';
}

const std::string& e03::info()
{
	static std::string p{
	    "This option loads the Readings stored on disk and calculates\n"
	    "some statistics such as the mean and median temperatures."};
	return p;
}
