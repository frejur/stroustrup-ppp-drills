#ifndef TEST_DATE_H
#define TEST_DATE_H

#include "../date/date.h"

// Runs all tests
void test_date();

void test_is_valid_date(int y, Month m, int d, bool invert=false);

// Weeks per year
void test_wpyear(int tear, int expected);
void test_wpyear_multiple();

// ISO Week number
void test_wofyear(const Date& date, int expected);
void test_wofyear_multiple();

// Leap years
void test_leap_year_helper(int year, bool invert=false);
void test_count_leap_years(int start_y, int end_y, int expected);
void test_count_leap_years_multiple();

// Add days / months / years
void test_add_year_eof_feb();
void test_add_days(const Date& start, const int add_days, const Date& expected);
void test_add_days_multiple();
void test_add_months(const Date& start, const int add_months,
                     const Date& expected);
void test_add_months_multiple();

// Test days until end of year / end of month
void test_days_until_eofy(int y, Month m, int expected);
void test_days_until_eofy_multiple();
void test_days_until_sofm(int y, Month m, int expected);
void test_days_until_sofm_multiple();

// Test duration in days
void test_duration(const Date& start, const Date& end, int expected);
void test_duration_multiple();

// Test Day of the week and Next workday
void test_dotw(const Date& d, const Day_of_the_week expected);
void test_workday(const Date& d, const Date& expected);
void test_dotw_multiple();
void test_workday_multiple();

#endif // TEST_DATE_H
