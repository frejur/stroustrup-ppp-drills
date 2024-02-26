#include "e05.h"
#include "date/date.h"
#include "help/helpers.h"
#include <algorithm>
#include <fstream>

void print_hello(std::ostream& os)
{
	os << "Print grouped readings using print_year()" << '\n';
}
void print_generate(std::ostream& os)
{
	os << "Press <ENTER> to generate and write a series of random readings to "
	      "disk."
	   << '\n';
}
void print_read(std::ostream& os)
{
	os << "Press <ENTER> to read and parse the readings stored on disk."
	   << '\n';
}
void print_compare(std::ostream& os)
{
	os << "Press <ENTER> to compare the generated values with the ones stored "
	      "on disk."
	   << '\n';
}
void print_display(std::ostream& os)
{
	os << "Press <ENTER> to format and print the recorded readings." << '\n';
}
void print_save(std::ostream& os)
{
	os << "Press <ENTER> to save a copy of the formatted readings to disk."
	   << '\n';
}

void print_goodbye(std::ostream& os)
{
	os << "Bye!" << '\n';
}

std::vector<tmpr::Year> generate_random_readings(Year_range y_range,
                                                 Freq_range freq_y,
                                                 Freq_range freq_m,
                                                 Freq_range freq_d,
                                                 Freq_range freq_h,
                                                 Temperature_range t_range)
{
	validate(y_range);
	validate(freq_y);
	validate(freq_m);
	validate(freq_d);
	validate(freq_h);
	validate(t_range);

	int num_years_total{y_range.end - y_range.start};
	Min_max min_max_y{min_max(num_years_total, freq_y)};
	Min_max min_max_m{min_max(12, freq_m)};
	Min_max min_max_h{min_max(24, freq_h)};

	// Test with lowest possible number of days, will throw if invalid
	Min_max min_max_d_test{min_max(26, freq_m)};

	help::seed_randint();

	std::vector<int> all_years{
	    help::sequence(y_range.start, y_range.end, num_years_total)};
	std::vector<int> all_months{help::sequence(1, 12, 12)};
	std::vector<int> all_hours{help::sequence(1, 24, 24)};

	help::shuffle(all_years, 3);
	std::vector<tmpr::Year> reading_years;
	int num_years{help::randint(min_max_y.min, min_max_y.max)};

	std::vector<int> selected_years;
	for (int i = 0; i < num_years; ++i) {
		selected_years.push_back(all_years[i]);
	}
	std::sort(selected_years.begin(), selected_years.end());

	for (int y = 0; y < num_years; ++y) {
		tmpr::Year r_year;
		r_year.year = selected_years[y];

		int num_months{help::randint(min_max_m.min, min_max_m.max)};
		help::shuffle(all_months, 3);
		for (int m = 0; m < num_months; ++m) {
			int m_num = all_months[m] - 1; // zero-indexed
			r_year.month[m_num].month = m_num;
			int max_days{ch9d::days_in_month(r_year.year,
			                                 static_cast<ch9d::Month>(
			                                     m_num + 1))}; // 1-indexed
			std::vector<int> all_days{help::sequence(1, max_days, max_days)};
			help::shuffle(all_days, 3);

			Min_max min_max_d{min_max(max_days, freq_d)};
			int num_days{help::randint(min_max_d.min, min_max_d.max)};

			for (int d = 0; d < num_days; ++d) {
				int d_num = all_days[d];

				int num_hours{help::randint(min_max_h.min, min_max_h.max)};
				help::shuffle(all_hours, 3);
				for (int h = 0; h < num_hours; ++h) {
					int h_num = all_hours[h] - 1; // zero-indexed
					double rand_t{static_cast<double>(
					    help::randint(t_range.min * 100, t_range.max * 100)
					    / 100.0)};
					r_year.month[m_num].day[d_num].hour[h_num] = rand_t;
				}
			}
		}
		reading_years.push_back(r_year);
	}

	return reading_years;
}

void write_readings_to_file(const std::string f_path,
                            const std::vector<tmpr::Year> readings)
{
	std::ofstream ofs{f_path};

	if (!ofs) {
		throw std::runtime_error("Invalid file path for output '" + f_path
		                         + "'.");
	}

	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit); // throw if bad

	for (const tmpr::Year& y : readings) {
		ofs << y;
	}
}

std::vector<tmpr::Year> load_readings_from_file(const std::string f_path)
{
	std::ifstream ifs{f_path};

	if (!ifs) {
		throw std::runtime_error("Invalid file path for output '" + f_path
		                         + "'.");
	}

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit); // throw if bad

	std::vector<tmpr::Year> new_years;
	for (;;) {
		tmpr::Year y;
		if (ifs >> y) {
			new_years.push_back(y);
		} else {
			break;
		}
	}
	return new_years;
}

void write_formatted_readings_to_file(const std::string f_path,
                                      const std::vector<tmpr::Year> readings)
{
	std::ofstream ofs{f_path};

	if (!ofs) {
		throw std::runtime_error("Invalid file path for output '" + f_path
		                         + "'.");
	}

	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit); // throw if bad

	for (const tmpr::Year& y : readings) {
		print_year(ofs, y);
	}
}
