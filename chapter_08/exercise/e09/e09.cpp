#include "../../lib/std_lib_facilities.h"

// Chapter 8, Exercise 9. Price-weight values.
//                        The sum of the combined products of two vectors.

// Prompt for pairs of numbers: Price and weight. Store in two separate vectors.
// Write a function that calculates the "index" of the two vectors:
//   Calculate price * weight for each pair.
//   Return the sum of the combined result of the above.

void clear_buffer() {
	char c{};
	while(std::cin.get(c) && c != '\n') {}
}

class Price_weight_pairs
{
public:
	const vector<double>& prices() { return p; };
	const vector<double>& weights() { return w; };
	vector<double> p{};
	vector<double> w{};
};

bool should_finish() {
	std::cout
	<< "WARNING: The current entry is missing a weight value."
	<< '\n'
	<< "Would you still like to finish? (y/n)" << '\n';
	bool is_y{ false };
	char c{};
	while (std::cin >> c) {
		if (c == 'y') {
			is_y = true;
			break;
		} else if (c == 'n') {
			break;
		}
	}
	return is_y;
}

Price_weight_pairs get_price_weight() {
	Price_weight_pairs pw{};
	std::cout << "Enter pairs of prices and weights, finish with ';'" << '\n';

	char c{};
	double price{}, weight{};
	while (std::cin >> c)
	try {
		bool is_neg{ false };
		if (pw.p.size() > 0 && c == ';') {
			if (pw.w.size() < pw.p.size()) {
				if (!should_finish()) {
					std::cout << "Okay, then please continue..." << '\n';
					continue; // resume input
				}
			}
			break;
		}

		while (c == '-') {
			std::cin >> c;
			is_neg = true;
		}

		if (isdigit(c)) {
			std::cin.putback(c);
			if (pw.p.size() == pw.w.size()) {
				std::cin >> price;
				price *= is_neg ? -1 : 1;
				pw.p.push_back(price);
			} else {
				std::cin >> weight;
				if (is_neg) {
					error("Weight cannot be negative");
				}
				pw.w.push_back(weight);
				std::cout
					<< "Added " << "( " << price << ", "
					<< weight << " )" << '\n';
			}
		} else {
			error("Invalid input");
		}
	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what() << '\n';
		clear_buffer();
	}
	catch (...) {
		error("Unknown error");
	}

	std::cout
		<< (pw.p.size() + pw.w.size()) * 0.5 <<	" entries were registered."
		<< '\n';
	return pw;
}

// print vectors, assumes both are the same size
void print(
	const std::string& label,
	const vector<double>& a,
	const vector<double>& b)
{
	std::cout << label << ':' << '\n';
	for (int i = 0; i < a.size(); ++i) {
		std::cout << "  " << a.at(i) << '\t' << '\t' << b.at(i)
		<< '\n';
	}
	std::cout << '\n';
}

// Calculate the sum of all products
double index(const vector<double>& a, const vector<double>& b) {
	if (a.size() * b.size() == 0) {
		error("Empty vectors");
	}
	if (a.size() != b.size()) {
		error("Vector size mismatch");
	}
	double index{ 0 };
	for (int i = 0; i < a.size(); ++i) {
		index += a[i] * b[i];
	}
	return index;
}

// Retries once with truncated a if index() fails
double price_weight_index(vector<double>& a, const vector<double>& b) {
	double idx{};
	int tries{ 0 };
	while (tries <= 2)
	try {
		++tries;
		idx = index(a, b);
		break;
	}
	catch (std::exception& e) {
		if (b.size() > 0 && a.size() == b.size() + 1) {
			std::cerr << "Error: " << e.what() << '\n';
			std::cerr << "Removing last element and retrying..." << '\n';
			a.pop_back();
			continue;
		} else {
			error(e.what());
		}
	}
	catch (...) {
		error("Unknown Error");
	}
	return idx;
}

std::string label_w_note(const int pre_count, const int post_count) {
	return (
		"Entries" +
		std::string(
	    	(pre_count == post_count + 1)
	    	? " (Note that one entry has been discarded)"
	    	: ""
	    )
	);
}

int main()
try
{
	std::cout
		<< "Price-weight pairs (The sum of 2 vectors multiplied)"
		<< '\n';

	Price_weight_pairs pw{ get_price_weight() };

	int price_count_before{ narrow_cast<int>(pw.p.size()) };
	double idx { price_weight_index(pw.p, pw.w) };
	int price_count_after{ narrow_cast<int>(pw.p.size()) };

	std::cout << '\n'
		<< "The index is: " << idx << '\n' << '\n';

	print(label_w_note(price_count_before, price_count_after),
	      pw.p,
	      pw.w);

	std::cout << "Goodbye!" << '\n';
	keep_window_open();
	return 0;
}
catch (std::exception e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
