#include "../../../lib/std_lib_facilities.h"

// Exercise 11a.	Revisit exercise 21 from chapter 4: Name-value pairs.
//					~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//					This exercise was already "revisited" in Chapter 06,
//					where the two vectors of names and values where merged
//					into a single vector of user-defined type 'Name_value'.
//					This can be further expanded upon by having a class
//					called High_score that contains the same vector, along
//					with a couple of useful member functions.
//------------------------------------------------------------------------------
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
// A very simple High Score tracker.
//
// Features:
// - Add high scores. ('Name( name name...) number')
// - Search for scores by name or value. ('number', or '"name"')
// - Print the High Score table sorted by value. (See constant 'PRINT')
//
// The user may NOT add an entry with a name that is already "on record".
//
// A Name may only contain alphanumericals, and hyphens (See below).
// It may consist of a series of words separated by spaces, but the very first
// character must always be a letter.
// Hyphens are also allowed, but only in the middle of a word, NOT as a single
// character or as the first or last character of a word.
//
// Numbers are defined using decimal / integer notation and may only contain
// digits and a '.' as the decimal separator. An initial '-' may also be used
// to indicate a negative number.
//
// Numbers are stored as <double>'s.
//
//------------------------------------------------------------------------------

class Score
{
public:
	std::string name;
	double value;
};
//------------------------------------------------------------------------------
// Manages all Score entries of the High Score table.

class High_score
{
public:
	void add(std::string n, double v);
	Score search(std::string n);
	vector<Score> search(double v);
	vector<Score> sorted();
private:
	vector<Score> scores;
	bool name_is_unique(std::string n);
};

High_score hs{};
//------------------------------------------------------------------------------

void High_score::add(std::string n, double v) {
	if (!name_is_unique(n)) {
		error("Cannot add score, an entry with that name already exists");
	}
	scores.push_back({ n, v });
};

// Find entries by name
Score High_score::search(std::string n) {
	for (Score s : scores) {
		if (s.name == n) {
			return s;
		}
	}
 	return {};
 };

// Find entries by score value
vector<Score> High_score::search(double v) {
	vector<Score> matches{ };
	for (Score s : scores) {
		if (s.value == v) {
			matches.push_back(s);
		}
	}
	return matches;
};

bool High_score::name_is_unique(std::string n) {
	if (scores.size() == 0) {
		return true;
	}
	for (Score s : scores) {
		if (s.name == n) {
			return false;
		}
	}
	return true;
};

// Returns scores sorted by descending value
vector<Score> High_score::sorted() {
	vector<int> idx_v{};
	for (int i = 0; i < scores.size(); ++i) {
		idx_v.push_back(i);
	}
	// bubble sort, TODO: implement something better
	int n = scores.size();
	bool swapped{ true };
	while (swapped) {
		swapped = false;
		for (int j = 1; j < n; ++j) {
			if (scores.at(idx_v.at(j - 1)).value
			    < scores.at(idx_v.at(j)).value
			){
				int temp{ idx_v.at(j - 1) };
				idx_v.at(j - 1) = idx_v.at(j);
				idx_v.at(j) = temp;
				swapped = true;
			}
		}
	}
	vector<Score> sorted{ };
	for (int k = 0; k < scores.size(); ++k) {
		sorted.push_back(scores.at(idx_v.at(k)));
	}
	return sorted;
};
//------------------------------------------------------------------------------

constexpr char PROMPT{ '>' };
const std::string PRINT{ "print" }; // user input to trigger print_high_score()

//------------------------------------------------------------------------------
// These functions are used to provide a more user-friendly interface:
// Instructions, feedback, output formatted data...

void print_intro()
{
	std::cout
		<< "  H I G H   S C O R E    (Name-value pairs revisited)" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n'
		<< "Please enter a name followed by a number (delimiter = ' ')." << '\n'
		<< '\n'
		<< "The name must start with a letter, and may only contain" << '\n'
		<< "alphanumerics, spaces and hyphens."
		<< '\n' << '\n';
}

void print_help()
{
	static const std::string TXT_SEARCH_BY_NAME {
		"+ You can search for entries by entering a name surrounded w. quotes."
	};
	static const std::string TXT_SEARCH_BY_SCORE {
		"+ You can also search for past entries by entering a score value."
	};
	static const std::string TXT_VIEW_ALL {
		"+ Or just type '" + PRINT + "' to print the full High Scores table."
	};
	std::cout
		<< TXT_SEARCH_BY_NAME << '\n'
		<< TXT_SEARCH_BY_SCORE << '\n'
		<< TXT_VIEW_ALL << '\n'
		<< '\n';
}

void print_continue()
{
	std::cout
		<< "Please submit another entry, or press <ENTER>"
		<< "to finish." << '\n';
	print_help();
}

void print_score(Score s) {
	std::cout
		<< '\t' << s.value << '\t' << '\t' << '"' << s.name << '"' << '\n';
}

void print_scores(vector<Score> score_v) {
	for (Score s : score_v) {
		print_score(s);
	}
}

void print_high_score()
{
	std::cout << "High Score:" << '\n';
	print_scores(hs.sorted());
}

void print_outro()
{
	std::cout << "Goodbye!" << '\n' << '\n';
	print_high_score();
}
//------------------------------------------------------------------------------
// Gets the user's input as a vector of strings

vector<std::string> get_commands()
{
	char c{};
	std::string cmd{ "" };
	vector<std::string> cmd_v{ };
	bool eol{ false };
	while (!eol && std::cin.get(c)) {
		if (isspace(c)) {
			if (cmd.size() > 0) {
				cmd_v.push_back(cmd);
				cmd = "";
			}
			if (c == '\n') {
				eol = true;
			}
		} else {
			cmd += c;
		}
	}
	return cmd_v;
}
//------------------------------------------------------------------------------
// Check for valid names (Rules described at the top)

bool is_valid_name(std::string name) {
	if (name == "") {
		error("Name cannot be an empty string");
	}
	if (name.front() == '-' || name.back() == '-') {
		return false;
	}
	for (char c : name) {
		if (!isalnum(c) && c != '-') {
			return false;
		}
	}
	return true;
}

bool is_valid_first_name(std::string name) {
	return (
		name != PRINT &&
		isalpha(name.front()) &&
		(name.size() == 1 || is_valid_name(name))
	);
}
//------------------------------------------------------------------------------
// Cleans up the vector of 'commands' from quotation marks that are used to
// encapsulate the overall search string.

vector<std::string> drop_quotes(vector<std::string> name_v) {
	name_v.front() = name_v.front().substr(1, name_v.front().size() - 1);
	if (name_v.front().size() == 0) {
		error("Expected a character after '\"'");
	}
	if (name_v.back().back() != '"') {
		error("Expected '\"' to terminate search string");
	}
	name_v.back().pop_back();
	if (name_v.back() == "") {
		name_v.pop_back();
	}
	return name_v;
}
//------------------------------------------------------------------------------
// Validates the names and joins them with spaces.

std::string join_names(vector<std::string> name_v) {
	std::string final_name{ "" };
	bool found_valid_first_name{ false };
	for (std::string name : name_v) {
		if  (!found_valid_first_name) {
			if (!(found_valid_first_name = is_valid_first_name(name))) {
				error("Invalid first name");
			}
			final_name += name;
		} else {
			if (!is_valid_name(name)) {
				error("Invalid name");
			}
			final_name += " ";
			final_name += name;
		}
	}
	return final_name;
}
//------------------------------------------------------------------------------
// Check for valid number (Rules described at the top)

bool is_valid_number(std::string number) {
	if (number.front() == '-') {
		if (number.size() == 1) {
			return false;
		}
		number = number.substr(1, number.size()-1);
	}
	bool has_dot{ false };
	for (char c : number) {
		if (c == '.') {
			if (has_dot) {
				return false;
			}
			has_dot = true;
		} else if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}
//------------------------------------------------------------------------------
// String (User input) to number

double str_to_num(std::string num_str) {
	if (!is_valid_number(num_str)) {
		error("Invalid number format");
	}
	return std::stod(num_str);
}

double cmds_to_num(vector<std::string> cmd_v) {
	// Needed to allow: "- <number>" (Note whitespace)
	double num{};
	if (cmd_v.size() == 1) {
		num = str_to_num(cmd_v.front());
	} else if (cmd_v.size() == 2 && cmd_v.front() == "-") {
		num = str_to_num(cmd_v.front() + cmd_v.back());
	} else {
		error("Expected a single number in integer or decimal notation");
	}
	return num;
}
//------------------------------------------------------------------------------
// The main actions that the user can have the program perform.

void print_by_score(vector<std::string> cmd_v) {
	double score{ cmds_to_num(cmd_v) };
	vector<Score> same_score_v{ hs.search(score) };
	if (same_score_v.size() == 0) {
		std::cout
			<< "No entries with a score value of: " << score << " were found."
			<< '\n';
	} else {
		std::cout << "The following entries have a score value "
			<< "of " << score << ":" << '\n';
		print_scores(same_score_v);
	}
}

void print_by_name(vector<std::string> name_v) {
	name_v = drop_quotes(name_v);
	std::string name{ join_names(name_v) };
	Score score_same_name{ hs.search(name) };
	if (score_same_name.name == name) {
		std::cout
			<< "An entry for the name \"" << name << "\" was found: " << '\n';
		print_score(score_same_name);
	} else {
		std::cout
			<< "No entries found for the name \"" << name << "\"." << '\n';
	}
}

void add_score(vector<std::string> cmd_v) {
	double score{};
	if (cmd_v.size() < 2) {
		error("Too few arguments, expected at least a name and a number");
	} else if ((cmd_v.size() > 2) && (cmd_v.at(cmd_v.size() - 2) == "-")) {
		// '- <number>' (Note whitespace)
		score = cmds_to_num({ cmd_v.at(cmd_v.size()-2), cmd_v.back() });
		cmd_v.pop_back();
		cmd_v.pop_back();
	} else {
		score = cmds_to_num({ cmd_v.back() });
		cmd_v.pop_back();
	}
	std::string name{ join_names(cmd_v) };
	hs.add(name, score);
	std::cout << "Added score: " << score << ", \"" << name << '"' << '\n';
}
//------------------------------------------------------------------------------
// Determine the type of input and perform the appropriate action.

void query_scores()
{
	while (std::cin)
	try {
		std::cout << PROMPT << ' ';
		vector<std::string> cmd_v{ };
		cmd_v = get_commands();

		if (cmd_v.size() == 0) {
			break; // exit program
		}

		if (cmd_v.size() == 1 && cmd_v.front() == PRINT) {
			print_high_score();
			continue;
		}

		char first_c{ cmd_v.front().front() };
		if (first_c == '-' || isdigit(first_c)) {
			print_by_score(cmd_v);
		} else if (first_c == '"') {
			print_by_name(cmd_v);
		} else if (isalpha(first_c)) {
			add_score(cmd_v);
		} else {
			error("Invalid command, expected either a '\"', a number or a "
			      "letter.");
		}
		print_continue();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "exception" << ' ' << '\n';
	}
}
//------------------------------------------------------------------------------

void add_predefined_scores() {
	hs.add("Amira Dickerson-Clarke", 1490.123);
	hs.add("Flynn Baxter", 0);
	hs.add("Lara Huff Jr", 30.856);
	hs.add("FINN 89", 460);
	hs.add("Vienna Avocado", 0);
	hs.add("PJ Loves Sally", 0);
	hs.add("Friedman 2k", 1580.804);
	hs.add("Darwin Carr", 1300.251);
	hs.add("Rowan J", -99999);
	hs.add("Calum Romero", 3890.823);
	hs.add("Elizabeth Maynard-Reeves", 60.301);
	hs.add("L4ndry C0sta", 420.386);
	hs.add("ROBIN WAS HERE", 2730.986);
	hs.add("icanhazcheeseburger", 3320.168);
	hs.add("berkley gentry", 1710.836);
}
//------------------------------------------------------------------------------

int main()
{
	print_intro();
	print_help();

	add_predefined_scores();

	query_scores();

	print_outro();

	keep_window_open();
	return 0;
}

