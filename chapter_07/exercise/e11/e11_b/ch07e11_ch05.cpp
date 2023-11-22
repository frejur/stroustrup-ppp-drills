#include "../../lib/std_lib_facilities.h"

// Exercise 14, Values grouped by day-of-the-week.

// The user inputs a sequence of name-value pairs:
// (<string> day-of-the-week, <int>)
// The values are grouped by name, there are multiple accepted variations of
// the same day, e.g. "Monday", "monday", "mon".
// Ignore any names not recognized.
// Print:
// 	1. The sum of each group.
// 	2. The number of rejected values.

// Addition: exit the program and write out values by entering "print".

const std::string EXIT_WORD{ "print" };

// forward declare helpers
bool is_mon(std::string s); bool is_tue(std::string s);
bool is_wed(std::string s); bool is_thu(std::string s);
bool is_fri(std::string s); bool is_sat(std::string s);
bool is_sun(std::string s); bool is_x_day(std::string, vector<std::string> v);

int s_to_day_idx(std::string s) {
	// returns 0 - 6 (Monday - Sunday) on success
	// returns -1 on failure
	int i{ -1 };
	if (is_mon(s)) {
		i = 0;
	} else if (is_tue(s)) {
		i = 1;
	} else if (is_wed(s)) {
		i = 2;
	} else if (is_thu(s)) {
		i = 3;
	} else if (is_fri(s)) {
		i = 4;
	} else if (is_sat(s)) {
		i = 5;
	} else if (is_sun(s)) {
		i = 6;
	}
	return i;
}

void print_sum_ints(std::string name, vector<int> v) {
	if (v.size() == 0) {
		std::cout << name << ':' << '\t' << '-' << '\n';
		return;
	}
	double sum { 0 };
	for (int i : v) {
		sum = (double)narrow_cast<int>(sum + i);
	}
	std::cout << name << ':' << '\t' << (int)sum << '\n';
}



int main()
try {
	std::cout
		<< "The sum of values grouped by day-of-the-week." << '\n' << '\n'
		<< "Please enter a day-of-the-week and a value (integer) " << '\n'
		<< "associated with that day:"
		<< '\n' << '\n';

	vector<int> mon_v{}, tue_v{}, wed_v{}, thu_v{}, fri_v{}, sat_v{}, sun_v{};
	int count_accepted{ 0 };
	int count_rejected{ 0 };

	std::string day{};
	int val{};
	while (day != EXIT_WORD) {
		// name
		if (day.size() == 0) {
			if (!(std::cin >> day)) {
				error("Invalid input, expected a name");
			}
			continue; // move on to value
		}

		// value
		if (!(std::cin >> val)) {
			error("Invalid input, expected an integer");
		}
		int day_idx{ s_to_day_idx(day) };
		if (day_idx == -1) {
			++count_rejected;
			day = "";
			continue; //ignore
		}

		// add entry
		switch (day_idx) {
		case 0:
			mon_v.push_back(val);
			break;
		case 1:
			tue_v.push_back(val);
			break;
		case 2:
			wed_v.push_back(val);
			break;
		case 3:
			thu_v.push_back(val);
			break;
		case 4:
			fri_v.push_back(val);
			break;
		case 5:
			sat_v.push_back(val);
			break;
		case 6:
			sun_v.push_back(val);
			break;
		default:
			error("Invalid day-of-the-week index");
			break;
		}

		std::cout << "Keep adding entries, or enter 'print' to finish." << '\n';
		day = "";
		++count_accepted;
	}
	if (!std::cin) {
		error("Input error, expected a name-value pair.");
	}

	if (count_accepted) {
		std::cout << '\n'
			<< "Printing the sum of values:" << '\n'
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			<< '\n';
		print_sum_ints("MON", mon_v);
		print_sum_ints("TUE", tue_v);
		print_sum_ints("WED", wed_v);
		print_sum_ints("THU", thu_v);
		print_sum_ints("FRI", fri_v);
		print_sum_ints("SAT", sat_v);
		print_sum_ints("SUN", sun_v);
	} else {
		std::cout << "No entries were registered." << '\n';
	}
	if (count_rejected) {
		if (count_rejected == 1) {
			std::cout << "1 value was rejected" << '\n';
		} else {
			std::cout
				<< count_rejected << " value(s) were rejected." << '\n';
		}
	}

	keep_window_open();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}

bool is_x_day(std::string s, vector<std::string> names) {
	if (s.size() == 0) {
		return false;
	}
	for (std::string n : names) {
		if (s == n) {
			return true;
		}
	}
	return false;
}

bool is_mon(std::string s) {
	return is_x_day(s, { "Monday", "Mon", "mon", "monday" });
}
bool is_tue(std::string s) {
	return is_x_day(s, { "Tuesday", "Tue", "tue", "tuesday" });
}
bool is_wed(std::string s) {
	return is_x_day(s, { "Wednesday", "Wed", "wed", "wednesday" });
}
bool is_thu(std::string s) {
	return is_x_day(s, { "Thursday", "Thu", "thu", "thursday" });
}
bool is_fri(std::string s) {
	return is_x_day(s, { "Friday", "Fri", "fri", "friday" });
}
bool is_sat(std::string s) {
	return is_x_day(s, { "Saturday", "Sat", "sat", "saturday" });
}
bool is_sun(std::string s) {
	return is_x_day(s, { "Sunday", "Sun", "sun", "sunday" });
}


