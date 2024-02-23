#include "e02_to_04_shared.h"
#include "../lib/helpers.h"
#include <fstream>

double share::conv_temp(double t, Temperature_unit in, Temperature_unit out)
{
	if (in == Temperature_unit::Celsius && out == Temperature_unit::Fahrenheit) {
		return help::ctof(t);
	}
	if (in == Temperature_unit::Fahrenheit && out == Temperature_unit::Celsius) {
		return help::ftoc(t);
	}

	throw std::runtime_error("Invalid arguments for conversion");
	return t;
}

share::Temperature_unit share::temp_unit_from_ch(char ch)
{
	if (ch == 'f') {
		return Temperature_unit::Fahrenheit;
	}
	if (ch == 'c') {
		return Temperature_unit::Celsius;
	}
	return Temperature_unit::Not_a_unit;
}

char share::ch_from_temp_unit(Temperature_unit u)
{
	// Returns 0 if not a unit
	char ch = 0;
	if (u == Temperature_unit::Celsius) {
		ch = 'c';
	} else if (u == Temperature_unit::Fahrenheit) {
		ch = 'f';
	}
	return ch;
}

std::string share::str_from_temp_unit(Temperature_unit u)
{
	// Returns empty when unit == 0 == Not_a_unit
	std::string s{};
	char unit{help::chtoupper(ch_from_temp_unit(u))};
	if (unit != 0) {
		// Format: "<Unit> °"
		s.push_back(symbol_degree);
		s.push_back(unit);
	}
	return s;
}

std::vector<double> share::temps_v_from_readings(const std::vector<Reading> v,
                                                 Temperature_unit base_unit)
{
	/* Note that this function also converts to the base_unit of temperature if
	 *  specified by the caller */
	std::vector<double> temps;
	bool should_conv{base_unit != Temperature_unit::Not_a_unit};
	for (const Reading& r : v) {
		if (should_conv && r.unit != base_unit) {
			temps.push_back(conv_temp(r.temperature, r.unit, base_unit));
		} else {
			temps.push_back(r.temperature);
		}
	}

	return temps;
}

std::ostream& share::operator<<(std::ostream& os, const Reading& r)
{
	std::string u{};
	if (r.unit != share::Temperature_unit::Not_a_unit) {
		u.push_back(share::ch_from_temp_unit(r.unit));
	}
	return os << symbol_reading_start << r.hour << symbol_reading_delimiter
	          << ' ' << r.temperature << u << symbol_reading_end;
}

std::istream& share::operator>>(std::istream& is, Reading& r)
{
	char start_c{};
	is >> start_c;
	if (start_c != symbol_reading_start) {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	int h{};
	is >> h;

	char delim{};
	is >> delim;
	if (delim != symbol_reading_delimiter) {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	double t{};
	is >> t;

	// Attempts to fetch unit char, ignores it if no match
	char unit_ch{};
	is >> unit_ch;
	Temperature_unit unit{temp_unit_from_ch(unit_ch)};
	if (unit == Temperature_unit::Not_a_unit) {
		is.unget();
	}

	char end_c{};
	is >> end_c;
	if (end_c != symbol_reading_end) {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	r.hour = h;
	r.temperature = t;
	r.unit = unit;

	return is;
}

// Stats -----------------------------------------------------------------------

double share::sumv(const std::vector<Reading>& v)
{
	double sum{ 0 };
	for (const Reading& r : v) {
		sum += r.temperature;
	}
	return sum;
}

share::Stats share::statsv(const std::vector<Reading>& v,
                           Temperature_unit base_unit)
{
	int num_readings{static_cast<int>(v.size())};
	if (num_readings == 0) {
		throw std::runtime_error("Cannot calculate stats for an empty vector");
	}
	if (num_readings == 1) {
		return {num_readings,
		        (double) v.front().temperature,
		        (double) v.front().temperature,
		        v.front().temperature,
		        v.front().temperature,
		        base_unit};
	}

	std::vector<double> temperatures = {temps_v_from_readings(v)};
	std::sort(temperatures.begin(), temperatures.end());
	double avg{sumv(v) / (double) v.size()};
	avg = static_cast<int>(avg * 100 + 5 * (avg >= 0 ? 1 : -1))
	      / 100.0; // enough precision
	double med = 0;
	if (v.size() % 2 == 0) {
		med = (temperatures[num_readings / 2 - 1]
		       + temperatures[num_readings / 2])
		      * 0.5;
		med = static_cast<int>(med * 100 + 5 * (avg >= 0 ? 1 : -1))
		      / 100.0; // enough precision
	} else {
		med = temperatures[num_readings / 2];
	}

	return {num_readings,
	        avg,
	        med,
	        temperatures.front(),
	        temperatures.back(),
	        base_unit};
}

std::string share::equals_as_str(bool e)
{
	if (e) {
		return "==";
	}
	return "!=";
}

void share::print_stats(std::ostream& os, const Stats& stats)
{
	// Unit if present
	std::string u{share::str_from_temp_unit(stats.unit)};
	if (u.size()) {
		u = " " + u;
	}

	os << "Count   " << stats.num << u << '\n'
	   << "Min:    " << stats.min << u << '\n'
	   << "Max:    " << stats.max << u << '\n'
	   << "Mean:   " << stats.avg << u << '\n'
	   << "Median: " << stats.med << u << '\n';
}

void share::print_stats(std::ostream& os,
                        const Stats& stats_a,
                        const Stats& stats_b)
{
	// Units if present
	std::string ua{share::str_from_temp_unit(stats_a.unit)};
	if (ua.size()) {
		ua = " " + ua;
	}
	std::string ub{share::str_from_temp_unit(stats_b.unit)};
	if (ub.size()) {
		ub = " " + ub;
	}

	os << "Calculated vs. Expected" << '\n'
	   << "-----------------------" << '\n'
	   << "Count:   " << stats_a.num << ua << ' '
	   << equals_as_str(stats_a.num == stats_b.num) << ' ' << stats_b.num << ub
	   << '\n'
	   << "Min:     " << stats_a.min << ua << ' '
	   << equals_as_str(stats_a.min == stats_b.min) << ' ' << stats_b.min << ub
	   << '\n'
	   << "Max:     " << stats_a.max << ua << ' '
	   << equals_as_str(stats_a.max == stats_b.max) << ' ' << stats_b.max << ub
	   << '\n'
	   << "Mean:    " << stats_a.avg << ua << ' '
	   << equals_as_str(stats_a.avg == stats_b.avg) << ' ' << stats_b.avg << ub
	   << '\n'
	   << "Median:  " << stats_a.med << ua << ' '
	   << equals_as_str(stats_a.med == stats_b.med) << ' ' << stats_b.med << ub
	   << '\n';
}

bool share::operator==(const Stats& a, const Stats& b)
{
	return (a.num == b.num && a.avg == b.avg && a.med == b.med && a.min == b.min
	        && a.max == b.max && a.unit == b.unit);
}

bool share::operator!=(const Stats& a, const Stats& b)
{
	return !(a == b);
}

std::ostream& share::operator<<(std::ostream& os, const Stats& s)
{
	std::string unit;
	char unit_ch{share::ch_from_temp_unit(s.unit)};
	if (unit_ch != 0) {
		unit.push_back(unit_ch);
	}
	return os << s.num << ' ' << s.avg << ' ' << s.med << ' ' << s.min << ' '
	          << s.max << ' ' << unit;
}

std::istream& share::operator>>(std::istream& is, Stats& s)
{
	int num_vals = 0;
	double min_val = 0;
	double max_val = 0;
	double mean = 0;
	double median = 0;
	char unit_ch = 0;
	Temperature_unit unit = Temperature_unit::Not_a_unit;

	is >> num_vals >> mean >> median >> min_val >> max_val;

	// Attempts to read unit, skip if not present
	if (!is.eof()) {
		is >> unit_ch;
		if (is.fail()) {
			is.clear();
		} else {
			unit = share::temp_unit_from_ch(unit_ch);
			if (unit == Temperature_unit::Not_a_unit) {
				is.unget();
				is.clear(std::ios_base::failbit);
			}
		}
	}

	if (is || is.eof()) {
		s.num = num_vals;
		s.avg = mean;
		s.med = median;
		s.min = min_val;
		s.max = max_val;
		s.unit = unit;
	}

	return is;
}

// Generate readings -----------------------------------------------------------

std::vector<share::Reading> share::generate_readings(int min_count,
                                                     int max_count,
                                                     double min_temp,
                                                     double max_temp,
                                                     bool generate_units,
                                                     int num_dec_places)
{
	if (min_count >= max_count || min_count < 1) {
		throw std::runtime_error("Invalid min / max count");
	}
	if (min_temp >= max_temp) {
		throw std::runtime_error("Invalid min / max count");
	}
	if (num_dec_places < 0) {
		throw std::runtime_error("Invalid number of decimal places");
	}

	help::seed_randint();
	int scale_f{help::scale_factor(num_dec_places)};
	int num_readings{help::randint(min_count, max_count)};
	std::vector<share::Reading> readings{
	    std::vector<share::Reading>(num_readings,
	                                {0, 0, share::Temperature_unit::Not_a_unit})};
	for (Reading& r : readings) {
		r.hour = help::randint(0, 23);
		r.temperature = help::randint(static_cast<int>(min_temp * scale_f),
		                              static_cast<int>(max_temp * scale_f))
		                / static_cast<double>(scale_f);
		if (generate_units) {
			r.unit = help::randint(1) ? Temperature_unit::Celsius
			                          : Temperature_unit::Fahrenheit;
		}
	}
	return readings;
}
// Write to file ---------------------------------------------------------------

void share::write_readings_to_disk(const std::string& file_path,
                                   const std::vector<share::Reading>& readings)
{
	if (readings.size() == 0) {
		throw std::runtime_error(
		    "Cannot write to file when there are no registered Readings");
	}

	std::ofstream ofs{file_path};
	if (!ofs) {
		throw std::runtime_error("Invalid file path for output '" + file_path
		                         + "'.");
	}

	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit); // throw if bad
	for (const share::Reading& r : readings) {
		ofs << r << '\n';
	}
}

void share::write_stats_to_disk(const std::string& file_path,
                                const share::Stats s)
{
	std::ofstream ofs{file_path};
	if (!ofs) {
		throw std::runtime_error("Invalid file path for output");
	}

	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit); // throw if bad
	ofs << s << '\n';
}
// Read from file --------------------------------------------------------------

std::vector<share::Reading> share::load_readings_from_disk(
    const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Invalid file path for input '" + file_path
		                         + "'.");
	}

	std::vector<Reading> readings;

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit); // throw if bad
	for (Reading r; ifs >> r;) {
		readings.push_back(r);
	}

	if (ifs.fail()) {
		std::runtime_error("Failed to parse reading, aborting...");
	}

	return readings;
}

share::Stats share::load_stats_from_disk(const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Invalid file path for input '" + file_path
		                         + "'.");
	}

	/* Expects a file with a single line of stats, anything else is ignored */
	Stats stats;
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit); // throw if bad
	ifs >> stats;

	if (ifs.fail()) {
		throw std::runtime_error("Failed to read stats");
	}

	return stats;
}

// Main loop -------------------------------------------------------------------

const std::string& share::file_extension()
{
	static std::string p{ ".txt" };
	return p;
}

const std::string& share::file_path_readings()
{
	static std::string p{ "data/raw_temps" };
	return p;
}

const std::string& share::file_path_readings_with_units()
{
	static std::string p{ "data/raw_temps_w_units" };
	return p;
}

const std::string& share::file_path_results_suffix()
{
	static std::string s{"_results"};
	return s;
}

const std::string& share::symbol_prompt()
{
	static std::string p{"> "};
	return p;
}

const std::string& share::info_option_generate()
{
	static std::string p{"Generates and stores temperature readings in a "
	                     "text file."};
	return p;
}

const std::string& share::info_option_read()
{
	static std::string p{"Loads temperature readings from a text file."};
	return p;
}

const std::string& share::info_option_generate_units()
{
	static std::string p{"Generates and stores temperatures readings of "
	                     "varying units in a text file."};
	return p;
}

const std::string& share::info_option_read_units()
{
	static std::string p{"Loads temperature readings of varying units from "
	                     "disks."};
	return p;
}

const std::string& share::info_option_quit()
{
	static std::string p{"Quits the program."};
	return p;
}

void share::print_hello(std::ostream& os)
{
	os << "Read and write temperature values to and from a text file" << '\n'
	   << '\n';
}

void share::print_options(std::ostream& os)
{
	os << "Select one of the options below to proceed:" << '\n';
	print_option(os, symbol_option_generate);
	print_option(os, symbol_option_read);
	print_option(os, symbol_option_generate_units);
	print_option(os, symbol_option_read_units);
	print_option(os, symbol_option_quit);
}

void share::print_option(std::ostream& os, char symbol)
{
	switch (symbol) {
	case symbol_option_generate:
		os << '\'' << symbol_option_generate << "' " << info_option_generate()
		   << '\n';
		break;
	case symbol_option_read:
		os << '\'' << symbol_option_read << "' " << info_option_read() << '\n';
		break;
	case symbol_option_generate_units:
		os << '\'' << symbol_option_generate_units << "' "
		   << info_option_generate_units() << '\n';
		break;
	case symbol_option_read_units:
		os << '\'' << symbol_option_read_units << "' "
		   << info_option_read_units() << '\n';
		break;
	case symbol_option_quit:
		os << '\'' << symbol_option_quit << "' " << info_option_quit() << '\n';
		break;
	default:
		break;
	}
}

void share::print_goodbye(std::ostream& os)
{
	os << "Bye!" << '\n';
}

void share::wait_for_exit()
{
	std::cout << "Press <ENTER> to exit." << '\n';
	if (!std::cin) {
		std::cin.clear();
	}
	help::clear_buffer(std::cin);
	std::cin.get();
}
share::Selection share::get_selection(std::istream& is)
{
	Selection s{ Selection::Invalid_selection };
	char temp_c{};
	std::string temp_str;

	try {
		is.get(temp_c);
		if (temp_c == '\n') {
			return s;
		}
		is.unget();

		is >> temp_str;
		help::clear_buffer(is);

		if (temp_str.size() > 1) {
			return s;
		}

		switch (temp_str.front()) {
		case symbol_option_generate:
			s = Selection::Generate;
			break;
		case symbol_option_read:
			s = Selection::Read;
			break;
		case symbol_option_generate_units:
			s = Selection::Generate_with_units;
			break;
		case symbol_option_read_units:
			s = Selection::Read_with_units;
			break;
		case symbol_option_quit:
			s = Selection::Quit;
			break;
		default:
			break;
		}
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	} catch (...) {
		throw std::runtime_error("Unknown error");
	}

	return s;
}
