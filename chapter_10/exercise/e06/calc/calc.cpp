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

// CH07E03, Symbol_table

int calc::Symbol_table::get(string name)
{
	// attempts to find Variable s and return its value
	for (const Variable& v : var_table)
		if (v.name == name) return v.value;
	help::error("unable to get undefined variable; ", name);
	return 0;
}

void calc::Symbol_table::set(string name, int val)
{
	// attempts to find variable s and set its value to d
	for (Variable& v : var_table)
		if (v.name == name) {
			if (v.is_const) {
				help::error("Cannot reassign a constant"); // CH03E07
			}
			v.value = val;
			return;
		}
	help::error("unable to assign value to undefined variable ", name);
}

bool calc::Symbol_table::is_declared(string name)
{
	for (const Variable& v : var_table) {
		if (v.name == name) {
			return true;
		}
	}
	return false;
}

int calc::Symbol_table::declare(string name, int val, bool is_const)
{
	if (is_declared(name))
		help::error(name, " declared twice");
	if (output_trace) std::cout << "DEF: adding " << name << " = " << val << '\n';
	var_table.push_back(Variable{ name, val, is_const });
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
			return Token(hex_token, s);
		}
		std::cin.putback(ch2);
		std::cin.putback(ch);
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
		if (output_trace) std::cout << "TOK: operator '" << ch << "'" << '\n';
		if (peek) {
			std::cin.putback(ch);
		}
		return Token(ch);   // characters represent themselves
	case '0': case '1': case '2': case '3': case '4': // CH07E10, removed dot
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);    // put digit back into input stream
		double val_dbl; // CH07E10
		int val;
		std::cin >> val_dbl;
		val = help::narrow_cast<int>(val_dbl);
		if (output_trace) std::cout << "TOK: number " << val << '\n';
		if (peek) {
			for (char c : std::to_string(val)) {
				std::cin.putback(c);
			}
		}
		return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == declkey.front() || ch == quit_key.front()) {
			if (output_trace) std::cout << "TOK: alphanumeric character found: " << ch << '\n';
			string s;
			s += ch;

			// read through std::cin, feed alphanumeric chars into string
			// CH07E01: add underscore to list of valid characters
			while (
				std::cin.get(ch)
				&& (isalpha(ch) || isdigit(ch) || ch == '_')
			) {
				s += ch;
			}

			if (peek) {
				for (char c : s) {
					std::cin.putback(c);
				}
			}

			std::cin.putback(ch); // put non-alphanumeric back into std::cin

			if (s == quit_key) {
				if (output_trace) std::cout << "TOK: quit keyword found: " << s << '\n';
				return Token(quit_token);
			}

			if (s == help_key) {
				if (output_trace) std::cout << "TOK: help keyword found: " << s << '\n';
				return Token(help_token);
			}

			if (s == declkey) {
				if (output_trace) std::cout << "TOK: declaration keyword found: " << s << '\n';
				return Token(let);
			}

			if (s == constkey) { // CH07E03
				if (output_trace) std::cout << "TOK: const keyword found: " << s << '\n';
				return Token(const_token);
			}

			if (s == sqrt_word) {
				if (output_trace) std::cout << "TOK: squareroot keyword found: " << s << '\n';
				return Token(sqrt_token);
			}

			if (s == pow_word) {
				if (output_trace) std::cout << "TOK: power of keyword found: " << s << '\n';
				return Token(pow_token);
			}
			if (islower(s.front())) {
				if (output_trace) std::cout << "TOK: string found: " << s << '\n';
				return Token{ name, s };
			}
		}
		help::error("Bad token");
		break;
	}
	return 0;
}

//------------------------------------------------------------------------------

int calc::run()
{
	calc::Token_stream ts;
	print_greeting();

	// predefined variables
	ts.sym.declare("rmin", romi::min_int, true);
	ts.sym.declare("rmax", romi::max_int, true);

	calculate(ts);
	help::keep_window_open();
	return 0;
}

//------------------------------------------------------------------------------

// void calc::print_instructions()
// {
// 	std::cout
// 		<< "The following arithmetic operators are available: " << '\n'
// 		<< "    " << "'-', '+', '/', '*' ,'%'" << '\n'
// 		<< "Use parentheses for grouping.\n"
// 		<< "Declare / define variables using:" << '\n'
// 		<< "    '" << declkey << " name " << assign << " value'" << '\n'
// 		<< "    '" << constkey << " name " << assign << " value'"
// 			<< " (immutable variable)" << '\n'
// 		<< "    'name " << assign << " value'"
// 			<< " (reassign value to existing)" << '\n'
// 		<< "Available functions:" << '\n';
// 	for (const string& fn : available_fn()) {
// 		std::cout << "    " << fn << '\n';
// 	}
// }

void calc::print_instructions()
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

// void calc::print_greeting() {
// 	std::cout
// 		<< "Calculator\n"
// 		<< "Please enter expressions using floating-point numbers, " << '\n'
// 		<< "finish with <Enter>.\n"
// 		<< "(!) Use the '" << hex_prefix << "' prefix to define numbers using "
// 		<< '\n'
// 		<< "    hexadecimal notation. e.g. '0xFF' equals '255'" << '\n'
// 		<< "(!) Write '" << quit_key << "' to exit"
// 		<< " or '" << help_key << "' for more info." << '\n'
// 		<< "(!) This version of the calculator operates on <int>'s " << '\n'
// 		<< "    only so loss of precision may occur, e.g. anything" << '\n'
// 		<< "    above 0x7FFFFFFF will cause overflow on most systems." << '\n';
// }

void calc::print_greeting()
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

int calc::statement(Token_stream& ts)
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
	return 0;
}

//------------------------------------------------------------------------------

int calc::redefinition(Token_stream& ts)
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
	int d = expression(ts);
	if (output_trace) std::cout << "RED: set_value(" << t.name << ", " << d << ')' << '\n';
	ts.sym.set(t.name, d);
	return d;
}

// CH0703, modififed declaration() to handle both constants and regular vars
int calc::declaration(Token_stream& ts)
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
	int d = expression(ts);
	if (output_trace) std::cout << "DEC: define_name(" << t2.name << ", " << d << ")" << '\n';
	ts.sym.declare(t2.name, d, is_const);
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
			print_instructions();
			ts.ignore('\n');
			continue;
		}
		ts.putback(t);
		std::cout << result << ' ' << statement(ts) << '\n';
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

int calc::primary(Token_stream& ts)
{
	if (output_trace) std::cout << "PRI: get token" << '\n';
	Token t = ts.get();
	switch (t.kind) {
	case '(':   // expression
	{
		if (output_trace) std::cout << "PRI: found '(', get expression" << '\n';
		int exp = expression(ts);
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
		int exp = expression(ts);
		if (exp < 0)
			help::error("cannot calculate square root of a negative number");
		t = ts.get();
		if (t.kind != ')')
			help::error("expected ')' after square root expression");
		if (output_trace) std::cout << "PRI: getting squareroot." << '\n';
		return static_cast<int>(sqrt(exp));
	}
	case pow_token: // power of
	{
		t = ts.get();
		if (t.kind != '(')
			help::error("expected '(' after power of keyword");
		if (output_trace) std::cout << "PRI: found '(' after power of keyword, "
			<< "get the expression() of which we want to raise by a number" << '\n';
		int expr = expression(ts);
		t = ts.get();
		if (t.kind != ',')
			help::error("expected ',' after expression");
		if (output_trace) std::cout << "PRI: getting exponent expression()" << '\n';
		int expo = help::narrow_cast<int>(expression(ts));
		t = ts.get();
		if (t.kind != ')')
			help::error("expected ')' after exponent");
		return help::narrow_cast<int>(pow(expr, expo));
	}
	case number:   // number
		if (output_trace) std::cout << "PRI: found number: " << t.value << '\n';
		return t.value;
	case hex_token: // CH07E09
		return hextodec(t.name);
	case '-':
		return -primary(ts);
	case '+':
		return primary(ts);
	case name:
		return ts.sym.get(t.name);
	default:
		help::error("expected Primary");
	}
	return 0;
}

//------------------------------------------------------------------------------

int calc::term(Token_stream& ts)
{
	if (output_trace) std::cout << "TER: get primary" << '\n';
	int left{primary(ts)};
	double left_dbl{ (double)left };

	if (output_trace) std::cout << "TER: get next token" << '\n';
	Token t = ts.get(); // get next token

	while (true) {
		switch (t.kind) {
		case '*':       // multiply
			if (output_trace) std::cout << "TER: multiply, getting primary" << '\n';
			left_dbl *= primary(ts);
			left = help::narrow_cast<int>(left_dbl);
			if (output_trace) std::cout << "TER: result of multiplication: " << left << '\n';
			if (output_trace) std::cout << "TER: get next token" << '\n';
			t = ts.get();
			break;
		case '/':       // division
		{
			if (output_trace) std::cout << "TER: divide, getting primary" << '\n';
			int prim = primary(ts);
			if (prim == 0)
				help::error("divide by zero");
			left_dbl /= prim;
			left = static_cast<int>(left_dbl);
			if (output_trace) std::cout << "TER: result of division: " << left << '\n';
			if (output_trace) std::cout << "TER: get next token" << '\n';
			t = ts.get();
			break;
		}
		case '%':       // modulo
		{
			int i1 = primary(ts);
			if (i1 == 0)
				help::error("% divide by zero");
			left %= i1;
			t = ts.get();
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
	return 0;
}

//------------------------------------------------------------------------------

int calc::expression(Token_stream& ts)
{
	if (output_trace) std::cout << "EXP: get term" << '\n';
	int left = term(ts);
	double left_dbl{ (double)left };

	if (output_trace) std::cout << "EXP: get next token" << '\n';
	Token t = ts.get();  // get next token
	while (true) {
		switch (t.kind) {
		case '+':       // addition
			if (output_trace) std::cout << "EXP: add, getting term" << '\n';
			left_dbl += term(ts);
			left = help::narrow_cast<int>(left_dbl);
			if (output_trace) std::cout << "EXP: result of addition " << left << '\n';
			if (output_trace) std::cout << "EXP: get next token" << '\n';
			t = ts.get();
			break;
		case '-':       // subtraction
			if (output_trace) std::cout << "EXP: subtract, getting term" << '\n';
			left_dbl -= term(ts);
			left = help::narrow_cast<int>(left_dbl);
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
	return 0;
}

//------------------------------------------------------------------------------

void calc::clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}
