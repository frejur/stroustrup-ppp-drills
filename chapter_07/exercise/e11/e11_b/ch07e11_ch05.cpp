#include "../../../lib/std_lib_facilities.h"

// Exercise 11b.	Revisit exercise 14 from chapter 5: Grouped day values.
//					~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//					As a candidate for programs that could be improved using
//					the "rules" from chapter 7, this exercise just ticks a lot
//					of boxes.
//------------------------------------------------------------------------------
// Added functionality:
// + Instead of simply summing up some abstract numbers, start by asking the
//   user for the name of an activity or task he or she has been busy with the
//   past week. Then ask him or her to log all instances of that activity.
// + Prompt for the day-of-the-week it was performed along with the time spent
//   expressed in hours, minutes and seconds.
// + Establish a "grammar" for valid input.
// + Parse the input using a Token parser similar to the one implemented for
//   the calculator.
// + Output the sum of each day as time expressed in hours and minues.
// + Throw an error if an entered value, or the sum of time for a day,
//   exceeds 24 hours.
//
// Steps taken:
// 1. Add prompt symbol.
// 2. Terminate user input with linebreak.
// 3. Refactor parts of the program into functions.
// 4. Improve code layout.
// 5. Add comments where useful.
// 6. Recover from errors.
// 7. Use classes where applicable.
// 8. Try to break the program with random input data, fix bugs.
//------------------------------------------------------------------------------
//
// Program description TODO
//
// All values are stored as <double>s but the user may only put in whole values.
//
//------------------------------------------------------------------------------
//
// Grammar
//
//	Command:
//		[QUIT]'\n'
//		[PRINT]'\n'
//		Activity-Record'\n'
//
//	Activity-Record:
//		Day-of-the-week Duration
//
//	Day-of-the-week:
//		String literal (Letters only)
//
//	Duration:
//		Seconds
//		Minutes Seconds
//		Hours Minutes
//		Hours Seconds
//		Hours Minutes Seconds
//
//	Hours:
//		Number'h'
//
//	Minutes:
//		Minutes'm'
//
//	Seconds:
//		Seconds's'
//
//	Number:
//	Integer literal (>= 0)
//
// Notes: [NAME OF TERM] are special characters or strings defined in
//        the program code.
//
//        Day-of-the-week must (at least partially) match one of the days
//        defined in the program code.
//
//------------------------------------------------------------------------------

constexpr char PROMPT{ '>' };
const std::string QUIT{ "exit" };
const std::string PRINT{ "print" };

constexpr int DAY_MINUTES{ 24 * 60};
constexpr int DAY_SECONDS{ DAY_MINUTES * 60 };
constexpr int HOUR_SECONDS{ 3600 };

//------------------------------------------------------------------------------
// Convert string / char into lowercase (TODO: swap for something proper)

constexpr int LOWER_OFFS{ 'a' - 'A' };

char to_lower(char c) {
    if (!isalpha(c)) {
        return c;
    }
    if ('a' <= c && c <= 'z') {
    	return c;
    }
    char low{ char(c + LOWER_OFFS) };
    if (!isalpha(low)) {
        return c;
    }
    return low;
}

std::string to_lower(std::string s) {
    std::string low{ "" };
    for (char c : s) {
        low += to_lower(c);
    }
    return low;
}

// Trim spaces TODO: Swap with something built-in
std::string trim(std::string s) {
	std::string new_s;
	int sp_count{ (s.front() == ' ') };
	for (char c : s) {
		if (c != ' ') {
			new_s += c;
			sp_count = 0;
		} else {
			if (sp_count == 0) {
				new_s += ' ';
			}
			sp_count++;
		}
	}
	if (new_s.back() == ' ') {
		new_s.pop_back();
	}

	return new_s;
}
//------------------------------------------------------------------------------
// Manages the program's definition of the different days-of-the-week

class Day_of_the_week {
public:
	std::string name;
	std::string search_str; // Characters needed to distinguish one day from
	                        // another, e.g. if there are three days called
	                        // 'Jumatatu', 'Jumanne', 'Jumatano' one would
	                        // need to enter "Juman", "Jumatat" or "Jumatan" to
	                        // avoid any ambiguity.
};

class Week {
public:
	void add_day(Day_of_the_week day);
	int search(std::string search_str) { return day_idx_lazy(search_str); };
	std::string name_of_day(int day_idx) { return days.at(day_idx).name; };
private:
	vector<Day_of_the_week> days;
	int day_idx(std::string name); // Returns matching index or -1 if no match
	int day_idx_lazy(std::string name);
};

// Find by exact name match
int Week::day_idx(std::string search_str) {
	for (int i = 0; i < days.size(); ++i) {
		if (days.at(i).name == search_str) {
			return i;
		}
	}
	return -1;
}

// Find by partial, NOT case-sensitive match
int Week::day_idx_lazy(std::string search_str) {
	search_str = to_lower(search_str);
	for (int i = 0; i < days.size(); ++i) {
		std::string check_str{ days.at(i).search_str };
		if (search_str.size() >= check_str.size() &&
		    search_str.substr(0, check_str.size()) == check_str
		) {
			return i;
		}
	}
	return -1;
}

void Week::add_day(Day_of_the_week day) {
	if (day.name == "" || day.search_str == "") {
		error("Day cannot be an empty string");
	}
	if (day_idx(day.name) == -1) {
		days.push_back({ day.name, to_lower(day.search_str) });
	} else {
		error("A day-of-the-week by that name already exists.");
	}
}
//------------------------------------------------------------------------------
// Expresses durations in a more human-readable format
class HMS_Duration {
public:
	double hours;
	double minutes;
	double seconds;
};

// Keeps durations in the form of seconds
class Duration {
public:
	void init(double max_s) { sum = 0; max = max_s; };

	// updates sum and returns true if max is not exceeded
	bool add_seconds(double s);
	bool add(double h, double m, double s);

	double total() { return sum; }; // seconds
	HMS_Duration as_units();
private:
	double sum;
	double max;
};

bool Duration::add_seconds(double s) {
	if (sum + s > max) {
		return false;
	}
	sum += s;
	return true;
};

bool Duration::add(double h, double m, double s) {
	return add_seconds(h * 60 * 60 + m * 60 + s);
}

HMS_Duration Duration::as_units() {
	if (sum == 0) {
		return {0, 0, 0};
	}

	// TODO: swap for something better, could cause integer overflow
	double h{ (double)static_cast<int>(sum / HOUR_SECONDS) };
	double m{ (double)static_cast<int>((sum - h * HOUR_SECONDS) / 60) };
	double s{ sum - (h * HOUR_SECONDS) - (m * 60) };
	return {h, m, s};
}
//------------------------------------------------------------------------------
// Manages time tied to days-of-the-week

class Activity_log {
public:
	void init(std::string activity, vector<Day_of_the_week> days);
	void add_record(std::string name_of_day, double h, double m, double s);

	// returns the sum of all the logged time for a given day
	double sum_of_day(int day_idx);
	HMS_Duration unit_sum_of_day(int day_idx);

	std::string activity() { return act; };
	std::string name_of_day(int day_idx) { return week.name_of_day(day_idx); };
private:
	std::string act;
	Week week;
	vector<Duration> sums;
	void update_sum(int day_idx, double h, double m, double s);
	int fail_count; // number of rejected entries
};

void Activity_log::init(std::string a, vector<Day_of_the_week> days) {
	act = a;
	if (days.size() != 7) {
		error("Failed to specify all seven days of the week");
	}
	week = Week{ };
	for (Day_of_the_week d : days) {
		week.add_day(d);
	}

	// init. vector of seven 24 hour durations
	Duration d{};
	d.init(DAY_SECONDS);
	sums = { d, d, d, d, d, d, d };

	fail_count = 0;
}

void Activity_log::update_sum(int day_idx, double h, double m, double s) {
	if (h < 0 || m < 0 || s < 0) {
		error("Negative duration values are not allowed");
	}
	if (h + m + s == 0) {
		error("Zero value duration");
	}
	if (h != (double)static_cast<int>(h) ||
	    m != (double)static_cast<int>(m) ||
	    s != (double)static_cast<int>(s)
	) {
		error("Duration values must be whole numbers");
	}
	if (h > 24 || m > DAY_MINUTES || s > DAY_SECONDS) {
		error("Duration component exceeds 24 hours");
	}

	if (!sums.at(day_idx).add(h, m, s)) { // Updates if result < 24h
		error("Total duration would exceed 24 hours");
	}
}

void Activity_log::add_record(
	std::string name_of_day, double h, double m, double s)
{
	try {
		int day_idx{ week.search(name_of_day) };
		if (day_idx == -1) {
			error("Invalid day-of-the-week");
		}
		update_sum(day_idx, h, m, s);
	}
	catch(std::exception& e) {
		++fail_count;
		error(e.what());
	}
	catch(...) {
		++fail_count;
		error("Unknown error evaluating sum");
	}
}

double Activity_log::sum_of_day(int day_idx) {
	return sums.at(day_idx).total();
}

HMS_Duration Activity_log::unit_sum_of_day(int day_idx) {
	return sums.at(day_idx).as_units();
}

Activity_log al{}; // Global instance

//------------------------------------------------------------------------------
// These functions are used to provide a more user-friendly interface:
// Instructions, feedback, output formatted data...

void print_intro()
{
	std::cout
		<< "Activity Logger (Days-of-the-week revisited)" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n'
		<< "This program allows the user to log time for a certain" << '\n'
		<< "activity or task over the course of a week."
		<< '\n' << '\n';
}

void print_help_for_activity() {
	std::cout
		<< "Please enter the name of a task or activity that has " << '\n'
		<< "been keeping you busy the past week."
		<< '\n';
}

void print_hints()
{
	static const std::string TXT_LAZY {
		"+ Instead of typing the full day-of-the-week, just enter the" "\n"
		"  first few letters."
	};
	static const std::string TXT_TIME {
		"+ Only include the units of time relevant to your log entry:" "\n"
		"  \"1h 20m\", \"500s\", \"30m\" are all valid duration values."
	};
	static const std::string TXT_PRINT {
		"+ Type '" + PRINT + "' to print a summary of the logged values."
	};
	std::cout
		<< TXT_LAZY << '\n'
		<< TXT_TIME << '\n'
		<< TXT_PRINT << '\n'
		<< '\n';
}

void print_help_for_log() {
	std::string TXT_EXAMPLE{ al.name_of_day(0) + " 1h 20m 30s" };

	std::cout << "Here's the full list of the days-of-the-week:" << '\n';
	for (int i = 0; i < 7; ++i) {
		if (i > 0) {
			std::cout << ", ";
		}
		std::cout << al.name_of_day(i);
	}

	std::cout
		<< '\n' << '\n'
		<< "You may now log time for the chosen activity." << '\n'
		<< "Please specify the day-of-the-week and the time spent." << '\n'
		<< "Example input: '" << TXT_EXAMPLE << '\'' << '\n'
		<< '\n';

	print_hints();
}

void print_summary() {
	std::cout
		<< "Summary of last week" << '\n'
		<< "Activity: '" << al.activity() << "'" << '\n';
	for (int i = 0; i < 7; ++i) {
		HMS_Duration d{ al.unit_sum_of_day(i) };
		std::cout
			<< "  " << d.hours << "h " << d.minutes << "m " << d.seconds << "s"
			<< '\t' << " on "
			<< al.name_of_day(i)
			<<  '\n';
	}
}

void print_continue()
{
	print_summary();

	std::cout
		<< '\n'
		<< "Please submit another entry, or enter '" << QUIT << "' to exit"
		<< '\n';
	print_hints();
}

void print_outro()
{
	std::cout << "Goodbye!" << '\n' << '\n';
	print_summary();
}

//------------------------------------------------------------------------------
// Reads entire line into string and returns it if it contains characters
std::string get_activity() {
	std::string activity{ "" };
	char c{};
	int c_count{ 0 }; // Count alphanumericals

	std::cout << PROMPT << ' ';
	while (std::cin.get(c)) {
		if (isalnum(c)) {
			++c_count;
		}
		if (c == '\n') {
			if (c_count > 0) {
				break;
			} else {
				activity = "";
				std::cout << PROMPT << ' ';
				continue;
			}
		}
		activity += c;
	}
	return activity;
}

// Prepares the global Activity_log instance for input
void init_log()
{
	al.init(
		trim(get_activity()),
		{
			{ "Monday", "mo" }, { "Tuesday", "tu" }, { "Wednesday", "we" },
			{ "Thursday", "th" }, { "Friday", "fr" },
			{ "Saturday", "sa" }, { "Sunday", "su" }
		}
	);
	std::cout
		<< '\n'
		<< "Then let's log time for the activity / task by the name of:" << '\n'
		<< "'" << al.activity() << "'" << '\n'
		<< '\n';
}

//------------------------------------------------------------------------------

void log_time()
{
	while (std::cin)
	try {
		std::string dotw{};
		double h{}, m{}, s{};
		std::cin >> dotw >> h >> m >> s;
		al.add_record(dotw, h, m, s);
		print_continue();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
	catch (...) {
		std::cout << "Unknown error" << '\n';
	}
}

//------------------------------------------------------------------------------
int main()
{
	print_intro();

	print_help_for_activity();
	init_log();

	print_help_for_log();
	log_time();

	print_outro();

	keep_window_open();
	return 0;
}

//const std::string EXIT_WORD{ "print" };

//// forward declare helpers
//bool is_mon(std::string s); bool is_tue(std::string s);
//bool is_wed(std::string s); bool is_thu(std::string s);
//bool is_fri(std::string s); bool is_sat(std::string s);
//bool is_sun(std::string s); bool is_x_day(std::string, vector<std::string> v);

//int s_to_day_idx(std::string s) {
//	// returns 0 - 6 (Monday - Sunday) on success
//	// returns -1 on failure
//	int i{ -1 };
//	if (is_mon(s)) {
//		i = 0;
//	} else if (is_tue(s)) {
//		i = 1;
//	} else if (is_wed(s)) {
//		i = 2;
//	} else if (is_thu(s)) {
//		i = 3;
//	} else if (is_fri(s)) {
//		i = 4;
//	} else if (is_sat(s)) {
//		i = 5;
//	} else if (is_sun(s)) {
//		i = 6;
//	}
//	return i;
//}

//void print_sum_ints(std::string name, vector<int> v) {
//	if (v.size() == 0) {
//		std::cout << name << ':' << '\t' << '-' << '\n';
//		return;
//	}
//	double sum { 0 };
//	for (int i : v) {
//		sum = (double)narrow_cast<int>(sum + i);
//	}
//	std::cout << name << ':' << '\t' << (int)sum << '\n';
//}



//int main()
//try {
//	std::cout
//		<< "The sum of values grouped by day-of-the-week." << '\n' << '\n'
//		<< "Please enter a day-of-the-week and a value (integer) " << '\n'
//		<< "associated with that day:"
//		<< '\n' << '\n';

//	vector<int> mon_v{}, tue_v{}, wed_v{}, thu_v{}, fri_v{}, sat_v{}, sun_v{};
//	int count_accepted{ 0 };
//	int count_rejected{ 0 };

//	std::string day{};
//	int val{};
//	while (day != EXIT_WORD) {
//		// name
//		if (day.size() == 0) {
//			if (!(std::cin >> day)) {
//				error("Invalid input, expected a name");
//			}
//			continue; // move on to value
//		}

//		// value
//		if (!(std::cin >> val)) {
//			error("Invalid input, expected an integer");
//		}
//		int day_idx{ s_to_day_idx(day) };
//		if (day_idx == -1) {
//			++count_rejected;
//			day = "";
//			continue; //ignore
//		}

//		// add entry
//		switch (day_idx) {
//		case 0:
//			mon_v.push_back(val);
//			break;
//		case 1:
//			tue_v.push_back(val);
//			break;
//		case 2:
//			wed_v.push_back(val);
//			break;
//		case 3:
//			thu_v.push_back(val);
//			break;
//		case 4:
//			fri_v.push_back(val);
//			break;
//		case 5:
//			sat_v.push_back(val);
//			break;
//		case 6:
//			sun_v.push_back(val);
//			break;
//		default:
//			error("Invalid day-of-the-week index");
//			break;
//		}

//		std::cout << "Keep adding entries, or enter 'print' to finish." << '\n';
//		day = "";
//		++count_accepted;
//	}
//	if (!std::cin) {
//		error("Input error, expected a name-value pair.");
//	}

//	if (count_accepted) {
//		std::cout << '\n'
//			<< "Printing the sum of values:" << '\n'
//			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
//			<< '\n';
//		print_sum_ints("MON", mon_v);
//		print_sum_ints("TUE", tue_v);
//		print_sum_ints("WED", wed_v);
//		print_sum_ints("THU", thu_v);
//		print_sum_ints("FRI", fri_v);
//		print_sum_ints("SAT", sat_v);
//		print_sum_ints("SUN", sun_v);
//	} else {
//		std::cout << "No entries were registered." << '\n';
//	}
//	if (count_rejected) {
//		if (count_rejected == 1) {
//			std::cout << "1 value was rejected" << '\n';
//		} else {
//			std::cout
//				<< count_rejected << " value(s) were rejected." << '\n';
//		}
//	}

//	keep_window_open();
//	return 0;
//}
//catch (std::exception& e) {
//	std::cerr << "Error: " << e.what() << '\n';
//	keep_window_open();
//	return 1;
//}
//catch (...) {
//	std::cerr << "Unknown error" << '\n';
//	keep_window_open();
//	return 2;
//}

//bool is_x_day(std::string s, vector<std::string> names) {
//	if (s.size() == 0) {
//		return false;
//	}
//	for (std::string n : names) {
//		if (s == n) {
//			return true;
//		}
//	}
//	return false;
//}

//bool is_mon(std::string s) {
//	return is_x_day(s, { "Monday", "Mon", "mon", "monday" });
//}
//bool is_tue(std::string s) {
//	return is_x_day(s, { "Tuesday", "Tue", "tue", "tuesday" });
//}
//bool is_wed(std::string s) {
//	return is_x_day(s, { "Wednesday", "Wed", "wed", "wednesday" });
//}
//bool is_thu(std::string s) {
//	return is_x_day(s, { "Thursday", "Thu", "thu", "thursday" });
//}
//bool is_fri(std::string s) {
//	return is_x_day(s, { "Friday", "Fri", "fri", "friday" });
//}
//bool is_sat(std::string s) {
//	return is_x_day(s, { "Saturday", "Sat", "sat", "saturday" });
//}
//bool is_sun(std::string s) {
//	return is_x_day(s, { "Sunday", "Sun", "sun", "sunday" });
//}


