#include "calc.h"
#include "../help/help.h"
#include <cmath>

namespace {
using std::string;
using std::vector;
using EC = calc::Error_code;
} // namespace

//------------------------------------------------------------------------------
// CH07E09
int calc::hextodec(std::string hex)
{
	double dec{0};
	bool error = false;
	for (int i = 0; i < hex.size(); ++i) {
		if (!help::isvalidch(hex.at(i))) {
			error = true;
			break;
		}

		int char_int{hex.at(i) - '0'};
		if (0 <= char_int && char_int <= 9) {
			dec += (char_int * pow(16, (hex.size() - i - 1)));
		} else if (('a' - '0') <= char_int && char_int <= ('f' - '0')) {
			char_int = char_int - ('a' - '0') + 10;
			dec += (char_int * pow(16, (hex.size() - i - 1)));
		} else if (('A' - '0') <= char_int && char_int <= ('F' - '0')) {
			char_int = char_int - ('A' - '0') + 10;
			dec += (char_int * pow(16, (hex.size() - i - 1)));
		} else {
			error = true;
			break;
		}
	}
	if (error) {
		calc_error(EC::Hex_invalid, "Invalid hex character");
	}
	return help::narrow_cast<int>(dec);
}
//------------------------------------------------------------------------------

std::ostream& calc::operator<<(std::ostream& os, const Result& r)
{
	if (r.type == Result_type::Floating_point_value) {
		os << r.val_dec;
	} else if (r.type == Result_type::Integer_value) {
		os << r.val_int;
	}
	return os;
}

bool calc::operator==(const Result& a, const Result& b)
{
	return a.as_floating_point() == b.as_floating_point();
}
bool calc::operator!=(const Result& a, const Result& b)
{
	return !(a == b);
}
bool calc::operator==(const Result& a, double b)
{
	return a.as_floating_point() == b;
}
bool calc::operator!=(const Result& a, double b)
{
	return !(a == b);
}

bool calc::operator<(const Result& a, double b)
{
	return a.as_floating_point() < b;
}

bool calc::operator<=(const Result& a, double b)
{
	return (a < b) && (a == b);
}

bool calc::operator>=(const Result& a, double b)
{
	return (a > b) && (a == b);
}

bool calc::operator>(const Result& a, double b)
{
	return a.as_floating_point() > b;
}
calc::Result calc::operator*(const Result& a, const Result& b)
{
	return {Result_type::Floating_point_value,
	        a.as_floating_point() * b.as_floating_point()};
}
calc::Result calc::operator/(const Result& a, const Result& b)
{
	return {Result_type::Floating_point_value,
	        a.as_floating_point() / b.as_floating_point()};
}
calc::Result calc::operator%(const Result& a, const Result& b)
{
	try {
		return {a.type,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            % help::narrow_cast<int>(b.as_floating_point()))};
	} catch (...) {
		calc_error(EC::Modulus_on_floating_point,
		           "Cannot perform modulus on floating-point values");
	}
	return {};
}
calc::Result calc::operator*(const Result& a, int b)
{
	if (a.type != Result_type::Floating_point_value) {
		return {a.type, help::narrow_cast<int>(a.as_floating_point() * b)};
	}
	return {a.type, a.as_floating_point() * b};
}

calc::Result calc::operator*(int a, const Result& b)
{
	return b * a;
}
calc::Result calc::operator+(const Result& a, const Result& b)
{
	return {Result_type::Floating_point_value,
	        a.as_floating_point() + b.as_floating_point()};
}

calc::Result calc::operator-(const Result& a, const Result& b)
{
	return {Result_type::Floating_point_value,
	        a.as_floating_point() - b.as_floating_point()};
}

//------------------------------------------------------------------------------
// CH07E03, Symbol_table

double calc::Symbol_table_decimal::get(string name)
{
	// attempts to find Variable s and return its value
	for (const Variable_decimal& v : var_table)
		if (v.name == name)
			return v.value;
	calc_error(EC::Get_undefined, "Unable to get undefined variable: " + name);
	return 0;
}


void calc::Symbol_table_decimal::set(string name, double val)
{
	if (count_assignments > 500) {
		calc_error(EC::Too_many_assignments,
		           "Cannot assign to variable, limit reached");
	}
	// attempts to find variable s and set its value to d
	for (Variable_decimal& v : var_table)
		if (v.name == name) {
			if (v.is_const) {
				calc_error(EC::Reassign_constant, "Cannot reassign a constant");
			}
			v.value = val;
			++count_assignments;
			return;
		}
	calc_error(EC::Assign_to_undefined,
	           "Unable to assign value to undefined variable ");
}

bool calc::Symbol_table_decimal::is_declared(string name)
{
	for (const Variable_decimal& v : var_table) {
		if (v.name == name) {
			return true;
		}
	}
	return false;
}

double calc::Symbol_table_decimal::declare(string name,
                                           double val,
                                           bool is_const)
{
	if (var_table.size() > 100) {
		calc_error(EC::Too_many_variables,
		           "Could not declare variable, limit reached");
	}
	if (is_declared(name))
		calc_error(EC::Redeclaration, "'" + name + "' declared twice");
	var_table.push_back(Variable_decimal{name, val, is_const});
	return val;
}
//------------------------------------------------------------------------------

calc::Token_stream::Token_stream()
    : full(false)
    , buffer(0)
{}

void calc::Token_stream::putback(Token t)
{
	if (full)
		calc_error(EC::Buffer_full, "buffer is full");
	buffer = t; full = true;
}

calc::Token calc::Token_stream::getBuffer()
{
	full = false;
	return buffer;
}
//------------------------------------------------------------------------------

void calc::Token_stream::ignore(std::istream& istr)
{
	// check buffer for char
	if (full && getBuffer().kind == '\n') {
		return;
	}
	char ch = 0;
	while (ch != '\n') {
		istr.get(ch);
	}
}

void calc::clean_up_mess(Token_stream& ts, std::istream& istr)
{
	ts.ignore(istr);
}

char calc::Token_stream::skipto_break_nonws(std::istream& istr)
{
	char ch{' '};
	while (istr && (help::isspace(ch) && ch != '\n')) {
		istr.get(ch);
	}
	return ch;
}
//------------------------------------------------------------------------------

calc::Token calc::Token_stream::peek(std::istream& istr)
{
	return get(istr, true);
}

calc::Token calc::Token_stream::get(std::istream& istr, bool peek)
{
	if (full) {
		Token t = getBuffer();
		if (peek) {
			putback(t);
		}
		return t;
	}
	char ch{};
	ch = skipto_break_nonws(istr);

	// check for hexadecimal prefix CH07E09
	if (ch == hex_prefix().at(0)) {
		char ch2{};
		istr.get(ch2);
		if (ch2 == hex_prefix().at(1)) {
			std::string s{ "" };
			char ch3{ };
			while (istr.get(ch3) && help::isalnum(ch3)) {
				s += ch3;
			}
			istr.putback(ch3);
			if (s.size() == 0) {
				calc_error(EC::Hex_incomplete, "Incomplete Hexadecimal number");
			}

			return Token(hex_token, {Result_type::Integer_value, hextodec(s)});
		}
		istr.putback(ch2);
		// istr.putback(ch);
	}

	switch (ch) {
	case '\n':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ',':
	case assign:
		if (peek) {
			istr.putback(ch);
		}
		return Token(ch); // characters represent themselves
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		istr.putback(ch); // put digit back into input stream
		double val_dbl;   // CH07E10
		istr >> val_dbl;

		if (peek) {
			for (char c : std::to_string(val_dbl)) {
				istr.putback(c);
			}
		}
		return Token(number, {Result_type::Floating_point_value, val_dbl});
		break;
	}
	default:
		if (help::isalpha(ch) || ch == declkey.front()) {
			// || ch == quit_key.front()) {
			string s;
			s += ch;

			// read through istr, feed alphanumeric chars into string
			// CH07E01: add underscore to list of valid characters
			while (istr.get(ch)
			       && (help::isalpha(ch) || help::isdigit(ch) || ch == '_')) {
				s += ch;
			}

			if (peek) {
				for (char c : s) {
					istr.putback(c);
				}
			}

			istr.putback(ch); // put non-alphanumeric back into std::cin

			// if (s == quit_key) {
			// 	return Token(quit_token);
			// }

			// if (s == help_key) {
			// 	return Token(help_token);
			// }

			if (s == declkey) {
				return Token(let);
			}

			if (s == constkey) { // CH07E03
				return Token(const_token);
			}

			if (s == sqrt_word()) {
				return Token(sqrt_token);
			}

			if (s == pow_word()) {
				return Token(pow_token);
			}
			if (islower(s.front())) {
				return Token{name, s};
			}
		}
		calc_error(EC::Token_bad, "Bad token");
		break;
	}
	return 0;
}

//------------------------------------------------------------------------------

std::vector<string> calc::line_to_expressions(std::istream& is)
{
	std::vector<std::string> expressions;

	char c{};
	int count_chars = 0;
	bool prev_char_is_print = false;
	bool prev_char_is_wspace = false;
	bool exp_too_long = false;
	std::string e;
	while (is.get(c)) {
		++count_chars;
		if (count_chars > expression_char_limit
		    || expressions.size() > expression_count_limit) {
			exp_too_long = true;
			break;
		}

		if (c == '\n') {
			if (!prev_char_is_print) {
				if (e.size() > 0) {
					expressions.push_back(e);
				}
				e = "";
				prev_char_is_print = true;
				prev_char_is_wspace = false;
			}
			if (c == '\n') {
				break;
			}
			continue;
		}

		if (help::isspace(c)) {
			if (prev_char_is_wspace || e.size() == 0) {
				continue;
			}
			prev_char_is_wspace = true;
		} else {
			prev_char_is_wspace = false;
		}

		e += c;
		prev_char_is_print = false;
	}
	if (exp_too_long) {
		calc_error(
		    EC::Expression_too_long,
		    "Expression too long or too many chained expressions, please "
		    "split up into multiple lines");
	}
	return expressions;
}

//------------------------------------------------------------------------------

calc::Result calc::statement(Token_stream& ts, std::istream& istr)
{
	Token t = ts.get(istr);
	switch (t.kind) {
	case let:
	case const_token:
		ts.putback(t); // CH07E03
		return declaration(ts, istr);
		break;
	case name: {
		// CH07E02 Redefine if 'name' is followed by 'assignment' token
		Token t_peek = ts.peek(istr); // peek ahead
		if (t_peek.kind == assign) {
			ts.putback(t);
			return redefinition(ts, istr);
		}
	}
	default:
		ts.putback(t);
		Result r = expression(ts, istr);
		return r;
		break;
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::redefinition(Token_stream& ts, std::istream& istr)
{
	// after detecting statement w. a name followed by the assignment operator

	Token t{ts.get(istr)};
	if (t.kind != name) {
		ts.putback(t);
		calc_error(EC::Name_expected_in_redefinition,
		           "Expected name in redefinition");
	}

	Token t2{ts.get(istr)};
	if (t2.kind != assign) {
		ts.putback(t2);
		calc_error(EC::Assignment_operator_expected_in_redefinition,
		           "Expected assigment operator in redefinition");
	}

	Result d = expression(ts, istr);
	ts.set(t.name, d);
	return d;
}

// CH0703, modififed declaration() to handle both constants and regular vars
calc::Result calc::declaration(Token_stream& ts, std::istream& istr)
{
	// after detecting statement w. the declaration or constant keyword
	Token t = ts.get(istr);
	if (t.kind != let && t.kind != const_token) {
		ts.putback(t);
		calc_error(EC::Declaration_or_constant_token_expected,
		           "Expected a declaration or constant token");
	}
	bool is_const{(t.kind == const_token)};
	Token t2 = ts.get(istr);
	if (t2.kind != name) {
		ts.putback(t2);
		calc_error(EC::Name_expected_in_declaration,
		           "name expected in declaration");
	}
	Token t3 = ts.get(istr);
	if (t3.kind != '=') {
		ts.putback(t3);
		calc_error(EC::Assignment_operator_expected_in_declaration,
		           "= missing in declaration of '" + t.name + "'");
	}

	Result d = expression(ts, istr);

	ts.declare(t2.name, d, is_const);
	return d;
}

//------------------------------------------------------------------------------

calc::Result calc::expression(Token_stream& ts,
                              std::istream& istr,
                              char expected_closing_char)
{
	Result left = term(ts, istr);

	Token t = ts.get(istr); // get next token
	while (true) {
		switch (t.kind) {
		case '+': // addition
			left = left + term(ts, istr);
			t = ts.get(istr);
			break;
		case '-': // subtraction
			left = left - term(ts, istr);
			t = ts.get(istr);
			break;
		default:
			if (t.kind == expected_closing_char) {
				ts.putback(t.kind);
				return left;
			}
			calc_error(EC::Token_bad, "Illegal closing character");
		}
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::term(Token_stream& ts, std::istream& istr)
{
	Result left{primary(ts, istr)};
	Token t = ts.get(istr); // get next token

	while (true) {
		switch (t.kind) {
		case '*': // multiply
			left = left * primary(ts, istr);
			t = ts.get(istr);
			break;
		case '/': // division
		{
			Result prim = primary(ts, istr);
			if (prim == 0)
				calc_error(EC::Divide_by_zero, "Divide by zero");
			left = left / prim;
			t = ts.get(istr);
			break;
		}
		case '%': // modulo
		{
			Result mod = primary(ts, istr);
			if (mod == 0)
				calc_error(EC::Modulo_divide_by_zero, "% Divide by zero");
			left = left % mod;
			t = ts.get(istr);
			break;
		}
		case assign: // CH07E02, assignment not allowed as part of an expression
			calc_error(
			    EC::Assignment_operator_invalid_context,
			    "The assignment operator cannot be used in this context. "
			    "Variables may only be redefined as separate statements.");
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::primary(Token_stream& ts, std::istream& istr)
{
	Token t = ts.get(istr);
	switch (t.kind) {
	case '(': // expression
	{
		Result exp = expression(ts, istr, ')');
		t = ts.get(istr);
		if (t.kind != ')') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_expression_end,
			           "expected ')'");
		}
		return exp;
	}
	case sqrt_token: // square root
	{
		t = ts.get(istr);
		if (t.kind != '(') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_square_root_start,
			           "expected '(' after square root keyword");
		}
		Result exp = expression(ts, istr, ')');
		if (exp < 0)
			calc_error(EC::Square_root_of_negative_value,
			           "cannot calculate square root of a negative number");
		t = ts.get(istr);
		if (t.kind != ')') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_square_root_end,
			           "expected ')' after square root expression");
		}
		double sqrt_val{sqrt(exp.as_floating_point())};
		Result_type type{exp.type};
		if (type == Result_type::Floating_point_value) {
			return {type, sqrt_val};
		} else {
			return {type, help::narrow_cast<int>(sqrt_val)};
		}
	}
	case pow_token: // power of
	{
		t = ts.get(istr);
		if (t.kind != '(') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_power_of_start,
			           "expected '(' after power of keyword");
		}
		Result expr = expression(ts, istr, ',');
		t = ts.get(istr);
		if (t.kind != ',') {
			ts.putback(t);
			calc_error(EC::Comma_expected_after_power_of_base,
			           "expected ',' after expression");
		}

		Result expo = expression(ts, istr, ')');
		t = ts.get(istr);
		if (t.kind != ')') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_power_of_end,
			           "expected ')' after exponent");
		}
		double pow_val = 0;
		double expr_val = expr.as_floating_point();
		double expo_val = expo.as_floating_point();
		Result_type type_return{Result_type::Floating_point_value};
		pow_val = pow(expr_val, expo_val);
		return {type_return, pow_val};
	}
	case number: // number
		return t.result;
	case hex_token: // CH07E09
		return t.result;
	case '-':
		return -1 * primary(ts, istr);
	case '+':
		return primary(ts, istr);
	case name:
		return ts.get(t.name);
	default:
		ts.putback(t);
		calc_error(EC::Primary_expected, "expected Primary");
	}
	return {};
}

//------------------------------------------------------------------------------

void calc::print_instructions(std::ostream& os)
{
	os << "The following arithmetic operators are available: " << '\n'
	   << "    "
	   << "'-', '+', '/', '*' ,'%'" << '\n'
	   << "Use parentheses for grouping.\n"
	   << "Declare / define variables using:" << '\n'
	   << "    '" << declkey << " name " << assign << " value'" << '\n'
	   << "    '" << constkey << " name " << assign << " value'"
	   << " (immutable variable)" << '\n'
	   << "    'name " << assign << " value'"
	   << " (reassign value to existing)" << '\n'
	   << "Available functions:" << '\n';
	for (const string& fn : available_fn()) {
		os << "    " << fn << '\n';
	}
}

void calc::print_greeting(std::ostream& os)
{
	os << "Calculator\n"
	   << "Please enter expressions using floating-point numbers, " << '\n'
	   << "finish with <Enter>.\n"
	   << "(!) Use the '" << hex_prefix() << "' prefix to define numbers using "
	   << '\n'
	   << "    hexadecimal notation. e.g. '0xFF' equals '255'" << '\n';
	// << "(!) Write '" << quit_key << "' to exit"
	// << " or '" << help_key << "' for more info." << '\n';
}
