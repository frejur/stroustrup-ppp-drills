#ifndef CALC_H
#define CALC_H
#include "../roman/roman.h"
#include <string>
#include <vector>

namespace calc {

constexpr bool output_trace{false}; // debug

// various tokens with descriptive names
constexpr char prompt{'>'};
constexpr char result_sign{'='};
constexpr char number{'8'};
constexpr char roman{'R'};
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

inline const std::vector<std::string>& available_fn()
{
	static std::vector<std::string> v{sqrt_word, pow_word};
	return v;
}

//------------------------------------------------------------------------------

enum class Result_type { Floating_point_value, Integer_value, Roman_numeral };

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
		} else {
			val_rom.change_value(static_cast<int>(v));
		}
	};
	Result(Result_type t, int v)
	    : Result(t, static_cast<double>(v)){}; // TODO: Find a solution without
	                                           // needless conversion
	Result(Result_type t, const std::string& s)
	    : type(t)
	    , val_rom(s){};
	Result(Result_type t, romi::Roman_int r)
	    : type(t)
	    , val_rom(r){};
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
		case Result_type::Roman_numeral:
			val = static_cast<int>(val_rom.as_int());
			break;
		}
		return val;
	}
	Result_type type = Result_type::Floating_point_value;
	double val_dec = 0;
	int val_int = 0;
	romi::Roman_int val_rom;
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

class Variable_roman
{
public:
	std::string name;
	romi::Roman_int value;
	bool is_const; // CH07E03
};

class Variable_decimal
{
public:
	std::string name;
	double value;
	bool is_const;
};

class Symbol_table_roman
{
public:
	romi::Roman_int get(std::string name);
	void set(std::string name, romi::Roman_int val);
	romi::Roman_int declare(std::string name,
	                        romi::Roman_int val,
	                        bool is_const);
	bool is_declared(std::string name);

private:
	std::vector<Variable_roman> var_table;
};

class Symbol_table_decimal
{
public:
	double get(std::string name);
	void set(std::string name, double val);
	double declare(std::string name, double val, bool is_const);
	bool is_declared(std::string name);

private:
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
enum class Calculator_version { Decimal, Roman };

class Token_stream
{
public:
	Token_stream(Calculator_version v
	             = Calculator_version::Decimal); // read tokens from std::cin
	Token get(bool peek = false); // get next token in stream. CH07E02, peek bool
	Token peek();                 // CH07E02 get next token without consuming it
	void putback(Token t);        // put back token, put into buffer
	void ignore(char c);          // discard all up to and including c
	Token getBuffer();
	char skipto_break_nonws(); // CH07E05, consume whitespace and return '\n'
	                           // or non-whitespace char
	// Symbol table
	Result get(std::string name)
	{
		if (ver == Calculator_version::Decimal) {
			return {Result_type::Floating_point_value, sym_dec.get(name)};
		} else {
			return {Result_type::Roman_numeral, sym_rom.get(name)};
		}
	}
	void set(std::string name, Result val)
	{
		if (ver == Calculator_version::Decimal) {
			sym_dec.set(name, val.val_dec);
		} else {
			sym_rom.set(name, val.val_rom);
		}
	}
	Result declare(std::string name, Result val, bool is_const)
	{
		if (ver == Calculator_version::Decimal) {
			return {Result_type::Floating_point_value,
			        sym_dec.declare(name, val.val_dec, is_const)};
		} else {
			return {Result_type::Roman_numeral,
			        sym_rom.declare(name, val.val_rom, is_const)};
		}
	}
	bool is_declared(std::string name);
	Calculator_version version() const { return ver; };

private:
	bool full;    // full when token in buffer
	Token buffer; // keep tokens that are put back
	Calculator_version ver;
	Symbol_table_decimal sym_dec;
	Symbol_table_roman sym_rom;
};

//------------------------------------------------------------------------------

void print_greeting();       // program greeting / info string
void print_greeting_latin(); // program greeting / info string
void print_instructions();
void print_instructions_latin();

void calculate(Token_stream& ts);      // parse and evaluate input
Result statement(Token_stream& ts);    // read and evaluate a Statement
Result declaration(Token_stream& ts);  // read and evaluate a Declaration
Result redefinition(Token_stream& ts); // CH07E02 redefine a variable
Result expression(Token_stream& ts);   // read and evaluate an Expression
Result term(Token_stream& ts);         // read and evaluate a Term
Result primary(Token_stream& ts);      // read and evaluate a Primary

void clean_up_mess(Token_stream& ts); // discard invalid input from stream

void run(Calculator_version v = Calculator_version::Decimal); // Main loop

int hextodec(std::string hex);

} // namespace calc

#endif // CALC_H
