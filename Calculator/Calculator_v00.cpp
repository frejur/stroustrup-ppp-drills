#include "std_lib_facilities.h"

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
    Token_stream();         // read tokens from cin
    Token get();            // get next token in stream
    void putback(Token t);  // put back token, put into buffer
    bool isFull();
    Token getBuffer();
    void clearBuffer();
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
        return getBuffer();
    }
    char ch;
    cin >> ch;

    switch (ch) {
    case ';':    // for "print"
    case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        cout << "TOK: operator '" << ch << "'" << '\n';
        return Token(ch);   // characters represent themselves
    case '.': case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);    // put digit back into input stream
        double val;
        cin >> val;
        cout << "TOK: number " << val << '\n';
        return Token('#', val);
    }
    default:
        error("Bad token");
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
    int val = 0;
    while (cin) {
        Token t = ts.get();

        if (t.kind == 'q') break;
        if (t.kind == ';') {
            cout << "=" << val << '\n';
        } else {
            ts.putback(t);
        }
        val = expression();
    }
    keep_window_open("~0");
}
catch (exception& e) {
    cerr << e.what() << endl;
    keep_window_open("~1");
    return 1;
}
catch (...) {
    cerr << "exception" << '\s' << '\n';
    keep_window_open("~2");
    return 2;
}

//-------------------------------------------------------------------

double primary() {
    cout << "PRI: get token" << '\n';
    Token t = ts.get();
    switch (t.kind) {
        case '(':   // expression
        {
            cout << "PRI: found '(', get expression" << '\n';
            double exp = expression();
            cout << "PRI: eof expression, expecting ')'" << '\n';
            t = ts.get();
            if (t.kind != ')') error("expected ')'");
            return exp;
         }
        case '#':   // number
            cout << "PRI: found #: " << t.value << '\n';
            return t.value;
        default:
            error("expected Primary");
    }
}

//-------------------------------------------------------------------

double term() {
    cout << "TER: get primary" << '\n';
    double left = primary();

    cout << "TER: get next token" << '\n';
    Token t = ts.get();  // get next token

    while (true) {
        switch (t.kind) {
        case '*':       // multiply
            cout << "TER: multiply, getting primary" << '\n';
            left *= primary();
            cout << "TER: result of multiplication: " << left << '\n';
            cout << "TER: get next token" << '\n';
            t = ts.get();
            break;
        case '/':       // division
        {
            cout << "TER: divide, getting primary" << '\n';
            double prim = primary();
            if (prim == 0) error("divide by zero");
            left /= prim;
            cout << "TER: result of division: " << left << '\n';
            cout << "TER: get next token" << '\n';
            t = ts.get();
            break;
        }
        default:
            cout << "TER: put back" << t.kind << " into buffer" << '\n';
            ts.putback(t);
            cout << "TER: return result: " << left << '\n';
            return left;
        }
    }
}

//-------------------------------------------------------------------

double expression()
{
    cout << "EXP: get term" << '\n';
    double left = term();

    cout << "EXP: get next token" << '\n';
    Token t = ts.get();  // get next token
    while (true) {
        switch (t.kind) {
        case '+':       // addition
            cout << "EXP: add, getting term" << '\n';
            left += term();
            cout << "EXP: result of addition " << left << '\n';
            cout << "EXP: get next token" << '\n';
            t = ts.get();
            break;
        case '-':       // subtraction
            cout << "EXP: subtract, getting term" << '\n';
            left -= term();
            cout << "EXP: result of subtraction " << left << '\n';
            cout << "EXP: get next token" << '\n';
            t = ts.get();
            break;
        default:
            cout << "EXP: put back " << t.kind << " into buffer" << '\n';
            ts.putback(t);
            cout << "EXP: return result " << left << '\n';
            return left;
        }
    }
}

//-------------------------------------------------------------------
