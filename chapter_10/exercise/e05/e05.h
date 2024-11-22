#ifndef E05_H
#define E05_H
#include "reading/reading.h"
#include <iostream>
#include <vector>

inline const std::string& file_path()
{
	static std::string p{"data_e05/readings.txt"};
	return p;
}
inline const std::string& file_path_formatted()
{
	static std::string p{"data_e05/readings_formatted.txt"};
	return p;
}

void print_hello(std::ostream& os);
void print_generate(std::ostream& os);
void print_read(std::ostream& os);
void print_compare(std::ostream& os);
void print_display(std::ostream& os);
void print_save(std::ostream& os);
void print_goodbye(std::ostream& os);

struct Year_range
{
	int start;
	int end;
};

struct Freq_range
{
	double min;
	double max;
};

struct Min_max
{
	int min;
	int max;
};

struct Temperature_range
{
	double min;
	double max;
};

inline void validate(Year_range y_range)
{
	if (tmpr::min_year > y_range.start || y_range.start > tmpr::max_year) {
		throw std::runtime_error("Invalid start year");
	}
	if (y_range.start > y_range.end || y_range.end > tmpr::max_year) {
		throw std::runtime_error("Invalid end year");
	}
}

inline void validate(Freq_range f)
{
	if ((f.min > f.max) || f.min <= 0) {
		throw std::runtime_error("Invalid minimum");
	}
	if (f.max > 1) {
		throw std::runtime_error("Invalid maximum");
	}
}

inline void validate(Temperature_range t)
{
	if (t.min < tmpr::implausible_min_temp || t.min > tmpr::implausible_max_temp
	    || t.max < tmpr::implausible_min_temp
	    || t.max > tmpr::implausible_max_temp) {
		throw std::runtime_error("Invalid temperature values");
	}
	if (t.min > t.max) {
		throw std::runtime_error("Invalid minimum");
	}
}

inline Min_max min_max(int total, Freq_range f)
{
	int count_min{static_cast<int>(total * f.min * 10.0 + 5) / 10};
	int count_max{static_cast<int>(total * f.max * 10.0 + 5) / 10};
	if (count_min < 1) {
		throw std::runtime_error("Invalid minimum");
	}
	return {count_min, count_max};
}

std::vector<tmpr::Year> generate_random_readings(Year_range y_range,
                                                 Freq_range freq_y,
                                                 Freq_range freq_m,
                                                 Freq_range freq_d,
                                                 Freq_range freq_h,
                                                 Temperature_range t_range);

void write_readings_to_file(const std::string f_path,
                            const std::vector<tmpr::Year> readings);

std::vector<tmpr::Year> load_readings_from_file(const std::string f_path);

void write_formatted_readings_to_file(const std::string f_path,
                                      const std::vector<tmpr::Year> readings);

#endif // E05_H
