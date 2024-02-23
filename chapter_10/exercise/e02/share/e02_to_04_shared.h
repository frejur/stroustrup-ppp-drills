#ifndef E02_TO_04_SHARED_H
#define E02_TO_04_SHARED_H

#include <iostream>
#include <string>
#include <vector>

namespace share { //------------------------------------------------------------

constexpr char symbol_degree{ '\370' };
enum class Temperature_unit { Not_a_unit = -1, Fahrenheit, Celsius };

Temperature_unit temp_unit_from_ch(char ch);
char ch_from_temp_unit(Temperature_unit u);
std::string str_from_temp_unit(Temperature_unit u);

double conv_temp(double t, Temperature_unit in, Temperature_unit out);

constexpr char symbol_reading_start{'('};
constexpr char symbol_reading_delimiter{','};
constexpr char symbol_reading_end{')'};

struct Reading
{
	double temperature{ 0 };
	int hour{ 0 };
	Temperature_unit unit = Temperature_unit::Not_a_unit;
};

std::vector<double> temps_v_from_readings(
    const std::vector<Reading> v,
    Temperature_unit base_unit = Temperature_unit::Not_a_unit);

std::ostream& operator<<(std::ostream& os, const Reading& r);
std::istream& operator>>(std::istream& is, Reading& r);

// Generate readings -----------------------------------------------------------

std::vector<Reading> generate_readings(int min_count,
                                       int max_count,
                                       double min_temp,
                                       double max_temp,
                                       bool generate_units = false,
                                       int num_dec_places = 2);

// Stats -----------------------------------------------------------------------
// From CH8E11
struct Stats
{
	int num;
	double avg;
	double med;
	double min;
	double max;
	Temperature_unit unit;
};

double sumv(const std::vector<Reading>& v);
Stats statsv(const std::vector<Reading>& v,
             Temperature_unit base_unit = Temperature_unit::Not_a_unit);

std::string equals_as_str(bool e);
void print_stats(std::ostream& os, const Stats& stats);
void print_stats(std::ostream& os, const Stats& stats_a, const Stats& stats_b);

bool operator==(const Stats& a, const Stats& b);
bool operator!=(const Stats& a, const Stats& b);

std::ostream& operator<<(std::ostream& os, const Stats& s);
std::istream& operator>>(std::istream& is, Stats& s);

// Write to file ---------------------------------------------------------------

void write_readings_to_disk(const std::string& file_path,
                            const std::vector<Reading>& readings);
void write_stats_to_disk(const std::string& file_path, const Stats s);

// Read from file --------------------------------------------------------------

std::vector<Reading> load_readings_from_disk(const std::string& file_path);
Stats load_stats_from_disk(const std::string& file_path);

// Main loop -------------------------------------------------------------------

const std::string& file_extension();
const std::string& file_path_readings();                // Plain readings
const std::string& file_path_readings_with_units();     // Readings with f / c
const std::string& file_path_results_suffix();          // Cache mean and median

const std::string& symbol_prompt();

enum class Selection {
	Invalid_selection = 0,
	Generate,
	Read,
	Generate_with_units,
	Read_with_units,
	Quit
};

Selection get_selection(std::istream& is);

constexpr char symbol_option_generate{ 'a' };
constexpr char symbol_option_read{ 'b' };
constexpr char symbol_option_generate_units{ 'c' };
constexpr char symbol_option_read_units{ 'd' };
constexpr char symbol_option_quit{ 'q' };

const std::string& info_option_generate();
const std::string& info_option_read();
const std::string& info_option_generate_units();
const std::string& info_option_read_units();
const std::string& info_option_quit();

void print_hello(std::ostream& os);
void print_options(std::ostream& os);
void print_option(std::ostream& os, char symbol);
void print_goodbye(std::ostream& os);

void wait_for_exit();

} // namespace share

#endif // E02_TO_04_SHARED_H
