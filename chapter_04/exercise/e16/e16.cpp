#include "../../lib/std_lib_facilities.h"

// Exercise 16. Calculate the mode of a sequence of numbers.

vector<float> mode_from_sorted(vector<float> sorted_v) {
	int min_freq{};
	int max_freq{};
	int cur_freq{ 0 };
	bool first_freq_already_found{ false };
	vector<float> unique_v;
	vector<int> freq_v;
	vector<float> mode_v;
	for (int i = 0; i < sorted_v.size(); ++i) {
		++cur_freq;
		if (i == (sorted_v.size() - 1) || sorted_v[i] != sorted_v[i + 1]) {
			if (!first_freq_already_found) {
				min_freq = cur_freq;
				max_freq = cur_freq;
				first_freq_already_found = true;
			} else {
				min_freq = std::min(min_freq,  cur_freq);
				max_freq = std::max(max_freq, cur_freq);
			}
			unique_v.push_back(sorted_v[i]);
			freq_v.push_back(cur_freq);
			cur_freq = 0;
		}
	}

	int unique_count{ static_cast<int>(unique_v.size()) };
	if (unique_count != freq_v.size()) {
		std::ostringstream e;
		e << "Mode operation could not find the same no. of unique values "
			<< "as the no. of frequencies";
		throw std::runtime_error(e.str());
	}

	if (min_freq == max_freq) {
		return {};
	}
	for (int i = 0; i < unique_count; ++i) {
		if (freq_v[i] == max_freq) {
			mode_v.push_back(unique_v[i]);
		}
	}

	return mode_v;
}

// Forward declare
bool validate_string_float(std::string s);
std::string get_unit(std::string s);
bool validate_string_float(std::string s);
float conv_to_meters(float val, std::string u);
std::string get_size_text(int val, int smallest, int largest);

//------------------------------------------------------------------------------
int main()
{
	constexpr char exit_symbol { '|' };	// Character used to exit the program
	std::string inp_string;				// Store the input as a std::string
	double num;							// Convert above std::string to a number
	double smallest, largest;			// Store the smallest and largest so far

	bool graceful;	// Graceful exit flag, triggered by the exit symbol
	bool evaluate;	// Only evaluate expression when this flag is true

	float value_in_m; // value in meters
	float sum = 0;
	int count = 0;

	vector<float> recorded_values;

	std::cout << "Please enter a series of measurements "
		<< "(One per line) to record their value in meters. " << '\n'
		<< "Each measurement needs to have a valid two letter unit. "
		<< "(The available units are 'm', 'cm', 'ft' and 'in')" << '\n'
		<< "When you are finished, type '|' to summarize the values and "
		<< "exit the program." << '\n';

	while (true) {
		std::string unit;
		std::cout << '>';
		std::getline(std::cin, inp_string);
		if (inp_string.size() == 0) continue; // skip empty line

		evaluate = true;
		graceful = false;

		if (inp_string.back() == exit_symbol) {
			graceful = true;
			inp_string.resize(inp_string.size() - 1); // strip exit symbol
		}

		try {
		unit = get_unit(inp_string);
		} catch (...) {
			std::cout << "Invalid input, ";
			break;
		}

		if (evaluate) {
			inp_string.resize(inp_string.size() - unit.size()); // strip unit

			if (inp_string.size() > 1 && inp_string.back() == ' ') {
				// one whitespace allowed, strip it if present
				inp_string.resize(inp_string.size() - 1);
			}

			if (!validate_string_float(inp_string)) {
				continue; // skip invalid input
			}

			try {
				num = stod(inp_string);
			} catch (...) {
				std::cout << "Invalid input, ";
				break;
			}

			value_in_m = conv_to_meters(num, unit);

			std::cout
				<< num << ' ' << unit << "\t=\t" << value_in_m << " meters\n";

			if (count == 0) {
				smallest = value_in_m; // initilialize min max
				largest = value_in_m;
			}
			else {
				std::cout
					<< get_size_text(value_in_m, smallest, largest) << '\n';
				if (value_in_m < smallest) {
					smallest = value_in_m;
				} else if (value_in_m > largest) {
					largest = value_in_m;
				}
			}

			// count, add to vector, sum up
			sum += value_in_m;
			count++;
			recorded_values.push_back(value_in_m);
			sort(recorded_values.begin(), recorded_values.end());
			std::cout << "\n";
		}
		if (graceful) {
			break;
		}
	}
	std::cout << "Goodbye!\n\n";
	std::cout << "Here are all the recorded values:\n";
	sort(recorded_values.begin(), recorded_values.end());
	for (float val : recorded_values) {
		std::cout << val << '\n';
	}
	std::cout << "----------------\n";
	std::cout << count << " values with the Total Sum of: " << sum << '\n';

	vector<float> mode_v { mode_from_sorted(recorded_values) };
	int mode_count { static_cast<int>(mode_v.size()) };
	if (mode_count > 0) {
		std::cout << "The mode" << ((mode_count > 1) ? "s are" : " is")
			<< ": " << '\t';
	} else {
		std::cout
			<< "The mode can't be calculated for this seq. of numbers" << '\n';
	}
	for (int i = 0; i < mode_count; ++i) {
		std::cout << mode_v[i];
		if (i < (mode_count - 1)) {
			std::cout << ", ";
		}
	}
	std::cout << '\n';

	keep_window_open();

	return 0;
}
//------------------------------------------------------------------------------
std::string get_size_text(int val, int smallest, int largest) {
	if (val < smallest) {
		return "That is the smallest value so far.";
	}
	if (val == smallest) {
		return "That is on par with the smallest value recorded.";
	}
	if (val > largest) {
		return "That is the largest value so far.";
	}
	return "That is on par with the largest value recorded.";
}

std::string get_unit(std::string s) {
	std::string ss;
	if (s.length() == 2) ss += s.back();
	else ss = s.substr(s.length() - 2);

	if (ss.size() == 2) {
		std::string sback, sfront;
		sback += ss.back(); sfront += ss.front();
		if (validate_string_float(sfront)) ss = sback;
	}

	if (ss == "m"  || ss == "cm" ||
		ss == "ft" || ss == "in") {
		return ss;
	}
	else if (ss == " m") return "m";
	else throw std::invalid_argument("Invalid unit");

}

bool validate_string_float(std::string s) {

	for (std::string::size_type i = 0; i < s.size(); i++) {
		switch (s[i]) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case '.':
			break;
		default:
			return false;
		}
	}
	return true;
}

float conv_to_meters(float val, std::string u) {
	constexpr float cm_f{ 0.01 };
	constexpr float in_f{ 0.0254 };
	constexpr float ft_f{ in_f * 12 };

	if (u == "m") return val;
	else if (u == "cm") return cm_f * val;
	else if (u == "in") return in_f * val;
	else if (u == "ft") return ft_f * val;
	else throw std::invalid_argument("Invalid unit");
}
