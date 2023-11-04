#include "../../lib/std_lib_facilities.h"

bool validate_string_float(std::string s);

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

int main()
{
	const std::string exit_symbol { '|' };	// Character the user can input to terminate the program
	std::string inp_string;					// Store the input as a std::string
	double num;							// Convert above std::string to a number
	double smallest, largest;			// Store the smallest and largest so far

	const std::string txt_smallest   { "That is the smallest value so far." };
	const std::string txt_also_small { "That is on par with the smallest value recorded." };
	const std::string txt_largest    { "That is the largest value so far." };
	const std::string txt_also_large { "That is on par with the largest value recorded." };

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
		std::string end_char;
		std::string unit;

		std::cout << '>';

		std::getline(std::cin, inp_string);

		if (inp_string.size() == 0) continue; // skip empty line

		end_char += inp_string.back();

		evaluate = true;
		graceful = false;

		if (end_char == exit_symbol) {
			graceful = true;
			inp_string.resize(inp_string.size() - 1); // strip exit symbol
		}

		try {
			unit = get_unit(inp_string);
		}
		catch (...) {
			evaluate = false;
		}

		if (evaluate) {
			inp_string.resize(inp_string.size() - unit.size()); // strip unit

			if (inp_string.size() > 1 && inp_string.back() == ' ') {
				inp_string.resize(inp_string.size() - 1); // one whitespace allowed, strip it if present
			}

			if (!validate_string_float(inp_string)) continue; // skip invalid input

			try {
				num = stod(inp_string);
			}
			catch (...) {
				std::cout << "Invalid input, ";
				break;
			}

			value_in_m = conv_to_meters(num, unit);

			std::cout << num << ' ' << unit << "\t=\t" << value_in_m << " meters\n";

			if (count == 0) {
				smallest = value_in_m; // initilialize min max
				largest = value_in_m;
			}
			else {
				if (value_in_m == smallest) std::cout << txt_also_small << '\n';
				else if (value_in_m == largest) std::cout << txt_also_large << '\n';
				else if (value_in_m < smallest) {
					std::cout << txt_smallest << '\n';
					smallest = value_in_m;
				}
				else if (value_in_m > largest) {
					std::cout << txt_largest << '\n';
					largest = value_in_m;
				}
			}

			// count, add to vector, sum up
			sum += value_in_m;
			count++;
			recorded_values.push_back(value_in_m);
			std::cout << "\n";
		}
		if (graceful) {
			std::cout << "Graceful ";
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

	keep_window_open();

	return 0;
}
