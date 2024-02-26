#include "reading.h"
#include "../date/date.h"
#include "../help/helpers.h"

std::string tmpr::formatted_temperature(double t)
{
	return help::double_to_string(t) + " " + symbol_degree + symbol_temperature;
}

std::string tmpr::formatted_day(int y, int m, int d)
{
	ch9d::Date date{y, static_cast<ch9d::Month>(m), d};
	return ch9d::dotw_to_str(date.day_of_the_week()) + " the "
	       + help::int_to_ordinal(d);
}

std::string tmpr::formatted_time(int h)
{
	std::string t;
	if (0 > h || h > 23) {
		throw std::runtime_error("Invalid hour value.");
	}

	if (h == 0) {
		t = "12:00 AM";
	} else if (h <= 11) {
		t = help::int_to_string(h) + ":00 AM";
	} else if (h == 12) {
		t = "12:00 PM";
	} else {
		t = help::int_to_string(h - 12) + ":00 PM";
	}

	return t;
}

void tmpr::end_of_loop(std::istream& is, char term, const std::string& message)
{
	if (is.fail()) {
		is.clear();
		char ch;
		if (is >> ch && ch == term) {
			return;
		}
		throw std::runtime_error(message);
	}
}

//------------------------------------------------------------------------------
std::istream& tmpr::operator>>(std::istream& is, Reading& r)
{
	char ch1 = 0;
	if (is >> ch1 && ch1 != '(') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	char ch2 = 0;
	int d = 0;
	int h = 0;
	double t = 0;
	is >> d >> h >> t >> ch2;

	if (!is || ch2 != ')') {
		throw std::runtime_error("Could not parse Reading, expected ')'");
	}

	r.day = d;
	r.hour = h;
	r.temperature = t;

	return is;
}

std::ostream& tmpr::operator<<(std::ostream& os, const Reading& r)
{
	os << '(' << r.day << ' ' << r.hour << ' ' << r.temperature << ')';
	return os;
}

bool tmpr::operator==(const Reading& a, const Reading& b)
{
	return (a.day == b.day) && (a.hour == b.hour)
	       && (a.temperature == b.temperature);
}

bool tmpr::operator!=(const Reading& a, const Reading& b)
{
	return !(a == b);
}
//------------------------------------------------------------------------------
bool tmpr::days_are_eq(const Day& a, const Day& b, bool debug)
{
	if (a.hour.size() != b.hour.size()) {
		if (debug) {
			throw std::runtime_error(
			    "Hour vector size mismatch: '"
			    + help::int_to_string(a.hour.size()) + "' != '"
			    + help::int_to_string(b.hour.size()) + "'");
		}
		return false;
	}
	for (int i = 0; i < a.hour.size(); ++i) {
		if (a.hour[i] != b.hour[i]) {
			if (debug) {
				throw std::runtime_error(
				    "Temperature value mismatch: hour " + help::int_to_string(i)
				    + ": '" + help::double_to_string(a.hour[i]) + "' != hour "
				    + help::int_to_string(i) + ": '"
				    + help::double_to_string(b.hour[i]) + "'");
			}
			return false;
		}
	}
	return true;
}

bool tmpr::operator==(const Day& a, const Day& b)
{
	return days_are_eq(a, b);
}
bool tmpr::operator!=(const Day& a, const Day& b)
{
	return !(a == b);
}

//------------------------------------------------------------------------------
std::istream& tmpr::operator>>(std::istream& is, Month& m)
{
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	std::string marker;
	is >> marker;
	if (!is || marker != month_marker()) {
		throw std::runtime_error("Could not parse Month, expected '"
		                         + month_marker() + "'");
	}

	std::string m_str;
	is >> m_str;
	int m_num = not_a_month;

	m_num = month_to_int(m_str);

	if (!is || m_num == not_a_month) {
		throw std::runtime_error("Could not parse Month, '" + m_str
		                         + "' is not the name of a month");
	}

	bool is_empty = true;
	int num_duplicates = 0;
	int num_invalid = 0;
	for (Reading r; is >> r;) {
		if (is_valid(r)) {
			if (is_empty) {
				is_empty = false;
			} else if (m.day[r.day].hour[r.hour] != not_a_reading) {
				++num_duplicates;
			}
			m.day[r.day].hour[r.hour] = r.temperature;
		} else {
			++num_invalid;
		}
	}

	if (num_invalid > 0) {
		throw std::runtime_error("Found " + help::int_to_string(num_invalid)
		                         + " invalid Readings in Month");
	}
	if (num_duplicates > 0) {
		throw std::runtime_error("Found " + help::int_to_string(num_duplicates)
		                         + " duplicate Readings in Month");
	}
	end_of_loop(is, '}', "Could not parse Month, expected '}'");
	if (is_empty) {
		m.month = not_a_month;
	} else {
		m.month = m_num;
	}
	return is;
}

std::ostream& tmpr::operator<<(std::ostream& os, const Month& m)
{
	if (m.month == not_a_month) {
		return os; // Nothing to output
	}

	os << "{ " << month_marker() << ' ' << int_to_month(m.month) << ' ';
	for (int d = 1; d < 32; ++d) {
		for (int h = 0; h < 24; ++h) {
			if (m.day[d].hour[h] != not_a_reading) {
				os << '(' << d << ' ' << h << ' ' << m.day[d].hour[h] << ')';
			}
		}
	}
	os << " }";

	return os;
}

bool tmpr::months_are_eq(const Month& a, const Month& b, bool debug)
{
	if (a.month != b.month || a.day.size() != b.day.size()) {
		if (debug) {
			throw std::runtime_error(
			    "Month value or days vector size mismatch: month '"
			    + help::int_to_string(a.month) + "', size '"
			    + help::int_to_string(a.day.size()) + "' != month '"
			    + help::int_to_string(b.month) + "', size '"
			    + help::int_to_string(b.day.size()) + "'");
		}
		return false;
	}

	for (int i = 0; i < a.day.size(); ++i) {
		if (days_are_eq(a.day[i], b.day[i], debug)) {
			return false;
		}
	}
	return true;
}

bool tmpr::operator==(const Month& a, const Month& b)
{
	return months_are_eq(a, b);
}
bool tmpr::operator!=(const Month& a, const Month& b)
{
	return !(a == b);
}
void tmpr::print_month(std::ostream& os, const Month& m, int y)
{
	if (m.month == not_a_month) {
		return;
	}
	os << indent() << formatted_month(m.month) << ':' << '\n';
	for (int d = 0; d < 24; ++d) {
		print_day(os, m, y, d);
	}
}

void tmpr::print_day(std::ostream& os, const Month& m, int y, int d)
{
	std::vector<std::string> readings;
	for (int h = 0; h < 24; ++h) {
		double t{m.day[d].hour[h]};
		if (t != not_a_reading) {
			readings.push_back(formatted_time(h) + ": "
			                   + formatted_temperature(t));
		}
	}
	if (readings.size()) {
		os << indent() << indent() << tmpr::formatted_day(y, m.month, d) << ':'
		   << '\n';
		for (const std::string& r : readings) {
			os << indent() << indent() << indent() << r << '\n';
		}
	}
}

//------------------------------------------------------------------------------

std::istream& tmpr::operator>>(std::istream& is, Year& y)
{
	char ch = 0;
	if (!is || !(is >> ch)) {
		return is;
	}

	if (ch != '{') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	std::string marker;
	is >> marker;
	if (!is || marker != year_marker()) {
		throw std::runtime_error("Could not parse Year, expected '"
		                         + year_marker() + "'");
	}

	int year = not_a_year;
	is >> year;
	if (!is || !is_valid_year(year)) {
		throw std::runtime_error(
		    "Could not parse Year, expected an integer value between "
		    + help::int_to_string(min_year) + " and "
		    + help::int_to_string(max_year));
	}

	std::vector<Month> new_months;
	for (;;) {
		Month m;
		if (!(is >> m)) {
			break;
		}
		if (m.month == not_a_month) {
			continue; // empty
		}
		new_months.push_back(m);
	}

	end_of_loop(is, '}', "Could not parse Year, expected '}'");

	y.year = year;
	for (const Month& m : new_months) {
		y.month[m.month] = m;
	}
	return is;
}

std::ostream& tmpr::operator<<(std::ostream& os, const Year& y)
{
	os << "{ " << year_marker() << ' ' << y.year << ' ';

	int is_empty = true;
	for (const Month& m : y.month) {
		os << m;
		if (is_empty && m.month != not_a_month) {
			is_empty = false;
		}
	}

	if (is_empty) {
		os << ' ';
	}

	os << " }";
	return os;
}

bool tmpr::years_are_eq(const Year& a, const Year& b, bool debug)
{
	if (a.year != b.year || a.month.size() != b.month.size()) {
		if (debug) {
			throw std::runtime_error(
			    "Year value or months vector size mismatch: year '"
			    + help::int_to_string(a.year) + "', size '"
			    + help::int_to_string(a.month.size()) + "' != year '"
			    + help::int_to_string(b.year) + "', size '"
			    + help::int_to_string(b.month.size()) + "'");
		}
		return false;
	}

	for (int i = 0; i < a.month.size(); ++i) {
		if (months_are_eq(a.month[i], b.month[i], debug)) {
			return false;
		}
	}
	return true;
}

bool tmpr::operator==(const Year& a, const Year& b)
{
	if (a.year != b.year || a.month.size() != b.month.size()) {
		return false;
	}
	for (int i = 0; i < a.month.size(); ++i) {
		if (a.month[i] != b.month[i]) {
			return false;
		}
	}
	return true;
}
bool tmpr::operator!=(const Year& a, const Year& b)
{
	return !(a == b);
}

void tmpr::print_year(std::ostream& os, const Year& y)
{
	bool is_empty = true;
	for (const Month& m : y.month) {
		if (m.month != not_a_month) {
			is_empty = false;
			break;
		}
	}
	if (is_empty) {
		os << y.year << " is empty." << '\n';
		return;
	}

	os << help::int_to_string(y.year) << ':' << '\n';
	for (int m_p = 1; m_p < y.month.size(); ++m_p) {
		print_month(os, y.month[m_p], y.year);
	}
}
