#ifndef CALC_H
#define CALC_H
#include <string>
#include <vector>

namespace calc {

constexpr bool output_trace{false}; // debug

// various tokens with descriptive names
constexpr char prompt{'>'};
constexpr char result{'='};
constexpr char number{'8'};
constexpr char print{';'};

constexpr char name{'a'};            // variable name token
constexpr char let{'L'};             // declaration token
constexpr char const_token{'C'};     // CH07E03
const std::string declkey{"let"};    // declaration keyword
const std::string constkey{"const"}; // CH07E03
constexpr char assign{'='};          // assignment token

// help
constexpr char help_token{'h'}; // CH07E06
const std::string help_key{"help"};

// quitting
constexpr char quit_token{'q'};
const std::string quit_key{"quit"};

// squareroot
const std::string sqrt_word{"sqrt"}; // keyword
constexpr char sqrt_token{'s'};      // token

// power of
const std::string pow_word{"pow"}; // keyword
constexpr char pow_token{'p'};     // token

// hexadecimals, CH07E09
const std::string hex_prefix{"0x"};
const char hex_token{'X'};

inline const std::vector<std::string> available_fn()
{
	static std::vector<std::string> v{sqrt_word, pow_word};
	return v;
}

//------------------------------------------------------------------------------

class Variable
{
public:
	std::string name;
	int value;
	bool is_const; // CH07E03
};

class Symbol_table
{
public:
	int get(std::string name);
	void set(std::string name, int val);
	int declare(std::string name, int val, bool is_const);
	bool is_declared(std::string name);

private:
	std::vector<Variable> var_table;
};

//------------------------------------------------------------------------------

class Token
{
public:
	char kind;
	int value = 0;
	std::string name;
	Token(char ch)
	    : kind(ch)
	    , value(0){};
	Token(char ch, int val)
	    : kind(ch)
	    , value(val){};
	Token(char ch, std::string n)
	    : kind(ch)
	    , name(n){};
};

//------------------------------------------------------------------------------

class Token_stream
{
public:
	Token_stream();               // read tokens from std::cin
	Token get(bool peek = false); // get next token in stream. CH07E02, peek bool
	Token peek();                 // CH07E02 get next token without consuming it
	void putback(Token t);        // put back token, put into buffer
	void ignore(char c);          // discard all up to and including c
	Token getBuffer();
	char skipto_break_nonws(); // CH07E05, consume whitespace and return '\n'
	                           // or non-whitespace char
	Symbol_table sym;

private:
	bool full;    // full when token in buffer
	Token buffer; // keep tokens that are put back
};

//------------------------------------------------------------------------------

void print_greeting(); // program greeting / info string
void print_instructions();

void calculate(Token_stream& ts);   // parse and evaluate input
int statement(Token_stream& ts);    // read and evaluate a Statement
int declaration(Token_stream& ts);  // read and evaluate a Declaration
int redefinition(Token_stream& ts); // CH07E02 redefine a variable
int expression(Token_stream& ts);   // read and evaluate an Expression
int term(Token_stream& ts);         // read and evaluate a Term
int primary(Token_stream& ts);      // read and evaluate a Primary

void clean_up_mess(Token_stream& ts); // discard invalid input from stream

int run(); // Main loop

int hextodec(std::string hex);

} // namespace calc

#endif // CALC_H
