#include "csv_parser.h"
#include <algorithm>
#include <fstream>
#include <sstream>

std::istream& operator>>(std::istream& is, CSV_value& val)
{
	char c;
	is >> c;
	if (!is) {
		return is; // Note: Also catches manually cleared eofbit
	}

	if (c == ',') {
		val.value = "";
		return is;
	}

	bool open_quote{c == '"'};
	std::string name = (open_quote) ? "" : std::string{c};
	while (is) {
		is.get(c);
		if (is.eof()) {
			break;
		}
		if (c == '"') {
			if (open_quote) {
				if ((is >> c) && ((c != ',') && !is.eof())) {
					is.clear(std::ios_base::badbit);
				} else {
					val.value = name;
				}
			} else {
				is.clear(std::ios_base::badbit);
			}
			return is;
		}
		if (c == ',' && !open_quote) {
			val.value = name;
			return is;
		}
		name += c;
	}

	if (open_quote) {
		is.clear(std::ios_base::badbit);
	} else {
		if (is.eof()) {
			is.clear(); // Manually clears eofbit to signal success
		}
		val.value = name;
	}

	return is;
}

CSV_parser::CSV_parser(const std::string& filename)
    : fname(filename)
{
	std::ifstream ifs{filename};
	if (!ifs) {
		throw std::runtime_error("Cannot open file '" + filename + "'");
	}
	std::string ln;
	std::istringstream iss;
	std::getline(ifs, ln);
	iss.str(ln);
	CSV_value hdr;
	while (iss >> hdr) {
		cols.push_back(hdr.value);
	}
	if (cols.size() == 0) {
		throw std::runtime_error("Could not parse any header values");
	}
}

void CSV_parser::perform_action_on(
    std::initializer_list<const std::string> column_names,
    std::function<void(CSV_value_vector)> action)
{
	if (column_names.size() == 0) {
		throw std::runtime_error("No column names specififed");
	}

	std::vector<int> hdr_idx_v;
	for (const std::string& n : column_names) {
		hdr_idx_v.push_back(col_idx(n));
	}
	std::sort(hdr_idx_v.begin(), hdr_idx_v.end());

	std::ifstream ifs{fname};
	if (!ifs) {
		throw std::runtime_error("Cannot open file '" + fname + "'");
	}

	std::string dummy;
	std::getline(ifs, dummy); // discard first line = headers
	if (!ifs) {
		throw std::runtime_error("File contains no values");
	}

	int count_ln = 0;
	std::istringstream iss;
	while (ifs) {
		values.clear();
		std::string ln;
		std::getline(ifs, ln);
		iss.str(ln);
		CSV_value val;
		int hdr_count = 0;
		int hdr_idx = hdr_idx_v[hdr_count];
		int val_idx = 0;
		while (val_idx <= hdr_idx_v.back() && iss >> val) {
			if (val_idx == hdr_idx) {
				values.push_back(cols[hdr_idx], val.value);
				++hdr_count;
				if (hdr_count < hdr_idx_v.size()) {
					hdr_idx = hdr_idx_v[hdr_count];
				} else {
					break;
				}
			}
			++val_idx;
		}

		if (values.size() == 0) {
			continue;
		}

		if (values.size() < hdr_idx_v.size()) {
			throw std::runtime_error(
			    "At line " + std::to_string(count_ln) + ": Could not parse "
			    + std::to_string(hdr_idx_v.size()) + " values, only found "
			    + std::to_string(values.size()) + " values");
		}
		action(values);
		++count_ln;
	}
}

void CSV_value_vector::push_back(const std::string& col_name,
                                 const std::string& value)
{
	cols.push_back(col_name);
	vals.push_back(value);
}

int CSV_value_vector::as_int(const std::string& col_name) const
{
	std::istringstream iss;
	std::string val = vals[col_idx(col_name)];
	if (val.size() == 0) {
		return 0;
	}
	iss.str(val);
	int n = 0;
	if (!(iss >> n)) {
		throw std::runtime_error("Could not convert to int");
	}
	return n;
}

double CSV_value_vector::as_double(const std::string& col_name) const
{
	std::istringstream iss;
	std::string val = vals[col_idx(col_name)];
	if (val.size() == 0) {
		return 0;
	}
	iss.str(val);
	double n = 0;
	if (!(iss >> n)) {
		throw std::runtime_error("Could not convert to double");
	}
	return n;
}

int CSV_value_vector::col_idx(const std::string& hdr) const
{
	int match = -1;
	for (int i = 0; i < cols.size(); ++i) {
		if (cols[i] == hdr) {
			match = i;
		}
	}
	if (match == -1) {
		throw std::runtime_error("Could not find a column header by that name");
	}
	return match;
}

int CSV_parser::col_idx(const std::string& hdr) const
{
	int match = -1;
	for (int i = 0; i < cols.size(); ++i) {
		if (cols[i] == hdr) {
			match = i;
		}
	}
	if (match == -1) {
		throw std::runtime_error("Could not find a column header by that name");
	}
	return match;
}
