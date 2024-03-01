#include "calc.h"
#include "../help/help.h"
#include "../roman/roman.h"

using std::string;
using std::vector;

//------------------------------------------------------------------------------
// CH07E09
int calc::hextodec(std::string hex)
{
	double dec{0};
	for (int i = 0; i < hex.size(); ++i) {
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
			throw(std::runtime_error("Invalid Hex character"));
		}
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
	} else if (r.type == Result_type::Roman_numeral) {
		os << r.val_rom.as_roman();
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
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            * help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() * b.as_floating_point()};
}
calc::Result calc::operator/(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            / help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() / b.as_floating_point()};
}
calc::Result calc::operator%(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            % help::narrow_cast<int>(b.as_floating_point()))};
	}
	throw std::runtime_error("Cannot perform modulus on floating-point values");
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
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            + help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() + b.as_floating_point()};
}

calc::Result calc::operator-(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            - help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() - b.as_floating_point()};
}

//------------------------------------------------------------------------------
// CH07E03, Symbol_table

romi::Roman_int calc::Symbol_table_roman::get(string name)
{
	// attempts to find Variable s and return its value
	for (const Variable_roman& v : var_table)
		if (v.name == name) return v.value;
	help::error("unable to get undefined variable; ", name);
	return 0;
}

double calc::Symbol_table_decimal::get(string name)
{
	// attempts to find Variable s and return its value
	for (const Variable_decimal& v : var_table)
		if (v.name == name)
			return v.value;
	help::error("unable to get undefined variable; ", name);
	return 0;
}

void calc::Symbol_table_roman::set(string name, romi::Roman_int val)
{
	// attempts to find variable s and set its value to d
	for (Variable_roman& v : var_table)
		if (v.name == name) {
			if (v.is_const) {
				help::error("Cannot reassign a constant"); // CH03E07
			}
			v.value = val;
			return;
		}
	help::error("unable to assign value to undefined variable ", name);
}

void calc::Symbol_table_decimal::set(string name, double val)
{
	// attempts to find variable s and set its value to d
	for (Variable_decimal& v : var_table)
		if (v.name == name) {
			if (v.is_const) {
				help::error("Cannot reassign a constant"); // CH03E07
			}
			v.value = val;
			return;
		}
	help::error("unable to assign value to undefined variable ", name);
}

bool calc::Symbol_table_roman::is_declared(string name)
{
	for (const Variable_roman& v : var_table) {
		if (v.name == name) {
			return true;
		}
	}
	return false;
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

romi::Roman_int calc::Symbol_table_roman::declare(string name,
                                                  romi::Roman_int val,
                                                  bool is_const)
{
	if (is_declared(name))
		help::error(name, " declared twice");
	if (output_trace)
		std::cout << "DEF: adding " << name << " = " << val << '\n';
	var_table.push_back(Variable_roman{name, val, is_const});
	return val;
}

double calc::Symbol_table_decimal::declare(string name,
                                           double val,
                                           bool is_const)
{
	if (is_declared(name))
		help::error(name, " declared twice");
	if (output_trace) std::cout << "DEF: adding " << name << " = " << val << '\n';
	var_table.push_back(Variable_decimal{name, val, is_const});
	return val;
}
//------------------------------------------------------------------------------

calc::Token_stream::Token_stream(Calculator_version v)
    : full(false)
    , buffer(0)
    , ver(v)
{}

void calc::Token_stream::putback(Token t)
{
	if (full)
		help::error("buffer is full");
	if (output_trace) std::cout << "TOK: putting back token into buffer\n";
	buffer = t; full = true;
}

calc::Token calc::Token_stream::getBuffer()
{
	full = false;
	return buffer;
}

void calc::Token_stream::ignore(char c)
{
	// check and empty buffer, stop if ignore char is found
	if (full && getBuffer().kind == c) return;

	// else: read through std::cin for ignore char while discarding
	char ch = 0;
	while (std::cin.get(ch) && ch == c) return; // stop discarding
}

//------------------------------------------------------------------------------

char calc::Token_stream::skipto_break_nonws()
{
	char ch{ ' ' };
	while (std::cin && (isspace(ch) && ch != '\n')) {
		std::cin.get(ch);
	}
	return ch;
}
//------------------------------------------------------------------------------

calc::Token calc::Token_stream::peek()
{
	return get(true);
}

calc::Token calc::Token_stream::get(bool peek)
{
	if (full) {
		if (output_trace) std::cout << "TOK: getting token from buffer\n";
		Token t = getBuffer();
		if (peek) {
			putback(t);
		}
		return t;
	}
	char ch{};
	// CH07E05, eat whitespace, return print token on linebreak '\n'
	ch = skipto_break_nonws();
	if (ch == '\n') {
		if (peek) {
			std::cin.putback('\n');
		}
		return Token(print);
	}

	// check for hexadecimal prefix CH07E09
	if (ch == hex_prefix.at(0)) {
		char ch2{};
		std::cin.get(ch2);
		if (ch2 == hex_prefix.at(1)) {
			std::string s{ "" };
			char ch3{ };
			while (std::cin.get(ch3) && isalnum(ch3)) {
				s += ch3;
			}
			std::cin.putback(ch3);
			if (s.size() == 0) {
				help::error("Incomplete Hexadecimal number");
			}
			if (ver == Calculator_version::Roman) {
				return Token(hex_token,
				             {Result_type::Roman_numeral, hextodec(s)});
			}
			return Token(hex_token, {Result_type::Integer_value, hextodec(s)});
		}
		std::cin.putback(ch2);
		std::cin.putback(ch);
	}

	// check for roman numeral
	if (ver == Calculator_version::Roman
	    && (ch == 'N' || romi::ch_is_valid(ch))) {
		std::string r{ch};
		char ch2{};
		while (std::cin.get(ch2) && isalnum(ch2)) {
			r += ch2;
		}
		std::cin.putback(ch2);
		return Token(roman, {Result_type::Roman_numeral, r});
	}

	switch (ch) {
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ',':
	case assign:
		if (output_trace)
			std::cout << "TOK: operator '" << ch << "'" << '\n';
		if (peek) {
			std::cin.putback(ch);
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
		if (ver == Calculator_version::Decimal) {
			std::cin.putback(ch); // put digit back into input stream
			double val_dbl;       // CH07E10
			std::cin >> val_dbl;
			if (output_trace)
				std::cout << "TOK: number " << val_dbl << '\n';
			if (peek) {
				for (char c : std::to_string(val_dbl)) {
					std::cin.putback(c);
				}
			}
			return Token(number, {Result_type::Floating_point_value, val_dbl});
		}
		break;
	}
	default:
		if (isalpha(ch) || ch == declkey.front() || ch == quit_key.front()) {
			if (output_trace)
				std::cout << "TOK: alphanumeric character found: " << ch
				          << '\n';
			string s;
			s += ch;

			// read through std::cin, feed alphanumeric chars into string
			// CH07E01: add underscore to list of valid characters
			while (std::cin.get(ch)
			       && (isalpha(ch) || isdigit(ch) || ch == '_')) {
				s += ch;
			}

			if (peek) {
				for (char c : s) {
					std::cin.putback(c);
				}
			}

			std::cin.putback(ch); // put non-alphanumeric back into std::cin

			if (s == quit_key) {
				if (output_trace)
					std::cout << "TOK: quit keyword found: " << s << '\n';
				return Token(quit_token);
			}

			if (s == help_key) {
				if (output_trace)
					std::cout << "TOK: help keyword found: " << s << '\n';
				return Token(help_token);
			}

			if (s == declkey) {
				if (output_trace)
					std::cout << "TOK: declaration keyword found: " << s
					          << '\n';
				return Token(let);
			}

			if (s == constkey) { // CH07E03
				if (output_trace)
					std::cout << "TOK: const keyword found: " << s << '\n';
				return Token(const_token);
			}

			if (s == sqrt_word) {
				if (output_trace)
					std::cout << "TOK: squareroot keyword found: " << s << '\n';
				return Token(sqrt_token);
			}

			if (s == pow_word) {
				if (output_trace)
					std::cout << "TOK: power of keyword found: " << s << '\n';
				return Token(pow_token);
			}
			if (islower(s.front())) {
				if (output_trace)
					std::cout << "TOK: string found: " << s << '\n';
				return Token{name, s};
			}
		}
		help::error("Bad token");
		break;
	}
	return 0;
}

//------------------------------------------------------------------------------

void calc::run(Calculator_version v)
{
	calc::Token_stream ts(v);
	if (v == Calculator_version::Decimal) {
		print_greeting();
		ts.declare("pi",
		           {Result_type::Floating_point_value, 3.14159265358979323846},
		           true);
	} else {
		print_greeting_latin();
		ts.declare("rmin", {Result_type::Roman_numeral, romi::min_int}, true);
		ts.declare("rmax", {Result_type::Roman_numeral, romi::max_int}, true);
	}

	calculate(ts);
	help::keep_window_open();
}

//------------------------------------------------------------------------------

void calc::print_instructions()
{
	std::cout << "The following arithmetic operators are available: " << '\n'
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
		std::cout << "    " << fn << '\n';
	}
}

void calc::print_instructions_latin()
{
	std::cout << "Sequentes operatores arithmetici sunt disponibiles: " << '\n'
	          << "    "
	          << "'-', '+', '/', '*' ,'%'" << '\n'
	          << "Utere parenthesibus ad grouping.\n"
	          << "Variabiles declara/define usando:" << '\n'
	          << "    '" << declkey << " nomen " << assign << " valor'" << '\n'
	          << "    '" << constkey << " nomen " << assign << " valor'"
	          << " (variabilis immutabilis)" << '\n'
	          << "    'nomen " << assign << " valor'"
	          << " (reassigna valorem ad existentem)" << '\n'
	          << "Functiones disponibiles:" << '\n';
	for (const string& fn : available_fn()) {
		std::cout << "    " << fn << '\n';
	}
}

//------------------------------------------------------------------------------

void calc::print_greeting()
{
	std::cout << "Calculator\n"
	          << "Please enter expressions using floating-point numbers, "
	          << '\n'
	          << "finish with <Enter>.\n"
	          << "(!) Use the '" << hex_prefix
	          << "' prefix to define numbers using " << '\n'
	          << "    hexadecimal notation. e.g. '0xFF' equals '255'" << '\n'
	          << "(!) Write '" << quit_key << "' to exit"
	          << " or '" << help_key << "' for more info." << '\n';
}

void calc::print_greeting_latin()
{
	std::cout
	    << "Computus\n"
	    << "Quaeso inscribe expressiones usurpando numeros fluminis mobilis, "
	    << '\n'
	    << "conclude cum <Enter>.\n"
	    << "(!) Utere praefixo '" << hex_prefix
	    << "' ad definiendum numeros usurpando " << '\n'
	    << "    notationem hexadecimalem. e.g. '0xFF' aequabitur '255'" << '\n'
	    << "(!) Scribe '" << quit_key << "' ad exeundum"
	    << " vel '" << help_key << "' ad petendum plus informationis." << '\n'
	    << "(!) Haec versio calculatoris operatur in <int> solummodo " << '\n'
	    << "    itaque amissio praecisionis posset accidere, e.g. quicquid "
	    << '\n'
	    << "    supra 0x7FFFFFFF efficiet inundationem in plerisque "
	       "systematibus."
	    << '\n';
}

//------------------------------------------------------------------------------

calc::Result calc::statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let: case const_token:
		if (output_trace) std::cout << "STA: declaration keyword found, get declaration()" << '\n';
		ts.putback(t); // CH07E03
		return declaration(ts);
		break;
	case name: {
		// CH07E02 Redefine if 'name' is followed by 'assignment' token
		if (output_trace) std::cout << "STA: name found, try to get assigment" << '\n';
		Token t_peek = ts.peek(); // peek ahead
		if (t_peek.kind == assign) {
			if (output_trace) std::cout << "STA: name followed by assignment keyword found, put back token: " << t.kind << '\n';
			ts.putback(t);
			return redefinition(ts);
		} else {
			if (output_trace) std::cout << "STA: no assigment operator found" << '\n';
		}
	}
	default:
		if (output_trace) std::cout << "STA: get expression()" << '\n';
		ts.putback(t);
		return expression(ts);
		break;
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::redefinition(Token_stream& ts)
{
	// after detecting statement w. a name followed by the assignment operator
	if (output_trace) std::cout << "RED: get token, expecting name." << '\n';
	Token t{ ts.get() };
	if (t.kind != name) {
		help::error("Expected name in redefinition");
	}
	if (output_trace) std::cout << "RED: get token, expecting assignment." << '\n';
	Token t2{ ts.get() };
	if (t2.kind != assign) {
		help::error("Expected assigment operator in redefinition");
	}
	if (output_trace) std::cout << "RED: get expression()" << '\n';
	Result d = expression(ts);
	if (output_trace) std::cout << "RED: set_value(" << t.name << ", " << d << ')' << '\n';
	ts.set(t.name, d);
	return d;
}

// CH0703, modififed declaration() to handle both constants and regular vars
calc::Result calc::declaration(Token_stream& ts)
{
	// after detecting statement w. the declaration or constant keyword
	Token t = ts.get();
	if (t.kind != let && t.kind != const_token) {
		help::error("Expected a declaration or constant token");
	}
	bool is_const{ (t.kind == const_token) };
	Token t2 = ts.get();
	if (t2.kind != name) {
		help::error("name expected in declaration");
	}
	Token t3 = ts.get();
	if (t3.kind != '=')
		help::error("= missing in declaration of ", t.name);
	if (output_trace) std::cout << "DEC: get expression()" << '\n';
	Result d = expression(ts);
	if (output_trace) std::cout << "DEC: define_name(" << t2.name << ", " << d << ")" << '\n';
	ts.declare(t2.name, d, is_const);
	return d;
}

//------------------------------------------------------------------------------

void calc::calculate(Token_stream& ts)
{
	while (std::cin)
	try {
		std::cout << prompt << ' ';
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // eat print tokens
		if (t.kind == quit_token) return;
		if (t.kind == help_token) {
			if (ts.version() == Calculator_version::Decimal) {
				print_instructions();
			} else {
				print_instructions_latin();
			}
			ts.ignore('\n');
			continue;
		}
		ts.putback(t);
		std::cout << result_sign << ' ' << statement(ts) << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		clean_up_mess(ts);
	}
	catch (...) {
		std::cerr << "exception" << ' ' << '\n';
		clean_up_mess(ts);
	}
}

//------------------------------------------------------------------------------

calc::Result calc::primary(Token_stream& ts)
{
	if (output_trace) std::cout << "PRI: get token" << '\n';
	Token t = ts.get();
	switch (t.kind) {
	case '(':   // expression
	{
		if (output_trace) std::cout << "PRI: found '(', get expression" << '\n';
		Result exp = expression(ts);
		if (output_trace) std::cout << "PRI: eof expression, expecting ')'" << '\n';
		t = ts.get();
		if (t.kind != ')')
			help::error("expected ')'");
		return exp;
	}
	case sqrt_token: // square root
	{
		t = ts.get();
		if (t.kind != '(')
			help::error("expected '(' after square root keyword");
		if (output_trace) std::cout << "PRI: found '(' after square root keyword, "
							   << "get expression() of which we want to get "
							   << "the square root" << '\n';
		Result exp = expression(ts);
		if (exp < 0)
			help::error("cannot calculate square root of a negative number");
		t = ts.get();
		if (t.kind != ')')
			help::error("expected ')' after square root expression");
		if (output_trace) std::cout << "PRI: getting squareroot." << '\n';
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
		t = ts.get();
		if (t.kind != '(')
			help::error("expected '(' after power of keyword");
		if (output_trace) std::cout << "PRI: found '(' after power of keyword, "
			<< "get the expression() of which we want to raise by a number" << '\n';
		Result expr = expression(ts);
		t = ts.get();
		if (t.kind != ',')
			help::error("expected ',' after expression");
		if (output_trace) std::cout << "PRI: getting exponent expression()" << '\n';
		Result expo = expression(ts);
		t = ts.get();
		if (t.kind != ')')
			help::error("expected ')' after exponent");
		double pow_val = 0;
		double expr_val = expr.as_floating_point();
		double expo_val = expr.as_floating_point();
		Result_type type_expr{expr.type};
		Result_type type_expo{expo.type};
		Result_type type_return{Result_type::Floating_point_value};
		if (type_expr != Result_type::Floating_point_value
		    || type_expo != Result_type::Floating_point_value) {
			expr_val = help::narrow_cast<int>(expr_val);
			expo_val = help::narrow_cast<int>(expo_val);
			pow_val = help::narrow_cast<int>(pow(expr_val, expo_val));
			type_return = Result_type::Roman_numeral;
		} else {
			pow_val = pow(expr_val, expo_val);
		}
		return {type_return, pow_val};
	}
	case number:   // number
		if (output_trace)
			std::cout << "PRI: found number: " << t.result << '\n';
		return t.result;
	case hex_token: // CH07E09
		return t.result;
	case roman: // CH07E09
		return t.result;
	case '-':
		return -1 * primary(ts);
	case '+':
		return primary(ts);
	case name:
		return ts.get(t.name);
	default:
		help::error("expected Primary");
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::term(Token_stream& ts)
{
	if (output_trace) std::cout << "TER: get primary" << '\n';
	Result left{primary(ts)};

	if (output_trace) std::cout << "TER: get next token" << '\n';
	Token t = ts.get(); // get next token

	while (true) {
		switch (t.kind) {
		case '*':       // multiply
			if (output_trace) std::cout << "TER: multiply, getting primary" << '\n';
			left = left * primary(ts);
			if (output_trace) std::cout << "TER: result of multiplication: " << left << '\n';
			if (output_trace) std::cout << "TER: get next token" << '\n';
			t = ts.get();
			break;
		case '/':       // division
		{
			if (output_trace) std::cout << "TER: divide, getting primary" << '\n';
			Result prim = primary(ts);
			if (prim == 0)
				help::error("divide by zero");
			left = left / prim;
			if (output_trace) std::cout << "TER: result of division: " << left << '\n';
			if (output_trace) std::cout << "TER: get next token" << '\n';
			t = ts.get();
			break;
		}
		case '%':       // modulo
		{
			if (ts.version() == Calculator_version::Roman) {
				Result i1 = primary(ts);
				if (i1 == 0)
					help::error("% divide by zero");
				left = left / i1;
				t = ts.get();
			}
			break;
		}
		case assign: // CH07E02, assignment not allowed as part of an expression
			help::error(
			    "The assignment operator cannot be used in this context. "
			    "Variables may only be redefined as separate statements.");
			break;
		default:
			if (output_trace) std::cout << "TER: put back" << t.kind << " into buffer" << '\n';
			ts.putback(t);
			if (output_trace) std::cout << "TER: return result: " << left << '\n';
			return left;
		}
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::expression(Token_stream& ts)
{
	if (output_trace) std::cout << "EXP: get term" << '\n';
	Result left = term(ts);

	if (output_trace) std::cout << "EXP: get next token" << '\n';
	Token t = ts.get();  // get next token
	while (true) {
		switch (t.kind) {
		case '+':       // addition
			if (output_trace) std::cout << "EXP: add, getting term" << '\n';
			left = left + term(ts);
			if (output_trace) std::cout << "EXP: result of addition " << left << '\n';
			if (output_trace) std::cout << "EXP: get next token" << '\n';
			t = ts.get();
			break;
		case '-':       // subtraction
			if (output_trace) std::cout << "EXP: subtract, getting term" << '\n';
			left = left - term(ts);
			if (output_trace) std::cout << "EXP: result of subtraction " << left << '\n';
			if (output_trace) std::cout << "EXP: get next token" << '\n';
			t = ts.get();
			break;
		default:
			if (output_trace) std::cout << "EXP: put back " << t.kind << " into buffer" << '\n';
			ts.putback(t);
			if (output_trace) std::cout << "EXP: return result " << left << '\n';
			return left;
		}
	}
	return {};
}

//------------------------------------------------------------------------------

void calc::clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}
