#ifndef TEST_CALC_H
#define TEST_CALC_H

#include "../calc/calc.h"

namespace tcal {

enum class Test_case_type { None, Result_decimal, Result_roman, Error };

char get_selection();
void print_test_or_fuzz();

inline std::string str_to_error_msg(const std::string& s)
{
	std::string e;
	int count = 0;
	bool first_char_found = false;
	bool prev_is_wspace = false;
	for (char c : s) {
		if (count > 64) {
			break;
		}
		if (help::isalnum(c) || c == '=' || c == '(' || c == ')' || c == ',') {
			if (first_char_found && prev_is_wspace) {
				e.push_back('_');
				++count;
			}
			e.push_back(c);
			first_char_found = true;
			prev_is_wspace = false;
			++count;
		} else if (help::isspace(c) && !prev_is_wspace) {
			prev_is_wspace = true;
		}
	}
	if (e.size() == 0) {
		e = "NA";
	}
	return e;
}

inline Test_case_type validate_type(Test_case_type t)
{
	if (t == Test_case_type::None) {
		throw std::runtime_error("Invalid argument");
	};
	return t;
}

inline Test_case_type validate_error_type(Test_case_type t)
{
	t = validate_type(t);
	if (t != Test_case_type::Error) {
		throw std::runtime_error("Invalid argument, expected Error");
	}
	return t;
}

inline Test_case_type validate_result_type(Test_case_type t)
{
	t = validate_type(t);
	if (!(t == Test_case_type::Result_decimal
	      || t == Test_case_type::Result_roman)) {
		throw std::runtime_error("Invalid argument, expected Result");
	}
	return t;
}

struct Test_case
{
	Test_case(){};
	Test_case(Test_case_type t, const std::string& i, calc::Error_code e)
	    : type(validate_error_type(t))
	    , input(i)
	    , error_code(e){};
	Test_case(Test_case_type t, const std::string& i, calc::Result r)
	    : type(validate_result_type(t))
	    , input(i)
	    , result(r){};
	Test_case_type type = Test_case_type::None;
	std::string input;
	calc::Error_code error_code;
	std::string error_str; // Name of enum or description
	calc::Result result;
	int indent_w = 0;
};

void eval_result(std::istream& is, Test_case& t);
void eval_error_code(std::istream& is, Test_case& t);
std::istream& operator>>(std::istream& is, Test_case& t);
std::ostream& operator<<(std::ostream& os, const Test_case& t);

inline bool operator==(Test_case a, Test_case b)
{
	if (a.type == Test_case_type::None || b.type == Test_case_type::None) {
		return false;
	}
	if (a.type != b.type) {
		return false;
	}
	if (a.type == Test_case_type::Error && a.error_code != b.error_code) {
		return false;
	}
	if ((a.type == Test_case_type::Result_decimal
	     || a.type == Test_case_type::Result_decimal)
	    && a.result != b.result) {
		return false;
	}
	return true;
};

inline bool operator!=(Test_case a, Test_case b)
{
	return !(a == b);
};

inline int output_str_len(const Test_case& t)
{
	int len = 0;
	if (t.type == Test_case_type::Error) {
		len = 2 + help::int_to_string(static_cast<int>(t.error_code)).size() + 1
		      + t.error_str.size();
	} else if (t.type == Test_case_type::Result_decimal
	           || t.type == Test_case_type::Result_roman) {
		len = 2 + t.result.as_string().size();
	}
	return len;
}

int get_indent_w(const std::vector<Test_case>& test_cases);

void run_calculator_tests(
    calc::Calculator_version version = calc::Calculator_version::Decimal);
void do_regular_tests(
    calc::Calculator_version version = calc::Calculator_version::Decimal);
void do_fuzz_testing(
    calc::Calculator_version version = calc::Calculator_version::Decimal);
std::vector<Test_case> load_test_cases(const std::string& file_path,
                                       const calc::Calculator_version version);
void print_test_cases(std::ostream& os,
                      std::vector<Test_case>& test_cases,
                      int indent_w);
void save_test_input(const std::string& file_path,
                     const std::vector<Test_case>& test_cases);
void load_evaluate_and_save_test_expressions(const std::string& file_path_in,
                                             const std::string& file_path_out,
                                             calc::Calculator_version version);
void merge_and_save_in_and_out_data(const std::string& file_path_expressions,
                                    const std::string& file_path_results,
                                    const std::string& file_path_out);
std::vector<std::string> file_to_strings(const std::string& file_path);
void save_string_pairs_to_file(const std::string& file_path,
                               const std::vector<std::string>& a,
                               const std::vector<std::string>& b,
                               int indent_w);
void print_test_comparison(std::ostream& os,
                           std::vector<Test_case>& test_cases,
                           std::vector<Test_case>& merged_data,
                           int indent_w);

} // namespace tcal

#endif // TEST_CALC_H
