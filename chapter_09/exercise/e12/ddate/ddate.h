#ifndef DDATE_H
#define DDATE_H

#include <iostream>
#include <vector>

namespace DDATE { // -----------------------------------------------------------

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul,
	aug, sep, oct, nov, dec
};

enum class Day_of_the_week {
	mon = 1, tue, wed, thu, fri, sat, sun
};


//------------------------------------------------------------------------------

constexpr int                EPOCH_Y{ 1970 };
constexpr Month              EPOCH_M{ Month::jan };
constexpr int                EPOCH_D{ 1 };
constexpr Day_of_the_week EPOCH_DOTW{ Day_of_the_week::thu };
// Constants (ddate_const.cpp) -------------------------------------------------

const int EPOCH_D_UNTIL_EOFM();
const int EPOCH_D_UNTIL_EOFY();
const int EPOCH_D_CALC_OFFSET();
const int EPOCH_Y_CALC_OFFSET();

const std::vector<int>&			MONTH_DAYS();
const std::vector<std::string>& MONTH_NAMES();
const std::vector<std::string>& DOTW_NAMES();

//------------------------------------------------------------------------------

class Date {
public:
	int days_since_epoch() const { return d_diff; };

	// Initialization (ddate_init.cpp) -----------------------------------------
	Date(long days);
	Date(int y, Month m, int d);
	Date() : d_diff{ 0 }, is_cached{ false } {};

	// Getters (ddate_get.cpp) -------------------------------------------------
	// Calculating these is relatively expensive and it makes more sense to
	// to just calculate all at once with 'update()' and then cache the results.
	int day();
	Month month();
	int year();

	// The day-of-the-week on the other hand, is simple stuff.
	inline Day_of_the_week day_of_the_week() const
	{
		return (
		 static_cast<Day_of_the_week>(
			1 + (static_cast<int>(EPOCH_DOTW) + (d_diff % 7) - 1) % 7)
		);
	}

	// Setters (ddate_set.cpp) -------------------------------------------------
	// When the parameter != 0 these will set 'is_cached' to false.
	void add_days(const long n);
	void add_months(const int n);
	void add_years(const int n);
	void subtract_days(const long n);
	// void subtract_months(const int n); // Skip
	// void subtract_years(const int n);  // Skip
private:
	long d_diff; // Days since epoch

	int d;
	Month m;
	int y;

	// Calculate day, month, year from d_diff then cache results
	bool is_cached;
	void update(); // Defined along with the getter functions (ddate_get.cpp)
};

// Basic helpers (ddate_basic.cpp) ---------------------------------------------

bool is_before_date(int y1, Month m1, int d1, int y2, Month m2, int d2);
bool is_before_min_date(int y, Month m, int d);
bool is_date(const int y, const Month m, const int d); // validate
bool is_date(long int days);
bool is_leap_year(const int y);
int days_in_month(const int y, const Month m);

// Duration helpers (ddate_duration.cpp) ---------------------------------------

int leap_years_from_year_span(int start_y, int end_y);
long days_from_sofm_until_sofm(int y, Month m1, Month m2);
long days_from_sofy_until_sofm(int y, Month m);
long days_from_sofm_until_eofy(int y, Month m);
long duration_in_days(int y1, Month m1, int d1, int y2, Month m2, int d2);

// Operators (ddate_op.cpp) ----------------------------------------

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

// Iostream operators (ddate_iostr.cpp) ----------------------------------------

std::ostream& operator<<(std::ostream& os, Date& date);
std::istream& operator>>(std::istream& is, Date& date);

std::ostream& operator<<(std::ostream& os, const Month month);
std::ostream& operator<<(std::ostream& os, const Day_of_the_week dotw);

// More day-of-the-week helpers (ddate_dotw.cpp) -------------------------------

Date next_sunday(const Date& d);
Date next_weekday(const Date& d);

} // DDATE NAMESPACE------------------------------------------------------------

#endif // DDATE_H
