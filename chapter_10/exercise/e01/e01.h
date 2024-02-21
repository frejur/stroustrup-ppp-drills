#ifndef E01_H
#define E01_H

#include <iostream>
#include <string>
#include <vector>

const std::string& input_file_path();

constexpr int expected_count{ 100 };
constexpr int max_decimal_count{ 2 };
constexpr double expected_sum{ 150'573.71 };

void print_hello(std::ostream& os);
void print_sum(std::ostream& os, double sum, int count);
void print_expected(std::ostream& os, double sum, int count);
void print_success(std::ostream& os);
void print_failure(std::ostream& os);
void print_goodbye(std::ostream& os);

std::vector<double> read_values_from_ifstream(const std::string& file_path);

int scale_factor(int decimal_count);
char digit_to_char(int i);
std::string double_to_string(double d, int decimal_count = 2);
double sum_of_values(const std::vector<double>& values);

#endif // E01_H
