#ifndef TEST_INTERACTIVE_H
#define TEST_INTERACTIVE_H

#include <iostream>
#include <string>
#include "../money/money.h"

const std::string Key_help{ "help" };
const std::string Key_quit{ "quit" };
const std::string Key_currencies{ "currencies" };
const std::string Key_operators{ "operators" };

const std::string Symbol_prompt{ "> " };
const std::string Symbol_result{ "= " };

void test_interactive();
void setup_session(Money_lib::Monetary_math_session& s);

void print_intro();
void print_more_info();
void print_currencies(const Money_lib::Monetary_math_session& session);
void print_operators();

void clear_buffer(std::istream& is);
std::string string_until_newline(std::istream& is);
void putback_string(const std::string& s, std::istream& is);
int word_count(const std::string& s, int max=5);

Money_lib::Money_Operator get_operator_by_symbol(const std::string& s);

// Money_Expression ------------------------------------------------------------
// Deals with all the parsing and evaluation

enum class Money_Expression_Type{ Money_Money, Money_Value };
enum class Money_Result_Type{ Money, Decimal_Number, Boolean };

class Money_Expression{
public:
	Money_Expression(Money_lib::Monetary_math_session& s, std::istream& is)
		: session{ s }, istr{ is }, money_a{ s.new_money() },
		money_b{ s.new_money() }
	{}
	void reset() { parse_success = false; eval_success = false; error = "";
	               reverse_terms = false; };
	void parse_money_money(); // "1 USD + 2 EUR", etc.
	void parse_money_value(bool reverse=false); // "2 * 1 EUR", etc.
	void evaluate();
	Money_lib::Money result_as_money() const {
		error_if_eval_failed();
		return session.new_money(result_money_amt, result_money_cur.id);
	};
	long double result_as_decimal_number() const {
		error_if_eval_failed();
		return result_val;
	};
	std::string result_as_true_or_false() const {
		error_if_eval_failed();
		return (result_comp ? "True" : "False");
	};
	bool is_parsed() const { return parse_success; };
	bool is_evaluated() const { return eval_success; };
	Money_Expression_Type expression_type() const { return expr_t; };
	Money_Result_Type result_type() const { return result_t; };
	const std::string& error_message() const { return error; };
private:
	Money_Expression_Type expr_t = Money_Expression_Type::Money_Money;
	Money_Result_Type result_t = Money_Result_Type::Money;
	Money_lib::Monetary_math_session& session;
	std::istream& istr;
	Money_lib::Money money_a;
	Money_lib::Money_Operator op{};
	Money_lib::Money money_b;
	long double val;
	bool parse_success = false;
	bool eval_success = false;
	bool reverse_terms = false;
	std::string error = "";

	// The book hasn't covered copy constructors so far, storing the amount
	// and currency
	long int result_money_amt = 0;
	Money_lib::Currency result_money_cur = Money_lib::DEFAULT_CURRENCY();


	long double result_val = 0;
	bool result_comp = false;
	void update_result(const Money_lib::Money& m);
	void error_if_eval_failed() const {
		if (!eval_success) {
			throw std::runtime_error("Cannot return a result for an expression "
			                         " that didn't evaluate properly");
		}
	}
};

//------------------------------------------------------------------------------

enum class Parser_Action_Type{
	Unknown=-1, Print_instructions, Quit, List_currencies, List_operators
};

struct Parser_Action{
public:
	Parser_Action_Type type{ Parser_Action_Type::Unknown };
	std::string buffer;
};

Parser_Action get_action(const std::string& input);

#endif // TEST_INTERACTIVE_H
