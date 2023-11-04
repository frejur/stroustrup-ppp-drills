#include "../lib/std_lib_facilities.h"

/*
Chapter 7, Try This

So, we feed the calculator a mix of correct and incorrect
expressions. For example:
1+2+3+4+5+6+7+8
1–2–3–4
!+2
(...)
Feed a few such “problematic” expressions to the
calculator and try to figure out in how many ways you can get it
to misbehave. Can you get it to crash, that is, to get it past
our error handling and give a machine error? We don’t think you
can. Can you get it to exit without a useful error message?
You can.
*/

constexpr bool output_trace{ false };
constexpr char prompt{ '>' };
constexpr char result{ '=' };

//-------------------------------------------------------------------

const char print = ';';

//-------------------------------------------------------------------

class Token {
public:
	char kind;
	double value;
	Token(char ch)
		:kind(ch), value(0) { }
	Token(char ch, double val)
		:kind(ch), value(val) { }
};

//-------------------------------------------------------------------

class Token_stream {
public:
	Token_stream();         // read tokens from std::cin
	Token get();            // get next token in stream
	void putback(Token t);  // put back token, put into buffer
	bool isFull();
	Token getBuffer();
private:
	bool full;              // full when token in buffer
	Token buffer;           // keep tokens that are put back
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

bool Token_stream::isFull() {
	return full ? true : false;
}

//-------------------------------------------------------------------

Token Token_stream::getBuffer() {
	full = false;
	return buffer;
}

//-------------------------------------------------------------------

Token Token_stream::get()
{
	if (isFull()) {
		if (output_trace) std::cout << "TOK: getting token from buffer\n";
		return getBuffer();
	}
	char ch;
	std::cin >> ch;

	switch (ch) {
	case ';':    // for "print"
	case 'q':    // for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		if (output_trace) std::cout << "TOK: operator '" << ch << "'" << '\n';
		return Token(ch);   // characters represent themselves
	case '.': case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);    // put digit back into input stream
		double val;
		std::cin >> val;
		if (output_trace) std::cout << "TOK: number " << val << '\n';
		return Token('#', val);
	}
	default:
		error("Bad token");
		break;
	}
}

//-------------------------------------------------------------------

Token_stream ts;

//-------------------------------------------------------------------

double expression();    // read and evaluate an Expression
double term();          // read and evaluate a Term
double primary();       // read and evaluate a Primary

//-------------------------------------------------------------------

int main()
	try {

	std::cout << "- Welcome to Just Another Calculator.\n"
		<< "- - Please enter expressions using"
		<< " floating-point numbers.\n"
		<< "- - The following arithmetic operators are"
		<< " available: '-', '+', '/', '*'\n"
		<< "- - Use parentheses for grouping.\n"
		<< "- - Enter '" << print << "' to terminate and"
		<< " print out an expression. Enter 'q' to exit\n";

	while (std::cin) {
		std::cout << prompt << ' ';
		Token t = ts.get();
		while (t.kind == ';') t = ts.get(); // eat print tokens
		if (t.kind == 'q') break;
		ts.putback(t);
		std::cout << result << ' ' << expression() << '\n';
	 }
	keep_window_open();
	return 0;
}
catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "exception" << '\n';
	keep_window_open();
	return 2;
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
	case '#':   // number
		if (output_trace) std::cout << "PRI: found #: " << t.value << '\n';
		return t.value;
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
