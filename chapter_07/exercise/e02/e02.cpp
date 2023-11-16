#include "../../lib/std_lib_facilities.h"

// Chapter 7, Exercise 2. Allow (re)assignment using "=".
// Scroll down to comments marked: CH07E02

// First of all, it doesn't seem very practical to introduce '=' as an operator
// that can be in used in any expression. This code adds the ability to define
// a variable using '=' in a statement only (Much like a declaration).

//	Pros and cons of this addition
//	Pros:	Definitely nice to have, avoids having to restart the program to
//			reuse the same 'syntax'.
//			Makes more sense, not all variables are constants by definition.
//	Cons:	Feature creep: more work, introducing new bugs.
//			Also, users may assume that variables containing references to other
//			variables will dynamically update when the values of those
//			references are redefined. They may argue that you cannot implement
//			A without also implementing B.

using std::string;

constexpr bool output_trace{ false }; // debug

// various tokens with descriptive names
constexpr char prompt{ '>' };
constexpr char result{ '=' };
constexpr char number{ '8' };
constexpr char print { ';' };

constexpr char name  { 'a' };   // variable name token
constexpr char let   { 'L' };   // declaration token
const string declkey { "#" };   // declaration keyword
constexpr char assign{ '=' };   // assignment token

// quitting
constexpr char quit_token{ 'q' };
const string   quit_key  { "quit" };

// squareroot
const string   sqrt_word { "sqrt" }; // keyword
constexpr char sqrt_token{ 's' };    // token

// power of
const string    pow_word { "pow" }; // keyword
constexpr char  pow_token{ 'p' };   // token

vector<string> available_fn{ sqrt_word, pow_word };

//-------------------------------------------------------------------

class Token {
public:
	char kind;
	double value = 0;
	string name;
	Token(char ch)
		:kind(ch), value(0) { }
	Token(char ch, double val)
		:kind(ch), value(val) { }
	Token(char ch, string n)
		:kind(ch), name(n) { }
};

//-------------------------------------------------------------------

class Token_stream {
public:
	Token_stream();				// read tokens from std::cin
	Token get(bool peek=false);	// get next token in stream. CH07E02, peek bool
	Token peek();				// CH07E02 get next token without consuming it
	void putback(Token t);		// put back token, put into buffer
	void ignore(char c);		// discard all up to and including c
	Token getBuffer();
private:
	bool full;					// full when token in buffer
	Token buffer;				// keep tokens that are put back
};

//-------------------------------------------------------------------

Token_stream::Token_stream()
	:full(false), buffer(0) { }

//-------------------------------------------------------------------

void Token_stream::putback(Token t)
{
	if (full) error("buffer is full");
	if (output_trace) std::cout << "TOK: putting back token into buffer\n";
	buffer = t; full = true;
}

//-------------------------------------------------------------------

Token Token_stream::getBuffer() {
	full = false;
	return buffer;
}

//-------------------------------------------------------------------

void Token_stream::ignore(char c)
{
	// check and empty buffer, stop if ignore char is found
	if (full && getBuffer().kind == c) return;

	// else: read through std::cin for ignore chard while discarding
	char ch = 0;
	while (std::cin >> ch && ch == c) return; // stop discarding
}

//-------------------------------------------------------------------

// CH07E02, peek()
Token Token_stream::peek() {
	return get(true);
}

Token Token_stream::get(bool peek)
{
	if (full) {
		if (output_trace) std::cout << "TOK: getting token from buffer\n";
		Token t = getBuffer();
		if (peek) {
			putback(t);
		}
		return t;
	}
	char ch;
	std::cin >> ch;

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
	case '.': case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);    // put digit back into input stream
		double val;
		std::cin >> val;
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

			if (s == declkey) {
				if (output_trace) std::cout << "TOK: declaration keyword found: " << s << '\n';
				return Token(let);
			}

			if (s == sqrt_word) {
				if (output_trace) std::cout << "TOK: squareroot keyword found: " << s << '\n';
				return Token(sqrt_token);
			}

			if (s == pow_word) {
				if (output_trace) std::cout << "TOK: power of keyword found: " << s << '\n';
				return Token(pow_token);
			}
			if (isalpha(s.front())) {
				if (output_trace) std::cout << "TOK: string found: " << s << '\n';
				return Token{ name, s };
			}
		}
		error("Bad token");
		break;
	}
}

//-------------------------------------------------------------------

class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;

//-------------------------------------------------------------------

Token_stream ts;

//-------------------------------------------------------------------

double get_value(string s)
{
	// attempts to find Variable s and return its value
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;
	error("unable to get undefined variable; ", s);
}

void set_value(string s, double d)
{
	// attempts to find variable s and set its value to d
	for (Variable& v : var_table)
		if (v.name == s) {
			v.value = d; // success
			return;
		}
	error("unable to assign value to undefined variable ",
		s);
}

bool is_declared(string s)
{
	// checks if a variable s is in var_table
	for (const Variable& v : var_table)
		if (v.name == s) return true;
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var)) error(var, " declared twice");
	if (output_trace) std::cout << "DEF: adding " << var << " = " << val << '\n';
	var_table.push_back(Variable{ var, val });
	return val;
}
//-------------------------------------------------------------------

void print_greeting();					// program greeting / info string

void calculate();						// parse and evaluate input
double statement();						// read and evaluate a Statement
double declaration();					// read and evaluate a Declaration
double redefinition();					// CH07E02 redefine a variable
double expression();					// read and evaluate an Expression
double term();							// read and evaluate a Term
double primary();						// read and evaluate a Primary

void clean_up_mess();					// discard invalid input from stream

//-------------------------------------------------------------------

int main()
{
	print_greeting();

	// predefined variables
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	define_name("k", 1000);

	calculate();
	for (Variable x : var_table) {
		std::cout << x.name << '\t' << x.value << '\n';
	}
	keep_window_open();
	return 0;
}

//-------------------------------------------------------------------

void print_greeting() {
	std::cout
		<< "- Welcome to Just Another Calculator.\n"
		<< "- - Please enter expressions using"
		<< " floating-point numbers.\n"
		<< "- - The following arithmetic operators are"
		<< " available: '-', '+', '/', '*'\n"
		<< "- - Use parentheses for grouping.\n"
		<< "- - Declare variables using: '"
		<< declkey << " name " << assign << " value'." << '\n'
		<< "- - Available functions:" << '\n';
	for (const string& fn : available_fn) {
		std::cout << "- - - " << fn << '\n';
	}
	std::cout
		<< "- - Enter '" << print << "' to terminate and"
		<< " print out an expression. Enter '" << quit_key
		<< "' to exit\n";
}

//-------------------------------------------------------------------

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		if (output_trace) std::cout << "STA: declaration keyword found, get declaration()" << '\n';
		return declaration();
		break;
	case name: {
		// CH07E02 Redefine if 'name' is followed by 'assignment' token
		if (output_trace) std::cout << "STA: name found, try to get assigment" << '\n';
		Token t_peek = ts.peek(); // peek ahead
		if (t_peek.kind == assign) {
			if (output_trace) std::cout << "STA: name followed by assignment keyword found, put back token: " << t.kind << '\n';
			ts.putback(t);
			return redefinition();
		} else {
			if (output_trace) std::cout << "STA: no assigment operator found" << '\n';
		}
	}
	default:
		if (output_trace) std::cout << "STA: get expression()" << '\n';
		ts.putback(t);
		return expression();
		break;
	}
}

//-------------------------------------------------------------------
// CH07E02: Redefinition of a variable

double redefinition() {
	// after detecting statement w. a name followed by the assignment operator
	if (output_trace) std::cout << "RED: get token, expecting name." << '\n';
	Token t{ ts.get() };
	if (t.kind != name) {
		error("Expected name in redefinition");
	}
	if (output_trace) std::cout << "RED: get token, expecting assignment." << '\n';
	Token t2{ ts.get() };
	if (t2.kind != assign) {
		error("Expected assigment operator in redefinition");
	}
	if (output_trace) std::cout << "RED: get expression()" << '\n';
	double d = expression();
	if (output_trace) std::cout << "RED: set_value(" << t.name << d << ')' << '\n';
	set_value(t.name, d);
	return d;
}

double declaration()
{
	// after detecting statement w. the declaration-keyword
	Token t = ts.get();
	if (t.kind != name) {
		error("name expected in declaration");
	}
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", t.name);
	if (output_trace) std::cout << "DEC: get expression()" << '\n';
	double d = expression();
	if (output_trace) std::cout << "DEC: define_name(" << t.name << ", " << d << ")" << '\n';
	define_name(t.name, d);
	return d;
}

//-------------------------------------------------------------------

void calculate()
{
	while (std::cin)
	try {
		std::cout << prompt << ' ';
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // eat print tokens
		if (t.kind == quit_token) return;
		ts.putback(t);
		std::cout << result << ' ' << statement() << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		clean_up_mess();
	}
	catch (...) {
		std::cerr << "exception" << ' ' << '\n';
		clean_up_mess();
	}
}

//-------------------------------------------------------------------

double primary() {
	if (output_trace) std::cout << "PRI: get token" << '\n';
	Token t = ts.get();
	switch (t.kind) {
	case '(':   // expression
	{
		if (output_trace) std::cout << "PRI: found '(', get expression" << '\n';
		double exp = expression();
		if (output_trace) std::cout << "PRI: eof expression, expecting ')'" << '\n';
		t = ts.get();
		if (t.kind != ')') error("expected ')'");
		return exp;
	}
	case sqrt_token: // square root
	{
		t = ts.get();
		if (t.kind != '(') error("expected '(' after square root keyword");
		if (output_trace) std::cout << "PRI: found '(' after square root keyword, "
							   << "get expression() of which we want to get "
							   << "the square root" << '\n';
		double exp = expression();
		if (exp < 0) error("cannot calculate square root of a negative number");
		t = ts.get();
		if (t.kind != ')') error("expected ')' after square root expression");
		if (output_trace) std::cout << "PRI: getting squareroot." << '\n';
		return sqrt(exp);
	}
	case pow_token: // power of
	{
		t = ts.get();
		if (t.kind != '(') error("expected '(' after power of keyword");
		if (output_trace) std::cout << "PRI: found '(' after power of keyword, "
			<< "get the expression() of which we want to raise by a number" << '\n';
		double expr = expression();
		t = ts.get();
		if (t.kind != ',') error("expected ',' after expression");
		if (output_trace) std::cout << "PRI: getting exponent expression()" << '\n';
		double expo = narrow_cast<int>(expression());
		t = ts.get();
		if (t.kind != ')') error("expected ')' after exponent");
		return pow(expr, expo);
	}
	case number:   // number
		if (output_trace) std::cout << "PRI: found number: " << t.value << '\n';
		return t.value;
	case '-':
		return -primary();
	case '+':
		return primary();
	case name:
		return get_value(t.name);
	default:
		error("expected Primary");
	}
}

//-------------------------------------------------------------------

double term() {
	if (output_trace) std::cout << "TER: get primary" << '\n';
	double left = primary();

	if (output_trace) std::cout << "TER: get next token" << '\n';
	Token t = ts.get();  // get next token

	while (true) {
		switch (t.kind) {
		case '*':       // multiply
			if (output_trace) std::cout << "TER: multiply, getting primary" << '\n';
			left *= primary();
			if (output_trace) std::cout << "TER: result of multiplication: " << left << '\n';
			if (output_trace) std::cout << "TER: get next token" << '\n';
			t = ts.get();
			break;
		case '/':       // division
		{
			if (output_trace) std::cout << "TER: divide, getting primary" << '\n';
			double prim = primary();
			if (prim == 0) error("divide by zero");
			left /= prim;
			if (output_trace) std::cout << "TER: result of division: " << left << '\n';
			if (output_trace) std::cout << "TER: get next token" << '\n';
			t = ts.get();
			break;
		}
		case '%':       // modulo
		{   int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error("% divide by zero");
			left = i1 % i2;
			t = ts.get();
			break;
		}
		case assign: // CH07E02, assignment not allowed as part of an expression
			error(
				"The assignment operator cannot be used in this context. "
				"Variables may only be redefined as separate statements.");
				break;
			break;
		default:
			if (output_trace) std::cout << "TER: put back" << t.kind << " into buffer" << '\n';
			ts.putback(t);
			if (output_trace) std::cout << "TER: return result: " << left << '\n';
			return left;
		}
	}
}

//-------------------------------------------------------------------

double expression()
{
	if (output_trace) std::cout << "EXP: get term" << '\n';
	double left = term();

	if (output_trace) std::cout << "EXP: get next token" << '\n';
	Token t = ts.get();  // get next token
	while (true) {
		switch (t.kind) {
		case '+':       // addition
			if (output_trace) std::cout << "EXP: add, getting term" << '\n';
			left += term();
			if (output_trace) std::cout << "EXP: result of addition " << left << '\n';
			if (output_trace) std::cout << "EXP: get next token" << '\n';
			t = ts.get();
			break;
		case '-':       // subtraction
			if (output_trace) std::cout << "EXP: subtract, getting term" << '\n';
			left -= term();
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
}

//-------------------------------------------------------------------

void clean_up_mess()
{
	ts.ignore(print);
}
