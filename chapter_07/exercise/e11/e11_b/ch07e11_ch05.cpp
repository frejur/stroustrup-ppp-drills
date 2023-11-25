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
// Activity Logger
//
// A program that allows users to track the time they spent on a specific task
// or activity over the course of a week. It provides an interface for
// inputting time logs and generating a summary of the logged time.
//
// Users specify the name of the task or activity they want to track at the
// beginning of the program.
//
// Users can then enter time logs on a line-by-line basis. Each time log
// consists of the day of the week followed by the duration of time spent on
// expressed in hours, minutes, and seconds (See the grammar below for more
// details).
//
// When requested, the program prints out:
// - Additional instructions and hints.
// - A list of the days-of-the-week as defined by the program.
// - A summary of the total time logged for each day of the week.
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
//		[HELP]'\n'
//		[HINT]'\n'
//		[WEEK]'\n'
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
const std::string HELP{ "help" };
const std::string HINT{ "hint" };
const std::string WEEK{ "week" };

const std::string UNIT_HOURS{ "h" };
const std::string UNIT_MINUTES{ "m" };
const std::string UNIT_SECONDS{ "s" };

constexpr char TOKEN_QUIT{ 'Q' };
constexpr char TOKEN_PRINT{ 'P' };
constexpr char TOKEN_HELP{ 'H' };
constexpr char TOKEN_HINT{ '!' };
constexpr char TOKEN_WEEK{ 'W' };
constexpr char TOKEN_DAY{ 'D' };
constexpr char TOKEN_NUMBER{ '#' };
constexpr char TOKEN_HOURS{ 'h' };
constexpr char TOKEN_MINUTES{ 'm' };
constexpr char TOKEN_SECONDS{ 's' };

constexpr int DAY_MINUTES{ 24 * 60};
constexpr int DAY_SECONDS{ DAY_MINUTES * 60 };
constexpr int HOUR_SECONDS{ 3600 };

// These keywords may not be used as shorthands for days-of-the-week
const vector<std::string> RESERVED_WORDS{
	QUIT, PRINT, HELP, HINT, WEEK, UNIT_HOURS, UNIT_MINUTES, UNIT_SECONDS
};

//------------------------------------------------------------------------------
// "Hacks" TODO: Replace all of these with something proper.

// Convert string / char into lowercase
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

// Trim spaces
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
class HMS_duration {
public:
	HMS_duration() : hours(0), minutes(0), seconds(0) {};
	HMS_duration(double h, double m, double s)
	: hours(h), minutes(m), seconds(s) {};
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
	HMS_duration as_units();
private:
	double sum;
	double max;
};

class Activity_record {
public:
	std::string day;
	HMS_duration hms;
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

HMS_duration Duration::as_units() {
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
	Activity_log() : is_init(false) {};
	bool has_been_initialized() { return is_init; };
	void init(
		std::string activity,
		vector<Day_of_the_week> days,
		vector<std::string> reserved_words
	);
	void add_record(Activity_record record);
	int day_index(std::string day) { return week.search(day); };

	// returns the sum of all the logged time for a given day
	double sum_of_day(int day_idx);
	HMS_duration unit_sum_of_day(int day_idx);

	std::string activity() { return act; };
	std::string name_of_day(int day_idx) { return week.name_of_day(day_idx); };
private:
	bool is_init;
	std::string act;
	vector<std::string> reserved; // list of reserved words
	Week week;
	vector<Duration> sums;
	void update_sum(int day_idx, double h, double m, double s);
};

void Activity_log::init(
	std::string a,
	vector<Day_of_the_week> days,
	vector<std::string> reserved_words
) {
	act = a;
	if (days.size() != 7) {
		error("Failed to specify all seven days of the week");
	}
	reserved = reserved_words;
	week = Week{ };
	for (Day_of_the_week d : days) {
		for (std::string w : reserved) {
			if (d.search_str == w) {
				error(
					"Reserved word '" + w + "' may not be used as a short-hand "
					"for a day-of-the-week"
				);
			}
		}
		week.add_day(d);
	}

	// init. vector of seven 24 hour durations
	Duration d{};
	d.init(DAY_SECONDS);
	sums = { d, d, d, d, d, d, d };

	is_init = true;
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

void Activity_log::add_record(Activity_record record)
{
	try {
		int day_idx{ week.search(record.day) };
		if (day_idx == -1) {
			error("Invalid day-of-the-week");
		}
		update_sum(
			day_idx,
			record.hms.hours, record.hms.minutes, record.hms.seconds
		);
	}
	catch(std::exception& e) {
		error(e.what());
	}
	catch(...) {
		error("Unknown error evaluating sum");
	}
}

double Activity_log::sum_of_day(int day_idx) {
	return sums.at(day_idx).total();
}

HMS_duration Activity_log::unit_sum_of_day(int day_idx) {
	return sums.at(day_idx).as_units();
}

Activity_log al{}; // Global instance

//------------------------------------------------------------------------------
// These functions are used to provide a more user-friendly interface:
// Instructions, feedback, output formatted data...

void print_intro()
{
	std::cout
		<< "Activity Logger (Days-of-the-week revisited)"
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
	std::cout
		<< "Hints:" << '\n'
		<< TXT_LAZY << '\n' << '\n'
		<< TXT_TIME << '\n'
		<< '\n';
}

void print_week() {
	std::cout << "Here's the full list of the days-of-the-week:" << '\n';
	for (int i = 0; i < 7; ++i) {
		if (i > 0) {
			std::cout << ", ";
		}
		std::cout << al.name_of_day(i);
	}
	std::cout << '\n' << '\n';
}

void print_commands() {
	std::cout
		<< "'" << HELP << "' '" << HINT << "' '" << WEEK
		<< "' '" << PRINT << "' '" << QUIT << "'";
}

void print_more_help_for_log() {
	std::string TXT_EXAMPLE{ al.name_of_day(0) + " 1h 20m 30s" };
	std::cout
		<< "Logs are entered one at a time."
		<< '\n' << '\n'
		<< "First enter the day-of-the-week." << '\n'
		<< "(Type '" << WEEK << "' to list the days defined by the program)"
		<< '\n' << '\n'
		<< "Then, on the same line, state the duration of time spent," << '\n'
		<< "expressed in hours, minutes and seconds."
		<< '\n' << '\n'
		<< "Example input: '" << TXT_EXAMPLE << '\''
		<< '\n' << '\n'
		<< "Other available commands: " << '\n';
		print_commands();
	std::cout << "\n";
}

void print_help_for_log() {
	std::cout
		<< "Please specify the day-of-the-week and the time spent." << '\n'
		<< "(Type '" << HELP << "' for more info)" <<'\n';
}

void print_continue()
{
	std::cout
		<< '\n'
		<< "Please submit another entry, or type '" << QUIT << "'" << '\n';
}

void print_success(Activity_record record) {
	int day_idx{ al.day_index(record.day) };
	std::string day{ al.name_of_day(day_idx) };
	HMS_duration d{ al.unit_sum_of_day(day_idx) };
	std::cout
		<< day << " was updated successfully." << '\n'
		<< "  New total: " << '\t'
		<< d.hours << "h " << d.minutes << "m " << d.seconds << "s"
		<<  '\n';
}

void print_summary() {
	std::cout
		<< "Summary of last week" << '\n'
		<< "Activity: '" << al.activity() << "'" << '\n';
	for (int i = 0; i < 7; ++i) {
		HMS_duration d{ al.unit_sum_of_day(i) };
		std::cout
			<< "  " << d.hours << "h " << d.minutes << "m " << d.seconds << "s"
			<< '\t' << " on "
			<< al.name_of_day(i)
			<<  '\n';
	}
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
	try {
		al.init(
			trim(get_activity()),
			{
				{ "Monday", "mo" }, { "Tuesday", "tu" }, { "Wednesday", "we" },
				{ "Thursday", "th" }, { "Friday", "fr" },
				{ "Saturday", "sa" }, { "Sunday", "su" }
			},
			RESERVED_WORDS
		);
	}
	catch (std::exception& e) {
		std::cerr << "Error initiliazing Activity_log: " << e.what() << '\n';
		return;
	}
	catch (...) {
		std::cerr << "Unknown error initializing Activity_log" << '\n';
		return;
	}
}

//------------------------------------------------------------------------------
// Parses user input and represents them as Tokens

class Token
{
public:
	char kind;
	double value;
	std::string day; // day-of-the-week

	Token(char k) : kind(k), value(0) {};
	Token(char k, double v) : kind(k), value(v) {};
	Token(char k, std::string d) : kind(k), value(0), day(d) {};
};

class Token_stream
{
public:
	Token_stream() : buffer(0), buffer_is_full(false) {};
	Token get();
	void ignore();

	bool next_is_eol();

	void putback(Token t);
	void putback_eol(Token t); // Only if token == '\n'
	Token get_buffer();
private:
	Token buffer;
	bool buffer_is_full;
};

void Token_stream::ignore() {
	if (buffer_is_full && get_buffer().kind == '\n') {
		return;
	}
	char c{};
	while (std::cin.get(c)) {
		 if (c == '\n') return;
	}
}

void Token_stream::putback(Token t) {
	if (buffer_is_full) {
		error("Cannot put back Token into full buffer");
	}
	buffer = t;
	buffer_is_full = true;
}

void Token_stream::putback_eol(Token t) {
	if (t.kind == '\n') {
		putback(t);
	}
}

Token Token_stream::get_buffer() {
	if (!buffer_is_full) {
		error("Cannot retrieve Token from empty buffer");
	}
	buffer_is_full = false;
	return buffer;
}

Token Token_stream::get() {
	if (buffer_is_full) {
		return get_buffer();
	}

	char c{};

	// Get next non-whitespace or linebreak
	while (std::cin.get(c) && isspace(c)) {
		if (c == '\n') {
			return { '\n' }; // EOL
		}
	}

	if (isalpha(c)) {
		std::string s{};
		std::cin.putback(c);
		std::cin >> s;

		if (s == QUIT) {
			return { TOKEN_QUIT };
		}
		else
		if (s == PRINT) {
			return { TOKEN_PRINT };
		}
		else
		if (s == HELP) {
			return { TOKEN_HELP };
		}
		else
		if (s == HINT) {
			return { TOKEN_HINT };
		}
		else
		if (s == WEEK) {
			return { TOKEN_WEEK };
		}
		else
		if (s == UNIT_HOURS) {
			return { TOKEN_HOURS };
		}
		else
		if (s == UNIT_MINUTES) {
			return { TOKEN_MINUTES };
		}
		else
		if (s == UNIT_SECONDS) {
			return { TOKEN_SECONDS };
		}
		else {
			return { TOKEN_DAY, s };
		}
	}
	else
	if (isdigit(c)) {
		double val{};
		std::cin.putback(c);
		std::cin >> val;
		return { TOKEN_NUMBER, val };
	}
	else {
		error("Bad token");
	}

	return 0;
}

bool Token_stream::next_is_eol() {
	Token t{ get() };
	putback(t);
	return t.kind == '\n';
}

Token_stream ts{}; // Global intance of Token_stream

//------------------------------------------------------------------------------

Activity_record parse_activity_record();
HMS_duration parse_duration();
double parse_number();
char parse_time_unit();
double hours();
double minutes();
double seconds();

//------------------------------------------------------------------------------
// Parses Tokens

Activity_record parse_activity_record() {
	Token t{ ts.get() };
	HMS_duration hms{};
	if (t.kind == TOKEN_DAY ) {
		hms = parse_duration();
	}
	else {
		ts.putback_eol(t);
		error("Expected day-of-the-week string");
	}
	return { t.day, hms };
}

char parse_time_unit() {
	Token t{ ts.get() };
	if (t.kind != TOKEN_HOURS
	    && t.kind != TOKEN_MINUTES
	    && t.kind != TOKEN_SECONDS)
	{
		ts.putback_eol(t);
		error("Expected a unit of time");
	}
	return t.kind;
}

HMS_duration parse_duration() {
	HMS_duration hms{};

	// Hours, minutes or seconds
	double a_val{ parse_number() };
	char a_unit{ parse_time_unit() };
	bool has_minutes{ false };

	if (a_unit == TOKEN_SECONDS) {
		hms.seconds = a_val;
		return hms;
	}
	else
	if (a_unit == TOKEN_MINUTES) {
		hms.minutes = a_val;
		has_minutes = true;
	}
	else {
		hms.hours = a_val;
	}

	if (ts.next_is_eol()) {
		return hms;
	}

	// Minutes or seconds
	double b_val{ parse_number() };
	char b_unit{ parse_time_unit() };

	if (b_unit == TOKEN_SECONDS) {
		hms.seconds = b_val;
	}
	else
	if (b_unit == TOKEN_MINUTES && !has_minutes) {
		hms.minutes = b_val;
	}
	else {
		error("Invalid sequence of time units");
	}

	if (ts.next_is_eol()) {
		return hms;
	}

	// Seconds
	double c_val{ parse_number() };
	char c_unit{ parse_time_unit() };

	if (c_unit == TOKEN_SECONDS) {
		hms.seconds = c_val;
	}
	else {
		error("Expected seconds");
	}

	return hms;
}

double parse_number() {
	Token t{ ts.get() };
	if (t.kind != TOKEN_NUMBER) {
		ts.putback_eol(t);
		error("Expected number");
	}
	return t.value;
}

//------------------------------------------------------------------------------

// Listens for user input and commands
void log_time()
{
	while (std::cin)
	try {
		Activity_record rec{};
		std::cout << PROMPT << ' ';
		Token t{ ts.get() };

		if (t.kind != TOKEN_QUIT && t.kind != TOKEN_PRINT
		    && t.kind != TOKEN_HELP && t.kind != TOKEN_HINT
		    && t.kind != TOKEN_WEEK) {
			ts.putback(t);
			rec = parse_activity_record();
		}

		Token t2{ ts.get() };
		if (t2.kind != '\n') {
			error("Expected end of command");
		}

		if (t.kind == TOKEN_QUIT) {
			return;
		}
		else
		if (t.kind == TOKEN_PRINT) {
			print_summary();
			continue;
		}
		else
		if (t.kind == TOKEN_HELP) {
			print_more_help_for_log();
			continue;
		}
		else
		if (t.kind == TOKEN_HINT) {
			print_hints();
			continue;
		}
		else
		if (t.kind == TOKEN_WEEK) {
			print_week();
			continue;
		}
		else {
			try {
				al.add_record(rec);
			}
			catch (std::exception& e) {
				ts.putback('\n'); // prevent ignore() hang-ups
				error(e.what());
			}
			catch (...) {
				ts.putback('\n');
				error("Unknown error");
			}

			print_success(rec);
			print_continue();
		}

	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
		ts.ignore();
	}
	catch (...) {
		std::cout << "Unknown error" << '\n';
		ts.ignore();
	}
}

//------------------------------------------------------------------------------
int main()
{
	print_intro();

	print_help_for_activity();
	init_log();

	if (!al.has_been_initialized()) {
		return 1;
	}

	print_help_for_log();
	log_time();

	print_outro();

	keep_window_open();
	return 0;
}
