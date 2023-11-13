#include "../../lib/std_lib_facilities.h"

// Chapter 6, Exercise 3
// Add factorial operator '!':
// - '!' must appear directly after primary n.
// - "Multiply all whole numbers from n down to 1"
// - Eg. 'n!' and n = 4 -> 4! = 4 * 3 * 2 * 1 = 24
// - n must be an integer (For this implementation).
// - '!' is of higher order of operations than '*', '/'.
// - '0!' evaluates to 1.

// Updated grammar:
// Expression:
// 		Term
//		Term '+' Expression
// Term:
//		Factorial
//		Term '*' Factorial
//		Term '/' Factorial
// Factorial
//		Primary
//		Primary "!"
//		(Scrolldown to E03FACTORIAL for the relevant code)
// Primary:
//		Number
//		"(" Expression ")"
//		"{" Expression "}"
// Number:
//		literal -> <double>

constexpr bool output_trace{ true };

double calc_factorial(double n) {
	if (n < 0) {
		error("Cannot calculate factorial for n < 0");
	}
	if (n == 0) {
		return 1;
	}
	int n_int{};
	try {
		n_int = narrow_cast<int>(n);
	} catch (...) {
		error("Factorials of floating-point values not supported");
	}
	double f{ (double)n_int };
	for (int i = n_int - 1; i > 0; --i) {
		f *= i;
	}
	return f;
}

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
    Token getBuffer();      // get buffer token and mark as not full
private:
    bool full;              // full when token in buffer
    Token buffer;           // keep tokens that are put back
};

//-------------------------------------------------------------------

Token_stream::Token_stream()
    :full(false), buffer(0)
{
}

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

Token Token_stream::get()
{
    if (full) {
        if (output_trace) std::cout << "TOK: getting token from buffer\n";
        return getBuffer();
    }
    char ch;
    std::cin >> ch;

    switch (ch) {
    case '=':    // for "print"
    case 'x':    // for "quit"
    case '{': case '}': case '(': case ')':
    case '+': case '-': case '*': case '/': case '!':
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
        break;
    }
    error("Bad token");
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
    std::cout << "Welcome to Just Another Calculator.\n"
        << "Please enter expressions using floating-point numbers.\n"
        << "The following arithmetic operators are available: '-', '+', '/', '*'\n"
        << "Use parentheses for grouping.\n"
        << "Enter '=' to terminate and print out an expression. Enter 'x' to exit\n";

    float val = 0;
    while (std::cin) {
        Token t = ts.get();

        if (t.kind == 'x') break;
        if (t.kind == '=') {
            std::cout << "=" << val << '\n';
        }
        else {
            ts.putback(t);
        }
        val = expression();
    }
    keep_window_open();
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    keep_window_open();
    return 1;
}
catch (...) {
    std::cerr << "std::exception" << ' ' << '\n';
    keep_window_open();
    return 2;
}

// E03FACTORIAL ----------------------------------------------------------------

double factorial() {
    if (output_trace) std::cout << "FAC: get primary" << '\n';
    double left{ primary() };
    if (output_trace) std::cout << "FAC: get next token" << '\n';
    Token t = ts.get();
    switch (t.kind) {
    case '!':   // factorial
    {
    	double f{ calc_factorial(left) };
        if (output_trace) std::cout << "FAC: found '!', return factorial of '" << left << "': " << f << '\n';
        return f;
    }
    default:
        if (output_trace) std::cout << "FAC: putback token: " << t.kind  << '\n';
        ts.putback(t);
        if (output_trace) std::cout << "FACE: return unaltered result of primary: " << left  << '\n';
        return left;
    }
}

//-------------------------------------------------------------------

double primary() {
    if (output_trace) std::cout << "PRI: get token" << '\n';
    Token t = ts.get();
    switch (t.kind) {
    // Exercise 2 --------------------------------------------------------------
    case '{':   // expression
    {
        if (output_trace) std::cout << "PRI: found '{', get expression" << '\n';
        double exp = expression();
        if (output_trace) std::cout << "PRI: eof expression, expecting '}'" << '\n';
        t = ts.get();
        if (t.kind != '}') error("expected '}'");
        return exp;
    }
    // -------------------------------------------------------------- Exercise 2
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
    if (output_trace) std::cout << "TER: get factorial" << '\n';
    double left = factorial();

    if (output_trace) std::cout << "TER: get next token" << '\n';
    Token t = ts.get();  // get next token

    while (true) {
        switch (t.kind) {
        case '*':       // multiply
            if (output_trace) std::cout << "TER: multiply, getting factorial" << '\n';
            left *= factorial();
            if (output_trace) std::cout << "TER: result of multiplication: " << left << '\n';
            if (output_trace) std::cout << "TER: get next token" << '\n';
            t = ts.get();
            break;
        case '/':       // division
        {
            if (output_trace) std::cout << "TER: divide, getting factorial" << '\n';
            double prim = factorial();
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

//-------------------------------------------------------------------
