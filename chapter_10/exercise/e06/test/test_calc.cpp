#include "test_calc.h"
#include "../calc/calc.h"
#include "../help/help.h"

void tcal::eval_result(std::istream& is, Test_case& t)
{
	// TODO: Roman numerals
	double val = 0;
	is >> val;

	if (!is) {
		help::clear_buffer(is);
		return;
	}

	char c = help::skipto_break_nonws(is);
	is.putback(c);

	if (c == '\n') {
		is.clear(std::ios_base::failbit);
		return;
	}

	std::string i{help::feed_into_string_until_newline(is)};
	is.putback('\n');
	if (i.size() == 0) {
		is.clear(std::ios_base::failbit);
		return;
	}

	t.type = Test_case_type::Result;
	t.result = {calc::Result_type::Floating_point_value, val};
	t.input = i;
}

void tcal::eval_error_code(std::istream& is, Test_case& t)
{
	char undsc = 0;
	is.get(undsc);
	if (undsc != '_') {
		is.clear(std::ios_base::failbit);
		return;
	}

	char d = 0;
	is.get(d);
	is.putback(d);
	if (!help::isdigit(d)) {
		is.clear(std::ios_base::failbit);
		return;
	}

	int code = 0;
	is >> code;

	if (!calc::error_code_is_valid(code)) {
		is.clear(std::ios_base::failbit);
		return;
	}

	char c = help::skipto_break_nonws(is);
	is.putback(c);

	if (c == '\n') {
		is.clear(std::ios_base::failbit);
		return;
	}

	std::string enum_name;
	is >> enum_name;

	c = help::skipto_break_nonws(is);
	is.putback(c);

	if (!is) {
		return;
	}

	if (c == '\n') {
		is.putback('\n');
		is.clear(std::ios_base::failbit);
		return;
	}

	std::string i{help::feed_into_string_until_newline(is)};
	if (is) {
		is.putback('\n');
	}
	if (is && i.size() == 0) {
		is.clear(std::ios_base::failbit);
		return;
	}
	if (is.fail() && !is.eof()) {
		return;
	}
	if (is.eof()) {
		is.clear(); // allow EOF instead of newline
	}
	t.type = Test_case_type::Error;
	t.error_code = static_cast<calc::Error_code>(code);
	t.error_str = enum_name;
	t.input = i;
}

std::istream& tcal::operator>>(std::istream& is, Test_case& t)
{
	char c = 0;
	is >> c;

	if (c == '=') {
		eval_result(is, t);
	} else if (c == 'E') {
		eval_error_code(is, t);
	} else if (is) {
		is.putback(c);
		is.clear(std::ios_base::failbit);
	}

	return is;
}

std::ostream& tcal::operator<<(std::ostream& os, const Test_case& t)
{
	std::string output;
	if (t.type == tcal::Test_case_type::None) {
		os << "Incomplete Test Case";
	} else if (t.type == Test_case_type::Error) {
		std::string c{help::int_to_string(static_cast<int>(t.error_code))};
		output = "E_" + c + " " + t.error_str;
	} else if (t.type == tcal::Test_case_type::Result) {
		output = "= " + t.result.as_string();
	} else {
		throw std::runtime_error("Invalid test case type");
	}
	help::append_spaces(output, t.indent_w);
	os << output << t.input;
	return os;
}

std::vector<tcal::Test_case> tcal::load_decimal_test_cases()
{
	std::vector<Test_case> test_cases;
	std::ifstream is{calc::file_path_test_merged_decimal()};

	if (!is) {
		throw std::runtime_error("Could not load file: '"
		                         + calc::file_path_test_merged_decimal() + "'");
	}
	is.exceptions(is.exceptions() | std::ios_base::badbit);

	while (!is.fail()) {
		char c = 0;
		is >> c;
		if (c == '\n') {
			continue;
		}
		if (c == '#') {
			help::clear_buffer(is);
			continue;
		}
		is.putback(c);
		Test_case t{};
		is >> t;
		if (is.fail()) {
			is.clear();
			help::clear_buffer(is);
			continue;
		}
		test_cases.push_back(t);
	}

	return test_cases;
}
void tcal::print_test_cases(std::ostream& os,
                            std::vector<Test_case>& test_cases,
                            int indent_w)
{
	os << "Found the following test cases:" << '\n' << '\n';

	std::string hdr_col_a{"Expected Outcome"};
	std::string hdr_col_b{"Input"};
	help::append_spaces(hdr_col_a, indent_w + 2);
	std::string div;
	help::append_x_ch(div, (hdr_col_a.size() + hdr_col_b.size() + 20), '-');
	os << hdr_col_a << hdr_col_b << '\n' << div << '\n';

	for (Test_case& tc : test_cases) {
		tc.indent_w = indent_w + 2;
		os << tc << '\n';
	}
}
int tcal::get_indent_w(const std::vector<Test_case>& test_cases)
{
	int indent_w = 0;
	for (const Test_case& t : test_cases) {
		int len = output_str_len(t);
		indent_w = (len > indent_w) ? len : indent_w;
	}
	return indent_w;
}

void tcal::run_decimal_test()
{
	std::cout << "Reading from '" << calc::file_path_test_merged_decimal()
	          << "'..." << '\n';

	std::vector<Test_case> test_cases{load_decimal_test_cases()};

	int indent_w{get_indent_w(test_cases)};

	print_test_cases(std::cout, test_cases, indent_w);

	std::cout << "Writing to '" << calc::file_path_test_in_decimal() << "'..."
	          << '\n';
	save_decimal_test_input(test_cases);
}

void tcal::save_decimal_test_input(const std::vector<Test_case>& test_cases)
{
	if (test_cases.size() == 0) {
		throw std::runtime_error("No test cases found");
	}
	std::ofstream os{calc::file_path_test_in_decimal()};

	if (!os) {
		throw std::runtime_error("Could not open file '"
		                         + calc::file_path_test_in_decimal()
		                         + "' for writing.");
	}

	os.exceptions(os.exceptions() | std::ios_base::badbit);

	for (const Test_case& t : test_cases) {
		os << t.input << '\n';
	}
}
