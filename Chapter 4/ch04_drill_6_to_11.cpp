#include "std_lib_facilities.h"

namespace ch04_drill_6_to_11
{
	bool validate_string_float(string s);

	string get_unit(string s) {
		string ss;
		if (s.length() == 2) ss += s.back();
		else ss = s.substr(s.length() - 2);

		if (ss.size() == 2) {
			string sback, sfront;
			sback += ss.back(); sfront += ss.front();
			if (validate_string_float(sfront)) ss = sback;
		}

		if (ss == "m"  || ss == "cm" ||
			ss == "ft" || ss == "in") {
			return ss;
		}
		else if (ss == " m") return "m";
		else throw invalid_argument("Invalid unit");
		
	}

	bool validate_string_float(string s) {

		for (string::size_type i = 0; i < s.size(); i++) {
			switch (s[i]) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case '.':
				break;
			default:
				return false;
			}
		}
	}

	float conv_to_meters(float val, string u) {
		constexpr float cm_f{ 0.01 };
		constexpr float in_f{ 0.0254 };
		constexpr float ft_f{ in_f * 12 };

		if (u == "m") return val;
		else if (u == "cm") return cm_f * val;
		else if (u == "in") return in_f * val;
		else if (u == "ft") return ft_f * val;
		else throw invalid_argument("Invalid unit");
	}

	int main()
	{
		const string exit_symbol{ '|' };	// Character the user can input to terminate the program
		string inp_string;					// Store the input as a string
		double num;							// Convert above string to a number
		double smallest, largest;			// Store the smallest and largest so far

		string txt_smallest   = "That is the smallest value so far.";
		string txt_also_small = "That is on par with the smallest value recorded.";
		string txt_largest    = "That is the largest value so far.";
		string txt_also_large = "That is on par with the largest value recorded.";

		bool graceful;	// Graceful exit flag, triggered by the exit symbol
		bool evaluate;	// Only evaluate expression when this flag is true

		float value_in_m; // value in meters
		float sum = 0;
		int count = 0;

		vector<float> recorded_values;

		while (true) {
			string end_char;
			string unit;

			cout << '>';

			getline(cin, inp_string);

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
					cout << "Invalid input, ";
					break;
				}

				value_in_m = conv_to_meters(num, unit);

				cout << num << ' ' << unit << "\t=\t" << value_in_m << " meters\n";

				if (count == 0) {
					smallest = value_in_m; // initilialize min max
					largest = value_in_m;
				}
				else {
					if (value_in_m == smallest) cout << txt_also_small << '\n';
					else if (value_in_m == largest) cout << txt_also_large << '\n';
					else if (value_in_m < smallest) {
						cout << txt_smallest << '\n';
						smallest = value_in_m;
					}
					else if (value_in_m > largest) {
						cout << txt_largest << '\n';
						largest = value_in_m;
					}
				}

				// count, add to vector, sum up
				sum += value_in_m; 
				count++;
				recorded_values.push_back(value_in_m);
				cout << "end \n";
			}
			if (graceful) {
				cout << "Graceful ";
				break;
			}
		}
		cout << "Goodbye!\n\n";
		cout << "Here are all the recorded values:\n";
		sort(recorded_values.begin(), recorded_values.end());
		for (float val : recorded_values) {
			cout << val << '\n';
		}
		cout << "----------------\n";
		cout << count << " values with the Total Sum of: " << sum << '\n';


		return 0;
	}
}