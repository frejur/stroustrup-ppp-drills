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
		os << "Test Case N/A";
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

std::vector<tcal::Test_case> tcal::load_test_cases(const std::string& file_path)
{
	std::vector<Test_case> test_cases;
	std::ifstream is{file_path};

	if (!is) {
		throw std::runtime_error("Could not load file: '" + file_path + "'");
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

void tcal::run_calculator_tests(calc::Calculator_version version)
{
	std::string path_test_cases{(version == calc::Calculator_version::Decimal)
	                                ? calc::file_path_test_cases_decimal()
	                                : calc::file_path_test_cases_roman()};
	std::cout << "Reading from '" << path_test_cases << "'..." << '\n';

	std::vector<Test_case> test_cases{load_test_cases(path_test_cases)};

	int indent_w_test{get_indent_w(test_cases)};

	print_test_cases(std::cout, test_cases, indent_w_test);
	std::cout << '\n';

	std::string path_test_in{(version == calc::Calculator_version::Decimal)
	                             ? calc::file_path_test_in_decimal()
	                             : calc::file_path_test_in_roman()};
	std::cout << "Writing to '" << path_test_in << "'...";
	save_test_input(path_test_in, test_cases);
	std::cout << " Done!" << '\n' << '\n';

	std::string path_test_out{(version == calc::Calculator_version::Decimal)
	                              ? calc::file_path_test_out_decimal()
	                              : calc::file_path_test_out_roman()};
	std::cout << "Creating a new Calculator session." << '\n'
	          << "Reading from: " << '\'' << path_test_in << '\'' << '\n'
	          << "Writing to:   " << '\'' << path_test_out << '\'' << '\n'
	          << "...";
	load_evaluate_and_save_test_expressions(path_test_in, path_test_out);
	std::cout << " Done!" << '\n' << '\n';

	std::string path_test_merged{(version == calc::Calculator_version::Decimal)
	                                 ? calc::file_path_test_merged_decimal()
	                                 : calc::file_path_test_merged_roman()};
	std::cout << "Merging in and out data into one file." << '\n'
	          << "Reading from: " << '\'' << path_test_in << '\'' << '\n'
	          << "And from:     " << '\'' << path_test_out << '\'' << '\n'
	          << "Writing to:   " << '\''
	          << calc::file_path_test_merged_decimal() << '\'' << '\n'
	          << "...";
	merge_and_save_in_and_out_data(path_test_in,
	                               path_test_out,
	                               path_test_merged);
	std::cout << " Done!" << '\n' << '\n';

	std::cout << "Loading merged data as test cases." << '\n'
	          << "Reading from: '" << path_test_merged << "'...";

	std::vector<Test_case> merged_data{load_test_cases(path_test_merged)};

	std::cout << " Done!" << '\n';

	int indent_w_merged{get_indent_w(merged_data)};
	int indent_w_compare = (indent_w_test > indent_w_merged) ? indent_w_test
	                                                         : indent_w_merged;
	print_test_comparison(std::cout, test_cases, merged_data, indent_w_compare);

	std::cout << '\n';
	help::keep_window_open("return to the main program");
}

void tcal::save_test_input(const std::string& file_path,
                           const std::vector<Test_case>& test_cases)
{
	if (test_cases.size() == 0) {
		throw std::runtime_error("No test cases found");
	}
	std::ofstream os{file_path};

	if (!os) {
		throw std::runtime_error("Could not open file '" + file_path
		                         + "' for writing.");
	}

	os.exceptions(os.exceptions() | std::ios_base::badbit);

	for (const Test_case& t : test_cases) {
		os << t.input << '\n';
	}
}

void tcal::load_evaluate_and_save_test_expressions(
    const std::string& file_path_in, const std::string& file_path_out)
{
	calc::Token_stream ts{};
	calc::session(ts,
	              calc::Read_mode::Read_from_file,
	              calc::Write_mode::Write_to_file,
	              file_path_in,
	              file_path_out);
}

std::vector<std::string> tcal::file_to_strings(const std::string& file_path)
{
	std::ifstream is{file_path};

	if (!is) {
		throw std::runtime_error("Could not load file: '" + file_path + "'");
	}
	is.exceptions(is.exceptions() | std::ios_base::badbit);

	std::vector<std::string> strings;
	while (is) {
		std::string s{help::feed_into_string_until_newline(is)};
		strings.push_back(s);
	}
	return strings;
}

void tcal::merge_and_save_in_and_out_data(
    const std::string& file_path_expressions,
    const std::string& file_path_results,
    const std::string& file_path_out)
{
	std::vector<std::string> result_strings{file_to_strings(file_path_results)};

	int max_len = 0;
	for (std::string& s : result_strings) {
		if (s.size() != 0 && s.front() != '=' && s.front() == 'E') {
			int wspace_pos = 1; // assumes whitespace after 'E'
			for (; wspace_pos < s.size(); ++wspace_pos) {
				if (help::isspace(s[wspace_pos])) {
					break;
				}
			}
			if (wspace_pos < (s.size() - 1)) {
				std::string temp{
				    help::extract_ch_from_end(s, s.size() - wspace_pos)};
				s += " " + str_to_error_msg(temp);
			}
		}
		max_len = (max_len < s.size()) ? s.size() : max_len;
	}

	std::vector<std::string> expr_strings{
	    file_to_strings(file_path_expressions)};

	save_string_pairs_to_file(file_path_out,
	                          result_strings,
	                          expr_strings,
	                          max_len);
}

void tcal::save_string_pairs_to_file(const std::string& file_path,
                                     const std::vector<std::string>& a,
                                     const std::vector<std::string>& b,
                                     int indent_w)
{
	int max_count = (a.size() > b.size()) ? a.size() : b.size();
	if (max_count < 1) {
		return;
	}

	std::ofstream os{file_path};

	if (!os) {
		throw std::runtime_error("Could not open file '" + file_path
		                         + "' for writing.");
	}

	os.exceptions(os.exceptions() | std::ios_base::badbit);

	for (int i = 0; i < max_count; ++i) {
		std::string result, expr;
		if (i > (a.size() - 1)) {
			result = "= 0";
		} else {
			result = a[i];
		}
		help::append_spaces(result, indent_w + 2);

		if (i > (b.size() - 1)) {
			expr = "N/A";
		} else {
			expr = b[i];
		}

		os << result << expr << '\n';
	}
}

void tcal::print_test_comparison(std::ostream& os,
                                 std::vector<Test_case>& test_cases,
                                 std::vector<Test_case>& merged_data,
                                 int indent_w)
{
	os << "Comparing the test cases with the merged data:" << '\n' << '\n';

	std::string hdr_col_a{"Expected Outcome / Actual Outcome"};
	std::string hdr_col_b{"Input"};
	help::append_spaces(hdr_col_a, indent_w + 2);
	std::string div;
	help::append_x_ch(div, (hdr_col_a.size() + hdr_col_b.size() + 20), '-');
	os << hdr_col_a << hdr_col_b << '\n' << div << '\n';

	int max_len = (test_cases.size() > merged_data.size()) ? test_cases.size()
	                                                       : merged_data.size();
	int count_success = 0;
	for (int i = 0; i < max_len; ++i) {
		Test_case a, b;
		if (i < test_cases.size()) {
			a = test_cases[i];
		} else {
			a.type = Test_case_type::None;
		}
		a.indent_w = indent_w + 2;

		if (i < merged_data.size()) {
			b = merged_data[i];
		} else {
			b.type = Test_case_type::None;
		}
		b.indent_w = indent_w + 2;

		count_success += ((a == b) ? 1 : 0);
		os << ((a == b) ? "PASSED" : "FAILED") << '\n';
		os << a << '\n';
		os << b << '\n';
		os << div << '\n';
	}
	std::cout << '\n'
	          << count_success << " out of " << max_len
	          << " tests passed successfully!" << '\n';
}
