#ifndef TEST_CALC_H
#define TEST_CALC_H

#include "../calc/calc.h"

namespace tcal {

enum class Test_case_type { None, Result, Error };

inline Test_case_type validate_type(Test_case_type t, Test_case_type expected)
{
	if (t != expected) {
		throw std::runtime_error("Invalid argument");
	};
	return t;
}
struct Test_case
{
	Test_case(){};
	Test_case(Test_case_type t, const std::string& i, calc::Error_code e)
	    : type(validate_type(t, Test_case_type::Error))
	    , input(i)
	    , error_code(e){};
	Test_case(Test_case_type t, const std::string& i, calc::Result r)
	    : type(validate_type(t, Test_case_type::Result))
	    , input(i)
	    , result(r){};
	Test_case_type type = Test_case_type::None;
	std::string input;
	calc::Error_code error_code;
	std::string error_str; // Name of enum or description
	calc::Result result;
	Test_case& operator=(Test_case& t) { return t; };
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
	if (a.type == Test_case_type::Result && a.result != b.result) {
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
	} else if (t.type == Test_case_type::Result) {
		len = 2 + t.result.as_string().size();
	}
	return len;
}

int get_indent_w(const std::vector<Test_case>& test_cases);

void run_decimal_test();
std::vector<Test_case> load_decimal_test_cases();
void print_test_cases(std::ostream& os,
                      std::vector<Test_case>& test_cases,
                      int indent_w);
void save_decimal_test_input(const std::vector<Test_case>& test_cases);

} // namespace tcal

#endif // TEST_CALC_H
