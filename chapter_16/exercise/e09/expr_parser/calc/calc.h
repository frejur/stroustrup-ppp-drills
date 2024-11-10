#ifndef E_CALC_H
#define E_CALC_H
#include "../help/help.h"
#include <iostream>
#include <string>
#include <vector>

namespace calc {

// various tokens with descriptive names
constexpr char prompt{'>'};
constexpr char result_sign{'='};
constexpr char number{'8'};
// constexpr char print{';'};

constexpr char name{'a'};            // variable name token
constexpr char let{'L'};             // declaration token
constexpr char const_token{'C'};     // CH07E03
const std::string declkey{"let"};    // declaration keyword
const std::string constkey{"const"}; // CH07E03
constexpr char assign{'='};          // assignment token

// help
// constexpr char help_token{'h'}; // CH07E06
// const std::string help_key{"help"};

// quitting
// constexpr char quit_token{'q'};
// const std::string quit_key{"quit"};

// squareroot
static const std::string& sqrt_word()
{
	static const std::string s{"sqrt"};
	return s;
}

constexpr char sqrt_token{'s'};      // token

// power of
static const std::string& pow_word()
{
	static const std::string s{"pow"}; // keyword
	return s;
}

constexpr char pow_token{'p'};     // token

// hexadecimals, CH07E09
static const std::string& hex_prefix()
{
	static const std::string s{"0x"};
	return s;
}
const char hex_token{'X'};

inline const std::vector<std::string>& available_fn()
{
	static const std::vector<std::string> v{sqrt_word(), pow_word()};
	return v;
}

//------------------------------------------------------------------------------

enum class Error_code {
	Unknown = 0,
	// As to not mess up the established order used for testing,
	// add any new error codes at the BOTTOM, AFTER the existing ones.
	Hex_invalid = 1,
	Hex_incomplete,
	Expression_too_long,
	Token_bad,
	Primary_expected,
	Divide_by_zero,
	Get_undefined,
	Assign_to_undefined,
	Reassign_constant,
	Redeclaration,
	Name_expected_in_declaration,
	Assignment_operator_expected_in_declaration,
	Assignment_operator_invalid_context,
	Parentheses_expected_at_expression_end,
	Parentheses_expected_at_square_root_start,
	Parentheses_expected_at_square_root_end,
	Square_root_of_negative_value,
	Parentheses_expected_at_power_of_start,
	Parentheses_expected_at_power_of_end,
	Comma_expected_after_power_of_base,
	Command_not_last_in_chain,
	Quit_while_reading,

	// Integer values only
	Modulo_divide_by_zero,

	// Floating-point values only
	Modulus_on_floating_point,

	// Not part of automated testing
	To_or_from_in_ifstream,
	File_path_expected,
	Write_overflow,
	Read_overflow,
	Integer_overflow,

	// Should normally not be able to be triggered by the user
	Name_expected_in_redefinition,
	Assignment_operator_expected_in_redefinition,
	Declaration_or_constant_token_expected,
	End_of_statement_expected,
	Open_read_file_failure,
	Open_write_file_failure,
	Read_file_bad,
	Write_file_bad,
	Buffer_full,
	Session_parameters_invalid,

	// As to not mess up the established order used for testing,
	// add any new error codes BELOW this line.
	Too_many_variables,
	Too_many_assignments,

	// COUNT -------------------------------------------------------------------
	COUNT // Should always be at the bottom, used to count the # of entries
	// -------------------------------------------------------------------------
};

inline bool error_code_is_valid(int i)
{
	return (1 <= i && i < static_cast<int>(Error_code::COUNT));
}

inline void calc_error(Error_code c,
                       const std::string msg,
                       bool do_not_throw = false)
{
	std::string full_msg{"E_" + help::int_to_string(static_cast<int>(c)) + " : "
	                     + msg};
	if (!do_not_throw) {
		throw std::runtime_error(full_msg);
	}
	std::cerr << full_msg;
}

//------------------------------------------------------------------------------

// file paths, definition in filepaths.cpp
const std::string& file_path_in_decimal();
const std::string& file_path_in_roman();
const std::string& file_path_out_decimal();
const std::string& file_path_out_roman();
const std::string& file_path_test_in_decimal();
const std::string& file_path_test_in_roman();
const std::string& file_path_test_out_decimal();
const std::string& file_path_test_out_roman();
const std::string& file_path_test_cases_decimal();
const std::string& file_path_test_cases_roman();
const std::string& file_path_test_merged_decimal();
const std::string& file_path_test_merged_roman();
const std::string& file_path_fuzz_in_decimal();
const std::string& file_path_fuzz_in_roman();
const std::string& file_path_fuzz_out_decimal();
const std::string& file_path_fuzz_out_roman();

// Expression chaining limits
constexpr int expression_char_limit{100};
constexpr int expression_count_limit{10};
constexpr int read_from_file_char_limit{2048};
constexpr int write_to_file_char_limit{2048};
constexpr int write_to_file_statement_limit{512};

struct Write_quota
{
	int characters = 0;
	int statements = 0;
};

inline const Write_quota& write_to_file_quota()
{
	static Write_quota q{write_to_file_char_limit,
	                     write_to_file_statement_limit};
	return q;
}

//------------------------------------------------------------------------------

enum class Result_type { Floating_point_value, Integer_value };

struct Result
{
	Result(){};
	Result(Result_type t, double v)
	    : type(t)
	{
		if (t == Result_type::Floating_point_value) {
			val_dec = v;
		} else if (t == Result_type::Integer_value) {
			val_int = static_cast<int>(v);
		}
	};
	Result(Result_type t, int v)
	    : Result(t, static_cast<double>(v)){}; // TODO: Find a solution without
	                                           // needless conversion

	double as_floating_point() const
	{
		double val = 0;
		switch (type) {
		case Result_type::Floating_point_value:
			val = val_dec;
			break;
		case Result_type::Integer_value:
			val = static_cast<double>(val_int);
			break;
		}
		return val;
	}
	std::string as_string() const
	{
		std::string s;
		if (type == Result_type::Floating_point_value) {
			s = help::double_to_string(val_dec);
		} else if (type == Result_type::Integer_value) {
			s = help::int_to_string(val_int);
		}
		return s;
	};
	Result_type type = Result_type::Floating_point_value;
	double val_dec = 0;
	int val_int = 0;
};

std::ostream& operator<<(std::ostream& os, const Result& r);
bool operator==(const Result& a, const Result& b);
bool operator!=(const Result& a, const Result& b);
bool operator==(const Result& a, double b);
bool operator!=(const Result& a, double b);
bool operator<(const Result& a, double b);
bool operator<=(const Result& a, double b);
bool operator>=(const Result& a, double b);
bool operator>(const Result& a, double b);
Result operator*(const Result& a, const Result& b);
Result operator/(const Result& a, const Result& b);
Result operator*(const Result& a, int b);
Result operator*(int a, const Result& b);
Result operator+(const Result& a, const Result& b);
Result operator-(const Result& a, const Result& b);
Result operator%(const Result& a, const Result& b);

//------------------------------------------------------------------------------

class Variable_decimal
{
public:
	std::string name;
	double value;
	bool is_const;
};

class Symbol_table_decimal
{
public:
	double get(std::string name);
	void set(std::string name, double val);
	double declare(std::string name, double val, bool is_const);
	bool is_declared(std::string name);

private:
	int count_assignments{0};
	std::vector<Variable_decimal> var_table;
};

//------------------------------------------------------------------------------

class Token
{
public:
	char kind;
	Result result;
	std::string name;
	Token(char ch)
	    : kind(ch){};
	Token(char ch, Result val)
	    : kind(ch)
	    , result(val){};
	Token(char ch, std::string n)
	    : kind(ch)
	    , name(n){};
};

//------------------------------------------------------------------------------

class Token_stream
{
public:
	Token_stream();
	Token get(std::istream& istr, bool peek = false);
	Token peek(std::istream& istr);
	void putback(Token t);        // put back token, put into buffer
	void ignore(std::istream& istr); // discard all up to and including c
	bool buffer_is_full() const { return full; };
	Token getBuffer();
	char skipto_break_nonws(
	    std::istream& istr); // CH07E05, consume whitespace and return '\n'
	                         // or non-whitespace char
	// Symbol table
	Result get(std::string name)
	{
			return {Result_type::Floating_point_value, sym_dec.get(name)};
	}
	void set(std::string name, Result val)
	{
			sym_dec.set(name, val.as_floating_point());
	}
	Result declare(std::string name, Result val, bool is_const)
	{
			double v = 0;
			if (val.type == Result_type::Integer_value) {
				v = static_cast<double>(val.val_int);
			} else {
				v = val.val_dec;
			}
			return {Result_type::Floating_point_value,
			        sym_dec.declare(name, v, is_const)};
	}
	bool is_declared(std::string name);

private:
	bool full;    // full when token in buffer
	Token buffer; // keep tokens that are put back
	Symbol_table_decimal sym_dec;
};

//------------------------------------------------------------------------------

std::vector<std::string> line_to_expressions(std::istream& is);

//------------------------------------------------------------------------------

void print_greeting(std::ostream& os);       // program greeting / info string
void print_instructions(std::ostream& os);
void print_instr_to_from(std::ostream& os);

Result statement(Token_stream& ts, std::istream& istr);
Result declaration(Token_stream& ts, std::istream& istr);
Result redefinition(Token_stream& ts, std::istream& istr);
Result expression(Token_stream& ts,
                  std::istream& istr,
                  char expected_closing_char = '\n');
Result term(Token_stream& ts, std::istream& istr);
Result primary(Token_stream& ts, std::istream& istr);

void clean_up_mess(Token_stream& ts,
                   std::istream& istr); // discard invalid input from stream

int hextodec(std::string hex);

//------------------------------------------------------------------------------

inline void throw_if_not_end(Token_stream& ts, std::istream& is)
{
	Token t{ts.get(is)};
	ts.putback(t);
	if (t.kind != '\n') {
		calc_error(Error_code::End_of_statement_expected,
		           "Bad syntax, expected end of statement");
	}
}

inline void throw_if_mid_of_chain(const std::vector<std::string> expressions,
                                  int i)
{
	if (i != expressions.size() - 1) {
		calc_error(
		    Error_code::Command_not_last_in_chain,
		    "This command must be the last statement of the expression chain");
	}
}

} // namespace calc

#endif // E_CALC_H
